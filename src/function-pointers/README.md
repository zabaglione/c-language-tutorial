# 関数ポインタ

## 対応C規格

- **主要対象:** C90
- **学習内容:** 関数ポインタの基本、関数ポインタ配列、コールバック関数、高階関数の実装

## 学習目標
この章を完了すると、以下のことができるようになります。

- 関数ポインタの概念を理解し、適切に宣言・使用できる
- 関数ポインタを引数として渡す関数を作成できる
- 関数ポインタ配列を使った効率的なプログラムを書ける
- コールバック関数の仕組みを理解し、実装できる
- より柔軟で拡張性のあるプログラム設計ができる

## 概要と詳細

### 関数ポインタとは？

関数ポインタは、関数のアドレスを格納する変数です。関数も実際にはメモリ上の特定の場所に配置されており、その場所を指すポインタを作ることができます。

#### 日常生活での関数ポインタ
関数ポインタを理解するために、身近な例を考えてみましょう。

1. **リモコンのボタン**

   - ボタン = 関数ポインタ
   - ボタンを押す = 関数を実行
   - 設定でボタンの機能を変更 = 関数ポインタの値を変更

2. **電話の短縮ダイヤル**

   - 短縮番号1 = 関数ポインタ
   - 番号1を押す = 関数を呼び出す
   - 登録先を変更 = 関数ポインタを別の関数に変更

3. **イベントハンドラ**

   - ボタンクリック時の処理 = 関数ポインタ
   - クリックイベント = 関数の呼び出し
   - 処理を変更 = 別の関数を割り当て

#### なぜ関数ポインタが必要なの？

1. **柔軟性**: 実行時に呼び出す関数を変更できる
2. **再利用性**: 同じコードで異なる処理を実行できる
3. **拡張性**: 新しい機能を簡単に追加できる
4. **効率性**: switch文の代わりに関数ポインタ配列を使用
5. **コールバック**: 他の関数に処理を委譲できる

### 関数ポインタの基本概念

#### 関数ポインタの宣言

```c
戻り値の型 (*ポインタ名)(引数リスト);
```

#### 基本的な例

```c
/* 関数の定義 */
int add(int a, int b)
{
    return a + b;
}

int multiply(int a, int b)
{
    return a * b;
}

int main(void)
{
    /* 関数ポインタの宣言 */
    int (*operation)(int, int);
    
    /* 関数ポインタに関数を代入 */
    operation = add;
    printf("5 + 3 = %d\n", operation(5, 3));
    
    operation = multiply;
    printf("5 * 3 = %d\n", operation(5, 3));
    
    return 0;
}
```

### 関数ポインタの様々な形式

#### 引数なし・戻り値なしの関数ポインタ

```c
void (*func_ptr)(void);

void hello(void)
{
    printf("Hello, World!\n");
}

func_ptr = hello;
func_ptr();  /* hello()と同じ */
```

#### 複雑な引数を持つ関数ポインタ

```c
/* 文字列を引数に取る関数ポインタ */
void (*string_func)(const char *);

void print_upper(const char *str)
{
    /* 文字列を大文字で出力 */
    /* 実装は省略 */
}

string_func = print_upper;
string_func("hello");
```

#### 関数ポインタを返す関数

```c
/* 関数ポインタを返す関数 */
int (*get_operation(int choice))(int, int)
{
    if (choice == 1) {
        return add;
    } else {
        return multiply;
    }
}

/* 使用例 */
int (*op)(int, int) = get_operation(1);
int result = op(10, 20);
```

### 関数ポインタ配列

#### 基本的な関数ポインタ配列

```c
int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }
int multiply(int a, int b) { return a * b; }
int divide(int a, int b) { return a / b; }

/* 関数ポインタ配列 */
int (*operations[4])(int, int) = {add, subtract, multiply, divide};

/* 使用例 */
int a = 10, b = 5;
int i;

for (i = 0; i < 4; i++) {
    printf("結果: %d\n", operations[i](a, b));
}
```

#### 関数ポインタ配列を使った計算機

```c
typedef struct {
    char symbol;
    int (*func)(int, int);
    char *name;
} Calculator;

Calculator calc[] = {
    {'+', add, "加算"},
    {'-', subtract, "減算"},
    {'*', multiply, "乗算"},
    {'/', divide, "除算"}
};

/* 操作の検索と実行 */
int execute_operation(char op, int a, int b)
{
    int i;
    int size = sizeof(calc) / sizeof(calc[0]);
    
    for (i = 0; i < size; i++) {
        if (calc[i].symbol == op) {
            return calc[i].func(a, b);
        }
    }
    return 0;  /* 無効な操作 */
}
```

### コールバック関数

#### コールバック関数の概念
コールバック関数は、他の関数に引数として渡される関数です。呼び出される側が適切なタイミングで「呼び戻す（コールバック）」ことからこの名前が付いています。

#### 基本的なコールバック関数

```c
/* コールバック関数の型定義 */
typedef void (*callback_t)(int);

/* コールバック関数の例 */
void print_result(int result)
{
    printf("結果: %d\n", result);
}

void log_result(int result)
{
    printf("ログ: 計算結果は %d です\n", result);
}

/* コールバック関数を受け取る関数 */
void process_data(int data, callback_t callback)
{
    int result = data * 2;  /* 何らかの処理 */
    callback(result);       /* コールバック関数を呼び出し */
}

/* 使用例 */
process_data(10, print_result);  /* 結果: 20 */
process_data(15, log_result);    /* ログ: 計算結果は 30 です */
```

#### 配列処理でのコールバック関数

```c
/* 配列の各要素に対して処理を行う関数 */
void array_foreach(int *arr, int size, void (*callback)(int*, int))
{
    int i;
    for (i = 0; i < size; i++) {
        callback(&arr[i], i);
    }
}

/* コールバック関数の例 */
void double_value(int *value, int index)
{
    *value *= 2;
    printf("要素%d: %d\n", index, *value);
}

void square_value(int *value, int index)
{
    *value *= *value;
    printf("要素%d: %d\n", index, *value);
}

/* 使用例 */
int numbers[] = {1, 2, 3, 4, 5};
array_foreach(numbers, 5, double_value);   /* 各要素を2倍 */
array_foreach(numbers, 5, square_value);   /* 各要素を2乗 */
```

### より高度な関数ポインタ

#### 関数ポインタの構造体

```c
typedef struct {
    char *name;
    int (*init)(void);
    void (*process)(int);
    void (*cleanup)(void);
} Module;

/* モジュールの実装例 */
int module_a_init(void) { printf("Module A 初期化\n"); return 0; }
void module_a_process(int data) { printf("Module A: %d を処理\n", data); }
void module_a_cleanup(void) { printf("Module A クリーンアップ\n"); }

Module modules[] = {
    {"ModuleA", module_a_init, module_a_process, module_a_cleanup},
    /* 他のモジュールも追加可能 */
};

/* モジュールの実行 */
void run_module(Module *mod, int data)
{
    if (mod->init() == 0) {
        mod->process(data);
        mod->cleanup();
    }
}
```

#### 関数ポインタチェーン

```c
typedef struct filter {
    int (*process)(int);
    struct filter *next;
} Filter;

/* フィルター関数の例 */
int double_filter(int x) { return x * 2; }
int add_ten_filter(int x) { return x + 10; }
int square_filter(int x) { return x * x; }

/* フィルターチェーンの実行 */
int apply_filters(int input, Filter *chain)
{
    int result = input;
    Filter *current = chain;
    
    while (current != NULL) {
        result = current->process(result);
        current = current->next;
    }
    
    return result;
}

/* フィルターチェーンの構築 */
Filter filter3 = {square_filter, NULL};
Filter filter2 = {add_ten_filter, &filter3};
Filter filter1 = {double_filter, &filter2};

/* 使用例: 5 -> 10 -> 20 -> 400 */
int result = apply_filters(5, &filter1);
```

### qsort()関数との組み合わせ

#### 標準ライブラリのqsort()

```c
#include <stdlib.h>

/* 比較関数の例 */
int compare_int(const void *a, const void *b)
{
    int ia = *(const int*)a;
    int ib = *(const int*)b;
    return (ia > ib) - (ia < ib);
}

int compare_int_desc(const void *a, const void *b)
{
    return compare_int(b, a);  /* 降順 */
}

/* 使用例 */
int numbers[] = {5, 2, 8, 1, 9, 3};
int size = sizeof(numbers) / sizeof(numbers[0]);

qsort(numbers, size, sizeof(int), compare_int);      /* 昇順 */
qsort(numbers, size, sizeof(int), compare_int_desc); /* 降順 */
```

#### 文字列の比較関数

```c
int compare_string(const void *a, const void *b)
{
    return strcmp(*(const char**)a, *(const char**)b);
}

/* 文字列配列のソート */
const char *names[] = {"Alice", "Bob", "Charlie", "David"};
int name_count = sizeof(names) / sizeof(names[0]);

qsort(names, name_count, sizeof(char*), compare_string);
```

### 実用的な応用例

#### イベントシステム

```c
#define MAX_EVENTS 10

typedef struct {
    int event_type;
    void (*handler)(int);
} EventHandler;

EventHandler event_handlers[MAX_EVENTS];
int handler_count = 0;

/* イベントハンドラの登録 */
void register_event_handler(int event_type, void (*handler)(int))
{
    if (handler_count < MAX_EVENTS) {
        event_handlers[handler_count].event_type = event_type;
        event_handlers[handler_count].handler = handler;
        handler_count++;
    }
}

/* イベントの発生 */
void trigger_event(int event_type, int data)
{
    int i;
    for (i = 0; i < handler_count; i++) {
        if (event_handlers[i].event_type == event_type) {
            event_handlers[i].handler(data);
        }
    }
}
```

#### プラグインシステム

```c
typedef struct {
    char *name;
    char *version;
    int (*init)(void);
    void (*execute)(const char*);
    void (*shutdown)(void);
} Plugin;

/* プラグインの管理 */
Plugin *plugins[MAX_PLUGINS];
int plugin_count = 0;

int load_plugin(Plugin *plugin)
{
    if (plugin->init() == 0) {
        plugins[plugin_count++] = plugin;
        return 0;
    }
    return -1;
}

void execute_all_plugins(const char *command)
{
    int i;
    for (i = 0; i < plugin_count; i++) {
        plugins[i]->execute(command);
    }
}
```

### よくある間違いとデバッグ

#### 1. 関数ポインタの間違った宣言
**問題:** 括弧の位置が間違っている

```c
int *func(int, int);     /* 関数（ポインタを返す） */
int (*func)(int, int);   /* 関数ポインタ（正しい） */
```

#### 2. NULLポインタの呼び出し
**問題:** 未初期化の関数ポインタを呼び出す

```c
int (*func)(int, int);
int result = func(5, 3);  /* 危険！未初期化 */
```

**対策:**

```c
int (*func)(int, int) = NULL;
if (func != NULL) {
    int result = func(5, 3);
}
```

#### 3. 関数の型の不一致
**問題:** 関数ポインタの型と実際の関数の型が異なる

```c
int add(int a, int b) { return a + b; }
void (*func)(int, int) = add;  /* 戻り値の型が違う */
```

#### 4. 関数ポインタ配列の初期化ミス
**問題:** 配列のサイズと関数の数が一致しない

```c
int (*ops[3])(int, int) = {add, subtract, multiply, divide};  /* 4つの関数 */
```

### パフォーマンスの考慮事項

#### 関数ポインタ呼び出しのオーバーヘッド

- 直接関数呼び出しより若干遅い
- 分岐予測が困難な場合がある
- ただし、柔軟性の利益の方が大きい場合が多い

#### 最適化のヒント

- 頻繁に呼び出される関数ポインタはローカル変数に格納
- コンパイラの最適化オプションを活用
- プロファイリングでボトルネックを特定

## 実例コード
完全な実装例は以下のファイルを参照してください。

### 基本的な関数ポインタ

- [function_pointer_basics.c](examples/function_pointer_basics.c) - C90準拠版
- [function_pointer_basics_c99.c](examples/function_pointer_basics_c99.c) - C99準拠版

### 関数ポインタ配列と計算機

- [calculator.c](examples/calculator.c) - C90準拠版
- [calculator_c99.c](examples/calculator_c99.c) - C99準拠版

### コールバック関数とイベントシステム

- [callback_system.c](examples/callback_system.c) - C90準拠版
- [callback_system_c99.c](examples/callback_system_c99.c) - C99準拠版

## コンパイル方法

### 基本的なコンパイル（C90準拠）

```bash
gcc -std=c90 -Wall -Wextra -pedantic function_pointer_basics.c -o function_pointer_basics
```

### Makefileを使用した場合

```bash
# 全てのプログラムをコンパイル
make all
# 特定のプログラムをコンパイル
make calculator
# C99版をコンパイル
make calculator_c99
# プログラムを実行
make run-all
# クリーンアップ
make clean
```

## 学習フローとコンパイル方法

### 推奨学習順序

1. **理論学習**: README.mdで基本概念を理解
2. **サンプルコード**: examples/の基本例を確認
3. **演習課題**: exercises/README.mdで課題を確認
4. **実装練習**: solutions/の解答例を参考に自分で実装

### 学習のコツ

1. **段階的理解**: 基本→配列→コールバック→高度な応用の順で学習
2. **実用例の実装**: 計算機、イベントシステムなどを実際に作成
3. **デバッグ技術**: 関数ポインタの値をprintfで確認
4. **パターンの習得**: よくある設計パターンを覚える

## 実践的な応用分野

### システムプログラミング

- デバイスドライバのハンドラ
- 割り込み処理関数
- システムコールハンドラ

### GUI プログラミング

- イベントハンドラ
- ボタンのクリック処理
- メニュー項目の処理

### ゲーム開発

- ステートマシン
- アニメーション制御
- 入力処理

### 組み込みシステム

- タイマー割り込み処理
- センサーデータ処理
- 通信プロトコル処理

## 次の章へ
[第13章: 複数ファイル・発展技術](../advanced/README.md)

## 参考資料

- examples/ - 実装例（C90、C99両対応）
- exercises/ - 演習問題
- solutions/ - 解答例
- [C標準ライブラリリファレンス](https://en.cppreference.com/w/c)
- [関数ポインタ設計パターン](https://stackoverflow.com/questions/tagged/c+function-pointers)