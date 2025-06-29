/*
 * if文の基本的な使い方（C99版）
 * 
 * このプログラムは、if文、if-else文、if-else if文の
 * 基本的な使い方を示します。
 * 規格: C99準拠
 */
#include <stdio.h>

int main(void)
{
    // 点数の入力
    printf("点数を入力してください (0-100): ");
    int score;
    scanf("%d", &score);
    
    // 単純なif文
    if (score == 100) {
        printf("満点です！素晴らしい！\n");
    }
    
    // if-else文
    if (score >= 60) {
        printf("合格です\n");
    } else {
        printf("不合格です\n");
    }
    
    // if-else if文による成績判定
    printf("成績評価: ");
    if (score >= 90) {
        printf("A (優秀)\n");
    } else if (score >= 80) {
        printf("B (良好)\n");
    } else if (score >= 70) {
        printf("C (普通)\n");
    } else if (score >= 60) {
        printf("D (可)\n");
    } else {
        printf("F (不可)\n");
    }
    
    // ネストしたif文
    if (score >= 60) {
        printf("おめでとうございます！");
        if (score >= 80) {
            printf("優秀な成績です！");
        }
        printf("\n");
    }
    
    return 0;
}