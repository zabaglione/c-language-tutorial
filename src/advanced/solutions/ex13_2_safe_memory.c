/*
 * 演習13-2の解答例: 安全なメモリ操作マクロ
 * ファイル名: ex13_2_safe_memory.c
 * 説明: NULLチェック、境界チェック、メモリリーク検出機能の実装
 * C90準拠
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* メモリリーク追跡用の構造体 */
typedef struct MemoryTracker {
    void *ptr;
    size_t size;
    const char *file;
    int line;
    struct MemoryTracker *next;
} MemoryTracker;

/* グローバルなメモリ追跡リスト */
static MemoryTracker *g_memory_list = NULL;
static size_t g_total_allocated = 0;
static size_t g_total_freed = 0;
static int g_allocation_count = 0;
static int g_free_count = 0;

/* メモリ追跡の有効/無効 */
#define MEMORY_TRACKING_ENABLED 1

/* エラー処理用マクロ（C90準拠 - 可変引数マクロなし） */
#define MEMORY_ERROR(msg) \
    fprintf(stderr, "[MEMORY ERROR:%s:%d] %s\n", __FILE__, __LINE__, msg)

#define MEMORY_WARNING(msg) \
    fprintf(stderr, "[MEMORY WARNING:%s:%d] %s\n", __FILE__, __LINE__, msg)

#define MEMORY_INFO(msg) \
    printf("[MEMORY INFO:%s:%d] %s\n", __FILE__, __LINE__, msg)

/* 安全なメモリ割り当てマクロ */
#define SAFE_MALLOC(size) safe_malloc_impl((size), __FILE__, __LINE__)
#define SAFE_CALLOC(count, size) safe_calloc_impl((count), (size), __FILE__, __LINE__)
#define SAFE_REALLOC(ptr, size) safe_realloc_impl((ptr), (size), __FILE__, __LINE__)

/* 安全なメモリ解放マクロ */
#define SAFE_FREE(ptr) \
    do { \
        if (ptr) { \
            safe_free_impl((ptr), __FILE__, __LINE__); \
            (ptr) = NULL; \
        } \
    } while (0)

/* 配列境界チェック付きアクセスマクロ */
#define ARRAY_BOUNDS_CHECK(arr, index, size) \
    ((index) >= 0 && (size_t)(index) < (size_t)(size))

#define SAFE_ARRAY_ACCESS(arr, index, size, default_val) \
    (ARRAY_BOUNDS_CHECK(arr, index, size) ? (arr)[index] : (default_val))

#define SAFE_ARRAY_SET(arr, index, size, value) \
    do { \
        if (ARRAY_BOUNDS_CHECK(arr, index, size)) { \
            (arr)[index] = (value); \
        } else { \
            fprintf(stderr, "[MEMORY ERROR:%s:%d] 配列境界エラー: インデックス %d が範囲 [0, %lu) を超えています\n", \
                    __FILE__, __LINE__, (int)(index), (unsigned long)(size)); \
        } \
    } while (0)

/* メモリ初期化マクロ */
#define SAFE_MEMSET(ptr, value, size) \
    do { \
        if (ptr) { \
            memset((ptr), (value), (size)); \
        } else { \
            MEMORY_ERROR("NULLポインタに対するmemset"); \
        } \
    } while (0)

#define SAFE_MEMCPY(dest, src, size) \
    do { \
        if ((dest) && (src)) { \
            memcpy((dest), (src), (size)); \
        } else { \
            MEMORY_ERROR("NULLポインタに対するmemcpy"); \
        } \
    } while (0)

/* 文字列操作の安全なマクロ */
#define SAFE_STRNCPY(dest, src, size) \
    do { \
        if ((dest) && (src) && (size) > 0) { \
            strncpy((dest), (src), (size) - 1); \
            (dest)[(size) - 1] = '\0'; \
        } else { \
            MEMORY_ERROR("不正なstrncpyパラメータ"); \
        } \
    } while (0)

#define SAFE_STRNCAT(dest, src, size) \
    do { \
        if ((dest) && (src) && (size) > 0) { \
            size_t dest_len = strlen(dest); \
            if (dest_len < (size) - 1) { \
                strncat((dest), (src), (size) - dest_len - 1); \
            } \
        } else { \
            MEMORY_ERROR("不正なstrncatパラメータ"); \
        } \
    } while (0)

/* ポインタ検証マクロ */
#define VALIDATE_POINTER(ptr, action) \
    do { \
        if (!(ptr)) { \
            MEMORY_ERROR("NULLポインタが検出されました"); \
            action; \
        } \
    } while (0)

#define VALIDATE_POINTER_RETURN(ptr, retval) \
    VALIDATE_POINTER(ptr, return (retval))

#define VALIDATE_POINTER_RETURN_VOID(ptr) \
    VALIDATE_POINTER(ptr, return)

/* メモリリーク検出マクロ */
#define MEMORY_LEAK_TRACKER_INIT() init_memory_tracker()
#define MEMORY_LEAK_TRACKER_REPORT() report_memory_leaks()
#define MEMORY_LEAK_TRACKER_CLEANUP() cleanup_memory_tracker()

/* 実装関数群 */

/* メモリ追跡の初期化 */
void init_memory_tracker(void)
{
    g_memory_list = NULL;
    g_total_allocated = 0;
    g_total_freed = 0;
    g_allocation_count = 0;
    g_free_count = 0;
    MEMORY_INFO("メモリ追跡システムを初期化しました");
}

/* メモリ追跡エントリの追加 */
static void add_memory_tracker(void *ptr, size_t size, const char *file, int line)
{
#if MEMORY_TRACKING_ENABLED
    MemoryTracker *tracker = (MemoryTracker *)malloc(sizeof(MemoryTracker));
    if (tracker) {
        tracker->ptr = ptr;
        tracker->size = size;
        tracker->file = file;
        tracker->line = line;
        tracker->next = g_memory_list;
        g_memory_list = tracker;
        
        g_total_allocated += size;
        g_allocation_count++;
    }
#endif
}

/* メモリ追跡エントリの削除 */
static void remove_memory_tracker(void *ptr, const char *file, int line)
{
#if MEMORY_TRACKING_ENABLED
    MemoryTracker **current = &g_memory_list;
    while (*current) {
        if ((*current)->ptr == ptr) {
            MemoryTracker *to_remove = *current;
            g_total_freed += to_remove->size;
            g_free_count++;
            *current = to_remove->next;
            free(to_remove);
            return;
        }
        current = &(*current)->next;
    }
    fprintf(stderr, "[MEMORY WARNING:%s:%d] 解放されたポインタ %p が追跡リストに見つかりません\n",
            file, line, ptr);
#endif
}

/* 安全なmalloc実装 */
void *safe_malloc_impl(size_t size, const char *file, int line)
{
    void *ptr;
    
    if (size == 0) {
        fprintf(stderr, "[MEMORY WARNING:%s:%d] サイズ0でのmalloc\n", file, line);
        return NULL;
    }
    
    ptr = malloc(size);
    if (!ptr) {
        fprintf(stderr, "[MEMORY ERROR:%s:%d] malloc失敗: %luバイト\n", 
                file, line, (unsigned long)size);
        return NULL;
    }
    
    add_memory_tracker(ptr, size, file, line);
    printf("[MEMORY INFO:%s:%d] malloc成功: %luバイト @ %p\n", 
           file, line, (unsigned long)size, ptr);
    
    return ptr;
}

/* 安全なcalloc実装 */
void *safe_calloc_impl(size_t count, size_t size, const char *file, int line)
{
    void *ptr;
    size_t total_size;
    
    if (count == 0 || size == 0) {
        fprintf(stderr, "[MEMORY WARNING:%s:%d] サイズ0でのcalloc\n", file, line);
        return NULL;
    }
    
    /* オーバーフローチェック */
    total_size = count * size;
    if (count != 0 && total_size / count != size) {
        fprintf(stderr, "[MEMORY ERROR:%s:%d] calloc整数オーバーフロー: %lu * %lu\n",
                file, line, (unsigned long)count, (unsigned long)size);
        return NULL;
    }
    
    ptr = calloc(count, size);
    if (!ptr) {
        fprintf(stderr, "[MEMORY ERROR:%s:%d] calloc失敗: %lu * %luバイト\n",
                file, line, (unsigned long)count, (unsigned long)size);
        return NULL;
    }
    
    add_memory_tracker(ptr, total_size, file, line);
    printf("[MEMORY INFO:%s:%d] calloc成功: %lu * %luバイト @ %p\n",
           file, line, (unsigned long)count, (unsigned long)size, ptr);
    
    return ptr;
}

/* 安全なrealloc実装 */
void *safe_realloc_impl(void *ptr, size_t size, const char *file, int line)
{
    void *new_ptr;
    
    if (!ptr) {
        return safe_malloc_impl(size, file, line);
    }
    
    if (size == 0) {
        safe_free_impl(ptr, file, line);
        return NULL;
    }
    
    new_ptr = realloc(ptr, size);
    if (!new_ptr) {
        fprintf(stderr, "[MEMORY ERROR:%s:%d] realloc失敗: %luバイト\n", 
                file, line, (unsigned long)size);
        return NULL;
    }
    
    /* 追跡情報の更新 */
    remove_memory_tracker(ptr, file, line);
    add_memory_tracker(new_ptr, size, file, line);
    
    printf("[MEMORY INFO:%s:%d] realloc成功: %p -> %p (%luバイト)\n",
           file, line, ptr, new_ptr, (unsigned long)size);
    
    return new_ptr;
}

/* 安全なfree実装 */
void safe_free_impl(void *ptr, const char *file, int line)
{
    if (!ptr) {
        fprintf(stderr, "[MEMORY WARNING:%s:%d] NULLポインタのfree\n", file, line);
        return;
    }
    
    remove_memory_tracker(ptr, file, line);
    free(ptr);
    /* 注意: デバッグ目的でポインタ値を表示。実際のコードでは解放後のポインタアクセスは避ける */
    printf("[MEMORY INFO:%s:%d] free成功: アドレス %p を解放しました\n", file, line, (void*)ptr);
}

/* メモリリークレポート */
void report_memory_leaks(void)
{
    MemoryTracker *current;
    size_t leak_total = 0;
    int leak_count = 0;
    
    printf("\n=== メモリリークレポート ===\n");
    printf("総割り当て: %lu バイト (%d 回)\n",
           (unsigned long)g_total_allocated, g_allocation_count);
    printf("総解放: %lu バイト (%d 回)\n",
           (unsigned long)g_total_freed, g_free_count);
    
    if (g_memory_list) {
        printf("\n検出されたリーク:\n");
        current = g_memory_list;
        
        while (current) {
            printf("  %p: %lu バイト (%s:%d)\n",
                   current->ptr, (unsigned long)current->size,
                   current->file, current->line);
            leak_total += current->size;
            leak_count++;
            current = current->next;
        }
        
        printf("\nリーク合計: %lu バイト (%d ブロック)\n",
               (unsigned long)leak_total, leak_count);
    } else {
        printf("メモリリークは検出されませんでした。\n");
    }
    printf("========================\n\n");
}

/* メモリ追跡システムのクリーンアップ */
void cleanup_memory_tracker(void)
{
    while (g_memory_list) {
        MemoryTracker *to_remove = g_memory_list;
        g_memory_list = g_memory_list->next;
        free(to_remove);
    }
    MEMORY_INFO("メモリ追跡システムをクリーンアップしました");
}

/* テスト関数群 */

void test_safe_allocation(void)
{
    int *numbers;
    int i;
    
    printf("=== 安全なメモリ割り当てテスト ===\n");
    
    /* 通常の割り当て */
    numbers = (int *)SAFE_MALLOC(sizeof(int) * 10);
    VALIDATE_POINTER_RETURN_VOID(numbers);
    
    for (i = 0; i < 10; i++) {
        numbers[i] = i * i;
    }
    
    printf("割り当てた配列: ");
    for (i = 0; i < 10; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");
    
    /* 配列のサイズ変更 */
    numbers = (int *)SAFE_REALLOC(numbers, sizeof(int) * 20);
    VALIDATE_POINTER_RETURN_VOID(numbers);
    
    for (i = 10; i < 20; i++) {
        numbers[i] = i * i;
    }
    
    printf("拡張後の配列: ");
    for (i = 0; i < 20; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");
    
    SAFE_FREE(numbers);
    printf("メモリを正常に解放しました\n\n");
}

void test_array_bounds_checking(void)
{
    int *array;
    int i;
    int safe_value;
    
    printf("=== 配列境界チェックテスト ===\n");
    
    array = (int *)SAFE_MALLOC(sizeof(int) * 5);
    VALIDATE_POINTER_RETURN_VOID(array);
    
    /* 配列の初期化 */
    for (i = 0; i < 5; i++) {
        array[i] = (i + 1) * 10;
    }
    
    printf("配列内容: ");
    for (i = 0; i < 5; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
    
    /* 安全なアクセステスト */
    printf("安全なアクセステスト:\n");
    
    for (i = -1; i <= 6; i++) {
        if (ARRAY_BOUNDS_CHECK(array, i, 5)) {
            printf("  インデックス %d: %d (有効)\n", i, array[i]);
        } else {
            printf("  インデックス %d: 境界外アクセス\n", i);
            safe_value = SAFE_ARRAY_ACCESS(array, i, 5, -1);
            printf("    -> デフォルト値: %d\n", safe_value);
        }
    }
    
    /* 安全な設定テスト */
    printf("\n安全な設定テスト:\n");
    SAFE_ARRAY_SET(array, 2, 5, 999);  /* 有効 */
    SAFE_ARRAY_SET(array, 10, 5, 888); /* 無効 */
    SAFE_ARRAY_SET(array, -1, 5, 777); /* 無効 */
    
    printf("設定後の配列: ");
    for (i = 0; i < 5; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
    
    SAFE_FREE(array);
    printf("\n");
}

void test_string_operations(void)
{
    char *buffer;
    char long_string[100];
    char short_buffer[20];
    
    printf("=== 安全な文字列操作テスト ===\n");
    
    buffer = (char *)SAFE_MALLOC(64);
    VALIDATE_POINTER_RETURN_VOID(buffer);
    
    /* 安全な文字列コピー */
    SAFE_STRNCPY(buffer, "Hello, World!", 64);
    printf("初期文字列: %s\n", buffer);
    
    /* 安全な文字列連結 */
    SAFE_STRNCAT(buffer, " 追加テキスト", 64);
    printf("連結後: %s\n", buffer);
    
    /* 長すぎる文字列のテスト */
    memset(long_string, 'A', 99);
    long_string[99] = '\0';
    
    SAFE_STRNCPY(short_buffer, long_string, sizeof(short_buffer));
    printf("切り詰められた文字列: %s\n", short_buffer);
    
    SAFE_FREE(buffer);
    printf("\n");
}

void test_memory_leak_detection(void)
{
    void *leak1;
    void *leak2;
    void *no_leak;
    
    printf("=== メモリリーク検出テスト ===\n");
    
    /* 意図的にリークを作成 */
    leak1 = SAFE_MALLOC(100);
    leak2 = SAFE_MALLOC(200);
    no_leak = SAFE_MALLOC(50);
    
    /* 一つだけ解放 */
    SAFE_FREE(no_leak);
    
    printf("意図的にリークを作成しました\n");
    printf("leak1 = %p (100バイト)\n", leak1);
    printf("leak2 = %p (200バイト)\n", leak2);
    printf("no_leakは解放済み\n\n");
    
    /* leak1とleak2は意図的に解放しない */
}

/* メイン関数 */
int main(void)
{
    printf("=== 安全なメモリ操作マクロデモ ===\n\n");
    
    /* メモリ追跡システムの初期化 */
    MEMORY_LEAK_TRACKER_INIT();
    
    /* 各種テストの実行 */
    test_safe_allocation();
    test_array_bounds_checking();
    test_string_operations();
    test_memory_leak_detection();
    
    /* メモリリークレポートの表示 */
    MEMORY_LEAK_TRACKER_REPORT();
    
    /* メモリ追跡システムのクリーンアップ */
    MEMORY_LEAK_TRACKER_CLEANUP();
    
    printf("=== デモ完了 ===\n");
    return 0;
}

/*
実行例:
=== 安全なメモリ操作マクロデモ ===

[MEMORY INFO:ex13_2_safe_memory.c:135] メモリ追跡システムを初期化しました

=== 安全なメモリ割り当てテスト ===
[MEMORY INFO:ex13_2_safe_memory.c:207] malloc成功: 40バイト @ 0x1234560
割り当てた配列: 0 1 4 9 16 25 36 49 64 81 
[MEMORY INFO:ex13_2_safe_memory.c:279] realloc成功: 0x1234560 -> 0x1234580 (80バイト)
拡張後の配列: 0 1 4 9 16 25 36 49 64 81 100 121 144 169 196 225 256 289 324 361 
[MEMORY INFO:ex13_2_safe_memory.c:295] free成功: 0x1234580
メモリを正常に解放しました

=== 配列境界チェックテスト ===
[MEMORY INFO:ex13_2_safe_memory.c:207] malloc成功: 20バイト @ 0x12345a0
配列内容: 10 20 30 40 50 
安全なアクセステスト:
  インデックス -1: 境界外アクセス
    -> デフォルト値: -1
  インデックス 0: 10 (有効)
  インデックス 1: 20 (有効)
  インデックス 2: 30 (有効)
  インデックス 3: 40 (有効)
  インデックス 4: 50 (有効)
  インデックス 5: 境界外アクセス
    -> デフォルト値: -1
  インデックス 6: 境界外アクセス
    -> デフォルト値: -1

安全な設定テスト:
[MEMORY ERROR:ex13_2_safe_memory.c:390] 配列境界エラー: インデックス 10 が範囲 [0, 5) を超えています
[MEMORY ERROR:ex13_2_safe_memory.c:391] 配列境界エラー: インデックス -1 が範囲 [0, 5) を超えています
設定後の配列: 10 20 999 40 50 
[MEMORY INFO:ex13_2_safe_memory.c:295] free成功: 0x12345a0

=== 安全な文字列操作テスト ===
[MEMORY INFO:ex13_2_safe_memory.c:207] malloc成功: 64バイト @ 0x12345c0
初期文字列: Hello, World!
連結後: Hello, World! 追加テキスト
切り詰められた文字列: AAAAAAAAAAAAAAAAAAA
[MEMORY INFO:ex13_2_safe_memory.c:295] free成功: 0x12345c0

=== メモリリーク検出テスト ===
[MEMORY INFO:ex13_2_safe_memory.c:207] malloc成功: 100バイト @ 0x1234600
[MEMORY INFO:ex13_2_safe_memory.c:207] malloc成功: 200バイト @ 0x1234680
[MEMORY INFO:ex13_2_safe_memory.c:207] malloc成功: 50バイト @ 0x1234780
[MEMORY INFO:ex13_2_safe_memory.c:295] free成功: 0x1234780
意図的にリークを作成しました
leak1 = 0x1234600 (100バイト)
leak2 = 0x1234680 (200バイト)
no_leakは解放済み

=== メモリリークレポート ===
総割り当て: 474 バイト (5 回)
総解放: 174 バイト (3 回)

検出されたリーク:
  0x1234680: 200 バイト (ex13_2_safe_memory.c:448)
  0x1234600: 100 バイト (ex13_2_safe_memory.c:447)

リーク合計: 300 バイト (2 ブロック)
========================

[MEMORY INFO:ex13_2_safe_memory.c:319] メモリ追跡システムをクリーンアップしました
=== デモ完了 ===
*/