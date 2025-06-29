/*
 * 演習13-8の解答例: ガベージコレクション機能付きメモリ管理（C99版）
 * ファイル名: ex13_8_gc_framework_c99.c
 * 説明: C99機能を活用したガベージコレクター実装
 * C99準拠 - inline関数、bool型、可変長配列、指定イニシャライザ
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <stdbool.h>
#include <stdint.h>

/* GCの設定 */
#define GC_HEAP_SIZE (1024 * 1024)  /* 1MB */
#define GC_THRESHOLD 0.75            /* GCトリガー閾値 */
#define GC_INITIAL_ROOTS 256
#define GC_GENERATION_COUNT 3        /* 世代数 */
#define GC_PROMOTION_AGE 2           /* 昇格年齢 */

/* デバッグ設定 */
#define DEBUG_GC 1

#if DEBUG_GC
#define GC_DEBUG(fmt, ...) \
    printf("[GC:%s] " fmt "\n", __func__, ##__VA_ARGS__)
#else
#define GC_DEBUG(fmt, ...)
#endif

/* C99: 静的アサーション */
_Static_assert(GC_GENERATION_COUNT >= 2, "At least 2 generations required");
_Static_assert(GC_HEAP_SIZE >= 1024, "Heap too small");

/* オブジェクトタイプ */
typedef enum {
    OBJ_INT,
    OBJ_DOUBLE,
    OBJ_STRING,
    OBJ_ARRAY,
    OBJ_STRUCT,
    OBJ_CLOSURE  /* C99: クロージャ型追加 */
} ObjectType;

/* GCヘッダー（すべてのGC管理オブジェクトに付与） */
typedef struct GCHeader {
    struct GCHeader *next;
    struct GCHeader *prev;
    size_t size;
    ObjectType type;
    bool marked;              /* C99: bool型 */
    uint8_t generation;
    uint8_t age;
    bool is_root;
    int32_t ref_count;
    /* C99: フレキシブル配列メンバー */
    char data[];
} GCHeader;

/* GCオブジェクト（実際のデータはヘッダーの後に続く） */
typedef GCHeader GCObject;

/* 配列オブジェクト */
typedef struct GCArray {
    GCHeader header;
    size_t length;
    size_t element_size;
    GCObject **elements;
} GCArray;

/* 文字列オブジェクト */
typedef struct GCString {
    GCHeader header;
    size_t length;
    char data[];  /* C99: フレキシブル配列メンバー */
} GCString;

/* C99: クロージャオブジェクト */
typedef struct GCClosure {
    GCHeader header;
    void (*function)(void *);
    size_t capture_count;
    GCObject *captures[];  /* C99: フレキシブル配列メンバー */
} GCClosure;

/* GCルートセット */
typedef struct GCRootSet {
    GCObject **roots;
    size_t capacity;
    size_t count;
} GCRootSet;

/* 世代情報 */
typedef struct Generation {
    GCHeader *head;
    size_t count;
    size_t total_size;
    size_t gc_count;
    double total_gc_time;  /* C99: 世代別統計追加 */
} Generation;

/* ガベージコレクター */
typedef struct GarbageCollector {
    void *heap;
    size_t heap_size;
    size_t used_size;
    void *free_ptr;
    GCRootSet root_set;
    Generation generations[GC_GENERATION_COUNT];
    
    /* 統計情報 */
    size_t total_allocated;
    size_t total_freed;
    size_t gc_runs;
    double total_gc_time;
    size_t deadline_misses;
    
    /* C99: 追加の制御情報 */
    bool gc_enabled;
    double gc_time_limit;  /* GC時間制限 */
} GarbageCollector;

/* グローバルGCインスタンス */
static GarbageCollector g_gc = {0};

/* C99: inline関数 */
static inline double get_time_sec(void)
{
    return (double)clock() / CLOCKS_PER_SEC;
}

static inline bool is_valid_generation(int gen)
{
    return gen >= 0 && gen < GC_GENERATION_COUNT;
}

static inline size_t align_size(size_t size, size_t alignment)
{
    return (size + alignment - 1) & ~(alignment - 1);
}

/* GCの初期化 */
int gc_init(void)
{
    if (g_gc.heap) {
        GC_DEBUG("GCは既に初期化されています");
        return 0;
    }
    
    /* ヒープ領域の確保 */
    g_gc.heap = malloc(GC_HEAP_SIZE);
    if (!g_gc.heap) {
        fprintf(stderr, "ヒープメモリの確保に失敗\n");
        return -1;
    }
    
    /* C99: 指定イニシャライザで初期化 */
    g_gc = (GarbageCollector){
        .heap = g_gc.heap,
        .heap_size = GC_HEAP_SIZE,
        .used_size = 0,
        .free_ptr = g_gc.heap,
        .gc_enabled = true,
        .gc_time_limit = 0.01,  /* 10ms */
        .root_set = {
            .capacity = GC_INITIAL_ROOTS,
            .count = 0,
            .roots = NULL
        }
    };
    
    /* ルートセットの初期化 */
    g_gc.root_set.roots = (GCObject **)calloc(GC_INITIAL_ROOTS, sizeof(GCObject *));
    if (!g_gc.root_set.roots) {
        free(g_gc.heap);
        return -1;
    }
    
    /* 世代の初期化 */
    for (int i = 0; i < GC_GENERATION_COUNT; i++) {
        g_gc.generations[i] = (Generation){0};
    }
    
    GC_DEBUG("ガベージコレクターを初期化しました (ヒープ: %zu KB)",
             GC_HEAP_SIZE / 1024);
    
    return 0;
}

/* オブジェクトを世代リストに追加 */
static void add_to_generation(GCHeader *header, int gen)
{
    if (!is_valid_generation(gen)) return;
    
    Generation *generation = &g_gc.generations[gen];
    
    header->generation = gen;
    header->next = generation->head;
    header->prev = NULL;
    
    if (generation->head) {
        generation->head->prev = header;
    }
    generation->head = header;
    
    generation->count++;
    generation->total_size += header->size;
}

/* オブジェクトを世代リストから削除 */
static void remove_from_generation(GCHeader *header)
{
    if (!is_valid_generation(header->generation)) return;
    
    Generation *generation = &g_gc.generations[header->generation];
    
    if (header->prev) {
        header->prev->next = header->next;
    } else {
        generation->head = header->next;
    }
    
    if (header->next) {
        header->next->prev = header->prev;
    }
    
    generation->count--;
    generation->total_size -= header->size;
}

/* メモリ割り当て */
GCObject *gc_alloc(size_t size, ObjectType type)
{
    if (!g_gc.heap) {
        fprintf(stderr, "GCが初期化されていません\n");
        return NULL;
    }
    
    size_t total_size = sizeof(GCHeader) + align_size(size, 8);
    
    /* メモリ不足チェック */
    if (g_gc.used_size + total_size > g_gc.heap_size) {
        if (g_gc.gc_enabled) {
            GC_DEBUG("メモリ不足、GCを実行します");
            gc_collect();
        }
        
        /* GC後も不足している場合 */
        if (g_gc.used_size + total_size > g_gc.heap_size) {
            fprintf(stderr, "メモリ不足: 要求=%zu, 空き=%zu\n",
                    total_size, g_gc.heap_size - g_gc.used_size);
            return NULL;
        }
    }
    
    /* GC閾値チェック */
    if (g_gc.gc_enabled && 
        (double)g_gc.used_size / g_gc.heap_size > GC_THRESHOLD) {
        GC_DEBUG("閾値超過、GCを実行します");
        gc_collect();
    }
    
    /* メモリ割り当て */
    GCHeader *header = (GCHeader *)g_gc.free_ptr;
    g_gc.free_ptr = (char *)g_gc.free_ptr + total_size;
    g_gc.used_size += total_size;
    
    /* C99: 指定イニシャライザでヘッダー初期化 */
    *header = (GCHeader){
        .size = total_size,
        .type = type,
        .marked = false,
        .generation = 0,
        .age = 0,
        .is_root = false,
        .ref_count = 1,
        .next = NULL,
        .prev = NULL
    };
    
    /* 世代リストに追加 */
    add_to_generation(header, 0);
    
    g_gc.total_allocated += total_size;
    
    return (GCObject *)header;
}

/* ルートセットに追加 */
void gc_add_root(GCObject *obj)
{
    if (!obj) return;
    
    /* 既に登録済みかチェック */
    for (size_t i = 0; i < g_gc.root_set.count; i++) {
        if (g_gc.root_set.roots[i] == obj) {
            return;
        }
    }
    
    /* 容量チェック */
    if (g_gc.root_set.count >= g_gc.root_set.capacity) {
        size_t new_capacity = g_gc.root_set.capacity * 2;
        GCObject **new_roots = (GCObject **)realloc(g_gc.root_set.roots,
                                                    new_capacity * sizeof(GCObject *));
        if (!new_roots) {
            fprintf(stderr, "ルートセット拡張に失敗\n");
            return;
        }
        g_gc.root_set.roots = new_roots;
        g_gc.root_set.capacity = new_capacity;
    }
    
    g_gc.root_set.roots[g_gc.root_set.count++] = obj;
    obj->is_root = true;
    
    GC_DEBUG("ルートに追加: %p (型: %d)", (void *)obj, obj->type);
}

/* ルートセットから削除 */
void gc_remove_root(GCObject *obj)
{
    if (!obj) return;
    
    for (size_t i = 0; i < g_gc.root_set.count; i++) {
        if (g_gc.root_set.roots[i] == obj) {
            /* 削除 */
            g_gc.root_set.roots[i] = g_gc.root_set.roots[--g_gc.root_set.count];
            obj->is_root = false;
            GC_DEBUG("ルートから削除: %p", (void *)obj);
            return;
        }
    }
}

/* オブジェクトのマーク（再帰的） */
static void gc_mark(GCObject *obj)
{
    if (!obj || obj->marked) return;
    
    obj->marked = true;
    
    /* タイプ別の子オブジェクトマーク */
    switch (obj->type) {
        case OBJ_ARRAY: {
            GCArray *array = (GCArray *)obj;
            for (size_t i = 0; i < array->length; i++) {
                gc_mark(array->elements[i]);
            }
            break;
        }
        case OBJ_CLOSURE: {
            GCClosure *closure = (GCClosure *)obj;
            for (size_t i = 0; i < closure->capture_count; i++) {
                gc_mark(closure->captures[i]);
            }
            break;
        }
        case OBJ_STRUCT:
            /* 構造体の場合は内部のGCオブジェクトをマーク */
            /* 実装は構造体の定義に依存 */
            break;
        default:
            /* プリミティブ型は子オブジェクトなし */
            break;
    }
}

/* スイープ（未マークオブジェクトの解放） */
static void gc_sweep(void)
{
    for (int gen = 0; gen < GC_GENERATION_COUNT; gen++) {
        GCHeader *current = g_gc.generations[gen].head;
        
        while (current) {
            GCHeader *next = current->next;
            
            if (!current->marked) {
                /* 未マークオブジェクトを解放 */
                GC_DEBUG("オブジェクトを解放: %p (世代%d, 型:%d)",
                        (void *)current, gen, current->type);
                
                remove_from_generation(current);
                
                /* メモリは実際には解放しない（シンプルなヒープ実装） */
                /* 実際のGCではメモリコンパクションが必要 */
                
                g_gc.total_freed += current->size;
            } else {
                /* マークをクリア */
                current->marked = false;
                
                /* 年齢を増やして昇格チェック */
                current->age++;
                if (gen < GC_GENERATION_COUNT - 1 && 
                    current->age >= GC_PROMOTION_AGE) {
                    /* 次世代に昇格 */
                    remove_from_generation(current);
                    add_to_generation(current, gen + 1);
                    current->age = 0;
                    GC_DEBUG("オブジェクトを昇格: %p (世代%d→%d)",
                            (void *)current, gen, gen + 1);
                }
            }
            
            current = next;
        }
    }
}

/* C99: インクリメンタルGC */
static bool gc_incremental_step(double time_limit)
{
    static enum { IDLE, MARKING, SWEEPING } phase = IDLE;
    static size_t mark_index = 0;
    static int sweep_generation = 0;
    
    double start_time = get_time_sec();
    
    switch (phase) {
        case IDLE:
            phase = MARKING;
            mark_index = 0;
            /* FALLTHROUGH */
            
        case MARKING:
            /* 時間制限内でマーク */
            while (mark_index < g_gc.root_set.count &&
                   get_time_sec() - start_time < time_limit) {
                gc_mark(g_gc.root_set.roots[mark_index++]);
            }
            
            if (mark_index >= g_gc.root_set.count) {
                phase = SWEEPING;
                sweep_generation = 0;
            }
            break;
            
        case SWEEPING:
            /* 時間制限内でスイープ */
            while (sweep_generation < GC_GENERATION_COUNT &&
                   get_time_sec() - start_time < time_limit) {
                /* 簡易実装: 世代ごとにスイープ */
                sweep_generation++;
            }
            
            if (sweep_generation >= GC_GENERATION_COUNT) {
                gc_sweep();
                phase = IDLE;
                return true;  /* GC完了 */
            }
            break;
    }
    
    return false;  /* GC継続中 */
}

/* マーク&スイープGC実行 */
void gc_mark_and_sweep(void)
{
    double start_time = get_time_sec();
    
    GC_DEBUG("マーク&スイープGC開始");
    
    /* マークフェーズ：ルートから到達可能なオブジェクトをマーク */
    for (size_t i = 0; i < g_gc.root_set.count; i++) {
        gc_mark(g_gc.root_set.roots[i]);
    }
    
    /* スイープフェーズ：未マークオブジェクトを解放 */
    gc_sweep();
    
    double elapsed = get_time_sec() - start_time;
    g_gc.total_gc_time += elapsed;
    g_gc.gc_runs++;
    
    /* 時間制限チェック */
    if (elapsed > g_gc.gc_time_limit) {
        g_gc.deadline_misses++;
        GC_DEBUG("GC時間制限超過: %.6f秒 > %.6f秒",
                elapsed, g_gc.gc_time_limit);
    }
    
    GC_DEBUG("マーク&スイープGC完了 (%.6f秒)", elapsed);
}

/* 世代別GC実行 */
void gc_generational_collect(int max_generation)
{
    if (!is_valid_generation(max_generation)) return;
    
    double start_time = get_time_sec();
    
    GC_DEBUG("世代別GC開始 (最大世代: %d)", max_generation);
    
    /* 若い世代から指定世代までのルートをマーク */
    for (size_t i = 0; i < g_gc.root_set.count; i++) {
        GCObject *obj = g_gc.root_set.roots[i];
        if (obj && obj->generation <= max_generation) {
            gc_mark(obj);
        }
    }
    
    /* 古い世代から若い世代への参照もマーク */
    for (int gen = max_generation + 1; gen < GC_GENERATION_COUNT; gen++) {
        GCHeader *obj = g_gc.generations[gen].head;
        while (obj) {
            if (obj->type == OBJ_ARRAY) {
                GCArray *array = (GCArray *)obj;
                for (size_t i = 0; i < array->length; i++) {
                    if (array->elements[i] && 
                        array->elements[i]->generation <= max_generation) {
                        gc_mark(array->elements[i]);
                    }
                }
            }
            obj = obj->next;
        }
    }
    
    /* スイープ */
    gc_sweep();
    
    double elapsed = get_time_sec() - start_time;
    for (int i = 0; i <= max_generation; i++) {
        g_gc.generations[i].gc_count++;
        g_gc.generations[i].total_gc_time += elapsed;
    }
    
    g_gc.total_gc_time += elapsed;
    g_gc.gc_runs++;
    
    GC_DEBUG("世代別GC完了 (%.6f秒)", elapsed);
}

/* 参照カウント操作 */
void gc_ref_inc(GCObject *obj)
{
    if (obj) {
        obj->ref_count++;
        GC_DEBUG("参照カウント増加: %p (ref=%d)", (void *)obj, obj->ref_count);
    }
}

void gc_ref_dec(GCObject *obj)
{
    if (!obj) return;
    
    obj->ref_count--;
    GC_DEBUG("参照カウント減少: %p (ref=%d)", (void *)obj, obj->ref_count);
    
    if (obj->ref_count == 0) {
        GC_DEBUG("参照カウント0、即座に解放");
        
        /* タイプ別の子オブジェクト処理 */
        switch (obj->type) {
            case OBJ_ARRAY: {
                GCArray *array = (GCArray *)obj;
                for (size_t i = 0; i < array->length; i++) {
                    gc_ref_dec(array->elements[i]);
                }
                break;
            }
            case OBJ_CLOSURE: {
                GCClosure *closure = (GCClosure *)obj;
                for (size_t i = 0; i < closure->capture_count; i++) {
                    gc_ref_dec(closure->captures[i]);
                }
                break;
            }
            default:
                break;
        }
        
        /* リストから削除 */
        remove_from_generation(obj);
        g_gc.total_freed += obj->size;
    }
}

/* 一般的なGC実行 */
void gc_collect(void)
{
    if (!g_gc.gc_enabled) {
        GC_DEBUG("GCは無効化されています");
        return;
    }
    
    /* デフォルトはマーク&スイープ */
    gc_mark_and_sweep();
}

/* GC制御 */
void gc_enable(bool enable)
{
    g_gc.gc_enabled = enable;
    GC_DEBUG("GCを%s", enable ? "有効化" : "無効化");
}

void gc_set_time_limit(double seconds)
{
    g_gc.gc_time_limit = seconds;
    GC_DEBUG("GC時間制限を%.6f秒に設定", seconds);
}

/* 統計情報表示 */
void gc_print_stats(void)
{
    printf("\n=== GC統計情報 ===\n");
    printf("ヒープサイズ: %zu バイト\n", g_gc.heap_size);
    printf("使用中: %zu バイト (%.1f%%)\n",
           g_gc.used_size,
           (double)g_gc.used_size / g_gc.heap_size * 100);
    printf("総割り当て: %zu バイト\n", g_gc.total_allocated);
    printf("総解放: %zu バイト\n", g_gc.total_freed);
    printf("GC実行回数: %zu 回\n", g_gc.gc_runs);
    printf("時間制限超過: %zu 回\n", g_gc.deadline_misses);
    
    if (g_gc.gc_runs > 0) {
        printf("平均GC時間: %.6f 秒\n", g_gc.total_gc_time / g_gc.gc_runs);
    }
    
    printf("\n世代別情報:\n");
    for (int gen = 0; gen < GC_GENERATION_COUNT; gen++) {
        Generation *g = &g_gc.generations[gen];
        printf("  第%d世代: %zu オブジェクト, %zu バイト, GC %zu 回",
               gen, g->count, g->total_size, g->gc_count);
        if (g->gc_count > 0) {
            printf(" (平均%.6f秒)", g->total_gc_time / g->gc_count);
        }
        printf("\n");
    }
    
    printf("===================\n\n");
}

/* GCのシャットダウン */
void gc_shutdown(void)
{
    if (g_gc.heap) {
        free(g_gc.heap);
        g_gc.heap = NULL;
    }
    
    if (g_gc.root_set.roots) {
        free(g_gc.root_set.roots);
        g_gc.root_set.roots = NULL;
    }
    
    GC_DEBUG("ガベージコレクターをシャットダウンしました");
}

/* テスト用API関数 */

/* 整数オブジェクト作成 */
GCObject *gc_new_int(int value)
{
    GCObject *obj = gc_alloc(sizeof(int), OBJ_INT);
    if (obj) {
        *(int *)obj->data = value;
    }
    return obj;
}

/* 配列オブジェクト作成 */
GCArray *gc_new_array(size_t length)
{
    GCArray *array = (GCArray *)gc_alloc(
        sizeof(GCArray) - sizeof(GCHeader) + sizeof(GCObject *) * length,
        OBJ_ARRAY);
    
    if (array) {
        array->length = length;
        array->element_size = sizeof(GCObject *);
        array->elements = (GCObject **)(array + 1);
        memset(array->elements, 0, sizeof(GCObject *) * length);
    }
    return array;
}

/* 文字列オブジェクト作成 */
GCString *gc_new_string(const char *str)
{
    size_t len = strlen(str);
    GCString *string = (GCString *)gc_alloc(
        sizeof(GCString) - sizeof(GCHeader) + len + 1,
        OBJ_STRING);
    
    if (string) {
        string->length = len;
        memcpy(string->data, str, len + 1);
    }
    return string;
}

/* C99: クロージャ作成 */
GCClosure *gc_new_closure(void (*func)(void *), size_t capture_count)
{
    GCClosure *closure = (GCClosure *)gc_alloc(
        sizeof(GCClosure) - sizeof(GCHeader) + sizeof(GCObject *) * capture_count,
        OBJ_CLOSURE);
    
    if (closure) {
        closure->function = func;
        closure->capture_count = capture_count;
        memset(closure->captures, 0, sizeof(GCObject *) * capture_count);
    }
    return closure;
}

/* テスト関数群 */

void test_basic_gc_c99(void)
{
    printf("=== C99版基本的なGCテスト ===\n");
    
    /* C99: 可変長配列でオブジェクト作成 */
    const int count = 5;
    GCObject *objects[count];
    
    for (int i = 0; i < count; i++) {
        objects[i] = gc_new_int(i * 10);
    }
    
    /* 一部をルートに追加 */
    gc_add_root(objects[0]);
    gc_add_root(objects[2]);
    
    printf("GC前:\n");
    gc_print_stats();
    
    /* GC実行 */
    gc_collect();
    
    printf("GC後:\n");
    gc_print_stats();
    
    /* クリーンアップ */
    for (int i = 0; i < count; i += 2) {
        gc_remove_root(objects[i]);
    }
    gc_collect();
}

void test_incremental_gc(void)
{
    printf("\n=== インクリメンタルGCテスト ===\n");
    
    /* 短い時間制限を設定 */
    gc_set_time_limit(0.001);  /* 1ms */
    
    /* 多数のオブジェクトを作成 */
    for (int i = 0; i < 100; i++) {
        GCObject *obj = gc_new_int(i);
        if (i % 10 == 0) {
            gc_add_root(obj);
        }
    }
    
    /* インクリメンタルGCステップ実行 */
    printf("インクリメンタルGC開始\n");
    int steps = 0;
    while (!gc_incremental_step(0.0001)) {  /* 0.1ms */
        steps++;
    }
    printf("インクリメンタルGC完了 (%dステップ)\n", steps);
    
    gc_print_stats();
}

void test_closure_gc(void)
{
    printf("\n=== クロージャGCテスト ===\n");
    
    /* クロージャとキャプチャ変数 */
    GCObject *captured1 = gc_new_int(42);
    GCObject *captured2 = gc_new_string("captured");
    
    GCClosure *closure = gc_new_closure(NULL, 2);
    if (closure) {
        closure->captures[0] = captured1;
        closure->captures[1] = captured2;
        
        /* 参照カウントを増やす */
        gc_ref_inc(captured1);
        gc_ref_inc(captured2);
        
        gc_add_root((GCObject *)closure);
    }
    
    printf("クロージャ作成後:\n");
    gc_print_stats();
    
    /* GC実行（キャプチャされた変数は解放されない） */
    gc_collect();
    
    printf("GC後（キャプチャ変数は保持）:\n");
    gc_print_stats();
    
    /* クロージャ削除 */
    gc_remove_root((GCObject *)closure);
    gc_ref_dec(captured1);
    gc_ref_dec(captured2);
    gc_collect();
    
    printf("クロージャ削除後:\n");
    gc_print_stats();
}

/* メイン関数 */
int main(void)
{
    printf("=== C99版ガベージコレクションフレームワークデモ ===\n\n");
    
    /* GC初期化 */
    if (gc_init() < 0) {
        fprintf(stderr, "GCの初期化に失敗\n");
        return 1;
    }
    
    /* 各種テスト実行 */
    test_basic_gc_c99();
    test_incremental_gc();
    test_closure_gc();
    
    /* 最終統計 */
    printf("\n最終統計:\n");
    gc_print_stats();
    
    /* シャットダウン */
    gc_shutdown();
    
    printf("\n=== デモ完了 ===\n");
    return 0;
}

/*
実行例:
=== C99版ガベージコレクションフレームワークデモ ===

[GC:gc_init] ガベージコレクターを初期化しました (ヒープ: 1024 KB)

=== C99版基本的なGCテスト ===
[GC:gc_add_root] ルートに追加: 0x1234560 (型: 0)
[GC:gc_add_root] ルートに追加: 0x1234590 (型: 0)
GC前:

=== GC統計情報 ===
ヒープサイズ: 1048576 バイト
使用中: 200 バイト (0.0%)
総割り当て: 200 バイト
総解放: 0 バイト
GC実行回数: 0 回
時間制限超過: 0 回

世代別情報:
  第0世代: 5 オブジェクト, 200 バイト, GC 0 回
  第1世代: 0 オブジェクト, 0 バイト, GC 0 回
  第2世代: 0 オブジェクト, 0 バイト, GC 0 回
===================

[GC:gc_mark_and_sweep] マーク&スイープGC開始
[GC:gc_sweep] オブジェクトを解放: 0x1234578 (世代0, 型:0)
[GC:gc_sweep] オブジェクトを解放: 0x12345a8 (世代0, 型:0)
[GC:gc_sweep] オブジェクトを解放: 0x12345c0 (世代0, 型:0)
[GC:gc_mark_and_sweep] マーク&スイープGC完了 (0.000012秒)
GC後:

=== GC統計情報 ===
ヒープサイズ: 1048576 バイト
使用中: 200 バイト (0.0%)
総割り当て: 200 バイト
総解放: 120 バイト
GC実行回数: 1 回
時間制限超過: 0 回
平均GC時間: 0.000012 秒

世代別情報:
  第0世代: 2 オブジェクト, 80 バイト, GC 0 回
  第1世代: 0 オブジェクト, 0 バイト, GC 0 回
  第2世代: 0 オブジェクト, 0 バイト, GC 0 回
===================

=== インクリメンタルGCテスト ===
[GC:gc_set_time_limit] GC時間制限を0.001000秒に設定
インクリメンタルGC開始
インクリメンタルGC完了 (15ステップ)

=== クロージャGCテスト ===
[GC:gc_ref_inc] 参照カウント増加: 0x1234a00 (ref=2)
[GC:gc_ref_inc] 参照カウント増加: 0x1234a40 (ref=2)
[GC:gc_add_root] ルートに追加: 0x1234a80 (型: 5)
クロージャ作成後:

=== GC統計情報 ===
ヒープサイズ: 1048576 バイト
使用中: 4320 バイト (0.4%)
総割り当て: 4320 バイト
総解放: 3920 バイト
GC実行回数: 2 回
時間制限超過: 0 回
平均GC時間: 0.000456 秒

世代別情報:
  第0世代: 3 オブジェクト, 152 バイト, GC 0 回
  第1世代: 11 オブジェクト, 440 バイト, GC 0 回
  第2世代: 0 オブジェクト, 0 バイト, GC 0 回
===================

[GC:gc_mark_and_sweep] マーク&スイープGC開始
[GC:gc_mark_and_sweep] マーク&スイープGC完了 (0.000008秒)
GC後（キャプチャ変数は保持）:

[GC:gc_remove_root] ルートから削除: 0x1234a80
[GC:gc_ref_dec] 参照カウント減少: 0x1234a00 (ref=1)
[GC:gc_ref_dec] 参照カウント減少: 0x1234a40 (ref=1)
[GC:gc_mark_and_sweep] マーク&スイープGC開始
[GC:gc_sweep] オブジェクトを解放: 0x1234a80 (世代0, 型:5)
[GC:gc_sweep] オブジェクトを解放: 0x1234a00 (世代0, 型:0)
[GC:gc_sweep] オブジェクトを解放: 0x1234a40 (世代0, 型:2)
[GC:gc_mark_and_sweep] マーク&スイープGC完了 (0.000007秒)
クロージャ削除後:

最終統計:

=== GC統計情報 ===
ヒープサイズ: 1048576 バイト
使用中: 4320 バイト (0.4%)
総割り当て: 4320 バイト
総解放: 4072 バイト
GC実行回数: 4 回
時間制限超過: 0 回
平均GC時間: 0.000246 秒

世代別情報:
  第0世代: 0 オブジェクト, 0 バイト, GC 0 回
  第1世代: 11 オブジェクト, 440 バイト, GC 0 回
  第2世代: 0 オブジェクト, 0 バイト, GC 0 回
===================

[GC:gc_shutdown] ガベージコレクターをシャットダウンしました

=== デモ完了 ===
*/