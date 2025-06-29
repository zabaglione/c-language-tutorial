/*
 * 課題2-4の解答例: 書式指定子の練習（C99版）
 * ファイル名: ex2_4_format_demo_c99.c
 * 説明: printf関数の様々な書式指定子の使用方法
 * C99特有の機能：必要な時点での変数宣言を使用
 */

#include <stdio.h>

int main(void)
{
    printf("=== 書式指定子のデモ ===\n");
    
    /* 整数データの表示 */
    int integer_num = 123;  /* C99：必要な時点で変数宣言 */
    printf("整数 %d の表示:\n", integer_num);
    printf("  10進数: %d\n", integer_num);
    printf("  16進数: %x\n", integer_num);
    printf("  8進数: %o\n", integer_num);
    printf("  フィールド幅5: |%5d|\n", integer_num);
    printf("  ゼロ埋め: |%05d|\n", integer_num);
    printf("\n");
    
    /* 実数データの表示 */
    double real_num = 3.14159;  /* C99：必要な時点で変数宣言 */
    printf("実数 %.5f の表示:\n", real_num);
    printf("  デフォルト: %f\n", real_num);
    printf("  小数点以下2桁: %.2f\n", real_num);
    printf("  指数表記: %e\n", real_num);
    printf("  フィールド幅10.2: |%10.2f|\n", real_num);
    printf("\n");
    
    /* 文字コードデータの表示 */
    unsigned char char_code = 255;  /* C99：必要な時点で変数宣言 */
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

C99での変更点:
- 各データ型の変数を必要な時点で宣言
- より読みやすいコード構造
- 変数の役割がより明確になる配置
   
応用ポイント:
- 複数の書式を組み合わせて使用可能
- 表の整列や見やすい出力に活用
- 数値の表示形式を用途に応じて選択
*/