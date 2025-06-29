/*
 * ファイル名: ex4_6_janken_game.c
 * チャレンジ4-6: じゃんけんゲーム
 * 説明: コンピュータとじゃんけんをする3回勝負のプログラム
 * 規格: C90準拠
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    /* 変数の宣言（C90では先頭で宣言） */
    int user_choice, computer_choice;
    int user_wins, computer_wins, draws;
    int round;
    char *hands[3] = {"グー", "チョキ", "パー"};
    char *result_message;
    
    /* 勝利数の初期化 */
    user_wins = 0;
    computer_wins = 0;
    draws = 0;
    
    /* 乱数の初期化 */
    srand((unsigned int)time(NULL));
    
    printf("=== じゃんけんゲーム（3回勝負） ===\n");
    printf("1: グー, 2: チョキ, 3: パー\n");
    printf("さあ、始めましょう！\n\n");
    
    /* 3回勝負のループ */
    for (round = 1; round <= 3; round++) {
        printf("--- 第%d回戦 ---\n", round);
        
        /* ユーザーの手の入力 */
        do {
            printf("あなたの手を選んでください (1-3): ");
            scanf("%d", &user_choice);
            
            if (user_choice < 1 || user_choice > 3) {
                printf("エラー: 1〜3の数字を入力してください。\n");
            }
        } while (user_choice < 1 || user_choice > 3);
        
        /* コンピュータの手をランダムに決定 */
        computer_choice = rand() % 3 + 1;
        
        /* 手の表示 */
        printf("あなた: %s\n", hands[user_choice - 1]);
        printf("コンピュータ: %s\n", hands[computer_choice - 1]);
        
        /* 勝敗判定 */
        if (user_choice == computer_choice) {
            printf("結果: あいこ\n");
            result_message = "あいこ";
            draws++;
        } else if ((user_choice == 1 && computer_choice == 2) ||  /* グー vs チョキ */
                   (user_choice == 2 && computer_choice == 3) ||  /* チョキ vs パー */
                   (user_choice == 3 && computer_choice == 1)) {  /* パー vs グー */
            printf("結果: あなたの勝ち！\n");
            result_message = "勝利";
            user_wins++;
        } else {
            printf("結果: コンピュータの勝ち！\n");
            result_message = "敗北";
            computer_wins++;
        }
        
        /* 現在の戦績表示 */
        printf("現在の戦績 - あなた: %d勝, コンピュータ: %d勝, あいこ: %d回\n", 
               user_wins, computer_wins, draws);
        printf("\n");
    }
    
    /* 最終結果の表示 */
    printf("=== 最終結果 ===\n");
    printf("3回戦の結果:\n");
    printf("あなた: %d勝\n", user_wins);
    printf("コンピュータ: %d勝\n", computer_wins);
    printf("あいこ: %d回\n", draws);
    printf("-----------------\n");
    
    /* 総合勝者の判定 */
    if (user_wins > computer_wins) {
        printf("総合結果: あなたの勝利！\n");
        printf("おめでとうございます！素晴らしい戦いでした。\n");
        
        if (user_wins == 3) {
            printf("完全勝利です！パーフェクトゲーム達成！\n");
        } else if (user_wins == 2 && draws == 1) {
            printf("2勝1分けの安定した勝利です。\n");
        }
    } else if (computer_wins > user_wins) {
        printf("総合結果: コンピュータの勝利！\n");
        printf("残念！次回はきっと勝てますよ。\n");
        
        if (computer_wins == 3) {
            printf("完敗でした。次回に期待しましょう！\n");
        }
    } else {
        printf("総合結果: 引き分け！\n");
        printf("互角の戦いでした。良いゲームでしたね。\n");
    }
    
    /* 詳細な分析 */
    printf("\n=== ゲーム分析 ===\n");
    
    /* 勝率の計算 */
    if (user_wins + computer_wins > 0) {
        double win_rate = (double)user_wins / (user_wins + computer_wins) * 100.0;
        printf("あなたの勝率: %.1f%%\n", win_rate);
        
        if (win_rate >= 75.0) {
            printf("評価: 優秀な戦績です！\n");
        } else if (win_rate >= 50.0) {
            printf("評価: まずまずの戦績です。\n");
        } else {
            printf("評価: 次回頑張りましょう！\n");
        }
    }
    
    /* あいこの回数による分析 */
    if (draws == 0) {
        printf("あいこなしの白熱した戦いでした。\n");
    } else if (draws == 1) {
        printf("1回のあいこがありました。\n");
    } else if (draws == 2) {
        printf("2回のあいこがありました。運命的な戦いでしたね。\n");
    } else {
        printf("全てあいこ！これは珍しい結果です。\n");
    }
    
    /* ランダム性の説明 */
    printf("\n=== 豆知識 ===\n");
    printf("・コンピュータの手は完全にランダムです\n");
    printf("・じゃんけんの確率論では、各手が出る確率は1/3です\n");
    printf("・人間は無意識にパターンを作りがちですが、\n");
    printf("  本当のランダム性には勝てません\n");
    
    printf("\nゲーム終了！また遊んでくださいね。\n");
    
    return 0;
}

/*
学習ポイント:
1. ランダム数の生成（srand, rand）
2. 複雑な条件分岐による勝敗判定
3. ループを使った繰り返し処理
4. 配列を使った文字列の管理
5. 統計的な分析とパーセンテージ計算

実装のポイント:
- C90準拠のため、すべての変数を関数先頭で宣言
- time(NULL)を使った乱数の初期化
- 複雑な勝敗判定ロジック
- ユーザー入力の検証
- 詳細な結果分析とフィードバック

じゃんけんの勝敗ルール:
- グー(1) > チョキ(2)
- チョキ(2) > パー(3)  
- パー(3) > グー(1)
*/