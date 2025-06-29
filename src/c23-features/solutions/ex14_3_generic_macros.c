/**
 * 演習14-3: typeof演算子の応用
 * 汎用マクロの実装
 * 
 * C23のtypeof演算子を使用して、型安全な汎用マクロを実装します。
 */

#include <stdio.h>

/* 配列の要素数を取得 */
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

/* 型安全な最大値マクロ */
#define ARRAY_MAX(arr, size) ({ \
    typeof(arr[0]) _max = arr[0]; \
    for (size_t _i = 1; _i < (size); _i++) { \
        if (arr[_i] > _max) { \
            _max = arr[_i]; \
        } \
    } \
    _max; \
})

/* 型安全な最小値マクロ */
#define ARRAY_MIN(arr, size) ({ \
    typeof(arr[0]) _min = arr[0]; \
    for (size_t _i = 1; _i < (size); _i++) { \
        if (arr[_i] < _min) { \
            _min = arr[_i]; \
        } \
    } \
    _min; \
})

/* 型安全な配列要素の合計マクロ */
#define ARRAY_SUM(arr, size) ({ \
    typeof(arr[0]) _sum = 0; \
    for (size_t _i = 0; _i < (size); _i++) { \
        _sum += arr[_i]; \
    } \
    _sum; \
})

/* 型安全な変数交換マクロ */
#define SWAP_SAFE(a, b) do { \
    typeof(a) _temp = (a); \
    (a) = (b); \
    (b) = _temp; \
} while(0)

/* 型安全な絶対値マクロ */
#define ABS_SAFE(x) ({ \
    typeof(x) _x = (x); \
    _x < 0 ? -_x : _x; \
})

/* 型安全なクランプ（範囲制限）マクロ */
#define CLAMP(value, min, max) ({ \
    typeof(value) _val = (value); \
    typeof(value) _min = (min); \
    typeof(value) _max = (max); \
    _val < _min ? _min : (_val > _max ? _max : _val); \
})

/* 配列の平均を計算（整数版と浮動小数点版を自動選択） */
#define ARRAY_AVG(arr, size) ({ \
    typeof(arr[0]) _sum = ARRAY_SUM(arr, size); \
    _sum / (typeof(arr[0]))(size); \
})

/* 配列要素を表示する汎用関数マクロ */
#define PRINT_ARRAY(arr, size, format) do { \
    printf("[ "); \
    for (size_t _i = 0; _i < (size); _i++) { \
        printf(format, arr[_i]); \
        if (_i < (size) - 1) printf(", "); \
    } \
    printf(" ]\n"); \
} while(0)

/* デモンストレーション関数 */
void demonstrate_int_arrays(void)
{
    printf("=== 整数配列での動作 ===\n");
    
    int numbers[] = {45, 12, 78, 23, 56, 89, 34, 67};
    size_t size = ARRAY_SIZE(numbers);
    
    printf("配列: ");
    PRINT_ARRAY(numbers, size, "%d");
    
    int max = ARRAY_MAX(numbers, size);
    int min = ARRAY_MIN(numbers, size);
    int sum = ARRAY_SUM(numbers, size);
    int avg = ARRAY_AVG(numbers, size);
    
    printf("最大値: %d\n", max);
    printf("最小値: %d\n", min);
    printf("合計:   %d\n", sum);
    printf("平均:   %d\n", avg);
    
    /* 変数の交換 */
    printf("\n変数の交換:\n");
    int a = 100, b = 200;
    printf("交換前: a = %d, b = %d\n", a, b);
    SWAP_SAFE(a, b);
    printf("交換後: a = %d, b = %d\n", a, b);
    
    /* 絶対値 */
    int negative = -42;
    printf("\n絶対値: ABS(%d) = %d\n", negative, ABS_SAFE(negative));
    
    /* クランプ */
    printf("\nクランプ（範囲制限）:\n");
    for (int val = -5; val <= 15; val += 5) {
        printf("CLAMP(%d, 0, 10) = %d\n", val, CLAMP(val, 0, 10));
    }
}

void demonstrate_double_arrays(void)
{
    printf("\n=== 浮動小数点配列での動作 ===\n");
    
    double values[] = {3.14, 2.71, 1.41, 1.73, 2.23, 0.57};
    size_t size = ARRAY_SIZE(values);
    
    printf("配列: ");
    PRINT_ARRAY(values, size, "%.2f");
    
    double max = ARRAY_MAX(values, size);
    double min = ARRAY_MIN(values, size);
    double sum = ARRAY_SUM(values, size);
    double avg = ARRAY_AVG(values, size);
    
    printf("最大値: %.2f\n", max);
    printf("最小値: %.2f\n", min);
    printf("合計:   %.2f\n", sum);
    printf("平均:   %.2f\n", avg);
    
    /* 変数の交換 */
    printf("\n変数の交換:\n");
    double x = 3.14, y = 2.71;
    printf("交換前: x = %.2f, y = %.2f\n", x, y);
    SWAP_SAFE(x, y);
    printf("交換後: x = %.2f, y = %.2f\n", x, y);
    
    /* 絶対値 */
    double neg_val = -3.14159;
    printf("\n絶対値: ABS(%.5f) = %.5f\n", neg_val, ABS_SAFE(neg_val));
}

/* 複雑な型での動作確認 */
struct Point {
    int x;
    int y;
};

void demonstrate_complex_types(void)
{
    printf("\n=== 複雑な型での動作 ===\n");
    
    /* ポインタの交換 */
    int val1 = 100, val2 = 200;
    int *ptr1 = &val1;
    int *ptr2 = &val2;
    
    printf("ポインタの交換:\n");
    printf("交換前: *ptr1 = %d, *ptr2 = %d\n", *ptr1, *ptr2);
    SWAP_SAFE(ptr1, ptr2);
    printf("交換後: *ptr1 = %d, *ptr2 = %d\n", *ptr1, *ptr2);
    
    /* 構造体の交換 */
    struct Point p1 = {10, 20};
    struct Point p2 = {30, 40};
    
    printf("\n構造体の交換:\n");
    printf("交換前: p1=(%d,%d), p2=(%d,%d)\n", p1.x, p1.y, p2.x, p2.y);
    SWAP_SAFE(p1, p2);
    printf("交換後: p1=(%d,%d), p2=(%d,%d)\n", p1.x, p1.y, p2.x, p2.y);
}

/* 実用的な例: ソート関数での活用 */
#define BUBBLE_SORT(arr, size) do { \
    for (size_t i = 0; i < (size) - 1; i++) { \
        for (size_t j = 0; j < (size) - i - 1; j++) { \
            if (arr[j] > arr[j + 1]) { \
                SWAP_SAFE(arr[j], arr[j + 1]); \
            } \
        } \
    } \
} while(0)

void demonstrate_sorting(void)
{
    printf("\n=== 型安全なソート ===\n");
    
    /* 整数配列のソート */
    int int_arr[] = {64, 34, 25, 12, 22, 11, 90};
    size_t int_size = ARRAY_SIZE(int_arr);
    
    printf("整数配列（ソート前）: ");
    PRINT_ARRAY(int_arr, int_size, "%d");
    
    BUBBLE_SORT(int_arr, int_size);
    
    printf("整数配列（ソート後）: ");
    PRINT_ARRAY(int_arr, int_size, "%d");
    
    /* 浮動小数点配列のソート */
    double double_arr[] = {64.5, 34.2, 25.8, 12.1, 22.7};
    size_t double_size = ARRAY_SIZE(double_arr);
    
    printf("\n浮動小数点配列（ソート前）: ");
    PRINT_ARRAY(double_arr, double_size, "%.1f");
    
    BUBBLE_SORT(double_arr, double_size);
    
    printf("浮動小数点配列（ソート後）: ");
    PRINT_ARRAY(double_arr, double_size, "%.1f");
}

int main(void)
{
    printf("=== typeof演算子を使った汎用マクロ ===\n\n");
    
    /* 整数配列でのデモ */
    demonstrate_int_arrays();
    
    /* 浮動小数点配列でのデモ */
    demonstrate_double_arrays();
    
    /* 複雑な型でのデモ */
    demonstrate_complex_types();
    
    /* ソートのデモ */
    demonstrate_sorting();
    
    return 0;
}
