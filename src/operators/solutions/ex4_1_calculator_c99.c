/*
 * ファイル名: ex4_1_calculator_c99.c
 * 演習4-1: 四則演算計算機
 * 説明: 2つの整数を入力として受け取り、基本的な算術演算の結果を表示
 * 規格: C99準拠
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// C99: inline関数による効率的な計算
static inline int safe_divide(int a, int b, bool *success)
{
    if (b == 0) {
        *success = false;
        return 0;
    }
    *success = true;
    return a / b;
}

static inline int safe_modulo(int a, int b, bool *success)
{
    if (b == 0) {
        *success = false;
        return 0;
    }
    *success = true;
    return a % b;
}

// C99: inline関数による絶対値計算
static inline int abs_value(int n)
{
    return (n < 0) ? -n : n;
}

int main(void)
{
    printf("===== 四則演算計算機 (C99版) =====\n");
    printf("2つの整数を入力してください: ");
    
    // C99: 使用箇所での変数宣言
    int num1, num2;
    if (scanf("%d %d", &num1, &num2) != 2) {
        printf("エラー: 正しい整数を入力してください\n");
        return 1;
    }
    
    // 基本的な算術演算
    printf("\n=== 計算結果 ===\n");
    printf("%d + %d = %d\n", num1, num2, num1 + num2);
    printf("%d - %d = %d\n", num1, num2, num1 - num2);
    printf("%d * %d = %d\n", num1, num2, num1 * num2);
    
    // C99: bool型を使った安全な除算
    bool div_success, mod_success;
    int div_result = safe_divide(num1, num2, &div_success);
    int mod_result = safe_modulo(num1, num2, &mod_success);
    
    if (div_success) {
        printf("%d / %d = %d (整数除算)\n", num1, num2, div_result);
        printf("%d %% %d = %d (剰余)\n", num1, num2, mod_result);
        printf("%d / %d = %.2f (実数除算)\n", 
               num1, num2, (double)num1 / num2);
    } else {
        printf("%d / %d = エラー (ゼロ除算)\n", num1, num2);
        printf("%d %% %d = エラー (ゼロ除算)\n", num1, num2);
    }
    
    // 追加情報の表示
    printf("\n=== 追加情報 ===\n");
    printf("入力値の絶対値: |%d| = %d, |%d| = %d\n", 
           num1, abs_value(num1), num2, abs_value(num2));
    
    // C99: forループ内での変数宣言を使った範囲チェック
    printf("\n=== 値の範囲チェック ===\n");
    for (int i = 0; i < 2; i++) {
        int value = (i == 0) ? num1 : num2;
        const char *name = (i == 0) ? "第1引数" : "第2引数";
        
        if (value > 0) {
            printf("%s (%d) は正の数です\n", name, value);
        } else if (value < 0) {
            printf("%s (%d) は負の数です\n", name, value);
        } else {
            printf("%s (%d) はゼロです\n", name, value);
        }
    }
    
    // 代入演算子のデモンストレーション
    printf("\n=== 代入演算子のデモ (C99拡張) ===\n");
    int temp = num1;
    printf("初期値: temp = %d\n", temp);
    
    // C99: 複合リテラルを使った演算の記録
    typedef struct {
        const char *operation;
        int result;
    } Operation;
    
    Operation ops[] = {
        {"+=", (temp += num2, temp)},
        {"-=", (temp -= num2, temp)},
        {"*=", (num2 != 0) ? (temp *= num2, temp) : temp},
        {"/=", (num2 != 0) ? (temp /= num2, temp) : temp},
        {"%=", (num2 != 0) ? (temp %= num2, temp) : temp}
    };
    
    for (size_t i = 0; i < sizeof(ops) / sizeof(ops[0]); i++) {
        if (i < 2 || num2 != 0) {
            printf("temp %s %d -> temp = %d\n", 
                   ops[i].operation, num2, ops[i].result);
        }
    }
    
    // C99: 追加の統計情報
    printf("\n=== 統計情報 ===\n");
    int max = (num1 > num2) ? num1 : num2;
    int min = (num1 < num2) ? num1 : num2;
    double average = (num1 + num2) / 2.0;
    
    printf("最大値: %d\n", max);
    printf("最小値: %d\n", min);
    printf("平均値: %.1f\n", average);
    
    return 0;
}

/*
実行例:
$ ./ex3_1_calculator_c99
===== 四則演算計算機 (C99版) =====
2つの整数を入力してください: 10 3

=== 計算結果 ===
10 + 3 = 13
10 - 3 = 7
10 * 3 = 30
10 / 3 = 3 (整数除算)
10 % 3 = 1 (剰余)
10 / 3 = 3.33 (実数除算)

=== 追加情報 ===
入力値の絶対値: |10| = 10, |3| = 3

=== 値の範囲チェック ===
第1引数 (10) は正の数です
第2引数 (3) は正の数です

=== 代入演算子のデモ (C99拡張) ===
初期値: temp = 10
temp += 3 -> temp = 13
temp -= 3 -> temp = 10
temp *= 3 -> temp = 30
temp /= 3 -> temp = 10
temp %= 3 -> temp = 1

=== 統計情報 ===
最大値: 10
最小値: 3
平均値: 6.5

C99の改善点:
1. bool型による明確な成功/失敗の表現
2. inline関数による効率的な処理
3. 使用箇所での変数宣言
4. forループ内での変数宣言
5. 構造体と配列による演算結果の管理
*/