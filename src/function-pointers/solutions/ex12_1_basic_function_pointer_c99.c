/*
 * ファイル名: ex12_1_basic_function_pointer_c99.c
 * 演習12-1: 関数ポインタの基本操作
 * 説明: 関数ポインタを使って複数の関数を動的に呼び出すデモプログラム
 * 規格: C99準拠
 */
#include <stdio.h>

// 演算関数群
int maximum(int a, int b)
{
    return (a > b) ? a : b;
}

int minimum(int a, int b)
{
    return (a < b) ? a : b;
}

int power(int a, int b)
{
    // 簡単な累乗実装（正の整数のみ）
    if (b < 0) {
        return 0; // 負の指数は0を返す
    }
    
    int result = 1;
    for (int i = 0; i < b; i++) {
        result *= a;
    }
    
    return result;
}

int main(void)
{
    printf("=== 関数ポインタの基本操作デモ ===\n");
    
    // デモ用の値（実際のプログラムでは入力を受け取る）
    int a = 8;
    int b = 3;
    
    printf("対象の値: a = %d, b = %d\n\n", a, b);
    
    // 1. maximum関数のテスト
    int (*operation)(int, int) = maximum;
    int result = operation(a, b);
    printf("maximum(%d, %d) = %d\n", a, b, result);
    
    // 2. minimum関数のテスト
    operation = minimum;
    result = operation(a, b);
    printf("minimum(%d, %d) = %d\n", a, b, result);
    
    // 3. power関数のテスト
    operation = power;
    result = operation(a, b);
    printf("power(%d, %d) = %d\n", a, b, result);
    
    // 関数ポインタ配列のデモ
    printf("\n=== 関数ポインタ配列デモ ===\n");
    int (*operations[])(int, int) = {maximum, minimum, power};
    char *names[] = {"maximum", "minimum", "power"};
    
    for (int i = 0; i < 3; i++) {
        result = operations[i](a, b);
        printf("%s(%d, %d) = %d\n", names[i], a, b, result);
    }
    
    // 異なる値での演算デモ
    printf("\n=== 異なる値での演算例 ===\n");
    int test_values[][2] = {{10, 5}, {3, 7}, {2, 4}, {15, 15}};
    int num_tests = sizeof(test_values) / sizeof(test_values[0]);
    
    for (int i = 0; i < num_tests; i++) {
        int x = test_values[i][0];
        int y = test_values[i][1];
        
        printf("値: %d, %d\n", x, y);
        printf("  max: %d, min: %d, pow: %d\n", 
               maximum(x, y), minimum(x, y), power(x, y));
    }
    
    return 0;
}

/*
学習ポイント:
1. 関数ポインタの宣言と初期化
2. 関数ポインタを通じた間接関数呼び出し
3. 関数ポインタ配列の活用
4. 実行時の動的な関数選択

実装のポイント:
- C99準拠のため、変数を使用箇所の近くで宣言
- for文内でのループ変数宣言
- 変数の初期化を宣言と同時に実行
- コメントに//スタイルを使用
- デモ版として固定値を使用（実際は入力を受け取る）
*/
