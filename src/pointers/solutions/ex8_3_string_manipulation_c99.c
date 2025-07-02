/*
 * ex10_3_string_manipulation_c99.c
 * 
 * 演習8-3: 文字列操作 (C99版)
 * 
 * ポインタを使った文字列操作の実装
 * - カスタムstrlen関数
 * - 文字列逆順関数
 * - 文字列リテラルと文字配列の違い
 * 
 * Author: Claude
 * Date: 2025-06-29
 */

#include <stdio.h>
#include <stdbool.h>  // C99: bool型の使用

// カスタムstrlen関数：ポインタを使って文字列の長さを計算
size_t my_strlen(const char *str) {
    const char *p = str;  // ポインタで文字列の先頭を記憶
    
    // ヌル文字に到達するまでポインタを進める
    while (*p != '\0') {
        p++;
    }
    
    // ポインタの差分が文字列の長さ
    return p - str;
}

// 文字列を逆順にする関数：ポインタを使って実装
void reverse_string(char *str) {
    if (str == NULL) return;  // NULLポインタのチェック
    
    char *start = str;                    // 文字列の先頭ポインタ
    char *end = str + my_strlen(str) - 1; // 文字列の末尾ポインタ
    
    // 先頭と末尾のポインタが交差するまで文字を交換
    while (start < end) {
        // ポインタを使って文字を交換
        char temp = *start;
        *start = *end;
        *end = temp;
        
        // ポインタを内側に移動
        start++;
        end--;
    }
}

// 文字列情報を表示する関数
void print_string_info(const char *label, const char *str) {
    printf("%s: \"%s\"\n", label, str);
    printf("  アドレス: %p\n", (void*)str);
    printf("  長さ: %zu文字\n", my_strlen(str));
}

// 文字列の各文字を詳細表示する関数
void show_string_details(const char *str) {
    printf("文字列 \"%s\" の各文字:\n", str);
    
    for (int i = 0; str[i] != '\0'; i++) {  // C99: forループ内での変数宣言
        printf("  str[%d] = '%c' (アドレス: %p)\n", 
               i, str[i], (void*)&str[i]);
    }
}

// 文字列の変更可能性をテストする関数
bool test_string_mutability(const char *type_name, char *str) {
    printf("%sの変更テスト:\n", type_name);
    printf("  元の文字列: \"%s\"\n", str);
    
    // 最初の文字を大文字に変更してみる
    if (str[0] >= 'a' && str[0] <= 'z') {
        str[0] = str[0] - 'a' + 'A';
        printf("  変更後: \"%s\" (変更成功)\n", str);
        return true;
    } else {
        printf("  (変更対象なし)\n");
        return false;
    }
}

int main(void) {
    // 文字列リテラル（読み取り専用）
    const char *literal = "hello, world!";
    
    // 文字配列（変更可能）
    char array1[] = "c programming";
    char array2[] = "pointer practice";
    char array3[] = "12345";
    char array4[] = "abcdef";
    
    printf("=== 文字列操作のデモンストレーション (C99版) ===\n\n");
    
    // 1. カスタムstrlen関数のテスト
    printf("1. 文字列の長さ計算（my_strlen関数）\n");
    printf("----------------------------------------\n");
    print_string_info("文字列リテラル", literal);
    print_string_info("文字配列1", array1);
    print_string_info("文字配列2", array2);
    print_string_info("文字配列3", array3);
    printf("\n");
    
    // 2. 文字列の変更可能性テスト
    printf("2. 文字列の変更可能性テスト\n");
    printf("----------------------------------------\n");
    
    // 文字列リテラルは変更できないことを説明
    printf("文字列リテラル \"%s\" は読み取り専用のため、\n", literal);
    printf("変更することはできません。\n\n");
    
    // 文字配列の変更テスト
    test_string_mutability("文字配列", array4);
    printf("\n");
    
    // 3. 文字列の逆順処理
    printf("3. 文字列の逆順処理\n");
    printf("----------------------------------------\n");
    
    // 各文字配列を逆順にする
    for (int i = 1; i <= 3; i++) {  // C99: forループ内での変数宣言
        char *current_array;
        
        // 配列の選択
        switch (i) {
            case 1: current_array = array1; break;
            case 2: current_array = array2; break;
            case 3: current_array = array3; break;
            default: continue;
        }
        
        printf("文字配列%dの逆順処理:\n", i);
        printf("  元の文字列: \"%s\"\n", current_array);
        reverse_string(current_array);
        printf("  逆順文字列: \"%s\"\n\n", current_array);
    }
    
    // 4. ポインタ操作の詳細説明
    printf("4. ポインタ操作の仕組み\n");
    printf("----------------------------------------\n");
    show_string_details(array3);
    printf("\n");
    
    // 5. 文字列リテラルと文字配列の違い（詳細版）
    printf("5. 文字列リテラルと文字配列の違い\n");
    printf("----------------------------------------\n");
    
    // 型の違いを示す
    printf("型の違い:\n");
    printf("  文字列リテラル: const char *literal = \"hello\";\n");
    printf("  文字配列: char array[] = \"hello\";\n\n");
    
    // メモリ配置の違い
    printf("メモリ配置:\n");
    printf("  文字列リテラル: 読み取り専用データセグメント\n");
    printf("  文字配列: スタック領域（関数内の場合）\n\n");
    
    // 変更可能性の違い
    printf("変更可能性:\n");
    printf("  文字列リテラル: 読み取り専用（変更不可）\n");
    printf("  文字配列: 変更可能\n\n");
    
    // アドレスの比較
    printf("アドレス情報:\n");
    printf("  literal のアドレス: %p\n", (void*)literal);
    printf("  array1 のアドレス: %p\n", (void*)array1);
    printf("  差分: %td バイト\n", (char*)array1 - (char*)literal);
    
    return 0;
}
