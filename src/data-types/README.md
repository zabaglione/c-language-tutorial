# データ型と変数
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
| 型名 | サイズ | 範囲 | 使用例 |
|------|--------|------|--------|
| `char` | 1バイト | -128 〜 127 | 文字（'A'、'B'）、小さな数 |
| `unsigned char` | 1バイト | 0 〜 255 | 文字コード、画像のピクセル値 |
| `short` | 2バイト | -32,768 〜 32,767 | 音声データ、座標値 |
| `unsigned short` | 2バイト | 0 〜 65,535 | ポート番号、色情報 |
| `int` | 4バイト | 約-21億 〜 約21億 | 一般的な整数（年齢、個数など） |
| `unsigned int` | 4バイト | 0 〜 約42億 | 大きな正の数、ビット演算 |
| `long` | 4/8バイト | システム依存 | より大きな整数 |
| `unsigned long` | 4/8バイト | システム依存 | より大きな正の整数 |
**初心者のための型選択ガイド：**
- 普通の整数なら `int` を使う
- 文字を扱うなら `char` を使う
- 負の数が不要なら `unsigned` を付ける
- より大きな数が必要なら `long` を使う
#### 浮動小数点数型（小数を扱う型）
小数点を含む数（3.14、-0.5など）を扱うための型です。
| 型名 | サイズ | 精度 | 使用例 |
|------|--------|------|--------|
| `float` | 4バイト | 約7桁 | ゲームの座標、簡単な計算 |
| `double` | 8バイト | 約15桁 | 科学計算、金額計算 |
| `long double` | 12/16バイト | システム依存 | 超高精度計算 |
**初心者のための型選択ガイド：**
- 通常は `double` を使う（精度が高い）
- メモリを節約したい場合のみ `float` を使う
- `long double` は特殊な用途のみ
#### その他の型
| 型名 | 説明 | 使用例 |
|------|------|--------|
| `void` | 「型なし」を表す | 値を返さない関数、汎用ポインタ |
#### 型のサイズについて
「バイト」はコンピュータのメモリの単位です：
- 1バイト = 8ビット = 8個の0または1
- 1バイトで表現できる数：256通り（2の8乗）
- 4バイトで表現できる数：約42億通り（2の32乗）
サイズが大きいほど、より大きな数や、より精密な小数を扱えます。
### 変数の宣言と初期化 
変数は、データを入れる「箱」のようなものです。箱を使う前に、「どんな種類の箱か」「何という名前の箱か」を決める必要があります。これが変数の宣言です。
#### 変数とは何か？
変数を現実世界に例えると：
- **引き出し**：それぞれに名前（ラベル）が付いていて、中に物を入れられる
- **貯金箱**：お金（数値）を入れたり、取り出したりできる
- **メモ帳**：情報を書いたり、書き換えたりできる
プログラムの中で、変数は値を記憶し、必要なときに取り出せる仕組みです。
#### 基本的な変数宣言
変数を使うには、まず「宣言」が必要です：
```c
int age;        /* 年齢を入れる整数型の箱を用意 */
double height;  /* 身長を入れる小数型の箱を用意 */
char grade;     /* 成績（A、B、Cなど）を入れる文字型の箱を用意 */
```
宣言の構造：
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
変数は宣言と同時に初期値を設定できます。これを「初期化」といいます：
```c
int count = 10;          /* 最初から10が入った箱を用意 */
double pi = 3.14159;     /* 円周率の値で初期化 */
char letter = 'A';       /* 文字'A'で初期化 */
```
**なぜ初期化が重要なのか？**
初期化しない変数には「ゴミ値」（予測できない値）が入っています：
```c
int x;                /* 初期化なし：何が入っているか分からない */
printf("%d\n", x);    /* 予測不能な値が表示される */
int y = 0;            /* 初期化あり：確実に0 */
printf("%d\n", y);    /* 0が表示される */
```
**推奨：変数は必ず初期化しましょう！**
#### 複数変数の同時宣言
同じ型の変数は、まとめて宣言できます：
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
良いプログラムは、変数名を見ただけで何を表すか分かります：
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
int global_var = 100;  /* ファイル全体で使える */
int main(void)
{
    printf("グローバル変数: %d
", global_var);
    return 0;
}```
#### 2. 関数スコープ
関数内で宣言された変数は、その関数内でのみアクセス可能です。
```c
void function_a(void)
{
    int local_a = 10;  /* この関数内でのみ有効 */
    printf("local_a = %d
", local_a);
}
void function_b(void)
{
    /* local_a はここでは使えない */
    int local_b = 20;
    printf("local_b = %d
", local_b);
}```
#### 3. ブロックスコープ
`{` と `}` で囲まれたブロック内でのみアクセス可能な変数です。
```c
int main(void)
{
    int x = 10;
    
    if (x > 5) {
        int y = 20;  /* ifブロック内でのみ有効 */
        printf("x = %d, y = %d
", x, y);
    }
    /* y はここでは使えない */
    
    return 0;
}```
#### 4. スコープの隠蔽（シャドウイング）
内側のスコープで同じ名前の変数を宣言すると、外側の変数が隠蔽されます。
```c
int x = 100;  /* グローバル変数 */
int main(void)
{
    printf("グローバルx = %d
", x);
    
    int x = 200;  /* ローカル変数（グローバルを隠蔽） */
    printf("ローカルx = %d
", x);
    
    return 0;
}```
### 変数の生存期間（Storage Duration） 
変数がメモリ上に存在する期間を生存期間といいます。
#### 1. 自動変数（Automatic Variables）
関数やブロックに入るときに作成され、出るときに破棄される変数です。
```c
void count_calls(void)
{
    int count = 0;  /* 自動変数：毎回0に初期化 */
    count++;
    printf("呼び出し回数: %d
", count);
}```
#### 2. 静的変数（Static Variables）
プログラム開始時に作成され、プログラム終了まで存在し続ける変数です。
```c
void count_calls_static(void)
{
    static int count = 0;  /* 静的変数：値を保持 */
    count++;
    printf("呼び出し回数: %d
", count);
}```
#### 3. 静的グローバル変数
ファイル内でのみアクセス可能なグローバル変数です。
```c
static int file_private = 100;  /* このファイル内でのみ有効 */
int get_private_value(void)
{
    return file_private;
}```
#### 4. レジスタ変数（Register Variables）
可能であればレジスタに格納される変数です（C90では推奨のみ）。
```c
int main(void)
{
    register int i;  /* 高速アクセス用（推奨） */
    
    for (i = 0; i < 1000000; i++) {
        /* 繰り返し処理 */
    }
    
    return 0;
}```
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
    
    printf("a = %d (不定値)
", a);
    printf("b = %d
", b);
    
    return 0;
}```
#### 静的変数の初期化
```c
static int global_static;      /* 0に自動初期化 */
static int global_init = 100;  /* 明示的に初期化 */
void show_values(void)
{
    static int local_static;   /* 0に自動初期化 */
    printf("静的変数: %d, %d, %d
", 
           global_static, global_init, local_static);
}```
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
    printf("ID: %d
", get_next_id());  /* 1 */
    printf("ID: %d
", get_next_id());  /* 2 */
    printf("ID: %d
", get_next_id());  /* 3 */
    return 0;
}```
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
/*
 * ファイル名: data_types_demo_c99.c
 * 説明: C言語の基本データ型の使用例（C99版）
 * 規格: C99準拠
 */
#include <stdio.h>
int main(void)
{
    printf("=== データ型のサイズと値 ===\n");
    // 整数型の変数宣言と初期化（使用箇所で宣言）
    char letter = 'A';
    printf("char     : %lu バイト, 値: %c (%d)\n",
           sizeof(char), letter, letter);
    short small_num = 1000;
    printf("short    : %lu バイト, 値: %d\n",
           sizeof(short), small_num);
    int age = 25;
    printf("int      : %lu バイト, 値: %d\n",
           sizeof(int), age);
    long big_num = 1234567L;
    printf("long     : %lu バイト, 値: %ld\n",
           sizeof(long), big_num);
    unsigned int positive = 100U;
    printf("unsigned : %lu バイト, 値: %u\n",
           sizeof(unsigned int), positive);
    // 浮動小数点型の変数宣言と初期化
    float pi_f = 3.14f;
    printf("float    : %lu バイト, 値: %.6f\n",
           sizeof(float), pi_f);
    double pi_d = 3.141592653589793;
    printf("double   : %lu バイト, 値: %.15f\n",
           sizeof(double), pi_d);
    // 演算の例
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
## サンプルコード
### data_types_demo.c