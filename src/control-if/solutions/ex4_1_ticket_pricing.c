/*
 * ファイル名: ex4_1_ticket_pricing.c
 * 演習4-1: 年齢による料金計算
 * 説明: 映画館の料金システムを実装するプログラム
 * 規格: C90準拠
 */
#include <stdio.h>

int main(void)
{
    /* 変数の宣言（C90では先頭で宣言） */
    int age;
    int price;
    char *category;
    
    printf("=== 映画館料金計算システム ===\n");
    printf("年齢を入力してください: ");
    scanf("%d", &age);
    
    /* 入力値の検証 */
    if (age < 0) {
        printf("エラー: 年齢は0以上の値を入力してください。\n");
        return 1;
    }
    
    if (age > 120) {
        printf("エラー: 年齢は120歳以下の値を入力してください。\n");
        return 1;
    }
    
    /* 年齢による料金分類 */
    if (age < 3) {
        price = 0;
        category = "幼児";
    } else if (age >= 3 && age <= 12) {
        price = 800;
        category = "子供";
    } else if (age >= 13 && age <= 18) {
        price = 1200;
        category = "学生";
    } else if (age >= 19 && age <= 65) {
        price = 1800;
        category = "大人";
    } else {
        price = 1200;
        category = "シニア";
    }
    
    /* 結果の表示 */
    printf("\n=== 料金計算結果 ===\n");
    printf("年齢: %d歳\n", age);
    printf("区分: %s\n", category);
    
    if (price == 0) {
        printf("料金: 無料\n");
    } else {
        printf("料金: %d円\n", price);
    }
    
    /* 特別なメッセージ */
    if (age < 3) {
        printf("お子様は保護者の同伴が必要です。\n");
    } else if (age >= 66) {
        printf("シニア割引が適用されました。\n");
    } else if (age >= 13 && age <= 18) {
        printf("学生証の提示をお願いします。\n");
    }
    
    printf("\nご利用ありがとうございます！\n");
    
    return 0;
}

/*
学習ポイント:
1. if-else if文による段階的な条件判定
2. 境界値の処理（<=, >=の使い分け）
3. 入力値の検証とエラーハンドリング
4. 論理演算子（&&）による範囲指定
5. 変数の適切な初期化と使用

実装のポイント:
- C90準拠のため、すべての変数を関数先頭で宣言
- 境界値（3歳、12歳、18歳、65歳）を正確に処理
- ユーザーフレンドリーなエラーメッセージ
- 明確な結果表示
*/