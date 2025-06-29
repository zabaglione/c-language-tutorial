/*
 * ファイル名: ex8_1_string_operations_c99.c
 * 演習8-1: 基本的な文字列操作
 * 説明: C99機能を使って標準ライブラリを使わずに文字列操作関数を実装
 * 規格: C99準拠
 */

#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

// C99: inline関数による最適化された文字列長計算
static inline size_t my_strlen_fast(const char * restrict str)
{
    if (str == NULL) return 0;
    
    size_t length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

// C99: restrict修飾子による最適化された文字列コピー
void my_strcpy_optimized(char * restrict dest, const char * restrict src)
{
    if (dest == NULL || src == NULL) return;
    
    size_t i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0'; // 終端文字をコピー
}

// C99: bool型を返すより明確な文字列比較
bool my_strcmp_bool(const char * restrict str1, const char * restrict str2, int *result)
{
    if (str1 == NULL || str2 == NULL) {
        if (result) *result = (str1 == str2) ? 0 : (str1 == NULL ? -1 : 1);
        return false; // 比較失敗
    }
    
    size_t i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] < str2[i]) {
            if (result) *result = -1;
            return true;
        } else if (str1[i] > str2[i]) {
            if (result) *result = 1;
            return true;
        }
        i++;
    }
    
    // どちらかが終了した場合
    if (str1[i] == '\0' && str2[i] == '\0') {
        if (result) *result = 0;  // 等しい
    } else if (str1[i] == '\0') {
        if (result) *result = -1; // str1が短い
    } else {
        if (result) *result = 1;  // str2が短い
    }
    
    return true; // 比較成功
}

// 従来互換の比較関数
int my_strcmp(const char * restrict str1, const char * restrict str2)
{
    int result;
    my_strcmp_bool(str1, str2, &result);
    return result;
}

// C99: 安全な文字列連結（バッファサイズ指定）
bool my_strcat_safe(char * restrict dest, size_t dest_size, const char * restrict src)
{
    if (dest == NULL || src == NULL || dest_size == 0) {
        return false;
    }
    
    size_t dest_len = my_strlen_fast(dest);
    size_t src_len = my_strlen_fast(src);
    
    // バッファオーバーフローチェック
    if (dest_len + src_len >= dest_size) {
        return false; // 容量不足
    }
    
    // 連結元をコピー
    for (size_t i = 0; i < src_len; i++) {
        dest[dest_len + i] = src[i];
    }
    
    // 終端文字を追加
    dest[dest_len + src_len] = '\0';
    return true;
}

// C99: より安全な文字検索（結果情報付き）
typedef struct {
    bool found;
    size_t position;
    char *pointer;
} search_result_t;

search_result_t my_strchr_advanced(const char * restrict str, int ch)
{
    search_result_t result = {false, 0, NULL};
    
    if (str == NULL) return result;
    
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] == ch) {
            result.found = true;
            result.position = i;
            result.pointer = (char *)&str[i];
            return result;
        }
    }
    
    // 終端文字を検索する場合
    if (ch == '\0') {
        result.found = true;
        result.position = my_strlen_fast(str);
        result.pointer = (char *)&str[result.position];
    }
    
    return result;
}

// 従来互換の文字検索
char *my_strchr(const char * restrict str, int ch)
{
    search_result_t result = my_strchr_advanced(str, ch);
    return result.pointer;
}

// C99: 後方検索（最適化版）
search_result_t my_strrchr_advanced(const char * restrict str, int ch)
{
    search_result_t result = {false, 0, NULL};
    
    if (str == NULL) return result;
    
    size_t length = my_strlen_fast(str);
    
    // 後ろから検索（size_tでのオーバーフロー対策）
    for (size_t i = length + 1; i > 0; i--) {
        size_t index = i - 1;
        if (str[index] == ch) {
            result.found = true;
            result.position = index;
            result.pointer = (char *)&str[index];
            return result;
        }
    }
    
    return result;
}

char *my_strrchr(const char * restrict str, int ch)
{
    search_result_t result = my_strrchr_advanced(str, ch);
    return result.pointer;
}

// C99: 文字カウント（詳細情報付き）
typedef struct {
    size_t count;
    size_t first_position;
    size_t last_position;
    bool found;
} char_count_info_t;

char_count_info_t count_char_detailed(const char * restrict str, char ch)
{
    char_count_info_t info = {0, 0, 0, false};
    
    if (str == NULL) return info;
    
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] == ch) {
            if (!info.found) {
                info.first_position = i;
                info.found = true;
            }
            info.last_position = i;
            info.count++;
        }
    }
    
    return info;
}

// 従来互換の文字カウント
size_t count_char(const char * restrict str, char ch)
{
    char_count_info_t info = count_char_detailed(str, ch);
    return info.count;
}

// C99: 可変長配列を使った文字列テスト関数
void test_vla_string_functions(size_t buffer_size)
{
    char test_buffer[buffer_size];  // C99: 可変長配列
    
    printf("\n=== VLA文字列テスト（バッファサイズ: %zu） ===\n", buffer_size);
    
    // 安全な文字列操作のテスト
    my_strcpy_optimized(test_buffer, "Hello");
    printf("初期文字列: \"%s\"\n", test_buffer);
    
    bool concat_success = my_strcat_safe(test_buffer, buffer_size, " World");
    printf("連結%s: \"%s\"\n", 
           concat_success ? "成功" : "失敗", test_buffer);
    
    // 長い文字列での連結失敗テスト
    bool overflow_test = my_strcat_safe(test_buffer, buffer_size, 
                                       " This is a very long string that might overflow");
    printf("オーバーフローテスト%s\n", overflow_test ? "成功" : "失敗（期待通り）");
}

// C99: 統計情報を収集する総合テスト
void comprehensive_string_test(void)
{
    printf("\n=== 総合文字列テスト ===\n");
    
    const char *test_strings[] = {
        "Hello, World!",
        "Programming in C99",
        "String processing functions",
        "Advanced character operations",
        ""  // 空文字列
    };
    size_t test_count = sizeof(test_strings) / sizeof(test_strings[0]);
    
    // 統計情報の構造体
    struct {
        size_t total_length;
        size_t total_chars[256];  // ASCII文字の出現回数
        size_t string_count;
        size_t max_length;
        size_t min_length;
    } stats = {0};
    
    stats.min_length = SIZE_MAX;
    
    // 各文字列を分析
    for (size_t i = 0; i < test_count; i++) {
        size_t len = my_strlen_fast(test_strings[i]);
        stats.total_length += len;
        stats.string_count++;
        
        if (len > stats.max_length) stats.max_length = len;
        if (len < stats.min_length) stats.min_length = len;
        
        // 文字出現回数をカウント
        for (size_t j = 0; j < len; j++) {
            unsigned char c = (unsigned char)test_strings[i][j];
            stats.total_chars[c]++;
        }
        
        printf("文字列%zu: \"%s\" (長さ: %zu)\n", i + 1, test_strings[i], len);
    }
    
    printf("\n統計情報:\n");
    printf("  文字列数: %zu\n", stats.string_count);
    printf("  総文字数: %zu\n", stats.total_length);
    printf("  平均長: %.1f\n", (double)stats.total_length / stats.string_count);
    printf("  最長: %zu文字\n", stats.max_length);
    printf("  最短: %zu文字\n", stats.min_length);
    
    // 最も出現頻度の高い文字を表示
    printf("\n文字出現頻度（上位5位）:\n");
    for (int rank = 0; rank < 5; rank++) {
        size_t max_count = 0;
        unsigned char max_char = 0;
        
        for (size_t c = 32; c < 127; c++) { // 印刷可能文字のみ
            if (stats.total_chars[c] > max_count) {
                max_count = stats.total_chars[c];
                max_char = (unsigned char)c;
            }
        }
        
        if (max_count > 0) {
            printf("  %d位: '%c' (%zu回)\n", rank + 1, max_char, max_count);
            stats.total_chars[max_char] = 0; // 次回検索から除外
        }
    }
}

int main(void)
{
    printf("===== C99基本的な文字列操作の実装 =====\n");
    
    // 1. 基本関数のテスト
    printf("\n1. 基本関数のテスト:\n");
    
    // 長さ計算
    printf("my_strlen(\"Hello\"): %zu\n", my_strlen_fast("Hello"));
    printf("my_strlen(\"\"): %zu\n", my_strlen_fast(""));
    
    // 文字列比較
    int cmp_result;
    bool cmp_success = my_strcmp_bool("apple", "banana", &cmp_result);
    printf("my_strcmp(\"apple\", \"banana\"): %s, 結果=%d\n", 
           cmp_success ? "成功" : "失敗", cmp_result);
    
    // 2. 高度な検索テスト
    printf("\n2. 高度な検索テスト:\n");
    const char *search_text = "Hello, Programming World!";
    
    search_result_t result = my_strchr_advanced(search_text, 'o');
    if (result.found) {
        printf("最初の'o'の位置: %zu\n", result.position);
    }
    
    result = my_strrchr_advanced(search_text, 'o');
    if (result.found) {
        printf("最後の'o'の位置: %zu\n", result.position);
    }
    
    // 文字カウント詳細
    char_count_info_t count_info = count_char_detailed(search_text, 'l');
    printf("'l'の詳細情報: 個数=%zu, 最初=%zu, 最後=%zu\n",
           count_info.count, count_info.first_position, count_info.last_position);
    
    // 3. 可変長配列テスト
    printf("\n3. 可変長配列テスト:\n");
    for (size_t size = 10; size <= 50; size += 20) {
        test_vla_string_functions(size);
    }
    
    // 4. 安全な文字列操作
    printf("\n4. 安全な文字列操作:\n");
    char buffer[100] = "C99";
    
    bool success = my_strcat_safe(buffer, sizeof(buffer), " Features");
    printf("連結1 %s: \"%s\"\n", success ? "成功" : "失敗", buffer);
    
    success = my_strcat_safe(buffer, sizeof(buffer), " are amazing!");
    printf("連結2 %s: \"%s\"\n", success ? "成功" : "失敗", buffer);
    
    // 5. 総合テスト
    comprehensive_string_test();
    
    // 6. 実用例
    printf("\n=== 実用例 ===\n");
    const char *analysis_text = "C99 introduces many new features for better programming!";
    
    printf("分析対象: \"%s\"\n", analysis_text);
    printf("文字列長: %zu\n", my_strlen_fast(analysis_text));
    
    // 各文字の詳細分析
    char target_chars[] = {'C', 'e', 'r', 'n'};
    size_t target_count = sizeof(target_chars) / sizeof(target_chars[0]);
    
    for (size_t i = 0; i < target_count; i++) {
        char_count_info_t info = count_char_detailed(analysis_text, target_chars[i]);
        if (info.found) {
            printf("'%c': %zu個 (最初=%zu, 最後=%zu)\n",
                   target_chars[i], info.count, info.first_position, info.last_position);
        } else {
            printf("'%c': 見つからない\n", target_chars[i]);
        }
    }
    
    return 0;
}

/*
C99による文字列操作の改善点:

1. 型安全性の向上:
   - bool型による明確な成功/失敗表現
   - size_t型による適切なサイズ表現
   - 固定幅整数型による移植性

2. パフォーマンスの最適化:
   - inline関数による高速化
   - restrict修飾子による最適化ヒント
   - 効率的なアルゴリズム実装

3. 安全性の向上:
   - バッファサイズ指定による安全な操作
   - オーバーフロー検出
   - NULL ポインタ検査

4. 可読性の改善:
   - 構造体による詳細情報の返却
   - 明確な関数名と戻り値
   - エラー情報の詳細化

5. 柔軟性の向上:
   - 可変長配列による動的処理
   - 複合リテラルによる一時データ
   - 指定初期化子による部分初期化

6. デバッグ支援:
   - 詳細な統計情報
   - 位置情報の提供
   - 包括的なテスト機能

実用的メリット:
- メモリ安全性の向上
- パフォーマンスの最適化
- コードの保守性向上
- バグの早期発見
- 移植性の確保

注意点:
- C99対応コンパイラが必要
- VLAのスタック使用量に注意
- restrict修飾子の正しい使用
- 互換性の維持
*/

