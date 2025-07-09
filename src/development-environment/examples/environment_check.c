/*
 * environment_check.c - C言語開発環境確認プログラム
 *
 * このプログラムは開発環境が正しく設定されているかを確認します。
 * 各種C規格でコンパイルして動作を確認してください。
 */

#include <stdio.h>
#include <limits.h>

/*
 * 環境情報を表示する関数
 */
void print_environment_info(void)
{
    printf("=== C言語開発環境確認 ===\n\n");

    /* コンパイラ情報 */
    printf("コンパイラ情報:\n");

#ifdef __GNUC__
    printf("- GCC version: %d.%d.%d\n", __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__);
#endif

#ifdef _MSC_VER
    printf("- Microsoft Visual C++ version: %d\n", _MSC_VER);
#endif

#ifdef __clang__
    printf("- Clang version: %d.%d.%d\n", __clang_major__, __clang_minor__, __clang_patchlevel__);
#endif

    /* C規格情報 */
    printf("\nC規格情報:\n");

#ifdef __STDC_VERSION__
    printf("- __STDC_VERSION__: %ldL\n", __STDC_VERSION__);

    if (__STDC_VERSION__ >= 202311L)
    {
        printf("- 対応規格: C23\n");
    }
    else if (__STDC_VERSION__ >= 201710L)
    {
        printf("- 対応規格: C17 (C18)\n");
    }
    else if (__STDC_VERSION__ >= 201112L)
    {
        printf("- 対応規格: C11\n");
    }
    else if (__STDC_VERSION__ >= 199901L)
    {
        printf("- 対応規格: C99\n");
    }
    else
    {
        printf("- 対応規格: C90 (ANSI C)\n");
    }
#else
    printf("- 対応規格: C90 (ANSI C) または未定義\n");
#endif

    /* システム情報 */
    printf("\nシステム情報:\n");

    printf("- int型サイズ: %lu bytes\n", (unsigned long)sizeof(int));
    printf("- long型サイズ: %lu bytes\n", (unsigned long)sizeof(long));
    printf("- ポインタサイズ: %lu bytes\n", (unsigned long)sizeof(void *));
    printf("- char型範囲: %d 〜 %d\n", CHAR_MIN, CHAR_MAX);
    printf("- int型範囲: %d 〜 %d\n", INT_MIN, INT_MAX);
}

/*
 * 基本的な計算テスト
 */
void test_basic_operations(void)
{
    int a = 10;
    int b = 3;
    int result;

    printf("\n=== 基本演算テスト ===\n");

    result = a + b;
    printf("%d + %d = %d\n", a, b, result);

    result = a - b;
    printf("%d - %d = %d\n", a, b, result);

    result = a * b;
    printf("%d * %d = %d\n", a, b, result);

    result = a / b;
    printf("%d / %d = %d\n", a, b, result);

    result = a % b;
    printf("%d %% %d = %d\n", a, b, result);

    printf("基本演算テスト: 正常完了\n");
}

/*
 * メイン関数
 */
int main(void)
{
    printf("C言語開発環境確認プログラム\n");
    printf("コンパイル日時: %s %s\n\n", __DATE__, __TIME__);

    /* 環境情報の表示 */
    print_environment_info();

    /* 基本演算のテスト */
    test_basic_operations();

    printf("\n=== 環境確認完了 ===\n");
    printf("この出力が正常に表示されれば、開発環境は正しく設定されています。\n");

    return 0;
}
