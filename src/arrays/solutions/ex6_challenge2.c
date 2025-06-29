/*
 * チャレンジ問題 2: ライフゲーム（Conway's Game of Life）（C90準拠版）
 * 
 * セル・オートマトンの一種であるライフゲームを実装する
 * 20x20のグリッドで実装し、世代を進めるごとに画面を更新
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GRID_SIZE 20
#define MAX_GENERATIONS 100

/* グリッドの状態を表示する関数 */
void display_grid(int grid[][GRID_SIZE], int generation)
{
    int i, j;
    
    /* 画面をクリア（簡易的な方法） */
    printf("\n\n=== ライフゲーム - 第%d世代 ===\n", generation);
    printf("  ");
    for (j = 0; j < GRID_SIZE; j++) {
        printf("%2d", j % 10);
    }
    printf("\n");
    
    for (i = 0; i < GRID_SIZE; i++) {
        printf("%2d", i % 10);
        for (j = 0; j < GRID_SIZE; j++) {
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
    int i, j;
    int count = 0;
    int dr[] = {-1, -1, -1, 0, 0, 1, 1, 1};  /* 行の変位 */
    int dc[] = {-1, 0, 1, -1, 1, -1, 0, 1};  /* 列の変位 */
    
    for (i = 0; i < 8; i++) {
        int new_row = row + dr[i];
        int new_col = col + dc[i];
        
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
    int i, j;
    int neighbors;
    
    for (i = 0; i < GRID_SIZE; i++) {
        for (j = 0; j < GRID_SIZE; j++) {
            neighbors = count_neighbors(current, i, j);
            
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
    int i, j;
    for (i = 0; i < GRID_SIZE; i++) {
        for (j = 0; j < GRID_SIZE; j++) {
            grid[i][j] = 0;
        }
    }
}

/* グリッドをコピーする関数 */
void copy_grid(int source[][GRID_SIZE], int dest[][GRID_SIZE])
{
    int i, j;
    for (i = 0; i < GRID_SIZE; i++) {
        for (j = 0; j < GRID_SIZE; j++) {
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
    int i, j;
    
    clear_grid(grid);
    
    for (i = 0; i < GRID_SIZE; i++) {
        for (j = 0; j < GRID_SIZE; j++) {
            if (rand() % 100 < density) {
                grid[i][j] = 1;
            }
        }
    }
}

/* カスタムパターンを入力する関数 */
void set_custom_pattern(int grid[][GRID_SIZE])
{
    int row, col;
    char input[10];
    
    clear_grid(grid);
    
    printf("カスタムパターンを設定します。\n");
    printf("生きているセルの座標を入力してください（0-%d）\n", GRID_SIZE-1);
    printf("終了するには -1 -1 を入力してください。\n\n");
    
    while (1) {
        printf("行 列: ");
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
    int choice;
    
    printf("=== ライフゲーム ===\n");
    printf("1. グライダー（移動するパターン）\n");
    printf("2. ビーコン（振動するパターン）\n");
    printf("3. ランダムパターン\n");
    printf("4. カスタムパターン\n");
    printf("5. 終了\n");
    printf("選択してください (1-5): ");
    
    scanf("%d", &choice);
    return choice;
}

/* 2つのグリッドが同じかどうかチェックする関数 */
int grids_equal(int grid1[][GRID_SIZE], int grid2[][GRID_SIZE])
{
    int i, j;
    
    for (i = 0; i < GRID_SIZE; i++) {
        for (j = 0; j < GRID_SIZE; j++) {
            if (grid1[i][j] != grid2[i][j]) {
                return 0;
            }
        }
    }
    return 1;
}

int main(void)
{
    /* C90では先頭で全ての変数を宣言 */
    int current_grid[GRID_SIZE][GRID_SIZE];
    int next_grid[GRID_SIZE][GRID_SIZE];
    int previous_grid[GRID_SIZE][GRID_SIZE];
    int choice;
    int generation;
    char input[10];
    
    srand((unsigned int)time(NULL));
    
    while (1) {
        choice = display_menu();
        
        switch (choice) {
            case 1:
                set_glider_pattern(current_grid);
                break;
            case 2:
                set_beacon_pattern(current_grid);
                break;
            case 3:
                printf("セルの密度を入力してください (1-50): ");
                scanf("%d", &generation);  /* 一時的にgeneration変数を使用 */
                if (generation < 1) generation = 1;
                if (generation > 50) generation = 50;
                set_random_pattern(current_grid, generation);
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
        
        for (generation = 0; generation < MAX_GENERATIONS; generation++) {
            display_grid(current_grid, generation);
            
            printf("Enterキーで次世代へ、'q'で戻る: ");
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
        
        if (generation >= MAX_GENERATIONS) {
            printf("最大世代数に達しました。\n");
        }
        
        printf("\nメニューに戻ります...\n\n");
    }
    
    return 0;
}