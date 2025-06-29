/*
 * 課題3-2の解答例: 温度変換プログラム
 * ファイル名: ex3_2_temperature_converter_c99.c
 * 説明: 摂氏から華氏と絶対温度への変換（C99版）
 * 規格: C99準拠
 */

#include <stdio.h>

int main(void)
{
    // 摂氏温度の入力
    printf("=== 温度変換プログラム ===\n");
    printf("摂氏温度を入力してください: ");
    
    double celsius;
    scanf("%lf", &celsius);
    
    // 温度変換の計算（C99では宣言と計算を同時に実行可能）
    double fahrenheit = celsius * 9.0 / 5.0 + 32.0;  // 華氏 = 摂氏 × 9/5 + 32
    double kelvin = celsius + 273.15;                 // 絶対温度 = 摂氏 + 273.15
    
    // 変換結果の表示
    printf("\n=== 変換結果 ===\n");
    printf("摂氏: %.1f°C\n", celsius);
    printf("華氏: %.1f°F\n", fahrenheit);
    printf("絶対温度: %.1fK\n", kelvin);
    
    return 0;
}

/*
C99での改善点:
1. 変数宣言を使用直前に配置可能
2. 計算式を初期化時に直接記述
3. // 形式のコメント使用
4. より読みやすいコード構造
*/