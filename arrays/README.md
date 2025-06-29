#  配列と文字列配列

##  対応C規格
- **主要対象:** C90
- **学習内容:** 次元配列、多次元配列、文字列配列、配列の初期化、配列とポインタの関係

##  学習目標

この章を完了すると、以下のことができるようになります：

- 次元配列の宣言・初期化・使用ができる
- 多次元配列を理解して活用できる
- 文字列配列の扱い方を完全に理解する
- char配列とchar*配列の違いを把握する
- 配列を使った実践的なプログラムを作成できる

##  理論解説

### 配列の基本概念 

配列は同じデータ型の要素を連続したメモリ領域に格納するデータ構造です。

#### 次元配列の宣言

```c
データ型 配列名[要素数];
```

#### 基本的な配列の使用例

```c
#include <stdio.h>

int main(void)
{

    int numbers[5];         /* 5個のint型要素を持つ配列 */
    int i;
    
    /* 配列への値の代入 */
    numbers[0] = 10;
    numbers[1] = 20;
    numbers[2] = 30;
    numbers[3] = 40;
    numbers[4] = 50;
    
    /* 配列の値を出力 */
    for (i = 0; i < 5; i++) {
        printf("numbers[%d] = %d\n", i, numbers[i]);
    }
    
    
    return 0;

```

### 配列の初期化 

#### 宣言時の初期化

```c
/* 方法1: 全要素を明示的に初期化 */
int scores[5] = {85, 92, 78, 91, 88};

/* 方法2: 部分的な初期化（残りは0で初期化） */
int values[10] = {1, 2, 3};  /* values[0]=1, values[1]=2, values[2]=3, 残りは0 */

/* 方法3: サイズを省略（要素数から自動決定） */
int grades[] = {95, 87, 92, 76, 89};  /* サイズは5になる */

/* 方法4: 全要素を0で初期化 */
int zeros[10] = {0};        /* 全要素が0 */
```

#### C90での初期化の制限

```c
int main(void)
{

    int size = 5;
    /* int arr[size];  <- C90では不可（Variable Length Array） */
    
    /* C90では定数でサイズを指定 */
    #define ARRAY_SIZE 5
    int arr[ARRAY_SIZE] = {1, 2, 3, 4, 5};
    
    return 0;

```

### 配列の操作 

#### 配列要素へのアクセス

```c
#include <stdio.h>

int main(void)
{

    int data[5] = {10, 20, 30, 40, 50};
    int i;
    
    /* 読み取り */
    printf("3番目の要素: %d\n", data[2]);  /* 30が出力 */
    
    /* 書き込み */
    data[2] = 35;
    
    /* ループでのアクセス */
    for (i = 0; i < 5; i++) {
        data[i] = data[i] * 2;  /* 各要素を2倍 */
    }
    
    
    return 0;

```

#### 配列のサイズ計算

```c
#include <stdio.h>

int main(void)
{

    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size;
    int i;
    
    /* 配列のサイズを計算 */
    size = sizeof(numbers) / sizeof(numbers[0]);
    
    printf("配列のサイズ: %d\n", size);  /* 10が出力 */
    
    for (i = 0; i < size; i++) {
        printf("%d ", numbers[i]);
    }
    
    printf("\n");
    
    return 0;

```

### 文字配列（文字列） 

#### char配列による文字列

```c
#include <stdio.h>

int main(void)
{

    char str1[6] = {'H', 'e', 'l', 'l', 'o', '\0'};  /* 明示的初期化 */
    char str2[6] = "Hello";                           /* 文字列リテラル */
    char str3[] = "Hello";                            /* サイズ自動決定 */
    
    printf("str1: %s\n", str1);
    printf("str2: %s\n", str2);
    printf("str3: %s\n", str3);
    
    return 0;

```

#### 文字配列の操作

```c
#include <stdio.h>
#include <string.h>

int main(void)
{

    char buffer[50];
    char name[20];
    int i;
    
    /* 文字列のコピー */
    strcpy(buffer, "Hello, World!");
    printf("buffer: %s\n", buffer);
    
    /* 文字づつのアクセス */
    strcpy(name, "Alice");
    for (i = 0; name[i] != '\0'; i++) {
        printf("name[%d] = '%c'\n", i, name[i]);
    }
    
    
    return 0;

```

### 文字列配列の扱い 

これがユーザーの重要な要望の一2つです。

#### 方法: 次元char配列

```c
#include <stdio.h>
#include <string.h>

int main(void)
{

    /* 各文字列の最大長を20文字とする5つの文字列 */
    char names[5][20];  /* 19文字+null終端文字 */
    int i;
    
    /* 文字列配列への代入 */
    strcpy(names[0], "Alice");
    strcpy(names[1], "Bob");
    strcpy(names[2], "Charlie");
    strcpy(names[3], "David");
    strcpy(names[4], "Eve");
    
    /* 文字列配列の表示 */
    for (i = 0; i < 5; i++) {
        printf("names[%d] = %s\n", i, names[i]);
    }
    
    
    return 0;

```

#### 方法: char*配列（文字列ポインタ配列）

```c
#include <stdio.h>

int main(void)
{

    /* 文字列ポインタの配列 */
    char *fruits[] = {
        "Apple",
        "Banana", 
        "Cherry",
        "Date"
    };
    int i;
    
    /* 文字列ポインタ配列の表示 */
    for (i = 0; i < 4; i++) {
        printf("fruits[%d] = %s\n", i, fruits[i]);
    }
    
    
    return 0;

```

#### 文字列配列の初期化パターン

```c
/* パターン1: 2次元char配列の初期化 */
char cities[3][10] = {
    "Tokyo",
    "Osaka", 
    "Kyoto"
};

/* パターン2: char*配列の初期化 */
char *colors[] = {
    "Red",
    "Green",
    "Blue",
    "Yellow"
};

/* パターン3: 混合初期化 */
char languages[4][15] = {
    "C",           /* 文字列リテラル */
    "Python",        /* 文字列リテラル */
    "Java",        /* 文字列リテラル */
    "JavaScript"     /* 文字列リテラル */
};
```

### char配列 vs char*配列の違い 

これは文字列配列を扱う上で重要な概念です。

#### メモリ配置の違い

```c
#include <stdio.h>

int main(void)
{

    /* 2次元char配列 */
    char matrix[3][4] = {"ABC", "DEF", "GHI"};
    
    /* char*配列 */
    char *pointers[] = {"ABC", "DEF", "GHI"};
    
    printf("=== 2次元char配列 ===\n");
    printf("全体サイズ: %lu バイト\n", sizeof(matrix));        /* 12バイト */
    printf("1行のサイズ: %lu バイト\n", sizeof(matrix[0]));    /* 4バイト */
    
    printf("\n=== char*配列 ===\n");
    printf("全体サイズ: %lu バイト\n", sizeof(pointers));      /* 24バイト（8バイトx3） */
    printf("要素のサイズ: %lu バイト\n", sizeof(pointers[0])); /* 8バイト（ポインタサイズ） */
    
    return 0;

```

#### 変更可能性の違い

```c
#include <stdio.h>
#include <string.h>

int main(void)
{

    /* 2次元char配列（変更可能） */
    char mutable_array[3][10] = {"Hello", "World", "Test"};
    
    /* char*配列（文字列リテラルは変更不可） */
    char *immutable_array[] = {"Hello", "World", "Test"};
    
    /* 配列の内容変更 */
    strcpy(mutable_array[0], "Hi");     /* OK: 内容変更可能 */
    /* strcpy(immutable_array[0], "Hi"); <- NG: 文字列リテラルは変更不可 */
    
    /* ポインタの変更 */
    /* mutable_array[0] = "New"; <- NG: 配列名は変更不可 */
    immutable_array[0] = "New";         /* OK: ポインタ変更可能 */
    
    printf("mutable_array[0]: %s\n", mutable_array[0]);     /* "Hi" */
    printf("immutable_array[0]: %s\n", immutable_array[0]); /* "New" */
    
    return 0;

```

#### 用途に応じた使い分け

```c
/* 固定文字列の配列（読み取り専用） - char*配列が適している */
char *error_messages[] = {
    "Success",
    "File not found",
    "Permission denied",
    "Out of memory"
};

/* 動的に変更する文字列配列 - 2次元char配列が適している */
char user_inputs[10][100];  /* ユーザー入力を格納 */

/* 設定項目など（変更の可能性あり） - char*配列が適している */
char *config_items[] = {
    "debug=on",
    "log_level=info", 
    "max_connections=100"
};
```

### 多次元配列 

#### 次元配列の基本

```c
#include <stdio.h>

int main(void)
{

    int matrix[3][4] = {
        {1,  2,  3,  4},
        {5,  6,  7,  8},
        {9, 10, 11, 12}
    };
    int i, j;
    
    /* 2次元配列の表示 */
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 4; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    
    return 0;

```

#### 次元配列の例

```c
#include <stdio.h>

int main(void)
{

    /* 3次元配列: [2][3][4] */
    int cube[2][3][4] = {
        {
            {1, 2, 3, 4},
            {5, 6, 7, 8},
            {9, 10, 11, 12}
        },
        {
            {13, 14, 15, 16},
            {17, 18, 19, 20},
            {21, 22, 23, 24}
        }
    };
    int i, j, k;
    
    for (i = 0; i < 2; i++) {
        printf("=== Layer %d ===\n", i);
        for (j = 0; j < 3; j++) {
            for (k = 0; k < 4; k++) {
                printf("%d ", cube[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }
    
    return 0;

```

### 配列の実践的応用 

#### 成績管理システム

```c
#include <stdio.h>

#define MAX_STUDENTS 5
#define MAX_SUBJECTS 3

int main(void)
{

    char students[MAX_STUDENTS][20] = {
        "Alice", "Bob", "Charlie", "David", "Eve"
    };
    char subjects[MAX_SUBJECTS][10] = {
        "Math", "English", "Science"
    };
    int scores[MAX_STUDENTS][MAX_SUBJECTS] = {
        {85, 92, 78},  /* Alice */
        {90, 87, 85},  /* Bob */
        {95, 91, 89},  /* Charlie */
        {82, 79, 88},  /* David */
        {91, 88, 93}   /* Eve */
    };
    int i, j;
    int total;
    
    /* 成績表の表示 */
    printf("Student    ");
    for (j = 0; j < MAX_SUBJECTS; j++) {
        printf("%-10s", subjects[j]);
    }
    printf("Average\n");
    printf("----------------------------------------\n");
    
    for (i = 0; i < MAX_STUDENTS; i++) {
        printf("%-10s ", students[i]);
        total = 0;
        for (j = 0; j < MAX_SUBJECTS; j++) {
            printf("%-10d", scores[i][j]);
            total += scores[i][j];
        }
        printf("%.1f\n", (double)total / MAX_SUBJECTS);
    }
    
    return 0;

```

#### 文字列配列のソート

```c
#include <stdio.h>
#include <string.h>

#define MAX_NAMES 5
#define MAX_LENGTH 20

int main(void)
{

    char names[MAX_NAMES][MAX_LENGTH] = {
        "Charlie", "Alice", "Eve", "Bob", "David"
    };
    char temp[MAX_LENGTH];
    int i, j;
    
    printf("ソート前:\n");
    for (i = 0; i < MAX_NAMES; i++) {
        printf("%s ", names[i]);
    }
    printf("\n");
    
    /* バブルソート */
    for (i = 0; i < MAX_NAMES - 1; i++) {
        for (j = 0; j < MAX_NAMES - 1 - i; j++) {
            if (strcmp(names[j], names[j + 1]) > 0) {
                strcpy(temp, names[j]);
                strcpy(names[j], names[j + 1]);
                strcpy(names[j + 1], temp);
            }
        }
    }
    
    printf("ソート後:\n");
    for (i = 0; i < MAX_NAMES; i++) {
        printf("%s ", names[i]);
    }
    printf("\n");
    
    return 0;

```

### 配列とポインタの関係 

配列名はその先頭要素へのポインタとして動作します。

```c
#include <stdio.h>

int main(void)
{

    int arr[5] = {10, 20, 30, 40, 50};
    int *ptr;
    int i;
    
    ptr = arr;  /* arr は &arr[0] と同じ */
    
    printf("=== 配列表記 ===\n");
    for (i = 0; i < 5; i++) {
        printf("arr[%d] = %d\n", i, arr[i]);
    }
    
    printf("\n=== ポインタ表記 ===\n");
    for (i = 0; i < 5; i++) {
        printf("*(ptr + %d) = %d\n", i, *(ptr + i));
    }
    
    /* 配列名とポインタの関係 */
    printf("\n=== アドレス比較 ===\n");
    printf("arr = %p\n", (void*)arr);
    printf("&arr[0] = %p\n", (void*)&arr[0]);
    printf("ptr = %p\n", (void*)ptr);
    
    return 0;

```

## 実践的なプログラム例

### 基本的な配列操作（C90準拠）

#### 1次元配列の基本
```c
#include <stdio.h>

int main(void)
{
    /* C90では先頭で全ての変数を宣言 */
    int numbers[5] = {10, 20, 30, 40, 50};
    int total = 0;
    int i;
    
    /* 配列の全要素を表示 */
    printf("=== 配列の内容 ===\n");
    for (i = 0; i < 5; i++) {
        printf("numbers[%d] = %d\n", i, numbers[i]);
        total += numbers[i];
    }
    
    printf("合計: %d\n", total);
    printf("平均: %.1f\n", (double)total / 5);
    
    return 0;
}
```
📁 **ファイル**: [`examples/array_basics.c`](examples/array_basics.c)  
📁 **C99版**: [`examples/array_basics_c99.c`](examples/array_basics_c99.c)

### 文字列配列の実例（C90準拠）

#### char配列 vs char*配列の違い
```c
#include <stdio.h>
#include <string.h>

int main(void)
{
    /* C90では先頭で全ての変数を宣言 */
    char cities[3][20] = {"Tokyo", "Osaka", "Kyoto"};  /* 2次元char配列 */
    char *fruits[] = {"Apple", "Banana", "Cherry"};    /* char*配列 */
    int i;
    
    printf("=== 2次元char配列 ===\n");
    for (i = 0; i < 3; i++) {
        printf("cities[%d] = %s\n", i, cities[i]);
    }
    
    printf("\n=== char*配列 ===\n");
    for (i = 0; i < 3; i++) {
        printf("fruits[%d] = %s\n", i, fruits[i]);
    }
    
    /* メモリサイズの違い */
    printf("\n=== メモリサイズ比較 ===\n");
    printf("cities配列のサイズ: %lu バイト\n", (unsigned long)sizeof(cities));
    printf("fruits配列のサイズ: %lu バイト\n", (unsigned long)sizeof(fruits));
    
    return 0;
}
```
📁 **ファイル**: [`examples/string_arrays.c`](examples/string_arrays.c)  
📁 **C99版**: [`examples/string_arrays_c99.c`](examples/string_arrays_c99.c)

### 多次元配列の活用（C90準拠）

#### 3x4行列の操作
```c
#include <stdio.h>

int main(void)
{
    /* C90では先頭で全ての変数を宣言 */
    int matrix[3][4] = {
        {1,  2,  3,  4},
        {5,  6,  7,  8},
        {9, 10, 11, 12}
    };
    int i, j;
    int row_sum;
    
    printf("=== 行列の表示 ===\n");
    for (i = 0; i < 3; i++) {
        row_sum = 0;
        for (j = 0; j < 4; j++) {
            printf("%3d ", matrix[i][j]);
            row_sum += matrix[i][j];
        }
        printf("| 行の合計: %d\n", row_sum);
    }
    
    return 0;
}
```
📁 **ファイル**: [`examples/multidimensional_arrays.c`](examples/multidimensional_arrays.c)  
📁 **C99版**: [`examples/multidimensional_arrays_c99.c`](examples/multidimensional_arrays_c99.c)

### コンパイル方法

#### 基本的なコンパイル（C90準拠）
```bash
gcc -std=c90 -Wall -Wextra -pedantic array_basics.c -o array_basics
```

#### Makefileを使用した場合
```bash
# 全てのプログラムをコンパイル
make all

# 特定のプログラムをコンパイル  
make array_basics

# C99版をコンパイル
make array_basics_c99

# プログラムを実行
make run-all

# クリーンアップ
make clean
```

## 演習課題と解答例

### 利用可能な演習問題
[演習問題詳細](exercises/README.md)では、配列と文字列配列の理解を深める課題が提供されています。

#### 演習6-1: 配列の基本操作（C90準拠）
```c
#include <stdio.h>

int main(void)
{
    /* C90では先頭で全ての変数を宣言 */
    int numbers[10] = {15, 23, 8, 42, 7, 31, 19, 5, 28, 36};
    int i;
    int max, min, sum;
    double average;
    
    /* 最大値、最小値、合計の初期化 */
    max = min = sum = numbers[0];
    
    /* 配列の全要素を処理 */
    for (i = 1; i < 10; i++) {
        if (numbers[i] > max) max = numbers[i];
        if (numbers[i] < min) min = numbers[i];
        sum += numbers[i];
    }
    
    average = (double)sum / 10;
    
    printf("=== 配列の統計情報 ===\n");
    printf("最大値: %d\n", max);
    printf("最小値: %d\n", min);
    printf("合計: %d\n", sum);
    printf("平均: %.1f\n", average);
    
    return 0;
}
```
📁 **解答例**: [`solutions/ex6_1.c`](solutions/ex6_1.c)  
📁 **C99版**: [`solutions/ex6_1_c99.c`](solutions/ex6_1_c99.c)

#### 演習6-2: 成績管理システム（C90準拠）
```c
#include <stdio.h>

#define NUM_STUDENTS 5
#define NUM_SUBJECTS 4

/* 学生名と科目名 */
char students[NUM_STUDENTS][20] = {
    "田中太郎", "佐藤花子", "鈴木一郎", "高橋美咲", "伊藤健太"
};

char subjects[NUM_SUBJECTS][10] = {
    "国語", "数学", "英語", "理科"
};

int main(void)
{
    /* C90では先頭で全ての変数を宣言 */
    int grades[NUM_STUDENTS][NUM_SUBJECTS];
    int i, j;
    
    printf("=== 成績管理システム ===\n");
    printf("5人の学生の4科目の成績を入力してください。\n\n");
    
    /* 成績の入力 */
    for (i = 0; i < NUM_STUDENTS; i++) {
        printf("--- %s の成績 ---\n", students[i]);
        for (j = 0; j < NUM_SUBJECTS; j++) {
            printf("%s: ", subjects[j]);
            scanf("%d", &grades[i][j]);
        }
        printf("\n");
    }
    
    /* 成績表の表示処理などが続く... */
    
    return 0;
}
```
📁 **解答例**: [`solutions/ex6_2.c`](solutions/ex6_2.c)  
📁 **C99版**: [`solutions/ex6_2_c99.c`](solutions/ex6_2_c99.c)

#### 演習6-3: 文字列配列の操作（C90準拠）
```c
#include <stdio.h>
#include <string.h>

#define NUM_PREFECTURES 10
#define MAX_NAME_LENGTH 20

/* 都道府県名のサンプルデータ */
char prefectures[NUM_PREFECTURES][MAX_NAME_LENGTH] = {
    "東京都", "神奈川県", "大阪府", "愛知県", "埼玉県",
    "千葉県", "兵庫県", "北海道", "福岡県", "静岡県"
};

int main(void)
{
    /* C90では先頭で全ての変数を宣言 */
    char working_array[NUM_PREFECTURES][MAX_NAME_LENGTH];
    int i;
    
    printf("=== 都道府県管理システム ===\n\n");
    
    /* 作業用配列にコピー */
    for (i = 0; i < NUM_PREFECTURES; i++) {
        strcpy(working_array[i], prefectures[i]);
    }
    
    /* ソート、検索処理などが続く... */
    
    return 0;
}
```
📁 **解答例**: [`solutions/ex6_3.c`](solutions/ex6_3.c)  
📁 **C99版**: [`solutions/ex6_3_c99.c`](solutions/ex6_3_c99.c)

### 演習問題一覧
1. **演習6-1**: 配列の基本操作（最大値・最小値・平均値）
2. **演習6-2**: 成績管理システム（5人×4科目）
3. **演習6-3**: 文字列配列の操作（都道府県管理）
4. **演習6-4**: 行列演算（加算・減算・乗算・転置）
5. **演習6-5**: 簡易辞書プログラム（英和・和英検索）

### チャレンジ問題
- **チャレンジ1**: ソートアルゴリズムの実装と比較
- **チャレンジ2**: ライフゲーム（Conway's Game of Life）

すべての演習には**C90版**と**C99版**の両方の解答例が提供されています。

## 学習フローとコンパイル方法

### 推奨学習順序
1. **理論学習**: このREADME.mdで配列の概念を理解
2. **サンプルコード**: examples/の基本例を確認
3. **演習課題**: exercises/README.mdで課題を確認
4. **実装練習**: solutions/の解答例を参考に自分で実装

### Makefileを使用したコンパイル
```bash
# 全ての例題をコンパイル
make all

# 特定のプログラムをコンパイル
make array_basics         # C90版
make array_basics_c99     # C99版

# 全てのプログラムを実行
make run-all

# C90準拠でのテスト
make test

# 複数のC標準でのテスト
make test-standards

# クリーンアップ
make clean

# ヘルプ表示
make help
```

### 手動コンパイル
```bash
# C90準拠でコンパイル（推奨）
gcc -std=c90 -Wall -Wextra -pedantic examples/array_basics.c -o array_basics

# C99準拠でコンパイル
gcc -std=c99 -Wall -Wextra -pedantic examples/array_basics_c99.c -o array_basics_c99

# 実行
./array_basics
```

## C90とC99の違い

### C90の特徴（このチュートリアルの基準）
```c
int main(void)
{
    /* すべての変数を関数の先頭で宣言 */
    int numbers[5] = {1, 2, 3, 4, 5};
    int i;
    int sum = 0;
    
    /* 配列サイズは定数で指定 */
    #define ARRAY_SIZE 10
    int arr[ARRAY_SIZE];
    
    /* forループは従来のスタイル */
    for (i = 0; i < 5; i++) {
        sum += numbers[i];
    }
    
    return 0;
}
```

### C99の拡張機能
```c
int main(void)
{
    int numbers[5] = {1, 2, 3, 4, 5};
    
    /* forループ内での変数宣言（C99） */
    for (int i = 0; i < 5; i++) {
        printf("%d ", numbers[i]);
    }
    
    /* 必要な時点での変数宣言（C99） */
    int sum = 0;
    for (int i = 0; i < 5; i++) {
        sum += numbers[i];
    }
    
    /* 可変長配列（VLA）も可能（C99） */
    int size = 10;
    int vla[size];  /* C90では不可 */
    
    return 0;
}
```

### このチュートリアルでの方針
- **C90版**: 基準となる実装、互換性重視
- **C99版**: 現代的な書き方、読みやすさ重視
- **学習推奨**: まずC90で基礎を固めてからC99を学習

## よくある間違いとデバッグ方法

### 1. 配列の境界外アクセス

#### 間違った例
```c
/* NG: 配列の範囲を超える */
int arr[5] = {1, 2, 3, 4, 5};
printf("%d\n", arr[5]);  /* 範囲外アクセス - 未定義動作 */
```

#### 正しい例
```c
/* OK: 正しい範囲でアクセス */
#include <stdio.h>

int main(void)
{
    int arr[5] = {1, 2, 3, 4, 5};
    int i;
    
    /* 安全な配列アクセス */
    for (i = 0; i < 5; i++) {  /* i < 5 であることを確認 */
        printf("arr[%d] = %d\n", i, arr[i]);
    }
    
    return 0;
}
```

### 2. 文字列配列の初期化忘れ

#### 間違った例
```c
/* NG: 初期化されていない文字配列 */
char str[20];
printf("%s\n", str);     /* 未定義動作 */
```

#### 正しい例
```c
/* OK: 適切な初期化 */
#include <stdio.h>
#include <string.h>

int main(void)
{
    char str[20] = "";       /* 空文字列で初期化 */
    strcpy(str, "Hello");    /* 後から代入 */
    printf("%s\n", str);
    
    return 0;
}
```

### 3. 配列代入の間違い

#### 間違った例
```c
/* NG: 配列は直接代入できない */
char str1[20], str2[20] = "Hello";
str1 = str2;             /* コンパイルエラー */
```

#### 正しい例
```c
/* OK: strcpyを使用 */
#include <string.h>

char str1[20], str2[20] = "Hello";
strcpy(str1, str2);      /* 正しい文字列コピー */
```

### 4. C90とC99の混在エラー

#### C90でコンパイル時のエラー例
```c
/* C90ではエラーになる書き方 */
int main(void)
{
    int arr[5] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i++) {  /* C90ではNG */
        printf("%d ", arr[i]);
    }
    return 0;
}
```

#### 正しいC90の書き方
```c
/* C90準拠の書き方 */
int main(void)
{
    int arr[5] = {1, 2, 3, 4, 5};
    int i;  /* 先頭で宣言 */
    
    for (i = 0; i < 5; i++) {
        printf("%d ", arr[i]);
    }
    return 0;
}
```

### デバッグのコツ
- **境界チェック**: 配列アクセス時は必ずインデックスが範囲内かチェック
- **初期化の確認**: 配列や文字列は使用前に必ず初期化
- **コンパイル標準の確認**: `-std=c90` または `-std=c99` の指定を確認
- **解答例との比較**: solutions/の正解コードと比較して違いを確認

##  次の章へ

配列と文字列配列を理解したら、[文字列処理](../strings/README.md) に進んでください。

##  参考資料

- [C言語配列リファレンス](https://ja.cppreference.com/w/c/language/array)
- [文字列操作関数](https://ja.cppreference.com/w/c/string/byte)
- [多次元配列の詳細](https://ja.cppreference.com/w/c/language/array)
