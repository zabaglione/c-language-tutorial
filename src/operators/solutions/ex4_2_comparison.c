/*
 * ファイル名: ex4_2_comparison.c
 * 演習4-2: 比較と論理演算
 * 説明: 関係演算子と論理演算子を使って最大値と最小値を求める
 * 規格: C90準拠
 */

#include <stdio.h>

int main(void)
{
    int num1, num2;
    int max, min;
    int comparison_result;
    
    printf("===== 比較と論理演算 =====\n");
    printf("2つの整数を入力してください: ");
    
    /* 入力の取得 */
    if (scanf("%d %d", &num1, &num2) != 2) {
        printf("エラー: 正しい整数を入力してください\n");
        return 1;
    }
    
    /* 条件演算子（三項演算子）のみで最大値と最小値を求める */
    max = (num1 > num2) ? num1 : num2;
    min = (num1 < num2) ? num1 : num2;
    
    printf("\n=== 結果 ===\n");
    printf("入力値: %d, %d\n", num1, num2);
    printf("最大値: %d\n", max);
    printf("最小値: %d\n", min);
    
    /* 関係演算子の詳細な比較 */
    printf("\n=== 関係演算子による比較 ===\n");
    printf("%d == %d : %d\n", num1, num2, num1 == num2);
    printf("%d != %d : %d\n", num1, num2, num1 != num2);
    printf("%d <  %d : %d\n", num1, num2, num1 < num2);
    printf("%d <= %d : %d\n", num1, num2, num1 <= num2);
    printf("%d >  %d : %d\n", num1, num2, num1 > num2);
    printf("%d >= %d : %d\n", num1, num2, num1 >= num2);
    
    /* 論理演算子の使用例 */
    printf("\n=== 論理演算子の応用 ===\n");
    
    /* 両方の数が正の数かチェック */
    comparison_result = (num1 > 0) && (num2 > 0);
    printf("両方とも正の数: %s\n", comparison_result ? "はい" : "いいえ");
    
    /* 少なくとも一方が正の数かチェック */
    comparison_result = (num1 > 0) || (num2 > 0);
    printf("少なくとも一方が正の数: %s\n", comparison_result ? "はい" : "いいえ");
    
    /* 両方の数が偶数かチェック */
    comparison_result = !(num1 % 2) && !(num2 % 2);
    printf("両方とも偶数: %s\n", comparison_result ? "はい" : "いいえ");
    
    /* 条件演算子のネストによる3つの値の比較（拡張例） */
    printf("\n=== 条件演算子の応用 ===\n");
    {
        int third_value = 0;
        int max_of_three;
        int min_of_three;
        
        printf("3つ目の値として0を使用します\n");
        
        /* 3つの値の最大値（ネストした条件演算子） */
        max_of_three = (num1 > num2) ? 
                       ((num1 > third_value) ? num1 : third_value) :
                       ((num2 > third_value) ? num2 : third_value);
        
        /* 3つの値の最小値（ネストした条件演算子） */
        min_of_three = (num1 < num2) ? 
                       ((num1 < third_value) ? num1 : third_value) :
                       ((num2 < third_value) ? num2 : third_value);
        
        printf("3つの値 (%d, %d, %d) の最大値: %d\n", 
               num1, num2, third_value, max_of_three);
        printf("3つの値 (%d, %d, %d) の最小値: %d\n", 
               num1, num2, third_value, min_of_three);
    }
    
    /* 値の範囲判定（条件演算子のみ使用） */
    printf("\n=== 範囲判定 ===\n");
    {
        const char *range1 = (num1 >= -10 && num1 <= 10) ? 
                            "範囲内（-10〜10）" : "範囲外";
        const char *range2 = (num2 >= -10 && num2 <= 10) ? 
                            "範囲内（-10〜10）" : "範囲外";
        
        printf("第1の値（%d）: %s\n", num1, range1);
        printf("第2の値（%d）: %s\n", num2, range2);
    }
    
    return 0;
}

/*
実行例:
$ ./ex3_2_comparison
===== 比較と論理演算 =====
2つの整数を入力してください: 7 12

=== 結果 ===
入力値: 7, 12
最大値: 12
最小値: 7

=== 関係演算子による比較 ===
7 == 12 : 0
7 != 12 : 1
7 <  12 : 1
7 <= 12 : 1
7 >  12 : 0
7 >= 12 : 0

=== 論理演算子の応用 ===
両方とも正の数: はい
少なくとも一方が正の数: はい
両方とも偶数: いいえ

=== 条件演算子の応用 ===
3つ目の値として0を使用します
3つの値 (7, 12, 0) の最大値: 12
3つの値 (7, 12, 0) の最小値: 0

=== 範囲判定 ===
第1の値（7）: 範囲内（-10〜10）
第2の値（12）: 範囲外

学習ポイント:
1. 条件演算子（三項演算子）による最大値・最小値の判定
2. 関係演算子（==, !=, <, <=, >, >=）の使用
3. 論理演算子（&&, ||, !）の使用
4. 条件演算子のネストによる複雑な条件判定
5. if文を使わない条件分岐の実装
*/