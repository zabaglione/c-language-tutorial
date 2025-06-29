/*
 * pointer_arrays.c
 * ポインタと配列の関係、ポインタ演算を学習
 * C90準拠
 */

#include <stdio.h>

void print_array_with_index(int arr[], int size)
{
    int i;
    printf("インデックス記法: ");
    for (i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void print_array_with_pointer(int *ptr, int size)
{
    int i;
    printf("ポインタ記法: ");
    for (i = 0; i < size; i++) {
        printf("%d ", *(ptr + i));
    }
    printf("\n");
}

void print_array_with_increment(int *ptr, int size)
{
    int i;
    printf("インクリメント: ");
    for (i = 0; i < size; i++) {
        printf("%d ", *ptr);
        ptr++;  /* ポインタを次の要素に進める */
    }
    printf("\n");
}

int main(void)
{
    int numbers[6] = {10, 20, 30, 40, 50, 60};
    int *ptr = numbers;  /* 配列名は先頭要素のアドレス */
    int size = sizeof(numbers) / sizeof(numbers[0]);
    int i;
    int *start;     /* C90: ポインタ変数の宣言を先頭に配置 */
    int *end;
    char message[] = "Hello, World!";
    char *str_ptr;
    int str_len = 0;
    int matrix[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    int *matrix_ptr;
    int total_elements = 3 * 4;
    int a = 100, b = 200, c = 300;
    int *ptr_array[3];  /* ポインタの配列 */
    
    printf("===== 配列とポインタの関係 =====\n");
    printf("配列名numbers: %p\n", (void*)numbers);
    printf("&numbers[0]: %p\n", (void*)&numbers[0]);
    printf("ポインタptr: %p\n", (void*)ptr);
    printf("これらはすべて同じアドレスです\n");
    
    printf("\n===== 配列要素へのアクセス方法 =====\n");
    print_array_with_index(numbers, size);
    print_array_with_pointer(ptr, size);
    
    /* ポインタをリセット（print_array_with_incrementでptrが変更されるため） */
    ptr = numbers;
    print_array_with_increment(ptr, size);
    
    printf("\n===== ポインタ演算の詳細 =====\n");
    ptr = numbers;  /* 先頭に戻す */
    
    for (i = 0; i < size; i++) {
        printf("ptr + %d = %p, *(ptr + %d) = %d\n",
               i, (void*)(ptr + i), i, *(ptr + i));
    }
    
    printf("\n===== アドレスの差による要素間隔の確認 =====\n");
    printf("numbers[0]のアドレス: %p\n", (void*)&numbers[0]);
    printf("numbers[1]のアドレス: %p\n", (void*)&numbers[1]);
    printf("アドレス差: %ld バイト\n", 
           (char*)&numbers[1] - (char*)&numbers[0]);
    printf("int型のサイズ: %lu バイト\n", (unsigned long)sizeof(int));
    
    printf("\n===== ポインタによる配列の逆順表示 =====\n");
    ptr = numbers + size - 1;  /* 最後の要素を指す */
    printf("逆順: ");
    for (i = 0; i < size; i++) {
        printf("%d ", *ptr);
        ptr--;  /* ポインタを前の要素に戻す */
    }
    printf("\n");
    
    printf("\n===== ポインタ同士の演算 =====\n");
    start = &numbers[1];  /* numbers[1]を指す */
    end = &numbers[4];    /* numbers[4]を指す */
    
    printf("start が指す値: %d (numbers[1])\n", *start);
    printf("end が指す値: %d (numbers[4])\n", *end);
    printf("ポインタの差: %ld (要素数)\n", end - start);
    printf("バイト差: %ld バイト\n", (char*)end - (char*)start);
    
    printf("\n===== 文字列（文字配列）とポインタ =====\n");
    str_ptr = message;
    
    printf("文字列: %s\n", message);
    printf("文字ごとの表示: ");
    
    /* 文字列の終端（'\0'）まで表示 */
    while (*str_ptr != '\0') {
        printf("%c", *str_ptr);
        str_ptr++;
        str_len++;
    }
    printf("\n");
    printf("文字列の長さ: %d文字\n", str_len);
    
    printf("\n===== 2次元配列とポインタ =====\n");
    matrix_ptr = (int*)matrix;  /* 1次元ポインタとして扱う */
    
    printf("2次元配列を1次元ポインタで表示:\n");
    for (i = 0; i < total_elements; i++) {
        printf("%2d ", *(matrix_ptr + i));
        if ((i + 1) % 4 == 0) {
            printf("\n");
        }
    }
    
    printf("\n===== ポインタ配列の例 =====\n");
    
    ptr_array[0] = &a;
    ptr_array[1] = &b;
    ptr_array[2] = &c;
    
    printf("ポインタ配列の内容:\n");
    for (i = 0; i < 3; i++) {
        printf("ptr_array[%d] = %p, *ptr_array[%d] = %d\n",
               i, (void*)ptr_array[i], i, *ptr_array[i]);
    }
    
    return 0;
}

/*
学習ポイント:
1. 配列名は先頭要素のポインタと同等
2. ポインタ演算: ptr + n は n個後の要素を指す
3. *(ptr + i) と ptr[i] は同等
4. ポインタのインクリメント/デクリメント
5. ポインタ同士の差は要素数を表す
6. 文字列もポインタで操作可能
7. 2次元配列も1次元ポインタで扱える
8. ポインタの配列の活用

重要な概念:
- 配列の記法とポインタ記法の等価性
- ポインタ演算の自動的な型サイズ調整
- メモリレイアウトの理解
- 安全な境界チェックの重要性
*/
