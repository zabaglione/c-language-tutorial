/*
 * ファイル名: ex11_8_advanced_strings_c99.c
 * 演習11-8: 高度な文字列処理
 * 説明: 文字列の解析、パターンマッチング、フォーマット処理などの高度な関数群（C99版）
 * 規格: C99準拠
 */
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// 関数プロトタイプ
int tokenize(char str[], char tokens[][50], char delimiter);
bool check_brackets(const char str[]);
int extract_numbers(const char str[], int numbers[], int max_count);
bool wildcard_match(const char str[], const char pattern[]);
int string_replace(char str[], const char old_substr[], const char new_substr[]);
void center_string(char result[], const char str[], int width);
int parse_csv_line(const char line[], char fields[][100], int max_fields);

// 文字列をトークンに分割する関数（C99: for文内変数宣言）
int tokenize(char str[], char tokens[][50], char delimiter)
{
    int token_count = 0;
    int token_start = 0;
    
    for (int i = 0; str[i] != '\0' && token_count < 20; i++) {
        if (str[i] == delimiter) {
            // トークンの終了
            int token_len = i - token_start;
            if (token_len > 0) {
                // C99: 使用箇所で変数宣言
                for (int j = 0; j < token_len && j < 49; j++) {
                    tokens[token_count][j] = str[token_start + j];
                }
                tokens[token_count][token_len < 49 ? token_len : 49] = '\0';
                token_count++;
            }
            token_start = i + 1;
        }
    }
    
    // 最後のトークン
    int final_len = strlen(str) - token_start;
    if (final_len > 0 && token_count < 20) {
        strncpy(tokens[token_count], &str[token_start], 49);
        tokens[token_count][49] = '\0';
        token_count++;
    }
    
    return token_count;
}

// 文字列内の括弧の対応をチェックする関数（C99: bool型使用）
bool check_brackets(const char str[])
{
    int counts[3] = {0}; // [0]:(), [1]:[], [2]:{}
    
    for (int i = 0; str[i] != '\0'; i++) {
        switch (str[i]) {
            case '(': counts[0]++; break;
            case ')': if (--counts[0] < 0) return false; break;
            case '[': counts[1]++; break;
            case ']': if (--counts[1] < 0) return false; break;
            case '{': counts[2]++; break;
            case '}': if (--counts[2] < 0) return false; break;
        }
    }
    
    return (counts[0] == 0 && counts[1] == 0 && counts[2] == 0);
}

// 文字列から数値を抽出する関数
int extract_numbers(const char str[], int numbers[], int max_count)
{
    int count = 0;
    bool in_number = false;
    int current_number = 0;
    bool is_negative = false;
    
    for (int i = 0; str[i] != '\0' && count < max_count; i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            if (!in_number) {
                in_number = true;
                current_number = 0;
                is_negative = (i > 0 && str[i - 1] == '-');
            }
            current_number = current_number * 10 + (str[i] - '0');
        } else {
            if (in_number) {
                numbers[count++] = is_negative ? -current_number : current_number;
                in_number = false;
            }
        }
    }
    
    // 文字列の最後が数値の場合
    if (in_number && count < max_count) {
        numbers[count++] = is_negative ? -current_number : current_number;
    }
    
    return count;
}

// 簡単なワイルドカード（*、?）パターンマッチング関数（C99: bool型）
bool wildcard_match(const char str[], const char pattern[])
{
    int str_len = strlen(str);
    int pat_len = strlen(pattern);
    
    // C99: 可変長配列を使用したDPテーブル
    bool dp[str_len + 1][pat_len + 1];
    
    // 初期化
    for (int i = 0; i <= str_len; i++) {
        for (int j = 0; j <= pat_len; j++) {
            dp[i][j] = false;
        }
    }
    
    dp[0][0] = true;
    
    // パターンの*による初期化
    for (int j = 1; j <= pat_len; j++) {
        if (pattern[j-1] == '*') {
            dp[0][j] = dp[0][j-1];
        }
    }
    
    // DPテーブルの計算
    for (int i = 1; i <= str_len; i++) {
        for (int j = 1; j <= pat_len; j++) {
            if (pattern[j-1] == '*') {
                dp[i][j] = dp[i-1][j] || dp[i][j-1];
            } else if (pattern[j-1] == '?' || pattern[j-1] == str[i-1]) {
                dp[i][j] = dp[i-1][j-1];
            }
        }
    }
    
    return dp[str_len][pat_len];
}

// 文字列の置換関数（C99: 動的配列サイズ）
int string_replace(char str[], const char old_substr[], const char new_substr[])
{
    int str_len = strlen(str);
    int old_len = strlen(old_substr);
    int new_len = strlen(new_substr);
    
    // C99: 可変長配列
    char temp[str_len * 2 + 100]; // 十分なサイズを確保
    int temp_pos = 0;
    int replacements = 0;
    
    for (int i = 0; i < str_len; ) {
        if (strncmp(&str[i], old_substr, old_len) == 0) {
            // 置換対象が見つかった
            strcpy(&temp[temp_pos], new_substr);
            temp_pos += new_len;
            i += old_len;
            replacements++;
        } else {
            temp[temp_pos++] = str[i++];
        }
    }
    
    temp[temp_pos] = '\0';
    strcpy(str, temp);
    
    return replacements;
}

// 文字列を指定幅で中央揃えする関数
void center_string(char result[], const char str[], int width)
{
    int str_len = strlen(str);
    
    if (str_len >= width) {
        strcpy(result, str);
        return;
    }
    
    int padding = (width - str_len) / 2;
    
    // C99: 複合リテラル風の初期化
    memset(result, ' ', width);
    result[width] = '\0';
    
    // 文字列を中央に配置
    strncpy(&result[padding], str, str_len);
}

// CSV形式の文字列を解析する関数
int parse_csv_line(const char line[], char fields[][100], int max_fields)
{
    int field_count = 0;
    bool in_quotes = false;
    int field_start = 0;
    
    for (int i = 0; line[i] != '\0' && field_count < max_fields; i++) {
        if (line[i] == '"') {
            in_quotes = !in_quotes;
        } else if (line[i] == ',' && !in_quotes) {
            // フィールドの終了
            int field_len = i - field_start;
            strncpy(fields[field_count], &line[field_start], 
                   field_len < 99 ? field_len : 99);
            fields[field_count][field_len < 99 ? field_len : 99] = '\0';
            field_count++;
            field_start = i + 1;
        }
    }
    
    // 最後のフィールド
    if (field_count < max_fields) {
        int final_len = strlen(line) - field_start;
        strncpy(fields[field_count], &line[field_start], 
               final_len < 99 ? final_len : 99);
        fields[field_count][final_len < 99 ? final_len : 99] = '\0';
        field_count++;
    }
    
    return field_count;
}

int main(void)
{
    printf("=== 高度な文字列処理のデモ（C99版）===\n\n");

    // デモ1: 文字列の分割（C99: 配列初期化）
    printf("1. 文字列の分割（トークン化）\n");
    char test_string1[] = "apple,banana,orange,grape,kiwi";
    char tokens[20][50];
    int token_count = tokenize(test_string1, tokens, ',');
    
    printf("   文字列: \"%s\"\n", "apple,banana,orange,grape,kiwi");
    printf("   分割結果: ");
    for (int i = 0; i < token_count; i++) {
        printf("\"%s\"", tokens[i]);
        if (i < token_count - 1) printf(", ");
    }
    printf("\n\n");

    // デモ2: 括弧のバランスチェック（C99: 配列初期化と bool型）
    printf("2. 括弧のバランスチェック\n");
    const char* bracket_tests[] = {
        "((()))", "([{}])", "(()", "([)]", "{[()()()]}", "({[}])"
    };
    
    for (int i = 0; i < 6; i++) {
        bool is_balanced = check_brackets(bracket_tests[i]);
        printf("   \"%s\" -> %s\n", bracket_tests[i], 
               is_balanced ? "バランス取れています" : "バランスが取れていません");
    }
    printf("\n");

    // デモ3: 数値の抽出
    printf("3. 文字列からの数値抽出\n");
    const char* number_tests[] = {
        "価格は1500円、税込み1650円、送料500円です",
        "座標: x=10, y=-25, z=100, w=-5",
        "電話番号: 03-1234-5678, FAX: 03-9876-5432"
    };
    
    for (int i = 0; i < 3; i++) {
        int numbers[20];
        int count = extract_numbers(number_tests[i], numbers, 20);
        printf("   \"%s\"\n", number_tests[i]);
        printf("   抽出された数値: ");
        for (int j = 0; j < count; j++) {
            printf("%d", numbers[j]);
            if (j < count - 1) printf(", ");
        }
        printf("\n\n");
    }

    // デモ4: ワイルドカードマッチング（C99: 構造体配列）
    printf("4. ワイルドカードマッチング\n");
    struct { const char *str, *pattern; } match_tests[] = {
        {"hello", "h*o"}, {"test123", "test*"}, {"filename.txt", "*.txt"},
        {"abc", "a?c"}, {"hello", "world"}, {"pattern", "p*n"}
    };
    
    for (int i = 0; i < 6; i++) {
        bool matches = wildcard_match(match_tests[i].str, match_tests[i].pattern);
        printf("   \"%s\" と \"%s\" -> %s\n", 
               match_tests[i].str, match_tests[i].pattern,
               matches ? "マッチします" : "マッチしません");
    }
    printf("\n");

    // デモ5: 文字列の置換
    printf("5. 文字列の置換\n");
    char replace_test[] = "Hello world! This is a test world. Welcome to the world!";
    printf("   元の文字列: \"%s\"\n", replace_test);
    int replacements = string_replace(replace_test, "world", "universe");
    printf("   置換後: \"%s\"\n", replace_test);
    printf("   置換回数: %d回\n\n", replacements);

    // デモ6: 文字列の中央揃え
    printf("6. 文字列の中央揃え\n");
    const char* center_tests[] = {"Hello", "World", "C99", "Programming"};
    int widths[] = {15, 20, 10, 25};
    
    for (int i = 0; i < 4; i++) {
        char centered[50];
        center_string(centered, center_tests[i], widths[i]);
        printf("   幅%d: |%s|\n", widths[i], centered);
    }
    printf("\n");

    // デモ7: CSV解析
    printf("7. CSV形式の解析\n");
    const char* csv_tests[] = {
        "名前,年齢,職業,住所",
        "田中太郎,25,エンジニア,東京都",
        "\"佐藤,花子\",30,\"営業,マネージャー\",\"大阪府,大阪市\""
    };
    
    for (int i = 0; i < 3; i++) {
        char fields[10][100];
        int field_count = parse_csv_line(csv_tests[i], fields, 10);
        printf("   \"%s\"\n", csv_tests[i]);
        printf("   フィールド: ");
        for (int j = 0; j < field_count; j++) {
            printf("[%s]", fields[j]);
            if (j < field_count - 1) printf(" ");
        }
        printf("\n\n");
    }

    // C99追加デモ: 高度な文字列処理
    printf("=== C99機能を活用した高度な例 ===\n");
    
    // 複数パターンの一括マッチング
    printf("複数パターンマッチング:\n");
    const char* test_str = "document.pdf";
    const char* patterns[] = {"*.txt", "*.pdf", "*.doc", "doc*"};
    
    for (int i = 0; i < 4; i++) {
        printf("   \"%s\" vs \"%s\": %s\n", 
               test_str, patterns[i],
               wildcard_match(test_str, patterns[i]) ? "マッチ" : "不一致");
    }
    
    printf("\n=== C99高度な文字列処理デモ完了 ===\n");
    return 0;
}

/*
学習ポイント（C99追加機能）:
1. bool型を使ったより明確な戻り値
2. for文内での変数宣言による局所化
3. 可変長配列を活用した動的プログラミング
4. 構造体配列の初期化子による簡潔な記述
5. C99標準ライブラリ関数の活用

実装のポイント:
- C99準拠のため、変数を使用箇所で宣言
- bool型によるより読みやすいコード
- 可変長配列で効率的なメモリ使用
- 標準ライブラリとの組み合わせによる簡潔な実装
*/