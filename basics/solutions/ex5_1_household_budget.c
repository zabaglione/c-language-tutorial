/*
 * ファイル名: ex5_1_household_budget.c
 * 課題5-1: 家計簿計算機
 * 説明: 収入と支出を計算して家計の状況を表示するプログラム
 * 規格: C90準拠
 */

#include <stdio.h>

int main(void)
{
    /* 変数の宣言 */
    int income, rent, food, utilities, other;
    int total_expenses, remaining;
    double savings_rate;
    
    printf("=== 家計簿計算機 ===\n");
    
    /* 収入の入力 */
    printf("月収を入力してください: ");
    scanf("%d", &income);
    
    /* 支出項目の入力 */
    printf("家賃を入力してください: ");
    scanf("%d", &rent);
    
    printf("食費を入力してください: ");
    scanf("%d", &food);
    
    printf("光熱費を入力してください: ");
    scanf("%d", &utilities);
    
    printf("その他を入力してください: ");
    scanf("%d", &other);
    
    /* 計算 */
    total_expenses = rent + food + utilities + other;
    remaining = income - total_expenses;
    savings_rate = (double)remaining / income * 100.0;
    
    /* 結果の表示 */
    printf("\n=== 家計簿 ===\n");
    printf("【収入】\n");
    printf("  月収: %d円\n", income);
    
    printf("\n【支出】\n");
    printf("  家賃: %d円\n", rent);
    printf("  食費: %d円\n", food);
    printf("  光熱費: %d円\n", utilities);
    printf("  その他: %d円\n", other);
    printf("  ――――――――――――\n");
    printf("  支出合計: %d円\n", total_expenses);
    
    printf("\n【収支】\n");
    printf("  残金: %d円\n", remaining);
    printf("  貯蓄率: %.1f%%\n", savings_rate);
    
    return 0;
}