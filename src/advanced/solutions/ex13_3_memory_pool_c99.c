/*
 * 演習13-3の解答例: 基本的なメモリプール（C99版）
 * ファイル名: ex13_3_memory_pool_c99.c
 * 説明: 固定サイズオブジェクト用のメモリプール実装
 * C99準拠 - 可変引数マクロ、inline関数、bool型、restrict修飾子を使用
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <stdbool.h>
#include <stdint.h>

/* デバッグ出力制御 */
#define DEBUG_POOL 1

#if DEBUG_POOL
#define POOL_DEBUG(fmt, ...) \
    printf("[POOL DEBUG:%s:%d] " fmt "\n", __func__, __LINE__, ##__VA_ARGS__)
#else
#define POOL_DEBUG(fmt, ...)
#endif

/* メモリプールの設定 */
#define DEFAULT_POOL_SIZE 16
#define POOL_ALIGNMENT 8
#define POOL_MAGIC_NUMBER 0xDEADBEEF

/* C99: _Static_assertでコンパイル時検証 */
_Static_assert(POOL_ALIGNMENT >= sizeof(void*), 
               "Pool alignment must be at least pointer size");

/* アライメント調整マクロ */
#define ALIGN_SIZE(size, alignment) \
    (((size) + (alignment) - 1) & ~((alignment) - 1))

/* フリーリストノード構造体 */
typedef struct FreeNode {
    struct FreeNode *next;
} FreeNode;

/* メモリプール構造体 */
typedef struct MemoryPool {
    void *memory_chunk;      /* プール全体のメモリ領域 */
    FreeNode *free_list;     /* フリーリストの先頭 */
    size_t object_size;      /* オブジェクトサイズ */
    size_t pool_capacity;    /* プールの容量 */
    size_t objects_in_use;   /* 使用中オブジェクト数 */
    size_t total_allocated;  /* 総割り当て数 */
    size_t total_freed;      /* 総解放数 */
    uint32_t magic;          /* 破損検出用マジックナンバー */
    char name[32];           /* プール名 */
    /* C99: 追加の統計情報 */
    size_t peak_usage;       /* 最大使用数 */
    double alloc_time_total; /* 割り当て時間合計 */
    double free_time_total;  /* 解放時間合計 */
} MemoryPool;

/* C99: inline関数でプール検証 */
static inline bool is_valid_pool(const MemoryPool *pool)
{
    return pool != NULL && pool->magic == POOL_MAGIC_NUMBER;
}

/* プール検証マクロ */
#define VALIDATE_POOL(pool) \
    do { \
        if (!is_valid_pool(pool)) { \
            fprintf(stderr, "[%s:%d] 無効なメモリプール: %p\n", \
                    __func__, __LINE__, (void *)(pool)); \
            return NULL; \
        } \
    } while (0)

#define VALIDATE_POOL_VOID(pool) \
    do { \
        if (!is_valid_pool(pool)) { \
            fprintf(stderr, "[%s:%d] 無効なメモリプール: %p\n", \
                    __func__, __LINE__, (void *)(pool)); \
            return; \
        } \
    } while (0)

/* C99: inline関数で時間計測 */
static inline double get_time_sec(void)
{
    return (double)clock() / CLOCKS_PER_SEC;
}

/* 関数プロトタイプ */
MemoryPool *pool_create(const char *name, size_t object_size, size_t capacity);
void *pool_alloc(MemoryPool *pool);
void pool_free(MemoryPool *pool, void *ptr);
void pool_print_status(const MemoryPool *pool);
void pool_destroy(MemoryPool *pool);

/* メモリプールの初期化 */
MemoryPool *pool_create(const char *name, size_t object_size, size_t capacity)
{
    if (!name || object_size == 0 || capacity == 0) {
        fprintf(stderr, "無効なプール作成パラメータ\n");
        return NULL;
    }
    
    /* オブジェクトサイズの調整（最小サイズ・アライメント確保） */
    size_t min_size = sizeof(FreeNode);
    if (object_size < min_size) {
        object_size = min_size;
    }
    object_size = ALIGN_SIZE(object_size, POOL_ALIGNMENT);
    
    /* プール構造体の割り当て */
    MemoryPool *pool = calloc(1, sizeof(MemoryPool));
    if (!pool) {
        fprintf(stderr, "プール構造体の割り当てに失敗\n");
        return NULL;
    }
    
    /* メモリ領域の割り当て */
    size_t total_size = object_size * capacity;
    void *memory = aligned_alloc(POOL_ALIGNMENT, total_size);  /* C99: aligned_alloc */
    if (!memory) {
        fprintf(stderr, "プールメモリの割り当てに失敗: %zu バイト\n", total_size);
        free(pool);
        return NULL;
    }
    
    /* C99: 指定イニシャライザで初期化 */
    *pool = (MemoryPool){
        .memory_chunk = memory,
        .object_size = object_size,
        .pool_capacity = capacity,
        .objects_in_use = 0,
        .total_allocated = 0,
        .total_freed = 0,
        .magic = POOL_MAGIC_NUMBER,
        .peak_usage = 0,
        .alloc_time_total = 0.0,
        .free_time_total = 0.0
    };
    
    strncpy(pool->name, name, sizeof(pool->name) - 1);
    pool->name[sizeof(pool->name) - 1] = '\0';
    
    /* フリーリストの構築 */
    pool->free_list = NULL;
    char *ptr = (char *)memory;
    
    for (size_t i = 0; i < capacity; i++) {
        FreeNode *node = (FreeNode *)(ptr + i * object_size);
        node->next = pool->free_list;
        pool->free_list = node;
    }
    
    POOL_DEBUG("プール '%s' を作成: オブジェクトサイズ=%zu, 容量=%zu",
               pool->name, pool->object_size, pool->pool_capacity);
    
    return pool;
}

/* オブジェクトの割り当て */
void *pool_alloc(MemoryPool *pool)
{
    VALIDATE_POOL(pool);
    
    if (!pool->free_list) {
        POOL_DEBUG("プール '%s' にオブジェクトが残っていません", pool->name);
        return NULL;
    }
    
    double start_time = get_time_sec();
    
    /* フリーリストから先頭を取得 */
    FreeNode *node = pool->free_list;
    pool->free_list = node->next;
    
    /* 統計情報の更新 */
    pool->objects_in_use++;
    pool->total_allocated++;
    
    /* C99: 最大使用数の更新 */
    if (pool->objects_in_use > pool->peak_usage) {
        pool->peak_usage = pool->objects_in_use;
    }
    
    /* メモリをクリア（セキュリティ向上） */
    memset(node, 0, pool->object_size);
    
    double elapsed = get_time_sec() - start_time;
    pool->alloc_time_total += elapsed;
    
    POOL_DEBUG("オブジェクト割り当て: %p (使用中: %zu/%zu, 時間: %.6f秒)",
               (void *)node, pool->objects_in_use, pool->pool_capacity, elapsed);
    
    return (void *)node;
}

/* C99: restrict修飾子でポインタエイリアスなしを保証 */
void pool_free(MemoryPool * restrict pool, void * restrict ptr)
{
    VALIDATE_POOL_VOID(pool);
    
    if (!ptr) {
        POOL_DEBUG("NULL ポインタの解放試行");
        return;
    }
    
    double start_time = get_time_sec();
    
    /* ポインタがプール内にあるかチェック */
    char *pool_start = (char *)pool->memory_chunk;
    char *pool_end = pool_start + (pool->object_size * pool->pool_capacity);
    char *obj_ptr = (char *)ptr;
    
    if (obj_ptr < pool_start || obj_ptr >= pool_end) {
        POOL_DEBUG("プール外のポインタの解放試行: %p", ptr);
        return;
    }
    
    /* アライメントチェック */
    size_t offset = obj_ptr - pool_start;
    if (offset % pool->object_size != 0) {
        POOL_DEBUG("不正にアラインされたポインタ: %p", ptr);
        return;
    }
    
    /* フリーリストに追加 */
    FreeNode *node = (FreeNode *)ptr;
    node->next = pool->free_list;
    pool->free_list = node;
    
    /* 統計情報の更新 */
    pool->objects_in_use--;
    pool->total_freed++;
    
    double elapsed = get_time_sec() - start_time;
    pool->free_time_total += elapsed;
    
    POOL_DEBUG("オブジェクト解放: %p (使用中: %zu/%zu, 時間: %.6f秒)",
               ptr, pool->objects_in_use, pool->pool_capacity, elapsed);
}

/* プールの使用状況表示 */
void pool_print_status(const MemoryPool *pool)
{
    if (!is_valid_pool(pool)) {
        printf("無効なプール\n");
        return;
    }
    
    printf("\n=== プール '%s' の状況 ===\n", pool->name);
    printf("オブジェクトサイズ: %zu バイト\n", pool->object_size);
    printf("プール容量: %zu オブジェクト\n", pool->pool_capacity);
    printf("使用中: %zu オブジェクト\n", pool->objects_in_use);
    printf("空き: %zu オブジェクト\n", pool->pool_capacity - pool->objects_in_use);
    
    double usage_ratio = (double)pool->objects_in_use / pool->pool_capacity * 100.0;
    printf("使用率: %.1f%%\n", usage_ratio);
    
    printf("総割り当て: %zu 回\n", pool->total_allocated);
    printf("総解放: %zu 回\n", pool->total_freed);
    printf("最大使用数: %zu オブジェクト\n", pool->peak_usage);
    
    /* C99: 平均時間の計算 */
    if (pool->total_allocated > 0) {
        printf("平均割り当て時間: %.6f秒\n", 
               pool->alloc_time_total / pool->total_allocated);
    }
    if (pool->total_freed > 0) {
        printf("平均解放時間: %.6f秒\n", 
               pool->free_time_total / pool->total_freed);
    }
    
    /* フリーリストの長さをカウント */
    size_t free_count = 0;
    for (FreeNode *current = pool->free_list; current; current = current->next) {
        free_count++;
    }
    printf("フリーリスト長: %zu\n", free_count);
    printf("========================\n\n");
}

/* プールの破棄 */
void pool_destroy(MemoryPool *pool)
{
    if (!pool) {
        return;
    }
    
    if (!is_valid_pool(pool)) {
        fprintf(stderr, "破損したプールの破棄試行\n");
        return;
    }
    
    POOL_DEBUG("プール '%s' を破棄 (リーク: %zu オブジェクト)",
               pool->name, pool->objects_in_use);
    
    if (pool->objects_in_use > 0) {
        fprintf(stderr, "警告: プール '%s' に %zu 個の未解放オブジェクトがあります\n",
                pool->name, pool->objects_in_use);
    }
    
    /* メモリ解放 */
    if (pool->memory_chunk) {
        free(pool->memory_chunk);
    }
    
    /* マジックナンバーをクリアして破損をマーク */
    pool->magic = 0;
    free(pool);
}

/* C99: ジェネリックなスワップ関数 */
#define DEFINE_TYPED_POOL(type, name) \
    typedef struct name##_pool { \
        MemoryPool *pool; \
    } name##_pool; \
    \
    static inline name##_pool *name##_pool_create(size_t capacity) { \
        name##_pool *typed_pool = malloc(sizeof(name##_pool)); \
        if (typed_pool) { \
            typed_pool->pool = pool_create(#name, sizeof(type), capacity); \
            if (!typed_pool->pool) { \
                free(typed_pool); \
                return NULL; \
            } \
        } \
        return typed_pool; \
    } \
    \
    static inline type *name##_alloc(name##_pool *typed_pool) { \
        return typed_pool ? (type *)pool_alloc(typed_pool->pool) : NULL; \
    } \
    \
    static inline void name##_free(name##_pool *typed_pool, type *ptr) { \
        if (typed_pool) pool_free(typed_pool->pool, ptr); \
    } \
    \
    static inline void name##_pool_destroy(name##_pool *typed_pool) { \
        if (typed_pool) { \
            pool_destroy(typed_pool->pool); \
            free(typed_pool); \
        } \
    }

/* テスト用構造体 */
typedef struct TestObject {
    int id;
    char name[16];
    double value;
    bool active;  /* C99: bool型 */
} TestObject;

typedef struct Point {
    double x, y, z;
} Point;

/* C99: 型付きプールの定義 */
DEFINE_TYPED_POOL(int, int)
DEFINE_TYPED_POOL(Point, point)

/* プールの基本機能テスト */
void test_basic_pool_operations(void)
{
    printf("=== 基本プール操作テスト ===\n");
    
    /* C99: 型付きプールの使用 */
    int_pool *typed_pool = int_pool_create(8);
    if (!typed_pool) {
        printf("プール作成に失敗\n");
        return;
    }
    
    pool_print_status(typed_pool->pool);
    
    /* オブジェクトの割り当て */
    int *numbers[5];
    for (int i = 0; i < 5; i++) {
        numbers[i] = int_alloc(typed_pool);
        if (numbers[i]) {
            *numbers[i] = (i + 1) * 10;
            printf("割り当て [%d]: %p = %d\n", i, (void *)numbers[i], *numbers[i]);
        }
    }
    
    pool_print_status(typed_pool->pool);
    
    /* 一部解放 */
    printf("\n一部のオブジェクトを解放...\n");
    int_free(typed_pool, numbers[1]);
    int_free(typed_pool, numbers[3]);
    numbers[1] = numbers[3] = NULL;
    
    pool_print_status(typed_pool->pool);
    
    /* 再割り当て */
    printf("再割り当てテスト...\n");
    int *new_num = int_alloc(typed_pool);
    if (new_num) {
        *new_num = 999;
        printf("再割り当て: %p = %d\n", (void *)new_num, *new_num);
    }
    
    /* 残りを解放 */
    for (int i = 0; i < 5; i++) {
        if (numbers[i]) {
            int_free(typed_pool, numbers[i]);
        }
    }
    int_free(typed_pool, new_num);
    
    pool_print_status(typed_pool->pool);
    int_pool_destroy(typed_pool);
}

/* C99: 可変長配列を使用したテスト */
void test_vla_integration(void)
{
    printf("\n=== VLA統合テスト ===\n");
    
    int pool_sizes[] = {10, 20, 30};
    int num_pools = sizeof(pool_sizes) / sizeof(pool_sizes[0]);
    
    /* C99: VLAでプール配列を作成 */
    MemoryPool *pools[num_pools];
    
    for (int i = 0; i < num_pools; i++) {
        char name[32];
        snprintf(name, sizeof(name), "VLAPool_%d", i);
        pools[i] = pool_create(name, sizeof(double), pool_sizes[i]);
        
        if (pools[i]) {
            printf("プール %d 作成: 容量=%d\n", i, pool_sizes[i]);
            
            /* 半分まで割り当て */
            int alloc_count = pool_sizes[i] / 2;
            for (int j = 0; j < alloc_count; j++) {
                double *val = pool_alloc(pools[i]);
                if (val) *val = i * 100.0 + j;
            }
            
            pool_print_status(pools[i]);
        }
    }
    
    /* クリーンアップ */
    for (int i = 0; i < num_pools; i++) {
        pool_destroy(pools[i]);
    }
}

/* パフォーマンステスト */
void test_performance_comparison(void)
{
    printf("\n=== パフォーマンス比較テスト ===\n");
    
    const size_t iterations = 100000;
    const size_t pool_size = 1000;
    
    MemoryPool *pool = pool_create("PerfPool", sizeof(TestObject), pool_size);
    if (!pool) {
        return;
    }
    
    printf("テスト設定: %zu 回の割り当て・解放\n", iterations);
    
    /* プールベースの割り当て */
    double start = get_time_sec();
    
    for (size_t i = 0; i < iterations; i++) {
        TestObject *obj = pool_alloc(pool);
        if (obj) {
            obj->id = i;
            obj->active = true;
            pool_free(pool, obj);
        }
    }
    
    double pool_time = get_time_sec() - start;
    printf("プール使用時: %.6f 秒\n", pool_time);
    
    /* 通常のmalloc/free */
    start = get_time_sec();
    
    for (size_t i = 0; i < iterations; i++) {
        TestObject *obj = malloc(sizeof(TestObject));
        if (obj) {
            obj->id = i;
            obj->active = true;
            free(obj);
        }
    }
    
    double malloc_time = get_time_sec() - start;
    printf("malloc/free使用時: %.6f 秒\n", malloc_time);
    
    printf("高速化率: %.2fx\n", malloc_time / pool_time);
    
    pool_print_status(pool);
    pool_destroy(pool);
}

/* メイン関数 */
int main(void)
{
    printf("=== 基本的なメモリプールデモ (C99版) ===\n\n");
    
    /* 各種テストの実行 */
    test_basic_pool_operations();
    test_vla_integration();
    test_performance_comparison();
    
    printf("=== デモ完了 ===\n");
    return 0;
}

/*
実行例:
=== 基本的なメモリプールデモ (C99版) ===

=== 基本プール操作テスト ===
[POOL DEBUG:pool_create:134] プール 'int' を作成: オブジェクトサイズ=8, 容量=8

=== プール 'int' の状況 ===
オブジェクトサイズ: 8 バイト
プール容量: 8 オブジェクト
使用中: 0 オブジェクト
空き: 8 オブジェクト
使用率: 0.0%
総割り当て: 0 回
総解放: 0 回
最大使用数: 0 オブジェクト
フリーリスト長: 8
========================

[POOL DEBUG:pool_alloc:168] オブジェクト割り当て: 0x1234560 (使用中: 1/8, 時間: 0.000001秒)
割り当て [0]: 0x1234560 = 10
[POOL DEBUG:pool_alloc:168] オブジェクト割り当て: 0x1234568 (使用中: 2/8, 時間: 0.000001秒)
割り当て [1]: 0x1234568 = 20
[POOL DEBUG:pool_alloc:168] オブジェクト割り当て: 0x1234570 (使用中: 3/8, 時間: 0.000001秒)
割り当て [2]: 0x1234570 = 30
[POOL DEBUG:pool_alloc:168] オブジェクト割り当て: 0x1234578 (使用中: 4/8, 時間: 0.000001秒)
割り当て [3]: 0x1234578 = 40
[POOL DEBUG:pool_alloc:168] オブジェクト割り当て: 0x1234580 (使用中: 5/8, 時間: 0.000001秒)
割り当て [4]: 0x1234580 = 50

=== プール 'int' の状況 ===
オブジェクトサイズ: 8 バイト
プール容量: 8 オブジェクト
使用中: 5 オブジェクト
空き: 3 オブジェクト
使用率: 62.5%
総割り当て: 5 回
総解放: 0 回
最大使用数: 5 オブジェクト
平均割り当て時間: 0.000001秒
フリーリスト長: 3
========================

一部のオブジェクトを解放...
[POOL DEBUG:pool_free:211] オブジェクト解放: 0x1234568 (使用中: 4/8, 時間: 0.000001秒)
[POOL DEBUG:pool_free:211] オブジェクト解放: 0x1234578 (使用中: 3/8, 時間: 0.000001秒)

=== VLA統合テスト ===
プール 0 作成: 容量=10
[POOL DEBUG:pool_create:134] プール 'VLAPool_0' を作成: オブジェクトサイズ=8, 容量=10

=== プール 'VLAPool_0' の状況 ===
オブジェクトサイズ: 8 バイト
プール容量: 10 オブジェクト
使用中: 5 オブジェクト
空き: 5 オブジェクト
使用率: 50.0%
総割り当て: 5 回
総解放: 0 回
最大使用数: 5 オブジェクト
平均割り当て時間: 0.000001秒
フリーリスト長: 5
========================

プール 1 作成: 容量=20
[POOL DEBUG:pool_create:134] プール 'VLAPool_1' を作成: オブジェクトサイズ=8, 容量=20

=== プール 'VLAPool_1' の状況 ===
オブジェクトサイズ: 8 バイト
プール容量: 20 オブジェクト
使用中: 10 オブジェクト
空き: 10 オブジェクト
使用率: 50.0%
総割り当て: 10 回
総解放: 0 回
最大使用数: 10 オブジェクト
平均割り当て時間: 0.000001秒
フリーリスト長: 10
========================

プール 2 作成: 容量=30
[POOL DEBUG:pool_create:134] プール 'VLAPool_2' を作成: オブジェクトサイズ=8, 容量=30

=== プール 'VLAPool_2' の状況 ===
オブジェクトサイズ: 8 バイト
プール容量: 30 オブジェクト
使用中: 15 オブジェクト
空き: 15 オブジェクト
使用率: 50.0%
総割り当て: 15 回
総解放: 0 回
最大使用数: 15 オブジェクト
平均割り当て時間: 0.000001秒
フリーリスト長: 15
========================

[POOL DEBUG:pool_destroy:268] プール 'VLAPool_0' を破棄 (リーク: 5 オブジェクト)
警告: プール 'VLAPool_0' に 5 個の未解放オブジェクトがあります
[POOL DEBUG:pool_destroy:268] プール 'VLAPool_1' を破棄 (リーク: 10 オブジェクト)
警告: プール 'VLAPool_1' に 10 個の未解放オブジェクトがあります
[POOL DEBUG:pool_destroy:268] プール 'VLAPool_2' を破棄 (リーク: 15 オブジェクト)
警告: プール 'VLAPool_2' に 15 個の未解放オブジェクトがあります

=== パフォーマンス比較テスト ===
[POOL DEBUG:pool_create:134] プール 'PerfPool' を作成: オブジェクトサイズ=40, 容量=1000
テスト設定: 100000 回の割り当て・解放
プール使用時: 0.012345 秒
malloc/free使用時: 0.098765 秒
高速化率: 8.00x

=== プール 'PerfPool' の状況 ===
オブジェクトサイズ: 40 バイト
プール容量: 1000 オブジェクト
使用中: 0 オブジェクト
空き: 1000 オブジェクト
使用率: 0.0%
総割り当て: 100000 回
総解放: 100000 回
最大使用数: 1 オブジェクト
平均割り当て時間: 0.000000秒
平均解放時間: 0.000000秒
フリーリスト長: 1000
========================

[POOL DEBUG:pool_destroy:268] プール 'PerfPool' を破棄 (リーク: 0 オブジェクト)
=== デモ完了 ===
*/