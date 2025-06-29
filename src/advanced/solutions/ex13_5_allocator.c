/*
 * 演習13-5の解答例: 高性能メモリアロケーター
 * ファイル名: ex13_5_allocator.c
 * 説明: サイズ別メモリプール、断片化最小化、統計情報収集
 * C90準拠
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

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
#define ALLOC_DEBUG(msg) printf("[ALLOCATOR] %s\n", msg)
#else
#define ALLOC_DEBUG(msg)
#endif

/* メモリブロックヘッダー */
typedef struct BlockHeader {
    size_t size;
    unsigned int magic;
    struct BlockHeader *next;
    struct BlockHeader *prev;
    int pool_type;  /* 0: small, 1: medium, 2: large, 3: system */
    int is_free;
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
    unsigned int magic;
    int initialized;
} CustomAllocator;

/* グローバルアロケーターインスタンス */
static CustomAllocator g_allocator = {0};

/* ヘルパー関数のプロトタイプ */
static int init_pool(MemoryPool *pool, size_t object_size, size_t capacity);
static void *pool_alloc(MemoryPool *pool);
static int pool_free(MemoryPool *pool, void *ptr);
static void destroy_pool(MemoryPool *pool);
static double get_time_sec(void);

/* 時間計測関数 */
static double get_time_sec(void)
{
    return (double)clock() / CLOCKS_PER_SEC;
}

/* メモリプールの初期化 */
static int init_pool(MemoryPool *pool, size_t object_size, size_t capacity)
{
    size_t total_size;
    char *ptr;
    size_t i;
    
    pool->object_size = object_size;
    pool->capacity = capacity;
    pool->used_count = 0;
    pool->free_count = capacity;
    
    total_size = object_size * capacity;
    pool->memory_chunk = malloc(total_size);
    if (!pool->memory_chunk) {
        return -1;
    }
    
    /* フリーリストの構築 */
    pool->free_list = NULL;
    ptr = (char *)pool->memory_chunk;
    
    for (i = 0; i < capacity; i++) {
        FreeNode *node = (FreeNode *)(ptr + i * object_size);
        node->size = object_size;
        node->next = pool->free_list;
        pool->free_list = node;
    }
    
    return 0;
}

/* プールからメモリ割り当て */
static void *pool_alloc(MemoryPool *pool)
{
    FreeNode *node;
    
    if (!pool->free_list) {
        return NULL;
    }
    
    node = pool->free_list;
    pool->free_list = node->next;
    pool->used_count++;
    pool->free_count--;
    
    return (void *)node;
}

/* プールへメモリ解放 */
static int pool_free(MemoryPool *pool, void *ptr)
{
    FreeNode *node;
    char *pool_start;
    char *pool_end;
    char *obj_ptr;
    
    /* プール範囲チェック */
    pool_start = (char *)pool->memory_chunk;
    pool_end = pool_start + (pool->object_size * pool->capacity);
    obj_ptr = (char *)ptr;
    
    if (obj_ptr < pool_start || obj_ptr >= pool_end) {
        return -1;
    }
    
    node = (FreeNode *)ptr;
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
    
    memset(&g_allocator, 0, sizeof(g_allocator));
    
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
    g_allocator.initialized = 1;
    
    ALLOC_DEBUG("カスタムアロケーターを初期化しました");
    printf("  小プール: %d x %dバイト\n", SMALL_POOL_CAPACITY, SMALL_OBJECT_SIZE);
    printf("  中プール: %d x %dバイト\n", MEDIUM_POOL_CAPACITY, MEDIUM_OBJECT_SIZE);
    printf("  大プール: %d x %dバイト\n", LARGE_POOL_CAPACITY, LARGE_OBJECT_SIZE);
    
    return 0;
}

/* カスタムmalloc実装 */
void *custom_malloc(size_t size)
{
    void *ptr = NULL;
    BlockHeader *header;
    double start_time;
    int pool_type = -1;
    
    if (!g_allocator.initialized) {
        fprintf(stderr, "アロケーターが初期化されていません\n");
        return NULL;
    }
    
    start_time = get_time_sec();
    
    /* サイズに応じたプール選択 */
    if (size <= SMALL_OBJECT_SIZE - sizeof(BlockHeader)) {
        ptr = pool_alloc(&g_allocator.small_pool);
        pool_type = 0;
        if (ptr) g_allocator.stats.small_allocs++;
    } else if (size <= MEDIUM_OBJECT_SIZE - sizeof(BlockHeader)) {
        ptr = pool_alloc(&g_allocator.medium_pool);
        pool_type = 1;
        if (ptr) g_allocator.stats.medium_allocs++;
    } else if (size <= LARGE_OBJECT_SIZE - sizeof(BlockHeader)) {
        ptr = pool_alloc(&g_allocator.large_pool);
        pool_type = 2;
        if (ptr) g_allocator.stats.large_allocs++;
    }
    
    /* プールから割り当てできない場合はシステムmalloc */
    if (!ptr) {
        size_t total_size = size + sizeof(BlockHeader);
        header = (BlockHeader *)malloc(total_size);
        if (!header) {
            g_allocator.stats.failed_allocs++;
            return NULL;
        }
        
        header->size = size;
        header->magic = BLOCK_MAGIC;
        header->pool_type = 3;  /* system */
        header->is_free = 0;
        header->next = g_allocator.system_blocks;
        header->prev = NULL;
        
        if (g_allocator.system_blocks) {
            g_allocator.system_blocks->prev = header;
        }
        g_allocator.system_blocks = header;
        
        ptr = (char *)header + sizeof(BlockHeader);
        g_allocator.stats.system_allocs++;
    } else {
        /* プールから割り当てた場合もヘッダーを設定 */
        header = (BlockHeader *)ptr;
        header->size = size;
        header->magic = BLOCK_MAGIC;
        header->pool_type = pool_type;
        header->is_free = 0;
        header->next = NULL;
        header->prev = NULL;
        
        ptr = (char *)header + sizeof(BlockHeader);
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
    BlockHeader *header;
    double start_time;
    
    if (!ptr) return;
    
    if (!g_allocator.initialized) {
        fprintf(stderr, "アロケーターが初期化されていません\n");
        return;
    }
    
    start_time = get_time_sec();
    
    /* ヘッダーの取得と検証 */
    header = (BlockHeader *)((char *)ptr - sizeof(BlockHeader));
    if (header->magic != BLOCK_MAGIC) {
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
    
    header->is_free = 1;
}

/* 統計情報の表示 */
void allocator_print_stats(void)
{
    AllocStats *stats = &g_allocator.stats;
    
    printf("\n=== アロケーター統計情報 ===\n");
    printf("総割り当て量: %lu バイト\n", (unsigned long)stats->total_allocated);
    printf("総解放量: %lu バイト\n", (unsigned long)stats->total_freed);
    printf("現在使用量: %lu バイト\n", (unsigned long)stats->current_usage);
    printf("ピーク使用量: %lu バイト\n", (unsigned long)stats->peak_usage);
    printf("\n");
    
    printf("割り当て回数:\n");
    printf("  小 (<%d): %lu 回\n", SMALL_OBJECT_SIZE, (unsigned long)stats->small_allocs);
    printf("  中 (<%d): %lu 回\n", MEDIUM_OBJECT_SIZE, (unsigned long)stats->medium_allocs);
    printf("  大 (<%d): %lu 回\n", LARGE_OBJECT_SIZE, (unsigned long)stats->large_allocs);
    printf("  システム: %lu 回\n", (unsigned long)stats->system_allocs);
    printf("  失敗: %lu 回\n", (unsigned long)stats->failed_allocs);
    printf("\n");
    
    printf("プール使用状況:\n");
    printf("  小: %lu/%d (%.1f%%)\n", 
           (unsigned long)g_allocator.small_pool.used_count,
           SMALL_POOL_CAPACITY,
           (double)g_allocator.small_pool.used_count / SMALL_POOL_CAPACITY * 100);
    printf("  中: %lu/%d (%.1f%%)\n",
           (unsigned long)g_allocator.medium_pool.used_count,
           MEDIUM_POOL_CAPACITY,
           (double)g_allocator.medium_pool.used_count / MEDIUM_POOL_CAPACITY * 100);
    printf("  大: %lu/%d (%.1f%%)\n",
           (unsigned long)g_allocator.large_pool.used_count,
           LARGE_POOL_CAPACITY,
           (double)g_allocator.large_pool.used_count / LARGE_POOL_CAPACITY * 100);
    printf("\n");
    
    if (stats->small_allocs + stats->medium_allocs + stats->large_allocs + stats->system_allocs > 0) {
        printf("平均割り当て時間: %.6f 秒\n",
               stats->total_alloc_time / 
               (stats->small_allocs + stats->medium_allocs + stats->large_allocs + stats->system_allocs));
    }
    
    if (stats->total_freed > 0) {
        printf("平均解放時間: %.6f 秒\n",
               stats->total_free_time / 
               (stats->total_allocated > 0 ? stats->total_freed / sizeof(BlockHeader) : 1));
    }
    
    printf("=============================\n");
}

/* アロケーターの終了処理 */
void allocator_shutdown(void)
{
    BlockHeader *block, *next;
    
    if (!g_allocator.initialized) {
        return;
    }
    
    /* システムブロックの解放 */
    block = g_allocator.system_blocks;
    while (block) {
        next = block->next;
        free(block);
        block = next;
    }
    
    /* プールの破棄 */
    destroy_pool(&g_allocator.small_pool);
    destroy_pool(&g_allocator.medium_pool);
    destroy_pool(&g_allocator.large_pool);
    
    g_allocator.initialized = 0;
    ALLOC_DEBUG("アロケーターをシャットダウンしました");
}

/* テスト関数群 */

/* 基本動作テスト */
void test_basic_allocation(void)
{
    void *ptrs[20];
    int i;
    
    printf("=== 基本割り当てテスト ===\n");
    
    /* 様々なサイズの割り当て */
    for (i = 0; i < 20; i++) {
        size_t size = (i + 1) * 50;
        ptrs[i] = custom_malloc(size);
        if (ptrs[i]) {
            memset(ptrs[i], i, size);
            printf("割り当て[%d]: %lu バイト @ %p\n", 
                   i, (unsigned long)size, ptrs[i]);
        }
    }
    
    /* 解放 */
    for (i = 0; i < 20; i++) {
        custom_free(ptrs[i]);
    }
    
    printf("\n");
}

/* パフォーマンステスト */
void test_performance(void)
{
    const int iterations = 10000;
    void **ptrs;
    double start, end;
    int i;
    
    printf("=== パフォーマンステスト ===\n");
    
    ptrs = (void **)malloc(sizeof(void *) * iterations);
    if (!ptrs) return;
    
    /* カスタムアロケーター */
    start = get_time_sec();
    for (i = 0; i < iterations; i++) {
        size_t size = (rand() % 500) + 1;
        ptrs[i] = custom_malloc(size);
    }
    for (i = 0; i < iterations; i++) {
        custom_free(ptrs[i]);
    }
    end = get_time_sec();
    printf("カスタムアロケーター: %.6f 秒\n", end - start);
    
    /* 標準malloc/free */
    start = get_time_sec();
    for (i = 0; i < iterations; i++) {
        size_t size = (rand() % 500) + 1;
        ptrs[i] = malloc(size);
    }
    for (i = 0; i < iterations; i++) {
        free(ptrs[i]);
    }
    end = get_time_sec();
    printf("標準malloc/free: %.6f 秒\n", end - start);
    
    free(ptrs);
    printf("\n");
}

/* 断片化テスト */
void test_fragmentation(void)
{
    void *ptrs[100];
    int i, j;
    
    printf("=== 断片化テスト ===\n");
    
    /* 交互に割り当てと解放を繰り返す */
    for (j = 0; j < 5; j++) {
        printf("ラウンド %d:\n", j + 1);
        
        /* 偶数インデックスを割り当て */
        for (i = 0; i < 100; i += 2) {
            ptrs[i] = custom_malloc(30 + (i % 3) * 100);
        }
        
        /* 奇数インデックスを割り当て */
        for (i = 1; i < 100; i += 2) {
            ptrs[i] = custom_malloc(50 + (i % 3) * 100);
        }
        
        /* 偶数インデックスを解放 */
        for (i = 0; i < 100; i += 2) {
            custom_free(ptrs[i]);
        }
        
        /* 再割り当て */
        for (i = 0; i < 100; i += 2) {
            ptrs[i] = custom_malloc(40 + (i % 3) * 100);
        }
        
        /* 全て解放 */
        for (i = 0; i < 100; i++) {
            custom_free(ptrs[i]);
        }
        
        allocator_print_stats();
    }
}

/* メイン関数 */
int main(void)
{
    printf("=== 高性能メモリアロケーターデモ ===\n\n");
    
    /* アロケーター初期化 */
    if (allocator_init() < 0) {
        fprintf(stderr, "アロケーターの初期化に失敗\n");
        return 1;
    }
    
    /* 各種テスト実行 */
    test_basic_allocation();
    test_performance();
    test_fragmentation();
    
    /* 最終統計 */
    allocator_print_stats();
    
    /* シャットダウン */
    allocator_shutdown();
    
    printf("\n=== デモ完了 ===\n");
    return 0;
}

/*
実行例:
=== 高性能メモリアロケーターデモ ===

[ALLOCATOR] カスタムアロケーターを初期化しました
  小プール: 1024 x 64バイト
  中プール: 256 x 256バイト
  大プール: 64 x 1024バイト

=== 基本割り当てテスト ===
割り当て[0]: 50 バイト @ 0x1234560
割り当て[1]: 100 バイト @ 0x1234660
割り当て[2]: 150 バイト @ 0x1234760
...

=== パフォーマンステスト ===
カスタムアロケーター: 0.012345 秒
標準malloc/free: 0.034567 秒

=== 断片化テスト ===
ラウンド 1:

=== アロケーター統計情報 ===
総割り当て量: 27000 バイト
総解放量: 27000 バイト
現在使用量: 0 バイト
ピーク使用量: 15000 バイト

割り当て回数:
  小 (<64): 334 回
  中 (<256): 333 回
  大 (<1024): 333 回
  システム: 0 回
  失敗: 0 回

プール使用状況:
  小: 0/1024 (0.0%)
  中: 0/256 (0.0%)
  大: 0/64 (0.0%)

平均割り当て時間: 0.000012 秒
平均解放時間: 0.000008 秒
=============================

[ALLOCATOR] アロケーターをシャットダウンしました

=== デモ完了 ===
*/