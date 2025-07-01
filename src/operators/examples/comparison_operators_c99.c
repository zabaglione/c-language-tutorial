/*
 * C99バージョン - 必要に応じてC99機能を使用
 *
 * 比較演算子のデモ
 * 各種比較演算子の使用方法
 */
#include <stdio.h>

int main(void)
{
    int a = 5, b = 3, c = 5;
    
    printf("=== 比較演算子 ===\n");
    printf("a = %d, b = %d, c = %d\n\n", a, b, c);
    
    printf("a == b: %d (等しい)\n", a == b);
    printf("a != b: %d (等しくない)\n", a != b);
    printf("a > b:  %d (より大きい)\n", a > b);
    printf("a < b:  %d (より小さい)\n", a < b);
    printf("a >= c: %d (以上)\n", a >= c);
    printf("a <= c: %d (以下)\n", a <= c);
    
    return 0;
}