/*
 * ファイル名: sizeof_demo_c99.c
 * 説明: sizeof演算子の使用例（C99版）
 * 規格: C99準拠
 */
#include <stdio.h>

int main(void)
{
    printf("=== sizeof演算子の2つの形式 ===\n\n");
    
    // 形式1: sizeof(型名) - 括弧が必要
    printf("形式1: sizeof(型名) - 括弧が必要\n");
    printf("sizeof(int)      = %zu バイト\n", sizeof(int));
    printf("sizeof(double)   = %zu バイト\n", sizeof(double));
    printf("sizeof(char)     = %zu バイト\n", sizeof(char));
    printf("sizeof(long)     = %zu バイト\n", sizeof(long));
    printf("sizeof(void*)    = %zu バイト (ポインタサイズ)\n", sizeof(void*));
    
    printf("\n");
    
    // 変数の宣言（使用箇所で宣言）
    int num = 42;
    double pi = 3.14159;
    char str[] = "Hello";
    int array[10];
    
    // 形式2: sizeof 式 - 括弧は任意
    printf("形式2: sizeof 式 - 括弧は任意\n");
    printf("sizeof num       = %zu バイト\n", sizeof num);
    printf("sizeof pi        = %zu バイト\n", sizeof pi);
    printf("sizeof str       = %zu バイト (null終端含む)\n", sizeof str);
    printf("sizeof array     = %zu バイト (10要素×%zuバイト)\n", 
           sizeof array, sizeof(int));
    
    // 括弧付きでも動作する
    printf("sizeof(num)      = %zu バイト (括弧付きでもOK)\n", sizeof(num));
    
    printf("\n");
    
    // 配列の要素数を計算
    printf("=== 配列の要素数計算 ===\n");
    printf("array の要素数   = %zu\n", sizeof array / sizeof array[0]);
    printf("str の要素数     = %zu (null終端含む)\n", sizeof str / sizeof str[0]);
    
    printf("\n");
    
    // sizeof演算子の特性
    printf("=== sizeof演算子の特性 ===\n");
    printf("sizeof はコンパイル時に評価される\n");
    size_t i = 0;
    printf("sizeof(i)        = %zu\n", sizeof(i));
    i++;  // インクリメント
    printf("i の値           = %zu (増加した)\n", i);
    
    printf("\n");
    
    // ポインタと配列の違い
    printf("=== ポインタと配列のサイズの違い ===\n");
    char arr[] = "Hello World";
    char *ptr = "Hello World";
    
    printf("char arr[]       = %zu バイト (配列全体)\n", sizeof arr);
    printf("char *ptr        = %zu バイト (ポインタサイズ)\n", sizeof ptr);
    
    printf("\n");
    
    // C99の新機能: 可変長配列（VLA）
    printf("=== C99: 可変長配列のサイズ ===\n");
    int n = 5;
    int vla[n];  // 可変長配列
    printf("VLA[%d]のサイズ  = %zu バイト\n", n, sizeof vla);
    
    return 0;
}