/*
 * ファイル名: ex11_7_recursive_functions_c99.c
 * 演習11-7: 再帰関数
 * 説明: 階乗、フィボナッチ、ユークリッドの互除法などの再帰関数の実装（C99版）
 * 規格: C99準拠
 */
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// 関数プロトタイプ
long factorial_recursive(int n);
int fibonacci_recursive(int n);
int gcd_recursive(int a, int b);
bool is_palindrome_recursive(const char str[], int start, int end);
void reverse_string_recursive(char str[], int start, int end);
int array_sum_recursive(int arr[], int size);
int find_max_recursive(int arr[], int size);

// 階乗を計算する再帰関数
long factorial_recursive(int n)
{
    // ベースケース
    if (n <= 1) {
        return 1;
    }
    
    // 再帰ケース
    return n * factorial_recursive(n - 1);
}

// フィボナッチ数列を計算する再帰関数
int fibonacci_recursive(int n)
{
    // ベースケース
    if (n <= 0) return 0;
    if (n == 1) return 1;
    
    // 再帰ケース
    return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2);
}

// ユークリッドの互除法による最大公約数を求める再帰関数
int gcd_recursive(int a, int b)
{
    // ベースケース
    if (b == 0) return a;
    
    // 再帰ケース
    return gcd_recursive(b, a % b);
}

// 文字列が回文かどうか再帰的に判定する関数（C99: bool型使用）
bool is_palindrome_recursive(const char str[], int start, int end)
{
    // ベースケース: 文字が交差したか同じ位置になった場合
    if (start >= end) {
        return true; // 回文
    }
    
    // 現在の位置の文字が異なる場合
    if (str[start] != str[end]) {
        return false; // 回文ではない
    }
    
    // 再帰ケース: 内側の文字列をチェック
    return is_palindrome_recursive(str, start + 1, end - 1);
}

// 文字列を再帰的に逆順にする関数
void reverse_string_recursive(char str[], int start, int end)
{
    // ベースケース
    if (start >= end) return;
    
    // 文字を交換（C99: 使用箇所で変数宣言）
    char temp = str[start];
    str[start] = str[end];
    str[end] = temp;
    
    // 再帰ケース
    reverse_string_recursive(str, start + 1, end - 1);
}

// 配列の合計を再帰的に計算する関数
int array_sum_recursive(int arr[], int size)
{
    // ベースケース
    if (size <= 0) return 0;
    
    // 再帰ケース
    return arr[size - 1] + array_sum_recursive(arr, size - 1);
}

// 配列の最大値を再帰的に見つける関数
int find_max_recursive(int arr[], int size)
{
    // ベースケース
    if (size == 1) return arr[0];
    
    // 再帰ケース
    int max_of_rest = find_max_recursive(arr, size - 1);
    return (arr[size - 1] > max_of_rest) ? arr[size - 1] : max_of_rest;
}

int main(void)
{
    printf("=== 再帰関数のデモ（C99版）===\n\n");

    // デモ1: 階乗計算（C99: 配列初期化）
    printf("1. 階乗計算\n");
    int factorial_tests[] = {0, 1, 5, 10, 12, 15};
    
    for (int i = 0; i < (int)(sizeof(factorial_tests)/sizeof(factorial_tests[0])); i++) {
        int n = factorial_tests[i];
        printf("   %d! = %ld\n", n, factorial_recursive(n));
    }
    printf("\n");

    // デモ2: フィボナッチ数列（C99: for文内変数宣言）
    printf("2. フィボナッチ数列\n");
    printf("   最初の20項: ");
    for (int i = 0; i < 20; i++) {
        printf("%d ", fibonacci_recursive(i));
        if ((i + 1) % 10 == 0) printf("\n                   ");
    }
    printf("\n\n");

    // デモ3: 最大公約数（C99: 構造体と指定初期化子）
    printf("3. 最大公約数（ユークリッドの互除法）\n");
    struct { int a, b; } gcd_pairs[] = {
        {.a = 48, .b = 18},
        {.a = 60, .b = 48},
        {.a = 17, .b = 13},
        {.a = 100, .b = 75},
        {.a = 144, .b = 60}
    };
    
    for (int i = 0; i < 5; i++) {
        printf("   gcd(%d, %d) = %d\n", 
               gcd_pairs[i].a, gcd_pairs[i].b, 
               gcd_recursive(gcd_pairs[i].a, gcd_pairs[i].b));
    }
    printf("\n");

    // デモ4: 回文判定（C99: bool型使用）
    printf("4. 回文判定\n");
    const char* palindrome_tests[] = {
        "racecar", "hello", "madam", "abcba", "test", "level", "noon"
    };
    
    for (int i = 0; i < 7; i++) {
        const char* str = palindrome_tests[i];
        int len = strlen(str);
        bool is_pal = is_palindrome_recursive(str, 0, len - 1);
        printf("   \"%s\" -> %s\n", str, is_pal ? "回文です" : "回文ではありません");
    }
    printf("\n");

    // デモ5: 文字列の逆順（C99: 可変長配列）
    printf("5. 文字列の逆順\n");
    const char* test_strings[] = {"hello", "world", "recursive", "function", "algorithm"};
    
    for (int i = 0; i < 5; i++) {
        // C99: 可変長配列
        int len = strlen(test_strings[i]);
        char original[len + 1];
        char copy[len + 1];
        
        strcpy(original, test_strings[i]);
        strcpy(copy, test_strings[i]);
        
        reverse_string_recursive(copy, 0, len - 1);
        printf("   \"%s\" -> \"%s\"\n", original, copy);
    }
    printf("\n");

    // デモ6: 配列の合計（C99: 複合リテラル）
    printf("6. 配列の合計（再帰）\n");
    printf("   配列 {1, 2, 3, 4, 5} の合計: %d\n", 
           array_sum_recursive((int[]){1, 2, 3, 4, 5}, 5));
    printf("   配列 {10, 20, 30, 40} の合計: %d\n", 
           array_sum_recursive((int[]){10, 20, 30, 40}, 4));
    printf("   配列 {7, 14, 21, 28, 35, 42} の合計: %d\n", 
           array_sum_recursive((int[]){7, 14, 21, 28, 35, 42}, 6));
    printf("\n");

    // デモ7: 配列の最大値（C99: inline関数風の使用）
    printf("7. 配列の最大値（再帰）\n");
    int test_arrays[][6] = {
        {1, 2, 3, 4, 5, 0},
        {10, 20, 30, 40, 0, 0},
        {7, 14, 21, 28, 35, 42}
    };
    int sizes[] = {5, 4, 6};
    
    for (int i = 0; i < 3; i++) {
        printf("   配列 %d の最大値: %d\n", i + 1, 
               find_max_recursive(test_arrays[i], sizes[i]));
    }
    printf("\n");

    // C99追加デモ: 複雑な再帰例
    printf("=== C99機能を活用した高度な例 ===\n");
    
    // 複数の数値の最大公約数
    printf("複数の数値のGCD: ");
    int numbers[] = {48, 18, 24, 36};
    int result_gcd = numbers[0];
    for (int i = 1; i < 4; i++) {
        result_gcd = gcd_recursive(result_gcd, numbers[i]);
    }
    printf("gcd(48, 18, 24, 36) = %d\n", result_gcd);
    
    printf("\n=== C99再帰関数デモ完了 ===\n");
    return 0;
}

/*
学習ポイント（C99追加機能）:
1. bool型を使ったより明確な戻り値
2. for文内での変数宣言
3. 可変長配列の活用
4. 複合リテラルによる一時的な配列作成
5. 指定初期化子を使った構造体初期化

実装のポイント:
- C99準拠のため、変数を使用箇所で宣言
- bool型によるより読みやすいコード
- 複合リテラルで配列を簡潔に定義
- C99の機能を活用した効率的なコード記述
*/