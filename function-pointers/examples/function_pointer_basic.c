/* 関数ポインタの基本 */
#include <stdio.h>

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
    printf("=== 関数ポインタの基本 ===\n\n");

    /* 基本的な関数ポインタの使用 */
    int (*math_func)(int, int);
    int a = 10, b = 5;

    printf("数値: a = %d, b = %d\n\n", a, b);

    /* 加算 */
    math_func = add;
    printf("加算: %d + %d = %d\n", a, b, math_func(a, b));

    /* 減算 */
    math_func = subtract;
    printf("減算: %d - %d = %d\n", a, b, math_func(a, b));

    /* 乗算 */
    math_func = multiply;
    printf("乗算: %d * %d = %d\n", a, b, math_func(a, b));

    /* 除算 */
    math_func = divide;
    printf("除算: %d / %d = %d\n", a, b, math_func(a, b));

    printf("\n=== 関数選択システム ===\n");

    /* 演算子による関数選択 */
    char operators[] = {'+', '-', '*', '/', '%'};
    const char *op_names[] = {"加算", "減算", "乗算", "除算", "不明"};
    int i;

    for (i = 0; i < 5; i++)
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

    /* 対話的な演算実行 */
    char op;
    printf("演算子を入力してください (+, -, *, /): ");
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

    return 0;
}
