/*
 * ファイル名: ex12_2_function_selector.c
 * 演習12-2: 関数選択システム
 * 説明: 文字に基づいて関数を選択し実行するデモプログラム
 * 規格: C90準拠
 */
#include <stdio.h>

/* 演算関数群 */
int add(int a, int b)
{
    return a + b;
}

int subtract(int a, int b)
{
    return a - b;
}

int multiply(int a, int b)
{
    return a * b;
}

int divide_safe(int a, int b)
{
    if (b == 0) {
        printf("エラー: ゼロ除算を検出\n");
        return 0;
    }
    return a / b;
}

/* 関数ポインタと対応する文字を管理する構造体 */
typedef struct {
    char op_char;
    int (*func)(int, int);
    char *name;
} OperationMapping;

int main(void)
{
    /* 変数の宣言（C90では先頭で宣言） */
    OperationMapping operations[] = {
        {'+', add, "加算"},
        {'-', subtract, "減算"}, 
        {'*', multiply, "乗算"},
        {'/', divide_safe, "除算"}
    };
    int num_operations = sizeof(operations) / sizeof(operations[0]);
    int a, b, result;
    int i, j;
    char demo_ops[] = {'+', '-', '*', '/', 'X'}; /* X は無効な演算子 */
    int num_demos = sizeof(demo_ops) / sizeof(demo_ops[0]);
    
    printf("=== 関数選択システムデモ ===\n");
    
    /* デモ用の値 */
    a = 12;
    b = 4;
    
    printf("対象の値: a = %d, b = %d\n\n", a, b);
    
    /* 各演算子のデモ */
    for (i = 0; i < num_demos; i++) {
        char op = demo_ops[i];
        int found = 0;
        
        printf("演算子 '%c' を選択:\n", op);
        
        /* 対応する関数を検索 */
        for (j = 0; j < num_operations; j++) {
            if (operations[j].op_char == op) {
                result = operations[j].func(a, b);
                printf("  %s: %d %c %d = %d\n", 
                       operations[j].name, a, op, b, result);
                found = 1;
                break;
            }
        }
        
        if (!found) {
            printf("  エラー: 無効な演算子です\n");
        }
        printf("\n");
    }
    
    /* 関数ポインタ配列を使った方法 */
    printf("=== 関数ポインタ配列を使った実装 ===\n");
    {
        int (*operation_funcs[])(int, int) = {add, subtract, multiply, divide_safe};
        char operators[] = {'+', '-', '*', '/'};
        char *names[] = {"加算", "減算", "乗算", "除算"};
        
        for (i = 0; i < 4; i++) {
            result = operation_funcs[i](a, b);
            printf("%s (%c): %d %c %d = %d\n", 
                   names[i], operators[i], a, operators[i], b, result);
        }
    }
    
    /* 異なる値での演算例 */
    printf("\n=== 異なる値での演算例 ===\n");
    {
        int test_values[][2] = {{20, 5}, {7, 3}, {15, 0}};
        int num_tests = sizeof(test_values) / sizeof(test_values[0]);
        
        for (i = 0; i < num_tests; i++) {
            int x = test_values[i][0];
            int y = test_values[i][1];
            
            printf("値: %d, %d\n", x, y);
            printf("  加算: %d, 減算: %d, 乗算: %d, 除算: %d\n",
                   add(x, y), subtract(x, y), multiply(x, y), divide_safe(x, y));
        }
    }
    
    return 0;
}

/*
学習ポイント:
1. 文字による関数選択システム
2. 構造体を使った関数ポインタ管理
3. エラーハンドリングの実装
4. 動的な関数呼び出し

実装のポイント:
- C90準拠のため、すべての変数を関数先頭で宣言
- 構造体配列による関数ポインタの管理
- ループによる関数検索と実行
- デモ版として固定値を使用（実際は入力を受け取る）
- 無効な演算子のエラーハンドリング
*/
