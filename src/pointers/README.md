# 第8章：ポインタの基本

## 対応するC規格

- **主要対象**：C90
- **学習内容**：ポインタ、間接参照、配列との関係、関数引数、動的メモリ確保

## 学習目標

この章では、オブジェクトや関数を指すポインタを学びます。

- ポインタを宣言し、オブジェクトのアドレスを格納できる
- 間接参照が有効になる条件を説明できる
- 配列からポインタへの変換とポインタ演算の範囲を説明できる
- ポインタを関数へ渡して呼び出し元の値を変更できる
- 動的に確保したメモリの所有権と寿命を管理できる

## ポインタとは

ポインタ型のオブジェクトは、別のオブジェクトまたは関数を指す値を格納します。
指す対象の型は、宣言の`*`より左側に記述します。

```c
int *int_pointer;
double *double_pointer;
```

未初期化の自動変数であるポインタは不定値を持ちます。
有効なアドレスまたはヌルポインタで初期化してから使用します。

```c
int *pointer = NULL;
```

ヌルポインタは、どのオブジェクトも指していないことを表します。
ヌルポインタを間接参照すると、動作は未定義です。

## アドレス演算子と間接演算子

単項`&`演算子は、オブジェクトまたは関数を指すポインタを作ります。
単項`*`演算子は、有効なポインタが指す対象へアクセスします。

```c
#include <stdio.h>

int main(void)
{
    int value = 42;
    int *pointer = &value;

    printf("value: %d\n", value);
    printf("through pointer: %d\n", *pointer);
    printf("address: %p\n", (void *)pointer);
    return 0;
}
```

`printf`の`%p`に対応する引数は`void *`です。
オブジェクトへのポインタは、表示時に`void *`へ変換します。
表示形式は処理系定義であり、常に16進表記になるとは規定されていません。

間接参照した式は、指しているオブジェクトを表す左辺値になります。

```c
int value = 10;
int *pointer = &value;

*pointer = 20; /* value becomes 20. */
```

## ポインタと配列

配列はポインタではありません。
ただし、配列式は多くの式の中で、先頭要素を指すポインタへ変換されます。

```c
int values[5] = { 10, 20, 30, 40, 50 };
int *pointer = values; /* Same value as &values[0]. */
```

`values[i]`は`*(values + i)`と同じ規則で定義されます。

```c
int i;

for (i = 0; i < 5; i++) {
    printf("%d\n", *(pointer + i));
}
```

### 配列とポインタが異なる場面

`sizeof`のオペランドでは、配列からポインタへの変換は起こりません。

```c
int values[5];
int *pointer = values;

sizeof values;  /* Size of the entire array. */
sizeof pointer; /* Size of the pointer object. */
```

単項`&`のオペランドでも変換は起こりません。
`&values`の型は「5個の`int`の配列へのポインタ」であり、`&values[0]`の型である`int *`とは異なります。

## ポインタ演算

オブジェクトへのポインタには、整数を加減できます。
演算結果は、指している配列要素を基準に要素単位で移動します。

```c
int values[5];
int *begin = &values[0];
int *third = begin + 2;
```

ポインタ演算で定義される範囲は、同じ配列オブジェクトの要素と、その末尾の1つ後ろまでです。
末尾の1つ後ろを指すポインタは比較やループ終了判定に使えますが、間接参照できません。

```c
int *current;
int *end = values + 5;

for (current = values; current != end; current++) {
    printf("%d\n", *current);
}
```

別々の配列を指すポインタ同士の減算や、順序関係の比較には依存しません。
同じ配列内の2つのポインタを減算した結果の型は`ptrdiff_t`です。

## ポインタを関数へ渡す

Cの関数引数は値渡しです。
ポインタを値として渡すと、関数はそのポインタが指すオブジェクトを変更できます。

```c
void swap(int *left, int *right)
{
    int temporary;

    if (left == NULL || right == NULL) {
        return;
    }

    temporary = *left;
    *left = *right;
    *right = temporary;
}
```

```c
int a = 10;
int b = 20;

swap(&a, &b);
```

関数がヌルポインタを受け付けない設計なら、その事前条件を関数の契約として文書化します。
ヌルポインタをエラーとして処理する設計なら、間接参照より前に検査します。

## 配列を関数へ渡す

関数仮引数の配列宣言は、対応するポインタ型へ調整されます。
次の2つの宣言は、関数型として同じです。

```c
void process(int values[], int count);
void process(int *values, int count);
```

要素数は自動では渡らないため、別の引数で渡します。

```c
int sum_array(const int values[], int count)
{
    int sum = 0;
    int i;

    if (values == NULL || count < 0) {
        return 0;
    }

    for (i = 0; i < count; i++) {
        sum += values[i];
    }

    return sum;
}
```

この例では、加算結果が`int`の範囲を超えないことを呼び出し側の前提としています。
エラーと正しい合計値0を区別する必要がある場合は、戻り値と出力引数を分けます。

## 関数からポインタを返す

関数から返すポインタは、関数終了後も生存しているオブジェクトを指す必要があります。
自動記憶域期間のローカル変数へのポインタを返してはいけません。

```c
int *invalid_pointer(void)
{
    int local = 10;
    return &local; /* Invalid after the function returns. */
}
```

静的記憶域期間のオブジェクトへのポインタは、関数終了後も有効です。
ただし、呼び出しごとに同じオブジェクトを共有するため、再入可能性や並行実行に注意が必要です。

```c
int *shared_value(void)
{
    static int value;
    return &value;
}
```

呼び出し側へ所有権を渡す必要がある場合は、動的メモリ確保を使う方法もあります。

## 文字列とポインタ

文字列リテラルから配列を初期化すると、変更可能な配列が作られます。

```c
char text[] = "Hello";
text[0] = 'h';
```

文字列リテラルを指すポインタを通じて文字を変更すると、動作は未定義です。
C90でも、変更しない意図を`const char *`で表します。

```c
const char *text = "Hello";
```

文字列はヌル文字`'\0'`で終わります。
文字列処理では、配列の容量と終端文字の領域を管理します。

## 2次元配列へのポインタ

2次元配列の各要素は行を表す配列です。

```c
int matrix[3][4];
int (*row_pointer)[4] = matrix;
```

`row_pointer + 1`は、`int`1個ではなく、`int`4個からなる次の行へ進みます。

```c
matrix[2][3] == *(*(matrix + 2) + 3)
```

関数へ渡す場合も、最初の次元以外の要素数を型に含めます。

```c
void clear_matrix(int matrix[][4], int rows)
{
    int row;
    int column;

    for (row = 0; row < rows; row++) {
        for (column = 0; column < 4; column++) {
            matrix[row][column] = 0;
        }
    }
}
```

## 動的メモリ確保

`malloc`、`calloc`、`realloc`、`free`は`<stdlib.h>`で宣言されています。
Cでは、`malloc`が返す`void *`をオブジェクトへのポインタへ暗黙に変換できるため、キャストは不要です。

```c
#include <stdlib.h>

int *allocate_values(size_t count)
{
    int *values;

    if (count == 0 || count > (size_t)-1 / sizeof *values) {
        return NULL;
    }

    values = malloc(count * sizeof *values);
    return values;
}
```

`malloc`は、要求した大きさの領域を確保できない場合にヌルポインタを返します。
成功時に得られる領域の内容は不定です。

```c
int *values = allocate_values(100);

if (values == NULL) {
    return 1;
}

/* Use values here. */
free(values);
values = NULL;
```

`free`へ渡せるのは、動的メモリ確保関数が返したポインタ、またはヌルポインタです。
同じ領域を2回解放したり、配列の途中を指すポインタを渡したりすると、動作は未定義です。

### `calloc`

`calloc`は、要素数と1要素の大きさを受け取り、確保した全ビットを0にします。
これは整数型の0を作る用途には使えますが、すべての型についてヌルポインタや浮動小数点の`0.0`と同じ表現になることを標準Cは保証していません。

```c
int *values = calloc(count, sizeof *values);
```

要素数と要素サイズの積の処理は`calloc`側が行いますが、確保失敗を示すヌルポインタは検査します。

### `realloc`

`realloc`が失敗した場合、元の領域は解放されず、そのまま有効です。
戻り値を元のポインタへ直接代入すると、失敗時に元のアドレスを失います。

```c
int *temporary;

temporary = realloc(values, new_count * sizeof *values);

if (temporary == NULL) {
    /* values still refers to the original allocation. */
} else {
    values = temporary;
}
```

この例では、`new_count * sizeof *values`が`size_t`の範囲を超えないことを事前に確認する必要があります。
大きさ0の`realloc`には規格版や処理系による差があるため、解放したい場合は`free`を明示的に使います。

## 二重ポインタ

二重ポインタは、ポインタオブジェクトを指します。
関数内で呼び出し元のポインタ値そのものを変更するときに使えます。

```c
int allocate_one(int **result)
{
    int *value;

    if (result == NULL) {
        return 0;
    }

    value = malloc(sizeof *value);

    if (value == NULL) {
        return 0;
    }

    *value = 0;
    *result = value;
    return 1;
}
```

呼び出し側は、成功時に受け取った領域を`free`します。

## 関数ポインタ

関数ポインタは、互換性のある関数型を持つ関数を指します。

```c
int add(int left, int right)
{
    return left + right;
}

int main(void)
{
    int (*operation)(int, int) = add;
    int result = operation(2, 3);

    return result == 5 ? 0 : 1;
}
```

オブジェクトへのポインタと関数へのポインタは別の分類です。
標準Cは、関数ポインタと`void *`を相互変換できるとは保証していません。

## よくある誤り

### 未初期化ポインタ

```c
int *pointer;
*pointer = 10; /* Undefined behavior. */
```

### 解放後の使用

```c
int *pointer = malloc(sizeof *pointer);

if (pointer != NULL) {
    free(pointer);
    /* *pointer = 10; */ /* Undefined behavior. */
    pointer = NULL;
}
```

### 配列の範囲外への移動

ポインタを同じ配列の末尾よりさらに先へ進める演算自体が未定義です。

```c
int values[5];
int *invalid = values + 6; /* Undefined behavior. */
```

### メモリリーク

所有している動的領域を指す最後のポインタを失うと、その領域を解放できなくなります。
どの関数が解放責任を持つかをインターフェースで決めます。

## コンパイル

```bash
gcc -std=c90 -Wall -Wextra -pedantic examples/pointer_basic.c -o pointer_basic
./pointer_basic
```

Makefileを使う場合は、次のコマンドを実行します。

```bash
make all
make run-all
make clean
```

実装例は、次のファイルにあります。

- [pointer_basic.c](examples/pointer_basic.c)
- [pointer_arrays.c](examples/pointer_arrays.c)
- [pointer_functions.c](examples/pointer_functions.c)

## C99で追加された関連機能

C99では、`restrict`修飾子、可変長配列、複合リテラル、`<stdint.h>`などが追加されました。
`restrict`は、ポインタが指すオブジェクトへのアクセス関係について、プログラマが処理系へ契約を示す機能です。
契約に違反した場合は未定義動作になるため、単なる最適化の要望として追加してはいけません。

## 演習問題

[演習問題](exercises/)では、間接参照、配列走査、関数引数、動的メモリ管理を練習します。
