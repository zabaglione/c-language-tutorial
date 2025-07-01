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

### 1. C言語の概要
- C言語とは何か
- C言語の特徴と利点
- C言語の歴史
- プログラムの実行過程

### 2. 初めてのプログラム
- Hello Worldプログラム
- プログラムの構成要素
- コンパイルと実行
- 基本的な出力

### 3. 変数と型
- 変数とは何か
- 基本的なデータ型
- 変数の宣言と初期化
- 定数の使用

### 4. 演算子
- 算術演算子
- 代入演算子
- 比較演算子
- 論理演算子
- 演算子の優先順位

## 実践的なプログラム例
基礎理論を理解したら、[基本文法・Hello World章](../basics-syntax/README.md)で実際のソースコードを使った学習に進んでください。

### 基本的なプログラム構造

#### Hello Worldプログラムの基本構造
```c
#include <stdio.h>

int main(void)
{
    printf("Hello, World!\n");
    return 0;
}
```

#### 変数の基本使用例
```c
#include <stdio.h>

int main(void)
{
    int age = 25;
    float height = 170.5f;
    char grade = 'A';
    
    printf("年齢: %d歳\n", age);
    printf("身長: %.1fcm\n", height);
    printf("成績: %c\n", grade);
    
    return 0;
}
```

## 学習フローとコンパイル方法

### 推奨学習順序
1. **理論学習**: README.mdで基本概念を理解
2. **サンプルコード**: examples/の基本例を確認
3. **演習課題**: exercises/README.mdで課題を確認
4. **実装練習**: solutions/の解答例を参考に自分で実装

### 実践的な学習方法
1. **段階的な学習**: 一度にすべてを理解しようとせず、一つずつ確実に
2. **実際に書く**: 読むだけでなく、必ず自分でコードを書いて実行
3. **エラーを恐れない**: エラーはプログラミング学習の一部
4. **反復練習**: 同じ内容を何度も練習することで定着

### 効果的な学習方法
1. **コメントを書く習慣**: 自分の理解を確認
2. **小さな変更を試す**: プログラムを少しずつ変更して動作を確認
3. **エラーメッセージを読む**: エラーから学ぶ姿勢
4. **他の人のコードを読む**: 様々な書き方を学習

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

## 実例コード
完全な実装例は以下のファイルを参照してください：

### 基本的なプログラム例
- [hello_world.c](examples/hello_world.c) - C90準拠版
- [hello_world_c99.c](examples/hello_world_c99.c) - C99準拠版

### 変数とデータ型の例
- [variables_demo.c](examples/variables_demo.c) - C90準拠版
- [variables_demo_c99.c](examples/variables_demo_c99.c) - C99準拠版

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
- 💻 **実践学習**: [basics-syntax章](../basics-syntax/)
- 📝 **演習問題**: [basics-syntax演習](../basics-syntax/exercises/)
- ✅ **解答例**: [basics-syntax解答](../basics-syntax/solutions/)

---
**重要**: プログラミングは実践が最も重要です。理論だけでなく、必ず手を動かしてコードを書いてください。