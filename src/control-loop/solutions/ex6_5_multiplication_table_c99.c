/*
 * ファイル名: ex6_5_multiplication_table_c99.c
 * 演習6-5: 掛け算表
 * 説明: 9×9の掛け算表を表示するプログラム
 * 規格: C99準拠
 */
#include <stdio.h>

int main(void)
{
    printf("=== 9×9の掛け算表 ===\n\n");
    
    // 列ヘッダーの表示
    printf("   ");
    for (int j = 1; j <= 9; j++) {
        printf("%3d", j);
    }
    printf("\n");
    
    // 区切り線の表示
    printf("   ");
    for (int j = 1; j <= 9; j++) {
        printf("---");
    }
    printf("\n");
    
    // 掛け算表の本体
    for (int i = 1; i <= 9; i++) {
        // 行ヘッダーの表示
        printf("%2d|", i);
        
        // 各列の計算結果を表示
        for (int j = 1; j <= 9; j++) {
            int result = i * j;
            printf("%3d", result);
        }
        printf("\n");
    }
    
    printf("\n=== 掛け算表の完成 ===\n");
    
    // 簡単な統計情報
    printf("\n統計情報:\n");
    printf("- 最小値: 1 (1×1)\n");
    printf("- 最大値: 81 (9×9)\n");
    printf("- 表示された計算結果の総数: 81個\n");
    
    // 特別な値の表示
    printf("\n完全平方数:\n");
    for (int i = 1; i <= 9; i++) {
        int result = i * i;
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
- C99準拠のため、変数を使用箇所の近くで宣言
- for文内でのループ変数宣言
- 変数の初期化を宣言と同時に実行
- コメントに//スタイルを使用
- %3d書式指定子で3桁の右詰め表示
*/
