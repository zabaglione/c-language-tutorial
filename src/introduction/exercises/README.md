# 第1章「はじめてのC言語」の演習問題

## 演習の目的

この演習を通して、C言語の開発環境が正しく動作するか確認し、簡単なプログラムを作成・実行できるようになります。

## 基礎問題

### 問題1-1：Hello Worldの実行

`examples/hello_world.c` をコンパイルして実行してください。

```bash

# コンパイル

gcc examples/hello_world.c -o hello_world

# 実行

./hello_world
```

#### 期待される出力

```text
Hello, World!
```

### 問題1-2：自分でHello Worldを書く

新しいファイル `solutions/ex1_2_my_hello.c` を作成し、Hello Worldプログラムを自分で書いてください。

#### ヒント

- `#include <stdio.h>` を忘れずに
- `main` 関数の中に `printf` を書く
- 最後に `return 0;` を書く

### 問題1-3：日本語メッセージの表示

`solutions/ex1_3_japanese.c` を作成し、以下のメッセージを表示するプログラムを書いてください。

#### 表示するメッセージ

```text
こんにちは。
C言語の世界へようこそ。
プログラミングを始めます。
```

**ヒント：** `printf` を3回使うか、`\n` で改行します。

## 応用問題

### 問題1-4：簡単な自己紹介プログラム

`solutions/ex1_4_introduction.c` を作成し、自己紹介を表示するプログラムを書いてください。

#### 要件

- 名前を表示
- 好きなものを1つ表示
- C言語を学ぶ理由を表示

#### 実行例

```text
=== 自己紹介 ===
名前: 山田太郎
好きなもの: プログラミング
C言語を学ぶ理由: ゲームを作りたいから。
```

### 問題1-5：数字を使った挨拶

`solutions/ex1_5_greeting_with_number.c` を作成し、名前と年齢を入力して挨拶するプログラムを書いてください。

#### 実行例

```text
お名前は？: 花子
年齢は？: 20
こんにちは、花子さん（20歳）。
```

#### ヒント

```c
char name[50];
int age;
scanf("%s", name);
scanf("%d", &age);  /* 数字の入力には & が必要 */
```

## チャレンジ問題

### 問題1-6：簡単な計算機

`solutions/ex1_6_calculator.c` を作成し、2つの数を足し算するプログラムを書いてください。

#### 実行例

```text
簡単な計算機
1つ目の数: 10
2つ目の数: 25
10 + 25 = 35
```

### 問題1-7：ASCIIアート

`solutions/ex1_7_ascii_art.c` を作成し、簡単なASCIIアートを表示してください。

#### 例

```text
   /\_/\
  ( o.o )
   > ^ <
```

または自分で好きな絵を作ってもOKです。

## 提出形式

各問題の回答は以下のファイルに記述してください：

- **問題1-2**：`solutions/ex1_2_my_hello.c`
- **問題1-3**：`solutions/ex1_3_japanese.c`
- **問題1-4**：`solutions/ex1_4_introduction.c`
- **問題1-5**：`solutions/ex1_5_greeting_with_number.c`
- **問題1-6**：`solutions/ex1_6_calculator.c`
- **問題1-7**：`solutions/ex1_7_ascii_art.c`

## ヒント集

### printfの使い方

```c
printf("Display text\n");             /* 文字だけ */
printf("Name: %s\n", name);           /* 文字列を埋め込む */
printf("Number: %d\n", num);          /* 数字を埋め込む */
```

### scanfの使い方

```c
scanf("%s", name);    /* 文字列の入力（&不要） */
scanf("%d", &age);    /* 数字の入力（&必要） */
```
