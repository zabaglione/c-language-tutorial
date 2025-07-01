/*
 * ネストしたループのデモ
 * 二重ループによるパターン出力
 */
#include <stdio.h>

int main(void)
{
    int i, j;
    
    printf("=== ネストしたループ ===\n");
    
    /* 九九の表（3x3） */
    printf("3x3の九九:\n");
    for (i = 1; i <= 3; i++) {
        for (j = 1; j <= 3; j++) {
            printf("%2d ", i * j);
        }
        printf("\n");
    }
    
    /* 三角形パターン */
    printf("\n三角形パターン:\n");
    for (i = 1; i <= 5; i++) {
        for (j = 1; j <= i; j++) {
            printf("* ");
        }
        printf("\n");
    }
    
    return 0;
}