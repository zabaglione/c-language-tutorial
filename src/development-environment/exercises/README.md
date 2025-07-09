# 開発環境の詳細設定 - 演習問題

## 演習の目的

開発環境の詳細な設定と診断、コンパイル過程の理解を深めます。

## 基礎問題

### 問題1: 環境情報の確認

`examples/environment_check.c` を各C規格でコンパイルして実行し、結果を比較してください。

```bash

# C90準拠

gcc -std=c90 -pedantic environment_check.c -o check_c90
./check_c90

# C99準拠

gcc -std=c99 -pedantic environment_check.c -o check_c99
./check_c99

# C11準拠

gcc -std=c11 -pedantic environment_check.c -o check_c11
./check_c11
```

### 問題2: コンパイル過程の確認

以下のコマンドで各段階の出力を確認してください。

```bash

# プリプロセッサ出力

gcc -E examples/compiler_test.c > preprocessed.i

# アセンブリコード

gcc -S examples/compiler_test.c

# オブジェクトファイル

gcc -c examples/compiler_test.c

# 最終的な実行ファイル

gcc compiler_test.o -o compiler_test
```

## 応用問題

### 問題3: 環境診断ツールの作成

`solutions/env_diagnostic.c` を作成し、以下の情報を表示するプログラムを作成してください。

**表示項目:**

- コンパイラーの種類とバージョン
- C規格のバージョン
- システムのエンディアン
- 各データ型のサイズと範囲
- ポインターのサイズ（32bit/64bit判定）

### 問題4: コンパイラーオプションの比較

同じプログラムを異なるオプションでコンパイルし、違いを確認してください。

```bash

# 最適化なし

gcc -O0 test.c -o test_O0

# 最適化レベル2

gcc -O2 test.c -o test_O2

# サイズ最適化

gcc -Os test.c -o test_Os

# ファイルサイズを比較

ls -l test_*
```

## チャレンジ問題

### 問題5: マルチ規格対応プログラム

異なるC規格で異なる動作をするプログラムを作成してください。

**要求仕様:**

- プリプロセッサマクロで規格を判定
- 各規格特有の機能を使用
- 実行時に使用している規格を表示

### 問題6: 包括的環境レポート生成ツール

開発環境の完全なレポートを生成するツールを作成してください。

**機能要件:**

- HTMLまたはMarkdown形式でレポート出力
- 問題がある場合は警告と対処法を表示
- 推奨される設定を提案

## 参考資料

- [GCC公式ドキュメント](https://gcc.gnu.org/documentation.html)
- [Clang公式ドキュメント](https://clang.llvm.org/docs/)
- [GNU Make マニュアル](https://www.gnu.org/software/make/manual/)

## 次の章へ

演習問題お疲れさまでした！メインの学習に戻りましょう。
