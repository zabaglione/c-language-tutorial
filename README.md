#  C言語学習教材

C言語の基礎から応用まで、体系的に学習できる教材です。マイコン開発を見据えたビット操作も含め、実践的なプログラミングスキルを身につけることができます。

##  対応C規格

本教材は以下のC言語規格に対応しています：

- **C90** (ANSI C): 基本的な文法とライブラリ
- **C99**: _Bool型、可変長配列、forループ内宣言など
- **C11**: 匿名構造体、_Generic選択、_Static_assertなど  
- **C17**: C11の不具合修正版

## 📁 教材構成

### 🟢 初心者レベル（基礎編）
プログラミング初心者対象、基本概念から制御構造まで

| 章 | タイトル | 主要な学習内容 | 対象規格 |
|---|---------|---------------|---------|
|  | [導入・環境構築](introduction/README.md) | C言語とは、開発環境構築、規格解説 | 全規格 |
|  | [基本文法・Hello World](basics-syntax/README.md) | プログラム構造、printf関数 | C90 |
|  | [データ型と変数](data-types/README.md) | 基本データ型、変数宣言、スコープ、生存期間 | C90/C99 |
|  | [演算子](operators/README.md) | 算術・比較・論理・ビット演算子 | C90 |
|  | [制御構造（条件分岐）](control-if/README.md) | if文、else if文、switch文 | C90 |
|  | [制御構造（ループ）](control-loop/README.md) | for文、while文、do-while文、break/continue | C90/C99 |

### 🟡 中級レベル（応用編）
配列、文字列、関数、ポインタ

| 章 | タイトル | 主要な学習内容 | 対象規格 |
|---|---------|---------------|---------|
|  | [配列](arrays/README.md) | 配列宣言、初期化、多次元配列、文字列配列 | C90/C99 |
|  | [文字列処理](strings/README.md) | 文字配列、文字列関数、文字列配列操作 | C90 |
|  | [関数](functions/README.md) | 関数定義、引数、戻り値、再帰関数 | C90/C99 |
| 9 | [ポインタ基礎](pointers/README.md) | アドレス、間接参照、配列とポインタ | C90 |

### 🔴 発展レベル（上級編）
構造体、ファイル処理、応用技術

| 章 | タイトル | 主要な学習内容 | 対象規格 |
|---|---------|---------------|---------|
|  | [構造体とポインタ](structures/README.md) | 構造体定義、構造体ポインタ | C90/C11 |
|  | [関数ポインタ](function-pointers/README.md) | 関数ポインタ、コールバック関数 | C90 |
|  | [複数ファイル・発展技術](advanced/README.md) | 分割コンパイル、extern宣言、プリプロセッサ | C90/C99/C11/C17 |

##  開発環境

### 必要なソフトウェア

- **コンパイラ**: GCC 4.9以降またはClang 3.4以降
- **ビルドツール**: GNU Make
- **エディター**: 任意（Visual Studio Code、Vim、Emacsなど）

### インストール確認

```bash
# コンパイラバージョン確認
gcc --version

# Makeツール確認  
make --version
```

### 各章での学習方法

1. **README.md** で理論を学習
2. **examples/** でサンプルコードを確認・実行
3. **exercises/** で演習課題に挑戦
4. **solutions/** で解答例を確認

##  コンパイル方法

対応する章には規格別のMakefileが用意されています。

### 基本的なコンパイル
```bash
# 各章のディレクトリで実行
cd 章のディレクトリ
make all          # すべてのサンプルをコンパイル
make run-all      # コンパイル後に実行
make clean        # 生成ファイルを削除
```

### C規格を指定したコンパイル
```bash
make clean && make STANDARD=c90
make clean && make STANDARD=c99
make clean && make STANDARD=c11
```

### 手動コンパイル
```bash
gcc -Wall -Wextra -pedantic -std=c90 ファイル名.c -o 実行ファイル名
```

##  学習目標

### 初心者レベル完了時
- C言語の基本文法を理解
- 簡単なプログラムを作成可能
- 配列と関数を使った処理が書ける

### 中級レベル完了時  
- ポインターを理解し活用可能
- 構造体を使ったデータ管理ができる
- ビット操作でハードウェア制御が理解できる

### 発展レベル完了時
- メモリ管理を理解
- 大規模なプログラム開発の基礎を習得
- C言語の高度な機能を活用可能

##  学習順序の推奨

###  学習パス

1. **標準パス（推奨）**: introduction → basics-syntax → data-types → operators → control-if → control-loop → arrays → strings → functions → pointers → structures → function-pointers → advanced

2. **復習重点パス**: 基礎が不安な場合は introduction〜control-loop を繰り返し学習

3. **応用重点パス**: 経験者は functions 以降を重点的に

###  各章の推定学習時間
- **基礎編**: 各章 2-3時間（理論1時間 + 実習1-2時間）
- **応用編**: 各章 3-4時間（理論1時間 + 実習2-3時間）  
- **上級編**: 各章 4-5時間（理論2時間 + 実習2-3時間）

###  効果的な学習方法
1. 各章のREADME.mdで理論を理解
2. examples/のコードを実際に動かして確認
3. exercises/の課題に取り組む
4. solutions/で解答を確認し、理解を深める

##  学習進捗管理

各章の学習完了後、以下をチェックしてください：

- [ ] introduction: 環境構築完了
- [ ] basics-syntax: Hello Worldプログラム作成
- [ ] data-types: 各データ型の理解
- [ ] operators: 演算子の正しい使用
- [ ] control-if: 条件分岐の実装
- [ ] control-loop: ループ処理の実装
- [ ] arrays: 配列操作の習得
- [ ] strings: 文字列処理の理解
- [ ] functions: 関数の作成と使用
- [ ] pointers: ポインタの基本理解
- [ ] structures: 構造体の活用
- [ ] function-pointers: 関数ポインタの使用
- [ ] advanced: 高度な技術の理解

##  関連リンク

###  公式ドキュメント
- [C言語規格書](https://www.iso.org/standard/74528.html) (ISO/IEC 9899:2018)
- [GCC公式ドキュメント](https://gcc.gnu.org/documentation.html)
- [GNU Make マニュアル](https://www.gnu.org/software/make/manual/)

###  開発ツール
- [Visual Studio Code](https://code.visualstudio.com/) - 推奨エディタ
- [Online GDB](https://www.onlinegdb.com/) - オンラインコンパイラ
- [Compiler Explorer](https://godbolt.org/) - コンパイル結果確認

## 🆘 トラブルシューティング

### よくある問題と解決方法

**コンパイルエラーが発生する場合:**
- C90準拠のコンパイラを使用しているか確認
- 変数は関数の先頭で宣言されているか確認
- セミコロンやブレースの対応を確認

**プログラムが期待通りに動作しない場合:**
- printf文でデバッグ出力を追加
- 変数の値を段階的に確認
- examples/のサンプルコードと比較

**学習で困った場合:**
- 前の章に戻って基礎を復習
- サンプルコードを模写して理解を深める
- 演習問題を段階的に解く

##  ライセンス

この教材は教育目的での利用を前提としています。
商用利用については別途ご相談ください。
