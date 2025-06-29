/*
 * 演習 6-1: 配列の基本操作（C90準拠版）
 * 
 * 整数配列に対する各種操作（表示、最大値・最小値、
 * 平均値、逆順、検索）を行うプログラム
 */
#include <stdio.h>

#define ARRAY_SIZE 10

/* 配列を表示する関数 */
void display_array(int arr[], int size)
{
    int i;
    printf("配列の内容: ");
    for (i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

/* 最大値を見つける関数 */
int find_max(int arr[], int size)
{
    int max = arr[0];
    int i;
    
    for (i = 1; i < size; i++) {
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
    int i;
    
    for (i = 1; i < size; i++) {
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
    int i;
    
    for (i = 0; i < size; i++) {
        sum += arr[i];
    }
    return (double)sum / size;
}

/* 配列を逆順にする関数 */
void reverse_array(int arr[], int size)
{
    int temp;
    int i;
    
    for (i = 0; i < size / 2; i++) {
        temp = arr[i];
        arr[i] = arr[size - 1 - i];
        arr[size - 1 - i] = temp;
    }
}

/* 値を検索する関数 */
int search_value(int arr[], int size, int target)
{
    int i;
    
    for (i = 0; i < size; i++) {
        if (arr[i] == target) {
            return i;  /* 見つかった位置を返す */
        }
    }
    return -1;  /* 見つからなかった */
}

int main(void)
{
    /* C90では先頭で全ての変数を宣言 */
    int numbers[ARRAY_SIZE];
    int i;
    int search_target;
    int position;
    
    /* 配列に値を入力 */
    printf("=== 配列の基本操作プログラム ===\n");
    printf("%d個の整数を入力してください:\n", ARRAY_SIZE);
    
    for (i = 0; i < ARRAY_SIZE; i++) {
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
    scanf("%d", &search_target);
    
    position = search_value(numbers, ARRAY_SIZE, search_target);
    
    if (position != -1) {
        printf("値 %d は配列の %d 番目（インデックス %d）にあります。\n", 
               search_target, position + 1, position);
    } else {
        printf("値 %d は配列内に存在しません。\n", search_target);
    }
    
    return 0;
}