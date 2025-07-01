/*
 * ファイル名: ex6_6_factorial_c99.c
 * 演習6-6: 階乗計算
 * 説明: ユーザーから入力された数の階乗を計算するプログラム
 * 規格: C99準拠
 */
#include <stdio.h>

int main(void)
{
    printf("=== 階乗計算プログラム ===\n");
    printf("階乗を計算する正の整数を入力してください: ");
    
    int n;
    scanf("%d", &n);
    
    // 入力値の検証
    if (n < 0) {
        printf("エラー: 負の数の階乗は定義されていません。\n");
        return 1;
    }
    
    if (n > 20) {
        printf("警告: 20より大きい数はオーバーフローの可能性があります。\n");
        printf("計算を続行しますが、結果が正確でない可能性があります。\n");
    }
    
    // 階乗の計算（while文を使用）
    long long factorial = 1;
    int i = 1;
    
    printf("\n計算過程:\n");
    printf("%d! = ", n);
    
    // 0の階乗は1
    if (n == 0) {
        printf("1\n");
    } else {
        // while文による階乗計算
        while (i <= n) {
            factorial *= i;
            
            // 計算過程の表示
            if (i == 1) {
                printf("%d", i);
            } else {
                printf(" × %d", i);
            }
            
            i++;
        }
        printf(" = %lld\n", factorial);
    }
    
    // 結果の表示
    printf("\n=== 計算結果 ===\n");
    printf("%d! = %lld\n", n, factorial);
    
    // 追加情報の表示
    if (factorial > 1000000) {
        printf("この値は100万を超えています。\n");
    }
    
    // 関連する階乗値の表示
    if (n <= 10 && n > 0) {
        printf("\n参考: 1から%dまでの階乗:\n", n);
        long long ref_factorial = 1;
        for (int j = 1; j <= n; j++) {
            ref_factorial *= j;
            printf("%d! = %lld\n", j, ref_factorial);
        }
    }
    
    return 0;
}

/*
学習ポイント:
1. while文による繰り返し処理
2. 階乗計算のアルゴリズム
3. オーバーフロー対策（long long型の使用）
4. 計算過程の表示

実装のポイント:
- C99準拠のため、変数を使用箇所の近くで宣言
- 変数の初期化を宣言と同時に実行
- for文内でのループ変数宣言
- コメントに//スタイルを使用
- while文を使用した階乗計算
- long long型によるオーバーフロー対策
*/
