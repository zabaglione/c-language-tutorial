/*
 * ファイル名: ex3_3_sizeof_demo_c99.c
 * 演習3-3: データ型サイズの確認
 * 説明: sizeof演算子を使って、各データ型のサイズを表示する
 * 規格: C99準拠
 */
#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <stdint.h>  // C99の固定幅整数型

int main(void)
{
    printf("=== データ型サイズの確認 ===\n");
    
    // 基本データ型のサイズ
    printf("基本データ型のサイズ:\n");
    printf("  char          : %lu バイト\n", sizeof(char));
    printf("  signed char   : %lu バイト\n", sizeof(signed char));
    printf("  unsigned char : %lu バイト\n", sizeof(unsigned char));
    printf("  short         : %lu バイト\n", sizeof(short));
    printf("  unsigned short: %lu バイト\n", sizeof(unsigned short));
    printf("  int           : %lu バイト\n", sizeof(int));
    printf("  unsigned int  : %lu バイト\n", sizeof(unsigned int));
    printf("  long          : %lu バイト\n", sizeof(long));
    printf("  unsigned long : %lu バイト\n", sizeof(unsigned long));
    printf("  long long     : %lu バイト\n", sizeof(long long));     // C99
    printf("  unsigned long long: %lu バイト\n", sizeof(unsigned long long)); // C99
    printf("  float         : %lu バイト\n", sizeof(float));
    printf("  double        : %lu バイト\n", sizeof(double));
    printf("  long double   : %lu バイト\n", sizeof(long double));
    
    // C99固定幅整数型
    printf("\nC99固定幅整数型のサイズ:\n");
    printf("  int8_t        : %lu バイト\n", sizeof(int8_t));
    printf("  int16_t       : %lu バイト\n", sizeof(int16_t));
    printf("  int32_t       : %lu バイト\n", sizeof(int32_t));
    printf("  int64_t       : %lu バイト\n", sizeof(int64_t));
    printf("  uint8_t       : %lu バイト\n", sizeof(uint8_t));
    printf("  uint16_t      : %lu バイト\n", sizeof(uint16_t));
    printf("  uint32_t      : %lu バイト\n", sizeof(uint32_t));
    printf("  uint64_t      : %lu バイト\n", sizeof(uint64_t));
    
    // 変数のサイズ（使用箇所で宣言）
    char c = 'A';
    printf("\n変数のサイズ:\n");
    printf("  char変数 c    : %lu バイト\n", sizeof(c));
    
    int num = 42;
    printf("  int変数 num   : %lu バイト\n", sizeof(num));
    
    double value = 3.14;
    printf("  double変数 value: %lu バイト\n", sizeof(value));
    
    int array[10];
    printf("  int配列[10]   : %lu バイト\n", sizeof(array));
    printf("  配列要素数    : %lu 個\n", sizeof(array) / sizeof(array[0]));
    
    // ポインタのサイズ
    printf("\nポインタのサイズ:\n");
    printf("  char*         : %lu バイト\n", sizeof(char*));
    printf("  int*          : %lu バイト\n", sizeof(int*));
    printf("  double*       : %lu バイト\n", sizeof(double*));
    printf("  void*         : %lu バイト\n", sizeof(void*));
    
    // 整数型の値の範囲
    printf("\n=== 整数型の値の範囲 ===\n");
    printf("char: %d ～ %d\n", CHAR_MIN, CHAR_MAX);
    printf("signed char: %d ～ %d\n", SCHAR_MIN, SCHAR_MAX);
    printf("unsigned char: 0 ～ %u\n", UCHAR_MAX);
    printf("short: %d ～ %d\n", SHRT_MIN, SHRT_MAX);
    printf("unsigned short: 0 ～ %u\n", USHRT_MAX);
    printf("int: %d ～ %d\n", INT_MIN, INT_MAX);
    printf("unsigned int: 0 ～ %u\n", UINT_MAX);
    printf("long: %ld ～ %ld\n", LONG_MIN, LONG_MAX);
    printf("unsigned long: 0 ～ %lu\n", ULONG_MAX);
    printf("long long: %lld ～ %lld\n", LLONG_MIN, LLONG_MAX);        // C99
    printf("unsigned long long: 0 ～ %llu\n", ULLONG_MAX);             // C99
    
    // C99固定幅整数型の範囲
    printf("\nC99固定幅整数型の範囲:\n");
    printf("int8_t: %d ～ %d\n", INT8_MIN, INT8_MAX);
    printf("uint8_t: 0 ～ %u\n", UINT8_MAX);
    printf("int16_t: %d ～ %d\n", INT16_MIN, INT16_MAX);
    printf("uint16_t: 0 ～ %u\n", UINT16_MAX);
    printf("int32_t: %d ～ %d\n", INT32_MIN, INT32_MAX);
    printf("uint32_t: 0 ～ %u\n", UINT32_MAX);
    printf("int64_t: %lld ～ %lld\n", INT64_MIN, INT64_MAX);
    printf("uint64_t: 0 ～ %llu\n", UINT64_MAX);
    
    // 浮動小数点型の特性
    printf("\n=== 浮動小数点型の特性 ===\n");
    printf("float: 精度%d桁, 範囲 %e ～ %e\n", FLT_DIG, FLT_MIN, FLT_MAX);
    printf("double: 精度%d桁, 範囲 %e ～ %e\n", DBL_DIG, DBL_MIN, DBL_MAX);
    printf("long double: 精度%d桁, 範囲 %Le ～ %Le\n", LDBL_DIG, LDBL_MIN, LDBL_MAX);
    
    return 0;
}

/*
学習ポイント:
1. sizeof演算子でデータ型や変数のサイズを確認
2. limits.hヘッダで整数型の範囲定数を取得
3. float.hヘッダで浮動小数点型の特性を取得
4. C99の新機能: long long型、固定幅整数型（stdint.h）
5. 配列のサイズと要素数の計算方法

C99の新機能:
- long long型（64ビット整数保証）
- stdint.hの固定幅整数型（int8_t, int16_t, int32_t, int64_t等）
- 変数を使用箇所で宣言可能
- // 形式のコメント

固定幅整数型の利点:
- プラットフォーム間でサイズが保証される
- ビット数が明確で可読性が高い
- 組み込み開発やプロトコル実装で重要
*/
