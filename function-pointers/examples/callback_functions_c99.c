/* コールバック関数の活用（C99版） */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* 配列処理用のコールバック関数群 */
int square(int x) { return x * x; }
int cube(int x) { return x * x * x; }
int double_value(int x) { return x * 2; }
int increment(int x) { return x + 1; }

/* 条件判定用のコールバック関数群 - C99ではboolを使用 */
bool is_even(int x) { return x % 2 == 0; }
bool is_odd(int x) { return x % 2 != 0; }
bool is_positive(int x) { return x > 0; }
bool is_negative(int x) { return x < 0; }

/* 配列の各要素に関数を適用 */
void apply_to_array(int arr[], int size, int (*func)(int))
{
    for (int i = 0; i < size; i++)
    {
        arr[i] = func(arr[i]);
    }
}

/* 配列をフィルタリング - C99ではboolを使用 */
int filter_array(int source[], int dest[], int size, bool (*predicate)(int))
{
    int count = 0;
    for (int i = 0; i < size; i++)
    {
        if (predicate(source[i]))
        {
            dest[count++] = source[i];
        }
    }
    return count;
}

/* 配列を表示する関数 */
void print_array(const int arr[], int size, const char *label)
{
    printf("%s: ", label);
    for (int i = 0; i < size; i++)
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
    for (int i = 0; str[i] != '\0'; i++)
    {
        processor(&str[i]);
    }
}

/* ソート用の比較関数 */
int compare_ascending(const void *a, const void *b)
{
    return *(const int*)a - *(const int*)b;
}

int compare_descending(const void *a, const void *b)
{
    return *(const int*)b - *(const int*)a;
}

/* 汎用的なバブルソート */
void bubble_sort(void *arr, size_t n, size_t size, int (*compare)(const void *, const void *))
{
    char *array = (char *)arr;
    char temp[size];
    
    for (size_t i = 0; i < n - 1; i++)
    {
        for (size_t j = 0; j < n - 1 - i; j++)
        {
            if (compare(array + j * size, array + (j + 1) * size) > 0)
            {
                memcpy(temp, array + j * size, size);
                memcpy(array + j * size, array + (j + 1) * size, size);
                memcpy(array + (j + 1) * size, temp, size);
            }
        }
    }
}

/* イベントハンドラシステム */
typedef void (*EventHandler)(const char *);

typedef struct {
    const char *name;
    EventHandler handler;
} Event;

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

void on_warning_event(const char *message)
{
    printf("[警告イベント] %s\n", message);
}

/* イベントを処理する関数 */
void trigger_event(const char *message, EventHandler event_handler)
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

/* 簡単な計算関数群 */
int add_for_logging(int a, int b) { return a + b; }
int multiply_for_logging(int a, int b) { return a * b; }
int subtract_for_logging(int a, int b) { return a - b; }
int divide_for_logging(int a, int b) { return b != 0 ? a / b : 0; }

/* 高度な配列操作: マップ関数 */
void map_array(int dest[], const int src[], int size, int (*mapper)(int))
{
    for (int i = 0; i < size; i++)
    {
        dest[i] = mapper(src[i]);
    }
}

/* 高度な配列操作: リデュース関数 */
int reduce_array(const int arr[], int size, int (*reducer)(int, int), int initial)
{
    int result = initial;
    for (int i = 0; i < size; i++)
    {
        result = reducer(result, arr[i]);
    }
    return result;
}

/* リデューサー関数群 */
int sum_reducer(int acc, int val) { return acc + val; }
int product_reducer(int acc, int val) { return acc * val; }
int max_reducer(int acc, int val) { return acc > val ? acc : val; }
int min_reducer(int acc, int val) { return acc < val ? acc : val; }

int main(void)
{
    printf("=== コールバック関数の活用（C99版） ===\n\n");

    // 1. 配列処理のコールバック
    printf("=== 配列処理のコールバック ===\n");
    int numbers[] = {1, 2, 3, 4, 5};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    int temp[5];

    print_array(numbers, size, "元の配列");

    // マップ操作のデモ
    map_array(temp, numbers, size, square);
    print_array(temp, size, "2乗後");

    map_array(temp, numbers, size, cube);
    print_array(temp, size, "3乗後");

    map_array(temp, numbers, size, double_value);
    print_array(temp, size, "2倍後");

    // 2. 配列フィルタリング
    printf("\n=== 配列フィルタリング ===\n");
    int test_array[] = {-3, -1, 0, 2, 4, 5, 7, 8};
    int test_size = sizeof(test_array) / sizeof(test_array[0]);
    int filtered[8];

    print_array(test_array, test_size, "元の配列");

    int filtered_count = filter_array(test_array, filtered, test_size, is_even);
    print_array(filtered, filtered_count, "偶数のみ");

    filtered_count = filter_array(test_array, filtered, test_size, is_odd);
    print_array(filtered, filtered_count, "奇数のみ");

    filtered_count = filter_array(test_array, filtered, test_size, is_positive);
    print_array(filtered, filtered_count, "正の数のみ");

    // 3. リデュース操作
    printf("\n=== リデュース操作 ===\n");
    int sum = reduce_array(numbers, size, sum_reducer, 0);
    int product = reduce_array(numbers, size, product_reducer, 1);
    int max = reduce_array(numbers, size, max_reducer, numbers[0]);
    int min = reduce_array(numbers, size, min_reducer, numbers[0]);

    printf("合計: %d\n", sum);
    printf("積: %d\n", product);
    printf("最大値: %d\n", max);
    printf("最小値: %d\n", min);

    // 4. 文字列処理のコールバック
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

    // 5. ソートのコールバック（標準ライブラリ版）
    printf("\n=== ソートのコールバック ===\n");
    int sort_array[] = {64, 34, 25, 12, 22, 11, 90, 5};
    int sort_size = sizeof(sort_array) / sizeof(sort_array[0]);
    int sort_temp[8];

    print_array(sort_array, sort_size, "元の配列");

    // 昇順ソート
    memcpy(sort_temp, sort_array, sizeof(sort_array));
    qsort(sort_temp, sort_size, sizeof(int), compare_ascending);
    print_array(sort_temp, sort_size, "昇順ソート");

    // 降順ソート
    memcpy(sort_temp, sort_array, sizeof(sort_array));
    qsort(sort_temp, sort_size, sizeof(int), compare_descending);
    print_array(sort_temp, sort_size, "降順ソート");

    // 6. イベントハンドラシステム
    printf("\n=== イベントハンドラシステム ===\n");

    // イベントテーブルの使用
    Event events[] = {
        {"start", on_start_event},
        {"stop", on_stop_event},
        {"error", on_error_event},
        {"warning", on_warning_event}
    };

    // イベントの発火
    trigger_event("アプリケーション開始", events[0].handler);
    trigger_event("メモリ不足警告", events[3].handler);
    trigger_event("処理中にエラーが発生", events[2].handler);
    trigger_event("アプリケーション終了", events[1].handler);

    // 7. ログ付き計算実行
    printf("\n=== ログ付き計算実行 ===\n");

    // 関数ポインター配列を使った計算
    struct {
        const char *name;
        int (*func)(int, int);
    } operations[] = {
        {"加算", add_for_logging},
        {"減算", subtract_for_logging},
        {"乗算", multiply_for_logging},
        {"除算", divide_for_logging}
    };

    for (int i = 0; i < 4; i++)
    {
        execute_with_logging(20, 4, operations[i].func, operations[i].name);
    }

    printf("\n=== コールバック関数デモ完了 ===\n");

    return 0;
}

/*
C99の特徴:
1. bool型の使用（条件判定関数で活用）
2. 変数宣言を使用箇所で可能
3. for文内での変数宣言
4. 可変長配列（VLA）の使用
5. 複合リテラルの使用
6. // 形式のコメント

学習ポイント:
1. コールバック関数による汎用的な処理
2. 高階関数（マップ、フィルター、リデュース）の実装
3. イベント駆動プログラミングの基礎
4. 関数ポインターとデータ構造の組み合わせ
5. 標準ライブラリのqsortとの連携
*/