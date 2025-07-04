/*
 * ファイル名: ex6_2_number_guess_c99.c
 * 演習6-2: 数当てゲーム（改良版）
 * 説明: 1から100までの数当てゲーム（デモ版）
 * 規格: C99準拠
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    printf("=== 数当てゲーム ===\n");
    
    // ランダムシードの初期化
    srand(time(NULL));
    
    // 1から100までのランダムな数を生成
    int target_number = rand() % 100 + 1;
    int max_attempts = 10;
    int attempts = 0;
    int found = 0;
    
    printf("1から100までの数を%d回以内で当ててください。\n", max_attempts);
    printf("（実際のゲームでは対話的に入力しますが、デモでは自動実行します）\n\n");
    
    // デモ用の予想値配列（実際の実装では scanf で入力）
    int demo_guesses[] = {50, 75, 25, 37, 44, 41, 43, 42};
    int demo_count = sizeof(demo_guesses) / sizeof(demo_guesses[0]);
    
    printf("正解は %d です（通常は表示されません）\n\n", target_number);
    
    // do-while文を使用したゲームループ
    do {
        attempts++;
        
        // デモ用の予想値を使用
        int guess;
        if (attempts <= demo_count) {
            guess = demo_guesses[attempts - 1];
        } else {
            guess = target_number; // 最後は正解にする
        }
        
        printf("試行 %d: %d\n", attempts, guess);
        
        if (guess == target_number) {
            printf("おめでとうございます！正解です！\n");
            printf("%d回で正解しました。\n", attempts);
            found = 1;
        } else if (guess < target_number) {
            printf("もっと大きい数です。\n");
        } else {
            printf("もっと小さい数です。\n");
        }
        
        printf("\n");
        
    } while (!found && attempts < max_attempts);
    
    // ゲーム終了の処理
    if (!found) {
        printf("残念！%d回の試行で当てられませんでした。\n", max_attempts);
        printf("正解は %d でした。\n", target_number);
    }
    
    printf("ゲーム終了です。\n");
    
    return 0;
}

/*
学習ポイント:
1. do-while文による繰り返し処理
2. ランダム数の生成
3. 条件による処理の分岐
4. ループの終了条件の制御

実装のポイント:
- C99準拠のため、変数を使用箇所の近くで宣言
- 配列の初期化を宣言と同時に実行
- ループ内での変数宣言
- コメントに//スタイルを使用
- デモ版として自動実行する形に変更
*/
