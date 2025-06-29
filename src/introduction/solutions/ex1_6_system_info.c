/*
 * ファイル名: ex1_6_system_info.c
 * 演習1-6: 環境固有情報の調査
 * 説明: 環境固有の情報を調査・表示する
 * 規格: C90準拠
 */

#include <stdio.h>
#include <limits.h>

/*
 * エンディアンを判定する関数
 */
void check_endianness(void)
{
    union
    {
        unsigned int i;
        unsigned char c[sizeof(unsigned int)];
    } test;

    test.i = 0x12345678;

    printf("エンディアン判定:\n");
    if (test.c[0] == 0x78)
    {
        printf("- リトルエンディアン\n");
    }
    else if (test.c[0] == 0x12)
    {
        printf("- ビッグエンディアン\n");
    }
    else
    {
        printf("- 不明なエンディアン\n");
    }
}

/*
 * アーキテクチャ情報を表示する関数
 */
void show_architecture_info(void)
{
    printf("アーキテクチャ情報:\n");

    if (sizeof(void *) == 4)
    {
        printf("- 32ビットアーキテクチャ\n");
    }
    else if (sizeof(void *) == 8)
    {
        printf("- 64ビットアーキテクチャ\n");
    }
    else
    {
        printf("- 不明なアーキテクチャ（ポインタサイズ: %lu bytes）\n",
               (unsigned long)sizeof(void *));
    }
}

/*
 * OS情報を表示する関数
 */
void show_os_info(void)
{
    printf("オペレーティングシステム:\n");

#ifdef _WIN32
    printf("- Windows\n");
#elif defined(__APPLE__) && defined(__MACH__)
    printf("- macOS\n");
#elif defined(__linux__)
    printf("- Linux\n");
#elif defined(__unix__)
    printf("- Unix系OS\n");
#else
    printf("- 不明なOS\n");
#endif
}

/*
 * コンパイラ情報を表示する関数
 */
void show_compiler_info(void)
{
    printf("コンパイラ情報:\n");

#ifdef __GNUC__
    printf("- GCC %d.%d.%d\n", __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__);
#endif

#ifdef _MSC_VER
    printf("- Microsoft Visual C++ %d\n", _MSC_VER);
#endif

#ifdef __clang__
    printf("- Clang %d.%d.%d\n", __clang_major__, __clang_minor__, __clang_patchlevel__);
#endif

#ifdef __STDC_VERSION__
    printf("- C規格: ");
    if (__STDC_VERSION__ >= 201710L)
    {
        printf("C17\n");
    }
    else if (__STDC_VERSION__ >= 201112L)
    {
        printf("C11\n");
    }
    else if (__STDC_VERSION__ >= 199901L)
    {
        printf("C99\n");
    }
    else
    {
        printf("C90\n");
    }
#else
    printf("- C規格: C90またはコンパイラ固有\n");
#endif
}

/*
 * データ型のサイズを表示する関数
 */
void show_type_sizes(void)
{
    printf("データ型サイズ:\n");

    printf("- char: %lu bytes\n", (unsigned long)sizeof(char));
    printf("- short: %lu bytes\n", (unsigned long)sizeof(short));
    printf("- int: %lu bytes\n", (unsigned long)sizeof(int));
    printf("- long: %lu bytes\n", (unsigned long)sizeof(long));
    printf("- float: %lu bytes\n", (unsigned long)sizeof(float));
    printf("- double: %lu bytes\n", (unsigned long)sizeof(double));
    printf("- void*: %lu bytes\n", (unsigned long)sizeof(void *));

    printf("\nデータ型の範囲:\n");
    printf("- char: %d 〜 %d\n", CHAR_MIN, CHAR_MAX);
    printf("- short: %d 〜 %d\n", SHRT_MIN, SHRT_MAX);
    printf("- int: %d 〜 %d\n", INT_MIN, INT_MAX);
    printf("- long: %ld 〜 %ld\n", LONG_MIN, LONG_MAX);
}

/*
 * メイン関数
 */
int main(void)
{
    printf("=== システム情報調査プログラム ===\n\n");

    /* OS情報の表示 */
    show_os_info();
    printf("\n");

    /* コンパイラ情報の表示 */
    show_compiler_info();
    printf("\n");

    /* アーキテクチャ情報の表示 */
    show_architecture_info();
    printf("\n");

    /* エンディアン判定 */
    check_endianness();
    printf("\n");

    /* データ型サイズの表示 */
    show_type_sizes();

    printf("\n=== 調査完了 ===\n");

    return 0;
}
