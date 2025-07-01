/*
 * ファイル名: sizeof_demo.c
 * 説明: sizeof演算子の使用例（C90版）
 * 規格: C90準拠
 */
#include <stdio.h>

int main(void)
{
    /* 変数の宣言 */
    int num = 42;
    double pi = 3.14159;
    char str[] = "Hello";
    int array[10];
    size_t i = 0;
    
    printf("=== sizeof演算子の2つの形式 ===\n\n");
    
    /* 形式1: sizeof(型名) - 括弧が必要 */
    printf("形式1: sizeof(型名) - 括弧が必要\n");
    printf("sizeof(int)      = %lu バイト\n", (unsigned long)sizeof(int));
    printf("sizeof(double)   = %lu バイト\n", (unsigned long)sizeof(double));
    printf("sizeof(char)     = %lu バイト\n", (unsigned long)sizeof(char));
    printf("sizeof(long)     = %lu バイト\n", (unsigned long)sizeof(long));
    printf("sizeof(void*)    = %lu バイト (ポインタサイズ)\n", (unsigned long)sizeof(void*));
    
    printf("\n");
    
    /* 形式2: sizeof 式 - 括弧は任意 */
    printf("形式2: sizeof 式 - 括弧は任意\n");
    printf("sizeof num       = %lu バイト\n", (unsigned long)sizeof num);
    printf("sizeof pi        = %lu バイト\n", (unsigned long)sizeof pi);
    printf("sizeof str       = %lu バイト (null終端含む)\n", (unsigned long)sizeof str);
    printf("sizeof array     = %lu バイト (10要素×%luバイト)\n", 
           (unsigned long)sizeof array, (unsigned long)sizeof(int));
    
    /* 括弧付きでも動作する */
    printf("sizeof(num)      = %lu バイト (括弧付きでもOK)\n", (unsigned long)sizeof(num));
    
    printf("\n");
    
    /* 配列の要素数を計算 */
    printf("=== 配列の要素数計算 ===\n");
    printf("array の要素数   = %lu\n", (unsigned long)(sizeof array / sizeof array[0]));
    printf("str の要素数     = %lu (null終端含む)\n", (unsigned long)(sizeof str / sizeof str[0]));
    
    printf("\n");
    
    /* sizeof演算子の特性 */
    printf("=== sizeof演算子の特性 ===\n");
    printf("sizeof はコンパイル時に評価される\n");
    printf("sizeof(i)        = %lu\n", (unsigned long)sizeof(i));
    i++;  /* インクリメント */
    printf("i の値           = %lu (増加した)\n", (unsigned long)i);
    
    printf("\n");
    
    /* ポインタと配列の違い */
    printf("=== ポインタと配列のサイズの違い ===\n");
    {
        char arr[] = "Hello World";
        char *ptr = "Hello World";
        
        printf("char arr[]       = %lu バイト (配列全体)\n", (unsigned long)sizeof arr);
        printf("char *ptr        = %lu バイト (ポインタサイズ)\n", (unsigned long)sizeof ptr);
    }
    
    return 0;
}