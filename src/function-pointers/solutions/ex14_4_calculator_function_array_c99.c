/*
 * ファイル名: ex14_4_calculator_function_array_c99.c
 * 演習14-4: 関数ポインタ配列を使った計算機
 * 説明: 関数ポインタ配列を使用した計算機プログラム（デモ版）
 * 規格: C99準拠
 */
#include <stdio.h>

#define MAX_OPERATIONS 4
#define MAX_HISTORY 10

// 計算履歴を記録する構造体
typedef struct {
    int operand1;
    int operand2;
    char operation;
    int result;
} CalculationHistory;

// 演算関数群
int add(int a, int b)
{
    return a + b;
}

int subtract(int a, int b)
{
    return a - b;
}

int multiply(int a, int b)
{
    return a * b;
}

int divide_safe(int a, int b)
{
    if (b == 0) {
        printf("エラー: ゼロ除算\n");
        return 0;
    }
    return a / b;
}

// 履歴を表示する関数
void print_history(CalculationHistory *history, int count)
{
    printf("\n=== 計算履歴 ===\n");
    if (count == 0) {
        printf("履歴はありません\n");
        return;
    }
    
    for (int i = 0; i < count; i++) {
        printf("%d. %d %c %d = %d\n", 
               i + 1, 
               history[i].operand1, 
               history[i].operation,
               history[i].operand2,
               history[i].result);
    }
}

// 統計情報を表示する関数
void print_statistics(CalculationHistory *history, int count)
{
    printf("\n=== 統計情報 ===\n");
    printf("総計算回数: %d回\n", count);
    
    // 各演算の回数をカウント
    int operation_count[MAX_OPERATIONS] = {0};
    char operations[] = {'+', '-', '*', '/'};
    char *operation_names[] = {"加算", "減算", "乗算", "除算"};
    
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < MAX_OPERATIONS; j++) {
            if (history[i].operation == operations[j]) {
                operation_count[j]++;
                break;
            }
        }
    }
    
    // 演算別統計を表示
    for (int i = 0; i < MAX_OPERATIONS; i++) {
        printf("%s (%c): %d回\n", 
               operation_names[i], operations[i], operation_count[i]);
    }
}

int main(void)
{
    printf("=== 関数ポインタ配列計算機デモ ===\n");
    
    // 関数ポインタ配列と関連データ
    int (*operations[])(int, int) = {add, subtract, multiply, divide_safe};
    char op_symbols[] = {'+', '-', '*', '/'};
    char *op_names[] = {"加算", "減算", "乗算", "除算"};
    
    // 計算履歴管理
    CalculationHistory history[MAX_HISTORY];
    int history_count = 0;
    
    // デモ用の計算データ
    int demo_data[][3] = {
        {10, 5, 0},  // 10 + 5
        {15, 3, 1},  // 15 - 3
        {4, 6, 2},   // 4 * 6
        {20, 4, 3},  // 20 / 4
        {8, 0, 3},   // 8 / 0 (ゼロ除算テスト)
        {7, 2, 2},   // 7 * 2
        {100, 25, 1}, // 100 - 25
    };
    int num_demos = sizeof(demo_data) / sizeof(demo_data[0]);
    
    // デモ計算の実行
    for (int i = 0; i < num_demos && history_count < MAX_HISTORY; i++) {
        int a = demo_data[i][0];
        int b = demo_data[i][1];
        int op_index = demo_data[i][2];
        
        if (op_index >= 0 && op_index < MAX_OPERATIONS) {
            int result = operations[op_index](a, b);
            char op_char = op_symbols[op_index];
            
            printf("計算 %d: %d %c %d = %d (%s)\n", 
                   i + 1, a, op_char, b, result, op_names[op_index]);
            
            // 履歴に記録
            history[history_count].operand1 = a;
            history[history_count].operand2 = b;
            history[history_count].operation = op_char;
            history[history_count].result = result;
            history_count++;
        }
    }
    
    // 履歴表示
    print_history(history, history_count);
    
    // 統計情報表示
    print_statistics(history, history_count);
    
    // 関数ポインタ配列の活用例
    printf("\n=== 関数ポインタ配列の特徴デモ ===\n");
    int test_a = 12;
    int test_b = 3;
    
    printf("値 %d と %d での全演算結果:\n", test_a, test_b);
    for (int i = 0; i < MAX_OPERATIONS; i++) {
        int result = operations[i](test_a, test_b);
        printf("  %s: %d %c %d = %d\n", 
               op_names[i], test_a, op_symbols[i], test_b, result);
    }
    
    // 連続計算のデモ
    printf("\n=== 連続計算デモ ===\n");
    int value = 10;
    int operands[] = {2, 3, 4, 2};
    int ops[] = {0, 2, 1, 3}; // +, *, -, /
    
    printf("初期値: %d\n", value);
    for (int i = 0; i < 4; i++) {
        int old_value = value;
        value = operations[ops[i]](value, operands[i]);
        printf("ステップ %d: %d %c %d = %d\n", 
               i + 1, old_value, op_symbols[ops[i]], operands[i], value);
    }
    printf("最終結果: %d\n", value);
    
    return 0;
}

/*
学習ポイント:
1. 関数ポインタ配列による動的関数選択
2. 構造体を使った履歴管理
3. 統計情報の収集と表示
4. 連続計算での関数ポインタ活用

実装のポイント:
- C99準拠のため、変数を使用箇所の近くで宣言
- for文内でのループ変数宣言
- 配列の初期化を宣言と同時に実行
- コメントに//スタイルを使用
- デモ版として予め定義された計算パターンを使用
*/
