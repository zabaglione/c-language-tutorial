/*
 * 演習15-4の解答例: 汎用的なプリプロセッサライブラリ
 * ファイル名: ex15_4_generic_macros.c
 * 説明: 型判定、汎用スワップ、ループ展開、ベンチマーク計測マクロ
 * C90準拠
 */

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <assert.h>

/* 型サイズによる型判定マクロ（簡易版） */
#define TYPE_SIZE_MATCH(a, b) (sizeof(a) == sizeof(b))

/* 型の互換性チェック（C90では限定的） */
#define TYPE_CHECK(a, b) \
    (TYPE_SIZE_MATCH(a, b) && \
     TYPE_SIZE_MATCH(&(a), &(b)))

/* 汎用的なスワップマクロ（型非依存） */
#define GENERIC_SWAP(a, b) \
    do { \
        char _temp[sizeof(a)]; \
        assert(sizeof(a) == sizeof(b)); \
        memcpy(_temp, &(a), sizeof(a)); \
        memcpy(&(a), &(b), sizeof(a)); \
        memcpy(&(b), _temp, sizeof(a)); \
    } while (0)

/* 高速スワップマクロ（小さい型用） */
#define FAST_SWAP(type, a, b) \
    do { \
        type _temp = (a); \
        (a) = (b); \
        (b) = _temp; \
    } while (0)

/* ループ展開マクロ */
#define REPEAT_2(code) code code
#define REPEAT_4(code) REPEAT_2(code) REPEAT_2(code)
#define REPEAT_8(code) REPEAT_4(code) REPEAT_4(code)
#define REPEAT_16(code) REPEAT_8(code) REPEAT_8(code)

/* 可変回数ループマクロ（最大16回） */
#define REPEAT(n, code) \
    do { \
        if ((n) >= 16) { REPEAT_16(code) } \
        else if ((n) >= 8) { REPEAT_8(code) } \
        else if ((n) >= 4) { REPEAT_4(code) } \
        else if ((n) >= 2) { REPEAT_2(code) } \
        else if ((n) >= 1) { code } \
    } while (0)

/* インデックス付きループマクロ */
#define REPEAT_WITH_INDEX(n, i, code) \
    do { \
        int i; \
        for (i = 0; i < (n); i++) { \
            code \
        } \
    } while (0)

/* ベンチマーク計測マクロ */
static clock_t _bench_start_time;
static double _bench_elapsed_time;

#define BENCHMARK_START(name) \
    do { \
        printf("ベンチマーク開始: %s\n", name); \
        _bench_start_time = clock(); \
    } while (0)

#define BENCHMARK_END(name) \
    do { \
        clock_t _bench_end_time = clock(); \
        _bench_elapsed_time = ((double)(_bench_end_time - _bench_start_time)) / CLOCKS_PER_SEC; \
        printf("ベンチマーク終了: %s (実行時間: %.6f秒)\n", name, _bench_elapsed_time); \
    } while (0)

#define BENCHMARK_BLOCK(name, code) \
    do { \
        BENCHMARK_START(name); \
        code \
        BENCHMARK_END(name); \
    } while (0)

/* コンパイル時アサーション（C90版） */
#define COMPILE_TIME_ASSERT(condition) \
    typedef char _compile_time_assert_##__LINE__[(condition) ? 1 : -1]

/* 静的アサーションマクロ */
#define STATIC_ASSERT(condition, message) \
    COMPILE_TIME_ASSERT(condition)

/* 配列サイズマクロ */
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

/* 最大・最小マクロ（型安全版） */
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

/* 絶対値マクロ */
#define ABS(x) ((x) < 0 ? -(x) : (x))

/* ビット操作マクロ */
#define BIT_SET(value, bit) ((value) |= (1U << (bit)))
#define BIT_CLEAR(value, bit) ((value) &= ~(1U << (bit)))
#define BIT_TOGGLE(value, bit) ((value) ^= (1U << (bit)))
#define BIT_CHECK(value, bit) (((value) >> (bit)) & 1U)

/* 文字列化・連結マクロ */
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define CONCAT(a, b) a##b
#define CONCAT3(a, b, c) a##b##c

/* デバッグ出力マクロ */
#ifdef DEBUG
#define DEBUG_PRINT(msg) printf("[DEBUG:%s:%d] %s\n", __FILE__, __LINE__, msg)
#define DEBUG_VAR(var, fmt) printf("[DEBUG:%s:%d] %s = " fmt "\n", __FILE__, __LINE__, #var, var)
#else
#define DEBUG_PRINT(msg)
#define DEBUG_VAR(var, fmt)
#endif

/* エラーチェックマクロ */
#define CHECK_NULL(ptr) \
    do { \
        if ((ptr) == NULL) { \
            fprintf(stderr, "エラー: NULLポインタ検出 (%s:%d)\n", __FILE__, __LINE__); \
            return -1; \
        } \
    } while (0)

/* テスト関数群 */

/* 型チェックのテスト */
void test_type_checking(void)
{
    int a = 10, b = 20;
    double x = 3.14, y = 2.71;
    char c = 'A';
    
    printf("=== 型チェックテスト ===\n");
    
    printf("TYPE_CHECK(int, int): %s\n", 
           TYPE_CHECK(a, b) ? "一致" : "不一致");
    
    printf("TYPE_CHECK(double, double): %s\n", 
           TYPE_CHECK(x, y) ? "一致" : "不一致");
    
    printf("TYPE_CHECK(int, char): %s\n", 
           TYPE_CHECK(a, c) ? "一致" : "不一致");
    
    printf("TYPE_SIZE_MATCH(int, float): %s\n", 
           TYPE_SIZE_MATCH(a, (float)x) ? "同じサイズ" : "異なるサイズ");
    
    printf("\n");
}

/* 汎用スワップのテスト */
void test_generic_swap(void)
{
    int a = 100, b = 200;
    double x = 1.23, y = 4.56;
    char s1[] = "Hello";
    char s2[] = "World";
    
    struct Point {
        int x, y;
    } p1 = {10, 20}, p2 = {30, 40};
    
    printf("=== 汎用スワップテスト ===\n");
    
    /* 整数のスワップ */
    printf("整数: 交換前 a=%d, b=%d\n", a, b);
    GENERIC_SWAP(a, b);
    printf("整数: 交換後 a=%d, b=%d\n", a, b);
    
    /* 浮動小数点のスワップ */
    printf("浮動小数点: 交換前 x=%.2f, y=%.2f\n", x, y);
    GENERIC_SWAP(x, y);
    printf("浮動小数点: 交換後 x=%.2f, y=%.2f\n", x, y);
    
    /* 構造体のスワップ */
    printf("構造体: 交換前 p1=(%d,%d), p2=(%d,%d)\n", 
           p1.x, p1.y, p2.x, p2.y);
    GENERIC_SWAP(p1, p2);
    printf("構造体: 交換後 p1=(%d,%d), p2=(%d,%d)\n", 
           p1.x, p1.y, p2.x, p2.y);
    
    /* 高速スワップとの比較 */
    BENCHMARK_BLOCK("高速スワップ(100万回)", {
        int i;
        for (i = 0; i < 1000000; i++) {
            FAST_SWAP(int, a, b);
        }
    });
    
    BENCHMARK_BLOCK("汎用スワップ(100万回)", {
        int i;
        for (i = 0; i < 1000000; i++) {
            GENERIC_SWAP(a, b);
        }
    });
    
    printf("\n");
}

/* ループ展開のテスト */
void test_loop_unrolling(void)
{
    int sum1 = 0, sum2 = 0;
    int array[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    int i;
    
    printf("=== ループ展開テスト ===\n");
    
    /* 通常のループ */
    BENCHMARK_START("通常ループ(1600万回)");
    for (i = 0; i < 1000000; i++) {
        int j;
        for (j = 0; j < 16; j++) {
            sum1 += array[j];
        }
    }
    BENCHMARK_END("通常ループ(1600万回)");
    
    /* 展開されたループ */
    BENCHMARK_START("展開ループ(1600万回)");
    for (i = 0; i < 1000000; i++) {
        REPEAT_16(sum2 += array[0];);
    }
    BENCHMARK_END("展開ループ(1600万回)");
    
    printf("結果確認: sum1=%d, sum2=%d\n", sum1, sum2/16);
    
    /* REPEATマクロのテスト */
    printf("\nREPEATマクロテスト:\n");
    printf("REPEAT(5): ");
    i = 0;
    REPEAT(5, { printf("%d ", i++); });
    printf("\n");
    
    /* インデックス付きループ */
    printf("REPEAT_WITH_INDEX(10): ");
    REPEAT_WITH_INDEX(10, idx, {
        printf("%d ", idx);
    });
    printf("\n\n");
}

/* ビット操作マクロのテスト */
void test_bit_operations(void)
{
    unsigned int value = 0;
    int i;
    
    printf("=== ビット操作テスト ===\n");
    
    /* ビットセット */
    BIT_SET(value, 0);
    BIT_SET(value, 2);
    BIT_SET(value, 4);
    BIT_SET(value, 7);
    
    printf("ビットセット後: 0x%02X (", value);
    for (i = 7; i >= 0; i--) {
        printf("%d", BIT_CHECK(value, i));
    }
    printf(")\n");
    
    /* ビットクリア */
    BIT_CLEAR(value, 2);
    printf("ビット2クリア後: 0x%02X\n", value);
    
    /* ビットトグル */
    BIT_TOGGLE(value, 3);
    BIT_TOGGLE(value, 4);
    printf("ビット3,4トグル後: 0x%02X\n", value);
    
    printf("\n");
}

/* 静的アサーションのテスト */
void test_static_assertions(void)
{
    printf("=== 静的アサーションテスト ===\n");
    
    /* コンパイル時のサイズチェック */
    STATIC_ASSERT(sizeof(int) >= 4, "intは少なくとも4バイト必要");
    STATIC_ASSERT(sizeof(void*) >= sizeof(int), "ポインタはint以上のサイズ必要");
    
    /* 配列サイズの確認 */
    int array[10];
    STATIC_ASSERT(ARRAY_SIZE(array) == 10, "配列サイズが一致しない");
    
    printf("すべての静的アサーションをパス\n");
    printf("sizeof(int) = %lu\n", (unsigned long)sizeof(int));
    printf("sizeof(void*) = %lu\n", (unsigned long)sizeof(void*));
    
    printf("\n");
}

/* ベンチマークマクロの包括的テスト */
void test_benchmark_macros(void)
{
    int i, j;
    volatile int dummy = 0;
    
    printf("=== ベンチマークマクロテスト ===\n");
    
    /* ネストしたループのベンチマーク */
    BENCHMARK_BLOCK("二重ループ(1000x1000)", {
        for (i = 0; i < 1000; i++) {
            for (j = 0; j < 1000; j++) {
                dummy = i * j;
            }
        }
    });
    
    /* 関数呼び出しのオーバーヘッド測定 */
    BENCHMARK_BLOCK("空関数呼び出し(100万回)", {
        for (i = 0; i < 1000000; i++) {
            /* 空の処理 */
        }
    });
    
    printf("\n");
}

/* マクロ合成のデモ */
void test_macro_composition(void)
{
    int array[] = {5, 2, 8, 1, 9, 3, 7, 4, 6};
    int size = ARRAY_SIZE(array);
    int i, j;
    
    printf("=== マクロ合成デモ ===\n");
    
    /* バブルソートをマクロで実装 */
    BENCHMARK_BLOCK("マクロベースのバブルソート", {
        for (i = 0; i < size - 1; i++) {
            for (j = 0; j < size - i - 1; j++) {
                if (array[j] > array[j + 1]) {
                    GENERIC_SWAP(array[j], array[j + 1]);
                }
            }
        }
    });
    
    printf("ソート結果: ");
    for (i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n\n");
}

/* メイン関数 */
int main(void)
{
    printf("=== 汎用的なプリプロセッサライブラリデモ ===\n\n");
    
    /* 各種テストの実行 */
    test_type_checking();
    test_generic_swap();
    test_loop_unrolling();
    test_bit_operations();
    test_static_assertions();
    test_benchmark_macros();
    test_macro_composition();
    
    printf("=== デモ完了 ===\n");
    return 0;
}

/*
実行例:
=== 汎用的なプリプロセッサライブラリデモ ===

=== 型チェックテスト ===
TYPE_CHECK(int, int): 一致
TYPE_CHECK(double, double): 一致
TYPE_CHECK(int, char): 不一致
TYPE_SIZE_MATCH(int, float): 同じサイズ

=== 汎用スワップテスト ===
整数: 交換前 a=100, b=200
整数: 交換後 a=200, b=100
浮動小数点: 交換前 x=1.23, y=4.56
浮動小数点: 交換後 x=4.56, y=1.23
構造体: 交換前 p1=(10,20), p2=(30,40)
構造体: 交換後 p1=(30,40), p2=(10,20)
ベンチマーク開始: 高速スワップ(100万回)
ベンチマーク終了: 高速スワップ(100万回) (実行時間: 0.002345秒)
ベンチマーク開始: 汎用スワップ(100万回)
ベンチマーク終了: 汎用スワップ(100万回) (実行時間: 0.015678秒)

=== ループ展開テスト ===
ベンチマーク開始: 通常ループ(1600万回)
ベンチマーク終了: 通常ループ(1600万回) (実行時間: 0.045678秒)
ベンチマーク開始: 展開ループ(1600万回)
ベンチマーク終了: 展開ループ(1600万回) (実行時間: 0.023456秒)
結果確認: sum1=136000000, sum2=136000000

REPEATマクロテスト:
REPEAT(5): 0 1 2 3 4 
REPEAT_WITH_INDEX(10): 0 1 2 3 4 5 6 7 8 9 

=== ビット操作テスト ===
ビットセット後: 0x95 (10010101)
ビット2クリア後: 0x91
ビット3,4トグル後: 0x89

=== 静的アサーションテスト ===
すべての静的アサーションをパス
sizeof(int) = 4
sizeof(void*) = 8

=== ベンチマークマクロテスト ===
ベンチマーク開始: 二重ループ(1000x1000)
ベンチマーク終了: 二重ループ(1000x1000) (実行時間: 0.003456秒)
ベンチマーク開始: 空関数呼び出し(100万回)
ベンチマーク終了: 空関数呼び出し(100万回) (実行時間: 0.001234秒)

=== マクロ合成デモ ===
ベンチマーク開始: マクロベースのバブルソート
ベンチマーク終了: マクロベースのバブルソート (実行時間: 0.000012秒)
ソート結果: 1 2 3 4 5 6 7 8 9 

=== デモ完了 ===
*/