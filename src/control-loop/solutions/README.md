# 第5章 解答例: 制御構造（ループ）

## 解答例一覧

### 演習5-1: フィボナッチ数列
- **ファイル**: `ex6_1_fibonacci.c`, `ex6_1_fibonacci_c99.c`
- **学習内容**: for文による繰り返し処理、フィボナッチ数列のアルゴリズム
- **ポイント**: 変数の値の更新と循環、初期値の特別処理

### 演習5-2: 数当てゲーム（改良版）
- **ファイル**: `ex6_2_number_guess.c`, `ex6_2_number_guess_c99.c`
- **学習内容**: do-while文による繰り返し、ランダム数生成
- **ポイント**: 複数の終了条件、デモ版として自動実行

### 演習5-3: 素数リスト
- **ファイル**: `ex6_3_prime_list.c`, `ex6_3_prime_list_c99.c`
- **学習内容**: ネストしたループ、break文、効率的な素数判定
- **ポイント**: 数学的最適化、統計情報の計算

### 演習5-4: 図形の描画
- **ファイル**: `ex6_4_draw_shapes.c`, `ex6_4_draw_shapes_c99.c`
- **学習内容**: ネストしたループによる2次元パターン生成
- **ポイント**: 空白とアスタリスクの配置制御、複雑な図形の分解

### 演習5-5: 掛け算表
- **ファイル**: `ex6_5_multiplication_table.c`, `ex6_5_multiplication_table_c99.c`
- **学習内容**: ネストしたfor文、表形式データの生成
- **ポイント**: 書式指定子による桁揃え、ヘッダーと区切り線

### 演習5-6: 階乗計算
- **ファイル**: `ex6_6_factorial.c`, `ex6_6_factorial_c99.c`
- **学習内容**: while文による繰り返し、オーバーフロー対策
- **ポイント**: long long型の使用、計算過程の表示

## C90版とC99版の違い

### C90版（基本ファイル）
- すべての変数を関数の先頭で宣言
- `/* */` 形式のコメントを使用
- 従来のCの制御構造に準拠

### C99版（_c99.cファイル）
- 変数を使用する箇所の近くで宣言可能
- for文内でのループ変数宣言
- `//` 形式のコメントに対応
- より現代的な制御構造の書き方

## コンパイルと実行

### 基本的なコンパイル
```bash
gcc -Wall -Wextra -pedantic -std=c90 ex6_1_fibonacci.c -o ex6_1_fibonacci
./ex6_1_fibonacci
```

### C99版のコンパイル
```bash
gcc -Wall -Wextra -pedantic -std=c99 ex6_1_fibonacci_c99.c -o ex6_1_fibonacci_c99
./ex6_1_fibonacci_c99
```

### 数学関数を使用する場合（素数判定）
```bash
gcc -Wall -Wextra -pedantic -std=c90 ex6_3_prime_list.c -o ex6_3_prime_list -lm
./ex6_3_prime_list
```

## 学習のポイント

### ループの基本
1. **for文**: 回数が決まった繰り返し処理
2. **while文**: 条件が真の間の繰り返し処理
3. **do-while文**: 最低1回は実行される繰り返し処理
4. **ネストしたループ**: 2次元的な処理パターン

### 制御文の活用
1. **break文**: ループの早期終了
2. **continue文**: 次の繰り返しへのスキップ
3. **条件分岐との組み合わせ**: 複雑な制御フロー

### 実用的なテクニック
1. **計算アルゴリズム**: フィボナッチ、階乗、素数判定
2. **パターン生成**: 図形描画、表形式データ
3. **入力検証**: エラーハンドリングとユーザビリティ
4. **最適化**: 効率的なアルゴリズムの実装

### プログラム設計
1. **段階的な実装**: 簡単な処理から複雑な処理へ
2. **モジュール化**: 機能ごとの分割と整理
3. **デバッグ**: ループの動作確認と修正
4. **可読性**: 理解しやすいコードの書き方

## 注意事項

- ループの無限ループに注意
- 配列の境界を超えないよう注意
- オーバーフローの可能性を考慮
- 効率的なアルゴリズムの選択

## 対話型プログラムについて

このサンプルコードでは、学習効果を高めるため、一部のプログラムは非対話的なデモ版として実装されています。実際の開発では、ユーザー入力を適切に処理する対話型プログラムとして実装してください。

## 実用的な応用

これらの制御構造は以下のような実用的なプログラムで使用されます。

- **データ処理**: 大量データの反復処理
- **ゲーム**: ゲームループと状態管理
- **シミュレーション**: 反復計算による数値解析
- **グラフィックス**: パターン生成と描画処理

## 次のステップ

この章をマスターしたら、次の章に進みましょう。
- [第6章: 配列](../arrays/)
- [第7章: 文字列](../strings/)
- [第8章: 関数](../functions/)