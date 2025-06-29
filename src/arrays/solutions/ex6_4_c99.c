/*
 * 演習 6-4: 行列演算（C99版）
 * 
 * 2次元配列を使って行列演算（加算、減算、乗算、転置）を
 * 実行するプログラム
 * C99特有の機能：変数の混在宣言、forループ内変数宣言を使用
 */
#include <stdio.h>

#define ROWS 3
#define COLS 3

/* 行列を表示する関数 */
void display_matrix(int matrix[][COLS], int rows, int cols, const char* title)
{
    printf("=== %s ===\n", title);
    for (int i = 0; i < rows; i++) {  /* C99：forループ内変数宣言 */
        for (int j = 0; j < cols; j++) {  /* C99：forループ内変数宣言 */
            printf("%4d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

/* 行列の加算を行う関数 */
void add_matrices(int a[][COLS], int b[][COLS], int result[][COLS], int rows, int cols)
{
    for (int i = 0; i < rows; i++) {  /* C99：forループ内変数宣言 */
        for (int j = 0; j < cols; j++) {  /* C99：forループ内変数宣言 */
            result[i][j] = a[i][j] + b[i][j];
        }
    }
}

/* 行列の減算を行う関数 */
void subtract_matrices(int a[][COLS], int b[][COLS], int result[][COLS], int rows, int cols)
{
    for (int i = 0; i < rows; i++) {  /* C99：forループ内変数宣言 */
        for (int j = 0; j < cols; j++) {  /* C99：forループ内変数宣言 */
            result[i][j] = a[i][j] - b[i][j];
        }
    }
}

/* 行列の乗算を行う関数 */
void multiply_matrices(int a[][COLS], int b[][COLS], int result[][COLS], int rows, int cols)
{
    /* 結果行列を初期化 */
    for (int i = 0; i < rows; i++) {  /* C99：forループ内変数宣言 */
        for (int j = 0; j < cols; j++) {  /* C99：forループ内変数宣言 */
            result[i][j] = 0;
        }
    }
    
    /* 行列の乗算: result[i][j] = Σ(a[i][k] * b[k][j]) */
    for (int i = 0; i < rows; i++) {  /* C99：forループ内変数宣言 */
        for (int j = 0; j < cols; j++) {  /* C99：forループ内変数宣言 */
            for (int k = 0; k < cols; k++) {  /* C99：forループ内変数宣言 */
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

/* 転置行列を計算する関数 */
void transpose_matrix(int matrix[][COLS], int result[][ROWS], int rows, int cols)
{
    for (int i = 0; i < rows; i++) {  /* C99：forループ内変数宣言 */
        for (int j = 0; j < cols; j++) {  /* C99：forループ内変数宣言 */
            result[j][i] = matrix[i][j];
        }
    }
}

/* 転置行列専用の表示関数（行と列が入れ替わる） */
void display_transposed_matrix(int matrix[][ROWS], int rows, int cols, const char* title)
{
    printf("=== %s ===\n", title);
    for (int i = 0; i < rows; i++) {  /* C99：forループ内変数宣言 */
        for (int j = 0; j < cols; j++) {  /* C99：forループ内変数宣言 */
            printf("%4d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

/* 行列に値を入力する関数 */
void input_matrix(int matrix[][COLS], int rows, int cols, const char* name)
{
    printf("=== %s の入力 ===\n", name);
    for (int i = 0; i < rows; i++) {  /* C99：forループ内変数宣言 */
        for (int j = 0; j < cols; j++) {  /* C99：forループ内変数宣言 */
            printf("%s[%d][%d]: ", name, i, j);
            scanf("%d", &matrix[i][j]);
        }
    }
    printf("\n");
}

int main(void)
{
    int matrix_a[ROWS][COLS];
    int matrix_b[ROWS][COLS];
    int result[ROWS][COLS];
    int transposed[COLS][ROWS];  /* 転置行列は行と列が入れ替わる */
    
    printf("=== 行列演算プログラム ===\n");
    printf("3x3の行列2つで各種演算を行います。\n\n");
    
    /* 行列の入力 */
    input_matrix(matrix_a, ROWS, COLS, "行列A");
    input_matrix(matrix_b, ROWS, COLS, "行列B");
    
    /* 入力された行列を表示 */
    display_matrix(matrix_a, ROWS, COLS, "行列A");
    display_matrix(matrix_b, ROWS, COLS, "行列B");
    
    /* 行列の加算 */
    add_matrices(matrix_a, matrix_b, result, ROWS, COLS);
    display_matrix(result, ROWS, COLS, "行列A + 行列B");
    
    /* 行列の減算 */
    subtract_matrices(matrix_a, matrix_b, result, ROWS, COLS);
    display_matrix(result, ROWS, COLS, "行列A - 行列B");
    
    /* 行列の乗算 */
    multiply_matrices(matrix_a, matrix_b, result, ROWS, COLS);
    display_matrix(result, ROWS, COLS, "行列A x 行列B");
    
    /* 行列Aの転置 */
    transpose_matrix(matrix_a, transposed, ROWS, COLS);
    display_transposed_matrix(transposed, COLS, ROWS, "行列Aの転置");
    
    /* 行列Bの転置 */
    transpose_matrix(matrix_b, transposed, ROWS, COLS);
    display_transposed_matrix(transposed, COLS, ROWS, "行列Bの転置");
    
    return 0;
}