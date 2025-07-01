#  C言語学習教材

C言語の基礎から応用まで、体系的に学習できる教材です。マイコン開発を見据えたビット操作も含め、実践的なプログラミングスキルを身につけることができます。

##  対応C規格

本教材は以下のC言語規格に対応しています：

- **C90** (ANSI C): 基本的な文法とライブラリ
- **C99**: _Bool型、可変長配列、forループ内宣言など
- **C11**: 匿名構造体、_Generic選択、_Static_assertなど  
- **C17**: C11の不具合修正版
- **C23**: bool型標準化、typeof演算子、nullptr、2進数リテラルなど（オプション章）

## プロジェクト構成

```
c-language-tutorial/
├── src/                  # ソースコード（教材本体）
│   ├── introduction/     # 第1章: 導入・環境構築
│   ├── basics-syntax/    # 第2章: 基本文法・Hello World
│   ├── data-types/       # 第3章: データ型と変数
│   ├── operators/        # 第4章: 演算子
│   ├── control-if/       # 第5章: 制御構造（条件分岐）
│   ├── control-loop/     # 第6章: 制御構造（ループ）
│   ├── arrays-basics/    # 第7章: 配列（基本編）
│   ├── pointers/         # 第8章: ポインタ基礎
│   ├── arrays-pointers/  # 第9章: 配列とポインタ
│   ├── strings/          # 第10章: 文字列処理
│   ├── functions/        # 第11章: 関数
│   ├── bit-operations/   # 第12章: ビット操作とビットフィールド
│   ├── structures/       # 第13章: 構造体とポインタ
│   ├── function-pointers/# 第14章: 関数ポインタ
│   ├── advanced/         # 第15章: 複数ファイル・発展技術
│   └── c23-features/     # 第16章: C23の新機能（オプション）
├── scripts/              # 支援スクリプト
│   ├── create_main_textbook_basic.sh     # 基礎編テキスト生成
│   ├── create_main_textbook_intermediate.sh # 応用編テキスト生成
│   ├── create_main_textbook_advanced.sh  # 上級編テキスト生成
│   ├── create_exercises_basic.sh         # 基礎編演習問題集生成
│   ├── create_exercises_intermediate.sh  # 応用編演習問題集生成
│   ├── create_exercises_advanced.sh      # 上級編演習問題集生成
│   ├── test_all_builds.py               # 全章ビルドテスト
│   └── run_cppcheck.sh                  # 静的解析
├── output/               # 生成されたWord文書
│   └── word/
│       ├── C言語プログラミング教材_メインテキスト_基礎編.docx
│       ├── C言語プログラミング教材_メインテキスト_応用編.docx
│       ├── C言語プログラミング教材_メインテキスト_上級編.docx
│       ├── C言語プログラミング教材_演習問題集_基礎編.docx
│       ├── C言語プログラミング教材_演習問題集_応用編.docx
│       └── C言語プログラミング教材_演習問題集_上級編.docx
├── docs/                 # 中間ドキュメント（Markdown）
├── templates/            # Word文書テンプレート
├── README.md
├── CLAUDE.md
└── .gitignore
```

##  教材構成

### 初心者レベル（基礎編）
プログラミング初心者対象、基本概念から制御構造まで

| 章 | タイトル | 主要な学習内容 | 対象規格 |
|---|---------|---------------|---------|
| 1 | [導入・環境構築](src/introduction/README.md) | C言語とは、開発環境構築、規格解説 | 全規格 |
| 2 | [基本文法・Hello World](src/basics-syntax/README.md) | プログラム構造、printf関数 | C90 |
| 3 | [データ型と変数](src/data-types/README.md) | 基本データ型、変数宣言、スコープ、生存期間 | C90/C99 |
| 4 | [演算子](src/operators/README.md) | 算術・比較・論理・ビット演算子 | C90 |
| 5 | [制御構造（条件分岐）](src/control-if/README.md) | if文、else if文、switch文 | C90 |
| 6 | [制御構造（ループ）](src/control-loop/README.md) | for文、while文、do-while文、break/continue | C90/C99 |

### 中級レベル（応用編）
配列、ポインタ、文字列、関数

| 章 | タイトル | 主要な学習内容 | 対象規格 |
|---|---------|---------------|---------|
| 7 | [配列（基本編）](src/arrays-basics/README.md) | 配列宣言、初期化、多次元配列、基本操作 | C90/C99 |
| 8 | [ポインタ基礎](src/pointers/README.md) | アドレス、間接参照、ポインタ演算 | C90 |
| 9 | [配列とポインタ](src/arrays-pointers/README.md) | 配列とポインタの関係、関数への配列渡し | C90 |
| 10 | [文字列処理](src/strings/README.md) | 文字配列、文字列関数、文字列操作 | C90 |
| 11 | [関数](src/functions/README.md) | 関数定義、引数、戻り値、再帰関数 | C90/C99 |

### 発展レベル（上級編）
構造体、ビット操作、関数ポインタ、応用技術

| 章 | タイトル | 主要な学習内容 | 対象規格 |
|---|---------|---------------|---------|
| 12 | [ビット操作とビットフィールド](src/bit-operations/README.md) | ビット演算、ビットマスク、ビットフィールド | C90 |
| 13 | [構造体とポインタ](src/structures/README.md) | 構造体定義、構造体ポインタ | C90/C11 |
| 14 | [関数ポインタ](src/function-pointers/README.md) | 関数ポインタ、コールバック関数 | C90 |
| 15 | [複数ファイル・発展技術](src/advanced/README.md) | 分割コンパイル、extern宣言、プリプロセッサ | C90/C99/C11/C17 |

### オプション（最新規格）
C23対応コンパイラが利用可能な場合

| 章 | タイトル | 主要な学習内容 | 対象規格 |
|---|---------|---------------|---------|
| 16 | [C23の新機能](src/c23-features/README.md) | bool型、typeof、nullptr、2進数リテラル | C23 |

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

1. **README\.md** で理論を学習
2. **examples/** でサンプルコードを確認・実行
3. **exercises/** で演習課題に挑戦
4. **solutions/** で解答例を確認

##  コンパイル方法

対応する章には規格別のMakefileが用意されています。

### 基本的なコンパイル
```bash
# 各章のディレクトリで実行
cd src/章のディレクトリ
make all          # すべてのサンプルをコンパイル
make run-all      # コンパイル後に実行
make clean        # 生成ファイルを削除
```

### C規格を指定したコンパイル
```bash
make clean && make STANDARD=c90
make clean && make STANDARD=c99
make clean && make STANDARD=c11
make clean && make STANDARD=c17
# C23（第14章専用、コンパイラサポート必要）
cd src/c23-features && make all
```

### 手動コンパイル
```bash
gcc -Wall -Wextra -pedantic -std=c90 ファイル名.c -o 実行ファイル名
```

## 生成済みドキュメント

output/word/ディレクトリに以下のWord文書が含まれています：

### メインテキスト（3分冊）
- **C言語プログラミング教材_メインテキスト_基礎編.docx** - 第1章〜第6章（導入〜ループ）
- **C言語プログラミング教材_メインテキスト_応用編.docx** - 第7章〜第11章（配列〜関数）
- **C言語プログラミング教材_メインテキスト_上級編.docx** - 第12章〜第16章（ビット操作〜C23）

### 演習問題集（3分冊）
- **C言語プログラミング教材_演習問題集_基礎編.docx** - 第1章〜第6章の演習問題
- **C言語プログラミング教材_演習問題集_応用編.docx** - 第7章〜第11章の演習問題
- **C言語プログラミング教材_演習問題集_上級編.docx** - 第12章〜第16章の演習問題

### 文書生成方法
```bash
cd scripts
# すべての文書を一括生成
./create_main_textbook_basic.sh && ./create_main_textbook_intermediate.sh && ./create_main_textbook_advanced.sh
./create_exercises_basic.sh && ./create_exercises_intermediate.sh && ./create_exercises_advanced.sh

# 個別生成
./create_main_textbook_basic.sh      # 基礎編テキスト
./create_exercises_basic.sh          # 基礎編演習問題集
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

1. **標準パス（推奨）**: introduction → basics-syntax → data-types → operators → control-if → control-loop → arrays-basics → pointers → arrays-pointers → strings → functions → bit-operations → structures → function-pointers → advanced

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
- [ ] arrays-basics: 配列の基本操作
- [ ] pointers: ポインタの基本理解
- [ ] arrays-pointers: 配列とポインタの関係
- [ ] strings: 文字列処理の理解
- [ ] functions: 関数の作成と使用
- [ ] bit-operations: ビット操作の習得
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

## トラブルシューティング

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
