/*
 * C99バージョン - 必要に応じてC99機能を使用
 *
 * 成績判定システム
 * if-else if文を使った多段階判定
 */
#include <stdio.h>

int main(void)
{
    int score = 85;
    
    printf("=== 成績判定システム ===\n");
    printf("点数: %d点\n", score);
    
    if (score >= 90) {
        printf("成績: A（優秀）\n");
        printf("素晴らしい成績です！\n");
    } else if (score >= 80) {
        printf("成績: B（良好）\n");
        printf("よく頑張りました！\n");
    } else if (score >= 70) {
        printf("成績: C（普通）\n");
        printf("合格です\n");
    } else if (score >= 60) {
        printf("成績: D（可）\n");
        printf("ギリギリ合格です\n");
    } else {
        printf("成績: F（不可）\n");
        printf("もう少し頑張りましょう\n");
    }
    
    return 0;
}