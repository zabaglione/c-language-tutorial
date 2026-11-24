# 複数ファイル・発展技術

## 対応C規格

- **主要対象：** C90/C99/C11/C17
- **学習内容：** 分割コンパイル、extern宣言、プリプロセッサ、モジュール設計、ライブラリ作成、高度な演算子テクニック

## 学習目標

この章を完了すると、以下のことができるようになります。

- 複数ファイルに分割したプログラムを作成できる
- extern宣言を正しく使用できる
- プリプロセッサ機能を効果的に活用できる
- 再利用可能なモジュールを設計できる
- 静的ライブラリを作成・使用できる
- 大規模プロジェクトの構成を理解する
- 短絡評価の評価順序を利用して、事前条件を検査できる
- 共用体（union）を理解し活用できる

## 概要と詳細

### 複数ファイルへ分割する目的

小さなプログラムなら1つの`.c`ファイルに全部書いても問題ありません。
しかし、プログラムが大きくなって何百行、何千行にもなると、1つのファイルから目的の場所を探すだけで大変になります。
ちょうど、算数・国語・理科のノートを1冊に全部書くより、教科ごとにノートを分けた方が見やすいのと同じです。

C言語でも、ソースファイルを機能ごとに分けると、「外に見せるメニュー（宣言）」と「中身の計算（実装）」をきれいに分けられます。
さらに、どこか1か所を直したときも、直したファイル（翻訳単位）だけをコンパイルし直せば済むようになります。

#### 分割によって得られる性質

1. **大規模プログラムの開発**

    - 機能ごとに宣言と定義をきれいに配置できる
    - 複数人で作業するときに、担当するファイルと変更する範囲を分けられる

2. **コードの再利用**

    - 一度作った便利な機能を、別のプログラムでも部品としてそのまま使える
    - ライブラリ（道具箱）として他の人へ配ることもできる

3. **保守性の向上**

    - 機能ごとにファイルが分かれているので、どこに何が書いてあるか探しやすい
    - バグ（不具合）を見つけて直す作業がぐっと楽になる

### 分割コンパイルの基本

複数ファイルに分けるときは、基本的に「ヘッダーファイル（`.h`）」と「実装ファイル（`.c`）」をペアで作ります。

- **ヘッダーファイル（`.h`）：** 「こういう関数が使えますよ」というメニュー表（宣言）を書くファイルです
- **実装ファイル（`.c`）：** 関数の実際の処理（定義）を書くファイルです

#### 基本的な分割例

計算用の機能（足し算・掛け算・円の面積）を`math_utils`という部品に分け、`main.c`から呼び出す例を見てみましょう。

#### `math_utils.h`（ヘッダーファイル）

まずはメニュー表となるヘッダーファイルです。
関数の名前、受け取る引数、返す値の型（プロトタイプ宣言）だけを書きます。

```c
#ifndef MATH_UTILS_H
#define MATH_UTILS_H

int add(int a, int b);
int multiply(int a, int b);
double circle_area(double radius);

#endif
```

最初と最後にある`#ifndef`〜`#endif`は、「同じヘッダーファイルをうっかり2回読み込まないようにする仕組み（インクルードガード）」です。
あとで仕組みを説明します。

#### `math_utils.c`（実装ファイル）

次に、実際の計算内容を書く実装ファイルです。
自分のメニュー表（`math_utils.h`）を`#include`で読み込み、宣言と中身が一致しているかコンパイラにチェックしてもらいます。

```c
#include "math_utils.h"
#define PI 3.14159265359

int add(int a, int b)
{
    return a + b;
}

int multiply(int a, int b)
{
    return a * b;
}

double circle_area(double radius)
{
    return PI * radius * radius;
}
```

#### `main.c`（メインプログラム）

使う側の`main.c`では、`#include "math_utils.h"`と書いてメニュー表を読み込むだけで、`add`や`multiply`、`circle_area`を呼び出せます。
自分で作ったヘッダーファイルは`<...>`ではなく`"..."`で囲むのがポイントです。

```c
#include <stdio.h>
#include "math_utils.h"

int main(void)
{
    int sum = add(10, 20);
    int product = multiply(5, 6);
    double area = circle_area(3.0);

    printf("Sum: %d\n", sum);
    printf("Product: %d\n", product);
    printf("Circle area: %.2f\n", area);

    return 0;
}
```

### extern宣言とグローバル変数

複数のファイルで同じグローバル変数（プログラム全体で共有する箱）を使いたいとき、あちこちのファイルで普通に変数を定義してしまうと、「同じ名前の箱が2つある！」とリンクエラーになってしまいます。

そこで使うのが`extern`宣言です。
`extern`は、「この変数の実物（メモリ上の箱）は別の`.c`ファイルに作ってあるから、ここでも名前だけ借りて使うよ」とコンパイラに伝える合図です。

#### extern宣言の基本

ヘッダーファイル（`config.h`）に`extern`をつけて宣言を書き、実装ファイル（`config.c`）に1か所だけ実物（定義）を書きます。

```c
/* config.h */
#ifndef CONFIG_H
#define CONFIG_H

extern int debug_level;
extern char app_name[];

#endif

/* config.c */
#include "config.h"

int debug_level = 1;
char app_name[] = "MyApplication";
```

こうしておけば、`config.h`を`#include`したどの`.c`ファイルからも、`config.c`にある`debug_level`や`app_name`を共有して使えます。

#### 外部リンケージを持つ変数の宣言

ファイル同士をまたいで名前を共有できる性質を「外部リンケージ」といいます。
次の例では、ログ（動作の記録）のレベルを表す`current_log_level`を`extern`で宣言し、他のファイルからも参照できるようにしています。

```c
/* logger.h */
#ifndef LOGGER_H
#define LOGGER_H

typedef enum {
    LOG_ERROR,
    LOG_WARNING,
    LOG_INFO,
    LOG_DEBUG
} LogLevel;

extern LogLevel current_log_level;

void log_message(LogLevel level, const char *message);

#endif
```

なお、グローバル変数はどこからでも書き換えられるため、増えすぎると「誰が値を変えたのか」が追いにくくなります。
必要なものだけに絞り、なるべく関数を通して操作する設計が安全です。

### プリプロセッサの活用

プリプロセッサは、コンパイルを始める前にソースコードの文字を書き換えたり、不要な部分を削ったりする「下ごしらえ係」です。
`#`で始まる行（`#include`や`#define`など）はすべてプリプロセッサへの命令です。

#### 基本的なマクロ定義

`#define`を使うと、決まった数値や計算式にわかりやすい名前（マクロ）をつけられます。

```c
#define MAX_SIZE 100
#define PI 3.14159265359
#define SQUARE(x) ((x) * (x))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
```

`SQUARE(x)`や`MAX(a, b)`のように引数を持つマクロは、ただの文字の置き換えとして動きます。
ここで`((x) * (x))`のようにカッコをたくさんつけているのには大切な理由があります。
もし`x * x`とカッコなしで書いてしまうと、`SQUARE(1 + 2)`が`1 + 2 * 1 + 2`（答えは5）に置き換わってしまい、ほしい答えの`9`になりません。
マクロの引数と式全体は、必ずカッコで囲むのが鉄則です。

#### 条件付きコンパイル

「テスト用のときだけデバッグメッセージを出したい」「WindowsとLinuxで読み込むヘッダーを変えたい」というときは、`#ifdef`や`#if`を使ってコンパイルするコードを切り替えられます。

次の例で使っている可変個引数マクロ（`...`と`__VA_ARGS__`）はC99で追加されました。
`DEBUG_PRINT("value=%d\n", value)`のように、`printf`と同じ感覚で好きな個数の引数を渡せます。

```c
#ifdef DEBUG
    #define DEBUG_PRINT(...) fprintf(stderr, __VA_ARGS__)
#else
    #define DEBUG_PRINT(...) ((void)0)
#endif

#if defined(_WIN32)
    #include <windows.h>
#elif defined(__linux__)
    #include <unistd.h>
#endif
```

`DEBUG`が定義されているとき（例：`gcc -DDEBUG ...`でコンパイルしたとき）はメッセージを出し、定義されていないときは`((void)0)`（何もしない処理）に置き換わります。
また、`_WIN32`や`__linux__`はコンパイラなどの処理系が独自に定義しているマクロであり、C言語の標準規格で決められたものではありません。
使うときは、自分のコンパイラでどんなマクロが定義されているか確認しましょう。

#### マクロと関数の選択

マクロは便利ですが、思わぬワナもあります。
たとえば`SQUARE(i++)`と書くと、`((i++) * (i++))`に置き換わり、`i`が2回増えてしまう（副作用が2回起きる）という問題があります。
そのため、通常の計算やチェックはなるべく普通の関数で書くのが安全です。

```c
/* 引数を一度ずつ評価し、状態を戻り値で返す */
int safe_divide(int a, int b, int *result)
{
    if (b == 0 || result == NULL) {
        return 0;
    }

    *result = a / b;
    return 1;
}

/* 配列サイズ取得マクロ */
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
```

`safe_divide`のような関数にすれば、引数は必ず1回ずつしか計算されず、0での割り算も安全に防げます。
一方、`ARRAY_SIZE`のように「配列全体のバイト数÷要素1個のバイト数」で要素数を求める処理は、関数に渡すと配列がポインターに変わってしまうため、マクロを使う代表的な場面です。
ただし、`ARRAY_SIZE`は配列本体にしか使えず、ポインター変数を渡すと正しい要素数が求められない点に注意してください。

### ヘッダーファイルの設計

#### インクルードガードの重要性

ファイルが増えてくると、AのヘッダーがBのヘッダーを読み込み、別の場所でもBのヘッダーを読み込む、というように同じヘッダーが何度も`#include`されることがあります。
すると、同じ構造体や型が2回定義されてコンパイルエラーになってしまいます。

それを防ぐのが「インクルードガード」です。

```c
#ifndef MODULE_NAME_H
#define MODULE_NAME_H

/* ヘッダーファイルの内容 */

#endif /* MODULE_NAME_H */
```

動きはとてもシンプルです。

1. 1回目に読み込まれたときは、`MODULE_NAME_H`がまだ定義されていない（`#ifndef`）ので、`#define`で目印をつけ、中身を読み込みます
2. 2回目に読み込まれたときは、すでに目印がついているので、`#endif`までをまるごとスキップします

すべてのヘッダーファイルにこのインクルードガードを入れる習慣をつけましょう。

#### 共通ヘッダー

複数のファイルで毎回同じ標準ヘッダーや型を使う場合、1つの共通ヘッダー（`common.h`）にまとめることがあります。

```c
/* common.h - よく使われるヘッダーをまとめる */
#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

/* 共通の型定義 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

/* 共通のマクロ */
#define TRUE 1
#define FALSE 0

#endif
```

ただし、ここで作った`u8`、`u16`、`u32`は、すべてのコンピュータで必ず8ビット、16ビット、32ビットになるという保証はありません。
C99以降で「絶対に8ビットや32ビットの幅にしたい」という場合は、標準の`<stdint.h>`を読み込んで、`uint8_t`、`uint16_t`、`uint32_t`を使いましょう。

### モジュール設計の原則

プログラムの部品（モジュール）をうまく設計するには、2つの大切な考え方があります。

#### 単一責任の原則

「1つのモジュールには、1つのわかりやすい役割だけを持たせる」という考え方です。
たとえば、文字列を扱う道具とファイルを扱う道具をごちゃ混ぜにせず、それぞれ別のファイルに分けます。

```c
/* string_utils.h - 文字列処理のみ */
#ifndef STRING_UTILS_H
#define STRING_UTILS_H

char *trim_whitespace(char *str);
int string_compare_ignore_case(const char *s1, const char *s2);
char *string_duplicate(const char *src);

#endif

/* file_utils.h - ファイル操作のみ */
#ifndef FILE_UTILS_H
#define FILE_UTILS_H

int file_exists(const char *filename);
long file_size(const char *filename);
char *read_entire_file(const char *filename);

#endif
```

役割がはっきり分かれていると、あとから「文字列の処理だけ直したい」「別のプログラムにファイル処理だけ持っていきたい」というときにとても扱いやすくなります。

#### 依存関係の最小化

あるヘッダーファイルが他のたくさんのヘッダーに頼っている（依存している）と、1か所を直しただけで関係ないファイルまでエラーになることがあります。
必要な最小限のヘッダーだけを読み込むようにすると、独立した丈夫な部品になります。

```c
/* good_module.h - 最小限の依存関係 */
#ifndef GOOD_MODULE_H
#define GOOD_MODULE_H

/* 標準ライブラリのみに依存 */
#include <stddef.h>

typedef struct point {
    double x;
    double y;
} Point;

Point point_create(double x, double y);
double point_distance(const Point *p1, const Point *p2);

#endif
```

この`good_module.h`は標準ライブラリの`<stddef.h>`しか読み込んでいないため、他のどんなプロジェクトへ持っていってもすぐに使えます。

### 静的ライブラリの作成

よく使う機能が増えてきたら、複数のオブジェクトファイル（`.o`）を1つの「道具箱ファイル」にまとめられます。
これを「静的ライブラリ（拡張子は`.a`）」といいます。
静的ライブラリにしておくと、他のプログラムを作るときに1つのファイルとして簡単にリンクできます。

#### ライブラリの構築手順

次の3つのステップで静的ライブラリを作って使います。

```bash

# オブジェクトファイルの作成

gcc -c math_utils.c -o math_utils.o
gcc -c string_utils.c -o string_utils.o

# 静的ライブラリの作成

ar rcs libmyutils.a math_utils.o string_utils.o

# ライブラリの使用

gcc main.c -L. -lmyutils -o main
```

コマンドの意味を順番に確認しましょう。

- `gcc -c ...`：ソースファイルを部品（`.o`）にコンパイルします
- `ar rcs libmyutils.a ...`：`ar`（アーカイバ）コマンドで、複数の`.o`を`libmyutils.a`という1つの道具箱にまとめます（ライブラリ名は`lib`で始めるのが決まりです）
- `gcc main.c -L. -lmyutils -o main`：`-L.`は「今のフォルダ（`.`）からライブラリを探してね」、`-lmyutils`は「`libmyutils.a`をリンクしてね（先頭の`lib`と末尾の`.a`は省いて書きます）」という意味です

#### Makefileでのライブラリ管理

毎回コマンドを手打ちするのは大変なので、`Makefile`に手順を書いて自動化しておくと便利です。

```makefile
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c90
AR = ar
ARFLAGS = rcs

# ライブラリのソースファイル

LIB_SOURCES = math_utils.c string_utils.c file_utils.c
LIB_OBJECTS = $(LIB_SOURCES:.c=.o)
LIB_TARGET = libmyutils.a

# メインプログラム

MAIN_SOURCE = main.c
MAIN_TARGET = main

all: $(LIB_TARGET) $(MAIN_TARGET)

$(LIB_TARGET): $(LIB_OBJECTS)
    $(AR) $(ARFLAGS) $@ $^

$(MAIN_TARGET): $(MAIN_SOURCE) $(LIB_TARGET)
    $(CC) $(CFLAGS) $< -L. -lmyutils -o $@

clean:
    rm -f *.o $(LIB_TARGET) $(MAIN_TARGET)
```

`$(LIB_SOURCES:.c=.o)`は、`.c`ファイルの名前をすべて`.o`に書き換えた一覧を自動で作ってくれます。
なお、実際にMakefileを動かすときは、コマンド行の先頭をスペースではなくタブ文字にする必要があります。

### 大規模プロジェクトの構成

#### 推奨ディレクトリ構造

ファイルがさらに増えてきたら、フォルダ（ディレクトリ）を役割ごとに整理します。
本棚に「まんが」「図鑑」「ノート」と場所を決めて並べるのと同じです。

```text
project/
├── src/           # ソースファイル
│   ├── main.c
│   └── modules/
│       ├── math/
│       ├── string/
│       └── file/
├── include/       # ヘッダーファイル
│   └── myproject/
├── lib/          # ライブラリファイル
├── tests/        # テストファイル
├── docs/         # ドキュメント
├── Makefile
└── README.md
```

ソースコードは`src/`、公開するヘッダーは`include/`、テスト用コードは`tests/`、説明書は`docs/`に分けるのがよくあるきれいな構成です。

#### モジュール間のインターフェース設計

「インターフェース」とは、他のプログラムからそのモジュールを使うときの「窓口（関数や型の見せ方）」のことです。
よい窓口を作るコツは、名前のルールをそろえることです。

```c
/* 良いインターフェース設計の例 */

/* logger.h */
typedef enum {
    LOG_LEVEL_ERROR,
    LOG_LEVEL_WARNING,
    LOG_LEVEL_INFO,
    LOG_LEVEL_DEBUG
} LogLevel;

/* 初期化と終了 */
int logger_init(const char *filename);
void logger_cleanup(void);

/* ログ出力 */
void log_error(const char *format, ...);
void log_warning(const char *format, ...);
void log_info(const char *format, ...);
void log_debug(const char *format, ...);

/* 設定 */
void logger_set_level(LogLevel level);
LogLevel logger_get_level(void);
```

この例では、`logger_init`や`logger_cleanup`、`logger_set_level`のように、`logger_`で始まる名前に統一されています。
これなら「ログ関係の関数だな」と一目でわかり、他のモジュールの関数と名前がぶつかるのも防げます。

### C11で追加された機能

C11規格では、プログラムの安全性を高める便利な仕組みが追加されました。

#### _Static_assert

`_Static_assert`は、プログラムを実行する前（コンパイル時）に「この前提条件は正しいか？」をチェックする安全装置です。
条件が間違っていれば、指定したメッセージを出してコンパイルを止めてくれます。

```c
#include <assert.h>

/* コンパイル時アサーション */
_Static_assert(sizeof(int) >= 4, "int must be at least 4 bytes");

typedef struct {
    char data[64];
} Buffer;

_Static_assert(sizeof(Buffer) == 64, "Buffer size must be exactly 64 bytes");
```

「`int`型は4バイト以上あるはず」「`Buffer`構造体はぴったり64バイトのはず」といった思い込みを、実行前にコンパイラが確かめてくれるので安心です。

#### _Generic（型汎用選択）

C言語では、絶対値を求める関数だけでも`int`用は`abs`、`long`用は`labs`、`double`用は`fabs`と名前がバラバラです。
C11の`_Generic`を使うと、渡された値の型に合わせて使う関数を自動で選び分けるマクロを作れます。

```c
#include <math.h>
#include <stdlib.h>

#define abs_generic(x) _Generic((x), \
    int: abs, \
    long: labs, \
    float: fabsf, \
    double: fabs, \
    long double: fabsl \
    )(x)

/* 使用例 */
int i = -5;
double d = -3.14;
printf("%d\n", abs_generic(i));    /* abs(i) */
printf("%.2f\n", abs_generic(d));  /* fabs(d) */
```

`abs_generic(i)`と書くと`i`が`int`型なので`abs(i)`が選ばれ、`abs_generic(d)`と書くと`d`が`double`型なので`fabs(d)`が選ばれます。

### 実践的なモジュール例

実際のアプリ開発でよく作られるモジュールの設計例を見てみましょう。

#### エラーハンドリングモジュール

失敗した理由を番号（`ErrorCode`）で管理し、わかりやすいメッセージ文字列へ変換できるモジュールです。

```c
/* error.h */
#ifndef ERROR_H
#define ERROR_H

typedef enum {
    ERROR_SUCCESS = 0,
    ERROR_NULL_POINTER,
    ERROR_OUT_OF_MEMORY,
    ERROR_FILE_NOT_FOUND,
    ERROR_INVALID_ARGUMENT
} ErrorCode;

const char *error_get_message(ErrorCode code);
void error_set_last_error(ErrorCode code);
ErrorCode error_get_last_error(void);

#endif
```

このようにエラーの種類を`enum`（列挙型）でまとめておくと、「0は成功、それ以外はどんな失敗か」をプログラム全体でそろえて扱えます。

#### 設定管理モジュール

設定ファイルから「名前（キー）」と「値（バリュー）」のペアを読み込んで取り出すモジュールです。

```c
/* config.h */
#ifndef CONFIG_H
#define CONFIG_H

typedef struct {
    char *key;
    char *value;
} ConfigItem;

int config_load(const char *filename);
const char *config_get_string(const char *key, const char *default_value);
int config_get_int(const char *key, int default_value);
double config_get_double(const char *key, double default_value);
void config_cleanup(void);

#endif
```

設定が見つからなかったときに返す「初期値（`default_value`）」を受け取る設計にしておくと、設定が抜けていても安全に動かせます。

### デバッグとテスト支援

#### デバッグマクロの活用

バグを探すとき、「今どの関数に入ったか」「どの関数を出たか」を画面に表示できると便利です。
次の例で使っている`__func__`（今いる関数名が入る特別な識別子）と可変個引数マクロは、C99以降で使えます。

```c
/* debug.h */
#ifndef DEBUG_H
#define DEBUG_H

#ifdef DEBUG_MODE
    #define DBG_ENTER() printf("ENTER: %s\n", __func__)
    #define DBG_EXIT() printf("EXIT: %s\n", __func__)
    #define DBG_PRINT(...) fprintf(stderr, __VA_ARGS__)
#else
    #define DBG_ENTER() ((void)0)
    #define DBG_EXIT() ((void)0)
    #define DBG_PRINT(...) ((void)0)
#endif

#endif
```

開発中は`DEBUG_MODE`をオンにして動きを追い、完成したらオフにするだけで、デバッグ表示をすべて消せます。

#### 単体テストフレームワーク

関数が正しく動くかを自動でチェックする仕組みを「単体テスト（ユニットテスト）」といいます。
マクロを使うと、簡単なテストの仕組みを自分で作れます。

```c
/* test_framework.h */
#ifndef TEST_FRAMEWORK_H
#define TEST_FRAMEWORK_H

#include <stdio.h>

extern int test_count;
extern int test_passed;

#define TEST_ASSERT(condition) \
    do { \
        test_count++; \
        if (condition) { \
            test_passed++; \
            printf("PASS: %s\n", #condition); \
        } else { \
            printf("FAIL: %s (line %d)\n", #condition, __LINE__); \
        } \
    } while (0)

#define TEST_SUMMARY() \
    printf("\nTest Results: %d/%d passed\n", test_passed, test_count)

#endif
```

ここにはプリプロセッサの便利な技が3つ使われています。

- **`#condition`：** 引数に渡した条件式そのものを文字列（例：`"add(1, 2) == 3"`）に変えて表示します
- **`__LINE__`：** その行がファイルの何行目なのかを自動で数字にしてくれます
- **`do { ... } while (0)`：** 複数の文が入ったマクロを、`if`文の中などで1つの文として安全に使えるようにする定番の工夫です

### パフォーマンス最適化

#### インライン関数（C99以降）

とても小さな関数を何百万回も呼び出すと、関数を呼び出して戻るための手間（オーバーヘッド）が積み重なることがあります。
C99で追加された`inline`をつけると、コンパイラに「可能なら呼び出し場所へ中身を直接埋め込んで速くしてね」とヒントを出せます。

```c
/* C99のinline関数 */
static inline int max_inline(int a, int b)
{
    return (a > b) ? a : b;
}

/* ヘッダーファイルでは内部リンケージにすると定義を完結させやすい */
static inline double square_inline(double x)
{
    return x * x;
}
```

マクロと違って型のチェックが働き、引数が2回計算される事故も起きません。
ヘッダーファイルに書くときは`static inline`にしておくと、複数の`.c`ファイルから読み込んでも名前がぶつからず扱いやすくなります。

#### コンパイラ最適化の活用

`if`文で「ほとんどの場合はこちらを通るけれど、めったにないエラーのときだけあちらを通る」とあらかじめわかっていることがあります。
GCCなどのコンパイラには、その確率をヒントとして伝える拡張機能があります。

```c
/* 最適化ヒントの提供 */
#ifdef __GNUC__
    #define LIKELY(x)   __builtin_expect(!!(x), 1)
    #define UNLIKELY(x) __builtin_expect(!!(x), 0)
#else
    #define LIKELY(x)   (x)
    #define UNLIKELY(x) (x)
#endif

/* 使用例 */
if (LIKELY(ptr != NULL)) {
    /* 通常の処理 */
} else {
    /* エラー処理（稀） */
}
```

`__GNUC__`がない別のコンパイラでは単なる`(x)`になるように書かれているので、他の環境でもそのままコンパイルできます。
ただし、このような最適化は本当に速さが足りない場所を計測してから使うのが基本です。

## 実例コード

完全な実装例は以下のファイルを参照してください。

### 基本的な分割コンパイル

- [multi_file_basic/](examples/multi_file_basic/) - 基本的な分割例
- [library_example/](examples/library_example/) - ライブラリ作成例

### 高度なプリプロセッサ活用

- [preprocessor_demo.c](examples/preprocessor_demo.c) - マクロとプリプロセッサ
- [conditional_compile.c](examples/conditional_compile.c) - 条件付きコンパイル

### 実用的なモジュール

- [utils_library/](examples/utils_library/) - 実用的なユーティリティライブラリ
- [project_template/](examples/project_template/) - プロジェクトテンプレート

## コンパイル方法

### 基本的な分割コンパイル

1つずつオブジェクトファイル（`.o`）を作ってからリンクする方法と、まとめて一気にコンパイルする方法の2通りがあります。

```bash

# 個別にコンパイル

gcc -c math_utils.c -o math_utils.o
gcc -c main.c -o main.o
gcc math_utils.o main.o -o main

# 一括コンパイル

gcc math_utils.c main.c -o main
```

### 静的ライブラリの作成と使用

```bash

# ライブラリ作成

gcc -c *.c
ar rcs libmyutils.a *.o

# ライブラリ使用

gcc main.c -L. -lmyutils -o main
```

### Makefileを使用した場合

`Makefile`が用意されていれば、`make`コマンドだけでビルドや後片付けができます。

```bash

# 全てのターゲットをビルド

make all

# 特定のターゲットをビルド

make library

# クリーンアップ

make clean

# インストール

make install
```

## 学習フローとコンパイル方法

### 推奨学習順序

1. **理論学習：** README.mdで基本概念を理解
2. **サンプルコード：** examples/の基本例を確認
3. **演習課題：** exercises/README.mdで課題を確認
4. **実装練習：** solutions/の解答例を参考に自分で実装

### 実践的な学習方法

1. **小さなプロジェクトから始める：** まずは2〜3ファイルの分割から試す
2. **段階的に複雑化：** 機能を追加するたびにモジュールを分ける
3. **実際のライブラリを参考：** オープンソースプロジェクトの構成を学ぶ
4. **チーム開発の模擬：** 複数人でファイルを分担するつもりで設計してみる

## C標準の違いと対応

### C90での制限と対策

- `inline`関数なし → マクロやコンパイラの最適化に任せる
- 可変長引数マクロなし → 引数の数が決まったマクロを使う
- `_Bool`型なし → `int`型で`0`（偽）と`1`（真）を表す

### C99以降の拡張機能活用

- `inline`関数の使用
- 可変長引数マクロ（`__VA_ARGS__`）
- 指定初期化子
- 複合リテラル

### C11の機能とC17

- `_Static_assert`
- `_Generic`
- `_Alignas`/`_Alignof`
- `_Thread_local`

C17はC11の不具合修正が中心で、新しい言語機能は追加していません。

### 短絡評価と共用体

ここからは、安全なコードを書くための「短絡評価」と、メモリを共有して使う「共用体（`union`）」を学びます。

論理AND演算子`&&`（「かつ」）は、左側の条件が偽（`0`）だった時点で答えが偽に決まるため、右側の式を実行（評価）しません。
同じように、論理OR演算子`||`（「または」）は、左側の条件が真（`0`以外）だった時点で答えが真に決まるため、右側の式を実行しません。
この「結果が決まったら右側をスキップする仕組み」を「短絡評価（たんらくひょうか）」といいます。

たとえば、「鍵が開いているか確かめてから、ドアを開ける」ように、左側に安全な前提条件を書き、右側に実際の操作を書けば、危ない操作を未然に防げます。

#### 短絡評価による安全なプログラミング

短絡評価を使うときは、左から右へ「まず確認すべき安全条件」の順番に並べるのがルールです。

##### 配列とポインターの安全な操作

C言語では、配列の範囲をはみ出してアクセスしても自動でエラーにしてくれず、未定義動作（クラッシュやデータ破壊）につながります。
そのため、配列を読む前に必ず「番号が範囲内か」を左側で確認します。

```c
/* 配列の境界チェック */
int array[10];
int index = 15;
if (index >= 0 && index < 10 && array[index] > 0) {
    /* index が範囲外なので、array[index] へのアクセスは行われない */
    printf("Valid value: %d\n", array[index]);
}

/* 多次元配列の安全なアクセス */
int matrix[5][5];
int row = 3, col = 7;
if (row >= 0 && row < 5 && col >= 0 && col < 5 && matrix[row][col] != 0) {
    /* 行と列の両方が範囲内の場合のみアクセス */
    process_element(matrix[row][col]);
}

/* 動的配列（ポインター）の操作 */
int *data = NULL;
if (size > 0 && (size_t)size <= ((size_t)-1) / sizeof *data) {
    data = malloc((size_t)size * sizeof *data);
}
if (data != NULL && initialize_array(data, size)) {
    /* メモリ確保成功、かつ初期化成功の場合のみ使用 */
    use_array(data, size);
}
free(data);  /* free()はNULLに対して安全 */
```

最初の例では、`index`が`15`なので`index < 10`が偽になり、後ろの`array[index]`は読まれずに済みます。
3つ目の例では、`malloc`でメモリを確保する前に掛け算がオーバーフロー（数の上限あふれ）しないか確かめ、さらに`data != NULL`を確認してから初期化関数を呼んでいます。

##### 文字列処理の安全性確保

ポインターが`NULL`（どこも指していない状態）のまま`strlen`や`str[0]`を呼ぶと、プログラムが強制終了してしまいます。
左側に`str`（`str != NULL`と同じ意味）を置いておけば、`NULL`のときは右側がスキップされて安全です。

```c
/* 文字列の安全なチェック */
char *str = get_string();  /* NULL を返す可能性がある */
if (str && strlen(str) > 0 && str[0] == 'A') {
    /* str が NULL の場合、strlen や str[0] は評価されない */
    printf("String starts with 'A'\n");
}

/* 文字列の詳細な検証 */
char *input = get_user_input();
if (input && *input && strlen(input) < MAX_LENGTH && is_valid_format(input)) {
    /* NULL でない、空でない、長さ制限内、フォーマット正しい */
    process_input(input);
}
```

`*input`は文字列の1文字目を指します。
空の文字列（`""`）は1文字目が終端文字`'\0'`（数値の`0`）なので、`*input`が真かどうかを見るだけで「空文字でないこと」を素早く確認できます。

##### ファイル操作とリソース管理

ファイルを開いたりメモリを確保したりする処理を順番につなげるときも、短絡評価が役立ちます。

```c
/* ファイル操作の連鎖的エラーチェック */
FILE *fp = fopen("data.txt", "r");
if (fp != NULL && read_header(fp) && validate_data(fp)) {
    /* 各段階でエラーがあれば、後続の処理はスキップされる */
    process_file(fp);
}
if (fp != NULL) {
    fclose(fp);
}

/* 複数リソースの管理 */
void process_data_file(const char *filename)
{
    FILE *fp = NULL;
    char *buffer = NULL;
    int *data = NULL;

    /* リソースの段階的確保 */
    if ((fp = fopen(filename, "rb")) != NULL &&
        (buffer = malloc(BUFFER_SIZE)) != NULL &&
        (data = malloc(sizeof *data * MAX_ITEMS)) != NULL &&
        read_file_to_buffer(fp, buffer, BUFFER_SIZE) &&
        parse_buffer_to_data(buffer, data, MAX_ITEMS)) {

        /* すべてのリソースが正常に確保され、処理が成功 */
        analyze_data(data, MAX_ITEMS);

    } else {
        /* どこかでエラーが発生した */
        fprintf(stderr, "Data processing failed\n");
    }

    /* クリーンアップ（NULL チェック不要） */
    free(data);
    free(buffer);
    if (fp != NULL) fclose(fp);
}
```

もし途中の`fopen`や`malloc`で失敗したら、その時点で後ろの処理はすべてスキップされて`else`へ進みます。
最後に確保できた分だけ`free`や`fclose`で確実に片付けられるため、メモリリーク（片付け忘れ）を防ぎやすくなります。

#### ビット操作とビットフィールド

ビット演算の詳しい解説、ビットマスクを使ったテクニック、ビットフィールドによるメモリ節約については、専用の章で学べます。

[第12章：ビット操作とビットフィールド](../bit-operations/README.md)では、次の内容を説明しています。

- ビット演算子の詳細と活用法
- フラグ管理システムの実装
- ビットカウントなどの高度なアルゴリズム
- ビットフィールドによるデータ圧縮
- RGB色操作などの実践的な応用例

#### 共用体（union）

構造体（`struct`）は、複数のメンバがそれぞれ自分の部屋を持って横に並ぶ「マンション」のようなイメージでした。
一方、共用体（`union`）は、複数のメンバが「たった1つの同じメモリ領域（部屋）」を共有して使い回す「多目的室」のような型です。

同じ場所を使うため、同時に覚えておけるのは「最後に書き込んだ1つのメンバの値」だけです。
「今は整数、別の場面では小数、また別の場面では文字列」のように、同時に1種類しか入れないデータでメモリを節約したいときに使います。

##### 基本的な共用体の使い方

```c
/* 基本的な共用体の定義 */
union Data {
    int i;
    float f;
    char str[20];
};

int main(void) {
    union Data data;

    /* 整数として使用 */
    data.i = 42;
    printf("Integer: %d\n", data.i);

    /* 浮動小数点として使用（前の値は上書きされる） */
    data.f = 3.14f;
    printf("Floating: %f\n", data.f);

    /* 文字列として使用 */
    strcpy(data.str, "Hello");
    printf("String: %s\n", data.str);

    printf("Union size: %lu bytes\n", (unsigned long)sizeof(union Data));
    return 0;
}
```

`data.f = 3.14f;`と書き込んだ瞬間に、前に同じ場所へ入っていた`data.i`の値（`42`）は上書きされて消えます。
また、`sizeof(union Data)`は全メンバの合計ではなく、いちばん大きいメンバ（ここでは20バイトの`char str[20]`）が入る大きさ以上になります。

##### オブジェクト表現の取得

小数の`float`がメモリの中でどんなバイトの並び（オブジェクト表現）になっているか調べたいときは、共用体で別のメンバから読むのではなく、`unsigned char`の配列へ`memcpy`でコピーするのが安全な方法です。

```c
/* floatのオブジェクト表現を1バイトずつ表示する */
#include <stddef.h>
#include <stdio.h>
#include <string.h>

void print_float_representation(float value)
{
    unsigned char bytes[sizeof value];
    size_t i;

    memcpy(bytes, &value, sizeof value);
    for (i = 0; i < sizeof bytes; i++) {
        printf("%02X ", (unsigned int)bytes[i]);
    }
    putchar('\n');
}
```

`unsigned char`の配列へ`memcpy`する方法なら、共用体の別メンバを読むような環境に左右されやすい書き方に頼らず中身を観察できます。
ただし、`float`の詳しい形式やバイトの並び順（エンディアン）はコンピュータやコンパイラによって違うため、表示された結果が必ずIEEE 754という標準形式の並びと一致するとは限りません。

##### 32ビット値からオクテットを取り出す

ネットワークのIPv4アドレス（例：`192.168.0.1`）は、8ビット（1オクテット）の数字が4つ集まった32ビットの整数で表されることがあります。
この4つの数字を取り出すときは、共用体で重ねるのではなく、ビットシフト（`>>`）とビットAND（`&`）を使うのが確実です。

```c
#include <stdint.h>

void print_ipv4_value(uint32_t ip)
{
    printf("%u.%u.%u.%u\n",
           (unsigned int)((ip >> 24) & UINT32_C(0xff)),
           (unsigned int)((ip >> 16) & UINT32_C(0xff)),
           (unsigned int)((ip >> 8) & UINT32_C(0xff)),
           (unsigned int)(ip & UINT32_C(0xff)));
}
```

共用体で整数と文字配列を重ねる方法は、パソコンごとのバイトの並び順や`unsigned int`の大きさに影響されてしまいます。
外部データのように順番が決まっているものは、`uint32_t`のような幅が明確な型とシフト演算で取り出しましょう。

##### タグ付き共用体（判別共用体）

共用体だけだと、「今この部屋に入っているのは整数なのか、小数なのか、文字列なのか」が見た目ではわかりません。
そこで、「今どの型が入っているか」を記録する名札（タグ）を構造体でセットにしたものを「タグ付き共用体」といいます。

```c
/* データ型を識別するタグ付き共用体 */
typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_STRING
} DataType;

typedef struct {
    DataType type;
    union {
        int i;
        float f;
        char *s;
    } value;
} Variant;

void print_variant(const Variant *var) {
    switch (var->type) {
        case TYPE_INT:
            printf("Integer: %d\n", var->value.i);
            break;
        case TYPE_FLOAT:
            printf("Floating: %f\n", var->value.f);
            break;
        case TYPE_STRING:
            printf("String: %s\n", var->value.s);
            break;
    }
}
```

値をしまうときに`var->type`の名札もいっしょに更新しておけば、`print_variant`のように`switch`文で名札を確認してから、正しいメンバだけを安全に取り出せます。

##### 共用体の注意点

1. **現在の表現を管理する**

    - 最後に値を書き込んだメンバを、タグ（名札）で必ず記録する
    - 別のメンバとして無理やり読み出す方法は型や処理系に依存するため、移植性の高い型変換には使わない

2. **メモリサイズ**

    - 共用体のサイズは、最大のメンバを格納できる大きさ以上になる
    - メモリ配置を整えるためのすき間（パディング）が入ることもある

3. **初期化**

    - C90では、いちばん最初に宣言したメンバだけで初期化できる
    - C99以降では、`.f = 3.14f`のような指定初期化子を使って好きなメンバを初期化できる

##### 条件の評価順序を使った処理

最後に、短絡評価を「処理の効率化（無駄な計算を省く工夫）」に活かした実例を見てみましょう。

```c
/* 条件付き処理の最適化 */
typedef struct {
    int is_cached;
    int cache_value;
} Cache;

int get_expensive_value(Cache *cache, int param)
{
    int result;

    /* キャッシュ済みなら、値が0でもその値を返す */
    if (cache != NULL && cache->is_cached) {
        return cache->cache_value;
    }

    /* 高コストな計算 */
    result = expensive_calculation(param);

    /* キャッシュに保存 */
    if (cache != NULL) {
        cache->is_cached = 1;
        cache->cache_value = result;
    }

    return result;
}

/* 権限チェックの最適化 */
int can_access_resource(User *user, Resource *resource)
{
    /* 管理者の場合は、右辺の詳細な権限検査を評価しない */
    return (user != NULL && user->is_admin) ||
           /* 一般ユーザーは詳細な権限チェック */
           (user != NULL &&
            resource != NULL &&
            user->level >= resource->required_level &&
            has_permission(user, resource->type) &&
            !is_blocked(user, resource));
}
```

1つ目の`get_expensive_value`は、時間のかかる計算結果をキャッシュ（一時保存メモ）しておく関数です。
すでに計算済みなら、`cache != NULL && cache->is_cached`で安全に確認してメモの値をすぐ返します。

2つ目の`can_access_resource`は、`||`の短絡評価を使っています。
左側の`(user != NULL && user->is_admin)`が真（管理者である）なら、その瞬間にアクセス許可（真）が決まるため、右側の細かいチェック関数（`has_permission`や`is_blocked`）を呼ばずに高速に終わらせられます。

## 次の章へ

規格ごとの機能差を続けて確認する場合は、[C23の新機能](../c23-features/README.md)を参照してください。

- [C23の新機能](../c23-features/README.md)（オプション）

## 参考資料

- examples/ - 実装例（複数C標準対応）
- exercises/ - 演習問題
- solutions/ - 解答例
- [C標準ライブラリリファレンス](https://en.cppreference.com/w/c)
- [GNU Make Manual](https://www.gnu.org/software/make/manual/)

## 演習問題

[演習問題](exercises/)では、分割コンパイル、リンケージ、マクロ、短絡評価、共用体を確認できます。

- 基礎問題：基本的な文法や概念の確認
- 応用問題：より実践的なプログラムの作成
- チャレンジ問題：高度な理解と実装力が必要な問題
