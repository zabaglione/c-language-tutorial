/*
 * 関数の基本的な使い方
 * 
 * このプログラムは、関数の定義、呼び出し、
 * 引数と戻り値の基本的な使い方を示します。
 */
#include <stdio.h>

/* 関数プロトタイプ宣言 */
int add(int a, int b);
int subtract(int a, int b);
int multiply(int a, int b);
double divide(int a, int b);
void print_message(void);
void print_number(int num);
int square(int n);
int max(int a, int b);

/* 2つの数の加算 */
int add(int a, int b)
{
    return a + b;
}

/* 2つの数の減算 */
int subtract(int a, int b)
{
    return a - b;
}

/* 2つの数の乗算 */
int multiply(int a, int b)
{
    return a * b;
}

/* 2つの数の除算（浮動小数点で返す） */
double divide(int a, int b)
{
    if (b == 0) {
        printf("エラー: ゼロで割ることはできません\n");
        return 0.0;
    }
    return (double)a / b;
}

/* 戻り値なし、引数なしの関数 */
void print_message(void)
{
    printf("これは関数から出力されたメッセージです\n");
}

/* 戻り値なし、引数ありの関数 */
void print_number(int num)
{
    printf("数値: %d\n", num);
}

/* 数の平方を計算 */
int square(int n)
{
    return n * n;
}

/* 2つの数の最大値を返す */
int max(int a, int b)
{
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

int main(void)
{
    int x = 15;
    int y = 7;
    int result;
    double dresult;
    
    printf("=== 関数の基本操作 ===\n");
    printf("x = %d, y = %d\n\n", x, y);
    
    /* 1. 基本的な算術関数 */
    printf("=== 基本的な算術関数 ===\n");
    result = add(x, y);
    printf("%d + %d = %d\n", x, y, result);
    
    result = subtract(x, y);
    printf("%d - %d = %d\n", x, y, result);
    
    result = multiply(x, y);
    printf("%d x %d = %d\n", x, y, result);
    
    dresult = divide(x, y);
    printf("%d / %d = %.2f\n", x, y, dresult);
    printf("\n");
    
    /* 2. void関数の使用 */
    printf("=== void関数の使用 ===\n");
    print_message();
    print_number(42);
    print_number(x + y);
    printf("\n");
    
    /* 3. 関数の戻り値を直接使用 */
    printf("=== 関数の戻り値を直接使用 ===\n");
    printf("%d の平方は %d です\n", x, square(x));
    printf("%d と %d の最大値は %d です\n", x, y, max(x, y));
    
    /* 関数呼び出しをネスト */
    printf("(%d + %d) の平方は %d です\n", x, y, square(add(x, y)));
    printf("\n");
    
    /* 4. 関数を使った計算の例 */
    printf("=== 複雑な計算例 ===\n");
    {
        /* 三角形の面積計算（底辺 x 高さ / 2） */
        int base = 10;
        int height = 8;
        double area = divide(multiply(base, height), 2);
        printf("底辺%d、高さ%dの三角形の面積: %.1f\n", base, height, area);
        
        /* 円の面積の近似計算 */
        int radius = 5;
        double pi = 3.14159;
        double circle_area = pi * square(radius);
        printf("半径%dの円の面積（近似）: %.2f\n", radius, circle_area);
        printf("\n");
    }
    
    /* 5. デモ用の固定値を使った関数 */
    printf("=== デモ用固定値での関数使用 ===\n");
    int num1 = 15, num2 = 4;
    
    printf("使用する値: %d と %d\n", num1, num2);
    
    printf("\n計算結果:\n");
    printf("%d + %d = %d\n", num1, num2, add(num1, num2));
    printf("%d - %d = %d\n", num1, num2, subtract(num1, num2));
    printf("%d x %d = %d\n", num1, num2, multiply(num1, num2));
    
    if (num2 != 0) {
        printf("%d / %d = %.2f\n", num1, num2, divide(num1, num2));
    }
    
    printf("最大値: %d\n", max(num1, num2));
    
    return 0;
}
