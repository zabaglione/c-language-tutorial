# C言語プログラミング教材

C言語の基礎からC23の機能までを、サンプルコードと演習問題を通して学ぶ教材です。
各章は、概念の説明、実行できるコード、演習問題、解答例で構成されています。

## 教材の正本

教材の文章は`src`以下のMarkdownだけを編集します。
PDF用の結合Markdownや分冊Markdownはリポジトリに保存しません。

- 本文：`src/<chapter>/README.md`
- 演習問題：`src/<chapter>/exercises/README.md`
- 解答例：`src/<chapter>/solutions/README.md`
- 章順と書名：`docs/book.json`

この構成により、同じ文章を複数のファイルで管理する必要がありません。

## 章構成

| 章 | 内容 | ディレクトリ |
| --- | --- | --- |
| 第1章 | C言語入門 | `src/introduction` |
| 第2章 | 基本構文 | `src/basics-syntax` |
| 第3章 | データ型と変数 | `src/data-types` |
| 第4章 | 演算子 | `src/operators` |
| 第5章 | 条件分岐 | `src/control-if` |
| 第6章 | 繰り返し処理 | `src/control-loop` |
| 第7章 | 配列 | `src/arrays-basics` |
| 第8章 | ポインター | `src/pointers` |
| 第9章 | 配列とポインター | `src/arrays-pointers` |
| 第10章 | 文字列 | `src/strings` |
| 第11章 | 関数 | `src/functions` |
| 第12章 | ビット操作 | `src/bit-operations` |
| 第13章 | 構造体 | `src/structures` |
| 第14章 | 関数ポインター | `src/function-pointers` |
| 第15章 | 分割コンパイルと発展技術 | `src/advanced` |
| 第16章 | C23の機能 | `src/c23-features` |
| 補章1 | C言語規格の歴史 | `src/c-standards` |
| 補章2 | 開発環境 | `src/development-environment` |

## 学習方法

各章では、次の順序で学習します。

1. 章の`README.md`で概念と文法を確認します。
2. `examples`のコードをコンパイルして実行します。
3. `exercises/README.md`の課題に取り組みます。
4. 実装後に`solutions`の解答例と比較します。

サンプルコードを読むだけでなく、値や条件を変更して実行すると、式と制御構造の働きを確認できます。

## 対応するC規格

本文では、C90を基礎として、C99、C11、C17、C23で追加された機能を区別して説明します。
規格ごとの制約は各章の「対応C規格」で確認してください。

C23の章をコンパイルするには、対象機能に対応した新しいコンパイラーが必要です。

## サンプルコードのコンパイル

Makefileがある章では、章のディレクトリから次のコマンドを実行します。

```bash
make all
make run-all
make clean
```

個別にコンパイルする場合は、警告を有効にして規格を明示します。

```bash
cc -std=c17 -Wall -Wextra -pedantic sample.c -o sample
```

全Cソースの構文を検証するには、次のコマンドを実行します。

```bash
npm run c:check
```

## PDFの作成

PDFは、正本のMarkdownから直接生成します。
Word文書や永続的な結合Markdownは経由しません。

必要なコマンドは次の1つです。

```bash
npm run docs:publish
```

このコマンドは、本文、演習問題、解答例をまとめたPDFを生成し、全ページをPNGへ変換して確認用画像も作成します。

- PDF：`output/pdf/C言語プログラミング教材.pdf`
- 確認用画像：`tmp/pdfs/rendered`
- 全ページの一覧画像：`tmp/pdfs/rendered/contact-sheets`

PDF生成には、次のツールを使用します。

- Python 3.11以降
- uv
- Pandoc
- Mermaid CLI
- Poppler

Pythonライブラリは、`scripts/build_book.py`の依存定義に基づいてuvが準備します。

## 検証

教材全体を検証するには、次のコマンドを実行します。

```bash
npm run check
```

検証では、日本語表記、Markdownの構造、Cコードの構文、PDFの生成可能性を確認します。
