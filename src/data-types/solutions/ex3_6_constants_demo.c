/*
 * ファイル名: ex3_6_constants_demo.c
 * 演習3-6: 定数の活用
 * 説明: constと#defineを使って定数を定義し、計算に使用する
 * 規格: C90準拠
 */
#include <stdio.h>
#include <math.h>

/* プリプロセッサ定数（マクロ定数） */
#define PI 3.14159265358979323846
#define MAX_STUDENTS 30
#define PROGRAM_NAME "定数活用デモ"
#define VERSION "1.0"
#define GRAVITY 9.8
#define LIGHT_SPEED 299792458L  /* 光速 (m/s) */

/* 計算マクロ */
#define SQUARE(x) ((x) * (x))
#define CIRCLE_AREA(r) (PI * SQUARE(r))
#define FAHRENHEIT_TO_CELSIUS(f) (((f) - 32.0) * 5.0 / 9.0)

/* 関数プロトタイプ */
void const_variables_demo(void);
void macro_constants_demo(void);
void calculation_demo(void);
void physics_calculations(void);

int main(void)
{
    printf("=== %s v%s ===\n", PROGRAM_NAME, VERSION);
    
    /* const変数のデモ */
    const_variables_demo();
    
    /* マクロ定数のデモ */
    macro_constants_demo();
    
    /* 定数を使った計算のデモ */
    calculation_demo();
    
    /* 物理計算のデモ */
    physics_calculations();
    
    return 0;
}

/* const変数のデモ */
void const_variables_demo(void)
{
    /* const変数の宣言と初期化 */
    const int MAX_RETRY = 3;
    const double TAX_RATE = 0.08;
    const char GRADE_A = 'A';
    const float DISCOUNT = 0.15f;
    
    printf("\n=== const変数のデモ ===\n");
    printf("最大リトライ回数: %d\n", MAX_RETRY);
    printf("税率: %.1f%%\n", TAX_RATE * 100);
    printf("最高評価: %c\n", GRADE_A);
    printf("割引率: %.1f%%\n", DISCOUNT * 100);
    
    /* const変数を使った計算 */
    {
        int price = 1000;
        double tax = price * TAX_RATE;
        double discount_amount = price * DISCOUNT;
        double final_price = price + tax - discount_amount;
        
        printf("\n商品価格計算:\n");
        printf("  基本価格: %d円\n", price);
        printf("  税額: %.0f円\n", tax);
        printf("  割引額: %.0f円\n", discount_amount);
        printf("  最終価格: %.0f円\n", final_price);
    }
    
    /* const変数は変更不可（コンパイルエラーになる） */
    /* MAX_RETRY = 5;  <- これはコンパイルエラー */
}

/* マクロ定数のデモ */
void macro_constants_demo(void)
{
    printf("\n=== マクロ定数のデモ ===\n");
    printf("円周率: %.15f\n", PI);
    printf("最大学生数: %d人\n", MAX_STUDENTS);
    printf("重力加速度: %.1f m/s²\n", GRAVITY);
    printf("光速: %ld m/s\n", LIGHT_SPEED);
    
    /* マクロ関数の使用 */
    {
        double radius = 5.0;
        double area = CIRCLE_AREA(radius);
        
        printf("\n円の面積計算:\n");
        printf("  半径: %.1f\n", radius);
        printf("  面積: %.2f\n", area);
        printf("  計算式: π × %.1f² = %.15f × %.2f = %.2f\n", 
               radius, PI, SQUARE(radius), area);
    }
    
    /* 温度変換マクロ */
    {
        double fahrenheit = 100.0;
        double celsius = FAHRENHEIT_TO_CELSIUS(fahrenheit);
        
        printf("\n温度変換:\n");
        printf("  %.1f°F = %.1f°C\n", fahrenheit, celsius);
    }
}

/* 定数を使った計算のデモ */
void calculation_demo(void)
{
    /* ローカルconst変数 */
    const double SPHERE_VOLUME_COEFF = 4.0 / 3.0;
    const int ARRAY_SIZE = 5;
    
    printf("\n=== 定数を使った計算デモ ===\n");
    
    /* 球の体積計算 */
    {
        double radius = 3.0;
        double volume = SPHERE_VOLUME_COEFF * PI * SQUARE(radius) * radius;
        
        printf("球の体積計算:\n");
        printf("  半径: %.1f\n", radius);
        printf("  体積: %.2f\n", volume);
        printf("  計算式: (4/3) × π × %.1f³ = %.2f\n", radius, volume);
    }
    
    /* 配列サイズ定数の使用 */
    {
        const int numbers[5] = {10, 20, 30, 40, 50};  /* C90では配列サイズは定数が必要 */
        int sum = 0;
        int i;
        
        printf("\n配列計算（サイズ: %d）:\n", ARRAY_SIZE);
        
        for (i = 0; i < ARRAY_SIZE; i++) {
            sum += numbers[i];
            printf("  numbers[%d] = %d\n", i, numbers[i]);
        }
        
        printf("  合計: %d\n", sum);
        printf("  平均: %.1f\n", (double)sum / ARRAY_SIZE);
    }
}

/* 物理計算のデモ */
void physics_calculations(void)
{
    /* 物理定数（const変数として定義） */
    const double ELECTRON_CHARGE = 1.602176634e-19;  /* クーロン */
    const double PLANCK_CONSTANT = 6.62607015e-34;   /* ジュール秒 */
    const double AVOGADRO_NUMBER = 6.02214076e23;    /* 個/mol */
    
    printf("\n=== 物理計算デモ ===\n");
    
    /* 自由落下計算 */
    {
        double height = 100.0;  /* 高さ（メートル） */
        double time = sqrt(2.0 * height / GRAVITY);
        double velocity = GRAVITY * time;
        
        printf("自由落下計算:\n");
        printf("  高さ: %.1f m\n", height);
        printf("  落下時間: %.2f 秒\n", time);
        printf("  着地速度: %.2f m/s\n", velocity);
        printf("  重力加速度: %.1f m/s²\n", GRAVITY);
    }
    
    /* 円運動計算 */
    {
        double radius = 10.0;    /* 半径（メートル） */
        double period = 5.0;     /* 周期（秒） */
        double circumference = 2.0 * PI * radius;
        double velocity = circumference / period;
        double acceleration = SQUARE(velocity) / radius;
        
        printf("\n円運動計算:\n");
        printf("  半径: %.1f m\n", radius);
        printf("  周期: %.1f 秒\n", period);
        printf("  円周: %.2f m\n", circumference);
        printf("  速度: %.2f m/s\n", velocity);
        printf("  向心加速度: %.2f m/s²\n", acceleration);
    }
    
    /* 物理定数の表示 */
    printf("\n物理定数:\n");
    printf("  電子電荷: %.3e C\n", ELECTRON_CHARGE);
    printf("  プランク定数: %.3e J·s\n", PLANCK_CONSTANT);
    printf("  アボガドロ数: %.3e 個/mol\n", AVOGADRO_NUMBER);
    printf("  光速: %ld m/s\n", LIGHT_SPEED);
}

/*
学習ポイント:
1. #defineによるマクロ定数の定義
2. const変数による定数の定義
3. マクロ関数の作成と使用
4. 物理計算での定数の活用
5. 定数の命名規則（大文字、アンダースコア）

#define vs const の違い:
- #define: プリプロセッサによる文字列置換、型情報なし
- const: 型付き定数、デバッガで値確認可能、スコープあり

マクロ定数の利点:
- コンパイル時に値が確定
- 配列サイズとして使用可能（C90）
- 条件コンパイルで使用可能

const変数の利点:
- 型安全性
- デバッガでの確認が容易
- スコープによる制御が可能

注意点:
- マクロ関数は引数を括弧で囲む
- マクロは副作用に注意（SQUARE(++x)など）
- 物理定数は国際単位系の値を使用
*/
