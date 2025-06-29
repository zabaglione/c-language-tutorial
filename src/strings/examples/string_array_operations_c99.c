/*
 * 文字列配列の実践例（C99版）
 * ファイル名: string_array_operations_c99.c
 * 説明: C99機能を使った二次元文字配列と文字列ポインタ配列の操作
 * C99準拠 - 可変長配列、複合リテラル、指定初期化子、restrict修飾子
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX_STRINGS 5
#define MAX_LENGTH 20

// C99: inline関数による効率的な文字列配列操作
static inline void print_string_array(char arr[][MAX_LENGTH], size_t count, const char *title)
{
    printf("=== %s ===\n", title);
    for (size_t i = 0; i < count; i++) {
        printf("%zu. %s\n", i + 1, arr[i]);
    }
}

// C99: restrict修飾子による最適化された文字列コピー
void safe_string_copy(char * restrict dest, const char * restrict src, size_t dest_size)
{
    if (dest != NULL && src != NULL && dest_size > 0) {
        strncpy(dest, src, dest_size - 1);
        dest[dest_size - 1] = '\0';
    }
}

// C99: 可変長配列を使った動的文字列配列処理
void demonstrate_vla_string_array(size_t array_size, size_t string_length)
{
    printf("\n=== 可変長配列による文字列配列（%zu x %zu） ===\n", 
           array_size, string_length);
    
    char vla_strings[array_size][string_length];  // C99: 可変長配列
    
    // 初期化
    for (size_t i = 0; i < array_size; i++) {
        snprintf(vla_strings[i], string_length, "VLA String %zu", i + 1);
    }
    
    // 表示
    for (size_t i = 0; i < array_size; i++) {
        printf("  %zu: %s (max %zu chars)\n", i + 1, vla_strings[i], string_length - 1);
    }
    
    printf("Total memory: %zu bytes\n", array_size * string_length);
}

int main(void)
{
    printf("===== C99文字列配列の実践例 =====\n");
    
    // C99: 指定初期化子による二次元配列の初期化
    char languages[MAX_STRINGS][MAX_LENGTH] = {
        [0] = "C",
        [1] = "Python", 
        [2] = "Java",
        [3] = "JavaScript",
        [4] = "C++"
    };
    size_t lang_count = MAX_STRINGS;
    
    print_string_array(languages, lang_count, "プログラミング言語一覧（指定初期化子）");
    
    // 文字列の変更
    safe_string_copy(languages[0], "C言語", MAX_LENGTH);
    printf("\n変更後の1番目: %s\n", languages[0]);
    
    // C99: 複合リテラルによる文字列ポインタ配列
    printf("\n=== 複合リテラルによる文字列配列 ===\n");
    char **fruits = (char*[]){
        (char[]){"Apple"},
        (char[]){"Banana"}, 
        (char[]){"Cherry"},
        (char[]){"Date"},
        (char[]){"Elderberry"},
        NULL  // 終端マーカー
    };
    
    // NULL終端までカウント
    size_t fruit_count = 0;
    while (fruits[fruit_count] != NULL) {
        fruit_count++;
    }
    
    printf("果物一覧（複合リテラル）:\n");
    for (size_t i = 0; i < fruit_count; i++) {
        printf("%zu. %s (長さ: %zu)\n", i + 1, fruits[i], strlen(fruits[i]));
    }
    
    // C99: forループ内での変数宣言と複合リテラル
    printf("\n=== 動的メニューシステム ===\n");
    struct {
        char item[MAX_LENGTH];
        char category[MAX_LENGTH];
        bool available;
        double price;
    } menu[] = {
        {"サラダ", "前菜", true, 800.0},
        {"ステーキ", "メイン", true, 2500.0},
        {"アイスクリーム", "デザート", false, 500.0},
        {"コーヒー", "飲み物", true, 400.0}
    };
    size_t menu_count = sizeof(menu) / sizeof(menu[0]);
    
    printf("=== レストランメニュー ===\n");
    for (size_t i = 0; i < menu_count; i++) {
        printf("[%s] %s - %.0f円 %s\n", 
               menu[i].category, 
               menu[i].item, 
               menu[i].price,
               menu[i].available ? "(利用可能)" : "(売り切れ)");
    }
    
    // 利用可能な項目のみを表示
    printf("\n利用可能な項目:\n");
    for (size_t i = 0; i < menu_count; i++) {
        if (menu[i].available) {
            printf("  - %s (%s)\n", menu[i].item, menu[i].category);
        }
    }
    
    // C99: 可変長配列のデモンストレーション
    for (int demo_size = 3; demo_size <= 7; demo_size += 2) {
        demonstrate_vla_string_array(demo_size, 15);
    }
    
    // メモリ使用量の詳細比較
    printf("\n=== メモリ使用量の詳細比較 ===\n");
    
    // 二次元文字配列
    char matrix_strings[5][20] = {
        "Cat", "Dog", "Bird", "Fish", "Rabbit"
    };
    
    // 文字列ポインタ配列（C99複合リテラル）
    char *pointer_strings[] = {
        (char[]){"Cat"}, 
        (char[]){"Dog"}, 
        (char[]){"Bird"}, 
        (char[]){"Fish"}, 
        (char[]){"Rabbit"}
    };
    
    printf("二次元文字配列: %zu バイト\n", sizeof(matrix_strings));
    printf("文字列ポインタ配列: %zu バイト\n", sizeof(pointer_strings));
    
    // 実際の使用量計算
    size_t actual_usage = 0;
    for (size_t i = 0; i < 5; i++) {
        actual_usage += strlen(matrix_strings[i]) + 1;  // +1 for null terminator
    }
    printf("実際の文字列データ: %zu バイト\n", actual_usage);
    printf("無駄なメモリ（二次元配列）: %zu バイト\n", 
           sizeof(matrix_strings) - actual_usage);
    
    // C99: 効率的なメモリ使用パターン
    printf("\n=== 効率的なメモリ使用パターン（C99） ===\n");
    
    // 文字列長に応じた動的配列サイズ
    char *efficient_strings[] = {
        (char[4]){"Cat"},     // 正確なサイズ
        (char[4]){"Dog"},     // 正確なサイズ  
        (char[5]){"Bird"},    // 正確なサイズ
        (char[5]){"Fish"},    // 正確なサイズ
        (char[7]){"Rabbit"}   // 正確なサイズ
    };
    
    size_t efficient_total = 0;
    for (size_t i = 0; i < 5; i++) {
        size_t len = strlen(efficient_strings[i]);
        printf("%s: %zu文字（実際の配列サイズ: 適切）\n", 
               efficient_strings[i], len);
        efficient_total += len + 1;
    }
    printf("効率的パターンの総使用量: %zu バイト\n", efficient_total);
    
    // C99: 文字列処理の統計情報
    printf("\n=== 文字列処理統計（C99機能使用） ===\n");
    
    struct string_stats {
        size_t total_chars;
        size_t total_strings;
        size_t min_length;
        size_t max_length;
        double avg_length;
    } stats = {0, 0, SIZE_MAX, 0, 0.0};
    
    // 統計計算
    for (size_t i = 0; i < 5; i++) {
        size_t len = strlen(matrix_strings[i]);
        stats.total_chars += len;
        stats.total_strings++;
        
        if (len < stats.min_length) stats.min_length = len;
        if (len > stats.max_length) stats.max_length = len;
    }
    stats.avg_length = (double)stats.total_chars / stats.total_strings;
    
    printf("文字列数: %zu\n", stats.total_strings);
    printf("総文字数: %zu\n", stats.total_chars);
    printf("平均文字数: %.1f\n", stats.avg_length);
    printf("最短文字数: %zu\n", stats.min_length);
    printf("最長文字数: %zu\n", stats.max_length);
    
    // C99: 固定幅整数型による文字コード分析
    printf("\n=== 文字コード分析（固定幅整数型使用） ===\n");
    
    char sample[] = "Hello";
    uint32_t char_sum = 0;
    
    printf("文字コード詳細:\n");
    for (size_t i = 0; i < strlen(sample); i++) {
        uint8_t code = (uint8_t)sample[i];
        char_sum += code;
        printf("  '%c': %3u (0x%02X)\n", sample[i], code, code);
    }
    printf("文字コード合計: %u\n", char_sum);
    printf("平均文字コード: %.1f\n", (double)char_sum / strlen(sample));
    
    return 0;
}

/*
C99で追加された文字列配列機能:
1. 可変長配列（VLA）:
   - 実行時サイズ決定の配列
   - 関数パラメータとしても使用可能
   - メモリ効率的な処理

2. 複合リテラル:
   - (Type){初期化子}による一時オブジェクト
   - 動的な配列初期化
   - 関数引数としても使用可能

3. 指定初期化子:
   - [index] = valueによる特定要素初期化
   - より明確な初期化コード
   - 大きな配列での部分初期化

4. restrict修飾子:
   - ポインタの重複なしをコンパイラに通知
   - 最適化のヒント
   - 文字列操作の高速化

5. bool型:
   - より明確な真偽値表現
   - 条件判定の可読性向上

6. 固定幅整数型:
   - uint8_t, uint32_tなどの明確なサイズ
   - 文字コード処理での型安全性

7. 新しいprintf指定子:
   - %zuでsize_t型
   - より安全な出力

8. inline関数:
   - 関数呼び出しオーバーヘッドの削減
   - 小さな関数の最適化

実用的な改善点:
- メモリ効率の向上
- 型安全性の強化
- コードの可読性向上
- デバッグの容易さ
- 移植性の向上

注意点:
- VLAはスタック上に確保される
- 複合リテラルのライフタイム管理
- restrict修飾子の正しい使用
- C99対応コンパイラが必要
*/
