/*
 * bitwise_demo.c
 * ビット演算の動作を可視化して確認
 * C90準拠
 */

#include <stdio.h>

/* ビットパターンを表示する関数 */
void print_bits(unsigned char value) {
    int i;
    for (i = 7; i >= 0; i--) {
        printf("%d", (value >> i) & 1);
        if (i == 4) printf(" "); /* 読みやすさのため4ビットごとに空白 */
    }
}

int main(void) {
    unsigned char a = 5;    /* 00000101 */
    unsigned char b = 3;    /* 00000011 */
    unsigned char result;
    
    printf("===== ビット演算のデモ =====\n");
    printf("初期値:\n");
    printf("  a = %3d : ", a);
    print_bits(a);
    printf("\n");
    printf("  b = %3d : ", b);
    print_bits(b);
    printf("\n\n");
    
    /* ビットAND */
    result = a & b;
    printf("ビットAND (a & b):\n");
    printf("  ");
    print_bits(a);
    printf("\n& ");
    print_bits(b);
    printf("\n---------------\n  ");
    print_bits(result);
    printf(" = %d\n\n", result);
    
    /* ビットOR */
    result = a | b;
    printf("ビットOR (a | b):\n");
    printf("  ");
    print_bits(a);
    printf("\n| ");
    print_bits(b);
    printf("\n---------------\n  ");
    print_bits(result);
    printf(" = %d\n\n", result);
    
    /* ビットXOR */
    result = a ^ b;
    printf("ビットXOR (a ^ b):\n");
    printf("  ");
    print_bits(a);
    printf("\n^ ");
    print_bits(b);
    printf("\n---------------\n  ");
    print_bits(result);
    printf(" = %d\n\n", result);
    
    /* ビット反転 */
    result = ~a;
    printf("ビット反転 (~a):\n");
    printf("~ ");
    print_bits(a);
    printf("\n---------------\n  ");
    print_bits(result);
    printf(" = %d\n\n", result);
    
    /* 左シフト */
    printf("===== シフト演算のデモ =====\n");
    a = 5;  /* リセット */
    
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
    
    /* 右シフト */
    a = 20; /* 00010100 */
    
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
    
    /* 実用例：フラグ管理 */
    printf("===== ビット演算の実用例（フラグ管理） =====\n");
    #define FLAG_A 0x01  /* 0000 0001 */
    #define FLAG_B 0x02  /* 0000 0010 */
    #define FLAG_C 0x04  /* 0000 0100 */
    #define FLAG_D 0x08  /* 0000 1000 */
    
    unsigned char flags = 0;
    
    printf("初期状態: ");
    print_bits(flags);
    printf("\n");
    
    /* フラグを立てる */
    flags |= FLAG_A;
    printf("FLAG_A を立てる: ");
    print_bits(flags);
    printf("\n");
    
    flags |= FLAG_C;
    printf("FLAG_C を立てる: ");
    print_bits(flags);
    printf("\n");
    
    /* フラグのチェック */
    if (flags & FLAG_A) {
        printf("FLAG_A は ON です\n");
    }
    if (flags & FLAG_B) {
        printf("FLAG_B は ON です\n");
    } else {
        printf("FLAG_B は OFF です\n");
    }
    
    /* フラグをクリア */
    flags &= ~FLAG_A;
    printf("FLAG_A をクリア: ");
    print_bits(flags);
    printf("\n");
    
    /* フラグをトグル */
    flags ^= FLAG_B;
    printf("FLAG_B をトグル: ");
    print_bits(flags);
    printf("\n");
    
    return 0;
}
