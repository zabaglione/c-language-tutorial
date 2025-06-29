/*
 * ファイル名: ex9_7_recursive_functions.c
 * 演習9-7: 再帰関数
 * 説明: 階乗、フィボナッチ、ユークリッドの互除法などの再帰関数の実装
 * 規格: C90準拠
 */
#include <stdio.h>

/* 関数プロトタイプ */
long factorial_recursive(int n);
int fibonacci_recursive(int n);
int gcd_recursive(int a, int b);
int is_palindrome_recursive(const char str[], int start, int end);
void reverse_string_recursive(char str[], int start, int end);
int array_sum_recursive(int arr[], int size);
int find_max_recursive(int arr[], int size);

/* 階乗を計算する再帰関数 */
long factorial_recursive(int n)
{
    /* ベースケース */
    if (n <= 1)
    {
        return 1;
    }
    
    /* 再帰ケース */
    return n * factorial_recursive(n - 1);
}

/* フィボナッチ数列を計算する再帰関数 */
int fibonacci_recursive(int n)
{
    /* ベースケース */
    if (n <= 0)
    {
        return 0;
    }
    if (n == 1)
    {
        return 1;
    }
    
    /* 再帰ケース */
    return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2);
}

/* ユークリッドの互除法による最大公約数を求める再帰関数 */
int gcd_recursive(int a, int b)
{
    /* ベースケース */
    if (b == 0)
    {
        return a;
    }
    
    /* 再帰ケース */
    return gcd_recursive(b, a % b);
}

/* 文字列が回文かどうか再帰的に判定する関数 */
int is_palindrome_recursive(const char str[], int start, int end)
{
    /* ベースケース: 文字が交差したか同じ位置になった場合 */
    if (start >= end)
    {
        return 1; /* 回文 */
    }
    
    /* 現在の位置の文字が異なる場合 */
    if (str[start] != str[end])
    {
        return 0; /* 回文ではない */
    }
    
    /* 再帰ケース: 内側の文字列をチェック */
    return is_palindrome_recursive(str, start + 1, end - 1);
}

/* 文字列を再帰的に逆順にする関数 */
void reverse_string_recursive(char str[], int start, int end)
{
    char temp;
    
    /* ベースケース */
    if (start >= end)
    {
        return;
    }
    
    /* 文字を交換 */
    temp = str[start];
    str[start] = str[end];
    str[end] = temp;
    
    /* 再帰ケース */
    reverse_string_recursive(str, start + 1, end - 1);
}

/* 配列の合計を再帰的に計算する関数 */
int array_sum_recursive(int arr[], int size)
{
    /* ベースケース */
    if (size <= 0)
    {
        return 0;
    }
    
    /* 再帰ケース */
    return arr[size - 1] + array_sum_recursive(arr, size - 1);
}

/* 配列の最大値を再帰的に見つける関数 */
int find_max_recursive(int arr[], int size)
{
    int max_of_rest;
    
    /* ベースケース */
    if (size == 1)
    {
        return arr[0];
    }
    
    /* 再帰ケース */
    max_of_rest = find_max_recursive(arr, size - 1);
    
    /* 現在の要素と残りの最大値を比較 */
    return (arr[size - 1] > max_of_rest) ? arr[size - 1] : max_of_rest;
}

/* 文字列の長さを求める補助関数 */
int my_strlen(const char str[])
{
    int len = 0;
    while (str[len] != '\0')
    {
        len++;
    }
    return len;
}

int main(void)
{
    /* C90: すべての変数を関数先頭で宣言 */
    int factorial_tests[] = {0, 1, 5, 10, 12};
    int num_factorial_tests = sizeof(factorial_tests) / sizeof(factorial_tests[0]);
    int gcd_pairs[][2] = {{48, 18}, {60, 48}, {17, 13}, {100, 75}};
    int num_gcd_pairs = sizeof(gcd_pairs) / sizeof(gcd_pairs[0]);
    char* palindrome_tests[] = {"racecar", "hello", "madam", "abcba", "test"};
    int num_palindrome_tests = sizeof(palindrome_tests) / sizeof(palindrome_tests[0]);
    char test_strings[][20] = {"hello", "world", "recursive", "function"};
    int num_strings = sizeof(test_strings) / sizeof(test_strings[0]);
    int test_array1[] = {1, 2, 3, 4, 5};
    int test_array2[] = {10, 20, 30, 40};
    int test_array3[] = {7, 14, 21, 28, 35, 42};
    int i;
    
    printf("=== 再帰関数のデモ ===\n\n");

    /* デモ1: 階乗計算 */
    printf("1. 階乗計算\n");
    
    for (i = 0; i < num_factorial_tests; i++)
    {
        int n = factorial_tests[i];
        printf("   %d! = %ld\n", n, factorial_recursive(n));
    }
    printf("\n");

    /* デモ2: フィボナッチ数列 */
    printf("2. フィボナッチ数列\n");
    printf("   最初の15項: ");
    for (i = 0; i < 15; i++)
    {
        printf("%d ", fibonacci_recursive(i));
    }
    printf("\n\n");

    /* デモ3: 最大公約数 */
    printf("3. 最大公約数（ユークリッドの互除法）\n");
    
    for (i = 0; i < num_gcd_pairs; i++)
    {
        int a = gcd_pairs[i][0];
        int b = gcd_pairs[i][1];
        printf("   gcd(%d, %d) = %d\n", a, b, gcd_recursive(a, b));
    }
    printf("\n");

    /* デモ4: 回文判定 */
    printf("4. 回文判定\n");
    
    for (i = 0; i < num_palindrome_tests; i++)
    {
        char* str = palindrome_tests[i];
        int len = my_strlen(str);
        int is_pal = is_palindrome_recursive(str, 0, len - 1);
        printf("   \"%s\" -> %s\n", str, is_pal ? "回文です" : "回文ではありません");
    }
    printf("\n");

    /* デモ5: 文字列の逆順 */
    printf("5. 文字列の逆順\n");
    
    for (i = 0; i < num_strings; i++)
    {
        char original[20];
        int j;
        int len;
        
        /* 元の文字列をコピー */
        for (j = 0; test_strings[i][j] != '\0'; j++)
        {
            original[j] = test_strings[i][j];
        }
        original[j] = '\0';
        
        len = my_strlen(test_strings[i]);
        reverse_string_recursive(test_strings[i], 0, len - 1);
        printf("   \"%s\" -> \"%s\"\n", original, test_strings[i]);
    }
    printf("\n");

    /* デモ6: 配列の合計 */
    printf("6. 配列の合計（再帰）\n");
    
    printf("   配列 {1, 2, 3, 4, 5} の合計: %d\n", 
           array_sum_recursive(test_array1, 5));
    printf("   配列 {10, 20, 30, 40} の合計: %d\n", 
           array_sum_recursive(test_array2, 4));
    printf("   配列 {7, 14, 21, 28, 35, 42} の合計: %d\n", 
           array_sum_recursive(test_array3, 6));
    printf("\n");

    /* デモ7: 配列の最大値 */
    printf("7. 配列の最大値（再帰）\n");
    printf("   配列 {1, 2, 3, 4, 5} の最大値: %d\n", 
           find_max_recursive(test_array1, 5));
    printf("   配列 {10, 20, 30, 40} の最大値: %d\n", 
           find_max_recursive(test_array2, 4));
    printf("   配列 {7, 14, 21, 28, 35, 42} の最大値: %d\n", 
           find_max_recursive(test_array3, 6));
    printf("\n");

    printf("=== 再帰関数デモ完了 ===\n");
    return 0;
}

/*
学習ポイント:
1. 再帰関数の基本構造（ベースケースと再帰ケース）
2. 数学的計算での再帰の応用
3. 文字列処理での再帰の活用
4. 配列処理での再帰的アプローチ
5. 再帰の効率性と限界の理解

実装のポイント:
- C90準拠のため、変数は関数先頭で宣言
- ベースケースの重要性
- スタックオーバーフローの注意
- 再帰よりも反復が効率的な場合の判断
*/
