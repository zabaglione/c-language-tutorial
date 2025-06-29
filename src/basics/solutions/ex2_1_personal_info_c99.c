/*
 * 課題2-1の解答例: 個人情報管理
 * ファイル名: ex2_1_personal_info_c99.c
 * 説明: さまざまなデータ型を使った個人情報管理とBMI計算（C99版）
 * 規格: C99準拠
 */

#include <stdio.h>

int main(void)
{
    // 個人情報の変数宣言と初期化
    char name[] = "T.Yamada";
    int age = 23;
    double height = 170.5;  // cm
    double weight = 65.0;   // kg
    char blood_type = 'A';
    const char student_status[] = "はい";
    
    // 身長をメートルに変換
    double height_m = height / 100.0;
    
    // BMI計算: 体重(kg) ÷ (身長(m) × 身長(m))
    double bmi = weight / (height_m * height_m);
    
    // 個人情報の表示
    printf("=== 個人情報 ===\n");
    printf("名前: %s\n", name);
    printf("年齢: %d歳\n", age);
    printf("身長: %.1fcm\n", height);
    printf("体重: %.1fkg\n", weight);
    printf("血液型: %c\n", blood_type);
    printf("学生: %s\n", student_status);
    
    // 統計情報の表示
    printf("=== 統計情報 ===\n");
    printf("BMI: %.1f\n", bmi);
    printf("年齢の16進表記: 0x%x\n", age);
    
    return 0;
}

/*
C99での改善点:
1. // 形式のコメントが使用可能
2. 変数宣言と初期化を同時に行える
3. 計算式を宣言時に直接記述可能
4. より読みやすいコード構造
*/