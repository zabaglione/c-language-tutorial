/*
 * ファイル名: ex11_1_student.c
 * 演習11-1: 学生情報管理
 * 説明: 構造体とポインタを使った学生情報の管理
 * 規格: C90準拠
 */

#include <stdio.h>
#include <string.h>

#define MAX_NAME_LEN 50

/* 学生情報を表す構造体 */
struct Student {
    int id;
    char name[MAX_NAME_LEN];
    int age;
    double score;
};

/* 学生情報を入力する関数（デモ版） */
void input_student(struct Student *student)
{
    if (student == NULL) {
        printf("エラー: 無効なポインタです\n");
        return;
    }
    
    printf("学生情報を入力してください:\n");
    
    /* デモ用: 固定値を設定 */
    student->id = 1001;
    student->age = 20;
    student->score = 85.5;
    strcpy(student->name, "田中太郎");
    
    printf("ID: %d\n", student->id);
    printf("名前: %s\n", student->name);
    printf("年齢: %d\n", student->age);
    printf("成績: %.1f\n", student->score);
}

/* 学生情報を表示する関数 */
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
    printf("成績: %.1f点\n", student->score);
}

/* 成績を更新する関数 */
void update_score(struct Student *student, double new_score)
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
    student->score = new_score;
    
    printf("\n成績を更新しました。\n");
    printf("変更前: %.1f点 → 変更後: %.1f点\n", old_score, new_score);
}

/* 成績の評価を返す関数 */
char get_grade(double score)
{
    if (score >= 90.0) return 'A';
    if (score >= 80.0) return 'B';
    if (score >= 70.0) return 'C';
    if (score >= 60.0) return 'D';
    return 'F';
}

/* 詳細情報を表示する関数 */
void display_detailed_info(const struct Student *student)
{
    if (student == NULL) {
        return;
    }
    
    printf("\n=== 詳細な学生情報 ===\n");
    printf("ID: %d\n", student->id);
    printf("名前: %s\n", student->name);
    printf("年齢: %d歳\n", student->age);
    printf("成績: %.1f点 (評価: %c)\n", student->score, get_grade(student->score));
    
    /* 成績に応じたコメント */
    if (student->score >= 90.0) {
        printf("コメント: 大変優秀です！\n");
    } else if (student->score >= 80.0) {
        printf("コメント: 良い成績です。\n");
    } else if (student->score >= 70.0) {
        printf("コメント: まずまずの成績です。\n");
    } else if (student->score >= 60.0) {
        printf("コメント: もう少し頑張りましょう。\n");
    } else {
        printf("コメント: 努力が必要です。\n");
    }
}

int main(void)
{
    struct Student student;
    double new_score = 90.0;  /* デモ用: 固定値 */
    
    printf("===== 学生情報管理システム =====\n\n");
    
    /* 学生情報の入力 */
    input_student(&student);
    
    /* 学生情報の表示 */
    display_student(&student);
    
    /* 成績更新のデモ */
    printf("\n成績を更新しますか？ (y/n): y\n");
    printf("新しい成績を入力してください: %.1f\n", new_score);
    
    /* 成績の更新 */
    update_score(&student, new_score);
    
    /* 更新後の情報表示 */
    printf("\n=== 更新後の学生情報 ===\n");
    printf("ID: %d\n", student.id);
    printf("名前: %s\n", student.name);
    printf("年齢: %d歳\n", student.age);
    printf("成績: %.1f点\n", student.score);
    
    /* 詳細情報の表示 */
    display_detailed_info(&student);
    
    /* 追加機能：複数の学生の比較 */
    printf("\n\n=== 複数学生の管理デモ ===\n");
    
    struct Student students[3] = {
        {2001, "田中太郎", 20, 85.5},
        {2002, "佐藤花子", 21, 92.0},
        {2003, "山田次郎", 19, 78.0}
    };
    
    int i;
    double total_score = 0.0;
    struct Student *top_student = &students[0];
    
    printf("\n全学生の一覧:\n");
    for (i = 0; i < 3; i++) {
        printf("%d. %s (%.1f点)\n", 
               students[i].id, students[i].name, students[i].score);
        total_score += students[i].score;
        
        /* 最高得点の学生を記録 */
        if (students[i].score > top_student->score) {
            top_student = &students[i];
        }
    }
    
    printf("\n統計情報:\n");
    printf("平均点: %.1f点\n", total_score / 3);
    printf("最高得点: %s (%.1f点)\n", top_student->name, top_student->score);
    
    return 0;
}

/*
実行例:
===== 学生情報管理システム =====

学生情報を入力してください:
ID: 1001
名前: 田中太郎
年齢: 20
成績: 85.5

=== 学生情報 ===
ID: 1001
名前: 田中太郎
年齢: 20歳
成績: 85.5点

成績を更新しますか？ (y/n): y
新しい成績を入力してください: 90.0

成績を更新しました。
変更前: 85.5点 → 変更後: 90.0点

=== 更新後の学生情報 ===
ID: 1001
名前: 田中太郎
年齢: 20歳
成績: 90.0点

=== 詳細な学生情報 ===
ID: 1001
名前: 田中太郎
年齢: 20歳
成績: 90.0点 (評価: A)
コメント: 大変優秀です！

=== 複数学生の管理デモ ===

全学生の一覧:
2001. 田中太郎 (85.5点)
2002. 佐藤花子 (92.0点)
2003. 山田次郎 (78.0点)

統計情報:
平均点: 85.2点
最高得点: 佐藤花子 (92.0点)
*/
