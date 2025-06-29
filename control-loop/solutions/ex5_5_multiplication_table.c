/*
 * ファイル名: ex5_5_multiplication_table.c
 * 演習5-5: 掛け算表
 * 説明: 9×9の掛け算表を表示するプログラム
 * 規格: C90準拠
 */
#include <stdio.h>

int main(void)
{
    /* 変数の宣言（C90では先頭で宣言） */
    int i, j;
    int result;
    
    printf("=== 9×9の掛け算表 ===\n\n");
    
    /* 列ヘッダーの表示 */
    printf("   ");
    for (j = 1; j <= 9; j++) {
        printf("%3d", j);
    }
    printf("\n");
    
    /* 区切り線の表示 */
    printf("   ");
    for (j = 1; j <= 9; j++) {
        printf("---");
    }
    printf("\n");
    
    /* 掛け算表の本体 */
    for (i = 1; i <= 9; i++) {
        /* 行ヘッダーの表示 */
        printf("%2d|", i);
        
        /* 各列の計算結果を表示 */
        for (j = 1; j <= 9; j++) {
            result = i * j;
            printf("%3d", result);
        }
        printf("\n");
    }
    
    printf("\n=== 掛け算表の完成 ===\n");
    
    /* 簡単な統計情報 */
    printf("\n統計情報:\n");
    printf("- 最小値: 1 (1×1)\n");
    printf("- 最大値: 81 (9×9)\n");
    printf("- 表示された計算結果の総数: 81個\n");
    
    /* 特別な値の表示 */
    printf("\n完全平方数:\n");
    for (i = 1; i <= 9; i++) {
        result = i * i;
        printf("%d×%d=%d ", i, i, result);
    }
    printf("\n");
    
    return 0;
}

/*
学習ポイント:
1. ネストしたfor文による表形式データの生成
2. printf()の書式指定子による桁揃え
3. 表のヘッダーと区切り線の作成
4. 二重ループでの計算処理

実装のポイント:
- C90準拠のため、すべての変数を関数先頭で宣言
- %3d書式指定子で3桁の右詰め表示
- 行と列のヘッダーで見やすい表を作成
- ネストしたループでの計算と表示
- 統計情報と特別な値の追加表示
*/
