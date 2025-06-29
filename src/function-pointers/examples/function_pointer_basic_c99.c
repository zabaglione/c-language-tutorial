/* 関数ポインタの基本（C99版） */
#include <stdio.h>
#include <stdbool.h>

/* 数学演算関数群 */
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

int divide(int a, int b)
{
    if (b != 0)
    {
        return a / b;
    }
    printf("エラー: ゼロ除算\n");
    return 0;
}

/* 関数ポインタを使った計算 */
int calculate(int x, int y, int (*operation)(int, int))
{
    return operation(x, y);
}

/* 演算子に基づいて関数を選択 */
int (*get_operation(char op))(int, int)
{
    switch (op)
    {
    case '+':
        return add;
    case '-':
        return subtract;
    case '*':
        return multiply;
    case '/':
        return divide;
    default:
        return NULL;
    }
}

int main(void)
{
    printf("=== 関数ポインタの基本（C99版） ===\n\n");

    // 基本的な関数ポインタの使用
    int a = 10, b = 5;
    printf("数値: a = %d, b = %d\n\n", a, b);

    // 関数ポインタの宣言と使用（使用箇所で宣言）
    int (*math_func)(int, int) = add;
    printf("加算: %d + %d = %d\n", a, b, math_func(a, b));

    // 減算
    math_func = subtract;
    printf("減算: %d - %d = %d\n", a, b, math_func(a, b));

    // 乗算
    math_func = multiply;
    printf("乗算: %d * %d = %d\n", a, b, math_func(a, b));

    // 除算
    math_func = divide;
    printf("除算: %d / %d = %d\n", a, b, math_func(a, b));

    printf("\n=== 関数選択システム ===\n");

    // 演算子による関数選択
    char operators[] = {'+', '-', '*', '/', '%'};
    const char *op_names[] = {"加算", "減算", "乗算", "除算", "不明"};

    for (int i = 0; i < 5; i++)
    {
        int (*op_func)(int, int) = get_operation(operators[i]);
        if (op_func != NULL)
        {
            int result = calculate(a, b, op_func);
            printf("%s (%c): %d\n", op_names[i], operators[i], result);
        }
        else
        {
            printf("%s (%c): サポートされていません\n", op_names[i], operators[i]);
        }
    }

    printf("\n=== 動的な演算実行 ===\n");

    // 対話的な演算実行
    printf("演算子を入力してください (+, -, *, /): ");
    char op;
    if (scanf(" %c", &op) == 1)
    {
        int (*selected_op)(int, int) = get_operation(op);
        if (selected_op != NULL)
        {
            int result = calculate(15, 3, selected_op);
            printf("15 %c 3 = %d\n", op, result);
        }
        else
        {
            printf("無効な演算子です\n");
        }
    }

    // C99の機能を活用した例
    printf("\n=== C99機能の活用例 ===\n");
    
    // 複合リテラルと関数ポインタ
    struct operation_info {
        char op;
        const char *name;
        int (*func)(int, int);
    } operations[] = {
        {'+', "加算", add},
        {'-', "減算", subtract},
        {'*', "乗算", multiply},
        {'/', "除算", divide}
    };
    
    int num_ops = sizeof(operations) / sizeof(operations[0]);
    
    // テスト値で全演算を実行
    int test_a = 20, test_b = 4;
    printf("テスト値: a = %d, b = %d\n", test_a, test_b);
    
    for (int i = 0; i < num_ops; i++)
    {
        int result = operations[i].func(test_a, test_b);
        printf("%s: %d %c %d = %d\n", 
               operations[i].name, 
               test_a, 
               operations[i].op, 
               test_b, 
               result);
    }
    
    // 関数ポインタの比較
    printf("\n=== 関数ポインタの比較 ===\n");
    bool same_func = (add == add);
    bool diff_func = (add == subtract);
    
    printf("add == add: %s\n", same_func ? "true" : "false");
    printf("add == subtract: %s\n", diff_func ? "true" : "false");

    return 0;
}

/*
C99の特徴:
1. 変数宣言を使用箇所で可能
2. for文内での変数宣言
3. bool型の使用（stdbool.h）
4. // 形式のコメント
5. 複合リテラルの使用
6. より柔軟な構造体の初期化

学習ポイント:
1. 関数ポインタの基本的な宣言と使用
2. 関数ポインタを返す関数の作成
3. 関数ポインタを引数に取る関数
4. 関数ポインタの比較
5. 構造体と関数ポインタの組み合わせ
*/