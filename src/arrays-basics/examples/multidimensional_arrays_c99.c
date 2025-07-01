/*
 * 多次元配列の使い方（C99版）
 *
 * このプログラムは、2次元配列と3次元配列の
 * 宣言、初期化、操作方法を示します。
 * C99特有の機能：変数の混在宣言を使用
 */
#include <stdio.h>

int main(void)
{
    int i, j, k;

    /* 1. 2次元配列の基本 */
    printf("=== 2次元配列の基本 ===\n");

    /* 3x4の2次元配列 */
    int matrix[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}};

    /* 2次元配列の表示 */
    printf("3x4の行列:\n");
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 4; j++)
        {
            printf("%3d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    /* 2. 成績表の管理 */
    printf("=== 成績表（学生x科目）===\n");

    /* 5人の学生、3科目（国語、数学、英語）の成績 */
    int grades[5][3] = {
        {85, 92, 78}, /* 学生1 */
        {90, 88, 85}, /* 学生2 */
        {78, 85, 92}, /* 学生3 */
        {92, 76, 88}, /* 学生4 */
        {88, 90, 82}  /* 学生5 */
    };

    char *subjects[] = {"国語", "数学", "英語"};

    /* 成績表の表示 */
    printf("       ");
    for (j = 0; j < 3; j++)
    {
        printf("%-6s ", subjects[j]);
    }
    printf("平均\n");
    printf("----------------------------------------\n");

    for (i = 0; i < 5; i++)
    {
        printf("学生%d: ", i + 1);
        int sum = 0; /* C99：必要な時に変数宣言 */
        for (j = 0; j < 3; j++)
        {
            printf("%-6d ", grades[i][j]);
            sum += grades[i][j];
        }
        printf("%.1f\n", sum / 3.0);
    }

    /* 科目別平均 */
    printf("----------------------------------------\n");
    printf("平均:  ");
    for (j = 0; j < 3; j++)
    {
        int sum = 0; /* C99：必要な時に変数宣言 */
        for (i = 0; i < 5; i++)
        {
            sum += grades[i][j];
        }
        printf("%-6.1f ", sum / 5.0);
    }
    printf("\n\n");

    /* 3. 部分的な初期化 */
    printf("=== 2次元配列の部分初期化 ===\n");

    /* 部分的に初期化（残りは0） */
    int partial[4][5] = {
        {1, 2},    /* 残りの要素は0 */
        {3, 4, 5}, /* 残りの要素は0 */
        {6}        /* 残りの要素は0 */
        /* 4行目は全て0 */
    };

    printf("部分的に初期化された配列:\n");
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 5; j++)
        {
            printf("%2d ", partial[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    /* 4. 単位行列の作成 */
    printf("=== 単位行列の作成 ===\n");

    int identity[5][5];

    /* 単位行列を作成 */
    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 5; j++)
        {
            if (i == j)
            {
                identity[i][j] = 1;
            }
            else
            {
                identity[i][j] = 0;
            }
        }
    }

    /* 単位行列を表示 */
    printf("5x5の単位行列:\n");
    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 5; j++)
        {
            printf("%d ", identity[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    /* 5. 3次元配列の例 */
    printf("=== 3次元配列（RGB画像データの例）===\n");

    /* 2x3ピクセル、各ピクセルはRGB（3値） */
    int image[2][3][3] = {
        {
            {255, 0, 0}, /* 赤 */
            {0, 255, 0}, /* 緑 */
            {0, 0, 255}  /* 青 */
        },
        {
            {255, 255, 0}, /* 黄 */
            {255, 0, 255}, /* マゼンタ */
            {0, 255, 255}  /* シアン */
        }};

    printf("画像データ（2x3ピクセル）:\n");
    for (i = 0; i < 2; i++)
    {
        printf("行 %d:\n", i);
        for (j = 0; j < 3; j++)
        {
            printf("  ピクセル[%d][%d]: R=%3d, G=%3d, B=%3d\n",
                   i, j, image[i][j][0], image[i][j][1], image[i][j][2]);
        }
    }
    printf("\n");

    /* 6. 転置行列 */
    printf("=== 行列の転置 ===\n");

    int original_matrix[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}};
    int transposed[4][3];

    /* 転置を計算 */
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 4; j++)
        {
            transposed[j][i] = original_matrix[i][j];
        }
    }

    printf("元の行列（3x4）:\n");
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 4; j++)
        {
            printf("%3d ", original_matrix[i][j]);
        }
        printf("\n");
    }

    printf("\n転置行列（4x3）:\n");
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 3; j++)
        {
            printf("%3d ", transposed[i][j]);
        }
        printf("\n");
    }

    return 0;
}