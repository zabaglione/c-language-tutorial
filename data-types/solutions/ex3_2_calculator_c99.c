/*
 * ファイル名: ex3_2_calculator_c99.c
 * 演習3-2: 四則演算計算機
 * 説明: 2つの数値を変数に格納し、四則演算の結果を表示する
 * 規格: C99準拠
 */
#include <stdio.h>

int main(void)
{
    printf("=== 四則演算計算機 ===\n");
    
    // 整数演算（使用箇所で宣言）
    int num1 = 15;
    int num2 = 4;
    
    printf("整数演算 (%d と %d):\n", num1, num2);
    printf("  %d + %d = %d\n", num1, num2, num1 + num2);
    printf("  %d - %d = %d\n", num1, num2, num1 - num2);
    printf("  %d * %d = %d\n", num1, num2, num1 * num2);
    printf("  %d / %d = %d (余り: %d)\n", num1, num2, num1 / num2, num1 % num2);
    
    // 実数演算
    double real1 = 15.5;
    double real2 = 4.2;
    
    printf("\n実数演算 (%.1f と %.1f):\n", real1, real2);
    printf("  %.1f + %.1f = %.2f\n", real1, real2, real1 + real2);
    printf("  %.1f - %.1f = %.2f\n", real1, real2, real1 - real2);
    printf("  %.1f * %.1f = %.2f\n", real1, real2, real1 * real2);
    printf("  %.1f / %.1f = %.2f\n", real1, real2, real1 / real2);
    
    // 混合演算（型変換の例）
    printf("\n混合演算（整数と実数）:\n");
    printf("  %d + %.1f = %.2f\n", num1, real2, num1 + real2);
    printf("  %.1f - %d = %.2f\n", real1, num2, real1 - num2);
    printf("  %d * %.1f = %.2f\n", num1, real2, num1 * real2);
    printf("  %.1f / %d = %.2f\n", real1, num2, real1 / num2);
    
    // 整数除算と実数除算の比較
    printf("\n整数除算 vs 実数除算の比較:\n");
    printf("  %d / %d = %d (整数除算)\n", num1, num2, num1 / num2);
    printf("  %d / %d = %.2f (実数除算)\n", num1, num2, (double)num1 / num2);
    printf("  %.1f / %.1f = %.2f (実数除算)\n", real1, real2, real1 / real2);
    
    return 0;
}

/*
学習ポイント:
1. 整数演算と実数演算の違い
2. 四則演算子 (+, -, *, /, %) の使い方
3. 整数除算では小数点以下が切り捨てられる
4. 剰余演算子(%)は整数のみで使用可能
5. 混合演算での自動型変換
6. 明示的型変換 (キャスト) の使用

C99の特徴:
- 変数を使用箇所で宣言可能
- // 形式のコメントが使用可能
- より読みやすいコード構造
*/
