/*
 * ビットフィールドの活用例（C99準拠版）
 * 
 * C99の機能を活用してより柔軟で安全な
 * ビットフィールドの実装を示します。
 */
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

/* bool型を使ったフラグ構造体 */
typedef struct {
    bool flag_a : 1;
    bool flag_b : 1;
    bool flag_c : 1;
    bool flag_d : 1;
    uint8_t reserved : 4;
} BoolFlags;

/* 指定初期化子を使った初期化 */
typedef struct {
    unsigned int day   : 5;
    unsigned int month : 4;
    unsigned int year  : 7;
} PackedDate;

/* 匿名構造体でのビットフィールド（C11風だがC99でも一部使用可） */
typedef struct {
    union {
        struct {
            uint16_t blue  : 5;
            uint16_t green : 6;
            uint16_t red   : 5;
        };
        uint16_t raw;
    } color;
} RGB565Color;

/* ネットワークパケットヘッダ */
typedef struct {
    uint8_t version    : 4;
    uint8_t ihl        : 4;
    uint8_t tos;
    uint16_t total_length;
    uint16_t identification;
    struct {
        uint16_t flags     : 3;
        uint16_t fragment  : 13;
    } fragmentation;
} IPHeader;

/* センサーデータパック */
typedef struct {
    uint32_t temperature : 10;  // -512 to +511度（0.1度単位）
    uint32_t humidity    : 7;   // 0-100%
    uint32_t pressure    : 10;  // 800-1200hPa（0.1hPa単位）
    uint32_t battery     : 5;   // 0-31（バッテリーレベル）
} SensorData;

/* エラーコード管理 */
typedef struct {
    uint16_t module_id  : 8;   // モジュールID
    uint16_t error_code : 6;   // エラーコード
    uint16_t severity   : 2;   // 重要度（0:Info, 1:Warning, 2:Error, 3:Fatal）
} ErrorInfo;

/* 日付を文字列に変換（C99スタイル） */
void date_to_string(PackedDate date, char *buffer, size_t size)
{
    snprintf(buffer, size, "%04d/%02d/%02d", 
             2000 + date.year, date.month, date.day);
}

/* RGB565から各成分を8ビットに拡張 */
void rgb565_to_rgb888(RGB565Color c, uint8_t *r, uint8_t *g, uint8_t *b)
{
    // 5ビット→8ビット: 値を左に3ビットシフトして上位ビットで埋める
    *r = (c.color.red << 3) | (c.color.red >> 2);
    // 6ビット→8ビット: 値を左に2ビットシフトして上位ビットで埋める
    *g = (c.color.green << 2) | (c.color.green >> 4);
    // 5ビット→8ビット: 値を左に3ビットシフトして上位ビットで埋める
    *b = (c.color.blue << 3) | (c.color.blue >> 2);
}

/* センサーデータをデコード */
void decode_sensor_data(SensorData data, float *temp, float *hum, float *pres, int *bat)
{
    // 温度: 10ビット符号付き（-512 to +511）を0.1度単位に
    int temp_raw = (data.temperature & 0x200) ? 
                   (int)data.temperature - 1024 : (int)data.temperature;
    *temp = temp_raw * 0.1f;
    
    // 湿度: 7ビット（0-100%）
    *hum = (float)data.humidity;
    
    // 気圧: 10ビット（0-1023）を800-1200hPaの範囲に
    *pres = 800.0f + (data.pressure * 0.4f);
    
    // バッテリー: 5ビット（0-31）をパーセンテージに
    *bat = (data.battery * 100) / 31;
}

/* エラー情報の表示 */
void print_error_info(ErrorInfo err)
{
    const char *severity_str[] = {"INFO", "WARNING", "ERROR", "FATAL"};
    
    printf("エラー情報:\n");
    printf("  モジュール: 0x%02X\n", err.module_id);
    printf("  エラーコード: %d\n", err.error_code);
    printf("  重要度: %s\n", severity_str[err.severity]);
}

int main(void)
{
    printf("=== ビットフィールドの活用例（C99版） ===\n\n");
    
    /* bool型フラグの使用 */
    printf("--- bool型フラグ ---\n");
    BoolFlags flags = {
        .flag_a = true,
        .flag_b = false,
        .flag_c = true,
        .flag_d = false
    };
    
    printf("フラグ状態: A=%s, B=%s, C=%s, D=%s\n",
           flags.flag_a ? "ON" : "OFF",
           flags.flag_b ? "ON" : "OFF",
           flags.flag_c ? "ON" : "OFF",
           flags.flag_d ? "ON" : "OFF");
    printf("構造体サイズ: %zu バイト\n\n", sizeof(BoolFlags));
    
    /* 指定初期化子での日付設定 */
    printf("--- 指定初期化子 ---\n");
    PackedDate today = {
        .year = 25,   // 2025年
        .month = 1,
        .day = 1
    };
    
    char date_str[20];
    date_to_string(today, date_str, sizeof(date_str));
    printf("日付: %s\n", date_str);
    printf("構造体サイズ: %zu バイト\n\n", sizeof(PackedDate));
    
    /* RGB565色操作 */
    printf("--- RGB565色操作 ---\n");
    RGB565Color colors[] = {
        {.color.red = 31, .color.green = 0,  .color.blue = 0},   // 赤
        {.color.red = 0,  .color.green = 63, .color.blue = 0},   // 緑
        {.color.red = 0,  .color.green = 0,  .color.blue = 31},  // 青
        {.color.red = 31, .color.green = 63, .color.blue = 31}   // 白
    };
    
    const char *color_names[] = {"赤", "緑", "青", "白"};
    
    for (size_t i = 0; i < sizeof(colors)/sizeof(colors[0]); i++) {
        uint8_t r, g, b;
        rgb565_to_rgb888(colors[i], &r, &g, &b);
        printf("%s色: RGB565(0x%04X) → RGB888(%3d, %3d, %3d)\n",
               color_names[i], colors[i].color.raw, r, g, b);
    }
    printf("\n");
    
    /* センサーデータ */
    printf("--- センサーデータ ---\n");
    SensorData sensor = {
        .temperature = 0x0E1,  // 225 = 22.5度
        .humidity = 65,        // 65%
        .pressure = 0x264,     // 612 = 1044.8hPa
        .battery = 20          // 64%
    };
    
    float temp, hum, pres;
    int bat;
    decode_sensor_data(sensor, &temp, &hum, &pres, &bat);
    
    printf("センサー読み取り値:\n");
    printf("  温度: %.1f°C\n", temp);
    printf("  湿度: %.0f%%\n", hum);
    printf("  気圧: %.1fhPa\n", pres);
    printf("  バッテリー: %d%%\n", bat);
    printf("データサイズ: %zu バイト\n\n", sizeof(SensorData));
    
    /* エラー情報管理 */
    printf("--- エラー情報管理 ---\n");
    ErrorInfo errors[] = {
        {.module_id = 0x10, .error_code = 5,  .severity = 0},  // Info
        {.module_id = 0x20, .error_code = 12, .severity = 1},  // Warning
        {.module_id = 0x30, .error_code = 3,  .severity = 2},  // Error
        {.module_id = 0x40, .error_code = 1,  .severity = 3}   // Fatal
    };
    
    for (size_t i = 0; i < sizeof(errors)/sizeof(errors[0]); i++) {
        print_error_info(errors[i]);
        printf("\n");
    }
    
    /* 構造体のアライメント確認 */
    printf("--- 構造体アライメント ---\n");
    printf("PackedDate サイズ: %zu バイト\n", sizeof(PackedDate));
    printf("RGB565Color サイズ: %zu バイト\n", sizeof(RGB565Color));
    printf("SensorData サイズ: %zu バイト\n", sizeof(SensorData));
    printf("ErrorInfo サイズ: %zu バイト\n", sizeof(ErrorInfo));
    
    return 0;
}