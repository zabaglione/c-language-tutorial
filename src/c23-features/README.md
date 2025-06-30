# 第14章: C23の新機能

## 対応C規格
- **主要対象:** C23
- **学習内容:** bool型、typeof演算子、nullptr、2進数リテラル、その他の新機能

## 学習目標

この章を完了すると、以下のことができるようになります：

- C23で標準化されたbool型を使用できる
- typeof演算子で型を扱える
- nullptrを使った型安全なコードが書ける
- 2進数リテラルを活用できる
- C23の新機能を実践的に活用できる

## 理論解説

### C23とは

C23（正式にはISO/IEC 9899:2024）は、C言語の最新規格です。C99以来の大規模な改訂となり、現代的なプログラミングのニーズに対応した多くの新機能が追加されました。

### 主要な新機能

#### 1. bool型の標準化

C23では、`<stdbool.h>`をインクルードすることなく、`bool`、`true`、`false`が使用可能になりました。

```c
/* C90/C99 */
#include <stdbool.h>  /* 必要 */
bool flag = true;

/* C23 */
bool flag = true;     /* ヘッダー不要 */
```

#### 2. typeof演算子

式の型を取得できる演算子です。マクロでの型安全性向上に役立ちます。

```c
int x = 42;
typeof(x) y = 100;    /* yはint型 */

/* 型安全なマクロ */
#define SWAP(a, b) do { \
    typeof(a) temp = (a); \
    (a) = (b); \
    (b) = temp; \
} while(0)
```

#### 3. nullptr定数

型安全なNULLポインタ定数です。

```c
/* 従来 */
int *p1 = NULL;       /* NULLは0やvoid*として定義 */

/* C23 */
int *p2 = nullptr;    /* 明確にポインタ型 */
```

#### 4. 2進数リテラル

`0b`または`0B`プレフィックスで2進数を直接記述できます。

```c
int binary = 0b1010;     /* 10進数の10 */
int flags = 0b11111111;  /* 10進数の255 */

/* ビット演算での活用 */
#define READ_BIT  0b100
#define WRITE_BIT 0b010
#define EXEC_BIT  0b001
```

### その他の新機能（一部）

- `auto`型推論（制限付き）
- `constexpr`（コンパイル時定数）
- `_BitInt(N)`（任意ビット幅整数）
- 属性構文（`[[deprecated]]`など）
- プリプロセッサの拡張（`#elifdef`、`#elifndef`）

## 演習問題

### 演習14-1: bool型の活用
[exercises/README.md](exercises/README.md)を参照

### 演習14-2: ビット操作と2進数リテラル
[exercises/README.md](exercises/README.md)を参照

### 演習14-3: typeof演算子の応用
[exercises/README.md](exercises/README.md)を参照

## コンパイル方法

この章はC23専用です。以下のコマンドでコンパイルしてください：

```bash
# 個別ファイルのコンパイル
gcc -std=c23 -Wall -Wextra -pedantic source.c -o output

# Makefileを使用
make all          # すべてコンパイル
make test         # C23サポートテスト
make run-all      # すべて実行
```

### コンパイラサポート状況

C23は新しい規格のため、コンパイラサポートは発展途上です：

- **GCC**: 13以降で部分サポート（`-std=c23`）
- **Clang**: 16以降で部分サポート（`-std=c23`）
- **MSVC**: 未対応（2024年現在）

## 注意事項

1. **コンパイラ依存**: すべてのC23機能がサポートされているとは限りません
2. **移植性**: 古いコンパイラでは動作しません
3. **学習順序**: C90/C99の基礎を理解してから学習することを推奨

## 参考資料

- [C23規格ドラフト](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n3096.pdf)
- [C23新機能の概要](https://en.cppreference.com/w/c/23)
- コンパイラのドキュメント（GCC、Clang）

## 🔄 C90/C99/C11からの移行

### bool型
```c
/* C90 */
#define TRUE 1
#define FALSE 0
int flag = TRUE;

/* C99 */
#include <stdbool.h>
bool flag = true;

/* C23 */
bool flag = true;  /* ヘッダー不要 */
```

### NULLポインタ
```c
/* C90/C99/C11 */
int *p = NULL;

/* C23 */
int *p = nullptr;
```

### 型の取得
```c
/* C11: _Generic */
#define TYPE_NAME(x) _Generic((x), \
    int: "int", \
    double: "double", \
    default: "other")

/* C23: typeof */
typeof(x) y;  /* xと同じ型 */
```

---

**注**: この章はオプション的な内容です。実務では、使用するコンパイラのC23サポート状況を確認してから活用してください。