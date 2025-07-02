/*
 * 演習11-6: 構造体を使った関数 - 解答例（C99版）
 * 
 * 構造体を引数や戻り値として使用する関数群を実装します。
 * C99の機能：//コメント、変数宣言位置の自由化、複合リテラル、designated initializer、可変長配列
 */
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

// 構造体定義
// 商品情報
typedef struct {
    int id;
    char name[50];
    double price;
    int stock;
} Product;

// 学生情報
typedef struct {
    int id;
    char name[50];
    double score;
    char grade;
} Student;

// 日付
typedef struct {
    int year;
    int month;
    int day;
} Date;

// 座標点
typedef struct {
    double x;
    double y;
} Point;

// 矩形
typedef struct {
    Point top_left;
    Point bottom_right;
} Rectangle;

// 統計情報（C99追加）
typedef struct {
    double mean;
    double median;
    double std_dev;
    double min;
    double max;
} Statistics;

// 関数プロトタイプ
// 商品管理関数
Product create_product(int id, const char *name, double price, int stock);
void print_product(const Product *p);  // C99: constポインタ
double calculate_total_value(const Product *p);
int compare_products_by_price(const Product *p1, const Product *p2);
void update_stock(Product *p, int quantity);
void apply_discount(Product *p, double discount_percent);
Product* find_most_valuable_product(Product products[], int count);

// 学生管理関数
Student create_student(int id, const char *name, double score);
void print_student(const Student *s);
void update_score(Student *s, double new_score);
char calculate_grade(double score);
Student find_best_student(const Student students[], int count);
void sort_students_by_score(Student students[], int count);
Statistics calculate_class_statistics(const Student students[], int count);

// 日付操作関数
Date create_date(int year, int month, int day);
void print_date(const Date *d);
bool is_valid_date(const Date *d);  // C99: bool型
bool is_leap_year(int year);
int days_in_month(int year, int month);
int date_difference(const Date *d1, const Date *d2);
int compare_dates(const Date *d1, const Date *d2);

// 座標・図形関数
Point create_point(double x, double y);
double point_distance(const Point *p1, const Point *p2);
Rectangle create_rectangle(Point top_left, Point bottom_right);
double rectangle_area(const Rectangle *r);
double rectangle_perimeter(const Rectangle *r);
bool point_in_rectangle(const Point *p, const Rectangle *r);
bool rectangles_overlap(const Rectangle *r1, const Rectangle *r2);

// 商品を作成する関数
Product create_product(int id, const char *name, double price, int stock)
{
    // C99: designated initializer
    Product p = {
        .id = id,
        .price = price,
        .stock = stock
    };
    
    strncpy(p.name, name, sizeof(p.name) - 1);
    p.name[sizeof(p.name) - 1] = '\0';
    
    return p;
}

// 商品情報を表示する関数
void print_product(const Product *p)
{
    if (p == NULL) return;
    
    printf("商品ID: %d\n", p->id);
    printf("商品名: %s\n", p->name);
    printf("価格: %.2f円\n", p->price);
    printf("在庫: %d個\n", p->stock);
}

// 商品の総価値を計算する関数
double calculate_total_value(const Product *p)
{
    return p ? p->price * p->stock : 0.0;
}

// 商品を価格で比較する関数
int compare_products_by_price(const Product *p1, const Product *p2)
{
    if (p1 == NULL || p2 == NULL) return 0;
    
    if (p1->price < p2->price) return -1;
    if (p1->price > p2->price) return 1;
    return 0;
}

// 在庫を更新する関数
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

// 割引を適用する関数
void apply_discount(Product *p, double discount_percent)
{
    if (p != NULL && discount_percent >= 0.0 && discount_percent <= 100.0)
    {
        p->price *= (1.0 - discount_percent / 100.0);
    }
}

// 最も価値の高い商品を見つける関数（C99追加）
Product* find_most_valuable_product(Product products[], int count)
{
    if (products == NULL || count <= 0) return NULL;
    
    Product *most_valuable = &products[0];
    double max_value = calculate_total_value(most_valuable);
    
    for (int i = 1; i < count; i++)  // C99: forループ内で変数宣言
    {
        double value = calculate_total_value(&products[i]);
        if (value > max_value)
        {
            max_value = value;
            most_valuable = &products[i];
        }
    }
    
    return most_valuable;
}

// 学生を作成する関数
Student create_student(int id, const char *name, double score)
{
    // C99: designated initializer
    Student s = {
        .id = id,
        .score = score,
        .grade = calculate_grade(score)
    };
    
    strncpy(s.name, name, sizeof(s.name) - 1);
    s.name[sizeof(s.name) - 1] = '\0';
    
    return s;
}

// 学生情報を表示する関数
void print_student(const Student *s)
{
    if (s == NULL) return;
    
    printf("学生ID: %d\n", s->id);
    printf("氏名: %s\n", s->name);
    printf("得点: %.1f点\n", s->score);
    printf("成績: %c\n", s->grade);
}

// 学生の成績を更新する関数
void update_score(Student *s, double new_score)
{
    if (s != NULL && new_score >= 0.0 && new_score <= 100.0)
    {
        s->score = new_score;
        s->grade = calculate_grade(new_score);
    }
}

// 得点から成績を計算する関数
char calculate_grade(double score)
{
    if (score >= 90.0) return 'A';
    if (score >= 80.0) return 'B';
    if (score >= 70.0) return 'C';
    if (score >= 60.0) return 'D';
    return 'F';
}

// 学生配列から最高得点者を見つける関数
Student find_best_student(const Student students[], int count)
{
    Student best = students[0];
    
    for (int i = 1; i < count; i++)  // C99: forループ内で変数宣言
    {
        if (students[i].score > best.score)
        {
            best = students[i];
        }
    }
    
    return best;
}

// 学生を得点順にソートする関数
void sort_students_by_score(Student students[], int count)
{
    // C99: 改良版バブルソート
    bool swapped;
    
    for (int i = 0; i < count - 1; i++)
    {
        swapped = false;
        
        for (int j = 0; j < count - 1 - i; j++)
        {
            if (students[j].score < students[j + 1].score)
            {
                Student temp = students[j];  // C99: 使用箇所で変数宣言
                students[j] = students[j + 1];
                students[j + 1] = temp;
                swapped = true;
            }
        }
        
        if (!swapped) break;  // 既にソート済み
    }
}

// クラスの統計を計算する関数（C99追加）
Statistics calculate_class_statistics(const Student students[], int count)
{
    if (students == NULL || count <= 0)
    {
        return (Statistics){0};  // C99: 複合リテラル
    }
    
    // 可変長配列を使用
    double scores[count];  // C99: 可変長配列
    
    double sum = 0.0;
    double min = students[0].score;
    double max = students[0].score;
    
    // データを収集
    for (int i = 0; i < count; i++)
    {
        scores[i] = students[i].score;
        sum += scores[i];
        
        if (scores[i] < min) min = scores[i];
        if (scores[i] > max) max = scores[i];
    }
    
    double mean = sum / count;
    
    // 標準偏差を計算
    double variance = 0.0;
    for (int i = 0; i < count; i++)
    {
        double diff = scores[i] - mean;
        variance += diff * diff;
    }
    variance /= count;
    double std_dev = sqrt(variance);
    
    // 中央値を計算（簡易版）
    double median = (min + max) / 2.0;
    
    return (Statistics){
        .mean = mean,
        .median = median,
        .std_dev = std_dev,
        .min = min,
        .max = max
    };  // C99: designated initializer
}

// 日付を作成する関数
Date create_date(int year, int month, int day)
{
    // C99: designated initializer
    return (Date){
        .year = year,
        .month = month,
        .day = day
    };
}

// 日付を表示する関数
void print_date(const Date *d)
{
    if (d == NULL) return;
    printf("%04d年%02d月%02d日", d->year, d->month, d->day);
}

// 日付の妥当性をチェックする関数
bool is_valid_date(const Date *d)  // C99: bool型
{
    if (d == NULL) return false;
    
    if (d->year < 1 || d->year > 9999)
    {
        return false;
    }
    
    if (d->month < 1 || d->month > 12)
    {
        return false;
    }
    
    if (d->day < 1 || d->day > days_in_month(d->year, d->month))
    {
        return false;
    }
    
    return true;
}

// うるう年かどうかを判定する関数
bool is_leap_year(int year)  // C99: bool型
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// 月の日数を返す関数
int days_in_month(int year, int month)
{
    const int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};  // C99: const配列
    
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

// 2つの日付の差を計算する関数（簡易版）
int date_difference(const Date *d1, const Date *d2)
{
    if (d1 == NULL || d2 == NULL) return 0;
    
    // より正確な実装には、各月の日数を考慮した計算が必要
    int days1 = d1->year * 365 + d1->month * 30 + d1->day;
    int days2 = d2->year * 365 + d2->month * 30 + d2->day;
    
    return days1 - days2;
}

// 日付を比較する関数
int compare_dates(const Date *d1, const Date *d2)
{
    if (d1 == NULL || d2 == NULL) return 0;
    
    if (d1->year != d2->year)
    {
        return d1->year - d2->year;
    }
    
    if (d1->month != d2->month)
    {
        return d1->month - d2->month;
    }
    
    return d1->day - d2->day;
}

// 点を作成する関数
Point create_point(double x, double y)
{
    return (Point){.x = x, .y = y};  // C99: designated initializer
}

// 2点間の距離を計算する関数
double point_distance(const Point *p1, const Point *p2)
{
    if (p1 == NULL || p2 == NULL) return 0.0;
    
    double dx = p2->x - p1->x;
    double dy = p2->y - p1->y;
    return sqrt(dx * dx + dy * dy);  // 互換性のためsqrtを使用
}

// 矩形を作成する関数
Rectangle create_rectangle(Point top_left, Point bottom_right)
{
    return (Rectangle){
        .top_left = top_left,
        .bottom_right = bottom_right
    };  // C99: designated initializer
}

// 矩形の面積を計算する関数
double rectangle_area(const Rectangle *r)
{
    if (r == NULL) return 0.0;
    
    double width = r->bottom_right.x - r->top_left.x;
    double height = r->top_left.y - r->bottom_right.y;
    return fabs(width * height);
}

// 矩形の周囲長を計算する関数
double rectangle_perimeter(const Rectangle *r)
{
    if (r == NULL) return 0.0;
    
    double width = fabs(r->bottom_right.x - r->top_left.x);
    double height = fabs(r->top_left.y - r->bottom_right.y);
    return 2.0 * (width + height);
}

// 点が矩形内にあるかを判定する関数
bool point_in_rectangle(const Point *p, const Rectangle *r)  // C99: bool型
{
    if (p == NULL || r == NULL) return false;
    
    return p->x >= r->top_left.x && p->x <= r->bottom_right.x &&
           p->y <= r->top_left.y && p->y >= r->bottom_right.y;
}

// 2つの矩形が重なるかを判定する関数（C99追加）
bool rectangles_overlap(const Rectangle *r1, const Rectangle *r2)
{
    if (r1 == NULL || r2 == NULL) return false;
    
    // どちらかが他方の完全に左、右、上、下にある場合は重ならない
    if (r1->bottom_right.x < r2->top_left.x ||
        r2->bottom_right.x < r1->top_left.x ||
        r1->bottom_right.y > r2->top_left.y ||
        r2->bottom_right.y > r1->top_left.y)
    {
        return false;
    }
    
    return true;
}

// メイン関数 - テスト用
int main(void)
{
    printf("=== 構造体を使った関数のテスト（C99版） ===\n\n");
    
    // 商品管理のテスト
    printf("=== 商品管理 ===\n");
    
    // C99: 複合リテラルを使った初期化
    Product products[] = {
        create_product(1001, "ノートパソコン", 98000.0, 5),
        create_product(1002, "マウス", 2980.0, 20),
        create_product(1003, "キーボード", 5800.0, 15),
        (Product){.id = 1004, .name = "モニター", .price = 45000.0, .stock = 3}
    };
    int product_count = sizeof(products) / sizeof(products[0]);
    
    for (int i = 0; i < product_count; i++)  // C99: forループ内で変数宣言
    {
        printf("--- 商品%d ---\n", i + 1);
        print_product(&products[i]);
        printf("総価値: %.2f円\n\n", calculate_total_value(&products[i]));
    }
    
    Product *most_valuable = find_most_valuable_product(products, product_count);
    printf("最も価値の高い商品:\n");
    print_product(most_valuable);
    printf("\n");
    
    // 学生管理のテスト
    printf("=== 学生管理 ===\n");
    Student students[] = {
        create_student(2001, "田中太郎", 85.5),
        create_student(2002, "鈴木花子", 92.0),
        create_student(2003, "佐藤次郎", 78.3),
        create_student(2004, "山田美咲", 88.5)
    };
    int student_count = sizeof(students) / sizeof(students[0]);
    
    printf("学生一覧:\n");
    for (int i = 0; i < student_count; i++)
    {
        printf("--- 学生%d ---\n", i + 1);
        print_student(&students[i]);
    }
    
    // クラス統計
    Statistics stats = calculate_class_statistics(students, student_count);
    printf("\n=== クラス統計 ===\n");
    printf("平均点: %.2f\n", stats.mean);
    printf("中央値: %.2f\n", stats.median);
    printf("標準偏差: %.2f\n", stats.std_dev);
    printf("最低点: %.2f\n", stats.min);
    printf("最高点: %.2f\n", stats.max);
    
    printf("\n得点順にソート後:\n");
    sort_students_by_score(students, student_count);
    for (int i = 0; i < student_count; i++)
    {
        printf("%d位: %s (%.1f点)\n", i + 1, students[i].name, students[i].score);
    }
    printf("\n");
    
    // 日付操作のテスト
    printf("=== 日付操作 ===\n");
    Date dates[] = {
        create_date(2024, 3, 15),
        create_date(2024, 12, 25),
        create_date(2024, 2, 29),  // うるう年
        create_date(2023, 2, 29)   // 無効な日付
    };
    
    for (int i = 0; i < 4; i++)
    {
        printf("日付%d: ", i + 1);
        print_date(&dates[i]);
        printf(" (妥当性: %s)\n", is_valid_date(&dates[i]) ? "OK" : "NG");
    }
    
    printf("\n2024年はうるう年? %s\n", is_leap_year(2024) ? "はい" : "いいえ");
    printf("2023年はうるう年? %s\n", is_leap_year(2023) ? "はい" : "いいえ");
    printf("\n");
    
    // 座標・図形のテスト
    printf("=== 座標・図形 ===\n");
    
    // C99: 複合リテラルで点を作成
    Point points[] = {
        create_point(0.0, 0.0),
        create_point(3.0, 4.0),
        create_point(5.0, 5.0),
        (Point){.x = 15.0, .y = 8.0}
    };
    
    printf("点の距離計算:\n");
    for (int i = 0; i < 3; i++)
    {
        for (int j = i + 1; j < 4; j++)
        {
            printf("点%dと点%dの距離: %.2f\n", 
                   i + 1, j + 1, 
                   point_distance(&points[i], &points[j]));
        }
    }
    
    Rectangle rect1 = create_rectangle(create_point(0.0, 10.0), create_point(10.0, 0.0));
    Rectangle rect2 = create_rectangle(create_point(5.0, 15.0), create_point(15.0, 5.0));
    
    printf("\n矩形1: 左上(%.1f, %.1f) - 右下(%.1f, %.1f)\n",
           rect1.top_left.x, rect1.top_left.y,
           rect1.bottom_right.x, rect1.bottom_right.y);
    printf("面積: %.2f, 周囲長: %.2f\n", 
           rectangle_area(&rect1), rectangle_perimeter(&rect1));
    
    printf("\n矩形2: 左上(%.1f, %.1f) - 右下(%.1f, %.1f)\n",
           rect2.top_left.x, rect2.top_left.y,
           rect2.bottom_right.x, rect2.bottom_right.y);
    printf("面積: %.2f, 周囲長: %.2f\n", 
           rectangle_area(&rect2), rectangle_perimeter(&rect2));
    
    printf("\n矩形1と矩形2は重なる? %s\n", 
           rectangles_overlap(&rect1, &rect2) ? "はい" : "いいえ");
    
    printf("\n点の位置判定:\n");
    for (int i = 0; i < 4; i++)
    {
        printf("点%d(%.1f, %.1f)は矩形1内? %s\n", 
               i + 1, points[i].x, points[i].y, 
               point_in_rectangle(&points[i], &rect1) ? "はい" : "いいえ");
    }
    
    return 0;
}