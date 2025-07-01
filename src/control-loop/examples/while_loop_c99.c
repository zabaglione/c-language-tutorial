/*
 * C99バージョン - 必要に応じてC99機能を使用
 *
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
    
    /*
 * C99バージョン - 必要に応じてC99機能を使用
 * 基本的なwhile文 */
    printf("1から5まで: ");
    while (count <= 5) {
        printf("%d ", count);
        count++;
    }
    printf("\n");
    
    /*
 * C99バージョン - 必要に応じてC99機能を使用
 * 累計計算 */
    printf("1から10までの合計: ");
    while (i <= 10) {
        sum += i;
        i++;
    }
    printf("%d\n", sum);
    
    return 0;
}