/*
 * ファイル名: ex1_2_message_box.c
 * 課題1-2: メッセージボックス
 * 説明: Unicode文字を使った枠付きメッセージの表示
 * 規格: C90準拠
 */

#include <stdio.h>

int main(void)
{
    /* Unicode文字で枠付きメッセージを表示 */
    printf("┌─────────────────────────┐\n");
    printf("│  C言語学習プログラム    │\n");
    printf("│  頑張って勉強しよう！   │\n");
    printf("│  Ver 1.0               │\n");
    printf("└─────────────────────────┘\n");
    
    return 0;
}