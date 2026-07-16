# 第6章：繰り返し処理

## 対応するC規格

- **主要対象**：C90
- **学習内容**：`for`、`while`、`do-while`、`break`、`continue`、入れ子のループ

## 学習目標

この章では、同じ処理を条件に応じて繰り返す方法を学びます。

- 反復回数と終了条件に応じてループを選べる
- `for`文の各式が評価される順序を説明できる
- `break`と`continue`の制御先を説明できる
- 配列の境界を守るループを記述できる

## `for`文

`for`文は、初期化、継続条件、反復式を1か所にまとめます。

```c
for (initialization; condition; iteration) {
    statement;
}
```

実行順序は次のとおりです。

1. 初期化を1回だけ実行する
2. 継続条件を評価する
3. 条件が0ならループを終了する
4. 本体を実行する
5. 反復式を評価し、手順2へ戻る

C90では、ループ変数を`for`文より前で宣言します。

```c
#include <stdio.h>

int main(void)
{
    int i;

    for (i = 0; i < 5; i++) {
        printf("%d\n", i);
    }

    return 0;
}
```

配列を先頭から末尾まで処理するときは、添字の開始値と終了条件を配列の要素数に対応させます。

```c
int values[5] = { 10, 20, 30, 40, 50 };
int i;

for (i = 0; i < 5; i++) {
    printf("%d\n", values[i]);
}
```

`i <= 5`とすると、最後の反復で`values[5]`へアクセスし、配列の範囲を超えます。

## `while`文

`while`文は、本体を実行する前に継続条件を評価します。
最初の評価が偽なら、本体は一度も実行されません。

```c
while (condition) {
    statement;
}
```

入力の成否と終了条件を同時に検査する例です。

```c
#include <stdio.h>

int main(void)
{
    int number;

    while (scanf("%d", &number) == 1 && number > 0) {
        printf("value: %d\n", number);
    }

    return 0;
}
```

`scanf`が1を返すのは、1個の変換に成功した場合です。
数値へ変換できない入力では0を、入力の終端または読み取りエラーでは`EOF`を返します。

## `do-while`文

`do-while`文は、本体を実行した後で継続条件を評価します。
文へ到達した場合、本体は少なくとも1回実行されます。

```c
do {
    statement;
} while (condition);
```

`while (condition)`の末尾にはセミコロンが必要です。

```c
#include <stdio.h>

int main(void)
{
    int choice;

    do {
        printf("1: continue, 0: exit\n");

        if (scanf("%d", &choice) != 1) {
            return 1;
        }
    } while (choice != 0);

    return 0;
}
```

## `break`文

`break`は、最も内側にあるループまたは`switch`文を終了します。

```c
int i;

for (i = 0; i < 100; i++) {
    if (i == 5) {
        break;
    }

    printf("%d\n", i);
}
```

入れ子のループで`break`を実行しても、終了するのは最も内側のループだけです。
外側のループも終了する必要がある場合は、フラグを検査する、処理を関数へ分けて`return`する、または終了先を明示した構造にします。

```c
int row;
int column;
int found = 0;

for (row = 0; row < 3 && !found; row++) {
    for (column = 0; column < 3; column++) {
        if (matrix[row][column] == target) {
            found = 1;
            break;
        }
    }
}
```

## `continue`文

`continue`は、現在の反復の残りを飛ばして次の反復へ進みます。
`for`文では反復式へ、`while`文と`do-while`文では継続条件の評価へ移ります。

```c
int i;

for (i = 1; i <= 10; i++) {
    if (i % 2 == 0) {
        continue;
    }

    printf("%d\n", i);
}
```

`while`文で更新処理より前に`continue`すると、更新が実行されず無限ループになることがあります。

```c
int i = 0;

while (i < 10) {
    i++;

    if (i % 2 == 0) {
        continue;
    }

    printf("%d\n", i);
}
```

## 入れ子のループ

2次元の表や配列では、外側のループで行を、内側のループで列を処理します。

```c
int row;
int column;

for (row = 1; row <= 3; row++) {
    for (column = 1; column <= 3; column++) {
        printf("%d ", row * column);
    }

    printf("\n");
}
```

外側が`m`回、内側が各回`n`回実行される場合、本体の実行回数は`m * n`回です。
データ量が大きい場合は、この回数が処理時間へ与える影響を確認します。

## 無限ループ

継続条件を省略した`for`文と、0以外の定数を条件にした`while`文は、明示的に終了しない限り反復を続けます。

```c
for (;;) {
    if (should_stop()) {
        break;
    }

    process_one_item();
}
```

```c
while (1) {
    if (should_stop()) {
        break;
    }

    process_one_item();
}
```

イベントループや待受処理では無限ループが必要な場合があります。
終了条件、エラー処理、外部から停止する方法を設計してください。

## ループを安全に書く

### 境界を式で対応させる

配列の要素数を配列から求められる場所では、上限を重複して記述しない方法があります。

```c
#include <stddef.h>

int values[10];
size_t i;
size_t count = sizeof values / sizeof values[0];

for (i = 0; i < count; i++) {
    values[i] = 0;
}
```

### 終了条件を更新する

ループ内で条件に関わる値が変化しない場合、ループが終了しない可能性があります。

```c
int i = 0;

while (i < 10) {
    printf("%d\n", i);
    i++;
}
```

### 空文を確認する

次の`for`文の本体は、末尾のセミコロンによる空文です。

```c
for (i = 0; i < 10; i++); /* Empty loop body. */
{
    printf("executed once\n");
}
```

## コンパイル

```bash
gcc -std=c90 -Wall -Wextra -pedantic examples/basic_for.c -o basic_for
./basic_for
```

Makefileを使う場合は、次のコマンドを実行します。

```bash
make all
make run-all
make clean
```

実装例は、次のファイルにあります。

- [basic_for.c](examples/basic_for.c)
- [while_loop.c](examples/while_loop.c)
- [while_dowhile.c](examples/while_dowhile.c)
- [break_continue.c](examples/break_continue.c)
- [nested_loops.c](examples/nested_loops.c)

## C99以降との違い

C99以降では、`for`文の初期化部で変数を宣言できます。

```c
for (int i = 0; i < 10; i++) {
    printf("%d\n", i);
}
```

この`i`のスコープは`for`文を含む範囲に限定されます。

## 演習問題

[演習問題](exercises/)では、集計、入力ループ、入れ子のループ、終了条件を練習します。
