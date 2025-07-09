# 第1章: はじめてのC言語

## 学習目標

この章を完了すると、以下のことができるようになります。

- C言語がどんなプログラミング言語か理解する
- 簡単な開発環境を準備する
- はじめてのプログラム「Hello World」を作成・実行する
- 基本的なコンパイル方法を覚える

## C言語とは？

C言語は1972年に開発されたプログラミング言語です。今でも世界中で使われている、とても重要な言語の一つです。

### なぜC言語を学ぶの？

1. **コンピューターの基礎が学べる**
    - メモリやCPUの動きが理解できるようになります
    - 他のプログラミング言語を学ぶときの土台になります

2. **多くの言語の基礎になっている**
    - C++、Java、Pythonなど、多くの言語がC言語の影響を受けています
    - C言語を知っていると、他の言語も学びやすくなります

3. **今でも現役で活躍中**
    - OS（Windows、Linux、macOS）の開発
    - 家電製品やゲーム機の中で動いています
    - 速さが必要なプログラムで使われています

## 開発環境の準備

C言語でプログラミングを始めるには、以下のツールが必要です：

1. **テキストエディタ**：プログラムを書くためのソフト
    - メモ帳でもOKですが、Visual Studio Code（無料）がおすすめ

2. **コンパイラー**：書いたプログラムを実行できる形に変換するソフト
    - Windows: MinGW-w64
    - macOS: Xcode Command Line Tools
    - Linux: GCC（最初から入っていることが多い）

### かんたん環境構築

**Windows:**

1. [MinGW-w64](https://www.mingw-w64.org/)をダウンロード
2. インストーラーを実行（デフォルト設定でOK）
3. コマンドプロンプトで`gcc --version`と入力して確認

**macOS:**

```bash

# ターミナルを開いて以下を実行

xcode-select --install
```

**Linux (Ubuntu/Debian):**

```bash

# ターミナルを開いて以下を実行

sudo apt update
sudo apt install build-essential
```

## はじめてのプログラム：Hello World

それでは、最初のプログラムを作ってみましょう！

### 1. プログラムを書く

`hello.c`という名前のファイルを作成し、以下のコードを書きます：

```c
#include <stdio.h>

int main(void) {
    printf("Hello, World!\n");
    return 0;
}
```

### 2. プログラムの説明

- `#include <stdio.h>` - 画面に文字を表示するための準備
- `int main(void)` - プログラムの開始地点
- `printf("Hello, World!\n");` - 文字を画面に表示
- `return 0;` - プログラムが正常に終了したことを伝える

### 3. コンパイルと実行

```bash

# コンパイル（プログラムを実行できる形に変換）

gcc hello.c -o hello

# 実行

./hello    # macOS/Linux
hello.exe  # Windows
```

実行すると、画面に `Hello, World!` と表示されます。おめでとうございます！

## もう少し進んだプログラム

名前を入力して挨拶するプログラムを作ってみましょう：

```c
#include <stdio.h>

int main(void) {
    char name[50];

    printf("お名前は？: ");
    scanf("%s", name);
    printf("こんにちは、%sさん！\n", name);

    return 0;
}
```

### コンパイルと実行

```bash
gcc greeting.c -o greeting
./greeting
```

実行例：

```
お名前は？: 太郎
こんにちは、太郎さん！
```

## この章で使うコンパイル方法

この章のフォルダには、簡単にコンパイルできるMakefileが用意されています：

```bash

# すべてのプログラムをコンパイル

make all

# 実行

make run-hello_world

# きれいにする（作成したファイルを削除）

make clean
```

## 次の章へ

プログラムの作成と実行ができるようになりました！
次は[第2章: 基本文法](../basics-syntax/README.md)で、C言語の基本的な書き方を学びましょう。

## 演習問題

この章の内容を理解したら、[演習問題](exercises/)に挑戦してみましょう。
