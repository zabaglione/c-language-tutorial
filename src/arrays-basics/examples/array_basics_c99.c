/*
 * 配列の基本的な使い方（C99版）
 * 
 * このプログラムは、1次元配列の宣言、初期化、
 * 操作の基本的な方法を示します。
 * C99特有の機能：変数の混在宣言を使用
 */
#include <stdio.h>

#define MAX_SIZE 10

int main(void)
{
    /* 1. 配列の宣言と基本的な使用 */
    int numbers[5];
    int i;
    
    printf("=== 配列の基本的な使用 ===\n");
    
    /* 配列に値を代入 */
    for (i = 0; i < 5; i++) {
        numbers[i] = (i + 1) * 10;
    }
    
    /* 配列の内容を表示 */
    printf("配列の内容: ");
    for (i = 0; i < 5; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n\n");
    
    /* 2. 配列の初期化 */
    printf("=== 配列の初期化 ===\n");
    
    /* 完全な初期化（C99では必要な時に宣言可能） */
    int scores[5] = {85, 92, 78, 96, 88};
    printf("scores配列: ");
    for (i = 0; i < 5; i++) {
        printf("%d ", scores[i]);
    }
    printf("\n");
    
    /* 部分的な初期化 */
    int partial[10] = {1, 2, 3};  /* 残りは0で初期化 */
    printf("partial配列: ");
    for (i = 0; i < 10; i++) {
        printf("%d ", partial[i]);
    }
    printf("\n");
    
    /* サイズを省略した初期化 */
    int auto_size[] = {5, 10, 15, 20, 25, 30};
    int size = sizeof(auto_size) / sizeof(auto_size[0]);
    printf("auto_size配列（要素数%d）: ", size);
    for (i = 0; i < size; i++) {
        printf("%d ", auto_size[i]);
    }
    printf("\n\n");
    
    /* 3. 配列の統計計算 */
    printf("=== 配列の統計計算 ===\n");
    
    int test_scores[] = {75, 88, 92, 67, 85, 91, 78, 84, 90, 86};
    int n = sizeof(test_scores) / sizeof(test_scores[0]);
    int sum = 0;
    int max = test_scores[0];
    int min = test_scores[0];
    
    /* 合計、最大値、最小値を計算 */
    for (i = 0; i < n; i++) {
        sum += test_scores[i];
        if (test_scores[i] > max) {
            max = test_scores[i];
        }
        if (test_scores[i] < min) {
            min = test_scores[i];
        }
    }
    
    printf("テストの点数: ");
    for (i = 0; i < n; i++) {
        printf("%d ", test_scores[i]);
    }
    printf("\n");
    printf("要素数: %d\n", n);
    printf("合計: %d\n", sum);
    printf("平均: %.2f\n", (double)sum / n);
    printf("最高点: %d\n", max);
    printf("最低点: %d\n\n", min);
    
    /* 4. 配列の要素検索 */
    printf("=== 配列の検索 ===\n");
    
    int search_array[] = {15, 23, 8, 42, 16, 4, 11, 29, 36, 19};
    int search_value = 42;
    int found = 0;
    int position = -1;
    
    /* 線形探索 */
    for (i = 0; i < 10; i++) {
        if (search_array[i] == search_value) {
            found = 1;
            position = i;
            break;
        }
    }
    
    if (found) {
        printf("値 %d は位置 %d にあります\n", search_value, position);
    } else {
        printf("値 %d は見つかりませんでした\n", search_value);
    }
    printf("\n");
    
    /* 5. 配列の逆順表示 */
    printf("=== 配列の逆順表示 ===\n");
    
    int original[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    printf("元の配列: ");
    for (i = 0; i < 10; i++) {
        printf("%d ", original[i]);
    }
    printf("\n");
    
    printf("逆順: ");
    for (i = 9; i >= 0; i--) {
        printf("%d ", original[i]);
    }
    printf("\n\n");
    
    /* 6. 配列のコピー */
    printf("=== 配列のコピー ===\n");
    
    int source[5] = {11, 22, 33, 44, 55};
    int destination[5];
    
    /* 要素を1つずつコピー */
    for (i = 0; i < 5; i++) {
        destination[i] = source[i];
    }
    
    printf("source配列: ");
    for (i = 0; i < 5; i++) {
        printf("%d ", source[i]);
    }
    printf("\n");
    
    printf("destination配列: ");
    for (i = 0; i < 5; i++) {
        printf("%d ", destination[i]);
    }
    printf("\n\n");
    
    /* 7. 配列サイズの注意点 */
    printf("=== 配列サイズの情報 ===\n");
    
    int arr[MAX_SIZE];
    printf("配列のサイズ: %lu バイト\n", sizeof(arr));
    printf("要素1つのサイズ: %lu バイト\n", sizeof(arr[0]));
    printf("要素数: %lu\n", sizeof(arr) / sizeof(arr[0]));
    
    return 0;
}
