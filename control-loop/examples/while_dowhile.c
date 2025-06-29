/*
 * while文とdo-while文の使い方
 *
 * このプログラムは、while文とdo-while文の
 * 基本的な使い方と違いを示します。
 */
#include <stdio.h>

int main(void)
{
    int i;
    int num;
    int sum;
    char choice;
    int target;
    int guess;
    int attempts;

    /* 1. 基本的なwhile文 */
    printf("=== while文の基本 ===\n");
    i = 1;
    while (i <= 5)
    {
        printf("カウント: %d\n", i);
        i++;
    }
    printf("\n");

    /* 2. ユーザー入力を使ったwhile文 */
    printf("=== 合計計算（0で終了）===\n");
    sum = 0;
    printf("数値を入力してください（0で終了）: ");
    scanf("%d", &num);

    while (num != 0)
    {
        sum += num;
        printf("現在の合計: %d\n", sum);
        printf("次の数値を入力してください（0で終了）: ");
        scanf("%d", &num);
    }
    printf("最終合計: %d\n\n", sum);

    /* 3. do-while文の基本 */
    printf("=== do-while文の基本 ===\n");
    i = 1;
    do
    {
        printf("カウント: %d\n", i);
        i++;
    } while (i <= 5);
    printf("\n");

    /* 4. メニュー選択（do-whileの典型的な使用例） */
    printf("=== メニューシステム ===\n");
    do
    {
        printf("\n--- メインメニュー ---\n");
        printf("1. 挨拶\n");
        printf("2. 現在時刻の表示（ダミー）\n");
        printf("3. カウントダウン\n");
        printf("Q. 終了\n");
        printf("選択してください: ");
        scanf(" %c", &choice);

        switch (choice)
        {
        case '1':
            printf("こんにちは！\n");
            break;
        case '2':
            printf("現在時刻: 12:00（ダミー）\n");
            break;
        case '3':
            printf("カウントダウン開始: ");
            for (i = 5; i >= 1; i--)
            {
                printf("%d... ", i);
            }
            printf("発射！\n");
            break;
        case 'Q':
        case 'q':
            printf("プログラムを終了します。\n");
            break;
        default:
            printf("無効な選択です。\n");
        }
    } while (choice != 'Q' && choice != 'q');

    /* 5. while vs do-whileの違い */
    printf("\n=== while vs do-while ===\n");

    /* 条件が最初から偽の場合のwhile */
    printf("while文（条件が最初から偽）:\n");
    i = 10;
    while (i < 5)
    {
        printf("これは実行されません\n");
        i++;
    }
    printf("while文は一度も実行されませんでした\n");

    /* 条件が最初から偽の場合のdo-while */
    printf("\ndo-while文（条件が最初から偽）:\n");
    i = 10;
    do
    {
        printf("do-while文は最低1回実行されます（i = %d）\n", i);
        i++;
    } while (i < 5);

    /* 6. 数当てゲーム（簡易版） */
    printf("\n=== 数当てゲーム ===\n");
    target = 42; /* 正解の数 */
    attempts = 0;

    printf("1から100までの数を当ててください!\n");

    do
    {
        printf("予想を入力: ");
        scanf("%d", &guess);
        attempts++;

        if (guess < target)
        {
            printf("もっと大きいです\n");
        }
        else if (guess > target)
        {
            printf("もっと小さいです\n");
        }
        else
        {
            printf("正解！ %d回で当たりました!\n", attempts);
        }
    } while (guess != target);

    return 0;
}