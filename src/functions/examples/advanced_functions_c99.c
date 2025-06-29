/*
 * 高度な関数の使い方（C99版）
 * 
 * このプログラムは、再帰関数、ローカル変数とグローバル変数、
 * 配列を引数に取る関数の使い方を示します。
 * C99の機能：変数宣言位置の自由化、//コメント、可変長配列、inline関数
 */
#include <stdio.h>
#include <stdbool.h>

// グローバル変数
int global_counter = 0;

// 関数プロトタイプ
int factorial(int n);
int fibonacci(int n);
void display_array(const int arr[], int size);  // C99: const修飾子
int sum_array(const int arr[], int size);
double average_array(const int arr[], int size);
void increment_counter(void);
int local_vs_global_demo(int param);
void reverse_array(int arr[], int size);
inline int min(int a, int b);  // C99: inline関数
void process_variable_array(int size);  // C99: 可変長配列のデモ

// 階乗を計算する再帰関数
int factorial(int n)
{
    if (n <= 1) {
        return 1;  // 基底条件
    }
    return n * factorial(n - 1);  // 再帰呼び出し
}

// フィボナッチ数列を計算する再帰関数
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

// 配列を表示する関数（C99: const修飾子で読み取り専用を明示）
void display_array(const int arr[], int size)
{
    printf("配列の内容: ");
    for (int i = 0; i < size; i++) {  // C99: forループ内で変数宣言
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// 配列の合計を計算する関数
int sum_array(const int arr[], int size)
{
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

// 配列の平均を計算する関数
double average_array(const int arr[], int size)
{
    if (size == 0) {
        return 0.0;
    }
    return (double)sum_array(arr, size) / size;
}

// グローバルカウンタをインクリメントする関数
void increment_counter(void)
{
    global_counter++;
    printf("グローバルカウンタ: %d\n", global_counter);
}

// ローカル変数とグローバル変数のデモ
int local_vs_global_demo(int param)
{
    static int static_local = 0;  // 静的ローカル変数
    int local = 10;              // 通常のローカル変数
    
    local += param;
    static_local += param;
    global_counter += param;
    
    printf("パラメータ: %d\n", param);
    printf("ローカル変数: %d\n", local);
    printf("静的ローカル変数: %d\n", static_local);
    printf("グローバル変数: %d\n", global_counter);
    
    return local;
}

// 配列を逆順にする関数
void reverse_array(int arr[], int size)
{
    for (int i = 0; i < size / 2; i++) {  // C99: forループ内で変数宣言
        int temp = arr[i];
        arr[i] = arr[size - 1 - i];
        arr[size - 1 - i] = temp;
    }
}

// C99: inline関数（小さな関数の最適化）
inline int min(int a, int b)
{
    return (a < b) ? a : b;
}

// C99: 可変長配列を使った関数
void process_variable_array(int size)
{
    printf("\n=== 可変長配列のデモ (C99) ===\n");
    int vla[size];  // C99: 可変長配列
    
    // 配列を初期化
    for (int i = 0; i < size; i++) {
        vla[i] = i * i;
    }
    
    printf("サイズ%dの可変長配列を作成しました\n", size);
    display_array(vla, size);
}

int main(void)
{
    printf("=== 高度な関数の使い方 ===\n\n");
    
    // 1. 再帰関数のデモ
    printf("=== 再帰関数のデモ ===\n");
    
    // 階乗の計算
    printf("階乗の計算:\n");
    for (int n = 0; n <= 7; n++) {  // C99: forループ内で変数宣言
        printf("%d! = %d\n", n, factorial(n));
    }
    printf("\n");
    
    // フィボナッチ数列
    printf("フィボナッチ数列の最初の10項:\n");
    for (int n = 0; n < 10; n++) {
        printf("F(%d) = %d\n", n, fibonacci(n));
    }
    printf("\n");
    
    // 2. 配列を引数に取る関数
    printf("=== 配列を扱う関数 ===\n");
    int numbers[] = {3, 7, 2, 9, 1, 5, 8, 4, 6, 10};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    
    display_array(numbers, size);
    printf("合計: %d\n", sum_array(numbers, size));
    printf("平均: %.2f\n", average_array(numbers, size));
    
    // 最小値を見つける（inline関数の使用）
    int min_value = numbers[0];
    for (int i = 1; i < size; i++) {
        min_value = min(min_value, numbers[i]);
    }
    printf("最小値: %d\n", min_value);
    
    // 配列を逆順にする
    printf("\n配列を逆順にします:\n");
    reverse_array(numbers, size);
    display_array(numbers, size);
    printf("\n");
    
    // 3. ローカル変数とグローバル変数
    printf("=== 変数スコープのデモ ===\n");
    for (int i = 1; i <= 3; i++) {
        printf("\n呼び出し %d:\n", i);
        local_vs_global_demo(i);
    }
    printf("\n");
    
    // 4. グローバルカウンタの使用
    printf("=== グローバルカウンタ ===\n");
    for (int i = 0; i < 5; i++) {
        increment_counter();
    }
    printf("\n");
    
    // 5. 可変長配列のデモ（C99）
    process_variable_array(5);
    process_variable_array(8);
    
    // 6. 複合リテラル（C99）
    printf("\n=== 複合リテラルのデモ (C99) ===\n");
    display_array((int[]){1, 2, 3, 4, 5}, 5);  // C99: 複合リテラル
    
    return 0;
}