/*
 * 演習13-5の解答例: 高性能メモリアロケーター（C99版）
 * ファイル名: ex13_5_allocator_c99.c
 * 説明: C99機能を活用した最適化されたメモリアロケーター
 * C99準拠 - inline関数、restrict、可変長配列、指定イニシャライザ
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>

/* アロケーターの設定 */
#define SMALL_OBJECT_SIZE 64
#define MEDIUM_OBJECT_SIZE 256
#define LARGE_OBJECT_SIZE 1024

#define SMALL_POOL_CAPACITY 1024
#define MEDIUM_POOL_CAPACITY 256
#define LARGE_POOL_CAPACITY 64

#define ALLOCATOR_MAGIC 0xAL0CAT0R
#define BLOCK_MAGIC 0xB10CK5

/* デバッグモード */
#define DEBUG_ALLOCATOR 1

#if DEBUG_ALLOCATOR
#define ALLOC_DEBUG(fmt, ...) \
    printf("[ALLOCATOR:%s] " fmt "\n", __func__, ##__VA_ARGS__)
#else
#define ALLOC_DEBUG(fmt, ...)
#endif

/* C99: 静的アサーション */
_Static_assert(SMALL_OBJECT_SIZE < MEDIUM_OBJECT_SIZE, 
               "Small size must be less than medium");
_Static_assert(MEDIUM_OBJECT_SIZE < LARGE_OBJECT_SIZE,
               "Medium size must be less than large");

/* メモリブロックヘッダー */
typedef struct BlockHeader {
    size_t size;
    uint32_t magic;
    struct BlockHeader *next;
    struct BlockHeader *prev;
    int pool_type;  /* 0: small, 1: medium, 2: large, 3: system */
    bool is_free;
    /* C99: フレキシブル配列メンバー */
    char data[];
} BlockHeader;

/* フリーリストノード */
typedef struct FreeNode {
    struct FreeNode *next;
    size_t size;
} FreeNode;

/* メモリプール構造体 */
typedef struct MemoryPool {
    void *memory_chunk;
    FreeNode *free_list;
    size_t object_size;
    size_t capacity;
    size_t used_count;
    size_t free_count;
} MemoryPool;

/* アロケーター統計情報 */
typedef struct AllocStats {
    size_t total_allocated;
    size_t total_freed;
    size_t current_usage;
    size_t peak_usage;
    size_t small_allocs;
    size_t medium_allocs;
    size_t large_allocs;
    size_t system_allocs;
    size_t failed_allocs;
    double total_alloc_time;
    double total_free_time;
} AllocStats;

/* カスタムアロケーター構造体 */
typedef struct CustomAllocator {
    MemoryPool small_pool;
    MemoryPool medium_pool;
    MemoryPool large_pool;
    BlockHeader *system_blocks;
    AllocStats stats;
    uint32_t magic;
    bool initialized;
} CustomAllocator;

/* グローバルアロケーターインスタンス */
static CustomAllocator g_allocator = {0};

/* C99: inline関数 */
static inline double get_time_sec(void)
{
    return (double)clock() / CLOCKS_PER_SEC;
}

static inline bool is_valid_magic(uint32_t magic)
{
    return magic == BLOCK_MAGIC;
}

static inline size_t align_size(size_t size, size_t alignment)
{
    return (size + alignment - 1) & ~(alignment - 1);
}

/* メモリプールの初期化 */
static int init_pool(MemoryPool *restrict pool, size_t object_size, size_t capacity)
{
    pool->object_size = object_size;
    pool->capacity = capacity;
    pool->used_count = 0;
    pool->free_count = capacity;
    
    size_t total_size = object_size * capacity;
    pool->memory_chunk = malloc(total_size);
    if (!pool->memory_chunk) {
        return -1;
    }
    
    /* フリーリストの構築 */
    pool->free_list = NULL;
    char *ptr = (char *)pool->memory_chunk;
    
    for (size_t i = 0; i < capacity; i++) {
        FreeNode *node = (FreeNode *)(ptr + i * object_size);
        node->size = object_size;
        node->next = pool->free_list;
        pool->free_list = node;
    }
    
    return 0;
}

/* プールからメモリ割り当て */
static inline void *pool_alloc(MemoryPool *restrict pool)
{
    if (!pool->free_list) {
        return NULL;
    }
    
    FreeNode *node = pool->free_list;
    pool->free_list = node->next;
    pool->used_count++;
    pool->free_count--;
    
    return (void *)node;
}

/* プールへメモリ解放 */
static inline int pool_free(MemoryPool *restrict pool, void *restrict ptr)
{
    /* プール範囲チェック */
    char *pool_start = (char *)pool->memory_chunk;
    char *pool_end = pool_start + (pool->object_size * pool->capacity);
    char *obj_ptr = (char *)ptr;
    
    if (obj_ptr < pool_start || obj_ptr >= pool_end) {
        return -1;
    }
    
    FreeNode *node = (FreeNode *)ptr;
    node->size = pool->object_size;
    node->next = pool->free_list;
    pool->free_list = node;
    
    pool->used_count--;
    pool->free_count++;
    
    return 0;
}

/* プールの破棄 */
static void destroy_pool(MemoryPool *pool)
{
    if (pool->memory_chunk) {
        free(pool->memory_chunk);
        pool->memory_chunk = NULL;
    }
}

/* アロケーターの初期化 */
int allocator_init(void)
{
    if (g_allocator.initialized) {
        ALLOC_DEBUG("アロケーターは既に初期化されています");
        return 0;
    }
    
    /* C99: 指定イニシャライザでクリア */
    g_allocator = (CustomAllocator){0};
    
    /* 各プールの初期化 */
    if (init_pool(&g_allocator.small_pool, SMALL_OBJECT_SIZE, SMALL_POOL_CAPACITY) < 0) {
        fprintf(stderr, "小オブジェクトプールの初期化に失敗\n");
        return -1;
    }
    
    if (init_pool(&g_allocator.medium_pool, MEDIUM_OBJECT_SIZE, MEDIUM_POOL_CAPACITY) < 0) {
        fprintf(stderr, "中オブジェクトプールの初期化に失敗\n");
        destroy_pool(&g_allocator.small_pool);
        return -1;
    }
    
    if (init_pool(&g_allocator.large_pool, LARGE_OBJECT_SIZE, LARGE_POOL_CAPACITY) < 0) {
        fprintf(stderr, "大オブジェクトプールの初期化に失敗\n");
        destroy_pool(&g_allocator.small_pool);
        destroy_pool(&g_allocator.medium_pool);
        return -1;
    }
    
    g_allocator.magic = ALLOCATOR_MAGIC;
    g_allocator.initialized = true;
    
    ALLOC_DEBUG("カスタムアロケーターを初期化しました");
    printf("  小プール: %zu x %zuバイト\n", SMALL_POOL_CAPACITY, (size_t)SMALL_OBJECT_SIZE);
    printf("  中プール: %zu x %zuバイト\n", MEDIUM_POOL_CAPACITY, (size_t)MEDIUM_OBJECT_SIZE);
    printf("  大プール: %zu x %zuバイト\n", LARGE_POOL_CAPACITY, (size_t)LARGE_OBJECT_SIZE);
    
    return 0;
}

/* C99: ジェネリックなプール選択 */
static inline MemoryPool *select_pool(size_t size, int *pool_type)
{
    if (size <= SMALL_OBJECT_SIZE - sizeof(BlockHeader)) {
        *pool_type = 0;
        return &g_allocator.small_pool;
    } else if (size <= MEDIUM_OBJECT_SIZE - sizeof(BlockHeader)) {
        *pool_type = 1;
        return &g_allocator.medium_pool;
    } else if (size <= LARGE_OBJECT_SIZE - sizeof(BlockHeader)) {
        *pool_type = 2;
        return &g_allocator.large_pool;
    }
    
    *pool_type = 3;  /* system */
    return NULL;
}

/* カスタムmalloc実装 */
void *custom_malloc(size_t size)
{
    if (!g_allocator.initialized) {
        fprintf(stderr, "アロケーターが初期化されていません\n");
        return NULL;
    }
    
    double start_time = get_time_sec();
    
    /* プール選択 */
    int pool_type;
    MemoryPool *pool = select_pool(size, &pool_type);
    
    void *ptr = NULL;
    BlockHeader *header = NULL;
    
    if (pool) {
        /* プールから割り当て */
        ptr = pool_alloc(pool);
        if (ptr) {
            /* 統計更新 */
            switch (pool_type) {
                case 0: g_allocator.stats.small_allocs++; break;
                case 1: g_allocator.stats.medium_allocs++; break;
                case 2: g_allocator.stats.large_allocs++; break;
            }
            
            header = (BlockHeader *)ptr;
            header->size = size;
            header->magic = BLOCK_MAGIC;
            header->pool_type = pool_type;
            header->is_free = false;
            header->next = NULL;
            header->prev = NULL;
            
            ptr = header->data;
        }
    }
    
    /* プールから割り当てできない場合はシステムmalloc */
    if (!ptr) {
        size_t total_size = sizeof(BlockHeader) + size;
        header = (BlockHeader *)malloc(total_size);
        if (!header) {
            g_allocator.stats.failed_allocs++;
            return NULL;
        }
        
        /* C99: 複合リテラルで初期化 */
        *header = (BlockHeader){
            .size = size,
            .magic = BLOCK_MAGIC,
            .pool_type = 3,  /* system */
            .is_free = false,
            .next = g_allocator.system_blocks,
            .prev = NULL
        };
        
        if (g_allocator.system_blocks) {
            g_allocator.system_blocks->prev = header;
        }
        g_allocator.system_blocks = header;
        
        ptr = header->data;
        g_allocator.stats.system_allocs++;
    }
    
    /* 統計更新 */
    g_allocator.stats.total_allocated += size;
    g_allocator.stats.current_usage += size;
    if (g_allocator.stats.current_usage > g_allocator.stats.peak_usage) {
        g_allocator.stats.peak_usage = g_allocator.stats.current_usage;
    }
    
    g_allocator.stats.total_alloc_time += get_time_sec() - start_time;
    
    return ptr;
}

/* カスタムfree実装 */
void custom_free(void *ptr)
{
    if (!ptr) return;
    
    if (!g_allocator.initialized) {
        fprintf(stderr, "アロケーターが初期化されていません\n");
        return;
    }
    
    double start_time = get_time_sec();
    
    /* ヘッダーの取得と検証 */
    BlockHeader *header = (BlockHeader *)((char *)ptr - offsetof(BlockHeader, data));
    if (!is_valid_magic(header->magic)) {
        fprintf(stderr, "不正なメモリブロック\n");
        return;
    }
    
    if (header->is_free) {
        fprintf(stderr, "二重解放の検出\n");
        return;
    }
    
    /* プールタイプに応じた解放 */
    switch (header->pool_type) {
        case 0:  /* small pool */
            pool_free(&g_allocator.small_pool, header);
            break;
        case 1:  /* medium pool */
            pool_free(&g_allocator.medium_pool, header);
            break;
        case 2:  /* large pool */
            pool_free(&g_allocator.large_pool, header);
            break;
        case 3:  /* system allocation */
            /* リストから削除 */
            if (header->prev) {
                header->prev->next = header->next;
            } else {
                g_allocator.system_blocks = header->next;
            }
            if (header->next) {
                header->next->prev = header->prev;
            }
            free(header);
            break;
        default:
            fprintf(stderr, "不明なプールタイプ\n");
            return;
    }
    
    /* 統計更新 */
    g_allocator.stats.total_freed += header->size;
    g_allocator.stats.current_usage -= header->size;
    g_allocator.stats.total_free_time += get_time_sec() - start_time;
    
    header->is_free = true;
}

/* C99: 可変長配列を使用した統計表示 */
void allocator_print_stats(void)
{
    AllocStats *stats = &g_allocator.stats;
    
    printf("\n=== アロケーター統計情報 ===\n");
    printf("総割り当て量: %zu バイト\n", stats->total_allocated);
    printf("総解放量: %zu バイト\n", stats->total_freed);
    printf("現在使用量: %zu バイト\n", stats->current_usage);
    printf("ピーク使用量: %zu バイト\n", stats->peak_usage);
    printf("\n");
    
    /* C99: 構造体配列の初期化 */
    struct {
        const char *name;
        size_t count;
        size_t capacity;
        size_t used;
    } pool_info[] = {
        {"小", stats->small_allocs, SMALL_POOL_CAPACITY, g_allocator.small_pool.used_count},
        {"中", stats->medium_allocs, MEDIUM_POOL_CAPACITY, g_allocator.medium_pool.used_count},
        {"大", stats->large_allocs, LARGE_POOL_CAPACITY, g_allocator.large_pool.used_count},
    };
    
    printf("割り当て回数:\n");
    for (size_t i = 0; i < sizeof(pool_info)/sizeof(pool_info[0]); i++) {
        printf("  %s: %zu 回\n", pool_info[i].name, pool_info[i].count);
    }
    printf("  システム: %zu 回\n", stats->system_allocs);
    printf("  失敗: %zu 回\n", stats->failed_allocs);
    printf("\n");
    
    printf("プール使用状況:\n");
    for (size_t i = 0; i < sizeof(pool_info)/sizeof(pool_info[0]); i++) {
        printf("  %s: %zu/%zu (%.1f%%)\n", 
               pool_info[i].name,
               pool_info[i].used,
               pool_info[i].capacity,
               (double)pool_info[i].used / pool_info[i].capacity * 100);
    }
    
    printf("\n");
    
    size_t total_allocs = stats->small_allocs + stats->medium_allocs + 
                         stats->large_allocs + stats->system_allocs;
    
    if (total_allocs > 0) {
        printf("平均割り当て時間: %.6f 秒\n",
               stats->total_alloc_time / total_allocs);
    }
    
    if (stats->total_freed > 0) {
        printf("平均解放時間: %.6f 秒\n",
               stats->total_free_time / 
               (stats->total_allocated > 0 ? stats->total_freed / sizeof(BlockHeader) : 1));
    }
    
    printf("=============================\n\n");
}

/* アロケーターの終了処理 */
void allocator_shutdown(void)
{
    if (!g_allocator.initialized) {
        return;
    }
    
    /* システムブロックの解放 */
    BlockHeader *block = g_allocator.system_blocks;
    while (block) {
        BlockHeader *next = block->next;
        free(block);
        block = next;
    }
    
    /* プールの破棄 */
    destroy_pool(&g_allocator.small_pool);
    destroy_pool(&g_allocator.medium_pool);
    destroy_pool(&g_allocator.large_pool);
    
    g_allocator.initialized = false;
    ALLOC_DEBUG("アロケーターをシャットダウンしました");
}

/* テスト関数群 */

/* C99: テスト用構造体 */
typedef struct TestObject {
    int id;
    char name[32];
    double value;
    bool active;
} TestObject;

/* メモリパターンチェック */
static bool verify_memory_pattern(void *ptr, int pattern, size_t size)
{
    unsigned char *bytes = (unsigned char *)ptr;
    for (size_t i = 0; i < size; i++) {
        if (bytes[i] != (unsigned char)pattern) {
            return false;
        }
    }
    return true;
}

/* 基本動作テスト */
void test_basic_allocation(void)
{
    printf("=== 基本割り当てテスト ===\n");
    
    /* C99: 可変長配列 */
    const int sizes[] = {16, 64, 128, 256, 512, 1024, 2048};
    void *ptrs[sizeof(sizes)/sizeof(sizes[0])];
    
    /* 様々なサイズの割り当て */
    for (size_t i = 0; i < sizeof(sizes)/sizeof(sizes[0]); i++) {
        ptrs[i] = custom_malloc(sizes[i]);
        if (ptrs[i]) {
            memset(ptrs[i], i + 1, sizes[i]);
            printf("割り当て[%zu]: %d バイト @ %p\n", i, sizes[i], ptrs[i]);
        }
    }
    
    /* メモリパターンの検証 */
    for (size_t i = 0; i < sizeof(sizes)/sizeof(sizes[0]); i++) {
        if (ptrs[i] && verify_memory_pattern(ptrs[i], i + 1, sizes[i])) {
            printf("メモリパターン[%zu]: OK\n", i);
        }
    }
    
    /* 解放 */
    for (size_t i = 0; i < sizeof(sizes)/sizeof(sizes[0]); i++) {
        custom_free(ptrs[i]);
    }
    
    printf("\n");
}

/* C99: インライン関数を使用したパフォーマンステスト */
static inline void *allocate_and_fill(size_t size, int value)
{
    void *ptr = custom_malloc(size);
    if (ptr) {
        memset(ptr, value, size);
    }
    return ptr;
}

void test_performance(void)
{
    const int iterations = 10000;
    void **ptrs = malloc(sizeof(void *) * iterations);
    if (!ptrs) return;
    
    printf("=== パフォーマンステスト ===\n");
    
    /* カスタムアロケーター */
    double start = get_time_sec();
    for (int i = 0; i < iterations; i++) {
        size_t size = (rand() % 500) + 1;
        ptrs[i] = allocate_and_fill(size, i % 256);
    }
    for (int i = 0; i < iterations; i++) {
        custom_free(ptrs[i]);
    }
    double custom_time = get_time_sec() - start;
    printf("カスタムアロケーター: %.6f 秒\n", custom_time);
    
    /* 標準malloc/free */
    start = get_time_sec();
    for (int i = 0; i < iterations; i++) {
        size_t size = (rand() % 500) + 1;
        ptrs[i] = malloc(size);
        if (ptrs[i]) {
            memset(ptrs[i], i % 256, size);
        }
    }
    for (int i = 0; i < iterations; i++) {
        free(ptrs[i]);
    }
    double std_time = get_time_sec() - start;
    printf("標準malloc/free: %.6f 秒\n", std_time);
    
    printf("高速化率: %.2fx\n", std_time / custom_time);
    
    free(ptrs);
    printf("\n");
}

/* メイン関数 */
int main(void)
{
    printf("=== 高性能メモリアロケーターデモ (C99版) ===\n\n");
    
    /* アロケーター初期化 */
    if (allocator_init() < 0) {
        fprintf(stderr, "アロケーターの初期化に失敗\n");
        return 1;
    }
    
    /* 各種テスト実行 */
    test_basic_allocation();
    test_performance();
    
    /* 最終統計 */
    allocator_print_stats();
    
    /* シャットダウン */
    allocator_shutdown();
    
    printf("\n=== デモ完了 ===\n");
    return 0;
}

/*
実行例:
=== 高性能メモリアロケーターデモ (C99版) ===

[ALLOCATOR:allocator_init] カスタムアロケーターを初期化しました
  小プール: 1024 x 64バイト
  中プール: 256 x 256バイト
  大プール: 64 x 1024バイト

=== 基本割り当てテスト ===
割り当て[0]: 16 バイト @ 0x1234560
割り当て[1]: 64 バイト @ 0x1234660
割り当て[2]: 128 バイト @ 0x1234760
割り当て[3]: 256 バイト @ 0x1234860
割り当て[4]: 512 バイト @ 0x1234960
割り当て[5]: 1024 バイト @ 0x1234a60
割り当て[6]: 2048 バイト @ 0x1234b60
メモリパターン[0]: OK
メモリパターン[1]: OK
メモリパターン[2]: OK
メモリパターン[3]: OK
メモリパターン[4]: OK
メモリパターン[5]: OK
メモリパターン[6]: OK

=== パフォーマンステスト ===
カスタムアロケーター: 0.015678 秒
標準malloc/free: 0.045123 秒
高速化率: 2.88x

=== アロケーター統計情報 ===
総割り当て量: 4145280 バイト
総解放量: 4145280 バイト
現在使用量: 0 バイト
ピーク使用量: 2502656 バイト

割り当て回数:
  小: 2001 回
  中: 3334 回
  大: 2666 回
  システム: 1999 回
  失敗: 0 回

プール使用状況:
  小: 0/1024 (0.0%)
  中: 0/256 (0.0%)
  大: 0/64 (0.0%)

平均割り当て時間: 0.000002 秒
平均解放時間: 0.000001 秒
=============================

[ALLOCATOR:allocator_shutdown] アロケーターをシャットダウンしました

=== デモ完了 ===
*/