# 第5章 演習問題: 制御構造（条件分岐）

## 演習の目的

- if文、switch文の理解を深める
- 条件演算子の適切な使い方を習得する
- 複雑な条件分岐の設計力を養う

## 基礎問題

### 問題5-1: 年齢による料金計算
映画館の料金システムを実装してください。

**要件**

- 3歳未満: 無料
- 3歳以上12歳以下: 子供料金（800円）
- 13歳以上18歳以下: 学生料金（1200円）
- 19歳以上65歳以下: 大人料金（1800円）
- 66歳以上: シニア料金（1200円）

**実装のヒント**

- if-else if文を使用
- 境界値に注意

**期待される出力例:**

```
映画館料金計算システム
年齢を入力してください: 25
お客様の料金は 1800円 です（大人料金）

別の例:
年齢を入力してください: 5
お客様の料金は 800円 です（子供料金）

年齢を入力してください: 70
お客様の料金は 1200円 です（シニア料金）
```

**ファイル名:** `ex5_1_movie_price.c`

### 問題5-2: 電卓プログラム

四則演算ができる簡単な電卓を作成してください。

**要件**

- ユーザーから2つの数値と演算子（+, -, *, /）を入力
- switch文を使って演算を実行
- ゼロ除算のエラー処理を含める

**実装のヒント**

- 演算子は char 型で受け取る
- 除算の場合は分母が0でないかチェック

**期待される出力例:**

```
簡単な電卓プログラム
第1の数値を入力: 15
演算子を入力 (+, -, *, /): *
第2の数値を入力: 3
計算結果: 15.00 * 3.00 = 45.00

別の例（ゼロ除算）:
第1の数値を入力: 10
演算子を入力 (+, -, *, /): /
第2の数値を入力: 0
エラー: ゼロで除算することはできません
```

**ファイル名:** `ex5_2_calculator.c`

### 問題5-3: BMI判定プログラム
身長と体重からBMIを計算し、判定するプログラムを作成してください。

**要件**

- BMI = 体重(kg) / (身長(m) × 身長(m))
- BMI判定基準:
  - 18.5未満: 低体重
  - 18.5以上25未満: 標準体重
  - 25以上30未満: 肥満度1
  - 30以上: 肥満度2

**実装のヒント**

- 身長はセンチメートルで入力してメートルに変換
- 浮動小数点数を使用

**期待される出力例:**

```
BMI判定プログラム
身長(cm)を入力してください: 170
体重(kg)を入力してください: 65

BMI値: 22.49
判定: 標準体重です

別の例:
身長(cm)を入力してください: 165
体重(kg)を入力してください: 80

BMI値: 29.38
判定: 肥満度1です
```

**ファイル名:** `ex5_3_bmi_check.c`

## 応用問題

### 問題5-4: うるう年判定

西暦年を入力してうるう年かどうか判定するプログラムを作成してください。

**うるう年の条件:**

1. 4で割り切れる年はうるう年
2. ただし、100で割り切れる年は平年
3. ただし、400で割り切れる年はうるう年

**実装のヒント**

- 複数の条件を論理演算子で組み合わせる
- 条件の順序に注意

**期待される出力例:**

```
うるう年判定プログラム
西暦年を入力してください: 2024
2024年はうるう年です

別の例:
西暦年を入力してください: 1900
1900年は平年です

西暦年を入力してください: 2000
2000年はうるう年です
```

**ファイル名:** `ex5_4_leap_year.c`

### 問題5-5: 成績評価システム

複数の科目の点数から総合評価を出すプログラムを作成してください。

**要件**

- 3科目（国語、数学、英語）の点数を入力
- 平均点を計算
- 平均点による評価（A〜F）
- 全科目60点以上の場合のみ「合格」、それ以外は「不合格」
- 条件演算子を使って簡潔に表示

**評価基準**

- 90点以上: A
- 80点以上90点未満: B
- 70点以上80点未満: C
- 60点以上70点未満: D
- 50点以上60点未満: E
- 50点未満: F

**実装のヒント**

- 平均点の計算は整数演算に注意
- 複数の条件を組み合わせる

**期待される出力例:**

```
成績評価システム
国語の点数: 85
数学の点数: 92
英語の点数: 78

平均点: 85.00
評価: B
判定: 合格

別の例（不合格）:
国語の点数: 75
数学の点数: 55
英語の点数: 80

平均点: 70.00
評価: C
判定: 不合格（数学が60点未満）
```

**ファイル名:** `ex5_5_grade_system.c`

### 問題5-6: 曜日判定プログラム

年月日を入力して、その日の曜日を判定するプログラムを作成してください。

**要件**

- ツェラーの公式を使用して曜日を計算
- 入力値の妥当性チェック（月は1-12、日は1-31など）
- 曜日を日本語で表示

**ツェラーの公式（簡易版）**

- 1月、2月は前年の13月、14月として計算

**期待される出力例:**

```
曜日判定プログラム
年を入力: 2024
月を入力: 3
日を入力: 15

2024年3月15日は金曜日です

別の例:
年を入力: 2023
月を入力: 12
日を入力: 25

2023年12月25日は月曜日です
```

**ファイル名:** `ex5_6_weekday.c`

## チャレンジ問題

### 問題5-7: じゃんけんゲーム
コンピュータとじゃんけんをするプログラムを作成してください。

**要件**

- ユーザーの手を数値で入力（1:グー、2:チョキ、3:パー）
- コンピュータの手はランダムに決定
- 勝敗を判定して表示
- 不正な入力のチェック

**追加要件**

- 3回勝負で最終的な勝者を決定
- 各回の結果を記録して最後に表示
- 連勝ボーナスポイントシステム

**期待される出力例:**

```
=== じゃんけんゲーム（3回勝負） ===

第1回戦
あなたの手を選んでください（1:グー、2:チョキ、3:パー）: 1
あなた: グー
コンピュータ: チョキ
結果: あなたの勝ち！

第2回戦
あなたの手を選んでください（1:グー、2:チョキ、3:パー）: 2
あなた: チョキ
コンピュータ: チョキ
結果: あいこ

第3回戦
あなたの手を選んでください（1:グー、2:チョキ、3:パー）: 3
あなた: パー
コンピュータ: グー
結果: あなたの勝ち！（連勝ボーナス +1）

=== 最終結果 ===
あなた: 3ポイント（2勝0敗1分）
コンピュータ: 0ポイント
優勝: あなた！
```

**ファイル名:** `ex5_7_janken_game.c`

### 問題5-8: 交通信号シミュレーター

信号機の動作をシミュレートするプログラムを作成してください。

**要件**

- 現在の信号の色と経過時間から次の動作を決定
- 歩行者用信号も含める
- 緊急車両通過モード（すべて赤信号）
- 時間帯による点滅信号への切り替え

**信号のパターン**

- 青（30秒）→ 黄（3秒）→ 赤（30秒）
- 歩行者: 青（20秒）→ 点滅（10秒）→ 赤（33秒）

**期待される出力例:**

```
交通信号シミュレーター
現在の信号状態を入力（1:青、2:黄、3:赤）: 1
経過時間（秒）: 28
現在時刻（0-23時）: 14

=== 信号状態 ===
車両用信号: 青（残り2秒）
歩行者信号: 赤
次の状態: まもなく黄信号に変わります

別の例（深夜）:
現在時刻（0-23時）: 2
深夜モード: 黄色点滅信号

別の例（緊急車両）:
緊急車両通過モード（1:有効、0:無効）: 1
すべての信号: 赤（緊急車両通過中）
```

**ファイル名:** `ex5_8_traffic_light.c`

### 問題5-9: 複雑な料金計算システム
タクシー料金計算システムを実装してください。

**要件**

- 初乗り料金: 1.052kmまで420円
- 加算料金: 以降237mごとに80円
- 時間距離併用: 時速10km以下では90秒ごとに80円
- 深夜割増（22:00-5:00）: 2割増
- 予約料金、高速料金の加算オプション

**入力項目**

- 走行距離、走行時間、時刻、オプション選択

**期待される出力例:**

```
タクシー料金計算システム
走行距離(km): 5.5
走行時間(分): 25
現在時刻(0-23): 23
予約利用(1:あり、0:なし): 0
高速道路利用(1:あり、0:なし): 0

=== 料金明細 ===
初乗り料金: 420円
加算料金: 760円（4.448km分）
深夜割増（20%）: 236円
-----------------
合計料金: 1,416円

別の例（渋滞時）:
走行距離(km): 2.0
走行時間(分): 30
現在時刻(0-23): 18

=== 料金明細 ===
初乗り料金: 420円
加算料金: 320円（距離加算）
時間加算料金: 640円（低速走行）
-----------------
合計料金: 1,380円
```

**ファイル名:** `ex5_9_taxi_fare.c`

## 提出方法

1. 各問題に対して個別のCファイルを作成
2. ファイル名は指定された名前を使用
3. コメントで問題番号と簡単な説明を記載
4. コンパイル・実行確認を必ず行う

## 評価基準

- **正確性**: 要求仕様を満たしているか
- **可読性**: 適切なインデント、変数名、コメント
- **効率性**: 不要な条件分岐がないか
- **エラー処理**: 不正な入力への対処

## 学習のポイント
- 条件の順序と網羅性
- switch文とif文の使い分け
- 条件演算子による簡潔な記述
- 複雑な条件の論理的な整理

## 次の章へ

演習問題お疲れさまでした！次は[第6章: 制御構造（ループ）](../../control-loop/)に進みましょう。