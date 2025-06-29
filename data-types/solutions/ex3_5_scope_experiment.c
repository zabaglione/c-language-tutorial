/*
 * ファイル名: ex3_5_scope_experiment.c
 * 演習3-5: スコープの実験
 * 説明: グローバル変数とローカル変数を使い分ける
 * 規格: C90準拠
 */
#include <stdio.h>

/* グローバル変数 */
int global_counter = 0;
double global_total = 0.0;
static int file_private = 100;  /* ファイル内でのみアクセス可能 */

/* 関数プロトタイプ宣言 */
void increment_counter(void);
void add_to_total(double value);
void static_demo(void);
void scope_hiding_demo(void);
int get_next_id(void);

int main(void)
{
    /* ローカル変数 */
    int local_var = 10;
    
    printf("=== スコープの実験 ===\n");
    
    /* グローバル変数の初期値表示 */
    printf("初期状態:\n");
    printf("  global_counter = %d\n", global_counter);
    printf("  global_total = %.1f\n", global_total);
    printf("  local_var = %d\n", local_var);
    printf("  file_private = %d\n", file_private);
    
    /* グローバル変数の操作 */
    printf("\nグローバル変数の操作:\n");
    increment_counter();
    increment_counter();
    add_to_total(15.5);
    add_to_total(24.3);
    
    printf("  操作後 global_counter = %d\n", global_counter);
    printf("  操作後 global_total = %.1f\n", global_total);
    
    /* ローカル変数の操作 */
    printf("\nローカル変数の操作:\n");
    local_var += 5;
    printf("  操作後 local_var = %d\n", local_var);
    
    /* 静的変数のデモ */
    printf("\n静的変数のデモ:\n");
    static_demo();
    static_demo();
    static_demo();
    
    /* IDジェネレータのデモ */
    printf("\nIDジェネレータのデモ:\n");
    printf("  ID: %d\n", get_next_id());
    printf("  ID: %d\n", get_next_id());
    printf("  ID: %d\n", get_next_id());
    
    /* スコープの隠蔽デモ */
    printf("\nスコープの隠蔽デモ:\n");
    scope_hiding_demo();
    
    /* ブロックスコープのデモ */
    printf("\nブロックスコープのデモ:\n");
    {
        int block_var = 99;
        printf("  ブロック内 block_var = %d\n", block_var);
        printf("  ブロック内 local_var = %d\n", local_var);  /* main()のローカル変数にアクセス */
        
        {
            int nested_var = 88;
            printf("  さらに内側 nested_var = %d\n", nested_var);
            printf("  さらに内側 block_var = %d\n", block_var);  /* 外側のblock_varにアクセス */
        }
        /* nested_varはここではアクセス不可 */
    }
    /* block_varはここではアクセス不可 */
    
    return 0;
}

/* グローバルカウンタをインクリメントする関数 */
void increment_counter(void)
{
    global_counter++;
    printf("  increment_counter(): global_counter = %d\n", global_counter);
}

/* グローバル合計に値を加算する関数 */
void add_to_total(double value)
{
    global_total += value;
    printf("  add_to_total(%.1f): global_total = %.1f\n", value, global_total);
}

/* 静的ローカル変数のデモ */
void static_demo(void)
{
    static int static_count = 0;    /* 静的ローカル変数、初期化は1回のみ */
    int auto_count = 0;             /* 自動変数、関数呼出ごとに初期化 */
    
    static_count++;
    auto_count++;
    
    printf("  static_demo() 呼出: static_count = %d, auto_count = %d\n", 
           static_count, auto_count);
}

/* ユニークID生成器 */
int get_next_id(void)
{
    static int id_counter = 1000;  /* 初期値1000から開始 */
    
    return id_counter++;    /* 現在値を返してからインクリメント */
}

/* スコープの隠蔽（シャドウイング）のデモ */
void scope_hiding_demo(void)
{
    int global_counter = 999;   /* グローバル変数を隠蔽するローカル変数 */
    
    printf("  関数内 global_counter = %d (ローカル変数)\n", global_counter);
    printf("  実際のグローバル変数は隠蔽されている\n");
    
    {
        int global_counter = 777;   /* さらに内側で隠蔽 */
        printf("  ブロック内 global_counter = %d (より内側のローカル変数)\n", global_counter);
    }
    
    printf("  ブロック外 global_counter = %d (関数のローカル変数に戻る)\n", global_counter);
}

/*
学習ポイント:
1. グローバル変数はファイル全体でアクセス可能
2. ローカル変数は宣言されたブロック内でのみ有効
3. 静的ローカル変数は関数呼出間で値を保持
4. static指定子でファイル内限定のグローバル変数を作成可能
5. 内側のスコープで同名変数を宣言すると外側を隠蔽
6. ブロックスコープは {} で区切られた範囲

スコープの種類:
- ファイルスコープ: グローバル変数、関数
- 関数スコープ: 関数内のローカル変数
- ブロックスコープ: {} 内の変数

変数の生存期間:
- 自動変数: ブロック開始時に作成、終了時に破棄
- 静的変数: プログラム開始時に作成、終了まで存続
- グローバル変数: プログラム全体で存続

実践的な使用例:
- グローバル変数: 設定値、状態管理
- 静的ローカル変数: カウンタ、キャッシュ
- ローカル変数: 一時的な計算、処理用データ
*/
