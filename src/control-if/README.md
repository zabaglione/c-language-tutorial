# 条件分岐
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
##  概要と詳細
### 条件分岐の世界へようこそ
私たちは日常生活で常に「もし〜なら」という判断をしています。「もし雨が降ったら傘を持つ」「もし電車が遅れたらバスで行く」など、状況に応じて行動を変えています。
プログラミングでも同じように、条件によって処理を変える必要があります。この章では、C言語で条件分岐を実現する方法を学びます。
### なぜ条件分岐が必要なのか？
条件分岐がないプログラムは、いつも同じ処理しかできません。それでは：
- ユーザーの入力に応じた処理ができない
- エラーが発生しても対処できない
- 状況に応じた最適な処理を選べない
条件分岐を使うことで、プログラムに「知能」を与えることができます。
### if文の基本（もし〜なら）
if文は最も基本的な条件分岐です。日本語の「もし〜なら〜する」をそのままプログラムで表現できます。
#### 基本構文
```c
if (条件式) {
    /* 条件が真（正しい）の場合に実行される処理 */
}
```
**重要なポイント**：
- 条件式は括弧 `()` で囲む
- 処理部分は波括弧 `{}` で囲む（1行でも推奨）
- 条件が偽（正しくない）の場合は、if文の中は実行されない
#### 実生活に例えた単純なif文
```c
int temperature = 28;
if (temperature > 25) {
    printf("暑いのでエアコンをつけます\n");
}
```
#### 波括弧の重要性
```c
/* 危険な書き方（波括弧なし） */
if (score >= 80)
    printf("合格です\n");
    printf("おめでとう！\n");  /* これは常に実行される！ */

/* 安全な書き方（波括弧あり） */
if (score >= 80) {
    printf("合格です\n");
    printf("おめでとう！\n");  /* 両方とも条件が真の時だけ実行 */
}
```
### if-else文（そうでなければ）
現実の判断では「もし〜なら〜する、そうでなければ〜する」という二者択一の場面がよくあります。if-else文はまさにこの状況を表現します。
#### 基本構文
```c
if (条件式) {
    /* 条件が真（正しい）の場合の処理 */
} else {
    /* 条件が偽（正しくない）の場合の処理 */
}
```
**ポイント**：
- どちらか一方の処理が必ず実行される
- elseは「それ以外すべて」を意味する
#### 実用的なif-else文の例
```c
/* 成人判定 */
int age = 19;
if (age >= 20) {
    printf("成人です\n");
printf("選挙権があります\n");
} else {
    printf("未成年です\n");
    printf("あと%d年で成人です\n", 20 - age);
}
/* パスワード認証 */
int password = 1234;
int input = 1235;
if (password == input) {
    printf("ログイン成功！\n");
printf("ようこそ！\n");
} else {
    printf("パスワードが違います\n");
printf("もう一度お試しください\n");
}
/* 営業判定 */
int hour = 18;
if (hour >= 9 && hour < 17) {
    printf("営業中です\n");
} else {
    printf("営業時間外です\n");
}
```
#### よくある使い方：エラー処理
```c
int balance = 1000;  /* 残高 */
int withdraw = 1500; /* 引き出し額 */
if (balance >= withdraw) {
    balance -= withdraw;
    printf("引き出し成功\n");
    printf("残高: %d円\n", balance);
} else {
    printf("残高不足です\n");
    printf("現在の残高: %d円\n", balance);
}
```
### if-else if文（複数の選択肢）
3つ以上の選択肢から選ぶ場面では、if-else if文を使います。上から順番に条件をチェックし、最初に真になった処理を実行します。
#### 基本構文
```c
if (条件1) {
    /* 条件1が真の場合 */
} else if (条件2) {
    /* 条件1は偽で、条件2が真の場合 */
} else if (条件3) {
    /* 条件1,2は偽で、条件3が真の場合 */
} else {
    /* すべての条件が偽の場合 */
}
```
**重要な特徴**：
- 上から順番にチェックされる
- 最初に真になった部分だけ実行される
- それ以降の条件はチェックされない
#### 成績判定システムの例
```c
int score = 85;
printf("点数: %d点\n", score);
if (score >= 90) {
    printf("成績: A（優秀）\n");
printf("素晴らしい成績です！\n");
} else if (score >= 80) {
    printf("成績: B（良好）\n");
printf("よく頑張りました！\n");
} else if (score >= 70) {
    printf("成績: C（普通）\n");
printf("合格です\n");
} else if (score >= 60) {
    printf("成績: D（可）\n");
printf("ギリギリ合格です\n");
} else {
    printf("成績: F（不可）\n");
printf("もう少し頑張りましょう\n");
}
}
```
#### 時間帯による挨拶の例
```c
int hour = 14;  /* 14時（午後2時） */
if (hour >= 5 && hour < 12) {
    printf("おはようございます\n");
} else if (hour >= 12 && hour < 17) {
    printf("こんにちは\n");
} else if (hour >= 17 && hour < 21) {
    printf("こんばんは\n");
} else {
    printf("夜遅いですね、お疲れさまです\n");
}
```
#### 順序が重要な理由
```c
/* 間違った順序 */
int age = 15;
if (age >= 0) {
    printf("生まれています\n");  /* 15歳でもここで止まる！ */
} else if (age >= 13) {
    printf("中学生以上\n");  /* 実行されない */
} else if (age >= 18) {
    printf("成人\n");  /* 実行されない */
}
/* 正しい順序（厳しい条件から） */
if (age >= 18) {
    printf("成人\n");
} else if (age >= 13) {
    printf("中学生以上\n");
} else if (age >= 0) {
    printf("生まれています\n");
}
```
### ネストしたif文（入れ子構造）
if文の中にさらにif文を書くことで、より複雑な条件判断ができます。
```c
/* 天気と気温による服装アドバイス */
int temperature = 25;
int is_raining = 0;  /* 0:晴れ、1:雨 */
if (temperature >= 25) {
    printf("暖かい日です\n");
    if (is_raining) {
        printf("半袖で傘を持っていきましょう\n");
    } else {
        printf("半袖で大丈夫です\n");
    }
} else if (temperature >= 15) {
    printf("過ごしやすい気温です\n");
    if (is_raining) {
        printf("長袖で傘を持っていきましょう\n");
    } else {
        printf("長袖がおすすめです\n");
    }
} else {
    printf("寒い日です\n");
    if (is_raining) {
        printf("コートと傘が必要です\n");
    } else {
        printf("コートを着ていきましょう\n");
    }
}
```
#### ネストを避ける工夫
ネストが深くなると読みにくくなるので、論理演算子を使って簡潔に書くこともできます：
```c
/* ネストを使った場合 */
if (age >= 18) {
    if (has_license) {
        printf("運転できます\n");
    }
}
/* 論理演算子を使った場合 */
if (age >= 18 && has_license) {
    printf("運転できます\n");
}
```
### 条件式の詳細 
#### 比較演算子
```c
int a = 5, b = 3;
if (a == b)   printf("等しい\n");
if (a != b)   printf("等しくない\n");
if (a < b)    printf("a は b より小さい\n");
if (a <= b)   printf("a は b 以下\n");
if (a > b)    printf("a は b より大きい\n");
if (a >= b)   printf("a は b 以上\n"); 
```
#### 論理演算子の組み合わせ
```c
int age = 25;
int income = 300000;
/* AND演算子 */
if (age >= 20 && income >= 200000) {
    printf("ローン審査に通りました\n");
}
/* OR演算子 */
if (age < 6 || age > 65) {
    printf("特別料金が適用されます\n");
}
/* NOT演算子 */
if (!(age >= 18)) {
    printf("18歳未満です\n");
}
```
### switch文 
複数の値に対する分岐処理を効率的に記述できます。
#### switch文って何？
プログラムを書いていると、「この変数の値が1なら処理A、2なら処理B、3なら処理C...」というように、一つの変数の値によって多くの分岐をしたい場面があります。
これをif-else ifで書くと：
```c
if (choice == 1) {
    printf("処理A\n");
} else if (choice == 2) {
    printf("処理B\n");
} else if (choice == 3) {
    printf("処理C\n");
} else if (choice == 4) {
    printf("処理D\n");
} else {
    printf("その他の処理\n");
}
```
このように長くなってしまいます。switch文を使うと、もっとスッキリ書けます！
#### 日常生活での例え
switch文は「自動販売機」のようなものです：
1. ボタンを押す（変数の値）
2. 押したボタンに応じて違う商品が出る（caseごとの処理）
3. 存在しないボタンを押したら何も出ない（default処理）
```c
int button = 2;  /* 2番のボタンを押した */
switch (button) {
    case 1:
        printf("コーラが出ました\n");
        break;
    case 2:
        printf("オレンジジュースが出ました\n");
        break;
    case 3:
        printf("お茶が出ました\n");
        break;
    default:
        printf("そのボタンには商品がありません\n");
        break;
}
```
#### 基本構文
```c
switch (変数または式) {
    case 値1:
        /* 値1の場合の処理 */
        break;
    case 値2:
        /* 値2の場合の処理 */
        break;
    case 値3:
        /* 値3の場合の処理 */
        break;
    default:
        /* どの値にも一致しない場合の処理 */
        break;
}
```
#### 曜日判定の例
```c
int day = 3;
switch (day) {
    case 1:
        printf("月曜日\n");
        break;
    case 2:
        printf("火曜日\n");
        break;
    case 3:
        printf("水曜日\n");
        break;
    case 4:
        printf("木曜日\n");
        break;
    case 5:
        printf("金曜日\n");
        break;
    case 6:
        printf("土曜日\n");
        break;
    case 7:
        printf("日曜日\n");
        break;
    default:
        printf("無効な曜日です\n");
        break;
}
```
#### break文の重要性
break文を忘れると、次のcaseも実行されます（フォールスルー）：
**初心者がよくやるミス：breakを忘れる**
switch文で最も多いミスが「break文の書き忘れ」です。これは本当によくあるミスなので、必ず確認しましょう！
```c
int grade = 'B';
switch (grade) {
    case 'A':
        printf("優秀\n");
        /* break がないので次のcaseも実行される */
    case 'B':
        printf("良好\n");
        /* break がないので次のcaseも実行される */
    case 'C':
        printf("普通\n");
        break;
    default:
        printf("要努力\n");
        break;
}
/* grade が 'B' の場合、"良好" と "普通" の両方が出力される */
```
#### 意図的なフォールスルー
時には意図的にbreakを省略することもあります：
**フォールスルーが便利な場面**
「複数の値で同じ処理をしたい」ときは、あえてbreakを書かないことで、コードを簡潔に書けます：
```c
char ch = 'a';
switch (ch) {
    case 'a':
    case 'e':
    case 'i':
    case 'o':
    case 'u':
        printf("母音です\n");
        break;
    default:
        printf("子音です\n");
        break;
}
```
### 条件演算子（三項演算子）の復習 
条件分岐の簡潔な書き方として条件演算子があります。
```c
int a = 5, b = 3;
int max;
/* if-else文での記述 */
if (a > b) {
    max = a;
 } else {
    max = b;
}
/* 条件演算子での記述 */
max = (a > b) ? a : b;
printf("最大値: %d\n", max);
```
### 条件式での注意点 
初心者が陥りやすい間違いをいくつか紹介します。これらを知っておけば、デバッグ時間を大幅に短縮できます！
#### 代入と比較の混同
```c
int x = 5;
/* NG: 代入になってしまう */
if (x = 10) {  /* ← これは間違い！ */
    printf("常に実行される\n");  /* x に 10 が代入され、常に真 */
}
/* OK: 比較演算子を使用 */
if (x == 10) {  /* ← 正しい書き方 */
    printf("x が 10 の場合のみ実行\n");
}
/* 防御的プログラミング：定数を左側に書く */
if (10 == x) {  /* もし = を1つしか書かなかったらコンパイルエラーになる */
    printf("x が 10 の場合のみ実行\n");
}
```
#### 浮動小数点数の比較
コンピュータでは小数を完全に正確に表現できないことがあります。これは初心者にとって意外な落とし穴です：
```c
double d = 0.1 + 0.2;
/* NG: 浮動小数点の誤差で期待通りにならない可能性 */
if (d == 0.3) {
    printf("等しい\n");  /* 実行されないかも！ */
}
/* OK: 誤差を考慮した比較 */
if (d >= 0.299999 && d <= 0.300001) {
    printf("ほぼ等しい\n");
}
/* より実践的な方法：許容誤差を定義 */
#define EPSILON 0.00001
if (fabs(d - 0.3) < EPSILON) {
    printf("実質的に等しい\n");
}
```
**なぜこんなことが起きるの？**
コンピュータは2進数で計算するため、10進数の0.1や0.2を正確に表現できません。人間にとっての「0.1」は、コンピュータにとっては「0.1に限りなく近い値」なのです。
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
### 1. セミコロンの位置
```c
/* NG: if文の後にセミコロン */
if (condition);
{
    printf("常に実行される\n");  /* 条件に関係なく実行 */
}
/* OK: 正しい記述 */
if (condition) {
    printf("条件が真の場合のみ実行\n");
```
### 1. switch文でのbreak忘れ
```c
/* NG: break忘れでフォールスルー */
switch (value) {
    case 1:
        printf("1です\n");
        /* break; を忘れると次のcaseも実行される */
    case 2:
        printf("2です\n");
        break;
}
/* OK: 適切なbreak文 */
switch (value) {
    case 1:
        printf("1です\n");
        break;
    case 2:
        printf("2です\n");
        break;
}
```
### 1. 複雑な条件式での括弧不足
```c
/* NG: 意図しない優先順位 */
if (a == 1 || b == 2 && c == 3) 
    /* && が || より優先される */
/* OK: 括弧で明示 */
if ((a == 1) || (b == 2 && c == 3)) 
    /* 意図が明確 */
```
##  次の章へ
条件分岐を理解したら、[制御構造（ループ）](../control-loop/README.md) に進んでください。
##  参考資料
- [if文詳細](https://ja.cppreference.com/w/c/language/if)
- [switch文詳細](https://ja.cppreference.com/w/c/language/switch)
- [条件演算子](https://ja.cppreference.com/w/c/language/operator_other)
## サンプルコード
### conditional_operator.c