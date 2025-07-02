# 第1章 演習問題: 導入・環境構築

## 演習の目的

この演習を通して、C言語の開発環境が正しく構築されているかを確認し、基本的なコンパイル手順を習得します。

## 基礎問題

### 問題1-1: 環境構築確認
サンプルプログラム `examples/environment_check.c` を使用して、以下の作業を実行してください。

1. **C90準拠でコンパイル・実行**
   ```bash
   make c90
   ```

2. **C99準拠でコンパイル・実行**
   ```bash
   make c99
   ```

3. **C11準拠でコンパイル・実行**
   ```bash
   make c11
   ```

4. **C17準拠でコンパイル・実行**
   ```bash
   make c17
   ```

5. **実行結果の確認**
   - 各規格でコンパイルしたプログラムの出力結果を比較してください
   - 規格による違いがあるかを確認してください

**期待される出力例:**
```
環境チェックプログラム
==================
コンパイラ: GCC
C規格: C90
ポインタサイズ: 8 bytes
int型サイズ: 4 bytes
long型サイズ: 8 bytes
環境チェック完了
```

### 問題1-2: コンパイラ情報の確認
以下のコマンドを実行して、開発環境の情報を調べてください。

1. **コンパイラバージョンの確認**
   ```bash
   gcc --version
   ```
   
   **出力例:**
   ```
   gcc (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0
   Copyright (C) 2021 Free Software Foundation, Inc.
   ```

2. **対応規格の確認**
   ```bash
   gcc -std=c90 --help
   gcc -std=c99 --help
   gcc -std=c11 --help
   gcc -std=c17 --help
   ```

3. **プリプロセッサマクロの確認**
   ```bash
   echo | gcc -dM -E -
   ```

### 問題1-3: 基本的なプログラム作成
`solutions/ex1_3_hello_name.c` というファイルを作成し、以下の機能を実装してください。

**要求仕様**

- ユーザーに名前の入力を求める
- 入力された名前を使って挨拶メッセージを表示する
- C90準拠で記述する

**実行例:**

```
あなたの名前を入力してください: 田中
こんにちは、田中さん！
```

**追加の出力例:**

```
あなたの名前を入力してください: Alice
こんにちは、Aliceさん！
```

## 応用問題

### 問題1-4: 規格比較レポート
C90とC99の主な違いについて調べ、以下の点についてまとめてください。

1. **新しく追加されたデータ型**

2. **新しく追加された機能**

3. **プログラムの書き方で変わった点**

4. **組込み開発でC90が使われ続ける理由**

回答は `exercises/standards_comparison.md` に記述してください。

### 問題1-5: コンパイル手順の詳細調査
以下のコンパイラオプションを使用して、コンパイル過程を段階的に確認してください。

1. **プリプロセッサ出力の確認**
   ```bash
   gcc -E examples/environment_check.c > preprocessed.i
   ```

2. **アセンブリコード生成**
   ```bash
   gcc -S examples/environment_check.c
   ```

3. **オブジェクトファイル生成**
   ```bash
   gcc -c examples/environment_check.c
   ```

4. **実行ファイル生成**
   ```bash
   gcc environment_check.o -o environment_check
   ```

各段階で生成されるファイルの内容を確認し、`exercises/compilation_report.md` にまとめてください。

### 問題1-6: 環境固有情報の調査
以下の情報を調べて、`solutions/ex1_6_system_info.c` プログラムを作成してください。

**表示する情報**

- 使用しているOS
- コンパイラの種類とバージョン
- CPUアーキテクチャ（32bit/64bit）
- エンディアン（ビッグエンディアン/リトルエンディアン）
- 各データ型のサイズ

**期待される出力例:**

```
=== システム情報 ===
OS: Linux
コンパイラ: GCC 11.4.0
アーキテクチャ: 64bit
エンディアン: リトルエンディアン

=== データ型のサイズ ===
char: 1 bytes
short: 2 bytes
int: 4 bytes
long: 8 bytes
long long: 8 bytes
float: 4 bytes
double: 8 bytes
ポインタ: 8 bytes
```

## チャレンジ問題

### 問題1-7: マルチ規格対応プログラム
以下の要件を満たすプログラムを作成してください。

**要求仕様**

- C90、C99、C11で異なる動作をするプログラム
- プリプロセッサマクロを使って規格を判定
- 各規格で追加された機能を実際に使用
- 規格による違いを分かりやすく表示

**実装例**

- C90: 基本的な機能のみ
- C99: 可変長配列、inline関数を使用
- C11: _Generic、_Static_assertを使用

**期待される出力例:**

```
=== C規格判定プログラム ===

検出されたC規格: C11

使用可能な機能:
✓ 基本的なC言語機能
✓ C99の機能（可変長配列、inline関数）
✓ C11の機能（_Generic、_Static_assert）

機能デモ:
配列サイズ 5 の可変長配列を作成しました
_Generic による型判定: 整数型です
_Static_assert によるコンパイル時チェック: OK
```

### 問題1-8: 自動環境診断ツール
開発環境を自動診断するツールを作成してください。

**診断項目**

- コンパイラの種類と詳細バージョン
- 対応している全てのC言語規格
- システム情報（OS、アーキテクチャ、エンディアン）
- 標準ライブラリのバージョン
- 警告レベルごとのコンパイル結果

**出力形式**

- HTMLまたはMarkdown形式のレポート生成
- 問題がある場合は推奨対策を表示

**期待される出力例（コンソール）:**
```
環境診断ツール v1.0
===================

診断を開始します...

[✓] コンパイラチェック
    GCC 11.4.0 が検出されました
    
[✓] C規格サポート
    C90: 対応
    C99: 対応
    C11: 対応
    C17: 対応
    C23: 部分対応
    
[✓] システム情報
    OS: Linux 5.15.0
    アーキテクチャ: x86_64
    エンディアン: Little Endian
    
[!] 警告レベルテスト
    -Wall: 警告なし
    -Wextra: 警告なし
    -pedantic: 1個の警告
    
診断完了
レポートを report.html に保存しました
```

## 提出形式

各問題の回答は以下のファイルに記述してください。

- **問題1-3**: `solutions/ex1_3_hello_name.c`
- **問題1-4**: `exercises/standards_comparison.md`
- **問題1-5**: `exercises/compilation_report.md`
- **問題1-6**: `solutions/ex1_6_system_info.c`
- **問題1-7**: `solutions/ex1_7_multi_standard.c`
- **問題1-8**: `solutions/ex1_8_env_diagnostic.c`

## 参考資料

- [GCC公式ドキュメント](https://gcc.gnu.org/documentation.html)
- [C言語規格書](https://www.iso.org/standard/74528.html)
- [GNU Make マニュアル](https://www.gnu.org/software/make/manual/)

## 次の章へ

演習問題お疲れさまでした！次は[第2章: 基本文法・Hello World](../../basics-syntax/)に進みましょう。