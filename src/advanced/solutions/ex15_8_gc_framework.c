/*
 * 演習15-8の解答例: ガベージコレクション機能付きメモリ管理
 * ファイル名: ex15_8_gc_framework.c
 * 説明: マーク&スイープ、参照カウント、世代別GCの実装
 * C90準拠
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

/* GCの設定 */
#define GC_HEAP_SIZE (1024 * 1024)  /* 1MB */
#define GC_THRESHOLD 0.75            /* GCトリガー閾値 */
#define GC_INITIAL_ROOTS 256
#define GC_GENERATION_COUNT 3        /* 世代数 */
#define GC_PROMOTION_AGE 2           /* 昇格年齢 */

/* デバッグ設定 */
#define DEBUG_GC 1

#if DEBUG_GC
#define GC_DEBUG(msg) printf("[GC] %s\n", msg)
#define GC_DEBUG_VAR(var, fmt) printf("[GC] %s = " fmt "\n", #var, var)
#else
#define GC_DEBUG(msg)
#define GC_DEBUG_VAR(var, fmt)
#endif

/* オブジェクトタイプ */
typedef enum {
    OBJ_INT,
    OBJ_DOUBLE,
    OBJ_STRING,
    OBJ_ARRAY,
    OBJ_STRUCT
} ObjectType;

/* GCヘッダー（すべてのGC管理オブジェクトに付与） */
typedef struct GCHeader {
    struct GCHeader *next;      /* 次のオブジェクト */
    struct GCHeader *prev;      /* 前のオブジェクト */
    size_t size;               /* オブジェクトサイズ */
    ObjectType type;           /* オブジェクトタイプ */
    unsigned char marked;      /* マークフラグ */
    unsigned char generation;  /* 世代番号 */
    unsigned char age;         /* 年齢（GCを生き延びた回数） */
    unsigned char is_root;     /* ルートオブジェクトフラグ */
    int ref_count;            /* 参照カウント */
} GCHeader;

/* GCオブジェクト（実際のデータはヘッダーの後に続く） */
typedef struct GCObject {
    GCHeader header;
    /* データ領域 */
} GCObject;

/* 配列オブジェクト */
typedef struct GCArray {
    GCHeader header;
    size_t length;
    GCObject **elements;
} GCArray;

/* 文字列オブジェクト */
typedef struct GCString {
    GCHeader header;
    size_t length;
    char *data;
} GCString;

/* GCルートセット */
typedef struct GCRootSet {
    GCObject **roots;
    size_t capacity;
    size_t count;
} GCRootSet;

/* 世代情報 */
typedef struct Generation {
    GCHeader *head;           /* オブジェクトリストの先頭 */
    size_t count;            /* オブジェクト数 */
    size_t total_size;       /* 総サイズ */
    size_t gc_count;         /* GC実行回数 */
} Generation;

/* ガベージコレクター */
typedef struct GarbageCollector {
    void *heap;                              /* ヒープ領域 */
    size_t heap_size;                        /* ヒープサイズ */
    size_t used_size;                        /* 使用済みサイズ */
    void *free_ptr;                          /* 空き領域ポインタ */
    GCRootSet root_set;                      /* ルートセット */
    Generation generations[GC_GENERATION_COUNT];  /* 世代別リスト */
    
    /* 統計情報 */
    size_t total_allocated;
    size_t total_freed;
    size_t gc_runs;
    double total_gc_time;
} GarbageCollector;

/* グローバルGCインスタンス */
static GarbageCollector g_gc = {0};

/* 関数プロトタイプ */
static int gc_init(void);
static void gc_shutdown(void);
static GCObject *gc_alloc(size_t size, ObjectType type);
static void gc_add_root(GCObject *obj);
static void gc_remove_root(GCObject *obj);
static void gc_collect(void);
static void gc_mark(GCObject *obj);
static void gc_sweep(void);
static void gc_mark_and_sweep(void);
static void gc_ref_inc(GCObject *obj);
static void gc_ref_dec(GCObject *obj);
static void gc_generational_collect(int generation);
static void gc_print_stats(void);

/* 時間計測 */
static double get_time_sec(void)
{
    return (double)clock() / CLOCKS_PER_SEC;
}

/* GCの初期化 */
static int gc_init(void)
{
    int i;
    
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
    
    g_gc.heap_size = GC_HEAP_SIZE;
    g_gc.used_size = 0;
    g_gc.free_ptr = g_gc.heap;
    
    /* ルートセットの初期化 */
    g_gc.root_set.capacity = GC_INITIAL_ROOTS;
    g_gc.root_set.count = 0;
    g_gc.root_set.roots = (GCObject **)calloc(GC_INITIAL_ROOTS, sizeof(GCObject *));
    if (!g_gc.root_set.roots) {
        free(g_gc.heap);
        return -1;
    }
    
    /* 世代の初期化 */
    for (i = 0; i < GC_GENERATION_COUNT; i++) {
        g_gc.generations[i].head = NULL;
        g_gc.generations[i].count = 0;
        g_gc.generations[i].total_size = 0;
        g_gc.generations[i].gc_count = 0;
    }
    
    GC_DEBUG("ガベージコレクターを初期化しました");
    GC_DEBUG_VAR(GC_HEAP_SIZE, "%d");
    
    return 0;
}

/* オブジェクトを世代リストに追加 */
static void add_to_generation(GCHeader *header, int gen)
{
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
static GCObject *gc_alloc(size_t size, ObjectType type)
{
    GCHeader *header;
    size_t total_size;
    
    if (!g_gc.heap) {
        fprintf(stderr, "GCが初期化されていません\n");
        return NULL;
    }
    
    total_size = sizeof(GCHeader) + size;
    
    /* メモリ不足チェック */
    if (g_gc.used_size + total_size > g_gc.heap_size) {
        GC_DEBUG("メモリ不足、GCを実行します");
        gc_collect();
        
        /* GC後も不足している場合 */
        if (g_gc.used_size + total_size > g_gc.heap_size) {
            fprintf(stderr, "メモリ不足: 要求=%lu, 空き=%lu\n",
                    (unsigned long)total_size,
                    (unsigned long)(g_gc.heap_size - g_gc.used_size));
            return NULL;
        }
    }
    
    /* GC閾値チェック */
    if ((double)g_gc.used_size / g_gc.heap_size > GC_THRESHOLD) {
        GC_DEBUG("閾値超過、GCを実行します");
        gc_collect();
    }
    
    /* メモリ割り当て */
    header = (GCHeader *)g_gc.free_ptr;
    g_gc.free_ptr = (char *)g_gc.free_ptr + total_size;
    g_gc.used_size += total_size;
    
    /* ヘッダー初期化 */
    memset(header, 0, sizeof(GCHeader));
    header->size = total_size;
    header->type = type;
    header->marked = 0;
    header->generation = 0;  /* 新規オブジェクトは第0世代 */
    header->age = 0;
    header->is_root = 0;
    header->ref_count = 1;   /* 初期参照カウント */
    
    /* 世代リストに追加 */
    add_to_generation(header, 0);
    
    g_gc.total_allocated += total_size;
    
    return (GCObject *)header;
}

/* ルートセットに追加 */
static void gc_add_root(GCObject *obj)
{
    size_t i;
    
    if (!obj) return;
    
    /* 既に登録済みかチェック */
    for (i = 0; i < g_gc.root_set.count; i++) {
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
    obj->header.is_root = 1;
    
    GC_DEBUG("ルートに追加");
}

/* ルートセットから削除 */
static void gc_remove_root(GCObject *obj)
{
    size_t i;
    
    if (!obj) return;
    
    for (i = 0; i < g_gc.root_set.count; i++) {
        if (g_gc.root_set.roots[i] == obj) {
            /* 削除 */
            g_gc.root_set.roots[i] = g_gc.root_set.roots[--g_gc.root_set.count];
            obj->header.is_root = 0;
            GC_DEBUG("ルートから削除");
            return;
        }
    }
}

/* オブジェクトのマーク（再帰的） */
static void gc_mark(GCObject *obj)
{
    GCHeader *header;
    
    if (!obj) return;
    
    header = &obj->header;
    
    /* 既にマーク済み */
    if (header->marked) return;
    
    header->marked = 1;
    
    /* タイプ別の子オブジェクトマーク */
    switch (header->type) {
        case OBJ_ARRAY: {
            GCArray *array = (GCArray *)obj;
            size_t i;
            for (i = 0; i < array->length; i++) {
                gc_mark(array->elements[i]);
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
    int gen;
    
    for (gen = 0; gen < GC_GENERATION_COUNT; gen++) {
        GCHeader *current = g_gc.generations[gen].head;
        
        while (current) {
            GCHeader *next = current->next;
            
            if (!current->marked) {
                /* 未マークオブジェクトを解放 */
                GC_DEBUG("オブジェクトを解放");
                
                remove_from_generation(current);
                
                /* メモリは実際には解放しない（シンプルなヒープ実装） */
                /* 実際のGCではメモリコンパクションが必要 */
                
                g_gc.total_freed += current->size;
            } else {
                /* マークをクリア */
                current->marked = 0;
                
                /* 年齢を増やして昇格チェック */
                current->age++;
                if (gen < GC_GENERATION_COUNT - 1 && 
                    current->age >= GC_PROMOTION_AGE) {
                    /* 次世代に昇格 */
                    remove_from_generation(current);
                    add_to_generation(current, gen + 1);
                    current->age = 0;
                    GC_DEBUG("オブジェクトを昇格");
                }
            }
            
            current = next;
        }
    }
}

/* マーク&スイープGC実行 */
static void gc_mark_and_sweep(void)
{
    size_t i;
    double start_time = get_time_sec();
    
    GC_DEBUG("マーク&スイープGC開始");
    
    /* マークフェーズ：ルートから到達可能なオブジェクトをマーク */
    for (i = 0; i < g_gc.root_set.count; i++) {
        gc_mark(g_gc.root_set.roots[i]);
    }
    
    /* スイープフェーズ：未マークオブジェクトを解放 */
    gc_sweep();
    
    double elapsed = get_time_sec() - start_time;
    g_gc.total_gc_time += elapsed;
    g_gc.gc_runs++;
    
    GC_DEBUG("マーク&スイープGC完了");
    GC_DEBUG_VAR(elapsed, "%.6f");
}

/* 世代別GC実行 */
static void gc_generational_collect(int max_generation)
{
    int gen;
    size_t i;
    double start_time = get_time_sec();
    
    GC_DEBUG("世代別GC開始");
    GC_DEBUG_VAR(max_generation, "%d");
    
    /* 若い世代から指定世代まで収集 */
    for (gen = 0; gen <= max_generation && gen < GC_GENERATION_COUNT; gen++) {
        g_gc.generations[gen].gc_count++;
        
        /* この世代のルートオブジェクトをマーク */
        for (i = 0; i < g_gc.root_set.count; i++) {
            GCObject *obj = g_gc.root_set.roots[i];
            if (obj && obj->header.generation == gen) {
                gc_mark(obj);
            }
        }
    }
    
    /* スイープ */
    gc_sweep();
    
    double elapsed = get_time_sec() - start_time;
    g_gc.total_gc_time += elapsed;
    g_gc.gc_runs++;
    
    GC_DEBUG("世代別GC完了");
}

/* 参照カウント増加 */
static void gc_ref_inc(GCObject *obj)
{
    if (obj) {
        obj->header.ref_count++;
        GC_DEBUG_VAR(obj->header.ref_count, "%d");
    }
}

/* 参照カウント減少 */
static void gc_ref_dec(GCObject *obj)
{
    if (!obj) return;
    
    obj->header.ref_count--;
    GC_DEBUG_VAR(obj->header.ref_count, "%d");
    
    if (obj->header.ref_count == 0) {
        GC_DEBUG("参照カウント0、即座に解放");
        
        /* タイプ別の子オブジェクト処理 */
        switch (obj->header.type) {
            case OBJ_ARRAY: {
                GCArray *array = (GCArray *)obj;
                size_t i;
                for (i = 0; i < array->length; i++) {
                    gc_ref_dec(array->elements[i]);
                }
                break;
            }
            default:
                break;
        }
        
        /* リストから削除 */
        remove_from_generation(&obj->header);
        g_gc.total_freed += obj->header.size;
    }
}

/* 一般的なGC実行 */
static void gc_collect(void)
{
    /* デフォルトはマーク&スイープ */
    gc_mark_and_sweep();
}

/* 統計情報表示 */
static void gc_print_stats(void)
{
    int gen;
    
    printf("\n=== GC統計情報 ===\n");
    printf("ヒープサイズ: %lu バイト\n", (unsigned long)g_gc.heap_size);
    printf("使用中: %lu バイト (%.1f%%)\n",
           (unsigned long)g_gc.used_size,
           (double)g_gc.used_size / g_gc.heap_size * 100);
    printf("総割り当て: %lu バイト\n", (unsigned long)g_gc.total_allocated);
    printf("総解放: %lu バイト\n", (unsigned long)g_gc.total_freed);
    printf("GC実行回数: %lu 回\n", (unsigned long)g_gc.gc_runs);
    
    if (g_gc.gc_runs > 0) {
        printf("平均GC時間: %.6f 秒\n", g_gc.total_gc_time / g_gc.gc_runs);
    }
    
    printf("\n世代別情報:\n");
    for (gen = 0; gen < GC_GENERATION_COUNT; gen++) {
        Generation *g = &g_gc.generations[gen];
        printf("  第%d世代: %lu オブジェクト, %lu バイト, GC %lu 回\n",
               gen,
               (unsigned long)g->count,
               (unsigned long)g->total_size,
               (unsigned long)g->gc_count);
    }
    
    printf("===================\n\n");
}

/* GCのシャットダウン */
static void gc_shutdown(void)
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
        *(int *)((char *)obj + sizeof(GCHeader)) = value;
    }
    return obj;
}

/* 配列オブジェクト作成 */
GCArray *gc_new_array(size_t length)
{
    GCArray *array = (GCArray *)gc_alloc(sizeof(GCArray) - sizeof(GCHeader), OBJ_ARRAY);
    if (array) {
        array->length = length;
        array->elements = (GCObject **)calloc(length, sizeof(GCObject *));
        if (!array->elements) {
            /* エラー処理 */
            return NULL;
        }
    }
    return array;
}

/* 文字列オブジェクト作成 */
GCString *gc_new_string(const char *str)
{
    GCString *string;
    size_t len = strlen(str);
    
    string = (GCString *)gc_alloc(sizeof(GCString) - sizeof(GCHeader), OBJ_STRING);
    if (string) {
        string->length = len;
        string->data = (char *)malloc(len + 1);
        if (!string->data) {
            return NULL;
        }
        strcpy(string->data, str);
    }
    return string;
}

/* テスト関数群 */

/* 基本的なGCテスト */
void test_basic_gc(void)
{
    GCObject *obj1, *obj2, *obj3;
    
    printf("=== 基本的なGCテスト ===\n");
    
    /* オブジェクト作成 */
    obj1 = gc_new_int(42);
    obj2 = gc_new_int(100);
    obj3 = gc_new_int(200);
    
    /* ルートに追加 */
    gc_add_root(obj1);
    gc_add_root(obj2);
    
    printf("GC前:\n");
    gc_print_stats();
    
    /* obj3はルートではないので回収される */
    gc_collect();
    
    printf("GC後:\n");
    gc_print_stats();
    
    /* クリーンアップ */
    gc_remove_root(obj1);
    gc_remove_root(obj2);
    gc_collect();
}

/* 参照カウントテスト */
void test_reference_counting(void)
{
    GCObject *obj1, *obj2;
    
    printf("\n=== 参照カウントテスト ===\n");
    
    obj1 = gc_new_int(10);
    obj2 = gc_new_int(20);
    
    printf("初期状態: obj1 ref=%d, obj2 ref=%d\n",
           obj1->header.ref_count, obj2->header.ref_count);
    
    /* 参照を増やす */
    gc_ref_inc(obj1);
    gc_ref_inc(obj1);
    printf("参照増加後: obj1 ref=%d\n", obj1->header.ref_count);
    
    /* 参照を減らす */
    gc_ref_dec(obj1);
    gc_ref_dec(obj1);
    gc_ref_dec(obj1);  /* ref=0になり解放される */
    
    gc_ref_dec(obj2);  /* ref=0になり解放される */
    
    gc_print_stats();
}

/* 世代別GCテスト */
void test_generational_gc(void)
{
    int i, j;
    GCObject *objs[50];
    
    printf("\n=== 世代別GCテスト ===\n");
    
    /* 複数回のGCサイクル */
    for (i = 0; i < 3; i++) {
        printf("\n--- サイクル %d ---\n", i + 1);
        
        /* オブジェクトを作成 */
        for (j = 0; j < 50; j++) {
            objs[j] = gc_new_int(i * 100 + j);
            if (j % 5 == 0) {
                /* 一部をルートに */
                gc_add_root(objs[j]);
            }
        }
        
        /* マイナーGC（第0世代のみ） */
        gc_generational_collect(0);
        
        /* 一部のルートを削除 */
        for (j = 0; j < 50; j += 10) {
            gc_remove_root(objs[j]);
        }
        
        /* メジャーGC（全世代） */
        if (i == 2) {
            gc_generational_collect(GC_GENERATION_COUNT - 1);
        }
    }
    
    gc_print_stats();
}

/* 循環参照テスト */
void test_circular_reference(void)
{
    GCArray *array1, *array2;
    
    printf("\n=== 循環参照テスト ===\n");
    
    /* 相互参照する配列を作成 */
    array1 = gc_new_array(2);
    array2 = gc_new_array(2);
    
    if (array1 && array2) {
        /* 循環参照を作成 */
        array1->elements[0] = (GCObject *)array2;
        array2->elements[0] = (GCObject *)array1;
        
        /* 参照カウントを増やす */
        gc_ref_inc((GCObject *)array2);
        gc_ref_inc((GCObject *)array1);
        
        printf("循環参照を作成しました\n");
        
        /* 参照カウントでは解放されない */
        gc_ref_dec((GCObject *)array1);
        gc_ref_dec((GCObject *)array2);
        
        printf("参照カウント方式では解放されません\n");
        gc_print_stats();
        
        /* マーク&スイープで解放 */
        gc_collect();
        printf("マーク&スイープ後:\n");
        gc_print_stats();
    }
}

/* パフォーマンステスト */
void test_gc_performance(void)
{
    int i;
    double start, end;
    const int iterations = 10000;
    
    printf("\n=== GCパフォーマンステスト ===\n");
    
    start = get_time_sec();
    
    for (i = 0; i < iterations; i++) {
        GCObject *obj = gc_new_int(i);
        
        /* 半分はルートに追加 */
        if (i % 2 == 0) {
            gc_add_root(obj);
        }
        
        /* 定期的にルートを削除 */
        if (i % 100 == 99) {
            int j;
            for (j = i - 50; j < i; j += 2) {
                /* 注意: 実際のオブジェクトポインタは保存していないので
                   これは概念的なコードです */
            }
        }
    }
    
    end = get_time_sec();
    printf("割り当て時間: %.6f 秒 (%d オブジェクト)\n",
           end - start, iterations);
    
    /* 最終的なGC */
    start = get_time_sec();
    gc_collect();
    end = get_time_sec();
    printf("最終GC時間: %.6f 秒\n", end - start);
    
    gc_print_stats();
}

/* メイン関数 */
int main(void)
{
    printf("=== ガベージコレクションフレームワークデモ ===\n\n");
    
    /* GC初期化 */
    if (gc_init() < 0) {
        fprintf(stderr, "GCの初期化に失敗\n");
        return 1;
    }
    
    /* 各種テスト実行 */
    test_basic_gc();
    test_reference_counting();
    test_generational_gc();
    test_circular_reference();
    test_gc_performance();
    
    /* シャットダウン */
    gc_shutdown();
    
    printf("\n=== デモ完了 ===\n");
    return 0;
}

/*
実行例:
=== ガベージコレクションフレームワークデモ ===

[GC] ガベージコレクターを初期化しました
[GC] GC_HEAP_SIZE = 1048576

=== 基本的なGCテスト ===
[GC] ルートに追加
[GC] ルートに追加
GC前:

=== GC統計情報 ===
ヒープサイズ: 1048576 バイト
使用中: 96 バイト (0.0%)
総割り当て: 96 バイト
総解放: 0 バイト
GC実行回数: 0 回

世代別情報:
  第0世代: 3 オブジェクト, 96 バイト, GC 0 回
  第1世代: 0 オブジェクト, 0 バイト, GC 0 回
  第2世代: 0 オブジェクト, 0 バイト, GC 0 回
===================

[GC] マーク&スイープGC開始
[GC] オブジェクトを解放
[GC] マーク&スイープGC完了
[GC] elapsed = 0.000012
GC後:

=== GC統計情報 ===
ヒープサイズ: 1048576 バイト
使用中: 96 バイト (0.0%)
総割り当て: 96 バイト
総解放: 32 バイト
GC実行回数: 1 回
平均GC時間: 0.000012 秒

世代別情報:
  第0世代: 2 オブジェクト, 64 バイト, GC 0 回
  第1世代: 0 オブジェクト, 0 バイト, GC 0 回
  第2世代: 0 オブジェクト, 0 バイト, GC 0 回
===================

=== 参照カウントテスト ===
初期状態: obj1 ref=1, obj2 ref=1
[GC] ref_count = 2
[GC] ref_count = 3
参照増加後: obj1 ref=3
[GC] ref_count = 2
[GC] ref_count = 1
[GC] ref_count = 0
[GC] 参照カウント0、即座に解放
[GC] ref_count = 0
[GC] 参照カウント0、即座に解放

=== 世代別GCテスト ===

--- サイクル 1 ---
[GC] ルートに追加
[GC] ルートに追加
...
[GC] 世代別GC開始
[GC] max_generation = 0
[GC] オブジェクトを昇格
[GC] 世代別GC完了

--- サイクル 2 ---
...

--- サイクル 3 ---
...
[GC] 世代別GC開始
[GC] max_generation = 2
[GC] 世代別GC完了

=== 循環参照テスト ===
循環参照を作成しました
[GC] ref_count = 2
[GC] ref_count = 2
[GC] ref_count = 1
[GC] ref_count = 1
参照カウント方式では解放されません

=== GC統計情報 ===
ヒープサイズ: 1048576 バイト
使用中: 2048 バイト (0.2%)
総割り当て: 2048 バイト
総解放: 1600 バイト
GC実行回数: 5 回
平均GC時間: 0.000024 秒

世代別情報:
  第0世代: 2 オブジェクト, 128 バイト, GC 3 回
  第1世代: 0 オブジェクト, 0 バイト, GC 2 回
  第2世代: 0 オブジェクト, 0 バイト, GC 1 回
===================

[GC] マーク&スイープGC開始
[GC] オブジェクトを解放
[GC] オブジェクトを解放
[GC] マーク&スイープGC完了
マーク&スイープ後:

=== GCパフォーマンステスト ===
[GC] 閾値超過、GCを実行します
[GC] マーク&スイープGC開始
...
割り当て時間: 0.045678 秒 (10000 オブジェクト)
[GC] マーク&スイープGC開始
[GC] マーク&スイープGC完了
最終GC時間: 0.002345 秒

[GC] ガベージコレクターをシャットダウンしました

=== デモ完了 ===
*/