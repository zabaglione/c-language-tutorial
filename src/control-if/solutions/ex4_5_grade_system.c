/*
 * ファイル名: ex4_5_grade_system.c
 * 演習4-5: 成績評価システム
 * 説明: 3科目の点数から平均点を計算し総合評価を行う
 * 規格: C90準拠
 */
#include <stdio.h>

int main(void)
{
    /* 変数の宣言（C90では先頭で宣言） */
    int japanese, math, english;
    int total;
    double average;
    char grade;
    char *evaluation;
    int all_passed;
    char *result;
    
    printf("=== 成績評価システム ===\n");
    
    /* 各科目の点数入力 */
    printf("国語の点数を入力してください (0-100): ");
    scanf("%d", &japanese);
    
    printf("数学の点数を入力してください (0-100): ");
    scanf("%d", &math);
    
    printf("英語の点数を入力してください (0-100): ");
    scanf("%d", &english);
    
    /* 入力値の検証 */
    if (japanese < 0 || japanese > 100) {
        printf("エラー: 国語の点数は0-100の範囲で入力してください。\n");
        return 1;
    }
    
    if (math < 0 || math > 100) {
        printf("エラー: 数学の点数は0-100の範囲で入力してください。\n");
        return 1;
    }
    
    if (english < 0 || english > 100) {
        printf("エラー: 英語の点数は0-100の範囲で入力してください。\n");
        return 1;
    }
    
    /* 合計点と平均点の計算 */
    total = japanese + math + english;
    average = (double)total / 3.0;  /* 整数演算を避けるため型キャスト */
    
    /* 平均点による評価 */
    if (average >= 90) {
        grade = 'A';
        evaluation = "優秀";
    } else if (average >= 80) {
        grade = 'B';
        evaluation = "良好";
    } else if (average >= 70) {
        grade = 'C';
        evaluation = "普通";
    } else if (average >= 60) {
        grade = 'D';
        evaluation = "可";
    } else {
        grade = 'F';
        evaluation = "不可";
    }
    
    /* 全科目60点以上の確認 */
    all_passed = (japanese >= 60 && math >= 60 && english >= 60) ? 1 : 0;
    
    /* 条件演算子を使った簡潔な表示 */
    result = all_passed ? "合格" : "不合格";
    
    /* 結果の表示 */
    printf("\n=== 成績評価結果 ===\n");
    printf("国語: %d点\n", japanese);
    printf("数学: %d点\n", math);
    printf("英語: %d点\n", english);
    printf("--------------------\n");
    printf("合計点: %d点\n", total);
    printf("平均点: %.2f点\n", average);
    printf("評価: %c (%s)\n", grade, evaluation);
    printf("判定: %s\n", result);
    
    /* 詳細な分析 */
    printf("\n=== 詳細分析 ===\n");
    
    /* 各科目の個別評価 */
    printf("科目別評価:\n");
    printf("・国語: %s\n", (japanese >= 60) ? "合格" : "不合格");
    printf("・数学: %s\n", (math >= 60) ? "合格" : "不合格");
    printf("・英語: %s\n", (english >= 60) ? "合格" : "不合格");
    
    /* 最高点と最低点の科目 */
    if (japanese >= math && japanese >= english) {
        printf("最高得点科目: 国語 (%d点)\n", japanese);
    } else if (math >= japanese && math >= english) {
        printf("最高得点科目: 数学 (%d点)\n", math);
    } else {
        printf("最高得点科目: 英語 (%d点)\n", english);
    }
    
    if (japanese <= math && japanese <= english) {
        printf("最低得点科目: 国語 (%d点)\n", japanese);
    } else if (math <= japanese && math <= english) {
        printf("最低得点科目: 数学 (%d点)\n", math);
    } else {
        printf("最低得点科目: 英語 (%d点)\n", english);
    }
    
    /* 改善アドバイス */
    printf("\n=== 改善アドバイス ===\n");
    
    if (all_passed) {
        printf("全科目合格おめでとうございます！\n");
        if (average >= 90) {
            printf("優秀な成績です。この調子で頑張ってください。\n");
        } else if (average >= 80) {
            printf("良い成績です。さらなる向上を目指しましょう。\n");
        } else {
            printf("全科目クリアしました。より高い点数を目指しましょう。\n");
        }
    } else {
        printf("不合格科目があります。以下の科目の復習をしましょう:\n");
        if (japanese < 60) {
            printf("・国語: %d点 (不足 %d点)\n", japanese, 60 - japanese);
        }
        if (math < 60) {
            printf("・数学: %d点 (不足 %d点)\n", math, 60 - math);
        }
        if (english < 60) {
            printf("・英語: %d点 (不足 %d点)\n", english, 60 - english);
        }
    }
    
    /* 次回の目標設定 */
    printf("\n=== 次回の目標 ===\n");
    if (grade == 'A') {
        printf("目標: A評価の維持\n");
    } else if (grade == 'B') {
        printf("目標: A評価（平均90点以上）\n");
    } else if (grade == 'C') {
        printf("目標: B評価（平均80点以上）\n");
    } else if (grade == 'D') {
        printf("目標: C評価（平均70点以上）\n");
    } else {
        printf("目標: まずは全科目60点以上\n");
    }
    
    return 0;
}

/*
学習ポイント:
1. 複数の変数を使った計算処理
2. if-else if文による段階的評価
3. 条件演算子（?:）の実用的な使用
4. 論理演算子（&&）による複合条件
5. 型キャスト（int→double）による精密な計算

実装のポイント:
- C90準拠のため、すべての変数を関数先頭で宣言
- 整数演算を避けるための型キャスト
- 条件演算子による簡潔な条件分岐
- 複数条件の組み合わせによる判定
- ユーザーフレンドリーな結果表示
*/