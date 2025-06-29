/*
 * 課題2-3の解答例: 入力と出力（C99版）
 * ファイル名: ex2_3_age_calculator_c99.c
 * 説明: scanf関数を使った入力処理と計算
 * C99特有の機能：必要な時点での変数宣言を使用
 */

#include <stdio.h>

int main(void)
{
    char name[50];      /* 名前を格納する文字配列（50文字まで） */
    
    /* ユーザーからの入力 */
    printf("お名前を入力してください: ");
    scanf("%49s", name);  /* 49文字まで読み込み（バッファオーバーフロー対策） */
    
    printf("年齢を入力してください: ");
    int current_age;    /* C99：必要な時点で変数宣言 */
    scanf("%d", &current_age);
    
    /* 10年後の年齢を計算 */
    int future_age = current_age + 10;  /* C99：宣言と同時に計算 */
    
    /* 結果の表示 */
    printf("\n");
    printf("こんにちは、%sさん！\n", name);
    printf("現在の年齢: %d歳\n", current_age);
    printf("10年後の年齢: %d歳\n", future_age);
    printf("プログラミングの学習、頑張ってください！\n");
    
    return 0;
}

/*
学習ポイント:
1. scanf関数の使用:
   - %s: 文字列の入力
   - %d: 整数の入力
   - & (アドレス演算子): 変数のアドレスを指定
   
2. 文字配列の宣言:
   - char name[50]: 50文字まで格納可能
   - scanf("%49s", name): バッファオーバーフロー対策
   
3. 計算処理:
   - future_age = current_age + 10
   - 計算結果を変数に保存
   
4. 改行文字の使用:
   - \n で改行
   - printf("\n") で空行挿入

C99での変更点:
- current_age を使用直前に宣言
- future_age を宣言と同時に初期化
- より読みやすいコード構造
   
注意点:
- scanf使用時はバッファサイズに注意
- 実際のプログラムでは入力エラーのチェックも必要
- 配列のサイズは格納する文字数+1（終端文字\0のため）
*/