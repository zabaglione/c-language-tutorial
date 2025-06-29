/*
 * struct_basics.c - 構造体の基本操作
 * 
 * このプログラムでは以下を学習します：
 * - 構造体の定義方法
 * - 構造体変数の宣言と初期化
 * - 構造体メンバーへのアクセス
 * - 構造体の関数への渡し方
 */

#include <stdio.h>
#include <string.h>

/* 座標を表す構造体 */
struct Point {
    int x;
    int y;
};

/* 学生情報を表す構造体 */
struct Student {
    int id;
    char name[50];
    int age;
    double gpa;
};

/* 商品情報を表す構造体 */
struct Product {
    int code;
    char name[100];
    double price;
    int stock;
};

/* 構造体を値渡しで受け取る関数 */
void print_point_by_value(struct Point p)
{
    printf("座標: (%d, %d)\n", p.x, p.y);
}

/* 構造体をポインタ渡しで受け取る関数 */
void print_point_by_pointer(struct Point *p)
{
    if (p != NULL) {
        printf("座標: (%d, %d)\n", p->x, p->y);
    }
}

/* 学生情報を表示する関数 */
void display_student(struct Student s)
{
    printf("=== 学生情報 ===\n");
    printf("ID: %d\n", s.id);
    printf("名前: %s\n", s.name);
    printf("年齢: %d歳\n", s.age);
    printf("GPA: %.2f\n", s.gpa);
    printf("\n");
}

/* 商品情報を更新する関数（ポインタ使用） */
void update_stock(struct Product *p, int quantity)
{
    if (p != NULL) {
        p->stock += quantity;
        if (quantity > 0) {
            printf("%s の在庫を %d 個追加しました。現在の在庫: %d\n", 
                   p->name, quantity, p->stock);
        } else {
            printf("%s の在庫を %d 個減らしました。現在の在庫: %d\n", 
                   p->name, -quantity, p->stock);
        }
    }
}

int main(void)
{
    printf("===== 構造体の基本操作 =====\n\n");
    
    /* 1. 構造体の宣言と初期化 */
    printf("1. 構造体の宣言と初期化\n");
    
    /* 方法1: 宣言後に個別に代入 */
    struct Point p1;
    p1.x = 10;
    p1.y = 20;
    
    /* 方法2: 初期化リストを使用 */
    struct Point p2 = {30, 40};
    
    /* 方法3: 部分的な初期化（残りは0） */
    struct Point p3 = {50};  /* y は 0 になる */
    
    printf("p1: (%d, %d)\n", p1.x, p1.y);
    printf("p2: (%d, %d)\n", p2.x, p2.y);
    printf("p3: (%d, %d)\n", p3.x, p3.y);
    printf("\n");
    
    /* 2. 構造体のコピー */
    printf("2. 構造体のコピー\n");
    struct Point p4 = p1;  /* 構造体全体のコピー */
    p4.x = 100;  /* p4を変更してもp1は影響を受けない */
    
    printf("p1（元）: (%d, %d)\n", p1.x, p1.y);
    printf("p4（コピー後変更）: (%d, %d)\n", p4.x, p4.y);
    printf("\n");
    
    /* 3. 構造体と関数 */
    printf("3. 構造体と関数\n");
    print_point_by_value(p1);     /* 値渡し */
    print_point_by_pointer(&p2);  /* ポインタ渡し */
    printf("\n");
    
    /* 4. 文字列を含む構造体 */
    printf("4. 文字列を含む構造体\n");
    struct Student student1;
    student1.id = 1001;
    strcpy(student1.name, "田中太郎");
    student1.age = 20;
    student1.gpa = 3.5;
    
    display_student(student1);
    
    /* 5. 構造体の配列 */
    printf("5. 構造体の配列\n");
    struct Product products[3] = {
        {101, "ノートPC", 98000.0, 5},
        {102, "マウス", 2980.0, 20},
        {103, "キーボード", 4500.0, 15}
    };
    
    int i;
    printf("=== 商品リスト ===\n");
    for (i = 0; i < 3; i++) {
        printf("商品コード: %d, 名前: %s, 価格: %.0f円, 在庫: %d\n",
               products[i].code, products[i].name, 
               products[i].price, products[i].stock);
    }
    printf("\n");
    
    /* 6. 構造体ポインタの使用 */
    printf("6. 構造体ポインタの使用\n");
    struct Product *prod_ptr = &products[0];
    
    /* アロー演算子でメンバーアクセス */
    printf("ポインタ経由でアクセス: %s (%.0f円)\n", 
           prod_ptr->name, prod_ptr->price);
    
    /* 在庫の更新 */
    update_stock(prod_ptr, 3);
    update_stock(&products[1], -5);
    printf("\n");
    
    /* 7. 構造体のサイズ */
    printf("7. 構造体のサイズ\n");
    printf("sizeof(struct Point): %lu バイト\n", sizeof(struct Point));
    printf("sizeof(struct Student): %lu バイト\n", sizeof(struct Student));
    printf("sizeof(struct Product): %lu バイト\n", sizeof(struct Product));
    printf("\n");
    
    /* 8. ネストした構造体 */
    printf("8. ネストした構造体\n");
    struct Rectangle {
        struct Point top_left;
        struct Point bottom_right;
    };
    
    struct Rectangle rect = {{0, 0}, {100, 50}};
    printf("矩形: 左上(%d, %d) - 右下(%d, %d)\n",
           rect.top_left.x, rect.top_left.y,
           rect.bottom_right.x, rect.bottom_right.y);
    
    /* 矩形の幅と高さを計算 */
    int width = rect.bottom_right.x - rect.top_left.x;
    int height = rect.bottom_right.y - rect.top_left.y;
    printf("幅: %d, 高さ: %d, 面積: %d\n", width, height, width * height);
    
    return 0;
}

/*
実行結果例:
===== 構造体の基本操作 =====

1. 構造体の宣言と初期化
p1: (10, 20)
p2: (30, 40)
p3: (50, 0)

2. 構造体のコピー
p1（元）: (10, 20)
p4（コピー後変更）: (100, 20)

3. 構造体と関数
座標: (10, 20)
座標: (30, 40)

4. 文字列を含む構造体
=== 学生情報 ===
ID: 1001
名前: 田中太郎
年齢: 20歳
GPA: 3.50

5. 構造体の配列
=== 商品リスト ===
商品コード: 101, 名前: ノートPC, 価格: 98000円, 在庫: 5
商品コード: 102, 名前: マウス, 価格: 2980円, 在庫: 20
商品コード: 103, 名前: キーボード, 価格: 4500円, 在庫: 15

6. 構造体ポインタの使用
ポインタ経由でアクセス: ノートPC (98000円)
ノートPC の在庫を 3 個追加しました。現在の在庫: 8
マウス の在庫を 5 個減らしました。現在の在庫: 15

7. 構造体のサイズ
sizeof(struct Point): 8 バイト
sizeof(struct Student): 72 バイト
sizeof(struct Product): 120 バイト

8. ネストした構造体
矩形: 左上(0, 0) - 右下(100, 50)
幅: 100, 高さ: 50, 面積: 5000
*/
