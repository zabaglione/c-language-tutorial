/*
 * break文とcontinue文の使い方
 *
 * このプログラムは、ループ制御文である
 * break文とcontinue文の使い方を示します。
 */
#include <stdio.h>

int main(void)
{
    int i, j;
    int sum;
    int num;
    int is_prime;
    int count;
    int value;
    char ch;

    /* 1. break文の基本 */
    printf("=== break文の基本 ===\n");
    printf("1から10まで出力（5で中断）:\n");
    for (i = 1; i <= 10; i++)
    {
        if (i == 5)
        {
            printf("\n5に到達したので終了します\n");
            break;
        }
        printf("%d ", i);
    }
    printf("\n\n");

    /* 2. continue文の基本 */
    printf("=== continue文の基本 ===\n");
    printf("1から10まで出力（偶数をスキップ）:\n");
    for (i = 1; i <= 10; i++)
    {
        if (i % 2 == 0)
        {
            continue; /* 偶数の場合は次の繰り返しへ */
        }
        printf("%d ", i);
    }
    printf("\n\n");

    /* 3. 素数の判定（breakの活用） */
    printf("=== 素数判定 ===\n");
    printf("整数を入力してください: ");
    scanf("%d", &num);

    is_prime = 1; /* 素数フラグ（1:素数、0:素数でない） */

    if (num <= 1)
    {
        is_prime = 0;
    }
    else
    {
        for (i = 2; i * i <= num; i++)
        {
            if (num % i == 0)
            {
                is_prime = 0;
                break; /* 約数が見つかったら終了 */
            }
        }
    }

    if (is_prime)
    {
        printf("%d は素数です\n", num);
    }
    else
    {
        printf("%d は素数ではありません\n", num);
    }
    printf("\n");

    /* 4. 負の数を除外した合計（continueの活用） */
    printf("=== 正の数の合計計算 ===\n");
    printf("5つの数を入力してください（負の数は無視されます）:\n");

    sum = 0;
    count = 0;
    for (i = 0; i < 5; i++)
    {
        printf("%d番目の数: ", i + 1);
        scanf("%d", &value);

        if (value < 0)
        {
            printf("  → 負の数なのでスキップします\n");
            continue;
        }

        sum += value;
        count++;
    }

    printf("正の数の合計: %d（%d個）\n\n", sum, count);

    /* 5. ネストしたループでのbreak */
    printf("=== ネストしたループでのbreak ===\n");
    printf("九九の表（5x5で中断）:\n");

    for (i = 1; i <= 9; i++)
    {
        for (j = 1; j <= 9; j++)
        {
            if (i == 5 && j == 5)
            {
                printf("\n5x5で中断します\n");
                break; /* 内側のループのみ終了 */
            }
            printf("%2d ", i * j);
        }
        if (i == 5 && j == 5)
        {
            break; /* 外側のループも終了 */
        }
        printf("\n");
    }
    printf("\n");

    /* 6. 無限ループとbreak */
    printf("=== 無限ループの制御 ===\n");
    printf("'q'を入力すると終了します:\n");
    while (1)
    { /* 無限ループ */
        printf("文字を入力: ");
        scanf(" %c", &ch);

        if (ch == 'q' || ch == 'Q')
        {
            printf("終了します\n");
            break;
        }

        printf("入力された文字: %c\n", ch);
    }
    printf("\n");

    /* 7. 3の倍数と5の倍数をスキップ */
    printf("=== 3の倍数と5の倍数以外を表示 ===\n");
    printf("1から30まで（3の倍数と5の倍数を除く）:\n");

    for (i = 1; i <= 30; i++)
    {
        if (i % 3 == 0 || i % 5 == 0)
        {
            continue;
        }
        printf("%d ", i);
    }
    printf("\n");

    return 0;
}