# 第12章 演習問題解答: ビット操作とビットフィールド

## 解答の前に
ビット操作は低レベルプログラミングの基本です。これらの解答例を通じて、効率的なビット操作の手法を学んでください。

## 演習 12-1 解答: 基本的なビット操作
[ex12_1_bit_operations.c](ex12_1_bit_operations.c)

**実装のポイント:**
- ビット位置の範囲チェックが重要
- シフト演算は32ビット以上シフトすると未定義動作
- 循環シフトは通常のシフトと論理和で実現

```c
/* ビットの循環シフト例 */
unsigned int rotate_left(unsigned int value, int shift) {
    shift %= 32;  /* 32ビット以上のシフトを防ぐ */
    return (value << shift) | (value >> (32 - shift));
}
```

## 演習 12-2 解答: フラグ管理システム
[ex12_2_flag_system.c](ex12_2_flag_system.c)

**実装のポイント:**
- 複数フラグの同時操作は論理和/論理積を活用
- 相反する状態は自動的にクリアする設計
- フラグの名前と値の対応表を用意すると便利

```c
/* 相反する状態の処理例 */
if (status & STATUS_FROZEN) {
    status &= ~STATUS_BURNING;  /* 凍結時は燃焼を解除 */
}
```

## 演習 12-3 解答: ビットフィールドでメモリ節約
[ex12_3_student_grades.c](ex12_3_student_grades.c)

**実装のポイント:**
- ビットフィールドのサイズは慎重に設計
- パディングの影響を考慮
- 移植性を考慮した実装

通常の構造体では約16バイト必要なデータを、ビットフィールドで約6バイトに圧縮できます。

## 演習 12-4 解答: RGB色操作
[ex12_4_rgb_colors.c](ex12_4_rgb_colors.c)

**実装のポイント:**
- RGB565⇔RGB888変換時の精度損失に注意
- 5ビット→8ビット変換は上位ビットを下位に複製
- 色の混合は各成分を個別に計算

```c
/* RGB565からRGB888への変換例 */
r8 = (r5 << 3) | (r5 >> 2);  /* 5ビットを8ビットに拡張 */
```

## 演習 12-5 解答: ビットベクタで集合演算
[ex12_5_bit_set.c](ex12_5_bit_set.c)

**実装のポイント:**
- 集合演算はビット演算と直接対応
- 要素数カウントはBrian Kernighanのアルゴリズムを使用
- 大きな集合では複数のワードに分割

集合演算とビット演算の対応：
- 和集合 = OR演算
- 積集合 = AND演算
- 差集合 = AND NOT演算
- 対称差 = XOR演算

## 演習 12-6 解答: CRC計算の実装
[ex12_6_crc_checksum.c](ex12_6_crc_checksum.c)

**実装のポイント:**
- ビット単位の実装は理解しやすいが遅い
- テーブル方式は256エントリで大幅に高速化
- CRC多項式の選択が重要

CRCは単純なチェックサムより優れたエラー検出能力を持ちます。

## 演習 12-7 解答: ビットボードでオセロ
[ex12_7_othello_bitboard.c](ex12_7_othello_bitboard.c)

**実装のポイント:**
- 64ビット整数で8×8盤面を表現
- ビットシフトで方向を表現
- マスク演算で端の処理

ビットボードを使うと、複数の石の反転を一度に処理できます。

## チャレンジ問題解答

### チャレンジ 12-A 解答: ハフマン符号化
[ex12_a_huffman.c](ex12_a_huffman.c)

ハフマン符号化は可変長符号化の代表例です。頻出文字に短いビット列を割り当てることで圧縮を実現します。

### チャレンジ 12-B 解答: ブルームフィルタ
[ex12_b_bloom_filter.c](ex12_b_bloom_filter.c)

ブルームフィルタは空間効率的な確率的データ構造です。偽陽性は発生しますが、偽陰性は発生しません。

## 発展学習

### さらなる学習のために
1. **SIMD命令**: 現代のCPUはビット操作を並列化できる
2. **ビット並列アルゴリズム**: 複数のデータを同時処理
3. **圧縮アルゴリズム**: LZ77、LZW等の実装
4. **暗号化**: ビット操作は暗号化の基礎

### 参考図書
- "Hacker's Delight" by Henry S. Warren Jr.
- "ビット演算超入門" （日本語書籍）

## まとめ
ビット操作は以下の場面で威力を発揮します：
- メモリ制約が厳しい組み込みシステム
- 高速処理が必要なゲームエンジン
- ネットワークプロトコルの実装
- データ圧縮・暗号化

これらの技術を習得することで、より効率的なプログラムが書けるようになります。