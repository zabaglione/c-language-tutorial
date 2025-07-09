# 開発環境の詳細設定

## 対応C規格

- **主要対象:** 全規格共通
- **学習内容:** 開発環境の詳細設定、環境診断、コンパイル過程の理解

## 学習目標

この章を完了すると、以下のことができるようになります。

- 開発環境の詳細な設定方法を理解する
- コンパイル過程の各段階を理解する
- 環境固有の情報を取得・確認できる
- トラブルシューティングができるようになる

## 開発環境の詳細

### 必須ツールの詳細

1. **テキストエディター**
   - Visual Studio Code（推奨）
   - Sublime Text
   - Atom
   - Vim/Emacs（上級者向け）

2. **コンパイラー**
   - GCC（GNU Compiler Collection）
   - Clang/LLVM
   - Microsoft Visual C++
   - Intel C++ Compiler

3. **デバッガー**
   - GDB（GNU Debugger）
   - LLDB（LLVM Debugger）
   - Visual Studio Debugger

4. **ビルドツール**
   - Make
   - CMake
   - Ninja

### OS別の詳細設定

#### Windows

**MinGW-w64の詳細設定:**

1. インストーラーのダウンロード
2. インストール時の設定：
   - Architecture: x86_64（64ビット版）
   - Threads: posix（C11スレッド対応）
   - Exception: seh（構造化例外処理）

3. 環境変数の設定：

   ```batch
   setx PATH "%PATH%;C:\mingw64\bin"
   ```

**Visual Studio Community:**

- C++開発ワークロードをインストール
- Windows SDK を含める
- CMakeサポートを追加

#### macOS

**Xcode Command Line Toolsの詳細:**

```bash

# インストール

xcode-select --install

# 確認

xcode-select -p

# バージョン確認

gcc --version
clang --version
```

**Homebrewでの追加ツール:**

```bash

# Homebrewのインストール

/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# 開発ツールのインストール

brew install gcc
brew install gdb
brew install cmake
```

#### Linux

**各ディストリビューション別:**

**Ubuntu/Debian:**

```bash
sudo apt update
sudo apt install build-essential
sudo apt install gdb
sudo apt install cmake
sudo apt install valgrind
```

**Fedora/RHEL:**

```bash
sudo dnf groupinstall "Development Tools"
sudo dnf install gcc
sudo dnf install gdb
sudo dnf install cmake
```

**Arch Linux:**

```bash
sudo pacman -S base-devel
sudo pacman -S gdb
sudo pacman -S cmake
```

## コンパイル過程の詳細

### コンパイルの各段階

1. **プリプロセッサ処理**

   ```bash
   gcc -E source.c -o source.i
   ```

   - `#include`の展開
   - `#define`の置換
   - 条件付きコンパイルの処理

2. **コンパイル（狭義）**

   ```bash
   gcc -S source.i -o source.s
   ```

   - C言語からアセンブリ言語へ変換
   - 構文解析と意味解析
   - 最適化の実行

3. **アセンブル**

   ```bash
   gcc -c source.s -o source.o
   ```

   - アセンブリ言語から機械語へ変換
   - オブジェクトファイルの生成

4. **リンク**

   ```bash
   gcc source.o -o program
   ```

   - オブジェクトファイルの結合
   - ライブラリの結合
   - 実行ファイルの生成

### コンパイラーオプションの詳細

#### 警告オプション

```bash
-Wall          # 基本的な警告をすべて有効化
-Wextra        # 追加の警告を有効化
-Werror        # 警告をエラーとして扱う
-pedantic      # 規格に厳密に従う
-Wno-unused    # 未使用変数の警告を無効化
```

#### 最適化オプション

```bash
-O0            # 最適化なし（デフォルト）
-O1            # 基本的な最適化
-O2            # 推奨される最適化
-O3            # 積極的な最適化
-Os            # サイズ最適化
-Og            # デバッグ向け最適化
```

#### デバッグオプション

```bash
-g             # デバッグ情報を含める
-g3            # マクロ情報も含める
-ggdb          # GDB用の詳細情報
```

#### その他の重要なオプション

```bash
-std=c99       # C99規格を使用
-D DEBUG       # DEBUGマクロを定義
-I /path       # インクルードパスを追加
-L /path       # ライブラリパスを追加
-l library     # ライブラリをリンク
-fPIC          # 位置独立コード生成
-shared        # 共有ライブラリ作成
```

## 環境情報の取得

### システム情報の確認

```c
#include <stdio.h>
#include <limits.h>
#include <float.h>

void print_system_info(void) {
    printf("=== システム情報 ===\n");

    /* データ型のサイズ */
    printf("\nデータ型のサイズ:\n");
    printf("char: %lu bytes\n", sizeof(char));
    printf("short: %lu bytes\n", sizeof(short));
    printf("int: %lu bytes\n", sizeof(int));
    printf("long: %lu bytes\n", sizeof(long));
    printf("long long: %lu bytes\n", sizeof(long long));
    printf("float: %lu bytes\n", sizeof(float));
    printf("double: %lu bytes\n", sizeof(double));
    printf("pointer: %lu bytes\n", sizeof(void*));

    /* 整数型の範囲 */
    printf("\n整数型の範囲:\n");
    printf("CHAR: %d ~ %d\n", CHAR_MIN, CHAR_MAX);
    printf("SHORT: %d ~ %d\n", SHRT_MIN, SHRT_MAX);
    printf("INT: %d ~ %d\n", INT_MIN, INT_MAX);
    printf("LONG: %ld ~ %ld\n", LONG_MIN, LONG_MAX);

    /* 浮動小数点の情報 */
    printf("\n浮動小数点の情報:\n");
    printf("FLT_MIN: %e\n", FLT_MIN);
    printf("FLT_MAX: %e\n", FLT_MAX);
    printf("DBL_MIN: %e\n", DBL_MIN);
    printf("DBL_MAX: %e\n", DBL_MAX);
}
```

### コンパイラー情報の取得

```c
void print_compiler_info(void) {
    printf("=== コンパイラー情報 ===\n");

#ifdef __GNUC__
    printf("GCC version: %d.%d.%d\n",
           __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__);
#endif

#ifdef __clang__
    printf("Clang version: %d.%d.%d\n",
           __clang_major__, __clang_minor__, __clang_patchlevel__);
#endif

#ifdef _MSC_VER
    printf("Microsoft Visual C++ version: %d\n", _MSC_VER);
#endif

#ifdef __STDC_VERSION__
    printf("C Standard: %ld\n", __STDC_VERSION__);
#endif
}
```

### エンディアンの確認

```c
void check_endianness(void) {
    unsigned int x = 1;
    char *c = (char*)&x;

    if (*c) {
        printf("システムはリトルエンディアンです\n");
    } else {
        printf("システムはビッグエンディアンです\n");
    }
}
```

## トラブルシューティング

### よくあるエラーと対処法

1. **"gcc: command not found"**
   - 原因：コンパイラーがインストールされていない
   - 対処：環境構築の手順を再確認

2. **"undefined reference to `main'"**
   - 原因：main関数が定義されていない
   - 対処：main関数を追加

3. **"fatal error: stdio.h: No such file or directory"**
   - 原因：標準ライブラリが見つからない
   - 対処：開発環境の再インストール

4. **文字化け**
   - 原因：文字エンコーディングの不一致
   - 対処：UTF-8に統一

### デバッグ手法

1. **printf デバッグ**

   ```c
   printf("DEBUG: 変数x = %d\n", x);
   ```

2. **アサーション**

   ```c
   #include <assert.h>
   assert(x > 0);  /* 条件が偽なら停止 */
   ```

3. **GDBの基本的な使い方**

   ```bash
   gcc -g program.c -o program
   gdb ./program

   # GDB内のコマンド
   break main     # ブレークポイント設定
   run           # プログラム実行
   step          # 1行実行
   print x       # 変数の値を表示
   continue      # 実行継続
   quit          # 終了
   ```

## 環境設定のベストプラクティス

1. **エディターの設定**
   - インデント：スペース4つ
   - 文字エンコーディング：UTF-8
   - 改行コード：LF（Unix形式）

2. **コンパイラーの警告設定**

   ```bash
   alias gcc='gcc -Wall -Wextra -pedantic'
   ```

3. **Makefileの活用**

   ```makefile
   CC = gcc
   CFLAGS = -Wall -Wextra -pedantic -std=c99

   all: program

   program: main.o utils.o
       $(CC) $(CFLAGS) -o $@ $^

   %.o: %.c
       $(CC) $(CFLAGS) -c $<

   clean:
       rm -f *.o program
   ```

## 次の章へ

開発環境の詳細設定について理解できました。メインの学習に戻りましょう。

## 演習問題

この章の内容を理解したら、[演習問題](exercises/)に挑戦してみましょう。
