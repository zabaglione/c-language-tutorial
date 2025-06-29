# 構造体

## 対応C規格
- **主要対象:** C90
- **学習内容:** 構造体の基本、構造体ポインタ、構造体配列、->演算子、メモリ管理

## 学習目標

この章を完了すると、以下のことができるようになります：

- 構造体の基本概念を理解する
- 構造体ポインタを効果的に使える
- ->演算子と.演算子の使い分けができる
- 構造体配列とポインタ配列を活用できる
- 構造体を使ったデータ管理ができる

## 理論解説

### 構造体の基本概念

構造体は異なるデータ型を組み合わせて新しいデータ型を作る仕組みです。

#### 構造体の定義と宣言

```c
#include <stdio.h>
#include <string.h>

/* 学生情報を表す構造体 */
struct Student {
    int id;
    char name[50];
    int age;
    double gpa;
};

int main(void)
{
    struct Student student;
    
    /* メンバーに値を代入 */
    student.id = 1001;
    strcpy(student.name, "田中太郎");
    student.age = 20;
    student.gpa = 3.5;
    
    /* メンバーの値を表示 */
    printf("学生ID: %d\n", student.id);
    printf("名前: %s\n", student.name);
    printf("年齢: %d\n", student.age);
    printf("GPA: %.1f\n", student.gpa);
    
    return 0;
}
```

#### 構造体の初期化

```c
#include <stdio.h>

struct Point {
    int x;
    int y;
};

struct Rectangle {
    struct Point top_left;
    struct Point bottom_right;
};

int main(void)
{
    /* 初期化方法1: 順序指定 */
    struct Point p1 = {10, 20};
    
    /* 初期化方法2: 部分初期化 */
    struct Point p2 = {5};  /* x=5, y=0 */
    
    /* 初期化方法3: ネストした構造体 */
    struct Rectangle rect = {{0, 0}, {100, 50}};
    
    /* 初期化方法4: 個別代入 */
    struct Point p3;
    p3.x = 30;
    p3.y = 40;
    
    printf("p1: (%d, %d)\n", p1.x, p1.y);
    printf("p2: (%d, %d)\n", p2.x, p2.y);
    printf("p3: (%d, %d)\n", p3.x, p3.y);
    printf("矩形: (%d,%d) から (%d,%d)\n", 
           rect.top_left.x, rect.top_left.y,
           rect.bottom_right.x, rect.bottom_right.y);
    
    return 0;
}
```

### 構造体ポインタの基本

構造体もポインタで操作できます。大きな構造体を関数に渡す際に効率的です。

#### 構造体ポインタの宣言と使用

```c
#include <stdio.h>
#include <string.h>

struct Book {
    char title[100];
    char author[50];
    int pages;
    double price;
};

int main(void)
{
    struct Book book;
    struct Book *book_ptr;
    
    /* 構造体ポインタを構造体のアドレスに設定 */
    book_ptr = &book;
    
    /* ポインタを通じてメンバーにアクセス（方法1: (*ptr).member） */
    strcpy((*book_ptr).title, "C言語入門");
    strcpy((*book_ptr).author, "山田花子");
    (*book_ptr).pages = 350;
    (*book_ptr).price = 2800.0;
    
    /* 直接アクセスとポインタアクセスの比較 */
    printf("=== 直接アクセス ===\n");
    printf("書名: %s\n", book.title);
    printf("著者: %s\n", book.author);
    printf("ページ数: %d\n", book.pages);
    printf("価格: %.0f円\n", book.price);
    
    printf("\n=== ポインタアクセス ===\n");
    printf("書名: %s\n", (*book_ptr).title);
    printf("著者: %s\n", (*book_ptr).author);
    printf("ページ数: %d\n", (*book_ptr).pages);
    printf("価格: %.0f円\n", (*book_ptr).price);
    
    return 0;
}
```

### アロー演算子（->）の使用

構造体ポインタには便利なアロー演算子（->）が用意されています。

#### ->演算子と.演算子の比較

```c
#include <stdio.h>
#include <string.h>

struct Employee {
    int id;
    char name[50];
    char department[30];
    double salary;
};

void print_employee_info(struct Employee *emp)
{
    printf("=== 社員情報 ===\n");
    printf("ID: %d\n", emp->id);           /* emp->id は (*emp).id と同じ */
    printf("名前: %s\n", emp->name);       /* emp->name は (*emp).name と同じ */
    printf("部署: %s\n", emp->department); /* emp->department は (*emp).department と同じ */
    printf("給与: %.0f円\n", emp->salary); /* emp->salary は (*emp).salary と同じ */
}

int main(void)
{
    struct Employee emp;
    struct Employee *emp_ptr = &emp;
    
    /* ->演算子を使用してメンバーに値を設定 */
    emp_ptr->id = 2001;
    strcpy(emp_ptr->name, "佐藤次郎");
    strcpy(emp_ptr->department, "開発部");
    emp_ptr->salary = 350000.0;
    
    /* 3つの方法でアクセス */
    printf("=== 直接アクセス（.演算子） ===\n");
    printf("ID: %d\n", emp.id);
    
    printf("\n=== ポインタ経由（(*ptr).member） ===\n");
    printf("ID: %d\n", (*emp_ptr).id);
    
    printf("\n=== ポインタ経由（->演算子） ===\n");
    printf("ID: %d\n", emp_ptr->id);
    
    printf("\n");
    print_employee_info(emp_ptr);
    
    return 0;
}
```

#### ->演算子の実践例

```c
#include <stdio.h>
#include <string.h>

struct Car {
    char brand[30];
    char model[30];
    int year;
    double mileage;
    int is_electric;
};

/* 車の情報を更新する関数 */
void update_mileage(struct Car *car, double new_mileage)
{
    if (car != NULL && new_mileage >= car->mileage) {
        car->mileage = new_mileage;
        printf("%s %s の走行距離を %.1f km に更新しました\n", 
               car->brand, car->model, car->mileage);
    }
}

/* 車の詳細情報を表示する関数 */
void display_car_details(struct Car *car)
{
    if (car == NULL) {
        printf("無効な車両データです\n");
        return;
    }
    
    printf("=== 車両情報 ===\n");
    printf("ブランド: %s\n", car->brand);
    printf("モデル: %s\n", car->model);
    printf("年式: %d年\n", car->year);
    printf("走行距離: %.1f km\n", car->mileage);
    printf("電気自動車: %s\n", car->is_electric ? "はい" : "いいえ");
    printf("\n");
}

int main(void)
{
    struct Car my_car;
    struct Car *car_ptr = &my_car;
    
    /* ->演算子で車の初期設定 */
    strcpy(car_ptr->brand, "Toyota");
    strcpy(car_ptr->model, "Prius");
    car_ptr->year = 2020;
    car_ptr->mileage = 15000.0;
    car_ptr->is_electric = 0;  /* ハイブリッド車 */
    
    display_car_details(car_ptr);
    
    /* 走行距離を更新 */
    update_mileage(car_ptr, 18500.0);
    
    display_car_details(car_ptr);
    
    return 0;
}
```

### 構造体配列とポインタ

構造体の配列とそのポインタ操作について学習します。

#### 構造体配列の基本操作

```c
#include <stdio.h>
#include <string.h>

struct Product {
    int code;
    char name[50];
    double price;
    int stock;
};

void print_product(struct Product *prod)
{
    printf("商品コード: %d\n", prod->code);
    printf("商品名: %s\n", prod->name);
    printf("価格: %.0f円\n", prod->price);
    printf("在庫: %d個\n", prod->stock);
    printf("---\n");
}

void print_all_products(struct Product products[], int count)
{
    int i;
    printf("=== 全商品リスト ===\n");
    for (i = 0; i < count; i++) {
        print_product(&products[i]);  /* 配列要素のアドレスを渡す */
    }
}

int main(void)
{
    struct Product inventory[3];
    int i;
    
    /* 商品データの初期化 */
    inventory[0] = (struct Product){101, "ノートPC", 98000, 5};
    
    strcpy(inventory[1].name, "マウス");
    inventory[1].code = 102;
    inventory[1].price = 2980;
    inventory[1].stock = 20;
    
    inventory[2].code = 103;
    strcpy(inventory[2].name, "キーボード");
    inventory[2].price = 4500;
    inventory[2].stock = 15;
    
    print_all_products(inventory, 3);
    
    /* ポインタを使った配列操作 */
    printf("\n=== ポインタを使った操作 ===\n");
    struct Product *ptr = inventory;  /* 配列の先頭要素を指す */
    
    for (i = 0; i < 3; i++) {
        printf("%d番目: %s (%.0f円)\n", 
               i + 1, (ptr + i)->name, (ptr + i)->price);
    }
    
    return 0;
}
```

#### ポインタ演算による構造体配列操作

```c
#include <stdio.h>
#include <string.h>

struct Score {
    char subject[30];
    int points;
    char grade;
};

/* 成績を計算してグレードを設定 */
void calculate_grade(struct Score *score)
{
    if (score->points >= 90) {
        score->grade = 'A';
    } else if (score->points >= 80) {
        score->grade = 'B';
    } else if (score->points >= 70) {
        score->grade = 'C';
    } else if (score->points >= 60) {
        score->grade = 'D';
    } else {
        score->grade = 'F';
    }
}

/* 配列内の最高得点を見つける */
struct Score* find_best_score(struct Score scores[], int count)
{
    struct Score *best = &scores[0];
    int i;
    
    for (i = 1; i < count; i++) {
        if (scores[i].points > best->points) {
            best = &scores[i];
        }
    }
    
    return best;
}

int main(void)
{
    struct Score my_scores[4];
    struct Score *ptr;
    struct Score *best;
    int i;
    
    /* 成績データの入力 */
    strcpy(my_scores[0].subject, "数学");
    my_scores[0].points = 85;
    
    strcpy(my_scores[1].subject, "英語");
    my_scores[1].points = 92;
    
    strcpy(my_scores[2].subject, "理科");
    my_scores[2].points = 78;
    
    strcpy(my_scores[3].subject, "社会");
    my_scores[3].points = 88;
    
    /* 各科目のグレードを計算 */
    ptr = my_scores;  /* 配列の先頭を指すポインタ */
    for (i = 0; i < 4; i++) {
        calculate_grade(ptr + i);  /* ポインタ演算でi番目の要素 */
    }
    
    /* 結果表示 */
    printf("=== 成績表 ===\n");
    for (i = 0; i < 4; i++) {
        printf("%s: %d点 (評価: %c)\n", 
               my_scores[i].subject, 
               my_scores[i].points, 
               my_scores[i].grade);
    }
    
    /* 最高得点の科目を見つける */
    best = find_best_score(my_scores, 4);
    printf("\n最高得点: %s (%d点)\n", best->subject, best->points);
    
    return 0;
}
```

### 構造体ポインタ配列

ポインタの配列で複数の構造体を効率的に管理します。

#### 構造体ポインタ配列の基本

```c
#include <stdio.h>
#include <string.h>

struct Person {
    char name[50];
    int age;
    char city[30];
};

void print_person_info(struct Person *person)
{
    printf("名前: %s, 年齢: %d歳, 居住地: %s\n", 
           person->name, person->age, person->city);
}

int main(void)
{
    /* 個別の構造体変数 */
    struct Person person1 = {"山田太郎", 25, "東京"};
    struct Person person2 = {"佐藤花子", 30, "大阪"};
    struct Person person3 = {"田中次郎", 28, "名古屋"};
    struct Person person4 = {"鈴木美咲", 22, "福岡"};
    
    /* 構造体ポインタの配列 */
    struct Person *people[4];
    int i;
    
    /* ポインタ配列に各構造体のアドレスを設定 */
    people[0] = &person1;
    people[1] = &person2;
    people[2] = &person3;
    people[3] = &person4;
    
    printf("=== 全員の情報 ===\n");
    for (i = 0; i < 4; i++) {
        printf("%d. ", i + 1);
        print_person_info(people[i]);
    }
    
    /* 特定の条件で検索 */
    printf("\n=== 25歳未満の人 ===\n");
    for (i = 0; i < 4; i++) {
        if (people[i]->age < 25) {
            print_person_info(people[i]);
        }
    }
    
    return 0;
}
```

#### 動的な構造体ポインタ配列

```c
#include <stdio.h>
#include <string.h>

struct Student {
    int id;
    char name[50];
    double gpa;
};

/* 学生データを作成する関数 */
struct Student create_student(int id, const char* name, double gpa)
{
    struct Student student;
    student.id = id;
    strcpy(student.name, name);
    student.gpa = gpa;
    return student;
}

/* GPA順でソート（バブルソート） */
void sort_students_by_gpa(struct Student *students[], int count)
{
    int i, j;
    struct Student *temp;
    
    for (i = 0; i < count - 1; i++) {
        for (j = 0; j < count - 1 - i; j++) {
            if (students[j]->gpa < students[j + 1]->gpa) {
                temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}

/* 学生一覧を表示 */
void display_students(struct Student *students[], int count)
{
    int i;
    printf("ID\t名前\t\tGPA\n");
    printf("------------------------\n");
    for (i = 0; i < count; i++) {
        printf("%d\t%s\t\t%.1f\n", 
               students[i]->id, 
               students[i]->name, 
               students[i]->gpa);
    }
    printf("\n");
}

int main(void)
{
    /* 学生データの作成 */
    struct Student student1 = create_student(1001, "田中太郎", 3.2);
    struct Student student2 = create_student(1002, "佐藤花子", 3.8);
    struct Student student3 = create_student(1003, "山田次郎", 2.9);
    struct Student student4 = create_student(1004, "鈴木美咲", 3.5);
    struct Student student5 = create_student(1005, "高橋健太", 3.1);
    
    /* 構造体ポインタ配列 */
    struct Student *class_roster[] = {
        &student1, &student2, &student3, &student4, &student5
    };
    
    int class_size = sizeof(class_roster) / sizeof(class_roster[0]);
    
    printf("=== 入学順（元の順序） ===\n");
    display_students(class_roster, class_size);
    
    /* GPA順でソート */
    sort_students_by_gpa(class_roster, class_size);
    
    printf("=== GPA順（高い順） ===\n");
    display_students(class_roster, class_size);
    
    /* 優秀な学生を見つける */
    printf("=== GPA 3.5以上の学生 ===\n");
    int i;
    for (i = 0; i < class_size; i++) {
        if (class_roster[i]->gpa >= 3.5) {
            printf("%s (GPA: %.1f)\n", 
                   class_roster[i]->name, 
                   class_roster[i]->gpa);
        }
    }
    
    return 0;
}
```

### ネストした構造体とポインタ

構造体の中に他の構造体を含む場合のポインタ操作について学習します。

#### ネストした構造体の基本

```c
#include <stdio.h>
#include <string.h>

struct Address {
    char street[100];
    char city[50];
    char postal_code[20];
};

struct Contact {
    char phone[20];
    char email[50];
};

struct Employee {
    int id;
    char name[50];
    struct Address address;    /* ネストした構造体 */
    struct Contact contact;    /* ネストした構造体 */
    double salary;
};

void print_employee_details(struct Employee *emp)
{
    printf("=== 社員詳細情報 ===\n");
    printf("ID: %d\n", emp->id);
    printf("名前: %s\n", emp->name);
    printf("住所: %s, %s %s\n", 
           emp->address.street, 
           emp->address.city, 
           emp->address.postal_code);
    printf("電話: %s\n", emp->contact.phone);
    printf("メール: %s\n", emp->contact.email);
    printf("給与: %.0f円\n", emp->salary);
    printf("\n");
}

void update_address(struct Employee *emp, const char* street, 
                   const char* city, const char* postal_code)
{
    strcpy(emp->address.street, street);
    strcpy(emp->address.city, city);
    strcpy(emp->address.postal_code, postal_code);
    printf("%s の住所を更新しました\n", emp->name);
}

int main(void)
{
    struct Employee emp;
    struct Employee *emp_ptr = &emp;
    
    /* 基本情報の設定 */
    emp_ptr->id = 5001;
    strcpy(emp_ptr->name, "田中太郎");
    emp_ptr->salary = 450000.0;
    
    /* ネストした構造体メンバーの設定 */
    strcpy(emp_ptr->address.street, "新宿区西新宿1-2-3");
    strcpy(emp_ptr->address.city, "東京都");
    strcpy(emp_ptr->address.postal_code, "160-0023");
    
    strcpy(emp_ptr->contact.phone, "03-1234-5678");
    strcpy(emp_ptr->contact.email, "tanaka@company.co.jp");
    
    print_employee_details(emp_ptr);
    
    /* 住所更新 */
    update_address(emp_ptr, "渋谷区渋谷2-3-4", "東京都", "150-0002");
    
    print_employee_details(emp_ptr);
    
    return 0;
}
```

#### 構造体ポインタのネスト

```c
#include <stdio.h>
#include <string.h>

struct Engine {
    char type[50];
    double displacement;
    int horsepower;
};

struct Car {
    char model[50];
    int year;
    struct Engine *engine;  /* エンジン情報へのポインタ */
    double price;
};

struct Dealership {
    char name[50];
    struct Car *inventory;  /* 車の在庫配列へのポインタ */
    int car_count;
};

void print_car_info(struct Car *car)
{
    printf("=== 車両情報 ===\n");
    printf("モデル: %s (%d年)\n", car->model, car->year);
    if (car->engine != NULL) {
        printf("エンジン: %s %.1fL %dHP\n", 
               car->engine->type, 
               car->engine->displacement, 
               car->engine->horsepower);
    }
    printf("価格: %.0f万円\n", car->price);
    printf("\n");
}

void print_dealership_inventory(struct Dealership *dealer)
{
    int i;
    printf("=== %s の在庫 ===\n", dealer->name);
    for (i = 0; i < dealer->car_count; i++) {
        printf("%d. %s (%.0f万円)\n", 
               i + 1, 
               (dealer->inventory + i)->model, 
               (dealer->inventory + i)->price);
    }
    printf("\n");
}

int main(void)
{
    /* エンジン情報 */
    struct Engine engine1 = {"V6ガソリン", 3.5, 280};
    struct Engine engine2 = {"直4ハイブリッド", 1.8, 120};
    struct Engine engine3 = {"V8ガソリン", 5.0, 450};
    
    /* 車両情報 */
    struct Car cars[3] = {
        {"セダンLX", 2023, &engine1, 450},
        {"ハイブリッドEC", 2024, &engine2, 380},
        {"スポーツST", 2023, &engine3, 850}
    };
    
    /* ディーラー情報 */
    struct Dealership dealer = {
        "トーキョー自動車",
        cars,
        3
    };
    
    /* ディーラーの在庫一覧 */
    print_dealership_inventory(&dealer);
    
    /* 各車両の詳細情報 */
    int i;
    for (i = 0; i < dealer.car_count; i++) {
        print_car_info(dealer.inventory + i);
    }
    
    return 0;
}
```

### 構造体とメモリ管理

構造体のメモリレイアウトとアライメントについて理解します。

#### 構造体のメモリサイズとアライメント

```c
#include <stdio.h>

struct Example1 {
    char a;     /* 1バイト */
    int b;      /* 4バイト */
    char c;     /* 1バイト */
};

struct Example2 {
    char a;     /* 1バイト */
    char c;     /* 1バイト */
    int b;      /* 4バイト */
};

struct Example3 {
    double d;   /* 8バイト */
    char a;     /* 1バイト */
    int b;      /* 4バイト */
};

void analyze_struct_memory(void)
{
    struct Example1 ex1;
    struct Example2 ex2;
    struct Example3 ex3;
    
    printf("=== 構造体メモリ分析 ===\n");
    
    printf("Example1 (char, int, char):\n");
    printf("  sizeof: %lu バイト\n", sizeof(struct Example1));
    printf("  a のオフセット: %lu\n", (unsigned long)&ex1.a - (unsigned long)&ex1);
    printf("  b のオフセット: %lu\n", (unsigned long)&ex1.b - (unsigned long)&ex1);
    printf("  c のオフセット: %lu\n", (unsigned long)&ex1.c - (unsigned long)&ex1);
    printf("\n");
    
    printf("Example2 (char, char, int):\n");
    printf("  sizeof: %lu バイト\n", sizeof(struct Example2));
    printf("  a のオフセット: %lu\n", (unsigned long)&ex2.a - (unsigned long)&ex2);
    printf("  c のオフセット: %lu\n", (unsigned long)&ex2.c - (unsigned long)&ex2);
    printf("  b のオフセット: %lu\n", (unsigned long)&ex2.b - (unsigned long)&ex2);
    printf("\n");
    
    printf("Example3 (double, char, int):\n");
    printf("  sizeof: %lu バイト\n", sizeof(struct Example3));
    printf("  d のオフセット: %lu\n", (unsigned long)&ex3.d - (unsigned long)&ex3);
    printf("  a のオフセット: %lu\n", (unsigned long)&ex3.a - (unsigned long)&ex3);
    printf("  b のオフセット: %lu\n", (unsigned long)&ex3.b - (unsigned long)&ex3);
    printf("\n");
}

int main(void)
{
    analyze_struct_memory();
    
    printf("=== 基本データ型のサイズ ===\n");
    printf("char: %lu バイト\n", sizeof(char));
    printf("int: %lu バイト\n", sizeof(int));
    printf("double: %lu バイト\n", sizeof(double));
    printf("ポインタ: %lu バイト\n", sizeof(void*));
    
    return 0;
}
```

#### 構造体の配列とポインタの効率性

```c
#include <stdio.h>
#include <string.h>
#include <time.h>

struct LargeData {
    char description[256];
    double values[100];
    int status;
};

/* 値渡しで構造体を処理（非効率） */
double process_by_value(struct LargeData data)
{
    int i;
    double sum = 0.0;
    
    for (i = 0; i < 100; i++) {
        sum += data.values[i];
    }
    
    return sum / 100.0;  /* 平均値 */
}

/* ポインタ渡しで構造体を処理（効率的） */
double process_by_pointer(struct LargeData *data)
{
    int i;
    double sum = 0.0;
    
    for (i = 0; i < 100; i++) {
        sum += data->values[i];
    }
    
    return sum / 100.0;  /* 平均値 */
}

/* 構造体にテストデータを設定 */
void setup_test_data(struct LargeData *data)
{
    int i;
    strcpy(data->description, "テストデータセット");
    
    for (i = 0; i < 100; i++) {
        data->values[i] = (double)(i + 1) * 1.5;
    }
    
    data->status = 1;
}

int main(void)
{
    struct LargeData test_data;
    clock_t start, end;
    double result;
    int iterations = 10000;
    int i;
    
    setup_test_data(&test_data);
    
    printf("=== 構造体サイズ情報 ===\n");
    printf("LargeData のサイズ: %lu バイト\n", sizeof(struct LargeData));
    printf("テスト回数: %d 回\n\n", iterations);
    
    /* 値渡しのテスト */
    printf("値渡しでのテスト開始...\n");
    start = clock();
    for (i = 0; i < iterations; i++) {
        result = process_by_value(test_data);
    }
    end = clock();
    printf("値渡し結果: %.1f\n", result);
    printf("実行時間: %.3f 秒\n\n", (double)(end - start) / CLOCKS_PER_SEC);
    
    /* ポインタ渡しのテスト */
    printf("ポインタ渡しでのテスト開始...\n");
    start = clock();
    for (i = 0; i < iterations; i++) {
        result = process_by_pointer(&test_data);
    }
    end = clock();
    printf("ポインタ渡し結果: %.1f\n", result);
    printf("実行時間: %.3f 秒\n", (double)(end - start) / CLOCKS_PER_SEC);
    
    return 0;
}
```

### 実践的な構造体活用例

#### データベース風の学生管理システム

```c
#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 100
#define MAX_NAME_LEN 50

struct Student {
    int id;
    char name[MAX_NAME_LEN];
    int age;
    double gpa;
    char major[30];
};

struct StudentDatabase {
    struct Student *students[MAX_STUDENTS];
    int count;
};

/* 学生データベースの初期化 */
void init_database(struct StudentDatabase *db)
{
    int i;
    db->count = 0;
    for (i = 0; i < MAX_STUDENTS; i++) {
        db->students[i] = NULL;
    }
}

/* 学生を追加 */
int add_student(struct StudentDatabase *db, struct Student *student)
{
    if (db->count >= MAX_STUDENTS) {
        printf("エラー: データベースが満杯です\n");
        return 0;
    }
    
    db->students[db->count] = student;
    db->count++;
    printf("学生 %s を追加しました (ID: %d)\n", student->name, student->id);
    return 1;
}

/* IDで学生を検索 */
struct Student* find_student_by_id(struct StudentDatabase *db, int id)
{
    int i;
    for (i = 0; i < db->count; i++) {
        if (db->students[i]->id == id) {
            return db->students[i];
        }
    }
    return NULL;
}

/* 専攻で学生を検索 */
void find_students_by_major(struct StudentDatabase *db, const char* major)
{
    int i;
    int found = 0;
    
    printf("=== %s専攻の学生 ===\n", major);
    for (i = 0; i < db->count; i++) {
        if (strcmp(db->students[i]->major, major) == 0) {
            printf("ID: %d, 名前: %s, GPA: %.1f\n", 
                   db->students[i]->id,
                   db->students[i]->name,
                   db->students[i]->gpa);
            found = 1;
        }
    }
    
    if (!found) {
        printf("該当する学生が見つかりませんでした\n");
    }
    printf("\n");
}

/* 全学生の一覧表示 */
void display_all_students(struct StudentDatabase *db)
{
    int i;
    
    printf("=== 全学生一覧 (%d名) ===\n", db->count);
    printf("ID\t名前\t\t年齢\tGPA\t専攻\n");
    printf("------------------------------------------------\n");
    
    for (i = 0; i < db->count; i++) {
        printf("%d\t%s\t\t%d\t%.1f\t%s\n",
               db->students[i]->id,
               db->students[i]->name,
               db->students[i]->age,
               db->students[i]->gpa,
               db->students[i]->major);
    }
    printf("\n");
}

/* 平均GPAを計算 */
double calculate_average_gpa(struct StudentDatabase *db)
{
    double total = 0.0;
    int i;
    
    if (db->count == 0) return 0.0;
    
    for (i = 0; i < db->count; i++) {
        total += db->students[i]->gpa;
    }
    
    return total / db->count;
}

int main(void)
{
    struct StudentDatabase db;
    init_database(&db);
    
    /* 学生データの作成 */
    struct Student student1 = {2001, "田中太郎", 20, 3.2, "コンピュータ"};
    struct Student student2 = {2002, "佐藤花子", 21, 3.8, "数学"};
    struct Student student3 = {2003, "山田次郎", 19, 2.9, "コンピュータ"};
    struct Student student4 = {2004, "鈴木美咲", 20, 3.5, "物理"};
    struct Student student5 = {2005, "高橋健太", 22, 3.1, "数学"};
    
    /* データベースに学生を追加 */
    add_student(&db, &student1);
    add_student(&db, &student2);
    add_student(&db, &student3);
    add_student(&db, &student4);
    add_student(&db, &student5);
    
    /* 全学生表示 */
    display_all_students(&db);
    
    /* 特定IDの学生を検索 */
    struct Student *found = find_student_by_id(&db, 2003);
    if (found != NULL) {
        printf("ID 2003 の学生: %s (%s専攻)\n\n", found->name, found->major);
    }
    
    /* 専攻別検索 */
    find_students_by_major(&db, "コンピュータ");
    find_students_by_major(&db, "数学");
    
    /* 統計情報 */
    printf("=== 統計情報 ===\n");
    printf("登録学生数: %d名\n", db.count);
    printf("平均GPA: %.2f\n", calculate_average_gpa(&db));
    
    return 0;
}
```

## サンプルコード

### 構造体の基本操作

プログラムファイル: `examples/struct_basics.c`

構造体の定義、初期化、メンバーアクセスの基本を学習します。

### 構造体ポインタと->演算子

プログラムファイル: `examples/struct_pointers.c`

構造体ポインタと->演算子の使用方法を学習します。

### 構造体配列の操作

プログラムファイル: `examples/struct_arrays.c`

構造体配列とポインタを使ったデータ管理を学習します。

### コンパイルと実行

```bash
# examples ディレクトリに移動
cd examples

# C90準拠でコンパイル
gcc -std=c90 -Wall -Wextra -pedantic struct_basics.c -o struct_basics

# 実行
./struct_basics
```

## 演習課題

### 基礎問題

1. **学生情報管理**
   - 学生の情報（ID、名前、年齢、成績）を格納する構造体を定義し、ポインタを使って情報を表示・更新するプログラムを作成してください

2. **座標計算**
   - 2D座標を表す構造体を定義し、2点間の距離を計算する関数をポインタを使って実装してください

3. **商品管理**
   - 商品情報（コード、名前、価格、在庫）の構造体を作成し、構造体配列で複数商品を管理するプログラムを作成してください

### 応用問題

4. **従業員データベース**
   - 従業員情報と部署情報をネストした構造体で管理し、部署別の給与統計を算出するプログラムを作成してください

5. **図書管理システム**
   - 本の情報（タイトル、著者、出版年、貸出状況）を管理し、検索・貸出・返却機能を実装してください

6. **成績管理システム**
   - 学生と科目の構造体を使って、学生別・科目別の成績統計を管理するプログラムを作成してください

### 発展問題

7. **動的配列システム**
   - 構造体ポインタ配列を動的に拡張できるシステムを実装してください

8. **データソート**
   - 構造体ポインタ配列を複数の条件（名前、年齢、成績など）でソートできるプログラムを作成してください

9. **階層データ構造**
   - 会社組織（部署→チーム→従業員）のような階層構造を構造体とポインタで表現してください

## コンパイル方法

この章では以下のMakefileを使用してコンパイルができます：

```bash
# 全ての例題をコンパイル
make all

# 特定のプログラムをコンパイル
make struct_basics

# 実行
make run

# クリーンアップ
make clean
```

## 規格による違い

### C90での制限事項
- 構造体の初期化は順序通りのみ
- 可変長配列メンバーは不可
- 匿名構造体・共用体は不可

### C99以降の拡張
- 指定イニシャライザが使用可能
- 可変長配列メンバー（C99）
- 匿名構造体・共用体（C11）

## よくある間違い

### 1. NULLポインタの参照

```c
/* NG: NULLポインタの参照 */
struct Student *student = NULL;
printf("%s\n", student->name);  /* セグメンテーション違反 */

/* OK: NULLチェック */
if (student != NULL) {
    printf("%s\n", student->name);
}
```

### 2. スタック上の構造体アドレスの返却

```c
/* NG: ローカル構造体のアドレス返し */
struct Point* create_point(int x, int y) {
    struct Point p = {x, y};
    return &p;  /* 危険: ローカル変数のアドレス */
}

/* OK: 静的変数または呼び出し元で用意 */
void create_point(struct Point *p, int x, int y) {
    p->x = x;
    p->y = y;
}
```

### 3. 構造体の比較

```c
/* NG: 構造体の直接比較 */
struct Point p1 = {10, 20};
struct Point p2 = {10, 20};
if (p1 == p2) {  /* コンパイルエラー */
}

/* OK: メンバーごとの比較 */
if (p1.x == p2.x && p1.y == p2.y) {
    printf("同じ座標です\n");
}
```

## 次の章へ

構造体を理解したら、[関数ポインタ](../function-pointers/README.md) に進んでください。

## 参考資料

- [C言語構造体リファレンス](https://ja.cppreference.com/w/c/language/struct)
- [メモリアライメントの詳細](https://ja.cppreference.com/w/c/language/object)
- [構造体の初期化](https://ja.cppreference.com/w/c/language/struct_initialization)