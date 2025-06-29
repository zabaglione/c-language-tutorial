/*
 * ファイル名: ex5_4_draw_shapes.c
 * 演習5-4: 図形の描画
 * 説明: アスタリスクを使って様々な図形を描画するプログラム
 * 規格: C90準拠
 */
#include <stdio.h>

int main(void)
{
    /* 変数の宣言（C90では先頭で宣言） */
    int size;
    int i, j, spaces;
    
    printf("=== 図形描画プログラム ===\n");
    printf("図形のサイズを入力してください: ");
    scanf("%d", &size);
    
    /* 入力値の検証 */
    if (size <= 0) {
        printf("エラー: 正の整数を入力してください。\n");
        return 1;
    }
    
    /* 1. 正方形の描画 */
    printf("\n1. 正方形（%d×%d）:\n", size, size);
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            printf("*");
        }
        printf("\n");
    }
    
    /* 2. 直角三角形の描画 */
    printf("\n2. 直角三角形:\n");
    for (i = 1; i <= size; i++) {
        for (j = 0; j < i; j++) {
            printf("*");
        }
        printf("\n");
    }
    
    /* 3. 逆直角三角形の描画 */
    printf("\n3. 逆直角三角形:\n");
    for (i = size; i >= 1; i--) {
        for (j = 0; j < i; j++) {
            printf("*");
        }
        printf("\n");
    }
    
    /* 4. ダイヤモンドの描画 */
    printf("\n4. ダイヤモンド:\n");
    
    /* 上半分（中央含む） */
    for (i = 1; i <= size; i += 2) {
        /* 先頭のスペース */
        spaces = (size - i) / 2;
        for (j = 0; j < spaces; j++) {
            printf(" ");
        }
        
        /* アスタリスクの出力 */
        for (j = 0; j < i; j++) {
            printf("*");
        }
        printf("\n");
    }
    
    /* 下半分 */
    for (i = size - 2; i >= 1; i -= 2) {
        /* 先頭のスペース */
        spaces = (size - i) / 2;
        for (j = 0; j < spaces; j++) {
            printf(" ");
        }
        
        /* アスタリスクの出力 */
        for (j = 0; j < i; j++) {
            printf("*");
        }
        printf("\n");
    }
    
    /* 5. 右直角三角形（空白付き） */
    printf("\n5. 右直角三角形:\n");
    for (i = 1; i <= size; i++) {
        /* 先頭のスペース */
        for (j = 0; j < size - i; j++) {
            printf(" ");
        }
        /* アスタリスク */
        for (j = 0; j < i; j++) {
            printf("*");
        }
        printf("\n");
    }
    
    printf("\n図形の描画が完了しました。\n");
    
    return 0;
}

/*
学習ポイント:
1. ネストしたループによる2次元パターンの生成
2. 空白文字とアスタリスクの配置制御
3. ループ変数の増減による図形の変化
4. 複雑な図形（ダイヤモンド）の分解と実装

実装のポイント:
- C90準拠のため、すべての変数を関数先頭で宣言
- 外側ループで行、内側ループで列を制御
- 空白文字の計算と出力による図形の位置調整
- ダイヤモンドは上半分と下半分に分けて実装
- 様々なループパターンの組み合わせ
*/
