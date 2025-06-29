/*
 * precedence_demo.c
 * 演算子の優先順位による計算結果の違いを確認
 * C90準拠
 */

#include <stdio.h>

int main(void) {
    int a = 2, b = 3, c = 4, d = 5;
    int result;
    
    printf("===== 演算子優先順位のデモ =====\n");
    printf("初期値: a = %d, b = %d, c = %d, d = %d\n\n", a, b, c, d);
    
    /* 算術演算子の優先順位 */
    printf("【算術演算子の優先順位】\n");
    
    result = a + b * c;
    printf("a + b * c = %d + %d * %d = %d\n", a, b, c, result);
    printf("  → 乗算が先: %d + (%d * %d) = %d + %d = %d\n\n", a, b, c, b * c, b * c, result);
    
    result = (a + b) * c;
    printf("(a + b) * c = (%d + %d) * %d = %d\n", a, b, c, result);
    printf("  → 括弧が先: (%d + %d) * %d = %d * %d = %d\n\n", a, b, c, a + b, a + b, result);
    
    result = a * b + c * d;
    printf("a * b + c * d = %d * %d + %d * %d = %d\n", a, b, c, d, result);
    printf("  → 乗算が先: (%d * %d) + (%d * %d) = %d + %d = %d\n\n", 
           a, b, c, d, a * b, c * d, result);
    
    /* 複雑な式の例 */
    printf("【複雑な式の評価順序】\n");
    
    result = a + b * c - d;
    printf("a + b * c - d = %d + %d * %d - %d = %d\n", a, b, c, d, result);
    printf("  評価順序:\n");
    printf("  1) b * c = %d * %d = %d\n", b, c, b * c);
    printf("  2) a + (b * c) = %d + %d = %d\n", a, b * c, a + b * c);
    printf("  3) (a + b * c) - d = %d - %d = %d\n\n", a + b * c, d, result);
    
    /* 関係演算子と論理演算子 */
    printf("【関係演算子と論理演算子の優先順位】\n");
    
    result = a < b && c > d;
    printf("a < b && c > d = %d < %d && %d > %d = %d\n", a, b, c, d, result);
    printf("  評価順序:\n");
    printf("  1) a < b = %d < %d = %d (真)\n", a, b, a < b);
    printf("  2) c > d = %d > %d = %d (偽)\n", c, d, c > d);
    printf("  3) (a < b) && (c > d) = %d && %d = %d\n\n", a < b, c > d, result);
    
    /* ビット演算子と比較演算子 */
    printf("【ビット演算子と比較演算子の優先順位】\n");
    
    /* 注意：この例は優先順位を示すためのもの */
    result = (a & b) == 2;  /* 括弧を使って意図を明確にする */
    printf("(a & b) == 2 = (%d & %d) == 2 = %d\n", a, b, result);
    printf("  評価順序:\n");
    printf("  1) a & b = %d & %d = %d\n", a, b, a & b);
    printf("  2) (a & b) == 2 = %d == 2 = %d\n\n", a & b, result);
    
    /* 代入演算子の結合性 */
    printf("【代入演算子の結合性（右結合）】\n");
    
    a = b = c = 10;
    printf("a = b = c = 10 の後: a = %d, b = %d, c = %d\n", a, b, c);
    printf("  → 右から左に評価: a = (b = (c = 10))\n\n");
    
    /* インクリメントと他の演算子 */
    printf("【インクリメント演算子の優先順位】\n");
    
    a = 5;
    result = ++a * 2;
    printf("a = 5; result = ++a * 2;\n");
    printf("  result = %d (前置++が先: 6 * 2)\n", result);
    printf("  a = %d\n\n", a);
    
    a = 5;
    result = a++ * 2;
    printf("a = 5; result = a++ * 2;\n");
    printf("  result = %d (後置++は後: 5 * 2)\n", result);
    printf("  a = %d\n\n", a);
    
    /* 括弧を使った明確な表現 */
    printf("【推奨：括弧で意図を明確にする】\n");
    
    a = 2; b = 3; c = 4; d = 1;
    
    /* 曖昧な式 */
    result = a + b << 2 & c;
    printf("曖昧: a + b << 2 & c = %d\n", result);
    
    /* 明確な式 */
    result = ((a + b) << 2) & c;
    printf("明確: ((a + b) << 2) & c = %d\n", result);
    printf("  評価順序:\n");
    printf("  1) a + b = %d + %d = %d\n", a, b, a + b);
    printf("  2) (a + b) << 2 = %d << 2 = %d\n", a + b, (a + b) << 2);
    printf("  3) ((a + b) << 2) & c = %d & %d = %d\n", (a + b) << 2, c, result);
    
    return 0;
}
