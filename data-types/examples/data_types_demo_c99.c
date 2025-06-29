/*
 * ファイル名: data_types_demo_c99.c
 * 説明: C言語の基本データ型の使用例（C99版）
 * 規格: C99準拠
 */

#include <stdio.h>

int main(void)
{
    printf("=== データ型のサイズと値 ===\n");

    // 整数型の変数宣言と初期化（使用箇所で宣言）
    char letter = 'A';
    printf("char     : %lu バイト, 値: %c (%d)\n",
           sizeof(char), letter, letter);

    short small_num = 1000;
    printf("short    : %lu バイト, 値: %d\n",
           sizeof(short), small_num);

    int age = 25;
    printf("int      : %lu バイト, 値: %d\n",
           sizeof(int), age);

    long big_num = 1234567L;
    printf("long     : %lu バイト, 値: %ld\n",
           sizeof(long), big_num);

    unsigned int positive = 100U;
    printf("unsigned : %lu バイト, 値: %u\n",
           sizeof(unsigned int), positive);

    // 浮動小数点型の変数宣言と初期化
    float pi_f = 3.14f;
    printf("float    : %lu バイト, 値: %.6f\n",
           sizeof(float), pi_f);

    double pi_d = 3.141592653589793;
    printf("double   : %lu バイト, 値: %.15f\n",
           sizeof(double), pi_d);

    // 演算の例
    printf("\n=== 基本演算 ===\n");
    printf("10 + 3 = %d\n", 10 + 3);
    printf("10 - 3 = %d\n", 10 - 3);
    printf("10 * 3 = %d\n", 10 * 3);
    printf("10 / 3 = %d (整数除算)\n", 10 / 3);
    printf("10 %% 3 = %d (剰余)\n", 10 % 3);
    printf("10.0 / 3.0 = %.2f (実数除算)\n", 10.0 / 3.0);

    return 0;
}
