/*
 * ファイル名: ex6_1_fibonacci.c
 * 演習6-1: フィボナッチ数列
 * 説明: 最初のN個のフィボナッチ数を表示するプログラム
 * 規格: C90準拠
 */
#include <stdio.h>

int main(void)
{
    /* 変数の宣言（C90では先頭で宣言） */
    int n, i;
    int first, second, next;
    
    printf("=== フィボナッチ数列プログラム ===\n");
    printf("表示する個数を入力してください: ");
    scanf("%d", &n);
    
    /* 入力値の検証 */
    if (n <= 0) {
        printf("エラー: 正の整数を入力してください。\n");
        return 1;
    }
    
    printf("\n最初の%d個のフィボナッチ数:\n", n);
    
    /* 初期値の設定 */
    first = 0;
    second = 1;
    
    /* フィボナッチ数列の表示 */
    if (n >= 1) {
        printf("%d ", first);
    }
    if (n >= 2) {
        printf("%d ", second);
    }
    
    /* for文を使用してフィボナッチ数列を計算・表示 */
    for (i = 3; i <= n; i++) {
        next = first + second;
        printf("%d ", next);
        
        /* 次の計算のために値を更新 */
        first = second;
        second = next;
    }
    
    printf("\n\n");
    printf("フィボナッチ数列の計算が完了しました。\n");
    
    return 0;
}

/*
学習ポイント:
1. for文による繰り返し処理
2. 変数の値の更新と循環
3. フィボナッチ数列のアルゴリズム
4. 条件分岐との組み合わせ

実装のポイント:
- C90準拠のため、すべての変数を関数先頭で宣言
- for文を使用してフィボナッチ数列を計算
- 初期値（0, 1）の特別な処理
- 値の更新を正確に行う
*/
