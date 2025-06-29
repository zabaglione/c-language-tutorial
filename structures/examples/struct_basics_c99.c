/*
 * struct_basics_c99.c - 構造体の基本操作（C99版）
 * 
 * C99の新機能：
 * - 指定イニシャライザ
 * - 複合リテラル
 * - bool型
 * - inline関数
 * - 変数宣言位置の自由化
 * - //コメント
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// 座標を表す構造体
struct Point {
    int x;
    int y;
};

// 学生情報を表す構造体
struct Student {
    int id;
    char name[50];
    int age;
    double gpa;
    bool is_active;  // C99: bool型
};

// 商品情報を表す構造体
struct Product {
    int code;
    char name[100];
    double price;
    int stock;
    bool in_stock;  // C99: bool型
};

// C99: inline関数による効率化
static inline void print_point(const struct Point *p)
{
    if (p != NULL) {
        printf("座標: (%d, %d)\n", p->x, p->y);
    }
}

// C99: inline関数で距離の二乗を計算
static inline int distance_squared(const struct Point *p1, const struct Point *p2)
{
    int dx = p1->x - p2->x;
    int dy = p1->y - p2->y;
    return dx * dx + dy * dy;
}

// 学生情報を表示する関数
void display_student(const struct Student *s)
{
    printf("=== 学生情報 ===\n");
    printf("ID: %d\n", s->id);
    printf("名前: %s\n", s->name);
    printf("年齢: %d歳\n", s->age);
    printf("GPA: %.2f\n", s->gpa);
    printf("在籍状況: %s\n", s->is_active ? "在籍中" : "休学中");
    printf("\n");
}

// 商品の在庫状態を更新
void update_product_status(struct Product *p)
{
    if (p != NULL) {
        p->in_stock = (p->stock > 0);
    }
}

int main(void)
{
    printf("===== 構造体の基本操作 (C99版) =====\n\n");
    
    // 1. C99: 指定イニシャライザ
    printf("1. 指定イニシャライザ\n");
    
    struct Point p1 = {.x = 10, .y = 20};  // メンバー名を指定
    struct Point p2 = {.y = 40, .x = 30};  // 順序は自由
    struct Point p3 = {.x = 50};           // 指定しないメンバーは0
    
    print_point(&p1);
    print_point(&p2);
    print_point(&p3);
    printf("\n");
    
    // 2. C99: 複合リテラル
    printf("2. 複合リテラル\n");
    
    // 一時的な構造体オブジェクトを作成
    print_point(&(struct Point){100, 200});
    
    // 配列の初期化での使用
    struct Point points[] = {
        (struct Point){.x = 10, .y = 10},
        (struct Point){.x = 20, .y = 20},
        (struct Point){.x = 30, .y = 30}
    };
    
    // C99: forループ内での変数宣言
    for (int i = 0; i < 3; i++) {
        printf("points[%d]: ", i);
        print_point(&points[i]);
    }
    printf("\n");
    
    // 3. 構造体と距離計算
    printf("3. 構造体と距離計算\n");
    struct Point origin = {0, 0};
    struct Point target = {3, 4};
    
    int dist_sq = distance_squared(&origin, &target);
    printf("原点から(%d, %d)への距離の二乗: %d\n", 
           target.x, target.y, dist_sq);
    printf("\n");
    
    // 4. C99: bool型を含む構造体
    printf("4. bool型を含む構造体\n");
    
    struct Student student = {
        .id = 1001,
        .name = "田中太郎",
        .age = 20,
        .gpa = 3.5,
        .is_active = true
    };
    
    display_student(&student);
    
    // 5. 構造体配列の高度な初期化
    printf("5. 構造体配列の高度な初期化\n");
    
    struct Product products[] = {
        {.code = 101, .name = "ノートPC", .price = 98000.0, .stock = 5},
        {.code = 102, .name = "マウス", .price = 2980.0, .stock = 0},
        {.code = 103, .name = "キーボード", .price = 4500.0, .stock = 15}
    };
    
    // 在庫状態を更新
    for (int i = 0; i < 3; i++) {
        update_product_status(&products[i]);
    }
    
    printf("=== 商品リスト ===\n");
    for (int i = 0; i < 3; i++) {
        printf("商品: %s, 価格: %.0f円, 在庫: %d, ",
               products[i].name, products[i].price, products[i].stock);
        printf("状態: %s\n", products[i].in_stock ? "在庫あり" : "在庫なし");
    }
    printf("\n");
    
    // 6. 関数引数での複合リテラル
    printf("6. 関数引数での複合リテラル\n");
    
    // 複合リテラルを直接関数に渡す
    struct Student temp_student = (struct Student){
        .id = 2001,
        .name = "佐藤花子",
        .age = 21,
        .gpa = 3.8,
        .is_active = false
    };
    display_student(&temp_student);
    
    // 7. 構造体の条件付き初期化
    printf("7. 構造体の条件付き初期化\n");
    
    bool use_default = false;
    struct Point dynamic_point = use_default ? 
        (struct Point){.x = 0, .y = 0} :     // デフォルト値
        (struct Point){.x = 100, .y = 100};  // カスタム値
    
    printf("動的に初期化された点: ");
    print_point(&dynamic_point);
    printf("\n");
    
    // 8. 構造体配列のフィルタリング
    printf("8. 構造体配列のフィルタリング\n");
    
    struct Student students[] = {
        {.id = 3001, .name = "山田太郎", .age = 19, .gpa = 3.2, .is_active = true},
        {.id = 3002, .name = "鈴木次郎", .age = 20, .gpa = 2.8, .is_active = true},
        {.id = 3003, .name = "高橋美咲", .age = 21, .gpa = 3.9, .is_active = false},
        {.id = 3004, .name = "伊藤健太", .age = 20, .gpa = 3.6, .is_active = true}
    };
    
    printf("=== GPA 3.5以上の在籍中の学生 ===\n");
    for (size_t i = 0; i < sizeof(students) / sizeof(students[0]); i++) {
        if (students[i].is_active && students[i].gpa >= 3.5) {
            printf("%s (GPA: %.1f)\n", students[i].name, students[i].gpa);
        }
    }
    
    return 0;
}

/*
実行結果例:
===== 構造体の基本操作 (C99版) =====

1. 指定イニシャライザ
座標: (10, 20)
座標: (30, 40)
座標: (50, 0)

2. 複合リテラル
座標: (100, 200)
points[0]: 座標: (10, 10)
points[1]: 座標: (20, 20)
points[2]: 座標: (30, 30)

3. 構造体と距離計算
原点から(3, 4)への距離の二乗: 25

4. bool型を含む構造体
=== 学生情報 ===
ID: 1001
名前: 田中太郎
年齢: 20歳
GPA: 3.50
在籍状況: 在籍中

5. 構造体配列の高度な初期化
=== 商品リスト ===
商品: ノートPC, 価格: 98000円, 在庫: 5, 状態: 在庫あり
商品: マウス, 価格: 2980円, 在庫: 0, 状態: 在庫なし
商品: キーボード, 価格: 4500円, 在庫: 15, 状態: 在庫あり

6. 関数引数での複合リテラル
=== 学生情報 ===
ID: 2001
名前: 佐藤花子
年齢: 21歳
GPA: 3.80
在籍状況: 休学中

7. 構造体の条件付き初期化
動的に初期化された点: 座標: (100, 100)

8. 構造体配列のフィルタリング
=== GPA 3.5以上の在籍中の学生 ===
伊藤健太 (GPA: 3.6)
*/
