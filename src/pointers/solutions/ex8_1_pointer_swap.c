/*
 * ファイル名: ex8_1_pointer_swap.c
 * 演習8-1: ポインタの基本操作
 * 説明: 2つの整数変数の値をポインタを使って交換
 * 規格: C90準拠
 */

#include <stdio.h>

/* ポインタを使った値の交換関数 */
void swap_with_pointers(int *ptr_a, int *ptr_b)
{
    int temp;
    
    printf("  swap関数内部:\n");
    printf("    交換前: *ptr_a = %d, *ptr_b = %d\n", *ptr_a, *ptr_b);
    printf("    ポインタ: ptr_a = %p, ptr_b = %p\n", (void*)ptr_a, (void*)ptr_b);
    
    temp = *ptr_a;
    *ptr_a = *ptr_b;
    *ptr_b = temp;
    
    printf("    交換後: *ptr_a = %d, *ptr_b = %d\n", *ptr_a, *ptr_b);
}

/* 参考：値渡しでは交換できない例 */
void swap_by_value(int a, int b)
{
    int temp;
    
    printf("  値渡し関数内部:\n");
    printf("    交換前: a = %d, b = %d\n", a, b);
    
    temp = a;
    a = b;
    b = temp;
    
    printf("    交換後: a = %d, b = %d\n", a, b);
    printf("    (この変更は呼び出し元には反映されません)\n");
}

int main(void)
{
    int x = 10, y = 20;
    int *ptr_x, *ptr_y;
    int numbers[4] = {100, 200, 300, 400};
    int *start, *end;
    int i; /* C90: ループ変数をブロックの先頭で宣言 */
    
    printf("===== ポインタによる値の交換デモ =====\n\n");
    
    /* 初期状態の表示 */
    printf("1. 初期状態:\n");
    printf("   x = %d (アドレス: %p)\n", x, (void*)&x);
    printf("   y = %d (アドレス: %p)\n", y, (void*)&y);
    
    /* ポインタの初期化 */
    ptr_x = &x;
    ptr_y = &y;
    
    printf("\n2. ポインタの初期化後:\n");
    printf("   ptr_x = %p (指す値: %d)\n", (void*)ptr_x, *ptr_x);
    printf("   ptr_y = %p (指す値: %d)\n", (void*)ptr_y, *ptr_y);
    
    /* ポインタを使った交換の実行 */
    printf("\n3. ポインタを使った交換の実行:\n");
    swap_with_pointers(ptr_x, ptr_y);
    
    printf("\n4. 交換後の状態（main関数内）:\n");
    printf("   x = %d (アドレス: %p)\n", x, (void*)&x);
    printf("   y = %d (アドレス: %p)\n", y, (void*)&y);
    printf("   *ptr_x = %d, *ptr_y = %d\n", *ptr_x, *ptr_y);
    
    /* 元に戻して値渡しとの比較 */
    printf("\n===== 参考：値渡しとの比較 =====\n");
    
    /* 元の値に戻す */
    x = 10; y = 20;
    printf("\n5. 値を元に戻しました: x = %d, y = %d\n", x, y);
    
    printf("\n6. 値渡しによる交換試行（効果なし）:\n");
    swap_by_value(x, y);
    
    printf("\n7. 値渡し後の状態（main関数内）:\n");
    printf("   x = %d, y = %d (変更されていない)\n", x, y);
    
    /* アドレス演算子の使用例 */
    printf("\n===== アドレス演算子の直接使用 =====\n");
    
    printf("\n8. アドレス演算子を直接使った交換:\n");
    printf("   交換前: x = %d, y = %d\n", x, y);
    swap_with_pointers(&x, &y);
    printf("   交換後: x = %d, y = %d\n", x, y);
    
    /* ポインタ演算の応用例 */
    printf("\n===== ポインタ演算の応用 =====\n");
    
    start = numbers;
    end = numbers + 3;
    
    printf("\n9. 配列の両端要素の交換:\n");
    printf("   配列: ");
    for (i = 0; i < 4; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");
    
    printf("   start = %p (*start = %d)\n", (void*)start, *start);
    printf("   end = %p (*end = %d)\n", (void*)end, *end);
    
    swap_with_pointers(start, end);
    
    printf("   交換後の配列: ");
    for (i = 0; i < 4; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");
    
    return 0;
}

/*
学習ポイント:
1. ポインタによる参照渡し:
   - 関数で元の変数の値を変更可能
   - アドレスを渡すことで間接アクセス
   
2. 値渡しとの違い:
   - 値渡しでは元の変数は変更されない
   - ポインタ渡しでは元の変数が変更される
   
3. アドレス演算子(&)の使用:
   - &variable で変数のアドレスを取得
   - 関数呼び出し時に直接使用可能
   
4. 間接参照演算子(*)の使用:
   - *pointer でポインタが指す値にアクセス
   - 左辺値として使用すると値の変更が可能
   
5. メモリアドレスの理解:
   - 変数のアドレスは実行ごとに変わる可能性
   - ポインタはアドレスを格納する変数
   
6. 実用的な応用:
   - 配列要素の交換
   - 複数の値を同時に変更する関数
   - データ構造の操作

注意点:
- ポインタは必ず有効なアドレスを指すよう初期化
- NULLポインタの参照は避ける
- ポインタが指すメモリが有効であることを確認
*/
