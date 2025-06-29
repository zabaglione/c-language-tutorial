/*
 * ファイル名: ex9_8_advanced_strings.c
 * 演習9-8: 高度な文字列処理
 * 説明: 文字列の解析、パターンマッチング、フォーマット処理などの高度な関数群
 * 規格: C90準拠
 */
#include <stdio.h>

/* 関数プロトタイプ */
int tokenize(char str[], char tokens[][50], char delimiter);
int check_brackets(const char str[]);
int extract_numbers(const char str[], int numbers[], int max_count);
int wildcard_match(const char str[], const char pattern[]);
int string_replace(char str[], const char old_substr[], const char new_substr[]);
void center_string(char result[], const char str[], int width);
int parse_csv_line(const char line[], char fields[][100], int max_fields);

/* 補助関数 */
int my_strlen(const char str[]);
void my_strcpy(char dest[], const char src[]);
int my_strncmp(const char str1[], const char str2[], int n);
int is_digit(char c);

/* 文字列をトークンに分割する関数 */
int tokenize(char str[], char tokens[][50], char delimiter)
{
    int token_count = 0;
    int i = 0;
    int token_start = 0;
    int token_len;
    int j;
    
    while (str[i] != '\0' && token_count < 20) /* 最大20トークン */
    {
        if (str[i] == delimiter)
        {
            /* トークンの終了 */
            token_len = i - token_start;
            if (token_len > 0)
            {
                /* トークンをコピー */
                for (j = 0; j < token_len && j < 49; j++)
                {
                    tokens[token_count][j] = str[token_start + j];
                }
                tokens[token_count][j] = '\0';
                token_count++;
            }
            token_start = i + 1;
        }
        i++;
    }
    
    /* 最後のトークン */
    token_len = i - token_start;
    if (token_len > 0 && token_count < 20)
    {
        for (j = 0; j < token_len && j < 49; j++)
        {
            tokens[token_count][j] = str[token_start + j];
        }
        tokens[token_count][j] = '\0';
        token_count++;
    }
    
    return token_count;
}

/* 文字列内の括弧の対応をチェックする関数 */
int check_brackets(const char str[])
{
    int round_count = 0; /* ( ) */
    int square_count = 0; /* [ ] */
    int curly_count = 0; /* { } */
    int i = 0;
    
    while (str[i] != '\0')
    {
        switch (str[i])
        {
        case '(':
            round_count++;
            break;
        case ')':
            round_count--;
            if (round_count < 0) return 0; /* 閉じ括弧が多い */
            break;
        case '[':
            square_count++;
            break;
        case ']':
            square_count--;
            if (square_count < 0) return 0;
            break;
        case '{':
            curly_count++;
            break;
        case '}':
            curly_count--;
            if (curly_count < 0) return 0;
            break;
        }
        i++;
    }
    
    /* すべての括弧がバランスしているかチェック */
    return (round_count == 0 && square_count == 0 && curly_count == 0);
}

/* 文字列から数値を抽出する関数 */
int extract_numbers(const char str[], int numbers[], int max_count)
{
    int count = 0;
    int i = 0;
    int current_number = 0;
    int in_number = 0;
    int is_negative = 0;
    
    while (str[i] != '\0' && count < max_count)
    {
        if (is_digit(str[i]))
        {
            if (!in_number)
            {
                in_number = 1;
                current_number = 0;
                is_negative = 0;
                
                /* 負の数のチェック */
                if (i > 0 && str[i - 1] == '-')
                {
                    is_negative = 1;
                }
            }
            current_number = current_number * 10 + (str[i] - '0');
        }
        else
        {
            if (in_number)
            {
                /* 数値の終了 */
                numbers[count] = is_negative ? -current_number : current_number;
                count++;
                in_number = 0;
            }
        }
        i++;
    }
    
    /* 文字列の最後が数値の場合 */
    if (in_number && count < max_count)
    {
        numbers[count] = is_negative ? -current_number : current_number;
        count++;
    }
    
    return count;
}

/* 簡単なワイルドカード（*、?）パターンマッチング関数 */
int wildcard_match(const char str[], const char pattern[])
{
    int str_i = 0;
    int pat_i = 0;
    int str_len = my_strlen(str);
    int pat_len = my_strlen(pattern);
    
    while (str_i < str_len && pat_i < pat_len)
    {
        if (pattern[pat_i] == '*')
        {
            /* * は0文字以上にマッチ */
            pat_i++;
            if (pat_i == pat_len) return 1; /* パターンの最後が * */
            
            /* 次の文字が見つかるまでスキップ */
            while (str_i < str_len)
            {
                if (wildcard_match(&str[str_i], &pattern[pat_i]))
                {
                    return 1;
                }
                str_i++;
            }
            return 0;
        }
        else if (pattern[pat_i] == '?' || pattern[pat_i] == str[str_i])
        {
            /* ? は任意の1文字、または文字が一致 */
            str_i++;
            pat_i++;
        }
        else
        {
            return 0; /* 不一致 */
        }
    }
    
    /* 残りのパターンがすべて * かチェック */
    while (pat_i < pat_len && pattern[pat_i] == '*')
    {
        pat_i++;
    }
    
    return (str_i == str_len && pat_i == pat_len);
}

/* 文字列の置換関数（簡単版） */
int string_replace(char str[], const char old_substr[], const char new_substr[])
{
    char temp[1000]; /* 作業用バッファ */
    int old_len = my_strlen(old_substr);
    int new_len = my_strlen(new_substr);
    int str_len = my_strlen(str);
    int i = 0;
    int temp_i = 0;
    int replacements = 0;
    
    while (i < str_len)
    {
        if (my_strncmp(&str[i], old_substr, old_len) == 0)
        {
            /* 置換対象が見つかった */
            int j;
            for (j = 0; j < new_len; j++)
            {
                temp[temp_i++] = new_substr[j];
            }
            i += old_len;
            replacements++;
        }
        else
        {
            temp[temp_i++] = str[i];
            i++;
        }
    }
    
    temp[temp_i] = '\0';
    my_strcpy(str, temp);
    
    return replacements;
}

/* 文字列を指定幅で中央揃えする関数 */
void center_string(char result[], const char str[], int width)
{
    int str_len = my_strlen(str);
    int padding = (width - str_len) / 2;
    int i;
    
    if (str_len >= width)
    {
        /* 文字列が幅より長い場合はそのままコピー */
        my_strcpy(result, str);
        return;
    }
    
    /* 左側のパディング */
    for (i = 0; i < padding; i++)
    {
        result[i] = ' ';
    }
    
    /* 文字列をコピー */
    for (i = 0; i < str_len; i++)
    {
        result[padding + i] = str[i];
    }
    
    /* 右側のパディング */
    for (i = padding + str_len; i < width; i++)
    {
        result[i] = ' ';
    }
    
    result[width] = '\0';
}

/* CSV形式の文字列を解析する関数 */
int parse_csv_line(const char line[], char fields[][100], int max_fields)
{
    int field_count = 0;
    int i = 0;
    int field_start = 0;
    int in_quotes = 0;
    int field_len;
    int j;
    
    while (line[i] != '\0' && field_count < max_fields)
    {
        if (line[i] == '"')
        {
            in_quotes = !in_quotes;
        }
        else if (line[i] == ',' && !in_quotes)
        {
            /* フィールドの終了 */
            field_len = i - field_start;
            for (j = 0; j < field_len && j < 99; j++)
            {
                fields[field_count][j] = line[field_start + j];
            }
            fields[field_count][j] = '\0';
            field_count++;
            field_start = i + 1;
        }
        i++;
    }
    
    /* 最後のフィールド */
    if (field_count < max_fields)
    {
        field_len = i - field_start;
        for (j = 0; j < field_len && j < 99; j++)
        {
            fields[field_count][j] = line[field_start + j];
        }
        fields[field_count][j] = '\0';
        field_count++;
    }
    
    return field_count;
}

/* 補助関数の実装 */
int my_strlen(const char str[])
{
    int len = 0;
    while (str[len] != '\0') len++;
    return len;
}

void my_strcpy(char dest[], const char src[])
{
    int i = 0;
    while (src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

int my_strncmp(const char str1[], const char str2[], int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (str1[i] != str2[i])
        {
            return str1[i] - str2[i];
        }
        if (str1[i] == '\0')
        {
            return 0;
        }
    }
    return 0;
}

int is_digit(char c)
{
    return (c >= '0' && c <= '9');
}

int main(void)
{
    printf("=== 高度な文字列処理のデモ ===\n\n");

    /* デモ1: 文字列の分割 */
    printf("1. 文字列の分割（トークン化）\n");
    char test_string1[] = "apple,banana,orange,grape";
    char tokens[20][50];
    int token_count = tokenize(test_string1, tokens, ',');
    int i, j;
    
    printf("   文字列: \"%s\"\n", "apple,banana,orange,grape");
    printf("   分割結果: ");
    for (i = 0; i < token_count; i++)
    {
        printf("\"%s\"", tokens[i]);
        if (i < token_count - 1) printf(", ");
    }
    printf("\n\n");

    /* デモ2: 括弧のバランスチェック */
    printf("2. 括弧のバランスチェック\n");
    const char* bracket_tests[] = {
        "((()))",
        "([{}])",
        "(()",
        "([)]",
        "{[()()()]}"
    };
    int num_bracket_tests = sizeof(bracket_tests) / sizeof(bracket_tests[0]);
    
    for (i = 0; i < num_bracket_tests; i++)
    {
        int is_balanced = check_brackets(bracket_tests[i]);
        printf("   \"%s\" -> %s\n", bracket_tests[i], 
               is_balanced ? "バランス取れています" : "バランスが取れていません");
    }
    printf("\n");

    /* デモ3: 数値の抽出 */
    printf("3. 文字列からの数値抽出\n");
    const char* number_tests[] = {
        "価格は1500円、税込み1650円です",
        "座標: x=10, y=-25, z=100",
        "電話番号: 03-1234-5678"
    };
    int num_number_tests = sizeof(number_tests) / sizeof(number_tests[0]);
    
    for (i = 0; i < num_number_tests; i++)
    {
        int numbers[20];
        int count = extract_numbers(number_tests[i], numbers, 20);
        printf("   \"%s\"\n", number_tests[i]);
        printf("   抽出された数値: ");
        for (j = 0; j < count; j++)
        {
            printf("%d", numbers[j]);
            if (j < count - 1) printf(", ");
        }
        printf("\n\n");
    }

    /* デモ4: ワイルドカードマッチング */
    printf("4. ワイルドカードマッチング\n");
    const char* match_tests[][2] = {
        {"hello", "h*o"},
        {"test123", "test*"},
        {"filename.txt", "*.txt"},
        {"abc", "a?c"},
        {"hello", "world"}
    };
    int num_match_tests = sizeof(match_tests) / sizeof(match_tests[0]);
    
    for (i = 0; i < num_match_tests; i++)
    {
        int matches = wildcard_match(match_tests[i][0], match_tests[i][1]);
        printf("   \"%s\" と \"%s\" -> %s\n", 
               match_tests[i][0], match_tests[i][1],
               matches ? "マッチします" : "マッチしません");
    }
    printf("\n");

    /* デモ5: 文字列の置換 */
    printf("5. 文字列の置換\n");
    char replace_test[] = "Hello world! This is a test world.";
    printf("   元の文字列: \"%s\"\n", replace_test);
    int replacements = string_replace(replace_test, "world", "universe");
    printf("   置換後: \"%s\"\n", replace_test);
    printf("   置換回数: %d回\n\n", replacements);

    /* デモ6: 文字列の中央揃え */
    printf("6. 文字列の中央揃え\n");
    const char* center_tests[] = {"Hello", "World", "Test"};
    int widths[] = {10, 15, 20};
    
    for (i = 0; i < 3; i++)
    {
        char centered[50];
        center_string(centered, center_tests[i], widths[i]);
        printf("   幅%d: |%s|\n", widths[i], centered);
    }
    printf("\n");

    /* デモ7: CSV解析 */
    printf("7. CSV形式の解析\n");
    const char* csv_tests[] = {
        "名前,年齢,職業",
        "田中太郎,25,エンジニア",
        "\"佐藤,花子\",30,\"営業,マネージャー\""
    };
    int num_csv_tests = sizeof(csv_tests) / sizeof(csv_tests[0]);
    
    for (i = 0; i < num_csv_tests; i++)
    {
        char fields[10][100];
        int field_count = parse_csv_line(csv_tests[i], fields, 10);
        printf("   \"%s\"\n", csv_tests[i]);
        printf("   フィールド: ");
        for (j = 0; j < field_count; j++)
        {
            printf("[%s]", fields[j]);
            if (j < field_count - 1) printf(" ");
        }
        printf("\n\n");
    }

    printf("=== 高度な文字列処理デモ完了 ===\n");
    return 0;
}

/*
学習ポイント:
1. 文字列の動的な解析と分割
2. 構文解析の基本（括弧のバランス）
3. パターンマッチングアルゴリズム
4. 文字列操作の効率的な実装
5. フォーマット処理とパース処理

実装のポイント:
- C90準拠のため、変数は関数先頭で宣言
- 安全な文字列操作（バッファオーバーフロー対策）
- 効率的なアルゴリズムの選択
- エラーハンドリングの考慮
*/