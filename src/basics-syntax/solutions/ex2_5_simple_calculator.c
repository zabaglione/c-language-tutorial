/*
 * 課題2-5の解答例: 簡単な計算機
 * ファイル名: ex2_5_simple_calculator.c
 * 説明: 四則演算の実装と整数除算・実数除算の違い
 */

#include <stdio.h>

int main(void)
{
    int num1, num2;         /* 計算に使用する2つの整数 */
    int int_result;         /* 整数演算の結果 */
    double double_result;   /* 実数演算の結果 */
    
    /* プログラムのタイトル表示 */
    printf("簡単な計算機プログラム\n");
    printf("===================\n");
    
    /* 数値の入力 */
    printf("第1の数値を入力してください: ");
    scanf("%d", &num1);
    
    printf("第2の数値を入力してください: ");
    scanf("%d", &num2);
    
    printf("\n");
    
    /* 四則演算の実行と結果表示 */
    printf("計算結果:\n");
    
    /* 加算 */
    int_result = num1 + num2;
    printf("  %d + %d = %d\n", num1, num2, int_result);
    
    /* 減算 */
    int_result = num1 - num2;
    printf("  %d - %d = %d\n", num1, num2, int_result);
    
    /* 乗算 */
    int_result = num1 * num2;
    printf("  %d * %d = %d\n", num1, num2, int_result);
    
    /* 除算（整数除算） */
    int_result = num1 / num2;
    printf("  %d / %d = %d (整数除算)\n", num1, num2, int_result);
    
    /* 除算（実数除算） */
    double_result = (double)num1 / num2;  /* キャストを使用 */
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
   
注意点:
- ゼロ除算のチェックは省略（基礎課題のため）
- 実際のプログラムでは num2 が 0 でないかチェックが必要
- キャストは演算の前に行う必要がある
*/
