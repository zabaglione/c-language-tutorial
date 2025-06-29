/*
 * 演習 6-2: 成績管理システム（C90準拠版）
 * 
 * 5人の学生、4科目（国語、数学、英語、理科）の成績を管理し、
 * 各種統計を計算するプログラム
 */
#include <stdio.h>

#define NUM_STUDENTS 5
#define NUM_SUBJECTS 4

/* 学生名と科目名 */
char students[NUM_STUDENTS][20] = {
    "田中太郎", "佐藤花子", "鈴木一郎", "高橋美咲", "伊藤健太"
};

char subjects[NUM_SUBJECTS][10] = {
    "国語", "数学", "英語", "理科"
};

/* 成績表を表示する関数 */
void display_grade_table(int grades[][NUM_SUBJECTS])
{
    int i, j;
    
    printf("\n=== 成績表 ===\n");
    printf("%-12s", "学生名");
    for (j = 0; j < NUM_SUBJECTS; j++) {
        printf("%-8s", subjects[j]);
    }
    printf("%-8s%-8s\n", "合計", "平均");
    
    printf("------------------------------------------------\n");
    
    for (i = 0; i < NUM_STUDENTS; i++) {
        int total = 0;
        printf("%-12s", students[i]);
        
        for (j = 0; j < NUM_SUBJECTS; j++) {
            printf("%-8d", grades[i][j]);
            total += grades[i][j];
        }
        
        printf("%-8d%-8.1f\n", total, (double)total / NUM_SUBJECTS);
    }
}

/* 各科目の平均を計算・表示する関数 */
void display_subject_averages(int grades[][NUM_SUBJECTS])
{
    int i, j;
    int total;
    
    printf("\n=== 科目別平均点 ===\n");
    for (j = 0; j < NUM_SUBJECTS; j++) {
        total = 0;
        for (i = 0; i < NUM_STUDENTS; i++) {
            total += grades[i][j];
        }
        printf("%s: %.1f点\n", subjects[j], (double)total / NUM_STUDENTS);
    }
}

/* 最高得点の学生と科目を見つける関数 */
void find_highest_score(int grades[][NUM_SUBJECTS])
{
    int i, j;
    int max_score = grades[0][0];
    int max_student = 0;
    int max_subject = 0;
    
    for (i = 0; i < NUM_STUDENTS; i++) {
        for (j = 0; j < NUM_SUBJECTS; j++) {
            if (grades[i][j] > max_score) {
                max_score = grades[i][j];
                max_student = i;
                max_subject = j;
            }
        }
    }
    
    printf("\n=== 最高得点 ===\n");
    printf("学生: %s\n", students[max_student]);
    printf("科目: %s\n", subjects[max_subject]);
    printf("得点: %d点\n", max_score);
}

/* 学生ランキングを表示する関数 */
void display_student_ranking(int grades[][NUM_SUBJECTS])
{
    int i, j, k;
    int totals[NUM_STUDENTS];
    int ranking[NUM_STUDENTS];
    
    /* 各学生の合計点を計算 */
    for (i = 0; i < NUM_STUDENTS; i++) {
        totals[i] = 0;
        for (j = 0; j < NUM_SUBJECTS; j++) {
            totals[i] += grades[i][j];
        }
        ranking[i] = i;
    }
    
    /* 簡易バブルソート（合計点の降順） */
    for (i = 0; i < NUM_STUDENTS - 1; i++) {
        for (j = 0; j < NUM_STUDENTS - 1 - i; j++) {
            if (totals[ranking[j]] < totals[ranking[j + 1]]) {
                int temp = ranking[j];
                ranking[j] = ranking[j + 1];
                ranking[j + 1] = temp;
            }
        }
    }
    
    printf("\n=== 学生ランキング（合計点順） ===\n");
    for (i = 0; i < NUM_STUDENTS; i++) {
        int student_idx = ranking[i];
        printf("%d位: %s (%d点, 平均%.1f点)\n", 
               i + 1, 
               students[student_idx], 
               totals[student_idx],
               (double)totals[student_idx] / NUM_SUBJECTS);
    }
}

int main(void)
{
    /* C90では先頭で全ての変数を宣言 */
    int grades[NUM_STUDENTS][NUM_SUBJECTS];
    int i, j;
    
    printf("=== 成績管理システム ===\n");
    printf("5人の学生の4科目の成績を入力してください。\n\n");
    
    /* 成績の入力 */
    for (i = 0; i < NUM_STUDENTS; i++) {
        printf("--- %s の成績 ---\n", students[i]);
        for (j = 0; j < NUM_SUBJECTS; j++) {
            printf("%s: ", subjects[j]);
            scanf("%d", &grades[i][j]);
        }
        printf("\n");
    }
    
    /* 各種統計の表示 */
    display_grade_table(grades);
    display_subject_averages(grades);
    find_highest_score(grades);
    display_student_ranking(grades);
    
    return 0;
}