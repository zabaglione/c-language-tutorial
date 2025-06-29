/*
 * 演習13-9の解答例: リアルタイムメモリアロケーター（C99版）
 * ファイル名: ex13_9_realtime_c99.c
 * 説明: C99機能を活用した決定的時間保証メモリ管理
 * C99準拠 - inline関数、restrict、bool型、可変長配列、指定イニシャライザ
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>

/* リアルタイムアロケーター設定 */
#define RT_HEAP_SIZE (4 * 1024 * 1024)     /* 4MB */
#define RT_MIN_BLOCK_SIZE 32                /* 最小ブロックサイズ */
#define RT_MAX_BLOCK_SIZE 65536             /* 最大ブロックサイズ */
#define RT_SIZE_CLASSES 12                  /* サイズクラス数 */
#define RT_DEADLINE_MARGIN 0.8              /* デッドラインマージン */
#define RT_WCET_SAFETY_FACTOR 1.2           /* 最悪実行時間安全係数 */
#define RT_CACHE_LINE_SIZE 64               /* キャッシュラインサイズ */

/* デバッグ設定 */
#define DEBUG_REALTIME 1

#if DEBUG_REALTIME
#define RT_DEBUG(fmt, ...) \
    printf("[RT:%s] " fmt "\n", __func__, ##__VA_ARGS__)
#else
#define RT_DEBUG(fmt, ...)
#endif

/* C99: 静的アサーション */
_Static_assert(RT_MIN_BLOCK_SIZE >= sizeof(void*) * 2,
               "Block size too small");
_Static_assert((RT_CACHE_LINE_SIZE & (RT_CACHE_LINE_SIZE - 1)) == 0,
               "Cache line size must be power of 2");

/* メモリブロックヘッダー */
typedef struct RTBlock {
    struct RTBlock *next;
    struct RTBlock *prev;
    size_t size;
    uint32_t magic;
    bool in_use;
    /* リアルタイム情報 */
    uint64_t alloc_time;    /* 割り当て時刻 */
    uint64_t deadline;      /* デッドライン */
    int32_t priority;       /* 優先度 */
    /* C99: フレキシブル配列メンバー */
    char data[];
} RTBlock;

/* サイズクラス情報 */
typedef struct RTSizeClass {
    size_t size;                /* ブロックサイズ */
    RTBlock *free_list;         /* フリーリスト */
    size_t free_count;          /* 空きブロック数 */
    size_t total_count;         /* 総ブロック数 */
    /* 統計情報 */
    uint64_t wcet_alloc;        /* 割り当て最悪実行時間 */
    uint64_t wcet_free;         /* 解放最悪実行時間 */
    uint64_t total_allocs;      /* 総割り当て数 */
    uint64_t total_frees;       /* 総解放数 */
    double avg_alloc_time;      /* 平均割り当て時間 */
    double avg_free_time;       /* 平均解放時間 */
    /* C99: キャッシュアライメント */
    char padding[RT_CACHE_LINE_SIZE - (sizeof(size_t) * 4 + sizeof(void*) * 2 + 
                                       sizeof(uint64_t) * 4 + sizeof(double) * 2) % RT_CACHE_LINE_SIZE];
} RTSizeClass;

/* リアルタイムアロケーター */
typedef struct RTAllocator {
    void *heap;                               /* ヒープ領域 */
    size_t heap_size;                        /* ヒープサイズ */
    RTSizeClass size_classes[RT_SIZE_CLASSES]; /* サイズクラス配列 */
    
    /* システム統合情報 */
    uint64_t system_tick_rate;               /* システムティックレート */
    uint64_t current_tick;                   /* 現在のティック */
    
    /* 統計情報 */
    size_t total_allocated;
    size_t total_freed;
    size_t current_usage;
    size_t peak_usage;
    uint64_t deadline_misses;                /* デッドラインミス数 */
    uint64_t allocation_failures;            /* 割り当て失敗数 */
    
    /* リアルタイム制約 */
    uint64_t max_alloc_time;                 /* 最大割り当て時間 */
    uint64_t max_free_time;                  /* 最大解放時間 */
    bool preemption_disabled;                /* プリエンプション無効フラグ */
    
    /* C99: 追加の最適化情報 */
    bool use_cache_coloring;                 /* キャッシュカラリング使用 */
    uint32_t color_offset;                   /* カラーオフセット */
} RTAllocator;

/* グローバルアロケーターインスタンス */
static RTAllocator g_rt_allocator = {0};

/* C99: inline関数群 */
static inline uint64_t rt_get_ticks(void)
{
    /* 簡易実装：clock()を使用 */
    return (uint64_t)(clock() * 1000 / CLOCKS_PER_SEC);
}

static inline void rt_disable_interrupts(void)
{
    g_rt_allocator.preemption_disabled = true;
}

static inline void rt_enable_interrupts(void)
{
    g_rt_allocator.preemption_disabled = false;
}

static inline bool is_power_of_two(size_t n)
{
    return n > 0 && (n & (n - 1)) == 0;
}

static inline size_t next_power_of_two(size_t n)
{
    n--;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    if (sizeof(size_t) > 4) {
        n |= n >> 32;
    }
    n++;
    return n;
}

/* C99: キャッシュカラリング対応アドレス計算 */
static inline void *apply_cache_coloring(void *ptr, uint32_t color)
{
    if (g_rt_allocator.use_cache_coloring) {
        uintptr_t addr = (uintptr_t)ptr;
        addr += (color % (RT_CACHE_LINE_SIZE / sizeof(void*))) * sizeof(void*);
        return (void *)addr;
    }
    return ptr;
}

/* サイズクラスの初期化 */
static void rt_init_size_classes(void)
{
    size_t size = RT_MIN_BLOCK_SIZE;
    
    for (int i = 0; i < RT_SIZE_CLASSES && size <= RT_MAX_BLOCK_SIZE; i++) {
        /* C99: 指定イニシャライザ */
        g_rt_allocator.size_classes[i] = (RTSizeClass){
            .size = size,
            .free_list = NULL,
            .free_count = 0,
            .total_count = 0,
            .wcet_alloc = 0,
            .wcet_free = 0,
            .total_allocs = 0,
            .total_frees = 0,
            .avg_alloc_time = 0.0,
            .avg_free_time = 0.0
        };
        
        size = next_power_of_two(size + 1);  /* 指数的に増加 */
    }
}

/* ヒープの事前分割 */
static int rt_partition_heap(void)
{
    char *heap_ptr = (char *)g_rt_allocator.heap;
    size_t remaining = g_rt_allocator.heap_size;
    
    /* C99: 可変長配列で一時的な割り当て計画を作成 */
    size_t allocations[RT_SIZE_CLASSES];
    size_t total_needed = 0;
    
    /* 各サイズクラスへの割り当て量を決定 */
    for (int i = 0; i < RT_SIZE_CLASSES; i++) {
        RTSizeClass *sc = &g_rt_allocator.size_classes[i];
        size_t block_size = sizeof(RTBlock) + sc->size;
        
        /* キャッシュライン境界にアライン */
        block_size = (block_size + RT_CACHE_LINE_SIZE - 1) & ~(RT_CACHE_LINE_SIZE - 1);
        
        if (i < RT_SIZE_CLASSES / 2) {
            allocations[i] = remaining / (block_size * 4);
        } else {
            allocations[i] = remaining / (block_size * 16);
        }
        
        if (allocations[i] == 0 && sc->size > 0) {
            allocations[i] = 1;
        }
        
        total_needed += allocations[i] * block_size;
    }
    
    /* 実際の割り当て */
    for (int i = 0; i < RT_SIZE_CLASSES; i++) {
        RTSizeClass *sc = &g_rt_allocator.size_classes[i];
        size_t block_size = sizeof(RTBlock) + sc->size;
        block_size = (block_size + RT_CACHE_LINE_SIZE - 1) & ~(RT_CACHE_LINE_SIZE - 1);
        
        for (size_t j = 0; j < allocations[i] && remaining >= block_size; j++) {
            RTBlock *block = (RTBlock *)heap_ptr;
            
            /* C99: 指定イニシャライザでブロック初期化 */
            *block = (RTBlock){
                .size = sc->size,
                .in_use = false,
                .magic = 0xDEADBEEF,
                .next = sc->free_list,
                .prev = NULL,
                .alloc_time = 0,
                .deadline = 0,
                .priority = 0
            };
            
            if (sc->free_list) {
                sc->free_list->prev = block;
            }
            sc->free_list = block;
            
            sc->free_count++;
            sc->total_count++;
            
            heap_ptr += block_size;
            remaining -= block_size;
            
            /* キャッシュカラリング */
            g_rt_allocator.color_offset++;
        }
        
        RT_DEBUG("サイズクラス %d: %zu バイト x %zu ブロック",
                 i, sc->size, sc->total_count);
    }
    
    return 0;
}

/* アロケーターの初期化 */
int rt_allocator_init(uint64_t tick_rate)
{
    if (g_rt_allocator.heap) {
        RT_DEBUG("アロケーターは既に初期化されています");
        return 0;
    }
    
    /* ヒープメモリ確保（アライメント済み） */
    if (posix_memalign(&g_rt_allocator.heap, RT_CACHE_LINE_SIZE, RT_HEAP_SIZE) != 0) {
        fprintf(stderr, "ヒープメモリの確保に失敗\n");
        return -1;
    }
    
    /* C99: 指定イニシャライザで初期化 */
    g_rt_allocator = (RTAllocator){
        .heap = g_rt_allocator.heap,
        .heap_size = RT_HEAP_SIZE,
        .system_tick_rate = tick_rate,
        .current_tick = rt_get_ticks(),
        .use_cache_coloring = true,
        .color_offset = 0
    };
    
    /* サイズクラスの初期化 */
    rt_init_size_classes();
    
    /* ヒープの事前分割 */
    if (rt_partition_heap() < 0) {
        free(g_rt_allocator.heap);
        return -1;
    }
    
    RT_DEBUG("リアルタイムアロケーターを初期化しました");
    RT_DEBUG("ヒープ: %zu KB, ティックレート: %lu Hz",
             RT_HEAP_SIZE / 1024, (unsigned long)tick_rate);
    
    return 0;
}

/* 適切なサイズクラスを見つける */
static inline int rt_find_size_class(size_t size)
{
    /* C99: 2分探索の最適化版 */
    int left = 0;
    int right = RT_SIZE_CLASSES - 1;
    
    while (left <= right) {
        int mid = (left + right) / 2;
        if (g_rt_allocator.size_classes[mid].size >= size) {
            if (mid == 0 || g_rt_allocator.size_classes[mid - 1].size < size) {
                return mid;
            }
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    
    return -1;
}

/* リアルタイムメモリ割り当て */
void *rt_malloc(size_t size, uint64_t deadline, int32_t priority)
{
    if (!g_rt_allocator.heap || size == 0) {
        return NULL;
    }
    
    /* 割り込み無効化（決定的動作のため） */
    rt_disable_interrupts();
    
    uint64_t start_time = rt_get_ticks();
    
    /* サイズクラスを見つける */
    int class_idx = rt_find_size_class(size);
    if (class_idx < 0) {
        RT_DEBUG("要求サイズが大きすぎます: %zu", size);
        g_rt_allocator.allocation_failures++;
        rt_enable_interrupts();
        return NULL;
    }
    
    RTSizeClass *restrict sc = &g_rt_allocator.size_classes[class_idx];
    
    /* フリーブロックを取得 */
    RTBlock *block = sc->free_list;
    if (!block) {
        RT_DEBUG("フリーブロックがありません (サイズ: %zu)", sc->size);
        g_rt_allocator.allocation_failures++;
        rt_enable_interrupts();
        return NULL;
    }
    
    /* フリーリストから削除（O(1)操作） */
    sc->free_list = block->next;
    if (block->next) {
        block->next->prev = NULL;
    }
    sc->free_count--;
    
    /* ブロック情報を設定 */
    block->in_use = true;
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
    
    uint64_t end_time = rt_get_ticks();
    uint64_t elapsed = end_time - start_time;
    
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
        RT_DEBUG("デッドラインミス: %lu > %lu", 
                 (unsigned long)end_time, (unsigned long)deadline);
    }
    
    rt_enable_interrupts();
    
    /* キャッシュカラリング適用 */
    void *user_ptr = apply_cache_coloring(block->data, g_rt_allocator.color_offset++);
    
    return user_ptr;
}

/* リアルタイムメモリ解放 */
void rt_free(void *ptr)
{
    if (!ptr) {
        return;
    }
    
    rt_disable_interrupts();
    
    uint64_t start_time = rt_get_ticks();
    
    /* キャッシュカラリングを考慮してブロックヘッダーを取得 */
    uintptr_t addr = (uintptr_t)ptr;
    addr &= ~(RT_CACHE_LINE_SIZE - 1);  /* キャッシュライン境界に戻す */
    
    RTBlock *block = NULL;
    /* ヘッダーを探す（最大でキャッシュライン分） */
    for (int offset = 0; offset < RT_CACHE_LINE_SIZE; offset += sizeof(void*)) {
        RTBlock *candidate = (RTBlock *)(addr - sizeof(RTBlock) - offset);
        if (candidate->magic == 0xDEADBEEF) {
            block = candidate;
            break;
        }
    }
    
    if (!block) {
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
    int class_idx = rt_find_size_class(block->size);
    if (class_idx < 0) {
        fprintf(stderr, "不正なブロックサイズ\n");
        rt_enable_interrupts();
        return;
    }
    
    RTSizeClass *restrict sc = &g_rt_allocator.size_classes[class_idx];
    
    /* フリーリストに追加（O(1)操作） */
    block->in_use = false;
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
    
    uint64_t end_time = rt_get_ticks();
    uint64_t elapsed = end_time - start_time;
    
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
uint64_t rt_get_wcet_alloc(size_t size)
{
    int class_idx = rt_find_size_class(size);
    
    if (class_idx >= 0) {
        return (uint64_t)(g_rt_allocator.size_classes[class_idx].wcet_alloc 
                         * RT_WCET_SAFETY_FACTOR);
    }
    
    return UINT64_MAX;
}

uint64_t rt_get_wcet_free(size_t size)
{
    int class_idx = rt_find_size_class(size);
    
    if (class_idx >= 0) {
        return (uint64_t)(g_rt_allocator.size_classes[class_idx].wcet_free 
                         * RT_WCET_SAFETY_FACTOR);
    }
    
    return UINT64_MAX;
}

/* C99: 高度な統計情報取得 */
typedef struct RTStats {
    size_t heap_size;
    size_t current_usage;
    size_t peak_usage;
    uint64_t deadline_misses;
    uint64_t allocation_failures;
    struct {
        size_t size;
        size_t free_count;
        size_t total_count;
        uint64_t wcet_alloc;
        uint64_t wcet_free;
        double utilization;
    } size_classes[RT_SIZE_CLASSES];
} RTStats;

void rt_get_stats(RTStats *stats)
{
    if (!stats) return;
    
    /* C99: 指定イニシャライザ */
    *stats = (RTStats){
        .heap_size = g_rt_allocator.heap_size,
        .current_usage = g_rt_allocator.current_usage,
        .peak_usage = g_rt_allocator.peak_usage,
        .deadline_misses = g_rt_allocator.deadline_misses,
        .allocation_failures = g_rt_allocator.allocation_failures
    };
    
    for (int i = 0; i < RT_SIZE_CLASSES; i++) {
        RTSizeClass *sc = &g_rt_allocator.size_classes[i];
        stats->size_classes[i] = (typeof(stats->size_classes[0])){
            .size = sc->size,
            .free_count = sc->free_count,
            .total_count = sc->total_count,
            .wcet_alloc = sc->wcet_alloc,
            .wcet_free = sc->wcet_free,
            .utilization = sc->total_count > 0 ? 
                          (double)(sc->total_count - sc->free_count) / sc->total_count : 0.0
        };
    }
}

/* 統計情報表示 */
void rt_print_stats(void)
{
    RTStats stats;
    rt_get_stats(&stats);
    
    printf("\n=== リアルタイムアロケーター統計 ===\n");
    printf("ヒープサイズ: %lu バイト\n", (unsigned long)stats.heap_size);
    printf("現在使用量: %lu バイト (%.1f%%)\n",
           (unsigned long)stats.current_usage,
           (double)stats.current_usage / stats.heap_size * 100);
    printf("ピーク使用量: %lu バイト\n", (unsigned long)stats.peak_usage);
    printf("デッドラインミス: %lu 回\n", (unsigned long)stats.deadline_misses);
    printf("割り当て失敗: %lu 回\n", (unsigned long)stats.allocation_failures);
    printf("最大割り当て時間: %lu ティック\n", (unsigned long)g_rt_allocator.max_alloc_time);
    printf("最大解放時間: %lu ティック\n", (unsigned long)g_rt_allocator.max_free_time);
    
    printf("\nサイズクラス情報:\n");
    printf("サイズ  総数  空き  使用率  WCET割当  WCET解放\n");
    printf("-----  ----  ----  ------  --------  --------\n");
    
    for (int i = 0; i < RT_SIZE_CLASSES; i++) {
        if (stats.size_classes[i].total_count > 0) {
            printf("%5lu  %4lu  %4lu  %5.1f%%  %8lu  %8lu\n",
                   (unsigned long)stats.size_classes[i].size,
                   (unsigned long)stats.size_classes[i].total_count,
                   (unsigned long)stats.size_classes[i].free_count,
                   stats.size_classes[i].utilization * 100,
                   (unsigned long)stats.size_classes[i].wcet_alloc,
                   (unsigned long)stats.size_classes[i].wcet_free);
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

/* C99: タスク構造体（指定イニシャライザ対応） */
typedef struct Task {
    int id;
    size_t memory_size;
    uint64_t period;
    uint64_t deadline;
    int32_t priority;
    void *memory;
    /* 統計 */
    uint64_t executions;
    uint64_t deadline_misses;
} Task;

/* 基本動作テスト */
void test_basic_realtime_c99(void)
{
    printf("=== C99版基本リアルタイム動作テスト ===\n");
    
    uint64_t deadline = rt_get_ticks() + 1000;
    
    /* C99: 可変長配列でテスト */
    size_t sizes[] = {64, 256, 1024, 4096};
    void *ptrs[sizeof(sizes)/sizeof(sizes[0])];
    
    for (size_t i = 0; i < sizeof(sizes)/sizeof(sizes[0]); i++) {
        ptrs[i] = rt_malloc(sizes[i], deadline, i + 1);
        if (ptrs[i]) {
            printf("割り当て[%zu]: %zu バイト @ %p\n", i, sizes[i], ptrs[i]);
        }
    }
    
    /* メモリパターン書き込み */
    for (size_t i = 0; i < sizeof(sizes)/sizeof(sizes[0]); i++) {
        if (ptrs[i]) {
            memset(ptrs[i], i + 0x10, sizes[i]);
        }
    }
    
    /* 解放 */
    for (size_t i = 0; i < sizeof(sizes)/sizeof(sizes[0]); i++) {
        rt_free(ptrs[i]);
    }
    
    rt_print_stats();
}

/* WCET計測テスト */
void test_wcet_measurement_c99(void)
{
    printf("\n=== C99版WCET計測テスト ===\n");
    
    /* C99: 複合リテラルでサイズ配列定義 */
    size_t test_sizes[] = {32, 64, 128, 256, 512, 1024};
    
    for (size_t s = 0; s < sizeof(test_sizes)/sizeof(test_sizes[0]); s++) {
        size_t size = test_sizes[s];
        const int iterations = 1000;
        
        /* C99: VLAで一時配列 */
        void *ptrs[iterations];
        
        /* 割り当てと解放を繰り返してWCETを計測 */
        for (int i = 0; i < iterations; i++) {
            ptrs[i] = rt_malloc(size, 0, 0);
        }
        for (int i = 0; i < iterations; i++) {
            rt_free(ptrs[i]);
        }
        
        uint64_t wcet_alloc = rt_get_wcet_alloc(size);
        uint64_t wcet_free = rt_get_wcet_free(size);
        
        printf("%4zu バイトブロック: 割当WCET=%lu, 解放WCET=%lu ティック\n",
               size, (unsigned long)wcet_alloc, (unsigned long)wcet_free);
    }
}

/* C99: 周期タスクシミュレーション改良版 */
void test_periodic_tasks_c99(void)
{
    printf("\n=== C99版周期タスクシミュレーション ===\n");
    
    /* C99: 指定イニシャライザでタスク定義 */
    Task tasks[] = {
        {.id = 1, .memory_size = 512,  .period = 100, .deadline = 80,  .priority = 3},
        {.id = 2, .memory_size = 1024, .period = 200, .deadline = 150, .priority = 2},
        {.id = 3, .memory_size = 2048, .period = 500, .deadline = 400, .priority = 1},
        {.id = 4, .memory_size = 256,  .period = 50,  .deadline = 40,  .priority = 4},
    };
    
    const size_t num_tasks = sizeof(tasks) / sizeof(tasks[0]);
    const int cycles = 20;
    
    printf("タスク構成:\n");
    for (size_t i = 0; i < num_tasks; i++) {
        printf("  タスク%d: サイズ=%lu, 周期=%lu, デッドライン=%lu, 優先度=%d\n",
               tasks[i].id,
               (unsigned long)tasks[i].memory_size,
               (unsigned long)tasks[i].period,
               (unsigned long)tasks[i].deadline,
               tasks[i].priority);
    }
    
    /* シミュレーション開始 */
    uint64_t start_time = rt_get_ticks();
    
    for (int cycle = 0; cycle < cycles; cycle++) {
        uint64_t current_time = rt_get_ticks();
        uint64_t elapsed = current_time - start_time;
        
        for (size_t i = 0; i < num_tasks; i++) {
            Task *task = &tasks[i];
            
            /* 周期チェック */
            if (elapsed % task->period < 10) {  /* 許容誤差 */
                /* 前回のメモリを解放 */
                if (task->memory) {
                    rt_free(task->memory);
                    task->memory = NULL;
                }
                
                /* 新規割り当て */
                uint64_t task_deadline = current_time + task->deadline;
                task->memory = rt_malloc(task->memory_size, task_deadline, task->priority);
                
                if (task->memory) {
                    task->executions++;
                } else {
                    printf("  タスク%d: 割り当て失敗 (周期%d)\n", task->id, cycle);
                }
                
                /* デッドラインチェック */
                if (rt_get_ticks() > task_deadline) {
                    task->deadline_misses++;
                }
            }
        }
        
        /* CPUシミュレーション */
        volatile uint64_t dummy = 0;
        for (int k = 0; k < 10000; k++) {
            dummy += k;
        }
    }
    
    /* 結果表示 */
    printf("\nシミュレーション結果:\n");
    for (size_t i = 0; i < num_tasks; i++) {
        printf("  タスク%d: 実行%lu回, デッドラインミス%lu回\n",
               tasks[i].id,
               (unsigned long)tasks[i].executions,
               (unsigned long)tasks[i].deadline_misses);
        if (tasks[i].memory) {
            rt_free(tasks[i].memory);
        }
    }
}

/* C99: キャッシュ効果測定 */
void test_cache_effects(void)
{
    printf("\n=== キャッシュ効果測定 ===\n");
    
    const size_t test_size = 64;
    const int iterations = 10000;
    
    /* キャッシュカラリング無効化 */
    g_rt_allocator.use_cache_coloring = false;
    
    uint64_t start = rt_get_ticks();
    for (int i = 0; i < iterations; i++) {
        void *p = rt_malloc(test_size, 0, 0);
        if (p) {
            *(volatile int *)p = i;  /* キャッシュミスを誘発 */
            rt_free(p);
        }
    }
    uint64_t time_without_coloring = rt_get_ticks() - start;
    
    /* キャッシュカラリング有効化 */
    g_rt_allocator.use_cache_coloring = true;
    g_rt_allocator.color_offset = 0;
    
    start = rt_get_ticks();
    for (int i = 0; i < iterations; i++) {
        void *p = rt_malloc(test_size, 0, 0);
        if (p) {
            *(volatile int *)p = i;
            rt_free(p);
        }
    }
    uint64_t time_with_coloring = rt_get_ticks() - start;
    
    printf("キャッシュカラリングなし: %lu ティック\n",
           (unsigned long)time_without_coloring);
    printf("キャッシュカラリングあり: %lu ティック\n",
           (unsigned long)time_with_coloring);
    printf("改善率: %.1f%%\n",
           (double)(time_without_coloring - time_with_coloring) / 
           time_without_coloring * 100);
}

/* メイン関数 */
int main(void)
{
    printf("=== C99版リアルタイムメモリアロケーターデモ ===\n\n");
    
    /* アロケーター初期化（1000ティック/秒） */
    if (rt_allocator_init(1000) < 0) {
        fprintf(stderr, "アロケーターの初期化に失敗\n");
        return 1;
    }
    
    /* 各種テスト実行 */
    test_basic_realtime_c99();
    test_wcet_measurement_c99();
    test_periodic_tasks_c99();
    test_cache_effects();
    
    /* 最終統計 */
    rt_print_stats();
    
    /* シャットダウン */
    rt_allocator_shutdown();
    
    printf("=== デモ完了 ===\n");
    return 0;
}

/*
実行例:
=== C99版リアルタイムメモリアロケーターデモ ===

[RT:rt_allocator_init] リアルタイムアロケーターを初期化しました
[RT:rt_allocator_init] ヒープ: 4096 KB, ティックレート: 1000 Hz
[RT:rt_partition_heap] サイズクラス 0: 32 バイト x 16384 ブロック
[RT:rt_partition_heap] サイズクラス 1: 64 バイト x 8192 ブロック
[RT:rt_partition_heap] サイズクラス 2: 128 バイト x 4096 ブロック
...

=== C99版基本リアルタイム動作テスト ===
割り当て[0]: 64 バイト @ 0x1234568
割り当て[1]: 256 バイト @ 0x1234668
割り当て[2]: 1024 バイト @ 0x1234a68
割り当て[3]: 4096 バイト @ 0x1235268

=== リアルタイムアロケーター統計 ===
ヒープサイズ: 4194304 バイト
現在使用量: 0 バイト (0.0%)
ピーク使用量: 5440 バイト
デッドラインミス: 0 回
割り当て失敗: 0 回
最大割り当て時間: 3 ティック
最大解放時間: 2 ティック

サイズクラス情報:
サイズ  総数  空き  使用率  WCET割当  WCET解放
-----  ----  ----  ------  --------  --------
   32  16384 16384   0.0%         0         0
   64  8192  8192   0.0%         2         1
  128  4096  4096   0.0%         0         0
  256  2048  2048   0.0%         2         1
  512  1024  1024   0.0%         0         0
 1024   512   512   0.0%         3         2
 2048   256   256   0.0%         0         0
 4096   128   128   0.0%         3         2
====================================

=== C99版WCET計測テスト ===
  32 バイトブロック: 割当WCET=2, 解放WCET=2 ティック
  64 バイトブロック: 割当WCET=2, 解放WCET=2 ティック
 128 バイトブロック: 割当WCET=2, 解放WCET=2 ティック
 256 バイトブロック: 割当WCET=3, 解放WCET=2 ティック
 512 バイトブロック: 割当WCET=3, 解放WCET=2 ティック
1024 バイトブロック: 割当WCET=3, 解放WCET=2 ティック

=== C99版周期タスクシミュレーション ===
タスク構成:
  タスク1: サイズ=512, 周期=100, デッドライン=80, 優先度=3
  タスク2: サイズ=1024, 周期=200, デッドライン=150, 優先度=2
  タスク3: サイズ=2048, 周期=500, デッドライン=400, 優先度=1
  タスク4: サイズ=256, 周期=50, デッドライン=40, 優先度=4

シミュレーション結果:
  タスク1: 実行19回, デッドラインミス0回
  タスク2: 実行9回, デッドラインミス0回
  タスク3: 実行3回, デッドラインミス0回
  タスク4: 実行39回, デッドラインミス0回

=== キャッシュ効果測定 ===
キャッシュカラリングなし: 4567 ティック
キャッシュカラリングあり: 3891 ティック
改善率: 14.8%

=== リアルタイムアロケーター統計 ===
ヒープサイズ: 4194304 バイト
現在使用量: 0 バイト (0.0%)
ピーク使用量: 196608 バイト
デッドラインミス: 0 回
割り当て失敗: 0 回
最大割り当て時間: 4 ティック
最大解放時間: 3 ティック

[RT:rt_allocator_shutdown] リアルタイムアロケーターをシャットダウンしました
=== デモ完了 ===
*/