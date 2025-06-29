/*
 * ファイル名: ex3_4_type_conversion.c
 * 演習3-4: 型変換の理解
 * 説明: 整数除算と実数除算の違いを確認する
 * 規格: C90準拠
 */
#include <stdio.h>

int main(void)
{
    /* 変数の宣言と初期化 */
    int a = 7, b = 3;
    float f1 = 7.0f, f2 = 3.0f;
    double d1 = 7.0, d2 = 3.0;
    
    printf("=== 型変換の理解 ===\n");
    
    /* 整数除算 vs 実数除算 */
    printf("整数除算 vs 実数除算:\n");
    printf("  %d / %d = %d (整数除算)\n", a, b, a / b);
    printf("  %.1f / %.1f = %.6f (float除算)\n", f1, f2, f1 / f2);
    printf("  %.1f / %.1f = %.15f (double除算)\n", d1, d2, d1 / d2);
    
    /* 暗黙の型変換 */
    printf("\n暗黙の型変換:\n");
    printf("  %d + %.1f = %.6f (intからfloatへ自動変換)\n", a, f2, a + f2);
    printf("  %.1f + %d = %.6f (intからfloatへ自動変換)\n", f1, b, f1 + b);
    printf("  %d + %.1f = %.15f (intからdoubleへ自動変換)\n", a, d2, a + d2);
    printf("  %.6f + %.1f = %.15f (floatからdoubleへ自動変換)\n", f1, d2, f1 + d2);
    
    /* 明示的な型変換（キャスト） */
    printf("\n明示的な型変換（キャスト）:\n");
    printf("  %d / %d = %d (整数除算)\n", a, b, a / b);
    printf("  (double)%d / %d = %.6f (明示的にdoubleに変換)\n", a, b, (double)a / b);
    printf("  %d / (double)%d = %.6f (明示的にdoubleに変換)\n", a, b, a / (double)b);
    printf("  (double)%d / (double)%d = %.6f (両方をdoubleに変換)\n", a, b, (double)a / (double)b);
    
    /* 小数の整数への変換 */
    printf("\n小数の整数への変換:\n");
    printf("  %.6f を int に変換: %d (小数点以下切り捨て)\n", f1, (int)f1);
    printf("  %.6f を int に変換: %d (小数点以下切り捨て)\n", f1/f2, (int)(f1/f2));
    printf("  %.15f を int に変換: %d (小数点以下切り捨て)\n", d1/d2, (int)(d1/d2));
    
    /* 負数の型変換 */
    {
        int neg_int = -5;
        float neg_float = -2.7f;
        double neg_double = -3.14159;
        
        printf("\n負数の型変換:\n");
        printf("  %d を float に変換: %.1f\n", neg_int, (float)neg_int);
        printf("  %.1f を int に変換: %d (小数点以下切り捨て)\n", neg_float, (int)neg_float);
        printf("  %.5f を int に変換: %d (小数点以下切り捨て)\n", neg_double, (int)neg_double);
    }
    
    /* 文字と数値の変換 */
    {
        char digit_char = '5';
        char letter_char = 'A';
        int ascii_value;
        
        printf("\n文字と数値の変換:\n");
        ascii_value = digit_char;
        printf("  文字 '%c' のASCII値: %d\n", digit_char, ascii_value);
        printf("  数字文字 '%c' を数値に: %d (ASCII値 - '0')\n", digit_char, digit_char - '0');
        
        ascii_value = letter_char;
        printf("  文字 '%c' のASCII値: %d\n", letter_char, ascii_value);
        printf("  ASCII値 %d を文字に: '%c'\n", 66, (char)66);
    }
    
    /* 型変換の優先順位 */
    printf("\n型変換の優先順位（算術変換）:\n");
    printf("  char + int = int型\n");
    printf("  int + float = float型\n");
    printf("  float + double = double型\n");
    printf("  unsigned + signed = unsigned型（同サイズの場合）\n");
    
    /* オーバーフローの例 */
    {
        char small_char = 100;
        int big_int = 300;
        
        printf("\nオーバーフローの例:\n");
        printf("  char変数(100) に 200 を加算: %d\n", small_char + 200);
        printf("  int値 %d を char に変換: %d (上位ビット切り捨て)\n", big_int, (char)big_int);
    }
    
    return 0;
}

/*
学習ポイント:
1. 整数除算は小数点以下が切り捨てられる
2. 暗黙の型変換は自動的に行われる
3. 明示的な型変換（キャスト）で強制的に変換できる
4. 型変換には優先順位がある
5. charとintの間でASCII値による変換が可能
6. オーバーフローは上位ビットの切り捨てで発生

型変換の優先順位（低→高）:
char → short → int → long → float → double → long double

注意点:
- 精度の低い型への変換では情報が失われる可能性
- 符号付きから符号なしへの変換は予期しない結果を生む場合
- オーバーフローは未定義動作の原因となる場合がある
*/
