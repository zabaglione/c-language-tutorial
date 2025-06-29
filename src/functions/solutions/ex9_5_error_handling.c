/*
 * 演習9-5: エラーハンドリング付き関数 - 解答例
 * 
 * エラー処理を含む堅牢な関数群を実装します。
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

/* エラーコード定義 */
#define SUCCESS 0
#define ERROR_NULL_POINTER -1
#define ERROR_INVALID_ARGUMENT -2
#define ERROR_OVERFLOW -3
#define ERROR_UNDERFLOW -4
#define ERROR_MEMORY_ALLOCATION -5
#define ERROR_FILE_NOT_FOUND -6
#define ERROR_PERMISSION_DENIED -7
#define ERROR_DIVIDE_BY_ZERO -8
#define ERROR_OUT_OF_RANGE -9

/* グローバルエラー状態（オプション） */
static int g_last_error = SUCCESS;
static char g_error_message[256] = "";

/* エラー処理のヘルパー関数 */
void set_error(int error_code, const char *message);
int get_last_error(void);
const char* get_error_message(void);
void clear_error(void);
const char* error_to_string(int error_code);

/* 数値計算関数（エラーチェック付き） */
int safe_add(int a, int b, int *result);
int safe_multiply(int a, int b, int *result);
int safe_divide(int dividend, int divisor, int *result, int *remainder);
int safe_power(int base, int exponent, long *result);

/* 配列操作関数（エラーチェック付き） */
int safe_array_access(int arr[], int size, int index, int *value);
int safe_array_sum(int arr[], int size, long *sum);
int safe_array_average(int arr[], int size, double *average);

/* 文字列操作関数（エラーチェック付き） */
int safe_string_copy(char *dest, size_t dest_size, const char *src);
int safe_string_concat(char *dest, size_t dest_size, const char *src);
int safe_string_to_int(const char *str, int *value);

/* ファイル操作関数（エラーチェック付き） */
int safe_file_read_line(FILE *file, char *buffer, size_t buffer_size);
int safe_file_write_int(FILE *file, int value);

/* エラーを設定する関数 */
void set_error(int error_code, const char *message)
{
    g_last_error = error_code;
    if (message != NULL)
    {
        strncpy(g_error_message, message, sizeof(g_error_message) - 1);
        g_error_message[sizeof(g_error_message) - 1] = '\0';
    }
    else
    {
        g_error_message[0] = '\0';
    }
}

/* 最後のエラーコードを取得する関数 */
int get_last_error(void)
{
    return g_last_error;
}

/* エラーメッセージを取得する関数 */
const char* get_error_message(void)
{
    return g_error_message;
}

/* エラー状態をクリアする関数 */
void clear_error(void)
{
    g_last_error = SUCCESS;
    g_error_message[0] = '\0';
}

/* エラーコードを文字列に変換する関数 */
const char* error_to_string(int error_code)
{
    switch (error_code)
    {
        case SUCCESS:
            return "成功";
        case ERROR_NULL_POINTER:
            return "NULLポインターエラー";
        case ERROR_INVALID_ARGUMENT:
            return "無効な引数";
        case ERROR_OVERFLOW:
            return "オーバーフロー";
        case ERROR_UNDERFLOW:
            return "アンダーフロー";
        case ERROR_MEMORY_ALLOCATION:
            return "メモリ割り当てエラー";
        case ERROR_FILE_NOT_FOUND:
            return "ファイルが見つかりません";
        case ERROR_PERMISSION_DENIED:
            return "アクセス権限がありません";
        case ERROR_DIVIDE_BY_ZERO:
            return "ゼロ除算";
        case ERROR_OUT_OF_RANGE:
            return "範囲外";
        default:
            return "不明なエラー";
    }
}

/* 安全な加算関数 */
int safe_add(int a, int b, int *result)
{
    if (result == NULL)
    {
        set_error(ERROR_NULL_POINTER, "結果ポインターがNULL");
        return ERROR_NULL_POINTER;
    }
    
    /* オーバーフローチェック */
    if ((b > 0 && a > INT_MAX - b) || (b < 0 && a < INT_MIN - b))
    {
        set_error(ERROR_OVERFLOW, "加算でオーバーフロー");
        return ERROR_OVERFLOW;
    }
    
    *result = a + b;
    return SUCCESS;
}

/* 安全な乗算関数 */
int safe_multiply(int a, int b, int *result)
{
    if (result == NULL)
    {
        set_error(ERROR_NULL_POINTER, "結果ポインターがNULL");
        return ERROR_NULL_POINTER;
    }
    
    /* オーバーフローチェック */
    if (a > 0 && b > 0 && a > INT_MAX / b)
    {
        set_error(ERROR_OVERFLOW, "乗算でオーバーフロー");
        return ERROR_OVERFLOW;
    }
    if (a < 0 && b < 0 && a < INT_MAX / b)
    {
        set_error(ERROR_OVERFLOW, "乗算でオーバーフロー");
        return ERROR_OVERFLOW;
    }
    if (a > 0 && b < 0 && b < INT_MIN / a)
    {
        set_error(ERROR_OVERFLOW, "乗算でオーバーフロー");
        return ERROR_OVERFLOW;
    }
    if (a < 0 && b > 0 && a < INT_MIN / b)
    {
        set_error(ERROR_OVERFLOW, "乗算でオーバーフロー");
        return ERROR_OVERFLOW;
    }
    
    *result = a * b;
    return SUCCESS;
}

/* 安全な除算関数 */
int safe_divide(int dividend, int divisor, int *result, int *remainder)
{
    if (result == NULL || remainder == NULL)
    {
        set_error(ERROR_NULL_POINTER, "結果ポインターがNULL");
        return ERROR_NULL_POINTER;
    }
    
    if (divisor == 0)
    {
        set_error(ERROR_DIVIDE_BY_ZERO, "ゼロで除算");
        return ERROR_DIVIDE_BY_ZERO;
    }
    
    /* INT_MIN / -1 のオーバーフローチェック */
    if (dividend == INT_MIN && divisor == -1)
    {
        set_error(ERROR_OVERFLOW, "除算でオーバーフロー");
        return ERROR_OVERFLOW;
    }
    
    *result = dividend / divisor;
    *remainder = dividend % divisor;
    return SUCCESS;
}

/* 安全な累乗関数 */
int safe_power(int base, int exponent, long *result)
{
    if (result == NULL)
    {
        set_error(ERROR_NULL_POINTER, "結果ポインターがNULL");
        return ERROR_NULL_POINTER;
    }
    
    if (exponent < 0)
    {
        set_error(ERROR_INVALID_ARGUMENT, "負の指数はサポートされていません");
        return ERROR_INVALID_ARGUMENT;
    }
    
    long power = 1;
    long temp_base = base;
    
    while (exponent > 0)
    {
        if (exponent & 1)
        {
            /* オーバーフローチェック */
            if (temp_base > 0 && power > LONG_MAX / temp_base)
            {
                set_error(ERROR_OVERFLOW, "累乗でオーバーフロー");
                return ERROR_OVERFLOW;
            }
            if (temp_base < 0 && power < LONG_MIN / temp_base)
            {
                set_error(ERROR_OVERFLOW, "累乗でオーバーフロー");
                return ERROR_OVERFLOW;
            }
            power *= temp_base;
        }
        
        exponent >>= 1;
        if (exponent > 0)
        {
            /* temp_base * temp_base のオーバーフローチェック */
            if (temp_base > 0 && temp_base > LONG_MAX / temp_base)
            {
                set_error(ERROR_OVERFLOW, "累乗でオーバーフロー");
                return ERROR_OVERFLOW;
            }
            temp_base *= temp_base;
        }
    }
    
    *result = power;
    return SUCCESS;
}

/* 安全な配列アクセス関数 */
int safe_array_access(int arr[], int size, int index, int *value)
{
    if (arr == NULL || value == NULL)
    {
        set_error(ERROR_NULL_POINTER, "配列または値ポインターがNULL");
        return ERROR_NULL_POINTER;
    }
    
    if (size <= 0)
    {
        set_error(ERROR_INVALID_ARGUMENT, "配列サイズが無効");
        return ERROR_INVALID_ARGUMENT;
    }
    
    if (index < 0 || index >= size)
    {
        set_error(ERROR_OUT_OF_RANGE, "インデックスが範囲外");
        return ERROR_OUT_OF_RANGE;
    }
    
    *value = arr[index];
    return SUCCESS;
}

/* 安全な配列合計関数 */
int safe_array_sum(int arr[], int size, long *sum)
{
    if (arr == NULL || sum == NULL)
    {
        set_error(ERROR_NULL_POINTER, "配列または合計ポインターがNULL");
        return ERROR_NULL_POINTER;
    }
    
    if (size <= 0)
    {
        set_error(ERROR_INVALID_ARGUMENT, "配列サイズが無効");
        return ERROR_INVALID_ARGUMENT;
    }
    
    *sum = 0;
    int i;
    
    for (i = 0; i < size; i++)
    {
        /* オーバーフローチェック */
        if ((arr[i] > 0 && *sum > LONG_MAX - arr[i]) ||
            (arr[i] < 0 && *sum < LONG_MIN - arr[i]))
        {
            set_error(ERROR_OVERFLOW, "配列合計でオーバーフロー");
            return ERROR_OVERFLOW;
        }
        *sum += arr[i];
    }
    
    return SUCCESS;
}

/* 安全な配列平均関数 */
int safe_array_average(int arr[], int size, double *average)
{
    if (arr == NULL || average == NULL)
    {
        set_error(ERROR_NULL_POINTER, "配列または平均ポインターがNULL");
        return ERROR_NULL_POINTER;
    }
    
    if (size <= 0)
    {
        set_error(ERROR_INVALID_ARGUMENT, "配列サイズが無効");
        return ERROR_INVALID_ARGUMENT;
    }
    
    long sum;
    int result = safe_array_sum(arr, size, &sum);
    if (result != SUCCESS)
    {
        return result;
    }
    
    *average = (double)sum / size;
    return SUCCESS;
}

/* 安全な文字列コピー関数 */
int safe_string_copy(char *dest, size_t dest_size, const char *src)
{
    if (dest == NULL || src == NULL)
    {
        set_error(ERROR_NULL_POINTER, "送信先または送信元がNULL");
        return ERROR_NULL_POINTER;
    }
    
    if (dest_size == 0)
    {
        set_error(ERROR_INVALID_ARGUMENT, "バッファサイズがゼロ");
        return ERROR_INVALID_ARGUMENT;
    }
    
    size_t src_len = strlen(src);
    if (src_len >= dest_size)
    {
        set_error(ERROR_OUT_OF_RANGE, "バッファサイズ不足");
        return ERROR_OUT_OF_RANGE;
    }
    
    strcpy(dest, src);
    return SUCCESS;
}

/* 安全な文字列連結関数 */
int safe_string_concat(char *dest, size_t dest_size, const char *src)
{
    if (dest == NULL || src == NULL)
    {
        set_error(ERROR_NULL_POINTER, "送信先または送信元がNULL");
        return ERROR_NULL_POINTER;
    }
    
    if (dest_size == 0)
    {
        set_error(ERROR_INVALID_ARGUMENT, "バッファサイズがゼロ");
        return ERROR_INVALID_ARGUMENT;
    }
    
    size_t dest_len = strlen(dest);
    size_t src_len = strlen(src);
    
    if (dest_len + src_len >= dest_size)
    {
        set_error(ERROR_OUT_OF_RANGE, "バッファサイズ不足");
        return ERROR_OUT_OF_RANGE;
    }
    
    strcat(dest, src);
    return SUCCESS;
}

/* 安全な文字列から整数への変換関数 */
int safe_string_to_int(const char *str, int *value)
{
    if (str == NULL || value == NULL)
    {
        set_error(ERROR_NULL_POINTER, "文字列または値ポインターがNULL");
        return ERROR_NULL_POINTER;
    }
    
    char *endptr;
    errno = 0;
    long result = strtol(str, &endptr, 10);
    
    /* 変換エラーチェック */
    if (errno == ERANGE || result > INT_MAX || result < INT_MIN)
    {
        set_error(ERROR_OVERFLOW, "整数変換でオーバーフロー");
        return ERROR_OVERFLOW;
    }
    
    if (endptr == str || *endptr != '\0')
    {
        set_error(ERROR_INVALID_ARGUMENT, "無効な数値形式");
        return ERROR_INVALID_ARGUMENT;
    }
    
    *value = (int)result;
    return SUCCESS;
}

/* 安全なファイル読み込み関数 */
int safe_file_read_line(FILE *file, char *buffer, size_t buffer_size)
{
    if (file == NULL || buffer == NULL)
    {
        set_error(ERROR_NULL_POINTER, "ファイルまたはバッファがNULL");
        return ERROR_NULL_POINTER;
    }
    
    if (buffer_size == 0)
    {
        set_error(ERROR_INVALID_ARGUMENT, "バッファサイズがゼロ");
        return ERROR_INVALID_ARGUMENT;
    }
    
    if (fgets(buffer, buffer_size, file) == NULL)
    {
        if (feof(file))
        {
            set_error(ERROR_UNDERFLOW, "ファイルの終端に達しました");
            return ERROR_UNDERFLOW;
        }
        else
        {
            set_error(ERROR_FILE_NOT_FOUND, "ファイル読み込みエラー");
            return ERROR_FILE_NOT_FOUND;
        }
    }
    
    return SUCCESS;
}

/* 安全なファイル書き込み関数 */
int safe_file_write_int(FILE *file, int value)
{
    if (file == NULL)
    {
        set_error(ERROR_NULL_POINTER, "ファイルポインターがNULL");
        return ERROR_NULL_POINTER;
    }
    
    if (fprintf(file, "%d\n", value) < 0)
    {
        set_error(ERROR_PERMISSION_DENIED, "ファイル書き込みエラー");
        return ERROR_PERMISSION_DENIED;
    }
    
    return SUCCESS;
}

/* メイン関数 - テスト用 */
int main(void)
{
    int result;
    int int_result;
    long long_result;
    double double_result;
    char buffer[100];
    
    printf("=== エラーハンドリング付き関数のテスト ===\n\n");
    
    /* 数値計算のテスト */
    printf("=== 数値計算 ===\n");
    
    /* 正常な加算 */
    result = safe_add(100, 200, &int_result);
    printf("100 + 200 = ");
    if (result == SUCCESS)
    {
        printf("%d (成功)\n", int_result);
    }
    else
    {
        printf("エラー: %s\n", error_to_string(result));
    }
    
    /* オーバーフローする加算 */
    result = safe_add(INT_MAX, 1, &int_result);
    printf("INT_MAX + 1 = ");
    if (result == SUCCESS)
    {
        printf("%d (成功)\n", int_result);
    }
    else
    {
        printf("エラー: %s (%s)\n", error_to_string(result), get_error_message());
    }
    
    /* 除算のテスト */
    int remainder;
    result = safe_divide(17, 5, &int_result, &remainder);
    printf("17 ÷ 5 = ");
    if (result == SUCCESS)
    {
        printf("%d 余り %d (成功)\n", int_result, remainder);
    }
    else
    {
        printf("エラー: %s\n", error_to_string(result));
    }
    
    /* ゼロ除算 */
    result = safe_divide(10, 0, &int_result, &remainder);
    printf("10 ÷ 0 = ");
    if (result == SUCCESS)
    {
        printf("%d (成功)\n", int_result);
    }
    else
    {
        printf("エラー: %s (%s)\n", error_to_string(result), get_error_message());
    }
    
    /* 累乗のテスト */
    result = safe_power(2, 10, &long_result);
    printf("2^10 = ");
    if (result == SUCCESS)
    {
        printf("%ld (成功)\n", long_result);
    }
    else
    {
        printf("エラー: %s\n", error_to_string(result));
    }
    printf("\n");
    
    /* 配列操作のテスト */
    printf("=== 配列操作 ===\n");
    int test_array[] = {10, 20, 30, 40, 50};
    int array_size = 5;
    
    /* 正常な配列アクセス */
    result = safe_array_access(test_array, array_size, 2, &int_result);
    printf("配列[2] = ");
    if (result == SUCCESS)
    {
        printf("%d (成功)\n", int_result);
    }
    else
    {
        printf("エラー: %s\n", error_to_string(result));
    }
    
    /* 範囲外アクセス */
    result = safe_array_access(test_array, array_size, 10, &int_result);
    printf("配列[10] = ");
    if (result == SUCCESS)
    {
        printf("%d (成功)\n", int_result);
    }
    else
    {
        printf("エラー: %s (%s)\n", error_to_string(result), get_error_message());
    }
    
    /* 配列平均 */
    result = safe_array_average(test_array, array_size, &double_result);
    printf("配列の平均 = ");
    if (result == SUCCESS)
    {
        printf("%.2f (成功)\n", double_result);
    }
    else
    {
        printf("エラー: %s\n", error_to_string(result));
    }
    printf("\n");
    
    /* 文字列操作のテスト */
    printf("=== 文字列操作 ===\n");
    
    /* 正常な文字列コピー */
    result = safe_string_copy(buffer, sizeof(buffer), "Hello, World!");
    printf("文字列コピー: ");
    if (result == SUCCESS)
    {
        printf("\"%s\" (成功)\n", buffer);
    }
    else
    {
        printf("エラー: %s\n", error_to_string(result));
    }
    
    /* バッファオーバーフロー防止 */
    char small_buffer[5];
    result = safe_string_copy(small_buffer, sizeof(small_buffer), "This is too long");
    printf("小さいバッファへのコピー: ");
    if (result == SUCCESS)
    {
        printf("\"%s\" (成功)\n", small_buffer);
    }
    else
    {
        printf("エラー: %s (%s)\n", error_to_string(result), get_error_message());
    }
    
    /* 文字列から整数への変換 */
    result = safe_string_to_int("12345", &int_result);
    printf("\"12345\" を整数に変換: ");
    if (result == SUCCESS)
    {
        printf("%d (成功)\n", int_result);
    }
    else
    {
        printf("エラー: %s\n", error_to_string(result));
    }
    
    /* 無効な文字列 */
    result = safe_string_to_int("abc123", &int_result);
    printf("\"abc123\" を整数に変換: ");
    if (result == SUCCESS)
    {
        printf("%d (成功)\n", int_result);
    }
    else
    {
        printf("エラー: %s (%s)\n", error_to_string(result), get_error_message());
    }
    
    printf("\n");
    
    /* エラー処理のサマリー */
    printf("=== エラー処理のサマリー ===\n");
    printf("エラーハンドリングにより、以下の問題を防ぐことができました：\n");
    printf("- オーバーフロー/アンダーフロー\n");
    printf("- ゼロ除算\n");
    printf("- 範囲外アクセス\n");
    printf("- バッファオーバーフロー\n");
    printf("- 無効な入力\n");
    printf("- NULLポインター参照\n");
    
    return 0;
}