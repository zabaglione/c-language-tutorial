/*
 * ファイル名: ex5_4_draw_shapes_c99.c
 * 演習5-4: 図形の描画
 * 説明: アスタリスクを使って様々な図形を描画するプログラム
 * 規格: C99準拠
 */
#include <stdio.h>

int main(void)
{
    printf("=== 図形描画プログラム ===\n");
    printf("図形のサイズを入力してください: ");
    
    int size;
    scanf("%d", &size);
    
    // 入力値の検証
    if (size <= 0) {
        printf("エラー: 正の整数を入力してください。\n");
        return 1;
    }
    
    // 1. 正方形の描画
    printf("\n1. 正方形（%d×%d）:\n", size, size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("*");
        }
        printf("\n");
    }
    
    // 2. 直角三角形の描画
    printf("\n2. 直角三角形:\n");
    for (int i = 1; i <= size; i++) {
        for (int j = 0; j < i; j++) {
            printf("*");
        }
        printf("\n");
    }
    
    // 3. 逆直角三角形の描画
    printf("\n3. 逆直角三角形:\n");
    for (int i = size; i >= 1; i--) {
        for (int j = 0; j < i; j++) {
            printf("*");
        }
        printf("\n");
    }
    
    // 4. ダイヤモンドの描画
    printf("\n4. ダイヤモンド:\n");
    
    // 上半分（中央含む）
    for (int i = 1; i <= size; i += 2) {
        // 先頭のスペース
        int spaces = (size - i) / 2;
        for (int j = 0; j < spaces; j++) {
            printf(" ");
        }
        
        // アスタリスクの出力
        for (int j = 0; j < i; j++) {
            printf("*");
        }
        printf("\n");
    }
    
    // 下半分
    for (int i = size - 2; i >= 1; i -= 2) {
        // 先頭のスペース
        int spaces = (size - i) / 2;
        for (int j = 0; j < spaces; j++) {
            printf(" ");
        }
        
        // アスタリスクの出力
        for (int j = 0; j < i; j++) {
            printf("*");
        }
        printf("\n");
    }
    
    // 5. 右直角三角形（空白付き）
    printf("\n5. 右直角三角形:\n");
    for (int i = 1; i <= size; i++) {
        // 先頭のスペース
        for (int j = 0; j < size - i; j++) {
            printf(" ");
        }
        // アスタリスク
        for (int j = 0; j < i; j++) {
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
- C99準拠のため、変数を使用箇所の近くで宣言
- for文内でのループ変数宣言
- 変数の初期化を宣言と同時に実行
- コメントに//スタイルを使用
- ダイヤモンドは上半分と下半分に分けて実装
*/
