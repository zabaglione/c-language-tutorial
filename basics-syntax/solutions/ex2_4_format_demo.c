/*
 * 課題2-4の解答例: 書式指定子の練習
 * ファイル名: ex2_4_format_demo.c
 * 説明: printf関数の様々な書式指定子の使用方法
 */

#include <stdio.h>

int main(void)
{
    int integer_num = 123;
    double real_num = 3.14159;
    unsigned char char_code = 255;
    
    printf("=== 書式指定子のデモ ===\n");
    
    /* 整数の様々な表示形式 */
    printf("整数 %d の表示:\n", integer_num);
    printf("  10進数: %d\n", integer_num);
    printf("  16進数: %x\n", integer_num);
    printf("  8進数: %o\n", integer_num);
    printf("  フィールド幅5: |%5d|\n", integer_num);
    printf("  ゼロ埋め: |%05d|\n", integer_num);
    printf("\n");
    
    /* 実数の様々な表示形式 */
    printf("実数 %.5f の表示:\n", real_num);
    printf("  デフォルト: %f\n", real_num);
    printf("  小数点以下2桁: %.2f\n", real_num);
    printf("  指数表記: %e\n", real_num);
    printf("  フィールド幅10.2: |%10.2f|\n", real_num);
    printf("\n");
    
    /* 文字コードの表示 */
    printf("文字コード %d:\n", char_code);
    printf("  文字として: %c\n", char_code);
    printf("  16進数: %x\n", char_code);
    printf("  10進数: %d\n", char_code);
    
    printf("====================\n");
    
    return 0;
}

/*
学習ポイント:
1. 整数の書式指定子:
   - %d: 10進数表示
   - %x: 16進数表示（小文字）
   - %X: 16進数表示（大文字）
   - %o: 8進数表示
   
2. フィールド幅指定:
   - %5d: 5桁の幅で右寄せ
   - %05d: 5桁の幅でゼロ埋め
   - |%5d|: 表示範囲を見やすくするための記号
   
3. 浮動小数点数の書式指定子:
   - %f: 通常の小数表示
   - %.2f: 小数点以下2桁まで表示
   - %e: 指数表記（科学的記数法）
   - %10.2f: 幅10、小数点以下2桁
   
4. 文字の書式指定子:
   - %c: 文字として表示
   - %d: 文字コード（整数）として表示
   
応用ポイント:
- 複数の書式を組み合わせて使用可能
- 表の整列や見やすい出力に活用
- 数値の表示形式を用途に応じて選択
*/
