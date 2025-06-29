/*
 * ファイル名: ex10_2_array_reverse.c
 * 演習10-2: 配列とポインタ
 * 説明: ポインタ演算を使って配列の要素を逆順に表示
 * 規格: C90準拠
 */

#include <stdio.h>

/* インデックス記法で配列を表示 */
void print_array_index(int arr[], int size, char *label)
{
    int i;
    
    printf("%s (インデックス記法): ", label);
    for (i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

/* ポインタ記法で配列を表示 */
void print_array_pointer(int *ptr, int size, char *label)
{
    int i;
    
    printf("%s (ポインタ記法): ", label);
    for (i = 0; i < size; i++) {
        printf("%d ", *(ptr + i));
    }
    printf("\n");
}

/* ポインタ演算で配列を逆順表示 */
void print_array_reverse_pointer(int *ptr, int size)
{
    int i;
    int *last_ptr = ptr + size - 1;  /* 最後の要素を指す */
    
    printf("逆順表示 (ポインタ演算): ");
    for (i = 0; i < size; i++) {
        printf("%d ", *last_ptr);
        last_ptr--;  /* ポインタを前の要素に移動 */
    }
    printf("\n");
}

/* ポインタインクリメントで配列を逆順表示 */
void print_array_reverse_increment(int *ptr, int size)
{
    int *reverse_ptr = ptr + size - 1;  /* 最後の要素から開始 */
    
    printf("逆順表示 (デクリメント): ");
    while (reverse_ptr >= ptr) {
        printf("%d ", *reverse_ptr);
        reverse_ptr--;
    }
    printf("\n");
}

/* 配列のアドレス情報を表示 */
void show_address_info(int *arr, int size)
{
    int i;
    
    printf("\n=== アドレス情報 ===\n");
    printf("配列名のアドレス: %p\n", (void*)arr);
    printf("&arr[0]のアドレス: %p\n", (void*)&arr[0]);
    printf("同じアドレス? %s\n", (arr == &arr[0]) ? "はい" : "いいえ");
    
    printf("\n各要素のアドレスと値:\n");
    for (i = 0; i < size; i++) {
        printf("  arr[%d]: アドレス=%p, 値=%d, ポインタ記法=*(arr+%d)=%d\n",
               i, (void*)&arr[i], arr[i], i, *(arr + i));
    }
    
    printf("\nアドレス間隔の確認:\n");
    for (i = 0; i < size - 1; i++) {
        long byte_diff = (char*)&arr[i+1] - (char*)&arr[i];
        printf("  arr[%d]とarr[%d]の差: %ld バイト\n", i, i+1, byte_diff);
    }
    printf("  int型のサイズ: %lu バイト\n", (unsigned long)sizeof(int));
}

/* ポインタ演算の詳細確認 */
void demonstrate_pointer_arithmetic(int *arr, int size)
{
    int i;
    int *ptr = arr;
    
    printf("\n=== ポインタ演算の詳細 ===\n");
    printf("基準ポインタ ptr = %p\n", (void*)ptr);
    
    for (i = 0; i < size; i++) {
        printf("ptr + %d = %p, *(ptr + %d) = %d\n",
               i, (void*)(ptr + i), i, *(ptr + i));
    }
    
    printf("\n負のオフセットでのアクセス:\n");
    ptr = arr + size - 1;  /* 最後の要素を指す */
    printf("基準ポインタ ptr = %p (最後の要素)\n", (void*)ptr);
    
    for (i = 0; i < size; i++) {
        printf("ptr - %d = %p, *(ptr - %d) = %d\n",
               i, (void*)(ptr - i), i, *(ptr - i));
    }
}

/* 配列を実際に逆順に並び替える関数 */
void reverse_array_inplace(int *arr, int size)
{
    int *start = arr;
    int *end = arr + size - 1;
    int temp;
    
    printf("\n=== 配列の実際の逆順並び替え ===\n");
    printf("並び替え前: ");
    print_array_pointer(arr, size, "");
    
    while (start < end) {
        printf("交換: *%p(%d) ↔ *%p(%d)\n", 
               (void*)start, *start, (void*)end, *end);
        
        temp = *start;
        *start = *end;
        *end = temp;
        
        start++;
        end--;
    }
    
    printf("並び替え後: ");
    print_array_pointer(arr, size, "");
}

int main(void)
{
    int numbers[] = {10, 20, 30, 40, 50, 60};
    int backup[] = {10, 20, 30, 40, 50, 60};  /* 元の配列のバックアップ */
    int size = sizeof(numbers) / sizeof(numbers[0]);
    int *ptr = numbers;
    
    printf("===== ポインタ演算による配列の逆順表示 =====\n\n");
    
    /* 配列サイズの動的計算 */
    printf("配列サイズの動的計算:\n");
    printf("  sizeof(numbers) = %lu バイト\n", (unsigned long)sizeof(numbers));
    printf("  sizeof(numbers[0]) = %lu バイト\n", (unsigned long)sizeof(numbers[0]));
    printf("  要素数 = %d\n", size);
    
    printf("\n1. 通常の表示:\n");
    print_array_index(numbers, size, "元の配列");
    print_array_pointer(ptr, size, "元の配列");
    
    printf("\n2. 逆順表示の方法:\n");
    print_array_reverse_pointer(ptr, size);
    print_array_reverse_increment(ptr, size);
    
    /* アドレス情報の表示 */
    show_address_info(numbers, size);
    
    /* ポインタ演算の詳細 */
    demonstrate_pointer_arithmetic(numbers, size);
    
    /* 実際の逆順並び替え */
    reverse_array_inplace(numbers, size);
    
    printf("\n=== 元の配列との比較 ===\n");
    print_array_pointer(backup, size, "元の配列");
    print_array_pointer(numbers, size, "逆順配列");
    
    /* 配列を元に戻す */
    reverse_array_inplace(numbers, size);
    printf("\n再度逆順にして元に戻しました:\n");
    print_array_pointer(numbers, size, "復元された配列");
    
    /* 部分配列の逆順表示 */
    printf("\n=== 部分配列の逆順表示 ===\n");
    {
        int start_index = 1;
        int end_index = 4;
        int partial_size = end_index - start_index + 1;
        int i; /* C90: ループ変数をブロックの先頭で宣言 */
        int *partial_end;
    
        printf("部分配列 [%d-%d] の逆順表示:\n", start_index, end_index);
        printf("通常: ");
        for (i = start_index; i <= end_index; i++) {
            printf("%d ", numbers[i]);
        }
        printf("\n");
        
        printf("逆順: ");
        for (i = end_index; i >= start_index; i--) {
            printf("%d ", numbers[i]);
        }
        printf("\n");
        
        printf("ポインタ演算: ");
        partial_end = numbers + end_index;
        for (i = 0; i < partial_size; i++) {
            printf("%d ", *(partial_end - i));
        }
        printf("\n");
    }
    
    return 0;
}

/*
学習ポイント:
1. 配列とポインタの等価性:
   - 配列名は先頭要素のポインタと同等
   - arr[i] と *(arr + i) は同じ意味
   
2. ポインタ演算:
   - ptr + n は n個後の要素を指す
   - ptr - n は n個前の要素を指す
   - ポインタ同士の差は要素数
   
3. 逆順アクセスの方法:
   - 最後の要素から順次デクリメント
   - 負のオフセットを使用
   - ポインタの境界チェック
   
4. メモリレイアウト:
   - 配列要素は連続したメモリに配置
   - アドレス差 = 要素サイズ × 要素数の差
   
5. 実用的な応用:
   - 配列の逆順並び替え
   - 部分配列の処理
   - 動的なサイズ計算
   
6. 安全なプログラミング:
   - 配列の境界チェック (start < end)
   - ポインタの有効性確認
   - オーバーフロー・アンダーフローの防止

注意点:
- 配列の範囲外アクセスは未定義動作
- ポインタ演算は型サイズを自動考慮
- sizeof演算子は配列全体のサイズを返す
*/
