/*
 * 演習11-6: 構造体を使った関数 - 解答例
 * 
 * 構造体を引数や戻り値として使用する関数群を実装します。
 */
#include <stdio.h>
#include <string.h>
#include <math.h>

/* 構造体定義 */
/* 商品情報 */
typedef struct {
    int id;
    char name[50];
    double price;
    int stock;
} Product;

/* 学生情報 */
typedef struct {
    int id;
    char name[50];
    double score;
    char grade;
} Student;

/* 日付 */
typedef struct {
    int year;
    int month;
    int day;
} Date;

/* 座標点 */
typedef struct {
    double x;
    double y;
} Point;

/* 矩形 */
typedef struct {
    Point top_left;
    Point bottom_right;
} Rectangle;

/* 関数プロトタイプ */
/* 商品管理関数 */
Product create_product(int id, const char *name, double price, int stock);
void print_product(Product p);
double calculate_total_value(Product p);
int compare_products_by_price(Product p1, Product p2);
void update_stock(Product *p, int quantity);
void apply_discount(Product *p, double discount_percent);

/* 学生管理関数 */
Student create_student(int id, const char *name, double score);
void print_student(Student s);
void update_score(Student *s, double new_score);
char calculate_grade(double score);
Student find_best_student(Student students[], int count);
void sort_students_by_score(Student students[], int count);

/* 日付操作関数 */
Date create_date(int year, int month, int day);
void print_date(Date d);
int is_valid_date(Date d);
int is_leap_year(int year);
int days_in_month(int year, int month);
int date_difference(Date d1, Date d2);
int compare_dates(Date d1, Date d2);

/* 座標・図形関数 */
Point create_point(double x, double y);
double point_distance(Point p1, Point p2);
Rectangle create_rectangle(Point top_left, Point bottom_right);
double rectangle_area(Rectangle r);
double rectangle_perimeter(Rectangle r);
int point_in_rectangle(Point p, Rectangle r);

/* 商品を作成する関数 */
Product create_product(int id, const char *name, double price, int stock)
{
    Product p;
    p.id = id;
    strncpy(p.name, name, sizeof(p.name) - 1);
    p.name[sizeof(p.name) - 1] = '\0';
    p.price = price;
    p.stock = stock;
    return p;
}

/* 商品情報を表示する関数 */
void print_product(Product p)
{
    printf("商品ID: %d\n", p.id);
    printf("商品名: %s\n", p.name);
    printf("価格: %.2f円\n", p.price);
    printf("在庫: %d個\n", p.stock);
}

/* 商品の総価値を計算する関数 */
double calculate_total_value(Product p)
{
    return p.price * p.stock;
}

/* 商品を価格で比較する関数 */
int compare_products_by_price(Product p1, Product p2)
{
    if (p1.price < p2.price) return -1;
    if (p1.price > p2.price) return 1;
    return 0;
}

/* 在庫を更新する関数 */
void update_stock(Product *p, int quantity)
{
    if (p != NULL)
    {
        p->stock += quantity;
        if (p->stock < 0)
        {
            p->stock = 0;
        }
    }
}

/* 割引を適用する関数 */
void apply_discount(Product *p, double discount_percent)
{
    if (p != NULL && discount_percent >= 0.0 && discount_percent <= 100.0)
    {
        p->price *= (1.0 - discount_percent / 100.0);
    }
}

/* 学生を作成する関数 */
Student create_student(int id, const char *name, double score)
{
    Student s;
    s.id = id;
    strncpy(s.name, name, sizeof(s.name) - 1);
    s.name[sizeof(s.name) - 1] = '\0';
    s.score = score;
    s.grade = calculate_grade(score);
    return s;
}

/* 学生情報を表示する関数 */
void print_student(Student s)
{
    printf("学生ID: %d\n", s.id);
    printf("氏名: %s\n", s.name);
    printf("得点: %.1f点\n", s.score);
    printf("成績: %c\n", s.grade);
}

/* 学生の成績を更新する関数 */
void update_score(Student *s, double new_score)
{
    if (s != NULL && new_score >= 0.0 && new_score <= 100.0)
    {
        s->score = new_score;
        s->grade = calculate_grade(new_score);
    }
}

/* 得点から成績を計算する関数 */
char calculate_grade(double score)
{
    if (score >= 90.0) return 'A';
    if (score >= 80.0) return 'B';
    if (score >= 70.0) return 'C';
    if (score >= 60.0) return 'D';
    return 'F';
}

/* 学生配列から最高得点者を見つける関数 */
Student find_best_student(Student students[], int count)
{
    Student best = students[0];
    int i;
    
    for (i = 1; i < count; i++)
    {
        if (students[i].score > best.score)
        {
            best = students[i];
        }
    }
    
    return best;
}

/* 学生を得点順にソートする関数 */
void sort_students_by_score(Student students[], int count)
{
    int i, j;
    Student temp;
    
    for (i = 0; i < count - 1; i++)
    {
        for (j = 0; j < count - 1 - i; j++)
        {
            if (students[j].score < students[j + 1].score)
            {
                temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}

/* 日付を作成する関数 */
Date create_date(int year, int month, int day)
{
    Date d;
    d.year = year;
    d.month = month;
    d.day = day;
    return d;
}

/* 日付を表示する関数 */
void print_date(Date d)
{
    printf("%04d年%02d月%02d日", d.year, d.month, d.day);
}

/* 日付の妥当性をチェックする関数 */
int is_valid_date(Date d)
{
    if (d.year < 1 || d.year > 9999)
    {
        return 0;
    }
    
    if (d.month < 1 || d.month > 12)
    {
        return 0;
    }
    
    if (d.day < 1 || d.day > days_in_month(d.year, d.month))
    {
        return 0;
    }
    
    return 1;
}

/* うるう年かどうかを判定する関数 */
int is_leap_year(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

/* 月の日数を返す関数 */
int days_in_month(int year, int month)
{
    int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    if (month < 1 || month > 12)
    {
        return 0;
    }
    
    if (month == 2 && is_leap_year(year))
    {
        return 29;
    }
    
    return days[month - 1];
}

/* 2つの日付の差を計算する関数（簡易版） */
int date_difference(Date d1, Date d2)
{
    /* より正確な実装には、各月の日数を考慮した計算が必要 */
    /* ここでは簡易的に年と月を日数に変換 */
    int days1 = d1.year * 365 + d1.month * 30 + d1.day;
    int days2 = d2.year * 365 + d2.month * 30 + d2.day;
    
    return days1 - days2;
}

/* 日付を比較する関数 */
int compare_dates(Date d1, Date d2)
{
    if (d1.year != d2.year)
    {
        return d1.year - d2.year;
    }
    
    if (d1.month != d2.month)
    {
        return d1.month - d2.month;
    }
    
    return d1.day - d2.day;
}

/* 点を作成する関数 */
Point create_point(double x, double y)
{
    Point p;
    p.x = x;
    p.y = y;
    return p;
}

/* 2点間の距離を計算する関数 */
double point_distance(Point p1, Point p2)
{
    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;
    return sqrt(dx * dx + dy * dy);
}

/* 矩形を作成する関数 */
Rectangle create_rectangle(Point top_left, Point bottom_right)
{
    Rectangle r;
    r.top_left = top_left;
    r.bottom_right = bottom_right;
    return r;
}

/* 矩形の面積を計算する関数 */
double rectangle_area(Rectangle r)
{
    double width = r.bottom_right.x - r.top_left.x;
    double height = r.top_left.y - r.bottom_right.y;
    return fabs(width * height);
}

/* 矩形の周囲長を計算する関数 */
double rectangle_perimeter(Rectangle r)
{
    double width = fabs(r.bottom_right.x - r.top_left.x);
    double height = fabs(r.top_left.y - r.bottom_right.y);
    return 2.0 * (width + height);
}

/* 点が矩形内にあるかを判定する関数 */
int point_in_rectangle(Point p, Rectangle r)
{
    return p.x >= r.top_left.x && p.x <= r.bottom_right.x &&
           p.y <= r.top_left.y && p.y >= r.bottom_right.y;
}

/* メイン関数 - テスト用 */
int main(void)
{
    printf("=== 構造体を使った関数のテスト ===\n\n");
    
    /* 商品管理のテスト */
    printf("=== 商品管理 ===\n");
    Product p1 = create_product(1001, "ノートパソコン", 98000.0, 5);
    Product p2 = create_product(1002, "マウス", 2980.0, 20);
    
    print_product(p1);
    printf("総価値: %.2f円\n\n", calculate_total_value(p1));
    
    print_product(p2);
    printf("総価値: %.2f円\n\n", calculate_total_value(p2));
    
    printf("価格比較: ");
    int cmp = compare_products_by_price(p1, p2);
    if (cmp > 0)
    {
        printf("商品1の方が高い\n");
    }
    else if (cmp < 0)
    {
        printf("商品2の方が高い\n");
    }
    else
    {
        printf("同じ価格\n");
    }
    
    printf("\n商品1に20%%割引を適用\n");
    apply_discount(&p1, 20.0);
    print_product(p1);
    printf("\n");
    
    /* 学生管理のテスト */
    printf("=== 学生管理 ===\n");
    Student students[] = {
        create_student(2001, "田中太郎", 85.5),
        create_student(2002, "鈴木花子", 92.0),
        create_student(2003, "佐藤次郎", 78.3),
        create_student(2004, "山田美咲", 88.5)
    };
    int student_count = 4;
    
    int i;
    printf("学生一覧:\n");
    for (i = 0; i < student_count; i++)
    {
        printf("--- 学生%d ---\n", i + 1);
        print_student(students[i]);
    }
    
    printf("\n最高得点者:\n");
    Student best = find_best_student(students, student_count);
    print_student(best);
    
    printf("\n得点順にソート後:\n");
    sort_students_by_score(students, student_count);
    for (i = 0; i < student_count; i++)
    {
        printf("%d位: %s (%.1f点)\n", i + 1, students[i].name, students[i].score);
    }
    printf("\n");
    
    /* 日付操作のテスト */
    printf("=== 日付操作 ===\n");
    Date d1 = create_date(2024, 3, 15);
    Date d2 = create_date(2024, 12, 25);
    Date d3 = create_date(2024, 2, 29);  /* うるう年 */
    Date d4 = create_date(2023, 2, 29);  /* 無効な日付 */
    
    printf("日付1: ");
    print_date(d1);
    printf(" (妥当性: %s)\n", is_valid_date(d1) ? "OK" : "NG");
    
    printf("日付2: ");
    print_date(d2);
    printf(" (妥当性: %s)\n", is_valid_date(d2) ? "OK" : "NG");
    
    printf("日付3: ");
    print_date(d3);
    printf(" (妥当性: %s)\n", is_valid_date(d3) ? "OK" : "NG");
    
    printf("日付4: ");
    print_date(d4);
    printf(" (妥当性: %s)\n", is_valid_date(d4) ? "OK" : "NG");
    
    printf("\n2024年はうるう年? %s\n", is_leap_year(2024) ? "はい" : "いいえ");
    printf("2023年はうるう年? %s\n", is_leap_year(2023) ? "はい" : "いいえ");
    
    printf("\n日付の比較:\n");
    int date_cmp = compare_dates(d1, d2);
    if (date_cmp < 0)
    {
        printf("日付1の方が早い\n");
    }
    else if (date_cmp > 0)
    {
        printf("日付2の方が早い\n");
    }
    else
    {
        printf("同じ日付\n");
    }
    printf("\n");
    
    /* 座標・図形のテスト */
    printf("=== 座標・図形 ===\n");
    Point p_1 = create_point(0.0, 0.0);
    Point p_2 = create_point(3.0, 4.0);
    Point p_3 = create_point(5.0, 5.0);
    
    printf("点1: (%.1f, %.1f)\n", p_1.x, p_1.y);
    printf("点2: (%.1f, %.1f)\n", p_2.x, p_2.y);
    printf("点1と点2の距離: %.2f\n", point_distance(p_1, p_2));
    
    Rectangle rect = create_rectangle(create_point(0.0, 10.0), create_point(10.0, 0.0));
    printf("\n矩形: 左上(%.1f, %.1f) - 右下(%.1f, %.1f)\n",
           rect.top_left.x, rect.top_left.y,
           rect.bottom_right.x, rect.bottom_right.y);
    printf("面積: %.2f\n", rectangle_area(rect));
    printf("周囲長: %.2f\n", rectangle_perimeter(rect));
    
    printf("\n点の位置判定:\n");
    printf("点2(%.1f, %.1f)は矩形内? %s\n", 
           p_2.x, p_2.y, point_in_rectangle(p_2, rect) ? "はい" : "いいえ");
    printf("点3(%.1f, %.1f)は矩形内? %s\n", 
           p_3.x, p_3.y, point_in_rectangle(p_3, rect) ? "はい" : "いいえ");
    
    return 0;
}