/*
 * ファイル名: ex3_1_variable_declaration_c99.c
 * 演習3-1: 変数宣言と初期化
 * 説明: さまざまなデータ型の変数を宣言し、初期化して出力する
 * 規格: C99準拠
 */
#include <stdio.h>

int main(void)
{
    printf("=== 変数宣言と初期化の例 ===\n");
    
    // 整数型の変数宣言と初期化（使用箇所で宣言）
    char initial = 'C';
    printf("文字型 (char)      : %c\n", initial);
    
    short year = 2024;
    printf("短整数型 (short)   : %d\n", year);
    
    int score = 95;
    printf("整数型 (int)       : %d\n", score);
    
    long population = 125000000L;
    printf("長整数型 (long)    : %ld\n", population);
    
    unsigned int count = 42U;
    printf("符号なし整数 (unsigned): %u\n", count);
    
    // 浮動小数点型変数
    float temperature = 23.5f;
    printf("単精度浮動小数点 (float) : %.2f\n", temperature);
    
    double precision_value = 3.141592653589793;
    printf("倍精度浮動小数点 (double): %.15f\n", precision_value);
    
    // 定数の定義
    const int MAX_STUDENTS = 30;
    const double GRAVITY = 9.8;
    
    printf("定数 MAX_STUDENTS : %d\n", MAX_STUDENTS);
    printf("定数 GRAVITY      : %.1f\n", GRAVITY);
    
    // データ型のサイズ情報
    printf("\n=== データ型のサイズ ===\n");
    printf("char     : %lu バイト\n", sizeof(char));
    printf("short    : %lu バイト\n", sizeof(short));
    printf("int      : %lu バイト\n", sizeof(int));
    printf("long     : %lu バイト\n", sizeof(long));
    printf("unsigned : %lu バイト\n", sizeof(unsigned int));
    printf("float    : %lu バイト\n", sizeof(float));
    printf("double   : %lu バイト\n", sizeof(double));
    
    // 実際の値の範囲例
    printf("\n=== 値の範囲例 ===\n");
    printf("char 最大値の例: %d\n", 127);
    printf("char 最小値の例: %d\n", -128);
    printf("unsigned int 最大値の例: %u\n", 4294967295U);
    
    return 0;
}

/*
学習ポイント:
1. C99では変数を使用箇所で宣言可能
2. // 形式のコメントが使用可能
3. 各データ型の適切な使い分け
4. 定数の効果的な活用
5. sizeof演算子による型情報の取得

C99の特徴:
- 変数宣言の位置の自由度向上
- より読みやすいコード構造
- // コメントの標準サポート
*/
