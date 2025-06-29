/*
 * struct_pointers_c99.c - 構造体ポインタと->演算子（C99版）
 * 
 * C99の新機能：
 * - restrict修飾子
 * - inline関数
 * - bool型
 * - 可変長配列（VLA）
 * - 複合リテラル
 * - 指定イニシャライザ
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

// 従業員情報を表す構造体
struct Employee {
    int id;
    char name[50];
    char department[30];
    double salary;
    int years_of_service;
    bool is_manager;  // C99: bool型
};

// 日付を表す構造体
struct Date {
    int year;
    int month;
    int day;
};

// プロジェクト情報を表す構造体
struct Project {
    int id;
    char name[100];
    struct Date start_date;
    struct Date end_date;
    struct Employee *manager;
    double budget;
    bool is_active;  // C99: bool型
};

// C99: inline関数で日付の比較
static inline bool is_date_later(const struct Date *d1, const struct Date *d2)
{
    if (d1->year != d2->year) return d1->year > d2->year;
    if (d1->month != d2->month) return d1->month > d2->month;
    return d1->day > d2->day;
}

// C99: restrict修飾子で最適化のヒントを与える
void copy_employee(struct Employee * restrict dest, 
                  const struct Employee * restrict src)
{
    if (dest != NULL && src != NULL) {
        *dest = *src;
    }
}

// 従業員情報を表示する関数
void print_employee(const struct Employee *emp)
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
    printf("管理職: %s\n", emp->is_manager ? "はい" : "いいえ");
    printf("\n");
}

// C99: inline関数で給与計算
static inline double calculate_bonus(const struct Employee *emp)
{
    double base_bonus = emp->salary * 0.1;
    double years_bonus = emp->years_of_service * 10000.0;
    double manager_bonus = emp->is_manager ? 50000.0 : 0.0;
    return base_bonus + years_bonus + manager_bonus;
}

// 部署の統計情報を格納する構造体
struct DepartmentStats {
    char department[30];
    int count;
    double total_salary;
    double avg_salary;
    double avg_years;
    int manager_count;
};

// C99: VLAを使用した動的な統計計算
struct DepartmentStats* calculate_all_stats(struct Employee employees[], 
                                           int emp_count, int *dept_count)
{
    // 一時的な部署リスト（最大emp_count部署）
    char departments[emp_count][30];  // C99: VLA
    int num_depts = 0;
    
    // ユニークな部署を収集
    for (int i = 0; i < emp_count; i++) {
        bool found = false;
        for (int j = 0; j < num_depts; j++) {
            if (strcmp(employees[i].department, departments[j]) == 0) {
                found = true;
                break;
            }
        }
        if (!found) {
            strcpy(departments[num_depts++], employees[i].department);
        }
    }
    
    // 統計情報の配列を動的に確保
    static struct DepartmentStats stats[10];  // 簡易実装
    
    // 各部署の統計を計算
    for (int d = 0; d < num_depts; d++) {
        strcpy(stats[d].department, departments[d]);
        stats[d].count = 0;
        stats[d].total_salary = 0.0;
        stats[d].manager_count = 0;
        int total_years = 0;
        
        for (int i = 0; i < emp_count; i++) {
            if (strcmp(employees[i].department, departments[d]) == 0) {
                stats[d].count++;
                stats[d].total_salary += employees[i].salary;
                total_years += employees[i].years_of_service;
                if (employees[i].is_manager) {
                    stats[d].manager_count++;
                }
            }
        }
        
        stats[d].avg_salary = stats[d].total_salary / stats[d].count;
        stats[d].avg_years = (double)total_years / stats[d].count;
    }
    
    *dept_count = num_depts;
    return stats;
}

// プロジェクトの期間を計算（簡易版）
int calculate_project_days(const struct Project *proj)
{
    if (proj == NULL) return 0;
    
    // 簡易計算（月を30日として計算）
    int days = (proj->end_date.year - proj->start_date.year) * 365;
    days += (proj->end_date.month - proj->start_date.month) * 30;
    days += (proj->end_date.day - proj->start_date.day);
    
    return days;
}

int main(void)
{
    printf("===== 構造体ポインタと->演算子 (C99版) =====\n\n");
    
    // 1. C99: 指定イニシャライザとbool型
    printf("1. 指定イニシャライザとbool型\n");
    
    struct Employee emp1 = {
        .id = 1001,
        .name = "田中太郎",
        .department = "開発部",
        .salary = 350000.0,
        .years_of_service = 5,
        .is_manager = false
    };
    
    print_employee(&emp1);
    
    // 2. C99: inline関数の使用
    printf("2. inline関数によるボーナス計算\n");
    double bonus = calculate_bonus(&emp1);
    printf("%s のボーナス: %.0f円\n\n", emp1.name, bonus);
    
    // 3. C99: 複合リテラルでの一時オブジェクト
    printf("3. 複合リテラルでの一時オブジェクト\n");
    
    print_employee(&(struct Employee){
        .id = 9999,
        .name = "テスト社員",
        .department = "テスト部",
        .salary = 300000.0,
        .years_of_service = 1,
        .is_manager = false
    });
    
    // 4. 構造体配列の高度な操作
    printf("4. 構造体配列の高度な操作\n");
    
    struct Employee employees[] = {
        {.id = 2001, .name = "佐藤花子", .department = "営業部", 
         .salary = 300000.0, .years_of_service = 3, .is_manager = false},
        {.id = 2002, .name = "山田次郎", .department = "開発部", 
         .salary = 400000.0, .years_of_service = 7, .is_manager = true},
        {.id = 2003, .name = "鈴木美咲", .department = "人事部", 
         .salary = 320000.0, .years_of_service = 4, .is_manager = false},
        {.id = 2004, .name = "高橋健太", .department = "営業部", 
         .salary = 280000.0, .years_of_service = 2, .is_manager = false},
        {.id = 2005, .name = "伊藤良子", .department = "開発部", 
         .salary = 450000.0, .years_of_service = 10, .is_manager = true}
    };
    
    int emp_count = sizeof(employees) / sizeof(employees[0]);
    
    // C99: forループ内での変数宣言とフィルタリング
    printf("管理職の一覧:\n");
    for (int i = 0; i < emp_count; i++) {
        if (employees[i].is_manager) {
            printf("- %s (%s)\n", 
                   employees[i].name, employees[i].department);
        }
    }
    printf("\n");
    
    // 5. C99: VLAを使った統計計算
    printf("5. 部署別統計（VLA使用）\n");
    
    int dept_count;
    struct DepartmentStats *stats = calculate_all_stats(employees, 
                                                       emp_count, 
                                                       &dept_count);
    
    for (int i = 0; i < dept_count; i++) {
        printf("=== %s ===\n", stats[i].department);
        printf("人数: %d名\n", stats[i].count);
        printf("平均給与: %.0f円\n", stats[i].avg_salary);
        printf("平均勤続年数: %.1f年\n", stats[i].avg_years);
        printf("管理職数: %d名\n", stats[i].manager_count);
        printf("\n");
    }
    
    // 6. プロジェクトとポインタ
    printf("6. プロジェクトとポインタ\n");
    
    struct Project projects[] = {
        {
            .id = 101,
            .name = "新システム開発",
            .start_date = {2024, 1, 1},
            .end_date = {2024, 12, 31},
            .manager = &employees[1],  // 山田次郎
            .budget = 5000000.0,
            .is_active = true
        },
        {
            .id = 102,
            .name = "既存システム改修",
            .start_date = {2024, 3, 1},
            .end_date = {2024, 6, 30},
            .manager = &employees[4],  // 伊藤良子
            .budget = 2000000.0,
            .is_active = true
        }
    };
    
    printf("=== アクティブなプロジェクト ===\n");
    for (int i = 0; i < 2; i++) {
        if (projects[i].is_active) {
            printf("プロジェクト: %s\n", projects[i].name);
            printf("期間: 約%d日\n", calculate_project_days(&projects[i]));
            printf("管理者: %s\n", projects[i].manager->name);
            printf("予算: %.0f円\n\n", projects[i].budget);
        }
    }
    
    // 7. C99: restrict修飾子の使用例
    printf("7. restrict修飾子の使用例\n");
    
    struct Employee copy_emp;
    copy_employee(&copy_emp, &emp1);
    
    printf("コピーされた従業員:\n");
    printf("名前: %s (ID: %d)\n\n", copy_emp.name, copy_emp.id);
    
    // 8. 条件付きポインタ操作
    printf("8. 条件付きポインタ操作\n");
    
    // 最高給与の管理職を検索
    struct Employee *highest_paid_manager = NULL;
    double max_salary = 0.0;
    
    for (int i = 0; i < emp_count; i++) {
        if (employees[i].is_manager && employees[i].salary > max_salary) {
            highest_paid_manager = &employees[i];
            max_salary = employees[i].salary;
        }
    }
    
    if (highest_paid_manager != NULL) {
        printf("最高給与の管理職: %s (%.0f円)\n", 
               highest_paid_manager->name, 
               highest_paid_manager->salary);
    }
    
    return 0;
}

/*
実行結果例:
===== 構造体ポインタと->演算子 (C99版) =====

1. 指定イニシャライザとbool型
=== 従業員情報 ===
ID: 1001
名前: 田中太郎
部署: 開発部
給与: 350000円
勤続年数: 5年
管理職: いいえ

2. inline関数によるボーナス計算
田中太郎 のボーナス: 85000円

3. 複合リテラルでの一時オブジェクト
=== 従業員情報 ===
ID: 9999
名前: テスト社員
部署: テスト部
給与: 300000円
勤続年数: 1年
管理職: いいえ

4. 構造体配列の高度な操作
管理職の一覧:
- 山田次郎 (開発部)
- 伊藤良子 (開発部)

5. 部署別統計（VLA使用）
=== 営業部 ===
人数: 2名
平均給与: 290000円
平均勤続年数: 2.5年
管理職数: 0名

=== 開発部 ===
人数: 2名
平均給与: 425000円
平均勤続年数: 8.5年
管理職数: 2名

=== 人事部 ===
人数: 1名
平均給与: 320000円
平均勤続年数: 4.0年
管理職数: 0名

6. プロジェクトとポインタ
=== アクティブなプロジェクト ===
プロジェクト: 新システム開発
期間: 約360日
管理者: 山田次郎
予算: 5000000円

プロジェクト: 既存システム改修
期間: 約120日
管理者: 伊藤良子
予算: 2000000円

7. restrict修飾子の使用例
コピーされた従業員:
名前: 田中太郎 (ID: 1001)

8. 条件付きポインタ操作
最高給与の管理職: 伊藤良子 (450000円)
*/
