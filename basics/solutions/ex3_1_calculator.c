/*
 * 課題3-1の解答例: 基本計算機
 * ファイル名: ex3_1_calculator.c
 * 説明: 2つの数値を入力して四則演算を実行
 * 規格: C90準拠
 */

#include <stdio.h>

int main(void)
{
    /* 変数の宣言（C90では先頭で宣言） */
    double num1, num2;
    double sum, diff, product, quotient;
    
    /* 2つの数値を入力 */
    printf("第1の数値を入力してください: ");
    scanf("%lf", &num1);
    
    printf("第2の数値を入力してください: ");
    scanf("%lf", &num2);
    
    /* 四則演算の計算 */
    sum = num1 + num2;
    diff = num1 - num2;
    product = num1 * num2;
    quotient = num1 / num2;
    
    /* 結果の表示 */
    printf("\n=== 計算結果 ===\n");
    printf("%.2f + %.2f = %.2f\n", num1, num2, sum);
    printf("%.2f - %.2f = %.2f\n", num1, num2, diff);
    printf("%.2f × %.2f = %.2f\n", num1, num2, product);
    printf("%.2f ÷ %.2f = %.2f\n", num1, num2, quotient);
    
    return 0;
}

/*
学習ポイント:
1. scanf関数による入力:
   - %lf書式指定子でdouble型の入力
   - &演算子でアドレスを渡す

2. 基本的な算術演算:
   - + (加算), - (減算), * (乗算), / (除算)

3. 書式指定による出力:
   - %.2f で小数点以下2桁表示

注意事項:
- 0による除算のチェックは応用課題で実装
- 実際のプログラムでは入力エラーの処理も必要
*/