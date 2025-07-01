/*
 * 基本的なif文のデモ
 * 単純な条件分岐
 */
#include <stdio.h>

int main(void)
{
    int temperature = 28;
    int score = 85;
    
    printf("=== 基本的なif文 ===\n");
    
    /* 単純なif文 */
    printf("気温: %d度\n", temperature);
    if (temperature > 25) {
        printf("暑いのでエアコンをつけます\n");
    }
    
    /* 条件が偽の場合 */
    printf("\n点数: %d点\n", score);
    if (score >= 90) {
        printf("優秀な成績です\n");
    }
    
    return 0;
}