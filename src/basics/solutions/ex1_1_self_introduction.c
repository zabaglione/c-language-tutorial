/*
 * 課題1-1の解答例: 自己紹介プログラム
 * ファイル名: ex1_1_self_introduction.c
 * 説明: 罫線を使った見やすい自己紹介を表示
 * 規格: C90準拠
 */

#include <stdio.h>

int main(void)
{
    /* 自己紹介データ */
    char name[] = "田中太郎";
    int age = 25;
    char hobby[] = "プログラミング";
    char language[] = "C言語";
    
    /* 罫線付き自己紹介の表示 */
    printf("===========================\n");
    printf("    自己紹介\n");
    printf("===========================\n");
    printf("名前: %s\n", name);
    printf("年齢: %d歳\n", age);
    printf("趣味: %s\n", hobby);
    printf("好きな言語: %s\n", language);
    printf("===========================\n");
    
    return 0;
}

/*
学習ポイント:
1. 文字列の配列宣言と初期化
2. printf関数による書式指定出力
3. 罫線を使った見やすい表示
4. 変数の値を文字列に組み込む方法
*/