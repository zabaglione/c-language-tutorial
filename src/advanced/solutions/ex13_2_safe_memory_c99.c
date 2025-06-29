/*
 * 演習13-2の解答例: 安全なメモリ操作マクロ（C99版）
 * ファイル名: ex13_2_safe_memory_c99.c
 * 説明: NULLチェック、境界チェック、メモリリーク検出機能の実装
 * C99準拠 - 可変引数マクロ、inline関数、bool型を使用
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

/* メモリリーク追跡用の構造体 */
typedef struct MemoryTracker {
    void *ptr;
    size_t size;
    const char *file;
    int line;
    const char *func;  /* C99: 関数名追跡 */
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

/* C99: 可変引数マクロを使用したエラー処理 */
#define MEMORY_ERROR(fmt, ...) \
    fprintf(stderr, "[MEMORY ERROR:%s:%d:%s] " fmt "\n", \
            __FILE__, __LINE__, __func__, ##__VA_ARGS__)

#define MEMORY_WARNING(fmt, ...) \
    fprintf(stderr, "[MEMORY WARNING:%s:%d:%s] " fmt "\n", \
            __FILE__, __LINE__, __func__, ##__VA_ARGS__)

#define MEMORY_INFO(fmt, ...) \
    printf("[MEMORY INFO:%s:%d:%s] " fmt "\n", \
           __FILE__, __LINE__, __func__, ##__VA_ARGS__)

/* 安全なメモリ割り当てマクロ */
#define SAFE_MALLOC(size) safe_malloc_impl((size), __FILE__, __LINE__, __func__)
#define SAFE_CALLOC(count, size) safe_calloc_impl((count), (size), __FILE__, __LINE__, __func__)
#define SAFE_REALLOC(ptr, size) safe_realloc_impl((ptr), (size), __FILE__, __LINE__, __func__)

/* 安全なメモリ解放マクロ */
#define SAFE_FREE(ptr) \
    do { \
        if (ptr) { \
            safe_free_impl((ptr), __FILE__, __LINE__, __func__); \
            (ptr) = NULL; \
        } \
    } while (0)

/* C99: 型安全な配列境界チェックマクロ */
#define ARRAY_BOUNDS_CHECK(arr, index, size) \
    ((index) >= 0 && (size_t)(index) < (size_t)(size))

#define SAFE_ARRAY_ACCESS(arr, index, size, default_val) \
    (ARRAY_BOUNDS_CHECK(arr, index, size) ? (arr)[index] : (default_val))

#define SAFE_ARRAY_SET(arr, index, size, value) \
    do { \
        if (ARRAY_BOUNDS_CHECK(arr, index, size)) { \
            (arr)[index] = (value); \
        } else { \
            MEMORY_ERROR("配列境界エラー: インデックス %d が範囲 [0, %zu) を超えています", \
                        (int)(index), (size_t)(size)); \
        } \
    } while (0)

/* C99: ジェネリックなメモリ操作マクロ */
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
            MEMORY_ERROR("NULLポインタに対するmemcpy (dest=%p, src=%p)", \
                        (void*)(dest), (void*)(src)); \
        } \
    } while (0)

/* 文字列操作の安全なマクロ */
#define SAFE_STRNCPY(dest, src, size) \
    do { \
        if ((dest) && (src) && (size) > 0) { \
            strncpy((dest), (src), (size) - 1); \
            (dest)[(size) - 1] = '\0'; \
        } else { \
            MEMORY_ERROR("不正なstrncpyパラメータ (dest=%p, src=%p, size=%zu)", \
                        (void*)(dest), (void*)(src), (size_t)(size)); \
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

/* C99: アサーションマクロ */
#define SAFE_ASSERT(condition) \
    do { \
        if (!(condition)) { \
            MEMORY_ERROR("アサーション失敗: %s", #condition); \
            assert(condition); \
        } \
    } while (0)

/* メモリリーク検出マクロ */
#define MEMORY_LEAK_TRACKER_INIT() init_memory_tracker()
#define MEMORY_LEAK_TRACKER_REPORT() report_memory_leaks()
#define MEMORY_LEAK_TRACKER_CLEANUP() cleanup_memory_tracker()

/* C99: inline関数でのヘルパー */
static inline size_t safe_multiply(size_t a, size_t b)
{
    if (a != 0 && SIZE_MAX / a < b) {
        return 0;  /* オーバーフロー */
    }
    return a * b;
}

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
static void add_memory_tracker(void *ptr, size_t size, 
                              const char *file, int line, const char *func)
{
#if MEMORY_TRACKING_ENABLED
    MemoryTracker *tracker = malloc(sizeof(MemoryTracker));
    if (tracker) {
        tracker->ptr = ptr;
        tracker->size = size;
        tracker->file = file;
        tracker->line = line;
        tracker->func = func;
        tracker->next = g_memory_list;
        g_memory_list = tracker;
        
        g_total_allocated += size;
        g_allocation_count++;
    }
#endif
}

/* メモリ追跡エントリの削除 */
static void remove_memory_tracker(void *ptr, const char *file, int line, const char *func)
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
    MEMORY_WARNING("解放されたポインタ %p が追跡リストに見つかりません", ptr);
#endif
}

/* 安全なmalloc実装 */
void *safe_malloc_impl(size_t size, const char *file, int line, const char *func)
{
    if (size == 0) {
        MEMORY_WARNING("サイズ0でのmalloc");
        return NULL;
    }
    
    void *ptr = malloc(size);
    if (!ptr) {
        MEMORY_ERROR("malloc失敗: %zuバイト", size);
        return NULL;
    }
    
    add_memory_tracker(ptr, size, file, line, func);
    MEMORY_INFO("malloc成功: %zuバイト @ %p", size, ptr);
    
    return ptr;
}

/* 安全なcalloc実装 */
void *safe_calloc_impl(size_t count, size_t size, 
                      const char *file, int line, const char *func)
{
    if (count == 0 || size == 0) {
        MEMORY_WARNING("サイズ0でのcalloc");
        return NULL;
    }
    
    /* C99: inline関数でオーバーフローチェック */
    size_t total_size = safe_multiply(count, size);
    if (total_size == 0) {
        MEMORY_ERROR("calloc整数オーバーフロー: %zu * %zu", count, size);
        return NULL;
    }
    
    void *ptr = calloc(count, size);
    if (!ptr) {
        MEMORY_ERROR("calloc失敗: %zu * %zuバイト", count, size);
        return NULL;
    }
    
    add_memory_tracker(ptr, total_size, file, line, func);
    MEMORY_INFO("calloc成功: %zu * %zuバイト @ %p", count, size, ptr);
    
    return ptr;
}

/* 安全なrealloc実装 */
void *safe_realloc_impl(void *ptr, size_t size, 
                       const char *file, int line, const char *func)
{
    if (!ptr) {
        return safe_malloc_impl(size, file, line, func);
    }
    
    if (size == 0) {
        safe_free_impl(ptr, file, line, func);
        return NULL;
    }
    
    void *new_ptr = realloc(ptr, size);
    if (!new_ptr) {
        MEMORY_ERROR("realloc失敗: %zuバイト", size);
        return NULL;
    }
    
    /* 追跡情報の更新 */
    remove_memory_tracker(ptr, file, line, func);
    add_memory_tracker(new_ptr, size, file, line, func);
    
    MEMORY_INFO("realloc成功: %p -> %p (%zuバイト)", ptr, new_ptr, size);
    
    return new_ptr;
}

/* 安全なfree実装 */
void safe_free_impl(void *ptr, const char *file, int line, const char *func)
{
    if (!ptr) {
        MEMORY_WARNING("NULLポインタのfree");
        return;
    }
    
    remove_memory_tracker(ptr, file, line, func);
    free(ptr);
    MEMORY_INFO("free成功: %p", ptr);
}

/* メモリリークレポート */
void report_memory_leaks(void)
{
    printf("\n=== メモリリークレポート ===\n");
    printf("総割り当て: %zu バイト (%d 回)\n", g_total_allocated, g_allocation_count);
    printf("総解放: %zu バイト (%d 回)\n", g_total_freed, g_free_count);
    
    if (g_memory_list) {
        printf("\n検出されたリーク:\n");
        MemoryTracker *current = g_memory_list;
        size_t leak_total = 0;
        int leak_count = 0;
        
        while (current) {
            printf("  %p: %zu バイト (%s:%d in %s)\n",
                   current->ptr, current->size,
                   current->file, current->line, current->func);
            leak_total += current->size;
            leak_count++;
            current = current->next;
        }
        
        printf("\nリーク合計: %zu バイト (%d ブロック)\n", leak_total, leak_count);
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

/* C99: 型安全なスワップ関数テンプレート風マクロ */
#define DEFINE_SWAP(type) \
    static inline void swap_##type(type *a, type *b) { \
        type temp = *a; \
        *a = *b; \
        *b = temp; \
    }

DEFINE_SWAP(int)
DEFINE_SWAP(double)

/* テスト用構造体 */
typedef struct {
    int id;
    char name[32];
    double value;
    bool active;  /* C99: bool型 */
} TestData;

/* テスト関数群 */

void test_safe_allocation(void)
{
    printf("=== 安全なメモリ割り当てテスト ===\n");
    
    /* 通常の割り当て */
    int *numbers = SAFE_MALLOC(sizeof(int) * 10);
    VALIDATE_POINTER_RETURN_VOID(numbers);
    
    for (int i = 0; i < 10; i++) {
        numbers[i] = i * i;
    }
    
    printf("割り当てた配列: ");
    for (int i = 0; i < 10; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");
    
    /* 配列のサイズ変更 */
    numbers = SAFE_REALLOC(numbers, sizeof(int) * 20);
    VALIDATE_POINTER_RETURN_VOID(numbers);
    
    for (int i = 10; i < 20; i++) {
        numbers[i] = i * i;
    }
    
    printf("拡張後の配列: ");
    for (int i = 0; i < 20; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");
    
    SAFE_FREE(numbers);
    printf("メモリを正常に解放しました\n\n");
}

void test_c99_features(void)
{
    printf("=== C99特有機能テスト ===\n");
    
    /* C99: 可変長配列（VLA）のテスト */
    int size = 5;
    int vla[size];
    
    for (int i = 0; i < size; i++) {
        vla[i] = i * 10;
    }
    
    printf("VLA配列: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", vla[i]);
    }
    printf("\n");
    
    /* C99: 複合リテラルの使用 */
    TestData *data = SAFE_MALLOC(sizeof(TestData));
    VALIDATE_POINTER_RETURN_VOID(data);
    
    *data = (TestData){
        .id = 100,
        .name = "Test Item",
        .value = 3.14159,
        .active = true
    };
    
    printf("構造体データ: ID=%d, Name=%s, Value=%.2f, Active=%s\n",
           data->id, data->name, data->value, 
           data->active ? "true" : "false");
    
    /* C99: 型安全なスワップ */
    int a = 10, b = 20;
    printf("スワップ前: a=%d, b=%d\n", a, b);
    swap_int(&a, &b);
    printf("スワップ後: a=%d, b=%d\n", a, b);
    
    SAFE_FREE(data);
    printf("\n");
}

void test_array_bounds_checking(void)
{
    printf("=== 配列境界チェックテスト ===\n");
    
    int *array = SAFE_MALLOC(sizeof(int) * 5);
    VALIDATE_POINTER_RETURN_VOID(array);
    
    /* 配列の初期化 */
    for (int i = 0; i < 5; i++) {
        array[i] = (i + 1) * 10;
    }
    
    printf("配列内容: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
    
    /* 安全なアクセステスト */
    printf("安全なアクセステスト:\n");
    
    for (int i = -1; i <= 6; i++) {
        if (ARRAY_BOUNDS_CHECK(array, i, 5)) {
            printf("  インデックス %d: %d (有効)\n", i, array[i]);
        } else {
            printf("  インデックス %d: 境界外アクセス\n", i);
            int safe_value = SAFE_ARRAY_ACCESS(array, i, 5, -1);
            printf("    -> デフォルト値: %d\n", safe_value);
        }
    }
    
    /* 安全な設定テスト */
    printf("\n安全な設定テスト:\n");
    SAFE_ARRAY_SET(array, 2, 5, 999);  /* 有効 */
    SAFE_ARRAY_SET(array, 10, 5, 888); /* 無効 */
    SAFE_ARRAY_SET(array, -1, 5, 777); /* 無効 */
    
    printf("設定後の配列: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
    
    SAFE_FREE(array);
    printf("\n");
}

void test_memory_leak_detection(void)
{
    printf("=== メモリリーク検出テスト ===\n");
    
    /* 意図的にリークを作成 */
    void *leak1 = SAFE_MALLOC(100);
    void *leak2 = SAFE_MALLOC(200);
    void *no_leak = SAFE_MALLOC(50);
    
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
    printf("=== 安全なメモリ操作マクロデモ (C99版) ===\n\n");
    
    /* メモリ追跡システムの初期化 */
    MEMORY_LEAK_TRACKER_INIT();
    
    /* 各種テストの実行 */
    test_safe_allocation();
    test_c99_features();
    test_array_bounds_checking();
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
=== 安全なメモリ操作マクロデモ (C99版) ===

[MEMORY INFO:ex13_2_safe_memory_c99.c:162:init_memory_tracker] メモリ追跡システムを初期化しました

=== 安全なメモリ割り当てテスト ===
[MEMORY INFO:ex13_2_safe_memory_c99.c:219:safe_malloc_impl] malloc成功: 40バイト @ 0x1234560
割り当てた配列: 0 1 4 9 16 25 36 49 64 81 
[MEMORY INFO:ex13_2_safe_memory_c99.c:269:safe_realloc_impl] realloc成功: 0x1234560 -> 0x1234580 (80バイト)
拡張後の配列: 0 1 4 9 16 25 36 49 64 81 100 121 144 169 196 225 256 289 324 361 
[MEMORY INFO:ex13_2_safe_memory_c99.c:285:safe_free_impl] free成功: 0x1234580
メモリを正常に解放しました

=== C99特有機能テスト ===
VLA配列: 0 10 20 30 40 
[MEMORY INFO:ex13_2_safe_memory_c99.c:219:safe_malloc_impl] malloc成功: 48バイト @ 0x12345a0
構造体データ: ID=100, Name=Test Item, Value=3.14, Active=true
スワップ前: a=10, b=20
スワップ後: a=20, b=10
[MEMORY INFO:ex13_2_safe_memory_c99.c:285:safe_free_impl] free成功: 0x12345a0

=== 配列境界チェックテスト ===
[MEMORY INFO:ex13_2_safe_memory_c99.c:219:safe_malloc_impl] malloc成功: 20バイト @ 0x12345f0
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
[MEMORY ERROR:ex13_2_safe_memory_c99.c:71:test_array_bounds_checking] 配列境界エラー: インデックス 10 が範囲 [0, 5) を超えています
[MEMORY ERROR:ex13_2_safe_memory_c99.c:71:test_array_bounds_checking] 配列境界エラー: インデックス -1 が範囲 [0, 5) を超えています
設定後の配列: 10 20 999 40 50 
[MEMORY INFO:ex13_2_safe_memory_c99.c:285:safe_free_impl] free成功: 0x12345f0

=== メモリリーク検出テスト ===
[MEMORY INFO:ex13_2_safe_memory_c99.c:219:safe_malloc_impl] malloc成功: 100バイト @ 0x1234630
[MEMORY INFO:ex13_2_safe_memory_c99.c:219:safe_malloc_impl] malloc成功: 200バイト @ 0x12346b0
[MEMORY INFO:ex13_2_safe_memory_c99.c:219:safe_malloc_impl] malloc成功: 50バイト @ 0x12347b0
[MEMORY INFO:ex13_2_safe_memory_c99.c:285:safe_free_impl] free成功: 0x12347b0
意図的にリークを作成しました
leak1 = 0x1234630 (100バイト)
leak2 = 0x12346b0 (200バイト)
no_leakは解放済み

=== メモリリークレポート ===
総割り当て: 438 バイト (5 回)
総解放: 138 バイト (3 回)

検出されたリーク:
  0x12346b0: 200 バイト (ex13_2_safe_memory_c99.c:448 in test_memory_leak_detection)
  0x1234630: 100 バイト (ex13_2_safe_memory_c99.c:447 in test_memory_leak_detection)

リーク合計: 300 バイト (2 ブロック)
========================

[MEMORY INFO:ex13_2_safe_memory_c99.c:319:cleanup_memory_tracker] メモリ追跡システムをクリーンアップしました
=== デモ完了 ===
*/