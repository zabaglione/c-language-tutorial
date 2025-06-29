/*
 * ファイル名: ex10_2_array_reverse_c99.c
 * 演習10-2: 配列とポインタ
 * 説明: ポインタ演算を使って配列の要素を逆順に表示
 * 規格: C99準拠
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

// C99: インライン関数で配列を表示
static inline void print_array_index(int arr[], int size, const char *label)
{
    printf("%s (インデックス記法): ", label);
    for (int i = 0; i < size; i++) {  // C99: forループ内で変数宣言
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// ポインタ記法で配列を表示
static inline void print_array_pointer(int *ptr, int size, const char *label)
{
    printf("%s (ポインタ記法): ", label);
    for (int i = 0; i < size; i++) {
        printf("%d ", *(ptr + i));
    }
    printf("\n");
}

// ポインタ演算で配列を逆順表示
void print_array_reverse_pointer(int *ptr, int size)
{
    int *last_ptr = ptr + size - 1;  // 最後の要素を指す
    
    printf("逆順表示 (ポインタ演算): ");
    for (int i = 0; i < size; i++) {
        printf("%d ", *last_ptr);
        last_ptr--;  // ポインタを前の要素に移動
    }
    printf("\n");
}

// ポインタインクリメントで配列を逆順表示
void print_array_reverse_increment(int *ptr, int size)
{
    int *reverse_ptr = ptr + size - 1;  // 最後の要素から開始
    
    printf("逆順表示 (デクリメント): ");
    while (reverse_ptr >= ptr) {
        printf("%d ", *reverse_ptr);
        reverse_ptr--;
    }
    printf("\n");
}

// 配列のアドレス情報を表示
void show_address_info(int *arr, int size)
{
    printf("\n=== アドレス情報 ===\n");
    printf("配列名のアドレス: %p\n", (void*)arr);
    printf("&arr[0]のアドレス: %p\n", (void*)&arr[0]);
    
    // C99: bool型による判定
    bool addresses_equal = (arr == &arr[0]);
    printf("同じアドレス? %s\n", addresses_equal ? "true" : "false");
    
    printf("\n各要素のアドレスと値:\n");
    for (int i = 0; i < size; i++) {
        printf("  arr[%d]: アドレス=%p, 値=%d, ポインタ記法=*(arr+%d)=%d\n",
               i, (void*)&arr[i], arr[i], i, *(arr + i));
    }
    
    printf("\nアドレス間隔の確認:\n");
    for (int i = 0; i < size - 1; i++) {
        ptrdiff_t byte_diff = (char*)&arr[i+1] - (char*)&arr[i];  // C99: ptrdiff_t
        printf("  arr[%d]とarr[%d]の差: %td バイト\n", i, i+1, byte_diff);
    }
    printf("  int型のサイズ: %zu バイト\n", sizeof(int));
}

// ポインタ演算の詳細確認
void demonstrate_pointer_arithmetic(int *arr, int size)
{
    printf("\n=== ポインタ演算の詳細 ===\n");
    int *ptr = arr;
    printf("基準ポインタ ptr = %p\n", (void*)ptr);
    
    for (int i = 0; i < size; i++) {
        printf("ptr + %d = %p, *(ptr + %d) = %d\n",
               i, (void*)(ptr + i), i, *(ptr + i));
    }
    
    printf("\n負のオフセットでのアクセス:\n");
    ptr = arr + size - 1;  // 最後の要素を指す
    printf("基準ポインタ ptr = %p (最後の要素)\n", (void*)ptr);
    
    for (int i = 0; i < size; i++) {
        printf("ptr - %d = %p, *(ptr - %d) = %d\n",
               i, (void*)(ptr - i), i, *(ptr - i));
    }
}

// 配列を実際に逆順に並び替える関数
void reverse_array_inplace(int *arr, int size)
{
    printf("\n=== 配列の実際の逆順並び替え ===\n");
    printf("並び替え前: ");
    print_array_pointer(arr, size, "");
    
    int *start = arr;
    int *end = arr + size - 1;
    
    while (start < end) {
        printf("交換: *%p(%d) ↔ *%p(%d)\n", 
               (void*)start, *start, (void*)end, *end);
        
        int temp = *start;  // C99: 使用箇所で変数宣言
        *start = *end;
        *end = temp;
        
        start++;
        end--;
    }
    
    printf("並び替え後: ");
    print_array_pointer(arr, size, "");
}

// C99: 可変長配列を処理する関数
void demonstrate_vla_reverse(int size)
{
    printf("\n=== 可変長配列の逆順処理（C99） ===\n");
    int vla[size];  // C99: 可変長配列
    
    // VLAの初期化
    for (int i = 0; i < size; i++) {
        vla[i] = (i + 1) * 10;
    }
    
    printf("VLA（サイズ%d）:\n", size);
    print_array_index(vla, size, "元の配列");
    print_array_reverse_pointer(vla, size);
    
    // VLAの実際の逆順並び替え
    reverse_array_inplace(vla, size);
}

// C99: restrict修飾子を使った高速逆順コピー
void reverse_copy_restrict(int * restrict dest, int * restrict src, int size)
{
    for (int i = 0; i < size; i++) {
        dest[i] = src[size - 1 - i];
    }
}

int main(void)
{
    printf("===== ポインタ演算による配列の逆順表示 =====\n\n");
    
    // C99: 初期化リスト
    int numbers[] = {10, 20, 30, 40, 50, 60};
    int backup[] = {10, 20, 30, 40, 50, 60};  // 元の配列のバックアップ
    int size = sizeof(numbers) / sizeof(numbers[0]);
    int *ptr = numbers;
    
    // 配列サイズの動的計算
    printf("配列サイズの動的計算:\n");
    printf("  sizeof(numbers) = %zu バイト\n", sizeof(numbers));
    printf("  sizeof(numbers[0]) = %zu バイト\n", sizeof(numbers[0]));
    printf("  要素数 = %d\n", size);
    
    printf("\n1. 通常の表示:\n");
    print_array_index(numbers, size, "元の配列");
    print_array_pointer(ptr, size, "元の配列");
    
    printf("\n2. 逆順表示の方法:\n");
    print_array_reverse_pointer(ptr, size);
    print_array_reverse_increment(ptr, size);
    
    // アドレス情報の表示
    show_address_info(numbers, size);
    
    // ポインタ演算の詳細
    demonstrate_pointer_arithmetic(numbers, size);
    
    // 実際の逆順並び替え
    reverse_array_inplace(numbers, size);
    
    printf("\n=== 元の配列との比較 ===\n");
    print_array_pointer(backup, size, "元の配列");
    print_array_pointer(numbers, size, "逆順配列");
    
    // 配列を元に戻す
    reverse_array_inplace(numbers, size);
    printf("\n再度逆順にして元に戻しました:\n");
    print_array_pointer(numbers, size, "復元された配列");
    
    // 部分配列の逆順表示
    printf("\n=== 部分配列の逆順表示 ===\n");
    int start_index = 1;
    int end_index = 4;
    int partial_size = end_index - start_index + 1;
    
    printf("部分配列 [%d-%d] の逆順表示:\n", start_index, end_index);
    printf("通常: ");
    for (int i = start_index; i <= end_index; i++) {  // C99: forループ内で変数宣言
        printf("%d ", numbers[i]);
    }
    printf("\n");
    
    printf("逆順: ");
    for (int i = end_index; i >= start_index; i--) {
        printf("%d ", numbers[i]);
    }
    printf("\n");
    
    printf("ポインタ演算: ");
    int *partial_end = numbers + end_index;
    for (int i = 0; i < partial_size; i++) {
        printf("%d ", *(partial_end - i));
    }
    printf("\n");
    
    // C99: 可変長配列のデモ
    demonstrate_vla_reverse(4);
    demonstrate_vla_reverse(7);
    
    // C99: restrict修飾子を使った逆順コピー
    printf("\n=== restrict修飾子による逆順コピー（C99） ===\n");
    int source[] = {100, 200, 300, 400, 500};
    int destination[5];
    int copy_size = 5;
    
    printf("コピー前:\n");
    print_array_pointer(source, copy_size, "  source");
    print_array_pointer(destination, copy_size, "  destination");
    
    reverse_copy_restrict(destination, source, copy_size);
    
    printf("逆順コピー後:\n");
    print_array_pointer(source, copy_size, "  source");
    print_array_pointer(destination, copy_size, "  destination");
    
    // C99: 複合リテラルを使った逆順表示
    printf("\n=== 複合リテラルの逆順表示（C99） ===\n");
    int *compound = (int[]){777, 888, 999};  // C99: 複合リテラル
    print_array_reverse_pointer(compound, 3);
    
    // C99: 指定初期化子の配列
    printf("\n=== 指定初期化子の配列（C99） ===\n");
    int sparse[10] = {[0] = 1, [3] = 4, [7] = 8, [9] = 10};  // C99: 指定初期化子
    print_array_index(sparse, 10, "指定初期化配列");
    print_array_reverse_pointer(sparse, 10);
    
    return 0;
}

/*
学習ポイント:
1. 配列とポインタの等価性:
   - 配列名は先頭要素のポインタと同等
   - arr[i] と *(arr + i) は同じ意味

2. ポインタ演算による逆順アクセス:
   - ptr + size - 1 で最後の要素を指す
   - デクリメントで前の要素に移動

3. アドレス演算の理解:
   - ポインタ演算は型サイズを自動考慮
   - 要素間のアドレス差は型サイズと一致

4. 実用的な配列操作:
   - 逆順表示の複数の方法
   - 実際の要素の並び替え
   - 部分配列の処理

5. メモリレイアウトの可視化:
   - 各要素のアドレス表示
   - ポインタ演算の詳細確認

6. 安全な境界チェック:
   - 配列の境界チェック (start < end)
   - ポインタの有効性確認
   - オーバーフロー・アンダーフローの防止

7. C99での拡張:
   - //コメントの使用
   - bool型による明確な判定
   - forループ内での変数宣言
   - インライン関数
   - 可変長配列（VLA）
   - restrict修飾子
   - 複合リテラル
   - 指定初期化子
   - ptrdiff_t型の使用

注意点:
- 配列の範囲外アクセスは未定義動作
- ポインタ演算は型サイズを自動考慮
- sizeof演算子は配列全体のサイズを返す
- restrict修飾子は重複しないポインタにのみ使用
*/
