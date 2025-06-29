/*
 * ファイル名: variables_demo_c99.c
 * 説明: 変数とデータ型のデモンストレーション (C99版)
 * 規格: C99準拠
 */

#include <stdio.h>

int main(void)
{
    printf("=== 変数のデモンストレーション ===\n");
    
    // 変数の宣言と初期化（C99では必要な箇所で宣言可能）
    int age = 25;
    printf("年齢: %d歳\n", age);
    
    float height = 170.5f;
    printf("身長: %.1fcm\n", height);
    
    char blood_type = 'A';
    printf("血液型: %c型\n", blood_type);
    
    double pi = 3.14159;
    printf("円周率: %.5f\n", pi);
    
    // 計算例
    printf("\n=== 計算例 ===\n");
    printf("年齢の2倍: %d\n", age * 2);
    printf("身長をメートルで: %.2fm\n", height / 100.0f);
    
    return 0;
}