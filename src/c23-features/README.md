# C23の新機能

## 対応C規格

- **主要対象：** C23
- **学習内容：** `bool`、`typeof`、`nullptr`、2進整数定数、桁区切り、型推論、`constexpr`

## 学習目標

この章を完了すると、次のことができるようになります。

- C23の規格バージョンを機能テストマクロで判定できる
- `bool`、`true`、`false`をキーワードとして使用できる
- `typeof`と`typeof_unqual`の違いを説明できる
- `nullptr`と整数定数`0`の違いを説明できる
- 2進整数定数と桁区切りを正しい構文で記述できる
- 利用する処理系が各機能を実装しているか確認できる

## C23の位置づけ

C23はC言語規格の通称です。
国際規格はISO/IEC 9899:2024として2024年に発行されました。
規格に準拠する処理系では、`__STDC_VERSION__`が`202311L`になります。

```c
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 202311L
/* C23 mode */
#else
#error "C23 or later is required"
#endif
```

規格モードを指定しても、処理系がすべての機能を実装済みとは限りません。
コンパイル時の診断と処理系のリリースノートを併せて確認します。

## `bool`、`true`、`false`

C99では`_Bool`が言語の型として追加され、`<stdbool.h>`が`bool`、`true`、`false`をマクロとして提供しました。
C23では`bool`、`true`、`false`が言語機能になったため、これらを使うためだけに`<stdbool.h>`をインクルードする必要はありません。

```c
bool is_ready = false;

if (!is_ready) {
    is_ready = true;
}
```

`bool`へ変換した値は0なら`false`、0以外なら`true`になります。
`bool`は状態を表す型ですが、入力値の妥当性や処理の成功を自動的に保証するものではありません。

### 以前の規格との比較

```c
/* C90 */
int is_ready = 0;

/* C99以降 */
#include <stdbool.h>
bool is_ready = false;

/* C23 */
bool is_ready = false;
```

## `typeof`と`typeof_unqual`

`typeof`は、式または型名から型を得る演算子です。
GNU Cなどが拡張として提供してきた綴りに相当する機能が、C23で標準化されました。

```c
int count = 10;
typeof(count) next_count = count + 1;

double price = 19.99;
typeof(price) tax = 1.10;
```

`typeof`は、対象の型に含まれる修飾子や原子型の性質を保持します。
`typeof_unqual`は、結果の型から`const`、`volatile`、`restrict`、`_Atomic`に相当する修飾を除きます。

```c
const int limit = 100;
typeof(limit) same_limit_type = 50;          /* const int */
typeof_unqual(limit) mutable_limit = 50;     /* int */
```

配列を対象にした`typeof`は、通常の式で起こる先頭要素へのポインター変換を行わず、配列型を得ます。

```c
int values[4] = {1, 2, 3, 4};
typeof(values) copy = {5, 6, 7, 8};  /* int[4] */
```

## `nullptr`

`nullptr`は、C23で追加された定義済み定数です。
型は`nullptr_t`であり、オブジェクトへのポインター型、関数ポインター型、`bool`へ変換できます。

```c
#include <stddef.h>

int *data = nullptr;
nullptr_t no_address = nullptr;

if (data == nullptr) {
    /* data does not point to an object */
}
```

従来のnullポインター定数である整数定数`0`や`NULL`も引き続き使用できます。
`nullptr`は整数型の値としては扱えないため、ポインターを意図した値であることを型で区別できます。

```c
int *pointer_value = nullptr;  /* valid */
bool flag = nullptr;           /* false */
/* int integer_value = nullptr; */  /* constraint violation */
```

Cには関数オーバーロードがないため、C++のようなオーバーロード解決を`nullptr`の利点として説明することはできません。

## 2進整数定数

C23では、`0b`または`0B`で始まる2進整数定数を記述できます。
ビット位置がそのまま表記に現れるため、フラグやマスクの確認に使えます。

```c
#define PERMISSION_READ    0b100U
#define PERMISSION_WRITE   0b010U
#define PERMISSION_EXECUTE 0b001U

unsigned int permissions = PERMISSION_READ | PERMISSION_WRITE;
```

2進表記を使っても、整数型の幅や変換規則は変わりません。
値が格納先の型で表現できるかを確認します。

## 数値リテラルの桁区切り

C23では、整数定数と浮動小数点定数の数字の間へ単一引用符`'`を置けます。
区切り文字は値の計算では無視されます。

```c
unsigned int byte_mask = 0b1111'1111U;
unsigned long population = 1'000'000UL;
unsigned long color = 0xFF'80'20UL;
```

アンダースコアはC23の桁区切りではありません。
接頭辞の直後や数字列の末尾にも単一引用符は置けません。

## `auto`による型推論

C23では、初期化子からオブジェクトの型を推論する宣言に`auto`を使えます。

```c
auto count = 42;       /* int */
auto ratio = 3.14;     /* double */
auto pointer = &count; /* int * */
```

初期化子は必須です。
型を明示した方がインターフェースや変換の意図を伝えやすい場合は、従来どおり型名を書きます。

## `constexpr`オブジェクト

`constexpr`を指定したオブジェクトは、翻訳時に評価できる定数として定義します。

```c
constexpr int element_count = 100;
int values[element_count];
```

初期化子は定数式の要件を満たす必要があります。
単に実行中の変更を防ぐだけなら`const`、整数定数式など翻訳時の定数として使う必要があるなら`constexpr`という違いがあります。

## 条件付きインクルージョンの追加構文

`#elifdef`と`#elifndef`は、`#elif defined(...)`を短く書く構文です。

```c
#if defined(DEBUG)
#define LOG_LEVEL 2
#elifdef RELEASE
#define LOG_LEVEL 0
#elifndef LOG_LEVEL
#define LOG_LEVEL 1
#endif
```

## コンパイルと機能確認

処理系が受け付ける規格モードを確認し、C23モードでコンパイルします。
新しい処理系では`-std=c23`、移行期の処理系では`-std=c2x`というオプションを使う場合があります。

```bash
gcc -std=c23 -Wall -Wextra -pedantic source.c -o output
```

規格モードの名称と各機能の実装状況は、コンパイラとバージョンによって異なります。
特定のバージョン番号だけで一括判定せず、必要な機能を含む小さなコードを警告付きでコンパイルして確認します。

## 実例コード

実装例は次のファイルにあります。

- [bool_basics.c](examples/bool_basics.c)：`bool`の基本
- [typeof_demo.c](examples/typeof_demo.c)：`typeof`の使用例
- [nullptr_example.c](examples/nullptr_example.c)：`nullptr`の使用例
- [binary_literals.c](examples/binary_literals.c)：2進整数定数の使用例

## 以前の規格から移行するときの確認事項

1. **処理系の対応**：使用するすべてのコンパイラが、採用するC23機能を実装しているか確認します
2. **規格モード**：ビルドシステム、静的解析、エディタの設定を同じ規格モードにそろえます
3. **公開ヘッダー**：利用側が古い規格を使う場合、公開APIにC23専用の構文を出さない設計も検討します
4. **機械的な置換を避ける**：`NULL`をすべて`nullptr`へ置換する必要はなく、対応する処理系とコード規約に合わせます

## 参考資料

- [WG14公式サイト](https://www.open-std.org/jtc1/sc22/wg14/)
- [C23最終公開ドラフトN3096](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n3096.pdf)
- [WG14のプロジェクト状況](https://www.open-std.org/jtc1/sc22/wg14/www/projects.html)

## 演習問題

[演習問題](exercises/)では、`__STDC_VERSION__`、`bool`、`typeof`、`nullptr`、2進整数定数、桁区切りを確認できます。

- 基礎問題：構文と型の確認
- 応用問題：以前の規格との条件付きコンパイル
- チャレンジ問題：複数のC23機能を組み合わせた実装
