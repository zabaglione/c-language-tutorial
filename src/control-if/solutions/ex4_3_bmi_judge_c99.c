/*
 * ファイル名: ex4_3_bmi_judge_c99.c
 * 演習4-3: BMI判定プログラム
 * 説明: 身長と体重からBMIを計算し体型判定を行う
 * 規格: C99準拠
 */
#include <stdio.h>

int main(void)
{
    printf("=== BMI判定プログラム ===\n");
    
    // 身長の入力（センチメートル）
    printf("身長を入力してください（cm）: ");
    double height_cm;
    scanf("%lf", &height_cm);
    
    // 体重の入力
    printf("体重を入力してください（kg）: ");
    double weight;
    scanf("%lf", &weight);
    
    // 入力値の検証
    if (height_cm <= 0 || height_cm > 300) {
        printf("エラー: 身長は1cm〜300cmの範囲で入力してください。\n");
        return 1;
    }
    
    if (weight <= 0 || weight > 500) {
        printf("エラー: 体重は1kg〜500kgの範囲で入力してください。\n");
        return 1;
    }
    
    // 身長をメートルに変換
    double height_m = height_cm / 100.0;
    
    // BMI計算
    double bmi = weight / (height_m * height_m);
    
    // BMI判定
    char *category;
    char *advice;
    
    if (bmi < 18.5) {
        category = "低体重";
        advice = "栄養バランスの良い食事を心がけ、適度な運動で健康的に体重を増やしましょう。";
    } else if (bmi >= 18.5 && bmi < 25.0) {
        category = "標準体重";
        advice = "理想的な体重です。現在の生活習慣を維持しましょう。";
    } else if (bmi >= 25.0 && bmi < 30.0) {
        category = "肥満度1";
        advice = "軽度の肥満です。食事制限と有酸素運動を始めることをお勧めします。";
    } else {
        category = "肥満度2";
        advice = "高度な肥満です。医師に相談し、本格的な減量プログラムを検討してください。";
    }
    
    // 結果の表示
    printf("\n=== BMI計算結果 ===\n");
    printf("身長: %.1f cm (%.2f m)\n", height_cm, height_m);
    printf("体重: %.1f kg\n", weight);
    printf("BMI: %.2f\n", bmi);
    printf("判定: %s\n", category);
    printf("\nアドバイス: %s\n", advice);
    
    // 追加の健康情報
    printf("\n=== 健康情報 ===\n");
    
    if (bmi < 18.5) {
        printf("・BMI 18.5未満は痩せすぎの可能性があります\n");
        printf("・免疫力低下や骨密度減少のリスクがあります\n");
    } else if (bmi >= 18.5 && bmi < 25.0) {
        printf("・BMI 18.5-24.9は標準的な範囲です\n");
        printf("・生活習慣病のリスクが最も低い範囲です\n");
    } else if (bmi >= 25.0 && bmi < 30.0) {
        printf("・BMI 25.0-29.9は軽度肥満の範囲です\n");
        printf("・糖尿病や高血圧のリスクが上昇します\n");
    } else {
        printf("・BMI 30.0以上は高度肥満の範囲です\n");
        printf("・心血管疾患のリスクが大幅に増加します\n");
    }
    
    // 理想体重の計算と表示
    if (bmi < 18.5 || bmi >= 25.0) {
        double ideal_weight_min = 18.5 * (height_m * height_m);
        double ideal_weight_max = 24.9 * (height_m * height_m);
        
        printf("\n=== 理想体重の目安 ===\n");
        printf("あなたの理想体重: %.1f kg 〜 %.1f kg\n", 
               ideal_weight_min, ideal_weight_max);
        
        if (weight < ideal_weight_min) {
            printf("目標: %.1f kg の増量\n", ideal_weight_min - weight);
        } else if (weight > ideal_weight_max) {
            printf("目標: %.1f kg の減量\n", weight - ideal_weight_max);
        }
    }
    
    printf("\n※この判定は一般的な目安です。詳しくは医師にご相談ください。\n");
    
    return 0;
}

/*
学習ポイント:
1. 浮動小数点数を使った計算
2. if-else if文による範囲判定
3. 単位変換（cm→m）
4. 論理演算子による範囲指定
5. 計算結果を使った追加処理

実装のポイント:
- C99準拠のため、変数を使用箇所の近くで宣言
- BMI計算式の正確な実装
- 境界値（18.5, 25.0, 30.0）の適切な処理
- ユーザーフレンドリーな結果表示
- 入力値の妥当性チェック
*/