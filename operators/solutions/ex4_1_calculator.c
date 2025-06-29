/*
 * ファイル名: ex4_1_calculator.c
 * 演習4-1: 四則演算計算機
 * 説明: 2つの整数を入力として受け取り、基本的な算術演算の結果を表示
 * 規格: C90準拠
 */

#include <stdio.h>

int main(void)
{
    int num1, num2;
    int add_result, sub_result, mul_result;
    
    printf("===== 四則演算計算機 =====\n");
    printf("2つの整数を入力してください: ");
    
    /* 入力の取得 */
    if (scanf("%d %d", &num1, &num2) != 2) {
        printf("エラー: 正しい整数を入力してください\n");
        return 1;
    }
    
    /* 基本的な算術演算 */
    add_result = num1 + num2;
    sub_result = num1 - num2;
    mul_result = num1 * num2;
    
    /* 結果の表示 */
    printf("\n=== 計算結果 ===\n");
    printf("%d + %d = %d\n", num1, num2, add_result);
    printf("%d - %d = %d\n", num1, num2, sub_result);
    printf("%d * %d = %d\n", num1, num2, mul_result);
    
    /* 除算と剰余（ゼロ除算チェック付き） */
    if (num2 != 0) {
        printf("%d / %d = %d (整数除算)\n", num1, num2, num1 / num2);
        printf("%d %% %d = %d (剰余)\n", num1, num2, num1 % num2);
        
        /* 実数除算も表示 */
        printf("%d / %d = %.2f (実数除算)\n", 
               num1, num2, (double)num1 / num2);
    } else {
        printf("%d / %d = エラー (ゼロ除算)\n", num1, num2);
        printf("%d %% %d = エラー (ゼロ除算)\n", num1, num2);
    }
    
    /* 追加情報の表示 */
    printf("\n=== 追加情報 ===\n");
    printf("入力値の絶対値: |%d| = %d, |%d| = %d\n", 
           num1, (num1 < 0) ? -num1 : num1,
           num2, (num2 < 0) ? -num2 : num2);
    
    /* 代入演算子のデモンストレーション */
    printf("\n=== 代入演算子のデモ ===\n");
    {
        int temp = num1;
        printf("初期値: temp = %d\n", temp);
        
        temp += num2;
        printf("temp += %d -> temp = %d\n", num2, temp);
        
        temp -= num2;
        printf("temp -= %d -> temp = %d\n", num2, temp);
        
        if (num2 != 0) {
            temp *= num2;
            printf("temp *= %d -> temp = %d\n", num2, temp);
            
            temp /= num2;
            printf("temp /= %d -> temp = %d\n", num2, temp);
            
            temp %= num2;
            printf("temp %%= %d -> temp = %d\n", num2, temp);
        }
    }
    
    return 0;
}

/*
実行例:
$ ./ex3_1_calculator
===== 四則演算計算機 =====
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

=== 代入演算子のデモ ===
初期値: temp = 10
temp += 3 -> temp = 13
temp -= 3 -> temp = 10
temp *= 3 -> temp = 30
temp /= 3 -> temp = 10
temp %= 3 -> temp = 1

学習ポイント:
1. 基本的な算術演算子（+, -, *, /, %）の使用
2. ゼロ除算のエラーチェック
3. 整数除算と実数除算の違い
4. 代入演算子（+=, -=, *=, /=, %=）の動作
5. 条件演算子による絶対値の計算
*/