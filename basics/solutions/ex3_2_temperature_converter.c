/*
 * 課題3-2の解答例: 温度変換プログラム
 * ファイル名: ex3_2_temperature_converter.c
 * 説明: 摂氏から華氏と絶対温度への変換
 * 規格: C90準拠
 */

#include <stdio.h>

int main(void)
{
    /* 変数の宣言（C90では先頭で宣言） */
    double celsius;         /* 摂氏温度 */
    double fahrenheit;      /* 華氏温度 */
    double kelvin;          /* 絶対温度（ケルビン） */
    
    /* 摂氏温度の入力 */
    printf("=== 温度変換プログラム ===\n");
    printf("摂氏温度を入力してください: ");
    scanf("%lf", &celsius);
    
    /* 温度変換の計算 */
    fahrenheit = celsius * 9.0 / 5.0 + 32.0;  /* 華氏 = 摂氏 × 9/5 + 32 */
    kelvin = celsius + 273.15;                 /* 絶対温度 = 摂氏 + 273.15 */
    
    /* 変換結果の表示 */
    printf("\n=== 変換結果 ===\n");
    printf("摂氏: %.1f°C\n", celsius);
    printf("華氏: %.1f°F\n", fahrenheit);
    printf("絶対温度: %.1fK\n", kelvin);
    
    return 0;
}

/*
学習ポイント:
1. 温度変換の計算式:
   - 華氏変換: F = C × 9/5 + 32
   - ケルビン変換: K = C + 273.15

2. 浮動小数点演算:
   - 9.0 / 5.0 のように.0を付けて浮動小数点除算

3. scanf/printfでの浮動小数点:
   - %lf (scanf), %.1f (printf)

4. 物理単位の表記:
   - °C (摂氏), °F (華氏), K (ケルビン)
*/