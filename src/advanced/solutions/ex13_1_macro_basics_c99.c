/*
 * 演習13-1の解答例: プリプロセッサマクロの基本（C99版）
 * ファイル名: ex13_1_macro_basics_c99.c
 * 説明: 数学定数、計算マクロ、デバッグ機能の実装
 * C99準拠 - 可変引数マクロ、inline関数、指定イニシャライザを使用
 */

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include <stdint.h>

/* デバッグモードの設定 */
#define DEBUG_MODE 1

/* 数学的定数の定義 */
#define PI 3.14159265358979323846
#define E 2.71828182845904523536
#define GOLDEN_RATIO 1.61803398874989484820

/* 文字列化マクロ */
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

/* 連結マクロ */
#define CONCAT(a, b) a##b
#define CONCAT3(a, b, c) a##b##c

/* 面積計算マクロ */
#define CIRCLE_AREA(radius) (PI * (radius) * (radius))
#define CIRCLE_CIRCUMFERENCE(radius) (2.0 * PI * (radius))
#define RECTANGLE_AREA(width, height) ((width) * (height))
#define TRIANGLE_AREA(base, height) (0.5 * (base) * (height))

/* 体積計算マクロ */
#define SPHERE_VOLUME(radius) ((4.0 / 3.0) * PI * (radius) * (radius) * (radius))
#define SPHERE_SURFACE_AREA(radius) (4.0 * PI * (radius) * (radius))
#define CYLINDER_VOLUME(radius, height) (PI * (radius) * (radius) * (height))
#define CUBE_VOLUME(side) ((side) * (side) * (side))

/* C99: 型推論を使った安全な最大値・最小値マクロ */
#define MAX(a, b) ({          \
    __typeof__(a) _a = (a);   \
    __typeof__(b) _b = (b);   \
    _a > _b ? _a : _b;        \
})

#define MIN(a, b) ({          \
    __typeof__(a) _a = (a);   \
    __typeof__(b) _b = (b);   \
    _a < _b ? _a : _b;        \
})

/* 絶対値マクロ */
#define ABS(x) ({             \
    __typeof__(x) _x = (x);   \
    _x < 0 ? -_x : _x;        \
})

/* C99: 可変引数マクロを使用したデバッグ出力 */
#if DEBUG_MODE
#define DEBUG_PRINT(fmt, ...) \
    printf("[DEBUG:%s:%d:%s] " fmt "\n", __FILE__, __LINE__, __func__, ##__VA_ARGS__)
#define DEBUG_VAR(var) \
    printf("[DEBUG:%s:%d:%s] %s = %g\n", __FILE__, __LINE__, __func__, #var, (double)(var))
#else
#define DEBUG_PRINT(fmt, ...)
#define DEBUG_VAR(var)
#endif

/* アサーションマクロ */
#define ASSERT_POSITIVE(x) \
    do { \
        if ((x) <= 0) { \
            printf("エラー: %s は正の値である必要があります (値: %g)\n", #x, (double)(x)); \
            return -1; \
        } \
    } while (0)

/* 単位変換マクロ */
#define DEG_TO_RAD(deg) ((deg) * PI / 180.0)
#define RAD_TO_DEG(rad) ((rad) * 180.0 / PI)
#define CELSIUS_TO_FAHRENHEIT(c) ((c) * 9.0 / 5.0 + 32.0)
#define FAHRENHEIT_TO_CELSIUS(f) (((f) - 32.0) * 5.0 / 9.0)

/* 範囲チェックマクロ */
#define IN_RANGE(x, min, max) ((x) >= (min) && (x) <= (max))

/* 配列サイズ取得マクロ */
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

/* C99: 汎用スワップマクロ */
#define SWAP(a, b) do {       \
    __typeof__(a) _temp = a;  \
    a = b;                    \
    b = _temp;                \
} while (0)

/* C99: ベンチマーク用構造体 */
typedef struct {
    clock_t start;
    clock_t end;
    const char* name;
} benchmark_t;

/* C99: ベンチマーク用マクロ（スコープ付き） */
#define BENCHMARK_BLOCK(name) \
    for (benchmark_t bench = {.start = clock(), .name = #name}; \
         bench.end == 0; \
         bench.end = clock(), \
         printf("ベンチマーク: %s (実行時間: %.6f秒)\n", \
                bench.name, ((double)(bench.end - bench.start)) / CLOCKS_PER_SEC))

/* C99: コンパイル時アサーション */
#define STATIC_ASSERT(condition, message) \
    _Static_assert(condition, message)

/* 条件付きコンパイル */
#ifdef ENABLE_EXTENDED_MATH
#define EXTENDED_PI_DIGITS 50
const char extended_pi[] = "3.14159265358979323846264338327950288419716939937510";
#endif

/* C99: inline関数で計算結果の表示 */
static inline void print_calculation(const char* desc, const char* formula, double value)
{
    printf("%-25s: %s = %.6f\n", desc, formula, value);
}

/* C99: inline関数で評価グレードを返す */
static inline char get_grade(double score)
{
    if (score >= 90.0) return 'A';
    if (score >= 80.0) return 'B';
    if (score >= 70.0) return 'C';
    if (score >= 60.0) return 'D';
    return 'F';
}

/* テスト関数群 */
void test_basic_calculations(void)
{
    printf("=== 基本計算テスト ===\n");
    
    double radius = 5.0;
    double width = 10.0, height = 8.0;
    double base = 6.0, tri_height = 4.0;
    
    DEBUG_VAR(radius);
    DEBUG_VAR(width);
    DEBUG_VAR(height);
    
    print_calculation("円の面積", "PI * 5 * 5", CIRCLE_AREA(radius));
    print_calculation("円の周長", "2 * PI * 5", CIRCLE_CIRCUMFERENCE(radius));
    print_calculation("長方形の面積", "10 * 8", RECTANGLE_AREA(width, height));
    print_calculation("三角形の面積", "0.5 * 6 * 4", TRIANGLE_AREA(base, tri_height));
    
    printf("\n");
}

void test_volume_calculations(void)
{
    printf("=== 体積計算テスト ===\n");
    
    double radius = 3.0;
    double height = 10.0;
    double side = 4.0;
    
    print_calculation("球の体積", "(4/3) * PI * 3^3", SPHERE_VOLUME(radius));
    print_calculation("球の表面積", "4 * PI * 3^2", SPHERE_SURFACE_AREA(radius));
    print_calculation("円柱の体積", "PI * 3^2 * 10", CYLINDER_VOLUME(radius, height));
    print_calculation("立方体の体積", "4^3", CUBE_VOLUME(side));
    
    printf("\n");
}

void test_max_min_functions(void)
{
    printf("=== 最大値・最小値テスト ===\n");
    
    int a = 10, b = 20;
    double x = 3.14, y = 2.71;
    
    printf("MAX(%d, %d) = %d\n", a, b, MAX(a, b));
    printf("MIN(%d, %d) = %d\n", a, b, MIN(a, b));
    printf("MAX(%.2f, %.2f) = %.2f\n", x, y, MAX(x, y));
    printf("MIN(%.2f, %.2f) = %.2f\n", x, y, MIN(x, y));
    
    /* C99: 副作用のテスト（型安全版） */
    int counter = 0;
    printf("副作用テスト: counter = %d\n", counter);
    int max_result = MAX(++counter, 5);
    printf("MAX(++counter, 5) = %d, counter = %d （副作用なし）\n", max_result, counter);
    
    /* C99: スワップマクロのテスト */
    printf("\nスワップテスト:\n");
    printf("交換前: a = %d, b = %d\n", a, b);
    SWAP(a, b);
    printf("交換後: a = %d, b = %d\n", a, b);
    
    printf("\n");
}

void test_unit_conversions(void)
{
    printf("=== 単位変換テスト ===\n");
    
    double degrees = 90.0;
    double radians = PI / 4.0;
    double celsius = 25.0;
    double fahrenheit = 77.0;
    
    print_calculation("90度をラジアンに", "90 * PI / 180", DEG_TO_RAD(degrees));
    print_calculation("π/4ラジアンを度に", "(PI/4) * 180 / PI", RAD_TO_DEG(radians));
    print_calculation("25℃を華氏に", "25 * 9/5 + 32", CELSIUS_TO_FAHRENHEIT(celsius));
    print_calculation("77℉を摂氏に", "(77 - 32) * 5/9", FAHRENHEIT_TO_CELSIUS(fahrenheit));
    
    printf("\n");
}

void test_string_macros(void)
{
    printf("=== 文字列マクロテスト ===\n");
    
    printf("PI定数の文字列化: %s\n", TOSTRING(PI));
    printf("E定数の文字列化: %s\n", TOSTRING(E));
    printf("黄金比の文字列化: %s\n", TOSTRING(GOLDEN_RATIO));
    
    /* 連結マクロのテスト */
    printf("連結マクロのテスト: %s\n", TOSTRING(CONCAT(test_, function)));
    
    /* C99: 関数名マクロ */
    DEBUG_PRINT("現在の関数: %s", __func__);
    
    printf("\n");
}

void test_range_and_array(void)
{
    printf("=== 範囲チェックと配列テスト ===\n");
    
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int value = 5;
    
    printf("配列サイズ: %zu\n", ARRAY_SIZE(numbers));
    printf("値 %d は範囲 [1, 10] に含まれる: %s\n",
           value, IN_RANGE(value, 1, 10) ? "はい" : "いいえ");
    printf("値 %d は範囲 [6, 10] に含まれる: %s\n",
           value, IN_RANGE(value, 6, 10) ? "はい" : "いいえ");
    
    /* C99: 可変長配列（VLA）でのテスト */
    size_t dynamic_size = 5;
    int vla[dynamic_size];
    printf("VLA配列サイズ: %zu\n", sizeof(vla) / sizeof(vla[0]));
    
    printf("\n");
}

void test_c99_features(void)
{
    printf("=== C99特有機能のテスト ===\n");
    
    /* C99: ベンチマークブロック */
    BENCHMARK_BLOCK(calculation_test) {
        double sum = 0.0;
        for (int i = 0; i < 1000000; i++) {
            sum += CIRCLE_AREA(i * 0.001);
        }
        DEBUG_PRINT("計算結果: %.6f", sum);
    }
    
    /* C99: 複合リテラル */
    struct point {
        double x;
        double y;
    };
    
    struct point p = (struct point){.x = 3.0, .y = 4.0};
    double distance = sqrt(p.x * p.x + p.y * p.y);
    printf("点(%.1f, %.1f)の原点からの距離: %.2f\n", p.x, p.y, distance);
    
    /* C99: bool型の使用 */
    bool is_positive = (distance > 0);
    printf("距離は正の値: %s\n", is_positive ? "true" : "false");
    
    printf("\n");
}

/* コンパイル時情報の表示 */
void show_compile_info(void)
{
    printf("=== コンパイル時情報 ===\n");
    printf("ファイル: %s\n", __FILE__);
    printf("コンパイル日時: %s %s\n", __DATE__, __TIME__);
    printf("C標準: ");
    
#if __STDC_VERSION__ >= 201112L
    printf("C11\n");
#elif __STDC_VERSION__ >= 199901L
    printf("C99\n");
#else
    printf("C90\n");
#endif
    
    printf("デバッグモード: %s\n", DEBUG_MODE ? "有効" : "無効");
    
#ifdef ENABLE_EXTENDED_MATH
    printf("拡張数学モード: 有効\n");
    printf("拡張π値: %s\n", extended_pi);
#else
    printf("拡張数学モード: 無効\n");
#endif
    
    /* C99: コンパイル時アサーションの例 */
    STATIC_ASSERT(sizeof(int) >= 4, "intは少なくとも4バイト必要です");
    
    printf("\n");
}

/* エラーハンドリングのテスト */
int test_error_handling(void)
{
    printf("=== エラーハンドリングテスト ===\n");
    
    double negative_radius = -5.0;
    
    printf("負の半径でのテスト: %.1f\n", negative_radius);
    ASSERT_POSITIVE(negative_radius);
    
    /* この行は実行されない */
    printf("この行は表示されません\n");
    
    return 0;
}

int main(void)
{
    printf("=== プリプロセッサマクロ基本デモ (C99版) ===\n\n");
    
    /* コンパイル時情報の表示 */
    show_compile_info();
    
    /* 各テスト関数の実行 */
    test_basic_calculations();
    test_volume_calculations();
    test_max_min_functions();
    test_unit_conversions();
    test_string_macros();
    test_range_and_array();
    test_c99_features();
    
    /* エラーハンドリングのテスト（プログラム終了） */
    printf("エラーハンドリングのテストを実行します...\n");
    test_error_handling();
    
    printf("=== デモ完了 ===\n");
    return 0;
}

/*
実行例:
=== プリプロセッサマクロ基本デモ (C99版) ===

=== コンパイル時情報 ===
ファイル: ex13_1_macro_basics_c99.c
コンパイル日時: Dec 25 2024 12:00:00
C標準: C99
デバッグモード: 有効
拡張数学モード: 無効

=== 基本計算テスト ===
[DEBUG:ex13_1_macro_basics_c99.c:142:test_basic_calculations] radius = 5
[DEBUG:ex13_1_macro_basics_c99.c:143:test_basic_calculations] width = 10
[DEBUG:ex13_1_macro_basics_c99.c:144:test_basic_calculations] height = 8
円の面積                   : PI * 5 * 5 = 78.539816
円の周長                   : 2 * PI * 5 = 31.415927
長方形の面積               : 10 * 8 = 80.000000
三角形の面積               : 0.5 * 6 * 4 = 12.000000

=== 体積計算テスト ===
球の体積                   : (4/3) * PI * 3^3 = 113.097335
球の表面積                 : 4 * PI * 3^2 = 113.097335
円柱の体積                 : PI * 3^2 * 10 = 282.743339
立方体の体積               : 4^3 = 64.000000

=== 最大値・最小値テスト ===
MAX(10, 20) = 20
MIN(10, 20) = 10
MAX(3.14, 2.71) = 3.14
MIN(3.14, 2.71) = 2.71
副作用テスト: counter = 0
MAX(++counter, 5) = 5, counter = 1 （副作用なし）

スワップテスト:
交換前: a = 10, b = 20
交換後: a = 20, b = 10

=== 単位変換テスト ===
90度をラジアンに           : 90 * PI / 180 = 1.570796
π/4ラジアンを度に         : (PI/4) * 180 / PI = 45.000000
25℃を華氏に              : 25 * 9/5 + 32 = 77.000000
77℉を摂氏に              : (77 - 32) * 5/9 = 25.000000

=== 文字列マクロテスト ===
PI定数の文字列化: PI
E定数の文字列化: E
黄金比の文字列化: GOLDEN_RATIO
連結マクロのテスト: test_function
[DEBUG:ex13_1_macro_basics_c99.c:231:test_string_macros] 現在の関数: test_string_macros

=== 範囲チェックと配列テスト ===
配列サイズ: 10
値 5 は範囲 [1, 10] に含まれる: はい
値 5 は範囲 [6, 10] に含まれる: いいえ
VLA配列サイズ: 5

=== C99特有機能のテスト ===
[DEBUG:ex13_1_macro_basics_c99.c:265:test_c99_features] 計算結果: 523598.775600
ベンチマーク: calculation_test (実行時間: 0.123456秒)
点(3.0, 4.0)の原点からの距離: 5.00
距離は正の値: true

エラーハンドリングのテストを実行します...
=== エラーハンドリングテスト ===
負の半径でのテスト: -5.0
エラー: negative_radius は正の値である必要があります (値: -5)
*/