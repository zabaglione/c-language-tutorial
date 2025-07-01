# 関数
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
C言語では、通常の変数を渡すと「値のコピー」が渡されます：

```c
void modify_value(int x)
{
    x = 100;  /* 元の変数には影響しない */
}

int main(void)
{
    int num = 10;
    modify_value(num);
    printf("%d\n", num);  /* 10が出力される */
    return 0;
}
```

#### 参照渡し（Call by Reference）
ポインタを使用して、変数のアドレスを渡すことで元の変数を変更できます：

```c
void modify_value(int *x)
{
    *x = 100;  /* 元の変数を変更 */
}

int main(void)
{
    int num = 10;
    modify_value(&num);
    printf("%d\n", num);  /* 100が出力される */
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

#### ローカル変数
```c
void function_example(void)
{
    int local_var = 10;  /* この関数内でのみ有効 */
    /* ... */
}  /* local_varはここで破棄される */
```

#### グローバル変数
```c
int global_var = 100;  /* プログラム全体で有効 */

void function1(void)
{
    printf("%d\n", global_var);  /* アクセス可能 */
}

void function2(void)
{
    global_var = 200;  /* 変更可能 */
}
```

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
テレビのリモコンを想像してください：
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

## 注意事項
初心者が関数で間違えやすいポイント：

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
関数の基本を理解したら、以下のトピックに進みましょう：

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
[第10章: ポインタ基礎](../pointers/README.md)

## 参考資料
- examples/ - 実装例（C90、C99両対応）
- exercises/ - 演習問題
- solutions/ - 解答例
- [C90規格書](https://www.iso.org/standard/17782.html)
- [C99規格書](https://www.iso.org/standard/29237.html)