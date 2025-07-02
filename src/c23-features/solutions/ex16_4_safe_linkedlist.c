/**
 * 演習16-4: nullptr安全プログラミング
 * 安全なリンクリスト実装
 * 
 * C23のnullptrを使用して、NULL安全性を重視したリンクリストを実装します。
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ノード構造体 */
typedef struct Node {
    int data;
    struct Node *next;
} Node;

/* リンクリスト構造体 */
typedef struct {
    Node *head;
    size_t size;
} LinkedList;

/* エラーコード */
typedef enum {
    LIST_SUCCESS = 0,
    LIST_ERROR_NULL_POINTER,
    LIST_ERROR_MEMORY_ALLOCATION,
    LIST_ERROR_NOT_FOUND,
    LIST_ERROR_EMPTY_LIST,
    LIST_ERROR_INVALID_INDEX
} ListError;

/* エラーメッセージを取得 */
const char* get_error_message(ListError error)
{
    switch (error) {
        case LIST_SUCCESS:
            return "操作成功";
        case LIST_ERROR_NULL_POINTER:
            return "NULLポインタエラー";
        case LIST_ERROR_MEMORY_ALLOCATION:
            return "メモリ割り当てエラー";
        case LIST_ERROR_NOT_FOUND:
            return "要素が見つかりません";
        case LIST_ERROR_EMPTY_LIST:
            return "リストが空です";
        case LIST_ERROR_INVALID_INDEX:
            return "無効なインデックス";
        default:
            return "未知のエラー";
    }
}

/* リストを初期化 */
ListError list_init(LinkedList **list)
{
    if (list == nullptr) {
        return LIST_ERROR_NULL_POINTER;
    }
    
    *list = (LinkedList *)malloc(sizeof(LinkedList));
    if (*list == nullptr) {
        return LIST_ERROR_MEMORY_ALLOCATION;
    }
    
    (*list)->head = nullptr;
    (*list)->size = 0;
    
    return LIST_SUCCESS;
}

/* ノードを作成 */
static Node* create_node(int data)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node != nullptr) {
        new_node->data = data;
        new_node->next = nullptr;
    }
    return new_node;
}

/* リストの先頭に追加 */
ListError list_push_front(LinkedList *list, int data)
{
    if (list == nullptr) {
        return LIST_ERROR_NULL_POINTER;
    }
    
    Node *new_node = create_node(data);
    if (new_node == nullptr) {
        return LIST_ERROR_MEMORY_ALLOCATION;
    }
    
    new_node->next = list->head;
    list->head = new_node;
    list->size++;
    
    return LIST_SUCCESS;
}

/* リストの末尾に追加 */
ListError list_push_back(LinkedList *list, int data)
{
    if (list == nullptr) {
        return LIST_ERROR_NULL_POINTER;
    }
    
    Node *new_node = create_node(data);
    if (new_node == nullptr) {
        return LIST_ERROR_MEMORY_ALLOCATION;
    }
    
    if (list->head == nullptr) {
        list->head = new_node;
    } else {
        Node *current = list->head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = new_node;
    }
    
    list->size++;
    return LIST_SUCCESS;
}

/* 指定位置に挿入 */
ListError list_insert(LinkedList *list, size_t index, int data)
{
    if (list == nullptr) {
        return LIST_ERROR_NULL_POINTER;
    }
    
    if (index > list->size) {
        return LIST_ERROR_INVALID_INDEX;
    }
    
    if (index == 0) {
        return list_push_front(list, data);
    }
    
    Node *new_node = create_node(data);
    if (new_node == nullptr) {
        return LIST_ERROR_MEMORY_ALLOCATION;
    }
    
    Node *current = list->head;
    for (size_t i = 0; i < index - 1; i++) {
        current = current->next;
    }
    
    new_node->next = current->next;
    current->next = new_node;
    list->size++;
    
    return LIST_SUCCESS;
}

/* 値を検索 */
ListError list_find(const LinkedList *list, int data, size_t *index)
{
    if (list == nullptr || index == nullptr) {
        return LIST_ERROR_NULL_POINTER;
    }
    
    if (list->head == nullptr) {
        return LIST_ERROR_EMPTY_LIST;
    }
    
    Node *current = list->head;
    size_t pos = 0;
    
    while (current != nullptr) {
        if (current->data == data) {
            *index = pos;
            return LIST_SUCCESS;
        }
        current = current->next;
        pos++;
    }
    
    return LIST_ERROR_NOT_FOUND;
}

/* 先頭から削除 */
ListError list_pop_front(LinkedList *list, int *data)
{
    if (list == nullptr) {
        return LIST_ERROR_NULL_POINTER;
    }
    
    if (list->head == nullptr) {
        return LIST_ERROR_EMPTY_LIST;
    }
    
    Node *temp = list->head;
    if (data != nullptr) {
        *data = temp->data;
    }
    
    list->head = list->head->next;
    free(temp);
    list->size--;
    
    return LIST_SUCCESS;
}

/* 値で削除 */
ListError list_remove_value(LinkedList *list, int data)
{
    if (list == nullptr) {
        return LIST_ERROR_NULL_POINTER;
    }
    
    if (list->head == nullptr) {
        return LIST_ERROR_EMPTY_LIST;
    }
    
    /* 先頭要素の場合 */
    if (list->head->data == data) {
        return list_pop_front(list, nullptr);
    }
    
    /* それ以外の要素 */
    Node *current = list->head;
    while (current->next != nullptr && current->next->data != data) {
        current = current->next;
    }
    
    if (current->next == nullptr) {
        return LIST_ERROR_NOT_FOUND;
    }
    
    Node *temp = current->next;
    current->next = temp->next;
    free(temp);
    list->size--;
    
    return LIST_SUCCESS;
}

/* リストを表示 */
void list_display(const LinkedList *list)
{
    if (list == nullptr) {
        printf("Error: リストがnullptrです\n");
        return;
    }
    
    printf("リスト（要素数: %zu）: ", list->size);
    
    if (list->head == nullptr) {
        printf("空\n");
        return;
    }
    
    printf("[ ");
    Node *current = list->head;
    while (current != nullptr) {
        printf("%d", current->data);
        if (current->next != nullptr) {
            printf(" -> ");
        }
        current = current->next;
    }
    printf(" ]\n");
}

/* リストを解放 */
ListError list_destroy(LinkedList **list)
{
    if (list == nullptr || *list == nullptr) {
        return LIST_ERROR_NULL_POINTER;
    }
    
    Node *current = (*list)->head;
    while (current != nullptr) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    
    free(*list);
    *list = nullptr;
    
    return LIST_SUCCESS;
}

/* エラーハンドリングのデモ */
void demonstrate_error_handling(void)
{
    printf("=== エラーハンドリングのデモ ===\n");
    
    LinkedList *list = nullptr;
    ListError error;
    
    /* NULLポインタでの操作を試行 */
    error = list_push_front(nullptr, 10);
    printf("NULLリストへの追加: %s\n", get_error_message(error));
    
    /* リストを初期化 */
    error = list_init(&list);
    printf("リスト初期化: %s\n", get_error_message(error));
    
    /* 空のリストから削除を試行 */
    int value;
    error = list_pop_front(list, &value);
    printf("空リストからの削除: %s\n", get_error_message(error));
    
    /* 存在しない要素の検索 */
    list_push_back(list, 10);
    size_t index;
    error = list_find(list, 20, &index);
    printf("存在しない要素の検索: %s\n", get_error_message(error));
    
    /* 無効なインデックスへの挿入 */
    error = list_insert(list, 10, 30);
    printf("無効なインデックスへの挿入: %s\n", get_error_message(error));
    
    list_destroy(&list);
}

/* 通常操作のデモ */
void demonstrate_normal_operations(void)
{
    printf("\n=== 通常操作のデモ ===\n");
    
    LinkedList *list = nullptr;
    ListError error;
    
    /* リストの作成と初期化 */
    error = list_init(&list);
    if (error != LIST_SUCCESS) {
        printf("初期化エラー: %s\n", get_error_message(error));
        return;
    }
    
    printf("空のリスト: ");
    list_display(list);
    
    /* 要素の追加 */
    printf("\n要素を追加:\n");
    list_push_front(list, 10);
    list_display(list);
    
    list_push_back(list, 20);
    list_display(list);
    
    list_push_front(list, 5);
    list_display(list);
    
    list_insert(list, 2, 15);
    list_display(list);
    
    /* 検索 */
    printf("\n検索テスト:\n");
    size_t index;
    error = list_find(list, 15, &index);
    if (error == LIST_SUCCESS) {
        printf("値15はインデックス%zuにあります\n", index);
    }
    
    /* 削除 */
    printf("\n削除テスト:\n");
    int removed;
    list_pop_front(list, &removed);
    printf("先頭から%dを削除\n", removed);
    list_display(list);
    
    list_remove_value(list, 15);
    printf("値15を削除\n");
    list_display(list);
    
    /* メモリ解放 */
    list_destroy(&list);
    
    /* 解放後のポインタチェック */
    if (list == nullptr) {
        printf("\nリストは正常に解放されました\n");
    }
}

/* ストレステスト */
void stress_test(void)
{
    printf("\n=== ストレステスト ===\n");
    
    LinkedList *list = nullptr;
    list_init(&list);
    
    /* 大量のデータを追加 */
    printf("1000個の要素を追加...\n");
    for (int i = 0; i < 1000; i++) {
        if (i % 2 == 0) {
            list_push_front(list, i);
        } else {
            list_push_back(list, i);
        }
    }
    printf("要素数: %zu\n", list->size);
    
    /* ランダムに削除 */
    printf("500個の要素を削除...\n");
    for (int i = 0; i < 500; i++) {
        int value;
        list_pop_front(list, &value);
    }
    printf("残り要素数: %zu\n", list->size);
    
    /* メモリリークチェック */
    list_destroy(&list);
    printf("メモリを解放しました\n");
}

int main(void)
{
    printf("=== nullptr を使った安全なリンクリスト ===\n\n");
    
    /* エラーハンドリングのデモ */
    demonstrate_error_handling();
    
    /* 通常操作のデモ */
    demonstrate_normal_operations();
    
    /* ストレステスト */
    stress_test();
    
    printf("\nすべてのテストが完了しました\n");
    
    return 0;
}
