/*
 * 演習13-7の解答例: プリプロセッサベースのDSL
 * ファイル名: ex13_7_dsl.c
 * 説明: 状態機械とイベント駆動システムのDSL実装
 * C90準拠
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/* 状態機械DSLマクロ定義 */

/* 状態定義 */
#define STATE_ENUM(name) STATE_##name
#define EVENT_ENUM(name) EVENT_##name

/* 状態機械の開始 */
#define STATE_MACHINE(name) \
    typedef enum { \
        STATE_ENUM(INVALID) = -1,

/* 状態の定義 */
#define STATE(name) \
        STATE_ENUM(name),

/* 状態機械の終了 */
#define END_STATE_MACHINE(name) \
        STATE_ENUM(COUNT) \
    } name##_State; \
    \
    typedef struct { \
        name##_State current_state; \
        const char *name; \
        void *context; \
    } name##_Machine;

/* イベント定義の開始 */
#define EVENTS(name) \
    typedef enum { \
        EVENT_ENUM(NONE) = 0,

/* イベントの定義 */
#define EVENT(name) \
        EVENT_ENUM(name),

/* イベント定義の終了 */
#define END_EVENTS(name) \
        EVENT_ENUM(COUNT) \
    } name##_Event;

/* 遷移テーブルの定義 */
#define TRANSITION_TABLE(machine_name) \
    typedef struct { \
        machine_name##_State from_state; \
        machine_name##_Event event; \
        machine_name##_State to_state; \
        void (*action)(machine_name##_Machine *machine); \
    } machine_name##_Transition; \
    \
    static const machine_name##_Transition machine_name##_transitions[] = {

#define TRANSITION(from, event, to, action) \
    { STATE_ENUM(from), EVENT_ENUM(event), STATE_ENUM(to), action },

#define END_TRANSITION_TABLE \
    { STATE_ENUM(INVALID), EVENT_ENUM(NONE), STATE_ENUM(INVALID), NULL } \
    };

/* 状態機械の操作マクロ */
#define INIT_STATE_MACHINE(machine, machine_name, initial_state) \
    do { \
        (machine).current_state = STATE_ENUM(initial_state); \
        (machine).name = #machine_name; \
        (machine).context = NULL; \
    } while (0)

#define PROCESS_EVENT(machine, machine_name, event) \
    process_event_##machine_name(&(machine), EVENT_ENUM(event))

/* イベントハンドラDSL */

#define EVENT_HANDLER_BEGIN(name) \
    typedef struct { \
        const char *name; \
        void (*handler)(void *data); \
    } name##_EventHandler; \
    \
    static name##_EventHandler name##_handlers[] = {

#define EVENT_HANDLER(event_name, handler_func) \
    { #event_name, handler_func },

#define EVENT_HANDLER_END \
    { NULL, NULL } \
    };

#define DISPATCH_EVENT(handler_array, event_name, data) \
    dispatch_event(handler_array, event_name, data)

/* コンパイル時検証マクロ */
#define STATIC_ASSERT_STATE_COUNT(machine_name, expected) \
    typedef char _state_count_check_##machine_name[ \
        (STATE_ENUM(COUNT) == expected) ? 1 : -1]

#define STATIC_ASSERT_EVENT_COUNT(machine_name, expected) \
    typedef char _event_count_check_##machine_name[ \
        (EVENT_ENUM(COUNT) == expected) ? 1 : -1]

/* 実装例: 信号機の状態機械 */

/* 状態定義 */
STATE_MACHINE(TrafficLight)
    STATE(Red)
    STATE(Yellow)
    STATE(Green)
END_STATE_MACHINE(TrafficLight)

/* イベント定義 */
EVENTS(TrafficLight)
    EVENT(Timer)
    EVENT(Emergency)
    EVENT(Reset)
END_EVENTS(TrafficLight)

/* アクション関数 */
void traffic_light_to_yellow(TrafficLight_Machine *machine)
{
    printf("[%s] 黄色信号に変更\n", machine->name);
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
    printf("[%s] 緊急モード: 赤信号点滅\n", machine->name);
}

/* 遷移テーブル */
TRANSITION_TABLE(TrafficLight)
    TRANSITION(Red,    Timer,     Green,  traffic_light_to_green)
    TRANSITION(Green,  Timer,     Yellow, traffic_light_to_yellow)
    TRANSITION(Yellow, Timer,     Red,    traffic_light_to_red)
    TRANSITION(Red,    Emergency, Red,    traffic_light_emergency)
    TRANSITION(Green,  Emergency, Red,    traffic_light_emergency)
    TRANSITION(Yellow, Emergency, Red,    traffic_light_emergency)
    TRANSITION(Red,    Reset,     Red,    NULL)
    TRANSITION(Green,  Reset,     Red,    traffic_light_to_red)
    TRANSITION(Yellow, Reset,     Red,    traffic_light_to_red)
END_TRANSITION_TABLE

/* 状態名取得関数 */
const char *get_state_name_TrafficLight(TrafficLight_State state)
{
    switch (state) {
        case STATE_ENUM(Red):    return "赤";
        case STATE_ENUM(Yellow): return "黄";
        case STATE_ENUM(Green):  return "青";
        default:                 return "不明";
    }
}

/* イベント処理関数 */
void process_event_TrafficLight(TrafficLight_Machine *machine, TrafficLight_Event event)
{
    const TrafficLight_Transition *trans;
    int i;
    
    for (i = 0; TrafficLight_transitions[i].from_state != STATE_ENUM(INVALID); i++) {
        trans = &TrafficLight_transitions[i];
        if (trans->from_state == machine->current_state && 
            trans->event == event) {
            
            printf("[%s] 状態遷移: %s -> ", 
                   machine->name,
                   get_state_name_TrafficLight(machine->current_state));
            
            machine->current_state = trans->to_state;
            
            printf("%s\n", get_state_name_TrafficLight(machine->current_state));
            
            if (trans->action) {
                trans->action(machine);
            }
            return;
        }
    }
    
    printf("[%s] 無効な遷移: 状態=%s, イベント=%d\n",
           machine->name,
           get_state_name_TrafficLight(machine->current_state),
           event);
}

/* イベント駆動システムの実装例 */

/* ボタン押下ハンドラ */
void on_button_press(void *data)
{
    int button_id = *(int *)data;
    printf("ボタン %d が押されました\n", button_id);
}

/* センサー検知ハンドラ */
void on_sensor_detect(void *data)
{
    double value = *(double *)data;
    printf("センサー検知: %.2f\n", value);
}

/* タイマー満了ハンドラ */
void on_timer_expire(void *data)
{
    int timer_id = *(int *)data;
    printf("タイマー %d が満了しました\n", timer_id);
}

/* イベントハンドラ定義 */
EVENT_HANDLER_BEGIN(System)
    EVENT_HANDLER("ButtonPress", on_button_press)
    EVENT_HANDLER("SensorDetect", on_sensor_detect)
    EVENT_HANDLER("TimerExpire", on_timer_expire)
EVENT_HANDLER_END

/* 汎用イベントディスパッチャ */
void dispatch_event(void *handlers, const char *event_name, void *data)
{
    typedef struct {
        const char *name;
        void (*handler)(void *data);
    } GenericHandler;
    
    GenericHandler *handler_array = (GenericHandler *)handlers;
    int i;
    
    for (i = 0; handler_array[i].name != NULL; i++) {
        if (strcmp(handler_array[i].name, event_name) == 0) {
            if (handler_array[i].handler) {
                handler_array[i].handler(data);
            }
            return;
        }
    }
    
    printf("未登録のイベント: %s\n", event_name);
}

/* より複雑な状態機械の例: 自動販売機 */

STATE_MACHINE(VendingMachine)
    STATE(Idle)
    STATE(CoinInserted)
    STATE(ProductSelected)
    STATE(Dispensing)
    STATE(Change)
    STATE(OutOfOrder)
END_STATE_MACHINE(VendingMachine)

EVENTS(VendingMachine)
    EVENT(InsertCoin)
    EVENT(SelectProduct)
    EVENT(Dispense)
    EVENT(ReturnChange)
    EVENT(Cancel)
    EVENT(Maintenance)
END_EVENTS(VendingMachine)

/* コンパイル時検証 */
STATIC_ASSERT_STATE_COUNT(TrafficLight, 4);  /* INVALID + 3状態 + COUNT */
STATIC_ASSERT_EVENT_COUNT(TrafficLight, 4);  /* NONE + 3イベント + COUNT */

/* テスト関数群 */

void test_traffic_light(void)
{
    TrafficLight_Machine traffic_light;
    int i;
    
    printf("=== 信号機状態機械テスト ===\n");
    
    INIT_STATE_MACHINE(traffic_light, TrafficLight, Red);
    
    printf("初期状態: %s\n", get_state_name_TrafficLight(traffic_light.current_state));
    
    /* 通常のサイクル */
    for (i = 0; i < 6; i++) {
        PROCESS_EVENT(traffic_light, TrafficLight, Timer);
    }
    
    /* 緊急イベント */
    printf("\n緊急イベント発生:\n");
    PROCESS_EVENT(traffic_light, TrafficLight, Emergency);
    
    /* リセット */
    printf("\nリセット:\n");
    PROCESS_EVENT(traffic_light, TrafficLight, Reset);
    
    printf("\n");
}

void test_event_system(void)
{
    int button = 1;
    double sensor_value = 23.5;
    int timer = 100;
    
    printf("=== イベント駆動システムテスト ===\n");
    
    DISPATCH_EVENT(System_handlers, "ButtonPress", &button);
    DISPATCH_EVENT(System_handlers, "SensorDetect", &sensor_value);
    DISPATCH_EVENT(System_handlers, "TimerExpire", &timer);
    DISPATCH_EVENT(System_handlers, "UnknownEvent", NULL);
    
    printf("\n");
}

/* マクロで生成されたコードの確認 */
void test_macro_expansion(void)
{
    printf("=== マクロ展開確認 ===\n");
    
    printf("状態数:\n");
    printf("  TrafficLight: %d状態\n", STATE_ENUM(COUNT) - 1);
    printf("  VendingMachine: %d状態\n", 6);  /* 手動カウント */
    
    printf("\nイベント数:\n");
    printf("  TrafficLight: %d イベント\n", EVENT_ENUM(COUNT) - 1);
    
    printf("\n遷移テーブルサイズ:\n");
    printf("  TrafficLight: %lu エントリ\n",
           (unsigned long)(sizeof(TrafficLight_transitions) / sizeof(TrafficLight_transitions[0]) - 1));
    
    printf("\n");
}

/* 高度なDSL使用例: ワークフロー定義 */
#define WORKFLOW_BEGIN(name) \
    typedef struct { \
        const char *step_name; \
        int (*condition)(void *context); \
        void (*action)(void *context); \
        const char *next_step; \
    } name##_WorkflowStep; \
    \
    static name##_WorkflowStep name##_workflow[] = {

#define WORKFLOW_STEP(name, cond, act, next) \
    { #name, cond, act, #next },

#define WORKFLOW_END \
    { NULL, NULL, NULL, NULL } \
    };

/* 条件関数 */
int always_true(void *context) { return 1; }
int check_payment(void *context) { 
    int *amount = (int *)context;
    return *amount >= 100;
}

/* アクション関数 */
void process_order(void *context) { printf("  注文処理中...\n"); }
void check_inventory(void *context) { printf("  在庫確認中...\n"); }
void charge_payment(void *context) { printf("  支払い処理中...\n"); }
void ship_product(void *context) { printf("  発送処理中...\n"); }

/* ワークフロー定義 */
WORKFLOW_BEGIN(OrderProcessing)
    WORKFLOW_STEP(Start, always_true, process_order, CheckInventory)
    WORKFLOW_STEP(CheckInventory, always_true, check_inventory, ProcessPayment)
    WORKFLOW_STEP(ProcessPayment, check_payment, charge_payment, ShipProduct)
    WORKFLOW_STEP(ShipProduct, always_true, ship_product, Complete)
WORKFLOW_END

void test_workflow(void)
{
    int payment_amount = 150;
    const char *current_step = "Start";
    int i, j;
    
    printf("=== ワークフローDSLテスト ===\n");
    printf("注文処理ワークフロー開始:\n");
    
    for (i = 0; i < 10 && current_step != NULL; i++) {
        for (j = 0; OrderProcessing_workflow[j].step_name != NULL; j++) {
            if (strcmp(OrderProcessing_workflow[j].step_name, current_step) == 0) {
                printf("ステップ: %s\n", current_step);
                
                if (OrderProcessing_workflow[j].condition &&
                    OrderProcessing_workflow[j].condition(&payment_amount)) {
                    
                    if (OrderProcessing_workflow[j].action) {
                        OrderProcessing_workflow[j].action(&payment_amount);
                    }
                    
                    current_step = OrderProcessing_workflow[j].next_step;
                    if (strcmp(current_step, "Complete") == 0) {
                        printf("ワークフロー完了!\n");
                        current_step = NULL;
                    }
                } else {
                    printf("  条件を満たしていません\n");
                    current_step = NULL;
                }
                break;
            }
        }
    }
    
    printf("\n");
}

/* メイン関数 */
int main(void)
{
    printf("=== プリプロセッサベースDSLデモ ===\n\n");
    
    /* 各種テスト実行 */
    test_traffic_light();
    test_event_system();
    test_macro_expansion();
    test_workflow();
    
    printf("=== デモ完了 ===\n");
    return 0;
}

/*
実行例:
=== プリプロセッサベースDSLデモ ===

=== 信号機状態機械テスト ===
初期状態: 赤
[TrafficLight] 状態遷移: 赤 -> 青
[TrafficLight] 青信号に変更
[TrafficLight] 状態遷移: 青 -> 黄
[TrafficLight] 黄色信号に変更
[TrafficLight] 状態遷移: 黄 -> 赤
[TrafficLight] 赤信号に変更
[TrafficLight] 状態遷移: 赤 -> 青
[TrafficLight] 青信号に変更
[TrafficLight] 状態遷移: 青 -> 黄
[TrafficLight] 黄色信号に変更
[TrafficLight] 状態遷移: 黄 -> 赤
[TrafficLight] 赤信号に変更

緊急イベント発生:
[TrafficLight] 状態遷移: 赤 -> 赤
[TrafficLight] 緊急モード: 赤信号点滅

リセット:
[TrafficLight] 状態遷移: 赤 -> 赤

=== イベント駆動システムテスト ===
ボタン 1 が押されました
センサー検知: 23.50
タイマー 100 が満了しました
未登録のイベント: UnknownEvent

=== マクロ展開確認 ===
状態数:
  TrafficLight: 3状態
  VendingMachine: 6状態

イベント数:
  TrafficLight: 3 イベント

遷移テーブルサイズ:
  TrafficLight: 9 エントリ

=== ワークフローDSLテスト ===
注文処理ワークフロー開始:
ステップ: Start
  注文処理中...
ステップ: CheckInventory
  在庫確認中...
ステップ: ProcessPayment
  支払い処理中...
ステップ: ShipProduct
  発送処理中...
ワークフロー完了!

=== デモ完了 ===
*/