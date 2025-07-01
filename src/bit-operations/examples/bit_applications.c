/*
 * ビット操作の実践的応用（C90準拠版）
 * 
 * 実際のプログラミングで使用される
 * ビット操作テクニックを示します。
 */
#include <stdio.h>
#include <string.h>

/* CRC計算用テーブル（簡易版） */
static const unsigned char crc8_table[16] = {
    0x00, 0x07, 0x0E, 0x09, 0x1C, 0x1B, 0x12, 0x15,
    0x38, 0x3F, 0x36, 0x31, 0x24, 0x23, 0x2A, 0x2D
};

/* ======================= */
/* 1. ビットベクタ管理     */
/* ======================= */

/* ビットベクタ構造体 */
typedef struct {
    unsigned char bits[32];  /* 256ビット分 */
} BitVector;

/* ビットベクタの初期化 */
void bitvec_init(BitVector *bv)
{
    memset(bv->bits, 0, sizeof(bv->bits));
}

/* ビットをセット */
void bitvec_set(BitVector *bv, int bit)
{
    if (bit >= 0 && bit < 256) {
        bv->bits[bit / 8] |= (1 << (bit % 8));
    }
}

/* ビットをクリア */
void bitvec_clear(BitVector *bv, int bit)
{
    if (bit >= 0 && bit < 256) {
        bv->bits[bit / 8] &= ~(1 << (bit % 8));
    }
}

/* ビットをテスト */
int bitvec_test(const BitVector *bv, int bit)
{
    if (bit >= 0 && bit < 256) {
        return (bv->bits[bit / 8] & (1 << (bit % 8))) != 0;
    }
    return 0;
}

/* ======================= */
/* 2. チェックサム計算     */
/* ======================= */

/* 簡易CRC8計算 */
unsigned char calc_crc8(const unsigned char *data, int len)
{
    unsigned char crc = 0x00;
    int i;
    
    for (i = 0; i < len; i++) {
        crc = crc8_table[crc >> 4] ^ crc8_table[(crc ^ data[i]) & 0x0F];
    }
    
    return crc;
}

/* パリティビット計算 */
unsigned char calc_parity(unsigned char byte)
{
    byte ^= byte >> 4;
    byte ^= byte >> 2;
    byte ^= byte >> 1;
    return byte & 1;
}

/* ======================= */
/* 3. エンコード/デコード  */
/* ======================= */

/* Base64エンコード表（一部） */
static const char base64_chars[] = 
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

/* 3バイトを4文字のBase64にエンコード（簡易版） */
void encode_base64_block(const unsigned char *in, char *out)
{
    out[0] = base64_chars[in[0] >> 2];
    out[1] = base64_chars[((in[0] & 0x03) << 4) | (in[1] >> 4)];
    out[2] = base64_chars[((in[1] & 0x0F) << 2) | (in[2] >> 6)];
    out[3] = base64_chars[in[2] & 0x3F];
}

/* 7セグメントディスプレイのパターン */
unsigned char get_7seg_pattern(int digit)
{
    /* 各セグメント: gfedcba */
    static const unsigned char patterns[10] = {
        0x3F,  /* 0: 0111111 */
        0x06,  /* 1: 0000110 */
        0x5B,  /* 2: 1011011 */
        0x4F,  /* 3: 1001111 */
        0x66,  /* 4: 1100110 */
        0x6D,  /* 5: 1101101 */
        0x7D,  /* 6: 1111101 */
        0x07,  /* 7: 0000111 */
        0x7F,  /* 8: 1111111 */
        0x6F   /* 9: 1101111 */
    };
    
    if (digit >= 0 && digit <= 9) {
        return patterns[digit];
    }
    return 0x00;
}

/* ======================= */
/* 4. グラフィックス処理   */
/* ======================= */

/* モノクロビットマップの反転 */
void invert_bitmap(unsigned char *bitmap, int size)
{
    int i;
    for (i = 0; i < size; i++) {
        bitmap[i] = ~bitmap[i];
    }
}

/* ビットマップの90度回転（8x8） */
void rotate_bitmap_90(unsigned char src[8], unsigned char dst[8])
{
    int i, j;
    
    /* 転置行列の作成 */
    for (i = 0; i < 8; i++) {
        dst[i] = 0;
        for (j = 0; j < 8; j++) {
            if (src[j] & (1 << (7 - i))) {
                dst[i] |= (1 << j);
            }
        }
    }
}

/* ======================= */
/* 5. 最適化テクニック     */
/* ======================= */

/* 2のべき乗への切り上げ */
unsigned int next_power_of_2(unsigned int n)
{
    n--;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    return n + 1;
}

/* ビット反転（8ビット） */
unsigned char reverse_bits(unsigned char byte)
{
    byte = ((byte & 0xF0) >> 4) | ((byte & 0x0F) << 4);
    byte = ((byte & 0xCC) >> 2) | ((byte & 0x33) << 2);
    byte = ((byte & 0xAA) >> 1) | ((byte & 0x55) << 1);
    return byte;
}

/* 最上位ビットの位置を取得 */
int find_msb_position(unsigned int n)
{
    int pos = -1;
    while (n) {
        n >>= 1;
        pos++;
    }
    return pos;
}

/* ======================= */
/* メイン関数              */
/* ======================= */

int main(void)
{
    int i;
    
    printf("=== ビット操作の実践的応用 ===\n\n");
    
    /* ビットベクタの使用例 */
    printf("--- ビットベクタ管理 ---\n");
    BitVector bv;
    bitvec_init(&bv);
    
    /* 素数の位置にビットをセット */
    int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
    for (i = 0; i < 11; i++) {
        bitvec_set(&bv, primes[i]);
    }
    
    printf("100以下の素数: ");
    for (i = 2; i <= 100; i++) {
        if (bitvec_test(&bv, i)) {
            printf("%d ", i);
        }
    }
    printf("\n\n");
    
    /* チェックサム計算 */
    printf("--- チェックサム計算 ---\n");
    unsigned char data[] = {0x01, 0x23, 0x45, 0x67, 0x89};
    unsigned char crc = calc_crc8(data, 5);
    printf("データ: ");
    for (i = 0; i < 5; i++) {
        printf("%02X ", data[i]);
    }
    printf("\nCRC8: %02X\n", crc);
    
    /* パリティビット */
    unsigned char test_byte = 0xA5;  /* 10100101 */
    printf("\n0x%02X のパリティ: %s\n", 
           test_byte, calc_parity(test_byte) ? "奇数" : "偶数");
    printf("\n");
    
    /* Base64エンコード */
    printf("--- エンコード/デコード ---\n");
    unsigned char raw[3] = {'A', 'B', 'C'};
    char encoded[5] = {0};
    encode_base64_block(raw, encoded);
    printf("\"ABC\" → Base64: %s\n", encoded);
    
    /* 7セグメント表示 */
    printf("\n7セグメントパターン:\n");
    for (i = 0; i < 10; i++) {
        printf("  %d: 0x%02X\n", i, get_7seg_pattern(i));
    }
    printf("\n");
    
    /* ビットマップ操作 */
    printf("--- グラフィックス処理 ---\n");
    unsigned char bitmap[8] = {
        0x18,  /* 00011000 */
        0x3C,  /* 00111100 */
        0x7E,  /* 01111110 */
        0xFF,  /* 11111111 */
        0xFF,  /* 11111111 */
        0x7E,  /* 01111110 */
        0x3C,  /* 00111100 */
        0x18   /* 00011000 */
    };
    
    printf("元のビットマップ:\n");
    for (i = 0; i < 8; i++) {
        int j;
        for (j = 7; j >= 0; j--) {
            printf("%c", (bitmap[i] & (1 << j)) ? '#' : '.');
        }
        printf("\n");
    }
    
    /* 反転 */
    invert_bitmap(bitmap, 8);
    printf("\n反転後:\n");
    for (i = 0; i < 8; i++) {
        int j;
        for (j = 7; j >= 0; j--) {
            printf("%c", (bitmap[i] & (1 << j)) ? '#' : '.');
        }
        printf("\n");
    }
    printf("\n");
    
    /* 最適化テクニック */
    printf("--- 最適化テクニック ---\n");
    
    /* 2のべき乗への切り上げ */
    unsigned int test_values[] = {5, 16, 17, 100, 1000};
    for (i = 0; i < 5; i++) {
        printf("%4u → %4u\n", 
               test_values[i], next_power_of_2(test_values[i]));
    }
    
    /* ビット反転 */
    printf("\nビット反転:\n");
    unsigned char rev_test = 0xE4;  /* 11100100 */
    printf("0x%02X → 0x%02X\n", rev_test, reverse_bits(rev_test));
    
    /* MSB位置 */
    printf("\n最上位ビット位置:\n");
    unsigned int msb_tests[] = {1, 8, 15, 16, 255, 256};
    for (i = 0; i < 6; i++) {
        printf("%3u: ビット%d\n", 
               msb_tests[i], find_msb_position(msb_tests[i]));
    }
    
    return 0;
}