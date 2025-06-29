/*
 * 文字列操作の基本例
 * ファイル名: string_basic.c
 * 説明: 標準ライブラリの文字列操作関数の使用方法を学習
 */

#include <stdio.h>
#include <string.h>

int main(void)
{
    /* 文字列の表現方法 */
    char str1[] = {'H', 'e', 'l', 'l', 'o', '\0'};
    char str2[] = "Hello";
    char str3[10] = "Hello";
    char *str4 = "Hello";
    
    printf("=== 文字列の表現方法 ===\n");
    printf("str1: %s\n", str1);
    printf("str2: %s\n", str2);
    printf("str3: %s\n", str3);
    printf("str4: %s\n", str4);
    
    /* 文字列の長さとサイズ */
    printf("\n=== 文字列の長さとサイズ ===\n");
    printf("文字列: \"%s\"\n", str2);
    printf("strlen(str2): %lu文字\n", (unsigned long)strlen(str2));
    printf("sizeof(str2): %lu バイト\n", (unsigned long)sizeof(str2));
    
    /* strcpy() - 文字列のコピー */
    printf("\n=== 文字列のコピー ===\n");
    char source[] = "Hello, World!";
    char destination[50];
    
    strcpy(destination, source);
    printf("destination: %s\n", destination);
    
    /* 部分的なコピー */
    strncpy(destination, source, 5);
    destination[5] = '\0';  /* null終端を明示的に追加 */
    printf("partial copy: %s\n", destination);  /* "Hello" */
    
    /* strcat() - 文字列の連結 */
    printf("\n=== 文字列の連結 ===\n");
    char str_a[50] = "Hello";
    char str_b[] = ", World!";
    char str_c[] = " How are you?";
    
    strcat(str_a, str_b);
    printf("After strcat: %s\n", str_a);  /* "Hello, World!" */
    
    /* 部分的な連結 */
    strncat(str_a, str_c, 4);
    printf("After strncat: %s\n", str_a); /* "Hello, World! How" */
    
    /* strcmp() - 文字列の比較 */
    printf("\n=== 文字列の比較 ===\n");
    char apple[] = "Apple";
    char banana[] = "Banana";
    char apple2[] = "Apple";
    int result;
    
    result = strcmp(apple, banana);
    if (result < 0) {
        printf("\"%s\" < \"%s\"\n", apple, banana);
    } else if (result > 0) {
        printf("\"%s\" > \"%s\"\n", apple, banana);
    } else {
        printf("\"%s\" == \"%s\"\n", apple, banana);
    }
    
    /* 等価性の確認 */
    if (strcmp(apple, apple2) == 0) {
        printf("\"%s\" と \"%s\" は同じです\n", apple, apple2);
    }
    
    /* 部分比較 */
    if (strncmp(apple, banana, 1) != 0) {
        printf("最初の文字が異なります\n");
    }
    
    /* 文字列検索関数 */
    printf("\n=== 文字列検索関数 ===\n");
    char text[] = "Hello, World! Welcome to C programming.";
    char *found;
    
    /* 文字の検索 */
    found = strchr(text, 'W');
    if (found != NULL) {
        printf("'W' found at position: %ld\n", found - text);
    }
    
    /* 文字列の検索 */
    found = strstr(text, "World");
    if (found != NULL) {
        printf("\"World\" found at position: %ld\n", found - text);
        printf("Found: %s\n", found);
    }
    
    /* 最後の文字を検索 */
    found = strrchr(text, 'o');
    if (found != NULL) {
        printf("Last 'o' at position: %ld\n", found - text);
    }
    
    return 0;
}

/*
学習ポイント:
1. 文字列の表現方法:
   - 文字配列による初期化
   - 文字列リテラルによる初期化
   - ポインタによる文字列参照

2. 標準ライブラリ関数:
   - strlen(): 文字列の長さを取得
   - strcpy()/strncpy(): 文字列のコピー
   - strcat()/strncat(): 文字列の連結
   - strcmp()/strncmp(): 文字列の比較

3. 文字列検索:
   - strchr(): 文字の検索
   - strrchr(): 文字の後方検索
   - strstr(): 部分文字列の検索

注意点:
- strncpy()使用時はnull終端文字の確認が必要
- バッファオーバーフローの防止
- NULLポインタのチェック
*/

