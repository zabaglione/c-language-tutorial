/*
 * greeting.c - 名前を入力して挨拶するプログラム
 * 
 * このプログラムは、ユーザーの名前を入力してもらい、
 * 挨拶メッセージを表示します。
 */

#include <stdio.h>

int main(void) {
    char name[50];  /* 名前を保存する場所 */
    
    printf("お名前は？: ");
    scanf("%s", name);
    printf("こんにちは、%sさん！\n", name);
    
    return 0;
}