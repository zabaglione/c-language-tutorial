/*
 * ファイル名: ex4_2_comparison_c99.c
 * 演習4-2: 比較と論理演算
 * 説明: 関係演算子と論理演算子を使って最大値と最小値を求める
 * 規格: C99準拠
 */

#include <stdio.h>
#include <stdbool.h>

// C99: inline関数による比較処理
static inline int max2(int a, int b)
{
    return (a > b) ? a : b;
}

static inline int min2(int a, int b)
{
    return (a < b) ? a : b;
}

// C99: 3つの値の最大値・最小値を求めるinline関数
static inline int max3(int a, int b, int c)
{
    return max2(max2(a, b), c);
}

static inline int min3(int a, int b, int c)
{
    return min2(min2(a, b), c);
}

// C99: bool型を返す判定関数
static inline bool is_in_range(int value, int min, int max)
{
    return (value >= min) && (value <= max);
}

int main(void)
{
    printf("===== 比較と論理演算 (C99版) =====\n");
    printf("2つの整数を入力してください: ");
    
    // C99: 使用箇所での変数宣言
    int num1, num2;
    if (scanf("%d %d", &num1, &num2) != 2) {
        printf("エラー: 正しい整数を入力してください\n");
        return 1;
    }
    
    // 最大値と最小値の計算
    int max = max2(num1, num2);
    int min = min2(num1, num2);
    
    printf("\n=== 結果 ===\n");
    printf("入力値: %d, %d\n", num1, num2);
    printf("最大値: %d\n", max);
    printf("最小値: %d\n", min);
    
    // C99: bool型による関係演算子の結果
    printf("\n=== 関係演算子による比較 (bool型使用) ===\n");
    bool equal = (num1 == num2);
    bool not_equal = (num1 != num2);
    bool less = (num1 < num2);
    bool less_equal = (num1 <= num2);
    bool greater = (num1 > num2);
    bool greater_equal = (num1 >= num2);
    
    printf("%d == %d : %s\n", num1, num2, equal ? "true" : "false");
    printf("%d != %d : %s\n", num1, num2, not_equal ? "true" : "false");
    printf("%d <  %d : %s\n", num1, num2, less ? "true" : "false");
    printf("%d <= %d : %s\n", num1, num2, less_equal ? "true" : "false");
    printf("%d >  %d : %s\n", num1, num2, greater ? "true" : "false");
    printf("%d >= %d : %s\n", num1, num2, greater_equal ? "true" : "false");
    
    // 論理演算子の使用例
    printf("\n=== 論理演算子の応用 ===\n");
    
    // C99: bool型変数による条件判定
    bool both_positive = (num1 > 0) && (num2 > 0);
    bool either_positive = (num1 > 0) || (num2 > 0);
    bool both_even = !(num1 % 2) && !(num2 % 2);
    bool same_sign = ((num1 > 0) && (num2 > 0)) || ((num1 < 0) && (num2 < 0));
    
    printf("両方とも正の数: %s\n", both_positive ? "はい" : "いいえ");
    printf("少なくとも一方が正の数: %s\n", either_positive ? "はい" : "いいえ");
    printf("両方とも偶数: %s\n", both_even ? "はい" : "いいえ");
    printf("同じ符号: %s\n", same_sign ? "はい" : "いいえ");
    
    // 3つの値の比較（拡張例）
    printf("\n=== 3つの値の比較 ===\n");
    int third_value = 0;
    printf("3つ目の値として0を使用します\n");
    
    int max_of_three = max3(num1, num2, third_value);
    int min_of_three = min3(num1, num2, third_value);
    
    printf("3つの値 (%d, %d, %d) の最大値: %d\n", 
           num1, num2, third_value, max_of_three);
    printf("3つの値 (%d, %d, %d) の最小値: %d\n", 
           num1, num2, third_value, min_of_three);
    
    // C99: 構造体を使った詳細な比較結果
    printf("\n=== 詳細な比較分析 ===\n");
    
    typedef struct {
        int value;
        bool is_positive;
        bool is_even;
        bool is_in_standard_range;  // -100 〜 100
    } NumberInfo;
    
    // C99: 複合リテラルによる初期化
    NumberInfo info1 = {
        .value = num1,
        .is_positive = (num1 > 0),
        .is_even = !(num1 % 2),
        .is_in_standard_range = is_in_range(num1, -100, 100)
    };
    
    NumberInfo info2 = {
        .value = num2,
        .is_positive = (num2 > 0),
        .is_even = !(num2 % 2),
        .is_in_standard_range = is_in_range(num2, -100, 100)
    };
    
    // C99: forループ内での変数宣言を使った表示
    for (int i = 0; i < 2; i++) {
        NumberInfo *info = (i == 0) ? &info1 : &info2;
        printf("\n数値 %d の分析:\n", info->value);
        printf("  正の数: %s\n", info->is_positive ? "○" : "×");
        printf("  偶数: %s\n", info->is_even ? "○" : "×");
        printf("  標準範囲内（-100〜100）: %s\n", 
               info->is_in_standard_range ? "○" : "×");
    }
    
    // 条件演算子の高度な使用例
    printf("\n=== 条件演算子の高度な使用 ===\n");
    
    // 絶対値の差を条件演算子で計算
    int diff = (num1 > num2) ? (num1 - num2) : (num2 - num1);
    printf("絶対値の差: |%d - %d| = %d\n", num1, num2, diff);
    
    // 中央値の計算（3つの値）
    int median = (num1 > num2) ? 
                 ((num2 > third_value) ? num2 : 
                  ((num1 > third_value) ? third_value : num1)) :
                 ((num1 > third_value) ? num1 : 
                  ((num2 > third_value) ? third_value : num2));
    
    printf("3つの値 (%d, %d, %d) の中央値: %d\n", 
           num1, num2, third_value, median);
    
    return 0;
}

/*
実行例:
$ ./ex3_2_comparison_c99
===== 比較と論理演算 (C99版) =====
2つの整数を入力してください: 7 12

=== 結果 ===
入力値: 7, 12
最大値: 12
最小値: 7

=== 関係演算子による比較 (bool型使用) ===
7 == 12 : false
7 != 12 : true
7 <  12 : true
7 <= 12 : true
7 >  12 : false
7 >= 12 : false

=== 論理演算子の応用 ===
両方とも正の数: はい
少なくとも一方が正の数: はい
両方とも偶数: いいえ
同じ符号: はい

=== 3つの値の比較 ===
3つ目の値として0を使用します
3つの値 (7, 12, 0) の最大値: 12
3つの値 (7, 12, 0) の最小値: 0

=== 詳細な比較分析 ===

数値 7 の分析:
  正の数: ○
  偶数: ×
  標準範囲内（-100〜100）: ○

数値 12 の分析:
  正の数: ○
  偶数: ○
  標準範囲内（-100〜100）: ○

=== 条件演算子の高度な使用 ===
絶対値の差: |7 - 12| = 5
3つの値 (7, 12, 0) の中央値: 7

C99の改善点:
1. bool型による明確な真偽値表現
2. inline関数による再利用可能な比較処理
3. 構造体による情報の整理
4. 複合リテラルによる初期化
5. forループ内での変数宣言
*/