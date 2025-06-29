/*
 * ファイル名: nullptr_demo.c
 * 説明: C23のnullptr定数の使用例
 * 規格: C23
 */

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

/* 関数オーバーロードのシミュレーション（Cでは名前を変える） */
void process_int(int value);
void process_ptr(void *ptr);

/* nullptrチェック関数 */
bool is_nullptr(void *ptr)
{
    return ptr == nullptr;
}

/* リンクリストノード */
typedef struct Node {
    int data;
    struct Node *next;
} Node;

int main(void)
{
    printf("=== C23 nullptr定数 ===\n");
    
    /* 基本的な使用法 */
    printf("\n--- 基本的な使用法 ---\n");
    
    int *p1 = nullptr;
    char *p2 = nullptr;
    void *p3 = nullptr;
    
    printf("p1 == nullptr: %s\n", p1 == nullptr ? "true" : "false");
    printf("p2 == nullptr: %s\n", p2 == nullptr ? "true" : "false");
    printf("p3 == nullptr: %s\n", p3 == nullptr ? "true" : "false");
    
    /* NULLとnullptrの比較 */
    printf("\n--- NULLとnullptrの比較 ---\n");
    
    int *old_style = NULL;
    int *new_style = nullptr;
    
    printf("old_style == NULL: %s\n", old_style == NULL ? "true" : "false");
    printf("new_style == nullptr: %s\n", new_style == nullptr ? "true" : "false");
    printf("old_style == new_style: %s\n", old_style == new_style ? "true" : "false");
    
    /* 型安全性の向上 */
    printf("\n--- 型安全性の向上 ---\n");
    
    /* C23では、nullptrは明確にポインタ型 */
    process_ptr(nullptr);    /* OK: nullptrはポインタ */
    /* process_int(nullptr); */ /* エラー: nullptrは整数ではない */
    
    /* 従来のNULLの問題 */
    process_int(0);          /* OK: 0は整数 */
    process_ptr(NULL);       /* OK: NULLはポインタとして扱われる */
    /* process_int(NULL); */ /* 環境依存: NULLが0として定義されている場合は動作 */
    
    /* 関数での使用 */
    printf("\n--- 関数での使用 ---\n");
    
    void *ptr1 = malloc(100);
    void *ptr2 = nullptr;
    
    printf("ptr1 is nullptr: %s\n", is_nullptr(ptr1) ? "true" : "false");
    printf("ptr2 is nullptr: %s\n", is_nullptr(ptr2) ? "true" : "false");
    
    free(ptr1);
    
    /* リンクリストでの使用 */
    printf("\n--- リンクリストでの使用 ---\n");
    
    Node *head = nullptr;
    Node *current = nullptr;
    
    /* ノードの追加 */
    for (int i = 1; i <= 3; i++) {
        Node *new_node = malloc(sizeof(Node));
        if (new_node != nullptr) {
            new_node->data = i;
            new_node->next = nullptr;
            
            if (head == nullptr) {
                head = new_node;
                current = head;
            } else {
                current->next = new_node;
                current = new_node;
            }
        }
    }
    
    /* リストの表示 */
    printf("リスト: ");
    for (Node *node = head; node != nullptr; node = node->next) {
        printf("%d ", node->data);
    }
    printf("\n");
    
    /* メモリ解放 */
    while (head != nullptr) {
        Node *temp = head;
        head = head->next;
        free(temp);
    }
    
    /* 条件式での使用 */
    printf("\n--- 条件式での使用 ---\n");
    
    char *str = nullptr;
    
    if (str == nullptr) {
        printf("文字列は初期化されていません\n");
    }
    
    str = "Hello, C23!";
    
    if (str != nullptr) {
        printf("文字列: %s\n", str);
    }
    
    /* マクロでの使用 */
    printf("\n--- マクロでの使用 ---\n");
    
    #define SAFE_FREE(ptr) do { \
        if ((ptr) != nullptr) { \
            free(ptr); \
            (ptr) = nullptr; \
        } \
    } while(0)
    
    int *dynamic = malloc(sizeof(int));
    *dynamic = 42;
    printf("解放前: dynamic = %p\n", (void*)dynamic);
    
    SAFE_FREE(dynamic);
    printf("解放後: dynamic = %p (nullptr)\n", (void*)dynamic);
    
    return 0;
}


/* 関数の実装 */
void process_int(int value)
{
    printf("整数値を処理: %d\n", value);
}

void process_ptr(void *ptr)
{
    printf("ポインタを処理: %p\n", ptr);
}

/*
 * 実行結果例:
 * === C23 nullptr定数 ===
 * 
 * --- 基本的な使用法 ---
 * p1 == nullptr: true
 * p2 == nullptr: true
 * p3 == nullptr: true
 * 
 * --- NULLとnullptrの比較 ---
 * old_style == NULL: true
 * new_style == nullptr: true
 * old_style == new_style: true
 * 
 * --- 型安全性の向上 ---
 * ポインタを処理: 0x0
 * 整数値を処理: 0
 * ポインタを処理: 0x0
 * 
 * --- 関数での使用 ---
 * ptr1 is nullptr: false
 * ptr2 is nullptr: true
 * 
 * --- リンクリストでの使用 ---
 * リスト: 1 2 3 
 * 
 * --- 条件式での使用 ---
 * 文字列は初期化されていません
 * 文字列: Hello, C23!
 * 
 * --- マクロでの使用 ---
 * 解放前: dynamic = 0x1234abcd
 * 解放後: dynamic = 0x0 (nullptr)
 */