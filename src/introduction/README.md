# 第1章：はじめてのC言語

## 学習目標

この章では、Cプログラムを作成し、コンパイルして実行するまでの流れを学びます。

- C言語が使われる分野を説明できる
- コンパイラを準備し、動作を確認できる
- `Hello, World!`を表示するプログラムを作成できる
- コンパイルと実行を区別できる

## C言語が使われる分野

C言語は、オペレーティングシステム、組込み機器、処理系、性能が求められるライブラリなどで使われています。
メモリ上のデータやハードウェアに近い処理を明示的に記述できる一方、配列の境界やメモリの寿命はプログラマが管理します。

C言語を学ぶと、変数がメモリに格納される仕組み、ソースコードが実行可能ファイルへ変換される過程、処理系に依存する動作と規格で保証される動作の違いを理解しやすくなります。

## 開発環境

Cプログラムの作成には、テキストエディタとCコンパイラが必要です。
コンパイラを導入したら、ターミナルまたはコマンドプロンプトで次のコマンドを実行してください。

```bash
gcc --version
```

バージョン情報が表示されれば、`gcc`コマンドを実行できます。
環境によっては、コンパイラのコマンド名が`clang`です。

### Windows

MinGW-w64など、GCCを含む開発環境を利用できます。
インストール方法と`PATH`の設定は配布元によって異なるため、利用する配布パッケージの手順に従ってください。

### macOS

Command Line Toolsを利用できます。

```bash
xcode-select --install
```

### UbuntuとDebian

`build-essential`パッケージに、GCCや`make`などの基本ツールが含まれます。

```bash
sudo apt update
sudo apt install build-essential
```

## 最初のプログラム

`hello.c`を作成し、次のコードを保存します。

```c
#include <stdio.h>

int main(void)
{
    printf("Hello, World!\n");
    return 0;
}
```

各行には次の役割があります。

- `#include <stdio.h>`は、`printf`関数の宣言を取り込みます。
- `int main(void)`は、引数を受け取らずに`int`を返す`main`関数を定義します。
- `printf`は、標準出力へ文字列を書き出します。
- `return 0;`は、ホスト環境へ正常終了を通知します。

## コンパイルと実行

コンパイルでは、Cのソースファイルから実行可能ファイルを作ります。
警告を有効にすると、誤りの兆候を早い段階で確認できます。

```bash
gcc -std=c90 -Wall -Wextra -pedantic hello.c -o hello
```

コンパイルに成功したら、生成されたプログラムを実行します。

```bash
./hello
```

Windowsのコマンドプロンプトでは、実行ファイル名を指定します。

```text
hello.exe
```

実行結果は次のとおりです。

```text
Hello, World!
```

## 文字列を入力するプログラム

空白を含まない名前を読み取り、入力内容を表示する例です。
`scanf`のフィールド幅を配列の要素数より1小さく指定し、終端文字`'\0'`の領域を確保します。

```c
#include <stdio.h>

int main(void)
{
    char name[50];

    printf("Name: ");
    if (scanf("%49s", name) != 1) {
        return 1;
    }

    printf("Hello, %s!\n", name);
    return 0;
}
```

`%s`だけを指定すると、入力が配列に収まるかを`scanf`が判断できません。
また、この例は空白で入力を区切るため、空白を含む名前全体は読み取れません。
行全体を扱う方法は、文字列の章で説明します。

## 付属コードのビルド

このディレクトリのMakefileを使うと、付属コードをまとめてビルドできます。

```bash
make all
make run-hello_world
make clean
```

実装例は、次のファイルにあります。

- [hello_world.c](examples/hello_world.c)
- [greeting.c](examples/greeting.c)

## 演習問題

[演習問題](exercises/)では、出力内容の変更、複数行の表示、簡単な入力処理を練習します。
