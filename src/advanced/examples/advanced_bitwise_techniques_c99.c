/*
 * advanced_bitwise_techniques_c99.c
 * 高度なビット演算テクニックの実装例
 * C99準拠 - インライン関数、bool型、可変長配列の使用
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

// ビット表示関数（インライン化）
static inline void print_bits(uint32_t value, int bits) {
    for (int i = bits - 1; i >= 0; i--) {
        printf("%d", (value >> i) & 1);
        if (i % 4 == 0 && i > 0) printf(" ");
    }
}

// 2の累乗判定（Brian Kernighanのアルゴリズム）
static inline bool is_power_of_two(uint32_t n) {
    return n && !(n & (n - 1));
}

// ビットカウント - Brian Kernighanのアルゴリズム
static inline int count_bits_fast(uint32_t n) {
    int count = 0;
    while (n) {
        n &= (n - 1);  // 最下位の1を消す
        count++;
    }
    return count;
}

// ビットカウント - ルックアップテーブル版
static const uint8_t bit_count_table[256] = {
    0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4,
    // ... (省略 - 実際には256要素全て定義)
};

static inline int count_bits_lookup(uint32_t n) {
    return bit_count_table[n & 0xFF] +
           bit_count_table[(n >> 8) & 0xFF] +
           bit_count_table[(n >> 16) & 0xFF] +
           bit_count_table[(n >> 24) & 0xFF];
}

// RGB色構造体
typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} RGBColor;

// RGB色の操作（構造体版）
static inline uint32_t rgb_to_uint(const RGBColor *color) {
    return ((uint32_t)color->red << 16) | 
           ((uint32_t)color->green << 8) | 
           color->blue;
}

static inline RGBColor uint_to_rgb(uint32_t color) {
    return (RGBColor){
        .red   = (color >> 16) & 0xFF,
        .green = (color >> 8) & 0xFF,
        .blue  = color & 0xFF
    };
}

// 高度なフラグ管理
typedef enum {
    PERM_READ    = 0x01,
    PERM_WRITE   = 0x02,
    PERM_EXECUTE = 0x04,
    PERM_DELETE  = 0x08,
    PERM_ALL     = 0x0F
} Permission;

typedef struct {
    uint8_t flags;
} PermissionSet;

static inline void perm_grant(PermissionSet *pset, Permission perm) {
    pset->flags |= perm;
}

static inline void perm_revoke(PermissionSet *pset, Permission perm) {
    pset->flags &= ~perm;
}

static inline bool perm_check(const PermissionSet *pset, Permission perm) {
    return (pset->flags & perm) == perm;
}

// ビットフィールドを使った日付時刻
typedef struct {
    uint32_t year   : 12;  // 0-4095
    uint32_t month  : 4;   // 0-15
    uint32_t day    : 5;   // 0-31
    uint32_t hour   : 5;   // 0-31
    uint32_t minute : 6;   // 0-63
} PackedDateTime;

// 次の2の累乗に切り上げ
static inline uint32_t next_power_of_two(uint32_t n) {
    n--;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    n++;
    return n;
}

// ビット反転（32ビット）
static inline uint32_t reverse_bits(uint32_t n) {
    n = ((n & 0xAAAAAAAA) >> 1) | ((n & 0x55555555) << 1);
    n = ((n & 0xCCCCCCCC) >> 2) | ((n & 0x33333333) << 2);
    n = ((n & 0xF0F0F0F0) >> 4) | ((n & 0x0F0F0F0F) << 4);
    n = ((n & 0xFF00FF00) >> 8) | ((n & 0x00FF00FF) << 8);
    n = (n >> 16) | (n << 16);
    return n;
}

int main(void) {
    printf("===== 高度なビット演算テクニック (C99) =====\n");
    
    // 2の累乗判定と次の2の累乗
    printf("\n--- 2の累乗判定と切り上げ ---\n");
    uint32_t nums[] = {1, 7, 8, 15, 16, 31, 32};
    size_t num_count = sizeof(nums) / sizeof(nums[0]);
    
    for (size_t i = 0; i < num_count; i++) {
        uint32_t n = nums[i];
        printf("%u: ", n);
        if (is_power_of_two(n)) {
            printf("2の累乗です\n");
        } else {
            printf("2の累乗ではありません → 次の2の累乗: %u\n", 
                   next_power_of_two(n));
        }
    }
    
    // RGB色操作（構造体版）
    printf("\n--- RGB色操作（構造体版） ---\n");
    RGBColor color = {.red = 0xFF, .green = 0x57, .blue = 0x33};
    uint32_t packed = rgb_to_uint(&color);
    printf("RGB(%d, %d, %d) → 0x%06X\n", 
           color.red, color.green, color.blue, packed);
    
    // 色を変更
    color.green = 0x80;
    packed = rgb_to_uint(&color);
    printf("緑を変更後: 0x%06X\n", packed);
    
    // 高度なフラグ管理
    printf("\n--- 高度なフラグ管理 ---\n");
    PermissionSet user_perms = {0};
    
    perm_grant(&user_perms, PERM_READ | PERM_WRITE);
    printf("読み書き権限付与後: 0x%02X\n", user_perms.flags);
    
    if (perm_check(&user_perms, PERM_READ)) {
        printf("読み取り権限: あり\n");
    }
    
    perm_revoke(&user_perms, PERM_WRITE);
    printf("書き込み権限削除後: 0x%02X\n", user_perms.flags);
    
    // ビット反転
    printf("\n--- ビット反転 ---\n");
    uint32_t original = 0x12345678;
    uint32_t reversed = reverse_bits(original);
    printf("元: 0x%08X (", original);
    print_bits(original, 32);
    printf(")\n");
    printf("反転: 0x%08X (", reversed);
    print_bits(reversed, 32);
    printf(")\n");
    
    // 日付時刻の圧縮（ビットフィールド）
    printf("\n--- 日付時刻の圧縮 ---\n");
    PackedDateTime dt = {
        .year = 2024,
        .month = 12,
        .day = 25,
        .hour = 23,
        .minute = 59
    };
    
    printf("構造体サイズ: %zu バイト\n", sizeof(PackedDateTime));
    printf("保存された日時: %u年%u月%u日 %u時%u分\n",
           dt.year, dt.month, dt.day, dt.hour, dt.minute);
    
    // 可変長配列でビットマップ
    printf("\n--- 動的ビットマップ ---\n");
    int bitmap_size = 3;  // 3 * 32 = 96ビット
    uint32_t bitmap[bitmap_size];
    
    // 初期化
    for (int i = 0; i < bitmap_size; i++) {
        bitmap[i] = 0;
    }
    
    // ビット42を立てる
    int bit_pos = 42;
    int word_idx = bit_pos / 32;
    int bit_idx = bit_pos % 32;
    bitmap[word_idx] |= (1U << bit_idx);
    
    printf("ビット%dを立てた後:\n", bit_pos);
    for (int i = 0; i < bitmap_size; i++) {
        printf("  word[%d]: 0x%08X\n", i, bitmap[i]);
    }
    
    return 0;
}