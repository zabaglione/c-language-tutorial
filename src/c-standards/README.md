# C言語の規格と歴史

## 対応C規格

- **主要対象：** C90、C99、C11、C17、C23
- **学習内容：** 各規格の位置づけ、追加機能、規格モードの選び方

## 学習目標

この章を完了すると、次のことができるようになります。

- C89とC90の関係を説明できる
- C99、C11、C17、C23で追加または変更された主な機能を区別できる
- `__STDC_VERSION__`で言語規格の版を確認できる
- 対象処理系と依存ライブラリに合わせて規格モードを選べる

## 標準化までの経緯

Cは1970年代初頭にベル研究所で開発されました。
処理系ごとの差異を抑え、同じソースコードを異なる環境へ移植しやすくするため、1980年代に標準化が進められました。

- **1978年**：Brian KernighanとDennis Ritchieによる初版の書籍が出版されました
- **1989年**：ANSI X3.159-1989が発行されました。通称はC89です
- **1990年**：ISO/IEC 9899:1990が発行されました。通称はC90です

C89とC90は技術的な内容がほぼ同じで、標準化団体と発行年が異なります。

## 規格の一覧

| 通称 | 国際規格 | `__STDC_VERSION__` | 主な変更 |
|---|---|---:|---|
| C90 | ISO/IEC 9899:1990 | 定義なし | 初の国際規格 |
| C95 | ISO/IEC 9899:1990/Amd 1:1995 | `199409L` | ワイド文字関連などの追補 |
| C99 | ISO/IEC 9899:1999 | `199901L` | 複合リテラル、指定初期化子、`inline`、`_Bool`など |
| C11 | ISO/IEC 9899:2011 | `201112L` | `_Generic`、原子型、スレッド、静的アサーションなど |
| C17 | ISO/IEC 9899:2018 | `201710L` | C11に対する不具合修正と明確化 |
| C23 | ISO/IEC 9899:2024 | `202311L` | `bool`、`typeof`、`nullptr`、2進整数定数など |

C23という通称の数字と、国際規格の発行年は一致しません。
C23は2024年にISO/IEC 9899:2024として発行されました。

## C90

C90は、関数プロトタイプ、`void`、`const`、`volatile`や標準ライブラリを含む、国際標準としての基礎を定めました。
現在も古い処理系や長期保守される環境との互換性要件で使われることがあります。

C90では、ブロック内の宣言をそのブロックの文より前に置きます。
宣言場所は関数の先頭だけに限定されず、内側の複合文を作ればその先頭でも宣言できます。

```c
int sum_values(void)
{
    int i;
    int sum = 0;

    for (i = 0; i < 10; i++) {
        sum += i;
    }

    return sum;
}
```

## C99

C99では、宣言と文の混在、`for`初期化部での宣言、`//`コメント、`long long`、`_Bool`、`inline`、複合リテラル、指定初期化子などが追加されました。
`<stdint.h>`の規定幅整数型もC99で追加されています。

```c
#include <stdbool.h>
#include <stdio.h>

int main(void)
{
    bool enabled = true;
    int values[6] = {[0] = 10, [5] = 20};

    for (int i = 0; i < 6; i++) {
        printf("%d\n", values[i]);
    }

    return enabled ? 0 : 1;
}
```

可変長配列もC99で追加されました。
C11以降では自動記憶域期間を持つ可変長配列を提供しない処理系があるため、利用時は規格版だけでなく処理系の対応を確認します。

## C11

C11では、型に応じた式を選択する`_Generic`、`_Static_assert`、アラインメント指定、原子型、スレッドライブラリ、匿名構造体・共用体などが追加されました。

```c
#include <limits.h>

_Static_assert(sizeof(int) * CHAR_BIT >= 16,
               "int must occupy at least 16 bits");

#define TYPE_NAME(x) _Generic((x), \
    int: "int", \
    float: "float", \
    double: "double", \
    default: "other")
```

スレッドや原子操作など、一部の機能には処理系が対応しないことを示す機能テストマクロがあります。
たとえば、`__STDC_NO_THREADS__`が定義されている処理系は`<threads.h>`を提供しません。

## C17

C17はC11に対する不具合修正と明確化をまとめた規格です。
新しい言語機能は追加していません。
C11の機能を使うコードでも、利用可能ならC17モードを選ぶことで修正版の規格を基準にできます。

## C23

C23では、`bool`、`true`、`false`、`static_assert`などがキーワードになりました。
ほかに`typeof`、`typeof_unqual`、`nullptr`、`_BitInt`、2進整数定数、桁区切り、`#embed`、`auto`による型推論、`constexpr`オブジェクトなどが追加されています。

```c
bool ready = true;
auto count = 42;
typeof(count) next_count = count + 1;
int *pointer = nullptr;
unsigned int mask = 0b1111'0000U;
```

C23の詳細は[C23の新機能](../c23-features/README.md)で扱います。

## 規格版をプログラムから確認する

C95以降の規格に準拠する処理系は、`__STDC_VERSION__`を定義します。
C90モードではこのマクロが定義されないため、先に`defined`で確認します。

```c
#if !defined(__STDC_VERSION__)
/* C90 or a non-conforming mode */
#elif __STDC_VERSION__ >= 202311L
/* C23 or later */
#elif __STDC_VERSION__ >= 201710L
/* C17 */
#elif __STDC_VERSION__ >= 201112L
/* C11 */
#elif __STDC_VERSION__ >= 199901L
/* C99 */
#endif
```

このマクロは規格版の判定には使えますが、任意機能や処理系拡張の有無をすべて示すものではありません。
必要なヘッダー、機能テストマクロ、コンパイル結果も確認します。

## 規格モードを選ぶ基準

規格モードは、学習順序の新旧ではなく、プロジェクトの制約から選びます。

1. **対象処理系**：対応するすべてのコンパイラが受け付ける規格を確認します
2. **依存関係**：利用するライブラリやSDKが要求する規格を確認します
3. **公開インターフェース**：ヘッダーを利用する側が受け付けられる構文を選びます
4. **必要な機能**：`_Generic`や`nullptr`など、実際に必要な機能を特定します
5. **検証方法**：CIと警告オプションで、選んだ規格への準拠を継続して確認します

古い規格ほど移植性が高い、新しい規格ほど安全である、と一律には判断できません。
実装の品質、利用する機能、対象環境の組み合わせで決まります。

## コンパイラで規格モードを指定する

GCCやClang系の処理系では、次のようなオプションを使用します。

```bash
gcc -std=c90 -Wall -Wextra -pedantic program.c
gcc -std=c99 -Wall -Wextra -pedantic program.c
gcc -std=c11 -Wall -Wextra -pedantic program.c
gcc -std=c17 -Wall -Wextra -pedantic program.c
gcc -std=c23 -Wall -Wextra -pedantic program.c
```

C23への移行期の処理系では、`-std=c2x`という名称を使う場合があります。
利用できるオプションは、対象コンパイラのヘルプで確認します。

## 参考資料

- [WG14公式サイト](https://www.open-std.org/jtc1/sc22/wg14/)
- [WG14のプロジェクト状況](https://www.open-std.org/jtc1/sc22/wg14/www/projects.html)
- [C23最終公開ドラフトN3096](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n3096.pdf)

## 演習問題

[演習問題](exercises/)では、規格ごとの構文差、`__STDC_VERSION__`、コンパイルオプションを確認できます。
