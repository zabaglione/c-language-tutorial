# データ型と変数

##  対応C規格

- **主要対象:** C90
- **学習内容:** 基本データ型、変数宣言、初期化、スコープ、変数の生存期間

##  学習目標
この章を完了すると、以下のことができるようになります。

- C言語の基本データ型を理解する
- 変数の宣言と初期化ができる
- 変数のスコープ（有効範囲）を理解する
- データ型のサイズと範囲を把握する
- 適切な型を選択してプログラムを作成できる

##  概要と詳細

### データ型と変数の世界へようこそ
プログラミングでは、様々な種類のデータを扱います。数字、文字、文章など、それぞれのデータには適切な「入れ物」が必要です。この「入れ物」がデータ型で、その入れ物に名前を付けたものが変数です。

例えば、年齢を記録するなら整数の入れ物（int型）、身長を記録するなら小数の入れ物（double型）を使います。この章では、C言語で使えるデータ型と、変数の使い方を学びます。

### C言語の基本データ型 
C言語には、扱うデータの種類に応じて様々なデータ型が用意されています。まずは最も基本的な型から見ていきましょう。

#### なぜデータ型が必要なのか？

コンピュータのメモリは「0」と「1」の集まりです。データ型は、この0と1の並びをどのように解釈するかを決める「ルール」です。同じ0と1の並びでも、整数として読むか、文字として読むかで意味が変わります。

また、データ型によってメモリの使用量も変わります。大きな数を扱うには大きな入れ物が必要ですが、小さな数なら小さな入れ物で十分です。適切なデータ型を選ぶことで、効率的なプログラムが書けます。

#### 整数型（整数を扱う型）
整数型は、小数点のない数（...、-2、-1、0、1、2、...）を扱うための型です。

**注意**: 以下の表のサイズと範囲は一般的な値です。実際のサイズは使用するコンピュータやコンパイラによって異なる場合があります。確実なサイズが必要な場合は`sizeof`演算子で確認してください。

| 型名 | サイズ | 範囲 | 使用例 |
|------|--------|------|--------|
| `char` | 1バイト | -128 〜 127 | 文字（'A'、'B'）、小さな数 |
| `unsigned char` | 1バイト | 0 〜 255 | 文字コード、画像のピクセル値 |
| `short` | 2バイト以上 | -32,768 〜 32,767以上 | 音声データ、座標値 |
| `unsigned short` | 2バイト以上 | 0 〜 65,535以上 | ポート番号、色情報 |
| `int` | 2バイト以上 | 約-32,768以上 | 一般的な整数（年齢、個数など） |
| `unsigned int` | 2バイト以上 | 0以上 | 大きな正の数、ビット演算 |
| `long` | 4バイト以上 | システム依存 | より大きな整数 |
| `unsigned long` | 4バイト以上 | システム依存 | より大きな正の整数 |

##### 初心者のための型選択ガイド（整数型）

- 普通の整数なら `int` を使う
- 文字を扱うなら `char` を使う
- 負の数が不要なら `unsigned` を付ける
- より大きな数が必要なら `long` を使う

#### 浮動小数点数型（小数を扱う型）
小数点を含む数（3.14、-0.5など）を扱うための型です。

| 型名 | サイズ | 精度 | 使用例 |
|------|--------|------|--------|
| `float` | 4バイト以上 | 約6-7桁 | ゲームの座標、簡単な計算 |
| `double` | 8バイト以上 | 約15-16桁 | 科学計算、金額計算 |
| `long double` | 8バイト以上 | システム依存 | 超高精度計算 |

##### 初心者のための型選択ガイド（浮動小数点数型）

- 通常は `double` を使う（精度が高い）
- メモリを節約したい場合のみ `float` を使う
- `long double` は特殊な用途のみ

#### その他の型

| 型名 | 説明 | 使用例 |
|------|------|--------|
| `void` | 「型なし」を表す | 値を返さない関数、汎用ポインタ |

#### 型のサイズについて
「バイト」はコンピュータのメモリの単位です。

- 1バイト = 8ビット = 8個の0または1
- 1バイトで表現できる数：256通り（2の8乗）
- 4バイトで表現できる数：約42億通り（2の32乗）
サイズが大きいほど、より大きな数や、より精密な小数を扱えます。

### 変数の宣言と初期化 
変数は、データを入れる「箱」のようなものです。箱を使う前に、「どんな種類の箱か」「何という名前の箱か」を決める必要があります。これが変数の宣言です。

#### 変数とは何か？
変数を現実世界に例えると。

- **引き出し**：それぞれに名前（ラベル）が付いていて、中に物を入れられる
- **貯金箱**：お金（数値）を入れたり、取り出したりできる
- **メモ帳**：情報を書いたり、書き換えたりできる
プログラムの中で、変数は値を記憶し、必要なときに取り出せる仕組みです。

#### 基本的な変数宣言
変数を使うには、まず「宣言」が必要です。

```c
int age;        /* 年齢を入れる整数型の箱を用意 */
double height;  /* 身長を入れる小数型の箱を用意 */
char grade;     /* 成績（A、B、Cなど）を入れる文字型の箱を用意 */
```
宣言の構造。

```
データ型 変数名;
```
**変数名のルール：**

1. 英字（a-z、A-Z）、数字（0-9）、アンダースコア（_）が使える
2. 数字から始めることはできない
3. C言語の予約語（int、if、forなど）は使えない
4. 大文字と小文字は区別される（ageとAgeは別の変数）
**良い変数名の例：**

```c
int studentAge;      /* 学生の年齢 */
double roomTemperature;  /* 室温 */
char firstInitial;   /* 名前のイニシャル */
```
**悪い変数名の例：**

```c
int 2ndPlace;    /* NG: 数字で始まっている */
double my-score;  /* NG: ハイフンは使えない */
char int;        /* NG: 予約語は使えない */
```

#### 初期化付き宣言
変数は宣言と同時に初期値を設定できます。これを「初期化」といいます。

```c
int count = 10;          /* 最初から10が入った箱を用意 */
double pi = 3.14159;     /* 円周率の値で初期化 */
char letter = 'A';       /* 文字'A'で初期化 */
```
**なぜ初期化が重要なのか？**
初期化しない変数には「ゴミ値」（予測できない値）が入っています。

```c
int x;                /* 初期化なし：何が入っているか分からない */
printf("%d\n", x);    /* 予測不能な値が表示される */
int y = 0;            /* 初期化あり：確実に0 */
printf("%d\n", y);    /* 0が表示される */
```
**推奨：変数は必ず初期化しましょう！**

#### 複数変数の同時宣言
同じ型の変数は、まとめて宣言できます。

```c
/* 3つの整数変数を一度に宣言 */
int x, y, z;
/* 宣言と初期化を混ぜることも可能 */
int a = 1, b = 2, c;  /* aは1、bは2、cは未初期化 */
/* より読みやすい書き方（推奨） */
int width = 100;
int height = 200;
int depth = 50;
```

#### 変数の命名規則（ベストプラクティス）
良いプログラムは、変数名を見ただけで何を表すか分かります。
**1. 意味のある名前を使う**

```c
/* 悪い例 */
int a, b, c;
/* 良い例 */
int width, height, area;
```
**2. 命名スタイルを統一する**

```c
/* キャメルケース（推奨） */
int studentAge;
double averageScore;
/* スネークケース */
int student_age;
double average_score;
```
**3. 適切な長さにする**

```c
/* 短すぎる */
int s;  /* sが何を表すか不明 */
/* ちょうど良い */
int score;
/* 長すぎる */
int theScoreOfTheStudentInTheMathematicsExam;
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
異なるデータ型の間で値を変換することを型変換（キャスト）といいます。C言語では自動的に行われる場合と、明示的に指定する場合があります。

#### 暗黙の型変換（自動型変換）
コンパイラが自動的に型を変換します。一般的に、小さい型から大きい型への変換は安全です。

```c
int i = 42;
double d;
d = i;          /* int から double への自動変換 */

char c = 'A';
int num = c;    /* char から int への自動変換（65になる） */

float f = 3.14f;
double d2 = f;  /* float から double への自動変換 */
```

**変換の優先順位（低→高）**：
`char` → `short` → `int` → `long` → `float` → `double` → `long double`

#### 明示的な型変換（キャスト）
プログラマが意図的に型を変換する場合は、キャスト演算子を使います。

```c
double pi = 3.14159;
int rounded = (int)pi;      /* 小数部分を切り捨て（3になる） */

int total = 100;
int count = 3;
double average = (double)total / count;  /* 33.333... になる */

char letter = (char)65;     /* 'A' になる */
```

#### 型変換の注意点

##### 1. 精度の損失

```c
double big = 1234567890.123456;
float small = (float)big;   /* 精度が失われる */
printf("%.6f\n", small);    /* 1234567936.000000 など */
```

##### 2. 整数除算の罠

```c
int a = 5, b = 2;
double result;
result = a / b;         /* 結果: 2.0 (整数除算後に変換) */
result = (double)a / b; /* 結果: 2.5 (実数除算) */
result = a / (double)b; /* 結果: 2.5 (これでもOK) */
```

##### 3. オーバーフローに注意

```c
int big_int = 100000;
short small_short = (short)big_int;  /* オーバーフロー発生 */
printf("%d\n", small_short);          /* 予期しない値 */

unsigned int positive = 4294967295;   /* unsignedの最大値 */
int negative = (int)positive;         /* -1 になる */
```

##### 4. 符号の扱い

```c
int neg = -100;
unsigned int pos = (unsigned int)neg;  /* 大きな正の数になる */
printf("%u\n", pos);                   /* 4294967196 など */
```

### 変数のスコープ（有効範囲） 
スコープとは、変数がプログラム中のどの部分でアクセス可能かを示す概念です。変数を適切なスコープで管理することで、メモリの効率的な使用とバグの少ないプログラムが実現できます。

#### スコープを理解することの重要性

1. **名前の衝突を防ぐ** - 同じ名前の変数を異なるスコープで使える
2. **メモリの効率的利用** - 必要な期間だけメモリを使用
3. **プログラムの保守性向上** - 変数の影響範囲が限定される
4. **バグの削減** - 意図しない変数へのアクセスを防げる

#### 1. ファイルスコープ（グローバルスコープ）
ファイル全体でアクセス可能な変数です。

```c
int global_var = 100;  /* ファイル全体で使える */

int main(void)
{
    printf("グローバル変数: %d\n", global_var);
    return 0;
}
```

#### 2. 関数スコープ
関数内で宣言された変数は、その関数内でのみアクセス可能です。

```c
void function_a(void)
{
    int local_a = 10;  /* この関数内でのみ有効 */
    printf("local_a = %d\n", local_a);
}

void function_b(void)
{
    /* local_a はここでは使えない */
    int local_b = 20;
    printf("local_b = %d\n", local_b);
}
```

#### 3. ブロックスコープ
`{` と `}` で囲まれたブロック内でのみアクセス可能な変数です。

```c
int main(void)
{
    int x = 10;
    
    if (x > 5) {
        int y = 20;  /* ifブロック内でのみ有効 */
        printf("x = %d, y = %d\n", x, y);
    }
    /* y はここでは使えない */
    
    return 0;
}
```

#### 4. スコープの隠蔽（シャドウイング）
内側のスコープで同じ名前の変数を宣言すると、外側の変数が隠蔽されます。

```c
int x = 100;  /* グローバル変数 */

int main(void)
{
    printf("グローバルx = %d\n", x);
    
    {
        int x = 200;  /* ローカル変数（グローバルを隠蔽） */
        printf("ローカルx = %d\n", x);
    }
    
    printf("グローバルx（再度）= %d\n", x);
    
    return 0;
}
```

### 変数の生存期間（Storage Duration） 
変数がメモリ上に存在する期間を生存期間といいます。スコープが「どこから見えるか」を決めるのに対し、生存期間は「いつまで存在するか」を決めます。

#### 生存期間とスコープの違い

- **スコープ**: 変数にアクセスできる範囲（空間的な概念）
- **生存期間**: 変数がメモリに存在する期間（時間的な概念）

同じスコープでも生存期間が異なる場合があり、この違いを理解することが重要です。

#### 1. 自動変数（Automatic Variables）
関数やブロックに入るときに作成され、出るときに破棄される変数です。

**特徴**:

- デフォルトの生存期間（何も指定しない場合）
- スタック領域に確保される
- 関数が呼ばれるたびに新しく作られる
- 初期化しないと不定値（ゴミ値）を持つ

```c
void count_calls(void)
{
    int count = 0;  /* 自動変数：毎回0に初期化 */
    count++;
    printf("呼び出し回数: %d\n", count);  /* 常に1が表示される */
}

/* メイン関数での例 */
int main(void)
{
    count_calls();  /* 1 */
    count_calls();  /* 1 */
    count_calls();  /* 1 */
    return 0;
}
```

#### 2. 静的変数（Static Variables）
プログラム開始時に作成され、プログラム終了まで存在し続ける変数です。

**特徴**:

- プログラム実行中ずっと存在
- データ領域（静的領域）に確保される
- 自動的に0で初期化される
- 関数を抜けても値を保持する

```c
void count_calls_static(void)
{
    static int count = 0;  /* 静的変数：初回のみ初期化 */
    count++;
    printf("呼び出し回数: %d\n", count);
}

/* メイン関数での例 */
int main(void)
{
    count_calls_static();  /* 1 */
    count_calls_static();  /* 2 */
    count_calls_static();  /* 3 */
    return 0;
}
```

**静的変数の用途**:

- 関数呼び出し間での状態保持
- カウンターやフラグの実装
- 初回実行時のみの処理制御

#### 3. 静的グローバル変数
ファイル内でのみアクセス可能なグローバル変数です。

**特徴**:

- グローバル変数と同じ生存期間（プログラム全体）
- ファイルスコープに限定（他のファイルから見えない）
- 名前の衝突を防げる
- モジュール内部の状態管理に最適

```c
/* file1.c */
static int file_private = 100;  /* このファイル内でのみ有効 */

int get_private_value(void)
{
    return file_private;
}

void set_private_value(int value)
{
    file_private = value;
}

/* file2.c */
/* static int file_private = 200;  他のファイルなら同名でもOK */
```

#### 4. レジスタ変数（Register Variables）
可能であればレジスタに格納される変数です（C90では推奨のみ）。

**特徴**:

- CPUレジスタへの格納を要求（保証はされない）
- アドレス演算子（&）が使えない
- 自動変数と同じ生存期間
- 現代のコンパイラでは最適化で自動判断

```c
int main(void)
{
    register int i;  /* 高速アクセス用（推奨） */
    
    for (i = 0; i < 1000000; i++) {
        /* 繰り返し処理 */
    }
    
    /* &i は使えない（エラーになる） */
    
    return 0;
}
```

**注意**: 現代のコンパイラは自動的に最適化するため、registerキーワードの効果は限定的です。

#### 生存期間の実践的な比較例
以下のプログラムで、各種変数の生存期間の違いを確認できます：

```c
#include <stdio.h>

int global = 100;              /* グローバル変数（プログラム全体） */
static int static_global = 200; /* 静的グローバル（プログラム全体） */

void demonstrate_lifetime(void)
{
    int auto_var = 0;          /* 自動変数（関数実行中のみ） */
    static int static_var = 0; /* 静的変数（プログラム全体） */
    
    auto_var++;
    static_var++;
    global++;
    static_global++;
    
    printf("自動変数: %d, 静的変数: %d\n", auto_var, static_var);
    printf("グローバル: %d, 静的グローバル: %d\n", global, static_global);
}

int main(void)
{
    printf("=== 1回目の呼び出し ===\n");
    demonstrate_lifetime();
    
    printf("\n=== 2回目の呼び出し ===\n");
    demonstrate_lifetime();
    
    printf("\n=== 3回目の呼び出し ===\n");
    demonstrate_lifetime();
    
    return 0;
}
/* 出力結果:
   自動変数は毎回1、静的変数は1,2,3と増加
   グローバル変数も増加し続ける */
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
    int a;        /* 初期化なし：不定値 */
    int b = 10;   /* 初期化あり：10 */
    
    printf("a = %d (不定値)\n", a);
    printf("b = %d\n", b);
    
    return 0;
}
```

#### 静的変数の初期化

```c
static int global_static;      /* 0に自動初期化 */
static int global_init = 100;  /* 明示的に初期化 */

void show_values(void)
{
    static int local_static;   /* 0に自動初期化 */
    printf("静的変数: %d, %d, %d\n", 
           global_static, global_init, local_static);
}
```

### 実践的なスコープ活用例 

#### カウンター関数の実装

```c
int get_next_id(void)
{
    static int id = 0;  /* 静的変数で状態を保持 */
    return ++id;
}

int main(void)
{
    printf("ID: %d\n", get_next_id());  /* 1 */
    printf("ID: %d\n", get_next_id());  /* 2 */
    printf("ID: %d\n", get_next_id());  /* 3 */
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
プログラムで変更されない値を定数として定義することで、コードの可読性と保守性が向上します。C言語では主に2つの方法で定数を定義できます。

#### なぜ定数を使うのか？

1. **マジックナンバーの排除** - 意味不明な数値をなくす
2. **一括変更が容易** - 定数の値を1箇所で管理
3. **意図の明確化** - 値の意味が明確になる
4. **誤った変更の防止** - 値が変更されないことを保証

#### `const`キーワード（型付き定数）
`const`修飾子を使って、変数を読み取り専用にします。

```c
const int MAX_SIZE = 100;           /* 整数定数 */
const double PI = 3.14159265359;    /* 浮動小数点定数 */
const char NEWLINE = '\n';          /* 文字定数 */

/* 配列のサイズには使えない（C90） */
/* const int SIZE = 10; */
/* int array[SIZE];     エラー！ */

/* ポインタと const */
const char *str = "Hello";          /* 文字列の内容を変更不可 */
char * const ptr = buffer;          /* ポインタ自体を変更不可 */
const char * const cptr = "World";  /* 両方とも変更不可 */
```

**const の特徴**:

- 型安全性がある
- デバッガで値を確認できる
- スコープの制御が可能
- C90では配列サイズに使えない

#### `#define`プリプロセッサ（マクロ定数）
プリプロセッサ指令で、コンパイル前にテキスト置換を行います。

```c
#define MAX_STUDENTS 50              /* 数値定数 */
#define PI 3.14159265359            /* 浮動小数点定数 */
#define TITLE "C Language Tutorial"  /* 文字列定数 */
#define TRUE 1                       /* 論理定数 */
#define FALSE 0

/* 配列のサイズに使える */
int scores[MAX_STUDENTS];

/* 式も定義可能（括弧推奨） */
#define SQUARE(x) ((x) * (x))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
```

**#define の特徴**:

- 型情報を持たない
- どこでも使える（配列サイズなど）
- プリプロセス時に単純置換
- デバッグが難しい場合がある

#### const vs #define の使い分け

| 特徴 | const | #define |
|------|-------|---------|
| 型チェック | あり | なし |
| スコープ | あり | なし（ファイル全体） |
| デバッグ | 容易 | 困難 |
| 配列サイズ（C90） | 使用不可 | 使用可能 |
| メモリ使用 | 変数として確保 | 置換のみ |

**使い分けの指針**:

- 一般的な定数 → `const` を優先
- 配列サイズ → `#define`（C90）
- 条件コンパイル → `#define`
- 簡単なマクロ → `#define`

#### 定数定義のベストプラクティス

```c
/* 命名規則：全て大文字、単語はアンダースコアで区切る */
#define MAX_BUFFER_SIZE 1024
#define DEFAULT_TIMEOUT 30
#define ERROR_FILE_NOT_FOUND -1

/* 関連する定数はグループ化 */
/* ファイルシステム関連 */
#define MAX_PATH_LENGTH 260
#define MAX_FILENAME_LENGTH 255

/* ネットワーク関連 */
#define DEFAULT_PORT 8080
#define MAX_CONNECTIONS 100

/* エラーコード */
#define SUCCESS 0
#define ERROR_INVALID_ARGUMENT -1
#define ERROR_OUT_OF_MEMORY -2
```

#### enum を使った定数定義
関連する定数のグループは列挙型を使うと便利です。

```c
/* 曜日の定数 */
enum weekday {
    SUNDAY,    /* 0 */
    MONDAY,    /* 1 */
    TUESDAY,   /* 2 */
    WEDNESDAY, /* 3 */
    THURSDAY,  /* 4 */
    FRIDAY,    /* 5 */
    SATURDAY   /* 6 */
};

/* 明示的な値の指定 */
enum status {
    STATUS_OK = 0,
    STATUS_ERROR = -1,
    STATUS_BUSY = 100
};
```

### データ型のサイズ確認 
`sizeof`演算子を使ってデータ型のサイズを確認できます。sizeof演算子には2つの形式があります。

#### sizeof演算子の2つの形式

1. **sizeof(型名)** - 型名には必ず括弧が必要
2. **sizeof 式** - 式には括弧は任意（つけてもよい）

```c
/* 形式1: sizeof(型名) - 括弧が必要 */
size_t size1 = sizeof(int);        /* 正しい */
size_t size2 = sizeof(double);     /* 正しい */
/* size_t size3 = sizeof int;      エラー！括弧が必要 */

/* 形式2: sizeof 式 - 括弧は任意 */
int num = 42;
size_t size4 = sizeof num;         /* 正しい（括弧なし） */
size_t size5 = sizeof(num);        /* 正しい（括弧あり） */
size_t size6 = sizeof num + 1;     /* sizeof num の後に +1 */
```

#### sizeof演算子の特性

- **コンパイル時に評価**: 実行時ではなくコンパイル時にサイズが決定
- **型は size_t**: 結果の型は size_t（符号なし整数型）
- **副作用なし**: sizeof(i++) のような式でも i は増加しない

#### 実用的な使用例

```c
/* 配列の要素数を計算 */
int array[10];
size_t count = sizeof array / sizeof array[0];  /* 要素数 = 10 */

/* ポインタと配列の違い */
char arr[] = "Hello";     /* 配列: 6バイト（null終端含む） */
char *ptr = "Hello";      /* ポインタ: 8バイト（64ビット環境） */

/* 動的メモリ確保での使用 */
int *p = malloc(sizeof(int) * 100);  /* int型100個分 */
```

#### サンプルプログラム
完全な実装例は以下のファイルを参照してください：

- [sizeof_demo.c](examples/sizeof_demo.c) - C90準拠版
- [sizeof_demo_c99.c](examples/sizeof_demo_c99.c) - C99準拠版（可変長配列対応）

##  コンパイル方法
この章では以下のMakefileを使用してコンパイルができます。

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
データ型のサイズはシステムに依存するため、portable（移植可能）なプログラムを書く際は注意が必要です。

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

## 演習問題

この章の内容を理解したら、[演習問題](exercises/)に挑戦してみましょう。

- 基礎問題：基本的な文法や概念の確認
- 応用問題：より実践的なプログラムの作成
- チャレンジ問題：高度な理解と実装力が必要な問題