# 第9章: 関数

## 対応C規格
- **主要対象:** C90
- **学習内容:** 関数の基本、引数と戻り値、関数のスコープ、再帰関数、関数プロトタイプ

## 学習目標

この章を完了すると、以下のことができるようになります：

- 関数の定義と呼び出しができる
- 引数と戻り値を適切に使える
- 関数のスコープを理解する
- 再帰関数を作成できる
- 関数プロトタイプの重要性を理解する

## 概要と詳細

### 関数とは？

関数は、プログラムを「部品」に分けるための仕組みです。大きな問題を小さな部分に分割して解決する「分割統治」の考え方を実現します。

#### 日常生活での関数

関数を理解するために、料理を例に考えてみましょう：

**カレーライスを作る場合：**
1. ご飯を炊く（関数1）
2. 野菜を切る（関数2）
3. 肉を炒める（関数3）
4. カレーを煮込む（関数4）
5. 盛り付ける（関数5）

それぞれの作業を「関数」として独立させることで：
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

### 基本的な関数の例

まずは簡単な例から始めましょう：

```c
#include <stdio.h>

/* 2つの数の合計を計算する関数 */
int add(int a, int b)
{
    int result = a + b;
    return result;
}

int main(void)
{
    int num1 = 10;
    int num2 = 20;
    int sum;
    
    /* 関数の呼び出し */
    sum = add(num1, num2);
    
    printf("%d + %d = %d\n", num1, num2, sum);
    
    return 0;
}
```

**このプログラムの流れ：**
1. main関数が実行開始
2. add関数を呼び出す（10と20を渡す）
3. add関数が計算して結果（30）を返す
4. 結果をsumに格納
5. 結果を表示

### 関数の定義と宣言 

関数を使うには、「宣言」と「定義」を理解する必要があります。

#### なぜ関数プロトタイプが必要？

C言語では「使う前に宣言する」というルールがあります。関数プロトタイプは「この関数がありますよ」とコンパイラに教える役割があります。

#### 関数プロトタイプ（前方宣言）

```c
#include <stdio.h>

/* 関数プロトタイプ */
int multiply(int x, int y);
void print_result(int value);
double calculate_average(int *array, int size);

int main(void)
{
    int a = 5, b = 3;
    int product;
    
    product = multiply(a, b);
    print_result(product);
    
    return 0;
}

/* 関数の実装 */
int multiply(int x, int y)
{
    return x * y;
}

void print_result(int value)
{
    printf("結果: %d\n", value);
}

double calculate_average(int *array, int size)
{
    int i;
    int sum = 0;
    
    if (size <= 0)
    {
        return 0.0;
    }
    
    for (i = 0; i < size; i++)
    {
        sum += array[i];
    }
    
    return (double)sum / size;
}
```

### 引数の渡し方

関数に値を渡す方法は2つあります。この違いを理解することは非常に重要です！

#### 値渡し（Call by Value）

C言語では、通常の変数を渡すと「値のコピー」が渡されます：

```c
/* 値渡しの例（間違った交換関数） */
void swap_wrong(int a, int b)
{
    int temp = a;
    a = b;
    b = temp;
    /* ⚠️ 呼び出し元の変数は変更されない！ */
}

/* ポインタを使った参照渡し（正しい交換関数） */
void swap_correct(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
    /* ✅ 呼び出し元の変数が変更される！ */
}

int main(void)
{
    int x = 10, y = 20;
    
    printf("交換前: x = %d, y = %d\n", x, y);
    
    swap_wrong(x, y);
    printf("値渡し後: x = %d, y = %d\n", x, y);
    
    swap_correct(&x, &y);
    printf("ポインタ渡し後: x = %d, y = %d\n", x, y);
    
    return 0;
}
```

### 様々な関数の種類

関数にはいろいろな種類があります。用途に応じて使い分けましょう。

#### 戻り値のない関数（void関数）

処理だけ行って、結果を返さない関数です：

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

**ロシア人形（マトリョーシカ）**を想像してください：
1. 一番外側の人形を開ける
2. 中に人形があったら、それも開ける
3. さらに中に人形があったら、それも開ける
4. 最後の人形（これ以上開けない）に到達したら終了

これが再帰の考え方です！

```c
/* 階乗を計算する再帰関数 */
int factorial(int n)
{
    /* 基底条件（終了条件）*/
    if (n <= 1)
    {
        return 1;  /* ここで再帰が止まる！ */
    }
    
    /* 再帰呼び出し */
    return n * factorial(n - 1);
}

/* 
   factorial(5)の動き：
   factorial(5) = 5 * factorial(4)
                = 5 * 4 * factorial(3)
                = 5 * 4 * 3 * factorial(2)
                = 5 * 4 * 3 * 2 * factorial(1)
                = 5 * 4 * 3 * 2 * 1
                = 120
*/

/* フィボナッチ数列を計算する再帰関数 */
int fibonacci(int n)
{
    /* 基底条件 */
    if (n <= 1)
    {
        return n;
    }
    
    /* 再帰呼び出し */
    return fibonacci(n - 1) + fibonacci(n - 2);
}
```

### 関数のスコープと生存期間

変数には「見える範囲」と「生きている期間」があります。これを理解することで、バグを防げます。

#### ローカル変数とグローバル変数

**家族の例で考えてみましょう：**
- **ローカル変数**：自分の部屋にあるもの（他の人は使えない）
- **グローバル変数**：リビングにあるもの（家族全員が使える）

```c
#include <stdio.h>

/* グローバル変数 */
int global_count = 0;

void increment_global(void)
{
    global_count++;  /* グローバル変数にアクセス */
}

void local_example(void)
{
    int local_var = 10;  /* ローカル変数 */
    
    printf("ローカル変数: %d\n", local_var);
    /* 関数を抜けるとlocal_varは消滅 */
}

/* static変数の例 */
void counter(void)
{
    static int count = 0;  /* static変数は値を保持 */
    count++;
    printf("呼び出し回数: %d\n", count);
}

int main(void)
{
    int i;
    
    /* staticの効果を確認 */
    for (i = 0; i < 3; i++)
    {
        counter();
    }
    
    return 0;
}
```

### 関数ポインタの基礎

関数へのポインタを使うことで、関数を変数のように扱えます。これは少し高度な話題ですが、基本だけ紹介します。

#### 関数ポインタのイメージ

テレビのリモコンを想像してください：
- リモコンのボタン = 関数ポインタ
- ボタンを押す = 関数を実行
- ボタンの割り当てを変える = 別の関数を指すようにする

```c
#include <stdio.h>

/* 計算用の関数 */
int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }
int multiply(int a, int b) { return a * b; }

int main(void)
{
    /* 関数ポインタの宣言 */
    int (*operation)(int, int);
    int x = 10, y = 5;
    
    /* 関数ポインタに関数を代入 */
    operation = add;
    printf("%d + %d = %d\n", x, y, operation(x, y));
    
    operation = subtract;
    printf("%d - %d = %d\n", x, y, operation(x, y));
    
    operation = multiply;
    printf("%d * %d = %d\n", x, y, operation(x, y));
    
    return 0;
}
```

double calculate_average(int *array, int size)
{
    int i;
    int sum = 0;
    
    if (size <= 0)
    {
        return 0.0;
    }
    
    for (i = 0; i < size; i++)
    {
        sum += array[i];
    }
    
    return (double)sum / size;
}
```

### 引数の渡し方

#### 値渡し（Call by Value）

```c
/* 値渡しの例 */
void swap_wrong(int a, int b)
{
    int temp = a;
    a = b;
    b = temp;
    /* 呼び出し元の変数は変更されない */
}

/* ポインタを使った参照渡し */
void swap_correct(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
    /* 呼び出し元の変数が変更される */
}

int main(void)
{
    int x = 10, y = 20;
    
    printf("交換前: x = %d, y = %d\n", x, y);
    
    swap_wrong(x, y);
    printf("値渡し後: x = %d, y = %d\n", x, y);
    
    swap_correct(&x, &y);
    printf("ポインタ渡し後: x = %d, y = %d\n", x, y);
    
    return 0;
}
```

### 様々な関数の種類

#### 戻り値のない関数（void関数）

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

```c
/* 階乗を計算する再帰関数 */
int factorial(int n)
{
    /* 基底条件 */
    if (n <= 1)
    {
        return 1;
    }
    
    /* 再帰呼び出し */
    return n * factorial(n - 1);
}

/* フィボナッチ数列を計算する再帰関数 */
int fibonacci(int n)
{
    /* 基底条件 */
    if (n <= 1)
    {
        return n;
    }
    
    /* 再帰呼び出し */
    return fibonacci(n - 1) + fibonacci(n - 2);
}
```

### 関数のスコープと生存期間

#### ローカル変数とグローバル変数

```c
#include <stdio.h>

/* グローバル変数 */
int global_count = 0;

void increment_global(void)
{
    global_count++;  /* グローバル変数にアクセス */
}

void local_example(void)
{
    int local_var = 10;  /* ローカル変数 */
    
    printf("ローカル変数: %d\n", local_var);
    /* 関数を抜けるとlocal_varは消滅 */
}

/* static変数の例 */
void counter(void)
{
    static int count = 0;  /* static変数は値を保持 */
    count++;
    printf("呼び出し回数: %d\n", count);
}

int main(void)
{
    int i;
    
    /* staticの効果を確認 */
    for (i = 0; i < 3; i++)
    {
        counter();
    }
    
    return 0;
}
```

### 関数ポインタの基礎

関数へのポインタを使うことで、関数を変数のように扱えます。

```c
#include <stdio.h>

/* 計算用の関数 */
int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }
int multiply(int a, int b) { return a * b; }

int main(void)
{
    /* 関数ポインタの宣言 */
    int (*operation)(int, int);
    int x = 10, y = 5;
    
    /* 関数ポインタに関数を代入 */
    operation = add;
    printf("%d + %d = %d\n", x, y, operation(x, y));
    
    operation = subtract;
    printf("%d - %d = %d\n", x, y, operation(x, y));
    
    operation = multiply;
    printf("%d * %d = %d\n", x, y, operation(x, y));
    
    return 0;
}
```

## 実例コード

完全な実装例は以下のファイルを参照してください：

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

## 演習問題

この章の演習問題は[exercises/README.md](exercises/README.md)にあります。

## 注意事項

1. **関数プロトタイプ**: main関数より後に定義する関数は、必ずプロトタイプ宣言が必要
2. **配列の扱い**: 配列を関数に渡すときは、サイズ情報も一緒に渡す
3. **再帰の深さ**: 再帰関数は深くなりすぎるとスタックオーバーフローを起こす
4. **グローバル変数**: できるだけ使用を避け、必要な場合は慎重に使用する
5. **static変数**: 関数内でstatic変数を使うと、値が保持される

## 次のステップ

関数の基本を理解したら、以下のトピックに進みましょう：

1. より複雑な関数の設計パターン
2. 関数ポインタと高階関数
3. 可変長引数関数（stdarg.h）
4. インライン関数（C99以降）
5. ライブラリ関数の作成