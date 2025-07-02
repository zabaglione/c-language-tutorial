# ビット操作とビットフィールド

##  対応C規格

- **主要対象:** C90
- **学習内容:** ビット演算、ビットマスク、ビットフィールド、実践的なビット操作技術

##  学習目標
この章を完了すると、以下のことができるようになります。

- ビット演算子を使いこなせる
- ビットマスクを使ったフラグ管理ができる
- ビットフィールドを理解して活用できる
- メモリ効率的なプログラムを作成できる
- ハードウェア制御の基礎を理解する

##  概要と詳細

### ビット操作とは？

ビット操作は、データの最小単位であるビットを直接操作する技術です。これは、メモリ効率的なプログラミング、ハードウェア制御、高速な演算処理などで重要な役割を果たします。

#### 日常生活でのビット操作
身近な例を考えてみましょう。

1. **スイッチパネル**

   - 8個のスイッチ = 8ビット
   - 各スイッチのON/OFF = 1/0
   - 複数のスイッチの状態を1つの数値で表現

2. **アクセス権限**

   - 読み取り権限 = ビット0
   - 書き込み権限 = ビット1
   - 実行権限 = ビット2
   - 権限の組み合わせを数値で管理

3. **色の表現（RGB）**

   - 赤（R）: 5ビット
   - 緑（G）: 6ビット
   - 青（B）: 5ビット
   - 16ビットで1つの色を表現

### ビット演算子の詳細

#### ビット演算子一覧

| 演算子 | 名称 | 動作 | 使用例 |
|--------|------|------|--------|
| `&` | AND | 両方が1の時1 | `a & b` |
| `\|` | OR | どちらかが1なら1 | `a \| b` |
| `^` | XOR | 異なる時1 | `a ^ b` |
| `~` | NOT | ビット反転 | `~a` |
| `<<` | 左シフト | ビットを左へ移動 | `a << 2` |
| `>>` | 右シフト | ビットを右へ移動 | `a >> 2` |

#### ビット演算の真理値表

```
AND演算（&）
A | B | A & B
--|---|------
0 | 0 |   0
0 | 1 |   0
1 | 0 |   0
1 | 1 |   1

OR演算（|）
A | B | A | B
--|---|------
0 | 0 |   0
0 | 1 |   1
1 | 0 |   1
1 | 1 |   1

XOR演算（^）
A | B | A ^ B
--|---|------
0 | 0 |   0
0 | 1 |   1
1 | 0 |   1
1 | 1 |   0
```

### ビットマスクの活用

#### ビットマスクとは？

ビットマスクは、特定のビットを操作するためのパターンです。

```c
/* 基本的なビットマスク */
#define BIT0 0x01  /* 00000001 */
#define BIT1 0x02  /* 00000010 */
#define BIT2 0x04  /* 00000100 */
#define BIT3 0x08  /* 00001000 */
#define BIT4 0x10  /* 00010000 */
#define BIT5 0x20  /* 00100000 */
#define BIT6 0x40  /* 01000000 */
#define BIT7 0x80  /* 10000000 */
```

#### ビット操作の基本テクニック

##### 1. 特定ビットのセット（1にする）

```c
unsigned char flags = 0x00;
flags |= BIT3;  /* ビット3を1にセット */
/* flags = 00001000 */
```

##### 2. 特定ビットのクリア（0にする）

```c
flags &= ~BIT3;  /* ビット3を0にクリア */
/* flags = 00000000 */
```

##### 3. 特定ビットの反転（トグル）

```c
flags ^= BIT3;  /* ビット3を反転 */
/* 0なら1に、1なら0に */
```

##### 4. 特定ビットのテスト

```c
if (flags & BIT3) {
    /* ビット3が1の場合 */
}
```

### フラグ管理システム

#### 実用的なフラグシステムの例

```c
/* ファイルアクセス権限 */
#define PERM_READ    0x04  /* 100 */
#define PERM_WRITE   0x02  /* 010 */
#define PERM_EXECUTE 0x01  /* 001 */

/* ゲームの状態フラグ */
#define STATE_RUNNING   0x01
#define STATE_PAUSED    0x02
#define STATE_GAMEOVER  0x04
#define STATE_DEBUG     0x08

/* 使用例 */
unsigned char permissions = 0;
permissions |= PERM_READ | PERM_WRITE;  /* 読み書き権限を付与 */

if (permissions & PERM_WRITE) {
    /* 書き込み権限がある場合の処理 */
}
```

### 効率的なビット操作アルゴリズム

#### 1. ビットカウント（1の個数を数える）

```c
/* Brian Kernighanのアルゴリズム */
int count_bits(unsigned int n) {
    int count = 0;
    while (n) {
        n &= (n - 1);  /* 最下位の1を消す */
        count++;
    }
    return count;
}
```

#### 2. 2のべき乗判定

```c
int is_power_of_two(unsigned int n) {
    return n && !(n & (n - 1));
}
```

#### 3. ビットスワップ

```c
/* XORを使った値の交換 */
void swap_without_temp(int *a, int *b) {
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}
```

### ビットフィールド

#### ビットフィールドとは？

構造体のメンバーに対してビット単位でサイズを指定できる機能です。

#### 基本的な宣言

```c
struct PackedData {
    unsigned int flag1 : 1;   /* 1ビット */
    unsigned int flag2 : 1;   /* 1ビット */
    unsigned int value : 6;   /* 6ビット */
    unsigned int type  : 4;   /* 4ビット */
    unsigned int reserved : 4; /* 4ビット（予約） */
};
```

#### ビットフィールドの使用例

```c
#include <stdio.h>

/* 日付を圧縮して格納 */
struct Date {
    unsigned int day   : 5;  /* 1-31 (5ビット) */
    unsigned int month : 4;  /* 1-12 (4ビット) */
    unsigned int year  : 7;  /* 0-127 (7ビット) 2000年からのオフセット */
};

int main(void) {
    struct Date today = {15, 12, 24};  /* 2024年12月15日 */
    
    printf("日付: %d年%d月%d日\n", 
           2000 + today.year, today.month, today.day);
    printf("サイズ: %lu バイト\n", sizeof(struct Date));
    
    return 0;
}
```

#### ハードウェアレジスタの定義

```c
/* マイコンのレジスタ定義例 */
struct ControlRegister {
    unsigned int enable     : 1;   /* ビット0: 有効/無効 */
    unsigned int interrupt  : 1;   /* ビット1: 割り込み許可 */
    unsigned int mode       : 2;   /* ビット2-3: 動作モード */
    unsigned int speed      : 3;   /* ビット4-6: 速度設定 */
    unsigned int reserved   : 1;   /* ビット7: 予約 */
};
```

### ビットフィールドの注意点

#### 1. 移植性の問題

- ビットフィールドのレイアウトは処理系依存
- エンディアンの影響を受ける
- パディングの挿入位置が異なる場合がある

#### 2. アドレスが取得できない

```c
struct BitField {
    unsigned int flag : 1;
};

struct BitField bf;
/* &bf.flag はエラー！ビットフィールドのアドレスは取得不可 */
```

#### 3. 配列にできない

```c
struct Invalid {
    unsigned int flags[8] : 1;  /* エラー！配列のビットフィールドは不可 */
};
```

### 実践的な応用例

#### RGB565形式の色操作

```c
/* 16ビットRGB（5-6-5形式） */
typedef struct {
    unsigned int blue  : 5;
    unsigned int green : 6;
    unsigned int red   : 5;
} RGB565;

/* または単一の16ビット値として */
#define RGB565_RED_MASK   0xF800  /* 11111000 00000000 */
#define RGB565_GREEN_MASK 0x07E0  /* 00000111 11100000 */
#define RGB565_BLUE_MASK  0x001F  /* 00000000 00011111 */

unsigned short make_rgb565(int r, int g, int b) {
    return ((r & 0x1F) << 11) | ((g & 0x3F) << 5) | (b & 0x1F);
}
```

#### ネットワークプロトコルのヘッダ

```c
/* 簡易パケットヘッダ */
struct PacketHeader {
    unsigned int version  : 4;   /* プロトコルバージョン */
    unsigned int type     : 4;   /* パケットタイプ */
    unsigned int flags    : 8;   /* 各種フラグ */
    unsigned int length   : 16;  /* データ長 */
};
```

### ビット操作のベストプラクティス

#### 1. マクロの活用

```c
#define SET_BIT(value, bit)    ((value) |= (1 << (bit)))
#define CLEAR_BIT(value, bit)  ((value) &= ~(1 << (bit)))
#define TOGGLE_BIT(value, bit) ((value) ^= (1 << (bit)))
#define TEST_BIT(value, bit)   ((value) & (1 << (bit)))
```

#### 2. 型の明確化

```c
/* 符号なし型を使用してシフトの動作を明確に */
unsigned int flags = 0;
unsigned char byte_data = 0xFF;
```

#### 3. 定数の使用

```c
/* マジックナンバーを避ける */
#define MAX_FLAGS 32
#define BYTE_MASK 0xFF
#define NIBBLE_MASK 0x0F
```

### よくある間違いとデバッグ

#### 1. 符号付き整数の右シフト

```c
int negative = -16;  /* 11110000 (8ビットの場合) */
int result = negative >> 2;  /* 結果は処理系依存！ */
/* 算術シフトか論理シフトかは未定義 */
```

#### 2. シフト量の範囲外

```c
unsigned int value = 1;
value <<= 32;  /* 32ビット整数で32ビットシフトは未定義動作 */
```

#### 3. 演算子の優先順位

```c
/* 間違い */
if (flags & BIT0 == 0)  /* == が先に評価される！ */

/* 正しい */
if ((flags & BIT0) == 0)
```

## 実例コード
完全な実装例は以下のファイルを参照してください。

### ビット操作の基本

- [bit_basics.c](examples/bit_basics.c) - C90準拠版
- [bit_basics_c99.c](examples/bit_basics_c99.c) - C99準拠版

### ビットフィールドの活用

- [bitfield_examples.c](examples/bitfield_examples.c) - C90準拠版
- [bitfield_examples_c99.c](examples/bitfield_examples_c99.c) - C99準拠版

### 実践的な応用

- [bit_applications.c](examples/bit_applications.c) - C90準拠版
- [bit_applications_c99.c](examples/bit_applications_c99.c) - C99準拠版

## 学習のポイント

1. **ビット演算子の理解**: 各演算子の動作を完全に理解する
2. **ビットマスクの活用**: フラグ管理の基本パターンを習得
3. **効率性の意識**: ビット操作による高速化・省メモリ化
4. **ビットフィールドの適用**: 適切な使用場面を判断できる

##  次の章へ
ビット操作を理解したら、[構造体とポインタ](../structures/README.md) に進んでください。構造体でビットフィールドをより効果的に活用できます。

##  参考資料

- [ビット演算](https://en.cppreference.com/w/c/language/operator_arithmetic)
- [ビットフィールド](https://en.cppreference.com/w/c/language/struct)

## 演習問題

この章の内容を理解したら、[演習問題](exercises/)に挑戦してみましょう。

- 基礎問題：基本的な文法や概念の確認
- 応用問題：より実践的なプログラムの作成
- チャレンジ問題：高度な理解と実装力が必要な問題