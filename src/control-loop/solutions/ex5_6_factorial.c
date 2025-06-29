/*
 * ファイル名: ex5_6_factorial.c
 * 演習5-6: 階乗計算
 * 説明: ユーザーから入力された数の階乗を計算するプログラム
 * 規格: C90準拠
 */
#include <stdio.h>

int main(void)
{
    /* 変数の宣言（C90では先頭で宣言） */
    int n;
    long long factorial;
    int i;
    
    printf("=== 階乗計算プログラム ===\n");
    printf("階乗を計算する正の整数を入力してください: ");
    scanf("%d", &n);
    
    /* 入力値の検証 */
    if (n < 0) {
        printf("エラー: 負の数の階乗は定義されていません。\n");
        return 1;
    }
    
    if (n > 20) {
        printf("警告: 20より大きい数はオーバーフローの可能性があります。\n");
        printf("計算を続行しますが、結果が正確でない可能性があります。\n");
    }
    
    /* 階乗の計算（while文を使用） */
    factorial = 1;
    i = 1;
    
    printf("\n計算過程:\n");
    printf("%d! = ", n);
    
    /* 0の階乗は1 */
    if (n == 0) {
        printf("1\n");
    } else {
        /* while文による階乗計算 */
        while (i <= n) {
            factorial *= i;
            
            /* 計算過程の表示 */
            if (i == 1) {
                printf("%d", i);
            } else {
                printf(" × %d", i);
            }
            
            i++;
        }
        printf(" = %lld\n", factorial);
    }
    
    /* 結果の表示 */
    printf("\n=== 計算結果 ===\n");
    printf("%d! = %lld\n", n, factorial);
    
    /* 追加情報の表示 */
    if (factorial > 1000000) {
        printf("この値は100万を超えています。\n");
    }
    
    /* 関連する階乗値の表示 */
    if (n <= 10 && n > 0) {
        printf("\n参考: 1から%dまでの階乗:\n", n);
        factorial = 1;
        for (i = 1; i <= n; i++) {
            factorial *= i;
            printf("%d! = %lld\n", i, factorial);
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
- C90準拠のため、すべての変数を関数先頭で宣言
- while文を使用した階乗計算
- long long型によるオーバーフロー対策
- 0の階乗（0! = 1）の特別処理
- 計算過程の詳細な表示
- 入力値の検証とエラーハンドリング
*/
