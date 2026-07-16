# 第5章：条件分岐

## 対応するC規格

- **主要対象**：C90
- **学習内容**：`if`、`else`、`switch`、条件演算子、条件式の注意点

## 学習目標

この章では、条件に応じて実行する処理を選ぶ方法を学びます。

- `if`文と`if-else`文を記述できる
- 複数の条件を検査する順序を設計できる
- `switch`文の`case`、`break`、フォールスルーを説明できる
- 代入と比較、浮動小数点比較の誤りを避けられる

## 条件式

C90では、条件式の値が0なら偽、0以外なら真です。
関係演算子と論理演算子の結果は、`int`の0または1になります。

```c
if (count > 0) {
    printf("items available\n");
}
```

## `if`文

`if`文は、条件が真の場合に文を実行します。

```c
if (condition) {
    statement;
}
```

本体が1文だけでも波括弧を付けると、後から文を追加したときの誤りを防ぎやすくなります。

```c
if (score >= 60) {
    printf("passed\n");
    passed_count++;
}
```

波括弧がない場合、`if`が制御するのは直後の1文だけです。

```c
if (score >= 60)
    printf("passed\n");
passed_count++; /* Always executed. */
```

## `if-else`文

`if-else`文は、条件が真なら最初の文を、偽なら`else`側の文を実行します。

```c
if (age >= 18) {
    printf("adult\n");
} else {
    printf("minor\n");
}
```

入力値を前提とする処理では、正常系より先に不正値を処理すると、入れ子を浅くできます。

```c
if (amount <= 0) {
    printf("invalid amount\n");
} else if (amount > balance) {
    printf("insufficient balance\n");
} else {
    balance -= amount;
    printf("withdrawal completed\n");
}
```

## `else if`による複数分岐

条件は上から順に評価され、最初に真になった分岐だけを実行します。
範囲が重なる場合は、より限定された条件または大きい境界から並べます。

```c
if (score >= 90) {
    grade = 'A';
} else if (score >= 80) {
    grade = 'B';
} else if (score >= 70) {
    grade = 'C';
} else if (score >= 60) {
    grade = 'D';
} else {
    grade = 'F';
}
```

`score >= 60`を最初に置くと、90点もその分岐で処理されます。
各条件がどの範囲を担当するかを確認してください。

## 入れ子の`if`文

条件の中で追加条件を検査する場合は、`if`文を入れ子にできます。

```c
if (temperature >= 25) {
    if (is_raining) {
        printf("warm and rainy\n");
    } else {
        printf("warm and dry\n");
    }
}
```

波括弧を省略した入れ子では、`else`は対応可能な最も近い`if`へ結び付きます。
意図を明確にするため、入れ子では波括弧を省略しません。

条件を論理演算子でまとめた方が読みやすい場合もあります。

```c
if (age >= 18 && has_license) {
    printf("eligible\n");
}
```

ただし、条件ごとに異なるエラーを示す必要がある場合は、分岐を分けます。

## `switch`文

`switch`文は、整数型または列挙型の式の値に応じて処理を選びます。
各`case`には、変換後に重複しない整数定数式を指定します。

```c
switch (choice) {
case 1:
    printf("option 1\n");
    break;
case 2:
    printf("option 2\n");
    break;
default:
    printf("unknown option\n");
    break;
}
```

`break`を実行すると、最も内側の`switch`文から抜けます。
`break`がなければ、次の`case`へ処理が続きます。

### 意図的なフォールスルー

複数の値を同じ処理へまとめる場合は、文を置かずに`case`を連続させます。

```c
switch (letter) {
case 'a':
case 'e':
case 'i':
case 'o':
case 'u':
    printf("vowel\n");
    break;
default:
    printf("not a lowercase vowel\n");
    break;
}
```

処理を実行した後で次の`case`へ続ける場合は、その意図をコメントで示します。

```c
switch (level) {
case 2:
    enable_advanced_mode();
    /* Fall through. */
case 1:
    enable_basic_mode();
    break;
default:
    break;
}
```

C90では宣言そのものは文ではないため、`case`ラベルの直後で変数を宣言したい場合はブロックを作ります。

```c
switch (choice) {
case 1: {
    int value = read_value();
    use_value(value);
    break;
}
default:
    break;
}
```

## 条件演算子

条件演算子`?:`は、条件に応じて2つの式の一方を評価します。

```c
int max = a > b ? a : b;
```

値を選ぶ短い式に適しています。
複数の文や副作用を含む処理は、`if-else`文で記述します。

## 条件式の注意点

### 代入と比較

`=`は代入、`==`は比較です。

```c
if (x = 10) {  /* Assigns 10, then tests it as true. */
    printf("executed\n");
}
```

比較する場合は`==`を使います。

```c
if (x == 10) {
    printf("x is 10\n");
}
```

### 浮動小数点数の比較

0.1や0.2のような値は、一般的な2進浮動小数点形式で正確に表現できない場合があります。
計算結果を比較するときは、要求精度と値の大きさに応じた方法を選びます。

```c
#include <math.h>

if (fabs(a - b) <= tolerance) {
    printf("close\n");
}
```

固定の許容誤差だけでは、非常に大きい値や非常に小さい値に適さない場合があります。
用途に応じて絶対誤差と相対誤差を組み合わせます。

### 条件式の末尾に置くセミコロン

次のコードでは、`if`が制御する文は空文です。
後続のブロックは条件に関係なく実行されます。

```c
if (condition); /* Empty statement. */
{
    printf("always executed\n");
}
```

## コンパイル

```bash
gcc -std=c90 -Wall -Wextra -pedantic examples/basic_if.c -o basic_if
./basic_if
```

Makefileを使う場合は、次のコマンドを実行します。

```bash
make all
make run-all
make clean
```

実装例は、次のファイルにあります。

- [basic_if.c](examples/basic_if.c)
- [if_else.c](examples/if_else.c)
- [grade_system.c](examples/grade_system.c)
- [switch_basic.c](examples/switch_basic.c)
- [conditional_operator.c](examples/conditional_operator.c)

## C99以降との違い

C99以降では、文の後や`for`文の初期化部でも変数を宣言できます。
条件分岐そのものの基本構文と、0を偽・0以外を真とする規則はC90と共通です。

## 演習問題

[演習問題](exercises/)では、範囲判定、入力検査、`switch`文、条件演算子を練習します。
