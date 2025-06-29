/*
 * ファイル名: ex1_6_system_info_c99.c
 * 演習1-6: 環境固有情報の調査
 * 説明: 環境固有の情報を調査・表示する
 * 規格: C99準拠（//コメント、bool型、変数宣言の位置、複合リテラル）
 */

#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>

// エンディアンを判定する関数
void check_endianness(void)
{
    // C99: 複合リテラルを使用
    union {
        uint32_t i;
        uint8_t c[sizeof(uint32_t)];
    } test = { .i = 0x12345678 };

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

// アーキテクチャ情報を表示する関数
void show_architecture_info(void)
{
    printf("アーキテクチャ情報:\n");

    // C99: size_t型を使用
    size_t ptr_size = sizeof(void *);
    
    if (ptr_size == 4)
    {
        printf("- 32ビットアーキテクチャ\n");
    }
    else if (ptr_size == 8)
    {
        printf("- 64ビットアーキテクチャ\n");
    }
    else
    {
        printf("- 不明なアーキテクチャ（ポインタサイズ: %zu bytes）\n", ptr_size);
    }
}

// OS情報を表示する関数
void show_os_info(void)
{
    printf("オペレーティングシステム:\n");

    // C99: bool型を使用
    bool os_detected = false;

#ifdef _WIN32
    printf("- Windows\n");
    os_detected = true;
#elif defined(__APPLE__) && defined(__MACH__)
    printf("- macOS\n");
    os_detected = true;
#elif defined(__linux__)
    printf("- Linux\n");
    os_detected = true;
#elif defined(__unix__)
    printf("- Unix系OS\n");
    os_detected = true;
#endif

    if (!os_detected)
    {
        printf("- 不明なOS\n");
    }
}

// コンパイラ情報を表示する関数
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

    // C規格の判定
    printf("- C規格: ");
#ifdef __STDC_VERSION__
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
    printf("C90またはコンパイラ固有\n");
#endif
}

// データ型のサイズを表示する関数
void show_type_sizes(void)
{
    printf("データ型サイズ:\n");

    // C99: 構造体配列を使った整理
    struct {
        const char *name;
        size_t size;
    } types[] = {
        {"char", sizeof(char)},
        {"short", sizeof(short)},
        {"int", sizeof(int)},
        {"long", sizeof(long)},
        {"long long", sizeof(long long)},  // C99: long long型
        {"float", sizeof(float)},
        {"double", sizeof(double)},
        {"void*", sizeof(void *)},
        {"bool", sizeof(bool)}  // C99: bool型
    };

    // C99: 配列のサイズを計算
    size_t num_types = sizeof(types) / sizeof(types[0]);
    
    for (size_t i = 0; i < num_types; i++)
    {
        printf("- %s: %zu bytes\n", types[i].name, types[i].size);
    }

    printf("\nデータ型の範囲:\n");
    printf("- char: %d 〜 %d\n", CHAR_MIN, CHAR_MAX);
    printf("- short: %d 〜 %d\n", SHRT_MIN, SHRT_MAX);
    printf("- int: %d 〜 %d\n", INT_MIN, INT_MAX);
    printf("- long: %ld 〜 %ld\n", LONG_MIN, LONG_MAX);
#ifdef LLONG_MAX
    printf("- long long: %lld 〜 %lld\n", LLONG_MIN, LLONG_MAX);  // C99
#endif
}

// 追加: C99の機能を確認する関数
void show_c99_features(void)
{
    printf("C99の機能確認:\n");
    
    // 可変長配列（VLA）のテスト
    int n = 5;
    int vla[n];  // C99: 可変長配列
    printf("- 可変長配列（サイズ%d）: サポート済み\n", n);
    
    // bool型のテスト
    bool test = true;
    printf("- bool型: %s\n", test ? "サポート済み" : "未サポート");
    
    // inline関数のサポート
#ifdef __STDC_VERSION__
    if (__STDC_VERSION__ >= 199901L)
    {
        printf("- inline関数: サポート済み\n");
        printf("- //コメント: サポート済み\n");
        printf("- 複合リテラル: サポート済み\n");
    }
#endif
}

int main(void)
{
    printf("=== システム情報調査プログラム（C99版） ===\n\n");

    // OS情報の表示
    show_os_info();
    printf("\n");

    // コンパイラ情報の表示
    show_compiler_info();
    printf("\n");

    // アーキテクチャ情報の表示
    show_architecture_info();
    printf("\n");

    // エンディアン判定
    check_endianness();
    printf("\n");

    // データ型サイズの表示
    show_type_sizes();
    printf("\n");

    // C99機能の確認
    show_c99_features();

    printf("\n=== 調査完了 ===\n");

    return 0;
}
