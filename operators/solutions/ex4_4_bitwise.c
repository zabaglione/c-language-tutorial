/*
 * ファイル名: ex4_4_bitwise.c
 * 演習4-4: ビット演算
 * 説明: ビット演算子を使って数値の特定ビットを操作
 * 規格: C90準拠
 */

#include <stdio.h>

/* ビットを表示する関数 */
void print_bits(unsigned int value, int bits)
{
    int i;
    printf("0b");
    for (i = bits - 1; i >= 0; i--) {
        printf("%d", (value >> i) & 1);
        if (i % 4 == 0 && i > 0) {
            printf("_");  /* 4ビットごとに区切り */
        }
    }
}

int main(void)
{
    unsigned int num;
    int bit_position;
    unsigned int result;
    unsigned int mask;
    
    printf("===== ビット操作 =====\n");
    printf("整数を入力してください (0-255): ");
    
    if (scanf("%u", &num) != 1 || num > 255) {
        printf("エラー: 0から255の範囲で入力してください\n");
        return 1;
    }
    
    printf("\n元の値: %u = ", num);
    print_bits(num, 8);
    printf("\n\n");
    
    /* ビット単位の基本演算 */
    printf("=== ビット単位の基本演算 ===\n");
    
    /* AND演算 */
    result = num & 0xF0;  /* 上位4ビットを取得 */
    printf("AND演算 (上位4ビット取得):\n");
    printf("%u & 0xF0 = %u = ", num, result);
    print_bits(result, 8);
    printf("\n\n");
    
    /* OR演算 */
    result = num | 0x0F;  /* 下位4ビットを1にセット */
    printf("OR演算 (下位4ビットセット):\n");
    printf("%u | 0x0F = %u = ", num, result);
    print_bits(result, 8);
    printf("\n\n");
    
    /* XOR演算 */
    result = num ^ 0xFF;  /* 全ビット反転 */
    printf("XOR演算 (全ビット反転):\n");
    printf("%u ^ 0xFF = %u = ", num, result);
    print_bits(result, 8);
    printf("\n\n");
    
    /* NOT演算 */
    result = ~num & 0xFF;  /* 8ビットのみ表示 */
    printf("NOT演算 (ビット反転):\n");
    printf("~%u = %u = ", num, result);
    print_bits(result, 8);
    printf("\n\n");
    
    /* ビットシフト演算 */
    printf("=== ビットシフト演算 ===\n");
    
    /* 左シフト */
    result = num << 1;
    printf("左シフト (1ビット):\n");
    printf("%u << 1 = %u = ", num, result);
    print_bits(result, 8);
    printf(" (2倍)\n\n");
    
    /* 右シフト */
    result = num >> 1;
    printf("右シフト (1ビット):\n");
    printf("%u >> 1 = %u = ", num, result);
    print_bits(result, 8);
    printf(" (1/2)\n\n");
    
    /* 特定ビットの操作 */
    printf("=== 特定ビットの操作 ===\n");
    printf("操作するビット位置を入力 (0-7): ");
    
    if (scanf("%d", &bit_position) != 1 || bit_position < 0 || bit_position > 7) {
        printf("エラー: 0から7の範囲で入力してください\n");
        return 1;
    }
    
    /* ビットマスクの作成 */
    mask = 1u << bit_position;
    
    /* ビットのテスト */
    printf("\nビット%dのテスト:\n", bit_position);
    if (num & mask) {
        printf("ビット%dは1です\n", bit_position);
    } else {
        printf("ビット%dは0です\n", bit_position);
    }
    
    /* ビットのセット */
    result = num | mask;
    printf("\nビット%dをセット:\n", bit_position);
    printf("結果: %u = ", result);
    print_bits(result, 8);
    printf("\n");
    
    /* ビットのクリア */
    result = num & ~mask;
    printf("\nビット%dをクリア:\n", bit_position);
    printf("結果: %u = ", result);
    print_bits(result, 8);
    printf("\n");
    
    /* ビットの反転 */
    result = num ^ mask;
    printf("\nビット%dを反転:\n", bit_position);
    printf("結果: %u = ", result);
    print_bits(result, 8);
    printf("\n");
    
    /* 実用的な例 */
    printf("\n=== 実用的なビット操作例 ===\n");
    
    /* 偶数・奇数の判定 */
    printf("偶数・奇数判定: ");
    if (num & 1) {
        printf("%uは奇数です (最下位ビットが1)\n", num);
    } else {
        printf("%uは偶数です (最下位ビットが0)\n", num);
    }
    
    /* 2のべき乗の判定 */
    if (num > 0 && (num & (num - 1)) == 0) {
        printf("%uは2のべき乗です\n", num);
    } else {
        printf("%uは2のべき乗ではありません\n", num);
    }
    
    /* ビットカウント（立っているビットの数） */
    {
        unsigned int temp = num;
        int count = 0;
        while (temp) {
            count += temp & 1;
            temp >>= 1;
        }
        printf("立っているビットの数: %d個\n", count);
    }
    
    /* 上位ビットと下位ビットの交換 */
    {
        unsigned int upper = (num & 0xF0) >> 4;
        unsigned int lower = (num & 0x0F) << 4;
        result = upper | lower;
        printf("\n上位4ビットと下位4ビットの交換:\n");
        printf("元: ");
        print_bits(num, 8);
        printf("\n結果: ");
        print_bits(result, 8);
        printf(" (%u)\n", result);
    }
    
    return 0;
}

/*
実行例:
$ ./ex3_4_bitwise
===== ビット操作 =====
整数を入力してください (0-255): 170

元の値: 170 = 0b1010_1010

=== ビット単位の基本演算 ===
AND演算 (上位4ビット取得):
170 & 0xF0 = 160 = 0b1010_0000

OR演算 (下位4ビットセット):
170 | 0x0F = 175 = 0b1010_1111

XOR演算 (全ビット反転):
170 ^ 0xFF = 85 = 0b0101_0101

NOT演算 (ビット反転):
~170 = 85 = 0b0101_0101

=== ビットシフト演算 ===
左シフト (1ビット):
170 << 1 = 340 = 0b0101_0100 (2倍)

右シフト (1ビット):
170 >> 1 = 85 = 0b0101_0101 (1/2)

=== 特定ビットの操作 ===
操作するビット位置を入力 (0-7): 3

ビット3のテスト:
ビット3は1です

ビット3をセット:
結果: 170 = 0b1010_1010

ビット3をクリア:
結果: 162 = 0b1010_0010

ビット3を反転:
結果: 162 = 0b1010_0010

=== 実用的なビット操作例 ===
偶数・奇数判定: 170は偶数です (最下位ビットが0)
170は2のべき乗ではありません
立っているビットの数: 4個

上位4ビットと下位4ビットの交換:
元: 0b1010_1010
結果: 0b1010_1010 (170)

学習ポイント:
1. ビット演算子（&, |, ^, ~, <<, >>）の使い方
2. ビットマスクによる特定ビットの操作
3. ビット演算を使った効率的な処理
4. 2進数表示によるビット操作の可視化
5. 実用的なビット操作テクニック
*/