/*
 * while文のデモ
 * 条件による繰り返し処理
 */
#include <stdio.h>

int main(void)
{
    int count = 1;
    int sum = 0;
    int i = 1;
    
    printf("=== while文 ===\n");
    
    /* 基本的なwhile文 */
    printf("1から5まで: ");
    while (count <= 5) {
        printf("%d ", count);
        count++;
    }
    printf("\n");
    
    /* 累計計算 */
    printf("1から10までの合計: ");
    while (i <= 10) {
        sum += i;
        i++;
    }
    printf("%d\n", sum);
    
    return 0;
}