/**
 * 演習14-5: C23総合演習
 * 設定管理システム
 * 
 * C23の複数の新機能を組み合わせた設定管理システムを実装します。
 * - bool型で各種設定のON/OFF
 * - 2進数リテラルでフラグ管理
 * - typeof演算子で型安全な操作
 * - nullptrで安全なポインタ操作
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 設定フラグ（2進数リテラル使用） */
#define CONFIG_DEBUG        0b00000001
#define CONFIG_VERBOSE      0b00000010
#define CONFIG_LOGGING      0b00000100
#define CONFIG_NETWORKING   0b00001000
#define CONFIG_ENCRYPTION   0b00010000
#define CONFIG_COMPRESSION  0b00100000
#define CONFIG_BACKUP       0b01000000
#define CONFIG_READONLY     0b10000000

/* 設定値の型定義 */
typedef enum {
    TYPE_BOOL,
    TYPE_INT,
    TYPE_DOUBLE,
    TYPE_STRING
} ConfigType;

/* 設定項目構造体 */
typedef struct ConfigItem {
    char key[64];
    ConfigType type;
    union {
        bool bool_value;
        int int_value;
        double double_value;
        char *string_value;
    } value;
    struct ConfigItem *next;
} ConfigItem;

/* 設定マネージャー構造体 */
typedef struct {
    ConfigItem *items;
    unsigned char flags;
    bool is_modified;
    char *filename;
} ConfigManager;

/* 型安全な値の設定マクロ */
#define SET_CONFIG_VALUE(item, val) do { \
    typeof(val) _val = (val); \
    if (item != nullptr) { \
        item->value.int_value = (int)_val; \
    } \
} while(0)

/* 型安全な最大値取得マクロ */
#define GET_MAX_CONFIG(a, b) ({ \
    typeof(a) _a = (a); \
    typeof(b) _b = (b); \
    _a > _b ? _a : _b; \
})

/* 設定マネージャーを作成 */
ConfigManager* config_create(const char *filename)
{
    ConfigManager *config = (ConfigManager *)malloc(sizeof(ConfigManager));
    if (config == nullptr) {
        return nullptr;
    }
    
    config->items = nullptr;
    config->flags = 0;
    config->is_modified = false;
    
    if (filename != nullptr) {
        config->filename = (char *)malloc(strlen(filename) + 1);
        if (config->filename != nullptr) {
            strcpy(config->filename, filename);
        }
    } else {
        config->filename = nullptr;
    }
    
    return config;
}

/* 設定項目を追加（bool型） */
bool config_add_bool(ConfigManager *config, const char *key, bool value)
{
    if (config == nullptr || key == nullptr) {
        return false;
    }
    
    ConfigItem *item = (ConfigItem *)malloc(sizeof(ConfigItem));
    if (item == nullptr) {
        return false;
    }
    
    strncpy(item->key, key, sizeof(item->key) - 1);
    item->key[sizeof(item->key) - 1] = '\0';
    item->type = TYPE_BOOL;
    item->value.bool_value = value;
    item->next = config->items;
    config->items = item;
    config->is_modified = true;
    
    return true;
}

/* 設定項目を追加（int型） */
bool config_add_int(ConfigManager *config, const char *key, int value)
{
    if (config == nullptr || key == nullptr) {
        return false;
    }
    
    ConfigItem *item = (ConfigItem *)malloc(sizeof(ConfigItem));
    if (item == nullptr) {
        return false;
    }
    
    strncpy(item->key, key, sizeof(item->key) - 1);
    item->key[sizeof(item->key) - 1] = '\0';
    item->type = TYPE_INT;
    item->value.int_value = value;
    item->next = config->items;
    config->items = item;
    config->is_modified = true;
    
    return true;
}

/* 設定項目を追加（double型） */
bool config_add_double(ConfigManager *config, const char *key, double value)
{
    if (config == nullptr || key == nullptr) {
        return false;
    }
    
    ConfigItem *item = (ConfigItem *)malloc(sizeof(ConfigItem));
    if (item == nullptr) {
        return false;
    }
    
    strncpy(item->key, key, sizeof(item->key) - 1);
    item->key[sizeof(item->key) - 1] = '\0';
    item->type = TYPE_DOUBLE;
    item->value.double_value = value;
    item->next = config->items;
    config->items = item;
    config->is_modified = true;
    
    return true;
}

/* 設定項目を追加（文字列） */
bool config_add_string(ConfigManager *config, const char *key, const char *value)
{
    if (config == nullptr || key == nullptr || value == nullptr) {
        return false;
    }
    
    ConfigItem *item = (ConfigItem *)malloc(sizeof(ConfigItem));
    if (item == nullptr) {
        return false;
    }
    
    strncpy(item->key, key, sizeof(item->key) - 1);
    item->key[sizeof(item->key) - 1] = '\0';
    item->type = TYPE_STRING;
    item->value.string_value = (char *)malloc(strlen(value) + 1);
    if (item->value.string_value == nullptr) {
        free(item);
        return false;
    }
    strcpy(item->value.string_value, value);
    item->next = config->items;
    config->items = item;
    config->is_modified = true;
    
    return true;
}

/* 設定項目を検索 */
ConfigItem* config_find(ConfigManager *config, const char *key)
{
    if (config == nullptr || key == nullptr) {
        return nullptr;
    }
    
    ConfigItem *current = config->items;
    while (current != nullptr) {
        if (strcmp(current->key, key) == 0) {
            return current;
        }
        current = current->next;
    }
    
    return nullptr;
}

/* フラグを設定 */
void config_set_flag(ConfigManager *config, unsigned char flag, bool enable)
{
    if (config == nullptr) {
        return;
    }
    
    if (enable) {
        config->flags |= flag;
    } else {
        config->flags &= ~flag;
    }
    config->is_modified = true;
}

/* フラグをチェック */
bool config_check_flag(ConfigManager *config, unsigned char flag)
{
    if (config == nullptr) {
        return false;
    }
    
    return (config->flags & flag) != 0;
}

/* 設定を表示 */
void config_display(ConfigManager *config)
{
    if (config == nullptr) {
        printf("Error: 設定マネージャーがnullptrです\n");
        return;
    }
    
    printf("=== 設定情報 ===\n");
    printf("ファイル: %s\n", config->filename != nullptr ? config->filename : "(なし)");
    printf("変更状態: %s\n", config->is_modified ? "変更あり" : "変更なし");
    
    /* フラグ状態を2進数で表示 */
    printf("フラグ: 0b");
    for (int i = 7; i >= 0; i--) {
        printf("%d", (config->flags >> i) & 1);
    }
    printf("\n");
    
    /* 個別フラグの状態 */
    printf("  デバッグ:     %s\n", config_check_flag(config, CONFIG_DEBUG) ? "ON" : "OFF");
    printf("  詳細出力:     %s\n", config_check_flag(config, CONFIG_VERBOSE) ? "ON" : "OFF");
    printf("  ログ記録:     %s\n", config_check_flag(config, CONFIG_LOGGING) ? "ON" : "OFF");
    printf("  ネットワーク: %s\n", config_check_flag(config, CONFIG_NETWORKING) ? "ON" : "OFF");
    printf("  暗号化:       %s\n", config_check_flag(config, CONFIG_ENCRYPTION) ? "ON" : "OFF");
    printf("  圧縮:         %s\n", config_check_flag(config, CONFIG_COMPRESSION) ? "ON" : "OFF");
    printf("  バックアップ: %s\n", config_check_flag(config, CONFIG_BACKUP) ? "ON" : "OFF");
    printf("  読み取り専用: %s\n", config_check_flag(config, CONFIG_READONLY) ? "ON" : "OFF");
    
    /* 設定項目 */
    printf("\n設定項目:\n");
    ConfigItem *current = config->items;
    while (current != nullptr) {
        printf("  %s = ", current->key);
        switch (current->type) {
            case TYPE_BOOL:
                printf("%s", current->value.bool_value ? "true" : "false");
                break;
            case TYPE_INT:
                printf("%d", current->value.int_value);
                break;
            case TYPE_DOUBLE:
                printf("%.2f", current->value.double_value);
                break;
            case TYPE_STRING:
                printf("\"%s\"", current->value.string_value);
                break;
        }
        printf(" (%s型)\n", 
               current->type == TYPE_BOOL ? "bool" :
               current->type == TYPE_INT ? "int" :
               current->type == TYPE_DOUBLE ? "double" : "string");
        current = current->next;
    }
}

/* 設定を破棄 */
void config_destroy(ConfigManager **config)
{
    if (config == nullptr || *config == nullptr) {
        return;
    }
    
    /* 設定項目を解放 */
    ConfigItem *current = (*config)->items;
    while (current != nullptr) {
        ConfigItem *temp = current;
        current = current->next;
        
        if (temp->type == TYPE_STRING && temp->value.string_value != nullptr) {
            free(temp->value.string_value);
        }
        free(temp);
    }
    
    /* ファイル名を解放 */
    if ((*config)->filename != nullptr) {
        free((*config)->filename);
    }
    
    /* 設定マネージャーを解放 */
    free(*config);
    *config = nullptr;
}

/* 実用的な使用例 */
void demonstrate_practical_use(void)
{
    printf("=== 実用的な設定管理の例 ===\n\n");
    
    /* 設定マネージャーを作成 */
    ConfigManager *app_config = config_create("app_config.ini");
    if (app_config == nullptr) {
        printf("設定マネージャーの作成に失敗\n");
        return;
    }
    
    /* アプリケーション設定を追加 */
    config_add_string(app_config, "app_name", "C23 Demo Application");
    config_add_string(app_config, "version", "1.0.0");
    config_add_int(app_config, "max_connections", 100);
    config_add_int(app_config, "timeout", 30);
    config_add_double(app_config, "cache_size_mb", 256.5);
    config_add_bool(app_config, "auto_save", true);
    config_add_bool(app_config, "show_tips", false);
    
    /* フラグを設定 */
    config_set_flag(app_config, CONFIG_DEBUG | CONFIG_VERBOSE, true);
    config_set_flag(app_config, CONFIG_LOGGING | CONFIG_BACKUP, true);
    config_set_flag(app_config, CONFIG_ENCRYPTION, false);
    
    /* 設定を表示 */
    config_display(app_config);
    
    /* 設定の変更 */
    printf("\n\n--- 設定を変更 ---\n");
    ConfigItem *item = config_find(app_config, "max_connections");
    if (item != nullptr) {
        item->value.int_value = 200;
        printf("max_connectionsを200に変更しました\n");
    }
    
    /* セキュリティモードを有効化 */
    printf("\nセキュリティモードを有効化...\n");
    config_set_flag(app_config, CONFIG_ENCRYPTION, true);
    config_set_flag(app_config, CONFIG_READONLY, true);
    
    /* 最終状態を表示 */
    printf("\n");
    config_display(app_config);
    
    /* クリーンアップ */
    config_destroy(&app_config);
    
    if (app_config == nullptr) {
        printf("\n\n設定マネージャーは正常に破棄されました\n");
    }
}

/* デバッグモードのシミュレーション */
void simulate_debug_mode(void)
{
    printf("\n\n=== デバッグモードのシミュレーション ===\n");
    
    ConfigManager *debug_config = config_create("debug.conf");
    
    /* デバッグ設定 */
    config_add_bool(debug_config, "enable_assertions", true);
    config_add_int(debug_config, "log_level", 3);  /* 0:ERROR, 1:WARN, 2:INFO, 3:DEBUG */
    config_add_string(debug_config, "log_file", "/tmp/app_debug.log");
    
    /* すべてのデバッグフラグをON */
    config_set_flag(debug_config, CONFIG_DEBUG | CONFIG_VERBOSE | CONFIG_LOGGING, true);
    
    /* デバッグ情報を表示 */
    if (config_check_flag(debug_config, CONFIG_DEBUG)) {
        printf("デバッグモードが有効です\n");
        
        ConfigItem *log_level = config_find(debug_config, "log_level");
        if (log_level != nullptr) {
            printf("ログレベル: %d\n", log_level->value.int_value);
        }
        
        ConfigItem *log_file = config_find(debug_config, "log_file");
        if (log_file != nullptr) {
            printf("ログファイル: %s\n", log_file->value.string_value);
        }
    }
    
    config_destroy(&debug_config);
}

int main(void)
{
    printf("=== C23総合演習: 設定管理システム ===\n\n");
    
    /* 実用的な使用例 */
    demonstrate_practical_use();
    
    /* デバッグモードのシミュレーション */
    simulate_debug_mode();
    
    printf("\n\nプログラムを終了します\n");
    
    return 0;
}
