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
    for (i = 1; i <= 10; i++) {
        printf("%d ", i);
    }
    
    printf("\n");
    
    return 0;

```

#### for文の詳細動作

```c
for (i = 0; i < 5; i++) {
    printf("i = %d\n", i);
}


/* 上記は以下と同等 */
i = 0;              /* 初期化（1回のみ実行） */
while (i < 5) {     /* 条件チェック */
    printf("i = %d\n", i);  /* ループ本体 */
    i++;            /* 更新式 */
}

```

#### さまざまなfor文のパターン

```c
/* 逆順ループ */
for (i = 10; i >= 1; i--) {
    printf("%d ", i);
}


/* 2つずつ増加 */
for (i = 0; i <= 20; i += 2) {
    printf("%d ", i);
}


/* 複数変数の制御 */
for (i = 0, j = 10; i < j; i++, j--) {
    printf("i=%d, j=%d\n", i, j);
}

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

    int count = 1;
    
    while (count <= 5) {
        printf("count = %d\n", count);
        count++;
    }
    
    
    return 0;

```

#### while文の実践例

```c
/* ユーザー入力の処理 */
int number;
printf("正の数を入力してください（0で終了）: ");

while (scanf("%d", &number) == 1 && number > 0) {
    printf("入力された数: %d\n", number);
    printf("次の数を入力してください（0で終了）: ");
}


printf("プログラムを終了します。\n");
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
    
    do {
        printf("\nメニュー:\n");
        printf("1. オプション1\n");
        printf("2. オプション2\n");
        printf("3. 終了\n");
        printf("選択してください: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("オプション1が選択されました\n");
                break;
            case 2:
                printf("オプション2が選択されました\n");
                break;
            case 3:
                printf("プログラムを終了します\n");
                break;
            default:
                printf("無効な選択です\n");
                break;
        }
    } while (choice != 3);
    
    return 0;

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
    
    for (i = 1; i <= 10; i++) {
        if (i == 5) {
            break;  /* i が 5 のときループを抜ける */
        }
        printf("%d ", i);
    }
    printf("\nループを抜けました\n");
    
    return 0;

/* 出力: 1 2 3 4 */
```

#### continue文

現在の繰り返しをスキップして、次の繰り返しに進みます。

```c
#include <stdio.h>

int main(void)
{

    int i;
    
    for (i = 1; i <= 10; i++) {
        if (i % 2 == 0) {
            continue;  /* 偶数の場合はスキップ */
        }
        printf("%d ", i);
    }
    printf("\n");
    
    return 0;

/* 出力: 1 3 5 7 9 */
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
    for (i = 1; i <= 9; i++) {
        for (j = 1; j <= 9; j++) {
            printf("%3d ", i * j);
        }
        printf("\n");
    }
    
    return 0;

```

#### 三角形パターンの出力

```c
#include <stdio.h>

int main(void)
{

    int i, j;
    
    /* 星印の三角形 */
    for (i = 1; i <= 5; i++) {
        for (j = 1; j <= i; j++) {
            printf("* ");
        }
        printf("\n");
    }
    
    return 0;

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
    int found = 0;
    
    for (i = 1; i <= 10 && !found; i++) {
        for (j = 1; j <= 10; j++) {
            if (i * j == 36) {
                printf("発見: %d * %d = 36\n", i, j);
                found = 1;
                break;  /* 内側のループを抜ける */
            }
        }
    }
    
    return 0;

```

#### ラベル付きbreak（goto文を使用）

```c
#include <stdio.h>

int main(void)
{

    int i, j;
    
    for (i = 1; i <= 10; i++) {
        for (j = 1; j <= 10; j++) {
            if (i * j == 36) {
                printf("発見: %d * %d = 36\n", i, j);
                goto exit_loops;  /* 両方のループを抜ける */
            }
        }
    }
    
exit_loops:
    printf("ループ終了\n");
    return 0;

```

### 無限ループ ♾

意図的に終了しないループを作成することもあります。

#### 無限ループの作成方法

```c
/* 方法1: for文 */
for (;;) {
    /* 無限ループ */
    if (条件) {
        break;
    }
}


/* 方法2: while文 */
while (1) {
    /* 無限ループ */
    if (条件) {
        break;
    }
}


/* 方法3: do-while文 */
do {
    /* 無限ループ */
    if (条件) {
        break;
    }
} while (1);
```

#### 無限ループの実用例

```c
#include <stdio.h>

int main(void)
{

    int choice;
    
    while (1) {  /* 無限ループ */
        printf("\n=== 計算機 ===\n");
        printf("1. 足し算\n");
        printf("2. 引き算\n");
        printf("3. 終了\n");
        printf("選択: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("入力エラー\n");
            break;
        }
        
        if (choice == 3) {
            printf("終了します\n");
            break;
        }
        
        /* 計算処理... */
    }
    
    return 0;

```

### ループの最適化とベストプラクティス 

#### 効率的なループ

```c
/* NG: 毎回strlen()を呼び出し */
for (i = 0; i < strlen(str); i++) {
    /* 処理 */
}


/* OK: 長さを事前に計算 */
len = strlen(str);
for (i = 0; i < len; i++) {
    /* 処理 */
}

```

#### ループ変数の適切な使用

```c
int main(void)
{

    int i;  /* C90では関数の先頭で宣言 */
    
    for (i = 0; i < 10; i++) {
        /* iはループ外でも有効 */
    }
    
    printf("最終的なi = %d\n", i);  /* 10が出力 */
    
    return 0;

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

1. **数列の出力**
   - 1から20までの数を出力するプログラムを3種類のループで作成してください

2. **偶数・奇数の判定**
   - 1から50までの数で、偶数のみを出力するプログラムを作成してください

3. **階乗の計算**
   - 入力された数の階乗を計算するプログラムを作成してください

### 応用問題

4. **素数判定**
   - 入力された数が素数かどうかを判定するプログラムを作成してください

5. **フィボナッチ数列**
   - n項目までのフィボナッチ数列を出力するプログラムを作成してください

6. **パターン出力**
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

7. **成績管理システム**
   - 複数の学生の成績を入力し、平均・最高・最低点を計算するプログラム

8. **簡易ゲーム**
   - 数当てゲームを作成してください（1-100の範囲で乱数を生成）

9. **データ検索**
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
  for (int i = 0; i < 10; i++)   /* C99以降 */
      /* 処理 */
  
  ```

##  よくある間違い

### 1. 無限ループの作成

```c
/* NG: 終了条件の記述ミス */
for (i = 0; i > 10; i++)   /* 最初から条件が偽 */
    /* 実行されない */


/* NG: 更新式の記述ミス */
for (i = 0; i < 10; i--)   /* 負の方向に進む */
    /* 無限ループ */

```

### 2. セミコロンの位置

```c
/* NG: for文の後にセミコロン */
for (i = 0; i < 10; i++);  /* 空文が実行される */

    printf("%d\n", i);     /* ループ外で実行 */


/* OK: 正しい記述 */
for (i = 0; i < 10; i++) 
    printf("%d\n", i);

```

### 3. ループ変数の範囲外アクセス

```c
/* NG: 配列の範囲を超える */
int arr[10];
for (i = 0; i <= 10; i++)   /* i=10で範囲外 */
    arr[i] = i;


/* OK: 正しい範囲 */
for (i = 0; i < 10; i++) 
    arr[i] = i;

```

##  次の章へ

ループ処理を理解したら、[配列](../arrays/README.md) に進んでください。

##  参考資料

- [for文詳細](https://ja.cppreference.com/w/c/language/for)
- [while文詳細](https://ja.cppreference.com/w/c/language/while)
- [break・continue文](https://ja.cppreference.com/w/c/language/break)
