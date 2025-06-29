/*
 * 文字列操作の基本例（C99版）
 * ファイル名: string_basic_c99.c
 * 説明: C99機能を使った標準ライブラリの文字列操作関数の使用方法を学習
 * C99準拠 - //コメント、bool型、変数宣言位置の自由化、可変長配列
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

// C99: inline関数による最適化
static inline size_t safe_strlen(const char * restrict str)
{
    return (str != NULL) ? strlen(str) : 0;
}

// C99: 可変長配列を使った安全な文字列処理
void demonstrate_vla_strings(int max_length)
{
    char buffer[max_length];  // C99: 可変長配列
    
    printf("\n=== 可変長配列による文字列処理（最大%d文字） ===\n", max_length - 1);
    
    // C99: 複合リテラルによる初期化
    char *sample = (char[]){"Hello, VLA World!"};
    
    if (strlen(sample) < (size_t)max_length) {
        strcpy(buffer, sample);
        printf("VLA buffer: \"%s\"\n", buffer);
        printf("Buffer size: %d bytes\n", max_length);
    } else {
        printf("文字列が長すぎます（%zu > %d）\n", strlen(sample), max_length - 1);
    }
}

int main(void)
{
    printf("===== C99文字列操作の基本例 =====\n");
    
    // C99: 使用箇所での変数宣言
    for (int demo = 1; demo <= 8; demo++) {
        switch (demo) {
        case 1: {
            // 文字列の表現方法
            char str1[] = {'H', 'e', 'l', 'l', 'o', '\0'};
            char str2[] = "Hello";
            char str3[10] = "Hello";
            char *str4 = "Hello";
            
            printf("\n%d. 文字列の表現方法:\n", demo);
            printf("str1: %s\n", str1);
            printf("str2: %s\n", str2);
            printf("str3: %s\n", str3);
            printf("str4: %s\n", str4);
            
            // C99: bool型による明確な判定
            bool strings_equal = (strcmp(str1, str2) == 0);
            printf("str1とstr2は同じ: %s\n", strings_equal ? "true" : "false");
            break;
        }
        
        case 2: {
            // 文字列の長さとサイズ
            char str2[] = "Hello";
            printf("\n%d. 文字列の長さとサイズ:\n", demo);
            printf("文字列: \"%s\"\n", str2);
            printf("strlen(str2): %zu文字\n", strlen(str2));  // C99: %zu指定子
            printf("sizeof(str2): %zu バイト\n", sizeof(str2));
            
            // C99: restrict修飾子による最適化情報
            size_t len = safe_strlen(str2);
            printf("safe_strlen: %zu文字\n", len);
            break;
        }
        
        case 3: {
            // snprintf()による安全な文字列操作（C99）
            printf("\n%d. 安全な文字列操作（C99）:\n", demo);
            char buffer[50];
            
            int result = snprintf(buffer, sizeof(buffer), "Hello, %s! Number: %d", "World", 42);
            printf("フォーマット結果: \"%s\"\n", buffer);
            printf("書き込まれた文字数: %d\n", result);
            
            // バッファが小さい場合のテスト
            char small_buffer[10];
            int overflow_result = snprintf(small_buffer, sizeof(small_buffer), 
                                         "Very long string that will be truncated");
            printf("切り詰められた結果: \"%s\"\n", small_buffer);
            printf("必要だった文字数: %d\n", overflow_result);
            break;
        }
        
        case 4: {
            // 文字列のコピー
            printf("\n%d. 文字列のコピー:\n", demo);
            char source[] = "Hello, World!";
            char destination[50];
            
            strcpy(destination, source);
            printf("destination: %s\n", destination);
            
            // 部分的なコピー（C99の安全な書き方）
            size_t copy_len = 5;
            strncpy(destination, source, copy_len);
            destination[copy_len] = '\0';  // null終端を明示的に追加
            printf("partial copy: %s\n", destination);
            break;
        }
        
        case 5: {
            // 文字列の連結
            printf("\n%d. 文字列の連結:\n", demo);
            char str_a[50] = "Hello";
            char str_b[] = ", World!";
            char str_c[] = " How are you?";
            
            strcat(str_a, str_b);
            printf("After strcat: %s\n", str_a);
            
            // 部分的な連結
            strncat(str_a, str_c, 4);
            printf("After strncat: %s\n", str_a);
            break;
        }
        
        case 6: {
            // 文字列の比較
            printf("\n%d. 文字列の比較:\n", demo);
            char apple[] = "Apple";
            char banana[] = "Banana";
            char apple2[] = "Apple";
            
            int result = strcmp(apple, banana);
            printf("strcmp(\"%s\", \"%s\") = %d\n", apple, banana, result);
            
            // C99: bool型による明確な判定
            bool are_equal = (strcmp(apple, apple2) == 0);
            printf("\"%s\" と \"%s\" は同じ: %s\n", 
                   apple, apple2, are_equal ? "true" : "false");
            
            // 部分比較
            bool first_char_different = (strncmp(apple, banana, 1) != 0);
            printf("最初の文字が異なる: %s\n", 
                   first_char_different ? "true" : "false");
            break;
        }
        
        case 7: {
            // 文字列検索関数
            printf("\n%d. 文字列検索関数:\n", demo);
            char text[] = "Hello, World! Welcome to C programming.";
            
            // 文字の検索
            char *found = strchr(text, 'W');
            if (found != NULL) {
                ptrdiff_t position = found - text;  // C99: ptrdiff_t型
                printf("'W' found at position: %td\n", position);
            }
            
            // 文字列の検索
            found = strstr(text, "World");
            if (found != NULL) {
                printf("\"World\" found at position: %td\n", found - text);
                printf("Found: %s\n", found);
            }
            
            // 最後の文字を検索
            found = strrchr(text, 'o');
            if (found != NULL) {
                printf("Last 'o' at position: %td\n", found - text);
            }
            break;
        }
        
        case 8: {
            // C99: 可変長配列のデモンストレーション
            printf("\n%d. 可変長配列のデモ:\n", demo);
            demonstrate_vla_strings(20);
            demonstrate_vla_strings(50);
            demonstrate_vla_strings(10);  // 短いバッファのテスト
            break;
        }
        }
    }
    
    // C99: 指定初期化子による配列初期化
    printf("\n=== C99指定初期化子のデモ ===\n");
    char vowels[26] = {
        ['a' - 'a'] = 'A',
        ['e' - 'a'] = 'E', 
        ['i' - 'a'] = 'I',
        ['o' - 'a'] = 'O',
        ['u' - 'a'] = 'U'
    };
    
    printf("母音の大文字変換テーブル:\n");
    for (char c = 'a'; c <= 'z'; c++) {
        if (vowels[c - 'a'] != 0) {
            printf("'%c' -> '%c'\n", c, vowels[c - 'a']);
        }
    }
    
    // C99: 複合リテラルと文字列処理
    printf("\n=== 複合リテラルによる文字列処理 ===\n");
    char *messages[] = {
        (char[]){"First message"},
        (char[]){"Second message"},
        (char[]){"Third message"}
    };
    
    for (size_t i = 0; i < sizeof(messages) / sizeof(messages[0]); i++) {
        printf("Message %zu: %s (length: %zu)\n", 
               i + 1, messages[i], strlen(messages[i]));
    }
    
    // C99: 固定幅整数型を使った文字コード処理
    printf("\n=== 固定幅整数型による文字コード処理 ===\n");
    char sample[] = "Hello";
    
    for (size_t i = 0; i < strlen(sample); i++) {
        uint8_t char_code = (uint8_t)sample[i];
        printf("'%c': ASCII %u (0x%02X)\n", sample[i], char_code, char_code);
    }
    
    return 0;
}

/*
C99で追加された機能:
1. 使用箇所での変数宣言:
   - forループ内での変数宣言
   - ブロック内での自由な宣言位置

2. bool型とstdbool.h:
   - true/falseの明確な表現
   - より読みやすい条件判定

3. 可変長配列（VLA）:
   - 実行時に決まるサイズの配列
   - 関数パラメータとしても使用可能

4. restrict修飾子:
   - ポインタの重複なしをコンパイラに伝える
   - 最適化のヒント

5. 複合リテラル:
   - (Type){初期化子}の形式
   - 一時的なオブジェクトの作成

6. 指定初期化子:
   - [index] = valueの形式
   - 配列の特定要素のみを初期化

7. 新しい標準ライブラリ関数:
   - snprintf()による安全な文字列フォーマット
   - より安全な文字列操作

8. 固定幅整数型:
   - uint8_t, int32_tなどの明確なサイズ
   - 移植性の向上

9. 新しいprintf指定子:
   - %zuでsize_t型
   - %tdでptrdiff_t型

注意点:
- VLAは関数スコープでのみ使用可能
- restrict修飾子は最適化のヒントに過ぎない
- 複合リテラルは一時的なオブジェクト
- C99機能の可読性とパフォーマンスのバランス
*/

