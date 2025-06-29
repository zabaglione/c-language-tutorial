/*
 * 高度な関数の使い方
 * 
 * このプログラムは、再帰関数、ローカル変数とグローバル変数、
 * 配列を引数に取る関数の使い方を示します。
 */
#include <stdio.h>

/* グローバル変数 */
int global_counter = 0;

/* 関数プロトタイプ */
int factorial(int n);
int fibonacci(int n);
void display_array(int arr[], int size);
int sum_array(int arr[], int size);
double average_array(int arr[], int size);
void increment_counter(void);
int local_vs_global_demo(int param);

/* 階乗を計算する再帰関数 */
int factorial(int n)
{
    if (n <= 1) {
        return 1;  /* 基底条件 */
    }
    return n * factorial(n - 1);  /* 再帰呼び出し */
}

/* フィボナッチ数列を計算する再帰関数 */
int fibonacci(int n)
{
    if (n <= 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

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

/* 配列の合計を計算する関数 */
int sum_array(int arr[], int size)
{
    int sum = 0;
    int i;
    
    for (i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

/* 配列の平均を計算する関数 */
double average_array(int arr[], int size)
{
    if (size == 0) {
        return 0.0;
    }
    return (double)sum_array(arr, size) / size;
}

/* グローバル変数を操作する関数 */
void increment_counter(void)
{
    global_counter++;
    printf("グローバルカウンター: %d\n", global_counter);
}

/* ローカル変数とグローバル変数のデモ */
int local_vs_global_demo(int param)
{
    int local_var = 10;  /* ローカル変数 */
    
    printf("  関数内 - ローカル変数: %d\n", local_var);
    printf("  関数内 - グローバル変数: %d\n", global_counter);
    printf("  関数内 - 引数: %d\n", param);
    
    local_var += param;
    global_counter += param;
    
    return local_var;
}

int main(void)
{
    int i;
    
    printf("=== 高度な関数の使用例 ===\n\n");
    
    /* 1. 再帰関数（階乗） */
    printf("=== 再帰関数: 階乗 ===\n");
    for (i = 0; i <= 7; i++) {
        printf("%d! = %d\n", i, factorial(i));
    }
    printf("\n");
    
    /* 2. 再帰関数（フィボナッチ数列） */
    printf("=== 再帰関数: フィボナッチ数列 ===\n");
    printf("最初の10個のフィボナッチ数: ");
    for (i = 0; i < 10; i++) {
        printf("%d ", fibonacci(i));
    }
    printf("\n\n");
    
    /* 3. 配列を引数に取る関数 */
    printf("=== 配列を引数に取る関数 ===\n");
    int numbers[] = {5, 12, 8, 23, 16, 9, 14, 7};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    
    display_array(numbers, size);
    printf("合計: %d\n", sum_array(numbers, size));
    printf("平均: %.2f\n", average_array(numbers, size));
    printf("\n");
    
    /* 4. ローカル変数とグローバル変数 */
    printf("=== ローカル変数とグローバル変数 ===\n");
    printf("初期状態のグローバル変数: %d\n", global_counter);
    
    printf("\n1回目の関数呼び出し:\n");
    int result1 = local_vs_global_demo(5);
    printf("  戻り値: %d\n", result1);
    
    printf("\n2回目の関数呼び出し:\n");
    int result2 = local_vs_global_demo(3);
    printf("  戻り値: %d\n", result2);
    
    printf("\n最終的なグローバル変数: %d\n\n", global_counter);
    
    /* 5. グローバル変数を操作する関数 */
    printf("=== グローバル変数の操作 ===\n");
    for (i = 0; i < 5; i++) {
        increment_counter();
    }
    printf("\n");
    
    /* 6. 関数の組み合わせ使用 */
    printf("=== 関数の組み合わせ使用 ===\n");
    
    /* 配列の各要素の階乗を計算 */
    int sumall_numbers[] = {1, 2, 3, 4, 5};
    int sumall_size = sizeof(sumall_numbers) / sizeof(sumall_numbers[0]);
    
    printf("元の配列: ");
    display_array(sumall_numbers, sumall_size);
    
    printf("各要素の階乗:\n");
    for (i = 0; i < sumall_size; i++) {
        printf("%d! = %d\n", sumall_numbers[i], factorial(sumall_numbers[i]));
    }
    printf("\n");
    
    /* 7. 再帰の深さの制限例 */
    printf("=== 再帰の制限例 ===\n");
    printf("大きな数での階乗計算:\n");
    for (i = 10; i <= 12; i++) {
        printf("%d! = %d\n", i, factorial(i));
    }
    printf("注意: 大きな数では整数オーバーフローが発生する可能性があります\n");
    
    return 0;
}