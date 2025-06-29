/*
 * チャレンジ問題 1: ソートアルゴリズムの実装と比較（C99版）
 * 
 * バブルソート、選択ソート、挿入ソートを実装し、
 * 実行時間と比較・交換回数を測定して性能を比較する
 * C99特有の機能：変数の混在宣言、forループ内変数宣言を使用
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define ARRAY_SIZE 1000
#define MAX_BAR_LENGTH 50

/* ソート統計情報の構造 */
typedef struct {
    long comparisons;
    long swaps;
    clock_t start_time;
    clock_t end_time;
} SortStats;

/* 配列をコピーする関数 */
void copy_array(int source[], int dest[], int size)
{
    for (int i = 0; i < size; i++) {  /* C99：forループ内変数宣言 */
        dest[i] = source[i];
    }
}

/* 配列をランダムな値で初期化する関数 */
void randomize_array(int arr[], int size)
{
    for (int i = 0; i < size; i++) {  /* C99：forループ内変数宣言 */
        arr[i] = rand() % 1000;
    }
}

/* 配列をソート済みの状態にする関数 */
void sorted_array(int arr[], int size)
{
    for (int i = 0; i < size; i++) {  /* C99：forループ内変数宣言 */
        arr[i] = i;
    }
}

/* 配列を逆順にする関数 */
void reverse_array(int arr[], int size)
{
    for (int i = 0; i < size; i++) {  /* C99：forループ内変数宣言 */
        arr[i] = size - i - 1;
    }
}

/* バブルソート */
void bubble_sort(int arr[], int size, SortStats* stats)
{
    stats->comparisons = 0;
    stats->swaps = 0;
    stats->start_time = clock();
    
    for (int i = 0; i < size - 1; i++) {  /* C99：forループ内変数宣言 */
        for (int j = 0; j < size - 1 - i; j++) {  /* C99：forループ内変数宣言 */
            stats->comparisons++;
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];  /* C99：必要な時に変数宣言 */
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                stats->swaps++;
            }
        }
    }
    
    stats->end_time = clock();
}

/* 選択ソート */
void selection_sort(int arr[], int size, SortStats* stats)
{
    stats->comparisons = 0;
    stats->swaps = 0;
    stats->start_time = clock();
    
    for (int i = 0; i < size - 1; i++) {  /* C99：forループ内変数宣言 */
        int min_idx = i;  /* C99：必要な時に変数宣言 */
        for (int j = i + 1; j < size; j++) {  /* C99：forループ内変数宣言 */
            stats->comparisons++;
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            int temp = arr[i];  /* C99：必要な時に変数宣言 */
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
            stats->swaps++;
        }
    }
    
    stats->end_time = clock();
}

/* 挿入ソート */
void insertion_sort(int arr[], int size, SortStats* stats)
{
    stats->comparisons = 0;
    stats->swaps = 0;
    stats->start_time = clock();
    
    for (int i = 1; i < size; i++) {  /* C99：forループ内変数宣言 */
        int key = arr[i];  /* C99：必要な時に変数宣言 */
        int j = i - 1;  /* C99：必要な時に変数宣言 */
        
        while (j >= 0 && arr[j] > key) {
            stats->comparisons++;
            arr[j + 1] = arr[j];
            stats->swaps++;
            j--;
        }
        if (j >= 0) {
            stats->comparisons++;  /* 最後の比較もカウント */
        }
        arr[j + 1] = key;
    }
    
    stats->end_time = clock();
}

/* 実行時間を計算する関数（ミリ秒） */
double calculate_time_ms(SortStats* stats)
{
    return ((double)(stats->end_time - stats->start_time)) / CLOCKS_PER_SEC * 1000.0;
}

/* 簡易グラフを表示する関数 */
void draw_bar_graph(const char* label, long value, long max_value)
{
    int bar_length = (max_value == 0) ? 0 : (int)((double)value / max_value * MAX_BAR_LENGTH);  /* C99：必要な時に変数宣言 */
    
    printf("%-15s [", label);
    for (int i = 0; i < bar_length; i++) {  /* C99：forループ内変数宣言 */
        printf("*");
    }
    for (int i = bar_length; i < MAX_BAR_LENGTH; i++) {  /* C99：forループ内変数宣言 */
        printf(" ");
    }
    printf("] %ld\n", value);
}

/* ソート結果を表示する関数 */
void display_results(const char* test_name, SortStats bubble, SortStats selection, SortStats insertion)
{
    printf("\n=== %s ===\n", test_name);
    
    /* 最大値を計算（グラフ表示用） */
    long max_comparisons = bubble.comparisons;  /* C99：必要な時に変数宣言 */
    if (selection.comparisons > max_comparisons) max_comparisons = selection.comparisons;
    if (insertion.comparisons > max_comparisons) max_comparisons = insertion.comparisons;
    
    long max_swaps = bubble.swaps;  /* C99：必要な時に変数宣言 */
    if (selection.swaps > max_swaps) max_swaps = selection.swaps;
    if (insertion.swaps > max_swaps) max_swaps = insertion.swaps;
    
    double max_time = calculate_time_ms(&bubble);  /* C99：必要な時に変数宣言 */
    if (calculate_time_ms(&selection) > max_time) max_time = calculate_time_ms(&selection);
    if (calculate_time_ms(&insertion) > max_time) max_time = calculate_time_ms(&insertion);
    
    /* 比較回数のグラフ */
    printf("\n--- 比較回数 ---\n");
    draw_bar_graph("Bubble", bubble.comparisons, max_comparisons);
    draw_bar_graph("Selection", selection.comparisons, max_comparisons);
    draw_bar_graph("Insertion", insertion.comparisons, max_comparisons);
    
    /* 交換回数のグラフ */
    printf("\n--- 交換回数 ---\n");
    draw_bar_graph("Bubble", bubble.swaps, max_swaps);
    draw_bar_graph("Selection", selection.swaps, max_swaps);
    draw_bar_graph("Insertion", insertion.swaps, max_swaps);
    
    /* 実行時間の詳細 */
    printf("\n--- 実行時間 ---\n");
    printf("Bubble Sort:    %.3f ms\n", calculate_time_ms(&bubble));
    printf("Selection Sort: %.3f ms\n", calculate_time_ms(&selection));
    printf("Insertion Sort: %.3f ms\n", calculate_time_ms(&insertion));
}

int main(void)
{
    /* 乱数の種を設定 */
    srand((unsigned int)time(NULL));
    
    printf("=== ソートアルゴリズム性能比較プログラム ===\n");
    printf("配列サイズ: %d\n", ARRAY_SIZE);
    
    int original_array[ARRAY_SIZE];  /* C99：必要な時に変数宣言 */
    int test_array[ARRAY_SIZE];  /* C99：必要な時に変数宣言 */
    
    /* テスト1: ランダム配列 */
    randomize_array(original_array, ARRAY_SIZE);
    
    SortStats bubble_stats, selection_stats, insertion_stats;  /* C99：必要な時に変数宣言 */
    
    copy_array(original_array, test_array, ARRAY_SIZE);
    bubble_sort(test_array, ARRAY_SIZE, &bubble_stats);
    
    copy_array(original_array, test_array, ARRAY_SIZE);
    selection_sort(test_array, ARRAY_SIZE, &selection_stats);
    
    copy_array(original_array, test_array, ARRAY_SIZE);
    insertion_sort(test_array, ARRAY_SIZE, &insertion_stats);
    
    display_results("ランダム配列", bubble_stats, selection_stats, insertion_stats);
    
    /* テスト2: ソート済み配列 */
    sorted_array(original_array, ARRAY_SIZE);
    
    copy_array(original_array, test_array, ARRAY_SIZE);
    bubble_sort(test_array, ARRAY_SIZE, &bubble_stats);
    
    copy_array(original_array, test_array, ARRAY_SIZE);
    selection_sort(test_array, ARRAY_SIZE, &selection_stats);
    
    copy_array(original_array, test_array, ARRAY_SIZE);
    insertion_sort(test_array, ARRAY_SIZE, &insertion_stats);
    
    display_results("ソート済み配列", bubble_stats, selection_stats, insertion_stats);
    
    /* テスト3: 逆順配列 */
    reverse_array(original_array, ARRAY_SIZE);
    
    copy_array(original_array, test_array, ARRAY_SIZE);
    bubble_sort(test_array, ARRAY_SIZE, &bubble_stats);
    
    copy_array(original_array, test_array, ARRAY_SIZE);
    selection_sort(test_array, ARRAY_SIZE, &selection_stats);
    
    copy_array(original_array, test_array, ARRAY_SIZE);
    insertion_sort(test_array, ARRAY_SIZE, &insertion_stats);
    
    display_results("逆順配列", bubble_stats, selection_stats, insertion_stats);
    
    printf("\n=== まとめ ===\n");
    printf("一般的に：\n");
    printf("- 挿入ソート：少ないデータやほぼソート済みデータに効率的\n");
    printf("- 選択ソート：交換回数が少ない\n");
    printf("- バブルソート：理解しやすいが効率は劣る\n");
    
    return 0;
}