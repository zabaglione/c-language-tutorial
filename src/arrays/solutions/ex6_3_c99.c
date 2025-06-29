/*
 * 演習 6-3: 文字列配列の操作（C99版）
 * 
 * 都道府県名を管理し、各種操作（ソート、検索、
 * 文字数カウント等）を行うプログラム
 * C99特有の機能：変数の混在宣言、forループ内変数宣言を使用
 */
#include <stdio.h>
#include <string.h>

#define NUM_PREFECTURES 10
#define MAX_NAME_LENGTH 20

/* 都道府県名のサンプルデータ */
char prefectures[NUM_PREFECTURES][MAX_NAME_LENGTH] = {
    "東京都", "神奈川県", "大阪府", "愛知県", "埼玉県",
    "千葉県", "兵庫県", "北海道", "福岡県", "静岡県"
};

/* 文字列配列をアルファベット順（辞書順）にソートする関数 */
void sort_prefectures(char arr[][MAX_NAME_LENGTH], int size)
{
    char temp[MAX_NAME_LENGTH];
    
    /* バブルソート */
    for (int i = 0; i < size - 1; i++) {  /* C99：forループ内変数宣言 */
        for (int j = 0; j < size - 1 - i; j++) {  /* C99：forループ内変数宣言 */
            if (strcmp(arr[j], arr[j + 1]) > 0) {
                strcpy(temp, arr[j]);
                strcpy(arr[j], arr[j + 1]);
                strcpy(arr[j + 1], temp);
            }
        }
    }
}

/* 全都道府県名を表示する関数 */
void display_all_prefectures(char arr[][MAX_NAME_LENGTH], int size)
{
    printf("=== 都道府県一覧 ===\n");
    for (int i = 0; i < size; i++) {  /* C99：forループ内変数宣言 */
        printf("%2d. %s\n", i + 1, arr[i]);
    }
    printf("\n");
}

/* 最も文字数が長い都道府県名を見つける関数 */
void find_longest_name(char arr[][MAX_NAME_LENGTH], int size)
{
    int max_length = 0;
    int max_index = 0;
    
    for (int i = 0; i < size; i++) {  /* C99：forループ内変数宣言 */
        int length = strlen(arr[i]);  /* C99：必要な時に変数宣言 */
        if (length > max_length) {
            max_length = length;
            max_index = i;
        }
    }
    
    printf("=== 最も文字数が長い都道府県名 ===\n");
    printf("都道府県名: %s\n", arr[max_index]);
    printf("文字数: %d文字\n\n", max_length);
}

/* 指定した文字で始まる都道府県名を検索する関数 */
void search_by_first_char(char arr[][MAX_NAME_LENGTH], int size, char first_char)
{
    int found = 0;
    
    printf("=== '%c'で始まる都道府県名 ===\n", first_char);
    
    for (int i = 0; i < size; i++) {  /* C99：forループ内変数宣言 */
        if (arr[i][0] == first_char) {
            printf("- %s\n", arr[i]);
            found = 1;
        }
    }
    
    if (!found) {
        printf("見つかりませんでした。\n");
    }
    printf("\n");
}

/* 「県」が含まれる都道府県をカウントする関数 */
int count_ken_prefectures(char arr[][MAX_NAME_LENGTH], int size)
{
    int count = 0;
    
    for (int i = 0; i < size; i++) {  /* C99：forループ内変数宣言 */
        if (strstr(arr[i], "県") != NULL) {
            count++;
        }
    }
    
    return count;
}

/* 都道府県の種類別カウントを表示する関数 */
void display_type_count(char arr[][MAX_NAME_LENGTH], int size)
{
    int ken_count = 0;
    int fu_count = 0;
    int to_count = 0;
    int do_count = 0;
    
    for (int i = 0; i < size; i++) {  /* C99：forループ内変数宣言 */
        if (strstr(arr[i], "県") != NULL) {
            ken_count++;
        } else if (strstr(arr[i], "府") != NULL) {
            fu_count++;
        } else if (strstr(arr[i], "都") != NULL) {
            to_count++;
        } else if (strstr(arr[i], "道") != NULL) {
            do_count++;
        }
    }
    
    printf("=== 都道府県の種類別カウント ===\n");
    printf("県: %d個\n", ken_count);
    printf("府: %d個\n", fu_count);
    printf("都: %d個\n", to_count);
    printf("道: %d個\n", do_count);
    printf("\n");
}

int main(void)
{
    char working_array[NUM_PREFECTURES][MAX_NAME_LENGTH];
    
    printf("=== 都道府県管理システム ===\n\n");
    
    /* 作業用配列にコピー（元データを保持するため） */
    for (int i = 0; i < NUM_PREFECTURES; i++) {  /* C99：forループ内変数宣言 */
        strcpy(working_array[i], prefectures[i]);
    }
    
    /* 元の順序で表示 */
    printf("--- 元の順序 ---\n");
    display_all_prefectures(prefectures, NUM_PREFECTURES);
    
    /* ソートして表示 */
    sort_prefectures(working_array, NUM_PREFECTURES);
    printf("--- 辞書順ソート後 ---\n");
    display_all_prefectures(working_array, NUM_PREFECTURES);
    
    /* 最も長い都道府県名を表示 */
    find_longest_name(prefectures, NUM_PREFECTURES);
    
    /* 指定文字で始まる都道府県を検索 */
    printf("検索したい最初の文字を入力してください: ");
    char search_char;  /* C99：必要な時に変数宣言 */
    scanf(" %c", &search_char);  /* 先頭の空白でバッファをクリア */
    search_by_first_char(prefectures, NUM_PREFECTURES, search_char);
    
    /* 「県」を含む都道府県をカウント */
    int ken_count = count_ken_prefectures(prefectures, NUM_PREFECTURES);  /* C99：必要な時に変数宣言 */
    printf("「県」が含まれる都道府県: %d個\n\n", ken_count);
    
    /* 種類別カウントを表示 */
    display_type_count(prefectures, NUM_PREFECTURES);
    
    return 0;
}