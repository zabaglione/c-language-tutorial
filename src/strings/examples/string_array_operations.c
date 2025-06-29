/*
 * 文字列配列の実践例
 * ファイル名: string_array_operations.c
 * 説明: 二次元文字配列と文字列ポインタ配列の使い分けを学習
 */

#include <stdio.h>
#include <string.h>

#define MAX_STRINGS 5
#define MAX_LENGTH 20

int main(void)
{
    /* 二次元文字配列での文字列配列 */
    printf("=== 二次元文字配列による文字列配列 ===\n");
    char languages[MAX_STRINGS][MAX_LENGTH];
    int count = 0;
    int i;
    
    /* 文字列配列への代入 */
    strcpy(languages[count++], "C");
    strcpy(languages[count++], "Python");
    strcpy(languages[count++], "Java");
    strcpy(languages[count++], "JavaScript");
    strcpy(languages[count++], "C++");
    
    /* 表示 */
    printf("プログラミング言語一覧:\n");
    for (i = 0; i < count; i++) {
        printf("%d. %s\n", i + 1, languages[i]);
    }
    
    /* 文字列の変更 */
    strcpy(languages[0], "C言語");
    printf("\n変更後の1番目: %s\n", languages[0]);
    
    /* 文字列ポインタ配列での文字列配列 */
    printf("\n=== 文字列ポインタ配列 ===\n");
    char *fruits[] = {
        "Apple",
        "Banana", 
        "Cherry",
        "Date",
        "Elderberry"
    };
    int fruit_count = sizeof(fruits) / sizeof(fruits[0]);
    
    /* 表示 */
    printf("果物一覧:\n");
    for (i = 0; i < fruit_count; i++) {
        printf("%d. %s (長さ: %lu)\n", i + 1, fruits[i], 
               (unsigned long)strlen(fruits[i]));
    }
    
    /* ポインタの変更（文字列リテラルの置き換え） */
    fruits[0] = "リンゴ";
    printf("\n変更後の1番目: %s\n", fruits[0]);
    
    /* 文字列配列の初期化と動的変更 */
    printf("\n=== 動的に変更可能な文字列配列 ===\n");
    char menu_items[4][MAX_LENGTH];
    char *categories[] = {"前菜", "メイン", "デザート", "飲み物"};
    int item_count = 0;
    
    /* メニュー項目の追加 */
    strcpy(menu_items[item_count++], "サラダ");
    strcpy(menu_items[item_count++], "ステーキ");
    strcpy(menu_items[item_count++], "アイスクリーム");
    strcpy(menu_items[item_count++], "コーヒー");
    
    /* カテゴリ別表示 */
    printf("=== レストランメニュー ===\n");
    for (i = 0; i < item_count && i < 4; i++) {
        printf("[%s] %s\n", categories[i], menu_items[i]);
    }
    
    /* 項目の変更 */
    strcpy(menu_items[1], "ハンバーグ");
    printf("\nメイン料理を変更: %s\n", menu_items[1]);
    
    /* メモリ使用量の比較 */
    printf("\n=== メモリ使用量比較 ===\n");
    char matrix_strings[5][10] = {
        "Cat", "Dog", "Bird", "Fish", "Rabbit"
    };
    
    char *pointer_strings[] = {
        "Cat", "Dog", "Bird", "Fish", "Rabbit"
    };
    
    printf("二次元文字配列: %lu バイト\n", 
           (unsigned long)sizeof(matrix_strings));
    printf("文字列ポインタ配列: %lu バイト\n", 
           (unsigned long)sizeof(pointer_strings));
    
    printf("\n=== 実際の文字列長 ===\n");
    int total_chars = 0;
    for (i = 0; i < 5; i++) {
        int len = strlen(matrix_strings[i]);
        printf("%s: %d文字\n", matrix_strings[i], len);
        total_chars += len;
    }
    printf("総文字数: %d文字\n", total_chars);
    printf("未使用領域: %lu バイト\n", 
           sizeof(matrix_strings) - total_chars - 5);
    
    return 0;
}

/*
学習ポイント:
1. 二次元文字配列:
   - 固定サイズのメモリ確保
   - 文字列の変更が可能
   - メモリ使用効率は低い場合がある
   
2. 文字列ポインタ配列:
   - ポインタのみを格納
   - 文字列リテラルは変更不可
   - メモリ使用効率が良い
   
3. 使い分けの基準:
   - 文字列を変更する必要がある: 二次元配列
   - 文字列が固定: ポインタ配列
   - メモリ効率を重視: ポインタ配列
   
4. 実用的な応用:
   - メニュー管理システム
   - 設定項目の管理
   - データの分類・整理

注意点:
- 文字列リテラルの変更は未定義動作
- バッファサイズの確認
- 配列の境界チェック
*/
