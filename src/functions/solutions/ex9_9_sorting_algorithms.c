/*
 * ファイル名: ex9_9_sorting_algorithms.c
 * 演習9-9: ソートアルゴリズム関数
 * 説明: 各種ソートアルゴリズムの実装（バブル、選択、挿入、マージソート等）
 * 規格: C90準拠
 */
#include <stdio.h>

/* 関数プロトタイプ */
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

/* バブルソート */
void bubble_sort(int arr[], int size)
{
    int i, j, temp;
    int swapped;
    
    for (i = 0; i < size - 1; i++)
    {
        swapped = 0;
        for (j = 0; j < size - 1 - i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                /* 要素を交換 */
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }
        /* 交換が発生しなかった場合、ソート完了 */
        if (!swapped) break;
    }
}

/* 選択ソート */
void selection_sort(int arr[], int size)
{
    int i, j, min_idx, temp;
    
    for (i = 0; i < size - 1; i++)
    {
        min_idx = i;
        for (j = i + 1; j < size; j++)
        {
            if (arr[j] < arr[min_idx])
            {
                min_idx = j;
            }
        }
        
        /* 最小値を先頭に移動 */
        if (min_idx != i)
        {
            temp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
        }
    }
}

/* 挿入ソート */
void insertion_sort(int arr[], int size)
{
    int i, j, key;
    
    for (i = 1; i < size; i++)
    {
        key = arr[i];
        j = i - 1;
        
        /* key より大きい要素を後ろに移動 */
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

/* マージソート用のマージ関数 */
void merge(int arr[], int left, int mid, int right)
{
    int left_arr[1000]; /* 左の部分配列 */
    int right_arr[1000]; /* 右の部分配列 */
    int left_size = mid - left + 1;
    int right_size = right - mid;
    int i, j, k;
    
    /* 左の部分配列をコピー */
    for (i = 0; i < left_size; i++)
    {
        left_arr[i] = arr[left + i];
    }
    
    /* 右の部分配列をコピー */
    for (j = 0; j < right_size; j++)
    {
        right_arr[j] = arr[mid + 1 + j];
    }
    
    /* マージ処理 */
    i = 0; j = 0; k = left;
    while (i < left_size && j < right_size)
    {
        if (left_arr[i] <= right_arr[j])
        {
            arr[k] = left_arr[i];
            i++;
        }
        else
        {
            arr[k] = right_arr[j];
            j++;
        }
        k++;
    }
    
    /* 残りの要素をコピー */
    while (i < left_size)
    {
        arr[k] = left_arr[i];
        i++;
        k++;
    }
    
    while (j < right_size)
    {
        arr[k] = right_arr[j];
        j++;
        k++;
    }
}

/* マージソート */
void merge_sort(int arr[], int left, int right)
{
    int mid;
    
    if (left < right)
    {
        mid = left + (right - left) / 2;
        
        /* 左半分をソート */
        merge_sort(arr, left, mid);
        
        /* 右半分をソート */
        merge_sort(arr, mid + 1, right);
        
        /* マージ */
        merge(arr, left, mid, right);
    }
}

/* クイックソート用の分割関数 */
int partition(int arr[], int left, int right)
{
    int pivot = arr[right]; /* 最後の要素をピボットとする */
    int i = left - 1;
    int j, temp;
    
    for (j = left; j <= right - 1; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    
    temp = arr[i + 1];
    arr[i + 1] = arr[right];
    arr[right] = temp;
    
    return i + 1;
}

/* クイックソート */
void quick_sort(int arr[], int left, int right)
{
    int pivot_index;
    
    if (left < right)
    {
        pivot_index = partition(arr, left, right);
        
        /* ピボットの左側をソート */
        quick_sort(arr, left, pivot_index - 1);
        
        /* ピボットの右側をソート */
        quick_sort(arr, pivot_index + 1, right);
    }
}

/* 文字列配列のソート（バブルソート版） */
void sort_strings(char strings[][100], int count)
{
    int i, j, k;
    char temp[100];
    int compare_result;
    
    for (i = 0; i < count - 1; i++)
    {
        for (j = 0; j < count - 1 - i; j++)
        {
            /* 文字列比較 */
            compare_result = 0;
            for (k = 0; strings[j][k] != '\0' && strings[j + 1][k] != '\0'; k++)
            {
                if (strings[j][k] < strings[j + 1][k])
                {
                    compare_result = -1;
                    break;
                }
                else if (strings[j][k] > strings[j + 1][k])
                {
                    compare_result = 1;
                    break;
                }
            }
            
            if (compare_result == 0)
            {
                if (strings[j][k] != '\0') compare_result = 1;
                else if (strings[j + 1][k] != '\0') compare_result = -1;
            }
            
            if (compare_result > 0)
            {
                /* 文字列を交換 */
                for (k = 0; strings[j][k] != '\0'; k++)
                {
                    temp[k] = strings[j][k];
                }
                temp[k] = '\0';
                
                for (k = 0; strings[j + 1][k] != '\0'; k++)
                {
                    strings[j][k] = strings[j + 1][k];
                }
                strings[j][k] = '\0';
                
                for (k = 0; temp[k] != '\0'; k++)
                {
                    strings[j + 1][k] = temp[k];
                }
                strings[j + 1][k] = '\0';
            }
        }
    }
}

/* 配列を表示する関数 */
void print_array(int arr[], int size)
{
    int i;
    printf("[");
    for (i = 0; i < size; i++)
    {
        printf("%d", arr[i]);
        if (i < size - 1) printf(", ");
    }
    printf("]");
}

/* 配列をコピーする関数 */
void copy_array(int dest[], int src[], int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        dest[i] = src[i];
    }
}

int main(void)
{
    printf("=== ソートアルゴリズムのデモ ===\n\n");

    /* テスト用データ */
    int original_data[] = {64, 34, 25, 12, 22, 11, 90, 88, 76, 50};
    int data_size = sizeof(original_data) / sizeof(original_data[0]);
    int test_data[20];
    int i;

    printf("元のデータ: ");
    print_array(original_data, data_size);
    printf("\n\n");

    /* 1. バブルソート */
    printf("1. バブルソート\n");
    copy_array(test_data, original_data, data_size);
    printf("   ソート前: ");
    print_array(test_data, data_size);
    printf("\n");
    bubble_sort(test_data, data_size);
    printf("   ソート後: ");
    print_array(test_data, data_size);
    printf("\n\n");

    /* 2. 選択ソート */
    printf("2. 選択ソート\n");
    copy_array(test_data, original_data, data_size);
    printf("   ソート前: ");
    print_array(test_data, data_size);
    printf("\n");
    selection_sort(test_data, data_size);
    printf("   ソート後: ");
    print_array(test_data, data_size);
    printf("\n\n");

    /* 3. 挿入ソート */
    printf("3. 挿入ソート\n");
    copy_array(test_data, original_data, data_size);
    printf("   ソート前: ");
    print_array(test_data, data_size);
    printf("\n");
    insertion_sort(test_data, data_size);
    printf("   ソート後: ");
    print_array(test_data, data_size);
    printf("\n\n");

    /* 4. マージソート */
    printf("4. マージソート\n");
    copy_array(test_data, original_data, data_size);
    printf("   ソート前: ");
    print_array(test_data, data_size);
    printf("\n");
    merge_sort(test_data, 0, data_size - 1);
    printf("   ソート後: ");
    print_array(test_data, data_size);
    printf("\n\n");

    /* 5. クイックソート */
    printf("5. クイックソート\n");
    copy_array(test_data, original_data, data_size);
    printf("   ソート前: ");
    print_array(test_data, data_size);
    printf("\n");
    quick_sort(test_data, 0, data_size - 1);
    printf("   ソート後: ");
    print_array(test_data, data_size);
    printf("\n\n");

    /* 6. 文字列ソート */
    printf("6. 文字列ソート\n");
    char fruits[][100] = {"orange", "apple", "banana", "grape", "cherry"};
    int fruit_count = 5;
    
    printf("   ソート前: ");
    for (i = 0; i < fruit_count; i++)
    {
        printf("%s", fruits[i]);
        if (i < fruit_count - 1) printf(", ");
    }
    printf("\n");
    
    sort_strings(fruits, fruit_count);
    
    printf("   ソート後: ");
    for (i = 0; i < fruit_count; i++)
    {
        printf("%s", fruits[i]);
        if (i < fruit_count - 1) printf(", ");
    }
    printf("\n\n");

    /* 7. 性能比較用のより大きなデータセット */
    printf("7. 大きなデータセットでのテスト\n");
    int large_data[50];
    int large_size = 50;
    
    /* テストデータを生成（擬似ランダム） */
    printf("   生成されたデータ（最初の20個）: ");
    for (i = 0; i < large_size; i++)
    {
        large_data[i] = (i * 17 + 23) % 100; /* 簡単な擬似ランダム */
        if (i < 20)
        {
            printf("%d", large_data[i]);
            if (i < 19) printf(", ");
        }
    }
    printf("...\n");
    
    /* 挿入ソートでソート */
    insertion_sort(large_data, large_size);
    
    printf("   ソート後（最初の20個）: ");
    for (i = 0; i < 20; i++)
    {
        printf("%d", large_data[i]);
        if (i < 19) printf(", ");
    }
    printf("...\n\n");

    printf("=== ソートアルゴリズムデモ完了 ===\n");
    return 0;
}

/*
学習ポイント:
1. 基本的なソートアルゴリズムの理解と実装
2. 各アルゴリズムの時間計算量の違い
3. 分割統治法（マージソート、クイックソート）
4. 文字列ソートの実装方法
5. アルゴリズムの選択基準

実装のポイント:
- C90準拠のため、変数は関数先頭で宣言
- 各ソートの特徴を活かした実装
- 効率性と可読性のバランス
- メモリ使用量の考慮
*/