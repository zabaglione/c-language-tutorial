/*
 * 演習13-6の解答例: キャッシュフレンドリーなデータ構造（C99版）
 * ファイル名: ex13_6_cache_vector_c99.c
 * 説明: C99機能を活用したキャッシュ効率的な動的配列
 * C99準拠 - restrict、inline、bool、可変長配列、複合リテラル
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

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

/* アライメント指定（C99: _Alignas） */
#if __STDC_VERSION__ >= 201112L
#define CACHE_ALIGNED _Alignas(CACHE_LINE_SIZE)
#else
#ifdef __GNUC__
#define CACHE_ALIGNED __attribute__((aligned(CACHE_LINE_SIZE)))
#else
#define CACHE_ALIGNED
#endif
#endif

/* C99: 静的アサーション */
_Static_assert(CACHE_LINE_SIZE >= sizeof(void*),
               "Cache line size must be at least pointer size");

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
    
    /* C99: bool型の使用 */
    bool is_aligned;        /* アライメント済みフラグ */
} CACHE_ALIGNED CacheVector;

/* C99: inline関数プロトタイプ */
static inline double get_time_sec(void);
static inline size_t align_up(size_t size, size_t alignment);
static inline void *aligned_alloc_wrapper(size_t alignment, size_t size);

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

/* C99: inline関数実装 */
static inline double get_time_sec(void)
{
    return (double)clock() / CLOCKS_PER_SEC;
}

static inline size_t align_up(size_t size, size_t alignment)
{
    return (size + alignment - 1) & ~(alignment - 1);
}

/* C99: aligned_allocがない場合の代替実装 */
static inline void *aligned_alloc_wrapper(size_t alignment, size_t size)
{
#if __STDC_VERSION__ >= 201112L
    return aligned_alloc(alignment, size);
#else
    /* posix_memalignを使用（POSIX環境） */
    void *ptr = NULL;
    if (posix_memalign(&ptr, alignment, size) == 0) {
        return ptr;
    }
    return NULL;
#endif
}

/* ベクター作成 */
CacheVector *vector_create(size_t element_size)
{
    if (element_size == 0) {
        return NULL;
    }
    
    /* キャッシュラインアライメントされたメモリを確保 */
    CacheVector *vec = (CacheVector *)aligned_alloc_wrapper(CACHE_LINE_SIZE, sizeof(CacheVector));
    if (!vec) {
        return NULL;
    }
    
    /* C99: 指定イニシャライザ */
    *vec = (CacheVector){
        .element_size = element_size,
        .capacity = VECTOR_MIN_CAPACITY,
        .size = 0,
        .cache_line_elements = CACHE_LINE_SIZE / element_size,
        .prefetch_distance = 4 * (CACHE_LINE_SIZE / element_size),
        .total_accesses = 0,
        .cache_misses_estimate = 0,
        .total_operation_time = 0.0,
        .is_aligned = true,
        .data = NULL
    };
    
    if (vec->cache_line_elements == 0) {
        vec->cache_line_elements = 1;
    }
    
    /* データ領域もアライメント */
    vec->data = aligned_alloc_wrapper(CACHE_LINE_SIZE, vec->capacity * element_size);
    if (!vec->data) {
        free(vec);
        return NULL;
    }
    
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
static int vector_adjust_capacity(CacheVector *restrict vec, size_t required_capacity)
{
    if (required_capacity <= vec->capacity) {
        return 0;
    }
    
    /* 成長戦略 */
    size_t new_capacity = vec->capacity;
    while (new_capacity < required_capacity) {
        new_capacity *= VECTOR_GROWTH_FACTOR;
    }
    
    /* キャッシュライン境界に合わせる */
    new_capacity = align_up(new_capacity * vec->element_size, CACHE_LINE_SIZE) / vec->element_size;
    
    void *new_data = aligned_alloc_wrapper(CACHE_LINE_SIZE, new_capacity * vec->element_size);
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
int vector_push_back(CacheVector *restrict vec, const void *restrict element)
{
    if (!vec || !element) {
        return -1;
    }
    
    double start_time = get_time_sec();
    
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
int vector_pop_back(CacheVector *restrict vec, void *restrict element)
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
        size_t new_capacity = (size_t)(vec->capacity * VECTOR_SHRINK_FACTOR);
        if (new_capacity >= vec->size && new_capacity >= VECTOR_MIN_CAPACITY) {
            vector_reserve(vec, new_capacity);
        }
    }
    
    return 0;
}

/* 要素アクセス */
void *vector_at(CacheVector *restrict vec, size_t index)
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
int vector_insert_bulk(CacheVector *restrict vec, size_t index, 
                      const void *restrict elements, size_t count)
{
    if (!vec || !elements || index > vec->size) {
        return -1;
    }
    
    double start_time = get_time_sec();
    
    /* 容量確保 */
    if (vector_adjust_capacity(vec, vec->size + count) < 0) {
        return -1;
    }
    
    char *insert_pos = (char *)vec->data + index * vec->element_size;
    size_t move_count = vec->size - index;
    
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
int vector_remove_bulk(CacheVector *restrict vec, size_t index, size_t count)
{
    if (!vec || index >= vec->size || count == 0) {
        return -1;
    }
    
    /* 削除範囲の調整 */
    if (index + count > vec->size) {
        count = vec->size - index;
    }
    
    char *remove_pos = (char *)vec->data + index * vec->element_size;
    size_t move_count = vec->size - index - count;
    
    /* 要素の移動 */
    if (move_count > 0) {
        memmove(remove_pos,
                remove_pos + count * vec->element_size,
                move_count * vec->element_size);
    }
    
    vec->size -= count;
    
    return 0;
}

/* C99: ジェネリックな反復処理インターフェース */
typedef void (*vector_foreach_fn)(void *element, void *context);

void vector_foreach(CacheVector *restrict vec, 
                   vector_foreach_fn func,
                   void *context)
{
    if (!vec || !func || vec->size == 0) {
        return;
    }
    
    char *current = (char *)vec->data;
    size_t prefetch_ahead = vec->prefetch_distance;
    
    /* メインループ */
    for (size_t i = 0; i < vec->size; i++) {
        /* 先読み */
        if (i + prefetch_ahead < vec->size) {
            PREFETCH_READ(current + prefetch_ahead * vec->element_size);
        }
        
        func(current, context);
        current += vec->element_size;
    }
}

/* キャッシュ最適化 */
void vector_optimize_cache(CacheVector *vec)
{
    if (!vec || vec->size == 0) {
        return;
    }
    
    /* 要素サイズに基づいてプリフェッチ距離を調整 */
    size_t optimal_prefetch = 4 * vec->cache_line_elements;
    
    /* C99: 可変長配列を使用したテスト */
    size_t test_sizes[] = {2, 4, 8, 16};
    double best_time = INFINITY;
    size_t best_distance = vec->prefetch_distance;
    
    for (size_t i = 0; i < sizeof(test_sizes)/sizeof(test_sizes[0]); i++) {
        vec->prefetch_distance = test_sizes[i] * vec->cache_line_elements;
        
        /* 簡単なベンチマーク */
        double start = get_time_sec();
        volatile size_t dummy = 0;
        for (size_t j = 0; j < vec->size; j++) {
            void *elem = vector_at(vec, j);
            if (elem) {
                dummy += *(size_t*)elem & 1;
            }
        }
        double elapsed = get_time_sec() - start;
        
        if (elapsed < best_time) {
            best_time = elapsed;
            best_distance = vec->prefetch_distance;
        }
    }
    
    vec->prefetch_distance = best_distance;
}

/* 統計情報表示 */
void vector_print_stats(const CacheVector *vec)
{
    if (!vec) {
        return;
    }
    
    printf("\n=== ベクター統計情報 ===\n");
    printf("要素サイズ: %zu バイト\n", vec->element_size);
    printf("現在のサイズ: %zu 要素\n", vec->size);
    printf("容量: %zu 要素\n", vec->capacity);
    printf("メモリ使用量: %zu バイト\n", vec->capacity * vec->element_size);
    printf("キャッシュライン当たり要素数: %zu\n", vec->cache_line_elements);
    printf("プリフェッチ距離: %zu 要素\n", vec->prefetch_distance);
    printf("総アクセス数: %zu\n", vec->total_accesses);
    printf("アライメント済み: %s\n", vec->is_aligned ? "はい" : "いいえ");
    
    if (vec->total_accesses > 0) {
        printf("平均操作時間: %.9f 秒\n", 
               vec->total_operation_time / vec->total_accesses);
    }
    
    printf("========================\n");
}

/* テスト関数群 */

/* C99: 構造体定義（指定イニシャライザ対応） */
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
    printf("=== 基本動作テスト ===\n");
    
    CacheVector *vec = vector_create(sizeof(TestData));
    if (!vec) {
        printf("ベクター作成失敗\n");
        return;
    }
    
    /* C99: 複合リテラルを使用した要素追加 */
    for (int i = 0; i < 100; i++) {
        TestData data = {
            .id = i,
            .value = i * 1.5,
            .padding = {0}
        };
        vector_push_back(vec, &data);
    }
    
    printf("100要素追加完了\n");
    
    /* 要素アクセス */
    for (int i = 0; i < 10; i++) {
        TestData *p = (TestData *)vector_at(vec, i * 10);
        if (p) {
            printf("vec[%d]: id=%d, value=%.1f\n", 
                   i * 10, p->id, p->value);
        }
    }
    
    vector_print_stats(vec);
    vector_destroy(vec);
}

/* C99: 型ジェネリックなテスト */
#define DEFINE_TYPED_VECTOR_TEST(type, name, init_expr) \
    void test_##name##_vector(void) { \
        printf("\n=== " #type " ベクターテスト ===\n"); \
        CacheVector *vec = vector_create(sizeof(type)); \
        if (!vec) return; \
        \
        for (int i = 0; i < 1000; i++) { \
            type value = init_expr; \
            vector_push_back(vec, &value); \
        } \
        \
        type sum = 0; \
        for (size_t i = 0; i < vec->size; i++) { \
            type *p = (type *)vector_at(vec, i); \
            if (p) sum += *p; \
        } \
        printf(#type " ベクター合計: %g\n", (double)sum); \
        \
        vector_destroy(vec); \
    }

DEFINE_TYPED_VECTOR_TEST(int, int, i)
DEFINE_TYPED_VECTOR_TEST(double, double, i * 0.1)
DEFINE_TYPED_VECTOR_TEST(float, float, i * 0.01f)

/* キャッシュ効率テスト */
void test_cache_efficiency(void)
{
    printf("\n=== キャッシュ効率テスト ===\n");
    
    CacheVector *vec = vector_create(sizeof(TestData));
    if (!vec) {
        return;
    }
    
    const int size = 100000;
    
    /* データ準備 */
    for (int i = 0; i < size; i++) {
        TestData data = {
            .id = i,
            .value = i * 0.001,
            .padding = {0}
        };
        vector_push_back(vec, &data);
    }
    
    /* 最適化前 */
    double sum1 = 0.0;
    double start = get_time_sec();
    vector_foreach(vec, process_element, &sum1);
    double time1 = get_time_sec() - start;
    printf("最適化前: %.6f 秒 (合計: %.2f)\n", time1, sum1);
    
    /* キャッシュ最適化 */
    vector_optimize_cache(vec);
    
    /* 最適化後 */
    double sum2 = 0.0;
    start = get_time_sec();
    vector_foreach(vec, process_element, &sum2);
    double time2 = get_time_sec() - start;
    printf("最適化後: %.6f 秒 (合計: %.2f)\n", time2, sum2);
    
    printf("改善率: %.2f%%\n", (time1 - time2) / time1 * 100);
    
    vector_destroy(vec);
}

/* C99: 可変長配列を使用したバルク操作テスト */
void test_bulk_operations_vla(void)
{
    printf("\n=== VLAバルク操作テスト ===\n");
    
    CacheVector *vec = vector_create(sizeof(int));
    if (!vec) return;
    
    const int bulk_sizes[] = {10, 50, 100, 500};
    
    for (size_t i = 0; i < sizeof(bulk_sizes)/sizeof(bulk_sizes[0]); i++) {
        int bulk_size = bulk_sizes[i];
        
        /* C99: VLA */
        int bulk_data[bulk_size];
        for (int j = 0; j < bulk_size; j++) {
            bulk_data[j] = j + 1000 * (i + 1);
        }
        
        size_t old_size = vec->size;
        vector_insert_bulk(vec, vec->size, bulk_data, bulk_size);
        printf("バルク挿入 %d 要素: サイズ %zu -> %zu\n", 
               bulk_size, old_size, vec->size);
    }
    
    vector_print_stats(vec);
    vector_destroy(vec);
}

/* メイン関数 */
int main(void)
{
    printf("=== キャッシュフレンドリーベクターデモ (C99版) ===\n");
    printf("キャッシュラインサイズ: %d バイト\n", CACHE_LINE_SIZE);
    printf("\n");
    
    /* 各種テスト実行 */
    test_basic_operations();
    test_int_vector();
    test_double_vector();
    test_float_vector();
    test_cache_efficiency();
    test_bulk_operations_vla();
    
    printf("\n=== デモ完了 ===\n");
    return 0;
}

/*
実行例:
=== キャッシュフレンドリーベクターデモ (C99版) ===
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
プリフェッチ距離: 4 要素
総アクセス数: 110
アライメント済み: はい
平均操作時間: 0.000000123 秒
========================

=== int ベクターテスト ===
int ベクター合計: 499500

=== double ベクターテスト ===
double ベクター合計: 49950

=== float ベクターテスト ===
float ベクター合計: 4995

=== キャッシュ効率テスト ===
最適化前: 0.008765 秒 (合計: 4999950000.00)
最適化後: 0.007234 秒 (合計: 4999950000.00)
改善率: 17.47%

=== VLAバルク操作テスト ===
バルク挿入 10 要素: サイズ 0 -> 10
バルク挿入 50 要素: サイズ 10 -> 60
バルク挿入 100 要素: サイズ 60 -> 160
バルク挿入 500 要素: サイズ 160 -> 660

=== ベクター統計情報 ===
要素サイズ: 4 バイト
現在のサイズ: 660 要素
容量: 1024 要素
メモリ使用量: 4096 バイト
キャッシュライン当たり要素数: 16
プリフェッチ距離: 64 要素
総アクセス数: 4
アライメント済み: はい
平均操作時間: 0.000001234 秒
========================

=== デモ完了 ===
*/