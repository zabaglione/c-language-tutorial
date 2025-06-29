/*
 * pointer_arrays_c99.c
 * ポインタと配列の関係、ポインタ演算を学習
 * C99準拠 - //コメント、bool型、変数宣言位置の自由化、可変長配列
 */

#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// C99: インライン関数
static inline void print_array_with_index(int arr[], int size)
{
    printf("インデックス記法: ");
    for (int i = 0; i < size; i++) {  // C99: forループ内で変数宣言
        printf("%d ", arr[i]);
    }
    printf("\n");
}

static inline void print_array_with_pointer(int *ptr, int size)
{
    printf("ポインタ記法: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", *(ptr + i));
    }
    printf("\n");
}

static inline void print_array_with_increment(int *ptr, int size)
{
    printf("インクリメント: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", *ptr);
        ptr++;  // ポインタを次の要素に進める
    }
    printf("\n");
}

// C99: 可変長配列を使用した関数
void demonstrate_vla(int size)
{
    int vla[size];  // C99: 可変長配列（VLA）
    
    printf("\n===== 可変長配列のデモ（C99） =====\n");
    printf("サイズ %d の可変長配列を作成\n", size);
    
    // 配列の初期化
    for (int i = 0; i < size; i++) {
        vla[i] = (i + 1) * 10;
    }
    
    printf("可変長配列の内容: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", vla[i]);
    }
    printf("\n");
    
    // ポインタでアクセス
    int *vla_ptr = vla;
    printf("ポインタでアクセス: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", *(vla_ptr + i));
    }
    printf("\n");
}

int main(void)
{
    printf("===== 配列とポインタの関係 =====\n");
    
    // C99: 配列の宣言と初期化
    int numbers[6] = {10, 20, 30, 40, 50, 60};
    int *ptr = numbers;  // 配列名は先頭要素のアドレス
    int size = sizeof(numbers) / sizeof(numbers[0]);
    
    printf("配列名numbers: %p\n", (void*)numbers);
    printf("&numbers[0]: %p\n", (void*)&numbers[0]);
    printf("ポインタptr: %p\n", (void*)ptr);
    
    // C99: bool型による比較
    bool addresses_equal = (numbers == &numbers[0]);
    printf("これらはすべて同じアドレス? %s\n", addresses_equal ? "true" : "false");
    
    printf("\n===== 配列要素へのアクセス方法 =====\n");
    print_array_with_index(numbers, size);
    print_array_with_pointer(ptr, size);
    
    // ポインタをリセット（print_array_with_incrementでptrが変更されるため）
    ptr = numbers;
    print_array_with_increment(ptr, size);
    
    printf("\n===== ポインタ演算の詳細 =====\n");
    ptr = numbers;  // 先頭に戻す
    
    for (int i = 0; i < size; i++) {  // C99: forループ内で変数宣言
        printf("ptr + %d = %p, *(ptr + %d) = %d\n",
               i, (void*)(ptr + i), i, *(ptr + i));
    }
    
    printf("\n===== アドレスの差による要素間隔の確認 =====\n");
    printf("numbers[0]のアドレス: %p\n", (void*)&numbers[0]);
    printf("numbers[1]のアドレス: %p\n", (void*)&numbers[1]);
    
    // C99: ptrdiff_t型での差分計算
    ptrdiff_t byte_diff = (char*)&numbers[1] - (char*)&numbers[0];
    printf("アドレス差: %td バイト\n", byte_diff);  // C99: %td for ptrdiff_t
    printf("int型のサイズ: %zu バイト\n", sizeof(int));
    
    printf("\n===== ポインタによる配列の逆順表示 =====\n");
    ptr = numbers + size - 1;  // 最後の要素を指す
    printf("逆順: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", *ptr);
        ptr--;  // ポインタを前の要素に戻す
    }
    printf("\n");
    
    printf("\n===== ポインタ同士の演算 =====\n");
    int *start = &numbers[1];  // numbers[1]を指す
    int *end = &numbers[4];    // numbers[4]を指す
    
    printf("start が指す値: %d (numbers[1])\n", *start);
    printf("end が指す値: %d (numbers[4])\n", *end);
    printf("ポインタの差: %td (要素数)\n", end - start);  // C99: %td
    printf("バイト差: %td バイト\n", (char*)end - (char*)start);
    
    printf("\n===== 文字列（文字配列）とポインタ =====\n");
    char message[] = "Hello, World!";
    char *str_ptr = message;
    int str_len = 0;
    
    printf("文字列: %s\n", message);
    printf("文字ごとの表示: ");
    
    // 文字列の終端（'\0'）まで表示
    while (*str_ptr != '\0') {
        printf("%c", *str_ptr);
        str_ptr++;
        str_len++;
    }
    printf("\n");
    printf("文字列の長さ: %d文字\n", str_len);
    
    printf("\n===== 2次元配列とポインタ =====\n");
    int matrix[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    int *matrix_ptr = (int*)matrix;  // 1次元ポインタとして扱う
    int total_elements = 3 * 4;
    
    printf("2次元配列を1次元ポインタで表示:\n");
    for (int i = 0; i < total_elements; i++) {
        printf("%2d ", *(matrix_ptr + i));
        if ((i + 1) % 4 == 0) {
            printf("\n");
        }
    }
    
    printf("\n===== ポインタ配列の例 =====\n");
    int a = 100, b = 200, c = 300;
    int *ptr_array[3] = {&a, &b, &c};  // C99: 初期化リストで配列を初期化
    
    printf("ポインタ配列の内容:\n");
    for (int i = 0; i < 3; i++) {
        printf("ptr_array[%d] = %p, *ptr_array[%d] = %d\n",
               i, (void*)ptr_array[i], i, *ptr_array[i]);
    }
    
    // C99: 複合リテラルの例
    printf("\n===== 複合リテラル（C99） =====\n");
    int *compound_ptr = (int[]){100, 200, 300, 400};  // C99: 複合リテラル
    printf("複合リテラルによる配列:\n");
    for (int i = 0; i < 4; i++) {
        printf("  compound_ptr[%d] = %d\n", i, compound_ptr[i]);
    }
    
    // C99: 指定初期化子の例
    printf("\n===== 指定初期化子（C99） =====\n");
    int designated[10] = {[0] = 1, [4] = 5, [9] = 10};  // C99: 指定初期化子
    printf("指定初期化子による配列:\n");
    for (int i = 0; i < 10; i++) {
        if (designated[i] != 0) {
            printf("  designated[%d] = %d\n", i, designated[i]);
        }
    }
    
    // 可変長配列のデモ
    demonstrate_vla(4);
    demonstrate_vla(7);
    
    // C99: flexibleメンバー配列の概念（構造体で使用）
    printf("\n===== フレキシブル配列メンバーの概念（C99） =====\n");
    printf("構造体の最後のメンバーを未サイズ配列として宣言可能\n");
    printf("（実際の使用例は構造体の章で詳しく説明）\n");
    
    return 0;
}

/*
学習ポイント:
1. 配列名とポインタの等価性
2. ポインタ演算による配列要素アクセス
3. インデックス記法とポインタ記法の関係
4. 配列の境界を意識したポインタ操作
5. 文字列とポインタの関係
6. 多次元配列のポインタ表現
7. 2次元配列も1次元ポインタで扱える
8. ポインタの配列の活用

C99での拡張:
9. //コメントの使用
10. bool型による明確な判定
11. forループ内での変数宣言
12. インライン関数
13. 可変長配列（VLA）
14. 複合リテラル
15. 指定初期化子
16. %td, %zuフォーマット指定子

重要な概念:
- 配列の記法とポインタ記法の等価性
- ポインタ演算の自動的な型サイズ調整
- メモリレイアウトの理解
- 安全な境界チェックの重要性
- C99の新機能による柔軟な配列操作
*/
