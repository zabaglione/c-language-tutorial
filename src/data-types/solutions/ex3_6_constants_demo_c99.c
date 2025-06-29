/*
 * ファイル名: ex3_6_constants_demo_c99.c
 * 演習3-6: 定数の活用
 * 説明: constと#defineを使って定数を定義し、計算に使用する
 * 規格: C99準拠
 */
#include <stdio.h>
#include <math.h>

// プリプロセッサ定数（マクロ定数）
#define PI 3.14159265358979323846
#define MAX_STUDENTS 30
#define PROGRAM_NAME "定数活用デモ"
#define VERSION "1.0"
#define GRAVITY 9.8
#define LIGHT_SPEED 299792458L  // 光速 (m/s)

// 計算マクロ
#define SQUARE(x) ((x) * (x))
#define CIRCLE_AREA(r) (PI * SQUARE(r))
#define FAHRENHEIT_TO_CELSIUS(f) (((f) - 32.0) * 5.0 / 9.0)

// 関数プロトタイプ
void const_variables_demo(void);
void macro_constants_demo(void);
void calculation_demo(void);
void physics_calculations(void);

int main(void)
{
    printf("=== %s v%s ===\n", PROGRAM_NAME, VERSION);
    
    // const変数のデモ
    const_variables_demo();
    
    // マクロ定数のデモ
    macro_constants_demo();
    
    // 定数を使った計算のデモ
    calculation_demo();
    
    // 物理計算のデモ
    physics_calculations();
    
    return 0;
}

// const変数のデモ
void const_variables_demo(void)
{
    printf("\n=== const変数のデモ ===\n");
    
    // const変数の宣言と初期化（使用箇所で宣言）
    const int MAX_RETRY = 3;
    printf("最大リトライ回数: %d\n", MAX_RETRY);
    
    const double TAX_RATE = 0.08;
    printf("税率: %.1f%%\n", TAX_RATE * 100);
    
    const char GRADE_A = 'A';
    printf("最高評価: %c\n", GRADE_A);
    
    const float DISCOUNT = 0.15f;
    printf("割引率: %.1f%%\n", DISCOUNT * 100);
    
    // const変数を使った計算
    int price = 1000;
    double tax = price * TAX_RATE;
    double discount_amount = price * DISCOUNT;
    double final_price = price + tax - discount_amount;
    
    printf("\n商品価格計算:\n");
    printf("  基本価格: %d円\n", price);
    printf("  税額: %.0f円\n", tax);
    printf("  割引額: %.0f円\n", discount_amount);
    printf("  最終価格: %.0f円\n", final_price);
    
    // const変数は変更不可（コンパイルエラーになる）
    // MAX_RETRY = 5;  <- これはコンパイルエラー
}

// マクロ定数のデモ
void macro_constants_demo(void)
{
    printf("\n=== マクロ定数のデモ ===\n");
    printf("円周率: %.15f\n", PI);
    printf("最大学生数: %d人\n", MAX_STUDENTS);
    printf("重力加速度: %.1f m/s²\n", GRAVITY);
    printf("光速: %ld m/s\n", LIGHT_SPEED);
    
    // マクロ関数の使用
    double radius = 5.0;
    double area = CIRCLE_AREA(radius);
    
    printf("\n円の面積計算:\n");
    printf("  半径: %.1f\n", radius);
    printf("  面積: %.2f\n", area);
    printf("  計算式: π × %.1f² = %.15f × %.2f = %.2f\n", 
           radius, PI, SQUARE(radius), area);
    
    // 温度変換マクロ
    double fahrenheit = 100.0;
    double celsius = FAHRENHEIT_TO_CELSIUS(fahrenheit);
    
    printf("\n温度変換:\n");
    printf("  %.1f°F = %.1f°C\n", fahrenheit, celsius);
}

// 定数を使った計算のデモ
void calculation_demo(void)
{
    printf("\n=== 定数を使った計算デモ ===\n");
    
    // ローカルconst変数
    const double SPHERE_VOLUME_COEFF = 4.0 / 3.0;
    
    // 球の体積計算
    double radius = 3.0;
    double volume = SPHERE_VOLUME_COEFF * PI * SQUARE(radius) * radius;
    
    printf("球の体積計算:\n");
    printf("  半径: %.1f\n", radius);
    printf("  体積: %.2f\n", volume);
    printf("  計算式: (4/3) × π × %.1f³ = %.2f\n", radius, volume);
    
    // C99の可変長配列（VLA）と定数
    const int ARRAY_SIZE = 5;
    double numbers[ARRAY_SIZE];  // C99では変数を配列サイズに使用可能
    
    // 配列の初期化
    for (int i = 0; i < ARRAY_SIZE; i++) {
        numbers[i] = (i + 1) * 10.0;
    }
    
    printf("\n配列計算（サイズ: %d）:\n", ARRAY_SIZE);
    
    double sum = 0.0;
    for (int j = 0; j < ARRAY_SIZE; j++) {
        sum += numbers[j];
        printf("  numbers[%d] = %.1f\n", j, numbers[j]);
    }
    
    printf("  合計: %.1f\n", sum);
    printf("  平均: %.1f\n", sum / ARRAY_SIZE);
}

// 物理計算のデモ
void physics_calculations(void)
{
    printf("\n=== 物理計算デモ ===\n");
    
    // 物理定数（const変数として定義）
    const double ELECTRON_CHARGE = 1.602176634e-19;  // クーロン
    const double PLANCK_CONSTANT = 6.62607015e-34;   // ジュール秒
    const double AVOGADRO_NUMBER = 6.02214076e23;    // 個/mol
    
    // 自由落下計算
    double height = 100.0;  // 高さ（メートル）
    double time = sqrt(2.0 * height / GRAVITY);
    double velocity = GRAVITY * time;
    
    printf("自由落下計算:\n");
    printf("  高さ: %.1f m\n", height);
    printf("  落下時間: %.2f 秒\n", time);
    printf("  着地速度: %.2f m/s\n", velocity);
    printf("  重力加速度: %.1f m/s²\n", GRAVITY);
    
    // 円運動計算
    double radius = 10.0;    // 半径（メートル）
    double period = 5.0;     // 周期（秒）
    double circumference = 2.0 * PI * radius;
    double vel = circumference / period;
    double acceleration = SQUARE(vel) / radius;
    
    printf("\n円運動計算:\n");
    printf("  半径: %.1f m\n", radius);
    printf("  周期: %.1f 秒\n", period);
    printf("  円周: %.2f m\n", circumference);
    printf("  速度: %.2f m/s\n", vel);
    printf("  向心加速度: %.2f m/s²\n", acceleration);
    
    // エネルギー計算
    double mass = 1.0;  // 質量（kg）
    double kinetic_energy = 0.5 * mass * SQUARE(velocity);
    double potential_energy = mass * GRAVITY * height;
    
    printf("\nエネルギー計算:\n");
    printf("  質量: %.1f kg\n", mass);
    printf("  運動エネルギー: %.2f J\n", kinetic_energy);
    printf("  位置エネルギー: %.2f J\n", potential_energy);
    printf("  全エネルギー: %.2f J\n", kinetic_energy + potential_energy);
    
    // 物理定数の表示
    printf("\n基本物理定数:\n");
    printf("  電子電荷: %.3e C\n", ELECTRON_CHARGE);
    printf("  プランク定数: %.3e J·s\n", PLANCK_CONSTANT);
    printf("  アボガドロ数: %.3e 個/mol\n", AVOGADRO_NUMBER);
    printf("  光速: %ld m/s\n", LIGHT_SPEED);
    
    // 複合単位の計算
    double energy_photon = PLANCK_CONSTANT * LIGHT_SPEED / 500e-9;  // 500nm光子のエネルギー
    printf("  500nm光子のエネルギー: %.3e J\n", energy_photon);
}

/*
学習ポイント:
1. #defineによるマクロ定数の定義
2. const変数による定数の定義
3. マクロ関数の作成と使用
4. 物理計算での定数の活用
5. C99の可変長配列（VLA）

C99の特徴:
- 変数を使用箇所で宣言可能
- for文内で変数宣言可能 (for (int i = 0; ...))
- 可変長配列（VLA）をサポート
- // 形式のコメント

#define vs const の違い:
- #define: プリプロセッサによる文字列置換、型情報なし
- const: 型付き定数、デバッガで値確認可能、スコープあり

マクロ定数の利点:
- コンパイル時に値が確定
- 条件コンパイルで使用可能
- プリプロセッサレベルでの処理

const変数の利点:
- 型安全性
- デバッガでの確認が容易
- スコープによる制御が可能
- C99では配列サイズとしても使用可能

実用的な応用:
- 物理定数の正確な定義
- 科学計算での精度保持
- 単位変換の自動化
*/
