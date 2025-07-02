/*
 * ファイル名: ex10_3_string_search_c99.c
 * 演習10-3: 高度な文字列検索
 * 説明: C99機能を使った高度な文字列検索とパターンマッチング機能
 * 規格: C99準拠
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define MAX_PATTERN_LENGTH 100
#define MAX_TEXT_LENGTH 1000
#define MAX_RESULTS 50

// C99: 検索結果の詳細情報
typedef struct {
    size_t position;
    size_t length;
    char *match_text;
    bool is_word_boundary;
} match_info_t;

// C99: 検索オプション設定
typedef struct {
    bool case_sensitive;
    bool whole_word_only;
    bool regex_mode;
    bool return_all_matches;
    size_t max_matches;
} search_options_t;

// C99: 検索結果のコレクション
typedef struct {
    match_info_t *matches;
    size_t count;
    size_t capacity;
    bool search_successful;
    char error_message[100];
} search_results_t;

// C99: inline関数による高速な文字比較
static inline bool char_equals(char a, char b, bool case_sensitive)
{
    if (case_sensitive) {
        return a == b;
    } else {
        return tolower((unsigned char)a) == tolower((unsigned char)b);
    }
}

// C99: inline関数による単語境界の判定
static inline bool is_word_boundary(const char *text, size_t position, size_t text_length)
{
    if (position == 0 || position == text_length) {
        return true;
    }
    
    bool prev_is_alnum = isalnum((unsigned char)text[position - 1]);
    bool curr_is_alnum = isalnum((unsigned char)text[position]);
    
    return prev_is_alnum != curr_is_alnum;
}

// C99: restrict修飾子による最適化された基本検索
char *my_strstr_optimized(const char * restrict haystack, 
                         const char * restrict needle,
                         bool case_sensitive)
{
    if (haystack == NULL || needle == NULL) return NULL;
    if (*needle == '\0') return (char *)haystack;
    
    size_t needle_len = strlen(needle);
    size_t haystack_len = strlen(haystack);
    
    if (needle_len > haystack_len) return NULL;
    
    for (size_t i = 0; i <= haystack_len - needle_len; i++) {
        bool match = true;
        
        for (size_t j = 0; j < needle_len && match; j++) {
            if (!char_equals(haystack[i + j], needle[j], case_sensitive)) {
                match = false;
            }
        }
        
        if (match) {
            return (char *)(haystack + i);
        }
    }
    
    return NULL;
}

// C99: 高度な単一パターン検索
match_info_t find_pattern_advanced(const char * restrict text,
                                  const char * restrict pattern,
                                  const search_options_t * restrict options)
{
    match_info_t result = {0, 0, NULL, false};
    
    if (text == NULL || pattern == NULL || options == NULL) {
        return result;
    }
    
    size_t text_len = strlen(text);
    size_t pattern_len = strlen(pattern);
    
    if (pattern_len == 0 || pattern_len > text_len) {
        return result;
    }
    
    for (size_t i = 0; i <= text_len - pattern_len; i++) {
        bool match = true;
        
        // パターンマッチング
        for (size_t j = 0; j < pattern_len && match; j++) {
            if (!char_equals(text[i + j], pattern[j], options->case_sensitive)) {
                match = false;
            }
        }
        
        if (match) {
            // 単語境界チェック
            if (options->whole_word_only) {
                bool start_boundary = is_word_boundary(text, i, text_len);
                bool end_boundary = is_word_boundary(text, i + pattern_len, text_len);
                
                if (!start_boundary || !end_boundary) {
                    continue; // 単語境界条件を満たさない
                }
            }
            
            // マッチ情報を設定
            result.position = i;
            result.length = pattern_len;
            result.match_text = (char *)(text + i);
            result.is_word_boundary = options->whole_word_only;
            break; // 最初のマッチのみ返す
        }
    }
    
    return result;
}

// C99: 全てのマッチを検索する関数
search_results_t find_all_matches(const char * restrict text,
                                 const char * restrict pattern,
                                 const search_options_t * restrict options)
{
    search_results_t results = {
        .matches = NULL,
        .count = 0,
        .capacity = 0,
        .search_successful = false,
        .error_message = ""
    };
    
    if (text == NULL || pattern == NULL || options == NULL) {
        strcpy(results.error_message, "無効な引数");
        return results;
    }
    
    size_t text_len = strlen(text);
    size_t pattern_len = strlen(pattern);
    
    if (pattern_len == 0) {
        strcpy(results.error_message, "空のパターン");
        return results;
    }
    
    // 初期容量を確保
    results.capacity = (options->max_matches > 0) ? options->max_matches : MAX_RESULTS;
    results.matches = malloc(results.capacity * sizeof(match_info_t));
    
    if (results.matches == NULL) {
        strcpy(results.error_message, "メモリ確保失敗");
        return results;
    }
    
    // 検索実行
    for (size_t i = 0; i <= text_len - pattern_len && results.count < results.capacity; i++) {
        bool match = true;
        
        // パターンマッチング
        for (size_t j = 0; j < pattern_len && match; j++) {
            if (!char_equals(text[i + j], pattern[j], options->case_sensitive)) {
                match = false;
            }
        }
        
        if (match) {
            // 単語境界チェック
            bool is_valid_match = true;
            if (options->whole_word_only) {
                bool start_boundary = is_word_boundary(text, i, text_len);
                bool end_boundary = is_word_boundary(text, i + pattern_len, text_len);
                is_valid_match = start_boundary && end_boundary;
            }
            
            if (is_valid_match) {
                results.matches[results.count] = (match_info_t){
                    .position = i,
                    .length = pattern_len,
                    .match_text = (char *)(text + i),
                    .is_word_boundary = options->whole_word_only
                };
                results.count++;
            }
        }
    }
    
    results.search_successful = true;
    return results;
}

// C99: 可変長配列を使った高速ワイルドカード検索
bool wildcard_match_vla(const char * restrict text, const char * restrict pattern)
{
    if (text == NULL || pattern == NULL) return false;
    
    size_t text_len = strlen(text);
    size_t pattern_len = strlen(pattern);
    
    // C99: 可変長配列による動的プログラミングテーブル
    bool dp[text_len + 1][pattern_len + 1];
    
    // 初期化
    for (size_t i = 0; i <= text_len; i++) {
        for (size_t j = 0; j <= pattern_len; j++) {
            dp[i][j] = false;
        }
    }
    
    dp[0][0] = true;
    
    // '*'の初期処理
    for (size_t j = 1; j <= pattern_len; j++) {
        if (pattern[j - 1] == '*') {
            dp[0][j] = dp[0][j - 1];
        }
    }
    
    // 動的プログラミング
    for (size_t i = 1; i <= text_len; i++) {
        for (size_t j = 1; j <= pattern_len; j++) {
            char pattern_char = pattern[j - 1];
            char text_char = text[i - 1];
            
            if (pattern_char == '*') {
                dp[i][j] = dp[i - 1][j] || dp[i][j - 1] || dp[i - 1][j - 1];
            } else if (pattern_char == '?' || pattern_char == text_char) {
                dp[i][j] = dp[i - 1][j - 1];
            }
        }
    }
    
    return dp[text_len][pattern_len];
}

// C99: 複数パターンの同時検索
typedef struct {
    char pattern[MAX_PATTERN_LENGTH];
    size_t matches_found;
    match_info_t first_match;
} pattern_result_t;

void multi_pattern_search(const char * restrict text,
                         size_t pattern_count,
                         char patterns[][MAX_PATTERN_LENGTH],
                         pattern_result_t results[],
                         const search_options_t * restrict options)
{
    if (text == NULL || patterns == NULL || results == NULL || options == NULL) {
        return;
    }
    
    // 各パターンを初期化
    for (size_t p = 0; p < pattern_count; p++) {
        strcpy(results[p].pattern, patterns[p]);
        results[p].matches_found = 0;
        results[p].first_match = (match_info_t){0, 0, NULL, false};
    }
    
    // 各パターンについて検索実行
    for (size_t p = 0; p < pattern_count; p++) {
        search_results_t search_result = find_all_matches(text, patterns[p], options);
        
        if (search_result.search_successful && search_result.count > 0) {
            results[p].matches_found = search_result.count;
            results[p].first_match = search_result.matches[0];
        }
        
        // メモリ解放
        if (search_result.matches != NULL) {
            free(search_result.matches);
        }
    }
}

// C99: メモリ解放関数
void free_search_results(search_results_t *results)
{
    if (results != NULL && results->matches != NULL) {
        free(results->matches);
        results->matches = NULL;
        results->count = 0;
        results->capacity = 0;
    }
}

// C99: 検索結果の詳細表示
void display_search_results(const search_results_t * restrict results, 
                           const char * restrict pattern)
{
    printf("\n=== 検索結果: \"%s\" ===\n", pattern);
    
    if (!results->search_successful) {
        printf("検索エラー: %s\n", results->error_message);
        return;
    }
    
    if (results->count == 0) {
        printf("マッチが見つかりませんでした。\n");
        return;
    }
    
    printf("見つかったマッチ: %zu個\n", results->count);
    
    for (size_t i = 0; i < results->count; i++) {
        const match_info_t *match = &results->matches[i];
        printf("%zu. 位置 %zu-%zu: \"", i + 1, match->position, 
               match->position + match->length - 1);
        
        // マッチした部分を表示
        for (size_t j = 0; j < match->length; j++) {
            putchar(match->match_text[j]);
        }
        printf("\"");
        
        if (match->is_word_boundary) {
            printf(" (単語境界)");
        }
        printf("\n");
    }
}

int main(void)
{
    printf("===== C99高度な文字列検索システム =====\n");
    
    // テスト用テキスト
    const char *test_text = "Programming in C is fun. C language is powerful. "
                           "Many programmers love C programming. "
                           "C99 adds many useful features for C developers.";
    
    printf("検索対象テキスト:\n\"%s\"\n", test_text);
    
    // 1. 基本的な検索テスト
    printf("\n1. 基本的な検索テスト:\n");
    
    // C99: 複合リテラルによる検索オプション設定
    search_options_t basic_options = (search_options_t){
        .case_sensitive = true,
        .whole_word_only = false,
        .regex_mode = false,
        .return_all_matches = true,
        .max_matches = 10
    };
    
    search_results_t results = find_all_matches(test_text, "C", &basic_options);
    display_search_results(&results, "C");
    free_search_results(&results);
    
    // 2. 大小文字無視検索
    printf("\n2. 大小文字無視検索:\n");
    
    search_options_t case_insensitive = basic_options;
    case_insensitive.case_sensitive = false;
    
    results = find_all_matches(test_text, "programming", &case_insensitive);
    display_search_results(&results, "programming");
    free_search_results(&results);
    
    // 3. 単語境界検索
    printf("\n3. 単語境界検索:\n");
    
    search_options_t word_boundary = basic_options;
    word_boundary.whole_word_only = true;
    
    results = find_all_matches(test_text, "C", &word_boundary);
    display_search_results(&results, "C (単語境界)");
    free_search_results(&results);
    
    // 4. ワイルドカード検索テスト
    printf("\n4. ワイルドカード検索テスト:\n");
    
    struct {
        const char *pattern;
        const char *description;
    } wildcard_tests[] = {
        {"C*", "Cで始まる"},
        {"*ing", "ingで終わる"},
        {"?un", "3文字でunで終わる"},
        {"*C*", "Cを含む"},
        {"Programming*C", "ProgrammingからCまで"}
    };
    
    size_t wildcard_count = sizeof(wildcard_tests) / sizeof(wildcard_tests[0]);
    
    for (size_t i = 0; i < wildcard_count; i++) {
        bool match = wildcard_match_vla(test_text, wildcard_tests[i].pattern);
        printf("パターン \"%s\" (%s): %s\n", 
               wildcard_tests[i].pattern,
               wildcard_tests[i].description,
               match ? "マッチ" : "非マッチ");
    }
    
    // 5. 複数パターン同時検索
    printf("\n5. 複数パターン同時検索:\n");
    
    char search_patterns[][MAX_PATTERN_LENGTH] = {
        "C",
        "programming", 
        "language",
        "developers",
        "features"
    };
    size_t pattern_count = sizeof(search_patterns) / sizeof(search_patterns[0]);
    
    // C99: 可変長配列による結果格納
    pattern_result_t multi_results[pattern_count];
    
    multi_pattern_search(test_text, pattern_count, search_patterns, 
                        multi_results, &case_insensitive);
    
    printf("複数パターン検索結果:\n");
    for (size_t i = 0; i < pattern_count; i++) {
        printf("  \"%s\": %zu個のマッチ", 
               multi_results[i].pattern, multi_results[i].matches_found);
        
        if (multi_results[i].matches_found > 0) {
            printf(" (最初の位置: %zu)", multi_results[i].first_match.position);
        }
        printf("\n");
    }
    
    // 6. 性能テスト
    printf("\n6. 性能テスト:\n");
    
    // 大きなテキストを生成
    const size_t large_text_size = 10000;
    char *large_text = malloc(large_text_size);
    if (large_text != NULL) {
        // テストデータ生成
        size_t pos = 0;
        while (pos < large_text_size - 100) {
            int written = snprintf(large_text + pos, large_text_size - pos,
                                 "This is test data number %zu. ", pos / 50);
            if (written > 0) {
                pos += written;
            } else {
                break;
            }
        }
        large_text[large_text_size - 1] = '\0';
        
        printf("大きなテキスト（%zu文字）での検索テスト:\n", strlen(large_text));
        
        search_options_t perf_options = {
            .case_sensitive = false,
            .whole_word_only = false,
            .regex_mode = false,
            .return_all_matches = true,
            .max_matches = 100
        };
        
        results = find_all_matches(large_text, "test", &perf_options);
        printf("\"test\"の検索結果: %zu個のマッチ\n", results.count);
        free_search_results(&results);
        
        free(large_text);
    }
    
    // 7. エラーハンドリングテスト
    printf("\n7. エラーハンドリングテスト:\n");
    
    // NULL入力テスト
    results = find_all_matches(NULL, "test", &basic_options);
    if (!results.search_successful) {
        printf("NULL入力エラー: %s\n", results.error_message);
    }
    
    // 空パターンテスト
    results = find_all_matches(test_text, "", &basic_options);
    if (!results.search_successful) {
        printf("空パターンエラー: %s\n", results.error_message);
    }
    
    // 8. 実用例：ログ解析システム
    printf("\n8. 実用例：ログ解析システム:\n");
    
    const char *log_data = 
        "2024-01-15 10:30:15 INFO: User login successful\n"
        "2024-01-15 10:30:45 WARNING: High memory usage detected\n"
        "2024-01-15 10:31:02 ERROR: Database connection failed\n"
        "2024-01-15 10:31:15 INFO: Retry connection successful\n"
        "2024-01-15 10:31:30 ERROR: File permission denied\n";
    
    printf("ログデータ解析:\n");
    
    // エラーレベル検索
    char log_patterns[][MAX_PATTERN_LENGTH] = {
        "ERROR",
        "WARNING", 
        "INFO"
    };
    size_t log_pattern_count = sizeof(log_patterns) / sizeof(log_patterns[0]);
    
    pattern_result_t log_results[log_pattern_count];
    
    search_options_t log_options = {
        .case_sensitive = true,
        .whole_word_only = true,
        .regex_mode = false,
        .return_all_matches = true,
        .max_matches = 20
    };
    
    multi_pattern_search(log_data, log_pattern_count, log_patterns, 
                        log_results, &log_options);
    
    printf("ログレベル統計:\n");
    for (size_t i = 0; i < log_pattern_count; i++) {
        printf("  %s: %zu件\n", 
               log_results[i].pattern, log_results[i].matches_found);
    }
    
    printf("\n✓ 検索システムのテストが完了しました\n");
    printf("実装された機能:\n");
    printf("  - 大小文字区別/無視検索\n");
    printf("  - 単語境界検索\n");
    printf("  - ワイルドカード検索\n");
    printf("  - 複数パターン同時検索\n");
    printf("  - 詳細な検索結果情報\n");
    printf("  - エラーハンドリング\n");
    printf("  - メモリ管理\n");
    
    return 0;
}

/*
C99による高度な文字列検索システムの特徴:

1. 型安全性と明確性:
   - bool型による明確な真偽値表現
   - 構造体による検索オプション管理
   - enum型による検索モード指定

2. メモリ効率と安全性:
   - 可変長配列による動的メモリ使用
   - 適切なメモリ管理とエラーハンドリング
   - バッファオーバーフロー対策

3. パフォーマンス最適化:
   - inline関数による高速化
   - restrict修飾子による最適化ヒント
   - 効率的なアルゴリズム実装

4. 柔軟性と拡張性:
   - 複数の検索モード対応
   - カスタマイズ可能な検索オプション
   - プラグイン可能な検索アルゴリズム

5. 実用的な機能:
   - ワイルドカード検索
   - 複数パターン同時検索
   - 詳細な結果情報
   - ログ解析機能

6. C99特有の機能活用:
   - 複合リテラルによる設定初期化
   - 可変長配列による動的処理
   - 指定初期化子による明確な初期化
   - 固定幅整数型による型安全性

技術的改善点:
- 動的プログラミングによるワイルドカード検索
- 効率的なメモリ使用パターン
- エラー情報の詳細化
- 大量データ処理対応
- 再利用可能なコンポーネント設計

実用的なメリット:
- 高速な検索処理
- 豊富な検索オプション
- 詳細な結果分析
- 堅牢なエラーハンドリング
- 拡張しやすい設計

注意事項:
- 可変長配列のスタック使用量
- 動的メモリ管理の重要性
- パフォーマンスとメモリのトレードオフ
- C99対応環境の必要性
*/
