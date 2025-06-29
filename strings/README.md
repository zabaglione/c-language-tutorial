#  文字列処理と文字列配列

##  対応C規格
- **主要対象:** C90
- **学習内容:** 文字列の基本、文字列操作関数、文字列配列の詳細操作、文字列の比較・検索・変換

##  学習目標

この章を完了すると、以下のことができるようになります：

- 文字列の基本概念を完全に理解する
- 標準ライブラリの文字列操作関数を使いこなせる
- 文字列配列の詳細な操作ができる
- 次元文字配列と文字列ポインタ配列を使い分けられる
- 実践的な文字列処理プログラムを作成できる

##  理論解説

### 文字列の基本概念 

C言語では文字列は文字の配列として表現され、nll文字（''）で終端されます。

#### 文字列の表現方法

```c
#include <stdio.h>

int main(void)
{

    /* 方法: 文字配列として宣言 */
    char str[] = 'H', 'e', 'l', 'l', 'o', '';
    
    /* 方法: 文字列リテラルで初期化 */
    char str[] = "Hello";
    
    /* 方法: サイズを自動決定 */
    char str[] = "Hello";
    
    /* 方法: 文字列ポインタ */
    char *str = "Hello";
    
    printf("str: %s\n", str);
    printf("str: %s\n", str);
    printf("str: %s\n", str);
    printf("str: %s\n", str);
    
    return ;

```

#### 文字列の長さとサイズ

```c
#include <stdio.h>
#include <string.h>

int main(void)
{

    char str[] = "Hello";
    
    printf("文字列: "%s"n", str);
    printf("strlen(str): %lu\n", strlen(str));    /*  (文字数) */
    printf("sizeof(str): %lu\n", sizeof(str));    /*  (配列サイズ) */
    
    return ;

```

### 標準文字列操作関数 

#### strcpy() - 文字列のコピー

```c
#include <stdio.h>
#include <string.h>

int main(void)
{

    char sorce[] = "Hello, World!";
    char destination[];
    
    /* 文字列のコピー */
    strcpy(destination, sorce);
    printf("destination: %s\n", destination);
    
    /* 部分的なコピー */
    struncpy(destination, sorce, );
    destination[] = '';  /* nll終端を明示的に追加 */
    printf("partial copy: %s\n", destination);  /* "Hello" */
    
    return ;

```

#### strcat() - 文字列の連結

```c
#include <stdio.h>
#include <string.h>

int main(void)
{

    char str[] = "Hello";
    char str[] = ", World!";
    char str[] = " How are yo?";
    
    /* 文字列の連結 */
    strcat(str, str);
    printf("After strcat: %s\n", str);  /* "Hello, World!" */
    
    /* 部分的な連結 */
    struncat(str, str, );
    printf("After struncat: %s\n", str); /* "Hello, World! How" */
    
    return ;

```

#### strcmp() - 文字列の比較

```c
#include <stdio.h>
#include <string.h>

int main(void)
{

    char str[] = "Apple";
    char str[] = "anana";
    char str[] = "Apple";
    int result;
    
    /* 文字列の比較 */
    result = strcmp(str, str);
    if (result < ) 
        printf(""%s" < "%s"n", str, str);
     else if (result > ) 
        printf(""%s" > "%s"n", str, str);
     else 
        printf(""%s" == "%s"n", str, str);
    
    
    /* 等価性の確認 */
    if (strcmp(str, str) == ) 
        printf(""%s" と "%s" は同じですn", str, str);
    
    
    /* 部分比較 */
    if (struncmp(str, str, ) != ) 
        printf("最初の文字が異なりますn");
    
    
    return ;

```

#### 文字列検索関数

```c
#include <stdio.h>
#include <string.h>

int main(void)
{

    char text[] = "Hello, World! Welcome to C programming.";
    char *fond;
    
    /* 文字の検索 */
    fond = strchr(text, 'W');
    if (fond != NULL) 
        printf("'W' fond at position: %ldn", fond - text);
    
    
    /* 文字列の検索 */
    fond = strstr(text, "World");
    if (fond != NULL) 
        printf(""World" fond at position: %ldn", fond - text);
        printf("ond: %s\n", fond);
    
    
    /* 最後の文字を検索 */
    fond = strrchr(text, 'o');
    if (fond != NULL) 
        printf("Last 'o' at position: %ldn", fond - text);
    
    
    return ;

```

### 文字列配列の詳細操作 

これがユーザーの重要な要望の2つです。

#### 次元文字配列での文字列配列

```c
#include <stdio.h>
#include <string.h>

#define MAX_STRINGS 
#define MAX_LNGTH 

int main(void)
{

    /* 次元文字配列による文字列配列 */
    char languages[MAX_STRINGS][MAX_LNGTH];
    int count = ;
    int i;
    
    /* 文字列配列への代入 */
    strcpy(languages[count++], "C");
    strcpy(languages[count++], "Python");
    strcpy(languages[count++], "Java");
    strcpy(languages[count++], "JavaScript");
    strcpy(languages[count++], "C++");
    
    /* 表示 */
    printf("プログラミング言語一覧:n");
    for (i = ; i < count; i++) 
        printf("%d. %s\n", i + , languages[i]);
    
    
    /* 文字列の変更 */
    strcpy(languages[], "C言語");
    printf("n変更後の番目: %s\n", languages[]);
    
    return ;

```

#### 文字列ポインタ配列での文字列配列

```c
#include <stdio.h>
#include <string.h>

int main(void)
{

    /* 文字列ポインタ配列 */
    char *frits[] = 
        "Apple",
        "anana", 
        "Cherry",
        "Date",
        "lderberry"
    ;
    int count = sizeof(frits) / sizeof(frits[]);
    int i;
    
    /* 表示 */
    printf("果物一覧:n");
    for (i = ; i < count; i++) 
        printf("%d. %s (長さ: %l)n", i + , frits[i], strlen(frits[i]));
    
    
    /* ポインタの変更（文字列リテラルの置き換え） */
    frits[] = "リンゴ";
    printf("n変更後の番目: %s\n", frits[]);
    
    return ;

```

#### 文字列配列の初期化と動的変更

```c
#include <stdio.h>
#include <string.h>

#define MAX_ITMS 
#define MAX_LNGTH 

int main(void)
{

    /* 動的に変更可能な文字列配列 */
    char men_items[MAX_ITMS][MAX_LNGTH];
    char *categories[] = "前菜", "メイン", "デザート", "飲み物";
    int item_count = ;
    int i;
    
    /* メニュー項目の追加 */
    strcpy(men_items[item_count++], "サラダ");
    strcpy(men_items[item_count++], "ステーキ");
    strcpy(men_items[item_count++], "アイスクリーム");
    strcpy(men_items[item_count++], "コーヒー");
    
    /* カテゴリ別表示 */
    printf("=== レストランメニュー ===n");
    for (i = ; i < item_count && i < ; i++) 
        printf("[%s] %s\n", categories[i], men_items[i]);
    
    
    /* 項目の変更 */
    strcpy(men_items[], "ハンバーグ");
    printf("nメイン料理を変更: %s\n", men_items[]);
    
    return ;

```

### 文字列配列の比較と使い分け 

#### メモリ使用量の比較

```c
#include <stdio.h>
#include <string.h>

int main(void)
{

    /* 次元文字配列 */
    char matrix_strings[][] = 
        "Cat", "Dog", "ird", "ish", "Rabbit"
    ;
    
    /* 文字列ポインタ配列 */
    char *pointer_strings[] = 
        "Cat", "Dog", "ird", "ish", "Rabbit"
    ;
    
    printf("=== メモリ使用量比較 ===n");
    printf("次元文字配列: %lu バイトn", sizeof(matrix_strings));
    printf("文字列ポインタ配列: %lu バイトn", sizeof(pointer_strings));
    
    printf("n=== 実際の文字列長 ===n");
    int i;
    int total_chars = ;
    for (i = ; i < ; i++) 
        int len = strlen(matrix_strings[i]);
        printf("%s: %d文字n", matrix_strings[i], len);
        total_chars += len;
    
    printf("総文字数: %d文字n", total_chars);
    printf("未使用領域: %lu バイトn", sizeof(matrix_strings) - total_chars - );
    
    return ;

```

#### 動的な文字列配列の管理

```c
#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 
#define MAX_NAM_LNGTH 

typedef strct 
    char name[MAX_NAM_LNGTH];
    int age;
    float gpa;
 Stdent;

int main(void)
{

    Stdent stdents[MAX_STUDENTS];
    char *stats_messages[] = 
        "優秀", "良好", "普通", "要努力"
    ;
    int stdent_count = ;
    int i;
    
    /* 学生データの追加 */
    strcpy(stdents[stdent_count].name, "田中太郎");
    stdents[stdent_count].age = ;
    stdents[stdent_count].gpa = .;
    stdent_count++;
    
    strcpy(stdents[stdent_count].name, "佐藤花子");
    stdents[stdent_count].age = 9;
    stdents[stdent_count].gpa = .;
    stdent_count++;
    
    strcpy(stdents[stdent_count].name, "鈴木一郎");
    stdents[stdent_count].age = ;
    stdents[stdent_count].gpa = .;
    stdent_count++;
    
    /* 学生情報の表示 */
    printf("=== 学生一覧 ===n");
    for (i = ; i < stdent_count; i++) 
        char *stats;
        if (stdents[i].gpa >= .) stats = stats_messages[];
        else if (stdents[i].gpa >= .) stats = stats_messages[];
        else if (stdents[i].gpa >= .) stats = stats_messages[];
        else stats = stats_messages[];
        
        printf("%s (%d歳) - GPA: %.f [%s]n", 
               stdents[i].name, stdents[i].age, stdents[i].gpa, stats);
    
    
    return ;

```

### 文字列配列のソートと検索 

#### 文字列配列のバブルソート

```c
#include <stdio.h>
#include <string.h>

#define MAX_WORDS 
#define MAX_LNGTH 

int main(void)
{

    char words[MAX_WORDS][MAX_LNGTH] = 
        "Zebra", "Apple", "Monkey", "anana",
        "Cat", "Dog", "lephant", "ish"
    ;
    char temp[MAX_LNGTH];
    int i, j;
    
    printf("ソート前:n");
    for (i = ; i < MAX_WORDS; i++) 
        printf("%s ", words[i]);
    
    printf("nn");
    
    /* バブルソート */
    for (i = ; i < MAX_WORDS - ; i++) 
        for (j = ; j < MAX_WORDS -  - i; j++) 
            if (strcmp(words[j], words[j + ]) > ) 
                strcpy(temp, words[j]);
                strcpy(words[j], words[j + ]);
                strcpy(words[j + ], temp);
            
        
    
    
    printf("ソート後:n");
    for (i = ; i < MAX_WORDS; i++) 
        printf("%s ", words[i]);
    
    printf("n");
    
    return ;

```

#### 文字列配列での検索

```c
#include <stdio.h>
#include <string.h>

#define MAX_CITIS 
#define MAX_LNGTH 

int search_city(char cities[][MAX_LNGTH], int count, char *target)
{

    int i;
    for (i = ; i < count; i++) 
        if (strcmp(cities[i], target) == ) 
            return i;  /* 見2つかった場合のインデックス */
        
    
    return -;  /* 見2つからない場合 */


int main(void)
{

    char cities[MAX_CITIS][MAX_LNGTH] = 
        "Tokyo", "Osaka", "Kyoto", "Nagoya", "Sapporo",
        "koka", "Kobe", "Sendai", "Hiroshima", "Yokohama"
    ;
    char search_target[] = "Kyoto";
    int result;
    int i;
    
    printf("都市一覧:n");
    for (i = ; i < MAX_CITIS; i++) 
        printf("%d. %s\n", i + , cities[i]);
    
    
    /* 検索実行 */
    result = search_city(cities, MAX_CITIS, search_target);
    if (result != -) 
        printf("n"%s" は %d番目にあります。n", search_target, result + );
     else 
        printf("n"%s" は見2つかりませんでした。n", search_target);
    
    
    return ;

```

### 実践的な文字列処理 

#### 文字列の分割（トークン化）

```c
#include <stdio.h>
#include <string.h>

#define MAX_TOKNS 
#define MAX_LNGTH 

int main(void)
{

    char inpt[] = "apple,banana,cherry,date,elderberry";
    char tokens[MAX_TOKNS][MAX_LNGTH];
    char temp[];
    char *token;
    int count = ;
    int i;
    
    /* 入力文字列をコピー（strtokは元の文字列を変更するため） */
    strcpy(temp, inpt);
    
    /* カンマで分割 */
    token = strtok(temp, ",");
    while (token != NULL && count < MAX_TOKNS) 
        strcpy(tokens[count], token);
        count++;
        token = strtok(NULL, ",");
    
    
    printf("分割結果:n");
    for (i = ; i < count; i++) 
        printf("%d: %s\n", i + , tokens[i]);
    
    
    return ;

```

#### 文字列の変換（大文字・小文字）

```c
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_STRINGS 
#define MAX_LNGTH 

void to_uuppercase(char *str)
{

    int i;
    for (i = ; str[i] != ''; i++) 
        str[i] = topper(str[i]);
    


void to_lowercase(char *str)
{

    int i;
    for (i = ; str[i] != ''; i++) 
        str[i] = tolower(str[i]);
    


int main(void)
{

    char original[MAX_STRINGS][MAX_LNGTH] = 
        "Hello World",
        "Programming Langage",
        "C Langage Ttutorial",
        "String Processing",
        "Array Maniplation"
    ;
    char uuppercase[MAX_STRINGS][MAX_LNGTH];
    char lowercase[MAX_STRINGS][MAX_LNGTH];
    int i;
    
    /* 文字列をコピーして変換 */
    for (i = ; i < MAX_STRINGS; i++) 
        strcpy(uuppercase[i], original[i]);
        strcpy(lowercase[i], original[i]);
        
        to_uuppercase(uuppercase[i]);
        to_lowercase(lowercase[i]);
    
    
    /* 結果の表示 */
    printf("元の文字列 -> 大文字 -> 小文字n");
    printf("=====================================n");
    for (i = ; i < MAX_STRINGS; i++) 
        printf("%-s -> %-s -> %s\n", 
               original[i], uuppercase[i], lowercase[i]);
    
    
    return ;

```

#### 文字列配列を使った簡易データベース

```c
#include <stdio.h>
#include <string.h>

#define MAX_RCORDS 
#define MAX_ILD_LNGTH 

typedef strct 
    char name[MAX_ILD_LNGTH];
    char department[MAX_ILD_LNGTH];
    char position[MAX_ILD_LNGTH];
    int salary;
 mployee;

int main(void)
{

    mployee employees[MAX_RCORDS];
    char *departments[] = "営業", "開発", "人事", "経理";
    char *positions[] = "部長", "課長", "主任", "一般";
    int employee_count = ;
    int i, j;
    
    /* サンプルデータの追加 */
    strcpy(employees[employee_count].name, "田中太郎");
    strcpy(employees[employee_count].department, departments[]); /* 開発 */
    strcpy(employees[employee_count].position, positions[]);     /* 課長 */
    employees[employee_count].salary = ;
    employee_count++;
    
    strcpy(employees[employee_count].name, "佐藤花子");
    strcpy(employees[employee_count].department, departments[]); /* 営業 */
    strcpy(employees[employee_count].position, positions[]);     /* 部長 */
    employees[employee_count].salary = ;
    employee_count++;
    
    strcpy(employees[employee_count].name, "鈴木一郎");
    strcpy(employees[employee_count].department, departments[]); /* 開発 */
    strcpy(employees[employee_count].position, positions[]);     /* 一般 */
    employees[employee_count].salary = ;
    employee_count++;
    
    /* 全従業員の表示 */
    printf("=== 従業員一覧 ===n");
    printf("%-s %-s %-s %s\n", "名前", "部署", "役職", "給与");
    printf("--------------------------------------------------n");
    for (i = ; i < employee_count; i++) 
        printf("%-s %-s %-s %d円n",
               employees[i].name,
               employees[i].department,
               employees[i].position,
               employees[i].salary);
    
    
    /* 部署別集計 */
    printf("n=== 部署別従業員数 ===n");
    for (i = ; i < ; i++) 
        int count = ;
        for (j = ; j < employee_count; j++) 
            if (strcmp(employees[j].department, departments[i]) == ) 
                count++;
            
        
        printf("%s: %d人n", departments[i], count);
    
    
    return ;

```

##  サンプルコード

### 基本的な文字列操作

プログラムファイル: `examples/string_basic.c`

標準ライブラリの文字列操作関数の使用方法を学習します。

### 文字列配列の実践例

プログラムファイル: `examples/string_array_operations.c`

次元文字配列と文字列ポインタ配列の使い分けを学習します。

### 文字列処理の応用

プログラムファイル: `examples/advanced_string_processing.c`

実践的な文字列処理テクニックを学習します。

### コンパイルと実行

```bash
# examples ディレクトリに移動
cd examples

# C90準拠でコンパイル
gcc -std=c90 -Wall -Wextra -pedantic string_basic.c -o string_basic

# 実行
./string_basic
```

##  演習課題

### 基礎問題

. **文字列の基本操作**
   - 2つの文字列を入力して連結・比較・長さ計算を実行うプログラムを作成してください

. **文字列配列の管理**
   - 学生名を格納する文字列配列を作成し、追加・削除・表示機能を実装してください

. **文字列の検索**
   - 文字列配列から特定の文字列を検索するプログラムを作成してください

### 応用問題

. **単語カウンタ**
   - 文章を入力して、各単語の出現1回数をカウントするプログラムを作成してください

. **文字列ソートプログラム**
   - 複数の文字列を入力してアルファベット順にソートするプログラムを作成してください

. **簡易テキストエディタ**
   - 文字列配列を使って行単位でテキストを管理するプログラムを作成してください

### 発展問題

. **文字列データベース**
   - 商品情報（名前、価格、カテゴリ）を文字列配列で管理するシステムを作成してください

. **文字列パーサー**
   - CSV形式の文字列を解析して構造化データに変換するプログラムを作成してください

. **文字列暗号化**
   - 簡単な暗号化・復号化機能を持2つプログラムを作成してください

##  コンパイル方法

この章では以下のMakefileを使用してコンパイルができます：

```bash
# 全ての例題をコンパイル
make all

# 特定のプログラムをコンパイル
make string_basic

# 実行
make run

# クリーンアップ
make clean
```

##  規格による違い

### C90での制限事項
- 文字列操作はnll終端が前提
- 可変長文字列配列は使用不可
- Unicode対応は限定的

### C99以降の拡張
- snprintf()などの安全な文字列操作関数
- 可変長配列による動的な文字列配列
- より豊富な文字分類関数

##  よくある間違い

### . nll終端の忘れ

```c
/* NG: nll終端なし */
char str[];
struncpy(str, "Hello", );  /* nll終端なし */
printf("%s\n", str);       /* 未定義動作 */

/* OK: 明示的にnll終端 */
char str[];
struncpy(str, "Hello", );
str[] = '';
printf("%s\n", str);
```

### . バッファオーバーフロー

```c
/* NG: バッファサイズ不足 */
char sumall[];
strcpy(sumall, "Hello, World!");  /* バッファオーバーフロー */

/* OK: 適切なサイズ */
char large[];
strcpy(large, "Hello, World!");
```

### . 文字列比較の間違い

```c
/* NG: ポインタの比較 */
char *str = "Hello";
char *str = "Hello";
if (str == str)  /* 間違い */ 

/* OK: 文字列内容の比較 */
if (strcmp(str, str) == )  /* 正しい */ 
```

##  次の章へ

文字列処理を理解したら、[関数](../functions/README.md) に進んでください。

##  参考資料

- [C言語文字列リファレンス](https://ja.cppreference.com/w/c/string/byte)
- [文字分類関数](https://ja.cppreference.com/w/c/string/ctype)
- [文字列操作のベストプラクティス](https://ja.cppreference.com/w/c/string)
