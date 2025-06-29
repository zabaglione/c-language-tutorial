/*
 * 文字列処理の応用（C99版）
 * ファイル名: advanced_string_processing_c99.c
 * 説明: C99機能を使った実践的な文字列処理テクニック
 * C99準拠 - 可変長配列、複合リテラル、restrict修飾子、inline関数
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define MAX_TOKENS 10
#define MAX_LENGTH 100
#define MAX_STRINGS 5

// C99: inline関数による効率的な文字列変換
static inline void to_uppercase_fast(char * restrict str)
{
    if (str == NULL) return;
    
    for (size_t i = 0; str[i] != '\0'; i++) {
        str[i] = toupper((unsigned char)str[i]);
    }
}

static inline void to_lowercase_fast(char * restrict str)
{
    if (str == NULL) return;
    
    for (size_t i = 0; str[i] != '\0'; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

// C99: 可変長配列を使った動的文字列処理
void process_vla_strings(size_t count, size_t max_len, char data[][max_len])
{
    printf("\n=== 可変長配列文字列処理（%zu個、最大%zu文字） ===\n", count, max_len - 1);
    
    // 統計情報の計算
    size_t total_length = 0;
    size_t min_length = max_len;
    size_t max_length = 0;
    
    for (size_t i = 0; i < count; i++) {
        size_t len = strlen(data[i]);
        total_length += len;
        if (len < min_length) min_length = len;
        if (len > max_length) max_length = len;
    }
    
    printf("統計: 平均%.1f文字、最短%zu文字、最長%zu文字\n",
           (double)total_length / count, min_length, max_length);
}

// C99: restrict修飾子による最適化された文字列ソート
void optimized_string_sort(char * restrict * restrict arr, size_t n)
{
    for (size_t i = 0; i < n - 1; i++) {
        for (size_t j = 0; j < n - 1 - i; j++) {
            if (strcmp(arr[j], arr[j + 1]) > 0) {
                char *temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// C99: 複合リテラルを使った動的トークン分割
size_t advanced_tokenize(const char * restrict input, 
                        const char * restrict delimiters,
                        char result[][MAX_LENGTH], 
                        size_t max_tokens)
{
    char *temp = (char[]){0};  // C99: 複合リテラル（動的初期化）
    size_t input_len = strlen(input);
    
    // 入力をコピー
    temp = malloc(input_len + 1);
    if (temp == NULL) return 0;
    
    strcpy(temp, input);
    
    size_t token_count = 0;
    char *token = strtok(temp, delimiters);
    
    while (token != NULL && token_count < max_tokens) {
        strncpy(result[token_count], token, MAX_LENGTH - 1);
        result[token_count][MAX_LENGTH - 1] = '\0';
        token_count++;
        token = strtok(NULL, delimiters);
    }
    
    free(temp);
    return token_count;
}

// C99: bool型による明確な判定を持つ検索関数
bool advanced_string_search(const char * restrict haystack, 
                           const char * restrict needle,
                           bool case_sensitive,
                           bool whole_word_only)
{
    if (haystack == NULL || needle == NULL) return false;
    
    size_t haystack_len = strlen(haystack);
    size_t needle_len = strlen(needle);
    
    if (needle_len == 0) return true;
    if (needle_len > haystack_len) return false;
    
    for (size_t i = 0; i <= haystack_len - needle_len; i++) {
        bool match = true;
        
        // 文字列比較
        for (size_t j = 0; j < needle_len && match; j++) {
            char h_char = haystack[i + j];
            char n_char = needle[j];
            
            if (!case_sensitive) {
                h_char = tolower((unsigned char)h_char);
                n_char = tolower((unsigned char)n_char);
            }
            
            if (h_char != n_char) {
                match = false;
            }
        }
        
        if (match && whole_word_only) {
            // 単語境界チェック
            bool start_ok = (i == 0) || !isalnum((unsigned char)haystack[i - 1]);
            bool end_ok = (i + needle_len == haystack_len) || 
                         !isalnum((unsigned char)haystack[i + needle_len]);
            match = start_ok && end_ok;
        }
        
        if (match) return true;
    }
    
    return false;
}

int main(void)
{
    printf("===== C99高度な文字列処理 =====\n");
    
    // C99: 複合リテラルによる動的データ初期化
    char (*original_data)[MAX_LENGTH] = (char[][MAX_LENGTH]){
        {"Programming Language Tutorial"},
        {"Advanced String Processing"},
        {"C99 Features Demonstration"},
        {"Dynamic Array Management"},
        {"Efficient Algorithm Implementation"}
    };
    
    // 1. C99可変長配列による動的処理
    printf("\n1. 可変長配列による動的文字列処理:\n");
    for (size_t array_size = 3; array_size <= 5; array_size++) {
        char vla_data[array_size][MAX_LENGTH];  // C99: 可変長配列
        
        // データをコピー
        for (size_t i = 0; i < array_size; i++) {
            strcpy(vla_data[i], original_data[i]);
        }
        
        process_vla_strings(array_size, MAX_LENGTH, vla_data);
    }
    
    // 2. 高度なトークン分割
    printf("\n2. 高度なトークン分割:\n");
    char tokens[MAX_TOKENS][MAX_LENGTH];
    
    // 複数の区切り文字を使用
    const char *input_text = "apple,banana;cherry:date|elderberry grape";
    size_t token_count = advanced_tokenize(input_text, ",;:|", tokens, MAX_TOKENS);
    
    printf("入力: \"%s\"\n", input_text);
    printf("分割結果（%zu個）:\n", token_count);
    for (size_t i = 0; i < token_count; i++) {
        printf("  %zu: \"%s\"\n", i + 1, tokens[i]);
    }
    
    // 3. C99での文字列変換
    printf("\n3. 効率的な文字列変換:\n");
    
    // 複合リテラルによる一時配列
    char *test_strings[] = {
        (char[]){"Hello World"},
        (char[]){"Programming Language"},
        (char[]){"C99 Features"},
        (char[]){"String Processing"},
        (char[]){"Advanced Algorithms"}
    };
    size_t test_count = sizeof(test_strings) / sizeof(test_strings[0]);
    
    printf("変換前 -> 大文字 -> 小文字\n");
    printf("==========================================\n");
    
    for (size_t i = 0; i < test_count; i++) {
        // 元の文字列を保存
        char original[MAX_LENGTH];
        char uppercase[MAX_LENGTH]; 
        char lowercase[MAX_LENGTH];
        
        strcpy(original, test_strings[i]);
        strcpy(uppercase, test_strings[i]);
        strcpy(lowercase, test_strings[i]);
        
        to_uppercase_fast(uppercase);
        to_lowercase_fast(lowercase);
        
        printf("%-25s -> %-25s -> %s\n", original, uppercase, lowercase);
    }
    
    // 4. 最適化されたソート
    printf("\n4. 最適化された文字列ソート:\n");
    
    // ポインタ配列による効率的ソート
    char *sort_data[] = {
        (char[]){"Zebra"}, (char[]){"Apple"}, (char[]){"Monkey"},
        (char[]){"Banana"}, (char[]){"Cat"}, (char[]){"Dog"},
        (char[]){"Elephant"}, (char[]){"Fish"}
    };
    size_t sort_count = sizeof(sort_data) / sizeof(sort_data[0]);
    
    printf("ソート前: ");
    for (size_t i = 0; i < sort_count; i++) {
        printf("%s ", sort_data[i]);
    }
    printf("\n");
    
    optimized_string_sort(sort_data, sort_count);
    
    printf("ソート後: ");
    for (size_t i = 0; i < sort_count; i++) {
        printf("%s ", sort_data[i]);
    }
    printf("\n");
    
    // 5. 高度な文字列検索
    printf("\n5. 高度な文字列検索:\n");
    const char *search_text = "The Programming Language C is powerful and efficient.";
    
    // 検索テストケース
    struct {
        const char *needle;
        bool case_sensitive;
        bool whole_word;
        const char *description;
    } search_tests[] = {
        {"programming", false, false, "大小文字無視・部分一致"},
        {"Programming", true, false, "大小文字区別・部分一致"},
        {"Language", true, true, "大小文字区別・完全単語"},
        {"program", false, true, "大小文字無視・完全単語"},
        {"C", true, true, "大小文字区別・完全単語"},
        {"c", false, true, "大小文字無視・完全単語"}
    };
    size_t test_case_count = sizeof(search_tests) / sizeof(search_tests[0]);
    
    printf("検索対象: \"%s\"\n", search_text);
    printf("検索結果:\n");
    
    for (size_t i = 0; i < test_case_count; i++) {
        bool found = advanced_string_search(search_text, 
                                           search_tests[i].needle,
                                           search_tests[i].case_sensitive,
                                           search_tests[i].whole_word);
        
        printf("  \"%s\" (%s): %s\n", 
               search_tests[i].needle,
               search_tests[i].description,
               found ? "見つかった" : "見つからない");
    }
    
    // 6. C99機能を使った文字列統計
    printf("\n6. 文字列統計分析:\n");
    
    const char *analysis_text = "C99 brings many useful features like VLAs, compound literals, and designated initializers.";
    
    // 固定幅整数型による詳細分析
    struct {
        uint32_t char_count;
        uint32_t word_count; 
        uint32_t upper_count;
        uint32_t lower_count;
        uint32_t digit_count;
        uint32_t space_count;
        uint32_t punct_count;
    } stats = {0};
    
    bool in_word = false;
    
    for (size_t i = 0; analysis_text[i] != '\0'; i++) {
        char c = analysis_text[i];
        stats.char_count++;
        
        if (isupper((unsigned char)c)) stats.upper_count++;
        else if (islower((unsigned char)c)) stats.lower_count++;
        else if (isdigit((unsigned char)c)) stats.digit_count++;
        else if (isspace((unsigned char)c)) stats.space_count++;
        else if (ispunct((unsigned char)c)) stats.punct_count++;
        
        // 単語カウント
        if (isalnum((unsigned char)c)) {
            if (!in_word) {
                stats.word_count++;
                in_word = true;
            }
        } else {
            in_word = false;
        }
    }
    
    printf("分析テキスト: \"%s\"\n", analysis_text);
    printf("文字統計:\n");
    printf("  総文字数: %u\n", stats.char_count);
    printf("  単語数: %u\n", stats.word_count);
    printf("  大文字: %u\n", stats.upper_count);
    printf("  小文字: %u\n", stats.lower_count);
    printf("  数字: %u\n", stats.digit_count);
    printf("  空白: %u\n", stats.space_count);
    printf("  句読点: %u\n", stats.punct_count);
    
    // パーセンテージ計算
    printf("文字種別割合:\n");
    printf("  英字: %.1f%%\n", 
           (double)(stats.upper_count + stats.lower_count) * 100 / stats.char_count);
    printf("  数字: %.1f%%\n", 
           (double)stats.digit_count * 100 / stats.char_count);
    printf("  記号・空白: %.1f%%\n", 
           (double)(stats.space_count + stats.punct_count) * 100 / stats.char_count);
    
    return 0;
}

/*
C99高度な文字列処理の特徴:

1. 可変長配列（VLA）の活用:
   - 実行時サイズ決定による柔軟性
   - メモリ効率的な処理
   - 関数パラメータでの使用

2. 複合リテラルの実用性:
   - 動的な配列初期化
   - 一時的なデータ構造
   - 関数引数での直接使用

3. restrict修飾子による最適化:
   - ポインタエイリアシング情報の提供
   - コンパイラ最適化の向上
   - 高速な文字列操作

4. inline関数による効率化:
   - 関数呼び出しコストの削減
   - 小さな関数の最適化
   - ヘッダファイルでの定義可能

5. bool型による明確性:
   - 真偽値の明確な表現
   - 関数インターフェースの改善
   - コードの可読性向上

6. 固定幅整数型の活用:
   - 明確なデータサイズ
   - 移植性の向上
   - 統計計算での型安全性

7. 新しい標準ライブラリ機能:
   - snprintf()による安全な出力
   - より良いエラーハンドリング

実用的メリット:
- パフォーマンスの向上
- メモリ効率の改善
- コードの安全性向上
- デバッグの容易さ
- 保守性の向上

注意すべき点:
- VLAのスタック使用量
- 複合リテラルのライフタイム
- restrict修飾子の正しい使用法
- C99対応環境の必要性
*/
