/*
 * ファイル名: ex2_2_data_type_sizes.c
 * 課題2-2: データ型サイズ確認
 * 説明: 各データ型のサイズと範囲を表示するプログラム
 * 規格: C90準拠
 */

#include <stdio.h>
#include <limits.h>

int main(void)
{
    printf("=== C言語データ型情報 ===\n");
    
    /* データ型のサイズを表示 */
    printf("char: %luバイト, 範囲: %d 〜 %d\n", 
           (unsigned long)sizeof(char), CHAR_MIN, CHAR_MAX);
    printf("int: %luバイト, 範囲: %d 〜 %d\n", 
           (unsigned long)sizeof(int), INT_MIN, INT_MAX);
    printf("float: %luバイト\n", (unsigned long)sizeof(float));
    printf("double: %luバイト\n", (unsigned long)sizeof(double));
    
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