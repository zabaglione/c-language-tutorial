/*
 * C99バージョン - 必要に応じてC99機能を使用
 *
 * 基本的なfor文のデモ
 * 基礎的な繰り返し処理
 */
#include <stdio.h>

int main(void)
{
    int i;
    
    printf("=== 基本的なfor文 ===\n");
    
    /*
 * C99バージョン - 必要に応じてC99機能を使用
 * 1から5まで出力 */
    printf("1から5まで: ");
    for (i = 1; i <= 5; i++) {
        printf("%d ", i);
    }
    printf("\n");
    
    /*
 * C99バージョン - 必要に応じてC99機能を使用
 * 逆順ループ */
    printf("5から1まで: ");
    for (i = 5; i >= 1; i--) {
        printf("%d ", i);
    }
    printf("\n");
    
    /*
 * C99バージョン - 必要に応じてC99機能を使用
 * 偶数のみ */
    printf("偶数のみ: ");
    for (i = 2; i <= 10; i += 2) {
        printf("%d ", i);
    }
    printf("\n");
    
    return 0;
}