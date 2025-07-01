/*
 * ファイル名: ex5_4_leap_year.c
 * 演習5-4: うるう年判定
 * 説明: 西暦年を入力してうるう年かどうか判定するプログラム
 * 規格: C90準拠
 */
#include <stdio.h>

int main(void)
{
    /* 変数の宣言（C90では先頭で宣言） */
    int year;
    int is_leap_year;
    
    printf("=== うるう年判定プログラム ===\n");
    printf("西暦年を入力してください: ");
    scanf("%d", &year);
    
    /* 入力値の検証 */
    if (year < 1) {
        printf("エラー: 西暦1年以降を入力してください。\n");
        return 1;
    }
    
    if (year > 3000) {
        printf("エラー: 西暦3000年以下を入力してください。\n");
        return 1;
    }
    
    /* うるう年判定のロジック */
    /* 1. 4で割り切れる年はうるう年 */
    /* 2. ただし、100で割り切れる年は平年 */
    /* 3. ただし、400で割り切れる年はうるう年 */
    
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        is_leap_year = 1;
    } else {
        is_leap_year = 0;
    }
    
    /* 結果の表示 */
    printf("\n=== 判定結果 ===\n");
    printf("入力年: %d年\n", year);
    
    if (is_leap_year) {
        printf("判定: うるう年です\n");
        printf("2月は29日まであります。\n");
    } else {
        printf("判定: 平年です\n");
        printf("2月は28日まであります。\n");
    }
    
    /* 詳細な判定理由の表示 */
    printf("\n=== 判定理由 ===\n");
    
    if (year % 4 != 0) {
        printf("4で割り切れないため、平年です。\n");
    } else if (year % 100 != 0) {
        printf("4で割り切れ、かつ100で割り切れないため、うるう年です。\n");
    } else if (year % 400 != 0) {
        printf("100で割り切れ、かつ400で割り切れないため、平年です。\n");
    } else {
        printf("400で割り切れるため、うるう年です。\n");
    }
    
    /* 歴史的な情報 */
    printf("\n=== 豆知識 ===\n");
    
    if (year == 2000) {
        printf("2000年は特別なうるう年でした（400で割り切れる）。\n");
    } else if (year == 1900) {
        printf("1900年は100で割り切れるが400で割り切れないため平年でした。\n");
    } else if (year == 2100) {
        printf("2100年も100で割り切れるが400で割り切れないため平年になります。\n");
    }
    
    /* グレゴリオ暦の説明 */
    if (year >= 1582) {
        printf("グレゴリオ暦（現在の暦）での判定です。\n");
    } else {
        printf("注意: 1582年以前はユリウス暦が使われていました。\n");
    }
    
    /* 次のうるう年/平年の計算 */
    printf("\n=== 次のうるう年 ===\n");
    
    if (is_leap_year) {
        /* 現在がうるう年の場合、次のうるう年を探す */
        int next_year;
        for (next_year = year + 1; next_year <= year + 8; next_year++) {
            if ((next_year % 4 == 0 && next_year % 100 != 0) || (next_year % 400 == 0)) {
                printf("次のうるう年: %d年\n", next_year);
                break;
            }
        }
    } else {
        /* 現在が平年の場合、次のうるう年を探す */
        int next_year;
        for (next_year = year + 1; next_year <= year + 4; next_year++) {
            if ((next_year % 4 == 0 && next_year % 100 != 0) || (next_year % 400 == 0)) {
                printf("次のうるう年: %d年\n", next_year);
                break;
            }
        }
    }
    
    return 0;
}

/*
学習ポイント:
1. 複雑な論理演算子の組み合わせ
2. 剰余演算子（%）による割り切れる判定
3. 条件の優先順位と論理構造
4. 複合条件式の読みやすい書き方
5. ループを使った条件検索

実装のポイント:
- C90準拠のため、すべての変数を関数先頭で宣言
- うるう年判定の複雑なルールを正確に実装
- 論理演算子（&&, ||）の適切な使用
- 条件式を段階的に説明
- 歴史的背景も含めた教育的な内容
*/