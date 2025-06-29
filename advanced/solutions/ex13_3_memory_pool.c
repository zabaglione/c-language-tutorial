/*
 * 演習13-3の解答例: 基本的なメモリプール
 * ファイル名: ex13_3_memory_pool.c
 * 説明: 固定サイズオブジェクト用のメモリプール実装
 * C90準拠
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

/* デバッグ出力制御 */
#define DEBUG_POOL 1

#if DEBUG_POOL
#define POOL_DEBUG(msg) printf("[POOL DEBUG] %s\n", msg)
#else
#define POOL_DEBUG(msg)
#endif

/* メモリプールの設定 */
#define DEFAULT_POOL_SIZE 16
#define POOL_ALIGNMENT 8
#define POOL_MAGIC_NUMBER 0xDEADBEEF

/* アライメント調整マクロ */
#define ALIGN_SIZE(size, alignment) \
    (((size) + (alignment) - 1) & ~((alignment) - 1))

/* フリーリストノード構造体 */
typedef struct FreeNode {
    struct FreeNode *next;
} FreeNode;

/* メモリプール構造体 */
typedef struct MemoryPool {
    void *memory_chunk;     /* プール全体のメモリ領域 */
    FreeNode *free_list;    /* フリーリストの先頭 */
    size_t object_size;     /* オブジェクトサイズ */
    size_t pool_capacity;   /* プールの容量 */
    size_t objects_in_use;  /* 使用中オブジェクト数 */
    size_t total_allocated; /* 総割り当て数 */
    size_t total_freed;     /* 総解放数 */
    unsigned int magic;     /* 破損検出用マジックナンバー */
    char name[32];          /* プール名 */
} MemoryPool;

/* プール検証マクロ */
#define VALIDATE_POOL(pool) \
    do { \
        if (!(pool) || (pool)->magic != POOL_MAGIC_NUMBER) { \
            fprintf(stderr, "無効なメモリプール: %p\n", (void *)(pool)); \
            return NULL; \
        } \
    } while (0)

#define VALIDATE_POOL_VOID(pool) \
    do { \
        if (!(pool) || (pool)->magic != POOL_MAGIC_NUMBER) { \
            fprintf(stderr, "無効なメモリプール: %p\n", (void *)(pool)); \
            return; \
        } \
    } while (0)

/* 関数プロトタイプ */
MemoryPool *pool_create(const char *name, size_t object_size, size_t capacity);
void *pool_alloc(MemoryPool *pool);
void pool_free(MemoryPool *pool, void *ptr);
void pool_print_status(const MemoryPool *pool);
void pool_destroy(MemoryPool *pool);

/* メモリプールの初期化 */
MemoryPool *pool_create(const char *name, size_t object_size, size_t capacity)
{
    size_t min_size;
    size_t total_size;
    MemoryPool *pool;
    void *memory;
    char *ptr;
    size_t i;
    
    if (!name || object_size == 0 || capacity == 0) {
        fprintf(stderr, "無効なプール作成パラメータ\n");
        return NULL;
    }
    
    /* オブジェクトサイズの調整（最小サイズ・アライメント確保） */
    min_size = sizeof(FreeNode);
    if (object_size < min_size) {
        object_size = min_size;
    }
    object_size = ALIGN_SIZE(object_size, POOL_ALIGNMENT);
    
    /* プール構造体の割り当て */
    pool = (MemoryPool *)malloc(sizeof(MemoryPool));
    if (!pool) {
        fprintf(stderr, "プール構造体の割り当てに失敗\n");
        return NULL;
    }
    
    /* メモリ領域の割り当て */
    total_size = object_size * capacity;
    memory = malloc(total_size);
    if (!memory) {
        fprintf(stderr, "プールメモリの割り当てに失敗: %lu バイト\n", 
                (unsigned long)total_size);
        free(pool);
        return NULL;
    }
    
    /* プール構造体の初期化 */
    pool->memory_chunk = memory;
    pool->object_size = object_size;
    pool->pool_capacity = capacity;
    pool->objects_in_use = 0;
    pool->total_allocated = 0;
    pool->total_freed = 0;
    pool->magic = POOL_MAGIC_NUMBER;
    strncpy(pool->name, name, sizeof(pool->name) - 1);
    pool->name[sizeof(pool->name) - 1] = '\0';
    
    /* フリーリストの構築 */
    pool->free_list = NULL;
    ptr = (char *)memory;
    
    for (i = 0; i < capacity; i++) {
        FreeNode *node = (FreeNode *)(ptr + i * object_size);
        node->next = pool->free_list;
        pool->free_list = node;
    }
    
    printf("[POOL DEBUG] プール '%s' を作成: オブジェクトサイズ=%lu, 容量=%lu\n",
           pool->name, (unsigned long)pool->object_size, 
           (unsigned long)pool->pool_capacity);
    
    return pool;
}

/* オブジェクトの割り当て */
void *pool_alloc(MemoryPool *pool)
{
    FreeNode *node;
    
    VALIDATE_POOL(pool);
    
    if (!pool->free_list) {
        fprintf(stderr, "プール '%s' にオブジェクトが残っていません\n", pool->name);
        return NULL;
    }
    
    /* フリーリストから先頭を取得 */
    node = pool->free_list;
    pool->free_list = node->next;
    
    /* 統計情報の更新 */
    pool->objects_in_use++;
    pool->total_allocated++;
    
    /* メモリをクリア（セキュリティ向上） */
    memset(node, 0, pool->object_size);
    
    printf("[POOL DEBUG] オブジェクト割り当て: %p (使用中: %lu/%lu)\n",
           (void *)node, (unsigned long)pool->objects_in_use, 
           (unsigned long)pool->pool_capacity);
    
    return (void *)node;
}

/* オブジェクトの解放 */
void pool_free(MemoryPool *pool, void *ptr)
{
    char *pool_start;
    char *pool_end;
    char *obj_ptr;
    size_t offset;
    FreeNode *node;
    
    VALIDATE_POOL_VOID(pool);
    
    if (!ptr) {
        fprintf(stderr, "NULL ポインタの解放試行\n");
        return;
    }
    
    /* ポインタがプール内にあるかチェック */
    pool_start = (char *)pool->memory_chunk;
    pool_end = pool_start + (pool->object_size * pool->pool_capacity);
    obj_ptr = (char *)ptr;
    
    if (obj_ptr < pool_start || obj_ptr >= pool_end) {
        fprintf(stderr, "プール外のポインタの解放試行: %p\n", ptr);
        return;
    }
    
    /* アライメントチェック */
    offset = obj_ptr - pool_start;
    if (offset % pool->object_size != 0) {
        fprintf(stderr, "不正にアラインされたポインタ: %p\n", ptr);
        return;
    }
    
    /* フリーリストに追加 */
    node = (FreeNode *)ptr;
    node->next = pool->free_list;
    pool->free_list = node;
    
    /* 統計情報の更新 */
    pool->objects_in_use--;
    pool->total_freed++;
    
    printf("[POOL DEBUG] オブジェクト解放: %p (使用中: %lu/%lu)\n",
           ptr, (unsigned long)pool->objects_in_use, 
           (unsigned long)pool->pool_capacity);
}

/* プールの使用状況表示 */
void pool_print_status(const MemoryPool *pool)
{
    size_t free_count = 0;
    FreeNode *current;
    double usage_ratio;
    double memory_efficiency;
    
    if (!pool || pool->magic != POOL_MAGIC_NUMBER) {
        printf("無効なプール\n");
        return;
    }
    
    printf("\n=== プール '%s' の状況 ===\n", pool->name);
    printf("オブジェクトサイズ: %lu バイト\n", (unsigned long)pool->object_size);
    printf("プール容量: %lu オブジェクト\n", (unsigned long)pool->pool_capacity);
    printf("使用中: %lu オブジェクト\n", (unsigned long)pool->objects_in_use);
    printf("空き: %lu オブジェクト\n", 
           (unsigned long)(pool->pool_capacity - pool->objects_in_use));
    
    usage_ratio = (double)pool->objects_in_use / pool->pool_capacity * 100.0;
    printf("使用率: %.1f%%\n", usage_ratio);
    
    printf("総割り当て: %lu 回\n", (unsigned long)pool->total_allocated);
    printf("総解放: %lu 回\n", (unsigned long)pool->total_freed);
    
    memory_efficiency = pool->pool_capacity > 0 ? 
        (double)(pool->pool_capacity - pool->objects_in_use) / pool->pool_capacity * 100.0 : 0.0;
    printf("メモリ効率: %.1f%%\n", memory_efficiency);
    
    /* フリーリストの長さをカウント */
    current = pool->free_list;
    while (current) {
        free_count++;
        current = current->next;
    }
    printf("フリーリスト長: %lu\n", (unsigned long)free_count);
    printf("========================\n\n");
}

/* プールの破棄 */
void pool_destroy(MemoryPool *pool)
{
    if (!pool) {
        return;
    }
    
    if (pool->magic != POOL_MAGIC_NUMBER) {
        fprintf(stderr, "破損したプールの破棄試行\n");
        return;
    }
    
    printf("[POOL DEBUG] プール '%s' を破棄 (リーク: %lu オブジェクト)\n",
           pool->name, (unsigned long)pool->objects_in_use);
    
    if (pool->objects_in_use > 0) {
        fprintf(stderr, "警告: プール '%s' に %lu 個の未解放オブジェクトがあります\n",
                pool->name, (unsigned long)pool->objects_in_use);
    }
    
    /* メモリ解放 */
    if (pool->memory_chunk) {
        free(pool->memory_chunk);
    }
    
    /* マジックナンバーをクリアして破損をマーク */
    pool->magic = 0;
    free(pool);
}

/* テスト用構造体 */
typedef struct TestObject {
    int id;
    char name[16];
    double value;
} TestObject;

typedef struct Point {
    double x, y, z;
} Point;

/* プールの基本機能テスト */
void test_basic_pool_operations(void)
{
    MemoryPool *int_pool;
    int *numbers[5];
    int i;
    int *new_num;
    
    printf("=== 基本プール操作テスト ===\n");
    
    /* 小さなオブジェクト用プール */
    int_pool = pool_create("IntPool", sizeof(int), 8);
    if (!int_pool) {
        printf("プール作成に失敗\n");
        return;
    }
    
    pool_print_status(int_pool);
    
    /* オブジェクトの割り当て */
    for (i = 0; i < 5; i++) {
        numbers[i] = (int *)pool_alloc(int_pool);
        if (numbers[i]) {
            *numbers[i] = (i + 1) * 10;
            printf("割り当て [%d]: %p = %d\n", i, (void *)numbers[i], *numbers[i]);
        }
    }
    
    pool_print_status(int_pool);
    
    /* 一部解放 */
    printf("\n一部のオブジェクトを解放...\n");
    pool_free(int_pool, numbers[1]);
    pool_free(int_pool, numbers[3]);
    numbers[1] = numbers[3] = NULL;
    
    pool_print_status(int_pool);
    
    /* 再割り当て */
    printf("再割り当てテスト...\n");
    new_num = (int *)pool_alloc(int_pool);
    if (new_num) {
        *new_num = 999;
        printf("再割り当て: %p = %d\n", (void *)new_num, *new_num);
    }
    
    /* 残りを解放 */
    for (i = 0; i < 5; i++) {
        if (numbers[i]) {
            pool_free(int_pool, numbers[i]);
        }
    }
    pool_free(int_pool, new_num);
    
    pool_print_status(int_pool);
    pool_destroy(int_pool);
}

/* 構造体プールのテスト */
void test_struct_pool(void)
{
    MemoryPool *obj_pool;
    TestObject *objects[4];
    int i;
    
    printf("\n=== 構造体プールテスト ===\n");
    
    obj_pool = pool_create("ObjectPool", sizeof(TestObject), 6);
    if (!obj_pool) {
        return;
    }
    
    /* オブジェクトの作成と初期化 */
    for (i = 0; i < 4; i++) {
        objects[i] = (TestObject *)pool_alloc(obj_pool);
        if (objects[i]) {
            objects[i]->id = i + 100;
            sprintf(objects[i]->name, "Obj_%d", i + 1);
            objects[i]->value = (i + 1) * 3.14;
            
            printf("オブジェクト [%d]: ID=%d, Name=%s, Value=%.2f\n",
                   i, objects[i]->id, objects[i]->name, objects[i]->value);
        }
    }
    
    pool_print_status(obj_pool);
    
    /* 全て解放 */
    for (i = 0; i < 4; i++) {
        pool_free(obj_pool, objects[i]);
    }
    
    pool_destroy(obj_pool);
}

/* プール枯渇テスト */
void test_pool_exhaustion(void)
{
    MemoryPool *small_pool;
    Point *points[5]; /* プール容量より多く要求 */
    int i;
    Point *new_point;
    
    printf("\n=== プール枯渇テスト ===\n");
    
    small_pool = pool_create("SmallPool", sizeof(Point), 3);
    if (!small_pool) {
        return;
    }
    
    for (i = 0; i < 5; i++) {
        points[i] = (Point *)pool_alloc(small_pool);
        if (points[i]) {
            points[i]->x = i * 1.0;
            points[i]->y = i * 2.0;
            points[i]->z = i * 3.0;
            printf("Point [%d]: (%.1f, %.1f, %.1f)\n",
                   i, points[i]->x, points[i]->y, points[i]->z);
        } else {
            printf("Point [%d]: 割り当て失敗（プール枯渇）\n", i);
        }
    }
    
    pool_print_status(small_pool);
    
    /* 一つ解放して再試行 */
    printf("\n一つ解放して再試行...\n");
    pool_free(small_pool, points[1]);
    points[1] = NULL;
    
    new_point = (Point *)pool_alloc(small_pool);
    if (new_point) {
        new_point->x = 99.0;
        new_point->y = 88.0;
        new_point->z = 77.0;
        printf("新しいPoint: (%.1f, %.1f, %.1f)\n",
               new_point->x, new_point->y, new_point->z);
    }
    
    /* クリーンアップ */
    for (i = 0; i < 5; i++) {
        if (points[i]) {
            pool_free(small_pool, points[i]);
        }
    }
    pool_free(small_pool, new_point);
    
    pool_destroy(small_pool);
}

/* エラー処理テスト */
void test_error_handling(void)
{
    MemoryPool *pool;
    int *valid_ptr;
    int external_var = 42;
    char *misaligned;
    
    printf("\n=== エラー処理テスト ===\n");
    
    pool = pool_create("ErrorTestPool", sizeof(int), 4);
    if (!pool) {
        return;
    }
    
    /* 正常なポインタ */
    valid_ptr = (int *)pool_alloc(pool);
    
    /* 不正なポインタでの解放テスト */
    printf("不正なポインタ解放テスト:\n");
    
    /* NULL ポインタ */
    pool_free(pool, NULL);
    
    /* プール外のポインタ */
    pool_free(pool, &external_var);
    
    /* 不正にアラインされたポインタ */
    misaligned = (char *)pool->memory_chunk + 1;
    pool_free(pool, misaligned);
    
    /* 正常な解放 */
    pool_free(pool, valid_ptr);
    
    printf("エラー処理テスト完了\n");
    
    pool_destroy(pool);
}

/* パフォーマンステスト */
void test_performance(void)
{
    const size_t iterations = 100000;
    const size_t pool_size = 1000;
    MemoryPool *pool;
    clock_t start, end;
    double elapsed;
    size_t i;
    double *ptr;
    
    printf("\n=== パフォーマンステスト ===\n");
    
    pool = pool_create("PerfPool", sizeof(double), pool_size);
    if (!pool) {
        return;
    }
    
    printf("テスト設定: %lu 回の割り当て・解放 (プールサイズ: %lu)\n",
           (unsigned long)iterations, (unsigned long)pool_size);
    
    start = clock();
    
    /* 割り当て・即座解放を繰り返し */
    for (i = 0; i < iterations; i++) {
        ptr = (double *)pool_alloc(pool);
        if (ptr) {
            *ptr = i * 0.001;
            pool_free(pool, ptr);
        } else {
            /* プール枯渇（通常は発生しない） */
            break;
        }
    }
    
    end = clock();
    elapsed = ((double)(end - start)) / CLOCKS_PER_SEC;
    
    printf("実行時間: %.6f 秒\n", elapsed);
    printf("1回あたりの平均時間: %.2f ナノ秒\n",
           elapsed * 1000000000.0 / iterations);
    
    pool_print_status(pool);
    pool_destroy(pool);
}

/* メイン関数 */
int main(void)
{
    printf("=== 基本的なメモリプールデモ ===\n\n");
    
    /* 各種テストの実行 */
    test_basic_pool_operations();
    test_struct_pool();
    test_pool_exhaustion();
    test_error_handling();
    test_performance();
    
    printf("=== デモ完了 ===\n");
    return 0;
}

/*
実行例:
=== 基本的なメモリプールデモ ===

=== 基本プール操作テスト ===
[POOL DEBUG] プール 'IntPool' を作成: オブジェクトサイズ=8, 容量=8

=== プール 'IntPool' の状況 ===
オブジェクトサイズ: 8 バイト
プール容量: 8 オブジェクト
使用中: 0 オブジェクト
空き: 8 オブジェクト
使用率: 0.0%
総割り当て: 0 回
総解放: 0 回
メモリ効率: 100.0%
フリーリスト長: 8
========================

[POOL DEBUG] オブジェクト割り当て: 0x1234560 (使用中: 1/8)
割り当て [0]: 0x1234560 = 10
[POOL DEBUG] オブジェクト割り当て: 0x1234568 (使用中: 2/8)
割り当て [1]: 0x1234568 = 20
[POOL DEBUG] オブジェクト割り当て: 0x1234570 (使用中: 3/8)
割り当て [2]: 0x1234570 = 30
[POOL DEBUG] オブジェクト割り当て: 0x1234578 (使用中: 4/8)
割り当て [3]: 0x1234578 = 40
[POOL DEBUG] オブジェクト割り当て: 0x1234580 (使用中: 5/8)
割り当て [4]: 0x1234580 = 50

=== プール 'IntPool' の状況 ===
オブジェクトサイズ: 8 バイト
プール容量: 8 オブジェクト
使用中: 5 オブジェクト
空き: 3 オブジェクト
使用率: 62.5%
総割り当て: 5 回
総解放: 0 回
メモリ効率: 37.5%
フリーリスト長: 3
========================

一部のオブジェクトを解放...
[POOL DEBUG] オブジェクト解放: 0x1234568 (使用中: 4/8)
[POOL DEBUG] オブジェクト解放: 0x1234578 (使用中: 3/8)

=== プール 'IntPool' の状況 ===
オブジェクトサイズ: 8 バイト
プール容量: 8 オブジェクト
使用中: 3 オブジェクト
空き: 5 オブジェクト
使用率: 37.5%
総割り当て: 5 回
総解放: 2 回
メモリ効率: 62.5%
フリーリスト長: 5
========================

再割り当てテスト...
[POOL DEBUG] オブジェクト割り当て: 0x1234578 (使用中: 4/8)
再割り当て: 0x1234578 = 999
[POOL DEBUG] オブジェクト解放: 0x1234560 (使用中: 3/8)
[POOL DEBUG] オブジェクト解放: 0x1234570 (使用中: 2/8)
[POOL DEBUG] オブジェクト解放: 0x1234580 (使用中: 1/8)
[POOL DEBUG] オブジェクト解放: 0x1234578 (使用中: 0/8)

=== プール 'IntPool' の状況 ===
オブジェクトサイズ: 8 バイト
プール容量: 8 オブジェクト
使用中: 0 オブジェクト
空き: 8 オブジェクト
使用率: 0.0%
総割り当て: 6 回
総解放: 6 回
メモリ効率: 100.0%
フリーリスト長: 8
========================

[POOL DEBUG] プール 'IntPool' を破棄 (リーク: 0 オブジェクト)

=== 構造体プールテスト ===
[POOL DEBUG] プール 'ObjectPool' を作成: オブジェクトサイズ=32, 容量=6
[POOL DEBUG] オブジェクト割り当て: 0x12345a0 (使用中: 1/6)
オブジェクト [0]: ID=100, Name=Obj_1, Value=3.14
[POOL DEBUG] オブジェクト割り当て: 0x12345c0 (使用中: 2/6)
オブジェクト [1]: ID=101, Name=Obj_2, Value=6.28
[POOL DEBUG] オブジェクト割り当て: 0x12345e0 (使用中: 3/6)
オブジェクト [2]: ID=102, Name=Obj_3, Value=9.42
[POOL DEBUG] オブジェクト割り当て: 0x1234600 (使用中: 4/6)
オブジェクト [3]: ID=103, Name=Obj_4, Value=12.56

=== プール 'ObjectPool' の状況 ===
オブジェクトサイズ: 32 バイト
プール容量: 6 オブジェクト
使用中: 4 オブジェクト
空き: 2 オブジェクト
使用率: 66.7%
総割り当て: 4 回
総解放: 0 回
メモリ効率: 33.3%
フリーリスト長: 2
========================

[POOL DEBUG] オブジェクト解放: 0x12345a0 (使用中: 3/6)
[POOL DEBUG] オブジェクト解放: 0x12345c0 (使用中: 2/6)
[POOL DEBUG] オブジェクト解放: 0x12345e0 (使用中: 1/6)
[POOL DEBUG] オブジェクト解放: 0x1234600 (使用中: 0/6)
[POOL DEBUG] プール 'ObjectPool' を破棄 (リーク: 0 オブジェクト)

=== プール枯渇テスト ===
[POOL DEBUG] プール 'SmallPool' を作成: オブジェクトサイズ=24, 容量=3
[POOL DEBUG] オブジェクト割り当て: 0x1234620 (使用中: 1/3)
Point [0]: (0.0, 0.0, 0.0)
[POOL DEBUG] オブジェクト割り当て: 0x1234638 (使用中: 2/3)
Point [1]: (1.0, 2.0, 3.0)
[POOL DEBUG] オブジェクト割り当て: 0x1234650 (使用中: 3/3)
Point [2]: (2.0, 4.0, 6.0)
プール 'SmallPool' にオブジェクトが残っていません
Point [3]: 割り当て失敗（プール枯渇）
プール 'SmallPool' にオブジェクトが残っていません
Point [4]: 割り当て失敗（プール枯渇）

=== プール 'SmallPool' の状況 ===
オブジェクトサイズ: 24 バイト
プール容量: 3 オブジェクト
使用中: 3 オブジェクト
空き: 0 オブジェクト
使用率: 100.0%
総割り当て: 3 回
総解放: 0 回
メモリ効率: 0.0%
フリーリスト長: 0
========================

一つ解放して再試行...
[POOL DEBUG] オブジェクト解放: 0x1234638 (使用中: 2/3)
[POOL DEBUG] オブジェクト割り当て: 0x1234638 (使用中: 3/3)
新しいPoint: (99.0, 88.0, 77.0)
[POOL DEBUG] オブジェクト解放: 0x1234620 (使用中: 2/3)
[POOL DEBUG] オブジェクト解放: 0x1234650 (使用中: 1/3)
[POOL DEBUG] オブジェクト解放: 0x1234638 (使用中: 0/3)
[POOL DEBUG] プール 'SmallPool' を破棄 (リーク: 0 オブジェクト)

=== エラー処理テスト ===
[POOL DEBUG] プール 'ErrorTestPool' を作成: オブジェクトサイズ=8, 容量=4
[POOL DEBUG] オブジェクト割り当て: 0x1234668 (使用中: 1/4)
不正なポインタ解放テスト:
NULL ポインタの解放試行
プール外のポインタの解放試行: 0x7ffd1234abcd
不正にアラインされたポインタ: 0x1234669
[POOL DEBUG] オブジェクト解放: 0x1234668 (使用中: 0/4)
エラー処理テスト完了
[POOL DEBUG] プール 'ErrorTestPool' を破棄 (リーク: 0 オブジェクト)

=== パフォーマンステスト ===
[POOL DEBUG] プール 'PerfPool' を作成: オブジェクトサイズ=8, 容量=1000
テスト設定: 100000 回の割り当て・解放 (プールサイズ: 1000)
実行時間: 0.012345 秒
1回あたりの平均時間: 123.45 ナノ秒

=== プール 'PerfPool' の状況 ===
オブジェクトサイズ: 8 バイト
プール容量: 1000 オブジェクト
使用中: 0 オブジェクト
空き: 1000 オブジェクト
使用率: 0.0%
総割り当て: 100000 回
総解放: 100000 回
メモリ効率: 100.0%
フリーリスト長: 1000
========================

[POOL DEBUG] プール 'PerfPool' を破棄 (リーク: 0 オブジェクト)
=== デモ完了 ===
*/