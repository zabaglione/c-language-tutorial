/*
 * ファイル名: ex9_9_sorting_algorithms_c99.c
 * 演習9-9: ソートアルゴリズム関数
 * 説明: 各種ソートアルゴリズムの実装（バブル、選択、挿入、マージソート等）（C99版）
 * 規格: C99準拠
 */
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

// 関数プロトタイプ
void bubble_sort(int arr[], int size);
void selection_sort(int arr[], int size);
void insertion_sort(int arr[], int size);
void merge_sort(int arr[], int left, int right);
void merge(int arr[], int left, int mid, int right);
void quick_sort(int arr[], int left, int right);
int partition(int arr[], int left, int right);
void sort_strings(char strings[][100], int count);
void print_array(int arr[], int size);
void copy_array(int dest[], int src[], int size);

// バブルソート（C99: bool型とfor文内変数宣言）
void bubble_sort(int arr[], int size)
{
    for (int i = 0; i < size - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < size - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                // C99: 使用箇所で変数宣言
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        // 交換が発生しなかった場合、ソート完了
        if (!swapped) break;
    }
}

// 選択ソート
void selection_sort(int arr[], int size)
{
    for (int i = 0; i < size - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        
        // 最小値を先頭に移動
        if (min_idx != i) {
            int temp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
        }
    }
}

// 挿入ソート
void insertion_sort(int arr[], int size)
{
    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;
        
        // key より大きい要素を後ろに移動
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// マージソート用のマージ関数（C99: 可変長配列）
void merge(int arr[], int left, int mid, int right)
{
    int left_size = mid - left + 1;
    int right_size = right - mid;
    
    // C99: 可変長配列
    int left_arr[left_size];
    int right_arr[right_size];
    
    // 部分配列をコピー
    for (int i = 0; i < left_size; i++) {
        left_arr[i] = arr[left + i];
    }
    for (int j = 0; j < right_size; j++) {
        right_arr[j] = arr[mid + 1 + j];
    }
    
    // マージ処理
    int i = 0, j = 0, k = left;
    while (i < left_size && j < right_size) {
        if (left_arr[i] <= right_arr[j]) {
            arr[k++] = left_arr[i++];
        } else {
            arr[k++] = right_arr[j++];
        }
    }
    
    // 残りの要素をコピー
    while (i < left_size) arr[k++] = left_arr[i++];
    while (j < right_size) arr[k++] = right_arr[j++];
}

// マージソート
void merge_sort(int arr[], int left, int right)
{
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// クイックソート用の分割関数
int partition(int arr[], int left, int right)
{
    int pivot = arr[right]; // 最後の要素をピボットとする
    int i = left - 1;
    
    for (int j = left; j <= right - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    
    int temp = arr[i + 1];
    arr[i + 1] = arr[right];
    arr[right] = temp;
    
    return i + 1;
}

// クイックソート
void quick_sort(int arr[], int left, int right)
{
    if (left < right) {
        int pivot_index = partition(arr, left, right);
        quick_sort(arr, left, pivot_index - 1);
        quick_sort(arr, pivot_index + 1, right);
    }
}

// 文字列配列のソート（C99: strcmp使用）
void sort_strings(char strings[][100], int count)
{
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - 1 - i; j++) {
            if (strcmp(strings[j], strings[j + 1]) > 0) {
                char temp[100];
                strcpy(temp, strings[j]);
                strcpy(strings[j], strings[j + 1]);
                strcpy(strings[j + 1], temp);
            }
        }
    }
}

// 配列を表示する関数
void print_array(int arr[], int size)
{
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i < size - 1) printf(", ");
    }
    printf("]");
}

// 配列をコピーする関数
void copy_array(int dest[], int src[], int size)
{
    for (int i = 0; i < size; i++) {
        dest[i] = src[i];
    }
}

// C99追加: ソート関数ポインタ型
typedef void (*sort_func_t)(int[], int);

// C99追加: ソート性能測定関数（簡易版）
void measure_sort_performance(sort_func_t sort_func, const char* name, 
                             int test_data[], int size)
{
    int data_copy[size]; // C99: 可変長配列
    copy_array(data_copy, test_data, size);
    
    printf("   %s: ", name);
    print_array(data_copy, size);
    printf(" -> ");
    
    sort_func(data_copy, size);
    print_array(data_copy, size);
    printf("\n");
}

int main(void)
{
    printf("=== ソートアルゴリズムのデモ（C99版）===\n\n");

    // テスト用データ（C99: 配列初期化）
    int original_data[] = {64, 34, 25, 12, 22, 11, 90, 88, 76, 50, 42, 19};
    int data_size = sizeof(original_data) / sizeof(original_data[0]);

    printf("元のデータ: ");
    print_array(original_data, data_size);
    printf("\n\n");

    // C99: 構造体を使ったソート関数管理
    struct {
        sort_func_t func;
        const char* name;
    } sort_methods[] = {
        {bubble_sort, "バブルソート"},
        {selection_sort, "選択ソート"},
        {insertion_sort, "挿入ソート"}
    };

    // 基本的なソートアルゴリズムのデモ
    printf("=== 基本ソートアルゴリズム ===\n");
    for (int i = 0; i < 3; i++) {
        measure_sort_performance(sort_methods[i].func, sort_methods[i].name, 
                               original_data, data_size);
    }
    printf("\n");

    // マージソートとクイックソートのデモ
    printf("=== 分割統治法ソート ===\n");
    
    // マージソート
    int merge_data[data_size]; // C99: 可変長配列
    copy_array(merge_data, original_data, data_size);
    printf("   マージソート: ");
    print_array(merge_data, data_size);
    printf(" -> ");
    merge_sort(merge_data, 0, data_size - 1);
    print_array(merge_data, data_size);
    printf("\n");

    // クイックソート
    int quick_data[data_size]; // C99: 可変長配列
    copy_array(quick_data, original_data, data_size);
    printf("   クイックソート: ");
    print_array(quick_data, data_size);
    printf(" -> ");
    quick_sort(quick_data, 0, data_size - 1);
    print_array(quick_data, data_size);
    printf("\n\n");

    // 文字列ソート
    printf("=== 文字列ソート ===\n");
    char fruits[][100] = {"orange", "apple", "banana", "grape", "cherry", "kiwi"};
    int fruit_count = 6;
    
    printf("   ソート前: ");
    for (int i = 0; i < fruit_count; i++) {
        printf("%s", fruits[i]);
        if (i < fruit_count - 1) printf(", ");
    }
    printf("\n");
    
    sort_strings(fruits, fruit_count);
    
    printf("   ソート後: ");
    for (int i = 0; i < fruit_count; i++) {
        printf("%s", fruits[i]);
        if (i < fruit_count - 1) printf(", ");
    }
    printf("\n\n");

    // C99機能を活用したデモ
    printf("=== C99機能を活用した高度な例 ===\n");
    
    // 動的サイズ配列でのソート
    printf("1. 可変長配列を使ったソート:\n");
    int size_variations[] = {5, 8, 10};
    
    for (int s = 0; s < 3; s++) {
        int current_size = size_variations[s];
        int dynamic_data[current_size]; // C99: 可変長配列
        
        // テストデータを生成
        for (int i = 0; i < current_size; i++) {
            dynamic_data[i] = (i * 7 + 13) % 50;
        }
        
        printf("   サイズ %d: ", current_size);
        print_array(dynamic_data, current_size);
        printf(" -> ");
        
        insertion_sort(dynamic_data, current_size);
        print_array(dynamic_data, current_size);
        printf("\n");
    }
    
    // 複合リテラルを使った一時的なソート
    printf("\n2. 複合リテラルを使った一時的配列のソート:\n");
    int temp_result[5];
    copy_array(temp_result, (int[]){5, 2, 8, 1, 9}, 5);
    printf("   複合リテラル配列: ");
    print_array(temp_result, 5);
    printf(" -> ");
    bubble_sort(temp_result, 5);
    print_array(temp_result, 5);
    printf("\n");
    
    // bool型を使った条件付きソート
    printf("\n3. 条件付きソート（bool型使用）:\n");
    bool should_sort_ascending = true;
    int conditional_data[] = {3, 1, 4, 1, 5, 9, 2, 6};
    int cond_size = sizeof(conditional_data) / sizeof(conditional_data[0]);
    
    printf("   元データ: ");
    print_array(conditional_data, cond_size);
    printf("\n");
    
    if (should_sort_ascending) {
        insertion_sort(conditional_data, cond_size);
        printf("   昇順ソート結果: ");
    } else {
        printf("   ソートをスキップ: ");
    }
    print_array(conditional_data, cond_size);
    printf("\n");

    printf("\n=== C99ソートアルゴリズムデモ完了 ===\n");
    return 0;
}

/*
学習ポイント（C99追加機能）:
1. bool型を使った制御フローの明確化
2. for文内での変数宣言による局所化
3. 可変長配列による動的メモリ管理
4. 関数ポインタ型定義による抽象化
5. 複合リテラルによる一時的データ作成

実装のポイント:
- C99準拠のため、変数を使用箇所で宣言
- 可変長配列で効率的なメモリ使用
- bool型によるより読みやすい制御構造
- 構造体を活用したデータとロジックの整理
- 標準ライブラリ関数の活用
*/