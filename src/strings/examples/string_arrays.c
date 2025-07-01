/*
 * 文字列配列の使い方（C90準拠版）
 * 
 * このプログラムは、文字列配列の宣言、初期化、
 * 操作方法、およびchar配列とchar*配列の違いを示します。
 */
#include <stdio.h>
#include <string.h>

int main(void)
{
    /* C90では先頭で全ての変数を宣言 */
    int i;
    char str1[20];
    char str2[] = "World";
    char fruits[5][20] = {
        "Apple",
        "Banana",
        "Orange",
        "Grape",
        "Strawberry"
    };
    char *months[] = {
        "January", "February", "March", "April",
        "May", "June", "July", "August",
        "September", "October", "November", "December"
    };
    char cities1[3][20] = {"Tokyo", "New York", "London"};
    char *cities2[] = {"Tokyo", "New York", "London"};
    char *programming_languages[] = {
        "C", "C++", "Java", "Python", "JavaScript",
        "Ruby", "Go", "Rust", "Swift", "Kotlin"
    };
    int n_languages;
    char search_lang[20];
    int found = 0;
    char *words[] = {"cat", "elephant", "dog", "hippopotamus", "ant", "butterfly"};
    int n_words;
    int len;
    char *menu_items[] = {
        "1. ファイルを開く",
        "2. ファイルを保存",
        "3. 設定",
        "4. ヘルプ",
        "5. 終了"
    };
    int n_items;
    
    /* 1. char配列（文字配列）の基本 */
    printf("=== char配列（文字配列）===\n");
    
    strcpy(str1, "Hello");  /* C90では初期化後に代入 */
    
    printf("str1: %s（サイズ: %lu）\n", str1, sizeof(str1));
    printf("str2: %s（サイズ: %lu）\n", str2, sizeof(str2));
    
    /* 文字配列の変更 */
    str1[0] = 'h';  /* 最初の文字を小文字に */
    printf("変更後のstr1: %s\n\n", str1);
    
    /* 2. 文字列配列（2次元char配列）*/
    printf("=== 2次元char配列による文字列配列 ===\n");
    
    printf("果物リスト:\n");
    for (i = 0; i < 5; i++) {
        printf("%d: %s\n", i + 1, fruits[i]);
    }
    
    /* 文字列の変更 */
    strcpy(fruits[2], "Mango");  /* OrangeをMangoに変更 */
    printf("\n変更後（3番目をMangoに）:\n");
    for (i = 0; i < 5; i++) {
        printf("%d: %s\n", i + 1, fruits[i]);
    }
    printf("\n");
    
    /* 3. char*配列（ポインタ配列）*/
    printf("=== char*配列による文字列配列 ===\n");
    
    printf("月の名前:\n");
    for (i = 0; i < 12; i++) {
        printf("%2d月: %s\n", i + 1, months[i]);
    }
    printf("\n");
    
    /* 4. char配列とchar*配列の違い */
    printf("=== char配列とchar*配列の違い ===\n");
    
    printf("char配列のサイズ: %lu バイト\n", sizeof(cities1));
    printf("char*配列のサイズ: %lu バイト\n", sizeof(cities2));
    printf("（ポインタのサイズx要素数）\n\n");
    
    /* 5. 文字列の検索と操作 */
    printf("=== 文字列配列の検索 ===\n");
    
    n_languages = sizeof(programming_languages) / sizeof(programming_languages[0]);
    
    printf("検索する言語名を入力: ");
    scanf("%s", search_lang);
    
    found = 0;
    for (i = 0; i < n_languages; i++) {
        if (strcmp(programming_languages[i], search_lang) == 0) {
            printf("%s は %d 番目にあります\n", search_lang, i + 1);
            found = 1;
            break;
        }
    }
    
    if (!found) {
        printf("%s は見つかりませんでした\n", search_lang);
    }
    printf("\n");
    
    /* 6. 文字列の長さ順にソート（簡易版）*/
    printf("=== 文字列の長さ順表示 ===\n");
    
    n_words = sizeof(words) / sizeof(words[0]);
    
    printf("元の順序:\n");
    for (i = 0; i < n_words; i++) {
        printf("%s ", words[i]);
    }
    printf("\n");
    
    /* 長さ順に表示（実際の配列は変更しない） */
    printf("\n長さ順:\n");
    for (len = 1; len <= 20; len++) {
        for (i = 0; i < n_words; i++) {
            if ((int)strlen(words[i]) == len) { /* 型キャストで警告を回避 */
                printf("%s（%d文字） ", words[i], len);
            }
        }
    }
    printf("\n\n");
    
    /* 7. 動的な文字列配列の例 */
    printf("=== コマンドメニューシステム ===\n");
    
    n_items = sizeof(menu_items) / sizeof(menu_items[0]);
    
    printf("メニュー:\n");
    for (i = 0; i < n_items; i++) {
        printf("%s\n", menu_items[i]);
    }
    
    return 0;
}