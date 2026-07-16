# C言語の開発環境

## 対応C規格

- **主要対象：** 全規格
- **学習内容：** 必要なツール、翻訳工程、警告、規格モード、デバッグ

## 学習目標

この章を完了すると、次のことができるようになります。

- エディタ、コンパイラ、リンカ、デバッガの役割を説明できる
- プリプロセス、コンパイル、アセンブル、リンクの各段階を確認できる
- 規格モードと警告を指定してプログラムをビルドできる
- コンパイルエラーとリンクエラーを区別できる
- デバッグ情報を付けてデバッガを起動できる

## 最小構成

Cプログラムの作成に必要なのは、ソースファイルを編集するエディタと、ソースコードを実行ファイルへ変換する処理系です。
複数ファイルの管理やデバッグが必要になったら、ビルドツールとデバッガを追加します。

1. **エディタ**：プレーンテキストのソースファイルを編集します
2. **C処理系**：コンパイラ、アセンブラ、リンカ、標準ライブラリを提供します
3. **デバッガ**：停止位置の設定、変数の確認、1ステップ実行を行います
4. **ビルドツール**：複数の翻訳単位と依存関係をまとめてビルドします

特定のエディタやビルドツールは必須ではありません。
プロジェクトですでに使われている処理系とビルド手順がある場合は、その構成を優先します。

## 処理系を確認する

GCC系またはClang系の処理系では、次のコマンドで実行ファイルとバージョンを確認できます。

```bash
cc --version
cc -v
```

`cc`が利用できない場合は、環境が提供する`gcc`、`clang`などのコマンド名を確認します。
インストール方法やパッケージ名はOSと配布元によって変わるため、利用する環境の管理手順に従います。

## 翻訳工程

Cのソースコードは、概念上、前処理、翻訳、アセンブル、リンクを経て実行ファイルになります。
処理系は複数の段階を一つのコマンドで実行できますが、中間結果を出力すると問題の発生箇所を確認できます。

### 前処理

```bash
cc -E source.c -o source.i
```

前処理では、`#include`、マクロ置換、条件付きインクルージョンなどを処理します。
生成された`source.i`を調べると、展開後の宣言やマクロを確認できます。

### アセンブリコードの生成

```bash
cc -S source.c -o source.s
```

`-S`はリンクを行わず、処理系が生成したアセンブリコードを出力します。
最適化による変化を調べる場合は、最適化オプションを明示します。

### オブジェクトファイルの生成

```bash
cc -c source.c -o source.o
```

`-c`はリンクを行わず、翻訳単位ごとのオブジェクトファイルを生成します。

### リンク

```bash
cc main.o utility.o -o program
```

リンクでは、複数のオブジェクトファイルと必要なライブラリから実行ファイルを作ります。
宣言だけがあり定義が見つからない場合や、同じ外部定義が複数ある場合は、この段階で診断されます。

## 警告と規格モード

GCCやClangでは、次のように規格モードと警告を指定できます。

```bash
cc -std=c17 -Wall -Wextra -Wpedantic source.c -o program
```

- **`-std=c17`**：C17を基準に翻訳します
- **`-Wall`**：よく使われる警告群を有効にします。「すべての警告」という意味ではありません
- **`-Wextra`**：追加の警告群を有効にします
- **`-Wpedantic`**：選択した規格から外れる構文や機能の診断を増やします

警告を無効にする前に、警告が示すコード上の問題を確認します。
`-Werror`は警告をエラーとして扱うため、継続的インテグレーションでは有用ですが、処理系の更新で新しい警告が増える影響も考慮します。

### 規格モードの例

```bash
cc -std=c90 -Wall -Wextra -Wpedantic source.c -o program
cc -std=c99 -Wall -Wextra -Wpedantic source.c -o program
cc -std=c11 -Wall -Wextra -Wpedantic source.c -o program
cc -std=c17 -Wall -Wextra -Wpedantic source.c -o program
cc -std=c23 -Wall -Wextra -Wpedantic source.c -o program
```

受け付けるオプション名は処理系によって異なります。
C23への移行期の処理系では、`-std=c2x`を使う場合があります。

## 最適化とデバッグ情報

開発中は、デバッグ情報と、デバッグを妨げにくい最適化を指定できます。

```bash
cc -std=c17 -Wall -Wextra -Wpedantic -g -Og source.c -o program
```

- **`-g`**：デバッガが利用する情報を出力します
- **`-O0`**：最適化を抑えます
- **`-Og`**：デバッグ可能性を考慮した最適化を行います
- **`-O2`**：一般的な最適化を有効にします
- **`-O3`**：より積極的な最適化を試みます
- **`-Os`**：コードサイズを抑える最適化を試みます

最適化レベルが高いと、変数が除去されたり、ソースコードの行と実行順序が対応しにくくなったりします。
性能を比較する場合は、同じ入力とビルド条件で計測します。

## 実装の性質を確認する

型のサイズや範囲は処理系によって異なります。
次のプログラムは、`sizeof`の結果と整数型の範囲を表示します。

```c
#include <limits.h>
#include <stdio.h>

int main(void)
{
    printf("CHAR_BIT: %d\n", CHAR_BIT);
    printf("sizeof(char): %lu\n", (unsigned long)sizeof(char));
    printf("sizeof(short): %lu\n", (unsigned long)sizeof(short));
    printf("sizeof(int): %lu\n", (unsigned long)sizeof(int));
    printf("sizeof(long): %lu\n", (unsigned long)sizeof(long));
    printf("sizeof(void *): %lu\n", (unsigned long)sizeof(void *));
    printf("INT_MIN: %d\n", INT_MIN);
    printf("INT_MAX: %d\n", INT_MAX);
    printf("LONG_MIN: %ld\n", LONG_MIN);
    printf("LONG_MAX: %ld\n", LONG_MAX);
    return 0;
}
```

`sizeof(char)`は常に1ですが、1バイトが8ビットとは限りません。
1バイトのビット数は`CHAR_BIT`で確認します。

### 規格版と処理系を確認する

処理系固有のマクロは、対応する処理系でだけ使用します。
ClangはGCC互換マクロも定義するため、Clangの判定を先に置きます。

```c
#include <stdio.h>

int main(void)
{
#if defined(__clang__)
    printf("Clang: %d.%d.%d\n",
           __clang_major__, __clang_minor__, __clang_patchlevel__);
#elif defined(__GNUC__)
    printf("GCC: %d.%d.%d\n",
           __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__);
#elif defined(_MSC_VER)
    printf("MSVC: %d\n", _MSC_VER);
#else
    printf("Compiler: unknown\n");
#endif

#if defined(__STDC_VERSION__)
    printf("__STDC_VERSION__: %ld\n", __STDC_VERSION__);
#else
    printf("__STDC_VERSION__: not defined\n");
#endif

    return 0;
}
```

処理系固有マクロは、言語規格ではなく処理系の機能を判定するために使います。

## エラーを段階で分類する

### コンパイル時の診断

構文、型、宣言に問題がある場合は、オブジェクトファイルを生成する前に診断されます。
最初の診断が後続の診断を引き起こすことがあるため、先頭のエラーから確認します。

### リンク時の診断

`undefined reference`などの診断は、必要な定義を含むオブジェクトファイルやライブラリがリンク対象にない場合に発生します。
関数の宣言を追加するだけでは解決せず、その関数の定義をリンクする必要があります。

### 実行時の問題

境界外アクセス、解放済み領域の使用、未初期化値の使用などは、翻訳に成功しても実行時に問題になります。
デバッガや、処理系が提供するサニタイザを利用して原因を絞り込みます。

```bash
cc -std=c17 -Wall -Wextra -Wpedantic -g \
  -fsanitize=address,undefined source.c -o program
```

サニタイザはC規格の機能ではなく、処理系の拡張です。
利用可能な種類と対応環境は、使用する処理系で確認します。

## デバッガの基本操作

GDBを使う場合は、デバッグ情報を付けてビルドし、実行ファイルを指定して起動します。

```bash
cc -g -Og source.c -o program
gdb ./program
```

代表的な操作は次のとおりです。

```text
break main
run
next
step
print variable
continue
backtrace
quit
```

LLDBなど別のデバッガではコマンドが異なります。

## Makefileの最小例

複数の翻訳単位を扱う場合は、依存関係をビルドツールへ記述します。
Makefileのレシピ行は、先頭をタブ文字にします。

<!-- markdownlint-disable MD010 -->

```makefile
CC = cc
CFLAGS = -std=c17 -Wall -Wextra -Wpedantic -g

program: main.o utility.o
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c utility.h
	$(CC) $(CFLAGS) -c main.c

utility.o: utility.c utility.h
	$(CC) $(CFLAGS) -c utility.c

clean:
	rm -f main.o utility.o program
```

<!-- markdownlint-enable MD010 -->

ビルドコマンドをシェルのエイリアスへ埋め込むより、Makefileなどプロジェクト内の設定へ記録する方が、他の環境と同じ条件を再現しやすくなります。

## 演習問題

[演習問題](exercises/)では、翻訳工程、警告、リンクエラー、デバッグ情報を確認できます。
