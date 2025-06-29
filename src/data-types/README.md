# 第3章 データ型・変数・スコープ

##  対応C規格
- **主要対象:** C90
- **学習内容:** 基本データ型、変数宣言、初期化、スコープ、変数の生存期間

##  学習目標

この章を完了すると、以下のことができるようになります：

- C言語の基本データ型を理解する
- 変数の宣言と初期化ができる
- 変数のスコープ（有効範囲）を理解する
- データ型のサイズと範囲を把握する
- 適切な型を選択してプログラムを作成できる

##  理論解説

### C言語の基本データ型 

C言語では、さまざまなデータ型が用意されています。

#### 整数型

| 型名 | サイズ | 範囲 | 説明 |
|------|--------|------|------|
| `char` | 1バイト | -128 〜 127 | 文字、小さな整数 |
| `unsigned char` | 1バイト | 0 〜 255 | 符号なし文字 |
| `short` | 2バイト | -32,768 〜 32,767 | 短整数 |
| `unsigned short` | 2バイト | 0 〜 65,535 | 符号なし短整数 |
| `int` | 4バイト | -2,147,483,648 〜 2,147,483,647 | 整数 |
| `unsigned int` | 4バイト | 0 〜 4,294,967,295 | 符号なし整数 |
| `long` | 4/8バイト | システム依存 | 長整数 |
| `unsigned long` | 4/8バイト | システム依存 | 符号なし長整数 |

#### 浮動小数点数型

| 型名 | サイズ | 精度 | 説明 |
|------|--------|------|------|
| `float` | 4バイト | 約7桁 | 単精度浮動小数点 |
| `double` | 8バイト | 約15桁 | 倍精度浮動小数点 |
| `long double` | 12/16バイト | システム依存 | 拡張精度浮動小数点 |

#### その他の型

| 型名 | 説明 |
|------|------|
| `void` | 「型なし」を表す（関数の戻り値等で使用） |

### 変数の宣言と初期化 

#### 基本的な変数宣言

```c
int age;        /* 整数型変数の宣言 */
double height;  /* 倍精度浮動小数点型変数の宣言 */
char grade;     /* 文字型変数の宣言 */
```

#### 初期化付き宣言

```c
int count = 10;           /* 宣言と同時に初期化 */
double pi = 3.14159;     /* 浮動小数点数の初期化 |
char letter = 'A';       /* 文字の初期化 */
```

#### 複数変数の同時宣言

```c
int x, y, z;                    /* 同じ型の複数変数 */
int a = 1, b = 2, c;          /* 一部だけ初期化 */
```

### 変数の代入と演算 

#### 代入演算子

```c
int number;
number = 10;        /* 代入 */
number += 5;        /* number = number + 5 と同じ */
number -= 3;        /* number = number - 3 と同じ */
number *= 2;        /* number = number * 2 と同じ */
number /= 4;        /* number = number / 4 と同じ */
```

#### 基本演算子

```c
int a = 10, b = 3;
int sum = a + b;        /* 加算: 13 */
int diff = a - b;       /* 減算: 7 */
int product = a * b;    /* 乗算: 30 */
int quotient = a / b;   /* 除算: 3 (整数除算) */
int remainder = a % b;  /* 剰余: 1 */
```

### 型変換（キャスト） 

#### 暗黙の型変換

```c
int i = 42;
double d;
d = i;          /* int から double への自動変換 */
```

#### 明示的な型変換

```c
double pi = 3.14159;
int rounded;
rounded = (int)pi;      /* 明示的にintに変換（3になる） */
```

#### 型変換の注意点

```c
int a = 5, b = 2;
double result;

result = a / b;         /* 結果: 2.0 (整数除算後に変換) */
result = (double)a / b; /* 結果: 2.5 (実数除算) */
```

### 変数のスコープ（有効範囲） 

スコープとは、変数がプログラム中のどの部分でアクセス可能かを示す概念です。

#### 1. ファイルスコープ（グローバルスコープ）

ファイル全体でアクセス可能な変数です。

```c
#include <stdio.h>

int global_count = 100;   /* ファイルスコープ変数 */
double global_rate;     /* 初期化されていない場合は0になる */

void function(void)
{
    global_count = 200; /* 関数内からアクセス可能 */
}

int main(void)
{
    global_count = 150;  /* main関数からもアクセス可能 */
    function();
    printf("global_count = %d\n", global_count); /* 200が出力 */
    return 0;
}

```

#### 2. 関数スコープ

関数内で宣言された変数は、その関数内でのみアクセス可能です。

```c
void function_a(void)
{
    int local_a = 10;   /* function_a内でのみ有効 */
    printf("local_a = %d\n", local_a);
}

void function_b(void)
{
    int local_a = 20;   /* 異なる関数なので同じ名前でも別変数 */
    printf("local_a = %d\n", local_a);
    /* function_aのlocal_aにはアクセス不可 */
}

```

#### 3. ブロックスコープ

`{` と `}` で囲まれたブロック内でのみアクセス可能な変数です。

```c
int main(void)
{
    int main_var = 5;
    
    if (main_var > 0) {
        int block_var = 10;      /* このifブロック内でのみ有効 */
        printf("block_var = %d\n", block_var);
        
        {
            int nested_var = 20; /* さらに内側のブロック */
            printf("nested_var = %d\n", nested_var);
            /* block_varとmain_varにもアクセス可能 */
        }
        /* nested_varはここではアクセス不可 */
    }
    /* block_varはここではアクセス不可 */
    
    return 0;
}

```

#### 4. スコープの隠蔽（シャドウイング）

内側のスコープで同じ名前の変数を宣言すると、外側の変数が隠蔽されます。

```c
int x = 100;     /* グローバル変数 */

int main(void)
{
    printf("グローバルx = %d\n", x);    /* 100が出力 */
    
    {
        int x = 200; /* ローカル変数がグローバル変数を隠蔽 */
        printf("ローカルx = %d\n", x);   /* 200が出力 */
        
        {
            int x = 300; /* さらに内側で隠蔽 */
            printf("内側x = %d\n", x);   /* 300が出力 */
        }
        
        printf("ローカルx = %d\n", x);   /* 200が出力（復活） */
    }
    
    printf("グローバルx = %d\n", x);    /* 100が出力（復活） */
    return 0;
}

```

### 変数の生存期間（Storage Duration） 

変数がメモリ上に存在する期間を生存期間といいます。

#### 1. 自動変数（Automatic Variables）

関数やブロックに入るときに作成され、出るときに破棄される変数です。

```c
void demo_function(void)
{
    int auto_var = 5;      /* 自動変数（autoは省略可能） */
    auto int explicit_auto = 10; /* 明示的にauto指定 */
    
    printf("auto_var = %d\n", auto_var);
    /* 関数終了時にauto_varは破棄される */
}

int main(void)
{
    demo_function();
    demo_function();    /* 毎回新しくauto_varが作成される */
    return 0;
}
```

#### 2. 静的変数（Static Variables）

プログラム開始時に作成され、プログラム終了まで存在し続ける変数です。

```c
void counter_function(void)
{
    static int count = 0;   /* 静的ローカル変数、初期化は11回のみ */
    
    count++;
    printf("関数呼出回数: %d\n", count);
}

int main(void)
{
    counter_function();     /* 1が出力 */
    counter_function();     /* 2が出力 */
    counter_function();     /* 3が出力 */
    return 0;
}

```

#### 3. 静的グローバル変数

ファイル内でのみアクセス可能なグローバル変数です。

```c
static int file_private = 10;  /* このファイル内でのみアクセス可能 */
int file_public = 20;          /* 他のファイルからもアクセス可能 */

static void private_function(void)  /* このファイル内でのみ呼出可能 */
{
    printf("file_private = %d\n", file_private);
}

int main(void)
{
    private_function();
    return 0;
}
```

#### 4. レジスタ変数（Register Variables）

可能であればレジスタに格納される変数です（C90では推奨のみ）。

```c
int main(void)
{
    register int fast_var = 100; /* レジスタ格納を要求 */
    
    /* レジスタ変数のアドレスは取得できない */
    /* int *ptr = &fast_var;  <- エラー */
    
    return 0;
}
```

### ストレージクラス指定子まとめ 

| 指定子 | スコープ | 生存期間 | 初期化 | 説明 |
|--------|----------|----------|--------|------|
| `auto` | ブロック | 自動 | 未定義値 | デフォルト（省略可能） |
| `static`（ローカル） | ブロック | 静的 | 0 | 関数呼出間で値保持 |
| `static`（グローバル） | ファイル | 静的 | 0 | ファイル内限定 |
| `extern` | グローバル | 静的 | 他で定義 | 他ファイルの変数参照 |
| `register` | ブロック | 自動 | 未定義値 | レジスタ格納要求 |

### 変数の初期化規則 

#### 自動変数の初期化

```c
int main(void)
{
    int uninitialized;          /* 未定義値（危険） */
    int initialized = 0;       /* 明示的初期化（推奨） */
    
    printf("uninitialized = %d\n", uninitialized); /* 予測不能 */
    printf("initialized = %d\n", initialized);     /* 0 */
    
    return 0;
}
```

#### 静的変数の初期化

```c
int global_int;          /* 自動的に0で初期化 */
static int static_int;   /* 自動的に0で初期化 */

int main(void)
{
    static int local_static;    /* 自動的に0で初期化 */
    
    printf("global_int = %d\n", global_int);       /* 0 */
    printf("static_int = %d\n", static_int);       /* 0 */
    printf("local_static = %d\n", local_static);   /* 0 */
    
    return 0;
}
```

### 実践的なスコープ活用例 

#### カウンター関数の実装

```c
int get_next_id(void)
{
    static int id_counter = 1000;   /* 初期値 */
    
    return id_counter++;    /* 現在値を返してからインクリメント */
}

int main(void)
{
    printf("ID: %d\n", get_next_id());    /* 1000 */
    printf("ID: %d\n", get_next_id());    /* 1001 */
    printf("ID: %d\n", get_next_id());    /* 1002 */
    
    return 0;
}
```

#### モジュール内状態管理

```c
/* 設定管理モジュールの例 */
static int debug_mode = 0;      /* モジュール内部状態 */
static int max_connections = 10;

void set_debug_mode(int mode)
{
    debug_mode = mode;
}

int is_debug_enabled(void)
{
    return debug_mode;
}

void set_max_connections(int max)
{
    if (max > 0 && max <= 100) {
        max_connections = max;
    }
}

int get_max_connections(void)
{
    return max_connections;
}
```

### 定数の定義 

#### `const`キーワード

```c
const int MAX_SIZE = 100;       /* 定数の定義 */
const double PI = 3.14159;      /* 浮動小数点定数 */
```

#### `#define`プリプロセッサ

```c
#define MAX_STUDENTS 50          /* マクロ定数 */
#define TITLE "C Language Tutorial"
```

### データ型のサイズ確認 

`sizeof`演算子を使ってデータ型のサイズを確認できます：

```c
#include <stdio.h>

int main(void)
{
    printf("char: %lu バイト\n", sizeof(char));
    printf("int: %lu バイト\n", sizeof(int));
    printf("double: %lu バイト\n", sizeof(double));
    return 0;

```

##  サンプルコード

### 基本データ型の使用例

**プログラムファイル:** [`examples/data_types_demo.c`](examples/data_types_demo.c) | [C99版](examples/data_types_demo_c99.c)

各データ型の宣言、初期化、出力を学習します。

```c
/*
 * ファイル名: data_types_demo.c
 * 説明: C言語の基本データ型の使用例
 * 規格: C90準拠
 */

#include <stdio.h>

int main(void)
{
    /* 整数型の変数宣言と初期化 */
    char letter = 'A';
    short small_num = 1000;
    int age = 25;
    long big_num = 1234567L;
    unsigned int positive = 100U;

    /* 浮動小数点型の変数宣言と初期化 */
    float pi_f = 3.14f;
    double pi_d = 3.141592653589793;

    printf("=== データ型のサイズと値 ===\n");

    /* 各データ型のサイズを表示 */
    printf("char     : %lu バイト, 値: %c (%d)\n",
           sizeof(char), letter, letter);
    printf("short    : %lu バイト, 値: %d\n",
           sizeof(short), small_num);
    printf("int      : %lu バイト, 値: %d\n",
           sizeof(int), age);
    printf("long     : %lu バイト, 値: %ld\n",
           sizeof(long), big_num);
    printf("unsigned : %lu バイト, 値: %u\n",
           sizeof(unsigned int), positive);
    printf("float    : %lu バイト, 値: %.6f\n",
           sizeof(float), pi_f);
    printf("double   : %lu バイト, 値: %.15f\n",
           sizeof(double), pi_d);

    /* 演算の例 */
    printf("\n=== 基本演算 ===\n");
    printf("10 + 3 = %d\n", 10 + 3);
    printf("10 - 3 = %d\n", 10 - 3);
    printf("10 * 3 = %d\n", 10 * 3);
    printf("10 / 3 = %d (整数除算)\n", 10 / 3);
    printf("10 %% 3 = %d (剰余)\n", 10 % 3);
    printf("10.0 / 3.0 = %.2f (実数除算)\n", 10.0 / 3.0);

    return 0;
}
```

### 数値計算の応用例

**プログラムファイル:** [`solutions/numerical_calc.c`](solutions/numerical_calc.c) | [C99版](solutions/numerical_calc_c99.c)

math.hライブラリを使用した高度な数値計算を学習します。

### コンパイルと実行

```bash
# examples ディレクトリに移動
cd examples

# C90準拠でコンパイル
gcc -std=c90 -Wall -Wextra -pedantic data_types_demo.c -o data_types_demo

# 実行
./data_types_demo
```

##  演習課題

### 基礎問題

1. **変数宣言と初期化**
   - さまざまなデータ型の変数を宣言し、初期化してください
   - 各変数の値をprintf関数で出力してください

2. **四則演算計算機**
   - 2つの数値を変数に格納し、四則演算の結果を表示するプログラムを作成してください

3. **データ型サイズの確認**
   - sizeof演算子を使って、各データ型のサイズを表示するプログラムを作成してください

### 応用問題

1. **型変換の理解**
   - 整数除算と実数除算の違いを確認するプログラムを作成してください

2. **スコープの実験**
   - グローバル変数とローカル変数を使い分けるプログラムを作成してください

3. **定数の活用**
   - constと#defineを使って定数を定義し、計算に使用してください

##  コンパイル方法

この章では以下のMakefileを使用してコンパイルができます：

```bash
# 全ての例題をコンパイル
make all

# 特定のプログラムをコンパイル
make data_types_demo

# 実行
make run

# クリーンアップ
make clean
```

##  規格による違い

### C90での制限事項
- 変数宣言は関数やブロックの先頭で行う必要がある
- `long long`型は使用できない
- `_Bool`型は使用できない

### C99以降の拡張
- `long long`型の追加（64ビット整数）
- `_Bool`型の追加（論理型）
- 複素数型（`_Complex`）の追加
- 変数宣言位置の制限緩和

### 型サイズの注意点

データ型のサイズはシステムに依存するため、portable（移植可能）なプログラムを書く際は注意が必要です：

```c
/* 推奨: 具体的なサイズが必要な場合 */
#include <stdint.h>
int32_t exact_32bit;    /* C99以降 */
```

##  よくある間違い

### 1. 初期化忘れ
```c
/* NG: 初期化せずに使用 */
int count;
printf("%d\n", count);  /* 未定義値が出力される */

/* OK: 初期化してから使用 */
int count = 0;
printf("%d\n", count);
```

### 2. 整数除算の結果
```c
/* NG: 期待した結果にならない */
int result = 5 / 2;     /* 結果: 2 */

/* OK: 実数除算を使用 */
double result = 5.0 / 2.0;  /* 結果: 2.5 */
```

### 3. 型の範囲超過
```c
/* NG: charの範囲を超える */
char big_num = 300;     /* オーバーフロー */

/* OK: 適切な型を使用 */
int big_num = 300;
```

##  次の章へ

データ型と変数を理解したら、[演算子と式](../operators/README.md) に進んでください。

##  参考資料

- [C言語データ型リファレンス](https://ja.cppreference.com/w/c/language/type)
- [sizeof演算子](https://ja.cppreference.com/w/c/language/sizeof)
- [型変換](https://ja.cppreference.com/w/c/language/conversion)
