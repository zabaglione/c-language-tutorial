/*
 * ファイル名: ex5_3_prime_list_c99.c
 * 演習5-3: 素数リスト
 * 説明: 指定された範囲内のすべての素数を表示するプログラム
 * 規格: C99準拠
 */
#include <stdio.h>
#include <math.h>

int main(void)
{
    printf("=== 素数リスト プログラム ===\n");
    printf("開始値を入力してください: ");
    
    int start, end;
    scanf("%d", &start);
    printf("終了値を入力してください: ");
    scanf("%d", &end);
    
    // 入力値の検証
    if (start < 2) {
        start = 2; // 最小の素数は2
    }
    if (end < start) {
        printf("エラー: 終了値は開始値以上である必要があります。\n");
        return 1;
    }
    
    printf("\n%dから%dまでの素数:\n", start, end);
    int prime_count = 0;
    
    // 各数について素数判定を行う
    for (int num = start; num <= end; num++) {
        int is_prime = 1; // 素数と仮定
        
        // 2未満は素数ではない
        if (num < 2) {
            is_prime = 0;
        } else if (num == 2) {
            // 2は素数
            is_prime = 1;
        } else if (num % 2 == 0) {
            // 2以外の偶数は素数ではない
            is_prime = 0;
        } else {
            // 奇数について3からsqrt(num)まで割り切れるかチェック
            int sqrt_num = (int)sqrt(num);
            for (int i = 3; i <= sqrt_num; i += 2) {
                if (num % i == 0) {
                    is_prime = 0;
                    break; // 割り切れたので素数ではない
                }
            }
        }
        
        // 素数の場合は表示
        if (is_prime) {
            printf("%d ", num);
            prime_count++;
            
            // 10個ごとに改行
            if (prime_count % 10 == 0) {
                printf("\n");
            }
        }
    }
    
    printf("\n\n=== 結果 ===\n");
    printf("範囲内の素数の個数: %d個\n", prime_count);
    
    // 統計情報の表示
    if (prime_count > 0) {
        printf("素数の密度: %.2f%%\n", 
               (double)prime_count / (end - start + 1) * 100);
    }
    
    return 0;
}

/*
学習ポイント:
1. ネストしたループの使用
2. break文による早期ループ終了
3. 効率的な素数判定アルゴリズム
4. 数学的な最適化（sqrt、偶数のスキップ）

実装のポイント:
- C99準拠のため、変数を使用箇所の近くで宣言
- for文内でのループ変数宣言
- 変数の初期化を宣言と同時に実行
- コメントに//スタイルを使用
- sqrt()関数を使用した効率的な素数判定
*/
