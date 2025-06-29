/* 関数ポインタ配列の活用 */
#include <stdio.h>
#include <string.h>

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
    printf("関数ポインタ配列デモ v1.0\n");
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
    if (c >= 'a' && c <= 'z')
    {
        return c - 'a' + 'A';
    }
    return c;
}

int to_lower_case(int c)
{
    if (c >= 'A' && c <= 'Z')
    {
        return c - 'A' + 'a';
    }
    return c;
}

int rot13_transform(int c)
{
    if (c >= 'a' && c <= 'z')
    {
        return (c - 'a' + 13) % 26 + 'a';
    }
    if (c >= 'A' && c <= 'Z')
    {
        return (c - 'A' + 13) % 26 + 'A';
    }
    return c;
}

int reverse_case(int c)
{
    if (c >= 'a' && c <= 'z')
    {
        return c - 'a' + 'A';
    }
    if (c >= 'A' && c <= 'Z')
    {
        return c - 'A' + 'a';
    }
    return c;
}

/* メニュー項目構造体 */
struct MenuItem
{
    char name[30];
    void (*handler)(void);
};

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
    int i;
    for (i = 0; str[i] != '\0'; i++)
    {
        str[i] = transform(str[i]);
    }
}

/* 配列の表示 */
void print_double_array(double arr[], int size, const char *label)
{
    int i;
    printf("%s: ", label);
    for (i = 0; i < size; i++)
    {
        printf("%.2f ", arr[i]);
    }
    printf("\n");
}

int main(void)
{
    printf("=== 関数ポインタ配列の活用 ===\n\n");

    /* 1. 計算機システム */
    printf("=== 計算機システム ===\n");

    /* 関数ポインタ配列の定義 */
    double (*operations[])(double, double) = {
        add_operation, /* インデックス0: 加算 */
        sub_operation, /* インデックス1: 減算 */
        mul_operation, /* インデックス2: 乗算 */
        div_operation  /* インデックス3: 除算 */
    };

    const char *op_names[] = {"加算", "減算", "乗算", "除算"};
    const char *op_symbols[] = {"+", "-", "*", "/"};
    int num_ops = sizeof(operations) / sizeof(operations[0]);
    double a = 15.0, b = 4.0;
    int i;

    printf("数値: a = %.1f, b = %.1f\n", a, b);

    /* 全ての演算を実行 */
    for (i = 0; i < num_ops; i++)
    {
        double result = operations[i](a, b);
        printf("%s (%s): %.1f %s %.1f = %.2f\n",
               op_names[i], op_symbols[i], a, op_symbols[i], b, result);
    }

    /* 特定の演算のみ実行 */
    printf("\n特定の演算:\n");
    printf("乗算結果: %.2f\n", operations[2](a, b)); /* mul_operation */
    printf("除算結果: %.2f\n", operations[3](a, b)); /* div_operation */

    /* 2. メニューシステム */
    printf("\n=== メニューシステム ===\n");

    /* メニュー項目の定義 */
    struct MenuItem menu[] = {
        {"プロフィール", show_profile},
        {"設定", show_settings},
        {"ヘルプ", show_help},
        {"このアプリについて", show_about},
        {"終了", exit_application}};

    int menu_size = sizeof(menu) / sizeof(menu[0]);

    printf("利用可能なメニュー項目:\n");
    for (i = 0; i < menu_size; i++)
    {
        printf("%d. %s\n", i + 1, menu[i].name);
    }

    /* メニュー項目の実行例 */
    printf("\nメニュー実行例:\n");
    menu[0].handler(); /* プロフィール表示 */
    menu[2].handler(); /* ヘルプ表示 */

    /* 3. ゲーム状態管理システム */
    printf("\n=== ゲーム状態管理システム ===\n");

    /* 状態処理関数配列 */
    void (*state_handlers[])(void) = {
        state_menu,    /* GAME_MENU */
        state_playing, /* GAME_PLAYING */
        state_paused,  /* GAME_PAUSED */
        state_settings /* GAME_SETTINGS */
    };

    const char *state_names[] = {
        "メニュー", "プレイ中", "一時停止", "設定"};

    GameState current_state;

    printf("各ゲーム状態の処理:\n");
    for (current_state = GAME_MENU; current_state < GAME_STATE_COUNT; current_state++)
    {
        printf("\n現在の状態: %s\n", state_names[current_state]);
        state_handlers[current_state]();
    }

    /* 4. 動的な状態遷移 */
    printf("\n=== 動的な状態遷移 ===\n");

    current_state = GAME_MENU;
    printf("初期状態: %s\n", state_names[current_state]);
    state_handlers[current_state]();

    /* 状態遷移の例 */
    current_state = GAME_PLAYING;
    printf("\n状態遷移: %s\n", state_names[current_state]);
    state_handlers[current_state]();

    current_state = GAME_PAUSED;
    printf("\n状態遷移: %s\n", state_names[current_state]);
    state_handlers[current_state]();

    /* 5. 文字変換システム */
    printf("\n=== 文字変換システム ===\n");

    /* 変換関数配列 */
    int (*transforms[])(int) = {
        to_upper_case,
        to_lower_case,
        rot13_transform,
        reverse_case};

    const char *transform_names[] = {
        "大文字変換",
        "小文字変換",
        "ROT13暗号",
        "大小文字反転"};

    int num_transforms = sizeof(transforms) / sizeof(transforms[0]);
    char original[] = "Hello World!";
    char test_str[50];

    printf("元の文字列: '%s'\n", original);

    /* 各変換を適用 */
    for (i = 0; i < num_transforms; i++)
    {
        strcpy(test_str, original);
        apply_transform(test_str, transforms[i]);
        printf("%s: '%s'\n", transform_names[i], test_str);
    }

    /* 6. 複数の数値に同じ演算を適用 */
    printf("\n=== 複数数値への演算適用 ===\n");

    double numbers[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    double results[5];
    int numbers_size = sizeof(numbers) / sizeof(numbers[0]);

    print_double_array(numbers, numbers_size, "元の配列");

    /* 各演算を全ての数値ペア (numbers[i], 2.0) に適用 */
    for (i = 0; i < num_ops; i++)
    {
        int j;
        for (j = 0; j < numbers_size; j++)
        {
            results[j] = operations[i](numbers[j], 2.0);
        }
        printf("%s (x, 2.0): ", op_names[i]);
        print_double_array(results, numbers_size, "結果");
    }

    /* 7. 条件付き関数実行 */
    printf("\n=== 条件付き関数実行 ===\n");

    printf("演算インデックス指定実行:\n");
    int op_index = 2; /* 乗算 */
    if (op_index >= 0 && op_index < num_ops)
    {
        double result = operations[op_index](10.0, 3.0);
        printf("%s: 10.0 %s 3.0 = %.2f\n",
               op_names[op_index], op_symbols[op_index], result);
    }

    /* 複数のメニュー項目を一度に実行 */
    printf("\n複数メニュー項目の実行:\n");
    int menu_indices[] = {1, 3}; /* 設定, このアプリについて */
    int indices_count = sizeof(menu_indices) / sizeof(menu_indices[0]);

    for (i = 0; i < indices_count; i++)
    {
        int idx = menu_indices[i];
        if (idx >= 0 && idx < menu_size)
        {
            printf("\n[%s] 実行:\n", menu[idx].name);
            menu[idx].handler();
        }
    }

    printf("\n=== 関数ポインタ配列デモ完了 ===\n");

    return 0;
}
