/*
 * operators_demo.c
 * さまざまな演算子の使用方法を学習
 * C90準拠
 */

#include <stdio.h>

int main(void) {
    int a = 10, b = 3;
    double x = 10.0, y = 3.0;
    int result;
    
    printf("===== 算術演算子のデモ =====\n");
    printf("整数演算 (a = %d, b = %d):\n", a, b);
    printf("  a + b = %d\n", a + b);
    printf("  a - b = %d\n", a - b);
    printf("  a * b = %d\n", a * b);
    printf("  a / b = %d (整数除算)\n", a / b);
    printf("  a %% b = %d (剰余)\n", a % b);
    
    printf("\n実数演算 (x = %.1f, y = %.1f):\n", x, y);
    printf("  x / y = %.2f (実数除算)\n", x / y);
    
    printf("\n===== 代入演算子のデモ =====\n");
    result = a;
    printf("result = %d\n", result);
    result += 5;
    printf("result += 5 -> %d\n", result);
    result -= 3;
    printf("result -= 3 -> %d\n", result);
    result *= 2;
    printf("result *= 2 -> %d\n", result);
    result /= 4;
    printf("result /= 4 -> %d\n", result);
    result %= 3;
    printf("result %%= 3 -> %d\n", result);
    
    printf("\n===== インクリメント・デクリメント演算子 =====\n");
    a = 5;
    printf("初期値: a = %d\n", a);
    printf("a++ = %d (後置インクリメント)\n", a++);
    printf("現在の a = %d\n", a);
    printf("++a = %d (前置インクリメント)\n", ++a);
    printf("現在の a = %d\n", a);
    
    a = 5;
    printf("\n初期値: a = %d\n", a);
    printf("a-- = %d (後置デクリメント)\n", a--);
    printf("現在の a = %d\n", a);
    printf("--a = %d (前置デクリメント)\n", --a);
    printf("現在の a = %d\n", a);
    
    printf("\n===== 関係演算子のデモ =====\n");
    a = 5; b = 3;
    printf("a = %d, b = %d のとき:\n", a, b);
    printf("  a == b : %d\n", a == b);
    printf("  a != b : %d\n", a != b);
    printf("  a < b  : %d\n", a < b);
    printf("  a <= b : %d\n", a <= b);
    printf("  a > b  : %d\n", a > b);
    printf("  a >= b : %d\n", a >= b);
    
    printf("\n===== 論理演算子のデモ =====\n");
    a = 1; b = 0;
    printf("a = %d (真), b = %d (偽) のとき:\n", a, b);
    printf("  a && b : %d\n", a && b);
    printf("  a || b : %d\n", a || b);
    printf("  !a     : %d\n", !a);
    printf("  !b     : %d\n", !b);
    
    /* 短絡評価のデモ */
    printf("\n短絡評価のデモ:\n");
    a = 0; b = 5;
    printf("a = %d, b = %d のとき:\n", a, b);
    if (a != 0 && b / a > 2) {
        printf("  条件は真です\n");
    } else {
        printf("  条件は偽です (a が 0 なので b/a は評価されない)\n");
    }
    
    printf("\n===== 条件演算子（三項演算子）のデモ =====\n");
    a = 10; b = 20;
    result = (a > b) ? a : b;
    printf("a = %d, b = %d のとき:\n", a, b);
    printf("  (a > b) ? a : b = %d (大きい方の値)\n", result);
    
    printf("\n===== sizeof演算子のデモ =====\n");
    printf("基本データ型のサイズ:\n");
    printf("  sizeof(char)   = %lu バイト\n", (unsigned long)sizeof(char));
    printf("  sizeof(short)  = %lu バイト\n", (unsigned long)sizeof(short));
    printf("  sizeof(int)    = %lu バイト\n", (unsigned long)sizeof(int));
    printf("  sizeof(long)   = %lu バイト\n", (unsigned long)sizeof(long));
    printf("  sizeof(float)  = %lu バイト\n", (unsigned long)sizeof(float));
    printf("  sizeof(double) = %lu バイト\n", (unsigned long)sizeof(double));
    
    return 0;
}
