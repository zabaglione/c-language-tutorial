/*
 * 基本演算のデモ
 * 四則演算と型変換
 */
#include <stdio.h>

int main(void)
{
    int a = 10, b = 3;
    
    printf("=== 基本演算 ===\n");
    printf("a = %d, b = %d\n\n", a, b);
    
    /* 整数演算 */
    printf("整数演算:\n");
    printf("%d + %d = %d\n", a, b, a + b);
    printf("%d - %d = %d\n", a, b, a - b);
    printf("%d * %d = %d\n", a, b, a * b);
    printf("%d / %d = %d (整数除算)\n", a, b, a / b);
    printf("%d %% %d = %d (剰余)\n", a, b, a % b);
    
    /* 実数演算 */
    printf("\n実数演算:\n");
    printf("%.1f / %.1f = %.2f\n", (double)a, (double)b, (double)a / b);
    
    return 0;
}