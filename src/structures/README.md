# 構造体とポインター

## 対応C規格

- **主要対象：** C90/C11
- **学習内容：** 構造体の基本、構造体とポインター、構造体配列、複雑なデータ構造の構築

## 学習目標

この章を完了すると、以下のことができるようになります。

- 構造体の定義と使用ができる
- 構造体ポインターを適切に操作できる
- 構造体配列を操作できる
- 構造体の値渡しとポインター値の受け渡しを区別できる
- パディングを考慮して構造体のサイズを確認できる

## 概要と詳細

### 構造体とは

構造体は、型の異なる複数のメンバを一つのオブジェクトにまとめる集成体型です。
座標の`x`と`y`のように、同時に扱う値へ一つの型名を与えられます。

#### 構造体で関連する値をまとめる

構造体がないと、関連するデータをバラバラに管理することになります。

```c
/* 構造体を使わない場合は、値の対応関係を添字で管理する */
char names[10][50];
int ids[10];
int ages[10];

/* 構造体を使う場合は、学生ごとの値を一つの要素にまとめる */
struct student students[10];
```

### 構造体の基本概念

#### 構造体の定義

```c
struct 構造体名 {
    データ型 メンバ名1;
    データ型 メンバ名2;
    /* ... */
};
```

#### 基本的な構造体の例

```c
/* 学生の情報を表す構造体 */
struct student {
    char name[50];
    int id;
    int age;
    float gpa;
};

/* 2次元座標を表す構造体 */
struct point {
    int x;
    int y;
};

/* 日付を表す構造体 */
struct date {
    int year;
    int month;
    int day;
};
```

### 構造体変数の宣言と初期化

#### 構造体変数の宣言

```c
struct student s1;           /* 単一の構造体変数 */
struct student s2, s3;       /* 複数の構造体変数 */
struct student class[30];    /* 構造体配列 */
```

#### 構造体の初期化

```c
/* 宣言と同時に初期化 */
struct point p1 = {10, 20};

/* メンバ指定初期化（C99以降） */
struct point p2 = {.x = 15, .y = 25};

/* 後から初期化 */
struct student s;
strcpy(s.name, "山田太郎");
s.id = 12345;
s.age = 20;
s.gpa = 3.5;
```

### 構造体メンバのアクセス

#### ドット演算子（.）

構造体変数のメンバにアクセスします。

```c
struct point p = {10, 20};

printf("x: %d\n", p.x);
printf("y: %d\n", p.y);

p.x = 30;  /* メンバの値を変更 */
p.y = 40;
```

#### アロー演算子（->）

構造体ポインターのメンバにアクセスします。

```c
struct point p = {10, 20};
struct point *ptr = &p;

printf("x: %d\n", ptr->x);
printf("y: %d\n", ptr->y);

ptr->x = 50;  /* ポインター経由でメンバを変更 */
ptr->y = 60;
```

### 構造体とポインター

#### 構造体ポインターの基本

```c
struct student s = {"田中花子", 67890, 19, 3.8};
struct student *ptr = &s;

/* 以下は同じ結果 */
printf("Name: %s\n", s.name);
printf("Name: %s\n", ptr->name);
printf("Name: %s\n", (*ptr).name);
```

#### 構造体ポインターの利点

1. **コピーの回避**：構造体の値ではなく、構造体へのポインター値を渡せます
2. **呼び出し側の変更**：間接参照を通じて、呼び出し側の構造体を変更できます
3. **読み取り専用の指定**：`const struct point *`のように、変更しない契約を型で示せます

### 構造体と関数

#### 構造体を値渡しする関数

```c
void print_point(struct point p)
{
    printf("Point: (%d, %d)\n", p.x, p.y);
}

int main(void)
{
    struct point p = {10, 20};
    print_point(p);  /* 構造体のコピーが作られる */
    return 0;
}
```

#### 構造体ポインターを渡す関数

```c
void print_point_ptr(const struct point *p)
{
    printf("Point: (%d, %d)\n", p->x, p->y);
}

void move_point(struct point *p, int dx, int dy)
{
    p->x += dx;
    p->y += dy;
}

int main(void)
{
    struct point p = {10, 20};
    print_point_ptr(&p);
    move_point(&p, 5, 3);
    print_point_ptr(&p);  /* (15, 23) */
    return 0;
}
```

#### 構造体を返す関数

```c
struct point add_points(struct point p1, struct point p2)
{
    struct point result;
    result.x = p1.x + p2.x;
    result.y = p1.y + p2.y;
    return result;
}

struct point create_point(int x, int y)
{
    struct point p = {x, y};
    return p;
}
```

### 構造体配列

#### 構造体配列の宣言と初期化

```c
/* 学生配列の宣言 */
struct student class[3];

/* 初期化 */
struct student class[3] = {
    {"山田太郎", 12345, 20, 3.5},
    {"佐藤花子", 12346, 19, 3.8},
    {"田中次郎", 12347, 21, 3.2}
};
```

#### 構造体配列の操作

```c
int i;

/* 全学生の情報を表示 */
for (i = 0; i < 3; i++) {
    printf("Student %d: %s (ID: %d)\n",
           i+1, class[i].name, class[i].id);
}

/* 特定の学生を検索 */
for (i = 0; i < 3; i++) {
    if (class[i].id == 12346) {
        printf("Found: %s\n", class[i].name);
        break;
    }
}
```

### ネストした構造体

#### 構造体の中に構造体

```c
struct date {
    int year;
    int month;
    int day;
};

struct person {
    char name[50];
    struct date birthday;  /* 構造体をメンバとして含む */
    int age;
};

/* 使用例 */
struct person p = {
    "鈴木一郎",
    {1990, 5, 15},  /* birthday */
    33
};

printf("Birthday: %04d-%02d-%02d\n",
       p.birthday.year, p.birthday.month, p.birthday.day);
```

### 構造体の動的メモリ割り当て

#### malloc()を使った構造体の動的確保

```c
#include <stdlib.h>

/* 単一の構造体を動的確保 */
struct student *s = malloc(sizeof *s);

if (s == NULL) {
    fprintf(stderr, "Allocation failed\n");
    return 1;
}

/* 構造体の使用 */
strcpy(s->name, "動的太郎");
s->id = 99999;
s->age = 22;

/* メモリ解放 */
free(s);
s = NULL;

/* 構造体配列を動的確保 */
int size = 100;
struct student *students = malloc((size_t)size * sizeof *students);

if (students != NULL) {
    /* 構造体配列を使用 */
    free(students);
}
```

Cでは`void *`からオブジェクトへのポインターへ暗黙に変換できるため、`malloc`の戻り値をキャストする必要はありません。
`sizeof *s`の形式なら、ポインターの型を変更したときも確保サイズが追従します。

### typedefを使った構造体

#### `typedef`の利点

```c
/* typedef なし */
struct point {
    int x;
    int y;
};
struct point p1, p2;  /* 毎回 struct が必要 */

/* typedef あり */
typedef struct {
    int x;
    int y;
} Point;

Point p1, p2;
```

#### `typedef`の使用例

```c
typedef struct {
    char name[50];
    int id;
    float gpa;
} Student;

typedef struct {
    int year;
    int month;
    int day;
} Date;

/* 使用が簡潔に */
Student s1, s2;
Date today = {2024, 12, 25};
```

### 共用体（union）

#### 共用体の基本概念

共用体は、同じメモリ領域を複数のメンバで共有します。

```c
union data {
    int i;
    float f;
    char c;
};

union data d;
d.i = 10;
printf("int: %d\n", d.i);

d.f = 3.14f;
printf("float: %.2f\n", d.f);
/* 最後に格納したメンバはd.f */
```

最後に値を格納したメンバとは異なるメンバを読むと、格納した値のオブジェクト表現を別の型として解釈します。
結果は型や処理系に依存し、トラップ表現を生成する可能性もあるため、移植可能な型変換の代わりには使えません。

#### 共用体の用途

- 同時には一つしか使わない複数の表現で記憶域を共有する
- 別のタグメンバと組み合わせて、現在有効なメンバを管理する

### 構造体の高度な使用法

#### 自己参照構造体（リンクリスト）

```c
typedef struct node {
    int data;
    struct node *next;  /* 自分自身の型へのポインター */
} Node;

/* リンクリストの簡単な例 */
Node *head = NULL;
Node *new_node = malloc(sizeof *new_node);
if (new_node != NULL) {
    new_node->data = 42;
    new_node->next = head;
    head = new_node;
}
```

#### 関数ポインターを含む構造体

```c
typedef struct {
    char name[20];
    int (*calculate)(int, int);
} Operation;

int add(int a, int b) { return a + b; }
int multiply(int a, int b) { return a * b; }

Operation ops[] = {
    {"加算", add},
    {"乗算", multiply}
};

/* 使用例 */
int result = ops[0].calculate(5, 3);  /* add(5, 3) */
```

### よくある間違いとデバッグ

#### 1. 構造体の比較

**問題：** 構造体を直接比較しようとする

```c
struct point p1 = {10, 20};
struct point p2 = {10, 20};
if (p1 == p2) { /* 制約違反：構造体には==を適用できない */ }
```

**対策：**

```c
int points_equal(struct point p1, struct point p2)
{
    return (p1.x == p2.x && p1.y == p2.y);
}

if (points_equal(p1, p2)) { /* 正しい */ }
```

#### 2. 未初期化構造体の使用

**問題：** 構造体メンバが未初期化

```c
struct student s;
printf("Name: %s\n", s.name);  /* 未初期化データ */
```

**対策：**

```c
struct student s = {0};  /* ゼロ初期化 */
/* または */
memset(&s, 0, sizeof(s));
```

#### 3. 文字列の代入ミス

**問題：** 文字列を直接代入しようとする

```c
struct student s;
s.name = "山田太郎";  /* 制約違反：配列には代入できない */
```

**対策：**

```c
struct student s;
strcpy(s.name, "山田太郎");  /* strcpy を使用 */
```

#### 4. 構造体ポインターの初期化忘れ

**問題：** NULLポインターの使用

```c
struct student *s;
strcpy(s->name, "太郎");  /* 未初期化ポインターの間接参照は未定義動作 */
```

**対策：**

```c
struct student *s = malloc(sizeof *s);
if (s != NULL) {
    strcpy(s->name, "太郎");
}
```

### パフォーマンスとメモリ効率

#### 構造体のパディング

```c
struct example {
    char c;
    int i;
    char c2;
};
```

処理系は、各メンバの間や構造体の末尾にパディングを挿入できます。
たとえば`sizeof(int) == 4`で`int`を4バイト境界に配置する処理系では、この構造体が12バイトになる場合があります。
実際のサイズは`sizeof(struct example)`で確認します。

#### メモリ効率の改善

```c
/* パディングが増える場合がある配置 */
struct bad {
    char c1;
    int i;
    char c2;
};

/* パディングが減る場合がある配置 */
struct good {
    int i;
    char c1;
    char c2;
};
```

メンバ順の変更がサイズを減らすかどうかは、各型のサイズとアラインメントに依存します。
外部形式やABIとの互換性が必要な構造体では、サイズだけを理由にメンバ順を変更してはいけません。

## 実例コード

完全な実装例は以下のファイルを参照してください。

### 構造体の基本操作

- [struct_basics.c](examples/struct_basics.c) - C90準拠版
- [struct_basics_c99.c](examples/struct_basics_c99.c) - C99準拠版

### 構造体とポインター

- [struct_pointers.c](examples/struct_pointers.c) - C90準拠版
- [struct_pointers_c99.c](examples/struct_pointers_c99.c) - C99準拠版

### 複雑なデータ構造

- [complex_structures.c](examples/complex_structures.c) - C90準拠版
- [complex_structures_c99.c](examples/complex_structures_c99.c) - C99準拠版

## コンパイル方法

### 基本的なコンパイル（C90準拠）

```bash
gcc -std=c90 -Wall -Wextra -pedantic struct_basics.c -o struct_basics
```

### Makefileを使用した場合

```bash

# 全てのプログラムをコンパイル

make all

# 特定のプログラムをコンパイル

make struct_basics

# C99版をコンパイル

make struct_basics_c99

# プログラムを実行

make run-all

# クリーンアップ

make clean
```

## 学習フローとコンパイル方法

### 推奨学習順序

1. **理論学習**: README.mdで基本概念を理解
2. **サンプルコード**: examples/の基本例を確認
3. **演習課題**: exercises/README.mdで課題を確認
4. **実装練習**: solutions/の解答例を参考に自分で実装

### 学習のコツ

1. **実際のデータでモデリング**: 身近なものを構造体で表現
2. **段階的構築**: 単純な構造体から複雑なものへ
3. **メモリ図の描画**: ポインターと構造体の関係を視覚化
4. **実用例の実装**: 学生管理システムなどの小さなプロジェクト

## C90とC11の違い

### C90での制限

- メンバ指定初期化なし
- ブロック内の宣言は、そのブロックの文より前に置く
- コメントは `/* */` のみ

### C11での拡張

- 匿名構造体・共用体
- `_Static_assert` での構造体サイズチェック

メンバ指定初期化はC99で追加された機能であり、C11固有ではありません。

## 次の章へ

[第12章：関数ポインター](../function-pointers/README.md)

## 参考資料

- examples/ - 実装例（C90、C99両対応）
- exercises/ - 演習問題
- solutions/ - 解答例
- [C標準ライブラリリファレンス](https://en.cppreference.com/w/c)
- [構造体設計ベストプラクティス](https://stackoverflow.com/questions/tagged/c+struct)

## 演習問題

[演習問題](exercises/)では、構造体の値渡し、ポインターによる操作、配列、パディングを確認できます。

- 基礎問題：基本的な文法や概念の確認
- 応用問題：より実践的なプログラムの作成
- チャレンジ問題：高度な理解と実装力が必要な問題
