/*
 * pointer_functions_c99.c
 * 関数引数、戻り値としてのポインタの使用方法を学習
 * C99準拠 - //コメント、bool型、変数宣言位置の自由化、restrict
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

// C99: インライン関数として実装
static inline void swap_values(int *a, int *b)
{
    printf("  swap関数内: 交換前 *a = %d, *b = %d\n", *a, *b);
    
    int temp = *a;  // C99: 使用箇所で変数宣言
    *a = *b;
    *b = temp;
    
    printf("  swap関数内: 交換後 *a = %d, *b = %d\n", *a, *b);
}

// 値を2倍にする関数
static inline void double_value(int *value)
{
    printf("  double_value関数内: 変更前 *value = %d\n", *value);
    *value = (*value) * 2;
    printf("  double_value関数内: 変更後 *value = %d\n", *value);
}

// 配列の合計を計算する関数（C99: restrict修飾子）
int sum_array(int * restrict arr, int size)
{
    int sum = 0;
    
    for (int i = 0; i < size; i++) {  // C99: forループ内で変数宣言
        sum += *(arr + i);  // ポインタ記法
    }
    
    return sum;
}

// 配列の要素を変更する関数
void modify_array(int *arr, int size, int multiplier)
{
    printf("  modify_array関数内: 変更前\n    ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    for (int i = 0; i < size; i++) {
        arr[i] *= multiplier;
    }
    
    printf("  modify_array関数内: 変更後（%d倍）\n    ", multiplier);
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// 配列から最大値のポインタを返す関数
int* find_max_pointer(int *arr, int size)
{
    if (arr == NULL || size <= 0) {  // 安全性チェック
        return NULL;
    }
    
    int *max_ptr = arr;  // 最初の要素を最大とする
    
    for (int i = 1; i < size; i++) {  // C99: forループ内で変数宣言
        if (*(arr + i) > *max_ptr) {
            max_ptr = arr + i;
        }
    }
    
    return max_ptr;
}

// 特定の値を検索してポインタを返す関数
int* search_value(int *arr, int size, int target)
{
    for (int i = 0; i < size; i++) {
        if (*(arr + i) == target) {
            return arr + i;  // 見つかった要素のポインタを返す
        }
    }
    return NULL;  // 見つからなかった場合
}

// 配列を初期化する関数
void init_array(int *arr, int size, int initial_value)
{
    for (int i = 0; i < size; i++) {
        arr[i] = initial_value + i;
    }
}

// ポインタを使った文字列の長さ計算
int string_length_ptr(const char *str)
{
    if (str == NULL) return 0;  // NULLチェック
    
    int length = 0;
    while (*str != '\0') {  // 文字列の終端まで
        length++;
        str++;
    }
    return length;
}

// ポインタを使った文字列のコピー
void string_copy_ptr(char *dest, const char *src)
{
    if (dest == NULL || src == NULL) return;  // NULLチェック
    
    while ((*dest = *src) != '\0') {  // コピーしながら終端をチェック
        dest++;
        src++;
    }
}

// 配列を表示する補助関数
void print_array(const char *label, int *arr, int size)
{
    printf("%s: ", label);
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// C99: 可変長配列を処理する関数
void process_vla(int size, int vla[size])  // C99: VLAパラメータ
{
    printf("  可変長配列（サイズ%d）を処理中:\n", size);
    
    // 各要素を2倍にする
    for (int i = 0; i < size; i++) {
        vla[i] *= 2;
    }
    
    printf("    処理後: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", vla[i]);
    }
    printf("\n");
}

// C99: restrict修飾子を使った配列コピー関数
void copy_array_restrict(int * restrict dest, int * restrict src, int size)
{
    // restrict修飾子により、destとsrcは重複しないことが保証される
    for (int i = 0; i < size; i++) {
        dest[i] = src[i];
    }
}

// C99: bool型を返す関数 - 配列がソート済みかチェック
bool is_array_sorted(int *arr, int size)
{
    for (int i = 0; i < size - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return false;
        }
    }
    return true;
}

int main(void)
{
    printf("===== ポインタを引数とする関数 =====\n");
    
    // swap関数のテスト
    int x = 10, y = 20;
    printf("\nswap関数のテスト:\n");
    printf("交換前: x = %d, y = %d\n", x, y);
    swap_values(&x, &y);
    printf("交換後: x = %d, y = %d\n", x, y);
    
    // double_value関数のテスト
    printf("\ndouble_value関数のテスト:\n");
    printf("2倍前: x = %d\n", x);
    double_value(&x);
    printf("2倍後: x = %d\n", x);
    
    printf("\n===== 配列を操作する関数 =====\n");
    
    int numbers[6];
    int size = sizeof(numbers) / sizeof(numbers[0]);
    
    // 配列の初期化
    init_array(numbers, size, 10);
    print_array("初期化後", numbers, size);
    
    // 配列の合計計算
    int total = sum_array(numbers, size);
    printf("配列の合計: %d\n", total);
    
    // 配列の変更
    printf("\n配列変更のテスト:\n");
    modify_array(numbers, size, 3);
    print_array("main関数内での変更後", numbers, size);
    
    printf("\n===== ポインタを戻り値とする関数 =====\n");
    
    int data[] = {45, 67, 23, 89, 12, 56, 78};
    int data_size = sizeof(data) / sizeof(data[0]);
    int search_target = 56;
    
    print_array("検索対象配列", data, data_size);
    
    // 最大値の検索
    int *result_ptr = find_max_pointer(data, data_size);
    if (result_ptr != NULL) {
        printf("最大値: %d (アドレス: %p)\n", *result_ptr, (void*)result_ptr);
        printf("最大値のインデックス: %td\n", result_ptr - data);  // C99: %td
    }
    
    // 特定値の検索
    result_ptr = search_value(data, data_size, search_target);
    if (result_ptr != NULL) {
        printf("%d が見つかりました (アドレス: %p)\n", 
               *result_ptr, (void*)result_ptr);
        printf("見つかった位置のインデックス: %td\n", result_ptr - data);
        
        // 見つかった値を変更
        *result_ptr = 999;
        print_array("値変更後", data, data_size);
    } else {
        printf("%d は見つかりませんでした\n", search_target);
    }
    
    printf("\n===== 文字列操作関数 =====\n");
    
    char original[] = "Hello, World!";
    char copy_buffer[50];
    
    printf("元の文字列: \"%s\"\n", original);
    printf("文字列の長さ: %d文字\n", string_length_ptr(original));
    
    // 文字列のコピー
    string_copy_ptr(copy_buffer, original);
    printf("コピーした文字列: \"%s\"\n", copy_buffer);
    
    printf("\n===== ポインタによる高度な操作 =====\n");
    
    // ポインタの配列を使った複数の文字列
    char *fruits[] = {"Apple", "Banana", "Cherry", "Date"};
    int fruit_count = sizeof(fruits) / sizeof(fruits[0]);
    
    printf("果物リスト:\n");
    for (int i = 0; i < fruit_count; i++) {  // C99: forループ内で変数宣言
        printf("  %d. %s (長さ: %d文字)\n", 
               i + 1, fruits[i], string_length_ptr(fruits[i]));
    }
    
    // 複数の配列を処理
    int *arrays[] = {numbers, data};
    int sizes[] = {size, data_size};
    char *labels[] = {"numbers配列", "data配列"};
    
    printf("\n複数配列の合計:\n");
    for (int i = 0; i < 2; i++) {
        int array_sum = sum_array(arrays[i], sizes[i]);
        printf("  %s の合計: %d\n", labels[i], array_sum);
    }
    
    // C99: 可変長配列のテスト
    printf("\n===== 可変長配列の処理（C99） =====\n");
    int vla_size = 5;
    int vla[vla_size];  // C99: 可変長配列
    
    // VLAの初期化
    for (int i = 0; i < vla_size; i++) {
        vla[i] = (i + 1) * 5;
    }
    
    printf("VLA処理前: ");
    for (int i = 0; i < vla_size; i++) {
        printf("%d ", vla[i]);
    }
    printf("\n");
    
    process_vla(vla_size, vla);
    
    // C99: restrict修飾子のテスト
    printf("\n===== restrict修飾子のテスト（C99） =====\n");
    int source_array[] = {100, 200, 300, 400};
    int dest_array[4];
    int array_size = 4;
    
    printf("コピー前:\n");
    print_array("  source", source_array, array_size);
    print_array("  dest  ", dest_array, array_size);
    
    copy_array_restrict(dest_array, source_array, array_size);
    
    printf("コピー後:\n");
    print_array("  source", source_array, array_size);
    print_array("  dest  ", dest_array, array_size);
    
    // C99: bool型を返す関数の例
    printf("\n===== bool型を返す関数（C99） =====\n");
    
    bool sorted = is_array_sorted(data, data_size);
    printf("data配列はソート済み? %s\n", sorted ? "true" : "false");
    
    return 0;
}

/*
学習ポイント:
1. 関数引数としてのポインタ:
   - 値の変更が可能（参照渡し）
   - 配列を効率的に渡せる
   - NULLチェックによる安全性向上

2. 関数戻り値としてのポインタ:
   - 配列内の特定要素を指すポインタ
   - 見つからない場合のNULL返却
   - ローカル変数のアドレスは返さない

3. 配列操作の効率性:
   - メモリコピーなしで配列を渡せる
   - ポインタ演算による高速アクセス
   - インデックス記法とポインタ記法の使い分け

4. 文字列操作:
   - 文字列もポインタで効率的に処理
   - 終端文字の適切な処理
   - NULLポインタチェック

5. C99での拡張:
   - インライン関数による最適化
   - bool型による明確な戻り値
   - forループ内での変数宣言
   - 可変長配列（VLA）の活用
   - restrict修飾子による最適化ヒント
   - ローカル関数の定義

注意点:
- ローカル変数のアドレスを返してはいけない
- 配列の範囲外アクセスに注意
- NULLポインタの参照は避ける
- ポインタ演算の境界を意識する
- restrict修飾子は重複しないポインタにのみ使用
*/
