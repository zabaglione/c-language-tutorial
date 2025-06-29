/*
 * ファイル名: numeric_literals.c
 * 説明: C23の数値リテラル機能（2進数リテラル、数値区切り）
 * 規格: C23
 */

#include <stdio.h>

int main(void)
{
    printf("=== C23 数値リテラルの新機能 ===\n");
    
    /* 2進数リテラル (0b または 0B プレフィックス) */
    printf("\n--- 2進数リテラル ---\n");
    
    int binary1 = 0b1010;        /* 10進数の10 */
    int binary2 = 0B11111111;    /* 10進数の255 */
    int binary3 = 0b10101010;    /* 10進数の170 */
    
    printf("0b1010 = %d\n", binary1);
    printf("0B11111111 = %d\n", binary2);
    printf("0b10101010 = %d (0x%X)\n", binary3, binary3);
    
    /* ビット演算での活用 */
    printf("\n--- ビット演算での活用 ---\n");
    
    unsigned char flags = 0b00000000;
    flags |= 0b00000001;  /* ビット0をセット */
    flags |= 0b00001000;  /* ビット3をセット */
    flags |= 0b10000000;  /* ビット7をセット */
    
    printf("フラグ: 0b");
    for (int i = 7; i >= 0; i--) {
        printf("%d", (flags >> i) & 1);
    }
    printf(" (%d)\n", flags);
    
    /* マスクパターンの定義 */
    printf("\n--- マスクパターン ---\n");
    
    #define READ_PERMISSION   0b100  /* 読み取り許可 */
    #define WRITE_PERMISSION  0b010  /* 書き込み許可 */
    #define EXEC_PERMISSION   0b001  /* 実行許可 */
    
    unsigned int permissions = READ_PERMISSION | WRITE_PERMISSION;
    printf("権限: 0b%03b (読み取り%s, 書き込み%s, 実行%s)\n",
           permissions,
           (permissions & READ_PERMISSION) ? "○" : "×",
           (permissions & WRITE_PERMISSION) ? "○" : "×",
           (permissions & EXEC_PERMISSION) ? "○" : "×");
    
    /* 数値区切り（コンパイラサポート次第） */
    printf("\n--- 数値区切り（C23で検討中） ---\n");
    
    /* 注: 数値区切りは最終仕様では採用されない可能性あり */
    /* int large_number = 1'000'000; */  /* コンパイラサポート待ち */
    
    int large_number = 1000000;
    printf("大きな数値: %d\n", large_number);
    
    /* 他の基数での2進数リテラル */
    printf("\n--- 様々な基数との比較 ---\n");
    
    int value = 42;
    printf("10進数: %d\n", value);
    printf("16進数: 0x%X\n", value);
    printf("8進数: 0%o\n", value);
    printf("2進数: 0b");
    for (int i = 7; i >= 0; i--) {
        printf("%d", (value >> i) & 1);
    }
    printf("\n");
    
    /* 実用例: レジスタ設定 */
    printf("\n--- 実用例: レジスタ設定 ---\n");
    
    /* ハードウェアレジスタのビット定義 */
    #define REG_ENABLE    0b10000000
    #define REG_INTERRUPT 0b01000000
    #define REG_MODE_MASK 0b00110000
    #define REG_MODE_A    0b00000000
    #define REG_MODE_B    0b00010000
    #define REG_MODE_C    0b00100000
    
    unsigned char reg = REG_ENABLE | REG_MODE_B;
    printf("レジスタ値: 0b%08b (0x%02X)\n", reg, reg);
    
    return 0;
}


/*
 * 実行結果例:
 * === C23 数値リテラルの新機能 ===
 * 
 * --- 2進数リテラル ---
 * 0b1010 = 10
 * 0B11111111 = 255
 * 0b10101010 = 170 (0xAA)
 * 
 * --- ビット演算での活用 ---
 * フラグ: 0b10001001 (137)
 * 
 * --- マスクパターン ---
 * 権限: 0b110 (読み取り○, 書き込み○, 実行×)
 * 
 * --- 数値区切り（C23で検討中） ---
 * 大きな数値: 1000000
 * 
 * --- 様々な基数との比較 ---
 * 10進数: 42
 * 16進数: 0x2A
 * 8進数: 052
 * 2進数: 0b00101010
 * 
 * --- 実用例: レジスタ設定 ---
 * レジスタ値: 0b10010000 (0x90)
 */