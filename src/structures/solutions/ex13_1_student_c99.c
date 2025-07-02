/*
 * ファイル名: ex13_1_student_c99.c
 * 演習13-1: 学生情報管理（C99版）
 * 説明: 構造体とポインタを使った学生情報の管理
 * 規格: C99準拠 - bool型、inline関数、指定イニシャライザ、VLA
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NAME_LEN 50

// 学生情報を表す構造体
struct Student {
    int id;
    char name[MAX_NAME_LEN];
    int age;
    double score;
    bool is_active;  // C99: bool型で在籍状態を管理
};

// C99: inline関数で成績評価
static inline char get_grade(double score)
{
    if (score >= 90.0) return 'A';
    if (score >= 80.0) return 'B';
    if (score >= 70.0) return 'C';
    if (score >= 60.0) return 'D';
    return 'F';
}

// C99: inline関数で奨学金対象かチェック
static inline bool is_scholarship_eligible(double score)
{
    return score >= 85.0;
}

// 学生情報を入力する関数（デモ版）
void input_student(struct Student *student)
{
    if (student == NULL) {
        printf("エラー: 無効なポインタです\n");
        return;
    }
    
    printf("学生情報を入力してください:\n");
    
    // デモ用: 固定値を設定
    student->id = 1001;
    student->age = 20;
    student->score = 85.5;
    strcpy(student->name, "田中太郎");
    student->is_active = true;
    
    printf("ID: %d\n", student->id);
    printf("名前: %s\n", student->name);
    printf("年齢: %d\n", student->age);
    printf("成績: %.1f\n", student->score);
}

// 学生情報を表示する関数（拡張版）
void display_student(const struct Student *student)
{
    if (student == NULL) {
        printf("エラー: 無効なポインタです\n");
        return;
    }
    
    printf("\n=== 学生情報 ===\n");
    printf("ID: %d\n", student->id);
    printf("名前: %s\n", student->name);
    printf("年齢: %d歳\n", student->age);
    printf("成績: %.1f点 (評価: %c)\n", student->score, get_grade(student->score));
    printf("在籍状態: %s\n", student->is_active ? "在籍中" : "休学中");
    
    if (is_scholarship_eligible(student->score)) {
        printf("★ 奨学金対象者です\n");
    }
}

// 成績を更新する関数（履歴機能付き）
void update_score_with_history(struct Student *student, double new_score)
{
    if (student == NULL) {
        printf("エラー: 無効なポインタです\n");
        return;
    }
    
    if (new_score < 0.0 || new_score > 100.0) {
        printf("エラー: 成績は0〜100の範囲で入力してください\n");
        return;
    }
    
    double old_score = student->score;
    char old_grade = get_grade(old_score);
    
    student->score = new_score;
    char new_grade = get_grade(new_score);
    
    printf("\n成績を更新しました。\n");
    printf("変更前: %.1f点 (評価: %c) → 変更後: %.1f点 (評価: %c)\n", 
           old_score, old_grade, new_score, new_grade);
    
    // 評価の変化をチェック
    if (old_grade != new_grade) {
        printf("評価が %c から %c に変わりました！\n", old_grade, new_grade);
    }
    
    // 奨学金対象の変化をチェック
    bool was_eligible = is_scholarship_eligible(old_score);
    bool is_eligible = is_scholarship_eligible(new_score);
    
    if (!was_eligible && is_eligible) {
        printf("おめでとうございます！奨学金対象者になりました。\n");
    } else if (was_eligible && !is_eligible) {
        printf("残念ながら奨学金対象から外れました。\n");
    }
}

// C99: VLAを使った学生グループの分析
void analyze_student_group(struct Student students[], int count)
{
    if (count <= 0) return;
    
    // C99: VLAで動的に配列を作成
    double scores[count];
    int grade_count[5] = {0};  // A, B, C, D, F
    
    // データ収集
    for (int i = 0; i < count; i++) {
        scores[i] = students[i].score;
        
        switch (get_grade(students[i].score)) {
            case 'A': grade_count[0]++; break;
            case 'B': grade_count[1]++; break;
            case 'C': grade_count[2]++; break;
            case 'D': grade_count[3]++; break;
            case 'F': grade_count[4]++; break;
        }
    }
    
    // 統計計算
    double total = 0.0;
    double max_score = scores[0];
    double min_score = scores[0];
    
    for (int i = 0; i < count; i++) {
        total += scores[i];
        if (scores[i] > max_score) max_score = scores[i];
        if (scores[i] < min_score) min_score = scores[i];
    }
    
    double average = total / count;
    
    printf("\n=== グループ分析結果 ===\n");
    printf("人数: %d名\n", count);
    printf("平均点: %.1f点\n", average);
    printf("最高点: %.1f点\n", max_score);
    printf("最低点: %.1f点\n", min_score);
    
    printf("\n成績分布:\n");
    const char grades[] = {'A', 'B', 'C', 'D', 'F'};
    for (int i = 0; i < 5; i++) {
        if (grade_count[i] > 0) {
            printf("%c評価: %d名 (%.1f%%)\n", 
                   grades[i], grade_count[i], 
                   (double)grade_count[i] / count * 100);
        }
    }
    
    // 奨学金対象者数
    int scholarship_count = 0;
    for (int i = 0; i < count; i++) {
        if (is_scholarship_eligible(students[i].score)) {
            scholarship_count++;
        }
    }
    printf("\n奨学金対象者: %d名\n", scholarship_count);
}

int main(void)
{
    printf("===== 学生情報管理システム (C99版) =====\n\n");
    
    // C99: 指定イニシャライザで初期化
    struct Student student = {
        .id = 0,
        .name = "",
        .age = 0,
        .score = 0.0,
        .is_active = true
    };
    
    // 学生情報の入力
    input_student(&student);
    
    // 学生情報の表示
    display_student(&student);
    
    // 成績更新のデモ
    printf("\n成績を更新しますか？ (y/n): y\n");
    double new_score = 90.0;  // デモ用: 固定値
    printf("新しい成績を入力してください: %.1f\n", new_score);
    
    // 成績の更新（履歴付き）
    update_score_with_history(&student, new_score);
    
    // 更新後の情報表示
    display_student(&student);
    
    // C99: 複合リテラルを使った学生グループの作成
    printf("\n\n=== 複数学生の管理デモ (C99) ===\n");
    
    struct Student students[] = {
        {.id = 2001, .name = "田中太郎", .age = 20, .score = 85.5, .is_active = true},
        {.id = 2002, .name = "佐藤花子", .age = 21, .score = 92.0, .is_active = true},
        {.id = 2003, .name = "山田次郎", .age = 19, .score = 78.0, .is_active = true},
        {.id = 2004, .name = "鈴木美咲", .age = 20, .score = 88.5, .is_active = false},
        {.id = 2005, .name = "高橋健太", .age = 22, .score = 95.0, .is_active = true}
    };
    
    int student_count = sizeof(students) / sizeof(students[0]);
    
    // 全学生の表示
    printf("\n全学生リスト:\n");
    printf("%-6s %-15s %-6s %-8s %-10s\n", "ID", "名前", "年齢", "成績", "状態");
    printf("------------------------------------------------\n");
    
    for (int i = 0; i < student_count; i++) {
        printf("%-6d %-15s %-6d %-8.1f %-10s\n",
               students[i].id,
               students[i].name,
               students[i].age,
               students[i].score,
               students[i].is_active ? "在籍中" : "休学中");
    }
    
    // グループ分析
    analyze_student_group(students, student_count);
    
    // C99: 条件に合う学生をフィルタリング
    printf("\n\n=== 優秀学生（A評価）一覧 ===\n");
    for (int i = 0; i < student_count; i++) {
        if (get_grade(students[i].score) == 'A' && students[i].is_active) {
            printf("- %s (%.1f点)\n", students[i].name, students[i].score);
        }
    }
    
    return 0;
}

/*
実行例:
===== 学生情報管理システム (C99版) =====

学生情報を入力してください:
ID: 1001
名前: 田中太郎
年齢: 20
成績: 85.5

=== 学生情報 ===
ID: 1001
名前: 田中太郎
年齢: 20歳
成績: 85.5点 (評価: B)
在籍状態: 在籍中
★ 奨学金対象者です

成績を更新しますか？ (y/n): y
新しい成績を入力してください: 90.0

成績を更新しました。
変更前: 85.5点 (評価: B) → 変更後: 90.0点 (評価: A)
評価が B から A に変わりました！

=== 学生情報 ===
ID: 1001
名前: 田中太郎
年齢: 20歳
成績: 90.0点 (評価: A)
在籍状態: 在籍中
★ 奨学金対象者です

=== 複数学生の管理デモ (C99) ===

全学生リスト:
ID     名前            年齢   成績     状態      
------------------------------------------------
2001   田中太郎        20     85.5     在籍中    
2002   佐藤花子        21     92.0     在籍中    
2003   山田次郎        19     78.0     在籍中    
2004   鈴木美咲        20     88.5     休学中    
2005   高橋健太        22     95.0     在籍中    

=== グループ分析結果 ===
人数: 5名
平均点: 87.8点
最高点: 95.0点
最低点: 78.0点

成績分布:
A評価: 2名 (40.0%)
B評価: 2名 (40.0%)
C評価: 1名 (20.0%)

奨学金対象者: 4名

=== 優秀学生（A評価）一覧 ===
- 佐藤花子 (92.0点)
- 高橋健太 (95.0点)
*/
