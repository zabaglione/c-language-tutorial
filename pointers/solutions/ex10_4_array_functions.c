/*
 * 演習10-4: 配列操作関数
 * 
 * 配列を操作する関数をポインタを使って実装する演習です。
 * - 最大値・最小値を見つけてポインタを返す
 * - 平均値を計算する
 * - 統計情報をレポート形式で表示する
 * 
 * 作成者: C言語学習者
 * 作成日: 2024年
 */

#include <stdio.h>

/* 関数プロトタイプ宣言 */
int* find_max(int *arr, int size);
int* find_min(int *arr, int size);
double calculate_average(int *arr, int size);
void print_statistics(int *arr, int size);

/*
 * 配列の最大値を見つけてそのポインタを返す
 * 引数: arr - 配列の先頭ポインタ, size - 配列のサイズ
 * 戻り値: 最大値へのポインタ
 */
int* find_max(int *arr, int size) {
    int *max_ptr = arr;  /* 最初は先頭要素を最大値と仮定 */
    int i;
    
    /* 配列の全要素を走査 */
    for (i = 1; i < size; i++) {
        /*
         * ポインタ演算を使った要素アクセス
         * arr + i は i番目の要素のアドレス
         * *(arr + i) でその値を取得
         */
        if (*(arr + i) > *max_ptr) {
            max_ptr = arr + i;  /* 新しい最大値のアドレスを記録 */
        }
    }
    
    return max_ptr;  /* 最大値のアドレスを返す */
}

/*
 * 配列の最小値を見つけてそのポインタを返す
 * 引数: arr - 配列の先頭ポインタ, size - 配列のサイズ
 * 戻り値: 最小値へのポインタ
 */
int* find_min(int *arr, int size) {
    int *min_ptr = arr;  /* 最初は先頭要素を最小値と仮定 */
    int i;
    
    /* 配列の全要素を走査 */
    for (i = 1; i < size; i++) {
        /* ポインタを使った比較 */
        if (*(arr + i) < *min_ptr) {
            min_ptr = arr + i;  /* 新しい最小値のアドレスを記録 */
        }
    }
    
    return min_ptr;  /* 最小値のアドレスを返す */
}

/*
 * 配列の平均値を計算する
 * 引数: arr - 配列の先頭ポインタ, size - 配列のサイズ
 * 戻り値: 平均値（double型）
 */
double calculate_average(int *arr, int size) {
    int sum = 0;
    int i;
    
    /* ポインタを使った要素の合計計算 */
    for (i = 0; i < size; i++) {
        sum += *(arr + i);  /* ポインタ演算で各要素にアクセス */
    }
    
    /* 平均値を計算して返す（double型にキャスト） */
    return (double)sum / size;
}

/*
 * 配列の統計情報を表示する
 * 最大値、最小値、平均値とそれらのポインタ情報を含む
 */
void print_statistics(int *arr, int size) {
    int *max_ptr, *min_ptr;
    double average;
    int i;
    
    printf("========== 配列統計レポート ==========\n");
    printf("配列のサイズ: %d要素\n\n", size);
    
    /* 配列の内容を表示 */
    printf("配列の内容:\n");
    for (i = 0; i < size; i++) {
        printf("  arr[%d] = %d (アドレス: %p)\n", 
               i, *(arr + i), (void*)(arr + i));
    }
    printf("\n");
    
    /* 最大値の情報 */
    max_ptr = find_max(arr, size);
    printf("最大値:\n");
    printf("  値: %d\n", *max_ptr);
    printf("  アドレス: %p\n", (void*)max_ptr);
    printf("  インデックス: %ld\n", (long)(max_ptr - arr));
    printf("\n");
    
    /* 最小値の情報 */
    min_ptr = find_min(arr, size);
    printf("最小値:\n");
    printf("  値: %d\n", *min_ptr);
    printf("  アドレス: %p\n", (void*)min_ptr);
    printf("  インデックス: %ld\n", (long)(min_ptr - arr));
    printf("\n");
    
    /* 平均値の情報 */
    average = calculate_average(arr, size);
    printf("平均値: %.2f\n\n", average);
    
    /* ポインタ解析情報 */
    printf("ポインタ解析:\n");
    printf("  配列の先頭アドレス: %p\n", (void*)arr);
    printf("  最大値と先頭の差: %ld要素\n", (long)(max_ptr - arr));
    printf("  最小値と先頭の差: %ld要素\n", (long)(min_ptr - arr));
    printf("  最大値と最小値の差: %ld要素\n", (long)(max_ptr - min_ptr));
    
    printf("======================================\n");
}

int main(void) {
    /* デモ用配列データ */
    int numbers[] = {45, 23, 67, 89, 12, 34, 56, 78, 90, 1};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    
    printf("配列操作関数のデモンストレーション\n");
    printf("=====================================\n\n");
    
    /* 統計情報を表示 */
    print_statistics(numbers, size);
    
    /* 個別の関数呼び出しデモ */
    printf("\n個別関数の使用例:\n");
    printf("------------------\n");
    
    /* find_max関数の使用例 */
    {
        int *max = find_max(numbers, size);
        printf("find_max()の結果: 値=%d, アドレス=%p\n", 
               *max, (void*)max);
    }
    
    /* find_min関数の使用例 */
    {
        int *min = find_min(numbers, size);
        printf("find_min()の結果: 値=%d, アドレス=%p\n", 
               *min, (void*)min);
    }
    
    /* calculate_average関数の使用例 */
    {
        double avg = calculate_average(numbers, size);
        printf("calculate_average()の結果: %.2f\n", avg);
    }
    
    printf("\n");
    
    /* ポインタ概念の説明 */
    printf("ポインタの重要な概念:\n");
    printf("--------------------\n");
    printf("1. 配列名は配列の先頭要素へのポインタとして扱われる\n");
    printf("2. 関数に配列を渡すと、実際にはポインタが渡される\n");
    printf("3. ポインタ演算により配列要素にアクセスできる\n");
    printf("4. 関数からポインタを返すことで、配列内の特定要素を指示できる\n");
    
    return 0;
}
