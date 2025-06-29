# 第1章 サンプルコード: C言語の基本

## 概要

この章では、C言語の基本的な概念を学習するためのサンプルコードを提供します。

## 学習内容

### 基本概念
この章では、C言語の基本的な概念を実際のコードで学習します。詳細な理論については [README.md](../README.md) をご参照ください。

## サンプルコード

### 基本プログラム例

#### Hello World プログラム
- [`hello_world.c`](hello_world.c) - C90版の基本的なプログラム
- [`hello_world_c99.c`](hello_world_c99.c) - C99版の基本的なプログラム

#### 変数とデータ型のデモ
- [`variables_demo.c`](variables_demo.c) - C90版の変数使用例
- [`variables_demo_c99.c`](variables_demo_c99.c) - C99版の変数使用例

### コンパイルと実行方法

```bash
# 基本的なコンパイル
gcc -std=c90 -Wall -Wextra -pedantic hello_world.c -o hello_world

# または Makefile を使用
make examples
make run-hello        # Hello World の実行
make run-variables    # 変数デモの実行
```

## 演習問題

演習問題については [exercises/README.md](../exercises/README.md) をご覧ください。

## 解答例

解答例については [solutions/README.md](../solutions/README.md) をご覧ください。

## 次のステップ

この章をマスターしたら、次の章に進みましょう：
- [第2章: 基本文法・Hello World](../basics-syntax/)
- [第3章: データ型と演算子](../data-types/)
- [第4章: 制御構造（条件分岐）](../control-if/)