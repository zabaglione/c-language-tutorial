/*
 * ファイル名: ex3_7_temperature_converter_c99.c
 * チャレンジ問題: 温度変換プログラム
 * 説明: 摂氏・華氏・ケルビンの温度単位を相互変換するプログラム
 * 規格: C99準拠
 */
#include <stdio.h>

// 温度変換に使用する定数を定義
#define FAHRENHEIT_FACTOR 9.0/5.0
#define FAHRENHEIT_OFFSET 32.0
#define KELVIN_OFFSET 273.15

int main(void)
{
    printf("=== 温度変換プログラム ===\n");
    
    // デモ用の温度値（実際のプログラムでは入力を受け取る）
    double celsius = 25.0;
    
    printf("入力温度: %.2f℃\n\n", celsius);
    
    // 摂氏から華氏への変換
    double fahrenheit = celsius * FAHRENHEIT_FACTOR + FAHRENHEIT_OFFSET;
    
    // 摂氏からケルビンへの変換
    double kelvin = celsius + KELVIN_OFFSET;
    
    // 結果の表示
    printf("=== 温度変換結果 ===\n");
    printf("摂氏  : %.2f℃\n", celsius);
    printf("華氏  : %.2f°F\n", fahrenheit);
    printf("ケルビン: %.2fK\n", kelvin);
    
    // 変換公式の説明
    printf("\n=== 変換公式 ===\n");
    printf("華氏 = 摂氏 × 9/5 + 32\n");
    printf("ケルビン = 摂氏 + 273.15\n");
    
    // 他の温度での変換例
    printf("\n=== その他の変換例 ===\n");
    
    // 水の凝固点
    celsius = 0.0;
    fahrenheit = celsius * FAHRENHEIT_FACTOR + FAHRENHEIT_OFFSET;
    kelvin = celsius + KELVIN_OFFSET;
    printf("水の凝固点: %.1f℃ = %.1f°F = %.1fK\n", celsius, fahrenheit, kelvin);
    
    // 水の沸点
    celsius = 100.0;
    fahrenheit = celsius * FAHRENHEIT_FACTOR + FAHRENHEIT_OFFSET;
    kelvin = celsius + KELVIN_OFFSET;
    printf("水の沸点  : %.1f℃ = %.1f°F = %.1fK\n", celsius, fahrenheit, kelvin);
    
    // 絶対零度
    celsius = -273.15;
    fahrenheit = celsius * FAHRENHEIT_FACTOR + FAHRENHEIT_OFFSET;
    kelvin = celsius + KELVIN_OFFSET;
    printf("絶対零度  : %.2f℃ = %.2f°F = %.2fK\n", celsius, fahrenheit, kelvin);
    
    // 定数の使用例の説明
    printf("\n=== 実装のポイント ===\n");
    printf("- #defineマクロで変換係数を定義\n");
    printf("- 浮動小数点演算の精度に注意\n");
    printf("- 物理的に意味のある温度範囲を考慮\n");
    
    return 0;
}

/*
学習ポイント:
1. #defineマクロによる定数の定義
2. 浮動小数点演算の精度管理
3. 物理的な意味を持つ計算の実装
4. 複数の単位系の相互変換

実装のポイント:
- C99準拠のため、変数を使用箇所の近くで宣言
- 変数の初期化を宣言と同時に実行
- コメントに//スタイルを使用
- #defineで変換係数を定数として定義
- デモ版として固定値を使用（実際は入力を受け取る）
*/
