# 文字列処理
##  対応C規格
- **主要対象:** C90
- **学習内容:** 文字列の基本、文字列操作関数、文字列配列の詳細操作、文字列の比較・検索・変換

##  学習目標
この章を完了すると、以下のことができるようになります。
- 文字列の基本概念を完全に理解する
- 標準ライブラリの文字列操作関数を使いこなせる
- 文字列配列の詳細な操作ができる
- 次元文字配列と文字列ポインタ配列を使い分けられる
- 実践的な文字列処理プログラムを作成できる

##  概要と詳細

### 文字列処理とは？
文字列処理は、プログラミングで最も頻繁に行う作業の一つです。名前、メッセージ、ファイル名など、私たちが扱うデータの多くは文字列です。

#### 日常生活での文字列処理
身近な例を考えてみましょう。

1. **メールアドレスの検証**
   - "@"が含まれているか？
   - 適切な形式か？

2. **パスワードのチェック**  
   - 8文字以上か？
   - 大文字・小文字・数字が含まれているか？

3. **名前の整形**
   - 姓と名を分ける
   - 大文字・小文字を整える

これらはすべて文字列処理の例です！

### 文字列の基本概念 
C言語では文字列は文字の配列として表現され、null文字（'\0'）で終端されます。この仕組みを理解することが、文字列処理をマスターする第一歩です。

#### 文字列とは何か？

C言語における文字列は、実は「文字の配列」に過ぎません。ただし、特別なルールがあります。

```
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

/* 4. 文字列リテラルへのポインタ */
char *str4 = "Hello";
/* 文字列リテラルは読み取り専用領域に配置される */
```

#### null終端文字（'\0'）の重要性

null終端文字は、文字列の終わりを示す特別な文字です。

```c
char str[] = "ABC";
/* メモリ上では: 'A' 'B' 'C' '\0' と格納される */

/* null終端がない場合の問題 */
char bad_str[3] = {'A', 'B', 'C'};  /* '\0'がない！ */
printf("%s", bad_str);  /* どこまで表示されるか不明（危険） */
```

#### 文字と文字列の違い

初心者が混同しやすい重要な違いです。

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
/* 文字列リテラルは読み取り専用 */
char *ptr = "Hello";
ptr[0] = 'h';  /* 実行時エラー（セグメンテーションフォルト） */

/* 配列にコピーすれば変更可能 */
char arr[] = "Hello";
arr[0] = 'h';  /* OK: "hello"になる */

/* 同じ文字列リテラルは共有される可能性 */
char *p1 = "Hello";
char *p2 = "Hello";
/* p1とp2は同じアドレスを指す可能性がある */
```

### 基本的な文字列操作

#### 文字列の長さを取得
```c
#include <string.h>
char str[] = "Hello";
int len = strlen(str);  /* 結果: 5 */
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

3. **strncpy()** - 指定長でコピー（安全）
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

7. **strncat()** - 指定長で連結（安全）
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
char names[5][20];  /* 5つの名前、各最大20文字 */
char fruits[5][20] = {
    "Apple",
    "Banana", 
    "Orange",
    "Grape",
    "Strawberry"
};
```

**特徴:**
- 固定サイズのメモリ領域を確保
- 各文字列は固定長で格納される
- メモリ使用量が予測可能
- 文字列の変更が可能
- サイズ = 行数 × 列数 × sizeof(char)

#### 文字列ポインタ配列（char*配列）
```c
char *fruits[] = {"Apple", "Banana", "Orange"};
char *months[] = {
    "January", "February", "March", "April",
    "May", "June", "July", "August",
    "September", "October", "November", "December"
};
```

**特徴:**
- 文字列リテラルへのポインタを格納
- メモリ効率が良い（無駄な領域なし）
- 文字列の長さは可変
- 文字列リテラルの変更は不可
- サイズ = ポインタ数 × sizeof(char*)

#### char配列 vs char*配列の使い分け

**char配列を選ぶべき場合:**
- 文字列を変更する必要がある
- メモリ使用量を予測したい
- 全ての文字列が同程度の長さ

**char*配列を選ぶべき場合:**
- 文字列を変更しない（読み取り専用）
- メモリ効率を重視する
- 文字列の長さがバラバラ

#### 文字列配列の操作例

##### 配列の検索
```c
int search_string(char arr[][20], int size, char *target) {
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

#### 大文字・小文字変換
```c
#include <ctype.h>
char c = 'a';
char upper = toupper(c);  /* 'A' */
char lower = tolower('B'); /* 'b' */
```

#### 数値との変換
```c
#include <stdlib.h>
int num = atoi("123");        /* 文字列から整数へ */
double d = atof("3.14");      /* 文字列から浮動小数点へ */
```

### 文字列の入力と出力

#### 標準入力からの文字列読み込み
```c
char buffer[100];
printf("名前を入力: ");
scanf("%s", buffer);          /* 空白まで読み込み */
fgets(buffer, sizeof(buffer), stdin);  /* 改行まで読み込み（推奨） */
```

#### 安全な文字列入力
- **scanf()** - 空白で区切られる、バッファオーバーフローの危険
- **fgets()** - 改行まで読み込み、サイズ制限あり（推奨）

### 文字列処理のベストプラクティス

#### 安全性の確保
1. **バッファオーバーフローの防止**
   - strncpy(), strncat(), snprintf()を使用
   - 常にバッファサイズを意識

2. **null終端の確保**
   - strncpy()後は明示的にnull文字を設定
   - メモリ初期化を適切に行う

3. **戻り値のチェック**
   - 文字列関数の戻り値を適切にチェック
   - NULLポインタの可能性を考慮

#### 効率性の向上
1. **適切なデータ構造の選択**
   - 固定長vs可変長の選択
   - メモリ使用量の最適化

2. **文字列操作の最小化**
   - 不必要なコピーを避ける
   - インプレース操作の活用

### よくある間違いとデバッグ

#### 1. バッファオーバーフロー
**問題:** 文字列が配列のサイズを超える
```c
char buffer[5];
strcpy(buffer, "Hello World");  /* 危険！ */
```

**対策:**
- strncpy()やsnprintf()を使用
- 常にバッファサイズを確認

#### 2. null終端の忘れ
**問題:** null文字がない文字列
```c
char str[5] = {'H', 'e', 'l', 'l', 'o'};  /* null終端なし */
printf("%s", str);  /* 未定義動作 */
```

**対策:**
- 文字列リテラルを使用
- 明示的にnull文字を設定

#### 3. 文字列リテラルの変更
**問題:** 読み取り専用の文字列を変更
```c
char *str = "Hello";
str[0] = 'h';  /* 未定義動作 */
```

**対策:**
- 変更が必要な場合は配列を使用
- const修飾子を適切に使用

#### 4. ポインタの誤用
**問題:** 無効なポインタの使用
```c
char *str;
strcpy(str, "Hello");  /* 未初期化ポインタ */
```

**対策:**
- ポインタを適切に初期化
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
- **新しい関数**: C99以降で追加された関数の有無

## 注意事項とベストプラクティス

### セキュリティの考慮
1. **入力検証の徹底**
   - ユーザー入力は常に検証
   - バッファサイズを超える入力の制御

2. **安全な関数の使用**
   - 古い関数（strcpy, strcat等）より安全版を選択
   - 可能な限りstrncpy, strncat, snprintf等を使用

3. **メモリ管理**
   - 動的に確保したメモリの適切な解放
   - ダングリングポインタの回避

## 次の章へ
文字列を理解したら、[関数](../functions/README.md) に進んでください。


## 参考資料
- [C標準ライブラリリファレンス](https://en.cppreference.com/w/c/string/byte)
- [セキュアコーディング標準](https://wiki.sei.cmu.edu/confluence/pages/viewpage.action?pageId=87152177)