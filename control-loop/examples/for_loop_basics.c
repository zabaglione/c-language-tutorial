/*
 * for文の基本的な使い方
 *
 * このプログラムは、for文を使った様々な
 * ループパターンを示します。
 */
#include <stdio.h>

int main(void)
{
    int i, j;
    int sum;
    char ch;
    int n;
    int factorial;

    /* 1. 基本的なfor文：1から10まで出力 */
    printf("1から10まで: ");
    for (i = 1; i <= 10; i++)
    {
        printf("%d ", i);
    }
    printf("\n\n");

    /* 2. 逆順ループ：10から1まで出力 */
    printf("10から1まで（逆順）: ");
    for (i = 10; i >= 1; i--)
    {
        printf("%d ", i);
    }
    printf("\n\n");

    /* 3. 偶数だけを出力 */
    printf("0から20までの偶数: ");
    for (i = 0; i <= 20; i += 2)
    {
        printf("%d ", i);
    }
    printf("\n\n");

    /* 4. 累計の計算 */
    sum = 0;
    for (i = 1; i <= 100; i++)
    {
        sum += i;
    }
    printf("1から100までの合計: %d\n\n", sum);

    /* 5. 九九の表（ネストしたfor文） */
    printf("九九の表:\n");
    printf("    ");
    for (i = 1; i <= 9; i++)
    {
        printf("%3d ", i);
    }
    printf("\n");
    printf("   ");
    for (i = 1; i <= 9; i++)
    {
        printf("----");
    }
    printf("\n");

    for (i = 1; i <= 9; i++)
    {
        printf("%2d |", i);
        for (j = 1; j <= 9; j++)
        {
            printf("%3d ", i * j);
        }
        printf("\n");
    }
    printf("\n");

    /* 6. 文字の出力 */
    printf("アルファベット（大文字）: ");
    for (ch = 'A'; ch <= 'Z'; ch++)
    {
        printf("%c ", ch);
    }
    printf("\n\n");

    /* 7. 複数変数を使ったfor文 */
    printf("複数変数の例:\n");
    for (i = 0, j = 10; i < j; i++, j--)
    {
        printf("i = %d, j = %d, 合計 = %d\n", i, j, i + j);
    }
    printf("\n");

    /* 8. 階乗の計算 */
    n = 5;
    factorial = 1;
    printf("%d! = ", n);
    for (i = n; i >= 1; i--)
    {
        factorial *= i;
        printf("%d", i);
        if (i > 1)
            printf(" x ");
    }
    printf(" = %d\n", factorial);

    return 0;
}