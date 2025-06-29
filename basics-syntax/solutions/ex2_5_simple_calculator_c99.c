/*
 * 課題2-5の解答例: 簡単な計算機（C99版）
 * ファイル名: ex2_5_simple_calculator_c99.c
 * 説明: 四則演算の実装と整数除算・実数除算の違い
 * C99特有の機能：必要な時点での変数宣言を使用
 */

#include <stdio.h>

int main(void)
{
    /* プログラムのタイトル表示 */
    printf("簡単な計算機プログラム\n");
    printf("===================\n");
    
    /* 数値の入力 */
    printf("第1の数値を入力してください: ");
    int num1;  /* C99：必要な時点で変数宣言 */
    scanf("%d", &num1);
    
    printf("第2の数値を入力してください: ");
    int num2;  /* C99：必要な時点で変数宣言 */
    scanf("%d", &num2);
    
    printf("\n");
    
    /* 四則演算の実行と結果表示 */
    printf("計算結果:\n");
    
    /* 加算 */
    int add_result = num1 + num2;  /* C99：宣言と同時に計算 */
    printf("  %d + %d = %d\n", num1, num2, add_result);
    
    /* 減算 */
    int sub_result = num1 - num2;  /* C99：宣言と同時に計算 */
    printf("  %d - %d = %d\n", num1, num2, sub_result);
    
    /* 乗算 */
    int mul_result = num1 * num2;  /* C99：宣言と同時に計算 */
    printf("  %d * %d = %d\n", num1, num2, mul_result);
    
    /* 除算（整数除算） */
    int div_result = num1 / num2;  /* C99：宣言と同時に計算 */
    printf("  %d / %d = %d (整数除算)\n", num1, num2, div_result);
    
    /* 除算（実数除算） */
    double double_result = (double)num1 / num2;  /* C99：宣言と同時に計算 */
    printf("  %d / %d = %.2f (実数除算)\n", num1, num2, double_result);
    
    return 0;
}

/*
学習ポイント:
1. 四則演算子:
   - + : 加算
   - - : 減算
   - * : 乗算（アスタリスク）
   - / : 除算
   
2. 整数除算と実数除算の違い:
   - int / int → 整数除算（小数点以下切り捨て）
   - (double)int / int → 実数除算（小数点以下あり）
   
3. 型変換（キャスト）:
   - (double)num1 → num1を一時的にdouble型に変換
   - これにより実数除算が行われる
   
4. 書式指定子:
   - %d: 整数
   - %.2f: 小数点以下2桁の実数
   
5. プログラムの構成:
   - 入力 → 処理 → 出力の基本的な流れ
   - 見やすい出力のためのフォーマット

C99での変更点:
- 各変数を必要な時点で宣言
- 宣言と同時に計算結果を代入
- より読みやすいコード構造
- 演算結果ごとに意味のある変数名を使用
   
注意点:
- ゼロ除算のチェックは省略（基礎課題のため）
- 実際のプログラムでは num2 が 0 でないかチェックが必要
- キャストは演算の前に行う必要がある
*/