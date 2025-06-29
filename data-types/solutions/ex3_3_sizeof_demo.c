/*
 * ファイル名: ex3_3_sizeof_demo.c
 * 演習3-3: データ型サイズの確認
 * 説明: sizeof演算子を使って、各データ型のサイズを表示する
 * 規格: C90準拠
 */
#include <stdio.h>
#include <limits.h>
#include <float.h>

int main(void)
{
    printf("=== データ型サイズの確認 ===\n");
    
    /* 基本データ型のサイズ */
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
    printf("  float         : %lu バイト\n", sizeof(float));
    printf("  double        : %lu バイト\n", sizeof(double));
    printf("  long double   : %lu バイト\n", sizeof(long double));
    
    /* 変数のサイズ */
    {
        char c = 'A';
        int num = 42;
        double value = 3.14;
        int array[10];
        
        printf("\n変数のサイズ:\n");
        printf("  char変数 c    : %lu バイト\n", sizeof(c));
        printf("  int変数 num   : %lu バイト\n", sizeof(num));
        printf("  double変数 value: %lu バイト\n", sizeof(value));
        printf("  int配列[10]   : %lu バイト\n", sizeof(array));
        printf("  配列要素数    : %lu 個\n", sizeof(array) / sizeof(array[0]));
    }
    
    /* ポインタのサイズ */
    printf("\nポインタのサイズ:\n");
    printf("  char*         : %lu バイト\n", sizeof(char*));
    printf("  int*          : %lu バイト\n", sizeof(int*));
    printf("  double*       : %lu バイト\n", sizeof(double*));
    printf("  void*         : %lu バイト\n", sizeof(void*));
    
    /* 整数型の値の範囲 */
    printf("\n=== 整数型の値の範囲 ===\n");
    printf("char:\n");
    printf("  最小値: %d\n", CHAR_MIN);
    printf("  最大値: %d\n", CHAR_MAX);
    printf("signed char:\n");
    printf("  最小値: %d\n", SCHAR_MIN);
    printf("  最大値: %d\n", SCHAR_MAX);
    printf("unsigned char:\n");
    printf("  最大値: %u\n", UCHAR_MAX);
    
    printf("short:\n");
    printf("  最小値: %d\n", SHRT_MIN);
    printf("  最大値: %d\n", SHRT_MAX);
    printf("unsigned short:\n");
    printf("  最大値: %u\n", USHRT_MAX);
    
    printf("int:\n");
    printf("  最小値: %d\n", INT_MIN);
    printf("  最大値: %d\n", INT_MAX);
    printf("unsigned int:\n");
    printf("  最大値: %u\n", UINT_MAX);
    
    printf("long:\n");
    printf("  最小値: %ld\n", LONG_MIN);
    printf("  最大値: %ld\n", LONG_MAX);
    printf("unsigned long:\n");
    printf("  最大値: %lu\n", ULONG_MAX);
    
    /* 浮動小数点型の特性 */
    printf("\n=== 浮動小数点型の特性 ===\n");
    printf("float:\n");
    printf("  精度: %d 桁\n", FLT_DIG);
    printf("  最小値: %e\n", FLT_MIN);
    printf("  最大値: %e\n", FLT_MAX);
    printf("  イプシロン: %e\n", FLT_EPSILON);
    
    printf("double:\n");
    printf("  精度: %d 桁\n", DBL_DIG);
    printf("  最小値: %e\n", DBL_MIN);
    printf("  最大値: %e\n", DBL_MAX);
    printf("  イプシロン: %e\n", DBL_EPSILON);
    
    printf("long double:\n");
    printf("  精度: %d 桁\n", LDBL_DIG);
    printf("  最小値: %Le\n", LDBL_MIN);
    printf("  最大値: %Le\n", LDBL_MAX);
    printf("  イプシロン: %Le\n", LDBL_EPSILON);
    
    return 0;
}

/*
学習ポイント:
1. sizeof演算子でデータ型や変数のサイズを確認
2. limits.hヘッダで整数型の範囲定数を取得
3. float.hヘッダで浮動小数点型の特性を取得
4. 配列のサイズと要素数の計算方法
5. ポインタのサイズはシステム依存（32bit: 4バイト、64bit: 8バイト）

重要な定数:
- CHAR_MIN/MAX: char型の範囲
- INT_MIN/MAX: int型の範囲  
- FLT_DIG: float型の有効桁数
- DBL_DIG: double型の有効桁数
- FLT_EPSILON: float型の最小誤差
*/
