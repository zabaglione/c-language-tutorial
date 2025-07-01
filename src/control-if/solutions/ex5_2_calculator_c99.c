/*
 * ファイル名: ex5_2_calculator_c99.c
 * 演習5-2: 電卓プログラム
 * 説明: 四則演算ができる簡単な電卓プログラム
 * 規格: C99準拠
 */
#include <stdio.h>

int main(void)
{
    printf("=== 簡単電卓プログラム ===\n");
    
    // 第一の数値入力
    printf("最初の数値を入力してください: ");
    double num1;
    scanf("%lf", &num1);
    
    // 演算子の入力
    printf("演算子を入力してください (+, -, *, /): ");
    char operator;
    scanf(" %c", &operator);  // 空白文字を読み飛ばすため、%cの前に空白
    
    // 第二の数値入力
    printf("二番目の数値を入力してください: ");
    double num2;
    scanf("%lf", &num2);
    
    // 演算子の妥当性チェック
    int valid_operator = 1;
    double result;
    
    // switch文による演算の実行
    switch (operator) {
        case '+':
            result = num1 + num2;
            printf("%.2f + %.2f = %.2f\n", num1, num2, result);
            break;
            
        case '-':
            result = num1 - num2;
            printf("%.2f - %.2f = %.2f\n", num1, num2, result);
            break;
            
        case '*':
            result = num1 * num2;
            printf("%.2f * %.2f = %.2f\n", num1, num2, result);
            break;
            
        case '/':
            // ゼロ除算チェック
            if (num2 == 0.0) {
                printf("エラー: ゼロで割ることはできません。\n");
                return 1;
            } else {
                result = num1 / num2;
                printf("%.2f / %.2f = %.2f\n", num1, num2, result);
            }
            break;
            
        default:
            printf("エラー: 無効な演算子です。(+, -, *, /) のいずれかを使用してください。\n");
            valid_operator = 0;
            break;
    }
    
    // 演算が成功した場合の追加情報
    if (valid_operator && operator != '/') {
        printf("\n=== 計算完了 ===\n");
        
        // 結果の分析
        if (result > 0) {
            printf("結果は正の数です。\n");
        } else if (result < 0) {
            printf("結果は負の数です。\n");
        } else {
            printf("結果はゼロです。\n");
        }
        
        // 整数かどうかのチェック
        if (result == (int)result) {
            printf("結果は整数です。\n");
        } else {
            printf("結果は小数です。\n");
        }
    } else if (valid_operator && operator == '/') {
        printf("\n=== 除算完了 ===\n");
        
        // 除算の特別な処理
        if (result == 1.0) {
            printf("割る数と割られる数が同じです。\n");
        } else if (result > 1.0) {
            printf("割られる数の方が大きいです。\n");
        } else {
            printf("割る数の方が大きいです。\n");
        }
    }
    
    printf("電卓プログラムを終了します。\n");
    
    return 0;
}

/*
学習ポイント:
1. switch文による多分岐処理
2. ゼロ除算のエラーハンドリング
3. 浮動小数点数の比較
4. break文の重要性
5. default句によるエラー処理

実装のポイント:
- C99準拠のため、変数を使用箇所の近くで宣言
- scanf()での文字入力時の注意点（空白文字の処理）
- 浮動小数点数の比較（== 0.0の使用）
- switch文での各caseの適切な処理
- ユーザーフレンドリーなエラーメッセージ
*/