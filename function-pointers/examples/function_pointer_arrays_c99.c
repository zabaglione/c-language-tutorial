/* 関数ポインタ配列の活用（C99版） */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/* 計算機システム用の演算関数群 */
double add_operation(double a, double b) { return a + b; }
double sub_operation(double a, double b) { return a - b; }
double mul_operation(double a, double b) { return a * b; }
double div_operation(double a, double b)
{
    if (b != 0.0)
        return a / b;
    printf("エラー: ゼロ除算\n");
    return 0.0;
}

/* メニューシステム用の処理関数群 */
void show_profile(void)
{
    printf("=== プロフィール表示 ===\n");
    printf("名前: 田中太郎\n");
    printf("年齢: 25歳\n");
    printf("職業: エンジニア\n");
    printf("========================\n");
}

void show_settings(void)
{
    printf("=== 設定画面 ===\n");
    printf("言語: 日本語\n");
    printf("テーマ: ダーク\n");
    printf("通知: ON\n");
    printf("===============\n");
}

void show_help(void)
{
    printf("=== ヘルプ ===\n");
    printf("このアプリケーションの使用方法:\n");
    printf("1. メニューから項目を選択\n");
    printf("2. 処理が実行されます\n");
    printf("3. メインメニューに戻ります\n");
    printf("=============\n");
}

void show_about(void)
{
    printf("=== このアプリについて ===\n");
    printf("関数ポインタ配列デモ v1.0（C99版）\n");
    printf("C言語学習用サンプルプログラム\n");
    printf("========================\n");
}

void exit_application(void)
{
    printf("アプリケーションを終了します。\n");
}

/* ゲーム状態管理用の関数群 */
void state_menu(void)
{
    printf("[メニュー状態] ゲームメニューを表示中\n");
    printf("  利用可能なアクション: 開始(s), 設定(c), 終了(q)\n");
}

void state_playing(void)
{
    printf("[プレイ中状態] ゲームをプレイ中\n");
    printf("  利用可能なアクション: 一時停止(p), メニューに戻る(m)\n");
}

void state_paused(void)
{
    printf("[一時停止状態] ゲームが一時停止中\n");
    printf("  利用可能なアクション: 再開(r), メニューに戻る(m)\n");
}

void state_settings(void)
{
    printf("[設定状態] ゲーム設定を調整中\n");
    printf("  利用可能なアクション: 保存(s), キャンセル(c)\n");
}

/* データ変換関数群 */
int to_upper_case(int c)
{
    return (c >= 'a' && c <= 'z') ? c - 'a' + 'A' : c;
}

int to_lower_case(int c)
{
    return (c >= 'A' && c <= 'Z') ? c - 'A' + 'a' : c;
}

int rot13_transform(int c)
{
    if (c >= 'a' && c <= 'z')
        return (c - 'a' + 13) % 26 + 'a';
    if (c >= 'A' && c <= 'Z')
        return (c - 'A' + 13) % 26 + 'A';
    return c;
}

int reverse_case(int c)
{
    if (c >= 'a' && c <= 'z')
        return c - 'a' + 'A';
    if (c >= 'A' && c <= 'Z')
        return c - 'A' + 'a';
    return c;
}

/* メニュー項目構造体 - C99の指定初期化子を使用 */
typedef struct
{
    char name[30];
    void (*handler)(void);
} MenuItem;

/* ゲーム状態の列挙型 */
typedef enum
{
    GAME_MENU = 0,
    GAME_PLAYING = 1,
    GAME_PAUSED = 2,
    GAME_SETTINGS = 3,
    GAME_STATE_COUNT = 4
} GameState;

/* 文字変換関数の適用 */
void apply_transform(char *str, int (*transform)(int))
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        str[i] = transform(str[i]);
    }
}

/* 配列の表示 */
void print_double_array(const double arr[], int size, const char *label)
{
    printf("%s: ", label);
    for (int i = 0; i < size; i++)
    {
        printf("%.2f ", arr[i]);
    }
    printf("\n");
}

/* 高度な関数ポインタ配列操作 */
typedef struct {
    const char *name;
    const char *symbol;
    double (*operation)(double, double);
} CalculatorOperation;

int main(void)
{
    printf("=== 関数ポインタ配列の活用（C99版） ===\n\n");

    // 1. 計算機システム（構造体を使った拡張版）
    printf("=== 計算機システム ===\n");

    // C99の指定初期化子を使用
    CalculatorOperation operations[] = {
        {.name = "加算", .symbol = "+", .operation = add_operation},
        {.name = "減算", .symbol = "-", .operation = sub_operation},
        {.name = "乗算", .symbol = "*", .operation = mul_operation},
        {.name = "除算", .symbol = "/", .operation = div_operation}
    };

    int num_ops = sizeof(operations) / sizeof(operations[0]);
    double a = 15.0, b = 4.0;

    printf("数値: a = %.1f, b = %.1f\n", a, b);

    // 全ての演算を実行
    for (int i = 0; i < num_ops; i++)
    {
        double result = operations[i].operation(a, b);
        printf("%s (%s): %.1f %s %.1f = %.2f\n",
               operations[i].name, operations[i].symbol, 
               a, operations[i].symbol, b, result);
    }

    // 特定の演算のみ実行
    printf("\n特定の演算:\n");
    printf("乗算結果: %.2f\n", operations[2].operation(a, b));
    printf("除算結果: %.2f\n", operations[3].operation(a, b));

    // 2. メニューシステム（C99の複合リテラル使用）
    printf("\n=== メニューシステム ===\n");

    MenuItem menu[] = {
        {"プロフィール", show_profile},
        {"設定", show_settings},
        {"ヘルプ", show_help},
        {"このアプリについて", show_about},
        {"終了", exit_application}
    };

    int menu_size = sizeof(menu) / sizeof(menu[0]);

    printf("利用可能なメニュー項目:\n");
    for (int i = 0; i < menu_size; i++)
    {
        printf("%d. %s\n", i + 1, menu[i].name);
    }

    // メニュー項目の実行例
    printf("\nメニュー実行例:\n");
    menu[0].handler(); // プロフィール表示
    menu[2].handler(); // ヘルプ表示

    // 3. ゲーム状態管理システム
    printf("\n=== ゲーム状態管理システム ===\n");

    // 状態処理関数配列
    void (*state_handlers[])(void) = {
        [GAME_MENU] = state_menu,
        [GAME_PLAYING] = state_playing,
        [GAME_PAUSED] = state_paused,
        [GAME_SETTINGS] = state_settings
    };

    const char *state_names[] = {
        [GAME_MENU] = "メニュー",
        [GAME_PLAYING] = "プレイ中",
        [GAME_PAUSED] = "一時停止",
        [GAME_SETTINGS] = "設定"
    };

    printf("各ゲーム状態の処理:\n");
    for (GameState state = GAME_MENU; state < GAME_STATE_COUNT; state++)
    {
        printf("\n現在の状態: %s\n", state_names[state]);
        state_handlers[state]();
    }

    // 4. 動的な状態遷移
    printf("\n=== 動的な状態遷移 ===\n");

    GameState current_state = GAME_MENU;
    printf("初期状態: %s\n", state_names[current_state]);
    state_handlers[current_state]();

    // 状態遷移のシミュレーション
    GameState transitions[] = {GAME_PLAYING, GAME_PAUSED};
    for (int i = 0; i < 2; i++)
    {
        current_state = transitions[i];
        printf("\n状態遷移: %s\n", state_names[current_state]);
        state_handlers[current_state]();
    }

    // 5. 文字変換システム
    printf("\n=== 文字変換システム ===\n");

    // 変換関数テーブル
    struct {
        const char *name;
        int (*transform)(int);
    } transforms[] = {
        {"大文字変換", to_upper_case},
        {"小文字変換", to_lower_case},
        {"ROT13暗号", rot13_transform},
        {"大小文字反転", reverse_case}
    };

    int num_transforms = sizeof(transforms) / sizeof(transforms[0]);
    char original[] = "Hello World!";

    printf("元の文字列: '%s'\n", original);

    // 各変換を適用
    for (int i = 0; i < num_transforms; i++)
    {
        char test_str[50];
        strcpy(test_str, original);
        apply_transform(test_str, transforms[i].transform);
        printf("%s: '%s'\n", transforms[i].name, test_str);
    }

    // 6. 複数の数値に同じ演算を適用（ラムダ風の処理）
    printf("\n=== 複数数値への演算適用 ===\n");

    double numbers[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    int numbers_size = sizeof(numbers) / sizeof(numbers[0]);

    print_double_array(numbers, numbers_size, "元の配列");

    // 各演算を全ての数値ペアに適用
    for (int i = 0; i < num_ops; i++)
    {
        double results[numbers_size];
        for (int j = 0; j < numbers_size; j++)
        {
            results[j] = operations[i].operation(numbers[j], 2.0);
        }
        printf("%s (x, 2.0): ", operations[i].name);
        print_double_array(results, numbers_size, "結果");
    }

    // 7. 高度な関数ポインタの使用
    printf("\n=== 高度な関数ポインタの使用 ===\n");

    // 関数ポインタの配列のポインタ
    double (**op_ptr)(double, double) = &operations[0].operation;
    printf("ポインタ経由の演算: 10.0 + 3.0 = %.2f\n", (*op_ptr)(10.0, 3.0));

    // 関数ポインタのコピーと実行
    double (*copied_func)(double, double) = operations[2].operation;
    printf("コピーした関数の実行: 7.0 * 8.0 = %.2f\n", copied_func(7.0, 8.0));

    // 条件に基づく関数選択
    bool use_multiply = true;
    double (*selected_op)(double, double) = use_multiply ? 
                                            operations[2].operation : 
                                            operations[0].operation;
    printf("条件選択した演算: %.2f\n", selected_op(5.0, 6.0));

    printf("\n=== 関数ポインタ配列デモ完了 ===\n");

    return 0;
}

/*
C99の特徴:
1. 指定初期化子を使用した構造体の初期化
2. 配列の指定初期化子
3. bool型の使用
4. 変数宣言を使用箇所で可能
5. for文内での変数宣言
6. // 形式のコメント
7. 可変長配列（VLA）のサポート

学習ポイント:
1. 関数ポインタ配列の定義と使用
2. 構造体と関数ポインタの組み合わせ
3. 状態管理システムの実装
4. テーブル駆動型プログラミング
5. 動的な関数選択と実行
6. 関数ポインタの高度な操作
*/