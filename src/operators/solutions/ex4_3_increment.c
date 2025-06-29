/*
 * ファイル名: ex4_3_increment.c
 * 演習4-3: インクリメントとデクリメント演算
 * 説明: 前置と後置のインクリメント・デクリメント演算子の違いを確認
 * 規格: C90準拠
 */

#include <stdio.h>

int main(void)
{
    int a, b, result;
    int array[5] = {10, 20, 30, 40, 50};
    int i;
    
    printf("===== インクリメント・デクリメント演算子 =====\n");
    
    /* 基本的な動作確認 */
    printf("\n=== 基本的な動作 ===\n");
    
    a = 5;
    printf("初期値: a = %d\n", a);
    
    result = a++;  /* 後置インクリメント */
    printf("result = a++ → result = %d, a = %d\n", result, a);
    
    a = 5;
    result = ++a;  /* 前置インクリメント */
    printf("result = ++a → result = %d, a = %d\n", result, a);
    
    a = 5;
    result = a--;  /* 後置デクリメント */
    printf("result = a-- → result = %d, a = %d\n", result, a);
    
    a = 5;
    result = --a;  /* 前置デクリメント */
    printf("result = --a → result = %d, a = %d\n", result, a);
    
    /* 式の中での動作確認 */
    printf("\n=== 式の中での動作 ===\n");
    
    a = 5;
    b = 3;
    result = a++ * b;
    printf("a = 5, b = 3\n");
    printf("result = a++ * b → result = %d, a = %d\n", result, a);
    
    a = 5;
    b = 3;
    result = ++a * b;
    printf("a = 5, b = 3\n");
    printf("result = ++a * b → result = %d, a = %d\n", result, a);
    
    /* 複雑な式での使用 */
    printf("\n=== 複雑な式での使用 ===\n");
    
    a = 10;
    b = 5;
    result = a++ + ++b;
    printf("a = 10, b = 5\n");
    printf("result = a++ + ++b → result = %d, a = %d, b = %d\n", 
           result, a, b);
    
    a = 10;
    b = 5;
    result = --a - b--;
    printf("a = 10, b = 5\n");
    printf("result = --a - b-- → result = %d, a = %d, b = %d\n", 
           result, a, b);
    
    /* 配列とポインタでの使用 */
    printf("\n=== 配列での使用 ===\n");
    printf("配列: ");
    for (i = 0; i < 5; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
    
    i = 0;
    int temp_val = array[i++];
    printf("array[i++] = %d, i = %d\n", temp_val, i);
    
    i = 0;
    temp_val = array[++i];
    printf("array[++i] = %d, i = %d\n", temp_val, i);
    
    /* 実用的な例：ループでの使用 */
    printf("\n=== ループでの実用例 ===\n");
    
    printf("後置インクリメント（i++）:\n");
    for (i = 0; i < 5; i++) {
        printf("i = %d, array[%d] = %d\n", i, i, array[i]);
    }
    
    printf("\n前置インクリメント（++i）:\n");
    for (i = 0; i < 5; ++i) {
        printf("i = %d, array[%d] = %d\n", i, i, array[i]);
    }
    
    /* 注意事項：未定義動作の例（コメントアウト） */
    printf("\n=== 注意事項 ===\n");
    printf("以下のような式は未定義動作となるので避けるべきです：\n");
    printf("  i = i++; （同じ変数への複数の副作用）\n");
    printf("  a[i] = i++; （評価順序が不定）\n");
    printf("  func(i++, i++); （引数の評価順序が不定）\n");
    
    /* ポインタでの使用例 */
    printf("\n=== ポインタでの使用例 ===\n");
    {
        int *ptr = array;
        
        printf("*ptr++ = %d （値を取得してからポインタを進める）\n", *ptr++);
        printf("現在のptr位置の値: %d\n", *ptr);
        
        ptr = array;  /* リセット */
        printf("*++ptr = %d （ポインタを進めてから値を取得）\n", *++ptr);
        printf("現在のptr位置の値: %d\n", *ptr);
    }
    
    return 0;
}

/*
実行例:
$ ./ex3_3_increment
===== インクリメント・デクリメント演算子 =====

=== 基本的な動作 ===
初期値: a = 5
result = a++ → result = 5, a = 6
result = ++a → result = 6, a = 6
result = a-- → result = 5, a = 4
result = --a → result = 4, a = 4

=== 式の中での動作 ===
a = 5, b = 3
result = a++ * b → result = 15, a = 6
a = 5, b = 3
result = ++a * b → result = 18, a = 6

=== 複雑な式での使用 ===
a = 10, b = 5
result = a++ + ++b → result = 16, a = 11, b = 6
a = 10, b = 5
result = --a - b-- → result = 4, a = 9, b = 4

=== 配列での使用 ===
配列: 10 20 30 40 50
array[i++] = 10, i = 1
array[++i] = 20, i = 1

=== ループでの実用例 ===
後置インクリメント（i++）:
i = 0, array[0] = 10
i = 1, array[1] = 20
i = 2, array[2] = 30
i = 3, array[3] = 40
i = 4, array[4] = 50

前置インクリメント（++i）:
i = 0, array[0] = 10
i = 1, array[1] = 20
i = 2, array[2] = 30
i = 3, array[3] = 40
i = 4, array[4] = 50

=== 注意事項 ===
以下のような式は未定義動作となるので避けるべきです：
  i = i++; （同じ変数への複数の副作用）
  a[i] = i++; （評価順序が不定）
  func(i++, i++); （引数の評価順序が不定）

=== ポインタでの使用例 ===
*ptr++ = 10 （値を取得してからポインタを進める）
現在のptr位置の値: 20
*++ptr = 20 （ポインタを進めてから値を取得）
現在のptr位置の値: 20

学習ポイント:
1. 前置と後置の違い（値の返却タイミング）
2. 式の中での評価順序
3. 配列やポインタでの実用的な使い方
4. 未定義動作を避けるための注意点
5. ループでの効率的な使用方法
*/