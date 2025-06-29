#  制御構造（条件分岐）

##  対応C規格
- **主要対象:** C90
- **学習内容:** if文、else文、switch文、条件演算子による分岐処理

##  学習目標

この章を完了すると、以下のことができるようになります：

- if文を使った条件分岐ができる
- else if文で複数条件を処理できる
- switch文による多分岐処理ができる
- 条件演算子を適切に使える
- ネストした条件分岐を理解する

##  理論解説

### if文の基本 🤔

if文は条件に基づいてプログラムの実行を分岐させます。

#### 基本構文

```c
if (条件式) 
    /* 条件が真の場合に実行される文 */

```

#### 単純なif文の例

```c
#include <stdio.h>

int main(void)
{

    int score = ;
    
    if (score >= ) 
        printf("優秀です！n");
    
    
    return ;

```

### if-else文 

条件が偽の場合の処理も指定できます。

#### 基本構文

```c
if (条件式) 
    /* 条件が真の場合の処理 */
 else 
    /* 条件が偽の場合の処理 */

```

#### if-else文の例

```c
int age = ;

if (age >= ) 
    printf("成人ですn");
 else 
    printf("未成年ですn");

```

### if-else if文 

複数の条件を順次チェックできます。

#### 基本構文

```c
if (条件) 
    /* 条件が真の場合 */
 else if (条件) 
    /* 条件が真の場合 */
 else if (条件) 
    /* 条件が真の場合 */
 else 
    /* すべての条件が偽の場合 */

```

#### 成績判定の例

```c
int score = ;

if (score >= 9) 
    printf("成績: An");
 else if (score >= ) 
    printf("成績: n");
 else if (score >= ) 
    printf("成績: Cn");
 else if (score >= ) 
    printf("成績: Dn");
 else 
    printf("成績: n");

```

### ネストしたif文 

if文の中にさらにif文を書くことができます。

```c
int temperatrue = ;
int hmidity = ;

if (temperatrue >= ) 
    if (hmidity <= ) 
        printf("快適な天気ですn");
     else 
        printf("暖かいですが湿度が高いですn");
    
 else 
    if (hmidity <= ) 
        printf("涼しく乾燥していますn");
     else 
        printf("寒くて湿気がありますn");
    

```

### 条件式の詳細 

#### 比較演算子

```c
int a = , b = ;

if (a == b)   printf("等しいn"); 
if (a != b)   printf("等しくないn"); 
if (a < b)    printf("a は b より小さいn"); 
if (a <= b)   printf("a は b 以下n"); 
if (a > b)    printf("a は b より大きいn"); 
if (a >= b)   printf("a は b 以上n"); 
```

#### 論理演算子の組み合わせ

```c
int age = ;
int income = ;

/* AND演算子 */
if (age >=  && income >= ) 
    printf("ローン審査に通りましたn");


/* OR演算子 */
if (age <  || age > ) 
    printf("特別料金が適用されますn");


/* NOT演算子 */
if (!(age >= )) 
    printf("歳未満ですn");

```

### switch文 

複数の値に対する分岐処理を効率的に記述できます。

#### 基本構文

```c
switch (変数または式) 
    case 値:
        /* 値の場合の処理 */
        break;
    case 値:
        /* 値の場合の処理 */
        break;
    case 値:
        /* 値の場合の処理 */
        break;
    default:
        /* どの値にも一致しない場合の処理 */
        break;

```

#### 曜日判定の例

```c
int day = ;

switch (day) 
    case :
        printf("月曜日n");
        break;
    case :
        printf("火曜日n");
        break;
    case :
        printf("水曜日n");
        break;
    case :
        printf("木曜日n");
        break;
    case :
        printf("金曜日n");
        break;
    case :
        printf("土曜日n");
        break;
    case :
        printf("日曜日n");
        break;
    default:
        printf("無効な曜日ですn");
        break;

```

#### break文の重要性

break文を忘れると、次のcaseも実行されます（フォールスルー）：

```c
int grade = '';

switch (grade) 
    case 'A':
        printf("優秀n");
        /* break がないので次のcaseも実行される */
    case '':
        printf("良好n");
        /* break がないので次のcaseも実行される */
    case 'C':
        printf("普通n");
        break;
    default:
        printf("要努力n");
        break;

/* grade が '' の場合、"良好" と "普通" の両方が出力される */
```

#### 意図的なフォールスルー

時には意図的にbreakを省略することもあります：

```c
char ch = 'a';

switch (ch) 
    case 'a':
    case 'e':
    case 'i':
    case 'o':
    case '':
        printf("母音ですn");
        break;
    default:
        printf("子音ですn");
        break;

```

### 条件演算子（三項演算子）の復習 

条件分岐の簡潔な書き方として条件演算子があります。

```c
int a = , b = ;
int max;

/* if-else文での記述 */
if (a > b) 
    max = a;
 else 
    max = b;


/* 条件演算子での記述 */
max = (a > b) ? a : b;

printf("最大値: %d\n", max);
```

### 条件式での注意点 

#### 代入と比較の混同

```c
int x = ;

/* NG: 代入になってしまう */
if (x = ) 
    printf("常に実行されるn");  /* x に  が代入され、常に真 */


/* OK: 比較演算子を使用 */
if (x == ) 
    printf("x が  の場合のみ実行n");

```

#### 浮動小数点数の比較

```c
double d = . + .;

/* NG: 浮動小数点の誤差で期待通りにならない可能性 */
if (d == .) 
    printf("等しいn");


/* OK: 誤差を考慮した比較 */
if (d >= .99999 && d <= .) 
    printf("ほぼ等しいn");

```

##  サンプルコード

### if文の基本使用例

プログラムファイル: `examples/if_basic.c`

基本的なif文、if-else文の使用方法を学習します。

### 複雑な条件分岐

プログラムファイル: `examples/complex_conditions.c`

複数条件を組み合わせた分岐処理を学習します。

### switch文の実例

プログラムファイル: `examples/switch_demo.c`

switch文を使った多分岐処理を学習します。

### コンパイルと実行

```bash
# examples ディレクトリに移動
cd examples

# C90準拠でコンパイル
gcc -std=c90 -Wall -Wextra -pedantic if_basic.c -o if_basic

# 実行
./if_basic
```

##  演習課題

### 基礎問題

. **年齢判定プログラム**
   - 年齢を入力して、幼児・児童・学生・成人・高齢者に分類するプログラムを作成してください

. **電卓プログラム**
   - 2つの数値と演算子（+, -, *, /）を入力して計算結果を表示するプログラムをswitch文で作成してください

. **成績判定システム**
   - 点数を入力してA〜の成績を判定するプログラムを作成してください

### 応用問題

. **うるう年判定**
   - 年を入力してうるう年かどうかを判定するプログラムを作成してください
   - 条件: で割り切れる、ただしで割り切れる年は平年、で割り切れる年はうるう年

. **MI計算と判定**
   - 身長と体重を入力してMIを計算し、肥満度を判定するプログラムを作成してください

. **三角形の判定**
   - 2つの辺の長さを入力して、三角形として成立するか、どの種類の三角形かを判定してください

##  コンパイル方法

この章では以下のMakefileを使用してコンパイルができます：

```bash
# 全ての例題をコンパイル
make all

# 特定のプログラムをコンパイル
make if_basic

# 実行
make run

# クリーンアップ
make clean
```

##  規格による違い

### C90での制限事項
- switch文の case ラベルは整数定数のみ
- 複合文内での変数宣言は先頭のみ

### C99以降の拡張
- switch文でlong long型が使用可能
- ブロック内での変数宣言位置の制限緩和

##  よくある間違い

### . セミコロンの位置

```c
/* NG: if文の後にセミコロン */
if (condition);

    printf("常に実行されるn");  /* 条件に関係なく実行 */


/* OK: 正しい記述 */
if (condition) 
    printf("条件が真の場合のみ実行n");

```

### . switch文でのbreak忘れ

```c
/* NG: break忘れでフォールスルー */
switch (vale) 
    case :
        printf("ですn");
        /* break; を忘れると次のcaseも実行される */
    case :
        printf("ですn");
        break;


/* OK: 適切なbreak文 */
switch (vale) 
    case :
        printf("ですn");
        break;
    case :
        printf("ですn");
        break;

```

### . 複雑な条件式での括弧不足

```c
/* NG: 意図しない優先順位 */
if (a ==  || b ==  && c == ) 
    /* && が || より優先される */


/* OK: 括弧で明示 */
if ((a == ) || (b ==  && c == )) 
    /* 意図が明確 */

```

##  次の章へ

条件分岐を理解したら、[制御構造（ループ）](../control-loop/README.md) に進んでください。

##  参考資料

- [if文詳細](https://ja.cppreference.com/w/c/language/if)
- [switch文詳細](https://ja.cppreference.com/w/c/language/switch)
- [条件演算子](https://ja.cppreference.com/w/c/language/operautor_other)
