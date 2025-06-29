/*
 * bitwise_demo_c99.c
 * ビット演算の動作を可視化して確認
 * C99準拠 - //コメント、bool型、変数宣言位置の自由化、stdint.h
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

// ビットパターンを表示する関数
void print_bits(uint8_t value) {
    for (int i = 7; i >= 0; i--) {
        printf("%d", (value >> i) & 1);
        if (i == 4) printf(" "); // 読みやすさのため4ビットごとに空白
    }
}

// 16ビットのビットパターンを表示する関数（C99追加）
void print_bits16(uint16_t value) {
    for (int i = 15; i >= 0; i--) {
        printf("%d", (value >> i) & 1);
        if (i % 4 == 0 && i > 0) printf(" ");
    }
}

int main(void) {
    printf("===== ビット演算のデモ =====\n");
    
    // C99: uint8_t型を使用（正確な8ビット）
    uint8_t a = 5;    // 00000101
    uint8_t b = 3;    // 00000011
    
    printf("初期値:\n");
    printf("  a = %3d : ", a);
    print_bits(a);
    printf("\n");
    printf("  b = %3d : ", b);
    print_bits(b);
    printf("\n\n");
    
    // ビットAND
    uint8_t result = a & b;  // C99: 使用箇所で変数宣言
    printf("ビットAND (a & b):\n");
    printf("  ");
    print_bits(a);
    printf("\n& ");
    print_bits(b);
    printf("\n---------------\n  ");
    print_bits(result);
    printf(" = %d\n\n", result);
    
    // ビットOR
    result = a | b;
    printf("ビットOR (a | b):\n");
    printf("  ");
    print_bits(a);
    printf("\n| ");
    print_bits(b);
    printf("\n---------------\n  ");
    print_bits(result);
    printf(" = %d\n\n", result);
    
    // ビットXOR
    result = a ^ b;
    printf("ビットXOR (a ^ b):\n");
    printf("  ");
    print_bits(a);
    printf("\n^ ");
    print_bits(b);
    printf("\n---------------\n  ");
    print_bits(result);
    printf(" = %d\n\n", result);
    
    // ビット反転
    result = ~a;
    printf("ビット反転 (~a):\n");
    printf("~ ");
    print_bits(a);
    printf("\n---------------\n  ");
    print_bits(result);
    printf(" = %d\n\n", result);
    
    // シフト演算
    printf("===== シフト演算のデモ =====\n");
    a = 5;  // リセット
    
    result = a << 1;
    printf("左シフト (a << 1):\n");
    printf("  ");
    print_bits(a);
    printf(" << 1\n= ");
    print_bits(result);
    printf(" = %d (2倍)\n\n", result);
    
    result = a << 2;
    printf("左シフト (a << 2):\n");
    printf("  ");
    print_bits(a);
    printf(" << 2\n= ");
    print_bits(result);
    printf(" = %d (4倍)\n\n", result);
    
    // 右シフト
    a = 20; // 00010100
    
    result = a >> 1;
    printf("右シフト (a >> 1):\n");
    printf("  ");
    print_bits(a);
    printf(" >> 1\n= ");
    print_bits(result);
    printf(" = %d (1/2)\n\n", result);
    
    result = a >> 2;
    printf("右シフト (a >> 2):\n");
    printf("  ");
    print_bits(a);
    printf(" >> 2\n= ");
    print_bits(result);
    printf(" = %d (1/4)\n\n", result);
    
    // C99: 16ビット演算のデモ
    printf("===== 16ビット演算のデモ（C99） =====\n");
    uint16_t x = 0x1234;  // 0001 0010 0011 0100
    uint16_t y = 0x5678;  // 0101 0110 0111 1000
    
    printf("x = 0x%04X : ", x);
    print_bits16(x);
    printf("\n");
    printf("y = 0x%04X : ", y);
    print_bits16(y);
    printf("\n\n");
    
    uint16_t result16 = x & y;
    printf("x & y = 0x%04X : ", result16);
    print_bits16(result16);
    printf("\n\n");
    
    // 実用例：フラグ管理
    printf("===== ビット演算の実用例（フラグ管理） =====\n");
    
    // C99: enum定義
    enum {
        FLAG_A = 0x01,  // 0000 0001
        FLAG_B = 0x02,  // 0000 0010
        FLAG_C = 0x04,  // 0000 0100
        FLAG_D = 0x08   // 0000 1000
    };
    
    uint8_t flags = 0;
    
    printf("初期状態: ");
    print_bits(flags);
    printf("\n");
    
    // フラグを立てる
    flags |= FLAG_A;
    printf("FLAG_A を立てる: ");
    print_bits(flags);
    printf("\n");
    
    flags |= FLAG_C;
    printf("FLAG_C を立てる: ");
    print_bits(flags);
    printf("\n");
    
    // フラグのチェック（C99: bool型）
    bool flag_a_on = flags & FLAG_A;
    bool flag_b_on = flags & FLAG_B;
    
    if (flag_a_on) {
        printf("FLAG_A は ON です\n");
    }
    if (!flag_b_on) {
        printf("FLAG_B は OFF です\n");
    }
    
    // フラグをクリア
    flags &= ~FLAG_A;
    printf("FLAG_A をクリア: ");
    print_bits(flags);
    printf("\n");
    
    // フラグをトグル
    flags ^= FLAG_B;
    printf("FLAG_B をトグル: ");
    print_bits(flags);
    printf("\n");
    
    // C99: 複数フラグの同時操作
    printf("\n複数フラグの同時操作:\n");
    flags = 0;
    flags |= (FLAG_A | FLAG_C | FLAG_D);  // 複数フラグを一度に立てる
    printf("A,C,D を立てる: ");
    print_bits(flags);
    printf("\n");
    
    flags &= ~(FLAG_A | FLAG_C);  // 複数フラグを一度にクリア
    printf("A,C をクリア: ");
    print_bits(flags);
    printf("\n");
    
    return 0;
}
