# 第2章：基本構文

## 対応するC規格

- **主要対象**：C90
- **学習内容**：プログラムの構造、`main`関数、`printf`関数、コメント、エスケープシーケンス

## 学習目標

この章では、短いCプログラムを構成する要素と、標準出力の基本を学びます。

- `#include`、関数定義、文の役割を説明できる
- 標準規格に沿った`main`関数を定義できる
- `printf`の書式指定と引数の型を対応させられる
- C90で使用できるコメントを記述できる

## プログラムの構造

次のプログラムは、標準出力へ1行を書き出して終了します。

```c
#include <stdio.h>

int main(void)
{
    printf("Hello, World!\n");
    return 0;
}
```

`#include <stdio.h>`は、標準入出力ライブラリが提供する`printf`関数の宣言を取り込みます。
関数を正しい宣言なしで呼び出してはいけません。

`main`は、ホスト環境で実行されるCプログラムの開始点です。
関数本体は`{`と`}`で囲み、処理を構成する文の末尾には、必要に応じてセミコロンを置きます。

## `main`関数

コマンドライン引数を使わない場合は、次の形式を使用します。

```c
int main(void)
{
    return 0;
}
```

コマンドライン引数を受け取る場合は、次の形式を使用できます。

```c
#include <stdio.h>

int main(int argc, char *argv[])
{
    printf("Program: %s\n", argv[0]);

    if (argc > 1) {
        printf("First argument: %s\n", argv[1]);
    }

    return 0;
}
```

`argc`は引数の個数で、0以上です。
`argc`が0より大きい場合、`argv[0]`はプログラム名を表す文字列を指します。
実行環境からプログラム名を取得できない場合、`argv[0][0]`はヌル文字です。

`main`から0を返すと、正常終了を表します。
異常終了を表す移植可能な値には、`<stdlib.h>`で定義される`EXIT_FAILURE`を使用できます。
C99以降では、`main`の末尾まで到達した場合も0を返したものとして扱われますが、教材では終了状態を明示します。

標準Cのホスト環境では、`void main()`は規定された形式ではありません。
戻り値の型には`int`を使用してください。

## `printf`関数

`printf`は、書式文字列に従って標準出力へデータを書き出します。
書式指定子と対応する引数の型が一致しない場合、動作は未定義です。

| 指定子 | 対応する引数 | 用途 |
|---|---|---|
| `%d` | `int` | 符号付き10進整数 |
| `%u` | `unsigned int` | 符号なし10進整数 |
| `%c` | `int`へ整数拡張された文字 | 1文字 |
| `%s` | `char *` | ヌル終端文字列 |
| `%f` | `double` | 固定小数点表記 |
| `%p` | `void *` | ポインタ値 |

可変個引数関数では、`float`は`double`へ、`char`と`short`は通常`int`へ既定の実引数拡張を受けます。
このため、`printf`で浮動小数点数を表示するときの`%f`は`double`を受け取ります。

```c
#include <stdio.h>

int main(void)
{
    int age = 20;
    double height = 170.5;

    printf("Age: %d\n", age);
    printf("Height: %.1f cm\n", height);
    return 0;
}
```

`printf`は、書き出した文字数を返します。
出力エラーが発生した場合は負の値を返すため、出力の成否が必要なプログラムでは戻り値を検査します。

### 書式指定の誤り

書式指定子の個数と引数の個数を一致させます。

```c
printf("%d + %d = %d\n", 10, 20, 30);
```

次の呼び出しは、`%d`が要求する`int`に対して`double`を渡しているため、未定義動作です。

```c
double value = 3.14;
printf("%d\n", value); /* Wrong format: undefined behavior. */
```

正しくは`%f`を使用します。

```c
printf("%f\n", value);
```

## エスケープシーケンス

文字列リテラルの中では、バックスラッシュで始まるエスケープシーケンスを使って制御文字や引用符を表します。

| シーケンス | 意味 |
|---|---|
| `\n` | 改行 |
| `\t` | 水平タブ |
| `\"` | ダブルクォート |
| `\\` | バックスラッシュ |
| `\a` | 警告音 |
| `\b` | バックスペース |
| `\r` | 復帰 |

端末が警告音、バックスペース、復帰をどのように表示するかは、実行環境に依存します。
たとえば、`\b`が直前の文字を画面から必ず消すとは限りません。

```c
#include <stdio.h>

int main(void)
{
    printf("First line\nSecond line\n");
    printf("Name\tScore\n");
    printf("Quote: \"C\"\n");
    printf("Path: C:\\Program Files\\App\n");
    return 0;
}
```

## コメント

C90では、`/*`から`*/`までがコメントです。
コメントは入れ子にできません。

```c
/* This is a comment. */

/*
 * A comment can span
 * multiple lines.
 */
```

`//`で始まる行コメントは、C99で標準化されました。
C90としてコンパイルするコードでは使用しません。

## コンパイル

警告と規格適合性の診断を有効にしてコンパイルします。

```bash
gcc -std=c90 -Wall -Wextra -pedantic examples/hello_world.c -o hello_world
./hello_world
```

Makefileを使う場合は、次のコマンドを実行します。

```bash
make all
make run-all
make clean
```

実装例は、次のファイルにあります。

- [hello_world.c](examples/hello_world.c)
- [formatted_output.c](examples/formatted_output.c)
- [escape_sequences.c](examples/escape_sequences.c)

## C90とC99の違い

C90では、宣言を各複合文の文より前に置き、コメントには`/* ... */`を使います。
C99では、文の後や`for`文の初期化部でも変数を宣言でき、`//`コメントも使用できます。

## 演習問題

[演習問題](exercises/)では、標準出力、書式指定、エスケープシーケンスを練習します。

## 参考資料

- [第1章：はじめてのC言語](../introduction/README.md)
- [データ型と変数](../data-types/README.md)
