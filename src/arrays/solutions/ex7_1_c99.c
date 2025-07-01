/*
 * 演習 7-1: 配列の基本操作（C99版）
 * 
 * 整数配列に対する各種操作（表示、最大値・最小値、
 * 平均値、逆順、検索）を行うプログラム
 * C99特有の機能：変数の混在宣言を使用
 */
#include <stdio.h>

#define ARRAY_SIZE 10

/* 配列を表示する関数 */
void display_array(int arr[], int size)
{
    printf("配列の内容: ");
    for (int i = 0; i < size; i++) {  /* C99：forループ内で変数宣言 */
        printf("%d ", arr[i]);
    }
    printf("\n");
}

/* 最大値を見つける関数 */
int find_max(int arr[], int size)
{
    int max = arr[0];
    
    for (int i = 1; i < size; i++) {  /* C99：forループ内で変数宣言 */
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

/* 最小値を見つける関数 */
int find_min(int arr[], int size)
{
    int min = arr[0];
    
    for (int i = 1; i < size; i++) {  /* C99：forループ内で変数宣言 */
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    return min;
}

/* 平均値を計算する関数 */
double calculate_average(int arr[], int size)
{
    int sum = 0;
    
    for (int i = 0; i < size; i++) {  /* C99：forループ内で変数宣言 */
        sum += arr[i];
    }
    return (double)sum / size;
}

/* 配列を逆順にする関数 */
void reverse_array(int arr[], int size)
{
    for (int i = 0; i < size / 2; i++) {  /* C99：forループ内で変数宣言 */
        int temp = arr[i];  /* C99：必要な時に変数宣言 */
        arr[i] = arr[size - 1 - i];
        arr[size - 1 - i] = temp;
    }
}

/* 値を検索する関数 */
int search_value(int arr[], int size, int target)
{
    for (int i = 0; i < size; i++) {  /* C99：forループ内で変数宣言 */
        if (arr[i] == target) {
            return i;  /* 見つかった位置を返す */
        }
    }
    return -1;  /* 見つからなかった */
}

int main(void)
{
    int numbers[ARRAY_SIZE];
    
    /* 配列に値を入力 */
    printf("=== 配列の基本操作プログラム ===\n");
    printf("%d個の整数を入力してください:\n", ARRAY_SIZE);
    
    for (int i = 0; i < ARRAY_SIZE; i++) {  /* C99：forループ内で変数宣言 */
        printf("%d番目の数: ", i + 1);
        scanf("%d", &numbers[i]);
    }
    
    printf("\n");
    
    /* 1. 配列の表示 */
    display_array(numbers, ARRAY_SIZE);
    
    /* 2. 最大値と最小値 */
    printf("\n最大値: %d\n", find_max(numbers, ARRAY_SIZE));
    printf("最小値: %d\n", find_min(numbers, ARRAY_SIZE));
    
    /* 3. 平均値 */
    printf("平均値: %.2f\n", calculate_average(numbers, ARRAY_SIZE));
    
    /* 4. 逆順に並べ替え */
    printf("\n配列を逆順に並べ替えます...\n");
    reverse_array(numbers, ARRAY_SIZE);
    display_array(numbers, ARRAY_SIZE);
    
    /* 5. 値の検索 */
    printf("\n検索したい値を入力してください: ");
    int search_target;  /* C99：必要な時に変数宣言 */
    scanf("%d", &search_target);
    
    int position = search_value(numbers, ARRAY_SIZE, search_target);  /* C99：必要な時に変数宣言 */
    
    if (position != -1) {
        printf("値 %d は配列の %d 番目（インデックス %d）にあります。\n", 
               search_target, position + 1, position);
    } else {
        printf("値 %d は配列内に存在しません。\n", search_target);
    }
    
    return 0;
}