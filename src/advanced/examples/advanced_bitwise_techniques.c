/*
 * advanced_bitwise_techniques.c
 * 高度なビット演算テクニックの実装例
 * C90準拠
 */

#include <stdio.h>
#include <stdlib.h>

/* ビット表示関数 */
void print_bits(unsigned int value, int bits) {
    int i;
    for (i = bits - 1; i >= 0; i--) {
        printf("%d", (value >> i) & 1);
        if (i % 4 == 0 && i > 0) printf(" ");
    }
}

/* 2の累乗判定（Brian Kernighanのアルゴリズム） */
int is_power_of_two(unsigned int n) {
    /* n が 0 でなく、n & (n-1) が 0 なら2の累乗 */
    return n && !(n & (n - 1));
}

/* ビットカウント（1の数を数える）- 基本版 */
int count_bits(unsigned int n) {
    int count = 0;
    while (n) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}

/* ビットカウント - Brian Kernighanのアルゴリズム */
int count_bits_fast(unsigned int n) {
    int count = 0;
    while (n) {
        n &= (n - 1);  /* 最下位の1を消す */
        count++;
    }
    return count;
}

/* RGB色の操作デモ */
void rgb_demo(void) {
    unsigned int color = 0xFF5733;  /* RGB: FF(赤) 57(緑) 33(青) */
    unsigned char red, green, blue;
    unsigned int new_color;
    
    printf("\n=== RGB色の操作 ===\n");
    printf("元の色: 0x%06X\n", color);
    
    /* 各色成分を抽出 */
    red   = (color >> 16) & 0xFF;
    green = (color >> 8) & 0xFF;
    blue  = color & 0xFF;
    
    printf("赤: 0x%02X (%d)\n", red, red);
    printf("緑: 0x%02X (%d)\n", green, green);
    printf("青: 0x%02X (%d)\n", blue, blue);
    
    /* 色成分を変更 */
    green = 0x80;  /* 緑を変更 */
    new_color = (red << 16) | (green << 8) | blue;
    printf("\n緑を0x80に変更: 0x%06X\n", new_color);
    
    /* マスクを使った部分更新 */
    color = (color & 0xFF00FF) | (0x80 << 8);
    printf("マスクを使った更新: 0x%06X\n", color);
}

/* フラグ管理システムのデモ */
void flag_management_demo(void) {
    /* フラグの定義 */
    #define FLAG_READ     0x01  /* 00000001 */
    #define FLAG_WRITE    0x02  /* 00000010 */
    #define FLAG_EXECUTE  0x04  /* 00000100 */
    #define FLAG_DELETE   0x08  /* 00001000 */
    
    unsigned char permissions = 0;
    
    printf("\n=== フラグ管理システム ===\n");
    
    /* フラグを立てる */
    permissions |= FLAG_READ;
    permissions |= FLAG_WRITE;
    printf("読み書き権限設定後: ");
    print_bits(permissions, 8);
    printf("\n");
    
    /* 複数フラグを同時に立てる */
    permissions |= (FLAG_EXECUTE | FLAG_DELETE);
    printf("全権限設定後: ");
    print_bits(permissions, 8);
    printf("\n");
    
    /* フラグの確認 */
    if (permissions & FLAG_READ) {
        printf("読み取り: 可能\n");
    }
    
    /* 複数フラグの同時確認 */
    if ((permissions & (FLAG_READ | FLAG_WRITE)) == (FLAG_READ | FLAG_WRITE)) {
        printf("読み書き: 両方可能\n");
    }
    
    /* フラグをクリア */
    permissions &= ~FLAG_WRITE;
    printf("書き込み権限削除後: ");
    print_bits(permissions, 8);
    printf("\n");
    
    /* フラグを反転 */
    permissions ^= FLAG_EXECUTE;
    printf("実行権限反転後: ");
    print_bits(permissions, 8);
    printf("\n");
}

/* ビット圧縮の例 */
unsigned int pack_date(int year, int month, int day) {
    /* year: 12ビット (0-4095)
     * month: 4ビット (0-15)
     * day: 5ビット (0-31)
     * 合計21ビット使用
     */
    return ((year & 0xFFF) << 9) |  /* 年を上位12ビット */
           ((month & 0xF) << 5) |    /* 月を次の4ビット */
           (day & 0x1F);             /* 日を下位5ビット */
}

void unpack_date(unsigned int packed, int *year, int *month, int *day) {
    *year = (packed >> 9) & 0xFFF;
    *month = (packed >> 5) & 0xF;
    *day = packed & 0x1F;
}

int main(void) {
    unsigned int num;
    int year, month, day;
    unsigned int packed;
    
    printf("===== 高度なビット演算テクニック =====\n");
    
    /* 2の累乗判定 */
    printf("\n--- 2の累乗判定 ---\n");
    for (num = 0; num <= 16; num++) {
        if (is_power_of_two(num)) {
            printf("%u は2の累乗です\n", num);
        }
    }
    
    /* ビットカウント比較 */
    printf("\n--- ビットカウント ---\n");
    num = 0xF5;  /* 11110101 */
    printf("数値: 0x%02X (", num);
    print_bits(num, 8);
    printf(")\n");
    printf("基本アルゴリズム: %d個の1\n", count_bits(num));
    printf("高速アルゴリズム: %d個の1\n", count_bits_fast(num));
    
    /* RGB色操作 */
    rgb_demo();
    
    /* フラグ管理 */
    flag_management_demo();
    
    /* 日付の圧縮 */
    printf("\n=== 日付の圧縮 ===\n");
    year = 2024;
    month = 12;
    day = 25;
    
    packed = pack_date(year, month, day);
    printf("元の日付: %d年%d月%d日\n", year, month, day);
    printf("圧縮後: 0x%06X (", packed);
    print_bits(packed, 21);
    printf(")\n");
    
    unpack_date(packed, &year, &month, &day);
    printf("展開後: %d年%d月%d日\n", year, month, day);
    
    return 0;
}