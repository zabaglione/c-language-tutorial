/*
 * ファイル名: ex10_3_string_search.c
 * 演習10-3: 高度な文字列検索
 * 説明: 文字列配列から特定の文字列を検索する高度な機能
 * 規格: C90準拠
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_STRINGS 20
#define MAX_LENGTH 100

/* 完全一致検索 */
int exact_search(char strings[][MAX_LENGTH], int count, const char *target)
{
    int i;
    
    for (i = 0; i < count; i++) {
        if (strcmp(strings[i], target) == 0) {
            return i;  /* 見つかった位置 */
        }
    }
    
    return -1;  /* 見つからない */
}

/* 大文字小文字を区別しない検索 */
int case_insensitive_search(char strings[][MAX_LENGTH], int count, const char *target)
{
    int i, j;
    char str_lower[MAX_LENGTH];
    char target_lower[MAX_LENGTH];
    
    /* ターゲットを小文字に変換 */
    for (j = 0; target[j] != '\0' && j < MAX_LENGTH - 1; j++) {
        target_lower[j] = tolower((unsigned char)target[j]);
    }
    target_lower[j] = '\0';
    
    for (i = 0; i < count; i++) {
        /* 比較対象の文字列を小文字に変換 */
        for (j = 0; strings[i][j] != '\0' && j < MAX_LENGTH - 1; j++) {
            str_lower[j] = tolower((unsigned char)strings[i][j]);
        }
        str_lower[j] = '\0';
        
        if (strcmp(str_lower, target_lower) == 0) {
            return i;
        }
    }
    
    return -1;
}

/* 部分一致検索（すべての該当項目を表示） */
int partial_search(char strings[][MAX_LENGTH], int count, const char *partial, 
                   int results[], int max_results)
{
    int i;
    int found_count = 0;
    
    for (i = 0; i < count && found_count < max_results; i++) {
        if (strstr(strings[i], partial) != NULL) {
            results[found_count] = i;
            found_count++;
        }
    }
    
    return found_count;
}

/* 前方一致検索 */
int prefix_search(char strings[][MAX_LENGTH], int count, const char *prefix,
                  int results[], int max_results)
{
    int i;
    int found_count = 0;
    int prefix_len = strlen(prefix);
    
    for (i = 0; i < count && found_count < max_results; i++) {
        if (strncmp(strings[i], prefix, prefix_len) == 0) {
            results[found_count] = i;
            found_count++;
        }
    }
    
    return found_count;
}

/* 後方一致検索 */
int suffix_search(char strings[][MAX_LENGTH], int count, const char *suffix,
                  int results[], int max_results)
{
    int i;
    int found_count = 0;
    int suffix_len = strlen(suffix);
    
    for (i = 0; i < count && found_count < max_results; i++) {
        int str_len = strlen(strings[i]);
        
        if (str_len >= suffix_len) {
            if (strcmp(strings[i] + str_len - suffix_len, suffix) == 0) {
                results[found_count] = i;
                found_count++;
            }
        }
    }
    
    return found_count;
}

/* 正規表現風のワイルドカード検索（簡易版） */
int wildcard_search(const char *str, const char *pattern)
{
    const char *s = str;
    const char *p = pattern;
    
    while (*p != '\0') {
        if (*p == '*') {
            /* ワイルドカード：0文字以上の任意の文字 */
            p++; /* '*'をスキップ */
            
            if (*p == '\0') {
                return 1; /* パターンの最後が'*'なら一致 */
            }
            
            /* 次の文字が一致する位置を探す */
            while (*s != '\0') {
                if (wildcard_search(s, p)) {
                    return 1;
                }
                s++;
            }
            return 0;
        } else if (*p == '?') {
            /* 任意の1文字 */
            if (*s == '\0') {
                return 0; /* 文字列が足りない */
            }
            s++;
            p++;
        } else {
            /* 通常文字 */
            if (*s != *p) {
                return 0;
            }
            s++;
            p++;
        }
    }
    
    return (*s == '\0'); /* 両方とも終端に達していれば一致 */
}

/* ワイルドカード検索（配列用） */
int wildcard_search_array(char strings[][MAX_LENGTH], int count, const char *pattern,
                         int results[], int max_results)
{
    int i;
    int found_count = 0;
    
    for (i = 0; i < count && found_count < max_results; i++) {
        if (wildcard_search(strings[i], pattern)) {
            results[found_count] = i;
            found_count++;
        }
    }
    
    return found_count;
}

/* 検索結果の表示 */
void display_search_results(char strings[][MAX_LENGTH], int results[], int count,
                           const char *search_type, const char *query)
{
    int i;
    
    printf("\n=== %s検索結果: \"%s\" ===\n", search_type, query);
    
    if (count == 0) {
        printf("該当する項目はありません。\n");
        return;
    }
    
    printf("%d件が見つかりました:\n", count);
    for (i = 0; i < count; i++) {
        printf("  %d. [%d] %s\n", i + 1, results[i] + 1, strings[results[i]]);
    }
}

/* 文字列の統計情報を表示 */
void display_statistics(char strings[][MAX_LENGTH], int count, const char *query)
{
    int i;
    int total_length = 0;
    int min_length = MAX_LENGTH;
    int max_length = 0;
    int query_count = 0;
    
    printf("\n=== 統計情報 ===\n");
    
    for (i = 0; i < count; i++) {
        int len = strlen(strings[i]);
        total_length += len;
        
        if (len < min_length) min_length = len;
        if (len > max_length) max_length = len;
        
        if (strstr(strings[i], query) != NULL) {
            query_count++;
        }
    }
    
    printf("総項目数: %d\n", count);
    printf("平均文字数: %.1f\n", (double)total_length / count);
    printf("最短文字数: %d\n", min_length);
    printf("最長文字数: %d\n", max_length);
    printf("\"%s\"を含む項目数: %d (%.1f%%)\n", 
           query, query_count, (double)query_count * 100 / count);
}

int main(void)
{
    char data[MAX_STRINGS][MAX_LENGTH] = {
        "Apple", "Banana", "Cherry", "Date", "Elderberry",
        "Fig", "Grape", "apple", "BANANA", "cherry pie",
        "Apple juice", "grape fruit", "Date palm", "Elder tree",
        "Fig leaf", "Cherry blossom", "Banana split", "Apple pie",
        "Grape wine", "Date sugar"
    };
    int data_count = 20;
    int results[MAX_STRINGS];
    int found_count;
    int exact_index;
    
    printf("===== 高度な文字列検索システム =====\n");
    
    /* データ一覧の表示 */
    printf("\n=== データ一覧 ===\n");
    {
        int i;
        for (i = 0; i < data_count; i++) {
            printf("%2d. %s\n", i + 1, data[i]);
        }
    }
    
    /* 1. 完全一致検索 */
    printf("\n1. 完全一致検索:\n");
    exact_index = exact_search(data, data_count, "Apple");
    if (exact_index != -1) {
        printf("\"Apple\" は %d番目にあります: %s\n", 
               exact_index + 1, data[exact_index]);
    }
    
    exact_index = exact_search(data, data_count, "apple");
    if (exact_index != -1) {
        printf("\"apple\" は %d番目にあります: %s\n", 
               exact_index + 1, data[exact_index]);
    }
    
    /* 2. 大文字小文字を区別しない検索 */
    printf("\n2. 大文字小文字を区別しない検索:\n");
    exact_index = case_insensitive_search(data, data_count, "APPLE");
    if (exact_index != -1) {
        printf("\"APPLE\"（大小文字無視）は %d番目にあります: %s\n", 
               exact_index + 1, data[exact_index]);
    }
    
    /* 3. 部分一致検索 */
    found_count = partial_search(data, data_count, "Apple", results, MAX_STRINGS);
    display_search_results(data, results, found_count, "部分一致", "Apple");
    
    /* 4. 前方一致検索 */
    found_count = prefix_search(data, data_count, "Apple", results, MAX_STRINGS);
    display_search_results(data, results, found_count, "前方一致", "Apple");
    
    /* 5. 後方一致検索 */
    found_count = suffix_search(data, data_count, "pie", results, MAX_STRINGS);
    display_search_results(data, results, found_count, "後方一致", "pie");
    
    /* 6. ワイルドカード検索 */
    printf("\n=== ワイルドカード検索のテスト ===\n");
    
    /* *ple パターン */
    found_count = wildcard_search_array(data, data_count, "*ple", results, MAX_STRINGS);
    display_search_results(data, results, found_count, "ワイルドカード", "*ple");
    
    /* ?ate パターン */
    found_count = wildcard_search_array(data, data_count, "?ate", results, MAX_STRINGS);
    display_search_results(data, results, found_count, "ワイルドカード", "?ate");
    
    /* *e* パターン */
    found_count = wildcard_search_array(data, data_count, "*e*", results, MAX_STRINGS);
    display_search_results(data, results, found_count, "ワイルドカード", "*e*");
    
    /* 7. 複合検索の例 */
    printf("\n=== 複合検索の例 ===\n");
    printf("「Apple」で始まる項目:\n");
    found_count = prefix_search(data, data_count, "Apple", results, MAX_STRINGS);
    {
        int i;
        for (i = 0; i < found_count; i++) {
            printf("  %s\n", data[results[i]]);
        }
    }
    
    /* 8. 統計情報 */
    display_statistics(data, data_count, "e");
    
    /* 9. 対話的検索の例 */
    printf("\n=== 対話的検索のデモ ===\n");
    {
        char queries[][20] = {"Banana", "tree", "ju*", "????"};
        int i;
        
        for (i = 0; i < 4; i++) {
            printf("\nクエリ: \"%s\"\n", queries[i]);
            
            /* ワイルドカード文字が含まれているかチェック */
            if (strchr(queries[i], '*') != NULL || strchr(queries[i], '?') != NULL) {
                found_count = wildcard_search_array(data, data_count, queries[i], 
                                                   results, MAX_STRINGS);
                printf("ワイルドカード検索: %d件\n", found_count);
            } else {
                found_count = partial_search(data, data_count, queries[i], 
                                           results, MAX_STRINGS);
                printf("部分一致検索: %d件\n", found_count);
            }
            
            if (found_count > 0 && found_count <= 3) {
                int j;
                for (j = 0; j < found_count; j++) {
                    printf("  - %s\n", data[results[j]]);
                }
            }
        }
    }
    
    return 0;
}

/*
学習ポイント:
1. 多様な検索アルゴリズム:
   - 完全一致・部分一致・前方一致・後方一致
   - 大文字小文字を区別しない検索
   - ワイルドカード検索

2. 効率的な実装:
   - 結果配列による複数結果の処理
   - 早期終了による最適化
   - メモリ効率的な検索

3. 実用的な機能:
   - 統計情報の表示
   - 検索結果の整理
   - エラーハンドリング

4. アルゴリズムの応用:
   - パターンマッチング
   - 文字列処理の最適化
   - 再帰的処理

5. ユーザビリティ:
   - 分かりやすい結果表示
   - 複数の検索オプション
   - 対話的な機能

注意点:
- バッファオーバーフローの防止
- パターンマッチングの効率性
- 文字コードの適切な処理
- エッジケースの考慮
*/
