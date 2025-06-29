/*
 * operators_demo_c99.c
 * さまざまな演算子の使用方法を学習
 * C99準拠 - //コメント、bool型、変数宣言位置の自由化
 */

#include <stdio.h>
#include <stdbool.h>

int main(void) {
    printf("===== 算術演算子のデモ =====\n");
    
    // 整数演算
    int a = 10, b = 3;
    printf("整数演算 (a = %d, b = %d):\n", a, b);
    printf("  a + b = %d\n", a + b);
    printf("  a - b = %d\n", a - b);
    printf("  a * b = %d\n", a * b);
    printf("  a / b = %d (整数除算)\n", a / b);
    printf("  a %% b = %d (剰余)\n", a % b);
    
    // 実数演算
    double x = 10.0, y = 3.0;
    printf("\n実数演算 (x = %.1f, y = %.1f):\n", x, y);
    printf("  x / y = %.2f (実数除算)\n", x / y);
    
    printf("\n===== 代入演算子のデモ =====\n");
    int result = a;  // C99: 使用箇所で変数宣言
    printf("result = %d\n", result);
    result += 5;
    printf("result += 5 -> %d\n", result);
    result -= 3;
    printf("result -= 3 -> %d\n", result);
    result *= 2;
    printf("result *= 2 -> %d\n", result);
    result /= 4;
    printf("result /= 4 -> %d\n", result);
    result %= 3;
    printf("result %%= 3 -> %d\n", result);
    
    printf("\n===== インクリメント・デクリメント演算子 =====\n");
    a = 5;
    printf("初期値: a = %d\n", a);
    printf("a++ = %d (後置インクリメント)\n", a++);
    printf("現在の a = %d\n", a);
    printf("++a = %d (前置インクリメント)\n", ++a);
    printf("現在の a = %d\n", a);
    
    a = 5;
    printf("\n初期値: a = %d\n", a);
    printf("a-- = %d (後置デクリメント)\n", a--);
    printf("現在の a = %d\n", a);
    printf("--a = %d (前置デクリメント)\n", --a);
    printf("現在の a = %d\n", a);
    
    printf("\n===== 関係演算子のデモ =====\n");
    a = 10; b = 20;
    printf("a = %d, b = %d のとき:\n", a, b);
    printf("  a == b : %d\n", a == b);
    printf("  a != b : %d\n", a != b);
    printf("  a <  b : %d\n", a < b);
    printf("  a <= b : %d\n", a <= b);
    printf("  a >  b : %d\n", a > b);
    printf("  a >= b : %d\n", a >= b);
    
    // C99: bool型の使用
    printf("\n===== 論理演算子のデモ（bool型使用）=====\n");
    bool p = true, q = false;
    printf("p = %s, q = %s のとき:\n", p ? "true" : "false", q ? "true" : "false");
    printf("  !p     : %s\n", !p ? "true" : "false");
    printf("  p && q : %s\n", (p && q) ? "true" : "false");
    printf("  p || q : %s\n", (p || q) ? "true" : "false");
    
    // 短絡評価のデモ
    printf("\n短絡評価のデモ:\n");
    int count = 0;
    if (false && (++count > 0)) {
        // このブロックは実行されない
    }
    printf("  false && (++count > 0) の後、count = %d\n", count);
    
    count = 0;
    if (true || (++count > 0)) {
        // このブロックは実行される
    }
    printf("  true || (++count > 0) の後、count = %d\n", count);
    
    printf("\n===== 条件演算子（三項演算子）のデモ =====\n");
    a = 10; b = 20;
    result = (a > b) ? a : b;
    printf("a = %d, b = %d のとき:\n", a, b);
    printf("  (a > b) ? a : b = %d (大きい方の値)\n", result);
    
    // C99: 条件演算子の連鎖
    int score = 85;
    const char* grade = (score >= 90) ? "A" :
                       (score >= 80) ? "B" :
                       (score >= 70) ? "C" :
                       (score >= 60) ? "D" : "F";
    printf("\nスコア %d の評価: %s\n", score, grade);
    
    printf("\n===== sizeof演算子のデモ =====\n");
    printf("基本データ型のサイズ:\n");
    printf("  sizeof(char)      = %zu バイト\n", sizeof(char));
    printf("  sizeof(short)     = %zu バイト\n", sizeof(short));
    printf("  sizeof(int)       = %zu バイト\n", sizeof(int));
    printf("  sizeof(long)      = %zu バイト\n", sizeof(long));
    printf("  sizeof(long long) = %zu バイト\n", sizeof(long long));  // C99
    printf("  sizeof(float)     = %zu バイト\n", sizeof(float));
    printf("  sizeof(double)    = %zu バイト\n", sizeof(double));
    printf("  sizeof(bool)      = %zu バイト\n", sizeof(bool));       // C99
    
    // C99: 可変長配列のサイズ
    int n = 5;
    int vla[n];  // 可変長配列
    printf("\n可変長配列 vla[%d] のサイズ: %zu バイト\n", n, sizeof(vla));
    
    return 0;
}
