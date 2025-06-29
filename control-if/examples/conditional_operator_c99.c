/*
 * 条件演算子（三項演算子）の使い方（C99版）
 * 
 * このプログラムは、条件演算子を使った
 * 簡潔な条件分岐の書き方を示します。
 * 規格: C99準拠
 */
#include <stdio.h>

int main(void)
{
    // 2つの数の最大値・最小値を求める
    printf("2つの整数を入力してください: ");
    int a, b;
    scanf("%d %d", &a, &b);
    
    // 条件演算子を使った最大値・最小値の判定
    int max = (a > b) ? a : b;
    int min = (a < b) ? a : b;
    
    printf("最大値: %d\n", max);
    printf("最小値: %d\n", min);
    
    // 年齢による判定
    printf("\n年齢を入力してください: ");
    int age;
    scanf("%d", &age);
    
    char *status = (age >= 20) ? "成人" : "未成年";
    printf("あなたは%sです。\n", status);
    
    // 成績による合否判定
    printf("\n点数を入力してください (0-100): ");
    int score;
    scanf("%d", &score);
    
    char *result = (score >= 60) ? "合格" : "不合格";
    printf("判定: %s\n", result);
    
    // ネストした条件演算子（読みやすさには注意）
    printf("成績評価: ");
    printf("%c\n", (score >= 90) ? 'A' :
                   (score >= 80) ? 'B' :
                   (score >= 70) ? 'C' :
                   (score >= 60) ? 'D' : 'F');
    
    // 条件演算子と通常の計算を組み合わせる
    int bonus = (score >= 80) ? 10 : 0;
    printf("ボーナス点: %d\n", bonus);
    printf("最終得点: %d\n", score + bonus);
    
    // 絶対値の計算
    printf("\n整数を入力してください: ");
    int number;
    scanf("%d", &number);
    
    int abs_value = (number >= 0) ? number : -number;
    printf("%d の絶対値は %d です。\n", number, abs_value);
    
    return 0;
}