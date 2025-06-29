/* コールバック関数の活用 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 配列処理用のコールバック関数群 */
int square(int x) { return x * x; }
int cube(int x) { return x * x * x; }
int double_value(int x) { return x * 2; }
int increment(int x) { return x + 1; }

/* 条件判定用のコールバック関数群 */
int is_even(int x) { return x % 2 == 0; }
int is_odd(int x) { return x % 2 != 0; }
int is_positive(int x) { return x > 0; }
int is_negative(int x) { return x < 0; }

/* 配列の各要素に関数を適用 */
void apply_to_array(int arr[], int size, int (*func)(int))
{
    int i;
    for (i = 0; i < size; i++)
    {
        arr[i] = func(arr[i]);
    }
}

/* 配列をフィルタリング */
int filter_array(int source[], int dest[], int size, int (*predicate)(int))
{
    int count = 0;
    int i;

    for (i = 0; i < size; i++)
    {
        if (predicate(source[i]))
        {
            dest[count++] = source[i];
        }
    }

    return count;
}

/* 配列を表示する関数 */
void print_array(int arr[], int size, const char *label)
{
    int i;
    printf("%s: ", label);
    for (i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

/* 文字列処理用のコールバック関数群 */
void to_upper_char(char *c)
{
    if (*c >= 'a' && *c <= 'z')
    {
        *c = *c - 'a' + 'A';
    }
}

void to_lower_char(char *c)
{
    if (*c >= 'A' && *c <= 'Z')
    {
        *c = *c - 'A' + 'a';
    }
}

void replace_space_with_underscore(char *c)
{
    if (*c == ' ')
    {
        *c = '_';
    }
}

/* 文字列の各文字にコールバック関数を適用 */
void process_string(char str[], void (*processor)(char *))
{
    int i;
    for (i = 0; str[i] != '\0'; i++)
    {
        processor(&str[i]);
    }
}

/* ソート用の比較関数 */
int compare_ascending(int a, int b)
{
    return a - b;
}

int compare_descending(int a, int b)
{
    return b - a;
}

/* バブルソート（コールバック版） */
void bubble_sort(int arr[], int size, int (*compare)(int, int))
{
    int i, j, temp;

    for (i = 0; i < size - 1; i++)
    {
        for (j = 0; j < size - 1 - i; j++)
        {
            if (compare(arr[j], arr[j + 1]) > 0)
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

/* イベントハンドラシステム */
void on_start_event(const char *message)
{
    printf("[開始イベント] %s\n", message);
}

void on_stop_event(const char *message)
{
    printf("[停止イベント] %s\n", message);
}

void on_error_event(const char *message)
{
    printf("[エラーイベント] %s\n", message);
}

/* イベントを処理する関数 */
void trigger_event(const char *message, void (*event_handler)(const char *))
{
    if (event_handler != NULL)
    {
        event_handler(message);
    }
}

/* 計算処理のログ付き実行 */
int execute_with_logging(int a, int b, int (*operation)(int, int), const char *op_name)
{
    printf("計算開始: %s(%d, %d)\n", op_name, a, b);
    int result = operation(a, b);
    printf("計算完了: %s(%d, %d) = %d\n", op_name, a, b, result);
    return result;
}

/* 簡単な加算関数（ログ用） */
int add_for_logging(int a, int b)
{
    return a + b;
}

int multiply_for_logging(int a, int b)
{
    return a * b;
}

int main(void)
{
    printf("=== コールバック関数の活用 ===\n\n");

    /* 1. 配列処理のコールバック */
    printf("=== 配列処理のコールバック ===\n");
    int numbers[] = {1, 2, 3, 4, 5};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    int temp[5];
    int i;

    print_array(numbers, size, "元の配列");

    /* 2乗を適用 */
    for (i = 0; i < size; i++)
        temp[i] = numbers[i];
    apply_to_array(temp, size, square);
    print_array(temp, size, "2乗後");

    /* 3乗を適用 */
    for (i = 0; i < size; i++)
        temp[i] = numbers[i];
    apply_to_array(temp, size, cube);
    print_array(temp, size, "3乗後");

    /* 2倍を適用 */
    for (i = 0; i < size; i++)
        temp[i] = numbers[i];
    apply_to_array(temp, size, double_value);
    print_array(temp, size, "2倍後");

    /* 2. 配列フィルタリング */
    printf("\n=== 配列フィルタリング ===\n");
    int test_array[] = {-3, -1, 0, 2, 4, 5, 7, 8};
    int test_size = sizeof(test_array) / sizeof(test_array[0]);
    int filtered[8];
    int filtered_count;

    print_array(test_array, test_size, "元の配列");

    /* 偶数をフィルタリング */
    filtered_count = filter_array(test_array, filtered, test_size, is_even);
    print_array(filtered, filtered_count, "偶数のみ");

    /* 奇数をフィルタリング */
    filtered_count = filter_array(test_array, filtered, test_size, is_odd);
    print_array(filtered, filtered_count, "奇数のみ");

    /* 正の数をフィルタリング */
    filtered_count = filter_array(test_array, filtered, test_size, is_positive);
    print_array(filtered, filtered_count, "正の数のみ");

    /* 3. 文字列処理のコールバック */
    printf("\n=== 文字列処理のコールバック ===\n");
    char text1[] = "Hello World";
    char text2[] = "Hello World";
    char text3[] = "Hello World";

    printf("元の文字列: '%s'\n", text1);

    process_string(text1, to_upper_char);
    printf("大文字変換: '%s'\n", text1);

    process_string(text2, to_lower_char);
    printf("小文字変換: '%s'\n", text2);

    process_string(text3, replace_space_with_underscore);
    printf("スペース置換: '%s'\n", text3);

    /* 4. ソートのコールバック */
    printf("\n=== ソートのコールバック ===\n");
    int sort_array[] = {64, 34, 25, 12, 22, 11, 90, 5};
    int sort_size = sizeof(sort_array) / sizeof(sort_array[0]);
    int sort_temp[8];

    print_array(sort_array, sort_size, "元の配列");

    /* 昇順ソート */
    for (i = 0; i < sort_size; i++)
        sort_temp[i] = sort_array[i];
    bubble_sort(sort_temp, sort_size, compare_ascending);
    print_array(sort_temp, sort_size, "昇順ソート");

    /* 降順ソート */
    for (i = 0; i < sort_size; i++)
        sort_temp[i] = sort_array[i];
    bubble_sort(sort_temp, sort_size, compare_descending);
    print_array(sort_temp, sort_size, "降順ソート");

    /* 5. イベントハンドラシステム */
    printf("\n=== イベントハンドラシステム ===\n");

    trigger_event("アプリケーション開始", on_start_event);
    trigger_event("処理中にエラーが発生", on_error_event);
    trigger_event("アプリケーション終了", on_stop_event);

    /* 6. ログ付き計算実行 */
    printf("\n=== ログ付き計算実行 ===\n");

    execute_with_logging(10, 5, add_for_logging, "加算");
    execute_with_logging(7, 8, multiply_for_logging, "乗算");

    printf("\n=== コールバック関数デモ完了 ===\n");

    return 0;
}
