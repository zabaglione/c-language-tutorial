/*
 * 演習11-5: エラーハンドリング付き関数 - 解答例（C99版）
 * 
 * エラー処理を含む堅牢な関数群を実装します。
 * C99の機能：//コメント、enum、inline関数、可変長配列、restrict、stdbool.h
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>

// エラーコード列挙型（C99: より型安全）
typedef enum {
    ERROR_SUCCESS = 0,
    ERROR_NULL_POINTER = -1,
    ERROR_INVALID_ARGUMENT = -2,
    ERROR_OVERFLOW = -3,
    ERROR_UNDERFLOW = -4,
    ERROR_MEMORY_ALLOCATION = -5,
    ERROR_FILE_NOT_FOUND = -6,
    ERROR_PERMISSION_DENIED = -7,
    ERROR_DIVIDE_BY_ZERO = -8,
    ERROR_OUT_OF_RANGE = -9
} ErrorCode;

// エラー情報構造体
typedef struct {
    ErrorCode code;
    char message[256];
    const char *file;  // C99: __FILE__マクロ用
    int line;          // C99: __LINE__マクロ用
} ErrorInfo;

// グローバルエラー状態（スレッドローカルにできる）
static ErrorInfo g_last_error = {ERROR_SUCCESS, "", NULL, 0};

// エラー設定マクロ（C99: 可変長引数マクロ）
#define SET_ERROR(code, ...) set_error_with_location(code, __FILE__, __LINE__, __VA_ARGS__)

// エラー処理のヘルパー関数
void set_error_with_location(ErrorCode code, const char *file, int line, const char *format, ...);
inline ErrorCode get_last_error_code(void);  // C99: inline関数
inline const ErrorInfo* get_last_error_info(void);
inline void clear_error(void);
const char* error_code_to_string(ErrorCode code);

// 数値計算関数（エラーチェック付き）
ErrorCode safe_add(int a, int b, int *result);
ErrorCode safe_multiply(int a, int b, int *result);
ErrorCode safe_divide(int dividend, int divisor, int *result, int *remainder);
ErrorCode safe_power(int base, unsigned int exponent, int64_t *result);  // C99: stdint.h

// 配列操作関数（エラーチェック付き）
ErrorCode safe_array_access(const int arr[], size_t size, size_t index, int *value);
ErrorCode safe_array_sum(const int arr[], size_t size, int64_t *sum);
ErrorCode safe_array_average(const int arr[], size_t size, double *average);
ErrorCode safe_array_minmax(const int arr[], size_t size, int *min, int *max);

// 文字列操作関数（エラーチェック付き）
ErrorCode safe_string_copy(char *restrict dest, size_t dest_size, const char *restrict src);  // C99: restrict
ErrorCode safe_string_concat(char *restrict dest, size_t dest_size, const char *restrict src);
ErrorCode safe_string_to_int(const char *str, int *value);
ErrorCode safe_string_format(char *buffer, size_t size, const char *format, ...);

// ファイル操作関数（エラーチェック付き）
ErrorCode safe_file_read_line(FILE *file, char *buffer, size_t buffer_size);
ErrorCode safe_file_write_int(FILE *file, int value);

// 高度なエラー処理
typedef void (*ErrorHandler)(const ErrorInfo *error);  // エラーハンドラ型
void register_error_handler(ErrorHandler handler);
void trigger_error_handler(void);

// エラーを設定する関数（可変長引数版）
void set_error_with_location(ErrorCode code, const char *file, int line, const char *format, ...)
{
    g_last_error.code = code;
    g_last_error.file = file;
    g_last_error.line = line;
    
    if (format != NULL)
    {
        va_list args;
        va_start(args, format);
        vsnprintf(g_last_error.message, sizeof(g_last_error.message), format, args);
        va_end(args);
    }
    else
    {
        g_last_error.message[0] = '\0';
    }
}

// 最後のエラーコードを取得する関数
inline ErrorCode get_last_error_code(void)
{
    return g_last_error.code;
}

// 最後のエラー情報を取得する関数
inline const ErrorInfo* get_last_error_info(void)
{
    return &g_last_error;
}

// エラー状態をクリアする関数
inline void clear_error(void)
{
    g_last_error.code = ERROR_SUCCESS;
    g_last_error.message[0] = '\0';
    g_last_error.file = NULL;
    g_last_error.line = 0;
}

// エラーコードを文字列に変換する関数
const char* error_code_to_string(ErrorCode code)
{
    switch (code)
    {
        case ERROR_SUCCESS:          return "成功";
        case ERROR_NULL_POINTER:     return "NULLポインターエラー";
        case ERROR_INVALID_ARGUMENT: return "無効な引数";
        case ERROR_OVERFLOW:         return "オーバーフロー";
        case ERROR_UNDERFLOW:        return "アンダーフロー";
        case ERROR_MEMORY_ALLOCATION:return "メモリ割り当てエラー";
        case ERROR_FILE_NOT_FOUND:   return "ファイルが見つかりません";
        case ERROR_PERMISSION_DENIED:return "アクセス権限がありません";
        case ERROR_DIVIDE_BY_ZERO:   return "ゼロ除算";
        case ERROR_OUT_OF_RANGE:     return "範囲外";
        default:                     return "不明なエラー";
    }
}

// カスタムエラーハンドラ
static ErrorHandler g_error_handler = NULL;

void register_error_handler(ErrorHandler handler)
{
    g_error_handler = handler;
}

void trigger_error_handler(void)
{
    if (g_error_handler != NULL && g_last_error.code != ERROR_SUCCESS)
    {
        g_error_handler(&g_last_error);
    }
}

// 安全な加算関数
ErrorCode safe_add(int a, int b, int *result)
{
    if (result == NULL)
    {
        SET_ERROR(ERROR_NULL_POINTER, "結果ポインターがNULL");
        return ERROR_NULL_POINTER;
    }
    
    // オーバーフローチェック（C99: 一時変数を使用箇所で宣言）
    if ((b > 0 && a > INT_MAX - b) || (b < 0 && a < INT_MIN - b))
    {
        SET_ERROR(ERROR_OVERFLOW, "加算でオーバーフロー: %d + %d", a, b);
        return ERROR_OVERFLOW;
    }
    
    *result = a + b;
    return ERROR_SUCCESS;
}

// 安全な乗算関数
ErrorCode safe_multiply(int a, int b, int *result)
{
    if (result == NULL)
    {
        SET_ERROR(ERROR_NULL_POINTER, "結果ポインターがNULL");
        return ERROR_NULL_POINTER;
    }
    
    // オーバーフローチェック
    if (a > 0 && b > 0 && a > INT_MAX / b)
    {
        SET_ERROR(ERROR_OVERFLOW, "乗算でオーバーフロー: %d x %d", a, b);
        return ERROR_OVERFLOW;
    }
    if (a < 0 && b < 0 && a < INT_MAX / b)
    {
        SET_ERROR(ERROR_OVERFLOW, "乗算でオーバーフロー: %d x %d", a, b);
        return ERROR_OVERFLOW;
    }
    if (a > 0 && b < 0 && b < INT_MIN / a)
    {
        SET_ERROR(ERROR_OVERFLOW, "乗算でオーバーフロー: %d x %d", a, b);
        return ERROR_OVERFLOW;
    }
    if (a < 0 && b > 0 && a < INT_MIN / b)
    {
        SET_ERROR(ERROR_OVERFLOW, "乗算でオーバーフロー: %d x %d", a, b);
        return ERROR_OVERFLOW;
    }
    
    *result = a * b;
    return ERROR_SUCCESS;
}

// 安全な除算関数
ErrorCode safe_divide(int dividend, int divisor, int *result, int *remainder)
{
    if (result == NULL || remainder == NULL)
    {
        SET_ERROR(ERROR_NULL_POINTER, "結果ポインターがNULL");
        return ERROR_NULL_POINTER;
    }
    
    if (divisor == 0)
    {
        SET_ERROR(ERROR_DIVIDE_BY_ZERO, "%d ÷ 0", dividend);
        return ERROR_DIVIDE_BY_ZERO;
    }
    
    // INT_MIN / -1 のオーバーフローチェック
    if (dividend == INT_MIN && divisor == -1)
    {
        SET_ERROR(ERROR_OVERFLOW, "除算でオーバーフロー: INT_MIN ÷ -1");
        return ERROR_OVERFLOW;
    }
    
    *result = dividend / divisor;
    *remainder = dividend % divisor;
    return ERROR_SUCCESS;
}

// 安全な累乗関数（C99: stdint.h使用）
ErrorCode safe_power(int base, unsigned int exponent, int64_t *result)
{
    if (result == NULL)
    {
        SET_ERROR(ERROR_NULL_POINTER, "結果ポインターがNULL");
        return ERROR_NULL_POINTER;
    }
    
    int64_t power = 1;
    int64_t temp_base = base;
    
    while (exponent > 0)
    {
        if (exponent & 1)
        {
            // オーバーフローチェック
            if (temp_base > 0 && power > INT64_MAX / temp_base)
            {
                SET_ERROR(ERROR_OVERFLOW, "累乗でオーバーフロー: %d^%u", base, exponent);
                return ERROR_OVERFLOW;
            }
            if (temp_base < 0 && power < INT64_MIN / temp_base)
            {
                SET_ERROR(ERROR_OVERFLOW, "累乗でオーバーフロー: %d^%u", base, exponent);
                return ERROR_OVERFLOW;
            }
            power *= temp_base;
        }
        
        exponent >>= 1;
        if (exponent > 0)
        {
            if (temp_base > 0 && temp_base > INT64_MAX / temp_base)
            {
                SET_ERROR(ERROR_OVERFLOW, "累乗でオーバーフロー");
                return ERROR_OVERFLOW;
            }
            temp_base *= temp_base;
        }
    }
    
    *result = power;
    return ERROR_SUCCESS;
}

// 安全な配列アクセス関数
ErrorCode safe_array_access(const int arr[], size_t size, size_t index, int *value)
{
    if (arr == NULL || value == NULL)
    {
        SET_ERROR(ERROR_NULL_POINTER, "配列または値ポインターがNULL");
        return ERROR_NULL_POINTER;
    }
    
    if (size == 0)
    {
        SET_ERROR(ERROR_INVALID_ARGUMENT, "配列サイズがゼロ");
        return ERROR_INVALID_ARGUMENT;
    }
    
    if (index >= size)
    {
        SET_ERROR(ERROR_OUT_OF_RANGE, "インデックス %zu が範囲外 (サイズ: %zu)", index, size);
        return ERROR_OUT_OF_RANGE;
    }
    
    *value = arr[index];
    return ERROR_SUCCESS;
}

// 安全な配列合計関数
ErrorCode safe_array_sum(const int arr[], size_t size, int64_t *sum)
{
    if (arr == NULL || sum == NULL)
    {
        SET_ERROR(ERROR_NULL_POINTER, "配列または合計ポインターがNULL");
        return ERROR_NULL_POINTER;
    }
    
    if (size == 0)
    {
        SET_ERROR(ERROR_INVALID_ARGUMENT, "配列サイズがゼロ");
        return ERROR_INVALID_ARGUMENT;
    }
    
    *sum = 0;
    
    for (size_t i = 0; i < size; i++)  // C99: forループ内で変数宣言
    {
        // オーバーフローチェック
        if ((arr[i] > 0 && *sum > INT64_MAX - arr[i]) ||
            (arr[i] < 0 && *sum < INT64_MIN - arr[i]))
        {
            SET_ERROR(ERROR_OVERFLOW, "配列合計でオーバーフロー (インデックス: %zu)", i);
            return ERROR_OVERFLOW;
        }
        *sum += arr[i];
    }
    
    return ERROR_SUCCESS;
}

// 安全な配列平均関数
ErrorCode safe_array_average(const int arr[], size_t size, double *average)
{
    if (arr == NULL || average == NULL)
    {
        SET_ERROR(ERROR_NULL_POINTER, "配列または平均ポインターがNULL");
        return ERROR_NULL_POINTER;
    }
    
    if (size == 0)
    {
        SET_ERROR(ERROR_INVALID_ARGUMENT, "配列サイズがゼロ");
        return ERROR_INVALID_ARGUMENT;
    }
    
    int64_t sum;
    ErrorCode result = safe_array_sum(arr, size, &sum);
    if (result != ERROR_SUCCESS)
    {
        return result;
    }
    
    *average = (double)sum / size;
    return ERROR_SUCCESS;
}

// 安全な配列最小値最大値関数
ErrorCode safe_array_minmax(const int arr[], size_t size, int *min, int *max)
{
    if (arr == NULL || min == NULL || max == NULL)
    {
        SET_ERROR(ERROR_NULL_POINTER, "配列または結果ポインターがNULL");
        return ERROR_NULL_POINTER;
    }
    
    if (size == 0)
    {
        SET_ERROR(ERROR_INVALID_ARGUMENT, "配列サイズがゼロ");
        return ERROR_INVALID_ARGUMENT;
    }
    
    *min = *max = arr[0];
    
    for (size_t i = 1; i < size; i++)
    {
        if (arr[i] < *min) *min = arr[i];
        if (arr[i] > *max) *max = arr[i];
    }
    
    return ERROR_SUCCESS;
}

// 安全な文字列コピー関数（C99: restrict）
ErrorCode safe_string_copy(char *restrict dest, size_t dest_size, const char *restrict src)
{
    if (dest == NULL || src == NULL)
    {
        SET_ERROR(ERROR_NULL_POINTER, "送信先または送信元がNULL");
        return ERROR_NULL_POINTER;
    }
    
    if (dest_size == 0)
    {
        SET_ERROR(ERROR_INVALID_ARGUMENT, "バッファサイズがゼロ");
        return ERROR_INVALID_ARGUMENT;
    }
    
    size_t src_len = strlen(src);
    if (src_len >= dest_size)
    {
        SET_ERROR(ERROR_OUT_OF_RANGE, "バッファサイズ不足: 必要 %zu, 利用可能 %zu", 
                  src_len + 1, dest_size);
        return ERROR_OUT_OF_RANGE;
    }
    
    strcpy(dest, src);
    return ERROR_SUCCESS;
}

// 安全な文字列連結関数（C99: restrict）
ErrorCode safe_string_concat(char *restrict dest, size_t dest_size, const char *restrict src)
{
    if (dest == NULL || src == NULL)
    {
        SET_ERROR(ERROR_NULL_POINTER, "送信先または送信元がNULL");
        return ERROR_NULL_POINTER;
    }
    
    if (dest_size == 0)
    {
        SET_ERROR(ERROR_INVALID_ARGUMENT, "バッファサイズがゼロ");
        return ERROR_INVALID_ARGUMENT;
    }
    
    size_t dest_len = strlen(dest);
    size_t src_len = strlen(src);
    
    if (dest_len + src_len >= dest_size)
    {
        SET_ERROR(ERROR_OUT_OF_RANGE, "バッファサイズ不足: 必要 %zu, 利用可能 %zu",
                  dest_len + src_len + 1, dest_size);
        return ERROR_OUT_OF_RANGE;
    }
    
    strcat(dest, src);
    return ERROR_SUCCESS;
}

// 安全な文字列から整数への変換関数
ErrorCode safe_string_to_int(const char *str, int *value)
{
    if (str == NULL || value == NULL)
    {
        SET_ERROR(ERROR_NULL_POINTER, "文字列または値ポインターがNULL");
        return ERROR_NULL_POINTER;
    }
    
    char *endptr;
    errno = 0;
    long result = strtol(str, &endptr, 10);
    
    // 変換エラーチェック
    if (errno == ERANGE || result > INT_MAX || result < INT_MIN)
    {
        SET_ERROR(ERROR_OVERFLOW, "整数変換でオーバーフロー: \"%s\"", str);
        return ERROR_OVERFLOW;
    }
    
    if (endptr == str || *endptr != '\0')
    {
        SET_ERROR(ERROR_INVALID_ARGUMENT, "無効な数値形式: \"%s\"", str);
        return ERROR_INVALID_ARGUMENT;
    }
    
    *value = (int)result;
    return ERROR_SUCCESS;
}

// 安全な文字列フォーマット関数（C99: 可変長引数）
ErrorCode safe_string_format(char *buffer, size_t size, const char *format, ...)
{
    if (buffer == NULL || format == NULL)
    {
        SET_ERROR(ERROR_NULL_POINTER, "バッファまたはフォーマットがNULL");
        return ERROR_NULL_POINTER;
    }
    
    if (size == 0)
    {
        SET_ERROR(ERROR_INVALID_ARGUMENT, "バッファサイズがゼロ");
        return ERROR_INVALID_ARGUMENT;
    }
    
    va_list args;
    va_start(args, format);
    int result = vsnprintf(buffer, size, format, args);
    va_end(args);
    
    if (result < 0)
    {
        SET_ERROR(ERROR_INVALID_ARGUMENT, "フォーマットエラー");
        return ERROR_INVALID_ARGUMENT;
    }
    
    if ((size_t)result >= size)
    {
        SET_ERROR(ERROR_OUT_OF_RANGE, "バッファサイズ不足");
        return ERROR_OUT_OF_RANGE;
    }
    
    return ERROR_SUCCESS;
}

// 安全なファイル読み込み関数
ErrorCode safe_file_read_line(FILE *file, char *buffer, size_t buffer_size)
{
    if (file == NULL || buffer == NULL)
    {
        SET_ERROR(ERROR_NULL_POINTER, "ファイルまたはバッファがNULL");
        return ERROR_NULL_POINTER;
    }
    
    if (buffer_size == 0)
    {
        SET_ERROR(ERROR_INVALID_ARGUMENT, "バッファサイズがゼロ");
        return ERROR_INVALID_ARGUMENT;
    }
    
    if (fgets(buffer, buffer_size, file) == NULL)
    {
        if (feof(file))
        {
            SET_ERROR(ERROR_UNDERFLOW, "ファイルの終端に達しました");
            return ERROR_UNDERFLOW;
        }
        else
        {
            SET_ERROR(ERROR_FILE_NOT_FOUND, "ファイル読み込みエラー");
            return ERROR_FILE_NOT_FOUND;
        }
    }
    
    return ERROR_SUCCESS;
}

// 安全なファイル書き込み関数
ErrorCode safe_file_write_int(FILE *file, int value)
{
    if (file == NULL)
    {
        SET_ERROR(ERROR_NULL_POINTER, "ファイルポインターがNULL");
        return ERROR_NULL_POINTER;
    }
    
    if (fprintf(file, "%d\n", value) < 0)
    {
        SET_ERROR(ERROR_PERMISSION_DENIED, "ファイル書き込みエラー");
        return ERROR_PERMISSION_DENIED;
    }
    
    return ERROR_SUCCESS;
}

// カスタムエラーハンドラの例
void custom_error_handler(const ErrorInfo *error)
{
    fprintf(stderr, "[エラー] %s (%s:%d): %s\n",
            error_code_to_string(error->code),
            error->file ? error->file : "不明",
            error->line,
            error->message);
}

// メイン関数 - テスト用
int main(void)
{
    printf("=== エラーハンドリング付き関数のテスト（C99版） ===\n\n");
    
    // カスタムエラーハンドラを登録
    register_error_handler(custom_error_handler);
    
    // 数値計算のテスト
    printf("=== 数値計算 ===\n");
    
    // 正常な加算
    int int_result;
    ErrorCode result = safe_add(100, 200, &int_result);
    printf("100 + 200 = ");
    if (result == ERROR_SUCCESS)
    {
        printf("%d (成功)\n", int_result);
    }
    else
    {
        printf("エラー\n");
        trigger_error_handler();
    }
    
    // オーバーフローする加算
    result = safe_add(INT_MAX, 1, &int_result);
    printf("INT_MAX + 1 = ");
    if (result == ERROR_SUCCESS)
    {
        printf("%d (成功)\n", int_result);
    }
    else
    {
        printf("エラー\n");
        trigger_error_handler();
    }
    
    // 除算のテスト
    int remainder;
    result = safe_divide(17, 5, &int_result, &remainder);
    printf("17 ÷ 5 = ");
    if (result == ERROR_SUCCESS)
    {
        printf("%d 余り %d (成功)\n", int_result, remainder);
    }
    else
    {
        printf("エラー\n");
        trigger_error_handler();
    }
    
    // ゼロ除算
    result = safe_divide(10, 0, &int_result, &remainder);
    printf("10 ÷ 0 = ");
    if (result == ERROR_SUCCESS)
    {
        printf("%d (成功)\n", int_result);
    }
    else
    {
        printf("エラー\n");
        trigger_error_handler();
    }
    
    // 累乗のテスト
    int64_t long_result;
    result = safe_power(2, 10, &long_result);
    printf("2^10 = ");
    if (result == ERROR_SUCCESS)
    {
        printf("%lld (成功)\n", (long long)long_result);
    }
    else
    {
        printf("エラー\n");
        trigger_error_handler();
    }
    printf("\n");
    
    // 配列操作のテスト
    printf("=== 配列操作 ===\n");
    const int test_array[] = {10, 20, 30, 40, 50};  // C99: const配列
    const size_t array_size = sizeof(test_array) / sizeof(test_array[0]);
    
    // 正常な配列アクセス
    result = safe_array_access(test_array, array_size, 2, &int_result);
    printf("配列[2] = ");
    if (result == ERROR_SUCCESS)
    {
        printf("%d (成功)\n", int_result);
    }
    else
    {
        printf("エラー\n");
        trigger_error_handler();
    }
    
    // 範囲外アクセス
    result = safe_array_access(test_array, array_size, 10, &int_result);
    printf("配列[10] = ");
    if (result == ERROR_SUCCESS)
    {
        printf("%d (成功)\n", int_result);
    }
    else
    {
        printf("エラー\n");
        trigger_error_handler();
    }
    
    // 配列平均
    double double_result;
    result = safe_array_average(test_array, array_size, &double_result);
    printf("配列の平均 = ");
    if (result == ERROR_SUCCESS)
    {
        printf("%.2f (成功)\n", double_result);
    }
    else
    {
        printf("エラー\n");
        trigger_error_handler();
    }
    
    // 最小値・最大値
    int min, max;
    result = safe_array_minmax(test_array, array_size, &min, &max);
    printf("最小値・最大値 = ");
    if (result == ERROR_SUCCESS)
    {
        printf("%d, %d (成功)\n", min, max);
    }
    else
    {
        printf("エラー\n");
        trigger_error_handler();
    }
    printf("\n");
    
    // 文字列操作のテスト
    printf("=== 文字列操作 ===\n");
    
    // 正常な文字列コピー
    char buffer[100];
    result = safe_string_copy(buffer, sizeof(buffer), "Hello, World!");
    printf("文字列コピー: ");
    if (result == ERROR_SUCCESS)
    {
        printf("\"%s\" (成功)\n", buffer);
    }
    else
    {
        printf("エラー\n");
        trigger_error_handler();
    }
    
    // バッファオーバーフロー防止
    char small_buffer[5];
    result = safe_string_copy(small_buffer, sizeof(small_buffer), "This is too long");
    printf("小さいバッファへのコピー: ");
    if (result == ERROR_SUCCESS)
    {
        printf("\"%s\" (成功)\n", small_buffer);
    }
    else
    {
        printf("エラー\n");
        trigger_error_handler();
    }
    
    // 文字列フォーマット（C99機能）
    result = safe_string_format(buffer, sizeof(buffer), "値: %d, 文字列: %s", 42, "test");
    printf("フォーマット結果: ");
    if (result == ERROR_SUCCESS)
    {
        printf("\"%s\" (成功)\n", buffer);
    }
    else
    {
        printf("エラー\n");
        trigger_error_handler();
    }
    
    // 文字列から整数への変換
    result = safe_string_to_int("12345", &int_result);
    printf("\"12345\" を整数に変換: ");
    if (result == ERROR_SUCCESS)
    {
        printf("%d (成功)\n", int_result);
    }
    else
    {
        printf("エラー\n");
        trigger_error_handler();
    }
    
    // 無効な文字列
    result = safe_string_to_int("abc123", &int_result);
    printf("\"abc123\" を整数に変換: ");
    if (result == ERROR_SUCCESS)
    {
        printf("%d (成功)\n", int_result);
    }
    else
    {
        printf("エラー\n");
        trigger_error_handler();
    }
    
    printf("\n");
    
    // C99: 可変長配列を使ったテスト
    printf("=== 可変長配列のテスト ===\n");
    int n = 5;
    int vla[n];  // C99: 可変長配列
    
    // 配列を初期化
    for (int i = 0; i < n; i++)
    {
        vla[i] = (i + 1) * 10;
    }
    
    // 可変長配列の合計
    int64_t sum;
    result = safe_array_sum(vla, n, &sum);
    printf("可変長配列の合計 = ");
    if (result == ERROR_SUCCESS)
    {
        printf("%lld (成功)\n", (long long)sum);
    }
    else
    {
        printf("エラー\n");
        trigger_error_handler();
    }
    
    // エラー処理のサマリー
    printf("\n=== エラー処理のサマリー ===\n");
    printf("C99版の改善点：\n");
    printf("- enum型によるエラーコードの型安全性\n");
    printf("- 可変長引数マクロによる詳細なエラー情報\n");
    printf("- inline関数による効率的なエラーチェック\n");
    printf("- restrict修飾子による最適化\n");
    printf("- stdint.h型による移植性の向上\n");
    printf("- カスタムエラーハンドラによる柔軟なエラー処理\n");
    
    return 0;
}