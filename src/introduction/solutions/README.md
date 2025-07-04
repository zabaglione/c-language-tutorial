# 第1章 はじめに - 演習解答例

この章では、C言語の開発環境構築の確認と基本的なプログラムの作成練習を行いました。

## 解答ファイル一覧

### 問題3: 基本的なプログラム作成
ユーザーに名前の入力を求め、挨拶メッセージを表示するプログラムです。

- [ex1_3_hello_name.c](ex1_3_hello_name.c) - C90準拠版
- [ex1_3_hello_name_c99.c](ex1_3_hello_name_c99.c) - C99準拠版（//コメント、変数宣言位置の自由化）

**学習ポイント:**
- 標準入出力（printf、scanf）の基本的な使い方
- 文字配列（文字列）の扱い方
- 入力エラーの処理
- C90とC99のコーディングスタイルの違い

### 問題6: システム情報調査プログラム
実行環境の詳細情報を調査・表示するプログラムです。

- [ex1_6_system_info.c](ex1_6_system_info.c) - C90準拠版
- [ex1_6_system_info_c99.c](ex1_6_system_info_c99.c) - C99準拠版（bool型、stdint.h、複合リテラル使用）

**学習ポイント:**
- プリプロセッサディレクティブによる条件コンパイル
- エンディアン判定の実装方法
- データ型のサイズとlimits.hの使用
- C99で追加された機能の確認方法

## コンパイルと実行

各解答例は以下のようにコンパイルできます。

```bash
# C90版のコンパイル例
gcc -Wall -Wextra -pedantic -std=c90 ex1_3_hello_name.c -o ex1_3_hello_name

# C99版のコンパイル例
gcc -Wall -Wextra -pedantic -std=c99 ex1_3_hello_name_c99.c -o ex1_3_hello_name_c99

# 実行
./ex1_3_hello_name
```

親ディレクトリのMakefileを使用する場合。

```bash
# すべての解答例をコンパイル
make solutions

# 個別にコンパイル
make ex1_3_hello_name
make ex1_6_system_info_c99

# 実行
make run-ex1_3_hello_name
```

## 学習のポイント

### 1. C90とC99の主な違い

各解答例にはC90版とC99版の両方を用意しています。主な違いは。

- **コメント**: C90は`/* */`のみ、C99は`//`も使用可能
- **変数宣言**: C90は関数の先頭、C99は使用箇所で宣言可能
- **新しい型**: C99では`bool`、`long long`、`stdint.h`の固定幅整数型が追加
- **その他**: 可変長配列、複合リテラル、designated initializerなど

### 2. 入力処理の安全性

`ex1_3_hello_name.c`では、バッファオーバーフローを防ぐため。
```c
scanf("%99s", name);  /* 最大99文字に制限 */
```

### 3. システム情報の取得方法

`ex1_6_system_info.c`では、以下の技術を使用。
- **エンディアン判定**: unionを使用したバイト順の確認
- **アーキテクチャ判定**: ポインタサイズによる判定
- **OS判定**: プリプロセッサマクロの利用
- **コンパイラ判定**: コンパイラ固有のマクロ

### 4. エラー処理の重要性

すべてのプログラムで適切なエラー処理を実装。
- 入力エラーのチェック
- 戻り値による状態の通知
- エラーメッセージの表示

## 発展的な学習

これらの基本的な実装を理解したら、以下に挑戦してみましょう。

1. **入力の拡張**: 複数の単語を含む名前の入力（fgetsの使用）
2. **国際化**: 日本語以外の言語への対応
3. **クロスプラットフォーム**: より多くのOSやコンパイラへの対応
4. **ビルドシステム**: CMakeなどの高度なビルドツールの使用

## 注意事項

- 実装例はあくまで一例です。他の実装方法も検討してみましょう
- 実際のプロジェクトでは、より堅牢なエラー処理が必要です
- システム固有の情報は環境によって異なる結果となります