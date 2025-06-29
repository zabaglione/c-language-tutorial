# C言語基礎 - 演習解答例

## 概要

この解答例集は、[exercises/exercises.md](../exercises/exercises.md)で出題された演習課題の解答例を提供しています。各課題について、**C90版**と**C99版**の両方を作成しています。

## 解答例一覧

### 基本課題

#### 課題1: Hello Worldの応用

| 課題 | 内容 | C90版 | C99版 |
|------|------|-------|-------|
| 1-1 | 自己紹介プログラム | [`ex1_1_self_introduction.c`](ex1_1_self_introduction.c) | [`ex1_1_self_introduction_c99.c`](ex1_1_self_introduction_c99.c) |
| 1-2 | メッセージボックス | [`ex1_2_message_box.c`](ex1_2_message_box.c) | [`ex1_2_message_box_c99.c`](ex1_2_message_box_c99.c) |
| 1-3 | 曜日表示 | [`ex1_3_weekday_display.c`](ex1_3_weekday_display.c) | [`ex1_3_weekday_display_c99.c`](ex1_3_weekday_display_c99.c) |

#### 課題2: 変数と型の基本操作

| 課題 | 内容 | C90版 | C99版 |
|------|------|-------|-------|
| 2-1 | 個人情報管理 | [`ex2_1_personal_info.c`](ex2_1_personal_info.c) | [`ex2_1_personal_info_c99.c`](ex2_1_personal_info_c99.c) |
| 2-2 | データ型サイズ確認 | [`ex2_2_data_type_sizes.c`](ex2_2_data_type_sizes.c) | [`ex2_2_data_type_sizes_c99.c`](ex2_2_data_type_sizes_c99.c) |
| 2-3 | 型変換実験 | [`ex2_3_type_conversion.c`](ex2_3_type_conversion.c) | [`ex2_3_type_conversion_c99.c`](ex2_3_type_conversion_c99.c) |

#### 課題3: 計算プログラム

| 課題 | 内容 | C90版 | C99版 |
|------|------|-------|-------|
| 3-1 | 基本計算機 | [`ex3_1_calculator.c`](ex3_1_calculator.c) | [`ex3_1_calculator_c99.c`](ex3_1_calculator_c99.c) |
| 3-2 | 温度変換プログラム | [`ex3_2_temperature_converter.c`](ex3_2_temperature_converter.c) | [`ex3_2_temperature_converter_c99.c`](ex3_2_temperature_converter_c99.c) |
| 3-3 | 図形計算プログラム | [`ex3_3_geometry_calculator.c`](ex3_3_geometry_calculator.c) | [`ex3_3_geometry_calculator_c99.c`](ex3_3_geometry_calculator_c99.c) |

#### 課題4: 演算子の活用

| 課題 | 内容 | C90版 | C99版 |
|------|------|-------|-------|
| 4-1 | 複合代入演算子の練習 | [`ex4_1_compound_assignment.c`](ex4_1_compound_assignment.c) | [`ex4_1_compound_assignment_c99.c`](ex4_1_compound_assignment_c99.c) |
| 4-2 | インクリメント・デクリメント実験 | [`ex4_2_increment_decrement.c`](ex4_2_increment_decrement.c) | [`ex4_2_increment_decrement_c99.c`](ex4_2_increment_decrement_c99.c) |
| 4-3 | 三項演算子の練習 | [`ex4_3_ternary_operator.c`](ex4_3_ternary_operator.c) | [`ex4_3_ternary_operator_c99.c`](ex4_3_ternary_operator_c99.c) |

### 中級課題

#### 課題5: 実用的なプログラム

| 課題 | 内容 | C90版 | C99版 |
|------|------|-------|-------|
| 5-1 | 家計簿計算機 | [`ex5_1_household_budget.c`](ex5_1_household_budget.c) | [`ex5_1_household_budget_c99.c`](ex5_1_household_budget_c99.c) |
| 5-2 | ローン計算機 | [`ex5_2_loan_calculator.c`](ex5_2_loan_calculator.c) | [`ex5_2_loan_calculator_c99.c`](ex5_2_loan_calculator_c99.c) |

## C90版とC99版の違い

### C90版の特徴
- **互換性重視**: 古いコンパイラでも動作
- **変数宣言**: 関数の先頭で一括宣言
- **コメント**: `/* */` 形式のみ
- **厳密な構文**: より制限された文法

### C99版の特徴
- **現代的**: より読みやすく自然な書き方
- **変数宣言**: 必要な箇所で宣言可能
- **コメント**: `//` 形式も使用可能
- **柔軟な構文**: より直感的な記述

## コンパイル方法

### C90版のコンパイル
```bash
gcc -std=c90 -Wall -Wextra -pedantic ex1_1_self_introduction.c -o ex1_1_self_introduction
```

### C99版のコンパイル
```bash
gcc -std=c99 -Wall -Wextra -pedantic ex1_1_self_introduction_c99.c -o ex1_1_self_introduction_c99
```

### Makefileを使用する場合
```bash
# 全ての解答例をコンパイル
make all

# 特定の課題をコンパイル
make ex1_1_self_introduction
make ex1_1_self_introduction_c99

# クリーンアップ
make clean
```

## 学習のポイント

### 1. 段階的な理解
各解答例は、以下の順序で学習することを推奨します：
1. **要件の確認**: 課題で求められていることを理解
2. **C90版の確認**: 基本的な実装方法を学習
3. **C99版との比較**: 現代的な書き方との違いを理解
4. **自分で実装**: 解答例を参考に自分でコードを作成

### 2. 重要な概念

#### 変数とデータ型
- `int`, `double`, `char`, `char[]` の使い分け
- `const` による定数定義
- 型変換とキャスト

#### 入出力
- `printf` による書式指定出力
- `scanf` による入力受付
- エスケープシーケンスの使用

#### 演算子
- 算術演算子 (`+`, `-`, `*`, `/`, `%`)
- 複合代入演算子 (`+=`, `-=`, `*=`, `/=`, `%=`)
- インクリメント/デクリメント (`++`, `--`)

### 3. コーディングスタイル

#### 良いプログラムの特徴
- **可読性**: 他人が読んでも理解できる
- **適切なコメント**: 処理の意図を説明
- **統一されたインデント**: 見やすい構造
- **意味のある変数名**: 用途が分かる名前

#### デバッグのコツ
- **小さな単位でテスト**: 機能ごとに動作確認
- **printf文による確認**: 変数の値を途中で表示
- **エラーメッセージの解読**: コンパイラの指示に従う

## 次のステップ

基礎課題を完了したら、以下の章に進んでください：

1. **制御構造**: [control-if章](../../control-if/README.md)、[control-loop章](../../control-loop/README.md)
2. **配列**: [arrays章](../../arrays/README.md)
3. **関数**: [functions章](../../functions/README.md)
4. **ポインタ**: [pointers章](../../pointers/README.md)

## 参考資料

- [C言語の概要](../lessons/introduction.md)
- [初めてのプログラム](../lessons/hello-world.md)
- [変数と型](../lessons/variables.md)
- [演算子](../lessons/operators.md)

---

**重要**: これらの解答例は参考用です。まずは自分で考えて実装し、困った時に参照してください。プログラミングスキルは実践を通じて身に付きます。