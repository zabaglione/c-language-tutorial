# 第11章 演習問題: 関数

## 基礎問題

### 問題11-1: 基本的な関数作成
以下の関数を作成してください。

1. **数学関数**
   - 2つの整数の最大値を返す関数 `int max(int a, int b)`
   - 3つの整数の最小値を返す関数 `int min(int a, int b, int c)`
   - 数値が偶数かどうかを判定する関数 `int is_even(int n)`
   - 数値が素数かどうかを判定する関数 `int is_prime(int n)`

2. **文字・文字列関数**
   - 文字が英字かどうかを判定する関数 `int is_letter(char c)`
   - 文字列の長さを計算する関数 `int my_strlen(const char str[])`
   - 文字列内の特定文字を数える関数 `int count_char(const char str[], char ch)`

3. **表示関数**
   - 指定した長さの線を描く関数 `void draw_line(int length, char ch)`
   - 数値を指定した桁数で表示する関数 `void print_number_padded(int num, int width)`

**期待される出力例:**
```
=== 数学関数のテスト ===
max(10, 20) = 20
min(30, 15, 25) = 15
is_even(24) = 1 (偶数)
is_even(17) = 0 (奇数)
is_prime(17) = 1 (素数)
is_prime(24) = 0 (素数ではない)

=== 文字・文字列関数のテスト ===
is_letter('A') = 1
is_letter('5') = 0
my_strlen("Hello") = 5
count_char("Hello World", 'l') = 3

=== 表示関数のテスト ===
draw_line(20, '-'): --------------------
print_number_padded(42, 5): 00042
print_number_padded(1234, 3): 1234
```

### 問題11-2: 配列操作関数
以下の配列操作関数を作成してください。

1. **基本操作**
   - 配列の要素の合計を計算する関数 `int array_sum(int arr[], int size)`
   - 配列の平均値を計算する関数 `double array_average(int arr[], int size)`
   - 配列内の最大値のインデックスを返す関数 `int find_max_index(int arr[], int size)`

2. **検索・ソート**
   - 線形検索関数 `int linear_search(int arr[], int size, int target)`
   - 配列を昇順にソートする関数 `void sort_array(int arr[], int size)`
   - 配列の要素を逆順にする関数 `void reverse_array(int arr[], int size)`

3. **配列統計**
   - 配列の最大値と最小値を同時に求める関数 `void find_min_max(int arr[], int size, int *min, int *max)`
   - 配列内の重複する要素の数を数える関数 `int count_duplicates(int arr[], int size)`

**期待される出力例:**
```
=== 配列操作関数のテスト ===
配列: [34, 12, 67, 89, 23, 45, 78, 56, 90, 11]

基本操作:
array_sum() = 495
array_average() = 49.50
find_max_index() = 8 (値: 90)

検索・ソート:
linear_search(45) = 5
ソート前: [34, 12, 67, 89, 23, 45, 78, 56, 90, 11]
ソート後: [11, 12, 23, 34, 45, 56, 67, 78, 89, 90]
逆順: [90, 89, 78, 67, 56, 45, 34, 23, 12, 11]

配列統計:
最小値: 11, 最大値: 90
重複要素数: 0

配列: [1, 2, 3, 2, 4, 3, 5]
重複要素数: 2 (2と3が重複)
```

### 問題11-3: 文字列処理関数
以下の文字列処理関数を作成してください。

1. **基本処理**
   - 文字列をコピーする関数 `void my_strcpy(char dest[], const char src[])`
   - 文字列を連結する関数 `void my_strcat(char dest[], const char src[])`
   - 文字列を比較する関数 `int my_strcmp(const char str1[], const char str2[])`

2. **変換処理**
   - 文字列を大文字に変換する関数 `void to_uppercase(char str[])`
   - 文字列を小文字に変換する関数 `void to_lowercase(char str[])`
   - 文字列を逆順にする関数 `void reverse_string(char str[])`

3. **解析処理**
   - 文字列内の単語数を数える関数 `int count_words(const char str[])`
   - 文字列が回文かどうかを判定する関数 `int is_palindrome(const char str[])`
   - 文字列内の母音の数を数える関数 `int count_vowels(const char str[])`

**期待される出力例:**
```
=== 文字列処理関数のテスト ===

基本処理:
元の文字列: "Hello"
my_strcpy後: "Hello"
my_strcat後: "HelloWorld"
my_strcmp("Hello", "World") = -15

変換処理:
元: "Hello World"
大文字: "HELLO WORLD"
小文字: "hello world"
逆順: "dlroW olleH"

解析処理:
"Hello World Programming" の単語数: 3
"racecar" は回文: Yes
"hello" は回文: No
"Hello World" の母音数: 3 (e, o, o)
```

## 応用問題

### 問題11-4: 複数戻り値を持つ関数
以下の関数を作成してください。

1. **時間計算**
   - 秒数を時分秒に変換する関数 `void seconds_to_hms(int total_seconds, int *hours, int *minutes, int *seconds)`
   - 日数から年月日に変換する関数（365日/年として） `void days_to_ymd(int total_days, int *years, int *months, int *days)`

2. **座標計算**
   - 2点間の距離と中点を計算する関数 `void calculate_line_info(double x1, double y1, double x2, double y2, double *distance, double *mid_x, double *mid_y)`
   - 円の面積と周囲の長さを計算する関数 `void calculate_circle_info(double radius, double *area, double *circumference)`

3. **統計計算**
   - 配列の統計情報を計算する関数 `void calculate_statistics(int arr[], int size, int *min, int *max, double *mean, double *median)`
   - 成績から評価を計算する関数 `void calculate_grade_info(int scores[], int count, double *average, char *grade, int *pass_count)`

**期待される出力例:**
```
=== 複数戻り値関数のテスト ===

時間計算:
3661秒 = 1時間 1分 1秒
400日 = 1年 1月 5日

座標計算:
点(0, 0)と点(3, 4)の間:
距離: 5.00, 中点: (1.50, 2.00)

半径5の円:
面積: 78.54, 周囲: 31.42

統計計算:
配列: [34, 12, 67, 89, 23, 45, 78, 56, 90, 11]
最小: 11, 最大: 90, 平均: 50.50, 中央値: 50.50

成績情報:
点数: [85, 92, 78, 65, 98, 55, 73, 88]
平均: 79.25, 評価: B, 合格者数: 6
```

### 問題11-5: エラーハンドリング付き関数
安全性を考慮した以下の関数を作成してください。

1. **安全な基本操作**
   - 安全な除算関数 `int safe_divide(double a, double b, double *result)`
   - 安全な配列アクセス関数 `int safe_array_get(int arr[], int size, int index, int *value)`
   - 安全な文字列コピー関数 `int safe_strcpy(char dest[], int dest_size, const char src[])`

2. **範囲チェック付き関数**
   - 範囲指定付きランダム数生成関数 `int random_range(int min, int max, int *result)`
   - 配列の範囲チェック付き設定関数 `int safe_array_set(int arr[], int size, int index, int value)`

3. **バリデーション関数**
   - 文字列が数値として有効かチェックする関数 `int is_valid_number(const char str[])`
   - メールアドレスの基本形式をチェックする関数 `int is_valid_email(const char email[])`

**期待される出力例:**
```
=== エラーハンドリング関数のテスト ===

安全な除算:
safe_divide(10, 3) = 3.33 (成功)
safe_divide(10, 0) = エラー (ゼロ除算)

安全な配列アクセス:
safe_array_get(index=2) = 67 (成功)
safe_array_get(index=15) = エラー (範囲外)

安全な文字列コピー:
safe_strcpy("Hello") = 成功
safe_strcpy("VeryLongStringThatExceedsBufferSize") = エラー (バッファ不足)

バリデーション:
is_valid_number("123.45") = 1 (有効)
is_valid_number("12.3.4") = 0 (無効)
is_valid_email("user@example.com") = 1 (有効)
is_valid_email("invalid.email") = 0 (無効)
```

### 問題11-6: 構造体を使った関数
以下の構造体を使った関数を作成してください。

```c
typedef struct {
    double x;
    double y;
} Point;

typedef struct {
    int id;
    char name[50];
    int age;
    double score;
} Student;

typedef struct {
    int year;
    int month;
    int day;
} Date;
```

1. **座標操作**
   - 2点間の距離を計算する関数 `double point_distance(Point p1, Point p2)`
   - 点を移動する関数 `Point move_point(Point p, double dx, double dy)`
   - 複数の点の重心を計算する関数 `Point calculate_centroid(Point points[], int count)`

2. **学生情報処理**
   - 学生情報を表示する関数 `void print_student(Student s)`
   - 学生の成績を更新する関数 `void update_score(Student *s, double new_score)`
   - 学生配列から最高得点者を見つける関数 `Student find_best_student(Student students[], int count)`

3. **日付操作**
   - 日付を表示する関数 `void print_date(Date d)`
   - 日付の妥当性をチェックする関数 `int is_valid_date(Date d)`
   - 2つの日付の差を計算する関数 `int date_difference(Date d1, Date d2)`

**期待される出力例:**
```
=== 構造体関数のテスト ===

座標操作:
点A(0, 0)と点B(3, 4)の距離: 5.00
点(2, 3)を(1, -1)移動: (3, 2)
3点の重心: (2.00, 3.00)

学生情報処理:
学生: ID=1001, 名前=田中太郎, 年齢=20, 成績=85.5
成績更新後: 92.0
最高得点者: 山田花子 (成績: 95.0)

日付操作:
日付: 2024/3/15
is_valid_date(2024/2/30) = 0 (無効)
is_valid_date(2024/3/15) = 1 (有効)
2024/1/1 から 2024/3/15 までの日数: 74日
```

## チャレンジ問題

### 問題11-7: 再帰関数
以下の再帰関数を作成してください。

1. **数学的再帰**
   - 階乗を計算する再帰関数 `long factorial_recursive(int n)`
   - フィボナッチ数列を計算する再帰関数 `int fibonacci_recursive(int n)`
   - ユークリッドの互除法による最大公約数を求める再帰関数 `int gcd_recursive(int a, int b)`

2. **文字列再帰**
   - 文字列が回文かどうか再帰的に判定する関数 `int is_palindrome_recursive(const char str[], int start, int end)`
   - 文字列を再帰的に逆順にする関数 `void reverse_string_recursive(char str[], int start, int end)`

3. **配列再帰**
   - 配列の合計を再帰的に計算する関数 `int array_sum_recursive(int arr[], int size)`
   - 配列の最大値を再帰的に見つける関数 `int find_max_recursive(int arr[], int size)`

**期待される出力例:**
```
=== 再帰関数のテスト ===

数学的再帰:
5! = 120
fibonacci(10) = 55
gcd(48, 18) = 6

文字列再帰:
"racecar" は回文: Yes
"hello" は回文: No
"Hello" の逆順: "olleH"

配列再帰:
配列 [1, 2, 3, 4, 5] の合計: 15
配列 [34, 67, 12, 89, 23] の最大値: 89
```

### 問題11-8: 高度な文字列処理
以下の高度な文字列処理関数を作成してください。

1. **文字列解析**
   - 文字列をトークンに分割する関数 `int tokenize(char str[], char tokens[][50], char delimiter)`
   - 文字列内の括弧の対応をチェックする関数 `int check_brackets(const char str[])`
   - 文字列から数値を抽出する関数 `int extract_numbers(const char str[], int numbers[], int max_count)`

2. **パターンマッチング**
   - 簡単なワイルドカード（*、?）パターンマッチング関数 `int wildcard_match(const char str[], const char pattern[])`
   - 文字列の置換関数 `int string_replace(char str[], const char old_substr[], const char new_substr[])`

3. **文字列フォーマット**
   - 文字列を指定幅で中央揃えする関数 `void center_string(char result[], const char str[], int width)`
   - CSV形式の文字列を解析する関数 `int parse_csv_line(const char line[], char fields[][100], int max_fields)`

### 問題11-9: ソートアルゴリズム関数
以下のソートアルゴリズムを関数として実装してください。

1. **基本ソート**
   - バブルソート `void bubble_sort(int arr[], int size)`
   - 選択ソート `void selection_sort(int arr[], int size)`
   - 挿入ソート `void insertion_sort(int arr[], int size)`

2. **高速ソート**
   - マージソート `void merge_sort(int arr[], int left, int right)`
   - クイックソート `void quick_sort(int arr[], int left, int right)`

3. **特殊ソート**
   - 文字列配列のソート `void sort_strings(char strings[][100], int count)`
   - 構造体配列のソート（複数キー対応）`void sort_students(Student students[], int count, int sort_by)`

## 挑戦課題

### 課題9-10: 関数ポインター
以下の関数ポインターを使った課題に取り組んでください。

1. **計算機関数**
   - 四則演算を関数ポインターで切り替える計算機 `double calculator(double a, double b, double (*operation)(double, double))`
   - 配列に対する処理を関数ポインターで指定する関数 `void process_array(int arr[], int size, void (*processor)(int*))`

2. **ソート関数の汎用化**
   - 比較関数を引数に取る汎用ソート関数 `void generic_sort(void *arr, int size, int elem_size, int (*compare)(const void*, const void*))`

3. **コールバック関数**
   - イベント処理システム `void register_callback(int event_type, void (*callback)(int))`

### 課題9-11: メモリ効率を考慮した関数
メモリ使用量を最適化した関数を作成してください。

1. **動的メモリ管理**
   - 動的配列を管理する関数群
   - 文字列プールを管理する関数群
   - メモリリークを検出する関数

2. **効率的なアルゴリズム**
   - インプレース（元の配列内で処理）ソート関数
   - メモリ使用量を抑えた文字列処理関数
   - キャッシュ効率を考慮した配列処理関数

### 課題9-12: 総合プロジェクト
複数の関数を組み合わせた総合的なプロジェクトを作成してください。

1. **学生管理システム**
   - 学生情報の登録、検索、更新、削除機能
   - 成績統計の計算機能
   - データのファイル保存・読み込み機能

2. **テキスト解析ツール**
   - ファイルの読み込みと解析
   - 単語頻度の統計
   - 文字列パターンの検索

3. **数値計算ライブラリ**
   - 行列演算機能
   - 統計計算機能
   - 数値積分・微分機能

## 提出要件

各課題について、以下を提出してください。

1. **ソースコード**
   - 関数の実装（.cファイル）
   - ヘッダファイル（.hファイル）
   - テスト用のmain関数

2. **ドキュメント**
   - 各関数の仕様説明
   - 使用例とサンプル出力
   - エラーケースの説明

3. **テストケース**
   - 正常ケースのテスト
   - 境界値のテスト
   - エラーケースのテスト

## 評価ポイント

- **正確性**: 仕様通りに動作するか
- **安全性**: エラーハンドリングが適切か
- **効率性**: アルゴリズムの計算量は適切か
- **可読性**: コードが理解しやすいか
- **再利用性**: 他のプログラムでも使えるか

## 難易度別の推奨学習順序

### 初学者向け（基本課題から開始）
1. 課題9-1: 基本的な関数作成
2. 課題9-2: 配列操作関数
3. 課題9-3: 文字列処理関数

### 中級者向け（中級課題に挑戦）
4. 課題9-4: 複数戻り値を持つ関数
5. 課題9-5: エラーハンドリング付き関数
6. 課題9-6: 構造体を使った関数

### 上級者向け（上級・挑戦課題）
7. 課題9-7: 再帰関数
8. 課題9-8: 高度な文字列処理
9. 課題9-9: ソートアルゴリズム関数
10. 課題9-10: 関数ポインター
11. 課題9-11: メモリ効率を考慮した関数
12. 課題9-12: 総合プロジェクト

## 学習のヒント

1. **段階的実装**
   - 最初は基本機能のみ実装
   - 動作確認後に機能を追加
   - テストを頻繁に実行

2. **エラーハンドリング**
   - NULLポインターのチェック
   - 配列の境界チェック
   - 無効な引数の処理

3. **関数設計の原則**
   - 単一責任の原則
   - 適切な関数名と引数名
   - const修飾子の活用

4. **テスト駆動開発**
   - 関数作成前にテストケースを考える
   - 境界値のテスト
   - エラーケースのテスト

5. **コードレビュー**
   - 他の人に読んでもらう
   - 改善点を見つける
   - ベストプラクティスを学ぶ

## 参考資料

- C言語関数リファレンス
- アルゴリズムとデータ構造の教科書
- セキュアプログラミングガイド
- 関数型プログラミングの考え方

## 実装例の構成

各課題の実装では以下の構成を推奨します。

```c
// ヘッダーファイル（functions.h）
// - 関数プロトタイプ
// - 定数定義
// - 構造体定義

// 実装ファイル（functions.c）
// - 関数の実装
// - 静的関数（内部使用）
// - エラーハンドリング

// テストファイル（test.c）
// - main関数
// - 各関数のテスト
// - 結果の検証
```

## 発展的な学習内容

1. **可変長引数**
   - va_list、va_start、va_endの使用
   - printfライクな関数の作成

2. **関数ポインター**
   - コールバック関数の実装
   - 関数テーブルの作成

3. **マクロ関数**
   - 関数ライクマクロの作成
   - 条件付きコンパイル

4. **インライン関数**
   - パフォーマンスの最適化
   - 適切な使用場面

このチュートリアルを通じて、C言語の関数について体系的に学習し、実践的なプログラミングスキルを身に付けてください。
