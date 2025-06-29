/*
 * ファイル名: ex4_3_ternary_operator.c
 * 課題4-3: 三項演算子の練習
 * 説明: 三項演算子を使用して条件による値の選択を行うプログラム
 * 規格: C90準拠
 */

#include <stdio.h>

int main(void)
{
    /* 変数の宣言 */
    int num1, num2;
    int max_val, min_val, abs_val;
    int test_score = 85; /* テスト用の固定値 */
    
    /* 2つの整数を入力 */
    printf("2つの整数を入力してください: ");
    scanf("%d %d", &num1, &num2);
    
    printf("\n=== 三項演算子による比較 ===\n");
    
    /* 最大値の選択 */
    max_val = (num1 > num2) ? num1 : num2;
    printf("最大値: %d\n", max_val);
    
    /* 最小値の選択 */
    min_val = (num1 < num2) ? num1 : num2;
    printf("最小値: %d\n", min_val);
    
    /* 絶対値の計算（差の絶対値） */
    abs_val = (num1 - num2 >= 0) ? (num1 - num2) : -(num1 - num2);
    printf("絶対値（%d-%dの場合）: %d\n", num1, num2, abs_val);
    
    /* 合格・不合格の判定（60点以上で合格） */
    printf("判定（%d点の場合）: %s\n", 
           test_score, 
           (test_score >= 60) ? "合格" : "不合格");
    
    /*
     * 学習ポイント:
     * - 三項演算子の構文: (条件) ? 真の場合の値 : 偽の場合の値
     * - if文の代わりに短く書ける
     * - 値の選択や簡単な条件分岐に便利
     */
    
    return 0;
}