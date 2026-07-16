# 第7章：配列の基本

## 対応するC規格

- **主要対象**：C90
- **学習内容**：1次元配列、多次元配列、初期化、走査、検索、集計

## 学習目標

この章では、同じ型のオブジェクトを連続して保持する配列を学びます。

- 配列を宣言し、初期化できる
- 有効な添字の範囲を説明できる
- ループで配列を検索・集計できる
- 2次元配列の行と列を正しく処理できる
- 配列とポインタを同一視せず、変換が起こる場面を説明できる

## 配列とは

配列は、同じ型の要素を連続して並べたオブジェクトです。
次の宣言は、`int`型の要素を5個持つ配列`values`を定義します。

```c
int values[5];
```

要素の添字は0から始まります。
要素数が5なら、有効な添字は0から4までです。

```c
values[0] = 10;
values[4] = 50;
```

`values[5]`へのアクセスは配列の範囲外であり、動作は未定義です。
Cは実行時に添字を自動検査しません。

## 配列の宣言

C90の固定長配列では、要素数に0より大きい整数定数式を指定します。

```c
#define SCORE_COUNT 5

int scores[SCORE_COUNT];
```

配列の要素型は完全オブジェクト型である必要があります。
要素数を後から変更することはできません。

## 配列の初期化

すべての要素を列挙できます。

```c
int values[5] = { 10, 20, 30, 40, 50 };
```

初期化子が要素数より少ない場合、残りの要素は0で初期化されます。

```c
int values[5] = { 1, 2 }; /* { 1, 2, 0, 0, 0 } */
```

要素数を省略すると、初期化子から要素数が決まります。

```c
int values[] = { 10, 20, 30 };
```

すべての要素を0で初期化する一般的な書き方です。

```c
int values[100] = { 0 };
```

初期化後の配列へ別の配列を代入することはできません。

```c
int a[3] = { 1, 2, 3 };
int b[3];

/* b = a; */ /* Constraint violation. */
```

要素をコピーするには、ループまたは適切なライブラリ関数を使います。

```c
int i;

for (i = 0; i < 3; i++) {
    b[i] = a[i];
}
```

## 配列を走査する

配列全体を処理するループでは、添字を0から要素数未満まで進めます。

```c
#include <stddef.h>
#include <stdio.h>

int main(void)
{
    int values[] = { 10, 20, 30, 40, 50 };
    size_t count = sizeof values / sizeof values[0];
    size_t i;

    for (i = 0; i < count; i++) {
        printf("%d\n", values[i]);
    }

    return 0;
}
```

`sizeof values / sizeof values[0]`は、`values`が配列として見えている場所で要素数を求めます。
関数仮引数として宣言した配列には使えません。

## 線形探索

配列を先頭から調べ、目的の値が見つかった位置を返します。
見つからない場合は、添字として使わない負の値を返します。

```c
int find_value(const int values[], int count, int target)
{
    int i;

    for (i = 0; i < count; i++) {
        if (values[i] == target) {
            return i;
        }
    }

    return -1;
}
```

関数仮引数の`const int values[]`は、`const int *values`へ調整されます。
配列全体の要素数は関数へ自動では渡らないため、`count`を別の引数として渡します。

## 最大値、最小値、平均

最初の要素を初期値に使う場合、要素数が1以上であることを先に確認します。

```c
#include <stddef.h>

int max_value(const int values[], int count, int *result)
{
    int i;
    int max;

    if (values == NULL || result == NULL || count <= 0) {
        return 0;
    }

    max = values[0];

    for (i = 1; i < count; i++) {
        if (values[i] > max) {
            max = values[i];
        }
    }

    *result = max;
    return 1;
}
```

平均を求める場合は、0による除算を避けます。
加算結果が型の範囲を超える可能性も考慮し、データの範囲に応じて集計用の型を選びます。

```c
#include <stddef.h>

double average(const int values[], int count)
{
    long sum = 0;
    int i;

    if (values == NULL || count <= 0) {
        return 0.0;
    }

    for (i = 0; i < count; i++) {
        sum += values[i];
    }

    return (double)sum / count;
}
```

この例でも、要素数と値の範囲によっては`long`の加算がオーバーフローします。
実際の入力上限を定めてから型を選んでください。

## 要素を逆順に並べる

配列の両端から要素を交換します。

```c
void reverse(int values[], int count)
{
    int left = 0;
    int right = count - 1;

    while (left < right) {
        int temporary = values[left];
        values[left] = values[right];
        values[right] = temporary;
        left++;
        right--;
    }
}
```

このコードはC90でも有効です。
`temporary`は`while`本体の複合文で、文より前に宣言されています。

## 2次元配列

2次元配列は、配列を要素に持つ配列です。
次の`matrix`は、3個の「`int`を4個持つ配列」を要素に持ちます。

```c
int matrix[3][4];
```

`matrix[row][column]`で要素へアクセスします。
有効な行添字は0から2、列添字は0から3です。

```c
int matrix[2][3] = {
    { 1, 2, 3 },
    { 4, 5, 6 }
};
```

Cの多次元配列は行優先で連続配置されます。
この例では、`matrix[0][0]`から`matrix[0][2]`が並び、その後に2行目が続きます。

```c
int row;
int column;

for (row = 0; row < 2; row++) {
    for (column = 0; column < 3; column++) {
        printf("%d ", matrix[row][column]);
    }

    printf("\n");
}
```

2次元配列を関数へ渡すときは、ポインタ演算に必要な列数を型に含めます。

```c
void print_matrix(const int matrix[][3], int rows)
{
    int row;
    int column;

    for (row = 0; row < rows; row++) {
        for (column = 0; column < 3; column++) {
            printf("%d ", matrix[row][column]);
        }

        printf("\n");
    }
}
```

## 配列からポインタへの変換

配列式は、多くの式の中で先頭要素へのポインタに変換されます。
ただし、`sizeof`のオペランドや単項`&`のオペランドなどでは、この変換は起こりません。

```c
int values[5];
int *first = values;       /* &values[0] */
size_t bytes = sizeof values;
```

配列とポインタは別の型であり、同じオブジェクトではありません。
この違いは、次章で詳しく扱います。

## よくある誤り

### 範囲外アクセス

```c
int values[5] = { 0 };
values[5] = 10; /* Undefined behavior. */
```

### 初期化前の読み取り

```c
int values[5];
printf("%d\n", values[0]); /* Indeterminate value. */
```

### バイト数と要素数の混同

```c
int values[10];
size_t bytes = sizeof values;
size_t count = sizeof values / sizeof values[0];
```

`bytes`はバイト数、`count`は要素数です。

## コンパイル

```bash
gcc -std=c90 -Wall -Wextra -pedantic examples/array_basics.c -o array_basics
./array_basics
```

Makefileを使う場合は、次のコマンドを実行します。

```bash
make all
make run-all
make clean
```

実装例は、次のファイルにあります。

- [array_basics.c](examples/array_basics.c)
- [multidimensional_arrays.c](examples/multidimensional_arrays.c)

## C99で追加された配列機能

C99では、指定初期化子、複合リテラル、可変長配列が追加されました。
C11とC17では可変長配列への対応が処理系の任意機能です。

```c
int values[10] = { [2] = 5, [7] = 9 };
```

## 演習問題

[演習問題](exercises/)では、探索、集計、並べ替え、多次元配列を練習します。
