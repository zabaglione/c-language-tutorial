# C言語の基礎

## 概要

この章では、C言語プログラミングの基礎概念を学習します。プログラミング初心者の方でも理解できるよう、段階的に説明していきます。

## 学習目標

この章を完了すると、以下の内容を習得できます：

- C言語の歴史と特徴の理解
- 基本的なプログラムの作成と実行
- 変数と基本的なデータ型の使用
- 基本的な演算子の使用
- 入力と出力の基本操作

## 学習内容

### 1. [C言語の概要](lessons/introduction.md)
- C言語とは何か
- C言語の特徴と利点
- C言語の歴史
- プログラムの実行過程

### 2. [初めてのプログラム](lessons/hello-world.md)
- Hello Worldプログラム
- プログラムの構成要素
- コンパイルと実行
- 基本的な出力

### 3. [変数と型](lessons/variables.md)
- 変数とは何か
- 基本的なデータ型
- 変数の宣言と初期化
- 定数の使用

### 4. [演算子](lessons/operators.md)
- 算術演算子
- 代入演算子
- 比較演算子
- 論理演算子
- 演算子の優先順位

## 実践的なプログラム例

基礎理論を理解したら、[基本文法・Hello World章](../basics-syntax/README.md)で実際のソースコードを使った学習に進んでください。

### ソースコード例（C90準拠）

#### Hello Worldプログラム
```c
/*
 * ファイル名: hello_world.c
 * 説明: C言語の最も基本的なプログラム
 * 規格: C90準拠
 */

#include <stdio.h>

int main(void)
{
    printf("Hello, World!\n");
    return 0;
}
```
📁 **ファイル**: [`../basics-syntax/examples/hello_world.c`](../basics-syntax/examples/hello_world.c)  
📁 **C99版**: [`../basics-syntax/examples/hello_world_c99.c`](../basics-syntax/examples/hello_world_c99.c)

#### フォーマット出力プログラム
```c
/*
 * ファイル名: formatted_output.c
 * 説明: printf関数のさまざまなフォーマット指定子を学習
 * 規格: C90準拠
 */

#include <stdio.h>

int main(void)
{
    /* 基本的な文字列出力 */
    printf("=== C言語フォーマット出力 ===\n");

    /* 整数の出力 */
    printf("整数: %d\n", 42);
    printf("負の整数: %d\n", -123);

    /* 文字の出力 */
    printf("文字: %c\n", 'A');
    printf("文字コード: %c\n", 65); /* Aのアスキーコード */

    /* 文字列の出力 */
    printf("文字列: %s\n", "Hello, World!");

    /* 浮動小数点数の出力 */
    printf("浮動小数点数: %f\n", 3.14159);
    printf("小数点以下2桁: %.2f\n", 3.14159);

    /* エスケープシーケンスの使用 */
    printf("\n--- エスケープシーケンス ---\n");
    printf("改行\nとタブ\tの使用例：\n");
    printf("項目1\t項目2\t項目3\n");
    printf("値A\t値B\t値C\n");

    /* 特殊文字の表示 */
    printf("\n--- 特殊文字の表示 ---\n");
    printf("ダブルクォート: \"Hello\"\n");
    printf("バックスラッシュ: C:\\Program Files\\\n");

    /* フォーマット指定子の組み合わせ */
    printf("\n--- 複合表示 ---\n");
    printf("名前: %s, 年齢: %d歳, 身長: %.1fcm\n", "田中太郎", 25, 175.5);

    return 0;
}
```
📁 **ファイル**: [`../basics-syntax/examples/formatted_output.c`](../basics-syntax/examples/formatted_output.c)  
📁 **C99版**: [`../basics-syntax/examples/formatted_output_c99.c`](../basics-syntax/examples/formatted_output_c99.c)

## 演習課題

### 理論学習用演習
[基礎演習課題集](exercises/exercises.md)では、各概念を実際に使用して練習できます。

### 実践的なプログラミング演習
[基本文法・Hello World章の演習](../basics-syntax/exercises/README.md)では、より具体的なプログラム作成課題があります。

#### 実践演習の例（C90準拠）

**課題1-1: 基本的な出力**
```c
/*
 * 課題1-1の解答例: 基本的な出力
 * ファイル名: hello_intro.c
 * 説明: printf関数とエスケープシーケンスの基本的な使用
 */

#include <stdio.h>

int main(void)
{
    /* 基本的な文字列出力 */
    printf("こんにちは、C言語の世界へ！\n");
    printf("私の名前は 田中太郎 です。\n");
    printf("今日からプログラミングを始めます。\n");
    
    return 0;
}
```
📁 **解答例**: [`../basics-syntax/solutions/hello_intro.c`](../basics-syntax/solutions/hello_intro.c)  
📁 **C99版**: [`../basics-syntax/solutions/hello_intro_c99.c`](../basics-syntax/solutions/hello_intro_c99.c)

**課題1-2: 変数と基本データ型**
```c
/*
 * 課題1-2の解答例: 変数と基本データ型
 * ファイル名: personal_data.c
 * 説明: 基本データ型の変数宣言、初期化、書式指定子の使用
 */

#include <stdio.h>

int main(void)
{
    /* 変数の宣言と初期化 */
    int age = 25;           /* 年齢（整数） */
    float height = 170.5f;  /* 身長（浮動小数点数） */
    char blood_type = 'A';  /* 血液型（文字） */
    int favorite_number = 7; /* 好きな数字（整数） */
    
    /* 自己紹介データの表示 */
    printf("=== 自己紹介データ ===\n");
    printf("年齢: %d歳\n", age);
    printf("身長: %.1fcm\n", height);
    printf("血液型: %c型\n", blood_type);
    printf("好きな数字: %d\n", favorite_number);
    printf("================\n");
    
    return 0;
}
```
📁 **解答例**: [`../basics-syntax/solutions/personal_data.c`](../basics-syntax/solutions/personal_data.c)  
📁 **C99版**: [`../basics-syntax/solutions/personal_data_c99.c`](../basics-syntax/solutions/personal_data_c99.c)

### 利用可能な演習問題
1. **課題1-1**: 基本的な出力
2. **課題1-2**: 変数と基本データ型
3. **課題1-3**: 入力と出力
4. **課題1-4**: 書式指定子の練習
5. **課題1-5**: 簡単な計算機
6. **課題1-6**: 文字とASCIIコード

すべての演習には**C90版**と**C99版**の両方の解答例が提供されています。

## 学習のヒント

### プログラミング初心者の方へ
1. **段階的な学習**: 一度にすべてを理解しようとせず、一つずつ確実に
2. **実際に書く**: 読むだけでなく、必ず自分でコードを書いて実行
3. **エラーを恐れない**: エラーはプログラミング学習の一部
4. **反復練習**: 同じ内容を何度も練習することで定着

### 効果的な学習方法
1. **コメントを書く習慣**: 自分の理解を確認
2. **小さな変更を試す**: プログラムを少しずつ変更して動作を確認
3. **エラーメッセージを読む**: エラーから学ぶ姿勢
4. **他の人のコードを読む**: 様々な書き方を学習

### C90とC99の学習について
- **まずはC90版で学習**: 基本をしっかり理解
- **C99版で現代的な書き方を学習**: より読みやすいコードを体験
- **両方のファイルを比較**: 違いを理解することで理解が深まる

## 必要な環境

### 開発環境
- Cコンパイラ（gcc、clang、Visual Studio等）
- テキストエディタまたは統合開発環境（IDE）

### 推奨ツール
- **Windows**: Visual Studio Code + MinGW
- **macOS**: Xcode Command Line Tools
- **Linux**: gcc + お好みのエディタ

### コンパイル方法

#### 基本的なコンパイル（C90準拠）
```bash
gcc -std=c90 -Wall -Wextra -pedantic hello_world.c -o hello_world
```

#### Makefileを使用した場合
```bash
# basics-syntax章で利用可能
cd ../basics-syntax

# 全てのプログラムをコンパイル
make all

# 特定のプログラムをコンパイル
make hello_world

# C99版をコンパイル
make hello_world_c99

# プログラムを実行
make run          # C90版を実行
make run-c99      # C99版を実行

# クリーンアップ
make clean
```

## トラブルシューティング

### よくある問題
1. **コンパイルエラー**: 文法ミスやタイプミス
2. **実行時エラー**: 論理的な間違い
3. **環境問題**: コンパイラの設定やパス設定

解決方法は各レッスンで詳しく説明します。

### デバッグのコツ
- **段階的にコンパイル**: 少しずつコードを追加してテスト
- **basics-syntax章の解答例と比較**: 正しいコードと比べて違いを確認
- **C90とC99の違いに注意**: 適切な標準でコンパイルしているか確認

## 次のステップ

### 学習順序の推奨
1. **基礎理論** (このbasics章) ✅
2. **基本文法・Hello World** ([basics-syntax章](../basics-syntax/README.md)) ← 次はここ
3. **データ型と変数** ([data-types章](../data-types/README.md))
4. **演算子** ([operators章](../operators/README.md))
5. **制御構造** ([control-if章](../control-if/README.md), [control-loop章](../control-loop/README.md))
6. **配列** ([arrays章](../arrays/README.md))
7. **関数** ([functions章](../functions/README.md))
8. **ポインタ** ([pointers章](../pointers/README.md))

### C言語標準の違いについて
このチュートリアルでは**C90**を基準としていますが、各章でC99版のサンプルコードも提供しています：

- **C90版**: 従来の書き方、互換性重視
- **C99版**: 現代的な書き方、読みやすさ重視

## 参考資料

### 推奨書籍
- 『プログラミング言語C』（K&R本）- C言語の聖典
- 『新・明解C言語 入門編』- 初心者向け
- 『C言語本格入門』- より詳細な学習用

### オンライン資源
- [C言語リファレンス (cppreference)](https://ja.cppreference.com/w/c)
- [オンラインコンパイラ (Compiler Explorer)](https://godbolt.org/)
- [この教材のソースコード](../basics-syntax/)

### 実践的なリンク
- **基本文法の実習**: [basics-syntax章](../basics-syntax/README.md)
- **演習問題の解答**: [basics-syntax演習](../basics-syntax/exercises/README.md)
- **C90/C99の違い**: [basics-syntax Makefile](../basics-syntax/Makefile)

## サポート

学習中に疑問が生じた場合：
1. **エラーメッセージを詳しく読む**
2. **basics-syntax章の解答例を参照**
3. **C90版とC99版のコードを比較**
4. **小さな単位でテストする**
5. **関連するドキュメントを確認**
6. **オンラインコミュニティで質問**

### 便利なリンク集
- 📖 **理論学習**: [basics章lessons](lessons/)
- 💻 **実践学習**: [basics-syntax章](../basics-syntax/)
- 📝 **演習問題**: [basics-syntax演習](../basics-syntax/exercises/)
- ✅ **解答例**: [basics-syntax解答](../basics-syntax/solutions/)

---

**重要**: プログラミングは実践が最も重要です。理論だけでなく、必ず手を動かしてコードを書いてください。
