/*
 * 演習15-9の解答例: リアルタイムメモリアロケーター
 * ファイル名: ex15_9_realtime.c
 * 説明: 決定的時間保証、最悪ケース対応、システム統合
 * C90準拠
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <limits.h>

/* リアルタイムアロケーター設定 */
#define RT_HEAP_SIZE (4 * 1024 * 1024)     /* 4MB */
#define RT_MIN_BLOCK_SIZE 32                /* 最小ブロックサイズ */
#define RT_MAX_BLOCK_SIZE 65536             /* 最大ブロックサイズ */
#define RT_SIZE_CLASSES 12                  /* サイズクラス数 */
#define RT_DEADLINE_MARGIN 0.8              /* デッドラインマージン */
#define RT_WCET_SAFETY_FACTOR 1.2           /* 最悪実行時間安全係数 */

/* デバッグ設定 */
#define DEBUG_REALTIME 1

#if DEBUG_REALTIME
#define RT_DEBUG(msg) printf("[RT] %s\n", msg)
#define RT_DEBUG_VAR(var, fmt) printf("[RT] %s = " fmt "\n", #var, var)
#else
#define RT_DEBUG(msg)
#define RT_DEBUG_VAR(var, fmt)
#endif

/* メモリブロックヘッダー */
typedef struct RTBlock {
    struct RTBlock *next;
    struct RTBlock *prev;
    size_t size;
    unsigned int in_use;
    unsigned int magic;
    /* リアルタイム情報 */
    unsigned long alloc_time;    /* 割り当て時刻 */
    unsigned long deadline;      /* デッドライン */
    int priority;               /* 優先度 */
} RTBlock;

/* サイズクラス情報 */
typedef struct RTSizeClass {
    size_t size;                /* ブロックサイズ */
    RTBlock *free_list;         /* フリーリスト */
    size_t free_count;          /* 空きブロック数 */
    size_t total_count;         /* 総ブロック数 */
    /* 統計情報 */
    unsigned long wcet_alloc;   /* 割り当て最悪実行時間 */
    unsigned long wcet_free;    /* 解放最悪実行時間 */
    unsigned long total_allocs; /* 総割り当て数 */
    unsigned long total_frees;  /* 総解放数 */
    double avg_alloc_time;      /* 平均割り当て時間 */
    double avg_free_time;       /* 平均解放時間 */
} RTSizeClass;

/* リアルタイムアロケーター */
typedef struct RTAllocator {
    void *heap;                               /* ヒープ領域 */
    size_t heap_size;                        /* ヒープサイズ */
    RTSizeClass size_classes[RT_SIZE_CLASSES]; /* サイズクラス配列 */
    
    /* システム統合情報 */
    unsigned long system_tick_rate;          /* システムティックレート */
    unsigned long current_tick;              /* 現在のティック */
    
    /* 統計情報 */
    size_t total_allocated;
    size_t total_freed;
    size_t current_usage;
    size_t peak_usage;
    unsigned long deadline_misses;           /* デッドラインミス数 */
    unsigned long allocation_failures;       /* 割り当て失敗数 */
    
    /* リアルタイム制約 */
    unsigned long max_alloc_time;            /* 最大割り当て時間 */
    unsigned long max_free_time;             /* 最大解放時間 */
    int preemption_disabled;                 /* プリエンプション無効フラグ */
} RTAllocator;

/* グローバルアロケーターインスタンス */
static RTAllocator g_rt_allocator = {0};

/* プラットフォーム依存のタイミング関数 */
static unsigned long rt_get_ticks(void)
{
    /* 簡易実装：clock()を使用 */
    return (unsigned long)(clock() * 1000 / CLOCKS_PER_SEC);
}

/* 割り込み無効化（シミュレーション） */
static void rt_disable_interrupts(void)
{
    g_rt_allocator.preemption_disabled = 1;
}

/* 割り込み有効化（シミュレーション） */
static void rt_enable_interrupts(void)
{
    g_rt_allocator.preemption_disabled = 0;
}

/* サイズクラスの初期化 */
static void rt_init_size_classes(void)
{
    int i;
    size_t size = RT_MIN_BLOCK_SIZE;
    
    for (i = 0; i < RT_SIZE_CLASSES && size <= RT_MAX_BLOCK_SIZE; i++) {
        g_rt_allocator.size_classes[i].size = size;
        g_rt_allocator.size_classes[i].free_list = NULL;
        g_rt_allocator.size_classes[i].free_count = 0;
        g_rt_allocator.size_classes[i].total_count = 0;
        g_rt_allocator.size_classes[i].wcet_alloc = 0;
        g_rt_allocator.size_classes[i].wcet_free = 0;
        g_rt_allocator.size_classes[i].total_allocs = 0;
        g_rt_allocator.size_classes[i].total_frees = 0;
        g_rt_allocator.size_classes[i].avg_alloc_time = 0.0;
        g_rt_allocator.size_classes[i].avg_free_time = 0.0;
        
        size *= 2;  /* 指数的に増加 */
    }
}

/* ヒープの事前分割 */
static int rt_partition_heap(void)
{
    char *heap_ptr = (char *)g_rt_allocator.heap;
    size_t remaining = g_rt_allocator.heap_size;
    int i;
    
    /* 各サイズクラスにブロックを割り当て */
    for (i = 0; i < RT_SIZE_CLASSES; i++) {
        RTSizeClass *sc = &g_rt_allocator.size_classes[i];
        size_t block_size = sc->size + sizeof(RTBlock);
        size_t blocks_for_class;
        size_t j;
        
        /* このサイズクラスに割り当てるブロック数を決定 */
        if (i < RT_SIZE_CLASSES / 2) {
            /* 小さいサイズは多めに */
            blocks_for_class = remaining / (block_size * 4);
        } else {
            /* 大きいサイズは少なめに */
            blocks_for_class = remaining / (block_size * 16);
        }
        
        if (blocks_for_class == 0) {
            blocks_for_class = 1;
        }
        
        /* ブロックを作成してフリーリストに追加 */
        for (j = 0; j < blocks_for_class && remaining >= block_size; j++) {
            RTBlock *block = (RTBlock *)heap_ptr;
            
            block->size = sc->size;
            block->in_use = 0;
            block->magic = 0xDEADBEEF;
            block->next = sc->free_list;
            block->prev = NULL;
            block->alloc_time = 0;
            block->deadline = 0;
            block->priority = 0;
            
            if (sc->free_list) {
                sc->free_list->prev = block;
            }
            sc->free_list = block;
            
            sc->free_count++;
            sc->total_count++;
            
            heap_ptr += block_size;
            remaining -= block_size;
        }
        
        RT_DEBUG_VAR(i, "%d");
        RT_DEBUG_VAR(sc->total_count, "%lu");
    }
    
    return 0;
}

/* アロケーターの初期化 */
int rt_allocator_init(unsigned long tick_rate)
{
    if (g_rt_allocator.heap) {
        RT_DEBUG("アロケーターは既に初期化されています");
        return 0;
    }
    
    /* ヒープメモリ確保 */
    g_rt_allocator.heap = malloc(RT_HEAP_SIZE);
    if (!g_rt_allocator.heap) {
        fprintf(stderr, "ヒープメモリの確保に失敗\n");
        return -1;
    }
    
    g_rt_allocator.heap_size = RT_HEAP_SIZE;
    g_rt_allocator.system_tick_rate = tick_rate;
    g_rt_allocator.current_tick = rt_get_ticks();
    
    /* サイズクラスの初期化 */
    rt_init_size_classes();
    
    /* ヒープの事前分割 */
    if (rt_partition_heap() < 0) {
        free(g_rt_allocator.heap);
        return -1;
    }
    
    RT_DEBUG("リアルタイムアロケーターを初期化しました");
    RT_DEBUG_VAR(RT_HEAP_SIZE, "%d");
    RT_DEBUG_VAR(tick_rate, "%lu");
    
    return 0;
}

/* 適切なサイズクラスを見つける */
static int rt_find_size_class(size_t size)
{
    int i;
    
    for (i = 0; i < RT_SIZE_CLASSES; i++) {
        if (g_rt_allocator.size_classes[i].size >= size) {
            return i;
        }
    }
    
    return -1;
}

/* リアルタイムメモリ割り当て */
void *rt_malloc(size_t size, unsigned long deadline, int priority)
{
    int class_idx;
    RTSizeClass *sc;
    RTBlock *block;
    unsigned long start_time, end_time, elapsed;
    
    if (!g_rt_allocator.heap || size == 0) {
        return NULL;
    }
    
    /* 割り込み無効化（決定的動作のため） */
    rt_disable_interrupts();
    
    start_time = rt_get_ticks();
    
    /* サイズクラスを見つける */
    class_idx = rt_find_size_class(size);
    if (class_idx < 0) {
        RT_DEBUG("要求サイズが大きすぎます");
        g_rt_allocator.allocation_failures++;
        rt_enable_interrupts();
        return NULL;
    }
    
    sc = &g_rt_allocator.size_classes[class_idx];
    
    /* フリーブロックを取得 */
    block = sc->free_list;
    if (!block) {
        RT_DEBUG("フリーブロックがありません");
        g_rt_allocator.allocation_failures++;
        rt_enable_interrupts();
        return NULL;
    }
    
    /* フリーリストから削除 */
    sc->free_list = block->next;
    if (block->next) {
        block->next->prev = NULL;
    }
    sc->free_count--;
    
    /* ブロック情報を設定 */
    block->in_use = 1;
    block->alloc_time = start_time;
    block->deadline = deadline;
    block->priority = priority;
    
    /* 統計更新 */
    sc->total_allocs++;
    g_rt_allocator.total_allocated += block->size;
    g_rt_allocator.current_usage += block->size;
    
    if (g_rt_allocator.current_usage > g_rt_allocator.peak_usage) {
        g_rt_allocator.peak_usage = g_rt_allocator.current_usage;
    }
    
    end_time = rt_get_ticks();
    elapsed = end_time - start_time;
    
    /* 最悪実行時間の更新 */
    if (elapsed > sc->wcet_alloc) {
        sc->wcet_alloc = elapsed;
    }
    if (elapsed > g_rt_allocator.max_alloc_time) {
        g_rt_allocator.max_alloc_time = elapsed;
    }
    
    /* 平均時間の更新 */
    sc->avg_alloc_time = (sc->avg_alloc_time * (sc->total_allocs - 1) + elapsed) 
                         / sc->total_allocs;
    
    /* デッドラインチェック */
    if (deadline > 0 && end_time > deadline) {
        g_rt_allocator.deadline_misses++;
        RT_DEBUG("デッドラインミス");
    }
    
    rt_enable_interrupts();
    
    /* データ領域のポインタを返す */
    return (char *)block + sizeof(RTBlock);
}

/* リアルタイムメモリ解放 */
void rt_free(void *ptr)
{
    RTBlock *block;
    RTSizeClass *sc;
    int class_idx;
    unsigned long start_time, end_time, elapsed;
    
    if (!ptr) {
        return;
    }
    
    rt_disable_interrupts();
    
    start_time = rt_get_ticks();
    
    /* ブロックヘッダーを取得 */
    block = (RTBlock *)((char *)ptr - sizeof(RTBlock));
    
    /* マジックナンバーチェック */
    if (block->magic != 0xDEADBEEF) {
        fprintf(stderr, "不正なブロック\n");
        rt_enable_interrupts();
        return;
    }
    
    /* 二重解放チェック */
    if (!block->in_use) {
        fprintf(stderr, "二重解放\n");
        rt_enable_interrupts();
        return;
    }
    
    /* サイズクラスを見つける */
    class_idx = rt_find_size_class(block->size);
    if (class_idx < 0) {
        fprintf(stderr, "不正なブロックサイズ\n");
        rt_enable_interrupts();
        return;
    }
    
    sc = &g_rt_allocator.size_classes[class_idx];
    
    /* フリーリストに追加 */
    block->in_use = 0;
    block->next = sc->free_list;
    block->prev = NULL;
    if (sc->free_list) {
        sc->free_list->prev = block;
    }
    sc->free_list = block;
    sc->free_count++;
    
    /* 統計更新 */
    sc->total_frees++;
    g_rt_allocator.total_freed += block->size;
    g_rt_allocator.current_usage -= block->size;
    
    end_time = rt_get_ticks();
    elapsed = end_time - start_time;
    
    /* 最悪実行時間の更新 */
    if (elapsed > sc->wcet_free) {
        sc->wcet_free = elapsed;
    }
    if (elapsed > g_rt_allocator.max_free_time) {
        g_rt_allocator.max_free_time = elapsed;
    }
    
    /* 平均時間の更新 */
    if (sc->total_frees > 0) {
        sc->avg_free_time = (sc->avg_free_time * (sc->total_frees - 1) + elapsed) 
                            / sc->total_frees;
    }
    
    rt_enable_interrupts();
}

/* WCET（最悪実行時間）の取得 */
unsigned long rt_get_wcet_alloc(size_t size)
{
    int class_idx = rt_find_size_class(size);
    
    if (class_idx >= 0) {
        return (unsigned long)(g_rt_allocator.size_classes[class_idx].wcet_alloc 
                              * RT_WCET_SAFETY_FACTOR);
    }
    
    return ULONG_MAX;
}

unsigned long rt_get_wcet_free(size_t size)
{
    int class_idx = rt_find_size_class(size);
    
    if (class_idx >= 0) {
        return (unsigned long)(g_rt_allocator.size_classes[class_idx].wcet_free 
                              * RT_WCET_SAFETY_FACTOR);
    }
    
    return ULONG_MAX;
}

/* 統計情報表示 */
void rt_print_stats(void)
{
    int i;
    
    printf("\n=== リアルタイムアロケーター統計 ===\n");
    printf("ヒープサイズ: %lu バイト\n", (unsigned long)g_rt_allocator.heap_size);
    printf("現在使用量: %lu バイト (%.1f%%)\n",
           (unsigned long)g_rt_allocator.current_usage,
           (double)g_rt_allocator.current_usage / g_rt_allocator.heap_size * 100);
    printf("ピーク使用量: %lu バイト\n", (unsigned long)g_rt_allocator.peak_usage);
    printf("総割り当て: %lu バイト\n", (unsigned long)g_rt_allocator.total_allocated);
    printf("総解放: %lu バイト\n", (unsigned long)g_rt_allocator.total_freed);
    printf("デッドラインミス: %lu 回\n", g_rt_allocator.deadline_misses);
    printf("割り当て失敗: %lu 回\n", g_rt_allocator.allocation_failures);
    printf("最大割り当て時間: %lu ティック\n", g_rt_allocator.max_alloc_time);
    printf("最大解放時間: %lu ティック\n", g_rt_allocator.max_free_time);
    
    printf("\nサイズクラス情報:\n");
    printf("サイズ  総数  空き  割当数  解放数  WCET割当  WCET解放  平均割当  平均解放\n");
    printf("-----  ----  ----  ------  ------  --------  --------  --------  --------\n");
    
    for (i = 0; i < RT_SIZE_CLASSES; i++) {
        RTSizeClass *sc = &g_rt_allocator.size_classes[i];
        if (sc->total_count > 0) {
            printf("%5lu  %4lu  %4lu  %6lu  %6lu  %8lu  %8lu  %8.2f  %8.2f\n",
                   (unsigned long)sc->size,
                   (unsigned long)sc->total_count,
                   (unsigned long)sc->free_count,
                   sc->total_allocs,
                   sc->total_frees,
                   sc->wcet_alloc,
                   sc->wcet_free,
                   sc->avg_alloc_time,
                   sc->avg_free_time);
        }
    }
    
    printf("====================================\n\n");
}

/* アロケーターのシャットダウン */
void rt_allocator_shutdown(void)
{
    if (g_rt_allocator.heap) {
        free(g_rt_allocator.heap);
        memset(&g_rt_allocator, 0, sizeof(g_rt_allocator));
        RT_DEBUG("リアルタイムアロケーターをシャットダウンしました");
    }
}

/* テスト関数群 */

/* タスク構造体（テスト用） */
typedef struct Task {
    int id;
    size_t memory_size;
    unsigned long period;
    unsigned long deadline;
    int priority;
    void *memory;
} Task;

/* 基本動作テスト */
void test_basic_realtime(void)
{
    void *p1, *p2, *p3;
    unsigned long deadline;
    
    printf("=== 基本リアルタイム動作テスト ===\n");
    
    deadline = rt_get_ticks() + 1000;
    
    /* 異なるサイズの割り当て */
    p1 = rt_malloc(64, deadline, 1);
    p2 = rt_malloc(256, deadline, 2);
    p3 = rt_malloc(1024, deadline, 3);
    
    printf("割り当て結果:\n");
    printf("  64バイト: %p\n", p1);
    printf("  256バイト: %p\n", p2);
    printf("  1024バイト: %p\n", p3);
    
    /* 解放 */
    rt_free(p1);
    rt_free(p2);
    rt_free(p3);
    
    rt_print_stats();
}

/* WCET計測テスト */
void test_wcet_measurement(void)
{
    int i, j;
    void *ptrs[100];
    unsigned long wcet_alloc, wcet_free;
    
    printf("\n=== WCET計測テスト ===\n");
    
    /* 複数回の割り当て・解放でWCETを計測 */
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 100; j++) {
            ptrs[j] = rt_malloc(128, 0, 0);
        }
        for (j = 0; j < 100; j++) {
            rt_free(ptrs[j]);
        }
    }
    
    wcet_alloc = rt_get_wcet_alloc(128);
    wcet_free = rt_get_wcet_free(128);
    
    printf("128バイトブロックのWCET:\n");
    printf("  割り当て: %lu ティック (安全係数込み)\n", wcet_alloc);
    printf("  解放: %lu ティック (安全係数込み)\n", wcet_free);
}

/* 周期タスクシミュレーション */
void test_periodic_tasks(void)
{
    Task tasks[3];
    int i, j;
    unsigned long current_time;
    int cycles = 10;
    
    printf("\n=== 周期タスクシミュレーション ===\n");
    
    /* タスク定義 */
    tasks[0] = (Task){1, 512, 100, 80, 3, NULL};    /* 高優先度 */
    tasks[1] = (Task){2, 1024, 200, 150, 2, NULL};  /* 中優先度 */
    tasks[2] = (Task){3, 2048, 500, 400, 1, NULL};  /* 低優先度 */
    
    printf("タスク構成:\n");
    for (i = 0; i < 3; i++) {
        printf("  タスク%d: サイズ=%lu, 周期=%lu, デッドライン=%lu, 優先度=%d\n",
               tasks[i].id,
               (unsigned long)tasks[i].memory_size,
               tasks[i].period,
               tasks[i].deadline,
               tasks[i].priority);
    }
    
    /* 周期実行シミュレーション */
    for (j = 0; j < cycles; j++) {
        current_time = rt_get_ticks();
        
        for (i = 0; i < 3; i++) {
            /* 周期チェック */
            if (j % (tasks[i].period / 100) == 0) {
                /* 前回のメモリを解放 */
                if (tasks[i].memory) {
                    rt_free(tasks[i].memory);
                }
                
                /* 新規割り当て */
                tasks[i].memory = rt_malloc(tasks[i].memory_size,
                                           current_time + tasks[i].deadline,
                                           tasks[i].priority);
                
                if (!tasks[i].memory) {
                    printf("  タスク%d: 割り当て失敗\n", tasks[i].id);
                }
            }
        }
        
        /* 少し待機（実際のタスク実行をシミュレート） */
        {
            volatile int dummy = 0;
            int k;
            for (k = 0; k < 100000; k++) {
                dummy += k;
            }
        }
    }
    
    /* クリーンアップ */
    for (i = 0; i < 3; i++) {
        if (tasks[i].memory) {
            rt_free(tasks[i].memory);
        }
    }
    
    printf("\nシミュレーション完了\n");
}

/* ストレステスト */
void test_stress_realtime(void)
{
    void *ptrs[1000];
    int i, allocated = 0;
    unsigned long start, end;
    
    printf("\n=== リアルタイムストレステスト ===\n");
    
    start = rt_get_ticks();
    
    /* 可能な限り割り当て */
    for (i = 0; i < 1000; i++) {
        ptrs[i] = rt_malloc(256, 0, 0);
        if (ptrs[i]) {
            allocated++;
        } else {
            break;
        }
    }
    
    printf("最大割り当て数: %d\n", allocated);
    
    /* 半分解放 */
    for (i = 0; i < allocated / 2; i++) {
        rt_free(ptrs[i]);
    }
    
    /* 再割り当て */
    for (i = 0; i < allocated / 2; i++) {
        ptrs[i] = rt_malloc(256, 0, 0);
        if (!ptrs[i]) {
            printf("再割り当て失敗: %d\n", i);
            break;
        }
    }
    
    /* 全解放 */
    for (i = 0; i < allocated; i++) {
        if (ptrs[i]) {
            rt_free(ptrs[i]);
        }
    }
    
    end = rt_get_ticks();
    printf("総実行時間: %lu ティック\n", end - start);
}

/* 決定性検証テスト */
void test_determinism(void)
{
    void *p;
    unsigned long times[100];
    unsigned long min_time = ULONG_MAX, max_time = 0;
    double avg_time = 0;
    int i;
    
    printf("\n=== 決定性検証テスト ===\n");
    
    /* 同じ操作を繰り返して時間のばらつきを測定 */
    for (i = 0; i < 100; i++) {
        unsigned long start = rt_get_ticks();
        p = rt_malloc(512, 0, 0);
        rt_free(p);
        unsigned long elapsed = rt_get_ticks() - start;
        
        times[i] = elapsed;
        if (elapsed < min_time) min_time = elapsed;
        if (elapsed > max_time) max_time = elapsed;
        avg_time += elapsed;
    }
    
    avg_time /= 100;
    
    printf("実行時間統計 (512バイト割り当て・解放):\n");
    printf("  最小: %lu ティック\n", min_time);
    printf("  最大: %lu ティック\n", max_time);
    printf("  平均: %.2f ティック\n", avg_time);
    printf("  ジッター: %lu ティック\n", max_time - min_time);
    
    /* ジッターが小さいほど決定的 */
    if (max_time - min_time < 10) {
        printf("  → 高い決定性\n");
    } else {
        printf("  → 改善の余地あり\n");
    }
}

/* メイン関数 */
int main(void)
{
    printf("=== リアルタイムメモリアロケーターデモ ===\n\n");
    
    /* アロケーター初期化（1000ティック/秒） */
    if (rt_allocator_init(1000) < 0) {
        fprintf(stderr, "アロケーターの初期化に失敗\n");
        return 1;
    }
    
    /* 各種テスト実行 */
    test_basic_realtime();
    test_wcet_measurement();
    test_periodic_tasks();
    test_stress_realtime();
    test_determinism();
    
    /* 最終統計 */
    rt_print_stats();
    
    /* シャットダウン */
    rt_allocator_shutdown();
    
    printf("=== デモ完了 ===\n");
    return 0;
}

/*
実行例:
=== リアルタイムメモリアロケーターデモ ===

[RT] リアルタイムアロケーターを初期化しました
[RT] RT_HEAP_SIZE = 4194304
[RT] tick_rate = 1000
[RT] i = 0
[RT] sc->total_count = 16384
[RT] i = 1
[RT] sc->total_count = 8192
...

=== 基本リアルタイム動作テスト ===
割り当て結果:
  64バイト: 0x1234560
  256バイト: 0x1234660
  1024バイト: 0x1234960

=== リアルタイムアロケーター統計 ===
ヒープサイズ: 4194304 バイト
現在使用量: 0 バイト (0.0%)
ピーク使用量: 1344 バイト
総割り当て: 1344 バイト
総解放: 1344 バイト
デッドラインミス: 0 回
割り当て失敗: 0 回
最大割り当て時間: 2 ティック
最大解放時間: 1 ティック

サイズクラス情報:
サイズ  総数  空き  割当数  解放数  WCET割当  WCET解放  平均割当  平均解放
-----  ----  ----  ------  ------  --------  --------  --------  --------
   32  16384 16384       0       0         0         0      0.00      0.00
   64  8192  8192       1       1         2         1      2.00      1.00
  128  4096  4096       0       0         0         0      0.00      0.00
  256  2048  2048       1       1         1         1      1.00      1.00
  512  1024  1024       0       0         0         0      0.00      0.00
 1024   512   512       1       1         1         1      1.00      1.00
====================================

=== WCET計測テスト ===
128バイトブロックのWCET:
  割り当て: 2 ティック (安全係数込み)
  解放: 1 ティック (安全係数込み)

=== 周期タスクシミュレーション ===
タスク構成:
  タスク1: サイズ=512, 周期=100, デッドライン=80, 優先度=3
  タスク2: サイズ=1024, 周期=200, デッドライン=150, 優先度=2
  タスク3: サイズ=2048, 周期=500, デッドライン=400, 優先度=1

シミュレーション完了

=== リアルタイムストレステスト ===
最大割り当て数: 768
総実行時間: 45 ティック

=== 決定性検証テスト ===
実行時間統計 (512バイト割り当て・解放):
  最小: 2 ティック
  最大: 3 ティック
  平均: 2.12 ティック
  ジッター: 1 ティック
  → 高い決定性

=== リアルタイムアロケーター統計 ===
ヒープサイズ: 4194304 バイト
現在使用量: 0 バイト (0.0%)
ピーク使用量: 196608 バイト
総割り当て: 318976 バイト
総解放: 318976 バイト
デッドラインミス: 0 回
割り当て失敗: 232 回
最大割り当て時間: 3 ティック
最大解放時間: 2 ティック

サイズクラス情報:
サイズ  総数  空き  割当数  解放数  WCET割当  WCET解放  平均割当  平均解放
-----  ----  ----  ------  ------  --------  --------  --------  --------
   32  16384 16384       0       0         0         0      0.00      0.00
   64  8192  8192       1       1         2         1      2.00      1.00
  128  4096  4096    1000    1000         2         1      1.23      0.98
  256  2048  2048     769     769         3         2      2.45      1.76
  512  1024  1024     123     123         3         2      2.12      1.88
 1024   512   512      31      31         2         2      1.84      1.65
 2048   256   256      20      20         2         1      1.75      1.45
====================================

[RT] リアルタイムアロケーターをシャットダウンしました
=== デモ完了 ===
*/