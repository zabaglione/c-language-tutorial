/*
 * 演習11-3: 文字列処理関数 - 解答例（C99版）
 * 
 * 文字列に対する各種処理を行う関数群を実装します。
 * C99の機能：//コメント、変数宣言位置の自由化、bool型、restrict修飾子
 */
#include <stdio.h>
#include <stdbool.h>

// 関数プロトタイプ
// 基本処理
void my_strcpy(char dest[], const char src[]);
void my_strcat(char dest[], const char src[]);
int my_strcmp(const char str1[], const char str2[]);

// 変換処理
void to_uppercase(char str[]);
void to_lowercase(char str[]);
void reverse_string(char str[]);

// 解析処理
int count_words(const char str[]);
bool is_palindrome(const char str[]);  // C99: bool型
int count_vowels(const char str[]);

// 追加関数（C99版）
void trim_spaces(char str[]);
bool starts_with(const char str[], const char prefix[]);
bool ends_with(const char str[], const char suffix[]);

// ヘルパー関数
int my_strlen(const char str[]);
bool is_space(char c);
bool is_alpha(char c);
bool is_vowel(char c);

// 文字列の長さを計算する関数
int my_strlen(const char str[])
{
    int len = 0;
    
    while (str[len] != '\0')
    {
        len++;
    }
    
    return len;
}

// 文字列をコピーする関数（C99: restrict修飾子を使用可能）
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

// 文字列を連結する関数
void my_strcat(char dest[], const char src[])
{
    int dest_len = my_strlen(dest);
    
    for (int i = 0; src[i] != '\0'; i++)  // C99: forループ内で変数宣言
    {
        dest[dest_len + i] = src[i];
        dest[dest_len + i + 1] = '\0';
    }
}

// 文字列を比較する関数
int my_strcmp(const char str1[], const char str2[])
{
    for (int i = 0; ; i++)  // C99: forループ内で変数宣言
    {
        if (str1[i] != str2[i])
        {
            return (unsigned char)str1[i] - (unsigned char)str2[i];
        }
        if (str1[i] == '\0')
        {
            return 0;  // 両方とも終端に達した
        }
    }
}

// 文字列を大文字に変換する関数
void to_uppercase(char str[])
{
    for (int i = 0; str[i] != '\0'; i++)  // C99: forループ内で変数宣言
    {
        if (str[i] >= 'a' && str[i] <= 'z')
        {
            str[i] = str[i] - 'a' + 'A';
        }
    }
}

// 文字列を小文字に変換する関数
void to_lowercase(char str[])
{
    for (int i = 0; str[i] != '\0'; i++)  // C99: forループ内で変数宣言
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
        {
            str[i] = str[i] - 'A' + 'a';
        }
    }
}

// 文字列を逆順にする関数
void reverse_string(char str[])
{
    int len = my_strlen(str);
    
    for (int i = 0; i < len / 2; i++)  // C99: forループ内で変数宣言
    {
        char temp = str[i];  // C99: 使用箇所で変数宣言
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

// 文字列内の単語数を数える関数
int count_words(const char str[])
{
    int count = 0;
    bool in_word = false;  // C99: bool型
    
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (is_space(str[i]))
        {
            in_word = false;
        }
        else
        {
            if (!in_word)
            {
                count++;
                in_word = true;
            }
        }
    }
    
    return count;
}

// 文字列が回文かどうかを判定する関数
bool is_palindrome(const char str[])
{
    int len = my_strlen(str);
    int i = 0;
    int j = len - 1;
    
    while (i < j)
    {
        // 左側の非アルファベット文字をスキップ
        while (i < j && !is_alpha(str[i]))
        {
            i++;
        }
        
        // 右側の非アルファベット文字をスキップ
        while (i < j && !is_alpha(str[j]))
        {
            j--;
        }
        
        // 大文字小文字を無視して比較
        char left = str[i];
        char right = str[j];
        
        if (left >= 'A' && left <= 'Z')
        {
            left = left - 'A' + 'a';
        }
        if (right >= 'A' && right <= 'Z')
        {
            right = right - 'A' + 'a';
        }
        
        if (left != right)
        {
            return false;  // 回文ではない
        }
        
        i++;
        j--;
    }
    
    return true;  // 回文
}

// 文字列内の母音の数を数える関数
int count_vowels(const char str[])
{
    int count = 0;
    
    for (int i = 0; str[i] != '\0'; i++)  // C99: forループ内で変数宣言
    {
        if (is_vowel(str[i]))
        {
            count++;
        }
    }
    
    return count;
}

// 文字列の前後の空白を削除する関数（C99追加）
void trim_spaces(char str[])
{
    int len = my_strlen(str);
    int start = 0;
    int end = len - 1;
    
    // 先頭の空白をスキップ
    while (start < len && is_space(str[start]))
    {
        start++;
    }
    
    // 末尾の空白をスキップ
    while (end > start && is_space(str[end]))
    {
        end--;
    }
    
    // 結果を前に詰める
    int j = 0;
    for (int i = start; i <= end; i++)
    {
        str[j++] = str[i];
    }
    str[j] = '\0';
}

// 文字列が指定したプレフィックスで始まるかチェック（C99追加）
bool starts_with(const char str[], const char prefix[])
{
    for (int i = 0; prefix[i] != '\0'; i++)
    {
        if (str[i] != prefix[i])
        {
            return false;
        }
    }
    return true;
}

// 文字列が指定したサフィックスで終わるかチェック（C99追加）
bool ends_with(const char str[], const char suffix[])
{
    int str_len = my_strlen(str);
    int suffix_len = my_strlen(suffix);
    
    if (suffix_len > str_len)
    {
        return false;
    }
    
    for (int i = 0; i < suffix_len; i++)
    {
        if (str[str_len - suffix_len + i] != suffix[i])
        {
            return false;
        }
    }
    
    return true;
}

// 文字が空白かどうかを判定するヘルパー関数
inline bool is_space(char c)  // C99: inline関数
{
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

// 文字がアルファベットかどうかを判定するヘルパー関数
inline bool is_alpha(char c)  // C99: inline関数
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

// 文字が母音かどうかを判定するヘルパー関数
inline bool is_vowel(char c)  // C99: inline関数
{
    char lower = c;
    
    if (c >= 'A' && c <= 'Z')
    {
        lower = c - 'A' + 'a';
    }
    
    return lower == 'a' || lower == 'e' || lower == 'i' || 
           lower == 'o' || lower == 'u';
}

// メイン関数 - テスト用
int main(void)
{
    printf("=== 文字列処理関数のテスト（C99版） ===\n\n");
    
    // 基本処理のテスト
    printf("=== 基本処理 ===\n");
    char str1[100] = "Hello, World!";
    char str2[100] = "C Programming";
    char str3[100] = "";
    
    printf("str1: \"%s\" (長さ: %d)\n", str1, my_strlen(str1));
    printf("str2: \"%s\" (長さ: %d)\n", str2, my_strlen(str2));
    
    // strcpyのテスト
    my_strcpy(str3, str1);
    printf("\nstrcpy(str3, str1)後: \"%s\"\n", str3);
    
    // strcatのテスト
    char buffer[200];
    my_strcpy(buffer, str1);
    my_strcat(buffer, " ");
    my_strcat(buffer, str2);
    printf("strcat結果: \"%s\"\n", buffer);
    
    // strcmpのテスト
    printf("\nstrcmp結果:\n");
    printf("  str1 vs str2: %d\n", my_strcmp(str1, str2));
    printf("  str1 vs str1: %d\n", my_strcmp(str1, str1));
    printf("  \"ABC\" vs \"ABD\": %d\n", my_strcmp("ABC", "ABD"));
    printf("\n");
    
    // 変換処理のテスト
    printf("=== 変換処理 ===\n");
    char test_str[100] = "Hello World 123!";
    printf("元の文字列: \"%s\"\n", test_str);
    
    to_uppercase(test_str);
    printf("大文字変換: \"%s\"\n", test_str);
    
    to_lowercase(test_str);
    printf("小文字変換: \"%s\"\n", test_str);
    
    reverse_string(test_str);
    printf("逆順: \"%s\"\n", test_str);
    printf("\n");
    
    // 解析処理のテスト
    printf("=== 解析処理 ===\n");
    
    // 単語数カウント
    const char* sentences[] = {  // C99: 配列初期化の改善
        "The quick brown fox jumps over the lazy dog",
        "  One   two    three  ",
        "",
        "Hello"
    };
    
    for (int i = 0; i < 4; i++)
    {
        printf("\"%s\"\n  → 単語数: %d\n", sentences[i], count_words(sentences[i]));
    }
    printf("\n");
    
    // 回文判定
    printf("回文判定:\n");
    const char* palindrome_tests[] = {
        "A man a plan a canal Panama",
        "race car",
        "hello world",
        "Was it a car or a cat I saw"
    };
    
    for (int i = 0; i < 4; i++)
    {
        printf("  \"%s\": %s\n", 
               palindrome_tests[i], 
               is_palindrome(palindrome_tests[i]) ? "回文" : "回文ではない");
    }
    printf("\n");
    
    // 母音カウント
    printf("母音の数:\n");
    printf("  \"%s\": %d個\n", str1, count_vowels(str1));
    printf("  \"%s\": %d個\n", str2, count_vowels(str2));
    printf("  \"AEIOU aeiou\": %d個\n", count_vowels("AEIOU aeiou"));
    printf("\n");
    
    // C99追加機能のテスト
    printf("=== C99追加機能 ===\n");
    
    // trim_spacesのテスト
    char trim_test[] = "   Hello World   ";
    printf("トリム前: \"%s\"\n", trim_test);
    trim_spaces(trim_test);
    printf("トリム後: \"%s\"\n", trim_test);
    
    // starts_with/ends_withのテスト
    const char* filename = "document.txt";
    printf("\n\"%s\":\n", filename);
    printf("  \"doc\"で始まる?: %s\n", starts_with(filename, "doc") ? "はい" : "いいえ");
    printf("  \"ment\"で始まる?: %s\n", starts_with(filename, "ment") ? "はい" : "いいえ");
    printf("  \".txt\"で終わる?: %s\n", ends_with(filename, ".txt") ? "はい" : "いいえ");
    printf("  \".pdf\"で終わる?: %s\n", ends_with(filename, ".pdf") ? "はい" : "いいえ");
    
    return 0;
}