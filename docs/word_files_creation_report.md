# C言語学習教材 章別Wordファイル作成レポート

**作成日時**: 2025年6月29日 23:10  
**使用ツール**: pandoc 3.7.0.2  
**テンプレート**: custom-reference-1.docx

## 作成内容

custom-reference-1.docxをテンプレートとして使用し、pandocコマンドで全14章のWordファイルを作成しました。

### 作成ファイル一覧

| 章番号 | 章タイトル | 教科書ファイル | 演習問題ファイル |
|--------|-----------|--------------|----------------|
| 第1章 | 導入・環境構築 | chapter_01_textbook.docx | chapter_01_exercises.docx |
| 第2章 | 基本文法・Hello World | chapter_02_textbook.docx | chapter_02_exercises.docx |
| 第3章 | データ型と変数 | chapter_03_textbook.docx | chapter_03_exercises.docx |
| 第4章 | 演算子 | chapter_04_textbook.docx | chapter_04_exercises.docx |
| 第5章 | 制御構造（条件分岐） | chapter_05_textbook.docx | chapter_05_exercises.docx |
| 第6章 | 制御構造（ループ） | chapter_06_textbook.docx | chapter_06_exercises.docx |
| 第7章 | 配列 | chapter_07_textbook.docx | chapter_07_exercises.docx |
| 第8章 | 文字列処理 | chapter_08_textbook.docx | chapter_08_exercises.docx |
| 第9章 | 関数 | chapter_09_textbook.docx | chapter_09_exercises.docx |
| 第10章 | ポインタ基礎 | chapter_10_textbook.docx | chapter_10_exercises.docx |
| 第11章 | 構造体とポインタ | chapter_11_textbook.docx | chapter_11_exercises.docx |
| 第12章 | 関数ポインタ | chapter_12_textbook.docx | chapter_12_exercises.docx |
| 第13章 | 複数ファイル・発展技術 | chapter_13_textbook.docx | chapter_13_exercises.docx |
| 第14章 | C23の新機能（オプション） | chapter_14_textbook.docx | chapter_14_exercises.docx |

### ファイル構成

#### 教科書ファイル
- 章タイトル
- README.mdの内容（理論説明）
- サンプルコード（examples/ディレクトリのC90版）

#### 演習問題ファイル
- 章タイトル
- 演習問題（exercises/README.md）
- 解答例の説明（solutions/README.md）
- 解答コード（solutions/ディレクトリのC90版）

### 使用コマンド

```bash
pandoc [入力.md] --reference-doc=custom-reference-1.docx -o [出力.docx] --from markdown --to docx --standalone
```

### 作成スクリプト

- `scripts/create_docs_with_pandoc.sh` - pandocを使用した自動生成スクリプト

## 備考

- C99版のコードは含めず、C90版のみを使用
- custom-reference-1.docxのスタイルが適用されたWordファイル
- 合計28ファイル（14章 × 2種類）を生成