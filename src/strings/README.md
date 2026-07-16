# 文字列処理

## 対応C規格

- **主要対象：** C90
- **学習内容：** 文字列の基本、文字列操作関数、文字列配列の詳細操作、文字列の比較・検索・変換

## 学習目標

この章を完了すると、以下のことができるようになります。

- null文字で終端された文字列の表現を説明できる
- 標準ライブラリの文字列操作関数を使える
- 2次元文字配列と文字列へのポインター配列を使い分けられる
- 配列の容量を考慮して文字列を入出力できる

## 概要と詳細

### 文字列処理とは

文字列処理には、長さの取得、コピー、比較、検索、入力の検証などがあります。
Cの文字列は長さを別に保持しないため、null文字までを参照できる配列領域が必要です。

### 文字列の基本概念

Cの文字列は、最初のnull文字`'\0'`までを含む文字の並びです。
文字列を格納する配列には、内容に加えて終端のnull文字を置く領域が必要です。

#### 文字列のメモリ表現

文字列`"Hello"`は、次の6個の文字として表現されます。

```text
文字列 "Hello" のメモリ上の配置：

インデックス: [0] [1] [2] [3] [4] [5]
内容:        'H' 'e' 'l' 'l' 'o' '\0'
             ↑                    ↑
             最初の文字           null終端文字（文字列の終わり）
```

#### 文字列の4つの表現方法

```c
/* 1. 文字配列として明示的に初期化 */
char str1[] = {'H', 'e', 'l', 'l', 'o', '\0'};
/* 各文字を個別に指定。最後に必ず'\0'が必要 */

/* 2. 文字列リテラルで初期化（最も一般的） */
char str2[] = "Hello";
/* コンパイラが自動的に'\0'を追加。サイズは6バイト */

/* 3. 固定サイズ配列に文字列を格納 */
char str3[10] = "Hello";
/* 10バイト確保。"Hello\0"の後の4バイトは'\0'で初期化 */

/* 4. 文字列リテラルの先頭を指すポインター */
const char *str4 = "Hello";
/* 文字列リテラルを変更しないことを型で示す */
```

#### null文字（`'\0'`）による終端

null終端文字は、文字列の終わりを示す特別な文字です。

```c
char str[] = "ABC";
/* メモリ上では: 'A' 'B' 'C' '\0' と格納される */

/* null終端がない場合の問題 */
char bad_str[3] = {'A', 'B', 'C'};  /* '\0'がない */
printf("%s", bad_str);  /* 配列外まで読み得るため未定義動作 */
```

#### 文字と文字列の違い

文字定数はシングルクォート、文字列リテラルはダブルクォートで表します。

```c
/* 文字（1バイト） */
char ch = 'A';        /* シングルクォート */

/* 文字列（2バイト以上） */
char str[] = "A";     /* ダブルクォート */
/* 実際は 'A' と '\0' の2バイト */

/* 間違いやすい例 */
char wrong1 = "A";    /* エラー：文字列を文字型に代入 */
char wrong2[] = 'A';  /* エラー：文字で配列を初期化 */
```

#### 文字列のサイズと長さ

```c
char str[10] = "Hello";

/* サイズ：配列として確保されたメモリ量 */
sizeof(str)   /* 結果：10（バイト） */

/* 長さ：実際の文字数（'\0'を除く） */
strlen(str)   /* 結果：5（文字） */

/* メモリ配置 */
/* [H][e][l][l][o][\0][\0][\0][\0][\0] */
/*  0  1  2  3  4  5   6   7   8   9   */
```

#### 文字列リテラルの特殊性

```c
/* 文字列リテラルを変更すると未定義動作 */
const char *ptr = "Hello";

/* 配列にコピーすれば変更可能 */
char arr[] = "Hello";
arr[0] = 'h';  /* OK: "hello"になる */

/* 同じ文字列リテラルは共有される可能性 */
const char *p1 = "Hello";
const char *p2 = "Hello";
/* p1とp2は同じアドレスを指す可能性がある */
```

### 基本的な文字列操作

#### 文字列の長さを取得

```c
#include <string.h>
char str[] = "Hello";
size_t len = strlen(str);  /* 結果: 5 */
```

#### 文字列のコピー

```c
char src[] = "Hello";
char dest[20];
strcpy(dest, src);  /* srcをdestにコピー */
```

#### 文字列の比較

```c
char str1[] = "Hello";
char str2[] = "World";
int result = strcmp(str1, str2);  /* 0でない値が返される */
```

#### 文字列の連結

```c
char str1[20] = "Hello";
char str2[] = " World";
strcat(str1, str2);  /* str1が "Hello World" になる */
```

### 標準ライブラリの文字列関数

#### <string.h>の主要関数

1. **strlen()** - 文字列の長さを取得

   ```c
   size_t strlen(const char *s);
   ```

2. **strcpy()** - 文字列をコピー

   ```c
   char *strcpy(char *dest, const char *src);
   ```

3. **strncpy()** - 指定した個数の文字を配列へ書き込む

   ```c
   char *strncpy(char *dest, const char *src, size_t n);
   ```

4. **strcmp()** - 文字列を比較

   ```c
   int strcmp(const char *s1, const char *s2);
   ```

5. **strncmp()** - 指定長で比較

   ```c
   int strncmp(const char *s1, const char *s2, size_t n);
   ```

6. **strcat()** - 文字列を連結

   ```c
   char *strcat(char *dest, const char *src);
   ```

7. **strncat()** - 連結元から最大`n`文字を連結する

   ```c
   char *strncat(char *dest, const char *src, size_t n);
   ```

8. **strchr()** - 文字を検索

   ```c
   char *strchr(const char *s, int c);
   ```

9. **strstr()** - 文字列を検索

   ```c
   char *strstr(const char *haystack, const char *needle);
   ```

### 文字列配列の詳細操作

#### 2次元文字配列（char配列）

```c
char names[5][20];  /* 5つの名前、各最大19文字と終端のnull文字 */
char fruits[5][20] = {
    "Apple",
    "Banana",
    "Orange",
    "Grape",
    "Strawberry"
};
```

**特徴：**

- 固定サイズのメモリ領域を確保
- 各文字列は固定長で格納される
- メモリ使用量が予測可能
- 文字列の変更が可能
- サイズ = 行数 × 列数 × sizeof(char)

#### 文字列へのポインター配列（`const char *`配列）

```c
const char *fruits[] = {"Apple", "Banana", "Orange"};
const char *months[] = {
    "January", "February", "March", "April",
    "May", "June", "July", "August",
    "September", "October", "November", "December"
};
```

**特徴：**

- 文字列リテラルへのポインターを格納
- 各要素にはポインターの領域が必要
- 文字列の長さは可変
- 文字列リテラルの変更は不可
- サイズ = ポインター数 × sizeof(char*)

#### `char`配列と`const char *`配列の使い分け

**`char`配列を選ぶ場合：**

- 文字列を変更する必要がある
- メモリ使用量を予測したい
- 全ての文字列が同程度の長さ

**`const char *`配列を選ぶ場合：**

- 文字列を変更しない（読み取り専用）
- 文字列ごとに異なる長さを扱う
- 文字列の長さがバラバラ

#### 文字列配列の操作例

##### 配列の検索

```c
int search_string(char arr[][20], int size, const char *target) {
    int i;
    for (i = 0; i < size; i++) {
        if (strcmp(arr[i], target) == 0) {
            return i;  /* 見つかった位置 */
        }
    }
    return -1;  /* 見つからなかった */
}
```

##### 文字列配列のソート（選択ソート）

```c
void sort_strings(char arr[][20], int size) {
    int i, j, min_idx;
    char temp[20];

    for (i = 0; i < size - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < size; j++) {
            if (strcmp(arr[j], arr[min_idx]) < 0) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            strcpy(temp, arr[i]);
            strcpy(arr[i], arr[min_idx]);
            strcpy(arr[min_idx], temp);
        }
    }
}
```

### 文字列の検索と置換

#### 文字の検索

- **strchr()** - 最初に見つかった文字の位置
- **strrchr()** - 最後に見つかった文字の位置

#### 文字列の検索

- **strstr()** - 部分文字列の検索
- **大文字小文字を無視した検索**は標準関数では提供されていない

#### 文字列の置換

C標準ライブラリには置換関数はないため、自分で実装する必要があります。

### 文字列の変換

#### 大文字と小文字の変換

```c
#include <ctype.h>
unsigned char c = 'a';
int upper = toupper(c);  /* 'A' */
int lower = tolower((unsigned char)'B'); /* 'b' */
```

`toupper`と`tolower`の戻り値の型は`int`です。
引数には`EOF`、または`unsigned char`で表現できる値を渡します。

#### 数値との変換

```c
#include <stdlib.h>
long num = strtol("123", NULL, 10);  /* 文字列からlongへ */
double d = strtod("3.14", NULL);     /* 文字列からdoubleへ */
```

`atoi`や`atof`では変換エラーを判別できません。
入力を検証する場合は、終了位置や範囲エラーを確認できる`strtol`や`strtod`を使います。

### 文字列の入力と出力

#### 標準入力からの文字列読み込み

```c
char buffer[100];
scanf("%99s", buffer);  /* 空白までを最大99文字読み込む */
fgets(buffer, sizeof(buffer), stdin);  /* 改行までを配列の容量内で読み込む */
```

#### 安全な文字列入力

- **`scanf`**：`%s`を使う場合は、配列容量に合わせた最大フィールド幅を指定します
- **`fgets`**：最大読み取り数を指定でき、改行を配列に格納する場合があります

### 文字列処理のベストプラクティス

#### 安全性の確保

1. **バッファーオーバーフローの防止**

    - コピー元の長さとコピー先の容量を確認する
    - C99以降では、書式付き出力に`snprintf`を使用できる

2. **null終端の確保**

    - `strncpy`で切り詰めが起きる場合は、終端のnull文字を明示する
    - メモリ初期化を適切に行う

3. **戻り値のチェック**

    - 文字列関数の戻り値を適切にチェック
    - NULLポインターの可能性を考慮

#### 効率性の向上

1. **適切なデータ構造の選択**

    - 固定長vs可変長の選択
    - メモリ使用量の最適化

2. **文字列操作の最小化**

    - 不必要なコピーを避ける
    - インプレース操作の活用

### よくある間違いとデバッグ

#### 1. バッファーオーバーフロー

**問題：** 文字列が配列のサイズを超える

```c
char buffer[5];
strcpy(buffer, "Hello World");  /* 配列の境界を越えて書き込むため未定義動作 */
```

**対策：**

- 書き込む文字列と終端のnull文字が配列に収まるか確認する
- C99以降では、書式付き出力に`snprintf`を使用する

#### 2. null終端の忘れ

**問題：** null文字がない文字列

```c
char str[5] = {'H', 'e', 'l', 'l', 'o'};  /* null終端なし */
printf("%s", str);  /* 未定義動作 */
```

**対策：**

- 文字列リテラルを使用
- 明示的にnull文字を設定

#### 3. 文字列リテラルの変更

**問題：** 読み取り専用の文字列を変更

```c
char *str = "Hello";
str[0] = 'h';  /* 未定義動作 */
```

**対策：**

- 変更が必要な場合は配列を使用
- const修飾子を適切に使用

#### 4. ポインターの誤用

**問題：** 無効なポインターの使用

```c
char *str;
strcpy(str, "Hello");  /* 未初期化ポインター */
```

**対策：**

- ポインターを適切に初期化
- メモリ確保を忘れずに

## 実例コード

完全な実装例は以下のファイルを参照してください。

### 基本的な文字列操作

- [string_basics.c](examples/string_basics.c) - C90準拠版
- [string_basics_c99.c](examples/string_basics_c99.c) - C99準拠版

### 文字列操作関数の活用

- [string_functions.c](examples/string_functions.c) - C90準拠版
- [string_functions_c99.c](examples/string_functions_c99.c) - C99準拠版

### 文字列配列の実践と詳細操作

- [string_array_operations.c](examples/string_array_operations.c) - C90準拠版
- [string_array_operations_c99.c](examples/string_array_operations_c99.c) - C99準拠版

### 文字列配列の完全活用例

- [string_arrays.c](examples/string_arrays.c) - C90準拠版（配列章から移行）
- [string_arrays_c99.c](examples/string_arrays_c99.c) - C99準拠版（配列章から移行）

## コンパイル方法

### 基本的なコンパイル（C90準拠）

```bash
gcc -std=c90 -Wall -Wextra -pedantic string_basics.c -o string_basics
```

### Makefileを使用した場合

```bash

# 全てのプログラムをコンパイル

make all

# 特定のプログラムをコンパイル

make string_basics

# C99版をコンパイル

make string_basics_c99

# プログラムを実行

make run-all

# クリーンアップ

make clean
```

## 学習フローとコンパイル方法

### 推奨学習順序

1. **理論学習**: README.mdで基本概念を理解
2. **サンプルコード**: examples/の基本例を確認
3. **演習課題**: exercises/README.mdで課題を確認
4. **実装練習**: solutions/の解答例を参考に自分で実装

### 実践的な学習方法

1. **基本関数の理解** - strlen, strcpy, strcmp等の基本動作を確認
2. **安全な関数の活用** - strncpy, strncat等の安全版を使用
3. **実際の問題解決** - 具体的な文字列処理問題に取り組む
4. **エラー処理の実装** - 例外的なケースへの対応を学習

## C90とC99の違い

### 文字列処理での主な違い

- **C90**: 変数宣言は関数の先頭でまとめて行う
- **C99**: 変数を使用する場所で宣言可能
- **コメント**: C90は `/* */`のみ、C99は `//` も使用可能
- **書式付き出力**：C99では`snprintf`が標準化された

## 注意事項とベストプラクティス

### セキュリティの考慮

1. **入力検証の徹底**

    - ユーザー入力は常に検証
    - バッファーサイズを超える入力の制御

2. **容量を明示した操作**

    - `strcpy`や`strcat`を使う前に、書き込み先の容量を確認する
    - `strncpy`は必ずnull終端する関数ではなく、`strncat`の`n`も書き込み先の容量ではない点に注意する
    - C99以降では、書式付き出力に`snprintf`を利用できる

3. **メモリ管理**

    - 動的に確保したメモリの適切な解放
    - ダングリングポインターの回避

## 次の章へ

次の[関数](../functions/README.md)では、文字列を受け取る仮引数と配列の要素数を扱います。

## 参考資料

- [C標準ライブラリリファレンス](https://en.cppreference.com/w/c/string/byte)
- [セキュアコーディング標準](https://wiki.sei.cmu.edu/confluence/pages/viewpage.action?pageId=87152177)

## 演習問題

[演習問題](exercises/)では、null終端、配列容量、標準文字列関数の事前条件を確認できます。

- 基礎問題：基本的な文法や概念の確認
- 応用問題：より実践的なプログラムの作成
- チャレンジ問題：高度な理解と実装力が必要な問題
