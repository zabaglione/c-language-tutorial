/*
 * ファイル名: ex4_6_precedence_c99.c
 * 演習4-6: 演算子の優先順位
 * 説明: 複雑な式を含むプログラムで演算子の優先順位を確認
 * 規格: C99準拠
 */
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

// 複雑な式の評価を段階的に表示する関数
void demonstrate_evaluation_order(void);
void demonstrate_associativity(void);
void demonstrate_common_mistakes(void);

// C99: インライン関数
static inline int max(int a, int b) {
    return (a > b) ? a : b;
}

static inline int min(int a, int b) {
    return (a < b) ? a : b;
}

int main(void)
{
    printf("=== 演算子の優先順位 ===\n");

    // 基本的な優先順位
    printf("基本的な優先順位:\n");
    int result1 = 2 + 3 * 4;
    int result2 = (2 + 3) * 4;
    printf("  2 + 3 * 4 = %d (3*4が先に計算される)\n", result1);
    printf("  (2 + 3) * 4 = %d (括弧で優先順位変更)\n", result2);
    printf("\n");

    // 除算の優先順位
    printf("除算の優先順位:\n");
    int result3 = 10 / 2 * 3;
    int result4 = 10 / (2 * 3);
    printf("  10 / 2 * 3 = %d (左から右へ: (10/2)*3)\n", result3);
    printf("  10 / (2 * 3) = %d (括弧で変更)\n", result4);
    printf("\n");

    // 比較と論理（C99: bool型）
    printf("比較と論理:\n");
    int a = 5, b = 3, c = 4;
    bool result5 = a > b && b < c;  // C99: bool型
    bool result6 = a > b + 1;
    printf("  %d > %d && %d < %d = %s (比較が先、論理が後)\n", 
           a, b, b, c, result5 ? "true" : "false");
    printf("  %d > %d + 1 = %s (加算が先: %d > %d)\n", 
           a, b, result6 ? "true" : "false", a, b + 1);
    printf("\n");

    // 代入の右結合
    printf("代入の右結合:\n");
    int x, y, z;
    x = y = z = 5;
    printf("  x = y = z = 5\n");
    printf("  結果: x=%d, y=%d, z=%d\n", x, y, z);
    printf("\n");

    // ビット演算の優先順位
    printf("ビット演算の優先順位:\n");
    int result7 = 6 & 3 | 4;
    int result8 = 6 & (3 | 4);
    printf("  6 & 3 | 4 = %d (&が先: (6&3)|4 = %d|4)\n", result7, 6 & 3);
    printf("  6 & (3 | 4) = %d (括弧で変更: 6&%d)\n", result8, 3 | 4);
    printf("\n");

    // より詳細なデモ
    demonstrate_evaluation_order();
    demonstrate_associativity();
    demonstrate_common_mistakes();

    // 実用的な例
    printf("実用的な優先順位の例:\n");

    // 条件式での優先順位（C99: bool型）
    int score = 85;
    bool is_passing = score >= 60 && score <= 100;
    printf("  点数判定: score=%d\n", score);
    printf("  score >= 60 && score <= 100 = %s\n", is_passing ? "true" : "false");

    // 計算式での優先順位
    double radius = 5.0;
    double area = 3.14 * radius * radius; // 左から右へ評価
    double circumference = 2 * 3.14 * radius;
    printf("  円の面積 (r=%.1f): %.2f\n", radius, area);
    printf("  円の周長: %.2f\n", circumference);

    // 配列インデックスでの優先順位
    int array[] = {10, 20, 30, 40, 50};
    int index = 2;
    int value = array[index++]; // []が先、then ++
    printf("  配列アクセス: array[%d] = %d, その後index = %d\n", 
           index - 1, value, index);

    // C99: 追加の例
    printf("\nC99の追加例:\n");
    
    // インライン関数を使った例
    int num1 = 15, num2 = 23;
    int maximum = max(num1, num2) * 2 + min(num1, num2);
    printf("  max(%d,%d) * 2 + min(%d,%d) = %d\n", 
           num1, num2, num1, num2, maximum);

    printf("=======================\n");

    return 0;
}

// 複雑な式の評価順序デモ
void demonstrate_evaluation_order(void)
{
    printf("複雑な式の評価順序:\n");

    // 段階的に複雑にしていく
    int p = 2, q = 3, r = 4, s = 5;
    printf("  初期値: p=%d, q=%d, r=%d, s=%d\n", p, q, r, s);

    // 式1: 算術演算の組み合わせ
    int expr1 = p + q * r - s;
    printf("  p + q * r - s:\n");
    printf("    = %d + %d * %d - %d\n", p, q, r, s);
    printf("    = %d + %d - %d  (乗算先)\n", p, q * r, s);
    printf("    = %d - %d        (加算次)\n", p + q * r, s);
    printf("    = %d             (減算最後)\n", expr1);
    printf("\n");

    // 式2: 比較と論理の組み合わせ（C99: bool型）
    bool expr2 = p < q && r > s || p == q;
    printf("  p < q && r > s || p == q:\n");
    printf("    = %d < %d && %d > %d || %d == %d\n", p, q, r, s, p, q);
    printf("    = %s && %s || %s      (比較先)\n", 
           (p < q) ? "true" : "false",
           (r > s) ? "true" : "false",
           (p == q) ? "true" : "false");
    printf("    = %s || %s            (&&次)\n", 
           ((p < q) && (r > s)) ? "true" : "false",
           (p == q) ? "true" : "false");
    printf("    = %s                  (||最後)\n", expr2 ? "true" : "false");
    printf("\n");

    // 式3: 混合演算
    bool expr3 = p++ + ++q * r-- > s && q != r;
    printf("  複雑な混合演算の結果: %s\n", expr3 ? "true" : "false");
    printf("  演算後の値: p=%d, q=%d, r=%d, s=%d\n", p, q, r, s);
    printf("\n");

    // C99: 複合リテラルを使った優先順位の例
    printf("複合リテラルと優先順位（C99）:\n");
    int arr_result = (int[]){10, 20, 30}[1] + 5 * 2;
    printf("  (int[]){10, 20, 30}[1] + 5 * 2 = %d\n", arr_result);
    printf("  → 20 + 10 = 30 (配列アクセス→乗算→加算)\n");
    printf("\n");
}

// 結合性のデモ
void demonstrate_associativity(void)
{
    printf("結合性のデモ:\n");

    // 左結合の例
    printf("左結合の例:\n");
    int result1 = 100 / 5 / 2;   // (100 / 5) / 2
    int result2 = 100 / (5 / 2); // 100 / (5 / 2)
    printf("  100 / 5 / 2 = %d    (左結合: (100/5)/2)\n", result1);
    printf("  100 / (5 / 2) = %d  (括弧で右結合)\n", result2);

    int result3 = 20 - 10 - 5;   // (20 - 10) - 5
    int result4 = 20 - (10 - 5); // 20 - (10 - 5)
    printf("  20 - 10 - 5 = %d     (左結合: (20-10)-5)\n", result3);
    printf("  20 - (10 - 5) = %d   (括弧で右結合)\n", result4);
    printf("\n");

    // 右結合の例
    printf("右結合の例:\n");
    int a, b, c;
    a = b = c = 10; // a = (b = (c = 10))
    printf("  a = b = c = 10 → a=%d, b=%d, c=%d (右結合)\n", a, b, c);

    // 条件演算子の右結合
    int x = 5;
    int result5 = x > 0 ? x > 10 ? 10 : x : 0;
    printf("  条件演算子: x > 0 ? x > 10 ? 10 : x : 0\n");
    printf("  x=%d の場合: %d (右結合で評価)\n", x, result5);
    
    // C99: 変数宣言と初期化の連鎖
    printf("\n変数宣言の連鎖（C99）:\n");
    for (int i = 0, j = 10; i < 5; i++, j--) {
        printf("  i=%d, j=%d\n", i, j);
        if (i == 2) {
            break;  // 表示を短くする
        }
    }
    printf("\n");
}

// よくある間違いの例
void demonstrate_common_mistakes(void)
{
    printf("よくある間違いの例:\n");

    // 間違い1: ビット演算と比較の優先順位
    printf("間違い1: ビット演算の優先順位\n");
    int flags = 5; // 0101
    int mask = 1;  // 0001

    // 間違った書き方
    bool wrong = flags & mask == 1;     // flags & (mask == 1)
    bool correct = (flags & mask) == 1; // 正しい

    printf("  flags=%d, mask=%d\n", flags, mask);
    printf("  flags & mask == 1    = %s (間違い: flags & (mask == 1))\n", 
           wrong ? "true" : "false");
    printf("  (flags & mask) == 1  = %s (正しい)\n", 
           correct ? "true" : "false");
    printf("\n");

    // 間違い2: シフトと算術演算
    printf("間違い2: シフトと算術演算\n");
    int val = 4;
    int wrong2 = val << 2 + 1;     // val << (2 + 1)
    int correct2 = (val << 2) + 1; // 正しい

    printf("  val=%d\n", val);
    printf("  val << 2 + 1    = %d (間違い: val << (2 + 1))\n", wrong2);
    printf("  (val << 2) + 1  = %d (正しい)\n", correct2);
    printf("\n");

    // 間違い3: ポインタと配列の優先順位
    printf("間違い3: ポインタ演算\n");
    int array[] = {10, 20, 30, 40};
    int *ptr = array;

    printf("  *ptr++ = %d (ポインタを進めてから前の値)\n", *ptr++);
    printf("  現在のptr: %d\n", *ptr);

    ptr = array; // リセット
    printf("  (*ptr)++ = %d (値をインクリメント)\n", (*ptr)++);
    printf("  array[0] = %d (配列の値が変更された)\n", array[0]);

    array[0] = 10; // 復元
    printf("\n");

    // 間違い4: 条件演算子の優先順位
    printf("間違い4: 条件演算子\n");
    int score = 85;
    char grade1 = score >= 90 ? 'A' : 
                  score >= 80 ? 'B' : 'C';
    char grade2 = (score >= 90) ? 'A' : ((score >= 80) ? 'B' : 'C');

    printf("  score=%d\n", score);
    printf("  評価1: %c (右結合で正しく動作)\n", grade1);
    printf("  評価2: %c (括弧で明確化)\n", grade2);
    
    // C99: ビット幅を考慮した演算の優先順位
    printf("\nビット幅を考慮した演算（C99）:\n");
    uint8_t byte_val = 200;
    uint16_t result = byte_val + 100;  // 自動的に昇格
    printf("  uint8_t(200) + 100 = %u (uint16_tに昇格)\n", result);
    
    // オーバーフローを考慮
    uint8_t overflow_result = (uint8_t)(byte_val + 100);
    printf("  (uint8_t)(200 + 100) = %u (オーバーフロー)\n", overflow_result);
    printf("\n");
}

/*
学習ポイント:
1. 演算子の優先順位
   - 算術 > 関係 > 論理 > 代入
   - 乗除 > 加減
   - ビット演算は関係演算より低い

2. 結合性
   - 左結合: 算術、関係、論理演算
   - 右結合: 代入、条件演算子

3. よくある間違い
   - ビット演算と比較の混同
   - シフトと算術演算の優先順位
   - ポインタ演算の理解不足

4. 対策
   - 複雑な式では括弧を使う
   - 一行に複数の演算子を書かない
   - 可読性を優先する

5. 実用的なガイドライン
   - 疑問があれば括弧で明確にする
   - コンパイラ警告を確認する
   - 式を分割して可読性を向上させる

6. C99での拡張
   - bool型による真偽値の明確化
   - インライン関数による効率的な演算
   - 複合リテラルとの組み合わせ
   - stdint.hによる正確な型指定

重要な優先順位:
1. 後置演算子（++, --）
2. 単項演算子（前置++, --, !, ~, *, &）
3. 乗除（*, /, %）
4. 加減（+, -）
5. シフト（<<, >>）
6. 関係（<, <=, >, >=）
7. 等価（==, !=）
8. ビット演算（&, ^, |）
9. 論理演算（&&, ||）
10. 条件演算子（?:）
11. 代入（=, +=, -=, ...）
*/
