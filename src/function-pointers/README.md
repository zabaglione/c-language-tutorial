# 関数ポインター

## 対応C規格

- **主要対象：** C90
- **学習内容：** 関数ポインターの基本、関数ポインター配列、コールバック関数、高階関数の実装

## 学習目標

この章を完了すると、以下のことができるようになります。

- 関数ポインターの概念を理解し、適切に宣言・使用できる
- 関数ポインターを引数として渡す関数を作成できる
- 関数ポインター配列を使った表駆動の分岐を書ける
- コールバック関数の仕組みを理解し、実装できる
- 互換性のある関数型を見分けられる

## 概要と詳細

### 関数ポインターとは

これまでの章で学んだポインターは、`int`型や構造体などの「データの場所（アドレス）」を記憶する変数でした。
実は、プログラムの中にある**関数（処理の手順）**も、実行時にはメモリ上の決まった場所に置かれています。
**関数ポインター**とは、その「関数の場所（アドレス）」を記憶しておくためのポインターです。

好きな機能を割り当てられるリモコンのボタンをイメージするとわかりやすいでしょう。
ボタンに「足し算」を割り当てておけば押したときに足し算が動き、「掛け算」に切り替えれば同じボタンを押すだけで掛け算が動きます。
関数ポインターが指している関数は、普通の関数呼び出しとまったく同じ書き方で呼び出せます。

#### 関数ポインターを使う場面

関数ポインターは、次のような場面で力を発揮します。

1. **実行時の選択**：戻り値や引数の形が同じ複数の関数から、プログラムの実行中に「どれを呼ぶか」を切り替えられます
2. **表駆動の分岐**：長い`if-else`や`switch`文を書く代わりに、「番号や記号」と「関数」を対応表（配列）にまとめてすっきり処理できます
3. **コールバック**：処理の途中で行う作業を、別の関数へ「引数」として渡して実行してもらいます

### 関数ポインターの基本概念

#### 関数ポインターの宣言

関数ポインターは、少し独特な形で宣言します。
ポインター名の前に`*`を付け、さらに丸括弧`()`で囲むのがポイントです。

```c
戻り値の型 (*ポインター名)(引数リスト);
```

たとえば、`int (*operation)(int, int);`は「`int`型の引数を2つ受け取り、`int`型の値を返す関数を指すポインター`operation`」という意味になります。
関数ポインターに代入できるのは、このように**戻り値の型と引数の型が一致する関数（互換性のある関数型）**だけです。

#### 基本的な例

次の例では、`add`関数と`multiply`関数を1つの関数ポインター`operation`に順番に代入して呼び出しています。
C言語では関数名をそのまま書くと関数のアドレスとして扱われるため、`operation = add;`のように代入できます。

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
    /* 関数ポインターの宣言 */
    int (*operation)(int, int);

    /* 関数ポインターに関数を代入 */
    operation = add;
    printf("5 + 3 = %d\n", operation(5, 3));

    operation = multiply;
    printf("5 * 3 = %d\n", operation(5, 3));

    return 0;
}
```

前半の`operation(5, 3)`では`add(5, 3)`が呼ばれて`8`になり、後半では`operation`の中身を`multiply`に入れ替えたため、`operation(5, 3)`が`multiply(5, 3)`として動いて`15`になります。

### 関数ポインターの宣言形式

関数の引数や戻り値の形に合わせて、関数ポインターの宣言も変わります。
代表的なパターンを3つ確認しましょう。

#### 引数なし・戻り値なしの関数ポインター

引数も戻り値もない関数（`void hello(void)`など）を指す場合は、戻り値と引数の両方に`void`と書きます。

```c
void (*func_ptr)(void);

void hello(void)
{
    printf("Hello, World!\n");
}

func_ptr = hello;
func_ptr();  /* hello()と同じ */
```

#### 複雑な引数を持つ関数ポインター

文字列（`const char *`）を引数に取る関数を指す場合は、引数リストの部分に`const char *`と書きます。
引数名（`str`など）は省略してもかまいません。

```c
/* 文字列を引数に取る関数ポインター */
void (*string_func)(const char *);

void print_upper(const char *str)
{
    /* 文字列を大文字で出力 */
    /* 実装は省略 */
}

string_func = print_upper;
string_func("hello");
```

#### 関数ポインターを返す関数

関数ポインターの宣言は記号が多くて読みにくくなりがちです。
特に「関数ポインターを戻り値として返す関数」をそのまま書くととても複雑になります。
そこで、`typedef`を使って関数ポインター型に短い別名（ここでは`operation_t`）を付けておくと、普通の型と同じようにすっきり書けます。

```c
typedef int (*operation_t)(int, int);

operation_t get_operation(int choice)
{
    if (choice == 1) {
        return add;
    } else {
        return multiply;
    }
}

/* 使用例 */
operation_t op = get_operation(1);
int result = op(10, 20);
```

上の例では、`get_operation(1)`が`add`関数を返すため、`op(10, 20)`を実行すると`30`が返ってきます。

### 関数ポインター配列

関数ポインターも、普通の変数と同じように**配列**に並べることができます。

#### 基本的な関数ポインター配列

次の例では、四則演算を行う4つの関数を`operations`という配列にまとめています。
`operations[0]`が`add`、`operations[1]`が`subtract`……というように、番号を指定するだけで対応する関数を呼び出せます。

```c
int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }
int multiply(int a, int b) { return a * b; }
int divide(int a, int b) { return a / b; }

/* 関数ポインター配列 */
int (*operations[4])(int, int) = {add, subtract, multiply, divide};

/* 使用例 */
int a = 10, b = 5;
int i;

for (i = 0; i < 4; i++) {
    printf("Result: %d\n", operations[i](a, b));
}
```

この例では割り算があるため、`b`が0でないことを前提としています。
実際のプログラムで除算を含む表を使う場合は、呼び出し前に割る数（除数）が0でないかを検査するか、関数側からエラーを返す設計が必要です。

#### 関数ポインター配列を使った計算機

構造体と関数ポインターを組み合わせると、「演算子の記号」「実行する関数」「操作の名前」を1セットにした対応表（テーブル）を作れます。
こうした書き方を**表駆動（テーブル駆動）**と呼びます。
新しい計算を増やしたいときも、表に1行追加するだけで済むのが大きな利点です。

```c
#include <stddef.h>

typedef struct {
    char symbol;
    int (*func)(int, int);
    const char *name;
} Calculator;

Calculator calc[] = {
    {'+', add, "add"},
    {'-', subtract, "subtract"},
    {'*', multiply, "multiply"},
    {'/', divide, "divide"}
};

/* 操作の検索と実行 */
int execute_operation(char op, int a, int b, int *result)
{
    size_t i;
    size_t size = sizeof(calc) / sizeof(calc[0]);

    if (result == NULL) {
        return 0;
    }

    for (i = 0; i < size; i++) {
        if (calc[i].symbol == op) {
            if (op == '/' && b == 0) {
                return 0;
            }
            *result = calc[i].func(a, b);
            return 1;
        }
    }
    return 0;
}
```

`execute_operation`関数は、`calc`配列の中から記号`op`に一致する要素を探し、見つかったらその要素の`func(a, b)`を呼び出して結果を`*result`に書き込みます。
割り算で`b == 0`のときや見つからなかったときは、失敗を表す`0`を返します。

### コールバック関数

#### コールバック関数の概念

**コールバック関数**とは、別の関数に引数として渡しておき、その関数の処理の途中で「呼び戻して（call back）」実行してもらう関数のことです。
また、このように関数を引数として受け取る関数のことを**高階関数**と呼ぶことがあります。

料理の手順にたとえると、「材料を切って炒めるところまでは共通の関数に任せ、最後の味付け（塩味にするか、カレー味にするか）のレシピだけをコールバック関数として渡す」ようなイメージです。

#### 基本的なコールバック関数

次の例では、`process_data`関数が「受け取った数を2倍にする」という共通の処理を行ったあと、引数で渡された`callback`関数を呼び出しています。
渡す関数を`print_result`にするか`log_result`にするかで、結果の表示方法だけを自由に切り替えられます。

```c
/* コールバック関数の型定義 */
typedef void (*callback_t)(int);

/* コールバック関数の例 */
void print_result(int result)
{
    printf("Result: %d\n", result);
}

void log_result(int result)
{
    printf("Log result: %d\n", result);
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

配列のすべての要素に順番に処理を行うとき、`for`ループの書き方は毎回同じになります。
そこで、`array_foreach`関数に「配列を順番にたどる役割」を任せ、「各要素に何をするか（2倍にする、2乗するなど）」だけをコールバック関数として渡せるようにしたのが次の例です。

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
    printf("Element %d: %d\n", index, *value);
}

void square_value(int *value, int index)
{
    *value *= *value;
    printf("Element %d: %d\n", index, *value);
}

/* 使用例 */
int numbers[] = {1, 2, 3, 4, 5};
array_foreach(numbers, 5, double_value);   /* 各要素を2倍 */
array_foreach(numbers, 5, square_value);   /* 各要素を2乗 */
```

1回目の`array_foreach`で`numbers`の中身が`{2, 4, 6, 8, 10}`に書き換わり、2回目の`array_foreach`でそれぞれ2乗されて`{4, 16, 36, 64, 100}`になります。

### より高度な関数ポインター

関数ポインターと構造体を組み合わせると、大きなプログラムをきれいに部品分けする設計ができるようになります。

#### 関数ポインターの構造体

プログラムの部品（**モジュール**）ごとに、「準備（`init`）」「メイン処理（`process`）」「後片付け（`cleanup`）」の3つの関数を1つの構造体にまとめておく方法です。
このように同じ形の構造体にそろえておけば、`run_module`関数はどんな種類のモジュールでもまったく同じ手順で動かすことができます。

```c
typedef struct {
    const char *name;
    int (*init)(void);
    void (*process)(int);
    void (*cleanup)(void);
} Module;

/* モジュールの実装例 */
int module_a_init(void) { printf("Module A init\n"); return 0; }
void module_a_process(int data) { printf("Module A data: %d\n", data); }
void module_a_cleanup(void) { printf("Module A cleanup\n"); }

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

#### 関数ポインターチェーン

前の章で学んだリンクリストと関数ポインターを組み合わせると、工場のベルトコンベアのようにデータを次々と加工していく仕組み（**フィルターチェーン**）を作れます。
下の例では、`5`という数字が「2倍（`10`）」→「10を足す（`20`）」→「2乗する（`400`）」という3つのフィルターを順番に通って変換されます。

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
int apply_filters(int input, const Filter *chain)
{
    int result = input;
    const Filter *current = chain;

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

C言語の標準ライブラリには、配列の中身を高速に並べ替えて（ソートして）くれる**`qsort`関数**が用意されています。
`qsort`関数は、`int`型でも`double`型でも文字列でも構造体でも並べ替えられるように作られているため、「2つの要素のどちらを前に置くか」を決める**比較関数**をコールバックとして渡す仕組みになっています。

比較関数は2つの要素への`const void *`型ポインター（どんな型のデータでも受け取れる汎用ポインター）を受け取り、次のルールで整数を返します。

- 第1引数の方が小さければ**負の数**（例：`-1`）
- 2つが等しければ**`0`**
- 第1引数の方が大きければ**正の数**（例：`1`）

次の例では、`(ia > ib) - (ia < ib)`という式を使って安全に`-1`、`0`、`1`を返しています（単純に`ia - ib`と書くと、非常に大きい数と小さい数の引き算で桁あふれが起きる場合があるためです）。

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

`compare_int`を渡すと小さい順（昇順：`1, 2, 3, 5, 8, 9`）に、`a`と`b`を逆にして呼ぶ`compare_int_desc`を渡すと大きい順（降順：`9, 8, 5, 3, 2, 1`）に並びます。

#### 文字列の比較関数

文字列の配列（`const char *names[]`）をアルファベット順に並べ替える場合も、`qsort`に渡す比較関数を書くだけで実現できます。
`names`配列の各要素は`const char *`型なので、`qsort`から比較関数に渡されるポインターは「`const char *`へのポインター（`const char *const *`）」になります。
そのため、`*sa`と`*sb`で文字列の先頭ポインターを取り出してから`strcmp`関数で比較しています。

```c
int compare_string(const void *a, const void *b)
{
    const char *const *sa = a;
    const char *const *sb = b;
    return strcmp(*sa, *sb);
}

/* 文字列配列のソート */
const char *names[] = {"Alice", "Bob", "Charlie", "David"};
size_t name_count = sizeof(names) / sizeof(names[0]);

qsort(names, name_count, sizeof names[0], compare_string);
```

### 実用的な応用例

実際のアプリやゲームでは、関数ポインターを使って「何かが起きたときの反応」や「後から機能を追加できる仕組み」を作ることがよくあります。

#### イベントシステム

ゲームで「ボタンが押された」「敵にぶつかった」といった出来事のことを**イベント**と呼び、その出来事が起きたときに実行される関数のことを**イベントハンドラ**と呼びます。
あらかじめ`register_event_handler`で「イベント番号」と「ハンドラ関数」のペアを登録しておき、出来事が起きたら`trigger_event`で登録済みの関数を呼び出します。

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

Webブラウザの拡張機能やゲームの追加機能のように、本体プログラムを書き換えずに後から機能を足せる仕組みを**プラグインシステム**と呼びます。
各プラグインが共通の`Plugin`構造体（初期化・実行・終了の関数ポインター）を用意しておけば、本体側は`plugins`配列に登録されたプラグインをループで順番に実行するだけで動かせます。

```c
typedef struct {
    const char *name;
    const char *version;
    int (*init)(void);
    void (*execute)(const char*);
    void (*shutdown)(void);
} Plugin;

/* プラグインの管理 */
Plugin *plugins[MAX_PLUGINS];
int plugin_count = 0;

int load_plugin(Plugin *plugin)
{
    if (plugin == NULL || plugin_count >= MAX_PLUGINS) {
        return -1;
    }
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

関数ポインターを使い始めたときに特につまずきやすい4つのミスを確認しておきましょう。

#### 1. 関数ポインターの間違った宣言

**問題：** `(*func)`の丸括弧を書き忘れてしまうミスです。
括弧がないと、`*`は`int`の方に結びついてしまい、「`int *`（ポインター）を返す普通の関数`func`の宣言」というまったく別の意味になってしまいます。

```c
int *func(int, int);     /* 関数（ポインターを返す） */
int (*func)(int, int);   /* 関数ポインター（正しい） */
```

#### 2. NULLポインターの呼び出し

**問題：** 何も代入していない未初期化の関数ポインターや、`NULL`が入った関数ポインターを呼び出すと**未定義動作**（プログラムの強制終了など）になります。

```c
int (*func)(int, int);
int result = func(5, 3);  /* 未初期化の値を使うため未定義動作 */
```

**対策：** 最初は`NULL`で初期化しておき、呼び出す前に必ず`func != NULL`を確認します。

```c
int (*func)(int, int) = NULL;
if (func != NULL) {
    int result = func(5, 3);
}
```

#### 3. 関数の型の不一致

**問題：** 関数ポインターで宣言した戻り値や引数の型と、代入する関数の型が一致していないとエラーや警告になります。
下の例では、`add`は`int`を返すのに、`func`は`void`を返す型として宣言されているため一致しません。

```c
int add(int a, int b) { return a + b; }
void (*func)(int, int) = add;  /* 戻り値の型が違う */
```

#### 4. 関数ポインター配列の初期化ミス

**問題：** 配列の要素数（`[3]`）よりも多い数の関数を初期値として並べてしまうミスです。
要素数を省略して`int (*ops[])(int, int) = { ... };`と書くか、正しい要素数を指定しましょう。

```c
int (*ops[3])(int, int) = {add, subtract, multiply, divide};  /* 4つの関数 */
```

### 性能を評価する場合

関数ポインターを通じた呼び出し（**間接呼び出し**）は、関数名を直接書いて呼ぶ場合（**直接呼び出し**）と比べると、実行時に呼び出し先をたどる手間がわずかに増えることがあります。
コンパイラがプログラムを高速化する処理（**最適化**）で間接呼び出しを直接呼び出しと同じように速くできるかどうかは、コンパイラが呼び出し先の関数を特定できるかによって変わります。
性能が気になる場合は、想像だけで判断せず、最適化を有効にして実際のプログラムの実行時間を計測して確認します。

## 実例コード

完全な実装例は以下のファイルを参照してください。

### 基本的な関数ポインター

- [function_pointer_basics.c](examples/function_pointer_basics.c) - C90準拠版
- [function_pointer_basics_c99.c](examples/function_pointer_basics_c99.c) - C99準拠版

### 関数ポインター配列と計算機

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

1. **理論学習**：README.mdで基本概念を理解します
2. **サンプルコード**：examples/の基本例を確認します
3. **演習課題**：exercises/README.mdで課題を確認します
4. **実装練習**：solutions/の解答例を参考に自分で実装します

### 学習のコツ

1. **段階的理解**：基本→配列→コールバック→高度な応用の順に少しずつ学習します
2. **実用例の実装**：計算機やイベントシステムなど、動きが目に見えるプログラムを実際に作ってみます
3. **デバッグ技術**：ポインターにどの関数を代入したか、配列の添字や条件が正しいかを丁寧に確認します
4. **パターンの習得**：`typedef`の書き方やコールバックの形など、よく使う定番パターンを覚えます

## 実践的な応用分野

関数ポインターは、身近なコンピュータのあちこちで活躍しています。

### システムプログラミング

OS（WindowsやmacOS、Linuxなど）の内部を支えるプログラムで使われます。

- **デバイスドライバのハンドラ**：キーボードやマウスなどの機器ごとに異なる操作関数を共通の形で呼び出す
- **割り込み処理関数**：機器から緊急の合図が来たときに自動で呼ばれる処理を登録する
- **システムコールハンドラ**：アプリからの依頼番号に応じて、OS内部の対応する関数を呼び分ける

### GUIプログラミング

ボタンやウィンドウが表示される画面（GUI）のアプリで使われます。

- イベントハンドラ（画面上の出来事への反応）
- ボタンのクリック処理
- メニュー項目の処理

### ゲーム開発

キャラクターや画面の動きを制御する仕組みで使われます。

- **ステートマシン**：キャラクターの「待機・移動・攻撃」などの状態ごとに実行する関数を切り替える
- アニメーション制御
- キーボードやコントローラーの入力処理

### 組み込みシステム

家電製品やロボットなど、小型コンピュータ（マイコン）が組み込まれた機器で使われます。

- タイマー割り込み処理（一定時間ごとに決まった関数を呼ぶ）
- センサーデータ処理
- 通信プロトコル処理

## 次の章へ

[第13章：複数ファイル・発展技術](../advanced/README.md)

## 参考資料

- examples/ - 実装例（C90、C99両対応）
- exercises/ - 演習問題
- solutions/ - 解答例
- [C標準ライブラリリファレンス](https://en.cppreference.com/w/c)
- [関数ポインター設計パターン](https://stackoverflow.com/questions/tagged/c+function-pointers)

## 演習問題

[演習問題](exercises/)では、宣言の読み方、互換性のある関数型、コールバック、表駆動の分岐を確認できます。

- 基礎問題：基本的な文法や概念の確認
- 応用問題：より実践的なプログラムの作成
- チャレンジ問題：高度な理解と実装力が必要な問題
