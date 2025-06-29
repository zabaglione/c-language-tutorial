/*
 * ファイル名: variables_demo.c
 * 説明: 変数とデータ型のデモンストレーション
 * 規格: C90準拠
 */

#include <stdio.h>

int main(void)
{
    /* 変数の宣言と初期化 */
    int age = 25;
    float height = 170.5f;
    char blood_type = 'A';
    double pi = 3.14159;
    
    /* 自己紹介データの表示 */
    printf("=== 変数のデモンストレーション ===\n");
    printf("年齢: %d歳\n", age);
    printf("身長: %.1fcm\n", height);
    printf("血液型: %c型\n", blood_type);
    printf("円周率: %.5f\n", pi);
    
    /* 計算例 */
    printf("\n=== 計算例 ===\n");
    printf("年齢の2倍: %d\n", age * 2);
    printf("身長をメートルで: %.2fm\n", height / 100.0f);
    
    return 0;
}