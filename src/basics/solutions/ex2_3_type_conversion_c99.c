/*
 * ファイル名: ex2_3_type_conversion_c99.c
 * 課題2-3: 型変換実験 (C99版)
 * 説明: 異なる型間の変換を実験するプログラム
 * 規格: C99準拠
 */

#include <stdio.h>

int main(void)
{
    printf("=== 型変換実験 ===\n");
    
    // 変数の宣言は使用箇所で行う（C99の特徴）
    int integer_val = 42;
    printf("整数 %d を float に変換: %.1f\n", 
           integer_val, (float)integer_val);
    
    float float_val = 3.14f;
    printf("小数 %.2f を int に変換: %d\n", 
           float_val, (int)float_val);
    
    char char_val = 'A';
    printf("文字 '%c' を int に変換: %d\n", 
           char_val, (int)char_val);
    
    // 除算の実験
    int div1 = 7, div2 = 3;
    printf("整数除算: %d / %d = %d\n", 
           div1, div2, div1 / div2);
    printf("浮動小数点除算: %.1f / %.1f = %.2f\n", 
           (float)div1, (float)div2, (float)div1 / (float)div2);
    
    /*
     * 学習ポイント:
     * - 浮動小数点数から整数への変換では小数部分が切り捨てられる
     * - 文字は内部的にはASCII値として扱われる
     * - 整数除算では結果も整数になり、小数部分は切り捨てられる
     */
    
    return 0;
}