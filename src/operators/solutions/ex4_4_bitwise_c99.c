/*
 * ファイル名: ex4_4_bitwise_c99.c
 * 演習4-4: ビット演算
 * 説明: ビット演算子を使って数値の特定ビットを操作
 * 規格: C99準拠
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

// C99: inline関数によるビット操作ユーティリティ
static inline bool test_bit(uint8_t value, int position)
{
    return (value & (1u << position)) != 0;
}

static inline uint8_t set_bit(uint8_t value, int position)
{
    return value | (1u << position);
}

static inline uint8_t clear_bit(uint8_t value, int position)
{
    return value & ~(1u << position);
}

static inline uint8_t toggle_bit(uint8_t value, int position)
{
    return value ^ (1u << position);
}

// C99: inline関数によるビットカウント
static inline int count_bits(uint8_t value)
{
    int count = 0;
    while (value) {
        count += value & 1;
        value >>= 1;
    }
    return count;
}

// C99: bool型を返す2のべき乗判定
static inline bool is_power_of_two(unsigned int n)
{
    return n > 0 && (n & (n - 1)) == 0;
}

// ビットを表示する関数（改良版）
void print_bits_detailed(uint8_t value)
{
    printf("0b");
    for (int i = 7; i >= 0; i--) {
        printf("%d", test_bit(value, i) ? 1 : 0);
        if (i % 4 == 0 && i > 0) {
            printf("_");
        }
    }
    printf(" (0x%02X, %3u)", value, value);
}

int main(void)
{
    printf("===== ビット操作 (C99版) =====\n");
    printf("整数を入力してください (0-255): ");
    
    // C99: 使用箇所での変数宣言
    unsigned int input;
    if (scanf("%u", &input) != 1 || input > 255) {
        printf("エラー: 0から255の範囲で入力してください\n");
        return 1;
    }
    
    uint8_t num = (uint8_t)input;  // C99: 固定幅整数型
    
    printf("\n元の値: ");
    print_bits_detailed(num);
    printf("\n\n");
    
    // C99: 構造体による演算結果の管理
    typedef struct {
        const char *name;
        uint8_t result;
        const char *description;
    } BitOperation;
    
    // 基本的なビット演算
    printf("=== ビット単位の基本演算 ===\n");
    
    BitOperation basic_ops[] = {
        {"AND (上位4ビット)", num & 0xF0, "マスク: 0xF0"},
        {"AND (下位4ビット)", num & 0x0F, "マスク: 0x0F"},
        {"OR (下位4ビットセット)", num | 0x0F, "マスク: 0x0F"},
        {"XOR (全ビット反転)", num ^ 0xFF, "マスク: 0xFF"},
        {"NOT (ビット反転)", ~num, "単項演算子"}
    };
    
    for (size_t i = 0; i < sizeof(basic_ops) / sizeof(basic_ops[0]); i++) {
        printf("%s (%s):\n", basic_ops[i].name, basic_ops[i].description);
        printf("結果: ");
        print_bits_detailed(basic_ops[i].result);
        printf("\n\n");
    }
    
    // ビットシフト演算
    printf("=== ビットシフト演算 ===\n");
    
    // C99: forループ内での変数宣言
    for (int shift = 1; shift <= 3; shift++) {
        printf("左シフト %dビット: ", shift);
        print_bits_detailed(num << shift);
        printf(" (%d倍)\n", 1 << shift);
        
        printf("右シフト %dビット: ", shift);
        print_bits_detailed(num >> shift);
        printf(" (1/%d)\n", 1 << shift);
        printf("\n");
    }
    
    // 特定ビットの操作
    printf("=== 特定ビットの操作 ===\n");
    printf("操作するビット位置を入力 (0-7): ");
    
    int bit_position;
    if (scanf("%d", &bit_position) != 1 || bit_position < 0 || bit_position > 7) {
        printf("エラー: 0から7の範囲で入力してください\n");
        return 1;
    }
    
    // C99: bool型による判定結果
    bool bit_is_set = test_bit(num, bit_position);
    printf("\nビット%dの状態: %s\n", bit_position, bit_is_set ? "1 (セット)" : "0 (クリア)");
    
    // ビット操作のデモンストレーション
    typedef struct {
        const char *operation;
        uint8_t (*func)(uint8_t, int);
        const char *description;
    } BitManipulation;
    
    // 関数ポインタは直接使用せず、各操作を個別に実行
    printf("\nビット%dの操作:\n", bit_position);
    
    uint8_t set_result = set_bit(num, bit_position);
    printf("セット後: ");
    print_bits_detailed(set_result);
    printf("\n");
    
    uint8_t clear_result = clear_bit(num, bit_position);
    printf("クリア後: ");
    print_bits_detailed(clear_result);
    printf("\n");
    
    uint8_t toggle_result = toggle_bit(num, bit_position);
    printf("反転後: ");
    print_bits_detailed(toggle_result);
    printf("\n");
    
    // C99: 複数ビットの同時操作
    printf("\n=== 複数ビットの同時操作 ===\n");
    
    // 複数ビットのマスク作成
    uint8_t multi_mask = 0;
    printf("セットするビット位置を入力 (例: 0 2 4、-1で終了): ");
    
    while (true) {
        int pos;
        if (scanf("%d", &pos) != 1 || pos < 0) break;
        if (pos <= 7) {
            multi_mask |= (1u << pos);
        }
    }
    
    printf("作成されたマスク: ");
    print_bits_detailed(multi_mask);
    printf("\n");
    
    printf("元の値とマスクのOR: ");
    print_bits_detailed(num | multi_mask);
    printf("\n");
    
    // 実用的な例（拡張版）
    printf("\n=== 実用的なビット操作例 (C99拡張) ===\n");
    
    // ビットパターンの解析
    typedef struct {
        uint8_t value;
        bool is_even;
        bool is_power_of_two;
        int bit_count;
        uint8_t reversed;
    } BitAnalysis;
    
    // ビット反転関数
    uint8_t reverse_bits = 0;
    for (int i = 0; i < 8; i++) {
        if (test_bit(num, i)) {
            reverse_bits |= (1u << (7 - i));
        }
    }
    
    BitAnalysis analysis = {
        .value = num,
        .is_even = !test_bit(num, 0),
        .is_power_of_two = is_power_of_two(num),
        .bit_count = count_bits(num),
        .reversed = reverse_bits
    };
    
    printf("ビット解析結果:\n");
    printf("  値: %u\n", analysis.value);
    printf("  偶数/奇数: %s\n", analysis.is_even ? "偶数" : "奇数");
    printf("  2のべき乗: %s\n", analysis.is_power_of_two ? "はい" : "いいえ");
    printf("  1のビット数: %d個\n", analysis.bit_count);
    printf("  ビット反転: ");
    print_bits_detailed(analysis.reversed);
    printf("\n");
    
    // C99: ビットフィールドのシミュレーション
    printf("\n=== ビットフィールドのシミュレーション ===\n");
    
    // RGBカラーの例（5-6-5形式）
    uint16_t color = 0;
    printf("RGB値を入力 (R:0-31, G:0-63, B:0-31): ");
    
    int r, g, b;
    if (scanf("%d %d %d", &r, &g, &b) == 3) {
        if (r >= 0 && r <= 31 && g >= 0 && g <= 63 && b >= 0 && b <= 31) {
            color = (uint16_t)((r << 11) | (g << 5) | b);
            printf("RGB565形式: 0x%04X\n", color);
            printf("  赤: %d\n", (color >> 11) & 0x1F);
            printf("  緑: %d\n", (color >> 5) & 0x3F);
            printf("  青: %d\n", color & 0x1F);
        } else {
            printf("値が範囲外です\n");
        }
    }
    
    // 高度なビット操作技法
    printf("\n=== 高度なビット操作技法 ===\n");
    
    // 最下位の1ビットを取得
    if (num != 0) {
        uint8_t lowest_bit = num & -num;
        printf("最下位の1ビット: ");
        print_bits_detailed(lowest_bit);
        printf("\n");
    }
    
    // 最下位の1ビットをクリア
    if (num != 0) {
        uint8_t clear_lowest = num & (num - 1);
        printf("最下位の1ビットをクリア: ");
        print_bits_detailed(clear_lowest);
        printf("\n");
    }
    
    // すべての末尾の0ビットを1に設定
    uint8_t set_trailing = num | (num - 1);
    printf("末尾の0ビットを1に設定: ");
    print_bits_detailed(set_trailing);
    printf("\n");
    
    return 0;
}

/*
実行例:
$ ./ex3_4_bitwise_c99
===== ビット操作 (C99版) =====
整数を入力してください (0-255): 170

元の値: 0b1010_1010 (0xAA, 170)

=== ビット単位の基本演算 ===
AND (上位4ビット) (マスク: 0xF0):
結果: 0b1010_0000 (0xA0, 160)

AND (下位4ビット) (マスク: 0x0F):
結果: 0b0000_1010 (0x0A,  10)

OR (下位4ビットセット) (マスク: 0x0F):
結果: 0b1010_1111 (0xAF, 175)

XOR (全ビット反転) (マスク: 0xFF):
結果: 0b0101_0101 (0x55,  85)

NOT (ビット反転) (単項演算子):
結果: 0b0101_0101 (0x55,  85)

=== ビットシフト演算 ===
左シフト 1ビット: 0b0101_0100 (0x54,  84) (2倍)
右シフト 1ビット: 0b0101_0101 (0x55,  85) (1/2)

=== 特定ビットの操作 ===
操作するビット位置を入力 (0-7): 3

ビット3の状態: 1 (セット)

ビット3の操作:
セット後: 0b1010_1010 (0xAA, 170)
クリア後: 0b1010_0010 (0xA2, 162)
反転後: 0b1010_0010 (0xA2, 162)

=== 実用的なビット操作例 (C99拡張) ===
ビット解析結果:
  値: 170
  偶数/奇数: 偶数
  2のべき乗: いいえ
  1のビット数: 4個
  ビット反転: 0b0101_0101 (0x55,  85)

C99の改善点:
1. bool型による明確な真偽値表現
2. uint8_t/uint16_t による固定幅整数型
3. inline関数によるビット操作の抽象化
4. 構造体による情報の整理
5. 使用箇所での変数宣言による可読性向上
*/