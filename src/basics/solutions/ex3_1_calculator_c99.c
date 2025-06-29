/*
 * 課題3-1の解答例: 基本計算機
 * ファイル名: ex3_1_calculator_c99.c
 * 説明: 2つの数値を入力して四則演算を実行（C99版）
 * 規格: C99準拠
 */

#include <stdio.h>

int main(void)
{
    // 2つの数値を入力
    printf("第1の数値を入力してください: ");
    double num1;
    scanf("%lf", &num1);
    
    printf("第2の数値を入力してください: ");
    double num2;
    scanf("%lf", &num2);
    
    // 四則演算の計算（C99では必要時点で変数宣言可能）
    double sum = num1 + num2;
    double diff = num1 - num2;
    double product = num1 * num2;
    double quotient = num1 / num2;
    
    // 結果の表示
    printf("\n=== 計算結果 ===\n");
    printf("%.2f + %.2f = %.2f\n", num1, num2, sum);
    printf("%.2f - %.2f = %.2f\n", num1, num2, diff);
    printf("%.2f × %.2f = %.2f\n", num1, num2, product);
    printf("%.2f ÷ %.2f = %.2f\n", num1, num2, quotient);
    
    return 0;
}

/*
C99での改善点:
1. 変数宣言を必要な箇所で行える
2. 計算と宣言を同時に実行可能
3. より自然なプログラムの流れ
4. // 形式のコメント使用可能
*/