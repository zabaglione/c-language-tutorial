# 第4章：演算子と式

## 対応するC規格

- **主要対象**：C90
- **学習内容**：算術、代入、比較、論理、ビット、条件、`sizeof`、優先順位

## 学習目標

この章では、値を計算し、比較し、組み合わせるための演算子を学びます。

- 整数演算と浮動小数点演算を区別できる
- 前置・後置の`++`と`--`を使い分けられる
- 論理演算子の短絡評価を説明できる
- ビットシフトの未定義動作と処理系定義の動作を避けられる
- 優先順位と評価順序を区別できる

## 算術演算子

| 演算子 | 意味 | 例 |
|---|---|---|
| `+` | 加算 | `a + b` |
| `-` | 減算 | `a - b` |
| `*` | 乗算 | `a * b` |
| `/` | 除算 | `a / b` |
| `%` | 剰余 | `a % b` |

整数同士の演算結果は、原則として整数型です。

```c
int total = 7;
int count = 2;
int quotient = total / count;           /* 3 */
double average = (double)total / count; /* 3.5 */
```

0による整数除算と剰余は未定義動作です。
符号付き整数の加算、減算、乗算で結果を型の範囲内に表現できない場合も未定義動作です。

C99以降の整数除算は、小数部を0方向へ切り捨てます。
C90では、負のオペランドを含む除算と剰余の丸め方向が処理系定義だったため、移植性が必要なC90コードでは負数を含む結果に依存しません。

剰余は、周期的な処理や倍数の判定に使えます。

```c
if (number % 2 == 0) {
    printf("even\n");
}
```

## 代入演算子

単純代入`=`は、右辺の値を左辺の型へ変換して格納します。
複合代入は、演算と代入をまとめた構文です。

```c
int score = 100;

score += 20;
score -= 5;
score *= 2;
score /= 5;
score %= 7;
```

`E1 op= E2`は、おおむね`E1 = E1 op E2`に相当しますが、`E1`は1回だけ評価される点が異なります。
左辺が配列要素や間接参照を含む場合、この違いが重要です。

## インクリメントとデクリメント

前置形式は更新後の値を、後置形式は更新前の値を式の値とします。

```c
int a = 5;
int b = 5;
int x = ++a; /* a == 6, x == 6 */
int y = b++; /* b == 6, y == 5 */
```

更新後の値をその式で使わない場合、単独の文として`i++`または`++i`を使えます。
読みやすさのため、1つの式の中で同じオブジェクトを複数回更新しません。

```c
int n = 0;
int result = n++ + n++; /* Undefined behavior. */
```

C90とC99の用語では、次のシーケンスポイントまでに同じオブジェクトを複数回更新するため未定義動作です。

## 関係演算子と等価演算子

| 演算子 | 意味 |
|---|---|
| `<` | より小さい |
| `<=` | 以下 |
| `>` | より大きい |
| `>=` | 以上 |
| `==` | 等しい |
| `!=` | 等しくない |

比較結果の型は`int`で、真なら1、偽なら0です。
C90では専用のブール型を使わず、条件式では0を偽、0以外を真として扱います。

```c
if (count == 0) {
    printf("empty\n");
}
```

`=`は代入、`==`は比較です。
条件式の中で代入が必要な場合は、意図を明確にするため括弧で囲みます。

```c
if ((ch = getchar()) != EOF) {
    putchar(ch);
}
```

浮動小数点数は丸め誤差を含むことがあるため、計算結果を`==`で比較できるかは計算内容によって判断します。
許容誤差を使う場合は、固定値を無条件に選ばず、値の尺度と要求精度を考慮します。

## 論理演算子

| 演算子 | 意味 |
|---|---|
| `&&` | 論理積 |
| `\|\|` | 論理和 |
| `!` | 論理否定 |

論理演算子の結果は`int`の0または1です。
`!value`は、`value`が0なら1、0以外なら0になります。

### 短絡評価

`left && right`では、`left`が0なら`right`を評価しません。
`left || right`では、`left`が0以外なら`right`を評価しません。

この規則により、危険な演算の前提条件を先に検査できます。

```c
if (divisor != 0 && value / divisor > 10) {
    printf("large quotient\n");
}
```

```c
if (ptr != NULL && *ptr == 'A') {
    printf("match\n");
}
```

一方、右オペランドの副作用に依存すると、左オペランドの値によって更新が実行されない場合があります。

```c
int x = 0;
int y = 0;
int result = x && ++y; /* y remains 0. */
```

副作用が処理の目的なら、独立した文として記述する方が意図を確認しやすくなります。

## ビット演算子

| 演算子 | 意味 |
|---|---|
| `&` | ビット単位のAND |
| `\|` | ビット単位のOR |
| `^` | ビット単位のXOR |
| `~` | ビット反転 |
| `<<` | 左シフト |
| `>>` | 右シフト |

ビット集合には、符号なし整数型を使うと規則を説明しやすくなります。

```c
unsigned int read_flag = 1u << 0;
unsigned int write_flag = 1u << 1;
unsigned int flags = read_flag | write_flag;

if ((flags & read_flag) != 0u) {
    printf("read enabled\n");
}
```

`char`や`short`のオペランドには整数拡張が適用されます。
たとえば`~a`の計算結果は、`a`が`unsigned char`でも通常`int`です。
必要なら、目的の型へ明示的に変換します。

```c
unsigned char a = 5u;
unsigned char inverted = (unsigned char)~a;
```

### シフトの条件

シフト回数が負の場合、または整数拡張後の左オペランドの幅以上の場合、動作は未定義です。
符号付き負数の左シフトも未定義動作です。
符号付き非負数の左シフトは、結果をその型で表現できる場合にだけ定義されます。

符号なし整数の右シフトでは、空いた上位ビットに0が入ります。
負の符号付き整数の右シフト結果は処理系定義です。

## 条件演算子

条件演算子`?:`は、条件に応じて2つの式の一方だけを評価します。

```c
int max = a > b ? a : b;
```

短い値の選択には適しますが、副作用を伴う長い処理は`if`文で記述します。

## `sizeof`演算子

`sizeof`は、型またはオブジェクトが占めるバイト数を`size_t`型で返します。
C90で表示する場合は、値が`unsigned long`に収まることを前提に変換します。

```c
int values[10];

printf("int: %lu bytes\n", (unsigned long)sizeof(int));
printf("array: %lu bytes\n", (unsigned long)sizeof values);
```

## 優先順位と評価順序

優先順位は、演算子がどのオペランドと結び付くかを決めます。
オペランドを実際に評価する順序を決めるものではありません。

```c
int result = a + b * c; /* a + (b * c) */
```

関数引数など、多くの式では評価順序が規定されていません。
副作用の順序が必要な処理は、複数の文に分けます。

```c
int first = f();
int second = g();
int result = combine(first, second);
```

論理式では`!`、`&&`、`||`の順に強く結び付きます。
優先順位を覚えていても、条件のまとまりが読み取りにくい場合は括弧を使います。

```c
if (is_admin || (is_member && has_permission)) {
    printf("allowed\n");
}
```

## コンパイル

```bash
gcc -std=c90 -Wall -Wextra -pedantic examples/operators_demo.c -o operators_demo
./operators_demo
```

Makefileを使う場合は、次のコマンドを実行します。

```bash
make all
make run-all
make clean
```

実装例は、次のファイルにあります。

- [operators_demo.c](examples/operators_demo.c)
- [comparison_operators.c](examples/comparison_operators.c)
- [logical_operators.c](examples/logical_operators.c)
- [bitwise_demo.c](examples/bitwise_demo.c)
- [precedence_demo.c](examples/precedence_demo.c)

## 演習問題

[演習問題](exercises/)では、算術式、比較、短絡評価、ビット演算、優先順位を練習します。
