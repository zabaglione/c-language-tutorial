/*
 * 課題4-2の解答例: インクリメント・デクリメント実験
 * ファイル名: ex4_2_increment_decrement_c99.c
 * 説明: 前置と後置の違いを確認するプログラム（C99版）
 * 規格: C99準拠
 */

#include <stdio.h>

int main(void)
{
    // 変数の宣言と初期化
    int a = 10;
    int b = 20;
    
    // 初期値の表示
    printf("=== インクリメント・デクリメント実験 ===\n");
    printf("初期値: a = %d, b = %d\n", a, b);
    printf("\n");
    
    // 前置インクリメント: 先に増加してから値を返す
    printf("前置インクリメント:\n");
    int result_a = ++a;  // aを先に1増加させてから、その値をresult_aに代入
    printf("  ++a = %d, a = %d\n", result_a, a);
    
    // 後置インクリメント: 値を返してから増加
    printf("後置インクリメント:\n");
    int result_b = b++;  // bの現在値をresult_bに代入してから、bを1増加
    printf("  b++ = %d, b = %d\n", result_b, b);
    
    printf("\n");
    
    // 前置デクリメント: 先に減少してから値を返す
    printf("前置デクリメント:\n");
    result_a = --a;  // aを先に1減少させてから、その値をresult_aに代入
    printf("  --a = %d, a = %d\n", result_a, a);
    
    // 後置デクリメント: 値を返してから減少
    printf("後置デクリメント:\n");
    result_b = b--;  // bの現在値をresult_bに代入してから、bを1減少
    printf("  b-- = %d, b = %d\n", result_b, b);
    
    printf("\n最終値: a = %d, b = %d\n", a, b);
    
    return 0;
}

/*
C99での改善点:
1. 変数宣言を必要な箇所で実行可能
2. // 形式のコメント使用
3. より自然なプログラムの流れ

動作は同じ: a(10→11→10), b(20→21→20)
*/