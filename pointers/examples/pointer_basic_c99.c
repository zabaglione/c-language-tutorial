/*
 * pointer_basic_c99.c
 * ポインタの宣言、初期化、基本的な操作を学習
 * C99準拠 - //コメント、bool型、変数宣言位置の自由化、stdint.h
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

int main(void)
{
    printf("===== ポインタの基本操作 =====\n");
    
    // C99: 使用箇所で変数宣言
    int value = 42;         // 通常の整数変数
    int *ptr = &value;      // C99: 宣言と同時に初期化
    
    printf("変数valueの値: %d\n", value);
    printf("変数valueのアドレス: %p\n", (void*)&value);
    printf("ポインタptrの値（アドレス）: %p\n", (void*)ptr);
    printf("ポインタptrが指す値: %d\n", *ptr);
    
    printf("\n===== 間接参照による値の変更 =====\n");
    printf("変更前: value = %d, *ptr = %d\n", value, *ptr);
    
    *ptr = 75;              // ポインタを通じて値を変更
    printf("*ptr = 75 実行後:\n");
    printf("変更後: value = %d, *ptr = %d\n", value, *ptr);
    
    printf("\n===== ポインタの再代入 =====\n");
    int another_value = 100;  // C99: 必要な時点で宣言
    printf("another_value = %d\n", another_value);
    
    ptr = &another_value;   // ptrを別の変数に向ける
    printf("ptr = &another_value 実行後:\n");
    printf("ポインタptrが指す値: %d\n", *ptr);
    printf("ポインタptrのアドレス: %p\n", (void*)ptr);
    
    printf("\n===== 様々なデータ型のポインタ =====\n");
    // C99: 使用箇所で変数宣言
    char char_var = 'A';
    float float_var = 3.14f;
    double double_var = 2.718;
    
    char *char_ptr = &char_var;
    float *float_ptr = &float_var;
    double *double_ptr = &double_var;
    
    printf("char値: %c (アドレス: %p)\n", *char_ptr, (void*)char_ptr);
    printf("float値: %.2f (アドレス: %p)\n", *float_ptr, (void*)float_ptr);
    printf("double値: %.3f (アドレス: %p)\n", *double_ptr, (void*)double_ptr);
    
    printf("\n===== ポインタのサイズ =====\n");
    printf("int*のサイズ: %zu バイト\n", sizeof(int*));      // C99: %zu for size_t
    printf("char*のサイズ: %zu バイト\n", sizeof(char*));
    printf("float*のサイズ: %zu バイト\n", sizeof(float*));
    printf("double*のサイズ: %zu バイト\n", sizeof(double*));
    
    printf("\n===== NULLポインタ（C99での改良） =====\n");
    int *null_ptr = NULL;
    printf("NULLポインタの値: %p\n", (void*)null_ptr);
    
    // C99: bool型による明確な判定
    bool is_null = (null_ptr == NULL);
    printf("null_ptrはNULL? %s（bool型での判定）\n", is_null ? "true" : "false");
    
    // NULLポインタの参照は危険なのでコメントアウト
    // printf("NULL参照: %d\n", *null_ptr);  // 危険！
    
    printf("\n===== void*ポインタ（汎用ポインタ） =====\n");
    void *generic_ptr;
    int int_val = 123;
    double double_val = 45.67;
    
    generic_ptr = &int_val;
    printf("intを指すvoid*: %d\n", *(int*)generic_ptr);
    
    generic_ptr = &double_val;
    printf("doubleを指すvoid*: %.2f\n", *(double*)generic_ptr);
    
    // C99: stdint.hによる正確な型指定
    printf("\n===== 固定幅整数型のポインタ（C99） =====\n");
    int8_t  byte_val = 127;        // 8ビット符号付き整数
    int16_t short_val = 32767;     // 16ビット符号付き整数
    int32_t int_val32 = 2147483647; // 32ビット符号付き整数
    
    int8_t  *byte_ptr = &byte_val;
    int16_t *short_ptr = &short_val;
    int32_t *int_ptr32 = &int_val32;
    
    printf("int8_t 値: %d (サイズ: %zu バイト)\n", *byte_ptr, sizeof(int8_t));
    printf("int16_t値: %d (サイズ: %zu バイト)\n", *short_ptr, sizeof(int16_t));
    printf("int32_t値: %d (サイズ: %zu バイト)\n", *int_ptr32, sizeof(int32_t));
    
    // C99: ポインタの演算と配列の例
    printf("\n===== ポインタ演算の基本（C99） =====\n");
    int numbers[] = {10, 20, 30, 40, 50};
    int *num_ptr = numbers;  // 配列の先頭を指す
    
    printf("配列要素へのポインタアクセス:\n");
    for (int i = 0; i < 5; i++) {  // C99: forループ内で変数宣言
        printf("  numbers[%d] = %d, *(num_ptr + %d) = %d\n", 
               i, numbers[i], i, *(num_ptr + i));
    }
    
    // C99: restrict キーワードの例（コンパイラの最適化ヒント）
    printf("\n===== restrict ポインタ（C99） =====\n");
    int source = 100;
    int destination = 200;
    int * restrict src_ptr = &source;     // C99: restrict修飾子
    int * restrict dst_ptr = &destination;
    
    printf("restrictポインタ使用前: source=%d, destination=%d\n", 
           *src_ptr, *dst_ptr);
    
    // このコード内では src_ptr と dst_ptr は別のメモリ位置を指すことが保証される
    *dst_ptr = *src_ptr + 50;
    
    printf("restrictポインタ使用後: source=%d, destination=%d\n", 
           *src_ptr, *dst_ptr);
    
    return 0;
}

/*
学習ポイント:
1. ポインタの宣言: int *ptr;
2. アドレス演算子: &variable
3. 間接参照演算子: *pointer
4. ポインタの初期化と再代入
5. NULLポインタの安全な使用
6. void*ポインタと型キャスト
7. ポインタのサイズは型に関係なく一定
8. 安全なプログラミングのためのNULLチェック

C99での拡張:
9. //コメントの使用
10. bool型による明確な真偽値判定
11. 変数宣言位置の自由化
12. forループ内での変数宣言
13. stdint.hによる固定幅整数型
14. %zuフォーマット指定子（size_t用）
15. restrictキーワードによる最適化ヒント

注意点:
- 未初期化ポインタの使用は危険
- NULLポインタの参照は避ける
- void*ポインタは使用時に適切な型キャストが必要
- restrictポインタは同じメモリ位置を指さないことが前提
*/
