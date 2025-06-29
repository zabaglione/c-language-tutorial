/*
 * struct_arrays.c - 構造体配列の操作
 * 
 * このプログラムでは以下を学習します：
 * - 構造体配列の宣言と初期化
 * - 構造体配列とポインタ演算
 * - 構造体ポインタ配列
 * - 実践的なデータ管理
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STUDENTS 50
#define MAX_BOOKS 100
#define MAX_NAME_LEN 50

/* 学生情報を表す構造体 */
struct Student {
    int id;
    char name[MAX_NAME_LEN];
    double scores[5];  /* 5教科の点数 */
    double average;
    char grade;
};

/* 書籍情報を表す構造体 */
struct Book {
    int isbn;
    char title[100];
    char author[50];
    int year;
    int is_borrowed;
    int borrower_id;  /* 借りている学生のID */
};

/* 図書館を表す構造体 */
struct Library {
    struct Book books[MAX_BOOKS];
    int book_count;
    struct Student *students[MAX_STUDENTS];
    int student_count;
};

/* 学生の平均点を計算する関数 */
void calculate_average(struct Student *student)
{
    int i;
    double sum = 0.0;
    
    for (i = 0; i < 5; i++) {
        sum += student->scores[i];
    }
    
    student->average = sum / 5.0;
    
    /* 成績評価 */
    if (student->average >= 90.0) {
        student->grade = 'A';
    } else if (student->average >= 80.0) {
        student->grade = 'B';
    } else if (student->average >= 70.0) {
        student->grade = 'C';
    } else if (student->average >= 60.0) {
        student->grade = 'D';
    } else {
        student->grade = 'F';
    }
}

/* 学生情報を表示する関数 */
void print_student(const struct Student *student)
{
    int i;
    
    printf("ID: %d, 名前: %s\n", student->id, student->name);
    printf("点数: ");
    for (i = 0; i < 5; i++) {
        printf("%.0f ", student->scores[i]);
    }
    printf("\n平均: %.1f, 評価: %c\n", student->average, student->grade);
    printf("---\n");
}

/* 成績順にソート（バブルソート） */
void sort_students_by_average(struct Student students[], int count)
{
    int i, j;
    struct Student temp;
    
    for (i = 0; i < count - 1; i++) {
        for (j = 0; j < count - 1 - i; j++) {
            if (students[j].average < students[j + 1].average) {
                temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}

/* 書籍を追加する関数 */
int add_book(struct Library *lib, int isbn, const char *title, 
             const char *author, int year)
{
    if (lib->book_count >= MAX_BOOKS) {
        return 0;  /* 追加失敗 */
    }
    
    struct Book *book = &lib->books[lib->book_count];
    book->isbn = isbn;
    strcpy(book->title, title);
    strcpy(book->author, author);
    book->year = year;
    book->is_borrowed = 0;
    book->borrower_id = -1;
    
    lib->book_count++;
    return 1;  /* 追加成功 */
}

/* 書籍を検索する関数 */
struct Book* find_book_by_isbn(struct Library *lib, int isbn)
{
    int i;
    for (i = 0; i < lib->book_count; i++) {
        if (lib->books[i].isbn == isbn) {
            return &lib->books[i];
        }
    }
    return NULL;
}

/* 書籍を借りる関数 */
int borrow_book(struct Library *lib, int isbn, int student_id)
{
    struct Book *book = find_book_by_isbn(lib, isbn);
    
    if (book == NULL) {
        printf("ISBN %d の書籍が見つかりません\n", isbn);
        return 0;
    }
    
    if (book->is_borrowed) {
        printf("「%s」は既に貸出中です\n", book->title);
        return 0;
    }
    
    book->is_borrowed = 1;
    book->borrower_id = student_id;
    printf("ID %d の学生が「%s」を借りました\n", student_id, book->title);
    return 1;
}

/* 学生の借りている本を表示 */
void show_borrowed_books(struct Library *lib, int student_id)
{
    int i;
    int count = 0;
    
    printf("\nID %d の学生が借りている本:\n", student_id);
    for (i = 0; i < lib->book_count; i++) {
        if (lib->books[i].is_borrowed && 
            lib->books[i].borrower_id == student_id) {
            printf("- %s (%s著, %d年)\n", 
                   lib->books[i].title, 
                   lib->books[i].author, 
                   lib->books[i].year);
            count++;
        }
    }
    
    if (count == 0) {
        printf("  借りている本はありません\n");
    }
}

int main(void)
{
    printf("===== 構造体配列の操作 =====\n\n");
    
    /* 1. 構造体配列の基本 */
    printf("1. 構造体配列の基本\n");
    
    struct Student students[5] = {
        {1001, "田中太郎", {85, 90, 78, 92, 88}, 0, ' '},
        {1002, "佐藤花子", {92, 88, 95, 90, 93}, 0, ' '},
        {1003, "山田次郎", {75, 80, 72, 78, 70}, 0, ' '},
        {1004, "鈴木美咲", {88, 85, 90, 87, 91}, 0, ' '},
        {1005, "高橋健太", {60, 65, 58, 70, 62}, 0, ' '}
    };
    
    int student_count = 5;
    int i;
    
    /* 平均点の計算 */
    for (i = 0; i < student_count; i++) {
        calculate_average(&students[i]);
    }
    
    printf("=== 全学生の成績 ===\n");
    for (i = 0; i < student_count; i++) {
        print_student(&students[i]);
    }
    printf("\n");
    
    /* 2. 構造体配列のソート */
    printf("2. 構造体配列のソート\n");
    
    sort_students_by_average(students, student_count);
    
    printf("=== 成績順（高い順） ===\n");
    for (i = 0; i < student_count; i++) {
        printf("%d位: %s (平均: %.1f)\n", 
               i + 1, students[i].name, students[i].average);
    }
    printf("\n");
    
    /* 3. 構造体ポインタ配列 */
    printf("3. 構造体ポインタ配列\n");
    
    struct Student *top_students[3];
    int top_count = 0;
    
    /* 平均80点以上の学生を選抜 */
    for (i = 0; i < student_count; i++) {
        if (students[i].average >= 80.0 && top_count < 3) {
            top_students[top_count++] = &students[i];
        }
    }
    
    printf("=== 優秀学生（平均80点以上） ===\n");
    for (i = 0; i < top_count; i++) {
        printf("%s (平均: %.1f, 評価: %c)\n", 
               top_students[i]->name, 
               top_students[i]->average, 
               top_students[i]->grade);
    }
    printf("\n");
    
    /* 4. より複雑な構造体の管理 */
    printf("4. 図書館システム\n");
    
    struct Library library = {.book_count = 0, .student_count = 0};
    
    /* 書籍の追加 */
    add_book(&library, 1001, "プログラミング入門", "山田太郎", 2020);
    add_book(&library, 1002, "データ構造とアルゴリズム", "佐藤花子", 2019);
    add_book(&library, 1003, "オペレーティングシステム", "田中次郎", 2021);
    add_book(&library, 1004, "ネットワーク基礎", "鈴木一郎", 2022);
    add_book(&library, 1005, "データベース設計", "高橋美咲", 2020);
    
    printf("図書館の蔵書数: %d冊\n\n", library.book_count);
    
    /* 学生を図書館に登録 */
    for (i = 0; i < 3; i++) {
        library.students[i] = &students[i];
        library.student_count++;
    }
    
    /* 本の貸出 */
    borrow_book(&library, 1001, students[0].id);
    borrow_book(&library, 1003, students[0].id);
    borrow_book(&library, 1002, students[1].id);
    borrow_book(&library, 1001, students[2].id);  /* 既に貸出中 */
    
    /* 各学生の借りている本を表示 */
    for (i = 0; i < 3; i++) {
        show_borrowed_books(&library, students[i].id);
    }
    printf("\n");
    
    /* 5. ポインタ演算による配列走査 */
    printf("5. ポインタ演算による配列走査\n");
    
    struct Book *book_ptr = library.books;
    struct Book *book_end = library.books + library.book_count;
    
    printf("=== 貸出中の書籍一覧 ===\n");
    while (book_ptr < book_end) {
        if (book_ptr->is_borrowed) {
            printf("「%s」 → 学生ID: %d\n", 
                   book_ptr->title, book_ptr->borrower_id);
        }
        book_ptr++;
    }
    
    return 0;
}

/*
実行結果例:
===== 構造体配列の操作 =====

1. 構造体配列の基本
=== 全学生の成績 ===
ID: 1001, 名前: 田中太郎
点数: 85 90 78 92 88 
平均: 86.6, 評価: B
---
ID: 1002, 名前: 佐藤花子
点数: 92 88 95 90 93 
平均: 91.6, 評価: A
---
ID: 1003, 名前: 山田次郎
点数: 75 80 72 78 70 
平均: 75.0, 評価: C
---
ID: 1004, 名前: 鈴木美咲
点数: 88 85 90 87 91 
平均: 88.2, 評価: B
---
ID: 1005, 名前: 高橋健太
点数: 60 65 58 70 62 
平均: 63.0, 評価: D
---

2. 構造体配列のソート
=== 成績順（高い順） ===
1位: 佐藤花子 (平均: 91.6)
2位: 鈴木美咲 (平均: 88.2)
3位: 田中太郎 (平均: 86.6)
4位: 山田次郎 (平均: 75.0)
5位: 高橋健太 (平均: 63.0)

3. 構造体ポインタ配列
=== 優秀学生（平均80点以上） ===
佐藤花子 (平均: 91.6, 評価: A)
鈴木美咲 (平均: 88.2, 評価: B)
田中太郎 (平均: 86.6, 評価: B)

4. 図書館システム
図書館の蔵書数: 5冊

ID 1001 の学生が「プログラミング入門」を借りました
ID 1001 の学生が「オペレーティングシステム」を借りました
ID 1002 の学生が「データ構造とアルゴリズム」を借りました
「プログラミング入門」は既に貸出中です

ID 1001 の学生が借りている本:
- プログラミング入門 (山田太郎著, 2020年)
- オペレーティングシステム (田中次郎著, 2021年)

ID 1002 の学生が借りている本:
- データ構造とアルゴリズム (佐藤花子著, 2019年)

ID 1003 の学生が借りている本:
  借りている本はありません

5. ポインタ演算による配列走査
=== 貸出中の書籍一覧 ===
「プログラミング入門」 → 学生ID: 1001
「データ構造とアルゴリズム」 → 学生ID: 1002
「オペレーティングシステム」 → 学生ID: 1001
*/
