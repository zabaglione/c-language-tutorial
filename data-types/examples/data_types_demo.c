/*
 * ファイル名: data_types_demo.c
 * 説明: C言語の基本データ型の使用例
 * 規格: C90準拠
 */

#include <stdio.h>

int main(void)
{
    /* 整数型の変数宣言と初期化 */
    char letter = 'A';
    short small_num = 1000;
    int age = 25;
    long big_num = 1234567L;
    unsigned int positive = 100U;

    /* 浮動小数点型の変数宣言と初期化 */
    float pi_f = 3.14f;
    double pi_d = 3.141592653589793;

    printf("=== データ型のサイズと値 ===\n");

    /* 各データ型のサイズを表示 */
    printf("char     : %lu バイト, 値: %c (%d)\n",
           sizeof(char), letter, letter);
    printf("short    : %lu バイト, 値: %d\n",
           sizeof(short), small_num);
    printf("int      : %lu バイト, 値: %d\n",
           sizeof(int), age);
    printf("long     : %lu バイト, 値: %ld\n",
           sizeof(long), big_num);
    printf("unsigned : %lu バイト, 値: %u\n",
           sizeof(unsigned int), positive);
    printf("float    : %lu バイト, 値: %.6f\n",
           sizeof(float), pi_f);
    printf("double   : %lu バイト, 値: %.15f\n",
           sizeof(double), pi_d);

    /* 演算の例 */
    printf("\n=== 基本演算 ===\n");
    printf("10 + 3 = %d\n", 10 + 3);
    printf("10 - 3 = %d\n", 10 - 3);
    printf("10 * 3 = %d\n", 10 * 3);
    printf("10 / 3 = %d (整数除算)\n", 10 / 3);
    printf("10 %% 3 = %d (剰余)\n", 10 % 3);
    printf("10.0 / 3.0 = %.2f (実数除算)\n", 10.0 / 3.0);

    return 0;
}
