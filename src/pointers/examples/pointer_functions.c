/*
 * pointer_functions.c
 * 関数引数、戻り値としてのポインタの使用方法を学習
 * C90準拠
 */

#include <stdio.h>
#include <string.h>

/* 2つの値を交換する関数 */
void swap_values(int *a, int *b)
{
    int temp;
    
    printf("  swap関数内: 交換前 *a = %d, *b = %d\n", *a, *b);
    
    temp = *a;
    *a = *b;
    *b = temp;
    
    printf("  swap関数内: 交換後 *a = %d, *b = %d\n", *a, *b);
}

/* 値を2倍にする関数 */
void double_value(int *value)
{
    printf("  double_value関数内: 変更前 *value = %d\n", *value);
    *value = (*value) * 2;
    printf("  double_value関数内: 変更後 *value = %d\n", *value);
}

/* 配列の合計を計算する関数 */
int sum_array(int *arr, int size)
{
    int sum = 0;
    int i;
    
    for (i = 0; i < size; i++) {
        sum += *(arr + i);  /* ポインタ記法 */
    }
    
    return sum;
}

/* 配列の要素を変更する関数 */
void modify_array(int *arr, int size, int multiplier)
{
    int i;
    
    printf("  modify_array関数内: 変更前\n    ");
    for (i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    for (i = 0; i < size; i++) {
        arr[i] *= multiplier;
    }
    
    printf("  modify_array関数内: 変更後（%d倍）\n    ", multiplier);
    for (i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

/* 配列から最大値のポインタを返す関数 */
int* find_max_pointer(int *arr, int size)
{
    int *max_ptr = arr;  /* 最初の要素を最大とする */
    int i;
    
    for (i = 1; i < size; i++) {
        if (*(arr + i) > *max_ptr) {
            max_ptr = arr + i;
        }
    }
    
    return max_ptr;
}

/* 配列から指定値を検索してポインタを返す関数 */
int* search_value(int *arr, int size, int target)
{
    int i;
    
    for (i = 0; i < size; i++) {
        if (*(arr + i) == target) {
            return arr + i;  /* 見つかった要素のポインタを返す */
        }
    }
    
    return NULL;  /* 見つからない場合はNULLを返す */
}

/* 文字列の長さを計算する関数（ポインタ版） */
int string_length_ptr(char *str)
{
    int length = 0;
    
    while (*str != '\0') {
        length++;
        str++;
    }
    
    return length;
}

/* 文字列をコピーする関数（ポインタ版） */
void string_copy_ptr(char *dest, char *src)
{
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';  /* null終端文字を追加 */
}

/* 配列を初期化する関数 */
void init_array(int *arr, int size, int init_value)
{
    int i;
    
    for (i = 0; i < size; i++) {
        *(arr + i) = init_value + i;  /* 初期値 + インデックス */
    }
}

/* 配列を表示する関数 */
void print_array(char *label, int *arr, int size)
{
    int i;
    
    printf("%s: ", label);
    for (i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(void)
{
    /* C90: 全変数宣言を先頭に配置 */
    int x = 10, y = 20;
    int numbers[6];
    int size;
    int total;
    int data[] = {45, 67, 23, 89, 12, 56, 78};
    int data_size;
    int *result_ptr;
    int search_target = 56;
    char original[] = "Hello, World!";
    char copy_buffer[50];
    char *fruits[] = {"Apple", "Banana", "Cherry", "Date"};
    int fruit_count;
    int i;
    int *arrays[2];         /* C90では可変初期化ができないため配列サイズを固定 */
    int sizes[2];
    char *labels[] = {"numbers配列", "data配列"};
    int array_sum;
    
    printf("===== ポインタを引数とする関数 =====\n");
    
    /* 変数の初期化 */
    size = sizeof(numbers) / sizeof(numbers[0]);
    data_size = sizeof(data) / sizeof(data[0]);
    fruit_count = sizeof(fruits) / sizeof(fruits[0]);
    
    /* swap関数のテスト */
    printf("\nswap関数のテスト:\n");
    printf("交換前: x = %d, y = %d\n", x, y);
    swap_values(&x, &y);
    printf("交換後: x = %d, y = %d\n", x, y);
    
    /* double_value関数のテスト */
    printf("\ndouble_value関数のテスト:\n");
    printf("2倍前: x = %d\n", x);
    double_value(&x);
    printf("2倍後: x = %d\n", x);
    
    printf("\n===== 配列を操作する関数 =====\n");
    
    /* 配列の初期化 */
    init_array(numbers, size, 10);
    print_array("初期化後", numbers, size);
    
    /* 配列の合計計算 */
    total = sum_array(numbers, size);
    printf("配列の合計: %d\n", total);
    
    /* 配列の変更 */
    printf("\n配列変更のテスト:\n");
    modify_array(numbers, size, 3);
    print_array("main関数内での変更後", numbers, size);
    
    printf("\n===== ポインタを戻り値とする関数 =====\n");
    
    print_array("検索対象配列", data, data_size);
    
    /* 最大値の検索 */
    result_ptr = find_max_pointer(data, data_size);
    if (result_ptr != NULL) {
        printf("最大値: %d (アドレス: %p)\n", *result_ptr, (void*)result_ptr);
        printf("最大値のインデックス: %ld\n", result_ptr - data);
    }
    
    /* 特定値の検索 */
    result_ptr = search_value(data, data_size, search_target);
    if (result_ptr != NULL) {
        printf("%d が見つかりました (アドレス: %p)\n", 
               *result_ptr, (void*)result_ptr);
        printf("見つかった位置のインデックス: %ld\n", result_ptr - data);
        
        /* 見つかった値を変更 */
        *result_ptr = 999;
        print_array("値変更後", data, data_size);
    } else {
        printf("%d は見つかりませんでした\n", search_target);
    }
    
    printf("\n===== 文字列操作関数 =====\n");
    
    printf("元の文字列: \"%s\"\n", original);
    printf("文字列の長さ: %d文字\n", string_length_ptr(original));
    
    /* 文字列のコピー */
    string_copy_ptr(copy_buffer, original);
    printf("コピーした文字列: \"%s\"\n", copy_buffer);
    
    printf("\n===== ポインタによる高度な操作 =====\n");
    
    /* ポインタの配列を使った複数の文字列 */
    
    printf("果物リスト:\n");
    for (i = 0; i < fruit_count; i++) {
        printf("  %d. %s (長さ: %d文字)\n", 
               i + 1, fruits[i], string_length_ptr(fruits[i]));
    }
    
    /* 複数の配列を処理 */
    /* C90: 配列初期化は宣言時のみ可能なため、手動で代入 */
    arrays[0] = numbers;
    arrays[1] = data;
    sizes[0] = size;
    sizes[1] = data_size;
    
    printf("\n複数配列の合計:\n");
    for (i = 0; i < 2; i++) {
        array_sum = sum_array(arrays[i], sizes[i]);
        printf("  %s の合計: %d\n", labels[i], array_sum);
    }
    
    return 0;
}

/*
学習ポイント:
1. 関数引数としてのポインタ:
   - 値の変更が可能（参照渡し）
   - 配列の受け渡し
   - NULLチェックの重要性

2. 戻り値としてのポインタ:
   - 配列要素のアドレス返し
   - NULLによるエラー表現
   - ローカル変数のアドレス返しは危険

3. 実用的なポインタ活用:
   - 配列操作の効率化
   - 文字列処理
   - データ検索と変更
   - 複数データの一括処理

4. メモリ安全性:
   - 境界チェック
   - NULLポインタチェック
   - 適切な初期化

注意点:
- ローカル変数のアドレスを返してはいけない
- 配列の範囲外アクセスに注意
- NULLポインタの参照は避ける
- ポインタ演算の境界を意識する
*/
