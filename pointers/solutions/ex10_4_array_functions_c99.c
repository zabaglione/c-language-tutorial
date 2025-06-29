/*
 * 演習10-4: 配列操作関数 (C99版)
 * 
 * 配列を操作する関数をポインタを使って実装する演習です。
 * C99の機能（可変長配列、複合リテラル、混合宣言など）を活用しています。
 * - 最大値・最小値を見つけてポインタを返す
 * - 平均値を計算する
 * - 統計情報をレポート形式で表示する
 * 
 * 作成者: C言語学習者
 * 作成日: 2024年
 */

#include <stdio.h>
#include <stdbool.h>  /* C99のbool型を使用 */

/*
 * 配列の最大値を見つけてそのポインタを返す
 * C99版: restrict修飾子と混合宣言を使用
 */
int* find_max(int * restrict arr, int size) {
    if (size <= 0) return NULL;  /* エラーチェック */
    
    int *max_ptr = arr;  /* 最初は先頭要素を最大値と仮定 */
    
    /* C99の混合宣言: ループ変数をループ内で宣言 */
    for (int i = 1; i < size; i++) {
        if (*(arr + i) > *max_ptr) {
            max_ptr = arr + i;
        }
    }
    
    return max_ptr;
}

/*
 * 配列の最小値を見つけてそのポインタを返す
 * C99版: restrict修飾子とinline関数として定義可能
 */
int* find_min(int * restrict arr, int size) {
    if (size <= 0) return NULL;  /* エラーチェック */
    
    int *min_ptr = arr;
    
    for (int i = 1; i < size; i++) {
        if (*(arr + i) < *min_ptr) {
            min_ptr = arr + i;
        }
    }
    
    return min_ptr;
}

/*
 * 配列の平均値を計算する
 * C99版: long long型を使用してオーバーフローを防ぐ
 */
double calculate_average(int * restrict arr, int size) {
    if (size <= 0) return 0.0;  /* エラーチェック */
    
    long long sum = 0;  /* C99のlong long型を使用 */
    
    for (int i = 0; i < size; i++) {
        sum += *(arr + i);
    }
    
    return (double)sum / size;
}

/*
 * 配列の統計情報を表示する（C99版）
 * 可変長配列を使った動的処理を含む
 */
void print_statistics(int * restrict arr, int size) {
    printf("========== 配列統計レポート (C99版) ==========\n");
    printf("配列のサイズ: %d要素\n\n", size);
    
    if (size <= 0) {
        printf("エラー: 配列サイズが無効です\n");
        return;
    }
    
    /* 配列の内容を表示 */
    printf("配列の内容:\n");
    for (int i = 0; i < size; i++) {
        printf("  arr[%d] = %d (アドレス: %p)\n", 
               i, *(arr + i), (void*)(arr + i));
    }
    printf("\n");
    
    /* 最大値の情報 */
    int *max_ptr = find_max(arr, size);
    if (max_ptr != NULL) {
        printf("最大値:\n");
        printf("  値: %d\n", *max_ptr);
        printf("  アドレス: %p\n", (void*)max_ptr);
        printf("  インデックス: %td\n", max_ptr - arr);  /* C99の%td指定子 */
        printf("\n");
    }
    
    /* 最小値の情報 */
    int *min_ptr = find_min(arr, size);
    if (min_ptr != NULL) {
        printf("最小値:\n");
        printf("  値: %d\n", *min_ptr);
        printf("  アドレス: %p\n", (void*)min_ptr);
        printf("  インデックス: %td\n", min_ptr - arr);
        printf("\n");
    }
    
    /* 平均値の情報 */
    double average = calculate_average(arr, size);
    printf("平均値: %.2f\n\n", average);
    
    /* C99の可変長配列を使った統計計算 */
    bool above_average[size];  /* C99の可変長配列 */
    int above_count = 0;
    
    for (int i = 0; i < size; i++) {
        above_average[i] = (arr[i] > average);
        if (above_average[i]) {
            above_count++;
        }
    }
    
    printf("詳細統計:\n");
    printf("  平均以上の要素数: %d個 (%.1f%%)\n", 
           above_count, (double)above_count / size * 100);
    printf("  平均未満の要素数: %d個 (%.1f%%)\n", 
           size - above_count, (double)(size - above_count) / size * 100);
    printf("\n");
    
    /* ポインタ解析情報 */
    printf("ポインタ解析:\n");
    printf("  配列の先頭アドレス: %p\n", (void*)arr);
    if (max_ptr && min_ptr) {
        printf("  最大値と先頭の差: %td要素\n", max_ptr - arr);
        printf("  最小値と先頭の差: %td要素\n", min_ptr - arr);
        printf("  最大値と最小値の差: %td要素\n", max_ptr - min_ptr);
    }
    
    printf("==============================================\n");
}

/*
 * C99の複合リテラルを使ったテスト関数
 */
void test_with_compound_literal(void) {
    printf("\nC99複合リテラルのテスト:\n");
    printf("------------------------\n");
    
    /* 複合リテラルで配列を直接渡す */
    int *max = find_max((int[]){10, 5, 8, 3, 9}, 5);
    int *min = find_min((int[]){10, 5, 8, 3, 9}, 5);
    double avg = calculate_average((int[]){10, 5, 8, 3, 9}, 5);
    
    printf("複合リテラル配列 {10, 5, 8, 3, 9} の結果:\n");
    printf("  最大値: %d\n", *max);
    printf("  最小値: %d\n", *min);
    printf("  平均値: %.2f\n", avg);
}

int main(void) {
    printf("配列操作関数のデモンストレーション (C99版)\n");
    printf("==========================================\n\n");
    
    /* C99の指示初期化子を使った配列初期化 */
    int numbers[] = {
        [0] = 45, [1] = 23, [2] = 67, [3] = 89, [4] = 12,
        [5] = 34, [6] = 56, [7] = 78, [8] = 90, [9] = 1
    };
    
    int size = sizeof(numbers) / sizeof(numbers[0]);
    
    /* 統計情報を表示 */
    print_statistics(numbers, size);
    
    /* 個別の関数呼び出しデモ */
    printf("\n個別関数の使用例:\n");
    printf("------------------\n");
    
    /* C99の混合宣言を使用 */
    int *max = find_max(numbers, size);
    printf("find_max()の結果: 値=%d, アドレス=%p\n", 
           *max, (void*)max);
    
    int *min = find_min(numbers, size);
    printf("find_min()の結果: 値=%d, アドレス=%p\n", 
           *min, (void*)min);
    
    double avg = calculate_average(numbers, size);
    printf("calculate_average()の結果: %.2f\n", avg);
    
    /* C99の複合リテラルテスト */
    test_with_compound_literal();
    
    /* 動的サイズでのテスト */
    printf("\n動的サイズ配列のテスト:\n");
    printf("----------------------\n");
    
    /* ユーザー定義サイズ（実際の実装では入力を受け取る） */
    int test_size = 7;
    int test_array[test_size];  /* C99の可変長配列 */
    
    /* 配列を初期化 */
    for (int i = 0; i < test_size; i++) {
        test_array[i] = (i + 1) * 11;  /* 11, 22, 33, ... */
    }
    
    printf("動的配列のサイズ: %d\n", test_size);
    print_statistics(test_array, test_size);
    
    printf("\nC99の新機能:\n");
    printf("------------\n");
    printf("1. 混合宣言: ループ変数をfor文内で宣言\n");
    printf("2. 可変長配列: 実行時にサイズが決まる配列\n");
    printf("3. 複合リテラル: (int[]){1,2,3}のような無名配列\n");
    printf("4. 指示初期化子: [index] = valueによる初期化\n");
    printf("5. restrict修飾子: ポインタのエイリアシング制限\n");
    printf("6. bool型とstdbool.h: 真偽値の標準化\n");
    printf("7. long long型: 64ビット整数のサポート\n");
    
    return 0;
}
