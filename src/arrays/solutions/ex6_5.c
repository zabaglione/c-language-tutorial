/*
 * 演習 6-5: 簡易辞書プログラム（C90準拠版）
 * 
 * 英単語と日本語訳のペアを管理する辞書プログラム
 * 英和・和英検索、一覧表示、単語追加機能を実装
 */
#include <stdio.h>
#include <string.h>

#define MAX_WORDS 50
#define MAX_WORD_LENGTH 50

/* 辞書データ構造 */
char english_words[MAX_WORDS][MAX_WORD_LENGTH];
char japanese_words[MAX_WORDS][MAX_WORD_LENGTH];
int word_count = 0;

/* 初期データを設定する関数 */
void initialize_dictionary(void)
{
    strcpy(english_words[0], "apple");
    strcpy(japanese_words[0], "りんご");
    
    strcpy(english_words[1], "book");
    strcpy(japanese_words[1], "本");
    
    strcpy(english_words[2], "cat");
    strcpy(japanese_words[2], "猫");
    
    strcpy(english_words[3], "dog");
    strcpy(japanese_words[3], "犬");
    
    strcpy(english_words[4], "elephant");
    strcpy(japanese_words[4], "象");
    
    strcpy(english_words[5], "flower");
    strcpy(japanese_words[5], "花");
    
    strcpy(english_words[6], "guitar");
    strcpy(japanese_words[6], "ギター");
    
    strcpy(english_words[7], "house");
    strcpy(japanese_words[7], "家");
    
    strcpy(english_words[8], "internet");
    strcpy(japanese_words[8], "インターネット");
    
    strcpy(english_words[9], "japan");
    strcpy(japanese_words[9], "日本");
    
    word_count = 10;
}

/* 全単語を一覧表示する関数 */
void display_all_words(void)
{
    int i;
    
    printf("\n=== 辞書一覧 ===\n");
    printf("%-3s %-20s %-20s\n", "No.", "English", "Japanese");
    printf("--------------------------------------------\n");
    
    for (i = 0; i < word_count; i++) {
        printf("%-3d %-20s %-20s\n", i + 1, english_words[i], japanese_words[i]);
    }
    printf("\n");
}

/* 英単語で検索する関数（英和） */
void search_english_to_japanese(void)
{
    char search_word[MAX_WORD_LENGTH];
    int i;
    int found = 0;
    
    printf("英単語を入力してください: ");
    scanf("%s", search_word);
    
    for (i = 0; i < word_count; i++) {
        if (strcmp(english_words[i], search_word) == 0) {
            printf("結果: %s = %s\n\n", english_words[i], japanese_words[i]);
            found = 1;
            break;
        }
    }
    
    if (!found) {
        printf("「%s」は見つかりませんでした。\n\n", search_word);
    }
}

/* 日本語で検索する関数（和英） */
void search_japanese_to_english(void)
{
    char search_word[MAX_WORD_LENGTH];
    int i;
    int found = 0;
    
    printf("日本語を入力してください: ");
    scanf("%s", search_word);
    
    for (i = 0; i < word_count; i++) {
        if (strcmp(japanese_words[i], search_word) == 0) {
            printf("結果: %s = %s\n\n", japanese_words[i], english_words[i]);
            found = 1;
            break;
        }
    }
    
    if (!found) {
        printf("「%s」は見つかりませんでした。\n\n", search_word);
    }
}

/* 新しい単語を追加する関数 */
void add_new_word(void)
{
    char new_english[MAX_WORD_LENGTH];
    char new_japanese[MAX_WORD_LENGTH];
    int i;
    
    if (word_count >= MAX_WORDS) {
        printf("辞書が満杯です。これ以上追加できません。\n\n");
        return;
    }
    
    printf("新しい英単語を入力してください: ");
    scanf("%s", new_english);
    
    /* 重複チェック */
    for (i = 0; i < word_count; i++) {
        if (strcmp(english_words[i], new_english) == 0) {
            printf("その単語は既に登録されています。\n\n");
            return;
        }
    }
    
    printf("日本語訳を入力してください: ");
    scanf("%s", new_japanese);
    
    /* 新しい単語を追加 */
    strcpy(english_words[word_count], new_english);
    strcpy(japanese_words[word_count], new_japanese);
    word_count++;
    
    printf("「%s = %s」を追加しました。\n\n", new_english, new_japanese);
}

/* メニューを表示する関数 */
void display_menu(void)
{
    printf("=== 簡易辞書プログラム ===\n");
    printf("1. 英和検索（英語→日本語）\n");
    printf("2. 和英検索（日本語→英語）\n");
    printf("3. 辞書一覧表示\n");
    printf("4. 新しい単語を追加\n");
    printf("5. 終了\n");
    printf("選択してください (1-5): ");
}

int main(void)
{
    /* C90では先頭で全ての変数を宣言 */
    int choice;
    
    /* 初期データを設定 */
    initialize_dictionary();
    
    while (1) {
        display_menu();
        scanf("%d", &choice);
        printf("\n");
        
        switch (choice) {
            case 1:
                search_english_to_japanese();
                break;
            case 2:
                search_japanese_to_english();
                break;
            case 3:
                display_all_words();
                break;
            case 4:
                add_new_word();
                break;
            case 5:
                printf("辞書プログラムを終了します。\n");
                return 0;
            default:
                printf("無効な選択です。1-5の数字を入力してください。\n\n");
                break;
        }
    }
    
    return 0;
}