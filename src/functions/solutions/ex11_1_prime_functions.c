/*
 * 演習解答例: 素数判定関数とその活用
 *
 * このプログラムは、素数判定を行う関数を作成し、
 * それを使って様々な処理を行います。
 */
#include <stdio.h>

/* 関数プロトタイプ */
int is_prime(int n);
void print_primes_in_range(int start, int end);
int count_primes_in_range(int start, int end);
int nth_prime(int n);

/* 素数判定を行う関数 */
int is_prime(int n)
{
    int i;

    /* 1以下は素数ではない */
    if (n <= 1)
    {
        return 0;
    }

    /* 2は素数 */
    if (n == 2)
    {
        return 1;
    }

    /* 偶数は2以外素数ではない */
    if (n % 2 == 0)
    {
        return 0;
    }

    /* 3からsqrt(n)まで奇数のみをチェック */
    for (i = 3; i * i <= n; i += 2)
    {
        if (n % i == 0)
        {
            return 0; /* 約数が見つかった */
        }
    }

    return 1; /* 素数 */
}

/* 指定した範囲の素数を表示する関数 */
void print_primes_in_range(int start, int end)
{
    int i;
    int count = 0;

    printf("%dから%dまでの素数:\n", start, end);

    for (i = start; i <= end; i++)
    {
        if (is_prime(i))
        {
            printf("%d ", i);
            count++;

            /* 10個ごとに改行 */
            if (count % 10 == 0)
            {
                printf("\n");
            }
        }
    }

    if (count % 10 != 0)
    {
        printf("\n");
    }

    printf("見つかった素数の個数: %d\n", count);
}

/* 指定した範囲の素数の個数を数える関数 */
int count_primes_in_range(int start, int end)
{
    int i;
    int count = 0;

    for (i = start; i <= end; i++)
    {
        if (is_prime(i))
        {
            count++;
        }
    }

    return count;
}

/* n番目の素数を求める関数 */
int nth_prime(int n)
{
    int count = 0;
    int num = 2;

    if (n <= 0)
    {
        return -1; /* 無効な入力 */
    }

    while (count < n)
    {
        if (is_prime(num))
        {
            count++;
            if (count == n)
            {
                return num;
            }
        }
        num++;
    }

    return -1; /* ここには到達しないはず */
}

int main(void)
{
    printf("=== 素数判定プログラム（デモ版）===\n\n");

    /* デモ1: 単一の数の素数判定 */
    printf("1. 単一の数の素数判定\n");
    int test_numbers[] = {2, 3, 4, 17, 18, 97, 100, 101};
    int num_tests = sizeof(test_numbers) / sizeof(test_numbers[0]);
    int i;
    
    for (i = 0; i < num_tests; i++)
    {
        int number = test_numbers[i];
        printf("   %d -> ", number);
        if (is_prime(number))
        {
            printf("素数です\n");
        }
        else
        {
            printf("素数ではありません\n");
        }
    }
    printf("\n");

    /* デモ2: 範囲内の素数を表示 */
    printf("2. 範囲内の素数を表示\n");
    int demo_ranges[][2] = {{1, 20}, {30, 50}, {90, 110}};
    int num_ranges = sizeof(demo_ranges) / sizeof(demo_ranges[0]);
    
    for (i = 0; i < num_ranges; i++)
    {
        int start = demo_ranges[i][0];
        int end = demo_ranges[i][1];
        printf("   範囲 %d から %d の素数:\n   ", start, end);
        print_primes_in_range(start, end);
        printf("\n");
    }

    /* デモ3: 範囲内の素数の個数をカウント */
    printf("3. 範囲内の素数の個数をカウント\n");
    for (i = 0; i < num_ranges; i++)
    {
        int start = demo_ranges[i][0];
        int end = demo_ranges[i][1];
        int count = count_primes_in_range(start, end);
        printf("   範囲 %d から %d: %d個\n", start, end, count);
    }
    printf("\n");

    /* デモ4: n番目の素数を求める */
    printf("4. n番目の素数を求める\n");
    int nth_tests[] = {1, 5, 10, 15, 20, 25};
    int nth_count = sizeof(nth_tests) / sizeof(nth_tests[0]);
    
    for (i = 0; i < nth_count; i++)
    {
        int n = nth_tests[i];
        printf("   %d番目の素数: %d\n", n, nth_prime(n));
    }
    printf("\n");

    /* 追加デモ: 最初の30個の素数を表示 */
    printf("5. 最初の30個の素数\n   ");
    for (i = 1; i <= 30; i++)
    {
        printf("%d ", nth_prime(i));
        if (i % 10 == 0) printf("\n   ");
    }
    printf("\n\n");
    
    printf("=== デモ完了 ===\n");
    return 0;
}
