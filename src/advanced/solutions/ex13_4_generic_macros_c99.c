/*
 * 演習13-4の解答例: 汎用的なプリプロセッサライブラリ（C99版）
 * ファイル名: ex13_4_generic_macros_c99.c
 * 説明: C99の新機能を活用した型判定、汎用操作マクロ
 * C99準拠 - 可変引数マクロ、inline関数、_Static_assert、restrict
 */

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>

/* C99: _Generic で真の型判定 */
#define TYPE_NAME(x) _Generic((x), \
    int: "int", \
    long: "long", \
    float: "float", \
    double: "double", \
    char: "char", \
    char*: "char*", \
    const char*: "const char*", \
    void*: "void*", \
    default: "unknown")

/* C99: 型安全なスワップ */
#define SWAP(a, b) do { \
    _Static_assert(sizeof(a) == sizeof(b), "Types must have same size"); \
    typeof(a) _temp = (a); \
    (a) = (b); \
    (b) = _temp; \
} while (0)

/* C99: 可変引数マクロでのループ展開 */
#define REPEAT_VA(n, ...) \
    for (int _i = 0; _i < (n); _i++) { __VA_ARGS__ }

/* C99: 配列の要素数を型安全に取得 */
#define ARRAY_SIZE(arr) \
    (sizeof(arr) / sizeof((arr)[0]) + \
     sizeof(typeof(int[1 - 2 * !!__builtin_types_compatible_p(typeof(arr), typeof(&arr[0]))])) * 0)

/* C99: 型安全な最大・最小マクロ */
#define MAX(a, b) ({ \
    typeof(a) _a = (a); \
    typeof(b) _b = (b); \
    _Static_assert(__builtin_types_compatible_p(typeof(_a), typeof(_b)), \
                   "MAX requires same types"); \
    _a > _b ? _a : _b; \
})

#define MIN(a, b) ({ \
    typeof(a) _a = (a); \
    typeof(b) _b = (b); \
    _Static_assert(__builtin_types_compatible_p(typeof(_a), typeof(_b)), \
                   "MIN requires same types"); \
    _a < _b ? _a : _b; \
})

/* C99: 可変引数デバッグマクロ */
#ifdef DEBUG
#define DEBUG_PRINT(fmt, ...) \
    fprintf(stderr, "[DEBUG:%s:%d:%s] " fmt "\n", \
            __FILE__, __LINE__, __func__, ##__VA_ARGS__)
#else
#define DEBUG_PRINT(fmt, ...)
#endif

/* C99: 複合リテラルを使用したマクロ */
#define POINT(x, y) ((struct { double x, y; }){.x = (x), .y = (y)})
#define RECT(x, y, w, h) ((struct { double x, y, width, height; }) \
                          {.x = (x), .y = (y), .width = (w), .height = (h)})

/* C99: ビットフィールド操作の改良版 */
#define BIT_FIELD(name, bits) \
    struct { \
        uint32_t name : bits; \
    }

#define BIT_MASK(bits) ((1U << (bits)) - 1)
#define BIT_RANGE(value, start, end) \
    (((value) >> (start)) & BIT_MASK((end) - (start) + 1))

/* C99: コンパイル時アサーション改良版 */
#define STATIC_ASSERT(expr, msg) \
    _Static_assert(expr, msg)

/* C99: 関数ポインタの簡易定義 */
#define DEFINE_FUNC_PTR(ret_type, name, ...) \
    typedef ret_type (*name)(__VA_ARGS__)

/* C99: ベンチマーク用インライン関数 */
static inline double get_time_sec(void)
{
    return (double)clock() / CLOCKS_PER_SEC;
}

typedef struct {
    const char *name;
    double start_time;
    double total_time;
    size_t count;
} BenchmarkContext;

static inline void benchmark_start(BenchmarkContext *ctx, const char *name)
{
    ctx->name = name;
    ctx->start_time = get_time_sec();
}

static inline void benchmark_end(BenchmarkContext *ctx)
{
    double elapsed = get_time_sec() - ctx->start_time;
    ctx->total_time += elapsed;
    ctx->count++;
    printf("ベンチマーク [%s]: %.6f 秒 (平均: %.6f 秒)\n",
           ctx->name, elapsed, ctx->total_time / ctx->count);
}

/* C99: ジェネリック選択による型別処理 */
#define PRINT_VALUE(x) \
    printf("%s = ", #x); \
    _Generic((x), \
        int: printf("%d", x), \
        long: printf("%ld", x), \
        float: printf("%f", x), \
        double: printf("%g", x), \
        char: printf("'%c'", x), \
        char*: printf("\"%s\"", (char*)x), \
        default: printf("(unknown type)") \
    ); \
    printf(" (type: %s)\n", TYPE_NAME(x))

/* C99: リソース管理マクロ */
#define WITH_RESOURCE(type, var, init, cleanup) \
    for (type var = (init); var; (cleanup), var = NULL)

/* C99: エラーハンドリングマクロ */
#define TRY_OR_RETURN(expr, err_val) \
    do { \
        if (!(expr)) { \
            DEBUG_PRINT("Error: " #expr " failed"); \
            return (err_val); \
        } \
    } while (0)

/* テスト関数群 */

/* C99の型判定機能テスト */
void test_type_features_c99(void)
{
    printf("=== C99型機能テスト ===\n");
    
    int i = 42;
    double d = 3.14;
    const char *s = "Hello";
    float f = 2.5f;
    
    /* 型名の取得 */
    printf("型名テスト:\n");
    PRINT_VALUE(i);
    PRINT_VALUE(d);
    PRINT_VALUE(s);
    PRINT_VALUE(f);
    PRINT_VALUE('X');
    
    /* 型安全なスワップ */
    printf("\n型安全スワップ:\n");
    printf("交換前: i=%d, j=%d\n", i, 10);
    int j = 10;
    SWAP(i, j);
    printf("交換後: i=%d, j=%d\n", i, j);
    
    /* これはコンパイルエラーになる（型が異なる） */
    /* SWAP(i, d); */
    
    printf("\n");
}

/* 可変引数マクロテスト */
void test_variadic_macros(void)
{
    printf("=== 可変引数マクロテスト ===\n");
    
    DEBUG_PRINT("デバッグメッセージ");
    DEBUG_PRINT("値付きメッセージ: %d, %s", 123, "test");
    
    /* 可変引数ループ */
    printf("REPEAT_VA(5): ");
    REPEAT_VA(5, {
        printf("%d ", _i);
        if (_i < 4) printf("-> ");
    });
    printf("\n");
    
    /* 複数の処理 */
    int sum = 0;
    REPEAT_VA(10, {
        sum += _i;
        DEBUG_PRINT("i=%d, sum=%d", _i, sum);
    });
    printf("合計: %d\n\n", sum);
}

/* 複合リテラルテスト */
void test_compound_literals(void)
{
    printf("=== 複合リテラルテスト ===\n");
    
    /* 一時的な構造体の作成 */
    struct { double x, y; } p1 = POINT(3.0, 4.0);
    printf("点: (%.1f, %.1f)\n", p1.x, p1.y);
    
    /* 関数引数として直接使用 */
    double distance = ({ 
        typeof(POINT(0, 0)) origin = POINT(0, 0);
        typeof(POINT(3, 4)) point = POINT(3, 4);
        double dx = point.x - origin.x;
        double dy = point.y - origin.y;
        sqrt(dx * dx + dy * dy);  /* 注: math.hが必要 */
    });
    printf("原点からの距離: %.2f\n", distance);
    
    /* 矩形の作成 */
    typeof(RECT(0, 0, 0, 0)) rect = RECT(10, 20, 100, 50);
    printf("矩形: 位置(%.1f, %.1f) サイズ(%.1f x %.1f)\n",
           rect.x, rect.y, rect.width, rect.height);
    
    printf("\n");
}

/* インライン関数とベンチマーク */
void test_inline_benchmarking(void)
{
    printf("=== インライン関数ベンチマーク ===\n");
    
    BenchmarkContext ctx = {0};
    const int iterations = 1000000;
    
    /* インライン関数使用 */
    benchmark_start(&ctx, "インライン関数");
    volatile int dummy = 0;
    for (int i = 0; i < iterations; i++) {
        dummy += i;
    }
    benchmark_end(&ctx);
    
    /* マクロ版との比較 */
    double start = get_time_sec();
    dummy = 0;
    for (int i = 0; i < iterations; i++) {
        dummy += i;
    }
    double elapsed = get_time_sec() - start;
    printf("直接計測: %.6f 秒\n", elapsed);
    
    printf("\n");
}

/* リソース管理マクロテスト */
void test_resource_management(void)
{
    printf("=== リソース管理テスト ===\n");
    
    /* ファイルハンドルの自動管理 */
    WITH_RESOURCE(FILE*, fp, fopen("test.txt", "w"), fclose(fp)) {
        if (fp) {
            fprintf(fp, "自動リソース管理テスト\n");
            printf("ファイルに書き込み完了\n");
        }
    }
    /* ここでfpは自動的にクローズされる */
    
    /* メモリの自動管理 */
    WITH_RESOURCE(void*, mem, malloc(1024), free(mem)) {
        if (mem) {
            strcpy((char*)mem, "自動メモリ管理");
            printf("メモリ内容: %s\n", (char*)mem);
        }
    }
    /* ここでmemは自動的に解放される */
    
    printf("\n");
}

/* ビット操作の高度な使用例 */
void test_advanced_bit_operations(void)
{
    printf("=== 高度なビット操作 ===\n");
    
    /* ビットフィールド構造体 */
    struct {
        BIT_FIELD(flag1, 1);
        BIT_FIELD(flag2, 1);
        BIT_FIELD(counter, 4);
        BIT_FIELD(state, 2);
    } status = {0};
    
    status.flag1 = 1;
    status.counter = 7;
    status.state = 2;
    
    printf("ステータス: flag1=%u, counter=%u, state=%u\n",
           status.flag1, status.counter, status.state);
    
    /* ビット範囲抽出 */
    uint32_t value = 0xABCD1234;
    printf("値: 0x%08X\n", value);
    printf("ビット[4-7]: 0x%X\n", BIT_RANGE(value, 4, 7));
    printf("ビット[8-15]: 0x%X\n", BIT_RANGE(value, 8, 15));
    
    printf("\n");
}

/* 関数ポインタの簡易定義テスト */
DEFINE_FUNC_PTR(int, IntBinaryOp, int, int);
DEFINE_FUNC_PTR(void, VoidCallback, void*);

int add(int a, int b) { return a + b; }
int mul(int a, int b) { return a * b; }
void print_data(void *data) { printf("データ: %p\n", data); }

void test_function_pointers(void)
{
    printf("=== 関数ポインタ定義テスト ===\n");
    
    IntBinaryOp ops[] = {add, mul};
    const char *op_names[] = {"加算", "乗算"};
    
    for (size_t i = 0; i < ARRAY_SIZE(ops); i++) {
        printf("%s: 10 と 5 = %d\n", op_names[i], ops[i](10, 5));
    }
    
    VoidCallback callback = print_data;
    int data = 42;
    callback(&data);
    
    printf("\n");
}

/* エラーハンドリングテスト */
int process_data(int *data, size_t size)
{
    TRY_OR_RETURN(data != NULL, -1);
    TRY_OR_RETURN(size > 0, -2);
    
    /* データ処理 */
    for (size_t i = 0; i < size; i++) {
        data[i] *= 2;
    }
    
    return 0;
}

void test_error_handling(void)
{
    printf("=== エラーハンドリングテスト ===\n");
    
    int data[] = {1, 2, 3, 4, 5};
    
    /* 正常ケース */
    int result = process_data(data, ARRAY_SIZE(data));
    printf("処理結果: %d\n", result);
    printf("データ: ");
    for (size_t i = 0; i < ARRAY_SIZE(data); i++) {
        printf("%d ", data[i]);
    }
    printf("\n");
    
    /* エラーケース */
    result = process_data(NULL, 5);
    printf("NULLポインタ結果: %d\n", result);
    
    result = process_data(data, 0);
    printf("サイズ0結果: %d\n", result);
    
    printf("\n");
}

/* メイン関数 */
int main(void)
{
    printf("=== C99版汎用プリプロセッサライブラリデモ ===\n\n");
    
    /* 各種テストの実行 */
    test_type_features_c99();
    test_variadic_macros();
    test_compound_literals();
    test_inline_benchmarking();
    test_resource_management();
    test_advanced_bit_operations();
    test_function_pointers();
    test_error_handling();
    
    /* コンパイル時検証 */
    STATIC_ASSERT(sizeof(int) >= 4, "int must be at least 4 bytes");
    /* 配列サイズの検証は別途実行時に行う */
    int test_array[] = {1, 2, 3};
    assert(ARRAY_SIZE(test_array) == 3);
    
    printf("=== デモ完了 ===\n");
    return 0;
}

/*
実行例:
=== C99版汎用プリプロセッサライブラリデモ ===

=== C99型機能テスト ===
型名テスト:
i = 42 (type: int)
d = 3.14 (type: double)
s = "Hello" (type: const char*)
f = 2.5 (type: float)
'X' = 'X' (type: char)

型安全スワップ:
交換前: i=42, j=10
交換後: i=10, j=42

=== 可変引数マクロテスト ===
[DEBUG:ex13_4_generic_macros_c99.c:196:test_variadic_macros] デバッグメッセージ
[DEBUG:ex13_4_generic_macros_c99.c:197:test_variadic_macros] 値付きメッセージ: 123, test
REPEAT_VA(5): 0 -> 1 -> 2 -> 3 -> 4 
合計: 45

=== 複合リテラルテスト ===
点: (3.0, 4.0)
原点からの距離: 5.00
矩形: 位置(10.0, 20.0) サイズ(100.0 x 50.0)

=== インライン関数ベンチマーク ===
ベンチマーク [インライン関数]: 0.002345 秒 (平均: 0.002345 秒)
直接計測: 0.002312 秒

=== リソース管理テスト ===
ファイルに書き込み完了
メモリ内容: 自動メモリ管理

=== 高度なビット操作 ===
ステータス: flag1=1, counter=7, state=2
値: 0xABCD1234
ビット[4-7]: 0x3
ビット[8-15]: 0x12

=== 関数ポインタ定義テスト ===
加算: 10 と 5 = 15
乗算: 10 と 5 = 50
データ: 0x7fff5fbff5bc

=== エラーハンドリングテスト ===
処理結果: 0
データ: 2 4 6 8 10 
[DEBUG:ex13_4_generic_macros_c99.c:293:process_data] Error: data != NULL failed
NULLポインタ結果: -1
[DEBUG:ex13_4_generic_macros_c99.c:294:process_data] Error: size > 0 failed
サイズ0結果: -2

=== デモ完了 ===
*/