# 関数

## 対応C規格

- **主要対象:** C90
- **学習内容:** 関数の基本、引数と戻り値、関数のスコープ、再帰関数、関数プロトタイプ

## 学習目標
この章を完了すると、以下のことができるようになります。

- 関数の定義と呼び出しができる
- 引数と戻り値を適切に使える
- 関数のスコープを理解する
- 再帰関数を作成できる
- 関数プロトタイプの重要性を理解する

## 概要と詳細

### 関数とは？

関数は、プログラムを「部品」に分けるための仕組みです。大きな問題を小さな部分に分割して解決する「分割統治」の考え方を実現します。

#### 日常生活での関数
関数を理解するために、料理を例に考えてみましょう。

**カレーライスを作る場合：**

1. ご飯を炊く（関数1）
2. 野菜を切る（関数2）
3. 肉を炒める（関数3）
4. カレーを煮込む（関数4）
5. 盛り付ける（関数5）

それぞれの作業を「関数」として独立させることで。

- 同じ作業（ご飯を炊く）を他の料理でも使える
- 問題があったとき、どの工程か特定しやすい
- 複数人で分担できる

### 関数の基本概念 
関数は特定の処理をまとめたコードブロックで、プログラムの再利用性と保守性を向上させます。

#### 関数を使う理由

1. **コードの再利用性**: 同じ処理を何度も書く必要がない
2. **プログラムの構造化**: 複雑な問題を小さな部分に分割
3. **保守性の向上**: 修正が必要な箇所を特定しやすい
4. **可読性の向上**: プログラムの意図が明確になる
5. **デバッグの容易さ**: 問題のある部分を特定しやすい

#### 関数の構成要素

```c
戻り値の型 関数名(引数リスト)
{
    /* 関数本体 */
    return 戻り値;  /* 戻り値がある場合 */
}
```

### 関数の定義と宣言 
関数を使うには、「宣言」と「定義」を理解する必要があります。

#### なぜ関数プロトタイプが必要？

C言語では「使う前に宣言する」というルールがあります。関数プロトタイプは「この関数がありますよ」とコンパイラに教える役割があります。

#### 関数プロトタイプ（前方宣言）

```c
/* 関数プロトタイプ */
int add(int a, int b);
void print_message(void);
```

#### 関数の定義

```c
/* 関数の実装 */
int add(int a, int b)
{
    return a + b;
}

void print_message(void)
{
    printf("Hello, World!\n");
}
```

### 引数の渡し方
関数に値を渡す方法は2つあります。この違いを理解することは非常に重要です！

#### 値渡し（Call by Value）
C言語では、通常の変数を渡すと「値のコピー」が渡されます。これはC言語の基本的な動作です。

##### 値渡しのメカニズム

```
関数呼び出し時のメモリの様子：

main関数のメモリ:                  modify_value関数のメモリ:
+---------------+                +---------------+
| num = 10      | ---値をコピー--> | x = 10        |
+---------------+                +---------------+
                                      ↓ x = 100に変更
+---------------+                +---------------+
| num = 10      |                | x = 100       |
+---------------+                +---------------+
※numは変更されない
```

##### 値渡しの実例

```c
void modify_value(int x)
{
    printf("関数内（変更前）: x = %d\n", x);
    x = 100;  /* 元の変数には影響しない */
    printf("関数内（変更後）: x = %d\n", x);
}

int main(void)
{
    int num = 10;
    printf("呼び出し前: num = %d\n", num);
    
    modify_value(num);
    
    printf("呼び出し後: num = %d\n", num);  /* 10のまま */
    return 0;
}
```

##### 値渡しの利点と欠点
**利点：**

- 元の変数が保護される（予期しない変更を防げる）
- 理解しやすく、バグが起きにくい
- 関数の独立性が高い

**欠点：**

- 大きなデータ構造では非効率（コピーに時間がかかる）
- 複数の値を返すことができない
- 関数内で元の変数を変更できない

#### 参照渡し（Call by Reference）
ポインタを使用して、変数のアドレスを渡すことで元の変数を変更できます。

##### 参照渡しのメカニズム

```
関数呼び出し時のメモリの様子：

main関数のメモリ:                    modify_value関数のメモリ:
+---------------+                  +------------------+
| num = 10      |<--アドレスを指す-- | x = &num         |
| アドレス:1000 |                   +------------------+
+---------------+                      ↓ *x = 100でnumを変更
                                
+---------------+               
| num = 100     |               
| アドレス:1000 |               
+---------------+               
※numが直接変更される
```

##### 参照渡しの実例

```c
void modify_value(int *x)
{
    printf("関数内（変更前）: *x = %d\n", *x);
    *x = 100;  /* 元の変数を変更 */
    printf("関数内（変更後）: *x = %d\n", *x);
}

int main(void)
{
    int num = 10;
    printf("呼び出し前: num = %d\n", num);
    
    modify_value(&num);  /* &でアドレスを渡す */
    
    printf("呼び出し後: num = %d\n", num);  /* 100に変更されている */
    return 0;
}
```

##### 参照渡しの利点と欠点
**利点：**

- 関数内で元の変数を変更できる
- 大きなデータ構造でも効率的（アドレスだけ渡す）
- 複数の値を返すことができる

**欠点：**

- ポインタの理解が必要
- 意図しない変更の可能性がある
- NULLポインタのチェックが必要

#### 配列の引数渡し
配列を関数に渡す場合、特別な動作をします。

##### 配列は常に「参照渡し」になる

```c
void modify_array(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++) {
        arr[i] *= 2;  /* 元の配列を変更 */
    }
}

int main(void)
{
    int numbers[5] = {1, 2, 3, 4, 5};
    int i;
    
    printf("変更前: ");
    for (i = 0; i < 5; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");
    
    modify_array(numbers, 5);
    
    printf("変更後: ");
    for (i = 0; i < 5; i++) {
        printf("%d ", numbers[i]);  /* 値が2倍になっている */
    }
    printf("\n");
    
    return 0;
}
```

##### なぜ配列は参照渡しになるのか？

```
配列名は配列の先頭要素へのポインタとして扱われる：

numbers[5] = {1, 2, 3, 4, 5}

numbers → [1][2][3][4][5]
          ↑
     先頭要素のアドレス

関数に渡されるのは、この先頭要素のアドレス
```

#### 構造体の引数渡し
構造体は値渡しと参照渡しの両方が可能です。

##### 構造体の値渡し

```c
struct Point {
    int x;
    int y;
};

void move_point(struct Point p)
{
    p.x += 10;  /* コピーを変更（元の構造体は変わらない） */
    p.y += 10;
}
```

##### 構造体の参照渡し

```c
void move_point_ref(struct Point *p)
{
    p->x += 10;  /* 元の構造体を変更 */
    p->y += 10;
}
```

#### 引数渡しの実践的な使い分け

プログラミングでは、状況に応じて値渡しと参照渡しを使い分けることが重要です。ここでは、実際によく使われるパターンを詳しく見ていきましょう。

##### 1. swap関数（値の交換）
2つの変数の値を交換する関数は、参照渡しの必要性を理解する最も分かりやすい例です。

```c
/* 値渡しでは交換できない（間違い例） */
void swap_wrong(int a, int b)
{
    int temp = a;
    a = b;
    b = temp;
    /* 関数内でコピーを交換しただけ */
}

/* 参照渡しで正しく交換 */
void swap_correct(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main(void)
{
    int x = 5, y = 10;
    
    printf("交換前: x=%d, y=%d\n", x, y);
    
    swap_wrong(x, y);
    printf("swap_wrong後: x=%d, y=%d\n", x, y);  /* 5, 10のまま */
    
    swap_correct(&x, &y);
    printf("swap_correct後: x=%d, y=%d\n", x, y);  /* 10, 5に交換 */
    
    return 0;
}
```

**なぜswap_wrongは動作しないのか？**

```
swap_wrong呼び出し時：
main: x=5, y=10  →コピー→  swap_wrong: a=5, b=10
                             ↓交換
main: x=5, y=10  ←影響なし  swap_wrong: a=10, b=5（関数終了で消滅）
```

##### 2. 複数の値を返す関数
C言語の関数は通常1つの値しか返せませんが、参照渡しを使うと複数の値を返すことができます。

```c
/* 商と余りを同時に返す */
void divide_with_remainder(int dividend, int divisor, 
                          int *quotient, int *remainder)
{
    if (divisor == 0) {
        /* エラー処理 */
        if (quotient) *quotient = 0;
        if (remainder) *remainder = 0;
        return;
    }
    
    *quotient = dividend / divisor;
    *remainder = dividend % divisor;
}

/* 統計情報を一度に計算する */
void calculate_stats(int arr[], int size, 
                    int *min, int *max, double *average)
{
    int i, sum = 0;
    
    if (size <= 0 || arr == NULL) {
        return;  /* エラー処理 */
    }
    
    *min = *max = arr[0];
    
    for (i = 0; i < size; i++) {
        if (arr[i] < *min) *min = arr[i];
        if (arr[i] > *max) *max = arr[i];
        sum += arr[i];
    }
    
    *average = (double)sum / size;
}

int main(void)
{
    int q, r;
    int numbers[] = {23, 67, 12, 89, 45};
    int minimum, maximum;
    double avg;
    
    /* 除算の例 */
    divide_with_remainder(17, 5, &q, &r);
    printf("17 ÷ 5 = %d 余り %d\n", q, r);  /* 3 余り 2 */
    
    /* 統計計算の例 */
    calculate_stats(numbers, 5, &minimum, &maximum, &avg);
    printf("最小値: %d, 最大値: %d, 平均: %.1f\n", 
           minimum, maximum, avg);
    
    return 0;
}
```

##### 3. 安全な参照渡し（エラー処理）
ポインタを受け取る関数では、必ずNULLチェックを行うべきです。

```c
/* 基本的なNULLチェック */
void safe_increment(int *ptr)
{
    if (ptr != NULL) {  /* NULLポインタチェック */
        (*ptr)++;
    }
}

/* より実践的な例：文字列の安全なコピー */
int safe_string_copy(char *dest, const char *src, int dest_size)
{
    int i;
    
    /* 引数の検証 */
    if (dest == NULL || src == NULL || dest_size <= 0) {
        return -1;  /* エラー */
    }
    
    /* 安全にコピー */
    for (i = 0; i < dest_size - 1 && src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    dest[i] = '\0';  /* null終端を保証 */
    
    return i;  /* コピーした文字数を返す */
}

/* エラーコードを返す関数の例 */
int safe_divide(int a, int b, int *result)
{
    if (result == NULL) {
        return -1;  /* 引数エラー */
    }
    
    if (b == 0) {
        return -2;  /* ゼロ除算エラー */
    }
    
    *result = a / b;
    return 0;  /* 成功 */
}
```

##### 4. 大きなデータ構造の効率的な処理
構造体が大きくなると、値渡しのコピーコストが無視できなくなります。

```c
/* 大きな構造体の例 */
struct StudentRecord {
    char name[50];
    char id[20];
    int scores[10];
    double gpa;
    char address[100];
};

/* 値渡し（非効率） - 約200バイトをコピー */
void print_student_by_value(struct StudentRecord student)
{
    printf("名前: %s\n", student.name);
    printf("GPA: %.2f\n", student.gpa);
}

/* 参照渡し（効率的） - ポインタ（4-8バイト）のみコピー */
void print_student_by_reference(const struct StudentRecord *student)
{
    if (student == NULL) return;
    
    printf("名前: %s\n", student->name);
    printf("GPA: %.2f\n", student->gpa);
}

/* 構造体を変更する関数 */
void update_gpa(struct StudentRecord *student, double new_gpa)
{
    if (student == NULL) return;
    
    student->gpa = new_gpa;
    printf("%sのGPAを%.2fに更新しました\n", 
           student->name, new_gpa);
}
```

##### 5. 配列操作の実践例
配列は自動的に参照渡しになりますが、安全に扱うためのテクニックがあります。

```c
/* 配列の要素をすべて特定の値に設定 */
void fill_array(int arr[], int size, int value)
{
    int i;
    
    if (arr == NULL || size <= 0) return;
    
    for (i = 0; i < size; i++) {
        arr[i] = value;
    }
}

/* 2つの配列を比較 */
int compare_arrays(const int arr1[], const int arr2[], int size)
{
    int i;
    
    if (arr1 == NULL || arr2 == NULL || size <= 0) {
        return -1;  /* エラー */
    }
    
    for (i = 0; i < size; i++) {
        if (arr1[i] != arr2[i]) {
            return 0;  /* 異なる */
        }
    }
    
    return 1;  /* 同じ */
}

/* 配列の一部を別の配列にコピー */
void copy_array_range(int dest[], const int src[], 
                     int start, int count, int dest_size)
{
    int i;
    
    if (dest == NULL || src == NULL) return;
    if (start < 0 || count <= 0) return;
    if (count > dest_size) count = dest_size;  /* 安全性確保 */
    
    for (i = 0; i < count; i++) {
        dest[i] = src[start + i];
    }
}
```

##### 6. 関数の戻り値と参照渡しの組み合わせ
戻り値でステータスを返し、参照渡しで実際の値を返すパターンはよく使われます。

```c
/* 文字列を整数に変換（エラーチェック付き） */
int string_to_int(const char *str, int *result)
{
    int value = 0;
    int sign = 1;
    int i = 0;
    
    if (str == NULL || result == NULL) {
        return -1;  /* 引数エラー */
    }
    
    /* 空白をスキップ */
    while (str[i] == ' ') i++;
    
    /* 符号の処理 */
    if (str[i] == '-') {
        sign = -1;
        i++;
    } else if (str[i] == '+') {
        i++;
    }
    
    /* 数字でない場合はエラー */
    if (str[i] < '0' || str[i] > '9') {
        return -2;  /* フォーマットエラー */
    }
    
    /* 数値に変換 */
    while (str[i] >= '0' && str[i] <= '9') {
        value = value * 10 + (str[i] - '0');
        i++;
    }
    
    *result = value * sign;
    return 0;  /* 成功 */
}

/* 使用例 */
int main(void)
{
    int num;
    int status;
    
    status = string_to_int("123", &num);
    if (status == 0) {
        printf("変換成功: %d\n", num);
    } else {
        printf("変換失敗: エラーコード %d\n", status);
    }
    
    return 0;
}
```

##### 7. 実践的な選択基準

**値渡しを選ぶべき場合：**

- 基本データ型（int, char, float, double）
- 小さな構造体（数十バイト以下）
- 元の値を保護したい場合
- 関数の独立性を高めたい場合

**参照渡しを選ぶべき場合：**

- 大きな構造体や配列
- 複数の値を返したい場合
- 元の値を変更する必要がある場合
- パフォーマンスが重要な場合

**constを使った参照渡しを選ぶべき場合：**

- 大きなデータを読むだけの場合
- 誤った変更を防ぎたい場合
- APIの意図を明確にしたい場合

#### const修飾子による保護
参照渡しでも、値を変更したくない場合はconstを使います。

```c
/* 配列の内容を変更しない関数 */
int array_sum(const int arr[], int size)
{
    int i, sum = 0;
    
    /* arr[i] = 0;  コンパイルエラー（constで保護） */
    
    for (i = 0; i < size; i++) {
        sum += arr[i];  /* 読み取りはOK */
    }
    
    return sum;
}
```

#### 引数渡しのベストプラクティス

1. **基本データ型（int, char, floatなど）**

   - 通常は値渡しを使用
   - 変更が必要な場合のみ参照渡し

2. **配列**

   - 自動的に参照渡しになる
   - 変更しない場合はconstを付ける

3. **構造体**

   - 小さい構造体：値渡しでOK
   - 大きい構造体：参照渡しで効率化
   - 変更しない場合：const付き参照渡し

4. **文字列**

   - char配列またはchar*で渡す
   - 変更しない場合はconstを付ける

### 様々な関数の種類
関数にはいろいろな種類があります。用途に応じて使い分けましょう。

#### 戻り値のない関数（void関数）
処理だけ行って、結果を返さない関数です。

```c
void print_header(void)
{
    printf("====================\n");
    printf(" プログラム開始\n");
    printf("====================\n");
}

void greet_user(char *name)
{
    printf("こんにちは、%sさん！\n", name);
}
```

#### 配列を扱う関数

```c
/* 配列の要素数を計算できないため、サイズを別途渡す必要がある */
int array_sum(int arr[], int size)
{
    int i, sum = 0;
    
    for (i = 0; i < size; i++)
    {
        sum += arr[i];
    }
    
    return sum;
}

/* 配列を初期化する関数 */
void initialize_array(int arr[], int size, int value)
{
    int i;
    
    for (i = 0; i < size; i++)
    {
        arr[i] = value;
    }
}
```

### 再帰関数
再帰関数は自分自身を呼び出す関数です。

#### 再帰を理解する日常例
**ロシア人形（マトリョーシカ）**を想像してください。

1. 一番外側の人形を開ける
2. 中に人形があったら、それも開ける
3. さらに中に人形があったら、それも開ける
4. 最後の人形（これ以上開けない）に到達したら終了

これが再帰の考え方です！

#### 再帰関数の例

```c
/* 階乗を計算する再帰関数 */
int factorial(int n)
{
    if (n <= 1) {
        return 1;  /* 基底条件 */
    }
    return n * factorial(n - 1);  /* 再帰呼び出し */
}

/* フィボナッチ数列を計算する再帰関数 */
int fibonacci(int n)
{
    if (n <= 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}
```

#### 再帰関数の構成要素

1. **基底条件** - 再帰を終了する条件
2. **再帰呼び出し** - 自分自身を呼び出す部分
3. **問題の分割** - 元の問題をより小さな問題に分割

### 関数のスコープと生存期間
変数には「見える範囲」と「生きている期間」があります。これを理解することで、バグを防げます。

#### ローカル変数とグローバル変数
**家族の例で考えてみましょう：**

- **ローカル変数**：自分の部屋にあるもの（他の人は使えない）
- **グローバル変数**：リビングにあるもの（家族全員が使える）

この違いを理解することは、バグの少ない、保守しやすいプログラムを書くために非常に重要です。

#### ローカル変数の詳細
ローカル変数は関数内で宣言され、その関数内でのみ使用できる変数です。

##### ローカル変数の特徴

```c
void function_example(void)
{
    int local_var = 10;  /* この関数内でのみ有効 */
    
    {  /* ブロックスコープ */
        int block_var = 20;  /* このブロック内でのみ有効 */
        printf("block_var = %d\n", block_var);
    }  /* block_varはここで破棄される */
    
    /* printf("%d\n", block_var); エラー：block_varは見えない */
    
}  /* local_varはここで破棄される */
``` 

##### ローカル変数のメモリ配置

```
スタックメモリの様子：

関数呼び出し時:              関数終了時:
+----------------+           +----------------+
| main()の変数    |           | main()の変数    |
+----------------+           +----------------+
| function()の   |           |     （空）      |
| local_var = 10 |           |                |
+----------------+           +----------------+
```

##### 同名のローカル変数

```c
void func1(void)
{
    int count = 0;  /* func1のcount */
    count++;
    printf("func1: count = %d\n", count);  /* 1 */
}

void func2(void)
{
    int count = 100;  /* func2のcount（func1とは別物） */
    count++;
    printf("func2: count = %d\n", count);  /* 101 */
}

int main(void)
{
    int count = 50;  /* mainのcount */
    
    func1();  /* func1のcountを使用 */
    func2();  /* func2のcountを使用 */
    
    printf("main: count = %d\n", count);  /* 50（変更されない） */
    return 0;
}
```

#### グローバル変数の詳細
グローバル変数は関数の外で宣言され、プログラム全体で使用できる変数です。

##### グローバル変数の宣言と使用

```c
/* グローバル変数の宣言 */
int global_count = 0;      /* 初期化あり */
double global_rate;        /* 初期化なし（0.0になる） */
char global_message[100];  /* 初期化なし（全て0になる） */

void increment_counter(void)
{
    global_count++;  /* どの関数からでもアクセス可能 */
}

void print_counter(void)
{
    printf("カウンター: %d\n", global_count);
}

int main(void)
{
    print_counter();     /* カウンター: 0 */
    increment_counter();
    increment_counter();
    print_counter();     /* カウンター: 2 */
    
    global_count = 10;   /* main関数からも変更可能 */
    print_counter();     /* カウンター: 10 */
    
    return 0;
}
```

##### グローバル変数の初期化

```c
/* グローバル変数は自動的に0で初期化される */
int g_int;          /* 0 */
double g_double;    /* 0.0 */
char g_char;        /* '\0' */
int g_array[10];    /* すべて0 */

/* 明示的な初期化も可能 */
int g_initialized = 100;
char g_string[] = "Hello, Global!";

/* 関数呼び出しによる初期化はできない */
/* int g_value = get_value(); エラー！ */
```

#### 変数の可視性（スコープ）と名前の隠蔽
同じ名前の変数が複数ある場合、最も内側のスコープの変数が優先されます。

```c
int value = 100;  /* グローバル変数 */

void test_scope(void)
{
    printf("1: value = %d\n", value);  /* 100（グローバル） */
    
    int value = 200;  /* ローカル変数（グローバルを隠蔽） */
    printf("2: value = %d\n", value);  /* 200（ローカル） */
    
    {
        int value = 300;  /* ブロック内変数（ローカルを隠蔽） */
        printf("3: value = %d\n", value);  /* 300（ブロック内） */
    }
    
    printf("4: value = %d\n", value);  /* 200（ローカル） */
}

int main(void)
{
    test_scope();
    printf("5: value = %d\n", value);  /* 100（グローバル） */
    return 0;
}
```

#### グローバル変数の問題点と対策

##### 1. 予期しない変更

```c
int total_score = 0;  /* グローバル変数 */

void add_score(int points)
{
    total_score += points;
}

void reset_score(void)
{
    total_score = 0;  /* 他の場所で使用中かもしれない！ */
}

/* より良い設計：引数と戻り値を使用 */
int add_score_safe(int current_score, int points)
{
    return current_score + points;
}
```

##### 2. デバッグの困難さ

```c
/* 悪い例：グローバル変数を多用 */
int g_width, g_height, g_area;

void calculate_area(void)
{
    g_area = g_width * g_height;
}

/* 良い例：引数と戻り値を使用 */
int calculate_area_safe(int width, int height)
{
    return width * height;
}
```

##### 3. 名前の衝突

```c
/* file1.c */
int counter = 0;  /* グローバル変数 */

/* file2.c */
int counter = 0;  /* 同じ名前！リンクエラーになる */

/* 対策：staticを使用してファイルスコープに限定 */
static int counter = 0;  /* このファイル内でのみ有効 */
```

#### ローカル変数とグローバル変数の使い分け

##### ローカル変数を使うべき場合（推奨）

```c
/* 関数内で完結する処理 */
double calculate_average(int arr[], int size)
{
    int i;
    int sum = 0;  /* ローカル変数 */
    
    for (i = 0; i < size; i++) {
        sum += arr[i];
    }
    
    return (double)sum / size;
}

/* 一時的な計算 */
void print_multiplication_table(int n)
{
    int i, j;  /* ループカウンタはローカル変数 */
    
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            printf("%4d", i * j);
        }
        printf("\n");
    }
}
```

##### グローバル変数が適切な場合（限定的）

```c
/* 設定値やフラグ */
int debug_mode = 0;  /* デバッグモードのフラグ */
const double PI = 3.14159265359;  /* 定数 */

/* プログラム全体の状態 */
char program_name[256] = "MyApplication";
int error_count = 0;

void enable_debug(void)
{
    debug_mode = 1;
}

void log_message(const char *msg)
{
    if (debug_mode) {
        printf("[DEBUG] %s\n", msg);
    }
}
```

#### グローバル変数の安全な使用方法

##### 1. constを使用して読み取り専用にする

```c
const int MAX_USERS = 100;
const double TAX_RATE = 0.08;
const char VERSION[] = "1.0.0";
```

##### 2. staticでファイルスコープに限定

```c
/* このファイル内でのみ使用可能 */
static int file_local_counter = 0;

static void increment_counter(void)
{
    file_local_counter++;
}
```

##### 3. アクセス関数を提供する

```c
/* グローバル変数を直接公開しない */
static int score = 0;  /* ファイルスコープ */

/* アクセス関数を通じて操作 */
int get_score(void)
{
    return score;
}

void set_score(int new_score)
{
    if (new_score >= 0) {  /* 検証も可能 */
        score = new_score;
    }
}

void add_score(int points)
{
    if (points > 0) {
        score += points;
    }
}
```

#### まとめ：変数スコープのベストプラクティス

1. **可能な限りローカル変数を使用する**

   - バグが少なく、理解しやすいコードになる

2. **グローバル変数は最小限に**

   - 本当に必要な場合のみ使用
   - constやstaticで保護する

3. **明確な命名規則**

   - グローバル変数にはプレフィックスを付ける（例：g_count）
   - 意味のある名前を使用する

4. **初期化を忘れない**

   - ローカル変数は必ず初期化する
   - グローバル変数の初期値も明示する

#### static変数

```c
void counter_function(void)
{
    static int count = 0;  /* 初回のみ初期化 */
    count++;
    printf("呼び出し回数: %d\n", count);
}
```

### 関数ポインタの基礎
関数へのポインタを使うことで、関数を変数のように扱えます。これは少し高度な話題ですが、基本だけ紹介します。

#### 関数ポインタのイメージ
テレビのリモコンを想像してください。

- リモコンのボタン = 関数ポインタ
- ボタンを押す = 関数を実行
- ボタンの割り当てを変える = 別の関数を指すようにする

#### 基本的な関数ポインタ

```c
/* 関数の定義 */
int add(int a, int b)
{
    return a + b;
}

int multiply(int a, int b)
{
    return a * b;
}

int main(void)
{
    /* 関数ポインタの宣言 */
    int (*operation)(int, int);
    
    /* 関数ポインタに関数を代入 */
    operation = add;
    printf("加算: %d\n", operation(5, 3));
    
    operation = multiply;
    printf("乗算: %d\n", operation(5, 3));
    
    return 0;
}
```

## 実例コード
完全な実装例は以下のファイルを参照してください。

### 基本的な関数の使い方

- [function_basics.c](examples/function_basics.c) - C90準拠版
- [function_basics_c99.c](examples/function_basics_c99.c) - C99準拠版

### 高度な関数の使い方

- [advanced_functions.c](examples/advanced_functions.c) - C90準拠版
- [advanced_functions_c99.c](examples/advanced_functions_c99.c) - C99準拠版

## コンパイルと実行

```bash
# 基本的な関数の例をコンパイル
gcc -Wall -Wextra -pedantic -std=c90 examples/function_basics.c -o function_basics
# 実行
./function_basics

# C99版をコンパイル
gcc -Wall -Wextra -pedantic -std=c99 examples/function_basics_c99.c -o function_basics_c99

# 数学関数を使う場合は-lmを追加
gcc -Wall -Wextra -pedantic examples/advanced_functions.c -lm -o advanced_functions
```

## 注意事項
初心者が関数で間違えやすいポイント。

1. **関数プロトタイプ**: main関数より後に定義する関数は、必ずプロトタイプ宣言が必要

   ```c
   /* NG: プロトタイプなし */
   int main() { 
       add(1, 2);  /* エラー！ */
   }
   int add(int a, int b) { return a + b; }
   ```

2. **配列の扱い**: 配列を関数に渡すときは、サイズ情報も一緒に渡す

   ```c
   /* NG: サイズが分からない */
   void print_array(int arr[]) { /* 要素数不明 */ }
   
   /* OK: サイズも渡す */
   void print_array(int arr[], int size) { /* OK */ }
   ```

3. **再帰の深さ**: 再帰関数は深くなりすぎるとスタックオーバーフローを起こす

4. **グローバル変数**: できるだけ使用を避け、必要な場合は慎重に使用する

5. **static変数**: 関数内でstatic変数を使うと、値が保持される

## 次のステップ
関数の基本を理解したら、以下のトピックに進みましょう。

1. より複雑な関数の設計パターン
2. 関数ポインタと高階関数
3. 可変長引数関数（stdarg.h）
4. インライン関数（C99以降）
5. ライブラリ関数の作成

## 学習フローとコンパイル方法

### 推奨学習順序

1. **理論学習**: README.mdで基本概念を理解
2. **サンプルコード**: examples/の基本例を確認  
3. **演習課題**: exercises/README.mdで課題を確認
4. **実装練習**: solutions/の解答例を参考に自分で実装

### Makefileを使用したコンパイル

```bash
# 全てのプログラムをコンパイル
make all

# 特定のプログラムをコンパイル
make function_basics

# C99版をコンパイル
make function_basics_c99

# プログラムを実行
make run-all

# クリーンアップ
make clean
```

## 次の章へ
[構造体とポインタ](../structures/README.md)

## 参考資料

- [C90規格書](https://www.iso.org/standard/17782.html)
- [C99規格書](https://www.iso.org/standard/29237.html)