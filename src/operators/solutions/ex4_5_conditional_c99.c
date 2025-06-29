/*
 * ファイル名: ex4_5_conditional_c99.c
 * 演習4-5: 条件演算子
 * 説明: 3つの数値を条件演算子のみで昇順に並び替える
 * 規格: C99準拠
 */
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

// 時間表示用の構造体
typedef struct {
    int hour;
    int minute;
} Time;

// ユーティリティ関数
int max(int a, int b);
int min(int a, int b);
int sign(int x);
double absolute(double x);
char get_grade(int score);
const char *get_season(int month);

int main(void)
{
    printf("=== 条件演算子の応用 ===\n");

    // 基本的な使用
    printf("基本的な使用:\n");
    int number = 15;
    printf("  数値: %d\n", number);
    printf("  絶対値: %d (%s)\n",
           (number >= 0) ? number : -number,
           (number >= 0) ? "正数" : "負数");
    printf("  符号: %c\n", (number > 0) ? '+' : (number < 0) ? '-' : '0');
    printf("  偶数/奇数: %s\n", (number % 2 == 0) ? "偶数" : "奇数");
    printf("\n");

    // ネストした条件演算子
    printf("ネストした条件演算子:\n");
    int score = 85;
    char grade = (score >= 90) ? 'A' :
                 (score >= 80) ? 'B' :
                 (score >= 70) ? 'C' :
                 (score >= 60) ? 'D' : 'F';
    printf("  点数: %d\n", score);
    printf("  評価: %c (90以上:A, 80以上:B, 70以上:C, 60以上:D, その他:F)\n", grade);
    printf("\n");

    // 配列操作での使用
    printf("配列操作での使用:\n");
    int values[] = {23, 89, 45, 12, 67, 91, 34};
    int size = sizeof(values) / sizeof(values[0]);

    // 最大値・最小値の検索
    int array_max = values[0];
    int array_min = values[0];
    for (int i = 1; i < size; i++) {  // C99: forループ内で変数宣言
        array_max = (values[i] > array_max) ? values[i] : array_max;
        array_min = (values[i] < array_min) ? values[i] : array_min;
    }
    printf("  配列の最大値: %d\n", array_max);
    printf("  配列の最小値: %d\n", array_min);

    // 範囲内の要素数
    int range_min = 30, range_max = 80;
    int in_range_count = 0;
    for (int i = 0; i < size; i++) {
        in_range_count += (values[i] >= range_min && values[i] <= range_max) ? 1 : 0;
    }
    printf("  範囲[%d-%d]内の要素数: %d個\n", range_min, range_max, in_range_count);
    printf("\n");

    // 時間表示での使用
    printf("時間表示での使用:\n");
    Time current_time = {14, 30};
    printf("  現在時刻: %d時%d分\n", current_time.hour, current_time.minute);

    // 12時間表記への変換
    int hour_12 = (current_time.hour == 0) ? 12 :
                  (current_time.hour > 12) ? current_time.hour - 12 : current_time.hour;
    const char *ampm = (current_time.hour < 12) ? "午前" : "午後";
    printf("  12時間表記: %s%d時%d分\n", ampm, hour_12, current_time.minute);
    printf("  AM/PM: %s %d:%02d\n",
           (current_time.hour < 12) ? "AM" : "PM",
           hour_12, current_time.minute);
    printf("\n");

    // 複雑な条件（C99: bool型の使用）
    printf("複雑な条件:\n");
    int age = 20;
    char gender = 'M';
    bool is_student = true;  // C99: bool型

    printf("  年齢: %d歳, 性別: %c, 学生: %s\n",
           age, gender, is_student ? "はい" : "いいえ");

    // 割引率の計算
    int discount_rate = (is_student && age < 25) ? 20 :
                       (age >= 65) ? 15 :
                       (age < 18) ? 10 : 0;
    const char *discount_reason = (is_student && age < 25) ? "学生割引" :
                                 (age >= 65) ? "シニア割引" :
                                 (age < 18) ? "子供割引" : "割引なし";
    printf("  割引率: %d%% (%s)\n", discount_rate, discount_reason);
    printf("\n");

    // 計算での使用
    printf("計算での使用:\n");
    int x = 5, y = 3;
    printf("  x=%d, y=%d\n", x, y);
    printf("  max(x,y) = %d\n", max(x, y));
    printf("  min(x,y) = %d\n", min(x, y));
    printf("  sign(x-y) = %+d\n", sign(x - y));
    printf("\n");

    // 文字列処理での使用
    printf("文字列処理での使用:\n");
    char text[] = "Hello, World!";
    printf("  文字列: \"%s\"\n", text);
    printf("  文字数: %zu\n", strlen(text));  // C99: %zu for size_t

    // 文字の分類
    printf("  文字分類:\n");
    for (int i = 0; text[i] != '\0'; i++) {  // C99: forループ内で変数宣言
        char ch = text[i];
        const char *type = (ch >= 'A' && ch <= 'Z') ? "大文字" :
                          (ch >= 'a' && ch <= 'z') ? "小文字" :
                          (ch >= '0' && ch <= '9') ? "数字" :
                          (ch == ' ') ? "空白" : "記号";
        printf("    '%c': %s\n", ch, type);
    }
    printf("\n");

    // 季節判定
    printf("季節判定:\n");
    int months[] = {3, 6, 9, 12};
    for (int i = 0; i < 4; i++) {
        printf("  %d月: %s\n", months[i], get_season(months[i]));
    }
    printf("\n");

    // 配列の範囲制限（C99: 変数宣言位置の自由化）
    printf("配列の範囲制限:\n");
    int indices[] = {-1, 0, 3, 5, 7, 10};
    int array_size = 5;
    int safe_array[5] = {10, 20, 30, 40, 50};

    for (int i = 0; i < 6; i++) {
        int idx = indices[i];
        int safe_idx = (idx < 0) ? 0 :
                      (idx >= array_size) ? array_size - 1 : idx;
        int safe_value = safe_array[safe_idx];
        printf("  インデックス%d: %s (値:%d)\n",
               idx,
               (idx >= 0 && idx < array_size) ? "範囲内" : "範囲外→制限",
               safe_value);
    }

    // C99: 追加の例 - ビット幅を意識した条件演算
    printf("\nビット幅を意識した条件演算（C99）:\n");
    uint8_t byte_val = 200;
    uint16_t word_val = byte_val < 128 ? byte_val * 2 : 65535;
    printf("  byte_val=%u → word_val=%u\n", byte_val, word_val);

    // C99: 複合リテラルを使用した条件演算
    printf("\n構造体の条件演算（C99）:\n");
    bool is_morning = current_time.hour < 12;
    Time default_time = is_morning ? 
                       (Time){9, 0} :     // C99: 複合リテラル
                       (Time){14, 0};
    printf("  デフォルト時刻: %d時%d分\n", 
           default_time.hour, default_time.minute);

    printf("==================\n");

    return 0;
}

// ユーティリティ関数の実装
int max(int a, int b)
{
    return (a > b) ? a : b;
}

int min(int a, int b)
{
    return (a < b) ? a : b;
}

int sign(int x)
{
    return (x > 0) ? 1 : (x < 0) ? -1 : 0;
}

double absolute(double x)
{
    return (x >= 0.0) ? x : -x;
}

char get_grade(int score)
{
    return (score >= 90) ? 'A' :
           (score >= 80) ? 'B' :
           (score >= 70) ? 'C' :
           (score >= 60) ? 'D' : 'F';
}

const char *get_season(int month)
{
    return (month >= 3 && month <= 5) ? "春" :
           (month >= 6 && month <= 8) ? "夏" :
           (month >= 9 && month <= 11) ? "秋" : "冬";
}

/*
学習ポイント:
1. 条件演算子の基本構文
   - condition ? expression1 : expression2
   - 三項演算子とも呼ばれる

2. ネストした条件演算子
   - 複数の条件を組み合わせ可能
   - 可読性のため適度に使用
   - if-else文との使い分け

3. 実用的な応用
   - 最大値・最小値の選択
   - 範囲制限（クランプ）
   - デフォルト値の設定
   - 文字列の選択

4. パフォーマンス考慮
   - 式として評価されるため効率的
   - 関数呼び出しより高速
   - コンパイラ最適化が効きやすい

5. 使用上の注意点
   - 複雑な条件は分割する
   - 副作用のある式は避ける
   - 型の一致に注意
   - 可読性を優先

6. 適用場面
   - 簡単な値の選択
   - 初期化での条件分岐
   - マクロ内での条件処理
   - 関数の引数での条件

7. C99での拡張
   - bool型での条件評価
   - 複合リテラルとの組み合わせ
   - forループ内での変数宣言
   - stdint.hによる正確な型指定
*/
