# 第7章 演習問題: 配列（基本編）

## 演習の目的
- 1次元配列と多次元配列の理解を深める
- 配列を使った実践的な問題解決能力を養う
- 基本的な配列操作をマスターする

## 基礎問題

### 問題7-1: 配列の基本操作 
整数配列に対する各種操作を実行するプログラムを作成してください。

**要件**

- 5個の整数を入力して配列に格納
- 以下の操作を実装:
  - 配列の全要素を表示
  - 最大値と最小値を見つける
  - 平均値を計算
  - 配列を逆順に並べ替える
  - 指定した値が配列内に存在するか検索

**実装のヒント**

- 配列のサイズは#defineで定義
- 逆順は別の配列にコピーまたはその場で交換

**期待される出力例:**
```
配列操作プログラム
5個の整数を入力してください: 34 12 67 89 23

配列の内容: 34 12 67 89 23
最大値: 89
最小値: 12
平均値: 45.00

逆順配列: 23 89 67 12 34

検索する値を入力: 67
値 67 は位置 2 に存在します（0から数えて）

検索する値を入力: 50
値 50 は配列内に存在しません
```

**ファイル名:** `ex7_1_array_operations.c`

### 問題7-2: 配列の要素シフト 
配列の要素を左右にシフトするプログラムを作成してください。

**要件**

- 10個の整数を配列に格納
- 以下の操作を実装:
  - 全要素を右に1つシフト（最後の要素は先頭へ）
  - 全要素を左に1つシフト（最初の要素は最後へ）
  - 指定した数だけシフト
  - シフト前後の配列を表示

**実装のヒント**

- 一時変数を使って端の要素を保存
- ループの方向に注意

**期待される出力例:**
```
配列シフトプログラム
初期配列: 1 2 3 4 5 6 7 8 9 10

右に1シフト: 10 1 2 3 4 5 6 7 8 9
左に1シフト: 2 3 4 5 6 7 8 9 10 1

シフト数を入力してください: 3
右に3シフト: 8 9 10 1 2 3 4 5 6 7

シフト数を入力してください: -2
左に2シフト: 3 4 5 6 7 8 9 10 1 2
```

**ファイル名:** `ex7_2_array_shift.c`

### 問題7-3: 配列の統計処理 
整数配列に対する基本的な統計処理を行うプログラムを作成してください。

**要件**

- 10個の整数データを配列に格納
- 以下の統計値を計算:
  - 合計値と平均値
  - 最大値と最小値およびその位置
  - 標準偏差（簡易計算でよい）

**実装のヒント**

- 標準偏差は各要素と平均の差の二乗の平均の平方根

**期待される出力例:**
```
配列統計処理プログラム
10個の整数を入力してください: 78 65 92 83 71 96 54 88 67 79

=== 統計情報 ===
データ: 78 65 92 83 71 96 54 88 67 79
合計値: 773
平均値: 77.30
最大値: 96 (位置: 5)
最小値: 54 (位置: 6)
標準偏差: 12.85
```

**ファイル名:** `ex7_3_array_statistics.c`

## 応用問題

### 問題7-4: 成績管理システム 
複数の学生の複数科目の成績を管理するプログラムを作成してください。

**要件**

- 5人の学生、4科目（国語、数学、英語、理科）の成績を2次元配列で管理
- 各学生の合計点と平均点を計算
- 各科目の平均点を計算
- 最高得点の学生と科目を表示
- 成績表を見やすく表示

**実装のヒント**

- 2次元配列 grades[][] を使用
- 行が学生、列が科目

**期待される出力例:**
```
成績管理システム

成績表:
学生  国語  数学  英語  理科  合計  平均
-------------------------------------------
学生1   85    92    78    88   343  85.8
学生2   76    88    91    83   338  84.5
学生3   92    76    85    90   343  85.8
学生4   68    95    73    79   315  78.8
学生5   89    84    88    86   347  86.8
-------------------------------------------
科目平均 82.0  87.0  83.0  85.2

最高得点: 学生4の数学 95点
クラス全体の平均点: 84.3
```

**ファイル名:** `ex7_4_grade_management.c`

### 問題7-5: 行列演算
2次元配列を使って行列演算を実行するプログラムを作成してください。

**要件**

- 3x3の行列を2つ入力
- 以下の演算を実装:
  - 行列の加算
  - 行列の減算
  - 行列の乗算
  - 転置行列の計算

**実装のヒント**

- 行列の乗算: result[i][j] = Σ(a[i][k] * b[k][j])
- 各演算結果を見やすく表示

**期待される出力例:**
```
行列演算プログラム

行列A:
1  2  3
4  5  6
7  8  9

行列B:
9  8  7
6  5  4
3  2  1

加算結果 (A + B):
10  10  10
10  10  10
10  10  10

減算結果 (A - B):
-8  -6  -4
-2   0   2
 4   6   8

乗算結果 (A × B):
30  24  18
84  69  54
138 114  90

転置行列 (A^T):
1  4  7
2  5  8
3  6  9
```

**ファイル名:** `ex7_5_matrix_operations.c`

### 問題7-6: 頻度分布表
テストの点数分布を分析するプログラムを作成してください。

**要件**

- 30人分のテスト点数（0-100点）を配列に格納
- 10点刻みで頻度分布表を作成
- ヒストグラムを*を使って表示
- 最頻値の範囲を表示

**出力例:**
```
0- 9: ** (2人)
10-19: *** (3人)
20-29: * (1人)
...
90-99: ******** (8人)
```

**ファイル名:** `ex7_6_frequency_distribution.c`

## チャレンジ問題

### 問題7-7: ソートアルゴリズムの実装
配列のソートアルゴリズムを複数実装して比較してください。

**要件**

- 以下のソートアルゴリズムを実装:
  - バブルソート
  - 選択ソート
  - 挿入ソート
- 各アルゴリズムの実行時間を測定
- ランダムな配列、ソート済み配列、逆順配列で性能比較

**追加要件**

- 比較回数と交換回数をカウント
- 結果をグラフィカルに表示（*を使った簡易グラフ）

**期待される出力例:**
```
ソートアルゴリズムの比較

配列サイズ: 20
元の配列: 34 7 23 32 5 62 78 4 87 12 45 28 91 15 53 67 39 22 84 10

=== バブルソート ===
ソート後: 4 5 7 10 12 15 22 23 28 32 34 39 45 53 62 67 78 84 87 91
比較回数: 190
交換回数: 92
実行時間: 0.002ms

=== 選択ソート ===
ソート後: 4 5 7 10 12 15 22 23 28 32 34 39 45 53 62 67 78 84 87 91
比較回数: 190
交換回数: 19
実行時間: 0.001ms

=== 挿入ソート ===
ソート後: 4 5 7 10 12 15 22 23 28 32 34 39 45 53 62 67 78 84 87 91
比較回数: 92
交換回数: 92
実行時間: 0.001ms

効率性比較グラフ（比較回数）:
バブル: ******************** (190)
選択 : ******************** (190)
挿入 : ********** (92)
```

**ファイル名:** `ex7_7_sort_algorithms.c`

### 問題7-8: ライフゲーム
コンウェイのライフゲームの簡易版を実装してください。

**要件**

- 20x20の2次元配列でセルの状態を管理
- セルは生（1）または死（0）の状態
- 各世代で以下のルールを適用:
  - 生きているセルの周囲に2-3個の生きたセルがある→生存
  - 死んでいるセルの周囲にちょうど3個の生きたセルがある→誕生
  - それ以外→死亡
- 初期状態をランダムまたはパターンで設定
- 各世代の状態を表示

**期待される出力例:**
```
コンウェイのライフゲーム（20x20）

世代 0:
....................
......***.........
......*..*........
.......*..........
....................
（以下省略）

世代 1:
....................
.......*..........
......*..*........
......*...........
....................
（以下省略）

世代 2:
....................
......***.........
......*..*........
.......*..........
....................
（パターンが繰り返される）

10世代後の生存セル数: 8
```

**ファイル名:** `ex7_8_life_game.c`

### 問題7-9: 魔方陣の生成と検証
魔方陣を生成・検証するプログラムを作成してください。

**要件**

- 3x3の魔方陣を生成（1-9の数字を使用）
- 既存の配列が魔方陣かどうかを検証
- 検証条件:
  - 各行の合計が等しい
  - 各列の合計が等しい
  - 対角線の合計が等しい
  - 1-9の数字が重複なく使用されている
- 複数の魔方陣パターンを生成可能

**期待される出力例:**
```
魔方陣生成・検証プログラム

生成された魔方陣:
2  7  6
9  5  1
4  3  8

検証結果:
行の合計: 15, 15, 15 ✓
列の合計: 15, 15, 15 ✓
対角線の合計: 15, 15 ✓
すべての数字が1-9で重複なし ✓

これは正しい魔方陣です！

別の魔方陣パターン:
8  1  6
3  5  7
4  9  2

検証結果: 正しい魔方陣です！
```

**ファイル名:** `ex7_9_magic_square.c`

## 提出方法
1. 各問題に対して個別のCファイルを作成
2. ファイル名は指定された名前を使用
3. コメントで問題番号と簡単な説明を記載
4. コンパイル・実行確認を必ず行う

## 評価基準
- **正確性**: 要求仕様を満たしているか
- **効率性**: 配列操作の最適化
- **可読性**: 適切なインデント、変数名、コメント
- **境界処理**: 配列の境界チェック

## 学習のポイント
- 配列の初期化と要素アクセス
- 多次元配列の使い方
- 配列を使った効率的なデータ処理
- 配列の境界を超えないための注意点

## 次の章へ

演習問題お疲れさまでした！次は[第8章: ポインタ基礎](../../pointers/)に進みましょう。