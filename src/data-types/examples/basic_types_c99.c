/*
 * C99バージョン - 必要に応じてC99機能を使用
 *
 * 基本データ型のデモ
 * 各データ型の宣言と使用方法
 */
#include <stdio.h>

int main(void)
{
    /*
 * C99バージョン - 必要に応じてC99機能を使用
 * 整数型 */
    int age = 25;
    char letter = 'A';
    short small_num = 1000;
    long big_num = 1234567L;
    
    /*
 * C99バージョン - 必要に応じてC99機能を使用
 * 浮動小数点型 */
    float pi_f = 3.14f;
    double pi_d = 3.141592653589793;
    
    /*
 * C99バージョン - 必要に応じてC99機能を使用
 * 符号なし型 */
    unsigned int positive = 100U;
    
    printf("=== 基本データ型 ===\n");
    printf("int: %d\n", age);
    printf("char: %c (%d)\n", letter, letter);
    printf("short: %d\n", small_num);
    printf("long: %ld\n", big_num);
    printf("float: %.2f\n", pi_f);
    printf("double: %.10f\n", pi_d);
    printf("unsigned int: %u\n", positive);
    
    return 0;
}