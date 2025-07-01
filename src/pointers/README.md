# 第10章 ポインタ基礎

##  対応C規格
- **主要対象:** C90
- **学習内容:** ポインタの基本概念、アドレス演算子、間接参照演算子、ポインタと配列、ポインタ演算

##  学習目標

この章を完了すると、以下のことができるようになります：

- ポインタの基本概念を理解する
- アドレス演算子（&）と間接参照演算子（*）を使える
- ポインタと配列の関係を理解する
- ポインタ演算ができる
- ポインタを関数の引数として使える

##  概要と詳細

### ポインタとは？

ポインタは、C言語で最も重要かつ難しいと言われる概念です。しかし、適切な例えを使えば理解できます！

#### 日常生活でのポインタ

ポインタを理解するために、「住所」の例えを使いましょう：

1. **家 = 変数**
   - 実際に人が住んでいる場所
   - 中に値（住人）が入っている

2. **住所 = ポインタ**
   - 家の場所を示す情報
   - 住所を知っていれば、その家に行ける

3. **住所録 = ポインタ変数**
   - 住所を書き留めておく手帳
   - 違う住所に書き換えることもできる

```c
int house = 100;      /* 家（変数）に100という値が住んでいる */
int *address = &house; /* 住所録にhouseの住所を記録 */
```

### ポインタの基本概念 

ポインタは他の変数のメモリアドレスを格納する変数です。これにより間接的に他の変数にアクセスできます。

#### なぜポインタが必要？

1. **大きなデータを効率的に扱える**
   - データのコピーではなく、場所だけを教える
   
2. **関数で複数の値を返せる**
   - 通常の関数は1つしか値を返せないが、ポインタなら複数可能

3. **動的なメモリ管理ができる**
   - プログラム実行中に必要なメモリを確保

#### メモリとアドレス

```c
#include <stdio.h>

int main(void)
{
    int number = 42;
    
    printf("変数numberの値: %d\n", number);
    printf("変数numberのアドレス: %p\n", (void*)&number);
    printf("変数numberのサイズ: %lu バイト\n", (unsigned long)sizeof(number));
    
    return 0;
}
```

#### ポインタ変数の宣言

```c
#include <stdio.h>

int main(void)
{
    int value = 100;        /* 通常の整数変数 */
    int *ptr;               /* 整数を指すポインタ変数 */
    
    ptr = &value;           /* valueのアドレスをptrに代入 */
    
    printf("value = %d\n", value);
    printf("&value = %p\n", (void*)&value);
    printf("ptr = %p\n", (void*)ptr);
    printf("*ptr = %d\n", *ptr);        /* ポインタが指す値 */
    
    return 0;
}
```

### アドレス演算子（&）と間接参照演算子（*） 

この2つの演算子は、ポインタを使う上で最も重要です。

#### 演算子の意味を覚える方法

- **& = "の住所"**（address of）
  - `&house` = "houseの住所"
  
- **\* = "が指す場所の中身"**（value at）
  - `*address` = "addressが指す場所の中身"

#### アドレス演算子（&）

```c
#include <stdio.h>

int main(void)
{
    int a = 10;
    double b = 3.14;
    char c = 'A';
    
    printf("変数のアドレス:\n");
    printf("&a = %p\n", (void*)&a);
    printf("&b = %p\n", (void*)&b);
    printf("&c = %p\n", (void*)&c);
    
    /* ポインタ変数の宣言と初期化 */
    int *ptr_a = &a;
    double *ptr_b = &b;
    char *ptr_c = &c;
    
    printf("\nポインタの値（アドレス）:\n");
    printf("ptr_a = %p\n", (void*)ptr_a);
    printf("ptr_b = %p\n", (void*)ptr_b);
    printf("ptr_c = %p\n", (void*)ptr_c);
    
    return 0;
}
```

#### 間接参照演算子（*）

```c
#include <stdio.h>

int main(void)
{
    int original = 50;
    int *pointer = &original;
    
    printf("=== 元の状態 ===\n");
    printf("original = %d\n", original);
    printf("*pointer = %d\n", *pointer);
    
    /* ポインタを通じて値を変更 */
    *pointer = 75;
    
    printf("\n=== *pointer = 75 実行後 ===\n");
    printf("original = %d\n", original);      /* 75に変更される */
    printf("*pointer = %d\n", *pointer);      /* 75 */
    
    /* 元の変数を直接変更 */
    original = 99;
    
    printf("\n=== original = 99 実行後 ===\n");
    printf("original = %d\n", original);      /* 99 */
    printf("*pointer = %d\n", *pointer);      /* 99 */
    
    return 0;
}
```

### ポインタのデータ型 

#### さまざまなデータ型のポインタ

```c
#include <stdio.h>

int main(void)
{
    /* 各データ型の変数 */
    char char_var = 'X';
    int int_var = 123;
    float float_var = 3.14f;
    double double_var = 2.718;
    
    /* 各データ型のポインタ */
    char *char_ptr = &char_var;
    int *int_ptr = &int_var;
    float *float_ptr = &float_var;
    double *double_ptr = &double_var;
    
    printf("=== 値の表示 ===\n");
    printf("char: %c\n", *char_ptr);
    printf("int: %d\n", *int_ptr);
    printf("float: %.2f\n", *float_ptr);
    printf("double: %.3f\n", *double_ptr);
    
    printf("\n=== ポインタのサイズ ===\n");
    printf("char*: %lu バイト\n", (unsigned long)sizeof(char_ptr));
    printf("int*: %lu バイト\n", (unsigned long)sizeof(int_ptr));
    printf("float*: %lu バイト\n", (unsigned long)sizeof(float_ptr));
    printf("double*: %lu バイト\n", (unsigned long)sizeof(double_ptr));
    
    return 0;
}
```

#### void*ポインタ（汎用ポインタ）

```c
#include <stdio.h>

int main(void)
{
    int int_value = 456;
    double double_value = 1.618;
    
    void *generic_ptr;      /* 汎用ポインタ */
    
    /* intを指す */
    generic_ptr = &int_value;
    printf("int値: %d\n", *(int*)generic_ptr);  /* キャストが必要 */
    
    /* doubleを指す */
    generic_ptr = &double_value;
    printf("double値: %.3f\n", *(double*)generic_ptr);  /* キャストが必要 */
    
    return 0;
}
```

### ポインタと配列の関係 

ポインタと配列は非常に密接な関係があります。実は、配列名そのものがポインタとして扱われることを理解すると、C言語がより深く理解できます。

#### 配列名はポインタ

配列名は「配列の最初の要素を指すポインタ」として扱われます。これは重要な概念です！

```c
#include <stdio.h>

int main(void)
{
    int arr[] = {10, 20, 30, 40, 50};
    int *ptr = arr;         /* arr は &arr[0] と同じ */
    int i;
    
    printf("=== 配列とポインタの関係 ===\n");
    printf("arr = %p\n", (void*)arr);
    printf("&arr[0] = %p\n", (void*)&arr[0]);
    printf("ptr = %p\n", (void*)ptr);
    
    printf("\n=== 配列要素へのアクセス ===\n");
    for (i = 0; i < 5; i++) {
        printf("arr[%d] = %d, *(arr + %d) = %d, *(ptr + %d) = %d\n",
               i, arr[i], i, *(arr + i), i, *(ptr + i));
    }
    
    return 0;
}
```

#### ポインタを使った配列操作

```c
#include <stdio.h>

void print_array_index(int arr[], int size)
{
    int i;
    
    printf("インデックス記法: ");
    for (i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void print_array_pointer(int *ptr, int size)
{
    int i;
    
    printf("ポインタ記法: ");
    for (i = 0; i < size; i++) {
        printf("%d ", *(ptr + i));
    }
    printf("\n");
}

int main(void)
{
    int numbers[] = {11, 22, 33, 44, 55};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    
    print_array_index(numbers, size);
    print_array_pointer(numbers, size);
    
    return 0;
}
```

### ポインタ演算 

ポインタには通常の数値とは異なる特殊な演算規則があります。これを理解することで、配列やメモリを効率的に操作できるようになります。

#### なぜポインタ演算が特殊なのか？

ポインタに1を足しても、アドレスが1増えるわけではありません。代わりに「次の要素」に移動します。

```
int配列の場合：
ptr + 1 → 次のint（通常4バイト先）へ移動

char配列の場合：
ptr + 1 → 次のchar（1バイト先）へ移動
```

#### ポインタの加算・減算

```c
#include <stdio.h>

int main(void)
{
    int arr[] = {5, 15, 25, 35, 45};
    int *ptr = arr;
    int i;
    
    printf("=== ポインタ演算の例 ===\n");
    for (i = 0; i < 5; i++) {
        printf("ptr + %d = %p, *(ptr + %d) = %d\n",
               i, (void*)(ptr + i), i, *(ptr + i));
    }
    
    printf("\n=== ポインタのインクリメント ===\n");
    ptr = arr;  /* 先頭に戻す */
    for (i = 0; i < 5; i++) {
        printf("*ptr = %d (アドレス: %p)\n", *ptr, (void*)ptr);
        ptr++;  /* 次の要素に移動 */
    }
    
    return 0;
}
```

#### ポインタ同士の差

```c
#include <stdio.h>

int main(void)
{
    int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int *start = &arr[2];   /* arr[2]を指す */
    int *end = &arr[7];     /* arr[7]を指す */
    
    printf("start が指す値: %d (インデックス2)\n", *start);
    printf("end が指す値: %d (インデックス7)\n", *end);
    printf("ポインタの差: %ld\n", end - start);  /* 5 */
    printf("バイト差: %ld\n", (char*)end - (char*)start);
    
    return 0;
}
```

### ポインタと関数 

関数とポインタを組み合わせることで、C言語の真の力を発揮できます。特に、関数で複数の値を変更したり、大きなデータを効率的に扱えるようになります。

#### なぜ関数でポインタを使うのか？

1. **複数の値を変更できる**
   - 通常の関数は1つの値しか返せない
   - ポインタなら複数の値を同時に変更可能

2. **効率的なデータ処理**
   - 大きな配列や構造体をコピーせずに処理
   - メモリと処理時間を節約

3. **実際の変数を変更できる**
   - 値渡しでは元の変数は変わらない
   - ポインタ渡しなら元の変数を直接変更

#### ポインタを引数とする関数

```c
#include <stdio.h>

/* 値を交換する関数 */
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* 値を倍にする関数 */
void double_value(int *value)
{
    *value = (*value) * 2;
}

/* 配列の要素を変更する関数 */
void modify_array(int arr[], int size)
{
    int i;
    
    for (i = 0; i < size; i++) {
        arr[i] *= 3;  /* 各要素を3倍 */
    }
}

int main(void)
{
    int x = 8, y = 12;
    int numbers[] = {1, 2, 3, 4, 5};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    int i;
    
    printf("=== swap関数のテスト ===\n");
    printf("交換前: x = %d, y = %d\n", x, y);
    swap(&x, &y);
    printf("交換後: x = %d, y = %d\n", x, y);
    
    printf("\n=== double_value関数のテスト ===\n");
    printf("2倍前: x = %d\n", x);
    double_value(&x);
    printf("2倍後: x = %d\n", x);
    
    printf("\n=== modify_array関数のテスト ===\n");
    printf("変更前: ");
    for (i = 0; i < size; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");
    
    modify_array(numbers, size);
    
    printf("変更後: ");
    for (i = 0; i < size; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");
    
    return 0;
}
```

#### ポインタを戻り値とする関数

```c
#include <stdio.h>

/* 配列から最大値のアドレスを返す */
int* find_max_ptr(int arr[], int size)
{
    int *max_ptr = &arr[0];
    int i;
    
    for (i = 1; i < size; i++) {
        if (arr[i] > *max_ptr) {
            max_ptr = &arr[i];
        }
    }
    
    return max_ptr;
}

/* 配列から指定値を検索してアドレスを返す */
int* search_value(int arr[], int size, int target)
{
    int i;
    
    for (i = 0; i < size; i++) {
        if (arr[i] == target) {
            return &arr[i];  /* 見つかった要素のアドレス */
        }
    }
    
    return NULL;  /* 見つからない場合 */
}

int main(void)
{
    int data[] = {3, 7, 2, 9, 5, 1, 8};
    int size = sizeof(data) / sizeof(data[0]);
    int *result_ptr;
    int search_target = 9;
    int i;
    
    /* 配列の表示 */
    printf("配列: ");
    for (i = 0; i < size; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");
    
    /* 最大値の検索 */
    result_ptr = find_max_ptr(data, size);
    printf("最大値: %d (アドレス: %p)\n", *result_ptr, (void*)result_ptr);
    
    /* 特定値の検索 */
    result_ptr = search_value(data, size, search_target);
    if (result_ptr != NULL) {
        printf("%d が見つかりました (アドレス: %p)\n", 
               *result_ptr, (void*)result_ptr);
    } else {
        printf("%d は見つかりませんでした\n", search_target);
    }
    
    return 0;
}
```

##  サンプルコード

### 基本的なポインタ操作

プログラムファイル: `examples/pointer_basic.c`

ポインタの宣言、初期化、参照を学習します。

### ポインタと配列

プログラムファイル: `examples/pointer_array.c`

配列とポインタの関係、ポインタ演算を学習します。

### ポインタと関数

プログラムファイル: `examples/pointer_function.c`

関数でのポインタの使い方を学習します。

### コンパイルと実行

```bash
# examples ディレクトリに移動
cd examples

# C90準拠でコンパイル
gcc -std=c90 -Wall -Wextra -pedantic pointer_basic.c -o pointer_basic

# 実行
./pointer_basic
```

##  演習課題

### 基礎問題

1. **ポインタの基本操作**
   - 2つの変数の値をポインタを使って交換するプログラムを作成してください

2. **配列とポインタ**
   - ポインタ演算を使って配列の要素を逆順に表示するプログラムを作成してください

3. **文字列操作**
   - ポインタを使って文字列の長さを計算し、文字列を逆順にするプログラムを作成してください

### 応用問題

4. **配列操作関数**
   - ポインタを使って配列の最大値、最小値、平均値を計算する関数を作成してください

5. **文字列処理**
   - ポインタを使って文字列の検索、置換、分割を実行する関数群を作成してください

6. **データ変換**
   - ポインタを使って配列のデータ型変換を実行するプログラムを作成してください

### 発展問題

7. **メモリ操作**
   - ポインタを使って任意のデータ型の配列をコピーする汎用関数を作成してください

8. **アルゴリズム実装**
   - ポインタを使って各種ソートアルゴリズムを実装してください

##  コンパイル方法

この章では以下のMakefileを使用してコンパイルができます：

```bash
# 全ての例題をコンパイル
make all

# 特定のプログラムをコンパイル
make pointer_basic

# 実行
make run

# クリーンアップ
make clean
```

##  規格による違い

### C90での制限事項
- void*からの暗黙的な型変換は制限的
- ポインタ演算は整数型との組み合わせのみ
- 関数ポインタの表記法は限定的

### C99以降の拡張
- restrict修飾子の追加
- 可変長配列とポインタの関係改善
- より厳密なポインタ型チェック

##  よくある間違い

### 1. 未初期化ポインタの使用

```c
/* NG: 初期化されていないポインタ */
int *ptr;
*ptr = 10;  /* 危険: 不明なメモリへの書き込み */

/* OK: 適切に初期化 */
int value = 0;
int *ptr = &value;
*ptr = 10;
```

### 2. NULLポインタの参照

```c
/* NG: NULLポインタの参照 */
int *ptr = NULL;
printf("%d\n", *ptr);  /* セグメンテーション違反 */

/* OK: NULLチェック */
if (ptr != NULL) {
    printf("%d\n", *ptr);
}
```

### 3. スコープ外変数へのポインタ

```c
/* NG: ローカル変数のアドレス返し */
int* bad_function(void)
{
    int local = 100;
    return &local;  /* 危険: ローカル変数のアドレス */
}

/* OK: 静的変数または引数で渡された変数を使用 */
int* good_function(int *param)
{
    return param;  /* 引数で渡されたアドレスを返す */
}
```

### 4. 配列境界の越えた参照

```c
/* NG: 配列の範囲外アクセス */
int arr[] = {1, 2, 3, 4, 5};
int *ptr = arr;
printf("%d\n", *(ptr + 10));  /* 範囲外アクセス */

/* OK: 範囲チェック */
int index = 2;
if (index >= 0 && index < 5) {
    printf("%d\n", *(ptr + index));
}
```

##  次の章へ

ポインタの基礎を理解したら、[構造体](../structures/README.md) に進んでください。

##  参考資料

- [C言語ポインタリファレンス](https://ja.cppreference.com/w/c/language/pointer)
- [ポインタ演算の詳細](https://ja.cppreference.com/w/c/language/operator_arithmetic)
- [メモリモデルとポインタ](https://ja.cppreference.com/w/c/language/memory_model)