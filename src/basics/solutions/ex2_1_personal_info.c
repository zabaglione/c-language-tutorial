/*
 * 課題2-1の解答例: 個人情報管理
 * ファイル名: ex2_1_personal_info.c
 * 説明: さまざまなデータ型を使った個人情報管理とBMI計算
 * 規格: C90準拠
 */

#include <stdio.h>

int main(void)
{
    /* 個人情報の変数宣言（C90では先頭で宣言） */
    char name[] = "T.Yamada";
    int age = 23;
    double height = 170.5;  /* cm */
    double weight = 65.0;   /* kg */
    char blood_type = 'A';
    const char student_status[] = "はい";
    
    /* 計算用変数 */
    double height_m;        /* 身長をメートルに変換 */
    double bmi;
    
    /* 身長をメートルに変換 */
    height_m = height / 100.0;
    
    /* BMI計算: 体重(kg) ÷ (身長(m) × 身長(m)) */
    bmi = weight / (height_m * height_m);
    
    /* 個人情報の表示 */
    printf("=== 個人情報 ===\n");
    printf("名前: %s\n", name);
    printf("年齢: %d歳\n", age);
    printf("身長: %.1fcm\n", height);
    printf("体重: %.1fkg\n", weight);
    printf("血液型: %c\n", blood_type);
    printf("学生: %s\n", student_status);
    
    /* 統計情報の表示 */
    printf("=== 統計情報 ===\n");
    printf("BMI: %.1f\n", bmi);
    printf("年齢の16進表記: 0x%x\n", age);
    
    return 0;
}

/*
学習ポイント:
1. 各データ型の適切な使い分け:
   - int: 年齢（整数値）
   - double: 身長・体重・BMI（小数点を含む数値）
   - char: 血液型（1文字）
   - char[]: 名前・学生状況（文字列）
   - const: 変更されない値

2. 計算処理:
   - 単位変換（cm → m）
   - BMI計算式の実装
   - 16進数表記での出力

3. 書式指定子:
   - %s: 文字列
   - %d: 10進整数
   - %x: 16進整数
   - %.1f: 小数点以下1桁の浮動小数点数
*/