/*
 * 条件演算子（三項演算子）の使い方（C90準拠）
 * 
 * このプログラムは、条件演算子を使った
 * 簡潔な条件分岐の書き方を示します。
 * 規格: C90準拠
 */
#include <stdio.h>

int main(void)
{
    /* 変数の宣言（C90では先頭で宣言） */
    int a, b;
    int max, min;
    int age;
    int score;
    int bonus;
    int number;
    int abs_value;
    char *result;
    char *status;
    
    /* 2つの数の最大値・最小値を求める */
    printf("2つの整数を入力してください: ");
    scanf("%d %d", &a, &b);
    
    /* 条件演算子を使った最大値・最小値の判定 */
    max = (a > b) ? a : b;
    min = (a < b) ? a : b;
    
    printf("最大値: %d\n", max);
    printf("最小値: %d\n", min);
    
    /* 年齢による判定 */
    printf("\n年齢を入力してください: ");
    scanf("%d", &age);
    
    status = (age >= 20) ? "成人" : "未成年";
    printf("あなたは%sです。\n", status);
    
    /* 成績による合否判定 */
    printf("\n点数を入力してください (0-100): ");
    scanf("%d", &score);
    
    result = (score >= 60) ? "合格" : "不合格";
    printf("判定: %s\n", result);
    
    /* ネストした条件演算子（読みやすさには注意） */
    printf("成績評価: ");
    printf("%c\n", (score >= 90) ? 'A' :
                   (score >= 80) ? 'B' :
                   (score >= 70) ? 'C' :
                   (score >= 60) ? 'D' : 'F');
    
    /* 条件演算子と通常の計算を組み合わせる */
    bonus = (score >= 80) ? 10 : 0;
    printf("ボーナス点: %d\n", bonus);
    printf("最終得点: %d\n", score + bonus);
    
    /* 絶対値の計算 */
    printf("\n整数を入力してください: ");
    scanf("%d", &number);
    
    abs_value = (number >= 0) ? number : -number;
    printf("%d の絶対値は %d です。\n", number, abs_value);
    
    return 0;
}