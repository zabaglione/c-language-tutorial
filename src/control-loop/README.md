# 第5章 制御構造（ループ）

##  対応C規格
- **主要対象:** C90
- **学習内容:** for文、while文、do-while文、break文、continue文、ネストしたループ

##  学習目標

この章を完了すると、以下のことができるようになります：

- for文を使った繰り返し処理ができる
- while文とdo-while文の違いを理解する
- break文とcontinue文を適切に使える
- ネストしたループを理解して活用できる
- ループを使った実践的なプログラムを作成できる

##  理論解説

### for文 

最も一般的なループ文で、初期化・条件・更新を実行で記述できます。

#### 基本構文

```c
for (初期化; 条件式; 更新式) 
    /* 繰り返し実行される文 */

```

#### 基本的な使用例

```c
#include <stdio.h>

int main(void)
{

    int i;
    
    /* 1から10まで出力 */
    for (i = 1; i <= 10; i++) 
        printf("%d ", i);
    
    printf("\n");
    
    return 0;

```

#### for文の詳細動作

```c
for (i = ; i < ; i++) 
    printf("i = %d\n", i);


/* 上記は以下と同等 */
i = ;              /* 初期化（1回のみ実行） */
while (i < )      /* 条件チェック */
    printf("i = %d\n", i);  /* ループ本体 */
    i++;            /* 更新式 */

```

#### さまざまなfor文のパターン

```c
/* 逆順ループ */
for (i = ; i >= ; i--) 
    printf("%d ", i);


/* 2つず2つ増加 */
for (i = ; i <= ; i += ) 
    printf("%d ", i);


/* 複数変数の制御 */
for (i = , j = ; i < j; i++, j--) 
    printf("i=%d, j=%d\n", i, j);

```

### while文 

条件が真である間、繰り返し処理を実行します。

#### 基本構文

```c
while (条件式) 
    /* 繰り返し実行される文 */

```

#### while文の使用例

```c
#include <stdio.h>

int main(void)
{

    int count = ;
    
    while (count <= ) 
        printf("count = %d\n", count);
        count++;
    
    
    return ;

```

#### while文の実践例

```c
/* ユーザー入力の処理 */
int number;
printf("正の数を入力してください（で終了）: ");

while (scanf("%d", &number) ==  && number > ) 
    printf("入力された数: %d\n", number);
    printf("次の数を入力してください（で終了）: ");


printf("プログラムを終了します。n");
```

### do-while文 

最低1回は実行され、その後条件をチェックするループです。

#### 基本構文

```c
do 
    /* 最低1回は実行される文 */
 while (条件式);
```

#### do-while文の使用例

```c
#include <stdio.h>

int main(void)
{

    int choice;
    
    do 
        printf("nメニュー:n");
        printf(". オプションn");
        printf(". オプションn");
        printf(". 終了n");
        printf("選択してください: ");
        scanf("%d", &choice);
        
        switch (choice) 
            case :
                printf("オプションが選択されましたn");
                break;
            case :
                printf("オプションが選択されましたn");
                break;
            case :
                printf("プログラムを終了しますn");
                break;
            default:
                printf("無効な選択ですn");
                break;
        
     while (choice != );
    
    return ;

```

### break文とcontinue文 ⏭

ループの流れを制御する特別な文です。

#### break文

ループを強制的に終了します。

```c
#include <stdio.h>

int main(void)
{

    int i;
    
    for (i = ; i <= ; i++) 
        if (i == ) 
            break;  /* i が  のときループを抜ける */
        
        printf("%d ", i);
    
    printf("nループを抜けましたn");
    
    return ;

/* 出力:      */
```

#### continue文

現在の繰り返しをスキップして、次の繰り返しに進みます。

```c
#include <stdio.h>

int main(void)
{

    int i;
    
    for (i = ; i <= ; i++) 
        if (i %  == ) 
            continue;  /* 偶数の場合はスキップ */
        
        printf("%d ", i);
    
    printf("n");
    
    return ;

/* 出力:     9 */
```

### ネストしたループ 

ループの中にさらにループを含む構造です。

#### 二重ループの例

```c
#include <stdio.h>

int main(void)
{

    int i, j;
    
    /* 九九表の作成 */
    for (i = ; i <= 9; i++) 
        for (j = ; j <= 9; j++) 
            printf("%d ", i * j);
        
        printf("n");
    
    
    return ;

```

#### 三角形パターンの出力

```c
#include <stdio.h>

int main(void)
{

    int i, j;
    
    /* 星印の三角形 */
    for (i = ; i <= ; i++) 
        for (j = ; j <= i; j++) 
            printf("* ");
        
        printf("n");
    
    
    return ;

/*
出力:
* 
* * 
* * * 
* * * * 
* * * * * 
*/
```

### ループでのbreak・continueの応用 

#### ネストしたループでのbreak

```c
#include <stdio.h>

int main(void)
{

    int i, j;
    int fond = ;
    
    for (i = ; i <=  && !fond; i++) 
        for (j = ; j <= ; j++) 
            if (i * j == ) 
                printf("発見: %d * %d = n", i, j);
                fond = ;
                break;  /* 内側のループを抜ける */
            
        
    
    
    return ;

```

#### ラベル付きbreak（goto文を使用）

```c
#include <stdio.h>

int main(void)
{

    int i, j;
    
    for (i = ; i <= ; i++) 
        for (j = ; j <= ; j++) 
            if (i * j == ) 
                printf("発見: %d * %d = n", i, j);
                goto exit_loops;  /* 両方のループを抜ける */
            
        
    
    
exit_loops:
    printf("ループ終了n");
    return ;

```

### 無限ループ ♾

意図的に終了しないループを作成することもあります。

#### 無限ループの作成方法

```c
/* 方法: for文 */
for (;;) 
    /* 無限ループ */
    if (条件) break;


/* 方法: while文 */
while () 
    /* 無限ループ */
    if (条件) break;


/* 方法: do-while文 */
do 
    /* 無限ループ */
    if (条件) break;
 while ();
```

#### 無限ループの実用例

```c
#include <stdio.h>

int main(void)
{

    int choice;
    
    while ()   /* 無限ループ */
        printf("n=== 計算機 ===n");
        printf(". 足し算n");
        printf(". 引き算n");
        printf(". 終了n");
        printf("選択: ");
        
        if (scanf("%d", &choice) != ) 
            printf("入力エラーn");
            break;
        
        
        if (choice == ) 
            printf("終了しますn");
            break;
        
        
        /* 計算処理... */
    
    
    return ;

```

### ループの最適化とベストプラクティス 

#### 効率的なループ

```c
/* NG: 毎回strlen()を呼び出し */
for (i = ; i < strlen(str); i++) 
    /* 処理 */


/* OK: 長さを事前に計算 */
len = strlen(str);
for (i = ; i < len; i++) 
    /* 処理 */

```

#### ループ変数の適切な使用

```c
int main(void)
{

    int i;  /* C90では関数の先頭で宣言 */
    
    for (i = ; i < ; i++) 
        /* iはループ外でも有効 */
    
    
    printf("最終的なi = %d\n", i);  /* が出力 */
    
    return ;

```

##  サンプルコード

### 基本的なループ例

プログラムファイル: `examples/loop_basic.c`

for、while、do-while文の基本的な使用方法を学習します。

### ネストしたループ

プログラムファイル: `examples/nested_loops.c`

二重・三重ループの使用例を学習します。

### break・continue文

プログラムファイル: `examples/break_continue.c`

ループ制御文の使い方を学習します。

### コンパイルと実行

```bash
# examples ディレクトリに移動
cd examples

# C90準拠でコンパイル
gcc -std=c90 -Wall -Wextra -pedantic loop_basic.c -o loop_basic

# 実行
./loop_basic
```

##  演習課題

### 基礎問題

. **数列の出力**
   - からまでの数を出力するプログラムを種類のループで作成してください

. **偶数・奇数の判定**
   - からまでの数で、偶数のみを出力するプログラムを作成してください

. **階乗の計算**
   - 入力された数の階乗を計算するプログラムを作成してください

### 応用問題

. **素数判定**
   - 入力された数が素数かどうかを判定するプログラムを作成してください

. **フィボナッチ数列**
   - n項目までのフィボナッチ数列を出力するプログラムを作成してください

. **パターン出力**
   - 以下のようなパターンを出力するプログラムを作成してください：
   ```
   *
   **
   ***
   ****
   *****
   ****
   ***
   **
   *
   ```

### 発展問題

. **成績管理システム**
   - 複数の学生の成績を入力し、平均・最高・最低点を計算するプログラム

. **簡易ゲーム**
   - 数当てゲームを作成してください（-の範囲で乱数を生成）

. **データ検索**
   - 配列の中から特定の値を検索するプログラムを作成してください

##  コンパイル方法

この章では以下のMakefileを使用してコンパイルができます：

```bash
# 全ての例題をコンパイル
make all

# 特定のプログラムをコンパイル
make loop_basic

# 実行
make run

# クリーンアップ
make clean
```

##  規格による違い

### C90での制限事項
- ループ変数は関数の先頭で宣言する必要がある
- for文内での変数宣言は不可

### C99以降の拡張
- for文内での変数宣言が可能
  ```c
  for (int i = ; i < ; i++)   /* C99以降 */
      /* 処理 */
  
  ```

##  よくある間違い

### . 無限ループの作成

```c
/* NG: 終了条件の記述ミス */
for (i = ; i > ; i++)   /* 最初から条件が偽 */
    /* 実行されない */


/* NG: 更新式の記述ミス */
for (i = ; i < ; i--)   /* 負の方向に進む */
    /* 無限ループ */

```

### . セミコロンの位置

```c
/* NG: for文の後にセミコロン */
for (i = ; i < ; i++);  /* 空文が実行される */

    printf("%d\n", i);     /* ループ外で実行 */


/* OK: 正しい記述 */
for (i = ; i < ; i++) 
    printf("%d\n", i);

```

### . ループ変数の範囲外アクセス

```c
/* NG: 配列の範囲を超える */
int arr[];
for (i = ; i <= ; i++)   /* i=で範囲外 */
    arr[i] = i;


/* OK: 正しい範囲 */
for (i = ; i < ; i++) 
    arr[i] = i;

```

##  次の章へ

ループ処理を理解したら、[配列](../arrays/README.md) に進んでください。

##  参考資料

- [for文詳細](https://ja.cppreference.com/w/c/language/for)
- [while文詳細](https://ja.cppreference.com/w/c/language/while)
- [break・continue文](https://ja.cppreference.com/w/c/language/break)
