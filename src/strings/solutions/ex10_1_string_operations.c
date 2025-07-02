/*
 * ファイル名: ex10_1_string_operations.c
 * 演習10-1: 基本的な文字列操作
 * 説明: 標準ライブラリを使わずに文字列操作関数を実装
 * 規格: C90準拠
 */

#include <stdio.h>
#include <stddef.h>

/* 文字列の長さを計算する関数 */
int my_strlen(const char str[])
{
    int length = 0;
    
    if (str == NULL) {
        return 0;
    }
    
    while (str[length] != '\0') {
        length++;
    }
    
    return length;
}

/* 文字列をコピーする関数 */
void my_strcpy(char dest[], const char src[])
{
    int i = 0;
    
    if (dest == NULL || src == NULL) {
        return;
    }
    
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0'; /* 終端文字をコピー */
}

/* 文字列を比較する関数 */
int my_strcmp(const char str1[], const char str2[])
{
    int i = 0;
    
    if (str1 == NULL && str2 == NULL) {
        return 0;
    }
    if (str1 == NULL) {
        return -1;
    }
    if (str2 == NULL) {
        return 1;
    }
    
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] < str2[i]) {
            return -1;
        } else if (str1[i] > str2[i]) {
            return 1;
        }
        i++;
    }
    
    /* どちらかが終了した場合 */
    if (str1[i] == '\0' && str2[i] == '\0') {
        return 0;  /* 等しい */
    } else if (str1[i] == '\0') {
        return -1; /* str1が短い */
    } else {
        return 1;  /* str2が短い */
    }
}

/* 文字列を連結する関数 */
void my_strcat(char dest[], const char src[])
{
    int dest_len = 0;
    int i = 0;
    
    if (dest == NULL || src == NULL) {
        return;
    }
    
    /* 連結先の終端文字を見つける */
    while (dest[dest_len] != '\0') {
        dest_len++;
    }
    
    /* 連結元をコピー */
    while (src[i] != '\0') {
        dest[dest_len + i] = src[i];
        i++;
    }
    
    /* 終端文字を追加 */
    dest[dest_len + i] = '\0';
}

/* 文字列内で指定した文字を検索する関数 */
char *my_strchr(const char str[], int ch)
{
    int i = 0;
    
    if (str == NULL) {
        return NULL;
    }
    
    while (str[i] != '\0') {
        if (str[i] == ch) {
            return (char *)&str[i]; /* 見つかった位置を返す */
        }
        i++;
    }
    
    /* 終端文字を検索する場合 */
    if (ch == '\0') {
        return (char *)&str[i];
    }
    
    return NULL; /* 見つからなかった */
}

/* 文字列内で指定した文字を最後から検索する関数 */
char *my_strrchr(const char str[], int ch)
{
    int i;
    int length;
    
    if (str == NULL) {
        return NULL;
    }
    
    length = my_strlen(str);
    
    /* 後ろから検索 */
    for (i = length; i >= 0; i--) {
        if (str[i] == ch) {
            return (char *)&str[i];
        }
    }
    
    return NULL; /* 見つからなかった */
}

/* 文字列内の特定文字をカウントする関数 */
int count_char(const char str[], char ch)
{
    int count = 0;
    int i = 0;
    
    if (str == NULL) {
        return 0;
    }
    
    while (str[i] != '\0') {
        if (str[i] == ch) {
            count++;
        }
        i++;
    }
    
    return count;
}

/* テスト関数 */
void test_string_functions(void)
{
    char buffer[100];
    char *result;
    
    printf("=== 自作文字列関数のテスト ===\n");
    
    /* my_strlen のテスト */
    printf("\n1. my_strlen のテスト:\n");
    printf("my_strlen(\"Hello\"): %d\n", my_strlen("Hello"));
    printf("my_strlen(\"\"): %d\n", my_strlen(""));
    printf("my_strlen(\"Hello World\"): %d\n", my_strlen("Hello World"));
    
    /* my_strcpy のテスト */
    printf("\n2. my_strcpy のテスト:\n");
    my_strcpy(buffer, "Hello");
    printf("コピー結果: \"%s\"\n", buffer);
    
    /* my_strcmp のテスト */
    printf("\n3. my_strcmp のテスト:\n");
    printf("my_strcmp(\"apple\", \"apple\"): %d\n", my_strcmp("apple", "apple"));
    printf("my_strcmp(\"apple\", \"banana\"): %d\n", my_strcmp("apple", "banana"));
    printf("my_strcmp(\"banana\", \"apple\"): %d\n", my_strcmp("banana", "apple"));
    
    /* my_strcat のテスト */
    printf("\n4. my_strcat のテスト:\n");
    my_strcpy(buffer, "Hello");
    my_strcat(buffer, " World");
    printf("連結結果: \"%s\"\n", buffer);
    
    /* my_strchr のテスト */
    printf("\n5. my_strchr のテスト:\n");
    result = my_strchr("Hello World", 'W');
    if (result != NULL) {
        printf("'W' found at position: %ld\n", result - "Hello World");
    }
    
    result = my_strchr("Hello World", 'x');
    if (result == NULL) {
        printf("'x' not found\n");
    }
    
    /* my_strrchr のテスト */
    printf("\n6. my_strrchr のテスト:\n");
    result = my_strrchr("Hello World", 'l');
    if (result != NULL) {
        printf("Last 'l' found at position: %ld\n", result - "Hello World");
    }
    
    /* count_char のテスト */
    printf("\n7. count_char のテスト:\n");
    printf("count_char(\"Hello World\", 'l'): %d\n", count_char("Hello World", 'l'));
    printf("count_char(\"Hello World\", 'o'): %d\n", count_char("Hello World", 'o'));
    printf("count_char(\"Hello World\", 'x'): %d\n", count_char("Hello World", 'x'));
}

int main(void)
{
    printf("===== 基本的な文字列操作の実装 =====\n");
    
    test_string_functions();
    
    printf("\n=== 実用例 ===\n");
    
    /* 実用例: 文字列の解析 */
    char text[] = "C programming is fun and challenging!";
    printf("文字列: \"%s\"\n", text);
    printf("長さ: %d文字\n", my_strlen(text));
    printf("'n'の数: %d個\n", count_char(text, 'n'));
    printf("スペースの数: %d個\n", count_char(text, ' '));
    
    /* 'a'の最初と最後の位置 */
    char *first_a = my_strchr(text, 'a');
    char *last_a = my_strrchr(text, 'a');
    
    if (first_a != NULL) {
        printf("最初の'a'の位置: %ld\n", first_a - text);
    }
    if (last_a != NULL) {
        printf("最後の'a'の位置: %ld\n", last_a - text);
    }
    
    /* 文字列の組み立て */
    char result[200] = "";
    my_strcpy(result, "Hello");
    my_strcat(result, ", ");
    my_strcat(result, "World");
    my_strcat(result, "!");
    printf("\n組み立てた文字列: \"%s\"\n", result);
    
    return 0;
}

/*
学習ポイント:
1. 標準ライブラリの再実装:
   - 関数の内部動作の理解
   - ポインタ操作の練習
   - エッジケースの処理

2. エラーハンドリング:
   - NULLポインタのチェック
   - 境界条件の処理
   - 適切な戻り値の設定

3. メモリ安全性:
   - バッファオーバーフローの防止
   - 終端文字の適切な処理
   - ポインタの有効性確認

4. 実用的な応用:
   - 文字列解析
   - テキスト処理
   - データ検索

注意点:
- ポインタ演算時の型安全性
- 文字列の不変性の維持
- 効率的なアルゴリズムの選択
*/
