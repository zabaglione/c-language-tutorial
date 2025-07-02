/*
 * ファイル名: ex14_3_array_callback_c99.c
 * 演習14-3: 配列処理のコールバック
 * 説明: コールバック関数を使って配列の各要素に異なる処理を適用するプログラム
 * 規格: C99準拠
 */
#include <stdio.h>

#define ARRAY_SIZE 6

// 配列処理用のコールバック関数群
void double_element(int *element)
{
    *element *= 2;
}

void decrement_element(int *element)
{
    *element -= 1;
}

void negate_element(int *element)
{
    *element = -(*element);
}

// 配列を表示する関数
void print_array(int *arr, int size, char *description)
{
    printf("%s: [", description);
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i < size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

// 配列の各要素にコールバック関数を適用する関数
void apply_to_array(int *arr, int size, void (*callback)(int *), char *operation_name)
{
    printf("\n=== %s を適用 ===\n", operation_name);
    print_array(arr, size, "処理前");
    
    for (int i = 0; i < size; i++) {
        callback(&arr[i]);
    }
    
    print_array(arr, size, "処理後");
}

// 配列を初期値にリセットする関数
void reset_array(int *arr, int *original, int size)
{
    for (int i = 0; i < size; i++) {
        arr[i] = original[i];
    }
}

int main(void)
{
    printf("=== 配列処理のコールバックデモ ===\n");
    
    // 初期配列と作業用配列
    int original_array[ARRAY_SIZE] = {1, 2, 3, 4, 5, 6};
    int work_array[ARRAY_SIZE];
    
    // コールバック関数ポインタ配列
    void (*operations[])(int *) = {double_element, decrement_element, negate_element};
    char *operation_names[] = {"各要素を倍にする", "各要素から1を引く", "各要素の符号を反転"};
    int num_operations = sizeof(operations) / sizeof(operations[0]);
    
    // 初期配列の表示
    print_array(original_array, ARRAY_SIZE, "初期配列");
    
    // 各操作を順次実行
    for (int i = 0; i < num_operations; i++) {
        // 作業用配列に初期値をコピー
        reset_array(work_array, original_array, ARRAY_SIZE);
        
        // コールバック関数を適用
        apply_to_array(work_array, ARRAY_SIZE, operations[i], operation_names[i]);
    }
    
    // 複数の操作を連続適用するデモ
    printf("\n=== 複数操作の連続適用デモ ===\n");
    reset_array(work_array, original_array, ARRAY_SIZE);
    print_array(work_array, ARRAY_SIZE, "開始");
    
    // 1. 倍にする
    for (int i = 0; i < ARRAY_SIZE; i++) {
        double_element(&work_array[i]);
    }
    print_array(work_array, ARRAY_SIZE, "倍にした後");
    
    // 2. 1を引く
    for (int i = 0; i < ARRAY_SIZE; i++) {
        decrement_element(&work_array[i]);
    }
    print_array(work_array, ARRAY_SIZE, "1を引いた後");
    
    // 3. 符号を反転
    for (int i = 0; i < ARRAY_SIZE; i++) {
        negate_element(&work_array[i]);
    }
    print_array(work_array, ARRAY_SIZE, "符号反転後");
    
    // 関数ポインタを使った動的選択のデモ
    printf("\n=== 動的関数選択デモ ===\n");
    int selection_pattern[] = {0, 1, 2, 0, 1, 2}; // 操作の選択パターン
    
    reset_array(work_array, original_array, ARRAY_SIZE);
    print_array(work_array, ARRAY_SIZE, "開始");
    
    for (int i = 0; i < ARRAY_SIZE; i++) {
        int op_index = selection_pattern[i];
        printf("要素[%d]: %s を適用\n", i, operation_names[op_index]);
        operations[op_index](&work_array[i]);
    }
    
    print_array(work_array, ARRAY_SIZE, "最終結果");
    
    return 0;
}

/*
学習ポイント:
1. コールバック関数の概念と実装
2. 関数ポインタを引数として渡す方法
3. 配列処理での関数ポインタ活用
4. 動的な処理選択システム

実装のポイント:
- C99準拠のため、変数を使用箇所の近くで宣言
- for文内でのループ変数宣言
- 配列の初期化を宣言と同時に実行
- コメントに//スタイルを使用
- コールバック関数は配列要素を直接変更
*/
