# 第12章 関数ポインタ

##  対応C規格
- **主要対象:** C90
- **学習内容:** 関数ポインタの基本、コールバック関数、関数ポインタ配列、動的な関数呼び出し

##  学習目標

この章を完了すると、以下のことができるようになります：

- 関数ポインタの基本概念を理解する
- 関数ポインタの宣言と初期化ができる
- コールバック関数を実装できる
- 関数ポインタ配列を活用できる
- 動的な関数選択システムを作成できる

##  理論解説

### 関数ポインタの基本概念 

関数ポインタは関数のアドレスを格納するポインタです。これにより、実行時に呼び出す関数を動的に決定できます。

#### 関数ポインタの宣言

```c
#include <stdio.h>

/* 通常の関数 */
int add(int a, int b)
{

    return a + b;


int subtract(int a, int b)
{

    return a - b;


int main(void)
{

    /* 関数ポインタの宣言 */
    int (*operation)(int, int);
    
    /* 関数ポインタに関数のアドレスを代入 */
    operation = add;  /* または &add */
    
    /* 関数ポインタを通じて関数を呼び出し */
    printf("addition: %d\n", operation(, ));
    
    /* 別の関数を指すように変更 */
    operation = subtract;
    printf("subtraction: %d\n", operation(, ));
    
    return ;

```

#### 関数ポインタの基本文法

```c
#include <stdio.h>

/* さまざまな関数 */
void greet(void)
{

    printf("こんにちは！n");


int multiply(int x, int y)
{

    return x * y;


double divide(double a, double b)

    if (b != .) 
        return a / b;
    
    return .;


int main(void)
{

    /* さまざまな関数ポインタの宣言 */
    void (*greeting_fnc)(void);           /* 引数なし、戻り値なし */
    int (*math_fnc)(int, int);            /* int引数2つ、int戻り値 */
    double (*calc_fnc)(double, double);   /* double引数2つ、double戻り値 */
    
    /* 関数ポインタの初期化 */
    greeting_fnc = greet;
    math_fnc = multiply;
    calc_fnc = divide;
    
    /* 関数ポインタを使った呼び出し */
    greeting_fnc();                       /* greet()を呼び出し */
    printf("乗算: %d\n", math_fnc(, )); /* multiply(, )を呼び出し */
    printf("除算: %.fn", calc_fnc(., .)); /* divide(., .)を呼び出し */
    
    /* 2つの異なる呼び出し方法 */
    printf("直接呼び出し: %d\n", (*math_fnc)(, ));  /* (*ptr)(args) */
    printf("間接呼び出し: %d\n", math_fnc(, ));     /* ptr(args) */
    
    return ;

```

### 関数ポインタの実践的な使用 

#### 計算機システム

```c
#include <stdio.h>

/* 演算関数群 */
double add_op(double a, double b)  return a + b; 
double sb_op(double a, double b)  return a - b; 
double ml_op(double a, double b)  return a * b; 
double div_op(double a, double b) 

    if (b != .) return a / b;
    printf("エラー: ゼロ除算n");
    return .;


/* 演算を実行する関数 */
double calculate(double a, double b, double (*operation)(double, double))

    return operation(a, b);


/* 演算子に基づいて関数を選択 */
double (*get_operation(char op))(double, double)

    switch (op) 
        case '+': return add_op;
        case '-': return sb_op;
        case '*': return ml_op;
        case '/': return div_op;
        default:  return NULL;
    


int main(void)
{

    double num1 = 20.0, num2 = 5.0;
    char operators[] = {'+', '-', '*', '/'};
    const char* op_names[] = {"加算", "減算", "乗算", "除算"};
    int i;
    
    printf("数値1: %.1f, 数値2: %.1f\n\n", num1, num2);
    
    /* すべての演算を実行 */
    for (i = 0; i < 4; i++) 
    {
        double (*op_func)(double, double) = get_operation(operators[i]);
        if (op_func != NULL) 
        {
            double result = calculate(num1, num2, op_func);
            printf("%s (%c): %.2f\n", op_names[i], operators[i], result);
        }
    }
    
    return 0;

```

#### 動的メニューシステム

```c
#include <stdio.h>

/* メニュー項目の処理関数 */
void show_profile(void)
{

    printf("=== プロフィール表示 ===n");
    printf("名前: 田中太郎n");
    printf("年齢: 歳n");
    printf("職業: エンジニアnn");


void show_settings(void)
{

    printf("=== 設定画面 ===n");
    printf("言語: 日本語n");
    printf("テーマ: ダークn");
    printf("通知: ONnn");


void show_help(void)
{

    printf("=== ヘルプ ===n");
    printf("このアプリケーションの使用方法:n");
    printf(". メニューから項目を選択n");
    printf(". 処理が実行されますnn");


void exit_app(void)
{

    printf("アプリケーションを終了します。n");


/* メニュー項目の構造体 */
strct MenuItem 
    char name[];
    void (*handler)(void);  /* 関数ポインタ */
;

int main(void)
{

    /* メニュー項目の定義 */
    strct MenuItem men[] = 
        "プロフィール", show_profile,
        "設定", show_settings,
        "ヘルプ", show_help,
        "終了", exit_app
    ;
    
    int men_size = sizeof(men) / sizeof(men[]);
    int choice;
    int i;
    
    do 
        printf("=== メインメニュー ===n");
        for (i = ; i < men_size; i++) 
            printf("%d. %s\n", i + , men[i].name);
        
        printf("選択してください (-%d): ", men_size);
        
        if (scanf("%d", &choice) ==  && choice >=  && choice <= men_size) 
            printf("n");
            men[choice - ].handler();  /* 関数ポインタを使って実行 */
            
            if (choice == men_size)   /* 終了が選択された場合 */
                break;
            
         else 
            printf("無効な選択です。nn");
            /* 入力バッファをクリア */
            while (getchar() != 'n');
        
     while ();
    
    return ;

```

### コールバック関数 

コールバック関数は他の関数に引数として渡される関数です。

#### 配列処理のコールバック

```c
#include <stdio.h>

/* 配列の各要素に適用する関数群 */
int square(int x)  return x * x; 
int cube(int x)  return x * x * x; 
int double_vale(int x)  return x * ; 
int increment(int x)  return x + ; 

/* 配列の各要素に関数を適用 */
void apply_to_array(int arr[], int size, int (*fnc)(int))

    int i;
    for (i = ; i < size; i++) 
        arr[i] = fnc(arr[i]);
    


/* 配列を表示する関数 */
void print_array(int arr[], int size, const char* label)
{

    int i;
    printf("%s: ", label);
    for (i = ; i < size; i++) 
        printf("%d ", arr[i]);
    
    printf("n");


int main(void)
{

    int numbers[] = , , , , ;
    int size = sizeof(numbers) / sizeof(numbers[]);
    int temp[];
    int i;
    
    print_array(numbers, size, "元の配列");
    
    /* 乗を適用 */
    for (i = ; i < size; i++) temp[i] = numbers[i];
    apply_to_array(temp, size, square);
    print_array(temp, size, "乗後");
    
    /* 乗を適用 */
    for (i = ; i < size; i++) temp[i] = numbers[i];
    apply_to_array(temp, size, cube);
    print_array(temp, size, "乗後");
    
    /* 倍を適用 */
    for (i = ; i < size; i++) temp[i] = numbers[i];
    apply_to_array(temp, size, double_vale);
    print_array(temp, size, "倍後");
    
    /* インクリメントを適用 */
    for (i = ; i < size; i++) temp[i] = numbers[i];
    apply_to_array(temp, size, increment);
    print_array(temp, size, "インクリメント後");
    
    return ;

```

#### ソートのコールバック（比較関数）

```c
#include <stdio.h>
#include <string.h>

/* 比較関数の型定義 */
typedef int (*compare_fnc_t)(const void *a, const void *b);

/* 整数の比較関数 */
int compare_int_asc(const void *a, const void *b)
{

    int ia = *(const int*)a;
    int ib = *(const int*)b;
    return (ia > ib) - (ia < ib);  /* 昇順 */


int compare_int_desc(const void *a, const void *b)
{

    int ia = *(const int*)a;
    int ib = *(const int*)b;
    return (ib > ia) - (ib < ia);  /* 降順 */


/* 簡単なバブルソート（コールバック版） */
void bbble_sort(void *base, size_t num, size_t size, 
                 int (*compare)(const void *, const void *))

    char *arr = (char*)base;
    char *temp = malloc(size);
    size_t i, j;
    
    if (temp == NULL) return;
    
    for (i = ; i < num - ; i++) 
        for (j = ; j < num -  - i; j++) 
            void *elem = arr + j * size;
            void *elem = arr + (j + ) * size;
            
            if (compare(elem, elem) > ) 
                /* 要素を交換 */
                memcpy(temp, elem, size);
                memcpy(elem, elem, size);
                memcpy(elem, temp, size);
            
        
    
    
    free(temp);


/* 配列を表示 */
void print_int_array(int arr[], int size, const char* label)
{

    int i;
    printf("%s: ", label);
    for (i = ; i < size; i++) 
        printf("%d ", arr[i]);
    
    printf("n");


int main(void)
{

    int numbers[] = , , , , , , 9, ;
    int size = sizeof(numbers) / sizeof(numbers[]);
    int temp[];
    int i;
    
    print_int_array(numbers, size, "元の配列");
    
    /* 昇順ソート */
    for (i = ; i < size; i++) temp[i] = numbers[i];
    bbble_sort(temp, size, sizeof(int), compare_int_asc);
    print_int_array(temp, size, "昇順ソート");
    
    /* 降順ソート */
    for (i = ; i < size; i++) temp[i] = numbers[i];
    bbble_sort(temp, size, sizeof(int), compare_int_desc);
    print_int_array(temp, size, "降順ソート");
    
    return ;

```

### 関数ポインタ配列 

関数ポインタの配列を使って、複数の関数を効率的に管理できます。

#### 演算関数配列

```c
#include <stdio.h>

/* 演算関数群 */
int add_func(int a, int b) { return a + b; }
int sub_func(int a, int b) { return a - b; }
int mul_func(int a, int b) { return a * b; }
int div_func(int a, int b) { return b != 0 ? a / b : 0; }
int mod_func(int a, int b) { return b != 0 ? a % b : 0; }

int main(void)
{
    /* 関数ポインタ配列の宣言と初期化 */
    int (*operations[])(int, int) = 
    {
        add_func,  /* インデックス0: 加算 */
        sub_func,  /* インデックス1: 減算 */
        mul_func,  /* インデックス2: 乗算 */
        div_func,  /* インデックス3: 除算 */
        mod_func   /* インデックス4: 剰余 */
    };
    
    const char* op_names[] = {"加算", "減算", "乗算", "除算", "剰余"};
    const char* op_symbols[] = {"+", "-", "*", "/", "%"};
    int num_ops = sizeof(operations) / sizeof(operations[0]);
    int a = 20, b = 5;
    int i;
    
    printf("数値: a = %d, b = %d\n\n", a, b);
    
    /* すべての演算を実行 */
    for (i = 0; i < num_ops; i++) 
    {
        int result = operations[i](a, b);
        printf("%s (%s): %d %s %d = %d\n", 
               op_names[i], op_symbols[i], a, op_symbols[i], b, result);
    }
    
    /* 特定の演算だけ実行 */
    printf("\n特定の演算:\n");
    printf("乗算結果: %d\n", operations[2](a, b));  /* mul_func */
    printf("除算結果: %d\n", operations[3](a, b));  /* div_func */
    
    return 0;
}
```

#### 状態機械（ステートマシン）

```c
#include <stdio.h>

/* 状態の定義 */
typedef enum 
{
    STATE_IDLE,
    STATE_RUNNING,
    STATE_PAUSED,
    STATE_STOPPED,
    STATE_COUNT
} State;

/* 状態処理関数の宣言 */
void handle_idle(void);
void handle_running(void);
void handle_paused(void);
void handle_stopped(void);

/* 現在の状態 */
static State current_state = STATE_IDLE;

/* 状態処理関数配列 */
void (*state_handlers[])(void) = 
{
    handle_idle,     /* STATE_IDLE */
    handle_running,  /* STATE_RUNNING */
    handle_paused,   /* STATE_PAUSED */
    handle_stopped   /* STATE_STOPPED */
};

const char* state_names[] = 
{
    "待機中", "実行中", "一時停止", "停止中"
};

/* 各状態の処理関数 */
void handle_idle(void)
{
    printf("[待機中] システムが待機状態です\n");
    printf("  利用可能なアクション: 開始(s)\n");
}

void handle_running(void)
{
    printf("[実行中] システムが動作しています\n");
    printf("  利用可能なアクション: 一時停止(p), 停止(q)\n");
}

void handle_paused(void)
{
    printf("[一時停止] システムが一時停止中です\n");
    printf("  利用可能なアクション: 再開(r), 停止(q)\n");
}

void handle_stopped(void)
{
    printf("[停止中] システムが停止しました\n");
    printf("  利用可能なアクション: リセット(reset)\n");
}

/* 状態遷移関数 */
void transition_to_state(State new_state)
{
    if (new_state >= 0 && new_state < STATE_COUNT) 
    {
        printf("状態遷移: %s -> %s\n", 
               state_names[current_state], state_names[new_state]);
        current_state = new_state;
    }
}

/* 現在の状態を処理 */
void process_current_state(void)
{
    if (current_state >= 0 && current_state < STATE_COUNT) 
    {
        state_handlers[current_state]();
    }
}

int main(void)
{
    char command[10];
    
    printf("=== ステートマシンデモ ===\n");
    printf("コマンド: s(start), p(pause), r(resume), q(quit), reset\n\n");
    
    while (1) 
    {
        process_current_state();
        printf("\nコマンドを入力してください: ");
        
        if (scanf("%9s", command) == 1) 
        {
            if (strcmp(command, "s") == 0 && current_state == STATE_IDLE) 
            {
                transition_to_state(STATE_RUNNING);
            }
            else if (strcmp(command, "p") == 0 && current_state == STATE_RUNNING) 
            {
                transition_to_state(STATE_PAUSED);
            }
            else if (strcmp(command, "r") == 0 && current_state == STATE_PAUSED) 
            {
                transition_to_state(STATE_RUNNING);
            }
            else if (strcmp(command, "q") == 0) 
            {
                transition_to_state(STATE_STOPPED);
            }
            else if (strcmp(command, "reset") == 0) 
            {
                transition_to_state(STATE_IDLE);
            }
            else if (strcmp(command, "exit") == 0) 
            {
                printf("プログラムを終了します\n");
                break;
            }
            else 
            {
                printf("無効なコマンドまたは現在の状態では実行できません\n");
            }
        }
        printf("\n");
    }
    
    return 0;
}
```

### 高度な関数ポインタ活用

#### プラグインシステム

```c
#include <stdio.h>
#include <string.h>

/* プラグインインターフェース */
typedef struct 
{
    char name[50];
    char version[10];
    void (*init)(void);
    void (*execute)(void);
    void (*cleanup)(void);
} Plugin;

/* プラグイン: ログ出力 */
void log_init(void) { printf("ログプラグイン初期化\n"); }
void log_execute(void) { printf("ログファイルに出力中...\n"); }
void log_cleanup(void) { printf("ログプラグイン終了処理\n"); }

/* プラグイン: データベース接続 */
void db_init(void) { printf("データベースプラグイン初期化\n"); }
void db_execute(void) { printf("データベースに接続中...\n"); }
void db_cleanup(void) { printf("データベース接続終了\n"); }

/* プラグイン: ネットワーク通信 */
void net_init(void) { printf("ネットワークプラグイン初期化\n"); }
void net_execute(void) { printf("ネットワーク通信実行中...\n"); }
void net_cleanup(void) { printf("ネットワーク接続終了\n"); }

/* プラグインの登録 */
Plugin plugins[] = 
{
    {"LogPlugin", "1.0", log_init, log_execute, log_cleanup},
    {"DatabasePlugin", "2.0", db_init, db_execute, db_cleanup},
    {"NetworkPlugin", "1.5", net_init, net_execute, net_cleanup}
};

int plugin_count = sizeof(plugins) / sizeof(plugins[0]);

/* プラグイン管理システム */
void load_plugins(void)
{
    int i;
    printf("=== プラグイン読み込み ===\n");
    for (i = 0; i < plugin_count; i++) 
    {
        printf("プラグイン: %s (v%s)\n", plugins[i].name, plugins[i].version);
        plugins[i].init();
    }
    printf("\n");
}

void execute_plugins(void)
{
    int i;
    printf("=== プラグイン実行 ===\n");
    for (i = 0; i < plugin_count; i++) 
    {
        printf("[%s] ", plugins[i].name);
        plugins[i].execute();
    }
    printf("\n");
}

void unload_plugins(void)
{
    int i;
    printf("=== プラグイン終了処理 ===\n");
    for (i = 0; i < plugin_count; i++) 
    {
        printf("[%s] ", plugins[i].name);
        plugins[i].cleanup();
    }
    printf("\n");
}

/* 特定のプラグインを実行 */
void execute_plugin_by_name(const char* name)
{
    int i;
    for (i = 0; i < plugin_count; i++) 
    {
        if (strcmp(plugins[i].name, name) == 0) 
        {
            printf("プラグイン '%s' を実行:\n", name);
            plugins[i].execute();
            return;
        }
    }
    printf("プラグイン '%s' が見つかりません\n", name);
}

int main(void)
{
    load_plugins();
    execute_plugins();
    
    /* 特定のプラグインのみ実行 */
    execute_plugin_by_name("DatabasePlugin");
    execute_plugin_by_name("InvalidPlugin");
    
    unload_plugins();
    
    return 0;
}
```

#### イベントハンドラシステム

```c
#include <stdio.h>

/* イベントタイプ */
typedef enum 
{
    EVENT_CLICK,
    EVENT_KEYPRESS,
    EVENT_MOUSE_MOVE,
    EVENT_WINDOW_CLOSE,
    EVENT_TYPE_COUNT
} EventType;

/* イベントデータ */
typedef struct 
{
    EventType type;
    int x, y;      /* 座標 */
    int key_code;  /* キーコード */
    char message[100];
} Event;

/* イベントハンドラ関数の型 */
typedef void (*EventHandler)(const Event* event);

/* イベントハンドラ配列 */
EventHandler event_handlers[EVENT_TYPE_COUNT] = {NULL};

/* 各イベントのハンドラ実装 */
void handle_click(const Event* event)
{
    printf("クリックイベント: 座標(%d, %d) - %s\n", 
           event->x, event->y, event->message);
}

void handle_keypress(const Event* event)
{
    printf("キー押下イベント: キーコード %d - %s\n", 
           event->key_code, event->message);
}

void handle_mouse_move(const Event* event)
{
    printf("マウス移動イベント: 座標(%d, %d)\n", event->x, event->y);
}

void handle_window_close(const Event* event)
{
    printf("ウィンドウ閉じるイベント: %s\n", event->message);
}

/* イベントハンドラの登録 */
void register_event_handler(EventType type, EventHandler handler)
{
    if (type >= 0 && type < EVENT_TYPE_COUNT) 
    {
        event_handlers[type] = handler;
        printf("イベントハンドラ登録: タイプ %d\n", type);
    }
}

/* イベントの処理 */
void process_event(const Event* event)
{
    if (event->type >= 0 && event->type < EVENT_TYPE_COUNT && 
        event_handlers[event->type] != NULL) 
    {
        event_handlers[event->type](event);
    } 
    else 
    {
        printf("未処理のイベント: タイプ %d\n", event->type);
    }
}

/* イベントの作成補助関数 */
Event create_click_event(int x, int y, const char* msg)
{
    Event event = {EVENT_CLICK, x, y, 0, ""};
    strncpy(event.message, msg, sizeof(event.message) - 1);
    return event;
}

Event create_keypress_event(int key_code, const char* msg)
{
    Event event = {EVENT_KEYPRESS, 0, 0, key_code, ""};
    strncpy(event.message, msg, sizeof(event.message) - 1);
    return event;
}

int main(void)
{
    printf("=== イベントハンドラシステム ===\n\n");
    
    /* イベントハンドラを登録 */
    register_event_handler(EVENT_CLICK, handle_click);
    register_event_handler(EVENT_KEYPRESS, handle_keypress);
    register_event_handler(EVENT_MOUSE_MOVE, handle_mouse_move);
    register_event_handler(EVENT_WINDOW_CLOSE, handle_window_close);
    
    printf("\n=== イベント処理テスト ===\n");
    
    /* さまざまなイベントを生成・処理 */
    Event click_event = create_click_event(100, 200, "ボタンクリック");
    process_event(&click_event);
    
    Event key_event = create_keypress_event(65, "Aキー押下");
    process_event(&key_event);
    
    Event mouse_event = {EVENT_MOUSE_MOVE, 150, 300, 0, ""};
    process_event(&mouse_event);
    
    Event close_event = {EVENT_WINDOW_CLOSE, 0, 0, 0, "アプリケーション終了"};
    process_event(&close_event);
    
    /* 未登録のイベントタイプ */
    Event unknown_event = {99, 0, 0, 0, ""};
    process_event(&unknown_event);
    
    return 0;
}
```

### 関数ポインタのtypedef

複雑な関数ポインタの型を簡潔に書くためにtypedefを使用します。

```c
#include <stdio.h>

/* 関数ポインタの型定義 */
typedef int (*BinaryOperation)(int, int);
typedef void (*EventCallback)(int event_id, const char* message);
typedef double (*MathFunction)(double);

/* 演算関数 */
int add_nums(int a, int b) { return a + b; }
int mul_nums(int a, int b) { return a * b; }

/* イベントコールバック関数 */
void on_start(int id, const char* msg) 
{
    printf("開始イベント[%d]: %s\n", id, msg);
}

void on_stop(int id, const char* msg) 
{
    printf("停止イベント[%d]: %s\n", id, msg);
}

/* 数学関数 */
double square_root(double x) { return x * x; }   /* 簡易版 */
double absolute(double x) { return x < 0 ? -x : x; }

/* 関数を実行する汎用関数 */
int execute_binary_op(int a, int b, BinaryOperation op)
{
    return op(a, b);
}

void trigger_event(int id, const char* message, EventCallback callback)
{
    callback(id, message);
}

double apply_math_func(double value, MathFunction func)
{
    return func(value);
}

int main(void)
{
    /* 型定義を使った関数ポインタの使用 */
    BinaryOperation math_op;
    EventCallback event_handler;
    MathFunction math_func;
    
    printf("=== typedef を使った関数ポインタ ===\n\n");
    
    /* 数値演算 */
    math_op = add_nums;
    printf("加算: %d\n", execute_binary_op(10, 5, math_op));
    
    math_op = mul_nums;
    printf("乗算: %d\n", execute_binary_op(10, 5, math_op));
    
    /* イベント処理 */
    event_handler = on_start;
    trigger_event(1, "システム開始", event_handler);
    
    event_handler = on_stop;
    trigger_event(2, "システム終了", event_handler);
    
    /* 数学関数 */
    math_func = square_root;
    printf("二乗: %.2f\n", apply_math_func(5.0, math_func));
    
    math_func = absolute;
    printf("絶対値: %.2f\n", apply_math_func(-7.5, math_func));
    
    return 0;
}
```

## サンプルコード

### 関数ポインタの基本

- **C90版**: [examples/function_pointer_basic.c](examples/function_pointer_basic.c)
- **C99版**: [examples/function_pointer_basic_c99.c](examples/function_pointer_basic_c99.c)

関数ポインタの宣言、初期化、基本的な使用方法を学習します。

### コールバック関数

- **C90版**: [examples/callback_functions.c](examples/callback_functions.c)
- **C99版**: [examples/callback_functions_c99.c](examples/callback_functions_c99.c)

コールバック関数を使ったイベント処理システムを学習します。

### 関数ポインタ配列

- **C90版**: [examples/function_pointer_arrays.c](examples/function_pointer_arrays.c)
- **C99版**: [examples/function_pointer_arrays_c99.c](examples/function_pointer_arrays_c99.c)

関数ポインタ配列を使った動的な関数選択を学習します。

### コンパイルと実行

```bash
# examples ディレクトリに移動
cd examples

# C90準拠でコンパイル
gcc -std=c90 -Wall -Wextra -pedantic function_pointer_basic.c -o function_pointer_basic

# 実行
./function_pointer_basic
```

## 演習課題

### 基礎問題

1. **計算機の実装**
   - 四則演算の関数を作成し、関数ポインタを使って動的に演算を選択できる計算機を実装してください

2. **ソート比較関数**
   - 整数配列を昇順・降順でソートできるよう、比較関数を関数ポインタで渡すソート関数を実装してください

3. **メニューシステム**
   - 関数ポインタ配列を使って、複数の機能を持つメニューシステムを作成してください

### 応用問題

4. **データ変換システム**
   - さまざまなデータ変換関数（大文字変換、小文字変換など）を関数ポインタで管理するシステムを実装してください

5. **フィルタシステム**
   - 配列の要素をフィルタリングする関数を、条件を関数ポインタで渡して実装してください

6. **ゲームの状態管理**
   - ゲームの状態（メニュー、プレイ中、ポーズ、終了）を関数ポインタ配列で管理するシステムを作成してください

### 発展問題

7. **プラグインシステム**
   - 実行時に機能を追加できるプラグインシステムを関数ポインタで実装してください

8. **コマンドパターン**
   - コマンドパターンを関数ポインタで実装し、undo/redo機能付きのシステムを作成してください

9. **イベントドリブンシステム**
   - 複数のイベントタイプを処理できるイベントドリブンシステムを実装してください

## コンパイル方法

この章では以下のMakefileを使用してコンパイルができます：

```bash
# 全ての例題をコンパイル
make all

# 特定のプログラムをコンパイル
make function_pointer_basic

# 実行
make run

# クリーンアップ
make clean
```

## 規格による違い

### C90での制限事項
- 関数ポインタの型変換は明示的なキャストが必要
- 可変引数関数への関数ポインタは制限的

### C99以降の拡張
- より柔軟な関数ポインタの初期化
- inline関数への関数ポインタサポート改善

## よくある間違い

### 1. 関数ポインタの初期化忘れ

```c
/* NG: 初期化されていない関数ポインタ */
int (*func_ptr)(int, int);
int result = func_ptr(10, 5);  /* 未定義動作 */

/* OK: 適切な初期化 */
int (*func_ptr)(int, int) = add_function;
int result = func_ptr(10, 5);
```

### 2. 関数ポインタのNULLチェック不足

```c
/* NG: NULLチェックなし */
void execute_callback(void (*callback)(void))
{
    callback();  /* callbackがNULLの場合クラッシュ */
}

/* OK: NULLチェック */
void execute_callback(void (*callback)(void))
{
    if (callback != NULL) 
    {
        callback();
    }
}
```

### 3. 関数の戻り値型の不一致

```c
/* NG: 戻り値型が一致しない */
double divide_func(int a, int b) { return (double)a / b; }
int (*math_op)(int, int) = divide_func;  /* 型エラー */

/* OK: 戻り値型を一致させる */
int divide_func(int a, int b) { return a / b; }
int (*math_op)(int, int) = divide_func;
```

## 次の章へ

関数ポインタを理解したら、[複数ファイル・発展技術](../advanced/README.md) に進んでください。

## 参考資料

- [C言語関数ポインタリファレンス](https://ja.cppreference.com/w/c/language/pointer)
- [コールバック関数の設計パターン](https://en.wikipedia.org/wiki/Callback_(computer_programming))
- [関数ポインタの活用例](https://www.learn-c.org/en/Function_Pointers)
