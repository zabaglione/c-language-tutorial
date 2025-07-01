/*
 * チャレンジ問題 2: ライフゲーム（Conway's Game of Life）（C99版）
 * 
 * セル・オートマトンの一種であるライフゲームを実装する
 * 20x20のグリッドで実装し、世代を進めるごとに画面を更新
 * C99特有の機能：変数の混在宣言、forループ内変数宣言を使用
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define GRID_SIZE 20
#define MAX_GENERATIONS 100

/* グリッドの状態を表示する関数 */
void display_grid(int grid[][GRID_SIZE], int generation)
{
    /* 画面をクリア（簡易的な方法） */
    printf("\n\n=== ライフゲーム - 第%d世代 ===\n", generation);
    printf("  ");
    for (int j = 0; j < GRID_SIZE; j++) {  /* C99：forループ内変数宣言 */
        printf("%2d", j % 10);
    }
    printf("\n");
    
    for (int i = 0; i < GRID_SIZE; i++) {  /* C99：forループ内変数宣言 */
        printf("%2d", i % 10);
        for (int j = 0; j < GRID_SIZE; j++) {  /* C99：forループ内変数宣言 */
            if (grid[i][j] == 1) {
                printf(" *");  /* 生きているセル */
            } else {
                printf("  ");  /* 死んでいるセル */
            }
        }
        printf("\n");
    }
    printf("\n");
}

/* 指定位置の周囲の生きているセルの数を数える関数 */
int count_neighbors(int grid[][GRID_SIZE], int row, int col)
{
    int dr[] = {-1, -1, -1, 0, 0, 1, 1, 1};  /* 行の変位 */
    int dc[] = {-1, 0, 1, -1, 1, -1, 0, 1};  /* 列の変位 */
    
    int count = 0;  /* C99：必要な時に変数宣言 */
    for (int i = 0; i < 8; i++) {  /* C99：forループ内変数宣言 */
        int new_row = row + dr[i];  /* C99：必要な時に変数宣言 */
        int new_col = col + dc[i];  /* C99：必要な時に変数宣言 */
        
        /* 境界チェック */
        if (new_row >= 0 && new_row < GRID_SIZE && 
            new_col >= 0 && new_col < GRID_SIZE) {
            count += grid[new_row][new_col];
        }
    }
    
    return count;
}

/* 次世代の状態を計算する関数 */
void next_generation(int current[][GRID_SIZE], int next[][GRID_SIZE])
{
    for (int i = 0; i < GRID_SIZE; i++) {  /* C99：forループ内変数宣言 */
        for (int j = 0; j < GRID_SIZE; j++) {  /* C99：forループ内変数宣言 */
            int neighbors = count_neighbors(current, i, j);  /* C99：必要な時に変数宣言 */
            
            /* ライフゲームのルール */
            if (current[i][j] == 1) {  /* 生きているセル */
                if (neighbors == 2 || neighbors == 3) {
                    next[i][j] = 1;  /* 生存 */
                } else {
                    next[i][j] = 0;  /* 死亡 */
                }
            } else {  /* 死んでいるセル */
                if (neighbors == 3) {
                    next[i][j] = 1;  /* 誕生 */
                } else {
                    next[i][j] = 0;  /* 死亡のまま */
                }
            }
        }
    }
}

/* グリッドをクリアする関数 */
void clear_grid(int grid[][GRID_SIZE])
{
    for (int i = 0; i < GRID_SIZE; i++) {  /* C99：forループ内変数宣言 */
        for (int j = 0; j < GRID_SIZE; j++) {  /* C99：forループ内変数宣言 */
            grid[i][j] = 0;
        }
    }
}

/* グリッドをコピーする関数 */
void copy_grid(int source[][GRID_SIZE], int dest[][GRID_SIZE])
{
    for (int i = 0; i < GRID_SIZE; i++) {  /* C99：forループ内変数宣言 */
        for (int j = 0; j < GRID_SIZE; j++) {  /* C99：forループ内変数宣言 */
            dest[i][j] = source[i][j];
        }
    }
}

/* 振動子パターン（ビーコン）を設定する関数 */
void set_beacon_pattern(int grid[][GRID_SIZE])
{
    clear_grid(grid);
    
    /* ビーコンパターン */
    grid[5][5] = 1; grid[5][6] = 1;
    grid[6][5] = 1; grid[6][6] = 1;
    grid[7][7] = 1; grid[7][8] = 1;
    grid[8][7] = 1; grid[8][8] = 1;
}

/* グライダーパターンを設定する関数 */
void set_glider_pattern(int grid[][GRID_SIZE])
{
    clear_grid(grid);
    
    /* グライダーパターン */
    grid[1][2] = 1;
    grid[2][3] = 1;
    grid[3][1] = 1; grid[3][2] = 1; grid[3][3] = 1;
}

/* ランダムパターンを設定する関数 */
void set_random_pattern(int grid[][GRID_SIZE], int density)
{
    clear_grid(grid);
    
    for (int i = 0; i < GRID_SIZE; i++) {  /* C99：forループ内変数宣言 */
        for (int j = 0; j < GRID_SIZE; j++) {  /* C99：forループ内変数宣言 */
            if (rand() % 100 < density) {
                grid[i][j] = 1;
            }
        }
    }
}

/* カスタムパターンを入力する関数 */
void set_custom_pattern(int grid[][GRID_SIZE])
{
    clear_grid(grid);
    
    printf("カスタムパターンを設定します。\n");
    printf("生きているセルの座標を入力してください（0-%d）\n", GRID_SIZE-1);
    printf("終了するには -1 -1 を入力してください。\n\n");
    
    while (1) {
        printf("行 列: ");
        int row, col;  /* C99：必要な時に変数宣言 */
        if (scanf("%d %d", &row, &col) != 2) {
            /* 入力エラーの場合、バッファをクリア */
            while (getchar() != '\n');
            continue;
        }
        
        if (row == -1 && col == -1) {
            break;
        }
        
        if (row >= 0 && row < GRID_SIZE && col >= 0 && col < GRID_SIZE) {
            grid[row][col] = 1;
            printf("セル[%d][%d]を生きた状態に設定しました。\n", row, col);
        } else {
            printf("無効な座標です。0-%d の範囲で入力してください。\n", GRID_SIZE-1);
        }
    }
}

/* メニューを表示する関数 */
int display_menu(void)
{
    printf("=== ライフゲーム ===\n");
    printf("1. グライダー（移動するパターン）\n");
    printf("2. ビーコン（振動するパターン）\n");
    printf("3. ランダムパターン\n");
    printf("4. カスタムパターン\n");
    printf("5. 終了\n");
    printf("選択してください (1-5): ");
    
    int choice;  /* C99：必要な時に変数宣言 */
    scanf("%d", &choice);
    return choice;
}

/* 2つのグリッドが同じかどうかチェックする関数 */
int grids_equal(int grid1[][GRID_SIZE], int grid2[][GRID_SIZE])
{
    for (int i = 0; i < GRID_SIZE; i++) {  /* C99：forループ内変数宣言 */
        for (int j = 0; j < GRID_SIZE; j++) {  /* C99：forループ内変数宣言 */
            if (grid1[i][j] != grid2[i][j]) {
                return 0;
            }
        }
    }
    return 1;
}

int main(void)
{
    srand((unsigned int)time(NULL));
    
    int current_grid[GRID_SIZE][GRID_SIZE];  /* C99：必要な時に変数宣言 */
    int next_grid[GRID_SIZE][GRID_SIZE];  /* C99：必要な時に変数宣言 */
    int previous_grid[GRID_SIZE][GRID_SIZE];  /* C99：必要な時に変数宣言 */
    
    while (1) {
        int choice = display_menu();  /* C99：必要な時に変数宣言 */
        
        switch (choice) {
            case 1:
                set_glider_pattern(current_grid);
                break;
            case 2:
                set_beacon_pattern(current_grid);
                break;
            case 3:
                printf("セルの密度を入力してください (1-50): ");
                int density;  /* C99：必要な時に変数宣言 */
                scanf("%d", &density);
                if (density < 1) density = 1;
                if (density > 50) density = 50;
                set_random_pattern(current_grid, density);
                break;
            case 4:
                set_custom_pattern(current_grid);
                break;
            case 5:
                printf("ライフゲームを終了します。\n");
                return 0;
            default:
                printf("無効な選択です。\n");
                continue;
        }
        
        /* シミュレーション開始 */
        copy_grid(current_grid, previous_grid);
        
        for (int generation = 0; generation < MAX_GENERATIONS; generation++) {  /* C99：forループ内変数宣言 */
            display_grid(current_grid, generation);
            
            printf("Enterキーで次世代へ、'q'で戻る: ");
            char input[10];  /* C99：必要な時に変数宣言 */
            fgets(input, sizeof(input), stdin);
            if (input[0] == '\n') {
                fgets(input, sizeof(input), stdin);  /* 実際の入力を読む */
            }
            
            if (input[0] == 'q' || input[0] == 'Q') {
                break;
            }
            
            /* 次世代を計算 */
            next_generation(current_grid, next_grid);
            
            /* 変化がないか、前の状態に戻った場合は終了 */
            if (grids_equal(current_grid, next_grid)) {
                printf("安定状態に達しました。\n");
                break;
            }
            if (grids_equal(next_grid, previous_grid)) {
                printf("振動状態に達しました。\n");
                break;
            }
            
            /* グリッドを更新 */
            copy_grid(current_grid, previous_grid);
            copy_grid(next_grid, current_grid);
        }
        
        printf("\nメニューに戻ります...\n\n");
    }
    
    return 0;
}