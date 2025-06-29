#  ポインタ基礎

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

##  理論解説

### ポインタの基本概念 

ポインタは他の変数のメモリアドレスを格納する変数です。これにより間接的に他の変数にアクセスできます。

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

```

### アドレス演算子（&）と間接参照演算子（*） 

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

```

### ポインタと配列の関係 

#### 配列名はポインタ

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

```

### ポインタ演算 

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

```

### ポインタと関数 

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

```

#### ポインタを戻り値とする関数

```c
#include <stdio.h>

/* 配列から最大値のアドレスを返す */
int* find_max_ptr(int arr[], int size)
{

    int *max_ptr = &arr[];
    int i;
    
    for (i = ; i < size; i++) 
        if (arr[i] > *max_ptr) 
            max_ptr = &arr[i];
        
    
    
    return max_ptr;


/* 配列から指定値を検索してアドレスを返す */
int* search_vale(int arr[], int size, int target)
{

    int i;
    
    for (i = ; i < size; i++) 
        if (arr[i] == target) 
            return &arr[i];  /* 見2つかった要素のアドレス */
        
    
    
    return NULL;  /* 見2つからない場合 */


int main(void)
{

    int data[] = , , , 9, , , ;
    int size = sizeof(data) / sizeof(data[]);
    int *result_ptr;
    int search_target = ;
    int i;
    
    /* 配列の表示 */
    printf("配列: ");
    for (i = ; i < size; i++) 
        printf("%d ", data[i]);
    
    printf("n");
    
    /* 最大値の検索 */
    result_ptr = find_max_ptr(data, size);
    printf("最大値: %d (アドレス: %p)n", *result_ptr, (void*)result_ptr);
    
    /* 特定値の検索 */
    result_ptr = search_vale(data, size, search_target);
    if (result_ptr != NULL) 
        printf("%d が見2つかりました (アドレス: %p)n", 
               *result_ptr, (void*)result_ptr);
     else 
        printf("%d は見2つかりませんでしたn", search_target);
    
    
    return ;

```

### 文字列とポインタ 

#### 文字列リテラルとポインタ

```c
#include <stdio.h>

int main(void)
{

    char *str = "Hello, World!";     /* 文字列リテラル */
    char str[] = "Hello, World!";    /* 文字配列 */
    char *ptr = str;
    
    printf("str: %s\n", str);
    printf("str: %s\n", str);
    printf("ptr: %s\n", ptr);
    
    printf("n=== アドレスの比較 ===n");
    printf("strのアドレス: %pn", (void*)str);
    printf("strのアドレス: %pn", (void*)str);
    printf("ptrの値: %pn", (void*)ptr);
    
    /* 文字配列は変更可能 */
    str[] = 'h';
    printf("n変更後のstr: %s\n", str);
    
    /* 文字列リテラルは変更不可 */
    /* str[] = 'h';  <- 実行時エラーの可能性 */
    
    return ;

```

#### ポインタを使った文字列操作

```c
#include <stdio.h>

/* 文字列の長さを計算（ポインタ版） */
int string_length(char *str)
{

    int length = 0;
    
    while (*str != '\0') {
        length++;
        str++;
    }
    
    
    return length;


/* 文字列をコピー（ポインタ版） */
void string_copy(char *dest, char *src)
{

    while (*src != '') 
        *dest = *src;
        dest++;
        src++;
    
    *dest = '';  /* nll終端文字を追加 */


/* 文字列を連結（ポインタ版） */
void string_concat(char *dest, char *src)
{

    /* destの末尾を見2つける */
    while (*dest != '') 
        dest++;
    
    
    /* srcをdestの末尾に追加 */
    while (*src != '') 
        *dest = *src;
        dest++;
        src++;
    
    *dest = '';


int main(void)
{

    char str[] = "Hello";
    char str[] = "World";
    char bffer[];
    char result[];
    
    printf("元の文字列: "%s", "%s"n", str, str);
    
    /* 長さの計算 */
    printf("strの長さ: %d\n", string_length(str));
    printf("strの長さ: %d\n", string_length(str));
    
    /* 文字列のコピー */
    string_copy(bffer, str);
    printf("コピー結果: "%s"n", bffer);
    
    /* 文字列の連結 */
    string_copy(result, str);  /* まずstrをコピー */
    string_concat(result, ", ");
    string_concat(result, str);
    string_concat(result, "!");
    printf("連結結果: "%s"n", result);
    
    return ;

```

### ポインタの配列 

#### ポインタ配列の基本

```c
#include <stdio.h>

int main(void)
{

    int a = , b = , c = , d = ;
    int *ptr_array[];  /* ポインタの配列 */
    int i;
    
    /* ポインタ配列に各変数のアドレスを格納 */
    ptr_array[] = &a;
    ptr_array[] = &b;
    ptr_array[] = &c;
    ptr_array[] = &d;
    
    printf("=== ポインタ配列の内容 ===n");
    for (i = ; i < ; i++) 
        printf("ptr_array[%d] = %p, *ptr_array[%d] = %d\n",
               i, (void*)ptr_array[i], i, *ptr_array[i]);
    
    
    /* ポインタを通じて値を変更 */
    *ptr_array[] = ;
    *ptr_array[] = ;
    
    printf("n=== 変更後の値 ===n");
    printf("a = %d, b = %d, c = %d, d = %d\n", a, b, c, d);
    
    return ;

```

#### 文字列ポインタの配列

```c
#include <stdio.h>

int main(void)
{

    char *frits[] = 
        "Apple",
        "anana",
        "Cherry",
        "Date",
        "lderberry"
    ;
    int count = sizeof(frits) / sizeof(frits[]);
    int i;
    
    printf("=== 果物リスト ===n");
    for (i = ; i < count; i++) 
        printf("%d. %s\n", i + , frits[i]);
    
    
    /* ポインタの変更 */
    frits[] = "leberry";
    
    printf("n=== 変更後 ===n");
    for (i = ; i < count; i++) 
        printf("%d. %s\n", i + , frits[i]);
    
    
    return ;

```

### 実践的なポインタ活用例 

#### 動的配列の操作

```c
#include <stdio.h>

/* 配列内の要素を逆順にする */
void reverse_array(int *arr, int size)
{

    int *start = arr;
    int *end = arr + size - ;
    int temp;
    
    while (start < end) 
        temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    


/* 配列を1回転させる（右につシフト） */
void rotate_right(int *arr, int size)
{

    int last = *(arr + size - );
    int i;
    
    for (i = size - ; i > ; i--) 
        *(arr + i) = *(arr + i - );
    
    *arr = last;


int main(void)
{

    int numbers[] = , , , , , , , ;
    int size = sizeof(numbers) / sizeof(numbers[]);
    int i;
    
    printf("元の配列: ");
    for (i = ; i < size; i++) 
        printf("%d ", numbers[i]);
    
    printf("n");
    
    /* 配列を逆順にする */
    reverse_array(numbers, size);
    printf("逆順後: ");
    for (i = ; i < size; i++) 
        printf("%d ", numbers[i]);
    
    printf("n");
    
    /* 配列を右に1回転 */
    rotate_right(numbers, size);
    printf("右1回転後: ");
    for (i = ; i < size; i++) 
        printf("%d ", numbers[i]);
    
    printf("n");
    
    return ;

```

#### ポインタを使ったソート

```c
#include <stdio.h>

/* ポインタを使ったバブルソート */
void bbble_sort_ptr(int *arr, int size)
{

    int i, j;
    int *ptr, *ptr;
    int temp;
    
    for (i = ; i < size - ; i++) 
        for (j = ; j < size -  - i; j++) 
            ptr = arr + j;
            ptr = arr + j + ;
            
            if (*ptr > *ptr) 
                temp = *ptr;
                *ptr = *ptr;
                *ptr = temp;
            
        
    


/* 2つの配列を比較 */
int compare_arrays(int *arr, int *arr, int size)
{

    int i;
    
    for (i = ; i < size; i++) 
        if (*(arr + i) != *(arr + i)) 
            return ;  /* 異なる */
        
    
    
    return ;  /* 同じ */


int main(void)
{

    int original[] = , , , , , , 9;
    int copy[] = , , , , , , 9;
    int size = sizeof(original) / sizeof(original[]);
    int i;
    
    printf("ソート前: ");
    for (i = ; i < size; i++) 
        printf("%d ", original[i]);
    
    printf("n");
    
    /* ソート実行 */
    bbble_sort_ptr(original, size);
    
    printf("ソート後: ");
    for (i = ; i < size; i++) 
        printf("%d ", original[i]);
    
    printf("n");
    
    /* 配列の比較 */
    if (compare_arrays(original, copy, size)) 
        printf("配列は同じですn");
     else 
        printf("配列は異なりますn");
    
    
    return ;

```

##  サンプルコード

### ポインタの基本操作

プログラムファイル: `examples/pointer_basic.c`

ポインタの宣言、初期化、基本的な操作を学習します。

**C99版**: [pointer_basic_c99.c](examples/pointer_basic_c99.c) - bool型、restrict修飾子、固定幅整数型を使用

### ポインタと配列

プログラムファイル: `examples/pointer_arrays.c`

ポインタと配列の関係、ポインタ演算を学習します。

**C99版**: [pointer_arrays_c99.c](examples/pointer_arrays_c99.c) - 可変長配列、複合リテラル、指定初期化子を使用

### ポインタと関数

プログラムファイル: `examples/pointer_functions.c`

関数引数、戻り値としてのポインタの使用方法を学習します。

**C99版**: [pointer_functions_c99.c](examples/pointer_functions_c99.c) - インライン関数、restrict修飾子、可変長配列パラメータを使用

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
   - 解答例: [solutions/ex1_pointer_swap.c](solutions/ex1_pointer_swap.c) (C90版) / [solutions/ex1_pointer_swap_c99.c](solutions/ex1_pointer_swap_c99.c) (C99版)

2. **配列とポインタ**
   - ポインタ演算を使って配列の要素を逆順に表示するプログラムを作成してください
   - 解答例: [solutions/ex2_array_reverse.c](solutions/ex2_array_reverse.c) (C90版) / [solutions/ex2_array_reverse_c99.c](solutions/ex2_array_reverse_c99.c) (C99版)

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

9. **データ構造**
   - ポインタを使って簡単なリンクリスト構造を実装してください

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

ポインタの基礎を理解したら、「構造体とポインタ」の実装をお待ちください。現在実装中です。

##  参考資料

- [C言語ポインタリファレンス](https://ja.cppreference.com/w/c/language/pointer)
- [ポインタ演算の詳細](https://ja.cppreference.com/w/c/language/operautor_arithmetic)
- [メモリモデルとポインタ](https://ja.cppreference.com/w/c/language/memory_model)
