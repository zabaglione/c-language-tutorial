# 第2章 解答例: 基本文法・Hello World

## 解答例一覧

### 演習2-1: 自己紹介プログラム
- **ファイル**: [`ex2_1_hello_intro.c`](ex2_1_hello_intro.c), [`ex2_1_hello_intro_c99.c`](ex2_1_hello_intro_c99.c)
- **学習内容**: printf文の基本的な使い方、改行文字の使用
- **ポイント**: 複数行の出力とフォーマットの基本

### 演習2-2: 個人データ表示
- **ファイル**: [`ex2_2_personal_data.c`](ex2_2_personal_data.c), [`ex2_2_personal_data_c99.c`](ex2_2_personal_data_c99.c)
- **学習内容**: 変数の宣言と初期化、各種データ型の使用
- **ポイント**: int, float, char型の実用的な使い方

### 演習2-3: 年齢計算プログラム
- **ファイル**: [`ex2_3_age_calculator.c`](ex2_3_age_calculator.c), [`ex2_3_age_calculator_c99.c`](ex2_3_age_calculator_c99.c)
- **学習内容**: scanf関数による入力、計算処理
- **ポイント**: ユーザー入力を受け取って計算結果を表示

### 演習2-4: フォーマット指定子の実践
- **ファイル**: [`ex2_4_format_demo.c`](ex2_4_format_demo.c), [`ex2_4_format_demo_c99.c`](ex2_4_format_demo_c99.c)
- **学習内容**: printf文の書式指定子、桁数指定
- **ポイント**: %d, %f, %c, %sの実用的な使い方

### 演習2-5: 簡単な計算機
- **ファイル**: [`ex2_5_simple_calculator.c`](ex2_5_simple_calculator.c), [`ex2_5_simple_calculator_c99.c`](ex2_5_simple_calculator_c99.c)
- **学習内容**: 四則演算、浮動小数点数の処理
- **ポイント**: 複数の入力と計算結果の表示

### 演習2-6: ASCII文字探索
- **ファイル**: [`ex2_6_ascii_explorer.c`](ex2_6_ascii_explorer.c), [`ex2_6_ascii_explorer_c99.c`](ex2_6_ascii_explorer_c99.c)
- **学習内容**: 文字と数値の変換、ASCIIコードの理解
- **ポイント**: char型と整数型の関係性

## C90版とC99版の違い

### C90版（基本ファイル）
- すべての変数を関数の先頭で宣言
- `/* */` 形式のコメントを使用
- 従来のC言語の書き方に準拠

### C99版（_c99.cファイル）
- 変数を使用する箇所の近くで宣言可能
- `//` 形式のコメントに対応
- より現代的なC言語の書き方

## コンパイルと実行

### C90版
```bash
gcc -Wall -Wextra -pedantic -std=c90 hello_intro.c -o hello_intro
./hello_intro
```

### C99版
```bash
gcc -Wall -Wextra -pedantic -std=c99 hello_intro_c99.c -o hello_intro_c99
./hello_intro_c99
```

### Makefileを使用
```bash
make all           # 全ての解答例をコンパイル
make clean         # 実行ファイルを削除
make run-hello     # hello_introを実行
```

## 学習のポイント

1. **基本的な出力**: printf文の正しい使い方を習得
2. **変数の扱い**: 各種データ型の特徴を理解
3. **入力処理**: scanf関数の安全な使用方法
4. **書式指定**: 適切なフォーマット指定子の選択
5. **エラー処理**: 基本的な入力検証の考え方

## 注意事項

- すべての解答例は教育目的で作成されています
- 実際の開発では、より厳密なエラーハンドリングが必要です
- C90版を基本として学習し、C99版で現代的な書き方を確認してください

## 次のステップ

この章をマスターしたら、次は以下の章に進みましょう。
- [第3章: データ型と演算子](../data-types/)
- [第4章: 制御構造（条件分岐）](../control-if/)