/*
 * pointer_basic.c
 * ポインタの宣言、初期化、基本的な操作を学習
 * C90準拠
 */

#include <stdio.h>

int main(void)
{
    int value = 42;         /* 通常の整数変数 */
    int *ptr;               /* 整数ポインタ変数の宣言 */
    int another_value = 100;
    char char_var = 'A';    /* C90: 全変数宣言を先頭に配置 */
    float float_var = 3.14f;
    double double_var = 2.718;
    char *char_ptr;
    float *float_ptr;
    double *double_ptr;
    int *null_ptr;          /* C90: NULLポインタ用変数 */
    void *generic_ptr;      /* C90: void*ポインタ用変数 */
    int int_val = 123;
    double double_val = 45.67;
    
    printf("===== ポインタの基本操作 =====\n");
    
    /* ポインタの初期化 */
    ptr = &value;           /* valueのアドレスをptrに代入 */
    
    printf("変数valueの値: %d\n", value);
    printf("変数valueのアドレス: %p\n", (void*)&value);
    printf("ポインタptrの値（アドレス）: %p\n", (void*)ptr);
    printf("ポインタptrが指す値: %d\n", *ptr);
    
    printf("\n===== 間接参照による値の変更 =====\n");
    printf("変更前: value = %d, *ptr = %d\n", value, *ptr);
    
    *ptr = 75;              /* ポインタを通じて値を変更 */
    printf("*ptr = 75 実行後:\n");
    printf("変更後: value = %d, *ptr = %d\n", value, *ptr);
    
    printf("\n===== ポインタの再代入 =====\n");
    printf("another_value = %d\n", another_value);
    
    ptr = &another_value;   /* ptrを別の変数に向ける */
    printf("ptr = &another_value 実行後:\n");
    printf("ポインタptrが指す値: %d\n", *ptr);
    printf("ポインタptrのアドレス: %p\n", (void*)ptr);
    
    printf("\n===== 様々なデータ型のポインタ =====\n");
    
    /* C90: ポインタの初期化は宣言後に */
    char_ptr = &char_var;
    float_ptr = &float_var;
    double_ptr = &double_var;
    
    printf("char値: %c (アドレス: %p)\n", *char_ptr, (void*)char_ptr);
    printf("float値: %.2f (アドレス: %p)\n", *float_ptr, (void*)float_ptr);
    printf("double値: %.3f (アドレス: %p)\n", *double_ptr, (void*)double_ptr);
    
    printf("\n===== ポインタのサイズ =====\n");
    printf("int*のサイズ: %lu バイト\n", (unsigned long)sizeof(int*));
    printf("char*のサイズ: %lu バイト\n", (unsigned long)sizeof(char*));
    printf("float*のサイズ: %lu バイト\n", (unsigned long)sizeof(float*));
    printf("double*のサイズ: %lu バイト\n", (unsigned long)sizeof(double*));
    
    printf("\n===== NULLポインタ =====\n");
    null_ptr = NULL;        /* C90: 初期化は宣言後に */
    printf("NULLポインタの値: %p\n", (void*)null_ptr);
    
    if (null_ptr == NULL) {
        printf("null_ptrはNULLです（安全チェック）\n");
    }
    
    /* NULLポインタの参照は危険なのでコメントアウト */
    /* printf("NULL参照: %d\n", *null_ptr);  // 危険！ */
    
    printf("\n===== void*ポインタ（汎用ポインタ） =====\n");
    
    generic_ptr = &int_val;
    printf("intを指すvoid*: %d\n", *(int*)generic_ptr);
    
    generic_ptr = &double_val;
    printf("doubleを指すvoid*: %.2f\n", *(double*)generic_ptr);
    
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

注意点:
- 未初期化ポインタの使用は危険
- NULLポインタの参照は避ける
- void*ポインタは使用時に適切な型キャストが必要
*/
