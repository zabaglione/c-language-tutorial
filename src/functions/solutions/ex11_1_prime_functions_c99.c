/*
 * 演習解答例: 素数判定関数とその活用（C99版）
 * 
 * このプログラムは、素数判定を行う関数を作成し、
 * それを使って様々な処理を行います。
 * C99の機能：//コメント、bool型、変数宣言位置の自由化、for文内での変数宣言
 */
#include <stdio.h>
#include <stdbool.h>

// 関数プロトタイプ
bool is_prime(int n);
void print_primes_in_range(int start, int end);
int count_primes_in_range(int start, int end);
int nth_prime(int n);

// 素数判定を行う関数（C99: bool型を返す）
bool is_prime(int n)
{
    // 1以下は素数ではない
    if (n <= 1)
    {
        return false;
    }
    
    // 2は素数
    if (n == 2)
    {
        return true;
    }
    
    // 偶数は2以外素数ではない
    if (n % 2 == 0)
    {
        return false;
    }
    
    // 3からsqrt(n)まで奇数のみをチェック
    // C99: forループ内で変数宣言
    for (int i = 3; i * i <= n; i += 2)
    {
        if (n % i == 0)
        {
            return false;  // 約数が見つかった
        }
    }
    
    return true;  // 素数
}

// 指定した範囲の素数を表示する関数
void print_primes_in_range(int start, int end)
{
    printf("%dから%dまでの素数:\n", start, end);
    
    int count = 0;
    for (int i = start; i <= end; i++)  // C99: forループ内で変数宣言
    {
        if (is_prime(i))
        {
            printf("%d ", i);
            count++;
            
            // 10個ごとに改行
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

// 指定した範囲の素数の個数を数える関数
int count_primes_in_range(int start, int end)
{
    int count = 0;
    for (int i = start; i <= end; i++)  // C99: forループ内で変数宣言
    {
        if (is_prime(i))
        {
            count++;
        }
    }
    
    return count;
}

// n番目の素数を求める関数
int nth_prime(int n)
{
    if (n <= 0)
    {
        return -1;  // 無効な入力
    }
    
    int count = 0;
    int num = 2;
    
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
    
    return -1;  // ここには到達しないはず
}

// 素数間の距離（ギャップ）を分析する関数（C99追加機能）
void analyze_prime_gaps(int limit)
{
    printf("\n素数間のギャップ分析（%dまで）:\n", limit);
    
    int prev_prime = 2;
    int max_gap = 0;
    int max_gap_start = 0;
    
    for (int i = 3; i <= limit; i++)  // C99: forループ内で変数宣言
    {
        if (is_prime(i))
        {
            int gap = i - prev_prime;
            if (gap > max_gap)
            {
                max_gap = gap;
                max_gap_start = prev_prime;
            }
            prev_prime = i;
        }
    }
    
    printf("最大ギャップ: %d (%d と %d の間)\n", 
           max_gap, max_gap_start, max_gap_start + max_gap);
}

int main(void)
{
    int choice;
    
    printf("=== 素数判定プログラム ===\n\n");
    
    do
    {
        printf("メニューを選択してください:\n");
        printf("1. 単一の数の素数判定\n");
        printf("2. 範囲内の素数を表示\n");
        printf("3. 範囲内の素数の個数をカウント\n");
        printf("4. n番目の素数を求める\n");
        printf("5. 素数間のギャップ分析（C99追加機能）\n");
        printf("0. 終了\n");
        printf("選択: ");
        scanf("%d", &choice);
        
        switch (choice)
        {
        case 1:
            {
                printf("\n判定したい数を入力: ");
                int number;  // C99: 使用箇所で変数宣言
                scanf("%d", &number);
                
                if (is_prime(number))
                {
                    printf("%d は素数です\n\n", number);
                }
                else
                {
                    printf("%d は素数ではありません\n\n", number);
                }
            }
            break;
            
        case 2:
            {
                printf("\n開始値を入力: ");
                int start, end;  // C99: 使用箇所で変数宣言
                scanf("%d", &start);
                printf("終了値を入力: ");
                scanf("%d", &end);
                
                printf("\n");
                print_primes_in_range(start, end);
                printf("\n");
            }
            break;
            
        case 3:
            {
                printf("\n開始値を入力: ");
                int start, end;  // C99: 使用箇所で変数宣言
                scanf("%d", &start);
                printf("終了値を入力: ");
                scanf("%d", &end);
                
                printf("\n%dから%dまでの素数の個数: %d\n\n",
                       start, end, count_primes_in_range(start, end));
            }
            break;
            
        case 4:
            {
                printf("\n何番目の素数を求めますか: ");
                int n;  // C99: 使用箇所で変数宣言
                scanf("%d", &n);
                
                if (n <= 0)
                {
                    printf("1以上の数を入力してください\n\n");
                }
                else
                {
                    int result = nth_prime(n);
                    printf("%d番目の素数は %d です\n\n", n, result);
                }
            }
            break;
            
        case 5:
            {
                printf("\nどこまでの素数を分析しますか: ");
                int limit;  // C99: 使用箇所で変数宣言
                scanf("%d", &limit);
                analyze_prime_gaps(limit);
                printf("\n");
            }
            break;
            
        case 0:
            printf("プログラムを終了します\n");
            break;
            
        default:
            printf("無効な選択です\n\n");
        }
        
    } while (choice != 0);
    
    // デモ実行
    printf("\n=== デモ実行 ===\n");
    printf("最初の10個の素数: ");
    for (int i = 1; i <= 10; i++)  // C99: forループ内で変数宣言
    {
        printf("%d ", nth_prime(i));
    }
    printf("\n");
    
    printf("\n1から100までの素数:\n");
    print_primes_in_range(1, 100);
    
    // C99: 複合リテラルを使った素数チェック
    printf("\n特定の数値の素数判定:\n");
    int test_numbers[] = {17, 20, 23, 25, 29, 30};
    for (int i = 0; i < 6; i++)
    {
        printf("%d: %s\n", test_numbers[i], 
               is_prime(test_numbers[i]) ? "素数" : "素数ではない");
    }
    
    return 0;
}