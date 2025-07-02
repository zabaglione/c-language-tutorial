/*
 * 演習11-3: 文字列処理関数 - 解答例
 * 
 * 文字列に対する各種処理を行う関数群を実装します。
 */
#include <stdio.h>

/* 関数プロトタイプ */
/* 基本処理 */
void my_strcpy(char dest[], const char src[]);
void my_strcat(char dest[], const char src[]);
int my_strcmp(const char str1[], const char str2[]);

/* 変換処理 */
void to_uppercase(char str[]);
void to_lowercase(char str[]);
void reverse_string(char str[]);

/* 解析処理 */
int count_words(const char str[]);
int is_palindrome(const char str[]);
int count_vowels(const char str[]);

/* ヘルパー関数 */
int my_strlen(const char str[]);
int is_space(char c);
int is_alpha(char c);
int is_vowel(char c);

/* 文字列の長さを計算する関数 */
int my_strlen(const char str[])
{
    int len = 0;
    
    while (str[len] != '\0')
    {
        len++;
    }
    
    return len;
}

/* 文字列をコピーする関数 */
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

/* 文字列を連結する関数 */
void my_strcat(char dest[], const char src[])
{
    int dest_len = my_strlen(dest);
    int i = 0;
    
    while (src[i] != '\0')
    {
        dest[dest_len + i] = src[i];
        i++;
    }
    dest[dest_len + i] = '\0';
}

/* 文字列を比較する関数 */
int my_strcmp(const char str1[], const char str2[])
{
    int i = 0;
    
    while (str1[i] != '\0' && str2[i] != '\0')
    {
        if (str1[i] < str2[i])
        {
            return -1;
        }
        else if (str1[i] > str2[i])
        {
            return 1;
        }
        i++;
    }
    
    /* 片方の文字列が終了した場合 */
    if (str1[i] == '\0' && str2[i] == '\0')
    {
        return 0;  /* 同じ */
    }
    else if (str1[i] == '\0')
    {
        return -1;  /* str1が短い */
    }
    else
    {
        return 1;   /* str2が短い */
    }
}

/* 文字列を大文字に変換する関数 */
void to_uppercase(char str[])
{
    int i = 0;
    
    while (str[i] != '\0')
    {
        if (str[i] >= 'a' && str[i] <= 'z')
        {
            str[i] = str[i] - 'a' + 'A';
        }
        i++;
    }
}

/* 文字列を小文字に変換する関数 */
void to_lowercase(char str[])
{
    int i = 0;
    
    while (str[i] != '\0')
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
        {
            str[i] = str[i] - 'A' + 'a';
        }
        i++;
    }
}

/* 文字列を逆順にする関数 */
void reverse_string(char str[])
{
    int len = my_strlen(str);
    int i;
    char temp;
    
    for (i = 0; i < len / 2; i++)
    {
        temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

/* 文字列内の単語数を数える関数 */
int count_words(const char str[])
{
    int count = 0;
    int in_word = 0;
    int i = 0;
    
    while (str[i] != '\0')
    {
        if (is_space(str[i]))
        {
            in_word = 0;
        }
        else
        {
            if (!in_word)
            {
                count++;
                in_word = 1;
            }
        }
        i++;
    }
    
    return count;
}

/* 文字列が回文かどうかを判定する関数 */
int is_palindrome(const char str[])
{
    int len = my_strlen(str);
    int i, j;
    
    /* 空白を無視してチェック */
    i = 0;
    j = len - 1;
    
    while (i < j)
    {
        /* 左側の空白をスキップ */
        while (i < j && is_space(str[i]))
        {
            i++;
        }
        
        /* 右側の空白をスキップ */
        while (i < j && is_space(str[j]))
        {
            j--;
        }
        
        /* 大文字小文字を無視して比較 */
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
            return 0;  /* 回文ではない */
        }
        
        i++;
        j--;
    }
    
    return 1;  /* 回文 */
}

/* 文字列内の母音の数を数える関数 */
int count_vowels(const char str[])
{
    int count = 0;
    int i = 0;
    
    while (str[i] != '\0')
    {
        if (is_vowel(str[i]))
        {
            count++;
        }
        i++;
    }
    
    return count;
}

/* 文字が空白かどうかを判定するヘルパー関数 */
int is_space(char c)
{
    return c == ' ' || c == '\t' || c == '\n';
}

/* 文字がアルファベットかどうかを判定するヘルパー関数 */
int is_alpha(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

/* 文字が母音かどうかを判定するヘルパー関数 */
int is_vowel(char c)
{
    char lower = c;
    
    if (c >= 'A' && c <= 'Z')
    {
        lower = c - 'A' + 'a';
    }
    
    return lower == 'a' || lower == 'e' || lower == 'i' || 
           lower == 'o' || lower == 'u';
}

/* メイン関数 - テスト用 */
int main(void)
{
    char str1[100] = "Hello, World!";
    char str2[100] = "C Programming";
    char str3[100] = "";
    char str4[100] = "A man a plan a canal Panama";
    char str5[100] = "race car";
    char buffer[200];
    
    printf("=== 文字列処理関数のテスト ===\n\n");
    
    /* 基本処理のテスト */
    printf("=== 基本処理 ===\n");
    printf("str1: \"%s\"\n", str1);
    printf("str2: \"%s\"\n", str2);
    printf("strlen(str1): %d\n", my_strlen(str1));
    printf("strlen(str2): %d\n", my_strlen(str2));
    
    /* strcpyのテスト */
    my_strcpy(str3, str1);
    printf("\nstrcpy(str3, str1)後: \"%s\"\n", str3);
    
    /* strcatのテスト */
    my_strcpy(buffer, str1);
    my_strcat(buffer, " ");
    my_strcat(buffer, str2);
    printf("strcat結果: \"%s\"\n", buffer);
    
    /* strcmpのテスト */
    printf("\nstrcmp(str1, str2): %d\n", my_strcmp(str1, str2));
    printf("strcmp(str1, str1): %d\n", my_strcmp(str1, str1));
    printf("strcmp(\"ABC\", \"ABD\"): %d\n", my_strcmp("ABC", "ABD"));
    printf("\n");
    
    /* 変換処理のテスト */
    printf("=== 変換処理 ===\n");
    char test_str[100];
    
    /* 大文字変換 */
    my_strcpy(test_str, "Hello World 123!");
    printf("元の文字列: \"%s\"\n", test_str);
    to_uppercase(test_str);
    printf("大文字変換: \"%s\"\n", test_str);
    
    /* 小文字変換 */
    to_lowercase(test_str);
    printf("小文字変換: \"%s\"\n", test_str);
    
    /* 逆順 */
    my_strcpy(test_str, "abcdef");
    printf("\n元の文字列: \"%s\"\n", test_str);
    reverse_string(test_str);
    printf("逆順: \"%s\"\n", test_str);
    printf("\n");
    
    /* 解析処理のテスト */
    printf("=== 解析処理 ===\n");
    
    /* 単語数カウント */
    char sentence1[] = "The quick brown fox jumps over the lazy dog";
    char sentence2[] = "  One   two    three  ";
    char sentence3[] = "";
    
    printf("\"%s\"\n単語数: %d\n\n", sentence1, count_words(sentence1));
    printf("\"%s\"\n単語数: %d\n\n", sentence2, count_words(sentence2));
    printf("\"%s\"\n単語数: %d\n\n", sentence3, count_words(sentence3));
    
    /* 回文判定 */
    printf("回文判定:\n");
    printf("\"%s\": %s\n", str4, is_palindrome(str4) ? "回文" : "回文ではない");
    printf("\"%s\": %s\n", str5, is_palindrome(str5) ? "回文" : "回文ではない");
    printf("\"%s\": %s\n", str1, is_palindrome(str1) ? "回文" : "回文ではない");
    
    /* 母音カウント */
    printf("\n母音の数:\n");
    printf("\"%s\": %d個\n", str1, count_vowels(str1));
    printf("\"%s\": %d個\n", str2, count_vowels(str2));
    printf("\"%s\": %d個\n", "AEIOU aeiou", count_vowels("AEIOU aeiou"));
    
    return 0;
}