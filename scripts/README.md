# 文書とコードの検証スクリプト

このディレクトリには、教材の正本を検証し、配布用PDFを生成するスクリプトを置きます。

## PDF生成

`build_book.py`は、`docs/book.json`に定義した順序で`src`以下のMarkdownを読み込みます。
通常版では、読み込んだ本文、演習問題、解答例を1冊のPDFへまとめます。
演習問題集版では、同じ原稿から演習問題だけを抽出します。

```bash
npm run docs:publish
```

次のPDFを生成します。

- `output/pdf/C言語プログラミング教材.pdf`
- `output/pdf/C言語プログラミング演習問題集.pdf`

演習問題集だけを生成する場合は、次のコマンドを実行します。

```bash
npm run docs:publish:exercises
```

処理は次の順序で進みます。

1. 入力ファイルの文字コードと禁止表現を確認します。
2. PandocでMarkdownを構文木へ変換します。
3. Mermaidの図をPNGへ変換します。
4. ReportLabでA4判のPDFを生成します。
5. PDFのページ数、書名、禁止トークンを検証します。
6. Popplerで全ページをPNGへ変換します。

結合Markdownは`tmp/pdfs`内に一時生成され、正本として保存されません。

## Cコードの検証

`check_c_examples.py`は、すべてのCソースを個別に構文検査します。

```bash
npm run c:check
```

C17までの教材はC17モード、C23の教材はC2xモードで検査し、実行ファイルは生成しません。
