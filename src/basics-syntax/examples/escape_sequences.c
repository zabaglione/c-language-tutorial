/*
 * エスケープシーケンスのデモ
 * 特殊文字の使い方
 */
#include <stdio.h>

int main(void)
{
    printf("=== エスケープシーケンス ===\n");
    
    /* 改行とタブ */
    printf("改行\nとタブ\tの例\n");
    
    /* ダブルクォート */
    printf("ダブルクォート: \"Hello\"\n");
    
    /* バックスラッシュ */
    printf("パス: C:\\Program Files\\\n");
    
    /* 表形式の出力 */
    printf("\n--- 表形式の例 ---\n");
    printf("名前\t年齢\t職業\n");
    printf("田中\t25\tエンジニア\n");
    printf("佐藤\t30\tデザイナー\n");
    
    return 0;
}