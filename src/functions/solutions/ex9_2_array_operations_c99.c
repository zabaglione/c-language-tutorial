/*
 * 演習9-2: 配列操作関数 - 解答例（C99版）
 * 
 * 配列に対する各種操作を行う関数群を実装します。
 * C99の機能：//コメント、変数宣言位置の自由化、bool型、for文内での変数宣言
 */
#include <stdio.h>
#include <stdlib.h>  // calloc, free用
#include <stdbool.h>

// 関数プロトタイプ
// 基本操作
int array_sum(const int arr[], int size);  // C99: const修飾子
double array_average(const int arr[], int size);
int find_max_index(const int arr[], int size);

// 検索・ソート
int linear_search(const int arr[], int size, int target);
void sort_array(int arr[], int size);
void reverse_array(int arr[], int size);

// 配列統計
void find_min_max(const int arr[], int size, int *min, int *max);
int count_duplicates(const int arr[], int size);

// 追加関数（C99版）
bool is_sorted(const int arr[], int size);
int find_second_max(const int arr[], int size);

// ヘルパー関数
void print_array(const int arr[], int size);
void swap(int *a, int *b);

// 配列の要素の合計を計算する関数
int array_sum(const int arr[], int size)
{
    int sum = 0;
    
    for (int i = 0; i < size; i++)  // C99: forループ内で変数宣言
    {
        sum += arr[i];
    }
    
    return sum;
}

// 配列の平均値を計算する関数
double array_average(const int arr[], int size)
{
    if (size == 0)
    {
        return 0.0;
    }
    
    return (double)array_sum(arr, size) / size;
}

// 配列内の最大値のインデックスを返す関数
int find_max_index(const int arr[], int size)
{
    if (size <= 0)
    {
        return -1;  // エラー
    }
    
    int max_index = 0;
    
    for (int i = 1; i < size; i++)  // C99: forループ内で変数宣言
    {
        if (arr[i] > arr[max_index])
        {
            max_index = i;
        }
    }
    
    return max_index;
}

// 線形検索関数（見つかったらインデックス、見つからなければ-1を返す）
int linear_search(const int arr[], int size, int target)
{
    for (int i = 0; i < size; i++)  // C99: forループ内で変数宣言
    {
        if (arr[i] == target)
        {
            return i;
        }
    }
    
    return -1;  // 見つからなかった
}

// 配列を昇順にソートする関数（改良版バブルソート）
void sort_array(int arr[], int size)
{
    bool swapped;  // C99: bool型
    
    for (int i = 0; i < size - 1; i++)
    {
        swapped = false;
        
        for (int j = 0; j < size - 1 - i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(&arr[j], &arr[j + 1]);
                swapped = true;
            }
        }
        
        // 交換がなければソート済み
        if (!swapped)
        {
            break;
        }
    }
}

// 配列の要素を逆順にする関数
void reverse_array(int arr[], int size)
{
    for (int i = 0; i < size / 2; i++)  // C99: forループ内で変数宣言
    {
        swap(&arr[i], &arr[size - 1 - i]);
    }
}

// 配列の最大値と最小値を同時に求める関数
void find_min_max(const int arr[], int size, int *min, int *max)
{
    if (size <= 0 || min == NULL || max == NULL)
    {
        return;
    }
    
    *min = arr[0];
    *max = arr[0];
    
    for (int i = 1; i < size; i++)  // C99: forループ内で変数宣言
    {
        if (arr[i] < *min)
        {
            *min = arr[i];
        }
        if (arr[i] > *max)
        {
            *max = arr[i];
        }
    }
}

// 配列内の重複する要素の数を数える関数
int count_duplicates(const int arr[], int size)
{
    if (size <= 1)
    {
        return 0;
    }
    
    // カウント済みフラグ配列を作成
    bool *counted = (bool*)calloc(size, sizeof(bool));  // C99: bool型配列
    if (counted == NULL)
    {
        return -1;  // メモリ割り当てエラー
    }
    
    int count = 0;
    
    for (int i = 0; i < size - 1; i++)
    {
        if (counted[i])
        {
            continue;  // 既にカウント済み
        }
        
        int dup_count = 0;
        for (int j = i + 1; j < size; j++)
        {
            if (arr[i] == arr[j])
            {
                dup_count++;
                counted[j] = true;
            }
        }
        
        if (dup_count > 0)
        {
            count += dup_count;
        }
    }
    
    free(counted);
    return count;
}

// 配列がソート済みかチェックする関数（C99追加）
bool is_sorted(const int arr[], int size)
{
    if (size <= 1)
    {
        return true;
    }
    
    for (int i = 0; i < size - 1; i++)
    {
        if (arr[i] > arr[i + 1])
        {
            return false;
        }
    }
    
    return true;
}

// 2番目に大きい値を見つける関数（C99追加）
int find_second_max(const int arr[], int size)
{
    if (size < 2)
    {
        return -1;  // エラー
    }
    
    int max_idx = find_max_index(arr, size);
    int second_max = (max_idx == 0) ? arr[1] : arr[0];
    
    for (int i = 0; i < size; i++)
    {
        if (i != max_idx && arr[i] > second_max && arr[i] < arr[max_idx])
        {
            second_max = arr[i];
        }
    }
    
    return second_max;
}

// 配列を表示するヘルパー関数
void print_array(const int arr[], int size)
{
    printf("[");
    for (int i = 0; i < size; i++)  // C99: forループ内で変数宣言
    {
        printf("%d", arr[i]);
        if (i < size - 1)
        {
            printf(", ");
        }
    }
    printf("]\n");
}

// 2つの要素を交換するヘルパー関数
inline void swap(int *a, int *b)  // C99: inline関数
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// メイン関数 - テスト用
int main(void)
{
    int test_array[] = {5, 2, 8, 2, 9, 1, 5, 5, 3, 7};
    int size = sizeof(test_array) / sizeof(test_array[0]);
    
    printf("=== 配列操作関数のテスト（C99版） ===\n\n");
    
    // 元の配列を表示
    printf("元の配列: ");
    print_array(test_array, size);
    printf("\n");
    
    // 基本操作のテスト
    printf("=== 基本操作 ===\n");
    printf("合計: %d\n", array_sum(test_array, size));
    printf("平均: %.2f\n", array_average(test_array, size));
    
    int max_idx = find_max_index(test_array, size);
    printf("最大値のインデックス: %d (値: %d)\n", max_idx, test_array[max_idx]);
    printf("2番目に大きい値: %d\n", find_second_max(test_array, size));
    printf("\n");
    
    // 検索のテスト
    printf("=== 線形検索 ===\n");
    int targets[] = {8, 10, 5};  // C99: 配列初期化子
    
    for (int i = 0; i < 3; i++)
    {
        int result = linear_search(test_array, size, targets[i]);
        if (result != -1)
        {
            printf("%d はインデックス %d で見つかりました\n", targets[i], result);
        }
        else
        {
            printf("%d は見つかりませんでした\n", targets[i]);
        }
    }
    printf("\n");
    
    // 統計情報のテスト
    printf("=== 統計情報 ===\n");
    int min, max;
    find_min_max(test_array, size, &min, &max);
    printf("最小値: %d, 最大値: %d\n", min, max);
    printf("重複する要素の数: %d\n", count_duplicates(test_array, size));
    printf("\n");
    
    // C99: 可変長配列（VLA）を使用
    printf("=== 可変長配列を使ったテスト ===\n");
    int n = size;
    int work_array[n];  // C99: 可変長配列
    
    // 配列をコピー
    for (int i = 0; i < n; i++)
    {
        work_array[i] = test_array[i];
    }
    
    // ソートのテスト
    printf("ソート前: ");
    print_array(work_array, n);
    printf("ソート済み?: %s\n", is_sorted(work_array, n) ? "はい" : "いいえ");
    
    sort_array(work_array, n);
    
    printf("ソート後: ");
    print_array(work_array, n);
    printf("ソート済み?: %s\n", is_sorted(work_array, n) ? "はい" : "いいえ");
    printf("\n");
    
    // 逆順のテスト
    printf("=== 逆順 ===\n");
    reverse_array(work_array, n);
    printf("逆順後: ");
    print_array(work_array, n);
    printf("\n");
    
    // C99: 複合リテラルの使用
    printf("=== 複合リテラルのテスト ===\n");
    printf("即席配列の合計: %d\n", 
           array_sum((int[]){10, 20, 30, 40, 50}, 5));
    printf("即席配列の平均: %.2f\n", 
           array_average((int[]){1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 10));
    
    return 0;
}