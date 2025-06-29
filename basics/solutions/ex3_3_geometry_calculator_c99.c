/*
 * ファイル名: ex3_3_geometry_calculator_c99.c
 * 課題3-3: 図形計算プログラム (C99版)
 * 説明: 円と長方形の面積・周囲長を計算するプログラム
 * 規格: C99準拠
 */

#include <stdio.h>

// 円周率の定義
#define PI 3.14159

int main(void)
{
    printf("=== 図形計算プログラム ===\n");
    
    // ユーザーからの入力受付
    double radius;
    printf("円の半径を入力してください: ");
    scanf("%lf", &radius);
    
    double width, height;
    printf("長方形の幅を入力してください: ");
    scanf("%lf", &width);
    printf("長方形の高さを入力してください: ");
    scanf("%lf", &height);
    
    // 円の計算
    double circle_area = PI * radius * radius;
    double circle_circumference = 2 * PI * radius;
    
    // 長方形の計算
    double rectangle_area = width * height;
    double rectangle_perimeter = 2 * (width + height);
    
    // 結果の表示
    printf("\n=== 計算結果 ===\n");
    printf("【円】\n");
    printf("  半径: %.1f\n", radius);
    printf("  面積: %.1f\n", circle_area);
    printf("  円周: %.1f\n", circle_circumference);
    
    printf("\n【長方形】\n");
    printf("  幅: %.1f, 高さ: %.1f\n", width, height);
    printf("  面積: %.1f\n", rectangle_area);
    printf("  周囲長: %.1f\n", rectangle_perimeter);
    
    return 0;
}