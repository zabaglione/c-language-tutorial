/*
 * C99バージョン - 必要に応じてC99機能を使用
 *
 * sizeof演算子のデモ
 * データ型のサイズ確認
 */
#include <stdio.h>

int main(void)
{
    printf("=== データ型のサイズ ===\n");
    printf("char: %lu バイト\n", sizeof(char));
    printf("short: %lu バイト\n", sizeof(short));
    printf("int: %lu バイト\n", sizeof(int));
    printf("long: %lu バイト\n", sizeof(long));
    printf("float: %lu バイト\n", sizeof(float));
    printf("double: %lu バイト\n", sizeof(double));
    
    /*
 * C99バージョン - 必要に応じてC99機能を使用
 * 変数のサイズ */
    int number = 42;
    printf("\n変数のサイズ:\n");
    printf("int number: %lu バイト\n", sizeof(number));
    
    return 0;
}