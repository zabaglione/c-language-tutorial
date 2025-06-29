/*
 * ファイル名: ex3_1_variable_declaration.c
 * 演習3-1: 変数宣言と初期化
 * 説明: さまざまなデータ型の変数を宣言し、初期化して出力する
 * 規格: C90準拠
 */
#include <stdio.h>

int main(void)
{
    /* 整数型の変数宣言と初期化 */
    char initial = 'C';
    short year = 2024;
    int score = 95;
    long population = 125000000L;
    unsigned int count = 42U;
    
    /* 浮動小数点型の変数宣言と初期化 */
    float temperature = 23.5f;
    double precision_value = 3.141592653589793;
    
    /* 各種定数の定義 */
    const int MAX_STUDENTS = 30;
    const double GRAVITY = 9.8;
    
    printf("=== 変数宣言と初期化の例 ===\n");
    
    /* 整数型変数の出力 */
    printf("文字型 (char)      : %c\n", initial);
    printf("短整数型 (short)   : %d\n", year);
    printf("整数型 (int)       : %d\n", score);
    printf("長整数型 (long)    : %ld\n", population);
    printf("符号なし整数 (unsigned): %u\n", count);
    
    /* 浮動小数点型変数の出力 */
    printf("単精度浮動小数点 (float) : %.2f\n", temperature);
    printf("倍精度浮動小数点 (double): %.15f\n", precision_value);
    
    /* 定数の出力 */
    printf("定数 MAX_STUDENTS : %d\n", MAX_STUDENTS);
    printf("定数 GRAVITY      : %.1f\n", GRAVITY);
    
    /* データ型のサイズ情報 */
    printf("\n=== データ型のサイズ ===\n");
    printf("char     : %lu バイト\n", sizeof(char));
    printf("short    : %lu バイト\n", sizeof(short));
    printf("int      : %lu バイト\n", sizeof(int));
    printf("long     : %lu バイト\n", sizeof(long));
    printf("unsigned : %lu バイト\n", sizeof(unsigned int));
    printf("float    : %lu バイト\n", sizeof(float));
    printf("double   : %lu バイト\n", sizeof(double));
    
    /* 実際の値の範囲例 */
    printf("\n=== 値の範囲例 ===\n");
    printf("char 最大値の例: %d\n", 127);
    printf("char 最小値の例: %d\n", -128);
    printf("unsigned int 最大値の例: %u\n", 4294967295U);
    
    return 0;
}

/*
学習ポイント:
1. 各データ型の適切な宣言方法
2. 初期化の重要性
3. printf関数での型に応じた書式指定子の使用
4. sizeof演算子によるサイズ確認
5. 定数の定義と使用
6. 各型の値の範囲の理解

データ型の使い分け:
- char: 文字データ、小さな整数
- short: 小さな整数（メモリ節約）
- int: 一般的な整数計算
- long: 大きな整数
- unsigned: 負の値を扱わない場合
- float: 精度をそれほど要求しない実数
- double: 高精度な実数計算
*/
