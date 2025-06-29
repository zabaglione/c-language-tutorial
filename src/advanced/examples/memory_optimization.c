/* メモリ管理の最適化技法 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <stddef.h>

/* Cの_Alignofが利用できない場合の代替定義 */
#ifndef _Alignof
#define _Alignof(type) offsetof(struct { char c; type x; }, x)
#endif

/* メモリプールのブロックサイズ */
#define POOL_BLOCK_SIZE 1024
#define MAX_POOL_BLOCKS 10
#define SMALL_OBJECT_SIZE 64
#define MEDIUM_OBJECT_SIZE 256

/* メモリプール構造体 */
typedef struct MemoryBlock
{
    void *data;
    size_t size;
    int is_free;
    struct MemoryBlock *next;
} MemoryBlock;

typedef struct
{
    MemoryBlock *blocks;
    size_t total_size;
    size_t used_size;
    int num_blocks;
} MemoryPool;

/* スタックアロケーター */
typedef struct
{
    char *memory;
    size_t size;
    size_t offset;
} StackAllocator;

/* オブジェクトプール */
typedef struct ObjectNode
{
    struct ObjectNode *next;
} ObjectNode;

typedef struct
{
    ObjectNode *free_list;
    void *memory_chunk;
    size_t object_size;
    size_t capacity;
    size_t count;
} ObjectPool;

/* グローバルメモリプール */
static MemoryPool g_memory_pool = {NULL, 0, 0, 0};

/* メモリ使用統計 */
typedef struct
{
    size_t total_allocated;
    size_t total_freed;
    size_t peak_usage;
    size_t current_usage;
    int allocation_count;
    int free_count;
} MemoryStats;

static MemoryStats g_memory_stats = {0, 0, 0, 0, 0, 0};

/* メモリプールの初期化 */
int init_memory_pool(MemoryPool *pool, size_t total_size)
{
    pool->blocks = malloc(sizeof(MemoryBlock) * MAX_POOL_BLOCKS);
    if (!pool->blocks)
    {
        printf("メモリプール初期化エラー: ブロック配列の確保に失敗\n");
        return 0;
    }

    pool->total_size = total_size;
    pool->used_size = 0;
    pool->num_blocks = 1;

    /* 最初の大きなブロックを作成 */
    pool->blocks[0].data = malloc(total_size);
    if (!pool->blocks[0].data)
    {
        free(pool->blocks);
        printf("メモリプール初期化エラー: メモリブロックの確保に失敗\n");
        return 0;
    }

    pool->blocks[0].size = total_size;
    pool->blocks[0].is_free = 1;
    pool->blocks[0].next = NULL;

    printf("メモリプール初期化完了: %zu バイト\n", total_size);
    return 1;
}

/* メモリプールからの割り当て */
void *pool_alloc(MemoryPool *pool, size_t size)
{
    int i;

    /* 適切なサイズの空きブロックを検索 */
    for (i = 0; i < pool->num_blocks; i++)
    {
        if (pool->blocks[i].is_free && pool->blocks[i].size >= size)
        {
            /* ブロックが大きすぎる場合は分割 */
            if (pool->blocks[i].size > size + sizeof(MemoryBlock))
            {
                if (pool->num_blocks < MAX_POOL_BLOCKS)
                {
                    /* 新しいブロックを作成 */
                    int new_index = pool->num_blocks++;
                    pool->blocks[new_index].data = (char *)pool->blocks[i].data + size;
                    pool->blocks[new_index].size = pool->blocks[i].size - size;
                    pool->blocks[new_index].is_free = 1;
                    pool->blocks[new_index].next = NULL;

                    /* 元のブロックサイズを調整 */
                    pool->blocks[i].size = size;
                }
            }

            pool->blocks[i].is_free = 0;
            pool->used_size += size;

            /* 統計更新 */
            g_memory_stats.total_allocated += size;
            g_memory_stats.current_usage += size;
            g_memory_stats.allocation_count++;

            if (g_memory_stats.current_usage > g_memory_stats.peak_usage)
            {
                g_memory_stats.peak_usage = g_memory_stats.current_usage;
            }

            return pool->blocks[i].data;
        }
    }

    printf("メモリプール割り当てエラー: %zu バイトの空きブロックが見つかりません\n", size);
    return NULL;
}

/* メモリプールへの解放 */
void pool_free(MemoryPool *pool, void *ptr)
{
    int i;

    if (!ptr)
        return;

    for (i = 0; i < pool->num_blocks; i++)
    {
        if (pool->blocks[i].data == ptr && !pool->blocks[i].is_free)
        {
            pool->blocks[i].is_free = 1;
            pool->used_size -= pool->blocks[i].size;

            /* 統計更新 */
            g_memory_stats.total_freed += pool->blocks[i].size;
            g_memory_stats.current_usage -= pool->blocks[i].size;
            g_memory_stats.free_count++;

            /* 隣接する空きブロックとマージ */
            /* 簡単な実装のため、ここではマージを省略 */

            printf("メモリ解放: %zu バイト\n", pool->blocks[i].size);
            return;
        }
    }

    printf("メモリ解放エラー: 無効なポインタ\n");
}

/* メモリプールの状態表示 */
void print_pool_status(MemoryPool *pool)
{
    printf("\n=== メモリプール状態 ===\n");
    printf("総サイズ: %zu バイト\n", pool->total_size);
    printf("使用中: %zu バイト\n", pool->used_size);
    printf("空き: %zu バイト\n", pool->total_size - pool->used_size);
    printf("ブロック数: %d\n", pool->num_blocks);

    printf("ブロック詳細:\n");
    int i;
    for (i = 0; i < pool->num_blocks; i++)
    {
        printf("  ブロック%d: サイズ=%zu, 状態=%s\n",
               i, pool->blocks[i].size,
               pool->blocks[i].is_free ? "空き" : "使用中");
    }
}

/* メモリプールの終了処理 */
void cleanup_memory_pool(MemoryPool *pool)
{
    if (pool->blocks)
    {
        if (pool->blocks[0].data)
        {
            free(pool->blocks[0].data);
        }
        free(pool->blocks);
        pool->blocks = NULL;
    }
    printf("メモリプール終了処理完了\n");
}

/* スタックアロケーターの初期化 */
int init_stack_allocator(StackAllocator *stack, size_t size)
{
    stack->memory = malloc(size);
    if (!stack->memory)
    {
        printf("スタックアロケーター初期化エラー\n");
        return 0;
    }

    stack->size = size;
    stack->offset = 0;

    printf("スタックアロケーター初期化: %zu バイト\n", size);
    return 1;
}

/* スタックアロケーターからの割り当て */
void *stack_alloc(StackAllocator *stack, size_t size)
{
    /* アライメント調整 */
    size_t aligned_size = (size + 7) & ~7; /* 8バイト境界に整列 */

    if (stack->offset + aligned_size > stack->size)
    {
        printf("スタックアロケーターエラー: メモリ不足\n");
        return NULL;
    }

    void *ptr = stack->memory + stack->offset;
    stack->offset += aligned_size;

    return ptr;
}

/* スタックアロケーターのリセット */
void stack_reset(StackAllocator *stack)
{
    stack->offset = 0;
    printf("スタックアロケーターをリセットしました\n");
}

/* スタックアロケーターの終了処理 */
void cleanup_stack_allocator(StackAllocator *stack)
{
    if (stack->memory)
    {
        free(stack->memory);
        stack->memory = NULL;
    }
    printf("スタックアロケーター終了処理完了\n");
}

/* オブジェクトプールの初期化 */
int init_object_pool(ObjectPool *pool, size_t object_size, size_t capacity)
{
    size_t total_size = object_size * capacity;
    pool->memory_chunk = malloc(total_size);

    if (!pool->memory_chunk)
    {
        printf("オブジェクトプール初期化エラー\n");
        return 0;
    }

    pool->object_size = object_size;
    pool->capacity = capacity;
    pool->count = 0;

    /* フリーリストの構築 */
    pool->free_list = NULL;
    char *ptr = (char *)pool->memory_chunk;
    size_t i;

    for (i = 0; i < capacity; i++)
    {
        ObjectNode *node = (ObjectNode *)(ptr + i * object_size);
        node->next = pool->free_list;
        pool->free_list = node;
    }

    printf("オブジェクトプール初期化: オブジェクトサイズ=%zu, 容量=%zu\n",
           object_size, capacity);
    return 1;
}

/* オブジェクトプールからの取得 */
void *object_pool_get(ObjectPool *pool)
{
    if (!pool->free_list)
    {
        printf("オブジェクトプールエラー: 利用可能なオブジェクトがありません\n");
        return NULL;
    }

    ObjectNode *node = pool->free_list;
    pool->free_list = node->next;
    pool->count++;

    /* オブジェクトをクリア */
    memset(node, 0, pool->object_size);

    return node;
}

/* オブジェクトプールへの返却 */
void object_pool_return(ObjectPool *pool, void *obj)
{
    if (!obj)
        return;

    ObjectNode *node = (ObjectNode *)obj;
    node->next = pool->free_list;
    pool->free_list = node;
    pool->count--;
}

/* オブジェクトプールの終了処理 */
void cleanup_object_pool(ObjectPool *pool)
{
    if (pool->memory_chunk)
    {
        free(pool->memory_chunk);
        pool->memory_chunk = NULL;
    }
    printf("オブジェクトプール終了処理完了\n");
}

/* カスタムメモリアロケーター */
typedef struct
{
    void *(*alloc)(size_t size);
    void (*free)(void *ptr);
    void *(*realloc)(void *ptr, size_t new_size);
} CustomAllocator;

/* デバッグアロケーター */
void *debug_malloc(size_t size)
{
    void *ptr = malloc(size + sizeof(size_t));
    if (ptr)
    {
        *(size_t *)ptr = size;
        printf("[DEBUG MALLOC] %zu バイト割り当て: %p\n", size, (char *)ptr + sizeof(size_t));
        return (char *)ptr + sizeof(size_t);
    }
    return NULL;
}

void debug_free(void *ptr)
{
    if (ptr)
    {
        void *real_ptr = (char *)ptr - sizeof(size_t);
        size_t size = *(size_t *)real_ptr;
        printf("[DEBUG FREE] %zu バイト解放: %p\n", size, ptr);
        free(real_ptr);
    }
}

void *debug_realloc(void *ptr, size_t new_size)
{
    if (!ptr)
    {
        return debug_malloc(new_size);
    }

    void *real_ptr = (char *)ptr - sizeof(size_t);
    size_t old_size = *(size_t *)real_ptr;

    void *new_ptr = realloc(real_ptr, new_size + sizeof(size_t));
    if (new_ptr)
    {
        *(size_t *)new_ptr = new_size;
        printf("[DEBUG REALLOC] %zu バイト -> %zu バイト: %p -> %p\n",
               old_size, new_size, ptr, (char *)new_ptr + sizeof(size_t));
        return (char *)new_ptr + sizeof(size_t);
    }
    return NULL;
}

/* メモリ使用統計の表示 */
void print_memory_stats(void)
{
    printf("\n=== メモリ使用統計 ===\n");
    printf("総割り当て: %zu バイト\n", g_memory_stats.total_allocated);
    printf("総解放: %zu バイト\n", g_memory_stats.total_freed);
    printf("現在使用中: %zu バイト\n", g_memory_stats.current_usage);
    printf("ピーク使用量: %zu バイト\n", g_memory_stats.peak_usage);
    printf("割り当て回数: %d\n", g_memory_stats.allocation_count);
    printf("解放回数: %d\n", g_memory_stats.free_count);
}

/* メモリアライメントのテスト */
void test_memory_alignment(void)
{
    printf("\n=== メモリアライメントテスト ===\n");

    struct TestStruct
    {
        char c;
        int i;
        double d;
        char c2;
    };

    printf("char サイズ: %zu, アライメント: %zu\n", sizeof(char), _Alignof(char));
    printf("int サイズ: %zu, アライメント: %zu\n", sizeof(int), _Alignof(int));
    printf("double サイズ: %zu, アライメント: %zu\n", sizeof(double), _Alignof(double));
    printf("struct TestStruct サイズ: %zu\n", sizeof(struct TestStruct));

    struct TestStruct ts;
    printf("メンバーのオフセット:\n");
    printf("  c: %zu\n", offsetof(struct TestStruct, c));
    printf("  i: %zu\n", offsetof(struct TestStruct, i));
    printf("  d: %zu\n", offsetof(struct TestStruct, d));
    printf("  c2: %zu\n", offsetof(struct TestStruct, c2));
}

/* ベンチマーク用の構造体 */
typedef struct
{
    int id;
    char name[32];
    double value;
} TestObject;

/* 標準malloc/freeのベンチマーク */
double benchmark_standard_alloc(int iterations)
{
    clock_t start = clock();
    int i;

    TestObject **objects = malloc(sizeof(TestObject *) * iterations);

    for (i = 0; i < iterations; i++)
    {
        objects[i] = malloc(sizeof(TestObject));
        objects[i]->id = i;
        sprintf(objects[i]->name, "Object_%d", i);
        objects[i]->value = i * 3.14;
    }

    for (i = 0; i < iterations; i++)
    {
        free(objects[i]);
    }

    free(objects);

    clock_t end = clock();
    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

/* メモリプールのベンチマーク */
double benchmark_pool_alloc(int iterations)
{
    clock_t start = clock();

    MemoryPool pool;
    init_memory_pool(&pool, sizeof(TestObject) * iterations * 2);

    TestObject **objects = malloc(sizeof(TestObject *) * iterations);
    int i;

    for (i = 0; i < iterations; i++)
    {
        objects[i] = (TestObject *)pool_alloc(&pool, sizeof(TestObject));
        if (objects[i])
        {
            objects[i]->id = i;
            sprintf(objects[i]->name, "Object_%d", i);
            objects[i]->value = i * 3.14;
        }
    }

    for (i = 0; i < iterations; i++)
    {
        pool_free(&pool, objects[i]);
    }

    free(objects);
    cleanup_memory_pool(&pool);

    clock_t end = clock();
    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

/* オブジェクトプールのベンチマーク */
double benchmark_object_pool(int iterations)
{
    clock_t start = clock();

    ObjectPool pool;
    init_object_pool(&pool, sizeof(TestObject), iterations);

    TestObject **objects = malloc(sizeof(TestObject *) * iterations);
    int i;

    for (i = 0; i < iterations; i++)
    {
        objects[i] = (TestObject *)object_pool_get(&pool);
        if (objects[i])
        {
            objects[i]->id = i;
            sprintf(objects[i]->name, "Object_%d", i);
            objects[i]->value = i * 3.14;
        }
    }

    for (i = 0; i < iterations; i++)
    {
        object_pool_return(&pool, objects[i]);
    }

    free(objects);
    cleanup_object_pool(&pool);

    clock_t end = clock();
    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

/* メモリリークのシミュレーション */
void simulate_memory_leak(void)
{
    printf("\n=== メモリリークシミュレーション ===\n");

    CustomAllocator debug_allocator = {
        debug_malloc,
        debug_free,
        debug_realloc};

    /* 正常なパターン */
    void *ptr1 = debug_allocator.alloc(100);
    void *ptr2 = debug_allocator.alloc(200);
    debug_allocator.free(ptr1);
    debug_allocator.free(ptr2);

    /* リークのシミュレーション（意図的にfreeしない） */
    void *leak_ptr = debug_allocator.alloc(500);
    printf("リークポインタ: %p (解放されません)\n", leak_ptr);

    /* reallocのテスト */
    void *ptr3 = debug_allocator.alloc(50);
    ptr3 = debug_allocator.realloc(ptr3, 150);
    debug_allocator.free(ptr3);
}

int main(void)
{
    printf("=== メモリ管理の最適化技法デモ ===\n\n");

    /* メモリアライメントの確認 */
    test_memory_alignment();

    /* メモリプールのテスト */
    printf("\n=== メモリプールテスト ===\n");
    if (init_memory_pool(&g_memory_pool, 2048))
    {
        void *ptr1 = pool_alloc(&g_memory_pool, 100);
        void *ptr2 = pool_alloc(&g_memory_pool, 200);
        void *ptr3 = pool_alloc(&g_memory_pool, 300);

        print_pool_status(&g_memory_pool);

        pool_free(&g_memory_pool, ptr2);
        pool_free(&g_memory_pool, ptr1);

        print_pool_status(&g_memory_pool);

        void *ptr4 = pool_alloc(&g_memory_pool, 150);
        print_pool_status(&g_memory_pool);

        pool_free(&g_memory_pool, ptr3);
        pool_free(&g_memory_pool, ptr4);

        cleanup_memory_pool(&g_memory_pool);
    }

    /* スタックアロケーターのテスト */
    printf("\n=== スタックアロケーターテスト ===\n");
    StackAllocator stack;
    if (init_stack_allocator(&stack, 1024))
    {
        void *s1 = stack_alloc(&stack, 100);
        void *s2 = stack_alloc(&stack, 200);
        void *s3 = stack_alloc(&stack, 300);

        printf("割り当て後オフセット: %zu\n", stack.offset);

        stack_reset(&stack);
        printf("リセット後オフセット: %zu\n", stack.offset);

        cleanup_stack_allocator(&stack);
    }

    /* オブジェクトプールのテスト */
    printf("\n=== オブジェクトプールテスト ===\n");
    ObjectPool obj_pool;
    if (init_object_pool(&obj_pool, sizeof(TestObject), 5))
    {
        TestObject *objs[3];
        int i;

        for (i = 0; i < 3; i++)
        {
            objs[i] = (TestObject *)object_pool_get(&obj_pool);
            if (objs[i])
            {
                objs[i]->id = i;
                sprintf(objs[i]->name, "TestObj_%d", i);
                objs[i]->value = i * 2.5;
                printf("オブジェクト%d作成: ID=%d, Name=%s, Value=%.1f\n",
                       i, objs[i]->id, objs[i]->name, objs[i]->value);
            }
        }

        printf("使用中オブジェクト数: %zu\n", obj_pool.count);

        for (i = 0; i < 3; i++)
        {
            object_pool_return(&obj_pool, objs[i]);
        }

        printf("返却後オブジェクト数: %zu\n", obj_pool.count);

        cleanup_object_pool(&obj_pool);
    }

    /* メモリリークのシミュレーション */
    simulate_memory_leak();

    /* ベンチマークテスト */
    printf("\n=== パフォーマンステスト ===\n");
    int iterations = 10000;

    printf("テスト回数: %d\n", iterations);

    double std_time = benchmark_standard_alloc(iterations);
    printf("標準malloc/free: %.6f秒\n", std_time);

    double pool_time = benchmark_pool_alloc(iterations);
    printf("メモリプール: %.6f秒\n", pool_time);

    double obj_pool_time = benchmark_object_pool(iterations);
    printf("オブジェクトプール: %.6f秒\n", obj_pool_time);

    printf("\nパフォーマンス比較 (標準を100%%とした場合):\n");
    printf("メモリプール: %.1f%%\n", (pool_time / std_time) * 100);
    printf("オブジェクトプール: %.1f%%\n", (obj_pool_time / std_time) * 100);

    /* メモリ使用統計 */
    print_memory_stats();

    printf("\n=== メモリ最適化デモ完了 ===\n");

    return 0;
}
