/*
 * ファイル名: typeof_demo.c
 * 説明: C23のtypeof演算子の使用例
 * 規格: C23
 */

#include <stdio.h>
#include <string.h>

/* マクロでtypeofを活用 */
#define SWAP(a, b) do { \
    typeof(a) temp = (a); \
    (a) = (b); \
    (b) = temp; \
} while(0)

/* 型安全な最大値マクロ */
#define MAX(a, b) ({ \
    typeof(a) _a = (a); \
    typeof(b) _b = (b); \
    _a > _b ? _a : _b; \
})

/* 配列要素数の計算（型チェック付き） */
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(typeof(arr[0])))

int main(void)
{
    printf("=== C23 typeof演算子 ===\n");
    
    /* 基本的な使用法 */
    printf("\n--- 基本的な使用法 ---\n");
    
    int x = 42;
    typeof(x) y = 100;  /* yはint型 */
    
    printf("x = %d, y = %d\n", x, y);
    printf("yの型はxと同じ（int型）\n");
    
    /* 複雑な型での使用 */
    printf("\n--- 複雑な型での使用 ---\n");
    
    double array[5] = {1.1, 2.2, 3.3, 4.4, 5.5};
    typeof(array[0]) sum = 0.0;  /* sumはdouble型 */
    
    for (int i = 0; i < 5; i++) {
        sum += array[i];
    }
    printf("配列の合計: %.1f\n", sum);
    
    /* ポインタ型での使用 */
    printf("\n--- ポインタ型での使用 ---\n");
    
    char *str = "Hello";
    typeof(str) copy = "World";  /* copyはchar*型 */
    
    printf("str = %s, copy = %s\n", str, copy);
    
    /* SWAPマクロの使用 */
    printf("\n--- 型安全なSWAPマクロ ---\n");
    
    int a = 10, b = 20;
    printf("交換前: a = %d, b = %d\n", a, b);
    SWAP(a, b);
    printf("交換後: a = %d, b = %d\n", a, b);
    
    double d1 = 3.14, d2 = 2.71;
    printf("\n交換前: d1 = %.2f, d2 = %.2f\n", d1, d2);
    SWAP(d1, d2);
    printf("交換後: d1 = %.2f, d2 = %.2f\n", d1, d2);
    
    /* MAXマクロの使用 */
    printf("\n--- 型安全な最大値マクロ ---\n");
    
    int max_int = MAX(15, 25);
    double max_double = MAX(3.14, 2.71);
    
    printf("MAX(15, 25) = %d\n", max_int);
    printf("MAX(3.14, 2.71) = %.2f\n", max_double);
    
    /* 配列サイズの計算 */
    printf("\n--- 配列サイズの計算 ---\n");
    
    int int_array[] = {1, 2, 3, 4, 5};
    char char_array[] = "Hello";
    struct { int x; int y; } point_array[3];
    
    printf("int配列の要素数: %zu\n", ARRAY_SIZE(int_array));
    printf("char配列の要素数: %zu\n", ARRAY_SIZE(char_array));
    printf("構造体配列の要素数: %zu\n", ARRAY_SIZE(point_array));
    
    /* 関数ポインタでの使用 */
    printf("\n--- 関数ポインタでの使用 ---\n");
    
    int (*func_ptr)(const char *, ...) = printf;
    typeof(func_ptr) another_func = func_ptr;
    
    another_func("typeof で関数ポインタも複製可能\n");
    
    /* C11の_Genericとの比較 */
    printf("\n--- C11の_Genericとの比較 ---\n");
    printf("typeof: 式の型を取得（C23）\n");
    printf("_Generic: 型に基づく選択（C11）\n");
    
    return 0;
}


/*
 * 実行結果例:
 * === C23 typeof演算子 ===
 * 
 * --- 基本的な使用法 ---
 * x = 42, y = 100
 * yの型はxと同じ（int型）
 * 
 * --- 複雑な型での使用 ---
 * 配列の合計: 16.5
 * 
 * --- ポインタ型での使用 ---
 * str = Hello, copy = World
 * 
 * --- 型安全なSWAPマクロ ---
 * 交換前: a = 10, b = 20
 * 交換後: a = 20, b = 10
 * 
 * 交換前: d1 = 3.14, d2 = 2.71
 * 交換後: d1 = 2.71, d2 = 3.14
 * 
 * --- 型安全な最大値マクロ ---
 * MAX(15, 25) = 25
 * MAX(3.14, 2.71) = 3.14
 * 
 * --- 配列サイズの計算 ---
 * int配列の要素数: 5
 * char配列の要素数: 6
 * 構造体配列の要素数: 3
 * 
 * --- 関数ポインタでの使用 ---
 * typeof で関数ポインタも複製可能
 * 
 * --- C11の_Genericとの比較 ---
 * typeof: 式の型を取得（C23）
 * _Generic: 型に基づく選択（C11）
 */