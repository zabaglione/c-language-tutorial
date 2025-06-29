/*
 * ファイル名: formatted_output_c99.c
 * 説明: printf関数のさまざまなフォーマット指定子を学習（C99版）
 * 規格: C99準拠
 */

#include <stdio.h>

int main(void)
{
    /* 基本的な文字列出力 */
    printf("=== C言語フォーマット出力 ===\n");

    /* 整数データの出力 */
    int positive_num = 42;  /* C99：必要な時点で変数宣言 */
    printf("整数: %d\n", positive_num);
    
    int negative_num = -123;  /* C99：必要な時点で変数宣言 */
    printf("負の整数: %d\n", negative_num);

    /* 文字データの出力 */
    char letter = 'A';  /* C99：必要な時点で変数宣言 */
    printf("文字: %c\n", letter);
    printf("文字コード: %c\n", 65); /* Aのアスキーコード */

    /* 文字列の出力 */
    printf("文字列: %s\n", "Hello, World!");

    /* 浮動小数点数の出力 */
    double pi = 3.14159;  /* C99：必要な時点で変数宣言 */
    printf("浮動小数点数: %f\n", pi);
    printf("小数点以下2桁: %.2f\n", pi);

    /* エスケープシーケンスの使用 */
    printf("\n--- エスケープシーケンス ---\n");
    printf("改行\nとタブ\tの使用例：\n");
    printf("項目1\t項目2\t項目3\n");
    printf("値A\t値B\t値C\n");

    /* 特殊文字の表示 */
    printf("\n--- 特殊文字の表示 ---\n");
    printf("ダブルクォート: \"Hello\"\n");
    printf("バックスラッシュ: C:\\Program Files\\\n");

    /* フォーマット指定子の組み合わせ */
    printf("\n--- 複合表示 ---\n");
    char name[] = "田中太郎";  /* C99：必要な時点で変数宣言 */
    int age = 25;  /* C99：必要な時点で変数宣言 */
    double height = 175.5;  /* C99：必要な時点で変数宣言 */
    printf("名前: %s, 年齢: %d歳, 身長: %.1fcm\n", name, age, height);

    return 0;
}

/*
C99での変更点:
- 各変数を必要な時点で宣言
- より読みやすいコード構造
- 変数の役割がより明確になる配置
- 配列の初期化方法も活用

学習ポイント（C90版と共通）:
1. printf関数の基本的な使用方法
2. 各種データ型の書式指定子（%d, %c, %s, %f）
3. エスケープシーケンス（\n, \t, \", \\）
4. フィールド幅や精度の指定（%.2f等）
5. 複数の値を組み合わせた出力
*/