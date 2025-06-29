/*
 * ファイル名: ex4_3_increment_c99.c
 * 演習4-3: インクリメントとデクリメント演算
 * 説明: 前置と後置のインクリメント・デクリメント演算子の違いを確認
 * 規格: C99準拠
 */

#include <stdio.h>
#include <stdbool.h>

// C99: inline関数によるデモンストレーション
static inline void demonstrate_increment(int initial_value)
{
    int a = initial_value;
    int result;
    
    printf("\n初期値: a = %d\n", a);
    
    result = a++;
    printf("result = a++ → result = %d, a = %d\n", result, a);
    
    a = initial_value;
    result = ++a;
    printf("result = ++a → result = %d, a = %d\n", result, a);
}

static inline void demonstrate_decrement(int initial_value)
{
    int a = initial_value;
    int result;
    
    printf("\n初期値: a = %d\n", a);
    
    result = a--;
    printf("result = a-- → result = %d, a = %d\n", result, a);
    
    a = initial_value;
    result = --a;
    printf("result = --a → result = %d, a = %d\n", result, a);
}

int main(void)
{
    printf("===== インクリメント・デクリメント演算子 (C99版) =====\n");
    
    // 基本的な動作確認
    printf("\n=== 基本的な動作 ===\n");
    demonstrate_increment(5);
    demonstrate_decrement(5);
    
    // 式の中での動作確認
    printf("\n=== 式の中での動作 ===\n");
    {
        // C99: 使用箇所での変数宣言
        int a = 5, b = 3;
        int result = a++ * b;
        printf("a = 5, b = 3\n");
        printf("result = a++ * b → result = %d, a = %d\n", result, a);
        
        a = 5;
        result = ++a * b;
        printf("a = 5, b = 3\n");
        printf("result = ++a * b → result = %d, a = %d\n", result, a);
    }
    
    // 複雑な式での使用
    printf("\n=== 複雑な式での使用 ===\n");
    {
        int a = 10, b = 5;
        int result = a++ + ++b;
        printf("a = 10, b = 5\n");
        printf("result = a++ + ++b → result = %d, a = %d, b = %d\n", 
               result, a, b);
        
        a = 10;
        b = 5;
        result = --a - b--;
        printf("a = 10, b = 5\n");
        printf("result = --a - b-- → result = %d, a = %d, b = %d\n", 
               result, a, b);
    }
    
    // C99: 配列での詳細な動作分析
    printf("\n=== 配列での詳細な動作分析 ===\n");
    int array[5] = {10, 20, 30, 40, 50};
    
    printf("配列: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", array[i]);
    }
    printf("\n\n");
    
    // C99: 構造体を使った評価順序の記録
    typedef struct {
        int value;
        int index;
        const char *expression;
    } EvalResult;
    
    EvalResult results[] = {
        {0, 0, ""},  // プレースホルダー
        {0, 0, ""},
        {0, 0, ""},
        {0, 0, ""}
    };
    
    // 異なるインクリメント方式の比較
    int idx = 0;
    results[0] = (EvalResult){array[idx++], idx, "array[idx++]"};
    
    idx = 0;
    results[1] = (EvalResult){array[++idx], idx, "array[++idx]"};
    
    idx = 1;
    results[2] = (EvalResult){array[idx--], idx, "array[idx--]"};
    
    idx = 1;
    results[3] = (EvalResult){array[--idx], idx, "array[--idx]"};
    
    for (int i = 0; i < 4; i++) {
        printf("%s: 値 = %d, 最終idx = %d\n", 
               results[i].expression, results[i].value, results[i].index);
    }
    
    // C99: bool型を使った条件判定
    printf("\n=== 条件式でのインクリメント ===\n");
    {
        int counter = 0;
        bool should_increment = true;
        
        printf("カウンター初期値: %d\n", counter);
        
        // 条件付きインクリメント
        int new_value = should_increment ? ++counter : counter;
        printf("should_increment = true: new_value = %d, counter = %d\n", 
               new_value, counter);
        
        should_increment = false;
        new_value = should_increment ? ++counter : counter;
        printf("should_increment = false: new_value = %d, counter = %d\n", 
               new_value, counter);
    }
    
    // ポインタでの高度な使用例
    printf("\n=== ポインタでの高度な使用例 ===\n");
    {
        int *ptr = array;
        int *end = array + 5;
        
        printf("配列を前から後ろへ走査:\n");
        while (ptr < end) {
            printf("*ptr++ = %d\n", *ptr++);
        }
        
        printf("\n配列を後ろから前へ走査:\n");
        ptr = end - 1;
        while (ptr >= array) {
            printf("*ptr-- = %d\n", *ptr--);
        }
    }
    
    // C99: 文字列処理での実用例
    printf("\n=== 文字列処理での実用例 ===\n");
    {
        char str[] = "Hello";
        char *p = str;
        
        printf("文字列を1文字ずつ処理:\n");
        while (*p) {
            printf("文字 '%c' (ASCII: %d)\n", *p, *p);
            p++;
        }
        
        // 文字列の長さを計算
        p = str;
        int length = 0;
        while (*p++) {
            length++;
        }
        printf("文字列の長さ: %d\n", length);
    }
    
    // C99: パフォーマンスの考察
    printf("\n=== パフォーマンスの考察 ===\n");
    {
        const int iterations = 1000000;
        int sum1 = 0, sum2 = 0;
        
        // 後置インクリメント
        for (int i = 0; i < iterations; i++) {
            sum1 += i;
        }
        
        // 前置インクリメント
        for (int i = 0; i < iterations; ++i) {
            sum2 += i;
        }
        
        printf("大規模ループでの比較（%d回）:\n", iterations);
        printf("後置インクリメント（i++）の合計: %d\n", sum1);
        printf("前置インクリメント（++i）の合計: %d\n", sum2);
        printf("注: 最適化により実際の性能差はほとんどありません\n");
    }
    
    // 注意事項
    printf("\n=== 注意事項（C99版） ===\n");
    printf("C99でも以下の式は未定義動作です：\n");
    printf("  i = i++; （順序点間での複数の変更）\n");
    printf("  a[i] = i++; （副作用の順序が不定）\n");
    printf("  func(i++, i++); （引数評価順序が不定）\n");
    printf("\nC99の改善点：\n");
    printf("  - forループ内での変数宣言が可能\n");
    printf("  - bool型による明確な条件表現\n");
    printf("  - inline関数による効率的な実装\n");
    
    return 0;
}

/*
実行例（一部）:
$ ./ex3_3_increment_c99
===== インクリメント・デクリメント演算子 (C99版) =====

=== 基本的な動作 ===

初期値: a = 5
result = a++ → result = 5, a = 6
result = ++a → result = 6, a = 6

初期値: a = 5
result = a-- → result = 5, a = 4
result = --a → result = 4, a = 4

=== 配列での詳細な動作分析 ===
配列: 10 20 30 40 50

array[idx++]: 値 = 10, 最終idx = 1
array[++idx]: 値 = 20, 最終idx = 1
array[idx--]: 値 = 20, 最終idx = 0
array[--idx]: 値 = 10, 最終idx = 0

C99の改善点:
1. bool型による条件の明確化
2. 使用箇所での変数宣言
3. inline関数による再利用性の向上
4. 構造体による情報の整理
5. forループ内での変数宣言による簡潔な記述
*/