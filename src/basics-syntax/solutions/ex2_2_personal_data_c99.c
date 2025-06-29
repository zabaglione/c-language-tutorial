/*
 * 課題2-2の解答例: 変数と基本データ型（C99版）
 * ファイル名: ex2_2_personal_data_c99.c
 * 説明: 基本データ型の変数宣言、初期化、書式指定子の使用
 * C99特有の機能：必要な時点での変数宣言を使用
 */

#include <stdio.h>

int main(void)
{
    /* 基本データの変数宣言と初期化 */
    int age = 25;           /* 年齢（整数） */
    float height = 170.5f;  /* 身長（浮動小数点数） */
    char blood_type = 'A';  /* 血液型（文字） */
    
    /* 自己紹介データの表示 */
    printf("=== 自己紹介データ ===\n");
    printf("年齢: %d歳\n", age);
    printf("身長: %.1fcm\n", height);
    printf("血液型: %c型\n", blood_type);
    
    /* C99：必要な時点で変数宣言 */
    int favorite_number = 7; /* 好きな数字（整数） */
    printf("好きな数字: %d\n", favorite_number);
    printf("================\n");
    
    return 0;
}

/*
学習ポイント:
1. 基本データ型の使い分け:
   - int: 整数値
   - float: 浮動小数点数（単精度）
   - char: 1文字
   
2. 変数の初期化:
   - 宣言と同時に値を代入
   - float型には f を付ける（170.5f）
   - char型には シングルクォート（'A'）
   
3. printf関数の書式指定子:
   - %d: 整数（decimal）
   - %f: 浮動小数点数（float）
   - %c: 文字（character）
   - %.1f: 小数点以下1桁表示
   
4. コメントの書き方:
   - スラッシュとアスタリスクで囲む
   - 変数の説明を記述

C99での変更点:
- 必要な時点での変数宣言が可能
- favorite_number を使用直前に宣言
*/