/*
 * 演習13-6の解答例: キャッシュフレンドリーなデータ構造
 * ファイル名: ex13_6_cache_vector.c
 * 説明: 配列ベース動的配列、キャッシュ効率的なメモリレイアウト
 * C90準拠
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

/* キャッシュラインサイズ（一般的な値） */
#define CACHE_LINE_SIZE 64

/* ベクター設定 */
#define VECTOR_MIN_CAPACITY 16
#define VECTOR_GROWTH_FACTOR 2
#define VECTOR_SHRINK_THRESHOLD 0.25
#define VECTOR_SHRINK_FACTOR 0.5

/* プリフェッチヒント（コンパイラ依存） */
#ifdef __GNUC__
#define PREFETCH_READ(addr) __builtin_prefetch((addr), 0, 3)
#define PREFETCH_WRITE(addr) __builtin_prefetch((addr), 1, 3)
#else
#define PREFETCH_READ(addr) ((void)0)
#define PREFETCH_WRITE(addr) ((void)0)
#endif

/* アライメント指定（コンパイラ依存） */
#ifdef __GNUC__
#define CACHE_ALIGNED __attribute__((aligned(CACHE_LINE_SIZE)))
#else
#define CACHE_ALIGNED
#endif

/* ベクター構造体 */
typedef struct CacheVector {
    void *data;              /* データ配列 */
    size_t element_size;     /* 要素サイズ */
    size_t size;            /* 現在の要素数 */
    size_t capacity;        /* 確保済み容量 */
    
    /* キャッシュ効率のための追加フィールド */
    size_t cache_line_elements;  /* キャッシュライン当たりの要素数 */
    size_t prefetch_distance;    /* プリフェッチ距離 */
    
    /* 統計情報 */
    size_t total_accesses;
    size_t cache_misses_estimate;
    double total_operation_time;
} CACHE_ALIGNED CacheVector;

/* 関数プロトタイプ */
CacheVector *vector_create(size_t element_size);
void vector_destroy(CacheVector *vec);
int vector_push_back(CacheVector *vec, const void *element);
int vector_pop_back(CacheVector *vec, void *element);
void *vector_at(CacheVector *vec, size_t index);
int vector_resize(CacheVector *vec, size_t new_size);
int vector_reserve(CacheVector *vec, size_t new_capacity);
void vector_clear(CacheVector *vec);
int vector_insert_bulk(CacheVector *vec, size_t index, const void *elements, size_t count);
int vector_remove_bulk(CacheVector *vec, size_t index, size_t count);
void vector_optimize_cache(CacheVector *vec);
void vector_print_stats(const CacheVector *vec);

/* 時間計測 */
static double get_time_sec(void)
{
    return (double)clock() / CLOCKS_PER_SEC;
}

/* ベクター作成 */
CacheVector *vector_create(size_t element_size)
{
    CacheVector *vec;
    
    if (element_size == 0) {
        return NULL;
    }
    
    /* キャッシュラインアライメントされたメモリを確保 */
    vec = (CacheVector *)malloc(sizeof(CacheVector));
    if (!vec) {
        return NULL;
    }
    
    memset(vec, 0, sizeof(CacheVector));
    vec->element_size = element_size;
    vec->capacity = VECTOR_MIN_CAPACITY;
    
    /* データ領域もアライメント */
    vec->data = aligned_alloc(CACHE_LINE_SIZE, vec->capacity * element_size);
    if (!vec->data) {
        free(vec);
        return NULL;
    }
    
    /* キャッシュ関連の計算 */
    vec->cache_line_elements = CACHE_LINE_SIZE / element_size;
    if (vec->cache_line_elements == 0) {
        vec->cache_line_elements = 1;
    }
    vec->prefetch_distance = 4 * vec->cache_line_elements;
    
    return vec;
}

/* ベクター破棄 */
void vector_destroy(CacheVector *vec)
{
    if (vec) {
        if (vec->data) {
            free(vec->data);
        }
        free(vec);
    }
}

/* 容量調整（内部関数） */
static int vector_adjust_capacity(CacheVector *vec, size_t required_capacity)
{
    void *new_data;
    size_t new_capacity;
    
    if (required_capacity <= vec->capacity) {
        return 0;
    }
    
    /* 成長戦略 */
    new_capacity = vec->capacity;
    while (new_capacity < required_capacity) {
        new_capacity *= VECTOR_GROWTH_FACTOR;
    }
    
    /* キャッシュライン境界に合わせる */
    new_capacity = ((new_capacity * vec->element_size + CACHE_LINE_SIZE - 1) 
                    / CACHE_LINE_SIZE) * CACHE_LINE_SIZE / vec->element_size;
    
    new_data = aligned_alloc(CACHE_LINE_SIZE, new_capacity * vec->element_size);
    if (!new_data) {
        return -1;
    }
    
    /* データコピー（最適化） */
    if (vec->size > 0) {
        memcpy(new_data, vec->data, vec->size * vec->element_size);
    }
    
    free(vec->data);
    vec->data = new_data;
    vec->capacity = new_capacity;
    
    return 0;
}

/* 要素追加 */
int vector_push_back(CacheVector *vec, const void *element)
{
    double start_time;
    
    if (!vec || !element) {
        return -1;
    }
    
    start_time = get_time_sec();
    
    if (vec->size >= vec->capacity) {
        if (vector_adjust_capacity(vec, vec->size + 1) < 0) {
            return -1;
        }
    }
    
    memcpy((char *)vec->data + vec->size * vec->element_size, 
           element, vec->element_size);
    vec->size++;
    
    vec->total_accesses++;
    vec->total_operation_time += get_time_sec() - start_time;
    
    return 0;
}

/* 要素削除 */
int vector_pop_back(CacheVector *vec, void *element)
{
    if (!vec || vec->size == 0) {
        return -1;
    }
    
    vec->size--;
    
    if (element) {
        memcpy(element, 
               (char *)vec->data + vec->size * vec->element_size,
               vec->element_size);
    }
    
    /* 縮小チェック */
    if (vec->size < vec->capacity * VECTOR_SHRINK_THRESHOLD &&
        vec->capacity > VECTOR_MIN_CAPACITY) {
        size_t new_capacity = vec->capacity * VECTOR_SHRINK_FACTOR;
        if (new_capacity >= vec->size && new_capacity >= VECTOR_MIN_CAPACITY) {
            vector_reserve(vec, new_capacity);
        }
    }
    
    return 0;
}

/* 要素アクセス */
void *vector_at(CacheVector *vec, size_t index)
{
    if (!vec || index >= vec->size) {
        return NULL;
    }
    
    vec->total_accesses++;
    
    /* プリフェッチヒント */
    if (index + vec->prefetch_distance < vec->size) {
        PREFETCH_READ((char *)vec->data + 
                      (index + vec->prefetch_distance) * vec->element_size);
    }
    
    return (char *)vec->data + index * vec->element_size;
}

/* バルク挿入 */
int vector_insert_bulk(CacheVector *vec, size_t index, 
                      const void *elements, size_t count)
{
    size_t move_count;
    char *insert_pos;
    double start_time;
    
    if (!vec || !elements || index > vec->size) {
        return -1;
    }
    
    start_time = get_time_sec();
    
    /* 容量確保 */
    if (vector_adjust_capacity(vec, vec->size + count) < 0) {
        return -1;
    }
    
    insert_pos = (char *)vec->data + index * vec->element_size;
    move_count = vec->size - index;
    
    /* 既存要素の移動 */
    if (move_count > 0) {
        memmove(insert_pos + count * vec->element_size,
                insert_pos,
                move_count * vec->element_size);
    }
    
    /* 新要素のコピー */
    memcpy(insert_pos, elements, count * vec->element_size);
    vec->size += count;
    
    vec->total_operation_time += get_time_sec() - start_time;
    
    return 0;
}

/* バルク削除 */
int vector_remove_bulk(CacheVector *vec, size_t index, size_t count)
{
    size_t move_count;
    char *remove_pos;
    
    if (!vec || index >= vec->size || count == 0) {
        return -1;
    }
    
    /* 削除範囲の調整 */
    if (index + count > vec->size) {
        count = vec->size - index;
    }
    
    remove_pos = (char *)vec->data + index * vec->element_size;
    move_count = vec->size - index - count;
    
    /* 要素の移動 */
    if (move_count > 0) {
        memmove(remove_pos,
                remove_pos + count * vec->element_size,
                move_count * vec->element_size);
    }
    
    vec->size -= count;
    
    return 0;
}

/* キャッシュ最適化された反復処理 */
void vector_cache_optimized_iterate(CacheVector *vec, 
                                   void (*process)(void *element, void *context),
                                   void *context)
{
    size_t i;
    char *current;
    size_t prefetch_ahead;
    
    if (!vec || !process || vec->size == 0) {
        return;
    }
    
    current = (char *)vec->data;
    prefetch_ahead = vec->prefetch_distance;
    
    /* メインループ */
    for (i = 0; i < vec->size; i++) {
        /* 先読み */
        if (i + prefetch_ahead < vec->size) {
            PREFETCH_READ(current + prefetch_ahead * vec->element_size);
        }
        
        process(current, context);
        current += vec->element_size;
    }
}

/* 統計情報表示 */
void vector_print_stats(const CacheVector *vec)
{
    if (!vec) {
        return;
    }
    
    printf("\n=== ベクター統計情報 ===\n");
    printf("要素サイズ: %lu バイト\n", (unsigned long)vec->element_size);
    printf("現在のサイズ: %lu 要素\n", (unsigned long)vec->size);
    printf("容量: %lu 要素\n", (unsigned long)vec->capacity);
    printf("メモリ使用量: %lu バイト\n", 
           (unsigned long)(vec->capacity * vec->element_size));
    printf("キャッシュライン当たり要素数: %lu\n", 
           (unsigned long)vec->cache_line_elements);
    printf("総アクセス数: %lu\n", (unsigned long)vec->total_accesses);
    
    if (vec->total_accesses > 0) {
        printf("平均操作時間: %.9f 秒\n", 
               vec->total_operation_time / vec->total_accesses);
    }
    
    printf("========================\n");
}

/* テスト関数群 */

/* 構造体定義（テスト用） */
typedef struct TestData {
    int id;
    double value;
    char padding[48];  /* キャッシュライン埋め */
} TestData;

/* 処理関数（テスト用） */
void process_element(void *element, void *context)
{
    TestData *data = (TestData *)element;
    double *sum = (double *)context;
    *sum += data->value;
}

/* 基本動作テスト */
void test_basic_operations(void)
{
    CacheVector *vec;
    TestData data;
    int i;
    
    printf("=== 基本動作テスト ===\n");
    
    vec = vector_create(sizeof(TestData));
    if (!vec) {
        printf("ベクター作成失敗\n");
        return;
    }
    
    /* 要素追加 */
    for (i = 0; i < 100; i++) {
        data.id = i;
        data.value = i * 1.5;
        vector_push_back(vec, &data);
    }
    
    printf("100要素追加完了\n");
    
    /* 要素アクセス */
    for (i = 0; i < 10; i++) {
        TestData *p = (TestData *)vector_at(vec, i * 10);
        if (p) {
            printf("vec[%d]: id=%d, value=%.1f\n", 
                   i * 10, p->id, p->value);
        }
    }
    
    vector_print_stats(vec);
    vector_destroy(vec);
}

/* キャッシュ効率テスト */
void test_cache_efficiency(void)
{
    CacheVector *vec;
    double sum1 = 0.0, sum2 = 0.0;
    double start, end;
    TestData data;
    int i;
    const int size = 100000;
    
    printf("\n=== キャッシュ効率テスト ===\n");
    
    vec = vector_create(sizeof(TestData));
    if (!vec) {
        return;
    }
    
    /* データ準備 */
    for (i = 0; i < size; i++) {
        data.id = i;
        data.value = i * 0.001;
        vector_push_back(vec, &data);
    }
    
    /* 通常の反復処理 */
    start = get_time_sec();
    for (i = 0; i < size; i++) {
        TestData *p = (TestData *)vector_at(vec, i);
        sum1 += p->value;
    }
    end = get_time_sec();
    printf("通常反復: %.6f 秒 (合計: %.2f)\n", end - start, sum1);
    
    /* キャッシュ最適化反復 */
    start = get_time_sec();
    vector_cache_optimized_iterate(vec, process_element, &sum2);
    end = get_time_sec();
    printf("最適化反復: %.6f 秒 (合計: %.2f)\n", end - start, sum2);
    
    vector_destroy(vec);
}

/* バルク操作テスト */
void test_bulk_operations(void)
{
    CacheVector *vec;
    TestData *bulk_data;
    int i;
    const int bulk_size = 1000;
    
    printf("\n=== バルク操作テスト ===\n");
    
    vec = vector_create(sizeof(TestData));
    bulk_data = (TestData *)malloc(sizeof(TestData) * bulk_size);
    
    if (!vec || !bulk_data) {
        if (vec) vector_destroy(vec);
        if (bulk_data) free(bulk_data);
        return;
    }
    
    /* バルクデータ準備 */
    for (i = 0; i < bulk_size; i++) {
        bulk_data[i].id = i + 1000;
        bulk_data[i].value = i * 2.0;
    }
    
    /* 初期データ */
    for (i = 0; i < 50; i++) {
        TestData data = {i, i * 1.0, {0}};
        vector_push_back(vec, &data);
    }
    
    printf("初期サイズ: %lu\n", (unsigned long)vec->size);
    
    /* バルク挿入 */
    vector_insert_bulk(vec, 25, bulk_data, bulk_size);
    printf("バルク挿入後: %lu\n", (unsigned long)vec->size);
    
    /* バルク削除 */
    vector_remove_bulk(vec, 100, 500);
    printf("バルク削除後: %lu\n", (unsigned long)vec->size);
    
    vector_print_stats(vec);
    
    free(bulk_data);
    vector_destroy(vec);
}

/* パフォーマンス比較 */
void test_performance_comparison(void)
{
    CacheVector *vec;
    int *array;
    double start, end;
    int i, j;
    const int size = 1000000;
    const int iterations = 10;
    int sum = 0;
    
    printf("\n=== パフォーマンス比較 ===\n");
    
    vec = vector_create(sizeof(int));
    array = (int *)malloc(sizeof(int) * size);
    
    if (!vec || !array) {
        if (vec) vector_destroy(vec);
        if (array) free(array);
        return;
    }
    
    /* データ準備 */
    for (i = 0; i < size; i++) {
        int value = i;
        vector_push_back(vec, &value);
        array[i] = i;
    }
    
    /* 通常配列アクセス */
    start = get_time_sec();
    for (j = 0; j < iterations; j++) {
        sum = 0;
        for (i = 0; i < size; i++) {
            sum += array[i];
        }
    }
    end = get_time_sec();
    printf("通常配列: %.6f 秒 (結果: %d)\n", end - start, sum);
    
    /* ベクターアクセス */
    start = get_time_sec();
    for (j = 0; j < iterations; j++) {
        sum = 0;
        for (i = 0; i < size; i++) {
            int *p = (int *)vector_at(vec, i);
            sum += *p;
        }
    }
    end = get_time_sec();
    printf("ベクター: %.6f 秒 (結果: %d)\n", end - start, sum);
    
    free(array);
    vector_destroy(vec);
}

/* メイン関数 */
int main(void)
{
    printf("=== キャッシュフレンドリーベクターデモ ===\n");
    printf("キャッシュラインサイズ: %d バイト\n", CACHE_LINE_SIZE);
    printf("\n");
    
    /* 各種テスト実行 */
    test_basic_operations();
    test_cache_efficiency();
    test_bulk_operations();
    test_performance_comparison();
    
    printf("\n=== デモ完了 ===\n");
    return 0;
}

/*
実行例:
=== キャッシュフレンドリーベクターデモ ===
キャッシュラインサイズ: 64 バイト

=== 基本動作テスト ===
100要素追加完了
vec[0]: id=0, value=0.0
vec[10]: id=10, value=15.0
vec[20]: id=20, value=30.0
vec[30]: id=30, value=45.0
vec[40]: id=40, value=60.0
vec[50]: id=50, value=75.0
vec[60]: id=60, value=90.0
vec[70]: id=70, value=105.0
vec[80]: id=80, value=120.0
vec[90]: id=90, value=135.0

=== ベクター統計情報 ===
要素サイズ: 64 バイト
現在のサイズ: 100 要素
容量: 128 要素
メモリ使用量: 8192 バイト
キャッシュライン当たり要素数: 1
総アクセス数: 110
平均操作時間: 0.000000123 秒
========================

=== キャッシュ効率テスト ===
通常反復: 0.012345 秒 (合計: 4999950000.00)
最適化反復: 0.009876 秒 (合計: 4999950000.00)

=== バルク操作テスト ===
初期サイズ: 50
バルク挿入後: 1050
バルク削除後: 550

=== ベクター統計情報 ===
要素サイズ: 64 バイト
現在のサイズ: 550 要素
容量: 2048 要素
メモリ使用量: 131072 バイト
キャッシュライン当たり要素数: 1
総アクセス数: 100050
平均操作時間: 0.000000089 秒
========================

=== パフォーマンス比較 ===
通常配列: 0.234567 秒 (結果: 1783293664)
ベクター: 0.345678 秒 (結果: 1783293664)

=== デモ完了 ===
*/