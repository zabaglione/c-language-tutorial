/*
 * ex10_3_string_manipulation.c
 * 
 * 演習10-3: 文字列操作
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

/* カスタムstrlen関数：ポインタを使って文字列の長さを計算 */
size_t my_strlen(const char *str) {
    const char *p = str;  /* ポインタで文字列の先頭を記憶 */
    
    /* ヌル文字に到達するまでポインタを進める */
    while (*p != '\0') {
        p++;
    }
    
    /* ポインタの差分が文字列の長さ */
    return p - str;
}

/* 文字列を逆順にする関数：ポインタを使って実装 */
void reverse_string(char *str) {
    char *start = str;                    /* 文字列の先頭ポインタ */
    char *end = str + my_strlen(str) - 1; /* 文字列の末尾ポインタ */
    char temp;
    
    /* 先頭と末尾のポインタが交差するまで文字を交換 */
    while (start < end) {
        /* ポインタを使って文字を交換 */
        temp = *start;
        *start = *end;
        *end = temp;
        
        /* ポインタを内側に移動 */
        start++;
        end--;
    }
}

/* 文字列情報を表示する関数 */
void print_string_info(const char *label, const char *str) {
    printf("%s: \"%s\"\n", label, str);
    printf("  アドレス: %p\n", (void*)str);
    printf("  長さ: %zu文字\n", my_strlen(str));
}

int main(void) {
    /* 文字列リテラル（読み取り専用） */
    const char *literal = "Hello, World!";
    
    /* 文字配列（変更可能） */
    char array1[] = "C Programming";
    char array2[] = "Pointer Practice";
    char array3[] = "12345";
    
    printf("=== 文字列操作のデモンストレーション ===\n\n");
    
    /* 1. カスタムstrlen関数のテスト */
    printf("1. 文字列の長さ計算（my_strlen関数）\n");
    printf("----------------------------------------\n");
    print_string_info("文字列リテラル", literal);
    print_string_info("文字配列1", array1);
    print_string_info("文字配列2", array2);
    print_string_info("文字配列3", array3);
    printf("\n");
    
    /* 2. 文字列の逆順処理 */
    printf("2. 文字列の逆順処理\n");
    printf("----------------------------------------\n");
    
    /* 文字列リテラルは変更できないことを説明 */
    printf("文字列リテラル \"%s\" は読み取り専用のため、\n", literal);
    printf("逆順にすることはできません。\n\n");
    
    /* 文字配列は変更可能 */
    printf("文字配列1の逆順処理:\n");
    printf("  元の文字列: \"%s\"\n", array1);
    reverse_string(array1);
    printf("  逆順文字列: \"%s\"\n\n", array1);
    
    printf("文字配列2の逆順処理:\n");
    printf("  元の文字列: \"%s\"\n", array2);
    reverse_string(array2);
    printf("  逆順文字列: \"%s\"\n\n", array2);
    
    printf("文字配列3の逆順処理:\n");
    printf("  元の文字列: \"%s\"\n", array3);
    reverse_string(array3);
    printf("  逆順文字列: \"%s\"\n\n", array3);
    
    /* 3. ポインタ操作の詳細説明 */
    printf("3. ポインタ操作の仕組み\n");
    printf("----------------------------------------\n");
    
    /* 文字列をポインタで走査する例 */
    {
        const char *p;
        int count = 0;
        
        printf("文字列 \"%s\" の各文字:\n", array3);
        for (p = array3; *p != '\0'; p++) {
            printf("  array3[%d] = '%c' (アドレス: %p)\n", 
                   count, *p, (void*)p);
            count++;
        }
    }
    
    printf("\n");
    
    /* 4. 文字列リテラルと文字配列の違い */
    printf("4. 文字列リテラルと文字配列の違い\n");
    printf("----------------------------------------\n");
    printf("文字列リテラル:\n");
    printf("  - const char *型で宣言\n");
    printf("  - 読み取り専用メモリに配置\n");
    printf("  - 変更しようとするとエラー\n\n");
    
    printf("文字配列:\n");
    printf("  - char array[]型で宣言\n");
    printf("  - スタック上に配置\n");
    printf("  - 変更可能\n");
    
    return 0;
}
