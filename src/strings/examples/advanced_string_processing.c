/*
 * 文字列処理の応用
 * ファイル名: advanced_string_processing.c
 * 説明: 実践的な文字列処理テクニックを学習
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKENS 10
#define MAX_LENGTH 100
#define MAX_STRINGS 5

/* 文字列を大文字に変換 */
void to_uppercase(char *str)
{
    int i;
    
    if (str == NULL) {
        return;
    }
    
    for (i = 0; str[i] != '\0'; i++) {
        str[i] = toupper((unsigned char)str[i]);
    }
}

/* 文字列を小文字に変換 */
void to_lowercase(char *str)
{
    int i;
    
    if (str == NULL) {
        return;
    }
    
    for (i = 0; str[i] != '\0'; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

/* 文字列配列のバブルソート */
void bubble_sort_strings(char arr[][MAX_LENGTH], int n)
{
    int i, j;
    char temp[MAX_LENGTH];
    
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - 1 - i; j++) {
            if (strcmp(arr[j], arr[j + 1]) > 0) {
                strcpy(temp, arr[j]);
                strcpy(arr[j], arr[j + 1]);
                strcpy(arr[j + 1], temp);
            }
        }
    }
}

/* 文字列配列での検索 */
int search_string(char arr[][MAX_LENGTH], int count, char *target)
{
    int i;
    
    for (i = 0; i < count; i++) {
        if (strcmp(arr[i], target) == 0) {
            return i;  /* 見つかった場合のインデックス */
        }
    }
    return -1;  /* 見つからない場合 */
}

int main(void)
{
    /* 文字列の分割（トークン化） */
    printf("=== 文字列の分割（トークン化） ===\n");
    char input[] = "apple,banana,cherry,date,elderberry";
    char tokens[MAX_TOKENS][MAX_LENGTH];
    char temp[100];
    char *token;
    int token_count = 0;
    int i;
    
    /* 入力文字列をコピー（strtokは元の文字列を変更するため） */
    strcpy(temp, input);
    
    /* カンマで分割 */
    token = strtok(temp, ",");
    while (token != NULL && token_count < MAX_TOKENS) {
        strcpy(tokens[token_count], token);
        token_count++;
        token = strtok(NULL, ",");
    }
    
    printf("分割結果:\n");
    for (i = 0; i < token_count; i++) {
        printf("%d: %s\n", i + 1, tokens[i]);
    }
    
    /* 文字列の変換（大文字・小文字） */
    printf("\n=== 文字列の変換（大文字・小文字） ===\n");
    char original[MAX_STRINGS][MAX_LENGTH] = {
        "Hello World",
        "Programming Language",
        "C Language Tutorial",
        "String Processing",
        "Array Manipulation"
    };
    char uppercase_copy[MAX_STRINGS][MAX_LENGTH];
    char lowercase_copy[MAX_STRINGS][MAX_LENGTH];
    
    /* 文字列をコピーして変換 */
    for (i = 0; i < MAX_STRINGS; i++) {
        strcpy(uppercase_copy[i], original[i]);
        strcpy(lowercase_copy[i], original[i]);
        
        to_uppercase(uppercase_copy[i]);
        to_lowercase(lowercase_copy[i]);
    }
    
    /* 結果の表示 */
    printf("元の文字列 -> 大文字 -> 小文字\n");
    printf("=====================================\n");
    for (i = 0; i < MAX_STRINGS; i++) {
        printf("%-20s -> %-20s -> %s\n", 
               original[i], uppercase_copy[i], lowercase_copy[i]);
    }
    
    /* 文字列配列のソートと検索 */
    printf("\n=== 文字列配列のソート ===\n");
    char words[8][MAX_LENGTH] = {
        "Zebra", "Apple", "Monkey", "Banana",
        "Cat", "Dog", "Elephant", "Fish"
    };
    
    printf("ソート前:\n");
    for (i = 0; i < 8; i++) {
        printf("%s ", words[i]);
    }
    printf("\n\n");
    
    /* バブルソート */
    bubble_sort_strings(words, 8);
    
    printf("ソート後:\n");
    for (i = 0; i < 8; i++) {
        printf("%s ", words[i]);
    }
    printf("\n");
    
    /* 検索のテスト */
    printf("\n=== 文字列の検索 ===\n");
    char cities[10][MAX_LENGTH] = {
        "Tokyo", "Osaka", "Kyoto", "Nagoya", "Sapporo",
        "Fukuoka", "Kobe", "Sendai", "Hiroshima", "Yokohama"
    };
    char search_target[] = "Kyoto";
    int result;
    
    printf("都市一覧:\n");
    for (i = 0; i < 10; i++) {
        printf("%d. %s\n", i + 1, cities[i]);
    }
    
    /* 検索実行 */
    result = search_string(cities, 10, search_target);
    if (result != -1) {
        printf("\n\"%s\" は %d番目にあります。\n", search_target, result + 1);
    } else {
        printf("\n\"%s\" は見つかりませんでした。\n", search_target);
    }
    
    /* 簡易データベースの例 */
    printf("\n=== 簡易従業員データベース ===\n");
    char employee_names[3][MAX_LENGTH] = {
        "田中太郎", "佐藤花子", "鈴木一郎"
    };
    char departments[3][MAX_LENGTH] = {
        "開発", "営業", "開発"
    };
    char positions[3][MAX_LENGTH] = {
        "課長", "部長", "一般"
    };
    int salaries[3] = {800000, 1200000, 500000};
    
    /* 全従業員の表示 */
    printf("%-12s %-8s %-8s %s\n", "名前", "部署", "役職", "給与");
    printf("--------------------------------------------------\n");
    for (i = 0; i < 3; i++) {
        printf("%-12s %-8s %-8s %d円\n",
               employee_names[i],
               departments[i],
               positions[i],
               salaries[i]);
    }
    
    /* 部署別集計 */
    printf("\n=== 部署別従業員数 ===\n");
    char unique_depts[4][MAX_LENGTH] = {"営業", "開発", "人事", "経理"};
    int dept_count;
    
    for (i = 0; i < 4; i++) {
        int count = 0;
        int j;
        
        for (j = 0; j < 3; j++) {
            if (strcmp(departments[j], unique_depts[i]) == 0) {
                count++;
            }
        }
        printf("%s: %d人\n", unique_depts[i], count);
    }
    
    return 0;
}

/*
学習ポイント:
1. 文字列の分割:
   - strtok()関数による分割
   - 元の文字列が変更されることに注意
   - 区切り文字の指定方法

2. 文字列変換:
   - toupper()/tolower()による大文字小文字変換
   - ctype.hライブラリの活用
   - 文字列全体の変換処理

3. 文字列ソート:
   - バブルソートアルゴリズムの実装
   - strcmp()による文字列比較
   - 配列要素の交換処理

4. 実用的な応用:
   - データベース的な処理
   - 集計・分析機能
   - 検索・フィルタリング

注意点:
- strtok()は元の文字列を変更するため注意
- 文字のキャストにはunsigned charを使用
- バッファサイズの管理
- NULL文字の適切な処理
*/
