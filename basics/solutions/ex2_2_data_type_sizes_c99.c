/*
 * ファイル名: ex2_2_data_type_sizes_c99.c
 * 課題2-2: データ型サイズ確認 (C99版)
 * 説明: 各データ型のサイズと範囲を表示するプログラム
 * 規格: C99準拠
 */

#include <stdio.h>
#include <limits.h>

int main(void)
{
    printf("=== C言語データ型情報 ===\n");
    
    // データ型のサイズを表示
    printf("char: %zuバイト, 範囲: %d 〜 %d\n", 
           sizeof(char), CHAR_MIN, CHAR_MAX);
    printf("int: %zuバイト, 範囲: %d 〜 %d\n", 
           sizeof(int), INT_MIN, INT_MAX);
    printf("float: %zuバイト\n", sizeof(float));
    printf("double: %zuバイト\n", sizeof(double));
    
    printf("=== 実際の値での確認 ===\n");
    printf("char最大値: %d\n", CHAR_MAX);
    printf("int最大値: %d\n", INT_MAX);
    
    /*
     * 注意: データ型のサイズは環境に依存します
     * - 32ビット環境と64ビット環境で異なる場合があります
     * - コンパイラによっても異なる場合があります
     */
    
    return 0;
}