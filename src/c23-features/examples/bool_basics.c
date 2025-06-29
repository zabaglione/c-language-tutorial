/*
 * ファイル名: bool_basics.c
 * 説明: C23のbool型の基本的な使用例
 * 規格: C23
 */

#include <stdio.h>

/* C23では<stdbool.h>なしでbool, true, falseが使用可能 */

/* 関数プロトタイプ宣言 */
bool check_system(void);

int main(void)
{
    printf("=== C23 bool型の基本 ===\n");
    
    /* bool型の宣言と初期化 */
    bool is_ready = true;
    bool has_error = false;
    
    printf("is_ready: %s\n", is_ready ? "true" : "false");
    printf("has_error: %s\n", has_error ? "true" : "false");
    
    /* bool型のサイズ */
    printf("\nbool型のサイズ: %zu バイト\n", sizeof(bool));
    
    /* 論理演算 */
    bool result = is_ready && !has_error;
    printf("\nis_ready && !has_error = %s\n", result ? "true" : "false");
    
    /* 条件式での使用 */
    if (is_ready) {
        printf("\nシステムは準備完了です\n");
    }
    
    /* 関数の戻り値として使用 */
    bool status = check_system();
    printf("\nシステムチェック結果: %s\n", status ? "正常" : "異常");
    
    /* 配列での使用 */
    bool flags[5] = {true, false, true, true, false};
    printf("\nフラグ配列: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", flags[i]);
    }
    printf("\n");
    
    /* C90/C99との比較 */
    printf("\n=== C90/C99との比較 ===\n");
    printf("C90: int型や#defineマクロで真偽値を表現\n");
    printf("C99: <stdbool.h>をインクルードして使用\n");
    printf("C23: 標準でbool/true/falseが利用可能\n");
    
    return 0;
}


/* bool型を返す関数 */
bool check_system(void)
{
    /* システムチェックのシミュレーション */
    return true;  /* 正常 */
}

/*
 * 実行結果例:
 * === C23 bool型の基本 ===
 * is_ready: true
 * has_error: false
 * 
 * bool型のサイズ: 1 バイト
 * 
 * is_ready && !has_error = true
 * 
 * システムは準備完了です
 * 
 * システムチェック結果: 正常
 * 
 * フラグ配列: 1 0 1 1 0 
 * 
 * === C90/C99との比較 ===
 * C90: int型や#defineマクロで真偽値を表現
 * C99: <stdbool.h>をインクルードして使用
 * C23: 標準でbool/true/falseが利用可能
 */