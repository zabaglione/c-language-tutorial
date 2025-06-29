/*
 * struct_arrays_c99.c - 構造体配列の操作（C99版）
 * 
 * C99の新機能：
 * - 可変長配列（VLA）
 * - 柔軟な配列メンバー
 * - 指定イニシャライザ
 * - bool型
 * - inline関数
 * - 複合リテラル
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX_NAME_LEN 50
#define MAX_TITLE_LEN 100

// 学生情報を表す構造体
struct Student {
    int id;
    char name[MAX_NAME_LEN];
    double scores[5];  // 5教科の点数
    double average;
    char grade;
    bool is_scholarship;  // C99: bool型で奨学金対象かを示す
};

// 書籍情報を表す構造体
struct Book {
    int isbn;
    char title[MAX_TITLE_LEN];
    char author[50];
    int year;
    bool is_borrowed;     // C99: bool型
    int borrower_id;
    int borrow_count;     // 累計貸出回数
};

// 図書館統計情報
struct LibraryStats {
    int total_books;
    int borrowed_books;
    int total_students;
    double borrow_rate;
};

// C99: 柔軟な配列メンバーを持つ構造体
struct DynamicLibrary {
    int book_count;
    int student_count;
    struct LibraryStats stats;
    struct Book books[];  // C99: 柔軟な配列メンバー
};

// C99: inline関数で学生の平均点を計算
static inline double calculate_student_average(const double scores[], int count)
{
    double sum = 0.0;
    for (int i = 0; i < count; i++) {
        sum += scores[i];
    }
    return sum / count;
}

// C99: inline関数で成績評価
static inline char get_grade(double average)
{
    if (average >= 90.0) return 'A';
    if (average >= 80.0) return 'B';
    if (average >= 70.0) return 'C';
    if (average >= 60.0) return 'D';
    return 'F';
}

// 学生情報を更新
void update_student(struct Student *student)
{
    student->average = calculate_student_average(student->scores, 5);
    student->grade = get_grade(student->average);
    student->is_scholarship = (student->average >= 85.0);
}

// 学生情報を表示
void print_student_info(const struct Student *student)
{
    printf("ID: %d, 名前: %s\n", student->id, student->name);
    printf("点数: ");
    for (int i = 0; i < 5; i++) {
        printf("%.0f ", student->scores[i]);
    }
    printf("\n平均: %.1f, 評価: %c", student->average, student->grade);
    if (student->is_scholarship) {
        printf(" [奨学金対象]");
    }
    printf("\n---\n");
}

// C99: VLAを使った動的な成績分析
void analyze_scores(struct Student students[], int count)
{
    // 各教科の平均点を計算（VLA使用）
    double subject_averages[5] = {0};  
    int grade_counts[5] = {0};  // A, B, C, D, F
    
    // 教科別の点数を収集（VLA）
    double subject_scores[5][count];  // C99: VLA
    
    for (int subject = 0; subject < 5; subject++) {
        for (int i = 0; i < count; i++) {
            subject_scores[subject][i] = students[i].scores[subject];
            subject_averages[subject] += students[i].scores[subject];
        }
        subject_averages[subject] /= count;
    }
    
    // 成績分布を計算
    for (int i = 0; i < count; i++) {
        switch (students[i].grade) {
            case 'A': grade_counts[0]++; break;
            case 'B': grade_counts[1]++; break;
            case 'C': grade_counts[2]++; break;
            case 'D': grade_counts[3]++; break;
            case 'F': grade_counts[4]++; break;
        }
    }
    
    printf("=== 成績分析 ===\n");
    printf("教科別平均点:\n");
    const char *subjects[] = {"国語", "数学", "英語", "理科", "社会"};
    for (int i = 0; i < 5; i++) {
        printf("%s: %.1f点\n", subjects[i], subject_averages[i]);
    }
    
    printf("\n成績分布:\n");
    const char grades[] = {'A', 'B', 'C', 'D', 'F'};
    for (int i = 0; i < 5; i++) {
        printf("%c評価: %d名 (%.1f%%)\n", 
               grades[i], grade_counts[i], 
               (double)grade_counts[i] / count * 100);
    }
    printf("\n");
}

// 書籍の人気度を計算
static inline int calculate_popularity(const struct Book *book)
{
    return book->borrow_count * 10 + (2024 - book->year);
}

// クイックソート用の比較関数（人気度順）
int compare_books_by_popularity(const void *a, const void *b)
{
    const struct Book *book_a = (const struct Book *)a;
    const struct Book *book_b = (const struct Book *)b;
    return calculate_popularity(book_b) - calculate_popularity(book_a);
}

int main(void)
{
    printf("===== 構造体配列の操作 (C99版) =====\n\n");
    
    // 1. C99: 指定イニシャライザを使った構造体配列
    printf("1. 指定イニシャライザを使った構造体配列\n");
    
    struct Student students[] = {
        {.id = 1001, .name = "田中太郎", 
         .scores = {85, 90, 78, 92, 88}},
        {.id = 1002, .name = "佐藤花子", 
         .scores = {92, 88, 95, 90, 93}},
        {.id = 1003, .name = "山田次郎", 
         .scores = {75, 80, 72, 78, 70}},
        {.id = 1004, .name = "鈴木美咲", 
         .scores = {88, 85, 90, 87, 91}},
        {.id = 1005, .name = "高橋健太", 
         .scores = {60, 65, 58, 70, 62}}
    };
    
    int student_count = sizeof(students) / sizeof(students[0]);
    
    // 全学生の情報を更新
    for (int i = 0; i < student_count; i++) {
        update_student(&students[i]);
    }
    
    printf("=== 全学生の成績 ===\n");
    for (int i = 0; i < student_count; i++) {
        print_student_info(&students[i]);
    }
    printf("\n");
    
    // 2. C99: VLAを使った成績分析
    printf("2. VLAを使った成績分析\n");
    analyze_scores(students, student_count);
    
    // 3. 書籍管理システム
    printf("3. 書籍管理システム\n");
    
    struct Book books[] = {
        {.isbn = 1001, .title = "プログラミング入門", 
         .author = "山田太郎", .year = 2020, 
         .is_borrowed = false, .borrow_count = 15},
        {.isbn = 1002, .title = "データ構造とアルゴリズム", 
         .author = "佐藤花子", .year = 2019, 
         .is_borrowed = false, .borrow_count = 25},
        {.isbn = 1003, .title = "オペレーティングシステム", 
         .author = "田中次郎", .year = 2021, 
         .is_borrowed = false, .borrow_count = 10},
        {.isbn = 1004, .title = "ネットワーク基礎", 
         .author = "鈴木一郎", .year = 2022, 
         .is_borrowed = false, .borrow_count = 8},
        {.isbn = 1005, .title = "データベース設計", 
         .author = "高橋美咲", .year = 2020, 
         .is_borrowed = false, .borrow_count = 20}
    };
    
    int book_count = sizeof(books) / sizeof(books[0]);
    
    // 人気度でソート
    qsort(books, book_count, sizeof(struct Book), compare_books_by_popularity);
    
    printf("=== 人気書籍ランキング ===\n");
    for (int i = 0; i < book_count; i++) {
        printf("%d位: 「%s」\n", i + 1, books[i].title);
        printf("    著者: %s, 貸出回数: %d回, 人気度: %d\n", 
               books[i].author, books[i].borrow_count, 
               calculate_popularity(&books[i]));
    }
    printf("\n");
    
    // 4. C99: 複合リテラルを使った一時的な配列操作
    printf("4. 複合リテラルを使った一時的な配列操作\n");
    
    // 奨学金対象者のポインタ配列を動的に作成
    struct Student *scholarship_students[student_count];  // C99: VLA
    int scholarship_count = 0;
    
    for (int i = 0; i < student_count; i++) {
        if (students[i].is_scholarship) {
            scholarship_students[scholarship_count++] = &students[i];
        }
    }
    
    printf("=== 奨学金対象者 (%d名) ===\n", scholarship_count);
    for (int i = 0; i < scholarship_count; i++) {
        printf("%s (平均: %.1f点)\n", 
               scholarship_students[i]->name, 
               scholarship_students[i]->average);
    }
    printf("\n");
    
    // 5. 図書館統計の計算
    printf("5. 図書館統計\n");
    
    // 貸出シミュレーション
    books[0].is_borrowed = true;
    books[0].borrower_id = students[1].id;
    books[2].is_borrowed = true;
    books[2].borrower_id = students[0].id;
    
    // 統計情報の計算
    struct LibraryStats stats = {
        .total_books = book_count,
        .borrowed_books = 0,
        .total_students = student_count
    };
    
    for (int i = 0; i < book_count; i++) {
        if (books[i].is_borrowed) {
            stats.borrowed_books++;
        }
    }
    
    stats.borrow_rate = (double)stats.borrowed_books / stats.total_books * 100;
    
    printf("=== 図書館統計情報 ===\n");
    printf("総蔵書数: %d冊\n", stats.total_books);
    printf("貸出中: %d冊\n", stats.borrowed_books);
    printf("貸出率: %.1f%%\n", stats.borrow_rate);
    printf("登録学生数: %d名\n", stats.total_students);
    
    return 0;
}

/*
実行結果例:
===== 構造体配列の操作 (C99版) =====

1. 指定イニシャライザを使った構造体配列
=== 全学生の成績 ===
ID: 1001, 名前: 田中太郎
点数: 85 90 78 92 88 
平均: 86.6, 評価: B [奨学金対象]
---
ID: 1002, 名前: 佐藤花子
点数: 92 88 95 90 93 
平均: 91.6, 評価: A [奨学金対象]
---
ID: 1003, 名前: 山田次郎
点数: 75 80 72 78 70 
平均: 75.0, 評価: C
---
ID: 1004, 名前: 鈴木美咲
点数: 88 85 90 87 91 
平均: 88.2, 評価: B [奨学金対象]
---
ID: 1005, 名前: 高橋健太
点数: 60 65 58 70 62 
平均: 63.0, 評価: D
---

2. VLAを使った成績分析
=== 成績分析 ===
教科別平均点:
国語: 80.0点
数学: 81.6点
英語: 78.6点
理科: 83.4点
社会: 80.8点

成績分布:
A評価: 1名 (20.0%)
B評価: 2名 (40.0%)
C評価: 1名 (20.0%)
D評価: 1名 (20.0%)
F評価: 0名 (0.0%)

3. 書籍管理システム
=== 人気書籍ランキング ===
1位: 「データ構造とアルゴリズム」
    著者: 佐藤花子, 貸出回数: 25回, 人気度: 255
2位: 「データベース設計」
    著者: 高橋美咲, 貸出回数: 20回, 人気度: 204
3位: 「プログラミング入門」
    著者: 山田太郎, 貸出回数: 15回, 人気度: 154
4位: 「オペレーティングシステム」
    著者: 田中次郎, 貸出回数: 10回, 人気度: 103
5位: 「ネットワーク基礎」
    著者: 鈴木一郎, 貸出回数: 8回, 人気度: 82

4. 複合リテラルを使った一時的な配列操作
=== 奨学金対象者 (3名) ===
田中太郎 (平均: 86.6点)
佐藤花子 (平均: 91.6点)
鈴木美咲 (平均: 88.2点)

5. 図書館統計
=== 図書館統計情報 ===
総蔵書数: 5冊
貸出中: 2冊
貸出率: 40.0%
登録学生数: 5名
*/
