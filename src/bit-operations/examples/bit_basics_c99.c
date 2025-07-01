/*
 * ビット操作の基本（C99準拠版）
 * 
 * このプログラムは、C99の機能を活用して
 * より柔軟なビット操作の実装を示します。
 */
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

/* ビットマスクの定義 */
#define BIT(n) (1U << (n))

/* インライン関数でビット操作 */
static inline void set_bit(uint8_t *value, int bit) {
    *value |= BIT(bit);
}

static inline void clear_bit(uint8_t *value, int bit) {
    *value &= ~BIT(bit);
}

static inline void toggle_bit(uint8_t *value, int bit) {
    *value ^= BIT(bit);
}

static inline bool test_bit(uint8_t value, int bit) {
    return (value & BIT(bit)) != 0;
}

/* ビットを表示する関数（改良版） */
void print_bits_detailed(uint8_t value, const char *label)
{
    printf("%-20s: 0b", label);
    for (int i = 7; i >= 0; i--) {
        printf("%d", (value >> i) & 1);
        if (i == 4) printf(" ");  // 読みやすさのため4ビットごとに区切り
    }
    printf(" (0x%02X, %3u)\n", value, value);
}

/* ビットパターンの検索 */
int find_first_set_bit(uint32_t value)
{
    if (value == 0) return -1;
    
    int position = 0;
    while ((value & 1) == 0) {
        value >>= 1;
        position++;
    }
    return position;
}

/* ビット幅の取得 */
int get_bit_width(uint32_t value)
{
    if (value == 0) return 0;
    
    int width = 0;
    while (value > 0) {
        value >>= 1;
        width++;
    }
    return width;
}

int main(void)
{
    printf("=== ビット演算の基本（C99版） ===\n\n");
    
    /* 固定幅整数型の使用 */
    uint8_t flags = 0x00;
    uint16_t mask = 0xF0F0;
    uint32_t data = 0x12345678;
    
    printf("--- 固定幅整数型 ---\n");
    printf("uint8_t  サイズ: %zu バイト\n", sizeof(uint8_t));
    printf("uint16_t サイズ: %zu バイト\n", sizeof(uint16_t));
    printf("uint32_t サイズ: %zu バイト\n", sizeof(uint32_t));
    printf("\n");
    
    /* インライン関数でのビット操作 */
    printf("--- インライン関数での操作 ---\n");
    print_bits_detailed(flags, "初期状態");
    
    set_bit(&flags, 3);
    print_bits_detailed(flags, "ビット3をセット");
    
    set_bit(&flags, 6);
    print_bits_detailed(flags, "ビット6もセット");
    
    toggle_bit(&flags, 3);
    print_bits_detailed(flags, "ビット3を反転");
    
    clear_bit(&flags, 6);
    print_bits_detailed(flags, "ビット6をクリア");
    
    /* bool型でのテスト結果 */
    printf("\nビット状態（bool型）:\n");
    for (int i = 0; i < 8; i++) {
        bool is_set = test_bit(flags, i);
        if (is_set) {
            printf("  ビット%d: ON\n", i);
        }
    }
    printf("\n");
    
    /* 複合リテラルを使った初期化 */
    printf("--- 複合リテラル ---\n");
    struct BitFlags {
        uint8_t byte1;
        uint8_t byte2;
    };
    
    struct BitFlags *bf = &(struct BitFlags){0xAA, 0x55};
    printf("byte1: 0x%02X, byte2: 0x%02X\n", bf->byte1, bf->byte2);
    printf("\n");
    
    /* ビットパターンの検索 */
    printf("--- ビットパターン検索 ---\n");
    uint32_t test_values[] = {0x00000000, 0x00000001, 0x00000080, 0x00100000};
    
    for (size_t i = 0; i < sizeof(test_values)/sizeof(test_values[0]); i++) {
        int pos = find_first_set_bit(test_values[i]);
        printf("0x%08X: ", test_values[i]);
        if (pos >= 0) {
            printf("最初の1はビット%d\n", pos);
        } else {
            printf("1が見つかりません\n");
        }
    }
    printf("\n");
    
    /* ビット幅の計算 */
    printf("--- ビット幅計算 ---\n");
    uint32_t width_tests[] = {0, 1, 15, 16, 255, 256, 65535, 65536};
    
    for (size_t i = 0; i < sizeof(width_tests)/sizeof(width_tests[0]); i++) {
        int width = get_bit_width(width_tests[i]);
        printf("%6u: %2d ビット必要\n", width_tests[i], width);
    }
    printf("\n");
    
    /* 可変長配列でビットマップ */
    printf("--- 動的ビットマップ ---\n");
    int bitmap_size = 3;  // 3バイト = 24ビット
    uint8_t bitmap[bitmap_size];
    
    // 初期化
    for (int i = 0; i < bitmap_size; i++) {
        bitmap[i] = 0;
    }
    
    // 特定のビットをセット（0, 7, 8, 15, 23）
    int set_positions[] = {0, 7, 8, 15, 23};
    
    for (size_t i = 0; i < sizeof(set_positions)/sizeof(set_positions[0]); i++) {
        int pos = set_positions[i];
        int byte_idx = pos / 8;
        int bit_idx = pos % 8;
        bitmap[byte_idx] |= BIT(bit_idx);
    }
    
    // ビットマップの表示
    printf("ビットマップ（%dバイト）:\n", bitmap_size);
    for (int i = 0; i < bitmap_size; i++) {
        printf("  バイト%d: ", i);
        print_bits_detailed(bitmap[i], "");
    }
    
    return 0;
}