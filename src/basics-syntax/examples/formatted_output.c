/*
 * ファイル名: formatted_output.c
 * 説明: printf関数のさまざまなフォーマット指定子を学習
 * 規格: C90準拠
 */

#include <stdio.h>

int main(void)
{
    /* 基本的な文字列出力 */
    printf("=== C言語フォーマット出力 ===\n");

    /* 整数の出力 */
    printf("整数: %d\n", 42);
    printf("負の整数: %d\n", -123);

    /* 文字の出力 */
    printf("文字: %c\n", 'A');
    printf("文字コード: %c\n", 65); /* Aのアスキーコード */

    /* 文字列の出力 */
    printf("文字列: %s\n", "Hello, World!");

    /* 浮動小数点数の出力 */
    printf("浮動小数点数: %f\n", 3.14159);
    printf("小数点以下2桁: %.2f\n", 3.14159);

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
    printf("名前: %s, 年齢: %d歳, 身長: %.1fcm\n", "田中太郎", 25, 175.5);

    return 0;
}
