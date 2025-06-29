/*
 * 課題2-1の解答例: 基本的な出力
 * ファイル名: ex2_1_hello_intro.c
 * 説明: printf関数とエスケープシーケンスの基本的な使用
 * 規格: C90準拠
 */

#include <stdio.h>

int main(void)
{
    /* 基本的な文字列出力 */
    printf("こんにちは、C言語の世界へ！\n");
    printf("私の名前は 田中太郎 です。\n");
    printf("今日からプログラミングを始めます。\n");
    
    return 0;
}

/*
学習ポイント:
1. #include <stdio.h> - 標準入出力ライブラリの取り込み
2. int main(void) - プログラムのエントリーポイント
3. printf関数 - 文字列の出力
4. \n - 改行を表すエスケープシーケンス
5. return 0 - プログラムの正常終了を示す
*/
