/* 高度なプリプロセッサの活用 */
#include <stdio.h>
#include <string.h>
#include <time.h>

/* 基本的なマクロ定義 */
#define MAX_SIZE 100
#define PI 3.14159265359
#define SQUARE(x) ((x) * (x))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

/* 条件付きコンパイル用フラグ */
#define DEBUG_MODE 1
#define VERBOSE_OUTPUT 1

/* デバッグ用マクロ */
#if DEBUG_MODE
#define DEBUG_PRINT(fmt, ...) \
    printf("[DEBUG %s:%d] " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#else
#define DEBUG_PRINT(fmt, ...)
#endif

/* 詳細出力用マクロ */
#if VERBOSE_OUTPUT
#define VERBOSE(msg) printf("[VERBOSE] " msg "\n")
#else
#define VERBOSE(msg)
#endif

/* 文字列化マクロ */
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

/* 連結マクロ */
#define CONCAT(a, b) a##b
#define MAKE_FUNCTION_NAME(prefix, suffix) CONCAT(prefix, suffix)

/* 多行マクロ */
#define SAFE_DIVIDE(a, b, result)                         \
    do                                                    \
    {                                                     \
        if ((b) != 0)                                     \
        {                                                 \
            *(result) = (a) / (b);                        \
        }                                                 \
        else                                              \
        {                                                 \
            printf("エラー: ゼロ除算が検出されました\n"); \
            *(result) = 0;                                \
        }                                                 \
    } while (0)

/* 配列のサイズを取得するマクロ */
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

/* メモリ安全な操作マクロ */
#define SAFE_STRCPY(dest, src, size)  \
    do                                \
    {                                 \
        strncpy(dest, src, size - 1); \
        (dest)[(size) - 1] = '\0';    \
    } while (0)

/* 範囲チェック付きアクセスマクロ */
#define SAFE_ARRAY_ACCESS(arr, index, size) \
    ((index) >= 0 && (index) < (size) ? (arr)[index] : 0)

/* ビット操作マクロ */
#define SET_BIT(value, bit) ((value) |= (1 << (bit)))
#define CLEAR_BIT(value, bit) ((value) &= ~(1 << (bit)))
#define TOGGLE_BIT(value, bit) ((value) ^= (1 << (bit)))
#define CHECK_BIT(value, bit) (((value) >> (bit)) & 1)

/* 条件付きマクロ定義 */
#ifdef _WIN32
#define PLATFORM "Windows"
#define PATH_SEPARATOR "\\"
#elif defined(__linux__)
#define PLATFORM "Linux"
#define PATH_SEPARATOR "/"
#elif defined(__APPLE__)
#define PLATFORM "macOS"
#define PATH_SEPARATOR "/"
#else
#define PLATFORM "Unknown"
#define PATH_SEPARATOR "/"
#endif

/* コンパイル情報マクロ */
#define COMPILE_INFO()                            \
    printf("コンパイル情報:\n");                  \
    printf("  ファイル: %s\n", __FILE__);         \
    printf("  日付: %s\n", __DATE__);             \
    printf("  時刻: %s\n", __TIME__);             \
    printf("  プラットフォーム: %s\n", PLATFORM); \
    printf("  C標準: " TOSTRING(__STDC_VERSION__) "\n")

/* 動的に生成される関数群 */
#define DECLARE_OPERATION_FUNCTION(type, name, op)            \
    type MAKE_FUNCTION_NAME(name, _operation)(type a, type b) \
    {                                                         \
        DEBUG_PRINT("演算実行: %s", STRINGIFY(name));         \
        return a op b;                                        \
    }

/* 各種データ型用の演算関数を生成 */
DECLARE_OPERATION_FUNCTION(int, add_int, +)
DECLARE_OPERATION_FUNCTION(int, sub_int, -)
DECLARE_OPERATION_FUNCTION(int, mul_int, *)
DECLARE_OPERATION_FUNCTION(double, add_double, +)
DECLARE_OPERATION_FUNCTION(double, sub_double, -)
DECLARE_OPERATION_FUNCTION(double, mul_double, *)

/* 型判定マクロ（GCC拡張機能） - 教育目的でコメントアウト */
/* #define IS_SAME_TYPE(a, b) __builtin_types_compatible_p(typeof(a), typeof(b)) */

/* 汎用スワップマクロ（型固有版を使用） */
#define SWAP_INT(a, b)        \
    do                        \
    {                         \
        int temp = (a);       \
        (a) = (b);            \
        (b) = temp;           \
    } while (0)

#define SWAP_DOUBLE(a, b)     \
    do                        \
    {                         \
        double temp = (a);    \
        (a) = (b);            \
        (b) = temp;           \
    } while (0)

/* エラーチェック付きマクロ */
#define CHECK_NULL(ptr, action)                                                           \
    do                                                                                    \
    {                                                                                     \
        if ((ptr) == NULL)                                                                \
        {                                                                                 \
            printf("エラー: NULLポインタが検出されました (%s:%d)\n", __FILE__, __LINE__); \
            action;                                                                       \
        }                                                                                 \
    } while (0)

/* ベンチマーク用マクロ */
#define BENCHMARK_START() \
    clock_t start_time = clock()

#define BENCHMARK_END(operation_name)                                        \
    do                                                                       \
    {                                                                        \
        clock_t end_time = clock();                                          \
        double elapsed = ((double)(end_time - start_time)) / CLOCKS_PER_SEC; \
        printf("ベンチマーク [%s]: %.6f秒\n", operation_name, elapsed);      \
    } while (0)

/* アサーションマクロ */
#define ASSERT(condition, message)                                                 \
    do                                                                             \
    {                                                                              \
        if (!(condition))                                                          \
        {                                                                          \
            printf("アサーション失敗: %s (%s:%d)\n", message, __FILE__, __LINE__); \
            printf("条件: %s\n", STRINGIFY(condition));                            \
        }                                                                          \
    } while (0)

/* テスト用関数 */
void test_basic_macros(void)
{
    printf("=== 基本的なマクロテスト ===\n");

    VERBOSE("基本マクロのテストを開始します");

    int a = 5, b = 3;

    printf("SQUARE(%d) = %d\n", a, SQUARE(a));
    printf("MAX(%d, %d) = %d\n", a, b, MAX(a, b));
    printf("MIN(%d, %d) = %d\n", a, b, MIN(a, b));

    DEBUG_PRINT("変数値: a=%d, b=%d", a, b);

    printf("PI = %f\n", PI);
    printf("MAX_SIZE = %d\n", MAX_SIZE);
}

void test_string_macros(void)
{
    printf("\n=== 文字列操作マクロテスト ===\n");

    VERBOSE("文字列マクロのテストを開始します");

    int value = 42;
    printf("STRINGIFY(value) = %s\n", STRINGIFY(value));
    printf("TOSTRING(MAX_SIZE) = %s\n", TOSTRING(MAX_SIZE));

    char buffer[50];
    const char *source = "Hello, World!";
    SAFE_STRCPY(buffer, source, sizeof(buffer));
    printf("SAFE_STRCPY結果: %s\n", buffer);

    /* 長すぎる文字列のテスト */
    char sumall_buffer[10];
    const char *long_source = "This is a very long string that exceeds buffer size";
    SAFE_STRCPY(sumall_buffer, long_source, sizeof(sumall_buffer));
    printf("切り詰められた文字列: %s\n", sumall_buffer);
}

void test_safe_operations(void)
{
    printf("\n=== 安全操作マクロテスト ===\n");

    VERBOSE("安全操作マクロのテストを開始します");

    double result;

    /* 正常な除算 */
    SAFE_DIVIDE(10.0, 2.0, &result);
    printf("10.0 / 2.0 = %f\n", result);

    /* ゼロ除算 */
    SAFE_DIVIDE(10.0, 0.0, &result);
    printf("10.0 / 0.0 = %f (エラー処理後)\n", result);

    /* 配列アクセステスト */
    int array[] = {10, 20, 30, 40, 50};
    int size = ARRAY_SIZE(array);

    printf("配列サイズ: %d\n", size);

    /* 安全な配列アクセス */
    printf("array[2] = %d\n", SAFE_ARRAY_ACCESS(array, 2, size));
    /* 範囲外アクセスの例（実際にはマクロで保護される） */
    printf("array[10] = %d (範囲外アクセス、マクロで保護)\n", SAFE_ARRAY_ACCESS(array, 10, size));
    printf("array[-1] = %d (負のインデックス、マクロで保護)\n", SAFE_ARRAY_ACCESS(array, -1, size));
}

void test_bit_operations(void)
{
    printf("\n=== ビット操作マクロテスト ===\n");

    VERBOSE("ビット操作マクロのテストを開始します");

    unsigned int flags = 0;

    printf("初期値: 0x%02X\n", flags);

    SET_BIT(flags, 0);
    printf("ビット0セット後: 0x%02X\n", flags);

    SET_BIT(flags, 3);
    printf("ビット3セット後: 0x%02X\n", flags);

    TOGGLE_BIT(flags, 1);
    printf("ビット1トグル後: 0x%02X\n", flags);

    printf("ビット0チェック: %d\n", CHECK_BIT(flags, 0));
    printf("ビット2チェック: %d\n", CHECK_BIT(flags, 2));

    CLEAR_BIT(flags, 0);
    printf("ビット0クリア後: 0x%02X\n", flags);
}

void test_dynamic_functions(void)
{
    printf("\n=== 動的生成関数テスト ===\n");

    VERBOSE("動的生成関数のテストを開始します");

    int int_a = 15, int_b = 7;
    double double_a = 3.14, double_b = 2.71;

    printf("整数演算:\n");
    printf("  %d + %d = %d\n", int_a, int_b, add_int_operation(int_a, int_b));
    printf("  %d - %d = %d\n", int_a, int_b, sub_int_operation(int_a, int_b));
    printf("  %d * %d = %d\n", int_a, int_b, mul_int_operation(int_a, int_b));

    printf("浮動小数点演算:\n");
    printf("  %.2f + %.2f = %.2f\n", double_a, double_b, add_double_operation(double_a, double_b));
    printf("  %.2f - %.2f = %.2f\n", double_a, double_b, sub_double_operation(double_a, double_b));
    printf("  %.2f * %.2f = %.2f\n", double_a, double_b, mul_double_operation(double_a, double_b));
}

void test_generic_macros(void)
{
    printf("\n=== 汎用マクロテスト ===\n");

    VERBOSE("汎用マクロのテストを開始します");

    int x = 10, y = 20;
    double dx = 1.5, dy = 2.5;

    printf("スワップ前: x=%d, y=%d\n", x, y);
    SWAP_INT(x, y);
    printf("スワップ後: x=%d, y=%d\n", x, y);

    printf("スワップ前: dx=%.1f, dy=%.1f\n", dx, dy);
    SWAP_DOUBLE(dx, dy);
    printf("スワップ後: dx=%.1f, dy=%.1f\n", dx, dy);
}

void test_benchmarks(void)
{
    printf("\n=== ベンチマークテスト ===\n");

    VERBOSE("ベンチマークテストを開始します");

    /* 計算集約的な処理のベンチマーク */
    {
        BENCHMARK_START();
        
        volatile long long sum = 0;  /* オーバーフロー防止のため long long を使用 */
        int i;
        for (i = 0; i < 1000000; i++)
        {
            sum += (long long)i * i;  /* キャストしてオーバーフローを防ぐ */
        }

        BENCHMARK_END("100万回の平方計算");
    }

    /* 文字列処理のベンチマーク */
    {
        BENCHMARK_START();

        char buffer[1000];
        int i;
        for (i = 0; i < 10000; i++)
        {
            sprintf(buffer, "Test string %d", i);
        }

        BENCHMARK_END("1万回の文字列生成");
    }
}

void test_assertions(void)
{
    printf("\n=== アサーションテスト ===\n");

    VERBOSE("アサーションテストを開始します");

    int value = 42;

    ASSERT(value > 0, "値は正の数であるべきです");
    ASSERT(value == 42, "値は42であるべきです");
    ASSERT(value < 100, "値は100未満であるべきです");

    /* 失敗するアサーション */
    ASSERT(value > 100, "値は100より大きいべきです（これは失敗します）");
}

int main(void)
{
    printf("=== 高度なプリプロセッサの活用デモ ===\n\n");

    /* コンパイル情報の表示 */
    COMPILE_INFO();
    printf("\n");

    /* 各種テストの実行 */
    test_basic_macros();
    test_string_macros();
    test_safe_operations();
    test_bit_operations();
    test_dynamic_functions();
    test_generic_macros();
    test_benchmarks();
    test_assertions();

    /* 条件付きコンパイル情報 */
    printf("\n=== 条件付きコンパイル情報 ===\n");
    printf("プラットフォーム: %s\n", PLATFORM);
    printf("パス区切り文字: %s\n", PATH_SEPARATOR);

#if DEBUG_MODE
    printf("デバッグモード: 有効\n");
#else
    printf("デバッグモード: 無効\n");
#endif

#if VERBOSE_OUTPUT
    printf("詳細出力: 有効\n");
#else
    printf("詳細出力: 無効\n");
#endif

    printf("\n=== デモ完了 ===\n");

    return 0;
}
