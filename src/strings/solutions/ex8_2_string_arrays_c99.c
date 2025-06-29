/*
 * ファイル名: ex8_2_string_arrays_c99.c
 * 演習8-2: 文字列配列の管理
 * 説明: C99機能を使った学生名を格納する文字列配列の管理システム
 * 規格: C99準拠
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <ctype.h>

#define MAX_STUDENTS 10
#define MAX_NAME_LENGTH 50

// C99: 学生情報の詳細構造体
typedef struct {
    char name[MAX_NAME_LENGTH];
    uint16_t id;
    bool active;
    double gpa;
} student_info_t;

// C99: 検索結果の詳細情報
typedef struct {
    bool found;
    size_t index;
    size_t match_count;
} search_result_t;

// C99: inline関数による効率的な表示
static inline void display_separator(const char *title, char separator_char)
{
    printf("\n");
    for (size_t i = 0; i < strlen(title) + 6; i++) {
        putchar(separator_char);
    }
    printf("\n=== %s ===\n", title);
}

// C99: 可変長配列を使った学生表示
void display_students_vla(size_t count, char students[count][MAX_NAME_LENGTH], const char *title)
{
    display_separator(title, '=');
    
    if (count == 0) {
        printf("登録されている学生はいません。\n");
        return;
    }
    
    for (size_t i = 0; i < count; i++) {
        printf("%2zu. %s\n", i + 1, students[i]);
    }
    printf("合計: %zu名\n", count);
}

// C99: 詳細情報付き学生表示
void display_detailed_students(const student_info_t students[], size_t count)
{
    display_separator("詳細学生一覧", '=');
    
    if (count == 0) {
        printf("登録されている学生はいません。\n");
        return;
    }
    
    printf("%-4s %-20s %-6s %-8s %s\n", "ID", "名前", "状態", "GPA", "ステータス");
    printf("%-4s %-20s %-6s %-8s %s\n", "----", "--------------------", "------", "--------", "--------");
    
    for (size_t i = 0; i < count; i++) {
        printf("%-4u %-20s %-6s %-8.2f %s\n",
               students[i].id,
               students[i].name,
               students[i].active ? "有効" : "無効",
               students[i].gpa,
               students[i].gpa >= 3.5 ? "優秀" : 
               students[i].gpa >= 3.0 ? "良好" : 
               students[i].gpa >= 2.0 ? "普通" : "要注意");
    }
}

// C99: より安全で情報豊富な学生追加
bool add_student_safe(char students[][MAX_NAME_LENGTH], size_t *count, 
                     const char *name, size_t max_students)
{
    // 基本チェック
    if (*count >= max_students) {
        printf("エラー: これ以上学生を追加できません（最大%zu名）\n", max_students);
        return false;
    }
    
    if (name == NULL || strlen(name) == 0) {
        printf("エラー: 名前が無効です\n");
        return false;
    }
    
    if (strlen(name) >= MAX_NAME_LENGTH) {
        printf("エラー: 名前が長すぎます（最大%d文字）\n", MAX_NAME_LENGTH - 1);
        return false;
    }
    
    // 重複チェック
    for (size_t i = 0; i < *count; i++) {
        if (strcmp(students[i], name) == 0) {
            printf("エラー: \"%s\" は既に登録されています（%zu番目）\n", name, i + 1);
            return false;
        }
    }
    
    // 追加実行
    strcpy(students[*count], name);
    (*count)++;
    printf("✓ \"%s\" を%zu番目に追加しました\n", name, *count);
    return true;
}

// C99: 複数の削除モードを持つ削除関数
typedef enum {
    REMOVE_BY_NAME,
    REMOVE_BY_INDEX,
    REMOVE_BY_PATTERN
} remove_mode_t;

bool remove_student_advanced(char students[][MAX_NAME_LENGTH], size_t *count,
                            remove_mode_t mode, const void *criteria)
{
    size_t remove_index = SIZE_MAX;
    char removed_name[MAX_NAME_LENGTH];
    
    switch (mode) {
    case REMOVE_BY_NAME: {
        const char *name = (const char *)criteria;
        for (size_t i = 0; i < *count; i++) {
            if (strcmp(students[i], name) == 0) {
                remove_index = i;
                break;
            }
        }
        if (remove_index == SIZE_MAX) {
            printf("エラー: \"%s\" は見つかりませんでした\n", name);
            return false;
        }
        break;
    }
    
    case REMOVE_BY_INDEX: {
        size_t index = *(const size_t *)criteria;
        if (index >= *count) {
            printf("エラー: 無効なインデックスです（1-%zu の範囲で指定してください）\n", *count);
            return false;
        }
        remove_index = index;
        break;
    }
    
    case REMOVE_BY_PATTERN: {
        const char *pattern = (const char *)criteria;
        // 最初にマッチした学生を削除
        for (size_t i = 0; i < *count; i++) {
            if (strstr(students[i], pattern) != NULL) {
                remove_index = i;
                break;
            }
        }
        if (remove_index == SIZE_MAX) {
            printf("エラー: パターン \"%s\" にマッチする学生が見つかりませんでした\n", pattern);
            return false;
        }
        break;
    }
    }
    
    // 削除前に名前を保存
    strcpy(removed_name, students[remove_index]);
    
    // 要素を前に詰める
    for (size_t i = remove_index; i < *count - 1; i++) {
        strcpy(students[i], students[i + 1]);
    }
    
    (*count)--;
    printf("✓ %zu番目の学生 \"%s\" を削除しました\n", remove_index + 1, removed_name);
    return true;
}

// C99: 高度な検索機能
search_result_t search_students_advanced(char students[][MAX_NAME_LENGTH], size_t count,
                                        const char *query, bool partial_match, bool case_sensitive)
{
    search_result_t result = {false, 0, 0};
    size_t found_indices[MAX_STUDENTS];
    
    for (size_t i = 0; i < count; i++) {
        bool match = false;
        
        if (partial_match) {
            // 部分一致検索
            if (case_sensitive) {
                match = (strstr(students[i], query) != NULL);
            } else {
                // 大小文字無視の部分一致（簡易実装）
                char student_lower[MAX_NAME_LENGTH];
                char query_lower[MAX_NAME_LENGTH];
                
                // 小文字に変換
                for (size_t j = 0; j < strlen(students[i]) && j < MAX_NAME_LENGTH - 1; j++) {
                    student_lower[j] = tolower((unsigned char)students[i][j]);
                }
                student_lower[strlen(students[i])] = '\0';
                
                for (size_t j = 0; j < strlen(query) && j < MAX_NAME_LENGTH - 1; j++) {
                    query_lower[j] = tolower((unsigned char)query[j]);
                }
                query_lower[strlen(query)] = '\0';
                
                match = (strstr(student_lower, query_lower) != NULL);
            }
        } else {
            // 完全一致検索
            if (case_sensitive) {
                match = (strcmp(students[i], query) == 0);
            } else {
                match = (strcasecmp(students[i], query) == 0);
            }
        }
        
        if (match) {
            if (!result.found) {
                result.found = true;
                result.index = i;
            }
            found_indices[result.match_count] = i;
            result.match_count++;
        }
    }
    
    // 複数マッチの場合は詳細表示
    if (result.match_count > 1) {
        printf("検索結果（%zu件）:\n", result.match_count);
        for (size_t i = 0; i < result.match_count; i++) {
            printf("  %zu. [%zu] %s\n", i + 1, found_indices[i] + 1, students[found_indices[i]]);
        }
    }
    
    return result;
}

// C99: 学生配列のソート（複数ソートモード）
void sort_students_advanced(char students[][MAX_NAME_LENGTH], size_t count, bool reverse)
{
    // バブルソート（C99のforループ内変数宣言）
    for (size_t i = 0; i < count - 1; i++) {
        for (size_t j = 0; j < count - 1 - i; j++) {
            int comparison = strcmp(students[j], students[j + 1]);
            bool should_swap = reverse ? (comparison < 0) : (comparison > 0);
            
            if (should_swap) {
                char temp[MAX_NAME_LENGTH];
                strcpy(temp, students[j]);
                strcpy(students[j], students[j + 1]);
                strcpy(students[j + 1], temp);
            }
        }
    }
    
    printf("✓ 学生名を%sソートしました\n", reverse ? "逆順" : "アルファベット順");
}

// C99: 統計情報の計算
void calculate_statistics(char students[][MAX_NAME_LENGTH], size_t count)
{
    if (count == 0) {
        printf("統計情報: 学生が登録されていません\n");
        return;
    }
    
    size_t total_length = 0;
    size_t min_length = SIZE_MAX;
    size_t max_length = 0;
    uint32_t char_frequency[256] = {0};  // C99: 指定初期化子
    
    // 各学生名を分析
    for (size_t i = 0; i < count; i++) {
        size_t len = strlen(students[i]);
        total_length += len;
        
        if (len < min_length) min_length = len;
        if (len > max_length) max_length = len;
        
        // 文字頻度をカウント
        for (size_t j = 0; j < len; j++) {
            unsigned char c = (unsigned char)students[i][j];
            char_frequency[c]++;
        }
    }
    
    display_separator("統計情報", '-');
    printf("学生数: %zu名\n", count);
    printf("平均名前長: %.1f文字\n", (double)total_length / count);
    printf("最短名前: %zu文字\n", min_length);
    printf("最長名前: %zu文字\n", max_length);
    printf("総文字数: %zu文字\n", total_length);
    
    // 最も使用頻度の高い文字を表示
    printf("\n使用頻度の高い文字:\n");
    for (int rank = 0; rank < 5; rank++) {
        uint32_t max_count = 0;
        unsigned char max_char = 0;
        
        for (size_t c = 32; c < 127; c++) { // 印刷可能文字
            if (char_frequency[c] > max_count) {
                max_count = char_frequency[c];
                max_char = (unsigned char)c;
            }
        }
        
        if (max_count > 0) {
            printf("  %d位: '%c' (%u回)\n", rank + 1, max_char, max_count);
            char_frequency[max_char] = 0; // 次回検索から除外
        } else {
            break;
        }
    }
}

int main(void)
{
    printf("===== C99学生名管理システム =====\n");
    
    char students[MAX_STUDENTS][MAX_NAME_LENGTH];
    size_t student_count = 0;
    
    // C99: 複合リテラルによる初期データ
    char *initial_students[] = {
        (char[]){"田中太郎"},
        (char[]){"佐藤花子"}, 
        (char[]){"鈴木一郎"},
        (char[]){"高橋二郎"},
        (char[]){"伊藤三子"}
    };
    size_t initial_count = sizeof(initial_students) / sizeof(initial_students[0]);
    
    // 初期データの追加
    display_separator("初期データの追加", '=');
    for (size_t i = 0; i < initial_count; i++) {
        add_student_safe(students, &student_count, initial_students[i], MAX_STUDENTS);
    }
    
    display_students_vla(student_count, students, "初期学生一覧");
    
    // 追加テスト
    display_separator("追加テスト", '=');
    add_student_safe(students, &student_count, "山田花太郎", MAX_STUDENTS);
    add_student_safe(students, &student_count, "田中太郎", MAX_STUDENTS);  // 重複テスト
    add_student_safe(students, &student_count, "", MAX_STUDENTS);  // 空文字列テスト
    
    // 検索テスト
    display_separator("検索テスト", '=');
    
    search_result_t result = search_students_advanced(students, student_count, "田中", true, true);
    if (result.found) {
        printf("\"田中\" の部分一致検索: %zu件見つかりました\n", result.match_count);
    }
    
    result = search_students_advanced(students, student_count, "佐藤花子", false, true);
    if (result.found) {
        printf("\"佐藤花子\" の完全一致: %zu番目に見つかりました\n", result.index + 1);
    } else {
        printf("\"佐藤花子\" は見つかりませんでした\n");
    }
    
    // ソートテスト
    display_separator("ソートテスト", '=');
    sort_students_advanced(students, student_count, false);  // 昇順
    display_students_vla(student_count, students, "昇順ソート後");
    
    sort_students_advanced(students, student_count, true);   // 降順
    display_students_vla(student_count, students, "降順ソート後");
    
    // 削除テスト
    display_separator("削除テスト", '=');
    
    // 名前で削除
    bool success = remove_student_advanced(students, &student_count, REMOVE_BY_NAME, "佐藤花子");
    if (success) {
        display_students_vla(student_count, students, "名前削除後");
    }
    
    // インデックスで削除
    size_t remove_index = 0;
    remove_student_advanced(students, &student_count, REMOVE_BY_INDEX, &remove_index);
    display_students_vla(student_count, students, "インデックス削除後");
    
    // パターンで削除
    remove_student_advanced(students, &student_count, REMOVE_BY_PATTERN, "太郎");
    display_students_vla(student_count, students, "パターン削除後");
    
    // 統計情報
    calculate_statistics(students, student_count);
    
    // 詳細情報システムのデモ
    display_separator("詳細情報システム", '=');
    
    // C99: 指定初期化子による構造体配列初期化
    student_info_t detailed_students[] = {
        {.name = "田中太郎", .id = 1001, .active = true, .gpa = 3.8},
        {.name = "佐藤花子", .id = 1002, .active = true, .gpa = 3.2},
        {.name = "鈴木一郎", .id = 1003, .active = false, .gpa = 2.1},
        {.name = "高橋二郎", .id = 1004, .active = true, .gpa = 3.9}
    };
    size_t detailed_count = sizeof(detailed_students) / sizeof(detailed_students[0]);
    
    display_detailed_students(detailed_students, detailed_count);
    
    // 最終状態
    display_separator("最終状態", '=');
    display_students_vla(student_count, students, "最終学生一覧");
    
    printf("\n✓ システム終了: 現在%zu名の学生が登録されています\n", student_count);
    printf("  最大収容数: %d名\n", MAX_STUDENTS);
    printf("  残り収容可能数: %d名\n", MAX_STUDENTS - (int)student_count);
    
    return 0;
}

/*
C99による学生管理システムの改善点:

1. 型安全性とパフォーマンス:
   - bool型による明確な成功/失敗表現
   - size_t型による適切なサイズ管理
   - inline関数による最適化
   - 固定幅整数型による移植性

2. 可読性と保守性:
   - 構造体による詳細情報管理
   - enum型による操作モード指定
   - 指定初期化子による明確な初期化
   - forループ内変数宣言

3. 柔軟性と機能性:
   - 可変長配列による動的処理
   - 複合リテラルによる一時データ
   - 複数の検索・削除モード
   - 詳細な統計情報

4. 安全性とエラーハンドリング:
   - より詳細なエラーメッセージ
   - バッファオーバーフロー対策
   - NULL ポインタチェック
   - 範囲チェック

5. ユーザビリティ:
   - 視覚的な区切り表示
   - 進捗表示とフィードバック
   - 複数マッチ時の詳細表示
   - 統計情報の提供

実用的な機能追加:
- 大小文字無視検索
- パターンマッチング削除
- 学生詳細情報管理
- 文字使用頻度分析
- 双方向ソート

技術的改善:
- メモリ効率の向上
- 処理速度の最適化
- コードの再利用性
- デバッグの容易さ
- 拡張性の確保
*/
