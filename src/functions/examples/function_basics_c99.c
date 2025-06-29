/*
 * 関数の基本的な使い方（C99版）
 * 
 * このプログラムは、関数の定義、呼び出し、
 * 引数と戻り値の基本的な使い方を示します。
 * C99の機能：変数宣言位置の自由化、//コメント、bool型
 */
#include <stdio.h>
#include <stdbool.h>

// 関数プロトタイプ宣言
int add(int a, int b);
int subtract(int a, int b);
int multiply(int a, int b);
double divide(int a, int b);
void print_message(void);
void print_number(int num);
int square(int n);
int max(int a, int b);
bool is_even(int n);  // C99: bool型を使用

// 2つの数の加算
int add(int a, int b)
{
    return a + b;
}

// 2つの数の減算
int subtract(int a, int b)
{
    return a - b;
}

// 2つの数の乗算
int multiply(int a, int b)
{
    return a * b;
}

// 2つの数の除算（浮動小数点で返す）
double divide(int a, int b)
{
    if (b == 0) {
        printf("エラー: ゼロで割ることはできません\n");
        return 0.0;
    }
    return (double)a / b;
}

// 戻り値なし、引数なしの関数
void print_message(void)
{
    printf("これは関数から出力されたメッセージです\n");
}

// 戻り値なし、引数ありの関数
void print_number(int num)
{
    printf("数値: %d\n", num);
}

// 数の平方を計算
int square(int n)
{
    return n * n;
}

// 2つの数の最大値を返す
int max(int a, int b)
{
    return (a > b) ? a : b;  // C99: 三項演算子を使用
}

// 偶数判定（C99: bool型を返す）
bool is_even(int n)
{
    return n % 2 == 0;
}

int main(void)
{
    // C99: 変数宣言を使用箇所で行える
    printf("=== 関数の基本操作 ===\n");
    
    int x = 15;
    int y = 7;
    printf("x = %d, y = %d\n\n", x, y);
    
    // 1. 基本的な算術関数
    printf("=== 基本的な算術関数 ===\n");
    int result = add(x, y);  // C99: 使用時に変数宣言
    printf("%d + %d = %d\n", x, y, result);
    
    result = subtract(x, y);
    printf("%d - %d = %d\n", x, y, result);
    
    result = multiply(x, y);
    printf("%d x %d = %d\n", x, y, result);
    
    double dresult = divide(x, y);  // C99: 使用時に変数宣言
    printf("%d / %d = %.2f\n", x, y, dresult);
    printf("\n");
    
    // 2. void関数の使用
    printf("=== void関数の使用 ===\n");
    print_message();
    print_number(42);
    print_number(x + y);
    printf("\n");
    
    // 3. 関数の戻り値を直接使用
    printf("=== 関数の戻り値を直接使用 ===\n");
    printf("%d の平方は %d です\n", x, square(x));
    printf("%d と %d の最大値は %d です\n", x, y, max(x, y));
    
    // 関数呼び出しをネスト
    printf("(%d + %d) の平方は %d です\n", x, y, square(add(x, y)));
    
    // C99: bool型の使用
    printf("%d は%s数です\n", x, is_even(x) ? "偶" : "奇");
    printf("%d は%s数です\n", y, is_even(y) ? "偶" : "奇");
    printf("\n");
    
    // 4. 関数を使った計算の例
    printf("=== 複雑な計算例 ===\n");
    
    // 三角形の面積計算（底辺 x 高さ / 2）
    int base = 10;
    int height = 8;
    double area = divide(multiply(base, height), 2);
    printf("底辺%d、高さ%dの三角形の面積: %.1f\n", base, height, area);
    
    // 円の面積の近似計算
    int radius = 5;
    const double pi = 3.14159;  // C99: const修飾子
    double circle_area = pi * square(radius);
    printf("半径%dの円の面積（近似）: %.2f\n", radius, circle_area);
    printf("\n");
    
    // 5. デモ用の固定値を使った関数
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
    
    // C99: forループ内での変数宣言
    printf("\n最初の10個の平方数: ");
    for (int i = 1; i <= 10; i++) {
        printf("%d ", square(i));
    }
    printf("\n");
    
    return 0;
}