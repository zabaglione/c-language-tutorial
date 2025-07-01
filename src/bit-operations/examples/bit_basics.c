/*
 * ビット操作の基本（C90準拠版）
 * 
 * このプログラムは、ビット演算子の基本的な使い方と
 * ビットマスクを使った操作を示します。
 */
#include <stdio.h>

/* ビットマスクの定義 */
#define BIT0 0x01
#define BIT1 0x02
#define BIT2 0x04
#define BIT3 0x08
#define BIT4 0x10
#define BIT5 0x20
#define BIT6 0x40
#define BIT7 0x80

/* ビット操作マクロ */
#define SET_BIT(value, bit)    ((value) |= (1 << (bit)))
#define CLEAR_BIT(value, bit)  ((value) &= ~(1 << (bit)))
#define TOGGLE_BIT(value, bit) ((value) ^= (1 << (bit)))
#define TEST_BIT(value, bit)   ((value) & (1 << (bit)))

/* ビットを表示する関数 */
void print_bits(unsigned char value)
{
    int i;
    printf("0b");
    for (i = 7; i >= 0; i--) {
        printf("%d", (value >> i) & 1);
    }
    printf(" (0x%02X, %3u)\n", value, value);
}

int main(void)
{
    unsigned char a = 0xA5;  /* 10100101 */
    unsigned char b = 0x3C;  /* 00111100 */
    unsigned char result;
    unsigned char flags = 0x00;
    int i;
    
    printf("=== ビット演算の基本 ===\n\n");
    
    /* 元の値を表示 */
    printf("a = "); print_bits(a);
    printf("b = "); print_bits(b);
    printf("\n");
    
    /* 基本的なビット演算 */
    printf("--- 基本演算 ---\n");
    
    result = a & b;
    printf("a & b  = "); print_bits(result);
    
    result = a | b;
    printf("a | b  = "); print_bits(result);
    
    result = a ^ b;
    printf("a ^ b  = "); print_bits(result);
    
    result = ~a;
    printf("~a     = "); print_bits(result);
    
    printf("\n");
    
    /* シフト演算 */
    printf("--- シフト演算 ---\n");
    
    result = a << 2;
    printf("a << 2 = "); print_bits(result);
    
    result = a >> 2;
    printf("a >> 2 = "); print_bits(result);
    
    printf("\n");
    
    /* ビットマスクを使った操作 */
    printf("--- ビットマスク操作 ---\n");
    
    /* 特定ビットのセット */
    flags = 0x00;
    flags |= BIT3;
    printf("BIT3をセット後:     "); print_bits(flags);
    
    flags |= BIT5;
    printf("BIT5もセット後:     "); print_bits(flags);
    
    /* 特定ビットのクリア */
    flags &= ~BIT3;
    printf("BIT3をクリア後:     "); print_bits(flags);
    
    /* 特定ビットの反転 */
    flags ^= BIT5;
    printf("BIT5を反転後:       "); print_bits(flags);
    flags ^= BIT5;
    printf("BIT5を再度反転後:   "); print_bits(flags);
    
    /* 特定ビットのテスト */
    printf("\nBIT5の状態: %s\n", (flags & BIT5) ? "ON" : "OFF");
    printf("BIT3の状態: %s\n", (flags & BIT3) ? "ON" : "OFF");
    
    printf("\n");
    
    /* マクロを使った操作 */
    printf("--- マクロを使った操作 ---\n");
    
    flags = 0x00;
    printf("初期状態:           "); print_bits(flags);
    
    SET_BIT(flags, 2);
    printf("ビット2をセット:    "); print_bits(flags);
    
    SET_BIT(flags, 6);
    printf("ビット6もセット:    "); print_bits(flags);
    
    TOGGLE_BIT(flags, 2);
    printf("ビット2を反転:      "); print_bits(flags);
    
    CLEAR_BIT(flags, 6);
    printf("ビット6をクリア:    "); print_bits(flags);
    
    printf("\n");
    
    /* ビットカウント */
    printf("--- ビットカウント ---\n");
    a = 0xB7;  /* 10110111 */
    printf("値: "); print_bits(a);
    
    /* 1のビットを数える */
    result = 0;
    for (i = 0; i < 8; i++) {
        if (TEST_BIT(a, i)) {
            result++;
        }
    }
    printf("1のビット数: %d\n", result);
    
    /* Brian Kernighanのアルゴリズム */
    result = 0;
    b = a;
    while (b) {
        b &= (b - 1);
        result++;
    }
    printf("1のビット数（高速版）: %d\n", result);
    
    return 0;
}