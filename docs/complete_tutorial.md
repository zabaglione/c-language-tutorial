---
title: "C言語学習教材"
subtitle: "基礎から応用まで体系的に学ぶ"
author: ""
date: "2024年6月28日"
lang: ja
documentclass: book
geometry: margin=2.5cm
fontsize: 11pt
mainfont: "Hiragino Kaku Gothic ProN"
monofont: "Source Code Pro"
toc: true
toc-depth: 3
numbersections: true
colorlinks: true
linkcolor: blue
urlcolor: blue
citecolor: blue
---
# はじめに

本書は、C言語の基礎から応用まで、体系的に学習できる教材です。マイコン開発を見据えたビット操作も含め、実践的なプログラミングスキルを身につけることができます。

## 対応C規格

本教材は以下のC言語規格に対応しています：

- **C90** (ANSI C): 基本的な文法とライブラリ
- **C99**: bool型、可変長配列、forループ内宣言など
- **C11**: 匿名構造体、_Generic選択、_Static_assertなど  
- **C17**: C11のマイナーアップデート版

## 学習目標

### 初心者レベル完了時
- C言語の基本文法を理解
- 簡単なプログラムを作成可能
- 配列と関数を使った処理が書ける

### 中級レベル完了時  
- ポインターを理解し活用可能
- 構造体を使ったデータ管理ができる
- ビット操作でハードウェア制御が理解できる

### 発展レベル完了時
- メモリ管理を理解
- 大規模なプログラム開発の基礎を習得
- C言語の高度な機能を活用可能

## 学習方法

1. **README.md** で理論を学習
2. **examples/** でサンプルコードを確認・実行
3. **exercises/** で演習課題に挑戦
4. **solutions/** で解答例を確認

\newpage

#  第1章: 導入・環境構築

##  対応C規格
- **主要対象:** 全規格共通
- **学習内容:** C言語の基礎知識、開発環境構築、規格解説

##  学習目標

この章を完了すると、以下のことができるようになります：

- C言語の特徴と歴史を理解する
- 開発環境を構築し、基本的なコンパイル手順を覚える
- C言語の規格（C90, C99, C, C17）の違いを理解する
- 簡単なプログラムをコンパイル・実行できる

##  理論解説

### C言語とは 

C言語は1972年にデニス・リッチーがベル研稶所で開発したプログラミング言語です。以下の特徴があります：

#### 主な特徴
- **システムプログラミング向け**: OS開発やハードウェア制御に適している
- **高い移植性**: 異なるプラットフォーム間でのコード再利用が容易
- **効率性**: メモリとCPUの使用効率が良い
- **シンプルな文法**: 基本的な機能に絞られた明確な仕様

#### 使用分野
- オペレーティングシステム（Linux、Windows等）
- 組込みシステム（マイコン、IoTデバイス）
- データベースシステム
- ゲームエンジン
- 科学技術計算

### C言語の規格 

C言語は時代とともに進化し、複数の規格が策定されています：

| 規格名 | 発表年 | 正式名称 | 主な特徴 |
|--------|--------|----------|----------|
| **C90** | 1990年 | ISO/IEC 9899:1990 | 初の国際標準、ANSI C |
| **C99** | 1999年 | ISO/IEC 9899:1999 | _Bool型、可変長配列、inline関数 |
| **C** | 2011年 | ISO/IEC 9899:2011 | 匿名構造体、_Generic、マルチスレッド |
| **C17** | 2018年 | ISO/IEC 9899:2018 | Cのバグ修正版 |

#### 規格選択の指針
- **学習目的**: C90から始めて段階的に新機能を学習
- **業務開発**: C99以降を推奨（実用的な機能が多い）
- **組込み**: C90またはC99（コンパイラ対応状況による）

### 開発環境 

C言語プログラムの開発には以下のツールが必要です：

#### 必須ツール
1. **テキストエディター**: コードを記述するツール
2. **コンパイラ**: ソースコードを実行ファイルに変換
3. **リンカー**: 複数のオブジェクトファイルを結合
4. **デバッガー**: プログラムの動作を詳細に調査

#### 推奨開発環境

**Windows:**
```bash
# MinGW-w64のインストール（推奨）
# または Microsoft Visual Studio Community
```

**macOS:**
```bash
# Xcode Command Line T_Boolsのインストール
xcode-select --install
```

**Linux（Ubuntu/Debian）:**
```bash
sudo apt uupdate
sudo apt install build-essential
```

### コンパイル手順 

C言語プログラムの実行までの流れ：

1. **ソースコード作成**（.cファイル）
2. **プリプロセッサ処理**（#includeの展開等）
3. **コンパイル**（アセンブリコードに変換）
4. **アセンブル**（オブジェクトファイルに変換）
5. **リンク**（実行ファイルの生成）
6. **実行**

#### 基本的なコンパイルコマンド
```bash
# 一段階でコンパイル
gcc program.c -o program

# 段階的なコンパイル
gcc -c program.c          # オブジェクトファイル作成
gcc program.o -o program  # 実行ファイル作成
```

##  サンプルコード

### 環境確認プログラム

プログラムファイル: `examples/environument_check.c`

このプログラムは開発環境が正しく設定されているかを確認します。

### コンパイルと実行

```bash
# examples ディレクトリに移動
cd examples

# C90準拠でコンパイル
gcc -std=c90 -Wall -Wextra -pedantic environument_check.c -o env_check_c90

# C99準拠でコンパイル
gcc -std=c99 -Wall -Wextra -pedantic environument_check.c -o env_check_c99

# 実行
./env_check_c90
```

##  演習課題

### 基礎問題

1. **環境構築確認**
   - サンプルプログラムを正常にコンパイル・実行できることを確認してください
   - C90、C99、Cの各規格でコンパイルを試してください

2. **コンパイラ情報の確認**
   - 使用しているコンパイラの名前とバージョンを調べてください
   - 対応している規格を確認してください

### 応用問題

1. **規格比較**
   - C90とC99の主な違いを3つ以上挙げてください
   - 組込み開発でC90が今でも使われる理由を考えてください

2. **コンパイル手順の理解**
   - プリプロセッサ、コンパイラ、リンカーの役割を説明してください
   - `-E`, `-S`, `-c` オプションの効果を確認してください

##  コンパイル方法

この章では以下のMakefileを使用してコンパイルができます：

```bash
# 全ての例題をコンパイル
make all

# C90準拠でコンパイル
make STANDARD=c90

# C99準拠でコンパイル  
make STANDARD=c99

# C準拠でコンパイル
make STANDARD=c11

# クリーンアップ
make clean
```

##  規格による違い

この章では基本的な環境確認のため、規格による大きな違いはありません。ただし、コンパイラの警告やエラーメッセージに違いが出る場合があります。

##  次の章へ


##  参考資料

- [GCC公式ドキュメント](https://gcc.gnu.org/documentation.html)
- [C言語規格書 (ISO/IEC 9899:2018)](https://www.iso.org/standard/74528.html)
- [GNU Make マニュアル](https://www.gnu.org/software/make/manual/)

\newpage

#  第2章: 基本文法・Hello World

##  対応C規格
- **主要対象:** C90
- **学習内容:** プログラムの基本構造、main関数、printf関数

##  学習目標

この章を完了すると、以下のことができるようになります：

- C言語プログラムの基本構造を理解する
- main関数の役割を理解する
- printf関数を使った文字列出力ができる
- コメントの書き方を覚える
- 基本的なエスケープシーケンスを使える

##  理論解説

### プログラムの基本構造 

C言語のプログラムは以下の基本構造を持ちます：

```c
#include <stdio.h>    /* ヘッダーファイルのインクルード */

int main(void)        /* メイン関数の定義 */

    printf("Hello, World!\n");  /* 処理文 */
    return 0;         /* 戻り値 */

```

#### 各部分の説明

1. **プリプロセッサ指令** (`#include`)
   - ヘッダーファイルを取り込む指令
   - `stdio.h`は標準入出力関数の宣言を含む

2. **main関数**
   - プログラムの実行開始点
   - すべてのC言語プログラムに必須

3. **関数本体**（`{` と `}` で囲まれた部分）
   - 実際の処理を記述する場所

4. **return文**
   - 関数の終了と戻り値の指定

### main関数の詳細 

main関数はプログラムの**エントリーポイント**（実行開始点）です。

#### main関数の形式

**標準的な形式:**
```c
int main(void)
{
    /* プログラムの処理 */
    return 0;

```

**コマンドライン引数を受け取る形式:**
```c
int main(int argc, char *argv[])
{
    /* プログラムの処理 */
    return 0;

```

#### 戻り値の意味
- **0**: プログラムが正常終了
- **0以外**: エラーで終了（エラーコード）

### printf関数 

printf関数は**フォーマット付き出力**を実行う標準ライブラリ関数です。

#### 基本的な使い方

```c
printf("Hello, World!\n");
```

#### フォーマット指定子

| 指定子 | データ型 | 説明 | 例 |
|--------|----------|------|-----|
| `%d` | int | 10進整数 | `printf("%d", 42);` |
| `%c` | char | 文字 | `printf("%c", 'A');` |
| `%s` | char* | 文字列 | `printf("%s", "Hello");` |
| `%f` | double | 浮動小数点数 | `printf("%f", 3.14);` |

#### エスケープシーケンス

特殊文字を表現するための記号です：

| シーケンス | 意味 | 説明 |
|------------|------|------|
| `\n` | 改行 | 次の実行に移る |
| `\t` | タブ | タブ文字を挿入 |
| `\"` | ダブルクォート | 文字列内で`"`を表示 |
| `\\` | バックスラッシュ | `\`文字を表示 |

### コメント 

プログラムに説明を追加するためのコメント記法：

#### C90スタイル
```c
/* これは複数実行にわたる
   コメントです */

/* 1行コメント */
```

#### C99以降のスタイル
```c
// これは1行コメントです（C99以降）
```

**重要:** この章ではC90準拠のため、`/* */` スタイルを使用します。

### 基本的なプログラム例 

#### 例: 単純な文字列出力
```c
#include <stdio.h>

int main(void)
{
    printf("Hello, World!\n");
    return 0;

```

#### 例: 複数実行の出力
```c
#include <stdio.h>

int main(void)
{
    printf("C言語学習教材\n");
    printf("第2章: 基本文法・Hello World\n");
    printf("プログラムが正常に動作しています！\n");
    return 0;

```

#### 例: エスケープシーケンスの使用
```c
#include <stdio.h>

int main(void)
{
    printf("タブ区切り:\tアイテム1\tアイテム2\n");
    printf("引用符の表示: \"Hello, World!\"\n");
    printf("パス表示: C:\\Program Files\\MyApp\n");
    return 0;

```

##  サンプルコード

### Hello Worldプログラム

プログラムファイル: `examples/hello_world.c`

もっとも基本的なC言語プログラムです。

### フォーマット出力プログラム

プログラムファイル: `examples/formatted_output.c`

printf関数のさまざまな使い方を学習します。

### コンパイルと実行

```bash
# examples ディレクトリに移動
cd examples

# C90準拠でコンパイル
gcc -std=c90 -Wall -Wextra -pedantic hello_world.c -o hello_world

# 実行
./hello_world
```

##  演習課題

### 基礎問題

1. **Hello World**
   - 自分の名前を表示するプログラムを作成してください

2. **複数実行出力**
   - 好きな詩や歌詞を3実行以上で表示するプログラムを作成してください

3. **エスケープシーケンス**
   - タブとダブルクォートを使った表示プログラムを作成してください

### 応用問題

1. **フォーマット文字列**
   - printf関数のさまざまなフォーマット指定子を試してください

2. **プログラム構造の理解**
   - main関数の戻り値を変更して動作を確認してください

##  コンパイル方法

この章では以下のMakefileを使用してコンパイルができます：

```bash
# 全ての例題をコンパイル
make all

# 特定のプログラムをコンパイル
make hello_world

# 実行
make run

# クリーンアップ
make clean
```

##  規格による違い

### C90での制限事項
- コメントは `/* */` 形式のみ
- 変数宣言は関数やブロックの先頭で実行う
- forループ内での変数宣言は不可

### C99以降の拡張
- `//` 形式のコメント追加
- forループ内での変数宣言が可能
- 複合リテラル等の新機能

##  次の章へ


##  参考資料

- [printf関数リファレンス](https://ja.cppreference.com/w/c/io/fprintf)
- [エスケープシーケンス一覧](https://ja.cppreference.com/w/c/language/escape)
- [C90規格仕様](https://www.iso.org/standard/17782.html)

\newpage

#  第3章: データ型・変数・スコープ

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

プログラムファイル: `examples/data_types_demo.c`

各データ型の宣言、初期化、出力を学習します。

### 変数スコープの確認

プログラムファイル: `examples/scope_demo.c`

グローバル変数とローカル変数の違いを確認します。

### 型変換の実例

プログラムファイル: `examples/type_conversion.c`

暗黙的・明示的型変換の動作を学習します。

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


##  参考資料

- [C言語データ型リファレンス](https://ja.cppreference.com/w/c/language/type)
- [sizeof演算子](https://ja.cppreference.com/w/c/language/sizeof)
- [型変換](https://ja.cppreference.com/w/c/language/conversion)

\newpage

#  第章: 演算子と式

##  対応C規格
- **主要対象:** C90
- **学習内容:** 算術演算子、関係演算子、論理演算子、ビット演算子、演算子の優先順位

##  学習目標

この章を完了すると、以下のことができるようになります：

- さまざまな演算子の種類と使い方を理解する
- 演算子の優先順位と結合規則を把握する
- 複雑な式を正しく記述できる
- インクリメント・デクリメント演算子を適切に使える
- 64ビット演算の基本を理解する

##  理論解説

### 算術演算子 

基本的な数値計算を実行う演算子です。

| 演算子 | 意味 | 例 | 結果 |
|--------|------|----|----- |
| `+` | 加算 | ` + ` | `` |
| `-` | 減算 | ` - ` | `` |
| `*` | 乗算 | ` * ` | `` |
| `/` | 除算 | ` / ` | `` (整数除算) |
| `%` | 剰余 | ` % ` | `` |

#### 除算の注意点

```c
int a = , b = ;
int result = a / b;        /* 結果:  (整数除算) */
double result = a / b;     /* 結果: . (整数除算後に型変換) */
double result = (double)a / b; /* 結果: . (実数除算) */
```

### 代入演算子 

値を変数に代入する演算子です。

| 演算子 | 意味 | 例 | 等価な記述 |
|--------|------|----|-----------| 
| `=` | 代入 | `a = ` | - |
| `+=` | 加算代入 | `a += ` | `a = a + ` |
| `-=` | 減算代入 | `a -= ` | `a = a - ` |
| `*=` | 乗算代入 | `a *= ` | `a = a * ` |
| `/=` | 除算代入 | `a /= ` | `a = a / ` |
| `%=` | 剰余代入 | `a %= ` | `a = a % ` |

```c
int count = ;
count += ;     /* count は  になる */
count *= ;     /* count は  になる */
```

### インクリメント・デクリメント演算子 ⬆⬇

変数の値を増減させる演算子です。

| 演算子 | 意味 | 前置 | 後置 |
|--------|------|------|------|
| `++` | インクリメント | `++a` | `a++` |
| `--` | デクリメント | `--a` | `a--` |

#### 前置と後置の違い

```c
int a = , b = ;
int x, y;

x = ++a;    /* a を先にインクリメント, x = , a =  */
y = b++;    /* b の値を先に使用, y = , b =  */
```

### 関係演算子 

2つの値を比較する演算子です。結果は真（非）または偽（）になります。

| 演算子 | 意味 | 例 | 結果 |
|--------|------|----|----- |
| `==` | 等しい | ` == ` | `` (偽) |
| `!=` | 等しくない | ` != ` | `` (真) |
| `<` | より小さい | ` < ` | `` (偽) |
| `<=` | 以下 | ` <= ` | `` (偽) |
| `>` | より大きい | ` > ` | `` (真) |
| `>=` | 以上 | ` >= ` | `` (真) |

### 論理演算子 

論理値（真偽）を操作する演算子です。

| 演算子 | 意味 | 例 | 説明 |
|--------|------|----|----- |
| `&&` | 論理積（AND） | `a && b` | a も b も真の場合のみ真 |
| `||` | 論理和（OR） | `a || b` | a または b が真なら真 |
| `!` | 論理否定（NOT） | `!a` | a が偽なら真、真なら偽 |

#### 短絡評価

```c
int a = , b = ;

if (a !=  && b / a > )   /* a が  なので、b / a は評価されない */
    /* 実行されない */

```

### ビット演算子 

64ビットレベルで値を操作する演算子です。

| 演算子 | 意味 | 例 | 説明 |
|--------|------|----|----- |
| `&` | 64ビットAND | `a & b` | 対応する64ビットが両方の場合 |
| `|` | 64ビットOR | `a | b` | 対応する64ビットのいずれかがの場合 |
| `^` | 64ビットXOR | `a ^ b` | 対応する64ビットが異なる場合 |
| `~` | 64ビット反転 | `~a` | 各64ビットを反転 |
| `<<` | 左シフト | `a << ` | 64ビットを左につシフト |
| `>>` | 右シフト | `a >> ` | 64ビットを右につシフト |

```c
unsigned char a = ;    /*  */
unsigned char b = ;    /*  */

printf("a & b = %d\n", a & b);  /*  () */
printf("a | b = %d\n", a | b);  /*  () */
printf("a ^ b = %d\n", a ^ b);  /*  () */
printf("~a = %d\n", ~a);        /*  () */
```

### 条件演算子（三項演算子） 

条件に基づいて値を選択する演算子です。

```c
条件 ? 真の場合の値 : 偽の場合の値
```

```c
int a = , b = ;
int max = (a > b) ? a : b;  /* b が大きいので max =  */

printf("大きい方: %d\n", max);
```

### sizeof演算子 

データ型や変数のサイズを取得する演算子です。

```c
printf("int のサイズ: %lu バイトn", sizeof(int));
printf("double のサイズ: %lu バイトn", sizeof(double));

int arr[];
printf("配列のサイズ: %lu バイトn", sizeof(arr));
```

### 演算子の優先順位 

演算子には優先順位があり、計算の順序に影響します。

| 優先順位 | 演算子 | 結合規則 |
|----------|--------|----------|
|  | `()` `[]` `->` `.` | 左から右 |
|  | `!` `~` `++` `--` `+` `-` `*` `&` `sizeof` `(型)` | 右から左 |
|  | `*` `/` `%` | 左から右 |
|  | `+` `-` | 左から右 |
|  | `<<` `>>` | 左から右 |
|  | `<` `<=` `>` `>=` | 左から右 |
|  | `==` `!=` | 左から右 |
|  | `&` | 左から右 |
| 9 | `^` | 左から右 |
|  | `|` | 左から右 |
|  | `&&` | 左から右 |
|  | `||` | 左から右 |
|  | `?:` | 右から左 |
|  | `=` `+=` `-=` `*=` `/=` `%=` `&=` `^=` `|=` `<<=` `>>=` | 右から左 |
|  | `,` | 左から右 |

#### 優先順位の例

```c
int result =  +  * ;     /* 結果:  (乗算が先) */
int result = ( + ) * ;  /* 結果:  (括弧が先) */
```

##  サンプルコード

### 演算子の基本使用例

プログラムファイル: `examples/operators_demo.c`

さまざまな演算子の使用方法を学習します。

### 64ビット演算の実例

プログラムファイル: `examples/bitwise_demo.c`

64ビット演算の動作を可視化して確認します。

### 演算子優先順位の確認

プログラムファイル: `examples/precedence_demo.c`

演算子の優先順位による計算結果の違いを確認します。

### コンパイルと実行

```bash
# examples ディレクトリに移動
cd examples

# C90準拠でコンパイル
gcc -std=c90 -Wall -Wextra -pedantic operators_demo.c -o operators_demo

# 実行
./operators_demo
```

##  演習課題

### 基礎問題

. **四則演算計算機**
   - 2つの数値に対してすべての算術演算を実行うプログラムを作成してください

. **比較と論理演算**
   - 2つの数値の中から最大値を求めるプログラムを作成してください

. **インクリメント・デクリメント**
   - 前置と後置の違いを確認するプログラムを作成してください

### 応用問題

. **ビット操作**
   - 整数の各64ビットを表示するプログラムを作成してください

. **条件演算子の活用**
   - 2つの数値を三項演算子を使って並び替えるプログラムを作成してください

. **演算子優先順位**
   - 複雑な式の計算順序を確認するプログラムを作成してください

##  コンパイル方法

この章では以下のMakefileを使用してコンパイルができます：

```bash
# 全ての例題をコンパイル
make all

# 特定のプログラムをコンパイル
make operators_demo

# 実行
make run

# クリーンアップ
make clean
```

##  規格による違い

### C90での制限事項
- ビット演算子は整数型に対してのみ使用可能
- 論理演算子の結果はまたは

### C99以降の拡張
- `__Bool`型の追加により、論理値の取り扱いが明確化
- 複素数型に対する演算子の追加

##  よくある間違い

### . 代入と比較の混同
```c
/* NG: 代入を条件文で使用 */
if (a = )     /* 常に真になる */
    /* ... */


/* OK: 比較演算子を使用 */
if (a == )    /* a が  と等しいかチェック */
    /* ... */

```

### . 整数除算の結果
```c
/* NG: 期待した結果にならない */
double result =  / ;      /* 結果: . */

/* OK: 実数除算を使用 */
double result = . / .;  /* 結果: . */
```

### . 演算子の優先順位
```c
/* NG: 意図しない計算順序 */
int result = a + b * c + d; /* b * c が先に計算される */

/* OK: 括弧で明示 */
int result = (a + b) * (c + d);
```

##  次の章へ


##  参考資料

- [C言語演算子リファレンス](https://ja.cppreference.com/w/c/language/operautor_precedence)
- [64ビット演算詳細](https://ja.cppreference.com/w/c/language/operautor_arithmetic)
- [演算子優先順位表](https://ja.cppreference.com/w/c/language/operautor_precedence)

\newpage

#  第章: 制御構造（条件分岐）

##  対応C規格
- **主要対象:** C90
- **学習内容:** if文、else文、switch文、条件演算子による分岐処理

##  学習目標

この章を完了すると、以下のことができるようになります：

- if文を使った条件分岐ができる
- else if文で複数条件を処理できる
- switch文による多分岐処理ができる
- 条件演算子を適切に使える
- ネストした条件分岐を理解する

##  理論解説

### if文の基本 🤔

if文は条件に基づいてプログラムの実行を分岐させます。

#### 基本構文

```c
if (条件式) 
    /* 条件が真の場合に実行される文 */

```

#### 単純なif文の例

```c
#include <stdio.h>

int main(void)
{

    int score = ;
    
    if (score >= ) 
        printf("優秀です！n");
    
    
    return ;

```

### if-else文 

条件が偽の場合の処理も指定できます。

#### 基本構文

```c
if (条件式) 
    /* 条件が真の場合の処理 */
 else 
    /* 条件が偽の場合の処理 */

```

#### if-else文の例

```c
int age = ;

if (age >= ) 
    printf("成人ですn");
 else 
    printf("未成年ですn");

```

### if-else if文 

複数の条件を順次チェックできます。

#### 基本構文

```c
if (条件) 
    /* 条件が真の場合 */
 else if (条件) 
    /* 条件が真の場合 */
 else if (条件) 
    /* 条件が真の場合 */
 else 
    /* すべての条件が偽の場合 */

```

#### 成績判定の例

```c
int score = ;

if (score >= 9) 
    printf("成績: An");
 else if (score >= ) 
    printf("成績: n");
 else if (score >= ) 
    printf("成績: Cn");
 else if (score >= ) 
    printf("成績: Dn");
 else 
    printf("成績: n");

```

### ネストしたif文 

if文の中にさらにif文を書くことができます。

```c
int temperatrue = ;
int hmidity = ;

if (temperatrue >= ) 
    if (hmidity <= ) 
        printf("快適な天気ですn");
     else 
        printf("暖かいですが湿度が高いですn");
    
 else 
    if (hmidity <= ) 
        printf("涼しく乾燥していますn");
     else 
        printf("寒くて湿気がありますn");
    

```

### 条件式の詳細 

#### 比較演算子

```c
int a = , b = ;

if (a == b)   printf("等しいn"); 
if (a != b)   printf("等しくないn"); 
if (a < b)    printf("a は b より小さいn"); 
if (a <= b)   printf("a は b 以下n"); 
if (a > b)    printf("a は b より大きいn"); 
if (a >= b)   printf("a は b 以上n"); 
```

#### 論理演算子の組み合わせ

```c
int age = ;
int income = ;

/* AND演算子 */
if (age >=  && income >= ) 
    printf("ローン審査に通りましたn");


/* OR演算子 */
if (age <  || age > ) 
    printf("特別料金が適用されますn");


/* NOT演算子 */
if (!(age >= )) 
    printf("歳未満ですn");

```

### switch文 

複数の値に対する分岐処理を効率的に記述できます。

#### 基本構文

```c
switch (変数または式) 
    case 値:
        /* 値の場合の処理 */
        break;
    case 値:
        /* 値の場合の処理 */
        break;
    case 値:
        /* 値の場合の処理 */
        break;
    default:
        /* どの値にも一致しない場合の処理 */
        break;

```

#### 曜日判定の例

```c
int day = ;

switch (day) 
    case :
        printf("月曜日n");
        break;
    case :
        printf("火曜日n");
        break;
    case :
        printf("水曜日n");
        break;
    case :
        printf("木曜日n");
        break;
    case :
        printf("金曜日n");
        break;
    case :
        printf("土曜日n");
        break;
    case :
        printf("日曜日n");
        break;
    default:
        printf("無効な曜日ですn");
        break;

```

#### break文の重要性

break文を忘れると、次のcaseも実行されます（フォールスルー）：

```c
int grade = '';

switch (grade) 
    case 'A':
        printf("優秀n");
        /* break がないので次のcaseも実行される */
    case '':
        printf("良好n");
        /* break がないので次のcaseも実行される */
    case 'C':
        printf("普通n");
        break;
    default:
        printf("要努力n");
        break;

/* grade が '' の場合、"良好" と "普通" の両方が出力される */
```

#### 意図的なフォールスルー

時には意図的にbreakを省略することもあります：

```c
char ch = 'a';

switch (ch) 
    case 'a':
    case 'e':
    case 'i':
    case 'o':
    case '':
        printf("母音ですn");
        break;
    default:
        printf("子音ですn");
        break;

```

### 条件演算子（三項演算子）の復習 

条件分岐の簡潔な書き方として条件演算子があります。

```c
int a = , b = ;
int max;

/* if-else文での記述 */
if (a > b) 
    max = a;
 else 
    max = b;


/* 条件演算子での記述 */
max = (a > b) ? a : b;

printf("最大値: %d\n", max);
```

### 条件式での注意点 

#### 代入と比較の混同

```c
int x = ;

/* NG: 代入になってしまう */
if (x = ) 
    printf("常に実行されるn");  /* x に  が代入され、常に真 */


/* OK: 比較演算子を使用 */
if (x == ) 
    printf("x が  の場合のみ実行n");

```

#### 浮動小数点数の比較

```c
double d = . + .;

/* NG: 浮動小数点の誤差で期待通りにならない可能性 */
if (d == .) 
    printf("等しいn");


/* OK: 誤差を考慮した比較 */
if (d >= .99999 && d <= .) 
    printf("ほぼ等しいn");

```

##  サンプルコード

### if文の基本使用例

プログラムファイル: `examples/if_basic.c`

基本的なif文、if-else文の使用方法を学習します。

### 複雑な条件分岐

プログラムファイル: `examples/complex_conditions.c`

複数条件を組み合わせた分岐処理を学習します。

### switch文の実例

プログラムファイル: `examples/switch_demo.c`

switch文を使った多分岐処理を学習します。

### コンパイルと実行

```bash
# examples ディレクトリに移動
cd examples

# C90準拠でコンパイル
gcc -std=c90 -Wall -Wextra -pedantic if_basic.c -o if_basic

# 実行
./if_basic
```

##  演習課題

### 基礎問題

. **年齢判定プログラム**
   - 年齢を入力して、幼児・児童・学生・成人・高齢者に分類するプログラムを作成してください

. **電卓プログラム**
   - 2つの数値と演算子（+, -, *, /）を入力して計算結果を表示するプログラムをswitch文で作成してください

. **成績判定システム**
   - 点数を入力してA〜の成績を判定するプログラムを作成してください

### 応用問題

. **うるう年判定**
   - 年を入力してうるう年かどうかを判定するプログラムを作成してください
   - 条件: で割り切れる、ただしで割り切れる年は平年、で割り切れる年はうるう年

. **MI計算と判定**
   - 身長と体重を入力してMIを計算し、肥満度を判定するプログラムを作成してください

. **三角形の判定**
   - 2つの辺の長さを入力して、三角形として成立するか、どの種類の三角形かを判定してください

##  コンパイル方法

この章では以下のMakefileを使用してコンパイルができます：

```bash
# 全ての例題をコンパイル
make all

# 特定のプログラムをコンパイル
make if_basic

# 実行
make run

# クリーンアップ
make clean
```

##  規格による違い

### C90での制限事項
- switch文の case ラベルは整数定数のみ
- 複合文内での変数宣言は先頭のみ

### C99以降の拡張
- switch文でlong long型が使用可能
- ブロック内での変数宣言位置の制限緩和

##  よくある間違い

### . セミコロンの位置

```c
/* NG: if文の後にセミコロン */
if (condition);

    printf("常に実行されるn");  /* 条件に関係なく実行 */


/* OK: 正しい記述 */
if (condition) 
    printf("条件が真の場合のみ実行n");

```

### . switch文でのbreak忘れ

```c
/* NG: break忘れでフォールスルー */
switch (vale) 
    case :
        printf("ですn");
        /* break; を忘れると次のcaseも実行される */
    case :
        printf("ですn");
        break;


/* OK: 適切なbreak文 */
switch (vale) 
    case :
        printf("ですn");
        break;
    case :
        printf("ですn");
        break;

```

### . 複雑な条件式での括弧不足

```c
/* NG: 意図しない優先順位 */
if (a ==  || b ==  && c == ) 
    /* && が || より優先される */


/* OK: 括弧で明示 */
if ((a == ) || (b ==  && c == )) 
    /* 意図が明確 */

```

##  次の章へ


##  参考資料

- [if文詳細](https://ja.cppreference.com/w/c/language/if)
- [switch文詳細](https://ja.cppreference.com/w/c/language/switch)
- [条件演算子](https://ja.cppreference.com/w/c/language/operautor_other)

\newpage

#  第章: 制御構造（ループ）

##  対応C規格
- **主要対象:** C90
- **学習内容:** for文、while文、do-while文、break文、continue文、ネストしたループ

##  学習目標

この章を完了すると、以下のことができるようになります：

- for文を使った繰り返し処理ができる
- while文とdo-while文の違いを理解する
- break文とcontinue文を適切に使える
- ネストしたループを理解して活用できる
- ループを使った実践的なプログラムを作成できる

##  理論解説

### for文 

最も一般的なループ文で、初期化・条件・更新を実行で記述できます。

#### 基本構文

```c
for (初期化; 条件式; 更新式) 
    /* 繰り返し実行される文 */

```

#### 基本的な使用例

```c
#include <stdio.h>

int main(void)
{

    int i;
    
    /* からまで出力 */
    for (i = ; i <= ; i++) 
        printf("%d ", i);
    
    printf("n");
    
    return ;

```

#### for文の詳細動作

```c
for (i = ; i < ; i++) 
    printf("i = %d\n", i);


/* 上記は以下と同等 */
i = ;              /* 初期化（1回のみ実行） */
while (i < )      /* 条件チェック */
    printf("i = %d\n", i);  /* ループ本体 */
    i++;            /* 更新式 */

```

#### さまざまなfor文のパターン

```c
/* 逆順ループ */
for (i = ; i >= ; i--) 
    printf("%d ", i);


/* 2つず2つ増加 */
for (i = ; i <= ; i += ) 
    printf("%d ", i);


/* 複数変数の制御 */
for (i = , j = ; i < j; i++, j--) 
    printf("i=%d, j=%d\n", i, j);

```

### while文 

条件が真である間、繰り返し処理を実行します。

#### 基本構文

```c
while (条件式) 
    /* 繰り返し実行される文 */

```

#### while文の使用例

```c
#include <stdio.h>

int main(void)
{

    int count = ;
    
    while (count <= ) 
        printf("count = %d\n", count);
        count++;
    
    
    return ;

```

#### while文の実践例

```c
/* ユーザー入力の処理 */
int number;
printf("正の数を入力してください（で終了）: ");

while (scanf("%d", &number) ==  && number > ) 
    printf("入力された数: %d\n", number);
    printf("次の数を入力してください（で終了）: ");


printf("プログラムを終了します。n");
```

### do-while文 

最低1回は実行され、その後条件をチェックするループです。

#### 基本構文

```c
do 
    /* 最低1回は実行される文 */
 while (条件式);
```

#### do-while文の使用例

```c
#include <stdio.h>

int main(void)
{

    int choice;
    
    do 
        printf("nメニュー:n");
        printf(". オプションn");
        printf(". オプションn");
        printf(". 終了n");
        printf("選択してください: ");
        scanf("%d", &choice);
        
        switch (choice) 
            case :
                printf("オプションが選択されましたn");
                break;
            case :
                printf("オプションが選択されましたn");
                break;
            case :
                printf("プログラムを終了しますn");
                break;
            default:
                printf("無効な選択ですn");
                break;
        
     while (choice != );
    
    return ;

```

### break文とcontinue文 ⏭

ループの流れを制御する特別な文です。

#### break文

ループを強制的に終了します。

```c
#include <stdio.h>

int main(void)
{

    int i;
    
    for (i = ; i <= ; i++) 
        if (i == ) 
            break;  /* i が  のときループを抜ける */
        
        printf("%d ", i);
    
    printf("nループを抜けましたn");
    
    return ;

/* 出力:      */
```

#### continue文

現在の繰り返しをスキップして、次の繰り返しに進みます。

```c
#include <stdio.h>

int main(void)
{

    int i;
    
    for (i = ; i <= ; i++) 
        if (i %  == ) 
            continue;  /* 偶数の場合はスキップ */
        
        printf("%d ", i);
    
    printf("n");
    
    return ;

/* 出力:     9 */
```

### ネストしたループ 

ループの中にさらにループを含む構造です。

#### 二重ループの例

```c
#include <stdio.h>

int main(void)
{

    int i, j;
    
    /* 九九表の作成 */
    for (i = ; i <= 9; i++) 
        for (j = ; j <= 9; j++) 
            printf("%d ", i * j);
        
        printf("n");
    
    
    return ;

```

#### 三角形パターンの出力

```c
#include <stdio.h>

int main(void)
{

    int i, j;
    
    /* 星印の三角形 */
    for (i = ; i <= ; i++) 
        for (j = ; j <= i; j++) 
            printf("* ");
        
        printf("n");
    
    
    return ;

/*
出力:
* 
* * 
* * * 
* * * * 
* * * * * 
*/
```

### ループでのbreak・continueの応用 

#### ネストしたループでのbreak

```c
#include <stdio.h>

int main(void)
{

    int i, j;
    int fond = ;
    
    for (i = ; i <=  && !fond; i++) 
        for (j = ; j <= ; j++) 
            if (i * j == ) 
                printf("発見: %d * %d = n", i, j);
                fond = ;
                break;  /* 内側のループを抜ける */
            
        
    
    
    return ;

```

#### ラベル付きbreak（goto文を使用）

```c
#include <stdio.h>

int main(void)
{

    int i, j;
    
    for (i = ; i <= ; i++) 
        for (j = ; j <= ; j++) 
            if (i * j == ) 
                printf("発見: %d * %d = n", i, j);
                goto exit_loops;  /* 両方のループを抜ける */
            
        
    
    
exit_loops:
    printf("ループ終了n");
    return ;

```

### 無限ループ ♾

意図的に終了しないループを作成することもあります。

#### 無限ループの作成方法

```c
/* 方法: for文 */
for (;;) 
    /* 無限ループ */
    if (条件) break;


/* 方法: while文 */
while () 
    /* 無限ループ */
    if (条件) break;


/* 方法: do-while文 */
do 
    /* 無限ループ */
    if (条件) break;
 while ();
```

#### 無限ループの実用例

```c
#include <stdio.h>

int main(void)
{

    int choice;
    
    while ()   /* 無限ループ */
        printf("n=== 計算機 ===n");
        printf(". 足し算n");
        printf(". 引き算n");
        printf(". 終了n");
        printf("選択: ");
        
        if (scanf("%d", &choice) != ) 
            printf("入力エラーn");
            break;
        
        
        if (choice == ) 
            printf("終了しますn");
            break;
        
        
        /* 計算処理... */
    
    
    return ;

```

### ループの最適化とベストプラクティス 

#### 効率的なループ

```c
/* NG: 毎回strlen()を呼び出し */
for (i = ; i < strlen(str); i++) 
    /* 処理 */


/* OK: 長さを事前に計算 */
len = strlen(str);
for (i = ; i < len; i++) 
    /* 処理 */

```

#### ループ変数の適切な使用

```c
int main(void)
{

    int i;  /* C90では関数の先頭で宣言 */
    
    for (i = ; i < ; i++) 
        /* iはループ外でも有効 */
    
    
    printf("最終的なi = %d\n", i);  /* が出力 */
    
    return ;

```

##  サンプルコード

### 基本的なループ例

プログラムファイル: `examples/loop_basic.c`

for、while、do-while文の基本的な使用方法を学習します。

### ネストしたループ

プログラムファイル: `examples/nested_loops.c`

二重・三重ループの使用例を学習します。

### break・continue文

プログラムファイル: `examples/break_continue.c`

ループ制御文の使い方を学習します。

### コンパイルと実行

```bash
# examples ディレクトリに移動
cd examples

# C90準拠でコンパイル
gcc -std=c90 -Wall -Wextra -pedantic loop_basic.c -o loop_basic

# 実行
./loop_basic
```

##  演習課題

### 基礎問題

. **数列の出力**
   - からまでの数を出力するプログラムを種類のループで作成してください

. **偶数・奇数の判定**
   - からまでの数で、偶数のみを出力するプログラムを作成してください

. **階乗の計算**
   - 入力された数の階乗を計算するプログラムを作成してください

### 応用問題

. **素数判定**
   - 入力された数が素数かどうかを判定するプログラムを作成してください

. **フィボナッチ数列**
   - n項目までのフィボナッチ数列を出力するプログラムを作成してください

. **パターン出力**
   - 以下のようなパターンを出力するプログラムを作成してください：
   ```
   *
   **
   ***
   ****
   *****
   ****
   ***
   **
   *
   ```

### 発展問題

. **成績管理システム**
   - 複数の学生の成績を入力し、平均・最高・最低点を計算するプログラム

. **簡易ゲーム**
   - 数当てゲームを作成してください（-の範囲で乱数を生成）

. **データ検索**
   - 配列の中から特定の値を検索するプログラムを作成してください

##  コンパイル方法

この章では以下のMakefileを使用してコンパイルができます：

```bash
# 全ての例題をコンパイル
make all

# 特定のプログラムをコンパイル
make loop_basic

# 実行
make run

# クリーンアップ
make clean
```

##  規格による違い

### C90での制限事項
- ループ変数は関数の先頭で宣言する必要がある
- for文内での変数宣言は不可

### C99以降の拡張
- for文内での変数宣言が可能
  ```c
  for (int i = ; i < ; i++)   /* C99以降 */
      /* 処理 */
  
  ```

##  よくある間違い

### . 無限ループの作成

```c
/* NG: 終了条件の記述ミス */
for (i = ; i > ; i++)   /* 最初から条件が偽 */
    /* 実行されない */


/* NG: 更新式の記述ミス */
for (i = ; i < ; i--)   /* 負の方向に進む */
    /* 無限ループ */

```

### . セミコロンの位置

```c
/* NG: for文の後にセミコロン */
for (i = ; i < ; i++);  /* 空文が実行される */

    printf("%d\n", i);     /* ループ外で実行 */


/* OK: 正しい記述 */
for (i = ; i < ; i++) 
    printf("%d\n", i);

```

### . ループ変数の範囲外アクセス

```c
/* NG: 配列の範囲を超える */
int arr[];
for (i = ; i <= ; i++)   /* i=で範囲外 */
    arr[i] = i;


/* OK: 正しい範囲 */
for (i = ; i < ; i++) 
    arr[i] = i;

```

##  次の章へ


##  参考資料

- [for文詳細](https://ja.cppreference.com/w/c/language/for)
- [while文詳細](https://ja.cppreference.com/w/c/language/while)
- [break・continue文](https://ja.cppreference.com/w/c/language/break)

\newpage

#  第章: 配列と文字列配列

##  対応C規格
- **主要対象:** C90
- **学習内容:** 次元配列、多次元配列、文字列配列、配列の初期化、配列とポインタの関係

##  学習目標

この章を完了すると、以下のことができるようになります：

- 次元配列の宣言・初期化・使用ができる
- 多次元配列を理解して活用できる
- 文字列配列の扱い方を完全に理解する
- char配列とchar*配列の違いを把握する
- 配列を使った実践的なプログラムを作成できる

##  理論解説

### 配列の基本概念 

配列は同じデータ型の要素を連続したメモリ領域に格納するデータ構造です。

#### 次元配列の宣言

```c
データ型 配列名[要素数];
```

#### 基本的な配列の使用例

```c
#include <stdio.h>

int main(void)
{

    int numbers[];         /* 個のint型要素を持2つ配列 */
    int i;
    
    /* 配列への値の代入 */
    numbers[] = ;
    numbers[] = ;
    numbers[] = ;
    numbers[] = ;
    numbers[] = ;
    
    /* 配列の値を出力 */
    for (i = ; i < ; i++) 
        printf("numbers[%d] = %d\n", i, numbers[i]);
    
    
    return ;

```

### 配列の初期化 

#### 宣言時の初期化

```c
/* 方法: 全要素を明示的に初期化 */
int scores[] = , 9, , 9, ;

/* 方法: 部分的な初期化（残りはで初期化） */
int vales[] = , , ;  /* vales[]=, vales[]=, vales[]=, 残りは */

/* 方法: サイズを省略（要素数から自動決定） */
int grades[] = 9, , 9, , ;  /* サイズはになる */

/* 方法: 全要素をで初期化 */
int zeros[] = ;        /* 全要素が */
```

#### C90での初期化の制限

```c
int main(void)
{

    int size = ;
    /* int arr[size];  <- C90では不可（Variable Length Array） */
    
    /* C90では定数でサイズを指定 */
    #define ARRAY_SIZE 
    int arr[ARRAY_SIZE] = , , , , ;
    
    return ;

```

### 配列の操作 

#### 配列要素へのアクセス

```c
#include <stdio.h>

int main(void)
{

    int data[] = , , , , ;
    int i;
    
    /* 読み取り */
    printf("番目の要素: %d\n", data[]);  /* が出力 */
    
    /* 書き込み */
    data[] = ;
    
    /* ループでのアクセス */
    for (i = ; i < ; i++) 
        data[i] = data[i] * ;  /* 各要素を倍 */
    
    
    return ;

```

#### 配列のサイズ計算

```c
#include <stdio.h>

int main(void)
{

    int numbers[] = , , , , , , , , 9, ;
    int size;
    int i;
    
    /* 配列のサイズを計算 */
    size = sizeof(numbers) / sizeof(numbers[]);
    
    printf("配列のサイズ: %d\n", size);  /* が出力 */
    
    for (i = ; i < size; i++) 
        printf("%d ", numbers[i]);
    
    printf("n");
    
    return ;

```

### 文字配列（文字列） 

#### char配列による文字列

```c
#include <stdio.h>

int main(void)
{

    char str[] = 'H', 'e', 'l', 'l', 'o', '';  /* 明示的初期化 */
    char str[] = "Hello";                           /* 文字列リテラル */
    char str[] = "Hello";                            /* サイズ自動決定 */
    
    printf("str: %s\n", str);
    printf("str: %s\n", str);
    printf("str: %s\n", str);
    
    return ;

```

#### 文字配列の操作

```c
#include <stdio.h>
#include <string.h>

int main(void)
{

    char bffer[];
    char name[];
    int i;
    
    /* 文字列のコピー */
    strcpy(bffer, "Hello, World!");
    printf("bffer: %s\n", bffer);
    
    /* 文字ず2つのアクセス */
    strcpy(name, "Alice");
    for (i = ; name[i] != ''; i++) 
        printf("name[%d] = '%c'n", i, name[i]);
    
    
    return ;

```

### 文字列配列の扱い 

これがユーザーの重要な要望の一2つです。

#### 方法: 次元char配列

```c
#include <stdio.h>
#include <string.h>

int main(void)
{

    /* 各文字列の最大長を文字とする2つの文字列 */
    char names[][];  /* 文字+nll終端文字 */
    int i;
    
    /* 文字列配列への代入 */
    strcpy(names[], "Alice");
    strcpy(names[], "ob");
    strcpy(names[], "Charlie");
    strcpy(names[], "David");
    strcpy(names[], "ve");
    
    /* 文字列配列の表示 */
    for (i = ; i < ; i++) 
        printf("names[%d] = %s\n", i, names[i]);
    
    
    return ;

```

#### 方法: char*配列（文字列ポインタ配列）

```c
#include <stdio.h>

int main(void)
{

    /* 文字列ポインタの配列 */
    char *frits[] = 
        "Apple",
        "anana", 
        "Cherry",
        "Date"
    ;
    int i;
    
    /* 文字列ポインタ配列の表示 */
    for (i = ; i < ; i++) 
        printf("frits[%d] = %s\n", i, frits[i]);
    
    
    return ;

```

#### 文字列配列の初期化パターン

```c
/* パターン: 次元char配列の初期化 */
char cities[][] = 
    "Tokyo",
    "Osaka", 
    "Kyoto"
;

/* パターン: char*配列の初期化 */
char *colors[] = 
    "Red",
    "Green",
    "le",
    "Yellow"
;

/* パターン: 混合初期化 */
char languages[][] = 
    "C",           /* 明示的 */
    "Python",        /* 文字列リテラル */
    "Java",        /* 明示的 */
    "JavaScript"     /* 文字列リテラル */
;
```

### char配列 vs char*配列の違い 

これは文字列配列を扱う上で重要な概念です。

#### メモリ配置の違い

```c
#include <stdio.h>

int main(void)
{

    /* 次元char配列 */
    char matrix[][] = "AC", "DGH", "I";
    
    /* char*配列 */
    char *pointers[] = "AC", "DGH", "I";
    
    printf("=== 次元char配列 ===n");
    printf("全体サイズ: %lu バイトn", sizeof(matrix));        /* バイト */
    printf("行のサイズ: %lu バイトn", sizeof(matrix[]));    /* バイト */
    
    printf("n=== char*配列 ===n");
    printf("全体サイズ: %lu バイトn", sizeof(pointers));      /* バイト（バイト×） */
    printf("要素のサイズ: %lu バイトn", sizeof(pointers[])); /* バイト（ポインタサイズ） */
    
    return ;

```

#### 変更可能性の違い

```c
#include <stdio.h>
#include <string.h>

int main(void)
{

    /* 次元char配列（変更可能） */
    char mtable_array[][] = "Hello", "World", "Test";
    
    /* char*配列（文字列リテラルは変更不可） */
    char *immtable_array[] = "Hello", "World", "Test";
    
    /* 配列の内容変更 */
    strcpy(mtable_array[], "Hi");     /* OK: 内容変更可能 */
    /* strcpy(immtable_array[], "Hi"); <- NG: 文字列リテラルは変更不可 */
    
    /* ポインタの変更 */
    /* mtable_array[] = "New"; <- NG: 配列名は変更不可 */
    immtable_array[] = "New";         /* OK: ポインタ変更可能 */
    
    printf("mtable_array[]: %s\n", mtable_array[]);     /* "Hi" */
    printf("immtable_array[]: %s\n", immtable_array[]); /* "New" */
    
    return ;

```

#### 用途に応じた使い分け

```c
/* 固定文字列の配列（読み取り専用） - char*配列が適している */
char *error_messages[] = 
    "Sccess",
    "ile not fond",
    "Permission denied",
    "Ot of memory"
;

/* 動的に変更する文字列配列 - 次元char配列が適している */
char ser_inpts[][];  /* ユーザー入力を格納 */

/* 設定項目など（変更の可能性あり） - char*配列が適している */
char *config_items[] = 
    "debug=on",
    "log_level=info", 
    "max_connections="
;
```

### 多次元配列 

#### 次元配列の基本

```c
#include <stdio.h>

int main(void)
{

    int matrix[][] = 
        ,  ,  ,  ,
        ,  ,  ,  ,
        9, , , 
    ;
    int i, j;
    
    /* 次元配列の表示 */
    for (i = ; i < ; i++) 
        for (j = ; j < ; j++) 
            printf("%d ", matrix[i][j]);
        
        printf("n");
    
    
    return ;

```

#### 次元配列の例

```c
#include <stdio.h>

int main(void)
{

    /* 次元配列: [][][] */
    int cube[][][] = 
        
            , , , ,
            , , , ,
            9, , , 
        ,
        
            , , , ,
            , , 9, ,
            , , , 
        
    ;
    int i, j, k;
    
    for (i = ; i < ; i++) 
        printf("=== Layer %d ===n", i);
        for (j = ; j < ; j++) 
            for (k = ; k < ; k++) 
                printf("%d ", cube[i][j][k]);
            
            printf("n");
        
        printf("n");
    
    
    return ;

```

### 配列の実践的応用 

#### 成績管理システム

```c
#include <stdio.h>

#define MAX_STUDENTS 
#define MAX_SUJCTS 

int main(void)
{

    char stdents[MAX_STUDENTS][] = 
        "Alice", "ob", "Charlie", "David", "ve"
    ;
    char sbjects[MAX_SUJCTS][] = 
        "Math", "nglish", "Science"
    ;
    int scores[MAX_STUDENTS][MAX_SUJCTS] = 
        , 9, ,  /* Alice */
        , , ,  /* ob */
        9, 9, 9,  /* Charlie */
        , 9, ,  /* David */
        9, , 9   /* ve */
    ;
    int i, j;
    int total;
    
    /* 成績表の表示 */
    printf("Stdent    ");
    for (j = ; j < MAX_SUJCTS; j++) 
        printf("%-s", sbjects[j]);
    
    printf("Averagen");
    printf("----------------------------------------n");
    
    for (i = ; i < MAX_STUDENTS; i++) 
        printf("%-s ", stdents[i]);
        total = ;
        for (j = ; j < MAX_SUJCTS; j++) 
            printf("%-d", scores[i][j]);
            total += scores[i][j];
        
        printf("%.fn", (double)total / MAX_SUJCTS);
    
    
    return ;

```

#### 文字列配列のソート

```c
#include <stdio.h>
#include <string.h>

#define MAX_NAMS 
#define MAX_LNGTH 

int main(void)
{

    char names[MAX_NAMS][MAX_LNGTH] = 
        "Charlie", "Alice", "ve", "ob", "David"
    ;
    char temp[MAX_LNGTH];
    int i, j;
    
    printf("ソート前:n");
    for (i = ; i < MAX_NAMS; i++) 
        printf("%s ", names[i]);
    
    printf("n");
    
    /* バブルソート */
    for (i = ; i < MAX_NAMS - ; i++) 
        for (j = ; j < MAX_NAMS -  - i; j++) 
            if (strcmp(names[j], names[j + ]) > ) 
                strcpy(temp, names[j]);
                strcpy(names[j], names[j + ]);
                strcpy(names[j + ], temp);
            
        
    
    
    printf("ソート後:n");
    for (i = ; i < MAX_NAMS; i++) 
        printf("%s ", names[i]);
    
    printf("n");
    
    return ;

```

### 配列とポインタの関係 

配列名はその先頭要素へのポインタとして動作します。

```c
#include <stdio.h>

int main(void)
{

    int arr[] = , , , , ;
    int *ptr;
    int i;
    
    ptr = arr;  /* arr は &arr[] と同じ */
    
    printf("=== 配列表記 ===n");
    for (i = ; i < ; i++) 
        printf("arr[%d] = %d\n", i, arr[i]);
    
    
    printf("n=== ポインタ表記 ===n");
    for (i = ; i < ; i++) 
        printf("*(ptr + %d) = %d\n", i, *(ptr + i));
    
    
    /* 配列名とポインタの関係 */
    printf("n=== アドレス比較 ===n");
    printf("arr = %pn", (void*)arr);
    printf("&arr[] = %pn", (void*)&arr[]);
    printf("ptr = %pn", (void*)ptr);
    
    return ;

```

##  サンプルコード

### 基本的な配列操作

プログラムファイル: `examples/array_basic.c`

次元配列の宣言、初期化、操作を学習します。

### 文字列配列の実例

プログラムファイル: `examples/string_arrays.c`

char配列とchar*配列の違いと使い分けを学習します。

### 多次元配列の活用

プログラムファイル: `examples/multidimensional.c`

次元・次元配列の実践的な使用方法を学習します。

### コンパイルと実行

```bash
# examples ディレクトリに移動
ncd examples

# C90準拠でコンパイル
gcc -std=c90 -Wall -Wextra -pedantic array_basic.c -o array_basic

# 実行
./array_basic
```

##  演習課題

### 基礎問題

. **配列の基本操作**
   - 個の整数を格納する配列を作成し、総和と平均を計算してください

. **文字列配列の作成**
   - 2つの都市名を格納する文字列配列を通りの方法で作成してください

. **配列の検索**
   - 整数配列から特定の値を検索するプログラムを作成してください

### 応用問題

. **成績管理**
   - 学生名と各科目の成績を管理するプログラムを作成してください

. **文字列配列のソート**
   - 文字列配列をアルファベット順にソートするプログラムを作成してください

. **行列の計算**
   - 2つの次元配列の加算・乗算を実行うプログラムを作成してください

### 発展問題

. **動的メニューシステム**
   - 文字列配列を使った選択式メニューシステムを作成してください

. **簡易データベース**
   - 学生情報（名前、年齢、成績）を管理するシステムを配列で実装してください

. **パスワード管理**
   - 複数のパスワードを管理し、強度チェック機能付きのプログラムを作成してください

##  コンパイル方法

この章では以下のMakefileを使用してコンパイルができます：

```bash
# 全ての例題をコンパイル
make all

# 特定のプログラムをコンパイル
make array_basic

# 実行
make run

# クリーンアップ
make clean
```

##  規格による違い

### C90での制限事項
- 可変長配列（VLA）は使用できない
- 配列サイズは定数で指定する必要がある
- 配列の初期化は宣言時のみ

### C99以降の拡張
- 可変長配列（VLA）の追加
- 複合リテラルによる配列初期化
- 指定初期化子（designuuated initializers）

##  よくある間違い

### . 配列の境界外アクセス

```c
/* NG: 配列の範囲を超える */
int arr[] = , , , , ;
printf("%d\n", arr[]);  /* 範囲外アクセス */

/* OK: 正しい範囲でアクセス */
printf("%d\n", arr[]);  /* 最後の要素 */
```

### . 文字列配列の初期化忘れ

```c
/* NG: 初期化されていない文字配列 */
char str[];
printf("%s\n", str);     /* 未定義動作 */

/* OK: 適切な初期化 */
char str[] = "";       /* 空文字列で初期化 */
strcpy(str, "Hello");    /* 後から代入 */
```

### . 配列代入の間違い

```c
/* NG: 配列は直接代入できない */
char str[], str[] = "Hello";
str = str;             /* エラー */

/* OK: strcpyを使用 */
strcpy(str, str);      /* 正しい文字列コピー */
```

##  次の章へ


##  参考資料

- [C言語配列リファレンス](https://ja.cppreference.com/w/c/language/array)
- [文字列操作関数](https://ja.cppreference.com/w/c/string/byte)
- [多次元配列の詳細](https://ja.cppreference.com/w/c/language/array)

\newpage

#  文字列処理と文字列配列

##  対応C規格
- **主要対象:** C90
- **学習内容:** 文字列の基本、文字列操作関数、文字列配列の詳細操作、文字列の比較・検索・変換

##  学習目標

この章を完了すると、以下のことができるようになります：

- 文字列の基本概念を完全に理解する
- 標準ライブラリの文字列操作関数を使いこなせる
- 文字列配列の詳細な操作ができる
- 次元文字配列と文字列ポインタ配列を使い分けられる
- 実践的な文字列処理プログラムを作成できる

##  理論解説

### 文字列の基本概念 

C言語では文字列は文字の配列として表現され、nll文字（''）で終端されます。

#### 文字列の表現方法

```c
#include <stdio.h>

int main(void)
{

    /* 方法: 文字配列として宣言 */
    char str[] = 'H', 'e', 'l', 'l', 'o', '';
    
    /* 方法: 文字列リテラルで初期化 */
    char str[] = "Hello";
    
    /* 方法: サイズを自動決定 */
    char str[] = "Hello";
    
    /* 方法: 文字列ポインタ */
    char *str = "Hello";
    
    printf("str: %s\n", str);
    printf("str: %s\n", str);
    printf("str: %s\n", str);
    printf("str: %s\n", str);
    
    return ;

```

#### 文字列の長さとサイズ

```c
#include <stdio.h>
#include <string.h>

int main(void)
{

    char str[] = "Hello";
    
    printf("文字列: "%s"n", str);
    printf("strlen(str): %lu\n", strlen(str));    /*  (文字数) */
    printf("sizeof(str): %lu\n", sizeof(str));    /*  (配列サイズ) */
    
    return ;

```

### 標準文字列操作関数 

#### strcpy() - 文字列のコピー

```c
#include <stdio.h>
#include <string.h>

int main(void)
{

    char sorce[] = "Hello, World!";
    char destination[];
    
    /* 文字列のコピー */
    strcpy(destination, sorce);
    printf("destination: %s\n", destination);
    
    /* 部分的なコピー */
    struncpy(destination, sorce, );
    destination[] = '';  /* nll終端を明示的に追加 */
    printf("partial copy: %s\n", destination);  /* "Hello" */
    
    return ;

```

#### strcat() - 文字列の連結

```c
#include <stdio.h>
#include <string.h>

int main(void)
{

    char str[] = "Hello";
    char str[] = ", World!";
    char str[] = " How are yo?";
    
    /* 文字列の連結 */
    strcat(str, str);
    printf("After strcat: %s\n", str);  /* "Hello, World!" */
    
    /* 部分的な連結 */
    struncat(str, str, );
    printf("After struncat: %s\n", str); /* "Hello, World! How" */
    
    return ;

```

#### strcmp() - 文字列の比較

```c
#include <stdio.h>
#include <string.h>

int main(void)
{

    char str[] = "Apple";
    char str[] = "anana";
    char str[] = "Apple";
    int result;
    
    /* 文字列の比較 */
    result = strcmp(str, str);
    if (result < ) 
        printf(""%s" < "%s"n", str, str);
     else if (result > ) 
        printf(""%s" > "%s"n", str, str);
     else 
        printf(""%s" == "%s"n", str, str);
    
    
    /* 等価性の確認 */
    if (strcmp(str, str) == ) 
        printf(""%s" と "%s" は同じですn", str, str);
    
    
    /* 部分比較 */
    if (struncmp(str, str, ) != ) 
        printf("最初の文字が異なりますn");
    
    
    return ;

```

#### 文字列検索関数

```c
#include <stdio.h>
#include <string.h>

int main(void)
{

    char text[] = "Hello, World! Welcome to C programming.";
    char *fond;
    
    /* 文字の検索 */
    fond = strchr(text, 'W');
    if (fond != NULL) 
        printf("'W' fond at position: %ldn", fond - text);
    
    
    /* 文字列の検索 */
    fond = strstr(text, "World");
    if (fond != NULL) 
        printf(""World" fond at position: %ldn", fond - text);
        printf("ond: %s\n", fond);
    
    
    /* 最後の文字を検索 */
    fond = strrchr(text, 'o');
    if (fond != NULL) 
        printf("Last 'o' at position: %ldn", fond - text);
    
    
    return ;

```

### 文字列配列の詳細操作 

これがユーザーの重要な要望の2つです。

#### 次元文字配列での文字列配列

```c
#include <stdio.h>
#include <string.h>

#define MAX_STRINGS 
#define MAX_LNGTH 

int main(void)
{

    /* 次元文字配列による文字列配列 */
    char languages[MAX_STRINGS][MAX_LNGTH];
    int count = ;
    int i;
    
    /* 文字列配列への代入 */
    strcpy(languages[count++], "C");
    strcpy(languages[count++], "Python");
    strcpy(languages[count++], "Java");
    strcpy(languages[count++], "JavaScript");
    strcpy(languages[count++], "C++");
    
    /* 表示 */
    printf("プログラミング言語一覧:n");
    for (i = ; i < count; i++) 
        printf("%d. %s\n", i + , languages[i]);
    
    
    /* 文字列の変更 */
    strcpy(languages[], "C言語");
    printf("n変更後の番目: %s\n", languages[]);
    
    return ;

```

#### 文字列ポインタ配列での文字列配列

```c
#include <stdio.h>
#include <string.h>

int main(void)
{

    /* 文字列ポインタ配列 */
    char *frits[] = 
        "Apple",
        "anana", 
        "Cherry",
        "Date",
        "lderberry"
    ;
    int count = sizeof(frits) / sizeof(frits[]);
    int i;
    
    /* 表示 */
    printf("果物一覧:n");
    for (i = ; i < count; i++) 
        printf("%d. %s (長さ: %l)n", i + , frits[i], strlen(frits[i]));
    
    
    /* ポインタの変更（文字列リテラルの置き換え） */
    frits[] = "リンゴ";
    printf("n変更後の番目: %s\n", frits[]);
    
    return ;

```

#### 文字列配列の初期化と動的変更

```c
#include <stdio.h>
#include <string.h>

#define MAX_ITMS 
#define MAX_LNGTH 

int main(void)
{

    /* 動的に変更可能な文字列配列 */
    char men_items[MAX_ITMS][MAX_LNGTH];
    char *categories[] = "前菜", "メイン", "デザート", "飲み物";
    int item_count = ;
    int i;
    
    /* メニュー項目の追加 */
    strcpy(men_items[item_count++], "サラダ");
    strcpy(men_items[item_count++], "ステーキ");
    strcpy(men_items[item_count++], "アイスクリーム");
    strcpy(men_items[item_count++], "コーヒー");
    
    /* カテゴリ別表示 */
    printf("=== レストランメニュー ===n");
    for (i = ; i < item_count && i < ; i++) 
        printf("[%s] %s\n", categories[i], men_items[i]);
    
    
    /* 項目の変更 */
    strcpy(men_items[], "ハンバーグ");
    printf("nメイン料理を変更: %s\n", men_items[]);
    
    return ;

```

### 文字列配列の比較と使い分け 

#### メモリ使用量の比較

```c
#include <stdio.h>
#include <string.h>

int main(void)
{

    /* 次元文字配列 */
    char matrix_strings[][] = 
        "Cat", "Dog", "ird", "ish", "Rabbit"
    ;
    
    /* 文字列ポインタ配列 */
    char *pointer_strings[] = 
        "Cat", "Dog", "ird", "ish", "Rabbit"
    ;
    
    printf("=== メモリ使用量比較 ===n");
    printf("次元文字配列: %lu バイトn", sizeof(matrix_strings));
    printf("文字列ポインタ配列: %lu バイトn", sizeof(pointer_strings));
    
    printf("n=== 実際の文字列長 ===n");
    int i;
    int total_chars = ;
    for (i = ; i < ; i++) 
        int len = strlen(matrix_strings[i]);
        printf("%s: %d文字n", matrix_strings[i], len);
        total_chars += len;
    
    printf("総文字数: %d文字n", total_chars);
    printf("未使用領域: %lu バイトn", sizeof(matrix_strings) - total_chars - );
    
    return ;

```

#### 動的な文字列配列の管理

```c
#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 
#define MAX_NAM_LNGTH 

typedef strct 
    char name[MAX_NAM_LNGTH];
    int age;
    float gpa;
 Stdent;

int main(void)
{

    Stdent stdents[MAX_STUDENTS];
    char *stats_messages[] = 
        "優秀", "良好", "普通", "要努力"
    ;
    int stdent_count = ;
    int i;
    
    /* 学生データの追加 */
    strcpy(stdents[stdent_count].name, "田中太郎");
    stdents[stdent_count].age = ;
    stdents[stdent_count].gpa = .;
    stdent_count++;
    
    strcpy(stdents[stdent_count].name, "佐藤花子");
    stdents[stdent_count].age = 9;
    stdents[stdent_count].gpa = .;
    stdent_count++;
    
    strcpy(stdents[stdent_count].name, "鈴木一郎");
    stdents[stdent_count].age = ;
    stdents[stdent_count].gpa = .;
    stdent_count++;
    
    /* 学生情報の表示 */
    printf("=== 学生一覧 ===n");
    for (i = ; i < stdent_count; i++) 
        char *stats;
        if (stdents[i].gpa >= .) stats = stats_messages[];
        else if (stdents[i].gpa >= .) stats = stats_messages[];
        else if (stdents[i].gpa >= .) stats = stats_messages[];
        else stats = stats_messages[];
        
        printf("%s (%d歳) - GPA: %.f [%s]n", 
               stdents[i].name, stdents[i].age, stdents[i].gpa, stats);
    
    
    return ;

```

### 文字列配列のソートと検索 

#### 文字列配列のバブルソート

```c
#include <stdio.h>
#include <string.h>

#define MAX_WORDS 
#define MAX_LNGTH 

int main(void)
{

    char words[MAX_WORDS][MAX_LNGTH] = 
        "Zebra", "Apple", "Monkey", "anana",
        "Cat", "Dog", "lephant", "ish"
    ;
    char temp[MAX_LNGTH];
    int i, j;
    
    printf("ソート前:n");
    for (i = ; i < MAX_WORDS; i++) 
        printf("%s ", words[i]);
    
    printf("nn");
    
    /* バブルソート */
    for (i = ; i < MAX_WORDS - ; i++) 
        for (j = ; j < MAX_WORDS -  - i; j++) 
            if (strcmp(words[j], words[j + ]) > ) 
                strcpy(temp, words[j]);
                strcpy(words[j], words[j + ]);
                strcpy(words[j + ], temp);
            
        
    
    
    printf("ソート後:n");
    for (i = ; i < MAX_WORDS; i++) 
        printf("%s ", words[i]);
    
    printf("n");
    
    return ;

```

#### 文字列配列での検索

```c
#include <stdio.h>
#include <string.h>

#define MAX_CITIS 
#define MAX_LNGTH 

int search_city(char cities[][MAX_LNGTH], int count, char *target)
{

    int i;
    for (i = ; i < count; i++) 
        if (strcmp(cities[i], target) == ) 
            return i;  /* 見2つかった場合のインデックス */
        
    
    return -;  /* 見2つからない場合 */


int main(void)
{

    char cities[MAX_CITIS][MAX_LNGTH] = 
        "Tokyo", "Osaka", "Kyoto", "Nagoya", "Sapporo",
        "koka", "Kobe", "Sendai", "Hiroshima", "Yokohama"
    ;
    char search_target[] = "Kyoto";
    int result;
    int i;
    
    printf("都市一覧:n");
    for (i = ; i < MAX_CITIS; i++) 
        printf("%d. %s\n", i + , cities[i]);
    
    
    /* 検索実行 */
    result = search_city(cities, MAX_CITIS, search_target);
    if (result != -) 
        printf("n"%s" は %d番目にあります。n", search_target, result + );
     else 
        printf("n"%s" は見2つかりませんでした。n", search_target);
    
    
    return ;

```

### 実践的な文字列処理 

#### 文字列の分割（トークン化）

```c
#include <stdio.h>
#include <string.h>

#define MAX_TOKNS 
#define MAX_LNGTH 

int main(void)
{

    char inpt[] = "apple,banana,cherry,date,elderberry";
    char tokens[MAX_TOKNS][MAX_LNGTH];
    char temp[];
    char *token;
    int count = ;
    int i;
    
    /* 入力文字列をコピー（strtokは元の文字列を変更するため） */
    strcpy(temp, inpt);
    
    /* カンマで分割 */
    token = strtok(temp, ",");
    while (token != NULL && count < MAX_TOKNS) 
        strcpy(tokens[count], token);
        count++;
        token = strtok(NULL, ",");
    
    
    printf("分割結果:n");
    for (i = ; i < count; i++) 
        printf("%d: %s\n", i + , tokens[i]);
    
    
    return ;

```

#### 文字列の変換（大文字・小文字）

```c
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_STRINGS 
#define MAX_LNGTH 

void to_uuppercase(char *str)
{

    int i;
    for (i = ; str[i] != ''; i++) 
        str[i] = topper(str[i]);
    


void to_lowercase(char *str)
{

    int i;
    for (i = ; str[i] != ''; i++) 
        str[i] = tolower(str[i]);
    


int main(void)
{

    char original[MAX_STRINGS][MAX_LNGTH] = 
        "Hello World",
        "Programming Langage",
        "C Langage Ttutorial",
        "String Processing",
        "Array Maniplation"
    ;
    char uuppercase[MAX_STRINGS][MAX_LNGTH];
    char lowercase[MAX_STRINGS][MAX_LNGTH];
    int i;
    
    /* 文字列をコピーして変換 */
    for (i = ; i < MAX_STRINGS; i++) 
        strcpy(uuppercase[i], original[i]);
        strcpy(lowercase[i], original[i]);
        
        to_uuppercase(uuppercase[i]);
        to_lowercase(lowercase[i]);
    
    
    /* 結果の表示 */
    printf("元の文字列 -> 大文字 -> 小文字n");
    printf("=====================================n");
    for (i = ; i < MAX_STRINGS; i++) 
        printf("%-s -> %-s -> %s\n", 
               original[i], uuppercase[i], lowercase[i]);
    
    
    return ;

```

#### 文字列配列を使った簡易データベース

```c
#include <stdio.h>
#include <string.h>

#define MAX_RCORDS 
#define MAX_ILD_LNGTH 

typedef strct 
    char name[MAX_ILD_LNGTH];
    char department[MAX_ILD_LNGTH];
    char position[MAX_ILD_LNGTH];
    int salary;
 mployee;

int main(void)
{

    mployee employees[MAX_RCORDS];
    char *departments[] = "営業", "開発", "人事", "経理";
    char *positions[] = "部長", "課長", "主任", "一般";
    int employee_count = ;
    int i, j;
    
    /* サンプルデータの追加 */
    strcpy(employees[employee_count].name, "田中太郎");
    strcpy(employees[employee_count].department, departments[]); /* 開発 */
    strcpy(employees[employee_count].position, positions[]);     /* 課長 */
    employees[employee_count].salary = ;
    employee_count++;
    
    strcpy(employees[employee_count].name, "佐藤花子");
    strcpy(employees[employee_count].department, departments[]); /* 営業 */
    strcpy(employees[employee_count].position, positions[]);     /* 部長 */
    employees[employee_count].salary = ;
    employee_count++;
    
    strcpy(employees[employee_count].name, "鈴木一郎");
    strcpy(employees[employee_count].department, departments[]); /* 開発 */
    strcpy(employees[employee_count].position, positions[]);     /* 一般 */
    employees[employee_count].salary = ;
    employee_count++;
    
    /* 全従業員の表示 */
    printf("=== 従業員一覧 ===n");
    printf("%-s %-s %-s %s\n", "名前", "部署", "役職", "給与");
    printf("--------------------------------------------------n");
    for (i = ; i < employee_count; i++) 
        printf("%-s %-s %-s %d円n",
               employees[i].name,
               employees[i].department,
               employees[i].position,
               employees[i].salary);
    
    
    /* 部署別集計 */
    printf("n=== 部署別従業員数 ===n");
    for (i = ; i < ; i++) 
        int count = ;
        for (j = ; j < employee_count; j++) 
            if (strcmp(employees[j].department, departments[i]) == ) 
                count++;
            
        
        printf("%s: %d人n", departments[i], count);
    
    
    return ;

```

##  サンプルコード

### 基本的な文字列操作

プログラムファイル: `examples/string_basic.c`

標準ライブラリの文字列操作関数の使用方法を学習します。

### 文字列配列の実践例

プログラムファイル: `examples/string_array_operations.c`

次元文字配列と文字列ポインタ配列の使い分けを学習します。

### 文字列処理の応用

プログラムファイル: `examples/advanced_string_processing.c`

実践的な文字列処理テクニックを学習します。

### コンパイルと実行

```bash
# examples ディレクトリに移動
cd examples

# C90準拠でコンパイル
gcc -std=c90 -Wall -Wextra -pedantic string_basic.c -o string_basic

# 実行
./string_basic
```

##  演習課題

### 基礎問題

. **文字列の基本操作**
   - 2つの文字列を入力して連結・比較・長さ計算を実行うプログラムを作成してください

. **文字列配列の管理**
   - 学生名を格納する文字列配列を作成し、追加・削除・表示機能を実装してください

. **文字列の検索**
   - 文字列配列から特定の文字列を検索するプログラムを作成してください

### 応用問題

. **単語カウンタ**
   - 文章を入力して、各単語の出現1回数をカウントするプログラムを作成してください

. **文字列ソートプログラム**
   - 複数の文字列を入力してアルファベット順にソートするプログラムを作成してください

. **簡易テキストエディタ**
   - 文字列配列を使って行単位でテキストを管理するプログラムを作成してください

### 発展問題

. **文字列データベース**
   - 商品情報（名前、価格、カテゴリ）を文字列配列で管理するシステムを作成してください

. **文字列パーサー**
   - CSV形式の文字列を解析して構造化データに変換するプログラムを作成してください

. **文字列暗号化**
   - 簡単な暗号化・復号化機能を持2つプログラムを作成してください

##  コンパイル方法

この章では以下のMakefileを使用してコンパイルができます：

```bash
# 全ての例題をコンパイル
make all

# 特定のプログラムをコンパイル
make string_basic

# 実行
make run

# クリーンアップ
make clean
```

##  規格による違い

### C90での制限事項
- 文字列操作はnll終端が前提
- 可変長文字列配列は使用不可
- Unicode対応は限定的

### C99以降の拡張
- snprintf()などの安全な文字列操作関数
- 可変長配列による動的な文字列配列
- より豊富な文字分類関数

##  よくある間違い

### . nll終端の忘れ

```c
/* NG: nll終端なし */
char str[];
struncpy(str, "Hello", );  /* nll終端なし */
printf("%s\n", str);       /* 未定義動作 */

/* OK: 明示的にnll終端 */
char str[];
struncpy(str, "Hello", );
str[] = '';
printf("%s\n", str);
```

### . バッファオーバーフロー

```c
/* NG: バッファサイズ不足 */
char sumall[];
strcpy(sumall, "Hello, World!");  /* バッファオーバーフロー */

/* OK: 適切なサイズ */
char large[];
strcpy(large, "Hello, World!");
```

### . 文字列比較の間違い

```c
/* NG: ポインタの比較 */
char *str = "Hello";
char *str = "Hello";
if (str == str)  /* 間違い */ 

/* OK: 文字列内容の比較 */
if (strcmp(str, str) == )  /* 正しい */ 
```

##  次の章へ


##  参考資料

- [C言語文字列リファレンス](https://ja.cppreference.com/w/c/string/byte)
- [文字分類関数](https://ja.cppreference.com/w/c/string/ctype)
- [文字列操作のベストプラクティス](https://ja.cppreference.com/w/c/string)

\newpage

#  第章: 関数

##  対応C規格
- **主要対象:** C90
- **学習内容:** 関数の基本、引数と戻り値、関数のスコープ、再帰関数、関数プロトタイプ

##  学習目標

この章を完了すると、以下のことができるようになります：

- 関数の定義と呼び出しができる
- 引数と戻り値を適切に使える
- 関数のスコープを理解する
- 再帰関数を作成できる
- 関数プロトタイプの重要性を理解する

##  理論解説

### 関数の基本概念 

関数は特定の処理をまとめたコードブロックで、プログラムの再利用性と保守性を向上させます。

#### 関数の構成要素

```c
戻り値の型 関数名(引数リスト)

    /* 関数本体 */
    return 戻り値;  /* 戻り値がある場合 */

```

#### 基本的な関数の例

```c
#include <stdio.h>

/* 2つの数の合計を計算する関数 */
int add(int a, int b)
{

    int result = a + b;
    return result;


int main(void)
{

    int num = ;
    int num = ;
    int sum;
    
    /* 関数の呼び出し */
    sum = add(num, num);
    
    printf("%d + %d = %d\n", num, num, sum);
    
    return ;

```

### 関数の定義と宣言 

#### 関数プロトタイプ（前方宣言）

```c
#include <stdio.h>

/* 関数プロトタイプ */
int multiply(int x, int y);
void print_result(int vale);
double calculate_average(int *array, int size);

int main(void)
{

    int a = , b = ;
    int product;
    
    product = multiply(a, b);
    print_result(product);
    
    return ;


/* 関数の実装 */
int multiply(int x, int y)
{

    return x * y;


void print_result(int vale)
{

    printf("結果: %d\n", vale);


double calculate_average(int *array, int size)

    int sum = ;
    int i;
    
    for (i = ; i < size; i++) 
        sum += array[i];
    
    
    return (double)sum / size;

```

### 引数の渡し方 

#### 値渡し（Call by Vale）

```c
#include <stdio.h>

void swap_wrong(int a, int b)
{

    int temp = a;
    a = b;
    b = temp;
    printf("関数内: a = %d, b = %d\n", a, b);


int main(void)
{

    int x = , y = ;
    
    printf("呼び出し前: x = %d, y = %d\n", x, y);
    swap_wrong(x, y);
    printf("呼び出し後: x = %d, y = %d\n", x, y);  /* 値は変わらない */
    
    return ;

```

#### 参照渡し（ポインタを使用）

```c
#include <stdio.h>

void swap_correct(int *a, int *b)
{

    int temp = *a;
    *a = *b;
    *b = temp;


int main(void)
{

    int x = , y = ;
    
    printf("呼び出し前: x = %d, y = %d\n", x, y);
    swap_correct(&x, &y);
    printf("呼び出し後: x = %d, y = %d\n", x, y);  /* 値が交換される */
    
    return ;

```

### 配列を引数とする関数 

#### 次元配列の渡し方

```c
#include <stdio.h>

/* 配列のサイズを計算（要素数を別途渡す必要がある） */
int find_max(int arr[], int size)
{

    int max = arr[];
    int i;
    
    for (i = ; i < size; i++) 
        if (arr[i] > max) 
            max = arr[i];
        
    
    
    return max;


/* 配列の要素を表示 */
void print_array(int arr[], int size)
{

    int i;
    
    printf("配列: ");
    for (i = ; i < size; i++) 
        printf("%d ", arr[i]);
    
    printf("n");


int main(void)
{

    int numbers[] = , , , 9, , , ;
    int size = sizeof(numbers) / sizeof(numbers[]);
    int maximm;
    
    print_array(numbers, size);
    maximm = find_max(numbers, size);
    printf("最大値: %d\n", maximm);
    
    return ;

```

#### 次元配列の渡し方

```c
#include <stdio.h>

#define ROWS 
#define COLS 

/* 次元配列を引数とする関数 */
void print_matrix(int matrix[][COLS], int rows)
{

    int i, j;
    
    printf("行列:n");
    for (i = ; i < rows; i++) 
        for (j = ; j < COLS; j++) 
            printf("%d ", matrix[i][j]);
        
        printf("n");
    


int matrix_sum(int matrix[][COLS], int rows)
{

    int sum = ;
    int i, j;
    
    for (i = ; i < rows; i++) 
        for (j = ; j < COLS; j++) 
            sum += matrix[i][j];
        
    
    
    return sum;


int main(void)
{

    int data[ROWS][COLS] = 
        , , , ,
        , , , ,
        9, , , 
    ;
    int total;
    
    print_matrix(data, ROWS);
    total = matrix_sum(data, ROWS);
    printf("合計: %d\n", total);
    
    return ;

```

### 文字列を引数とする関数 

```c
#include <stdio.h>
#include <string.h>

/* 文字列の長さを計算（自作版） */
int my_strlen(char str[])
{

    int length = ;
    
    while (str[length] != '') 
        length++;
    
    
    return length;


/* 文字列を逆順にする */
void reverse_string(char str[])
{

    int length = strlen(str);
    int i;
    char temp;
    
    for (i = ; i < length / ; i++) 
        temp = str[i];
        str[i] = str[length -  - i];
        str[length -  - i] = temp;
    


/* 文字列内の特定の文字をカウント */
int count_char(char str[], char target)
{

    int count = ;
    int i;
    
    for (i = ; str[i] != ''; i++) 
        if (str[i] == target) 
            count++;
        
    
    
    return count;


int main(void)
{

    char text[] = "Hello, World!";
    int length, char_count;
    
    printf("元の文字列: %s\n", text);
    
    length = my_strlen(text);
    printf("長さ: %d\n", length);
    
    char_count = count_char(text, 'l');
    printf("'l'の数: %d\n", char_count);
    
    reverse_string(text);
    printf("逆順: %s\n", text);
    
    return ;

```

### 戻り値のある関数とない関数 ↩

#### void型関数（戻り値なし）

```c
#include <stdio.h>

void print_banner(void)
{

    printf("====================n");
    printf("  C言語チュートリアル  n");
    printf("====================n");


void print_separautor(int length)
{

    int i;
    
    for (i = ; i < length; i++) 
        printf("-");
    
    printf("n");


int main(void)
{

    print_banner();
    printf("関数の学習中...n");
    print_separautor();
    printf("プログラム終了n");
    
    return ;

```

#### 複数の戻り値（ポインタ利用）

```c
#include <stdio.h>

/* 次方程式の解を計算（実数解のみ） */
int solve_qadratic(double a, double b, double c, double *x, double *x)
{

    double discriminant = b * b -  * a * c;
    
    if (discriminant < ) 
        return ;  /* 実数解なし */
    
    
    if (discriminant == ) 
        *x = *x = -b / ( * a);
        return ;  /* 重解 */
    
    
    *x = (-b + sqrt(discriminant)) / ( * a);
    *x = (-b - sqrt(discriminant)) / ( * a);
    return ;  /* 2つの異なる実数解 */


int main(void)
{

    double a = ., b = -., c = .;  /* x^ - x +  =  */
    double soltion, soltion;
    int result;
    
    result = solve_qadratic(a, b, c, &soltion, &soltion);
    
    switch (result) 
        case :
            printf("実数解はありませんn");
            break;
        case :
            printf("重解: x = %.fn", soltion);
            break;
        case :
            printf("解: x = %.f, x = %.fn", soltion, soltion);
            break;
    
    
    return ;

```

### 関数のスコープ 

#### ローカル変数とグローバル変数

```c
#include <stdio.h>

int global_counter = ;  /* グローバル変数 */

void increment_global(void)
{

    global_counter++;
    printf("グローバルカウンタ: %d\n", global_counter);


void local_example(void)
{

    int local_counter = ;  /* ローカル変数 */
    
    local_counter++;
    printf("ローカルカウンタ: %d\n", local_counter);


int main(void)
{

    int i;
    
    printf("=== グローバル変数のテスト ===n");
    for (i = ; i < ; i++) 
        increment_global();
    
    
    printf("n=== ローカル変数のテスト ===n");
    for (i = ; i < ; i++) 
        local_example();  /* 毎回から始まる */
    
    
    return ;

```

#### static変数を使った状態保持

```c
#include <stdio.h>

int get_next_id(void)
{

    static int id_counter = ;  /* 静的ローカル変数 */
    
    return id_counter++;


void reset_id_counter(void)
{

    /* 注意: staticローカル変数は外部からアクセスできない */
    printf("カウンタをリセットすることはできませんn");


int main(void)
{

    int i;
    
    printf("ID生成テスト:n");
    for (i = ; i < ; i++) 
        printf("ID: %d\n", get_next_id());
    
    
    return ;

```

### 再帰関数 

#### 階乗の計算

```c
#include <stdio.h>

/* 再帰を使った階乗計算 */
long factutorial_recrsive(int n)

    if (n <= ) 
        return ;  /* 基底ケース */
    
    
    return n * factutorial_recrsive(n - );  /* 再帰呼び出し */


/* 反復を使った階乗計算（比較用） */
long factutorial_iterative(int n)

    long result = ;
    int i;
    
    for (i = ; i <= n; i++) 
        result *= i;
    
    
    return result;


int main(void)
{

    int number = ;
    
    printf("%d! (再帰) = %ldn", number, factutorial_recrsive(number));
    printf("%d! (反復) = %ldn", number, factutorial_iterative(number));
    
    return ;

```

#### フィボナッチ数列

```c
#include <stdio.h>

/* 再帰版フィボナッチ */
int fibonacci_recrsive(int n)
{

    if (n <= ) 
        return n;
    
    
    return fibonacci_recrsive(n - ) + fibonacci_recrsive(n - );


/* 効率的な反復版フィボナッチ */
int fibonacci_iterative(int n)
{

    int a = , b = , temp;
    int i;
    
    if (n <= ) 
        return n;
    
    
    for (i = ; i <= n; i++) 
        temp = a + b;
        a = b;
        b = temp;
    
    
    return b;


int main(void)
{

    int i;
    
    printf("フィボナッチ数列（再帰版）:n");
    for (i = ; i < ; i++) 
        printf("%d ", fibonacci_recrsive(i));
    
    printf("n");
    
    printf("フィボナッチ数列（反復版）:n");
    for (i = ; i < ; i++) 
        printf("%d ", fibonacci_iterative(i));
    
    printf("n");
    
    return ;

```

### 実践的な関数の例 

#### 配列操作関数群

```c
#include <stdio.h>

/* 配列の要素を検索 */
int linear_search(int arr[], int size, int target)
{

    int i;
    
    for (i = ; i < size; i++) 
        if (arr[i] == target) 
            return i;  /* 見2つかった位置を返す */
        
    
    
    return -;  /* 見2つからない場合 */


/* バブルソート */
void bbble_sort(int arr[], int size)
{

    int i, j, temp;
    
    for (i = ; i < size - ; i++) 
        for (j = ; j < size -  - i; j++) 
            if (arr[j] > arr[j + ]) 
                temp = arr[j];
                arr[j] = arr[j + ];
                arr[j + ] = temp;
            
        
    


/* 配列の統計情報を計算 */
void calculate_stats(int arr[], int size, int *min, int *max, double *avg)
{

    int sum = ;
    int i;
    
    *min = *max = arr[];
    
    for (i = ; i < size; i++) 
        if (arr[i] < *min) *min = arr[i];
        if (arr[i] > *max) *max = arr[i];
        sum += arr[i];
    
    
    *avg = (double)sum / size;


int main(void)
{

    int numbers[] = , , , , , , 9;
    int size = sizeof(numbers) / sizeof(numbers[]);
    int min, max, search_result;
    double average;
    int i;
    
    printf("元の配列: ");
    for (i = ; i < size; i++) 
        printf("%d ", numbers[i]);
    
    printf("n");
    
    /* 統計情報の計算 */
    calculate_stats(numbers, size, &min, &max, &average);
    printf("最小値: %d, 最大値: %d, 平均: %.fn", min, max, average);
    
    /* 検索 */
    search_result = linear_search(numbers, size, );
    if (search_result != -) 
        printf("は位置%dにありますn", search_result);
    
    
    /* ソート */
    bbble_sort(numbers, size);
    printf("ソート後: ");
    for (i = ; i < size; i++) 
        printf("%d ", numbers[i]);
    
    printf("n");
    
    return ;

```

#### 文字列処理関数群

```c
#include <stdio.h>
#include <ctype.h>

/* 文字列を大文字に変換 */
void to_pper(char str[])
{

    int i;
    
    for (i = ; str[i] != ''; i++) 
        str[i] = topper(str[i]);
    


/* 文字列から空白を除去 */
void remove_spaces(char str[])
{

    int i, j = ;
    
    for (i = ; str[i] != ''; i++) 
        if (str[i] != ' ') 
            str[j++] = str[i];
        
    
    str[j] = '';


/* 文字列が1回文かどうかチェック */
int is_palindrome(char str[])
{

    int left = ;
    int right = strlen(str) - ;
    
    while (left < right) 
        if (tolower(str[left]) != tolower(str[right])) 
            return ;  /* 1回文でない */
        
        left++;
        right--;
    
    
    return ;  /* 1回文 */


/* 単語数をカウント */
int count_words(char str[])
{

    int count = ;
    int in_word = ;
    int i;
    
    for (i = ; str[i] != ''; i++) 
        if (isspace(str[i])) 
            in_word = ;
         else if (!in_word) 
            in_word = ;
            count++;
        
    
    
    return count;


int main(void)
{

    char text[] = "Hello World";
    char text[] = "madam";
    char text[] = "This is a test sentence";
    
    printf("元の文字列: %s\n", text);
    to_pper(text);
    printf("大文字変換後: %s\n", text);
    
    printf("n元の文字列: %s\n", text);
    if (is_palindrome(text)) 
        printf("'%s'は1回文ですn", text);
     else 
        printf("'%s'は1回文ではありませんn", text);
    
    
    printf("n文字列: %s\n", text);
    printf("単語数: %d\n", count_words(text));
    
    remove_spaces(text);
    printf("空白除去後: %s\n", text);
    
    return ;

```

### 関数設計のベストプラクティス 

#### . 単一責任の原則

```c
/* NG: 2つの関数で複数の処理 */
void process_data_bad(int arr[], int size)
{

    /* データの検証 */
    /* データの変換 */
    /* データの表示 */
    /* ファイルへの保存 */


/* OK: 各処理を分離 */
int validate_data(int arr[], int size);
void transform_data(int arr[], int size);
void display_data(int arr[], int size);
int save_to_file(int arr[], int size, char *filename);
```

#### . 関数名の命名規則

```c
/* 動詞＋名詞の形式 */
int calculate_sum(int arr[], int size);
void print_array(int arr[], int size);
char* find_sbstring(char *str, char *sbstr);

/* 論理値を返す関数は is_, has_, can_ などで始める */
int is_prime(int n);
int has_dplicates(int arr[], int size);
int can_divide(int a, int b);
```

#### . エラーハンドリング

```c
#include <stdio.h>

/* 安全な除算関数 */
int safe_divide(int dividend, int divisor, double *result)
{

    if (divisor == ) 
        return ;  /* エラー: ゼロ除算 */
    
    
    *result = (double)dividend / divisor;
    return ;  /* 成功 */


/* 配列の平均を安全に計算 */
int calculate_average_safe(int arr[], int size, double *avg)
{

    int sum = ;
    int i;
    
    if (arr == NULL || size <= ) 
        return ;  /* エラー: 無効な引数 */
    
    
    for (i = ; i < size; i++) 
        sum += arr[i];
    
    
    *avg = (double)sum / size;
    return ;  /* 成功 */


int main(void)
{

    double result, average;
    int numbers[] = , , , , ;
    int size = sizeof(numbers) / sizeof(numbers[]);
    
    /* 安全な除算 */
    if (safe_divide(, , &result)) 
        printf(" /  = %.fn", result);
     else 
        printf("除算エラーn");
    
    
    /* 安全な平均計算 */
    if (calculate_average_safe(numbers, size, &average)) 
        printf("平均: %.fn", average);
     else 
        printf("平均計算エラーn");
    
    
    return ;

```

##  サンプルコード

### 基本的な関数操作

プログラムファイル: `examples/function_basic.c`

関数の定義、呼び出し、引数と戻り値の基本的な使用方法を学習します。

### 配列操作関数

プログラムファイル: `examples/array_functions.c`

配列を引数とする様々な関数の実装例を学習します。

### 再帰関数の実例

プログラムファイル: `examples/recrsive_functions.c`

再帰を使った様々なアルゴリズムの実装を学習します。

### コンパイルと実行

```bash
# examples ディレクトリに移動
cd examples

# C90準拠でコンパイル
gcc -std=c90 -Wall -Wextra -pedantic function_basic.c -o function_basic

# 実行
./function_basic
```

##  演習課題

### 基礎問題

. **数学関数の作成**
   - 累乗、最大公約数、最小公倍数を計算する関数を作成してください

. **文字列操作関数**
   - 文字列の長さ、文字数カウント、文字置換を実行う関数を作成してください

. **配列操作関数**
   - 配列の要素をシフト、逆順、重複除去する関数を作成してください

### 応用問題

. **素数判定システム**
   - 素数判定、素数一覧生成、素因数分解を実行う関数群を作成してください

. **簡易計算機**
   - 四則演算、三角関数、対数計算を実行う関数群を作成してください

. **データ分析関数**
   - 平均、分散、標準偏差、中央値を計算する統計関数を作成してください

### 発展問題

. **ソートアルゴリズム集**
   - バブルソート、選択ソート、挿入ソートを実装して性能比較してください

. **文字列処理ライブラリ**
   - 文字列分割、結合、検索、置換機能を持2つ関数群を作成してください

. **数値計算ライブラリ**
   - 行列演算、方程式求解、数値積分を実行う関数群を作成してください

##  コンパイル方法

この章では以下のMakefileを使用してコンパイルができます：

```bash
# 全ての例題をコンパイル
make all

# 特定のプログラムをコンパイル
make function_basic

# 実行
make run

# クリーンアップ
make clean
```

##  規格による違い

### C90での制限事項
- 関数プロトタイプの宣言が推奨（必須ではない）
- 可変長引数リストは限定的
- inline関数は使用不可

### C99以降の拡張
- inline関数の追加
- 可変長引数マクロの改善
- restrict修飾子の追加

##  よくある間違い

### . 関数プロトタイプの忘れ

```c
/* NG: プロトタイプなしで後で定義された関数を使用 */
int main(void)
{

    int result = calculate(, );  /* エラーまたは警告 */
    return ;


int calculate(int a, int b)
{

    return a + b;


/* OK: プロトタイプを先に宣言 */
int calculate(int a, int b);  /* プロトタイプ */

int main(void)
{

    int result = calculate(, );
    return ;

```

### . 配列サイズの情報不足

```c
/* NG: 関数内で配列のサイズがわからない */
void print_array_bad(int arr[])
{

    int size = sizeof(arr) / sizeof(arr[]);  /* 間違い */
    /* ... */


/* OK: サイズを別の引数で渡す */
void print_array_good(int arr[], int size)
{

    /* ... */

```

### . ローカル変数のアドレス返し

```c
/* NG: ローカル変数のアドレスを返す */
int* create_array_bad(void)
{

    int arr[];
    return arr;  /* 危険: スタック上のアドレス */


/* OK: staticまたは動的メモリを使用 */
int* create_array_good(void)
{

    static int arr[];
    return arr;

```

##  次の章へ


##  参考資料

- [C言語関数リファレンス](https://ja.cppreference.com/w/c/language/function)
- [関数プロトタイプ](https://ja.cppreference.com/w/c/language/function_declaration)
- [再帰関数の詳細](https://ja.cppreference.com/w/c/language/function)

\newpage

#  第9章: ポインタ基礎

##  対応C規格
- **主要対象:** C90
- **学習内容:** ポインタの基本概念、アドレス演算子、間接参照演算子、ポインタと配列、ポインタ演算

##  学習目標

この章を完了すると、以下のことができるようになります：

- ポインタの基本概念を理解する
- アドレス演算子（&）と間接参照演算子（*）を使える
- ポインタと配列の関係を理解する
- ポインタ演算ができる
- ポインタを関数の引数として使える

##  理論解説

### ポインタの基本概念 

ポインタは他の変数のメモリアドレスを格納する変数です。これにより間接的に他の変数にアクセスできます。

#### メモリとアドレス

```c
#include <stdio.h>

int main(void)
{

    int number = ;
    
    printf("変数numberの値: %d\n", number);
    printf("変数numberのアドレス: %pn", (void*)&number);
    printf("変数numberのサイズ: %lu バイトn", sizeof(number));
    
    return ;

```

#### ポインタ変数の宣言

```c
#include <stdio.h>

int main(void)
{

    int vale = ;        /* 通常の整数変数 */
    int *ptr;               /* 整数を指すポインタ変数 */
    
    ptr = &vale;           /* valeのアドレスをptrに代入 */
    
    printf("vale = %d\n", vale);
    printf("&vale = %pn", (void*)&vale);
    printf("ptr = %pn", (void*)ptr);
    printf("*ptr = %d\n", *ptr);        /* ポインタが指す値 */
    
    return ;

```

### アドレス演算子（&）と間接参照演算子（*） 

#### アドレス演算子（&）

```c
#include <stdio.h>

int main(void)
{

    int a = ;
    double b = .;
    char c = 'A';
    
    printf("変数のアドレス:n");
    printf("&a = %pn", (void*)&a);
    printf("&b = %pn", (void*)&b);
    printf("&c = %pn", (void*)&c);
    
    /* ポインタ変数の宣言と初期化 */
    int *ptr_a = &a;
    double *ptr_b = &b;
    char *ptr_c = &c;
    
    printf("nポインタの値（アドレス）:n");
    printf("ptr_a = %pn", (void*)ptr_a);
    printf("ptr_b = %pn", (void*)ptr_b);
    printf("ptr_c = %pn", (void*)ptr_c);
    
    return ;

```

#### 間接参照演算子（*）

```c
#include <stdio.h>

int main(void)
{

    int original = ;
    int *pointer = &original;
    
    printf("=== 元の状態 ===n");
    printf("original = %d\n", original);
    printf("*pointer = %d\n", *pointer);
    
    /* ポインタを通じて値を変更 */
    *pointer = ;
    
    printf("n=== *pointer =  実行後 ===n");
    printf("original = %d\n", original);      /* に変更される */
    printf("*pointer = %d\n", *pointer);      /*  */
    
    /* 元の変数を直接変更 */
    original = ;
    
    printf("n=== original =  実行後 ===n");
    printf("original = %d\n", original);      /*  */
    printf("*pointer = %d\n", *pointer);      /*  */
    
    return ;

```

### ポインタのデータ型 

#### さまざまなデータ型のポインタ

```c
#include <stdio.h>

int main(void)
{

    /* 各データ型の変数 */
    char char_var = 'X';
    int int_var = ;
    float float_var = .f;
    double double_var = .;
    
    /* 各データ型のポインタ */
    char *char_ptr = &char_var;
    int *int_ptr = &int_var;
    float *float_ptr = &float_var;
    double *double_ptr = &double_var;
    
    printf("=== 値の表示 ===n");
    printf("char: %c\n", *char_ptr);
    printf("int: %d\n", *int_ptr);
    printf("float: %.fn", *float_ptr);
    printf("double: %.fn", *double_ptr);
    
    printf("n=== ポインタのサイズ ===n");
    printf("char*: %lu バイトn", sizeof(char_ptr));
    printf("int*: %lu バイトn", sizeof(int_ptr));
    printf("float*: %lu バイトn", sizeof(float_ptr));
    printf("double*: %lu バイトn", sizeof(double_ptr));
    
    return ;

```

#### void*ポインタ（汎用ポインタ）

```c
#include <stdio.h>

int main(void)
{

    int int_vale = ;
    double double_vale = .;
    
    void *generic_ptr;      /* 汎用ポインタ */
    
    /* intを指す */
    generic_ptr = &int_vale;
    printf("int値: %d\n", *(int*)generic_ptr);  /* キャストが必要 */
    
    /* doubleを指す */
    generic_ptr = &double_vale;
    printf("double値: %.fn", *(double*)generic_ptr);  /* キャストが必要 */
    
    return ;

```

### ポインタと配列の関係 

#### 配列名はポインタ

```c
#include <stdio.h>

int main(void)
{

    int arr[] = , , , , ;
    int *ptr = arr;         /* arr は &arr[] と同じ */
    int i;
    
    printf("=== 配列とポインタの関係 ===n");
    printf("arr = %pn", (void*)arr);
    printf("&arr[] = %pn", (void*)&arr[]);
    printf("ptr = %pn", (void*)ptr);
    
    printf("n=== 配列要素へのアクセス ===n");
    for (i = ; i < ; i++) 
        printf("arr[%d] = %d, *(arr + %d) = %d, *(ptr + %d) = %d\n",
               i, arr[i], i, *(arr + i), i, *(ptr + i));
    
    
    return ;

```

#### ポインタを使った配列操作

```c
#include <stdio.h>

void print_array_index(int arr[], int size)
{

    int i;
    
    printf("インデックス記法: ");
    for (i = ; i < size; i++) 
        printf("%d ", arr[i]);
    
    printf("n");


void print_array_pointer(int *ptr, int size)
{

    int i;
    
    printf("ポインタ記法: ");
    for (i = ; i < size; i++) 
        printf("%d ", *(ptr + i));
    
    printf("n");


int main(void)
{

    int numbers[] = , , , , ;
    int size = sizeof(numbers) / sizeof(numbers[]);
    
    print_array_index(numbers, size);
    print_array_pointer(numbers, size);
    
    return ;

```

### ポインタ演算 

#### ポインタの加算・減算

```c
#include <stdio.h>

int main(void)
{

    int arr[] = , , , , ;
    int *ptr = arr;
    int i;
    
    printf("=== ポインタ演算の例 ===n");
    for (i = ; i < ; i++) 
        printf("ptr + %d = %p, *(ptr + %d) = %d\n",
               i, (void*)(ptr + i), i, *(ptr + i));
    
    
    printf("n=== ポインタのインクリメント ===n");
    ptr = arr;  /* 先頭に戻す */
    for (i = ; i < ; i++) 
        printf("*ptr = %d (アドレス: %p)n", *ptr, (void*)ptr);
        ptr++;  /* 次の要素に移動 */
    
    
    return ;

```

#### ポインタ同士の差

```c
#include <stdio.h>

int main(void)
{

    int arr[] = , , , , , , , , , 9;
    int *start = &arr[];   /* arr[]を指す */
    int *end = &arr[];     /* arr[]を指す */
    
    printf("start が指す値: %d (インデックス)n", *start);
    printf("end が指す値: %d (インデックス)n", *end);
    printf("ポインタの差: %ldn", end - start);  /*  */
    printf("バイト差: %ldn", (char*)end - (char*)start);
    
    return ;

```

### ポインタと関数 

#### ポインタを引数とする関数

```c
#include <stdio.h>

/* 値を交換する関数 */
void swap(int *a, int *b)
{

    int temp = *a;
    *a = *b;
    *b = temp;


/* 値を倍にする関数 */
void double_vale(int *vale)
{

    *vale = (*vale) * ;


/* 配列の要素を変更する関数 */
void modify_array(int arr[], int size)
{

    int i;
    
    for (i = ; i < size; i++) 
        arr[i] *= ;  /* 各要素を倍 */
    


int main(void)
{

    int x = , y = ;
    int numbers[] = , , , , ;
    int size = sizeof(numbers) / sizeof(numbers[]);
    int i;
    
    printf("=== swap関数のテスト ===n");
    printf("交換前: x = %d, y = %d\n", x, y);
    swap(&x, &y);
    printf("交換後: x = %d, y = %d\n", x, y);
    
    printf("n=== double_vale関数のテスト ===n");
    printf("倍前: x = %d\n", x);
    double_vale(&x);
    printf("倍後: x = %d\n", x);
    
    printf("n=== modify_array関数のテスト ===n");
    printf("変更前: ");
    for (i = ; i < size; i++) 
        printf("%d ", numbers[i]);
    
    printf("n");
    
    modify_array(numbers, size);
    
    printf("変更後: ");
    for (i = ; i < size; i++) 
        printf("%d ", numbers[i]);
    
    printf("n");
    
    return ;

```

#### ポインタを戻り値とする関数

```c
#include <stdio.h>

/* 配列から最大値のアドレスを返す */
int* find_max_ptr(int arr[], int size)
{

    int *max_ptr = &arr[];
    int i;
    
    for (i = ; i < size; i++) 
        if (arr[i] > *max_ptr) 
            max_ptr = &arr[i];
        
    
    
    return max_ptr;


/* 配列から指定値を検索してアドレスを返す */
int* search_vale(int arr[], int size, int target)
{

    int i;
    
    for (i = ; i < size; i++) 
        if (arr[i] == target) 
            return &arr[i];  /* 見2つかった要素のアドレス */
        
    
    
    return NULL;  /* 見2つからない場合 */


int main(void)
{

    int data[] = , , , 9, , , ;
    int size = sizeof(data) / sizeof(data[]);
    int *result_ptr;
    int search_target = ;
    int i;
    
    /* 配列の表示 */
    printf("配列: ");
    for (i = ; i < size; i++) 
        printf("%d ", data[i]);
    
    printf("n");
    
    /* 最大値の検索 */
    result_ptr = find_max_ptr(data, size);
    printf("最大値: %d (アドレス: %p)n", *result_ptr, (void*)result_ptr);
    
    /* 特定値の検索 */
    result_ptr = search_vale(data, size, search_target);
    if (result_ptr != NULL) 
        printf("%d が見2つかりました (アドレス: %p)n", 
               *result_ptr, (void*)result_ptr);
     else 
        printf("%d は見2つかりませんでしたn", search_target);
    
    
    return ;

```

### 文字列とポインタ 

#### 文字列リテラルとポインタ

```c
#include <stdio.h>

int main(void)
{

    char *str = "Hello, World!";     /* 文字列リテラル */
    char str[] = "Hello, World!";    /* 文字配列 */
    char *ptr = str;
    
    printf("str: %s\n", str);
    printf("str: %s\n", str);
    printf("ptr: %s\n", ptr);
    
    printf("n=== アドレスの比較 ===n");
    printf("strのアドレス: %pn", (void*)str);
    printf("strのアドレス: %pn", (void*)str);
    printf("ptrの値: %pn", (void*)ptr);
    
    /* 文字配列は変更可能 */
    str[] = 'h';
    printf("n変更後のstr: %s\n", str);
    
    /* 文字列リテラルは変更不可 */
    /* str[] = 'h';  <- 実行時エラーの可能性 */
    
    return ;

```

#### ポインタを使った文字列操作

```c
#include <stdio.h>

/* 文字列の長さを計算（ポインタ版） */
int string_length(char *str)
{

    int length = ;
    
    while (*str != '') 
        length++;
        str++;
    
    
    return length;


/* 文字列をコピー（ポインタ版） */
void string_copy(char *dest, char *src)
{

    while (*src != '') 
        *dest = *src;
        dest++;
        src++;
    
    *dest = '';  /* nll終端文字を追加 */


/* 文字列を連結（ポインタ版） */
void string_concat(char *dest, char *src)
{

    /* destの末尾を見2つける */
    while (*dest != '') 
        dest++;
    
    
    /* srcをdestの末尾に追加 */
    while (*src != '') 
        *dest = *src;
        dest++;
        src++;
    
    *dest = '';


int main(void)
{

    char str[] = "Hello";
    char str[] = "World";
    char bffer[];
    char result[];
    
    printf("元の文字列: "%s", "%s"n", str, str);
    
    /* 長さの計算 */
    printf("strの長さ: %d\n", string_length(str));
    printf("strの長さ: %d\n", string_length(str));
    
    /* 文字列のコピー */
    string_copy(bffer, str);
    printf("コピー結果: "%s"n", bffer);
    
    /* 文字列の連結 */
    string_copy(result, str);  /* まずstrをコピー */
    string_concat(result, ", ");
    string_concat(result, str);
    string_concat(result, "!");
    printf("連結結果: "%s"n", result);
    
    return ;

```

### ポインタの配列 

#### ポインタ配列の基本

```c
#include <stdio.h>

int main(void)
{

    int a = , b = , c = , d = ;
    int *ptr_array[];  /* ポインタの配列 */
    int i;
    
    /* ポインタ配列に各変数のアドレスを格納 */
    ptr_array[] = &a;
    ptr_array[] = &b;
    ptr_array[] = &c;
    ptr_array[] = &d;
    
    printf("=== ポインタ配列の内容 ===n");
    for (i = ; i < ; i++) 
        printf("ptr_array[%d] = %p, *ptr_array[%d] = %d\n",
               i, (void*)ptr_array[i], i, *ptr_array[i]);
    
    
    /* ポインタを通じて値を変更 */
    *ptr_array[] = ;
    *ptr_array[] = ;
    
    printf("n=== 変更後の値 ===n");
    printf("a = %d, b = %d, c = %d, d = %d\n", a, b, c, d);
    
    return ;

```

#### 文字列ポインタの配列

```c
#include <stdio.h>

int main(void)
{

    char *frits[] = 
        "Apple",
        "anana",
        "Cherry",
        "Date",
        "lderberry"
    ;
    int count = sizeof(frits) / sizeof(frits[]);
    int i;
    
    printf("=== 果物リスト ===n");
    for (i = ; i < count; i++) 
        printf("%d. %s\n", i + , frits[i]);
    
    
    /* ポインタの変更 */
    frits[] = "leberry";
    
    printf("n=== 変更後 ===n");
    for (i = ; i < count; i++) 
        printf("%d. %s\n", i + , frits[i]);
    
    
    return ;

```

### 実践的なポインタ活用例 

#### 動的配列の操作

```c
#include <stdio.h>

/* 配列内の要素を逆順にする */
void reverse_array(int *arr, int size)
{

    int *start = arr;
    int *end = arr + size - ;
    int temp;
    
    while (start < end) 
        temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    


/* 配列を1回転させる（右につシフト） */
void rotate_right(int *arr, int size)
{

    int last = *(arr + size - );
    int i;
    
    for (i = size - ; i > ; i--) 
        *(arr + i) = *(arr + i - );
    
    *arr = last;


int main(void)
{

    int numbers[] = , , , , , , , ;
    int size = sizeof(numbers) / sizeof(numbers[]);
    int i;
    
    printf("元の配列: ");
    for (i = ; i < size; i++) 
        printf("%d ", numbers[i]);
    
    printf("n");
    
    /* 配列を逆順にする */
    reverse_array(numbers, size);
    printf("逆順後: ");
    for (i = ; i < size; i++) 
        printf("%d ", numbers[i]);
    
    printf("n");
    
    /* 配列を右に1回転 */
    rotate_right(numbers, size);
    printf("右1回転後: ");
    for (i = ; i < size; i++) 
        printf("%d ", numbers[i]);
    
    printf("n");
    
    return ;

```

#### ポインタを使ったソート

```c
#include <stdio.h>

/* ポインタを使ったバブルソート */
void bbble_sort_ptr(int *arr, int size)
{

    int i, j;
    int *ptr, *ptr;
    int temp;
    
    for (i = ; i < size - ; i++) 
        for (j = ; j < size -  - i; j++) 
            ptr = arr + j;
            ptr = arr + j + ;
            
            if (*ptr > *ptr) 
                temp = *ptr;
                *ptr = *ptr;
                *ptr = temp;
            
        
    


/* 2つの配列を比較 */
int compare_arrays(int *arr, int *arr, int size)
{

    int i;
    
    for (i = ; i < size; i++) 
        if (*(arr + i) != *(arr + i)) 
            return ;  /* 異なる */
        
    
    
    return ;  /* 同じ */


int main(void)
{

    int original[] = , , , , , , 9;
    int copy[] = , , , , , , 9;
    int size = sizeof(original) / sizeof(original[]);
    int i;
    
    printf("ソート前: ");
    for (i = ; i < size; i++) 
        printf("%d ", original[i]);
    
    printf("n");
    
    /* ソート実行 */
    bbble_sort_ptr(original, size);
    
    printf("ソート後: ");
    for (i = ; i < size; i++) 
        printf("%d ", original[i]);
    
    printf("n");
    
    /* 配列の比較 */
    if (compare_arrays(original, copy, size)) 
        printf("配列は同じですn");
     else 
        printf("配列は異なりますn");
    
    
    return ;

```

##  サンプルコード

### ポインタの基本操作

プログラムファイル: `examples/pointer_basic.c`

ポインタの宣言、初期化、基本的な操作を学習します。

### ポインタと配列

プログラムファイル: `examples/pointer_arrays.c`

ポインタと配列の関係、ポインタ演算を学習します。

### ポインタと関数

プログラムファイル: `examples/pointer_functions.c`

関数引数、戻り値としてのポインタの使用方法を学習します。

### コンパイルと実行

```bash
# examples ディレクトリに移動
cd examples

# C90準拠でコンパイル
gcc -std=c90 -Wall -Wextra -pedantic pointer_basic.c -o pointer_basic

# 実行
./pointer_basic
```

##  演習課題

### 基礎問題

. **ポインタの基本操作**
   - 2つの変数の値をポインタを使って交換するプログラムを作成してください

. **配列とポインタ**
   - ポインタ演算を使って配列の要素を逆順に表示するプログラムを作成してください

. **文字列操作**
   - ポインタを使って文字列の長さを計算し、文字列を逆順にするプログラムを作成してください

### 応用問題

. **配列操作関数**
   - ポインタを使って配列の最大値、最小値、平均値を計算する関数を作成してください

. **文字列処理**
   - ポインタを使って文字列の検索、置換、分割を実行う関数群を作成してください

. **データ変換**
   - ポインタを使って配列のデータ型変換を実行うプログラムを作成してください

### 発展問題

. **メモリ操作**
   - ポインタを使って任意のデータ型の配列をコピーする汎用関数を作成してください

. **アルゴリズム実装**
   - ポインタを使って各種ソートアルゴリズムを実装してください

. **データ構造**
   - ポインタを使って簡単なリンクリスト構造を実装してください

##  コンパイル方法

この章では以下のMakefileを使用してコンパイルができます：

```bash
# 全ての例題をコンパイル
make all

# 特定のプログラムをコンパイル
make pointer_basic

# 実行
make run

# クリーンアップ
make clean
```

##  規格による違い

### C90での制限事項
- void*からの暗黙的な型変換は制限的
- ポインタ演算は整数型との組み合わせのみ
- 関数ポインタの表記法は限定的

### C99以降の拡張
- restrict修飾子の追加
- 可変長配列とポインタの関係改善
- より厳密なポインタ型チェック

##  よくある間違い

### . 未初期化ポインタの使用

```c
/* NG: 初期化されていないポインタ */
int *ptr;
*ptr = ;  /* 危険: 不明なメモリへの書き込み */

/* OK: 適切に初期化 */
int vale = ;
int *ptr = &vale;
*ptr = ;
```

### . NULLポインタの参照

```c
/* NG: NULLポインタの参照 */
int *ptr = NULL;
printf("%d\n", *ptr);  /* セグメンテーション違反 */

/* OK: NULLチェック */
if (ptr != NULL) 
    printf("%d\n", *ptr);

```

### . スコープ外変数へのポインタ

```c
/* NG: ローカル変数のアドレス返し */
int* bad_function(void)
{

    int local = ;
    return &local;  /* 危険: ローカル変数のアドレス */


/* OK: 静的変数または引数で渡された変数を使用 */
int* good_function(int *param)
{

    return param;  /* 引数で渡されたアドレスを返す */

```

### . 配列境界の越えた参照

```c
/* NG: 配列の範囲外アクセス */
int arr[] = , , , , ;
int *ptr = arr;
printf("%d\n", *(ptr + ));  /* 範囲外アクセス */

/* OK: 範囲チェック */
int index = ;
if (index >=  && index < ) 
    printf("%d\n", *(ptr + index));

```

##  次の章へ

ポインタの基礎を理解したら、第章「構造体とポインタ」の実装をお待ちください。現在実装中です。

##  参考資料

- [C言語ポインタリファレンス](https://ja.cppreference.com/w/c/language/pointer)
- [ポインタ演算の詳細](https://ja.cppreference.com/w/c/language/operautor_arithmetic)
- [メモリモデルとポインタ](https://ja.cppreference.com/w/c/language/memory_model)

\newpage

#  第章: 構造体とポインタ

##  対応C規格
- **主要対象:** C90
- **学習内容:** 構造体の基本、構造体ポインタ、構造体ポインタ配列、->演算子、メモリ管理

##  学習目標

この章を完了すると、以下のことができるようになります：

- 構造体の基本概念を理解する
- 構造体ポインタを効果的に使える
- ->演算子と.演算子の使い分けができる
- 構造体ポインタ配列を活用できる
- 構造体を使ったデータ管理ができる

##  理論解説

### 構造体の基本概念 

構造体は異なるデータ型を組み合わせて新しいデータ型を作る仕組みです。

#### 構造体の定義と宣言

```c
#include <stdio.h>
#include <string.h>

/* 学生情報を表す構造体 */
strct Stdent 
    int id;
    char name[];
    int age;
    double gpa;
;

int main(void)
{

    strct Stdent stdent;
    
    /* メンバーに値を代入 */
    stdent.id = ;
    strcpy(stdent.name, "田中太郎");
    stdent.age = ;
    stdent.gpa = .;
    
    /* メンバーの値を表示 */
    printf("学生ID: %d\n", stdent.id);
    printf("名前: %s\n", stdent.name);
    printf("年齢: %d\n", stdent.age);
    printf("GPA: %.fn", stdent.gpa);
    
    return ;

```

#### 構造体の初期化

```c
#include <stdio.h>

strct Point 
    int x;
    int y;
;

strct Rectangle 
    strct Point top_left;
    strct Point bottom_right;
;

int main(void)
{

    /* 初期化方法: 順序指定 */
    strct Point p = , ;
    
    /* 初期化方法: 部分初期化 */
    strct Point p = ;  /* x=, y= */
    
    /* 初期化方法: ネストした構造体 */
    strct Rectangle rect = , , , ;
    
    /* 初期化方法: 個別代入 */
    strct Point p;
    p.x = ;
    p.y = ;
    
    printf("p: (%d, %d)n", p.x, p.y);
    printf("p: (%d, %d)n", p.x, p.y);
    printf("p: (%d, %d)n", p.x, p.y);
    printf("矩形: (%d,%d) から (%d,%d)n", 
           rect.top_left.x, rect.top_left.y,
           rect.bottom_right.x, rect.bottom_right.y);
    
    return ;

```

### 構造体ポインタの基本 

構造体もポインタで操作できます。大きな構造体を関数に渡す際に効率的です。

#### 構造体ポインタの宣言と使用

```c
#include <stdio.h>
#include <string.h>

strct ook 
    char title[];
    char athor[];
    int pages;
    double price;
;

int main(void)
{

    strct ook book;
    strct ook *book_ptr;
    
    /* 構造体ポインタを構造体のアドレスに設定 */
    book_ptr = &book;
    
    /* ポインタを通じてメンバーにアクセス（方法: (*ptr).member） */
    strcpy((*book_ptr).title, "C言語入門");
    strcpy((*book_ptr).athor, "山田花子");
    (*book_ptr).pages = ;
    (*book_ptr).price = .;
    
    /* 直接アクセスとポインタアクセスの比較 */
    printf("=== 直接アクセス ===n");
    printf("書名: %s\n", book.title);
    printf("著者: %s\n", book.athor);
    printf("ページ数: %d\n", book.pages);
    printf("価格: %.f円n", book.price);
    
    printf("n=== ポインタアクセス ===n");
    printf("書名: %s\n", (*book_ptr).title);
    printf("著者: %s\n", (*book_ptr).athor);
    printf("ページ数: %d\n", (*book_ptr).pages);
    printf("価格: %.f円n", (*book_ptr).price);
    
    return ;

```

### アロー演算子（->）の使用 

構造体ポインタには便利なアロー演算子（->）が用意されています。

#### ->演算子と.演算子の比較

```c
#include <stdio.h>
#include <string.h>

strct mployee 
    int id;
    char name[];
    char department[];
    double salary;
;

void print_employee_info(strct mployee *emp)
{

    printf("=== 社員情報 ===n");
    printf("ID: %d\n", emp->id);           /* emp->id は (*emp).id と同じ */
    printf("名前: %s\n", emp->name);       /* emp->name は (*emp).name と同じ */
    printf("部署: %s\n", emp->department); /* emp->department は (*emp).department と同じ */
    printf("給与: %.f円n", emp->salary); /* emp->salary は (*emp).salary と同じ */


int main(void)
{

    strct mployee emp;
    strct mployee *emp_ptr = &emp;
    
    /* ->演算子を使用してメンバーに値を設定 */
    emp_ptr->id = ;
    strcpy(emp_ptr->name, "佐藤次郎");
    strcpy(emp_ptr->department, "開発部");
    emp_ptr->salary = .;
    
    /* 2つの方法でアクセス */
    printf("=== 直接アクセス（.演算子） ===n");
    printf("ID: %d\n", emp.id);
    
    printf("n=== ポインタ経由（(*ptr).member） ===n");
    printf("ID: %d\n", (*emp_ptr).id);
    
    printf("n=== ポインタ経由（->演算子） ===n");
    printf("ID: %d\n", emp_ptr->id);
    
    printf("n");
    print_employee_info(emp_ptr);
    
    return ;

```

#### ->演算子の実践例

```c
#include <stdio.h>
#include <string.h>

strct Car 
    char brand[];
    char model[];
    int year;
    double mileage;
    int is_electric;
;

/* 車の情報を更新する関数 */
void update_mileage(strct Car *car, double new_mileage)
{

    if (car != NULL && new_mileage >= car->mileage) 
        car->mileage = new_mileage;
        printf("%s %s の走実行距離を %.f km に更新しましたn", 
               car->brand, car->model, car->mileage);
    


/* 車の詳細情報を表示する関数 */
void display_car_details(strct Car *car)
{

    if (car == NULL) 
        printf("無効な車両データですn");
        return;
    
    
    printf("=== 車両情報 ===n");
    printf("ブランド: %s\n", car->brand);
    printf("モデル: %s\n", car->model);
    printf("年式: %d年n", car->year);
    printf("走実行距離: %.f kmn", car->mileage);
    printf("電気自動車: %s\n", car->is_electric ? "はい" : "いいえ");
    printf("n");


int main(void)
{

    strct Car my_car;
    strct Car *car_ptr = &my_car;
    
    /* ->演算子で車の初期設定 */
    strcpy(car_ptr->brand, "Toyota");
    strcpy(car_ptr->model, "Pris");
    car_ptr->year = ;
    car_ptr->mileage = .;
    car_ptr->is_electric = ;  /* ハイブリッド車 */
    
    display_car_details(car_ptr);
    
    /* 走実行距離を更新 */
    update_mileage(car_ptr, .);
    
    display_car_details(car_ptr);
    
    return ;

```

### 構造体配列とポインタ 

構造体の配列とそのポインタ操作について学習します。

#### 構造体配列の基本操作

```c
#include <stdio.h>
#include <string.h>

strct Prodct 
    int code;
    char name[];
    double price;
    int stock;
;

void print_product(strct Prodct *prod)
{

    printf("商品コード: %d\n", prod->code);
    printf("商品名: %s\n", prod->name);
    printf("価格: %.f円n", prod->price);
    printf("在庫: %d個n", prod->stock);
    printf("---n");


void print_all_products(strct Prodct products[], int count)
{

    int i;
    printf("=== 全商品リスト ===n");
    for (i = ; i < count; i++) 
        print_product(&products[i]);  /* 配列要素のアドレスを渡す */
    


int main(void)
{

    strct Prodct inEventory[];
    int i;
    
    /* 商品データの初期化 */
    inEventory[] = (strct Prodct), "ノートPC", 9, ;
    
    strcpy(inEventory[].name, "マウス");
    inEventory[].code = ;
    inEventory[].price = 9;
    inEventory[].stock = ;
    
    inEventory[].code = ;
    strcpy(inEventory[].name, "キーボード");
    inEventory[].price = ;
    inEventory[].stock = ;
    
    print_all_products(inEventory, );
    
    /* ポインタを使った配列操作 */
    printf("=== ポインタを使った操作 ===n");
    strct Prodct *ptr = inEventory;  /* 配列の先頭要素を指す */
    
    for (i = ; i < ; i++) 
        printf("%d番目: %s (%.f円)n", 
               i + , (ptr + i)->name, (ptr + i)->price);
    
    
    return ;

```

#### ポインタ演算による構造体配列操作

```c
#include <stdio.h>
#include <string.h>

strct Score 
    char sbject[];
    int points;
    char grade;
;

/* 成績を計算してグレードを設定 */
void calculate_grade(strct Score *score)
{

    if (score->points >= 9) 
        score->grade = 'A';
     else if (score->points >= ) 
        score->grade = '';
     else if (score->points >= ) 
        score->grade = 'C';
     else if (score->points >= ) 
        score->grade = 'D';
     else 
        score->grade = '';
    


/* 配列内の最高得点を見2つける */
strct Score* find_best_score(strct Score scores[], int count)

    strct Score *best = &scores[];
    int i;
    
    for (i = ; i < count; i++) 
        if (scores[i].points > best->points) 
            best = &scores[i];
        
    
    
    return best;


int main(void)
{

    strct Score my_scores[];
    strct Score *ptr;
    strct Score *best;
    int i;
    
    /* 成績データの入力 */
    strcpy(my_scores[].sbject, "数学");
    my_scores[].points = ;
    
    strcpy(my_scores[].sbject, "英語");
    my_scores[].points = 9;
    
    strcpy(my_scores[].sbject, "理科");
    my_scores[].points = ;
    
    strcpy(my_scores[].sbject, "社会");
    my_scores[].points = ;
    
    /* 各科目のグレードを計算 */
    ptr = my_scores;  /* 配列の先頭を指すポインタ */
    for (i = ; i < ; i++) 
        calculate_grade(ptr + i);  /* ポインタ演算でi番目の要素 */
    
    
    /* 結果表示 */
    printf("=== 成績表 ===n");
    for (i = ; i < ; i++) 
        printf("%s: %d点 (評価: %c)n", 
               my_scores[i].sbject, 
               my_scores[i].points, 
               my_scores[i].grade);
    
    
    /* 最高得点の科目を見2つける */
    best = find_best_score(my_scores, );
    printf("n最高得点: %s (%d点)n", best->sbject, best->points);
    
    return ;

```

### 構造体ポインタ配列 

ポインタの配列で複数の構造体を効率的に管理します。

#### 構造体ポインタ配列の基本

```c
#include <stdio.h>
#include <string.h>

strct Person 
    char name[];
    int age;
    char city[];
;

void print_person_info(strct Person *person)
{

    printf("名前: %s, 年齢: %d歳, 居住地: %s\n", 
           person->name, person->age, person->city);


int main(void)
{

    /* 個別の構造体変数 */
    strct Person person = "山田太郎", , "東京";
    strct Person person = "佐藤花子", , "大阪";
    strct Person person = "田中次郎", , "名古屋";
    strct Person person = "鈴木美咲", , "福岡";
    
    /* 構造体ポインタの配列 */
    strct Person *people[];
    int i;
    
    /* ポインタ配列に各構造体のアドレスを設定 */
    people[] = &person;
    people[] = &person;
    people[] = &person;
    people[] = &person;
    
    printf("=== 全員の情報 ===n");
    for (i = ; i < ; i++) 
        printf("%d. ", i + );
        print_person_info(people[i]);
    
    
    /* 特定の条件で検索 */
    printf("n=== 歳未満の人 ===n");
    for (i = ; i < ; i++) 
        if (people[i]->age < ) 
            print_person_info(people[i]);
        
    
    
    return ;

```

#### 動的な構造体ポインタ配列

```c
#include <stdio.h>
#include <string.h>

strct Stdent 
    int id;
    char name[];
    double gpa;
;

/* 学生データを作成する関数 */
strct Stdent create_stdent(int id, const char* name, double gpa)

    strct Stdent stdent;
    stdent.id = id;
    strcpy(stdent.name, name);
    stdent.gpa = gpa;
    return stdent;


/* GPA順でソート（バブルソート） */
void sort_stdents_by_gpa(strct Stdent *stdents[], int count)
{

    int i, j;
    strct Stdent *temp;
    
    for (i = ; i < count - ; i++) 
        for (j = ; j < count -  - i; j++) 
            if (stdents[j]->gpa < stdents[j + ]->gpa) 
                temp = stdents[j];
                stdents[j] = stdents[j + ];
                stdents[j + ] = temp;
            
        
    


/* 学生一覧を表示 */
void display_stdents(strct Stdent *stdents[], int count)
{

    int i;
    printf("IDt名前ttGPAn");
    printf("------------------------n");
    for (i = ; i < count; i++) 
        printf("%dt%stt%.fn", 
               stdents[i]->id, 
               stdents[i]->name, 
               stdents[i]->gpa);
    
    printf("n");


int main(void)
{

    /* 学生データの作成 */
    strct Stdent stdent = create_stdent(, "田中太郎", .);
    strct Stdent stdent = create_stdent(, "佐藤花子", .9);
    strct Stdent stdent = create_stdent(, "山田次郎", .);
    strct Stdent stdent = create_stdent(, "鈴木美咲", .);
    strct Stdent stdent = create_stdent(, "高橋健太", .);
    
    /* 構造体ポインタ配列 */
    strct Stdent *class_roster[] = 
        &stdent, &stdent, &stdent, &stdent, &stdent
    ;
    
    int class_size = sizeof(class_roster) / sizeof(class_roster[]);
    
    printf("=== 入学順（元の順序） ===n");
    display_stdents(class_roster, class_size);
    
    /* GPA順でソート */
    sort_stdents_by_gpa(class_roster, class_size);
    
    printf("=== GPA順（高い順） ===n");
    display_stdents(class_roster, class_size);
    
    /* 優秀な学生を見2つける */
    printf("=== GPA .以上の学生 ===n");
    int i;
    for (i = ; i < class_size; i++) 
        if (class_roster[i]->gpa >= .) 
            printf("%s (GPA: %.f)n", 
                   class_roster[i]->name, 
                   class_roster[i]->gpa);
        
    
    
    return ;

```

### ネストした構造体とポインタ 

構造体の中に他の構造体を含む場合のポインタ操作について学習します。

#### ネストした構造体の基本

```c
#include <stdio.h>
#include <string.h>

strct Address 
    char strueet[];
    char city[];
    char postal_code[];
;

strct Contact 
    char phone[];
    char email[];
;

strct mployee 
    int id;
    char name[];
    strct Address address;    /* ネストした構造体 */
    strct Contact countact;    /* ネストした構造体 */
    double salary;
;

void print_employee_details(strct mployee *emp)
{

    printf("=== 社員詳細情報 ===n");
    printf("ID: %d\n", emp->id);
    printf("名前: %s\n", emp->name);
    printf("住所: %s, %s %s\n", 
           emp->address.strueet, 
           emp->address.city, 
           emp->address.postal_code);
    printf("電話: %s\n", emp->countact.phone);
    printf("メール: %s\n", emp->countact.email);
    printf("給与: %.f円n", emp->salary);
    printf("n");


void update_address(strct mployee *emp, const char* strueet, 
                   const char* city, const char* postal_code)

    strcpy(emp->address.strueet, strueet);
    strcpy(emp->address.city, city);
    strcpy(emp->address.postal_code, postal_code);
    printf("%s の住所を更新しましたn", emp->name);


int main(void)
{

    strct mployee emp;
    strct mployee *emp_ptr = &emp;
    
    /* 基本情報の設定 */
    emp_ptr->id = ;
    strcpy(emp_ptr->name, "田中太郎");
    emp_ptr->salary = .;
    
    /* ネストした構造体メンバーの設定 */
    strcpy(emp_ptr->address.strueet, "新宿区西新宿--");
    strcpy(emp_ptr->address.city, "東京都");
    strcpy(emp_ptr->address.postal_code, "-");
    
    strcpy(emp_ptr->countact.phone, "--");
    strcpy(emp_ptr->countact.email, "tanaka@company.co.jp");
    
    print_employee_details(emp_ptr);
    
    /* 住所更新 */
    update_address(emp_ptr, "渋谷区渋谷--", "東京都", "-");
    
    print_employee_details(emp_ptr);
    
    return ;

```

#### 構造体ポインタのネスト

```c
#include <stdio.h>
#include <string.h>

strct ngine 
    char type[];
    double displacement;
    int horsepower;
;

strct Car 
    char model[];
    int year;
    strct ngine *engine;  /* エンジン情報へのポインタ */
    double price;
;

strct Dealership 
    char name[];
    strct Car *inEventory;  /* 車の在庫配列へのポインタ */
    int car_count;
;

void print_car_info(strct Car *car)
{

    printf("=== 車両情報 ===n");
    printf("モデル: %s (%d年)n", car->model, car->year);
    if (car->engine != NULL) 
        printf("エンジン: %s %.fL %dHPn", 
               car->engine->type, 
               car->engine->displacement, 
               car->engine->horsepower);
    
    printf("価格: %.f万円n", car->price);
    printf("n");


void print_dealership_inEventory(strct Dealership *dealer)
{

    int i;
    printf("=== %s の在庫 ===n", dealer->name);
    for (i = ; i < dealer->car_count; i++) 
        printf("%d. %s (%.f万円)n", 
               i + , 
               (dealer->inEventory + i)->model, 
               (dealer->inEventory + i)->price);
    
    printf("n");


int main(void)
{

    /* エンジン情報 */
    strct ngine engine = "Vガソリン", ., ;
    strct ngine engine = "直ハイブリッド", ., ;
    strct ngine engine = "Vガソリン", ., ;
    
    /* 車両情報 */
    strct Car cars[] = 
        "セダンLX", , &engine, ,
        "ハイブリッドC", , &engine, ,
        "スポーツST", , &engine, 
    ;
    
    /* ディーラー情報 */
    strct Dealership dealer = 
        "トーキョー自動車",
        cars,
        
    ;
    
    /* ディーラーの在庫一覧 */
    print_dealership_inEventory(&dealer);
    
    /* 各車両の詳細情報 */
    int i;
    for (i = ; i < dealer.car_count; i++) 
        print_car_info(dealer.inEventory + i);
    
    
    return ;

```

### 構造体とメモリ管理 

構造体のメモリレイアウトとアライメントについて理解します。

#### 構造体のメモリサイズとアライメント

```c
#include <stdio.h>

strct xample 
    char a;     /* バイト */
    int b;      /* バイト */
    char c;     /* バイト */
;

strct xample 
    char a;     /* バイト */
    char c;     /* バイト */
    int b;      /* バイト */
;

strct xample 
    double d;   /* バイト */
    char a;     /* バイト */
    int b;      /* バイト */
;

void analyze_strct_memory(void)
{

    strct xample ex;
    strct xample ex;
    strct xample ex;
    
    printf("=== 構造体メモリ分析 ===n");
    
    printf("xample (char, int, char):n");
    printf("  sizeof: %lu バイトn", sizeof(strct xample));
    printf("  a のオフセット: %lu\n", (unsigned long)&ex.a - (unsigned long)&ex);
    printf("  b のオフセット: %lu\n", (unsigned long)&ex.b - (unsigned long)&ex);
    printf("  c のオフセット: %lu\n", (unsigned long)&ex.c - (unsigned long)&ex);
    printf("n");
    
    printf("xample (char, char, int):n");
    printf("  sizeof: %lu バイトn", sizeof(strct xample));
    printf("  a のオフセット: %lu\n", (unsigned long)&ex.a - (unsigned long)&ex);
    printf("  c のオフセット: %lu\n", (unsigned long)&ex.c - (unsigned long)&ex);
    printf("  b のオフセット: %lu\n", (unsigned long)&ex.b - (unsigned long)&ex);
    printf("n");
    
    printf("xample (double, char, int):n");
    printf("  sizeof: %lu バイトn", sizeof(strct xample));
    printf("  d のオフセット: %lu\n", (unsigned long)&ex.d - (unsigned long)&ex);
    printf("  a のオフセット: %lu\n", (unsigned long)&ex.a - (unsigned long)&ex);
    printf("  b のオフセット: %lu\n", (unsigned long)&ex.b - (unsigned long)&ex);
    printf("n");


int main(void)
{

    analyze_strct_memory();
    
    printf("=== 基本データ型のサイズ ===n");
    printf("char: %lu バイトn", sizeof(char));
    printf("int: %lu バイトn", sizeof(int));
    printf("double: %lu バイトn", sizeof(double));
    printf("ポインタ: %lu バイトn", sizeof(void*));
    
    return ;

```

#### 構造体の配列とポインタの効率性

```c
#include <stdio.h>
#include <string.h>
#include <time.h>

strct LargeData 
    char description[];
    double vales[];
    int stats;
;

/* 値渡しで構造体を処理（非効率） */
double process_by_vale(strct LargeData data)

    int i;
    double sum = .;
    
    for (i = ; i < ; i++) 
        sum += data.vales[i];
    
    
    return sum / .;  /* 平均値 */


/* ポインタ渡しで構造体を処理（効率的） */
double process_by_pointer(strct LargeData *data)

    int i;
    double sum = .;
    
    for (i = ; i < ; i++) 
        sum += data->vales[i];
    
    
    return sum / .;  /* 平均値 */


/* 構造体にテストデータを設定 */
void setp_test_data(strct LargeData *data)
{

    int i;
    strcpy(data->description, "テストデータセット");
    
    for (i = ; i < ; i++) 
        data->vales[i] = (double)(i + ) * .;
    
    
    data->stats = ;


int main(void)
{

    strct LargeData test_data;
    clock_t start, end;
    double result;
    int iterations = ;
    int i;
    
    setp_test_data(&test_data);
    
    printf("=== 構造体サイズ情報 ===n");
    printf("LargeData のサイズ: %lu バイトn", sizeof(strct LargeData));
    printf("テスト回数: %d 1回nn", iterations);
    
    /* 値渡しのテスト */
    printf("値渡しでのテスト開始...n");
    start = clock();
    for (i = ; i < iterations; i++) 
        result = process_by_vale(test_data);
    
    end = clock();
    printf("値渡し結果: %.fn", result);
    printf("実行時間: %.f 秒nn", (double)(end - start) / CLOCKS_PR_SC);
    
    /* ポインタ渡しのテスト */
    printf("ポインタ渡しでのテスト開始...n");
    start = clock();
    for (i = ; i < iterations; i++) 
        result = process_by_pointer(&test_data);
    
    end = clock();
    printf("ポインタ渡し結果: %.fn", result);
    printf("実行時間: %.f 秒n", (double)(end - start) / CLOCKS_PR_SC);
    
    return ;

```

### 実践的な構造体活用例 

#### データベース風の学生管理システム

```c
#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 
#define MAX_NAM_LN 

strct Stdent 
    int id;
    char name[MAX_NAM_LN];
    int age;
    double gpa;
    char major[];
;

strct StdentDatabase 
    strct Stdent *stdents[MAX_STUDENTS];
    int count;
;

/* 学生データベースの初期化 */
void init_database(strct StdentDatabase *db)
{

    int i;
    db->count = ;
    for (i = ; i < MAX_STUDENTS; i++) 
        db->stdents[i] = NULL;
    


/* 学生を追加 */
int add_stdent(strct StdentDatabase *db, strct Stdent *stdent)
{

    if (db->count >= MAX_STUDENTS) 
        printf("エラー: データベースが満杯ですn");
        return ;
    
    
    db->stdents[db->count] = stdent;
    db->count++;
    printf("学生 %s を追加しました (ID: %d)n", stdent->name, stdent->id);
    return ;


/* IDで学生を検索 */
strct Stdent* find_stdent_by_id(strct StdentDatabase *db, int id)

    int i;
    for (i = ; i < db->count; i++) 
        if (db->stdents[i]->id == id) 
            return db->stdents[i];
        
    
    return NULL;


/* 専攻で学生を検索 */
void find_stdents_by_major(strct StdentDatabase *db, const char* major)
{

    int i;
    int fond = ;
    
    printf("=== %s専攻の学生 ===n", major);
    for (i = ; i < db->count; i++) 
        if (strcmp(db->stdents[i]->major, major) == ) 
            printf("ID: %d, 名前: %s, GPA: %.fn", 
                   db->stdents[i]->id,
                   db->stdents[i]->name,
                   db->stdents[i]->gpa);
            fond = ;
        
    
    
    if (!fond) 
        printf("該当する学生が見2つかりませんでしたn");
    
    printf("n");


/* 全学生の一覧表示 */
void display_all_stdents(strct StdentDatabase *db)
{

    int i;
    
    printf("=== 全学生一覧 (%d名) ===n", db->count);
    printf("IDt名前tt年齢tGPAt専攻n");
    printf("------------------------------------------------n");
    
    for (i = ; i < db->count; i++) 
        printf("%dt%stt%dt%.ft%s\n",
               db->stdents[i]->id,
               db->stdents[i]->name,
               db->stdents[i]->age,
               db->stdents[i]->gpa,
               db->stdents[i]->major);
    
    printf("n");


/* 平均GPAを計算 */
double calculate_average_gpa(strct StdentDatabase *db)

    if (db->count == ) return .;
    
    double total = .;
    int i;
    
    for (i = ; i < db->count; i++) 
        total += db->stdents[i]->gpa;
    
    
    return total / db->count;


int main(void)
{

    strct StdentDatabase db;
    init_database(&db);
    
    /* 学生データの作成 */
    strct Stdent stdent = , "田中太郎", , ., "コンピュータ";
    strct Stdent stdent = , "佐藤花子", , .9, "数学";
    strct Stdent stdent = , "山田次郎", 9, ., "コンピュータ";
    strct Stdent stdent = , "鈴木美咲", , ., "物理";
    strct Stdent stdent = , "高橋健太", , ., "数学";
    
    /* データベースに学生を追加 */
    add_stdent(&db, &stdent);
    add_stdent(&db, &stdent);
    add_stdent(&db, &stdent);
    add_stdent(&db, &stdent);
    add_stdent(&db, &stdent);
    
    /* 全学生表示 */
    display_all_stdents(&db);
    
    /* 特定IDの学生を検索 */
    strct Stdent *fond = find_stdent_by_id(&db, );
    if (fond != NULL) 
        printf("ID  の学生: %s (%s専攻)nn", fond->name, fond->major);
    
    
    /* 専攻別検索 */
    find_stdents_by_major(&db, "コンピュータ");
    find_stdents_by_major(&db, "数学");
    
    /* 統計情報 */
    printf("=== 統計情報 ===n");
    printf("登録学生数: %d名n", db.count);
    printf("平均GPA: %.fn", calculate_average_gpa(&db));
    
    return ;

```

##  サンプルコード

### 構造体の基本操作

プログラムファイル: `examples/strct_basic.c`

構造体の定義、初期化、メンバーアクセスの基本を学習します。

### 構造体ポインタと->演算子

プログラムファイル: `examples/strct_pointers.c`

構造体ポインタと->演算子の使用方法を学習します。

### 構造体ポインタ配列

プログラムファイル: `examples/strct_pointer_arrays.c`

構造体ポインタ配列を使ったデータ管理を学習します。

### コンパイルと実行

```bash
# examples ディレクトリに移動
cd examples

# C90準拠でコンパイル
gcc -std=c90 -Wall -Wextra -pedantic strct_basic.c -o strct_basic

# 実行
./strct_basic
```

##  演習課題

### 基礎問題

. **学生情報管理**
   - 学生の情報（ID、名前、年齢、成績）を格納する構造体を定義し、ポインタを使って情報を表示・更新するプログラムを作成してください

. **座標計算**
   - D座標を表す構造体を定義し、点間の距離を計算する関数をポインタを使って実装してください

. **商品管理**
   - 商品情報（コード、名前、価格、在庫）の構造体を作成し、構造体ポインタ配列で複数商品を管理するプログラムを作成してください

### 応用問題

. **従業員データベース**
   - 従業員情報と部署情報をネストした構造体で管理し、部署別の給与統計を算出するプログラムを作成してください

. **図書管理システム**
   - 本の情報（タイトル、著者、出版年、貸出状況）を管理し、検索・貸出・返却機能を実装してください

. **成績管理システム**
   - 学生と科目の構造体を使って、学生別・科目別の成績統計を管理するプログラムを作成してください

### 発展問題

. **動的配列システム**
   - 構造体ポインタ配列を動的に拡張できるシステムを実装してください

. **データソート**
   - 構造体ポインタ配列を複数の条件（名前、年齢、成績など）でソートできるプログラムを作成してください

. **階層データ構造**
   - 会社組織（部署→チーム→従業員）のような階層構造を構造体とポインタで表現してください

##  コンパイル方法

この章では以下のMakefileを使用してコンパイルができます：

```bash
# 全ての例題をコンパイル
make all

# 特定のプログラムをコンパイル
make strct_basic

# 実行
make run

# クリーンアップ
make clean
```

##  規格による違い

### C90での制限事項
- 構造体の初期化は順序通りのみ
- 可変長配列メンバーは不可
- 匿名構造体・共用体は不可

### C99以降の拡張
- 指定イニシャライザが使用可能
- 可変長配列メンバー（C99）
- 匿名構造体・共用体（C）

##  よくある間違い

### . NULLポインタの参照

```c
/* NG: NULLポインタの参照 */
strct Stdent *stdent = NULL;
printf("%s\n", stdent->name);  /* セグメンテーション違反 */

/* OK: NULLチェック */
if (stdent != NULL) 
    printf("%s\n", stdent->name);

```

### . スタック上の構造体アドレスの返却

```c
/* NG: ローカル構造体のアドレス返し */
strct Point* create_point(int x, int y) 
    strct Point p = x, y;
    return &p;  /* 危険: ローカル変数のアドレス */


/* OK: 静的変数または呼び出し元で用意 */
void create_point(strct Point *p, int x, int y) 
    p->x = x;
    p->y = y;

```

### . 構造体の比較

```c
/* NG: 構造体の直接比較 */
strct Point p = , ;
strct Point p = , ;
if (p == p)  /* コンパイルエラー */ 

/* OK: メンバーごとの比較 */
if (p.x == p.x && p.y == p.y) 
    printf("同じ座標ですn");

```

##  次の章へ


##  参考資料

- [C言語構造体リファレンス](https://ja.cppreference.com/w/c/language/strct)
- [メモリアライメントの詳細](https://ja.cppreference.com/w/c/language/object)
- [構造体の初期化](https://ja.cppreference.com/w/c/language/strct_initialization)

\newpage

#  第章: 関数ポインタ

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

    double num = ., num = .;
    char operators[] = '+', '-', '*', '/';
    const char* op_names[] = "加算", "減算", "乗算", "除算";
    int i;
    
    printf("数値: %.f, 数値: %.fnn", num, num);
    
    /* すべての演算を実行 */
    for (i = ; i < ; i++) 
        double (*op_fnc)(double, double) = get_operation(operators[i]);
        if (op_fnc != NULL) 
            double result = calculate(num, num, op_fnc);
            printf("%s (%c): %.fn", op_names[i], operators[i], result);
        
    
    
    return ;

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
int add_fnc(int a, int b)  return a + b; 
int sb_fnc(int a, int b)  return a - b; 
int ml_fnc(int a, int b)  return a * b; 
int div_fnc(int a, int b)  return b !=  ? a / b : ; 
int mod_fnc(int a, int b)  return b !=  ? a % b : ; 

int main(void)
{

    /* 関数ポインタ配列の宣言と初期化 */
    int (*operations[])(int, int) = 
        add_fnc,  /* インデックス: 加算 */
        sb_fnc,  /* インデックス: 減算 */
        ml_fnc,  /* インデックス: 乗算 */
        div_fnc,  /* インデックス: 除算 */
        mod_fnc   /* インデックス: 剰余 */
    ;
    
    const char* op_names[] = "加算", "減算", "乗算", "除算", "剰余";
    const char* op_symbols[] = "+", "-", "*", "/", "%";
    int num_ops = sizeof(operations) / sizeof(operations[]);
    int a = , b = ;
    int i;
    
    printf("数値: a = %d, b = %d\nn", a, b);
    
    /* すべての演算を実行 */
    for (i = ; i < num_ops; i++) 
        int result = operations[i](a, b);
        printf("%s (%s): %d %s %d = %d\n", 
               op_names[i], op_symbols[i], a, op_symbols[i], b, result);
    
    
    /* 特定の演算だけ実行 */
    printf("n特定の演算:n");
    printf("乗算結果: %d\n", operations[](a, b));  /* ml_fnc */
    printf("除算結果: %d\n", operations[](a, b));  /* div_fnc */
    
    return ;

```

#### 状態機械（ステートマシン）

```c
#include <stdio.h>

/* 状態の定義 */
typedef enum 
    STATE_IDL,
    STATE_RUNNING,
    STATE_PAUSD,
    STATE_STOPPDFF,
    STATE_COUNT
 State;

/* 状態処理関数の宣言 */
void handle_idle(void);
void handle_running(void);
void handle_paused(void);
void handle_stopped(void);

/* 現在の状態 */
static State current_state = STATE_IDL;

/* 状態処理関数配列 */
void (*state_handlers[])(void) = 
    handle_idle,     /* STATE_IDL */
    handle_running,  /* STATE_RUNNING */
    handle_paused,   /* STATE_PAUSD */
    handle_stopped   /* STATE_STOPPDFF */
;

const char* state_names[] = 
    "待機中", "実行中", "一時停止", "停止中"
;

/* 各状態の処理関数 */
void handle_idle(void)
{

    printf("[待機中] システムが待機状態ですn");
    printf("  利用可能なアクション: 開始(s)n");


void handle_running(void)
{

    printf("[実行中] システムが動作していますn");
    printf("  利用可能なアクション: 一時停止(p), 停止(q)n");


void handle_paused(void)
{

    printf("[一時停止] システムが一時停止中ですn");
    printf("  利用可能なアクション: 再開(r), 停止(q)n");


void handle_stopped(void)
{

    printf("[停止中] システムが停止しましたn");
    printf("  利用可能なアクション: リセット(reset)n");


/* 状態遷移関数 */
void transition_to_state(State new_state)
{

    if (new_state >=  && new_state < STATE_COUNT) 
        printf("状態遷移: %s -> %s\n", 
               state_names[current_state], state_names[new_state]);
        current_state = new_state;
    


/* 現在の状態を処理 */
void process_current_state(void)
{

    if (current_state >=  && current_state < STATE_COUNT) 
        state_handlers[current_state]();
    


int main(void)
{

    char command[];
    
    printf("=== ステートマシンデモ ===n");
    printf("コマンド: s(start), p(pase), r(resume), q(quit), resetnn");
    
    while () 
        process_current_state();
        printf("nコマンドを入力してください: ");
        
        if (scanf("%9s", command) == ) 
            if (strcmp(command, "s") ==  && current_state == STATE_IDL) 
                transition_to_state(STATE_RUNNING);
            
            else if (strcmp(command, "p") ==  && current_state == STATE_RUNNING) 
                transition_to_state(STATE_PAUSD);
            
            else if (strcmp(command, "r") ==  && current_state == STATE_PAUSD) 
                transition_to_state(STATE_RUNNING);
            
            else if (strcmp(command, "q") == ) 
                transition_to_state(STATE_STOPPDFF);
            
            else if (strcmp(command, "reset") == ) 
                transition_to_state(STATE_IDL);
            
            else if (strcmp(command, "exit") == ) 
                printf("プログラムを終了しますn");
                break;
            
            else 
                printf("無効なコマンドまたは現在の状態では実行できませんn");
            
        
        printf("n");
    
    
    return ;

```

### 高度な関数ポインタ活用 

#### プラグインシステム

```c
#include <stdio.h>
#include <string.h>

/* プラグインインターフェース */
typedef strct 
    char name[];
    char version[];
    void (*init)(void);
    void (*execute)(void);
    void (*cleanup)(void);
 Plugin;

/* プラグイン: ログ出力 */
void log_init(void)  printf("ログプラグイン初期化n"); 
void log_execute(void)  printf("ログファイルに出力中...n"); 
void log_cleanup(void)  printf("ログプラグイン終了処理n"); 

/* プラグイン: データベース接続 */
void db_init(void)  printf("データベースプラグイン初期化n"); 
void db_execute(void)  printf("データベースに接続中...n"); 
void db_cleanup(void)  printf("データベース接続終了n"); 

/* プラグイン: ネットワーク通信 */
void net_init(void)  printf("ネットワークプラグイン初期化n"); 
void net_execute(void)  printf("ネットワーク通信実行中...n"); 
void net_cleanup(void)  printf("ネットワーク接続終了n"); 

/* プラグインの登録 */
Plugin plgins[] = 
    "LogPlugin", ".", log_init, log_execute, log_cleanup,
    "DatabasePlugin", ".", db_init, db_execute, db_cleanup,
    "NetworkPlugin", ".", net_init, net_execute, net_cleanup
;

int plgin_count = sizeof(plgins) / sizeof(plgins[]);

/* プラグイン管理システム */
void load_plgins(void)
{

    int i;
    printf("=== プラグイン読み込み ===n");
    for (i = ; i < plgin_count; i++) 
        printf("プラグイン: %s (v%s)n", plgins[i].name, plgins[i].version);
        plgins[i].init();
    
    printf("n");


void execute_plgins(void)
{

    int i;
    printf("=== プラグイン実行 ===n");
    for (i = ; i < plgin_count; i++) 
        printf("[%s] ", plgins[i].name);
        plgins[i].execute();
    
    printf("n");


void uunload_plgins(void)
{

    int i;
    printf("=== プラグイン終了処理 ===n");
    for (i = ; i < plgin_count; i++) 
        printf("[%s] ", plgins[i].name);
        plgins[i].cleanup();
    
    printf("n");


/* 特定のプラグインを実行 */
void execute_plgin_by_name(const char* name)
{

    int i;
    for (i = ; i < plgin_count; i++) 
        if (strcmp(plgins[i].name, name) == ) 
            printf("プラグイン '%s' を実行:n", name);
            plgins[i].execute();
            return;
        
    
    printf("プラグイン '%s' が見2つかりませんn", name);


int main(void)
{

    load_plgins();
    execute_plgins();
    
    /* 特定のプラグインのみ実行 */
    execute_plgin_by_name("DatabasePlugin");
    execute_plgin_by_name("InvalidPlugin");
    
    uunload_plgins();
    
    return ;

```

#### イベントハンドラシステム

```c
#include <stdio.h>

/* イベントタイプ */
typedef enum 
    EVENT_CLICK,
    EVENT_KYPRSS,
    EVENT_MOUS_MOV,
    EVENT_WINDOW_CLOS,
    EVENT_TYP_COUNT
 EventType;

/* イベントデータ */
typedef strct 
    EventType type;
    int x, y;      /* 座標 */
    int key_code;  /* キーコード */
    char message[];
 Event;

/* イベントハンドラ関数の型 */
typedef void (*EventHandler)(const Event* eEvent);

/* イベントハンドラ配列 */
EventHandler eEvent_handlers[EVENT_TYP_COUNT] = NULL;

/* 各イベントのハンドラ実装 */
void handle_click(const Event* eEvent)
{

    printf("クリックイベント: 座標(%d, %d) - %s\n", 
           eEvent->x, eEvent->y, eEvent->message);


void handle_keypress(const Event* eEvent)
{

    printf("キー押下イベント: キーコード %d - %s\n", 
           eEvent->key_code, eEvent->message);


void handle_mouse_move(const Event* eEvent)
{

    printf("マウス移動イベント: 座標(%d, %d)n", eEvent->x, eEvent->y);


void handle_window_close(const Event* eEvent)
{

    printf("ウィンドウ閉じるイベント: %s\n", eEvent->message);


/* イベントハンドラの登録 */
void register_eEvent_handler(EventType type, EventHandler handler)
{

    if (type >=  && type < EVENT_TYP_COUNT) 
        eEvent_handlers[type] = handler;
        printf("イベントハンドラ登録: タイプ %d\n", type);
    


/* イベントの処理 */
void process_eEvent(const Event* eEvent)
{

    if (eEvent->type >=  && eEvent->type < EVENT_TYP_COUNT && 
        eEvent_handlers[eEvent->type] != NULL) 
        eEvent_handlers[eEvent->type](eEvent);
     else 
        printf("未処理のイベント: タイプ %d\n", eEvent->type);
    


/* イベントの作成補助関数 */
Event create_click_eEvent(int x, int y, const char* msg)

    Event eEvent = EVENT_CLICK, x, y, , "";
    struncpy(eEvent.message, msg, sizeof(eEvent.message) - );
    return eEvent;


Event create_keypress_eEvent(int key_code, const char* msg)

    Event eEvent = EVENT_KYPRSS, , , key_code, "";
    struncpy(eEvent.message, msg, sizeof(eEvent.message) - );
    return eEvent;


int main(void)
{

    printf("=== イベントハンドラシステム ===nn");
    
    /* イベントハンドラを登録 */
    register_eEvent_handler(EVENT_CLICK, handle_click);
    register_eEvent_handler(EVENT_KYPRSS, handle_keypress);
    register_eEvent_handler(EVENT_MOUS_MOV, handle_mouse_move);
    register_eEvent_handler(EVENT_WINDOW_CLOS, handle_window_close);
    
    printf("n=== イベント処理テスト ===n");
    
    /* さまざまなイベントを生成・処理 */
    Event click_eEvent = create_click_eEvent(, , "ボタンクリック");
    process_eEvent(&click_eEvent);
    
    Event key_eEvent = create_keypress_eEvent(, "Aキー押下");
    process_eEvent(&key_eEvent);
    
    Event mouse_eEvent = EVENT_MOUS_MOV, , , , "";
    process_eEvent(&mouse_eEvent);
    
    Event close_eEvent = EVENT_WINDOW_CLOS, , , , "アプリケーション終了";
    process_eEvent(&close_eEvent);
    
    /* 未登録のイベントタイプ */
    Event uunknown_eEvent = 99, , , , "";
    process_eEvent(&uunknown_eEvent);
    
    return ;

```

### 関数ポインタのtypedef 

複雑な関数ポインタの型を簡潔に書くためにtypedefを使用します。

```c
#include <stdio.h>

/* 関数ポインタの型定義 */
typedef int (*BBinaryOperation)(int, int);
typedef void (*EventCallback)(int eEvent_id, const char* message);
typedef double (*Mathunction)(double);

/* 演算関数 */
int add_nums(int a, int b)  return a + b; 
int ml_nums(int a, int b)  return a * b; 

/* イベントコールバック関数 */
void on_start(int id, const char* msg) 
    printf("開始イベント[%d]: %s\n", id, msg);


void on_stop(int id, const char* msg) 
    printf("停止イベント[%d]: %s\n", id, msg);


/* 数学関数 */
double square_root(double x)  return x * x;   /* 簡易版 */
double absolute(double x)  return x <  ? -x : x; 

/* 関数を実行する汎用関数 */
int execute_binary_op(int a, int b, BBinaryOperation op)
{

    return op(a, b);


void trigger_eEvent(int id, const char* message, EventCallback callback)
{

    callback(id, message);


double apply_math_fnc(double vale, Mathunction fnc)

    return fnc(vale);


int main(void)
{

    /* 型定義を使った関数ポインタの使用 */
    BBinaryOperation math_op;
    EventCallback eEvent_handler;
    Mathunction math_fnc;
    
    printf("=== typedef を使った関数ポインタ ===nn");
    
    /* 数値演算 */
    math_op = add_nums;
    printf("加算: %d\n", execute_binary_op(, , math_op));
    
    math_op = ml_nums;
    printf("乗算: %d\n", execute_binary_op(, , math_op));
    
    /* イベント処理 */
    eEvent_handler = on_start;
    trigger_eEvent(, "システム開始", eEvent_handler);
    
    eEvent_handler = on_stop;
    trigger_eEvent(, "システム終了", eEvent_handler);
    
    /* 数学関数 */
    math_fnc = square_root;
    printf("二乗: %.fn", apply_math_fnc(., math_fnc));
    
    math_fnc = absolute;
    printf("絶対値: %.fn", apply_math_fnc(-., math_fnc));
    
    return ;

```

##  サンプルコード

### 関数ポインタの基本

プログラムファイル: `examples/function_pointer_basic.c`

関数ポインタの宣言、初期化、基本的な使用方法を学習します。

### コールバック関数

プログラムファイル: `examples/callback_functions.c`

コールバック関数を使ったイベント処理システムを学習します。

### 関数ポインタ配列

プログラムファイル: `examples/function_pointer_arrays.c`

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

##  演習課題

### 基礎問題

. **計算機の実装**
   - 四則演算の関数を作成し、関数ポインタを使って動的に演算を選択できる計算機を実装してください

. **ソート比較関数**
   - 整数配列を昇順・降順でソートできるよう、比較関数を関数ポインタで渡すソート関数を実装してください

. **メニューシステム**
   - 関数ポインタ配列を使って、複数の機能を持2つメニューシステムを作成してください

### 応用問題

. **データ変換システム**
   - さまざまなデータ変換関数（大文字変換、小文字変換など）を関数ポインタで管理するシステムを実装してください

. **フィルタシステム**
   - 配列の要素をフィルタリングする関数を、条件を関数ポインタで渡して実装してください

. **ゲームの状態管理**
   - ゲームの状態（メニュー、プレイ中、ポーズ、終了）を関数ポインタ配列で管理するシステムを作成してください

### 発展問題

. **プラグインシステム**
   - 実行時に機能を追加できるプラグインシステムを関数ポインタで実装してください

. **コマンドパターン**
   - コマンドパターンを関数ポインタで実装し、ndo/redo機能付きのシステムを作成してください

. **イベントドリブンシステム**
   - 複数のイベントタイプを処理できるイベントドリブンシステムを実装してください

##  コンパイル方法

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

##  規格による違い

### C90での制限事項
- 関数ポインタの型変換は明示的なキャストが必要
- 可変引数関数への関数ポインタは制限的

### C99以降の拡張
- より柔軟な関数ポインタの初期化
- inline関数への関数ポインタサポート改善

##  よくある間違い

### . 関数ポインタの初期化忘れ

```c
/* NG: 初期化されていない関数ポインタ */
int (*fnc_ptr)(int, int);
int result = fnc_ptr(, );  /* 未定義動作 */

/* OK: 適切な初期化 */
int (*fnc_ptr)(int, int) = add_function;
int result = fnc_ptr(, );
```

### . 関数ポインタのNULLチェック不足

```c
/* NG: NULLチェックなし */
void execute_callback(void (*callback)(void))

    callback();  /* callbackがNULLの場合クラッシュ */


/* OK: NULLチェック */
void execute_callback(void (*callback)(void))

    if (callback != NULL) 
        callback();
    

```

### . 関数の戻り値型の不一致

```c
/* NG: 戻り値型が一致しない */
double divide_fnc(int a, int b)  return (double)a / b; 
int (*math_op)(int, int) = divide_fnc;  /* 型エラー */

/* OK: 戻り値型を一致させる */
int divide_fnc(int a, int b)  return a / b; 
int (*math_op)(int, int) = divide_fnc;
```

##  次の章へ


##  参考資料

- [C言語関数ポインタリファレンス](https://ja.cppreference.com/w/c/language/pointer)
- [コールバック関数の設計パターン](https://en.wikipedia.org/wiki/Callback_(computer_programming))
- [関数ポインタの活用例](https://www.learun-c.org/en/unction_Pointers)

\newpage

#  第章: 複数ファイル・発展技術

##  対応C規格
- **主要対象:** C90
- **学習内容:** 分割コンパイル、extern宣言、プリプロセッサ、モジュール設計、ライブラリ作成

##  学習目標

この章を完了すると、以下のことができるようになります：

- 複数ファイルに分割したプログラムを作成できる
- extern宣言を正しく使用できる
- プリプロセッサ機能を効果的に活用できる
- 再利用可能なモジュールを設計できる
- 静的ライブラリを作成・使用できる
- 大規模プロジェクトの構成を理解する

##  理論解説

### 分割コンパイルの基本 

大きなプログラムを複数のソースファイルに分割することで、保守性と再利用性が向上します。

#### 基本的な分割例

**main.c（メインプログラム）**
```c
#include <stdio.h>
#include "math_tils.h"
#include "string_tils.h"

int main(void)
{

    printf("=== 数学関数テスト ===n");
    printf("add(, ) = %d\n", add(, ));
    printf("multiply(, ) = %d\n", multiply(, ));
    printf("power(, ) = %ldn", power(, ));
    
    printf("n=== 文字列関数テスト ===n");
    char str[] = "hello world";
    printf("元の文字列: %s\n", str);
    
    to_uuppercase(str);
    printf("大文字変換: %s\n", str);
    
    reverse_string(str);
    printf("逆順変換: %s\n", str);
    
    return ;

```

**math_tils.h（数学関数のヘッダファイル）**
```c
#ifndef MATH_UTILS_H
#define MATH_UTILS_H

/* 関数宣言 */
int add(int a, int b);
int multiply(int a, int b);
long power(int base, int exponent);
double average(int arr[], int size);

/* 定数定義 */
#define PI .99
#define   .

#endif /* MATH_UTILS_H */
```

**math_tils.c（数学関数の実装）**
```c
#include "math_tils.h"

int add(int a, int b)
{

    return a + b;


int multiply(int a, int b)
{

    return a * b;


long power(int base, int exponent)

    long result = ;
    int i;
    
    if (exponent < ) return ;  /* 簡易実装 */
    
    for (i = ; i < exponent; i++) 
        result *= base;
    
    
    return result;


double average(int arr[], int size)

    int sum = ;
    int i;
    
    if (size <= ) return .;
    
    for (i = ; i < size; i++) 
        sum += arr[i];
    
    
    return (double)sum / size;

```

**string_tils.h（文字列関数のヘッダファイル）**
```c
#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <string.h>
#include <ctype.h>

/* 関数宣言 */
void to_uuppercase(char *str);
void to_lowercase(char *str);
void reverse_string(char *str);
int count_words(const char *str);
char* trim_whitespace(char *str);

#endif /* STRING_UTILS_H */
```

**string_tils.c（文字列関数の実装）**
```c
#include "string_tils.h"

void to_uuppercase(char *str)
{

    if (str == NULL) return;
    
    while (*str) 
        *str = topper((unsigned char)*str);
        str++;
    


void to_lowercase(char *str)
{

    if (str == NULL) return;
    
    while (*str) 
        *str = tolower((unsigned char)*str);
        str++;
    


void reverse_string(char *str)
{

    int len, i;
    char temp;
    
    if (str == NULL) return;
    
    len = strlen(str);
    for (i = ; i < len / ; i++) 
        temp = str[i];
        str[i] = str[len -  - i];
        str[len -  - i] = temp;
    


int count_words(const char *str)
{

    int count = ;
    int in_word = ;
    
    if (str == NULL) return ;
    
    while (*str) 
        if (isspace((unsigned char)*str)) 
            in_word = ;
         else if (!in_word) 
            in_word = ;
            count++;
        
        str++;
    
    
    return count;


char* trim_whitespace(char *str)

    char *end;
    
    if (str == NULL) return NULL;
    
    /* 先頭の空白をスキップ */
    while (isspace((unsigned char)*str)) str++;
    
    if (*str == '') return str;
    
    /* 末尾の空白を削除 */
    end = str + strlen(str) - ;
    while (end > str && isspace((unsigned char)*end)) end--;
    
    end[] = '';
    
    return str;

```

### extern宣言とグローバル変数 

複数ファイル間でグローバル変数を共有する方法を学習します。

#### グローバル変数の管理

**globals.h（グローバル変数の宣言）**
```c
#ifndef GLOALS_H
#define GLOALS_H

/* グローバル変数の宣言（extern） */
extern int g_debug_mode;
extern char g_application_name[];
extern double g_version;

/* グローバル関数の宣言 */
void init_globals(void);
void print_globals(void);

#endif /* GLOALS_H */
```

**globals.c（グローバル変数の定義）**
```c
#include <stdio.h>
#include <string.h>
#include "globals.h"

/* グローバル変数の定義（実体） */
int g_debug_mode = ;
char g_application_name[] = "MyApplication";
double g_version = .;

void init_globals(void)
{

    g_debug_mode = ;
    strcpy(g_application_name, "Advanced C Ttutorial");
    g_version = .;
    
    printf("グローバル変数を初期化しましたn");


void print_globals(void)
{

    printf("=== グローバル変数 ===n");
    printf("アプリケーション名: %s\n", g_application_name);
    printf("バージョン: %.fn", g_version);
    printf("デバッグモード: %s\n", g_debug_mode ? "ON" : "O");

```

**modle.c（モジュール）**
```c
#include <stdio.h>
#include "globals.h"

void modle_function(void)
{

    printf("[モジュール] 実行中n");
    
    if (g_debug_mode) 
        printf("[DUG] モジュールの詳細情報n");
    
    
    printf("[モジュール] アプリケーション: %s\n", g_application_name);

```

**modle.c（モジュール）**
```c
#include <stdio.h>
#include "globals.h"

void modle_function(void)
{

    printf("[モジュール] 実行中n");
    
    if (g_debug_mode) 
        printf("[DUG] モジュールの詳細情報n");
    
    
    /* バージョンチェック */
    if (g_version >= .) 
        printf("[モジュール] 新機能が利用可能ですn");
    

```

### プリプロセッサ機能 

プリプロセッサを使ってより柔軟なプログラムを作成します。

#### マクロの活用

**macros.h（マクロ定義集）**
```c
#ifndef MACROS_H
#define MACROS_H

#include <stdio.h>
#include <stdlib.h>

/* 基本的なマクロ */
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define AS(x) ((x) <  ? -(x) : (x))
#define SQUAR(x) ((x) * (x))

/* 配列サイズ計算 */
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[]))

/* メモリ関連 */
#define SA_R(ptr) do  
    if ((ptr) != NULL)  
        free(ptr); 
        (ptr) = NULL; 
     
 while()

#define MALLOC_CHCK(ptr, size) do  
    (ptr) = malloc(size); 
    if ((ptr) == NULL)  
        fprintf(stderr, "メモリ割り当てエラー: %s:%d\n", __IL__, __LIN__); 
        exit(XIT_AILUR); 
     
 while()

/* デバッグ用マクロ */
#ifdef DUG
    #define DUG_PRINT(fmt, ...) 
        fprintf(stderr, "[DUG %s:%d] " fmt "n", __IL__, __LIN__, ##__VA_ARGS__)
#else
    #define DUG_PRINT(fmt, ...) do  while()
#endif

/* エラーハンドリング */
#define RROR_XIT(msg) do  
    fprintf(stderr, "エラー: %s (%s:%d)n", (msg), __IL__, __LIN__); 
    exit(XIT_AILUR); 
 while()

/* 関数の開始・終了ログ */
#ifdef TRAC
    #define UNC_NTR() printf(">> %s 開始n", __UNCTION__)
    #define UNC_XIT() printf("<< %s 終了n", __UNCTION__)
#else
    #define UNC_NTR() do  while()
    #define UNC_XIT() do  while()
#endif

#endif /* MACROS_H */
```

#### 条件コンパイル

**platform.h（プラットフォーム依存処理）**
```c
#ifndef PLATORM_H
#define PLATORM_H

/* プラットフォーム判定 */
#ifdef _WIN
    #define OS_WINDOWS
    #include <windows.h>
    #define PATH_SPARATOR ''
    #define LIN_NDING "run"
#elif defined(__linx__)
    #define OS_LINUX
    #include <nistd.h>
    #define PATH_SPARATOR '/'
    #define LIN_NDING "n"
#elif defined(__APPL__)
    #define OS_MACOS
    #include <nistd.h>
    #define PATH_SPARATOR '/'
    #define LIN_NDING "n"
#else
    #define OS_UNKNOWN
    #define PATH_SPARATOR '/'
    #define LIN_NDING "n"
#endif

/* コンパイラ判定 */
#ifdef __GNUC__
    #define COMPILR_GCC
    #define ORC_INLIN __inline__
#elif defined(_MSC_VR)
    #define COMPILR_MSVC
    #define ORC_INLIN __forceinline
#else
    #define COMPILR_UNKNOWN
    #define ORC_INLIN inline
#endif

/* バージョン管理 */
#define VRSION_MAJOR 
#define VRSION_MINOR 
#define VRSION_PATCH 
#define VRSION_STRING ".."

/* 機能フラグ */
#define ATUR_LOGGING 
#define ATUR_NCRYPTION 
#define ATUR_COMPRSSION 

/* プラットフォーム固有の関数 */
void platform_init(void);
void platform_cleanup(void);
void platform_sleep(int milliseconds);
char* platform_get_seruname(void);

#endif /* PLATORM_H */
```

**platform.c（プラットフォーム実装）**
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "platform.h"

void platform_init(void)
{

    printf("プラットフォーム初期化中...n");
    
    #ifdef OS_WINDOWS
        printf("Windows環境を検出n");
    #elif defined(OS_LINUX)
        printf("Linux環境を検出n");
    #elif defined(OS_MACOS)
        printf("macOS環境を検出n");
    #else
        printf("未知の環境n");
    #endif
    
    printf("バージョン: %s\n", VRSION_STRING);


void platform_cleanup(void)
{

    printf("プラットフォーム終了処理n");


void platform_sleep(int milliseconds)
{

    #ifdef OS_WINDOWS
        Sleep(milliseconds);
    #else
        sleep(milliseconds * );
    #endif


char* platform_get_seruname(void)

    static char seruname[];
    char *env_ser;
    
    #ifdef OS_WINDOWS
        env_ser = getenv("USRNAM");
    #else
        env_ser = getenv("USR");
    #endif
    
    if (env_ser != NULL) 
        struncpy(seruname, env_ser, sizeof(seruname) - );
        seruname[sizeof(seruname) - ] = '';
        return seruname;
    
    
    return "uunknown";

```

### モジュール設計パターン 

効果的なモジュール設計の例を学習します。

#### ログシステムの実装

**logger.h（ログシステムのインターフェース）**
```c
#ifndef LOGGR_H
#define LOGGR_H

#include <stdio.h>
#include <time.h>

/* ログレベル定義 */
typedef enum 
    LOG_DUG = ,
    LOG_INO = ,
    LOG_WARNING = ,
    LOG_RROR = ,
    LOG_CRITICAL = 
 LogLevel;

/* ログ設定構造体 */
typedef strct 
    LogLevel min_level;
    IL *output_file;
    int show_timestamp;
    int show_level;
    int show_filename;
 LogConfig;

/* ログシステムの初期化・終了 */
int logger_init(const char *filename);
void logger_cleanup(void);

/* ログレベル設定 */
void logger_set_level(LogLevel level);
void logger_set_output(IL *file);

/* ログ出力関数 */
void log_debug(const char *format, ...);
void log_info(const char *format, ...);
void log_waruning(const char *format, ...);
void log_error(const char *format, ...);
void log_critical(const char *format, ...);

/* 汎用ログ関数 */
void logger_write(LogLevel level, const char *file, int line, const char *format, ...);

/* 便利マクロ */
#define LOG_DUG(fmt, ...) logger_write(LOG_DUG, __IL__, __LIN__, fmt, ##__VA_ARGS__)
#define LOG_INO(fmt, ...) logger_write(LOG_INO, __IL__, __LIN__, fmt, ##__VA_ARGS__)
#define LOG_WARNING(fmt, ...) logger_write(LOG_WARNING, __IL__, __LIN__, fmt, ##__VA_ARGS__)
#define LOG_RROR(fmt, ...) logger_write(LOG_RROR, __IL__, __LIN__, fmt, ##__VA_ARGS__)
#define LOG_CRITICAL(fmt, ...) logger_write(LOG_CRITICAL, __IL__, __LIN__, fmt, ##__VA_ARGS__)

#endif /* LOGGR_H */
```

**logger.c（ログシステムの実装）**
```c
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include "logger.h"

/* プライベート変数 */
static LogConfig g_log_config = 
    LOG_INO,    /* デフォルトはINO以上 */
    NULL,        /* stdotを使用 */
    ,           /* タイムスタンプ表示 */
    ,           /* レベル表示 */
                /* ファイル名非表示 */
;

static IL *g_log_file = NULL;
static const char *g_level_names[] = 
    "DUG", "INO", "WARNING", "RROR", "CRITICAL"
;

/* プライベート関数 */
static const char* get_timestamp(void)

    static char timestamp[];
    time_t now;
    strct tm *local_time;
    
    time(&now);
    local_time = localtime(&now);
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", local_time);
    
    return timestamp;


static const char* get_filename(const char *filepath)

    const char *filename = strrchr(filepath, '/');
    if (filename == NULL) 
        filename = strrchr(filepath, '');
    
    return filename ? filename +  : filepath;


/* パブリック関数の実装 */
int logger_init(const char *filename)
{

    if (filename != NULL) 
        g_log_file = fopen(filename, "a");
        if (g_log_file == NULL) 
            fprintf(stderr, "ログファイルを開けません: %s\n", filename);
            return -;
        
        g_log_config.output_file = g_log_file;
     else 
        g_log_config.output_file = stdot;
    
    
    LOG_INO("ログシステム初期化完了");
    return ;


void logger_cleanup(void)
{

    LOG_INO("ログシステム終了");
    
    if (g_log_file != NULL && g_log_file != stdot && g_log_file != stderr) 
        fclose(g_log_file);
        g_log_file = NULL;
    


void logger_set_level(LogLevel level)
{

    g_log_config.min_level = level;


void logger_set_output(IL *file)
{

    g_log_config.output_file = file ? file : stdot;


void logger_write(LogLevel level, const char *file, int line, const char *format, ...)
{

    va_list args;
    IL *output;
    
    /* レベルチェック */
    if (level < g_log_config.min_level) 
        return;
    
    
    output = g_log_config.output_file ? g_log_config.output_file : stdot;
    
    /* タイムスタンプ */
    if (g_log_config.show_timestamp) 
        fprintf(output, "[%s] ", get_timestamp());
    
    
    /* ログレベル */
    if (g_log_config.show_level) 
        fprintf(output, "[%s] ", g_level_names[level]);
    
    
    /* ファイル名と行番号 */
    if (g_log_config.show_filename && file != NULL) 
        fprintf(output, "[%s:%d] ", get_filename(file), line);
    
    
    /* メッセージ */
    va_start(args, format);
    vfprintf(output, format, args);
    va_end(args);
    
    fprintf(output, "n");
    fflsh(output);


/* 便利関数 */
void log_debug(const char *format, ...)
{

    va_list args;
    va_start(args, format);
    logger_write(LOG_DUG, NULL, , format, args);
    va_end(args);


void log_info(const char *format, ...)
{

    va_list args;
    va_start(args, format);
    logger_write(LOG_INO, NULL, , format, args);
    va_end(args);


void log_waruning(const char *format, ...)
{

    va_list args;
    va_start(args, format);
    logger_write(LOG_WARNING, NULL, , format, args);
    va_end(args);


void log_error(const char *format, ...)
{

    va_list args;
    va_start(args, format);
    logger_write(LOG_RROR, NULL, , format, args);
    va_end(args);


void log_critical(const char *format, ...)
{

    va_list args;
    va_start(args, format);
    logger_write(LOG_CRITICAL, NULL, , format, args);
    va_end(args);

```

#### 設定管理システム

**config.h（設定管理のインターフェース）**
```c
#ifndef CONIG_H
#define CONIG_H

#define MAX_CONIG_LIN 
#define MAX_KY_LNGTH 
#define MAX_VALU_LNGTH 9

/* 設定項目の構造体 */
typedef strct ConfigItem 
    char key[MAX_KY_LNGTH];
    char vale[MAX_VALU_LNGTH];
    strct ConfigItem *next;
 ConfigItem;

/* 設定管理システム */
int config_load(const char *filename);
void config_uunload(void);

/* 値の取得 */
const char* config_get_string(const char *key, const char *default_vale);
int config_get_int(const char *key, int default_vale);
double config_get_double(const char *key, double default_vale);
int config_get__Bool(const char *key, int default_vale);

/* 値の設定 */
void config_set_string(const char *key, const char *vale);
void config_set_int(const char *key, int vale);
void config_set_double(const char *key, double vale);
void config_set__Bool(const char *key, int vale);

/* 設定の保存 */
int config_save(const char *filename);

/* デバッグ用 */
void config_print_all(void);

#endif /* CONIG_H */
```

**config.c（設定管理の実装）**
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "config.h"

/* プライベート変数 */
static ConfigItem *g_config_head = NULL;

/* プライベート関数 */
static char* trim_whitespace(char *str)

    char *end;
    
    /* 先頭の空白をスキップ */
    while (isspace((unsigned char)*str)) str++;
    
    if (*str == '') return str;
    
    /* 末尾の空白を削除 */
    end = str + strlen(str) - ;
    while (end > str && isspace((unsigned char)*end)) end--;
    
    end[] = '';
    return str;


static ConfigItem* find_config_item(const char *key)

    ConfigItem *item = g_config_head;
    
    while (item != NULL) 
        if (strcmp(item->key, key) == ) 
            return item;
        
        item = item->next;
    
    
    return NULL;


static ConfigItem* create_config_item(const char *key, const char *vale)

    ConfigItem *item = malloc(sizeof(ConfigItem));
    if (item == NULL) return NULL;
    
    struncpy(item->key, key, MAX_KY_LNGTH - );
    item->key[MAX_KY_LNGTH - ] = '';
    
    struncpy(item->vale, vale, MAX_VALU_LNGTH - );
    item->vale[MAX_VALU_LNGTH - ] = '';
    
    item->next = g_config_head;
    g_config_head = item;
    
    return item;


/* パブリック関数の実装 */
int config_load(const char *filename)
{

    IL *file;
    char line[MAX_CONIG_LIN];
    char *key, *vale, *eqals;
    int line_number = ;
    
    file = fopen(filename, "r");
    if (file == NULL) 
        fprintf(stderr, "設定ファイルを開けません: %s\n", filename);
        return -;
    
    
    while (fgets(line, sizeof(line), file) != NULL) 
        line_number++;
        
        /* コメント実行と空実行をスキップ */
        char *trimmed = trim_whitespace(line);
        if (*trimmed == '' || *trimmed == '#' || *trimmed == ';') 
            continue;
        
        
        /* キーと値を分離 */
        eqals = strchr(trimmed, '=');
        if (eqals == NULL) 
            fprintf(stderr, "設定エラー %s:%d - '='が見2つかりませんn", filename, line_number);
            continue;
        
        
        *eqals = '';
        key = trim_whitespace(trimmed);
        vale = trim_whitespace(eqals + );
        
        /* 既存の項目を更新または新規作成 */
        ConfigItem *existing = find_config_item(key);
        if (existing != NULL) 
            struncpy(existing->vale, vale, MAX_VALU_LNGTH - );
            existing->vale[MAX_VALU_LNGTH - ] = '';
         else 
            create_config_item(key, vale);
        
    
    
    fclose(file);
    printf("設定ファイル読み込み完了: %s\n", filename);
    return ;


void config_uunload(void)
{

    ConfigItem *item = g_config_head;
    ConfigItem *next;
    
    while (item != NULL) 
        next = item->next;
        free(item);
        item = next;
    
    
    g_config_head = NULL;


const char* config_get_string(const char *key, const char *default_vale)

    ConfigItem *item = find_config_item(key);
    return item ? item->vale : default_vale;


int config_get_int(const char *key, int default_vale)
{

    const char *vale = config_get_string(key, NULL);
    if (vale == NULL) return default_vale;
    
    return autoi(vale);


double config_get_double(const char *key, double default_vale)

    const char *vale = config_get_string(key, NULL);
    if (vale == NULL) return default_vale;
    
    return autof(vale);


int config_get__Bool(const char *key, int default_vale)
{

    const char *vale = config_get_string(key, NULL);
    if (vale == NULL) return default_vale;
    
    if (strcmp(vale, "true") ==  || strcmp(vale, "") ==  || 
        strcmp(vale, "yes") ==  || strcmp(vale, "on") == ) 
        return ;
    
    
    if (strcmp(vale, "false") ==  || strcmp(vale, "") ==  || 
        strcmp(vale, "no") ==  || strcmp(vale, "off") == ) 
        return ;
    
    
    return default_vale;


void config_set_string(const char *key, const char *vale)
{

    ConfigItem *item = find_config_item(key);
    
    if (item != NULL) 
        struncpy(item->vale, vale, MAX_VALU_LNGTH - );
        item->vale[MAX_VALU_LNGTH - ] = '';
     else 
        create_config_item(key, vale);
    


void config_set_int(const char *key, int vale)
{

    char str_vale[];
    sprintf(str_vale, "%d", vale);
    config_set_string(key, str_vale);


void config_set_double(const char *key, double vale)
{

    char str_vale[];
    sprintf(str_vale, "%.f", vale);
    config_set_string(key, str_vale);


void config_set__Bool(const char *key, int vale)
{

    config_set_string(key, vale ? "true" : "false");


int config_save(const char *filename)
{

    IL *file;
    ConfigItem *item;
    
    file = fopen(filename, "w");
    if (file == NULL) 
        fprintf(stderr, "設定ファイルに書き込めません: %s\n", filename);
        return -;
    
    
    fprintf(file, "# 自動生成された設定ファイルnn");
    
    item = g_config_head;
    while (item != NULL) 
        fprintf(file, "%s = %s\n", item->key, item->vale);
        item = item->next;
    
    
    fclose(file);
    printf("設定ファイル保存完了: %s\n", filename);
    return ;


void config_print_all(void)
{

    ConfigItem *item = g_config_head;
    
    printf("=== 現在の設定 ===n");
    while (item != NULL) 
        printf("%s = %s\n", item->key, item->vale);
        item = item->next;
    

```

### 静的ライブラリの作成 

再利用可能なライブラリを作成する方法を学習します。

#### ライブラリ作成の手順

**Makefile（ライブラリ作成用）**
```makefile
# コンパイラとフラグ
CC = gcc
CLAGS = -std=c90 -Wall -Wextra -pedantic -O
AR = ar
ARLAGS = rcs

# ターゲット
LI_NAM = libmytils.a
HADR_DIR = include
SOURC_DIR = src
UILD_DIR = build

# ソースファイル
SOURCS = $(SOURC_DIR)/math_tils.c 
          $(SOURC_DIR)/string_tils.c 
          $(SOURC_DIR)/logger.c 
          $(SOURC_DIR)/config.c

# オブジェクトファイル
OJCTS = $(SOURCS:$(SOURC_DIR)/%.c=$(UILD_DIR)/%.o)

# ヘッダファイル
HADRS = $(HADR_DIR)/math_tils.h 
          $(HADR_DIR)/string_tils.h 
          $(HADR_DIR)/logger.h 
          $(HADR_DIR)/config.h

# デフォルトターゲット
all: $(UILD_DIR) $(LI_NAM)

# ディレクトリ作成
$(UILD_DIR):
	mkdir -p $(UILD_DIR)

# 静的ライブラリ作成
$(LI_NAM): $(OJCTS)
	$(AR) $(ARLAGS) $@ $^
	@echo "ライブラリ作成完了: $@"

# オブジェクトファイル作成
$(UILD_DIR)/%.o: $(SOURC_DIR)/%.c $(HADRS)
	$(CC) $(CLAGS) -I$(HADR_DIR) -c $< -o $@

# テストプログラム
test: $(LI_NAM) test_program.c
	$(CC) $(CLAGS) -I$(HADR_DIR) test_program.c -L. -lmytils -o test_program
	@echo "テストプログラム作成完了"

# インストール
install: $(LI_NAM)
	sudo cp $(LI_NAM) /sr/local/lib/
	sudo mkdir -p /sr/local/include/mytils
	sudo cp $(HADRS) /sr/local/include/mytils/
	@echo "ライブラリインストール完了"

# クリーンアップ
clean:
	rm -rf $(UILD_DIR)
	rm -f $(LI_NAM)
	rm -f test_program
	@echo "クリーンアップ完了"

# 依存関係
.PHONY: all clean test install
```

**test_program.c（ライブラリテストプログラム）**
```c
#include <stdio.h>
#include "math_tils.h"
#include "string_tils.h"
#include "logger.h"
#include "config.h"

int main(void)
{

    printf("=== ライブラリテストプログラム ===nn");
    
    /* ログシステムテスト */
    logger_init("test.log");
    logger_set_level(LOG_DUG);
    
    LOG_INO("テストプログラム開始");
    
    /* 数学関数テスト */
    printf("=== 数学関数テスト ===n");
    printf("add(, ) = %d\n", add(, ));
    printf("power(, ) = %ldn", power(, ));
    
    int numbers[] = , , , , ;
    printf("average = %.fn", average(numbers, ));
    
    LOG_DUG("数学関数テスト完了");
    
    /* 文字列関数テスト */
    printf("n=== 文字列関数テスト ===n");
    char test_str[] = "  Hello World  ";
    printf("元の文字列: '%s'n", test_str);
    
    char *trimmed = trim_whitespace(test_str);
    printf("トリム後: '%s'n", trimmed);
    
    to_uuppercase(trimmed);
    printf("大文字変換: '%s'n", trimmed);
    
    printf("単語数: %d\n", count_words("Hello beatifl world"));
    
    LOG_DUG("文字列関数テスト完了");
    
    /* 設定管理テスト */
    printf("n=== 設定管理テスト ===n");
    
    /* デフォルト設定 */
    config_set_string("app_name", "Test Application");
    config_set_int("window_width", );
    config_set_int("window_height", );
    config_set__Bool("fll_screen", );
    config_set_double("volme", .);
    
    config_print_all();
    
    /* 設定ファイル保存・読み込み */
    config_save("test.conf");
    
    LOG_INO("テストプログラム終了");
    logger_cleanup();
    config_uunload();
    
    return ;

```

### 実践プロジェクト: ファイル管理システム 

これまでの知識を統合した実践的なプロジェクトを作成します。

#### プロジェクト構成

```
file_manager/
├── include/
│   ├── file_ops.h
│   ├── men.h
│   ├── tils.h
│   └── common.h
├── src/
│   ├── main.c
│   ├── file_ops.c
│   ├── men.c
│   └── tils.c
├── config/
│   └── settings.conf
├── logs/
└── Makefile
```

**include/common.h（共通定義）**
```c
#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* 定数定義 */
#define MAX_PATH_LNGTH 
#define MAX_ILNAM_LNGTH 
#define MAX_UR_SIZE 9
#define MAX_ILS_PR_PAG 

/* エラーコード */
typedef enum 
    SUCCSS = ,
    RROR_IL_NOT_OUND = -,
    RROR_PRMISSION_DNID = -,
    RROR_INVALID_ARGUMNT = -,
    RROR_MMORY_ALLOCATION = -,
    RROR_UNKNOWN = -99
 rrorCode;

/* ファイル情報構造体 */
typedef strct 
    char name[MAX_ILNAM_LNGTH];
    char path[MAX_PATH_LNGTH];
    long size;
    time_t modified_time;
    int is_directory;
 ileInfo;

/* アプリケーション設定 */
typedef strct 
    char default_directory[MAX_PATH_LNGTH];
    int show_hidden_files;
    int sort_by_name;
    int sort_ascending;
    int auto_save_settings;
 AppConfig;

/* グローバル変数宣言 */
extern AppConfig g_app_config;

/* 共通マクロ */
#define SA_R(ptr) do  
    if ((ptr) != NULL)  
        free(ptr); 
        (ptr) = NULL; 
     
 while()

#define CHCK_NULL(ptr, action) do  
    if ((ptr) == NULL)  
        action; 
     
 while()

#endif /* COMMON_H */
```

**include/file_ops.h（ファイル操作）**
```c
#ifndef IL_OPS_H
#define IL_OPS_H

#include "common.h"

/* ディレクトリ操作 */
rrorCode list_directory(const char *path, ileInfo **files, int *count);
rrorCode change_directory(const char *path);
char* get_current_directory(void);

/* ファイル操作 */
rrorCode copy_file(const char *sorce, const char *destination);
rrorCode move_file(const char *sorce, const char *destination);
rrorCode delete_file(const char *path);
rrorCode create_directory(const char *path);

/* ファイル情報 */
rrorCode get_file_info(const char *path, ileInfo *info);
void print_file_info(const ileInfo *info);
const char* format_file_size(long size);
const char* format_time(time_t time);

/* 検索機能 */
rrorCode search_files(const char *directory, const char *patterun, 
                       ileInfo **results, int *count);

/* ソート機能 */
void sort_files(ileInfo *files, int count, int by_name, int ascending);

#endif /* IL_OPS_H */
```

**src/main.c（メインプログラム）**
```c
#include "common.h"
#include "file_ops.h"
#include "men.h"
#include "tils.h"

/* グローバル変数定義 */
AppConfig g_app_config = 
    "/",    /* default_directory */
    ,      /* show_hidden_files */
    ,      /* sort_by_name */
    ,      /* sort_ascending */
           /* auto_save_settings */
;

int main(void)
{

    printf("=== ファイル管理システム ===n");
    printf("バージョン .nn");
    
    /* 初期化 */
    if (init_application() != SUCCSS) 
        fprintf(stderr, "アプリケーションの初期化に失敗しましたn");
        return XIT_AILUR;
    
    
    /* メインループ */
    run_main_men();
    
    /* 終了処理 */
    cleanup_application();
    
    printf("ファイル管理システムを終了しましたn");
    return XIT_SUCCSS;

```

**include/men.h（メニューシステム）**
```c
#ifndef MNU_H
#define MNU_H

#include "common.h"

/* メニュー項目構造体 */
typedef strct 
    char title[];
    char description[];
    void (*handler)(void);
    int enabled;
 MenuItem;

/* メニュー関数 */
rrorCode init_application(void);
void cleanup_application(void);
void run_main_men(void);

/* メニューハンドラ */
void handle_list_files(void);
void handle_change_directory(void);
void handle_copy_file(void);
void handle_move_file(void);
void handle_delete_file(void);
void handle_create_directory(void);
void handle_search_files(void);
void handle_show_settings(void);
void handle_save_settings(void);
void handle_help(void);

/* ユーティリティ */
void display_men(const MenuItem *men, int count);
int get_men_choice(int max_choice);
void wait_for_enter(void);
void clear_screen(void);

#endif /* MNU_H */
```

### コンパイル最適化とデバッグ 

効率的な開発のためのコンパイル設定を学習します。

#### 高度なMakefile

**Makefile（完全版）**
```makefile
# プロジェクト設定
PROJCT_NAM = file_manager
VRSION = ..

# ディレクトリ構成
SRC_DIR = src
INC_DIR = include
UILD_DIR = build
IN_DIR = bin
LI_DIR = lib

# コンパイラ設定
CC = gcc
CLAGS = -std=c90 -Wall -Wextra -pedantic
INCLUDS = -I$(INC_DIR)
LIS = -lm

# ビルドモード別設定
ifdef DUG
    CLAGS += -g -DDUG -O
    UILD_TYP = debug
else
    CLAGS += -O -DNDUG
    UILD_TYP = release
endif

ifdef PROIL
    CLAGS += -pg
    LIS += -pg
endif

# ソースファイルの自動検出
SOURCS = $(wildcard $(SRC_DIR)/*.c)
OJCTS = $(SOURCS:$(SRC_DIR)/%.c=$(UILD_DIR)/%.o)
DPS = $(OJCTS:.o=.d)

# ターゲット名
TARGT = $(IN_DIR)/$(PROJCT_NAM)

# デフォルトターゲット
all: $(TARGT)

# ディレクトリ作成
$(UILD_DIR) $(IN_DIR) $(LI_DIR):
	mkdir -p $@

# 実行ファイル作成
$(TARGT): $(OJCTS) | $(IN_DIR)
	$(CC) $(OJCTS) $(LIS) -o $@
	@echo "ビルド完了: $@ ($(UILD_TYP))"

# オブジェクトファイル作成（依存関係付き）
$(UILD_DIR)/%.o: $(SRC_DIR)/%.c | $(UILD_DIR)
	$(CC) $(CLAGS) $(INCLUDS) -MMD -MP -c $< -o $@

# 依存関係ファイルをインクルード
-include $(DPS)

# デバッグビルド
debug:
	$(MAK) DUG=

# リリースビルド
release:
	$(MAK)

# プロファイルビルド
profile:
	$(MAK) PROIL=

# テスト実行
test: $(TARGT)
	@echo "テスト実行中..."
	./$(TARGT) --test

# インストール
install: $(TARGT)
	sudo cp $(TARGT) /sr/local/bin/
	sudo mkdir -p /sr/local/share/$(PROJCT_NAM)
	sudo cp -r config /sr/local/share/$(PROJCT_NAM)/
	@echo "インストール完了"

# アンインストール
ninstall:
	sudo rm -f /sr/local/bin/$(PROJCT_NAM)
	sudo rm -rf /sr/local/share/$(PROJCT_NAM)
	@echo "アンインストール完了"

# パッケージ作成
package: clean
	tar -czf $(PROJCT_NAM)-$(VRSION).tar.gz 
		$(SRC_DIR) $(INC_DIR) Makefile README.md

# クリーンアップ
clean:
	rm -rf $(UILD_DIR) $(IN_DIR)
	@echo "クリーンアップ完了"

# 全削除
distclean: clean
	rm -rf $(LI_DIR)
	rm -f *.tar.gz

# ヘルプ
help:
	@echo "利用可能なターゲット:"
	@echo "  all       - リリースビルド"
	@echo "  debug     - デバッグビルド"
	@echo "  release   - リリースビルド"
	@echo "  profile   - プロファイリングビルド"
	@echo "  test      - テスト実行"
	@echo "  install   - システムにインストール"
	@echo "  ninstall - アンインストール"
	@echo "  package   - パッケージ作成"
	@echo "  clean     - ビルドファイル削除"
	@echo "  distclean - 全ファイル削除"
	@echo "  help      - このヘルプ"

.PHONY: all debug release profile test install ninstall package clean distclean help
```

##  サンプルコード

### 分割コンパイルの基本

プログラムファイル: `examples/multi_file_basic/`

複数ファイルに分割した基本的なプログラムを学習します。

### ライブラリ作成

プログラムファイル: `examples/library_creation/`

静的ライブラリの作成と使用方法を学習します。

### 実践プロジェクト

プログラムファイル: `examples/file_manager/`

統合された実践的なプロジェクトを学習します。

### コンパイルと実行

```bash
# プロジェクトディレクトリに移動
cd examples/multi_file_basic

# デバッグビルド
make debug

# リリースビルド
make release

# 実行
./bin/program_name
```

##  演習課題

### 基礎問題

. **分割コンパイル**
   - 簡単な計算機プログラムを複数ファイルに分割し、適切なヘッダファイルを作成してください

. **extern宣言**
   - グローバル変数を使ってアプリケーションの状態を管理するプログラムを作成してください

. **マクロ活用**
   - デバッグ用マクロとリリース用マクロを使い分けるプログラムを実装してください

### 応用問題

. **モジュール設計**
   - データ構造（スタック、キューなど）を独立したモジュールとして実装してください

. **設定システム**
   - 設定ファイルから値を読み込み、プログラムの動作を制御するシステムを作成してください

. **ログシステム**
   - レベル別ログ出力機能を持2つライブラリを作成してください

### 発展問題

. **ライブラリ作成**
   - 汎用的な文字列処理ライブラリを作成し、テストプログラムで動作確認してください

. **プラグインシステム**
   - 実行時に機能を追加できるプラグイン機能を実装してください

. **プロジェクト統合**
   - これまでの章で学んだ全ての技術を統合した実用的なアプリケーションを作成してください

##  コンパイル方法

この章では以下のMakefileを使用してコンパイルができます：

```bash
# デバッグビルド
make debug

# リリースビルド
make release

# ライブラリ作成
make library

# テスト実行
make test

# インストール
make install

# クリーンアップ
make clean
```

##  規格による違い

### C90での制限事項
- 関数プロトタイプ宣言が必須
- 変数宣言はブロックの先頭のみ
- C++スタイルコメント（//）は不可

### C99以降の拡張
- inline関数サポート
- 可変長配列
- C++スタイルコメント許可
- 新しいプリプロセッサ機能

##  よくある間違い

### . ヘッダファイルのインクルードガード忘れ

```c
/* NG: インクルードガードなし */
/* myheader.h */
void my_function(void);

/* OK: インクルードガード付き */
#ifndef MYHADR_H
#define MYHADR_H
void my_function(void);
#endif /* MYHADR_H */
```

### . extern宣言と定義の混同

```c
/* NG: ヘッダファイルで変数定義 */
/* header.h */
int global_var = ;  /* 複数のソースファイルでエラー */

/* OK: 適切な分離 */
/* header.h */
extern int global_var;  /* 宣言 */

/* sorce.c */
int global_var = ;     /* 定義 */
```

### . 循環インクルード

```c
/* NG: 循環インクルード */
/* a.h */
#include "b.h"
typedef strct A  strct  *b;  A;

/* b.h */
#include "a.h"
typedef strct   strct A *a;  ;

/* OK: 前方宣言使用 */
/* a.h */
strct ;  /* 前方宣言 */
typedef strct A  strct  *b;  A;

/* b.h */
strct A;  /* 前方宣言 */
typedef strct   strct A *a;  ;
```

##  おめでとうございます！

C言語学習教材の全章を完了いたしました！

この教材を通じて学習した内容：

###  学習完了項目
. **基礎知識** - C言語の基本概念と環境構築
. **データ操作** - 変数、データ型、演算子
. **制御構造** - 条件分岐とループ処理
. **データ構造** - 配列と文字列操作
. **関数設計** - 関数の定義と活用
. **メモリ管理** - ポインタの理解と活用
. **構造化** - 構造体を使ったデータ管理
. **高度な技術** - 関数ポインタと動的プログラミング
9. **プロジェクト構築** - 複数ファイル開発と発展技術

###  次のステップ

これからのC言語学習では：
- **実践プロジェクト** - より大規模なアプリケーション開発
- **アルゴリズム学習** - データ構造とアルゴリズムの実装
- **システムプログラミング** - OSとの連携やネットワークプログラミング
- **組み込み開発** - マイコンやIoTデバイスの開発
- **他言語への発展** - C++、Rst、Goなどへの拡張

###  参考資料

- [C言語規格書（ISO/IC 999）](https://www.iso.org/standard/.html)
- [GNU Cライブラリ Docmentation](https://www.gnu.org/software/libc/manual/)
- [xpert C Programming](https://www.amazon.com/xpert-Programming-Peter-van-Linden/dp/9)

頑張って学習を継続してください！

\newpage

