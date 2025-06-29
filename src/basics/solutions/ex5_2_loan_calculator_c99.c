/*
 * ファイル名: ex5_2_loan_calculator_c99.c
 * 課題5-2: ローン計算機 (C99版)
 * 説明: 住宅ローンの月額返済額を計算するプログラム
 * 規格: C99準拠
 */

#include <stdio.h>
#include <math.h>

int main(void)
{
    printf("=== ローン計算機 ===\n");
    
    // 入力
    double loan_amount;
    printf("借入金額を入力してください（万円）: ");
    scanf("%lf", &loan_amount);
    loan_amount *= 10000; // 万円を円に変換
    
    double annual_rate;
    printf("年利率を入力してください（%%）: ");
    scanf("%lf", &annual_rate);
    annual_rate /= 100.0; // パーセントを小数に変換
    
    int years;
    printf("返済期間を入力してください（年）: ");
    scanf("%d", &years);
    
    // 計算
    double monthly_rate = annual_rate / 12.0;
    int months = years * 12;
    
    // 元利均等返済の月額返済額計算
    double factor = pow(1 + monthly_rate, months);
    double monthly_payment = loan_amount * monthly_rate * factor / (factor - 1);
    
    double total_payment = monthly_payment * months;
    double total_interest = total_payment - loan_amount;
    
    // 結果の表示
    printf("\n=== 計算結果 ===\n");
    printf("借入金額: %.0f円\n", loan_amount);
    printf("年利率: %.1f%%\n", annual_rate * 100);
    printf("返済期間: %d年（%d回払い）\n", years, months);
    printf("\n");
    printf("月額返済額: %.0f円\n", monthly_payment);
    printf("総返済額: %.0f円\n", total_payment);
    printf("利息総額: %.0f円\n", total_interest);
    
    return 0;
}