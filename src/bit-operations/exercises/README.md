# 第12章 演習問題: ビット操作とビットフィールド

## 演習問題の目的
この章では、ビット演算子の使い方、ビットマスクによるフラグ管理、ビットフィールドの活用、そして実践的なビット操作技術を習得します。

## 演習 12-1: 基本的なビット操作
**難易度:** ★☆☆

以下の処理を行う関数を実装してください：

1. 整数の特定ビットをセット/クリア/反転する関数
2. 整数の特定範囲のビットを抽出する関数
3. 整数のビットを左右に循環シフトする関数

```c
/* 実装すべき関数のプロトタイプ */
void set_bit(unsigned int *value, int bit);
void clear_bit(unsigned int *value, int bit);
void toggle_bit(unsigned int *value, int bit);
int test_bit(unsigned int value, int bit);

unsigned int extract_bits(unsigned int value, int start, int count);
unsigned int rotate_left(unsigned int value, int shift);
unsigned int rotate_right(unsigned int value, int shift);
```

**要件:**
- ビット位置は0から31まで
- 範囲外のビット位置の場合は何もしない
- 循環シフトは32ビットの範囲で行う

## 演習 12-2: フラグ管理システム
**難易度:** ★★☆

ゲームキャラクターの状態を管理するフラグシステムを実装してください：

```c
/* 状態フラグの定義 */
#define STATUS_ALIVE     0x0001
#define STATUS_POISONED  0x0002
#define STATUS_PARALYZED 0x0004
#define STATUS_CONFUSED  0x0008
#define STATUS_SLEEPING  0x0010
#define STATUS_BURNING   0x0020
#define STATUS_FROZEN    0x0040
#define STATUS_INVISIBLE 0x0080
#define STATUS_INVINCIBLE 0x0100
#define STATUS_BUFFED    0x0200
```

実装する機能：
1. 複数の状態を同時に設定/解除
2. 特定の状態の組み合わせをチェック
3. 状態の一覧を表示
4. 相反する状態の自動解除（例：凍結と燃焼）

## 演習 12-3: ビットフィールドでメモリ節約
**難易度:** ★★☆

学生の成績データを効率的に格納する構造体を設計してください：

```c
/* 成績データ構造体（ビットフィールド使用） */
struct StudentGrade {
    unsigned int student_id : 20;    /* 学生ID（0-1048575） */
    unsigned int subject_code : 10;  /* 科目コード（0-1023） */
    unsigned int grade : 7;          /* 成績（0-100） */
    unsigned int semester : 2;       /* 学期（1-4） */
    unsigned int year : 7;           /* 年度（0-99, 2000年基準） */
    unsigned int attendance : 1;     /* 出席状況（合格/不合格） */
    unsigned int retake : 1;         /* 再履修フラグ */
};
```

実装する機能：
1. 成績データの入力と表示
2. 通常の構造体とのサイズ比較
3. 成績の統計情報（平均点、最高点、最低点）
4. 条件に合う学生の検索

## 演習 12-4: RGB色操作
**難易度:** ★★☆

RGB565形式（16ビット）の色を操作するプログラムを作成してください：

```c
/* RGB565色構造体 */
typedef struct {
    unsigned int blue  : 5;
    unsigned int green : 6;
    unsigned int red   : 5;
} RGB565;

/* または16ビット整数として扱う */
typedef unsigned short RGB565_int;
```

実装する機能：
1. RGB888（24ビット）⇔ RGB565の相互変換
2. 色の明度調整（明るく/暗く）
3. グレースケール変換
4. 2つの色の混合（アルファブレンド風）

## 演習 12-5: ビットベクタで集合演算
**難易度:** ★★★

ビットベクタを使って集合演算を実装してください：

```c
#define SET_SIZE 256  /* 0-255の整数を扱う */

typedef struct {
    unsigned char bits[SET_SIZE / 8];
} BitSet;
```

実装する機能：
1. 集合の初期化、要素の追加/削除
2. 和集合、積集合、差集合、対称差
3. 部分集合の判定
4. 集合の要素数カウント
5. 集合の内容表示

## 演習 12-6: CRC計算の実装
**難易度:** ★★★

簡単なCRC-8チェックサムを計算する関数を実装してください：

```c
/* CRC-8計算（多項式: x^8 + x^2 + x + 1） */
unsigned char calculate_crc8(const unsigned char *data, int length);
```

実装内容：
1. ビット単位でCRCを計算する基本実装
2. テーブルを使った高速化実装
3. データの破損検出テスト
4. 性能比較

## 演習 12-7: ビットボードでオセロ
**難易度:** ★★★

8×8のオセロ盤面をビットボードで表現してください：

```c
typedef struct {
    unsigned long long black;  /* 黒石の位置 */
    unsigned long long white;  /* 白石の位置 */
} OthelloBoard;
```

実装する機能：
1. 盤面の初期化と表示
2. 石を置ける位置の判定
3. 石を置いた時の反転処理
4. 勝敗判定

## チャレンジ問題

### チャレンジ 12-A: ハフマン符号化
**難易度:** ★★★★

簡単なハフマン符号化を実装してください：

1. 文字の出現頻度をカウント
2. ハフマン木を構築
3. 各文字のビット列を決定
4. テキストをビット列に圧縮
5. ビット列から元のテキストに復元

### チャレンジ 12-B: ブルームフィルタ
**難易度:** ★★★★

確率的データ構造であるブルームフィルタを実装してください：

1. 複数のハッシュ関数の実装
2. 要素の追加
3. 要素の存在確認（偽陽性あり）
4. 偽陽性率の測定

## 演習のヒント

### ビット操作の基本パターン
```c
/* nビット目をセット */
value |= (1 << n);

/* nビット目をクリア */
value &= ~(1 << n);

/* nビット目を反転 */
value ^= (1 << n);

/* nビット目をテスト */
if (value & (1 << n)) { /* ... */ }
```

### ビットマスクの作成
```c
/* 下位nビットのマスク */
mask = (1 << n) - 1;

/* startからcountビット分のマスク */
mask = ((1 << count) - 1) << start;
```

### ビットカウント
```c
/* Brian Kernighanのアルゴリズム */
int count = 0;
while (n) {
    n &= n - 1;
    count++;
}
```

## 提出方法
1. 各演習問題ごとに`ex12_1.c`、`ex12_2.c`...という名前でファイルを作成
2. 動作確認用の`main`関数を含める
3. コメントで実装の工夫や考察を記載

## 評価基準
- **正確性**: 要求された機能が正しく動作するか
- **効率性**: ビット操作の利点を活かした実装か
- **可読性**: コードが理解しやすく整理されているか
- **完成度**: エラー処理やエッジケースへの対応

頑張ってください！