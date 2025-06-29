/*
 * struct_pointers.c - 構造体ポインタと->演算子
 * 
 * このプログラムでは以下を学習します：
 * - 構造体ポインタの宣言と使用
 * - アロー演算子（->）の使い方
 * - 構造体ポインタと関数
 * - 効率的なデータ処理
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* 従業員情報を表す構造体 */
struct Employee {
    int id;
    char name[50];
    char department[30];
    double salary;
    int years_of_service;
};

/* 日付を表す構造体 */
struct Date {
    int year;
    int month;
    int day;
};

/* プロジェクト情報を表す構造体 */
struct Project {
    int id;
    char name[100];
    struct Date start_date;
    struct Date end_date;
    struct Employee *manager;  /* 管理者へのポインタ */
    double budget;
};

/* 従業員情報を表示する関数 */
void print_employee(struct Employee *emp)
{
    if (emp == NULL) {
        printf("エラー: 無効な従業員データ\n");
        return;
    }
    
    printf("=== 従業員情報 ===\n");
    printf("ID: %d\n", emp->id);
    printf("名前: %s\n", emp->name);
    printf("部署: %s\n", emp->department);
    printf("給与: %.0f円\n", emp->salary);
    printf("勤続年数: %d年\n", emp->years_of_service);
    printf("\n");
}

/* 給与を更新する関数 */
void update_salary(struct Employee *emp, double percentage)
{
    if (emp == NULL || percentage < -100) {
        printf("エラー: 無効なパラメータ\n");
        return;
    }
    
    double old_salary = emp->salary;
    emp->salary = old_salary * (1 + percentage / 100.0);
    
    printf("%s の給与を更新しました\n", emp->name);
    printf("変更前: %.0f円 → 変更後: %.0f円 (%.1f%%)\n", 
           old_salary, emp->salary, percentage);
}

/* 最高給与の従業員を見つける関数 */
struct Employee* find_highest_paid(struct Employee employees[], int count)
{
    if (employees == NULL || count <= 0) {
        return NULL;
    }
    
    struct Employee *highest = &employees[0];
    int i;
    
    for (i = 1; i < count; i++) {
        if (employees[i].salary > highest->salary) {
            highest = &employees[i];
        }
    }
    
    return highest;
}

/* プロジェクト情報を表示する関数 */
void print_project(struct Project *proj)
{
    if (proj == NULL) {
        printf("エラー: 無効なプロジェクトデータ\n");
        return;
    }
    
    printf("=== プロジェクト情報 ===\n");
    printf("ID: %d\n", proj->id);
    printf("プロジェクト名: %s\n", proj->name);
    printf("開始日: %d年%d月%d日\n", 
           proj->start_date.year, proj->start_date.month, proj->start_date.day);
    printf("終了日: %d年%d月%d日\n", 
           proj->end_date.year, proj->end_date.month, proj->end_date.day);
    printf("予算: %.0f円\n", proj->budget);
    
    if (proj->manager != NULL) {
        printf("管理者: %s (%s)\n", 
               proj->manager->name, proj->manager->department);
    } else {
        printf("管理者: 未定\n");
    }
    printf("\n");
}

/* 部署別の統計を計算する関数 */
void calculate_department_stats(struct Employee employees[], int count, 
                              const char *department)
{
    int dept_count = 0;
    double total_salary = 0.0;
    int total_years = 0;
    int i;
    
    for (i = 0; i < count; i++) {
        if (strcmp(employees[i].department, department) == 0) {
            dept_count++;
            total_salary += employees[i].salary;
            total_years += employees[i].years_of_service;
        }
    }
    
    if (dept_count > 0) {
        printf("=== %s の統計 ===\n", department);
        printf("人数: %d名\n", dept_count);
        printf("平均給与: %.0f円\n", total_salary / dept_count);
        printf("平均勤続年数: %.1f年\n", (double)total_years / dept_count);
        printf("\n");
    } else {
        printf("%s に該当する従業員はいません\n\n", department);
    }
}

/* 構造体のスワップ（ポインタのみ交換） */
void swap_employees(struct Employee **emp1, struct Employee **emp2)
{
    struct Employee *temp = *emp1;
    *emp1 = *emp2;
    *emp2 = temp;
}

int main(void)
{
    printf("===== 構造体ポインタと->演算子 =====\n\n");
    
    /* 1. 構造体ポインタの基本 */
    printf("1. 構造体ポインタの基本\n");
    
    struct Employee emp1 = {
        1001, "田中太郎", "開発部", 350000.0, 5
    };
    
    struct Employee *emp_ptr = &emp1;
    
    /* ドット演算子とアロー演算子の比較 */
    printf("ドット演算子: %s\n", emp1.name);
    printf("アロー演算子: %s\n", emp_ptr->name);
    printf("間接参照とドット: %s\n", (*emp_ptr).name);
    printf("\n");
    
    /* 2. ポインタを使った関数呼び出し */
    printf("2. ポインタを使った関数呼び出し\n");
    print_employee(emp_ptr);
    
    /* 3. ポインタを通じた構造体の更新 */
    printf("3. ポインタを通じた構造体の更新\n");
    update_salary(emp_ptr, 10.0);  /* 10%昇給 */
    printf("\n");
    
    /* 4. 構造体配列とポインタ */
    printf("4. 構造体配列とポインタ\n");
    
    struct Employee employees[] = {
        {2001, "佐藤花子", "営業部", 300000.0, 3},
        {2002, "山田次郎", "開発部", 400000.0, 7},
        {2003, "鈴木美咲", "人事部", 320000.0, 4},
        {2004, "高橋健太", "営業部", 280000.0, 2},
        {2005, "伊藤良子", "開発部", 450000.0, 10}
    };
    
    int emp_count = sizeof(employees) / sizeof(employees[0]);
    
    /* 最高給与の従業員を検索 */
    struct Employee *highest_paid = find_highest_paid(employees, emp_count);
    if (highest_paid != NULL) {
        printf("最高給与の従業員:\n");
        printf("名前: %s, 給与: %.0f円\n\n", 
               highest_paid->name, highest_paid->salary);
    }
    
    /* 5. ポインタ配列 */
    printf("5. ポインタ配列\n");
    
    struct Employee *dept_members[5];
    int dept_count = 0;
    int i;
    
    /* 開発部のメンバーを抽出 */
    for (i = 0; i < emp_count; i++) {
        if (strcmp(employees[i].department, "開発部") == 0) {
            dept_members[dept_count++] = &employees[i];
        }
    }
    
    printf("開発部のメンバー:\n");
    for (i = 0; i < dept_count; i++) {
        printf("- %s (ID: %d)\n", 
               dept_members[i]->name, dept_members[i]->id);
    }
    printf("\n");
    
    /* 6. ネストした構造体とポインタ */
    printf("6. ネストした構造体とポインタ\n");
    
    struct Project project1 = {
        101,
        "新システム開発",
        {2024, 1, 1},
        {2024, 12, 31},
        &employees[1],  /* 山田次郎を管理者に設定 */
        5000000.0
    };
    
    print_project(&project1);
    
    /* 7. 部署別統計 */
    printf("7. 部署別統計\n");
    calculate_department_stats(employees, emp_count, "開発部");
    calculate_department_stats(employees, emp_count, "営業部");
    
    /* 8. ポインタのスワップ */
    printf("8. ポインタのスワップ\n");
    
    struct Employee *ptr1 = &employees[0];
    struct Employee *ptr2 = &employees[1];
    
    printf("スワップ前:\n");
    printf("ptr1 → %s\n", ptr1->name);
    printf("ptr2 → %s\n", ptr2->name);
    
    swap_employees(&ptr1, &ptr2);
    
    printf("\nスワップ後:\n");
    printf("ptr1 → %s\n", ptr1->name);
    printf("ptr2 → %s\n", ptr2->name);
    
    return 0;
}

/*
実行結果例:
===== 構造体ポインタと->演算子 =====

1. 構造体ポインタの基本
ドット演算子: 田中太郎
アロー演算子: 田中太郎
間接参照とドット: 田中太郎

2. ポインタを使った関数呼び出し
=== 従業員情報 ===
ID: 1001
名前: 田中太郎
部署: 開発部
給与: 350000円
勤続年数: 5年

3. ポインタを通じた構造体の更新
田中太郎 の給与を更新しました
変更前: 350000円 → 変更後: 385000円 (10.0%)

4. 構造体配列とポインタ
最高給与の従業員:
名前: 伊藤良子, 給与: 450000円

5. ポインタ配列
開発部のメンバー:
- 山田次郎 (ID: 2002)
- 伊藤良子 (ID: 2005)

6. ネストした構造体とポインタ
=== プロジェクト情報 ===
ID: 101
プロジェクト名: 新システム開発
開始日: 2024年1月1日
終了日: 2024年12月31日
予算: 5000000円
管理者: 山田次郎 (開発部)

7. 部署別統計
=== 開発部 の統計 ===
人数: 2名
平均給与: 425000円
平均勤続年数: 8.5年

=== 営業部 の統計 ===
人数: 2名
平均給与: 290000円
平均勤続年数: 2.5年

8. ポインタのスワップ
スワップ前:
ptr1 → 佐藤花子
ptr2 → 山田次郎

スワップ後:
ptr1 → 山田次郎
ptr2 → 佐藤花子
*/
