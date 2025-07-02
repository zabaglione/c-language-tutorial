/*
 * 演習11-2: 配列操作関数 - 解答例
 * 
 * 配列に対する各種操作を行う関数群を実装します。
 */
#include <stdio.h>
#include <stdlib.h>  /* calloc, free用 */

/* 関数プロトタイプ */
/* 基本操作 */
int array_sum(int arr[], int size);
double array_average(int arr[], int size);
int find_max_index(int arr[], int size);

/* 検索・ソート */
int linear_search(int arr[], int size, int target);
void sort_array(int arr[], int size);
void reverse_array(int arr[], int size);

/* 配列統計 */
void find_min_max(int arr[], int size, int *min, int *max);
int count_duplicates(int arr[], int size);

/* ヘルパー関数 */
void print_array(int arr[], int size);
void swap(int *a, int *b);

/* 配列の要素の合計を計算する関数 */
int array_sum(int arr[], int size)
{
    int sum = 0;
    int i;
    
    for (i = 0; i < size; i++)
    {
        sum += arr[i];
    }
    
    return sum;
}

/* 配列の平均値を計算する関数 */
double array_average(int arr[], int size)
{
    if (size == 0)
    {
        return 0.0;
    }
    
    return (double)array_sum(arr, size) / size;
}

/* 配列内の最大値のインデックスを返す関数 */
int find_max_index(int arr[], int size)
{
    int max_index = 0;
    int i;
    
    if (size <= 0)
    {
        return -1;  /* エラー */
    }
    
    for (i = 1; i < size; i++)
    {
        if (arr[i] > arr[max_index])
        {
            max_index = i;
        }
    }
    
    return max_index;
}

/* 線形検索関数（見つかったらインデックス、見つからなければ-1を返す） */
int linear_search(int arr[], int size, int target)
{
    int i;
    
    for (i = 0; i < size; i++)
    {
        if (arr[i] == target)
        {
            return i;
        }
    }
    
    return -1;  /* 見つからなかった */
}

/* 配列を昇順にソートする関数（バブルソート） */
void sort_array(int arr[], int size)
{
    int i, j;
    
    for (i = 0; i < size - 1; i++)
    {
        for (j = 0; j < size - 1 - i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

/* 配列の要素を逆順にする関数 */
void reverse_array(int arr[], int size)
{
    int i;
    
    for (i = 0; i < size / 2; i++)
    {
        swap(&arr[i], &arr[size - 1 - i]);
    }
}

/* 配列の最大値と最小値を同時に求める関数 */
void find_min_max(int arr[], int size, int *min, int *max)
{
    int i;
    
    if (size <= 0 || min == NULL || max == NULL)
    {
        return;
    }
    
    *min = arr[0];
    *max = arr[0];
    
    for (i = 1; i < size; i++)
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

/* 配列内の重複する要素の数を数える関数 */
int count_duplicates(int arr[], int size)
{
    int count = 0;
    int i, j;
    int *counted;
    
    if (size <= 1)
    {
        return 0;
    }
    
    /* カウント済みフラグ配列を作成 */
    counted = (int*)calloc(size, sizeof(int));
    if (counted == NULL)
    {
        return -1;  /* メモリ割り当てエラー */
    }
    
    for (i = 0; i < size - 1; i++)
    {
        if (counted[i])
        {
            continue;  /* 既にカウント済み */
        }
        
        int dup_count = 0;
        for (j = i + 1; j < size; j++)
        {
            if (arr[i] == arr[j])
            {
                dup_count++;
                counted[j] = 1;
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

/* 配列を表示するヘルパー関数 */
void print_array(int arr[], int size)
{
    int i;
    
    printf("[");
    for (i = 0; i < size; i++)
    {
        printf("%d", arr[i]);
        if (i < size - 1)
        {
            printf(", ");
        }
    }
    printf("]\n");
}

/* 2つの要素を交換するヘルパー関数 */
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* メイン関数 - テスト用 */
int main(void)
{
    int test_array[] = {5, 2, 8, 2, 9, 1, 5, 5, 3, 7};
    int size = sizeof(test_array) / sizeof(test_array[0]);
    int min, max;
    int search_target;
    int result;
    
    printf("=== 配列操作関数のテスト ===\n\n");
    
    /* 元の配列を表示 */
    printf("元の配列: ");
    print_array(test_array, size);
    printf("\n");
    
    /* 基本操作のテスト */
    printf("=== 基本操作 ===\n");
    printf("合計: %d\n", array_sum(test_array, size));
    printf("平均: %.2f\n", array_average(test_array, size));
    printf("最大値のインデックス: %d (値: %d)\n", 
           find_max_index(test_array, size), 
           test_array[find_max_index(test_array, size)]);
    printf("\n");
    
    /* 検索のテスト */
    printf("=== 線形検索 ===\n");
    search_target = 8;
    result = linear_search(test_array, size, search_target);
    if (result != -1)
    {
        printf("%d はインデックス %d で見つかりました\n", search_target, result);
    }
    else
    {
        printf("%d は見つかりませんでした\n", search_target);
    }
    
    search_target = 10;
    result = linear_search(test_array, size, search_target);
    if (result != -1)
    {
        printf("%d はインデックス %d で見つかりました\n", search_target, result);
    }
    else
    {
        printf("%d は見つかりませんでした\n", search_target);
    }
    printf("\n");
    
    /* 統計情報のテスト */
    printf("=== 統計情報 ===\n");
    find_min_max(test_array, size, &min, &max);
    printf("最小値: %d, 最大値: %d\n", min, max);
    printf("重複する要素の数: %d\n", count_duplicates(test_array, size));
    printf("\n");
    
    /* 配列のコピーを作成（ソート・逆順用） */
    int work_array[10];
    int i;
    for (i = 0; i < size; i++)
    {
        work_array[i] = test_array[i];
    }
    
    /* ソートのテスト */
    printf("=== ソート ===\n");
    printf("ソート前: ");
    print_array(work_array, size);
    sort_array(work_array, size);
    printf("ソート後: ");
    print_array(work_array, size);
    printf("\n");
    
    /* 逆順のテスト */
    printf("=== 逆順 ===\n");
    for (i = 0; i < size; i++)
    {
        work_array[i] = test_array[i];
    }
    printf("逆順前: ");
    print_array(work_array, size);
    reverse_array(work_array, size);
    printf("逆順後: ");
    print_array(work_array, size);
    printf("\n");
    
    /* エッジケースのテスト */
    printf("=== エッジケースのテスト ===\n");
    int empty_array[1];
    int single_element[] = {42};
    
    printf("空配列の平均: %.2f\n", array_average(empty_array, 0));
    printf("単一要素配列の最大値インデックス: %d\n", 
           find_max_index(single_element, 1));
    printf("単一要素配列の重複数: %d\n", 
           count_duplicates(single_element, 1));
    
    return 0;
}