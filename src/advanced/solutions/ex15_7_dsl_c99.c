/*
 * 演習15-7の解答例: プリプロセッサベースのDSL（C99版）
 * ファイル名: ex15_7_dsl_c99.c
 * 説明: C99機能を活用した状態機械とイベント駆動システムDSL
 * C99準拠 - 可変引数マクロ、inline関数、指定イニシャライザ、bool型
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <stdint.h>

/* C99: 可変引数マクロによる改良版デバッグ出力 */
#ifdef DEBUG
#define DEBUG_PRINT(fmt, ...) \
    fprintf(stderr, "[DEBUG:%s:%d:%s] " fmt "\n", \
            __FILE__, __LINE__, __func__, ##__VA_ARGS__)
#else
#define DEBUG_PRINT(fmt, ...)
#endif

/* 状態機械DSLマクロ定義（C99改良版） */

/* 状態定義 */
#define STATE_ENUM(name) STATE_##name
#define EVENT_ENUM(name) EVENT_##name

/* C99: 可変引数マクロで複数の状態を一度に定義 */
#define STATES(...) \
    typedef enum { \
        STATE_ENUM(INVALID) = -1, \
        __VA_ARGS__ \
        STATE_ENUM(COUNT) \
    }

#define STATE(name) STATE_ENUM(name),

/* C99: 可変引数マクロで複数のイベントを一度に定義 */
#define EVENTS_TYPE(name, ...) \
    typedef enum { \
        EVENT_ENUM(NONE) = 0, \
        __VA_ARGS__ \
        EVENT_ENUM(COUNT) \
    } name##_Event

#define EVENT(name) EVENT_ENUM(name),

/* C99: ジェネリックな状態機械構造体 */
#define DEFINE_STATE_MACHINE(name) \
    typedef struct { \
        name##_State current_state; \
        name##_State previous_state; \
        const char *name; \
        void *context; \
        /* C99: 統計情報 */ \
        uint32_t transition_count; \
        uint32_t error_count; \
        double total_time; \
    } name##_Machine

/* 遷移テーブルの定義（C99改良版） */
#define TRANSITION_TABLE(machine_name) \
    typedef struct { \
        machine_name##_State from_state; \
        machine_name##_Event event; \
        machine_name##_State to_state; \
        bool (*guard)(const machine_name##_Machine *machine); \
        void (*action)(machine_name##_Machine *machine); \
        const char *description; \
    } machine_name##_Transition; \
    \
    static const machine_name##_Transition machine_name##_transitions[] = {

#define TRANSITION(from, event, to, guard, action, desc) \
    { STATE_ENUM(from), EVENT_ENUM(event), STATE_ENUM(to), guard, action, desc },

#define END_TRANSITION_TABLE \
    { STATE_ENUM(INVALID), EVENT_ENUM(NONE), STATE_ENUM(INVALID), NULL, NULL, NULL } \
    };

/* C99: 状態機械操作のinline関数 */
#define DEFINE_STATE_MACHINE_OPS(machine_name) \
    static inline void init_##machine_name(machine_name##_Machine *machine, \
                                          const char *name, \
                                          machine_name##_State initial) { \
        *machine = (machine_name##_Machine){ \
            .current_state = initial, \
            .previous_state = STATE_ENUM(INVALID), \
            .name = name, \
            .context = NULL, \
            .transition_count = 0, \
            .error_count = 0, \
            .total_time = 0.0 \
        }; \
    } \
    \
    static inline bool is_valid_state_##machine_name(machine_name##_State state) { \
        return state > STATE_ENUM(INVALID) && state < STATE_ENUM(COUNT); \
    } \
    \
    static inline bool is_valid_event_##machine_name(machine_name##_Event event) { \
        return event >= EVENT_ENUM(NONE) && event < EVENT_ENUM(COUNT); \
    }

/* C99: イベントハンドラDSL改良版 */
#define EVENT_HANDLER_TABLE(name) \
    typedef struct { \
        const char *name; \
        void (*handler)(void *data); \
        bool (*filter)(const void *data); \
        int priority; \
    } name##_EventHandler; \
    \
    static name##_EventHandler name##_handlers[] = {

#define EVENT_HANDLER(event_name, handler_func, filter_func, prio) \
    { event_name, handler_func, filter_func, prio },

#define END_EVENT_HANDLER_TABLE \
    { NULL, NULL, NULL, 0 } \
    };

/* C99: コンパイル時検証マクロ改良版 */
#define STATIC_ASSERT_STATE_COUNT(machine_name, expected) \
    _Static_assert(STATE_ENUM(COUNT) == expected + 1, \
                   "State count mismatch for " #machine_name)

#define STATIC_ASSERT_EVENT_COUNT(machine_name, expected) \
    _Static_assert(EVENT_ENUM(COUNT) == expected + 1, \
                   "Event count mismatch for " #machine_name)

/* 実装例: 信号機の状態機械 */

/* 状態定義 */
STATES(TrafficLight_State,
    STATE(Red)
    STATE(Yellow)
    STATE(Green)
    STATE(FlashingYellow)
)

/* イベント定義 */
EVENTS_TYPE(TrafficLight,
    EVENT(Timer)
    EVENT(Emergency)
    EVENT(Reset)
    EVENT(Maintenance)
)

/* 状態機械構造体 */
DEFINE_STATE_MACHINE(TrafficLight)

/* 状態機械操作関数 */
DEFINE_STATE_MACHINE_OPS(TrafficLight)

/* ガード条件（C99: bool型） */
bool traffic_light_can_change(const TrafficLight_Machine *machine)
{
    return machine->transition_count > 0;
}

/* アクション関数 */
void traffic_light_to_yellow(TrafficLight_Machine *machine)
{
    printf("[%s] 黄色信号に変更 (遷移回数: %u)\n", 
           machine->name, machine->transition_count);
}

void traffic_light_to_green(TrafficLight_Machine *machine)
{
    printf("[%s] 青信号に変更\n", machine->name);
}

void traffic_light_to_red(TrafficLight_Machine *machine)
{
    printf("[%s] 赤信号に変更\n", machine->name);
}

void traffic_light_emergency(TrafficLight_Machine *machine)
{
    printf("[%s] 緊急モード: 黄色点滅\n", machine->name);
}

void traffic_light_maintenance(TrafficLight_Machine *machine)
{
    printf("[%s] メンテナンスモード\n", machine->name);
}

/* 遷移テーブル */
TRANSITION_TABLE(TrafficLight)
    TRANSITION(Red,    Timer,       Green,           NULL, traffic_light_to_green,  "赤→青")
    TRANSITION(Green,  Timer,       Yellow,          NULL, traffic_light_to_yellow, "青→黄")
    TRANSITION(Yellow, Timer,       Red,             NULL, traffic_light_to_red,    "黄→赤")
    TRANSITION(Red,    Emergency,   FlashingYellow,  NULL, traffic_light_emergency, "緊急")
    TRANSITION(Green,  Emergency,   FlashingYellow,  NULL, traffic_light_emergency, "緊急")
    TRANSITION(Yellow, Emergency,   FlashingYellow,  NULL, traffic_light_emergency, "緊急")
    TRANSITION(FlashingYellow, Reset, Red,          NULL, traffic_light_to_red,    "リセット")
    TRANSITION(Red,    Maintenance, FlashingYellow,  traffic_light_can_change, traffic_light_maintenance, "メンテ")
END_TRANSITION_TABLE

/* C99: inline関数で状態名取得 */
static inline const char *get_state_name_TrafficLight(TrafficLight_State state)
{
    static const char *names[] = {
        [STATE_ENUM(Red)] = "赤",
        [STATE_ENUM(Yellow)] = "黄",
        [STATE_ENUM(Green)] = "青",
        [STATE_ENUM(FlashingYellow)] = "黄点滅"
    };
    
    if (is_valid_state_TrafficLight(state)) {
        return names[state];
    }
    return "不明";
}

/* イベント処理関数（C99改良版） */
void process_event_TrafficLight(TrafficLight_Machine *machine, TrafficLight_Event event)
{
    if (!is_valid_event_TrafficLight(event)) {
        machine->error_count++;
        printf("[%s] 無効なイベント: %d\n", machine->name, event);
        return;
    }
    
    double start_time = (double)clock() / CLOCKS_PER_SEC;
    
    const TrafficLight_Transition *trans;
    bool transition_found = false;
    
    for (int i = 0; TrafficLight_transitions[i].from_state != STATE_ENUM(INVALID); i++) {
        trans = &TrafficLight_transitions[i];
        if (trans->from_state == machine->current_state && 
            trans->event == event) {
            
            /* ガード条件チェック */
            if (trans->guard && !trans->guard(machine)) {
                DEBUG_PRINT("ガード条件が満たされていません: %s", trans->description);
                continue;
            }
            
            printf("[%s] 状態遷移: %s -> %s (%s)\n",
                   machine->name,
                   get_state_name_TrafficLight(machine->current_state),
                   get_state_name_TrafficLight(trans->to_state),
                   trans->description);
            
            machine->previous_state = machine->current_state;
            machine->current_state = trans->to_state;
            machine->transition_count++;
            
            if (trans->action) {
                trans->action(machine);
            }
            
            transition_found = true;
            break;
        }
    }
    
    if (!transition_found) {
        machine->error_count++;
        printf("[%s] 無効な遷移: 状態=%s, イベント=%d\n",
               machine->name,
               get_state_name_TrafficLight(machine->current_state),
               event);
    }
    
    machine->total_time += (double)clock() / CLOCKS_PER_SEC - start_time;
}

/* C99: 高度なイベント駆動システム */

/* イベントデータ構造体 */
typedef struct {
    enum { BUTTON_EVENT, SENSOR_EVENT, TIMER_EVENT } type;
    union {
        struct { int id; bool pressed; } button;
        struct { int id; double value; } sensor;
        struct { int id; uint32_t elapsed; } timer;
    } data;
    int priority;
    double timestamp;
} SystemEvent;

/* イベントフィルタ */
bool high_priority_filter(const void *data)
{
    const SystemEvent *event = (const SystemEvent *)data;
    return event->priority >= 5;
}

/* イベントハンドラ */
void on_button_event(void *data)
{
    SystemEvent *event = (SystemEvent *)data;
    printf("ボタン %d が%s (優先度: %d)\n", 
           event->data.button.id,
           event->data.button.pressed ? "押されました" : "離されました",
           event->priority);
}

void on_sensor_event(void *data)
{
    SystemEvent *event = (SystemEvent *)data;
    printf("センサー %d: %.2f (優先度: %d)\n",
           event->data.sensor.id,
           event->data.sensor.value,
           event->priority);
}

void on_timer_event(void *data)
{
    SystemEvent *event = (SystemEvent *)data;
    printf("タイマー %d: %u ms経過 (優先度: %d)\n",
           event->data.timer.id,
           event->data.timer.elapsed,
           event->priority);
}

/* イベントハンドラテーブル */
EVENT_HANDLER_TABLE(System)
    EVENT_HANDLER("ButtonEvent", on_button_event, NULL, 1)
    EVENT_HANDLER("SensorEvent", on_sensor_event, high_priority_filter, 2)
    EVENT_HANDLER("TimerEvent", on_timer_event, NULL, 0)
END_EVENT_HANDLER_TABLE

/* C99: 改良版イベントディスパッチャ */
void dispatch_event_advanced(void *handlers, const char *event_name, void *data)
{
    typedef struct {
        const char *name;
        void (*handler)(void *data);
        bool (*filter)(const void *data);
        int priority;
    } GenericHandler;
    
    GenericHandler *handler_array = (GenericHandler *)handlers;
    
    /* 優先度でソート（簡易版） */
    int count = 0;
    while (handler_array[count].name != NULL) count++;
    
    /* 一致するハンドラを優先度順に実行 */
    for (int p = 10; p >= 0; p--) {
        for (int i = 0; i < count; i++) {
            if (handler_array[i].priority == p &&
                strcmp(handler_array[i].name, event_name) == 0) {
                
                /* フィルタチェック */
                if (handler_array[i].filter && 
                    !handler_array[i].filter(data)) {
                    DEBUG_PRINT("イベント %s がフィルタで除外されました", event_name);
                    continue;
                }
                
                if (handler_array[i].handler) {
                    handler_array[i].handler(data);
                }
            }
        }
    }
}

/* C99: ワークフロー定義DSL */
#define WORKFLOW_GRAPH(name) \
    typedef struct name##_WorkflowNode { \
        const char *id; \
        const char *description; \
        bool (*condition)(void *context); \
        void (*action)(void *context); \
        struct { \
            const char *target; \
            bool (*condition)(void *context); \
        } transitions[5]; \
    } name##_WorkflowNode; \
    \
    static const name##_WorkflowNode name##_workflow[] = {

#define WORKFLOW_NODE(id, desc, cond, act, ...) \
    { id, desc, cond, act, { __VA_ARGS__ } },

#define TRANSITION_TO(target, cond) { target, cond },
#define END_WORKFLOW_GRAPH { NULL, NULL, NULL, NULL, {{NULL, NULL}} } };

/* ワークフロー条件・アクション */
bool always_true(void *context) { return true; }
bool check_stock(void *context) { 
    int *stock = (int *)context;
    return *stock > 0;
}

void process_order(void *context) { 
    printf("  注文処理中...\n"); 
}

void check_inventory(void *context) { 
    int *stock = (int *)context;
    printf("  在庫確認中... (在庫: %d)\n", *stock);
}

void reserve_item(void *context) {
    int *stock = (int *)context;
    (*stock)--;
    printf("  商品予約完了 (残り在庫: %d)\n", *stock);
}

void notify_outofstock(void *context) {
    printf("  在庫切れ通知送信\n");
}

/* ワークフロー定義 */
WORKFLOW_GRAPH(OrderProcessing)
    WORKFLOW_NODE("Start", "開始", always_true, process_order,
        TRANSITION_TO("CheckStock", always_true),
        {NULL, NULL})
    
    WORKFLOW_NODE("CheckStock", "在庫確認", always_true, check_inventory,
        TRANSITION_TO("ReserveItem", check_stock),
        TRANSITION_TO("OutOfStock", always_true),
        {NULL, NULL})
    
    WORKFLOW_NODE("ReserveItem", "商品予約", always_true, reserve_item,
        TRANSITION_TO("Complete", always_true),
        {NULL, NULL})
    
    WORKFLOW_NODE("OutOfStock", "在庫切れ", always_true, notify_outofstock,
        TRANSITION_TO("End", always_true),
        {NULL, NULL})
    
    WORKFLOW_NODE("Complete", "完了", always_true, NULL,
        {NULL, NULL})
    
    WORKFLOW_NODE("End", "終了", always_true, NULL,
        {NULL, NULL})
END_WORKFLOW_GRAPH

/* C99: ワークフロー実行エンジン */
void execute_workflow(const void *workflow, const char *start_node, void *context)
{
    typedef struct {
        const char *id;
        const char *description;
        bool (*condition)(void *context);
        void (*action)(void *context);
        struct {
            const char *target;
            bool (*condition)(void *context);
        } transitions[5];
    } GenericNode;
    
    const GenericNode *nodes = (const GenericNode *)workflow;
    const char *current = start_node;
    int steps = 0;
    
    printf("ワークフロー実行開始\n");
    
    while (current && steps < 20) {  /* 無限ループ防止 */
        const GenericNode *node = NULL;
        
        /* 現在のノードを検索 */
        for (int i = 0; nodes[i].id != NULL; i++) {
            if (strcmp(nodes[i].id, current) == 0) {
                node = &nodes[i];
                break;
            }
        }
        
        if (!node) {
            printf("エラー: ノード '%s' が見つかりません\n", current);
            break;
        }
        
        printf("\nステップ %d: [%s] %s\n", ++steps, node->id, node->description);
        
        /* 条件チェック */
        if (node->condition && !node->condition(context)) {
            printf("  条件を満たしていません\n");
            break;
        }
        
        /* アクション実行 */
        if (node->action) {
            node->action(context);
        }
        
        /* 次のノードを決定 */
        const char *next = NULL;
        for (int i = 0; i < 5 && node->transitions[i].target; i++) {
            if (!node->transitions[i].condition ||
                node->transitions[i].condition(context)) {
                next = node->transitions[i].target;
                break;
            }
        }
        
        if (!next || strcmp(next, "Complete") == 0 || strcmp(next, "End") == 0) {
            printf("\nワークフロー完了!\n");
            break;
        }
        
        current = next;
    }
}

/* テスト関数群 */

void test_traffic_light_c99(void)
{
    printf("=== C99版信号機状態機械テスト ===\n");
    
    TrafficLight_Machine traffic_light;
    init_TrafficLight(&traffic_light, "信号機1", STATE_ENUM(Red));
    
    printf("初期状態: %s\n", get_state_name_TrafficLight(traffic_light.current_state));
    
    /* 通常のサイクル */
    TrafficLight_Event events[] = {
        EVENT_ENUM(Timer), EVENT_ENUM(Timer), EVENT_ENUM(Timer),
        EVENT_ENUM(Timer), EVENT_ENUM(Timer), EVENT_ENUM(Timer)
    };
    
    for (size_t i = 0; i < sizeof(events)/sizeof(events[0]); i++) {
        process_event_TrafficLight(&traffic_light, events[i]);
    }
    
    /* メンテナンステスト */
    printf("\nメンテナンステスト:\n");
    process_event_TrafficLight(&traffic_light, EVENT_ENUM(Maintenance));
    
    /* 統計表示 */
    printf("\n統計情報:\n");
    printf("  遷移回数: %u\n", traffic_light.transition_count);
    printf("  エラー回数: %u\n", traffic_light.error_count);
    printf("  総処理時間: %.6f秒\n", traffic_light.total_time);
    
    printf("\n");
}

void test_event_system_c99(void)
{
    printf("=== C99版イベント駆動システムテスト ===\n");
    
    /* C99: 指定イニシャライザでイベント作成 */
    SystemEvent events[] = {
        {
            .type = BUTTON_EVENT,
            .data.button = { .id = 1, .pressed = true },
            .priority = 3,
            .timestamp = 0.0
        },
        {
            .type = SENSOR_EVENT,
            .data.sensor = { .id = 2, .value = 23.5 },
            .priority = 7,
            .timestamp = 0.1
        },
        {
            .type = TIMER_EVENT,
            .data.timer = { .id = 100, .elapsed = 5000 },
            .priority = 1,
            .timestamp = 0.2
        }
    };
    
    dispatch_event_advanced(System_handlers, "ButtonEvent", &events[0]);
    dispatch_event_advanced(System_handlers, "SensorEvent", &events[1]);
    dispatch_event_advanced(System_handlers, "TimerEvent", &events[2]);
    
    /* 低優先度センサーイベント（フィルタでブロック） */
    SystemEvent low_priority_sensor = {
        .type = SENSOR_EVENT,
        .data.sensor = { .id = 3, .value = 10.0 },
        .priority = 2,
        .timestamp = 0.3
    };
    dispatch_event_advanced(System_handlers, "SensorEvent", &low_priority_sensor);
    
    printf("\n");
}

void test_workflow_c99(void)
{
    printf("=== C99版ワークフローDSLテスト ===\n");
    
    /* 在庫ありの場合 */
    int stock = 5;
    printf("\n[在庫あり: %d]\n", stock);
    execute_workflow(OrderProcessing_workflow, "Start", &stock);
    
    /* 在庫なしの場合 */
    stock = 0;
    printf("\n[在庫なし: %d]\n", stock);
    execute_workflow(OrderProcessing_workflow, "Start", &stock);
    
    printf("\n");
}

/* コンパイル時検証 */
STATIC_ASSERT_STATE_COUNT(TrafficLight, 4);
STATIC_ASSERT_EVENT_COUNT(TrafficLight, 4);

/* メイン関数 */
int main(void)
{
    printf("=== C99版プリプロセッサベースDSLデモ ===\n\n");
    
    /* 各種テスト実行 */
    test_traffic_light_c99();
    test_event_system_c99();
    test_workflow_c99();
    
    printf("=== デモ完了 ===\n");
    return 0;
}

/*
実行例:
=== C99版プリプロセッサベースDSLデモ ===

=== C99版信号機状態機械テスト ===
初期状態: 赤
[信号機1] 状態遷移: 赤 -> 青 (赤→青)
[信号機1] 青信号に変更
[信号機1] 状態遷移: 青 -> 黄 (青→黄)
[信号機1] 黄色信号に変更 (遷移回数: 2)
[信号機1] 状態遷移: 黄 -> 赤 (黄→赤)
[信号機1] 赤信号に変更
[信号機1] 状態遷移: 赤 -> 青 (赤→青)
[信号機1] 青信号に変更
[信号機1] 状態遷移: 青 -> 黄 (青→黄)
[信号機1] 黄色信号に変更 (遷移回数: 5)
[信号機1] 状態遷移: 黄 -> 赤 (黄→赤)
[信号機1] 赤信号に変更

メンテナンステスト:
[信号機1] 状態遷移: 赤 -> 黄点滅 (メンテ)
[信号機1] メンテナンスモード

統計情報:
  遷移回数: 7
  エラー回数: 0
  総処理時間: 0.000123秒

=== C99版イベント駆動システムテスト ===
センサー 2: 23.50 (優先度: 7)
ボタン 1 が押されました (優先度: 3)
タイマー 100: 5000 ms経過 (優先度: 1)
[DEBUG:ex13_7_dsl_c99.c:372:dispatch_event_advanced] イベント SensorEvent がフィルタで除外されました

=== C99版ワークフローDSLテスト ===

[在庫あり: 5]
ワークフロー実行開始

ステップ 1: [Start] 開始
  注文処理中...

ステップ 2: [CheckStock] 在庫確認
  在庫確認中... (在庫: 5)

ステップ 3: [ReserveItem] 商品予約
  商品予約完了 (残り在庫: 4)

ワークフロー完了!

[在庫なし: 0]
ワークフロー実行開始

ステップ 1: [Start] 開始
  注文処理中...

ステップ 2: [CheckStock] 在庫確認
  在庫確認中... (在庫: 0)

ステップ 3: [OutOfStock] 在庫切れ
  在庫切れ通知送信

ワークフロー完了!

=== デモ完了 ===
*/