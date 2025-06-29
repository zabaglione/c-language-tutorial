# ポインタ - 解答例

この章の演習問題の解答例です。各解答にはC90版とC99版の両方を用意しています。

## 演習問題の解答

### 演習10-1: ポインタの基本操作
2つの整数変数の値をポインタを使って交換する演習です。

- [ex10_1_pointer_swap.c](ex10_1_pointer_swap.c) - C90準拠版
- [ex10_1_pointer_swap_c99.c](ex10_1_pointer_swap_c99.c) - C99準拠版（//コメント、bool型、インライン関数、restrict修飾子）

**学習ポイント:**
- ポインタによる参照渡しの仕組み
- 値渡しとの違いの理解
- アドレス演算子（&）と間接参照演算子（*）の使用
- ポインタの安全な使用方法

### 演習10-2: 配列とポインタ
ポインタ演算を使って配列の要素を逆順に表示する演習です。

- [ex10_2_array_reverse.c](ex10_2_array_reverse.c) - C90準拠版
- [ex10_2_array_reverse_c99.c](ex10_2_array_reverse_c99.c) - C99準拠版（可変長配列、複合リテラル、指定初期化子）

**学習ポイント:**
- 配列とポインタの等価性
- ポインタ演算による配列要素アクセス
- メモリレイアウトの理解
- 安全な境界チェック

### 演習10-3: 文字列操作
ポインタを使った文字列の長さ計算、複写、連結を行う演習です。

- [ex10_3_string_manipulation.c](ex10_3_string_manipulation.c) - C90準拠版
- [ex10_3_string_manipulation_c99.c](ex10_3_string_manipulation_c99.c) - C99準拠版（//コメント、restrict修飾子、bool型）

**学習ポイント:**
- 文字列とポインタの関係
- 文字列の終端（ヌル文字）の処理
- ポインタを使った文字列操作関数の実装
- バッファオーバーフローの防止

### 演習10-4: 配列操作関数
ポインタを使って配列の最大値、最小値、平均値を求める演習です。

- [ex10_4_array_functions.c](ex10_4_array_functions.c) - C90準拠版
- [ex10_4_array_functions_c99.c](ex10_4_array_functions_c99.c) - C99準拠版（//コメント、bool型、restrict修飾子）

**学習ポイント:**
- 配列をポインタとして関数に渡す方法
- 配列サイズの適切な管理
- ポインタを使った効率的な配列操作
- 関数の戻り値としてのポインタの活用

## C90とC99の主な違い

### 1. コメントスタイル
- C90: `/* */` のみ
- C99: `//` 単一行コメントも使用可能

### 2. 変数宣言
- C90: ブロックの先頭でのみ宣言可能
- C99: 使用箇所で宣言可能（forループ内での宣言など）

### 3. bool型
- C90: 存在しない（intで代用）
- C99: `<stdbool.h>`で`bool`、`true`、`false`が使用可能

### 4. インライン関数
- C90: 存在しない
- C99: `inline`キーワードで関数のインライン化が可能

### 5. 可変長配列（VLA）
- C90: 存在しない
- C99: 実行時にサイズが決まる配列を作成可能

### 6. 複合リテラル
- C90: 存在しない
- C99: `(Type){初期化子}`の形式で一時オブジェクトを作成可能

### 7. 指定初期化子
- C90: 存在しない
- C99: `{[index] = value}`の形式で配列の特定要素を初期化可能

### 8. restrict修飾子
- C90: 存在しない
- C99: ポインタが重複しないことをコンパイラに伝える最適化ヒント

### 9. 固定幅整数型
- C90: 存在しない
- C99: `<stdint.h>`で`int8_t`、`int16_t`、`int32_t`などが使用可能

## 実行方法

```bash
# C90版のコンパイルと実行
gcc -std=c90 -Wall -Wextra -pedantic ex10_1_pointer_swap.c -o ex10_1_pointer_swap
./ex10_1_pointer_swap

# C99版のコンパイルと実行
gcc -std=c99 -Wall -Wextra -pedantic ex10_1_pointer_swap_c99.c -o ex10_1_pointer_swap_c99
./ex10_1_pointer_swap_c99

# その他の演習例
gcc -std=c90 -Wall -Wextra -pedantic ex10_2_array_reverse.c -o ex10_2_array_reverse
gcc -std=c90 -Wall -Wextra -pedantic ex10_3_string_manipulation.c -o ex10_3_string_manipulation
gcc -std=c90 -Wall -Wextra -pedantic ex10_4_array_functions.c -o ex10_4_array_functions

# Makefileを使用した場合
make run-ex10_1_pointer_swap      # C90版
make run-ex10_1_pointer_swap_c99  # C99版
make run-ex10_2_array_reverse     # C90版
make run-ex10_2_array_reverse_c99 # C99版
make run-ex10_3_string_manipulation     # C90版
make run-ex10_3_string_manipulation_c99 # C99版
make run-ex10_4_array_functions     # C90版
make run-ex10_4_array_functions_c99 # C99版
```

## ポインタ使用時の注意事項

### 1. 初期化の重要性
```c
// NG: 未初期化ポインタの使用
int *ptr;
*ptr = 10;  // 危険！未初期化ポインタの参照

// OK: 適切な初期化
int value = 0;
int *ptr = &value;
*ptr = 10;  // 安全
```

### 2. NULLポインタのチェック
```c
// 関数でポインタを受け取る際は必ずチェック
void process_data(int *ptr)
{
    if (ptr == NULL) {
        printf("エラー: NULLポインタが渡されました\n");
        return;
    }
    // 処理を続行
}
```

### 3. 配列の境界チェック
```c
// 配列のサイズを超えたアクセスは未定義動作
int arr[5] = {1, 2, 3, 4, 5};
int *ptr = arr;

// NG: 境界を超えたアクセス
printf("%d\n", *(ptr + 10));  // 危険！

// OK: 境界内でのアクセス
for (int i = 0; i < 5; i++) {
    printf("%d ", *(ptr + i));
}
```

### 4. ローカル変数のアドレスを返さない
```c
// NG: ローカル変数のアドレスを返す
int* dangerous_function(void)
{
    int local_var = 100;
    return &local_var;  // 危険！関数終了後に無効になる
}

// OK: 静的変数または呼び出し元から受け取ったポインタを返す
int* safe_function(int *input)
{
    static int static_var = 100;
    return &static_var;  // 安全（静的変数）
    // または return input; （引数として受け取ったポインタ）
}
```

## デバッグのヒント

1. **アドレスの確認**: `printf("%p\n", (void*)ptr)` でポインタの値を確認
2. **値の確認**: `printf("%d\n", *ptr)` でポインタが指す値を確認
3. **境界チェック**: 配列アクセス前に必ず範囲をチェック
4. **コンパイラ警告**: `-Wall -Wextra -pedantic` を使用して警告を有効化

これらの解答例を参考に、ポインタの安全で効果的な使用方法を身につけてください。