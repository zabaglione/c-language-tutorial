# ポインタ基礎
## 対応C規格
- **主要対象:** C90
- **学習内容:** ポインタの基本概念、ポインタと配列、ポインタと関数、メモリ管理の基礎

## 学習目標
この章を完了すると、以下のことができるようになります。
- ポインタの基本概念を完全に理解する
- ポインタを使った変数の操作ができる
- ポインタと配列の関係を理解する
- 関数でポインタを適切に使える
- 動的メモリ割り当ての基礎を理解する

## 概要と詳細

### ポインタとは？
ポインタは、他の変数のメモリアドレス（住所）を格納する変数です。C言語の最も強力で重要な機能の一つです。

#### 日常生活でのポインタ
ポインタを理解するために、身近な例を考えてみましょう。

1. **住所録**
   - 友人の名前 = 変数名
   - 友人の住所 = ポインタ（メモリアドレス）
   - 友人の家 = 実際のデータ

2. **図書館の目録**
   - 本のタイトル = 変数名
   - 本の所在（A棚3段目） = ポインタ
   - 実際の本 = データ

3. **リンク集**
   - サイト名 = 変数名
   - URL = ポインタ
   - 実際のWebページ = データ

#### なぜポインタが必要なの？
1. **効率的なデータ操作** - 大きなデータをコピーせず、アドレスだけを渡す
2. **動的メモリ管理** - 実行時にメモリを確保・解放
3. **関数間でのデータ共有** - 元の変数を直接変更
4. **複雑なデータ構造** - リスト、ツリーなどの実装
5. **配列の効率的な処理** - 配列要素への高速アクセス

### ポインタの基本概念

#### ポインタの宣言
```c
int *ptr;        /* int型へのポインタ */
char *str_ptr;   /* char型へのポインタ */
double *d_ptr;   /* double型へのポインタ */
```

#### アドレス演算子（&）
変数のアドレスを取得します。
```c
int num = 42;
int *ptr = &num;  /* numのアドレスをptrに格納 */
```

#### 間接参照演算子（*）
ポインタが指す場所の値にアクセスします。
```c
int value = *ptr;  /* ptrが指す場所の値を取得 */
*ptr = 100;        /* ptrが指す場所に100を代入 */
```

### ポインタの基本操作

#### 基本的な使い方
```c
int num = 42;
int *ptr;

ptr = &num;        /* numのアドレスをptrに代入 */
printf("numの値: %d\n", num);
printf("numのアドレス: %p\n", &num);
printf("ptrの値（アドレス）: %p\n", ptr);
printf("ptrが指す値: %d\n", *ptr);
```

#### ポインタを使った値の変更
```c
int num = 10;
int *ptr = &num;

printf("変更前: %d\n", num);  /* 10 */
*ptr = 20;
printf("変更後: %d\n", num);  /* 20 */
```

### ポインタと配列の関係

#### 配列名はポインタ
C言語では、配列名は最初の要素へのポインタと同じです。
```c
int arr[5] = {10, 20, 30, 40, 50};
int *ptr = arr;  /* arr は &arr[0] と同じ */
```

#### ポインタ演算
ポインタには加算・減算ができます。
```c
int arr[5] = {10, 20, 30, 40, 50};
int *ptr = arr;

printf("%d\n", *ptr);      /* 10 (arr[0]) */
printf("%d\n", *(ptr+1));  /* 20 (arr[1]) */
printf("%d\n", *(ptr+2));  /* 30 (arr[2]) */
```

#### 配列のポインタによる操作
```c
int arr[5] = {1, 2, 3, 4, 5};
int *ptr = arr;
int i;

/* ポインタを使った配列要素のアクセス */
for (i = 0; i < 5; i++) {
    printf("arr[%d] = %d\n", i, *(ptr + i));
}

/* ポインタのインクリメント */
for (ptr = arr; ptr < arr + 5; ptr++) {
    printf("値: %d\n", *ptr);
}
```

### ポインタと関数

#### 関数の引数としてのポインタ
関数で元の変数を変更するためにポインタを使用します。

```c
/* 値を交換する関数 */
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main(void)
{
    int x = 10, y = 20;
    
    printf("交換前: x=%d, y=%d\n", x, y);
    swap(&x, &y);
    printf("交換後: x=%d, y=%d\n", x, y);
    
    return 0;
}
```

#### 配列を関数に渡す
```c
/* 配列の合計を計算する関数 */
int array_sum(int *arr, int size)
{
    int sum = 0;
    int i;
    
    for (i = 0; i < size; i++) {
        sum += arr[i];  /* または sum += *(arr + i); */
    }
    
    return sum;
}

int main(void)
{
    int numbers[5] = {1, 2, 3, 4, 5};
    int total = array_sum(numbers, 5);
    printf("合計: %d\n", total);
    return 0;
}
```

#### 関数からポインタを返す
```c
/* 配列の最大値を指すポインタを返す */
int* find_max(int *arr, int size)
{
    int *max_ptr = arr;
    int i;
    
    for (i = 1; i < size; i++) {
        if (*(arr + i) > *max_ptr) {
            max_ptr = arr + i;
        }
    }
    
    return max_ptr;
}
```

### 文字列とポインタ

#### 文字列の表現方法
```c
char str1[] = "Hello";     /* 文字配列 */
char *str2 = "World";      /* 文字列リテラルへのポインタ */
```

#### 文字列の操作
```c
char *str = "Hello";
char *ptr = str;

/* 文字列を1文字ずつ表示 */
while (*ptr != '\0') {
    printf("%c", *ptr);
    ptr++;
}
printf("\n");
```

### 多次元配列とポインタ

#### 2次元配列へのポインタ
```c
int matrix[3][4] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12}
};

int (*ptr)[4] = matrix;  /* 4要素のint配列へのポインタ */
```

#### 2次元配列の要素アクセス
```c
/* 以下はすべて同じ要素にアクセス */
matrix[1][2];        /* 通常のアクセス */
(*(matrix + 1))[2];  /* ポインタ演算1 */
*(*(matrix + 1) + 2); /* ポインタ演算2 */
```

### 動的メモリ割り当て

#### malloc()とfree()
```c
#include <stdlib.h>

int *ptr;
int size = 5;

/* メモリの動的確保 */
ptr = (int*)malloc(size * sizeof(int));

if (ptr == NULL) {
    printf("メモリ確保に失敗しました\n");
    return 1;
}

/* メモリの使用 */
for (i = 0; i < size; i++) {
    ptr[i] = i * 2;
}

/* メモリの解放 */
free(ptr);
ptr = NULL;  /* ダングリングポインタの防止 */
```

#### calloc()とrealloc()
```c
/* calloc: ゼロ初期化されたメモリを確保 */
int *arr = (int*)calloc(5, sizeof(int));

/* realloc: メモリサイズを変更 */
arr = (int*)realloc(arr, 10 * sizeof(int));

free(arr);
```

### ポインタのポインタ

#### 2重ポインタの概念
```c
int num = 42;
int *ptr = &num;      /* numへのポインタ */
int **dptr = &ptr;    /* ptrへのポインタ */

printf("num = %d\n", num);
printf("*ptr = %d\n", *ptr);
printf("**dptr = %d\n", **dptr);
```

#### 2重ポインタの用途
- 関数でポインタ自体を変更する
- 動的な2次元配列の作成
- 複雑なデータ構造の実装

### よくある間違いとデバッグ

#### 1. 未初期化ポインタ
**問題:** ポインタを初期化せずに使用
```c
int *ptr;
*ptr = 10;  /* 危険！未初期化ポインタの使用 */
```

**対策:**
```c
int *ptr = NULL;  /* NULLで初期化 */
int num;
ptr = &num;       /* 適切なアドレスを代入してから使用 */
*ptr = 10;        /* 安全 */
```

#### 2. ダングリングポインタ
**問題:** 解放されたメモリを指すポインタ
```c
int *ptr = (int*)malloc(sizeof(int));
free(ptr);
*ptr = 10;  /* 危険！解放済みメモリにアクセス */
```

**対策:**
```c
int *ptr = (int*)malloc(sizeof(int));
free(ptr);
ptr = NULL;  /* NULLを代入 */
```

#### 3. 配列の境界外アクセス
**問題:** ポインタ演算での範囲外アクセス
```c
int arr[5] = {1, 2, 3, 4, 5};
int *ptr = arr;
printf("%d\n", *(ptr + 10));  /* 危険！境界外アクセス */
```

**対策:**
```c
int arr[5] = {1, 2, 3, 4, 5};
int *ptr = arr;
if (ptr + 2 < arr + 5) {  /* 境界チェック */
    printf("%d\n", *(ptr + 2));
}
```

#### 4. メモリリーク
**問題:** 確保したメモリを解放し忘れ
```c
void function()
{
    int *ptr = (int*)malloc(100 * sizeof(int));
    /* free(ptr); を忘れる */
}  /* メモリリーク発生 */
```

**対策:**
```c
void function()
{
    int *ptr = (int*)malloc(100 * sizeof(int));
    if (ptr == NULL) return;
    
    /* 処理 */
    
    free(ptr);  /* 必ず解放 */
    ptr = NULL;
}
```

### ポインタの高度な使用法

#### 関数ポインタ
```c
/* 関数の定義 */
int add(int a, int b) { return a + b; }
int multiply(int a, int b) { return a * b; }

/* 関数ポインタの使用 */
int (*operation)(int, int);
operation = add;
printf("5 + 3 = %d\n", operation(5, 3));

operation = multiply;
printf("5 * 3 = %d\n", operation(5, 3));
```

#### 構造体とポインタ
```c
struct point {
    int x;
    int y;
};

struct point p = {10, 20};
struct point *ptr = &p;

/* 構造体メンバへのアクセス */
printf("x = %d, y = %d\n", ptr->x, ptr->y);
/* または */
printf("x = %d, y = %d\n", (*ptr).x, (*ptr).y);
```

## 実例コード
完全な実装例は以下のファイルを参照してください。

### ポインタの基本操作
- [pointer_basics.c](examples/pointer_basics.c) - C90準拠版
- [pointer_basics_c99.c](examples/pointer_basics_c99.c) - C99準拠版

### ポインタと配列
- [pointer_arrays.c](examples/pointer_arrays.c) - C90準拠版
- [pointer_arrays_c99.c](examples/pointer_arrays_c99.c) - C99準拠版

### 動的メモリ管理
- [dynamic_memory.c](examples/dynamic_memory.c) - C90準拠版
- [dynamic_memory_c99.c](examples/dynamic_memory_c99.c) - C99準拠版

## コンパイル方法

### 基本的なコンパイル（C90準拠）
```bash
gcc -std=c90 -Wall -Wextra -pedantic pointer_basics.c -o pointer_basics
```

### Makefileを使用した場合
```bash
# 全てのプログラムをコンパイル
make all
# 特定のプログラムをコンパイル
make pointer_basics
# C99版をコンパイル
make pointer_basics_c99
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

### 学習のコツ
1. **視覚化**: メモリ図を描いてポインタの動作を理解
2. **段階的学習**: 基本→配列→関数→動的メモリの順で学習
3. **デバッグ技術**: printfでアドレスと値を出力して確認
4. **実践練習**: 小さなプログラムから始めて徐々に複雑に

## 注意事項とベストプラクティス

### セキュリティの考慮
1. **NULL チェック**: ポインタ使用前の NULL チェック
2. **境界チェック**: 配列アクセス時の範囲確認
3. **メモリ管理**: malloc/free のペア、ダブルフリーの防止
4. **初期化**: ポインタの適切な初期化

### パフォーマンスの最適化
1. **ポインタ演算**: 配列アクセスの高速化
2. **参照渡し**: 大きなデータのコピー回避
3. **キャッシュ効率**: メモリアクセスパターンの最適化

## 次の章へ
[第11章: 構造体とポインタ](../structures/README.md)

## 参考資料
- examples/ - 実装例（C90、C99両対応）
- exercises/ - 演習問題
- solutions/ - 解答例
- [C標準ライブラリリファレンス](https://en.cppreference.com/w/c)
- [セキュアコーディング標準](https://wiki.sei.cmu.edu/confluence/pages/viewpage.action?pageId=87152177)