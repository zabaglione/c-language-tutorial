/*
 * ファイル名: ex8_1_pointer_swap_c99.c
 * 演習8-1: ポインタの基本操作
 * 説明: 2つの整数変数の値をポインタを使って交換
 * 規格: C99準拠
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

// C99: インライン関数として実装
static inline void swap_with_pointers(int *ptr_a, int *ptr_b)
{
    printf("  swap関数内部:\n");
    printf("    交換前: *ptr_a = %d, *ptr_b = %d\n", *ptr_a, *ptr_b);
    printf("    ポインタ: ptr_a = %p, ptr_b = %p\n", (void*)ptr_a, (void*)ptr_b);
    
    int temp = *ptr_a;  // C99: 使用箇所で変数宣言
    *ptr_a = *ptr_b;
    *ptr_b = temp;
    
    printf("    交換後: *ptr_a = %d, *ptr_b = %d\n", *ptr_a, *ptr_b);
}

// 参考：値渡しでは交換できない例
void swap_by_value(int a, int b)
{
    printf("  値渡し関数内部:\n");
    printf("    交換前: a = %d, b = %d\n", a, b);
    
    int temp = a;  // C99: 使用箇所で変数宣言
    a = b;
    b = temp;
    
    printf("    交換後: a = %d, b = %d\n", a, b);
    printf("    (この変更は呼び出し元には反映されません)\n");
}

// C99: bool型を返すヘルパー関数
static inline bool pointers_are_valid(int *ptr1, int *ptr2)
{
    return (ptr1 != NULL && ptr2 != NULL);
}

// C99: restrict修飾子を使った高速交換関数
void swap_with_restrict(int * restrict ptr_a, int * restrict ptr_b)
{
    if (!pointers_are_valid(ptr_a, ptr_b)) {
        printf("エラー: 無効なポインタが渡されました\n");
        return;
    }
    
    // restrict修飾子により、ptr_aとptr_bは重複しないことが保証される
    int temp = *ptr_a;
    *ptr_a = *ptr_b;
    *ptr_b = temp;
}

// 汎用交換関数（void*版）
void swap_generic(void *ptr1, void *ptr2, size_t size)
{
    char *p1 = (char*)ptr1;
    char *p2 = (char*)ptr2;
    
    for (size_t i = 0; i < size; i++) {
        char temp = p1[i];
        p1[i] = p2[i];
        p2[i] = temp;
    }
}

int main(void)
{
    printf("===== ポインタによる値の交換デモ =====\n\n");
    
    // C99: 使用箇所で変数宣言
    int x = 10, y = 20;
    int *ptr_x = &x, *ptr_y = &y;  // C99: 宣言と同時に初期化
    
    // 初期状態の表示
    printf("1. 初期状態:\n");
    printf("   x = %d (アドレス: %p)\n", x, (void*)&x);
    printf("   y = %d (アドレス: %p)\n", y, (void*)&y);
    
    printf("\n2. ポインタの初期化後:\n");
    printf("   ptr_x = %p (指す値: %d)\n", (void*)ptr_x, *ptr_x);
    printf("   ptr_y = %p (指す値: %d)\n", (void*)ptr_y, *ptr_y);
    
    // C99: bool型による有効性チェック
    bool pointers_valid = pointers_are_valid(ptr_x, ptr_y);
    printf("   ポインタは有効? %s\n", pointers_valid ? "true" : "false");
    
    // ポインタを使った交換の実行
    printf("\n3. ポインタを使った交換の実行:\n");
    swap_with_pointers(ptr_x, ptr_y);
    
    printf("\n4. 交換後の状態（main関数内）:\n");
    printf("   x = %d (アドレス: %p)\n", x, (void*)&x);
    printf("   y = %d (アドレス: %p)\n", y, (void*)&y);
    printf("   *ptr_x = %d, *ptr_y = %d\n", *ptr_x, *ptr_y);
    
    // 元に戻して値渡しとの比較
    printf("\n===== 参考：値渡しとの比較 =====\n");
    
    // 元の値に戻す
    x = 10; y = 20;
    printf("\n5. 値を元に戻しました: x = %d, y = %d\n", x, y);
    
    printf("\n6. 値渡しによる交換試行（効果なし）:\n");
    swap_by_value(x, y);
    
    printf("\n7. 値渡し後の状態（main関数内）:\n");
    printf("   x = %d, y = %d (変更されていない)\n", x, y);
    
    // アドレス演算子の使用例
    printf("\n===== アドレス演算子の直接使用 =====\n");
    
    printf("\n8. アドレス演算子を直接使った交換:\n");
    printf("   交換前: x = %d, y = %d\n", x, y);
    swap_with_pointers(&x, &y);
    printf("   交換後: x = %d, y = %d\n", x, y);
    
    // ポインタ演算の応用例
    printf("\n===== ポインタ演算の応用 =====\n");
    
    int numbers[4] = {100, 200, 300, 400};
    int *start = numbers;
    int *end = numbers + 3;
    
    printf("\n9. 配列の両端要素の交換:\n");
    printf("   配列: ");
    for (int i = 0; i < 4; i++) {  // C99: forループ内で変数宣言
        printf("%d ", numbers[i]);
    }
    printf("\n");
    
    printf("   start = %p (*start = %d)\n", (void*)start, *start);
    printf("   end = %p (*end = %d)\n", (void*)end, *end);
    
    swap_with_pointers(start, end);
    
    printf("   交換後の配列: ");
    for (int i = 0; i < 4; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");
    
    // C99: restrict修飾子のテスト
    printf("\n===== restrict修飾子を使った交換（C99） =====\n");
    int a = 500, b = 600;
    printf("restrict交換前: a = %d, b = %d\n", a, b);
    swap_with_restrict(&a, &b);
    printf("restrict交換後: a = %d, b = %d\n", a, b);
    
    // C99: 固定幅整数型のポインタ交換
    printf("\n===== 固定幅整数型の交換（C99） =====\n");
    int32_t val1 = 123456;
    int32_t val2 = 789012;
    
    printf("int32_t交換前: val1 = %d, val2 = %d\n", val1, val2);
    
    // 汎用交換関数を使用
    swap_generic(&val1, &val2, sizeof(int32_t));
    printf("int32_t交換後: val1 = %d, val2 = %d\n", val1, val2);
    
    // C99: 複合リテラルを使ったポインタ操作
    printf("\n===== 複合リテラルとポインタ（C99） =====\n");
    int *temp_ptr = (int[]){999, 888};  // C99: 複合リテラル
    printf("複合リテラル: temp_ptr[0] = %d, temp_ptr[1] = %d\n", 
           temp_ptr[0], temp_ptr[1]);
    
    swap_with_pointers(&temp_ptr[0], &temp_ptr[1]);
    printf("交換後: temp_ptr[0] = %d, temp_ptr[1] = %d\n", 
           temp_ptr[0], temp_ptr[1]);
    
    return 0;
}

/*
学習ポイント:
1. ポインタによる参照渡し:
   - 関数で元の変数の値を変更可能
   - アドレスを渡すことで直接メモリを操作

2. 値渡しとの違い:
   - 値渡しでは呼び出し元の変数は変更されない
   - ポインタ渡しで真の値の交換が可能

3. ポインタの安全な使用:
   - NULLチェックによる安全性向上
   - 有効なアドレスの確認

4. 実用的な応用:
   - 配列要素の交換
   - 複数の値を同時に変更する関数
   - データ構造の操作

5. C99での拡張:
   - //コメントの使用
   - bool型による明確な真偽値判定
   - インライン関数による最適化
   - forループ内での変数宣言
   - restrict修飾子による最適化ヒント
   - 汎用的なvoid*ポインタを使った関数
   - 複合リテラルの活用

注意点:
- ポインタは必ず有効なアドレスを指すよう初期化
- NULLポインタの参照は避ける
- ポインタが指すメモリが有効であることを確認
- restrict修飾子は重複しないポインタにのみ使用
*/
