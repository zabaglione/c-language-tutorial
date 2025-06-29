/*
 * 課題1-1の解答例: 自己紹介プログラム
 * ファイル名: ex1_1_self_introduction_c99.c
 * 説明: 罫線を使った見やすい自己紹介を表示（C99版）
 * 規格: C99準拠
 */

#include <stdio.h>

int main(void)
{
    // 自己紹介データ（C99では必要時点で宣言可能）
    char name[] = "田中太郎";
    int age = 25;
    char hobby[] = "プログラミング";
    char language[] = "C言語";
    
    // 罫線付き自己紹介の表示
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
C99での改善点:
1. // 形式のコメントが使用可能
2. 変数宣言をより柔軟に配置可能
3. その他の機能（この例では基本的な内容のため差は少ない）
*/