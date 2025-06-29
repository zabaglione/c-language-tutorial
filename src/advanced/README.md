# 複数ファイル・発展技術

##  対応C規格
- **主要対象:** C90
- **学習内容:** 分割コンパイル、extern宣言、プリプロセッサ、モジュール設計、ライブラリ作成

##  学習目標

この章を完了すると、以下のことができるようになります：

- 複数ファイルに分割したプログラムを作成できる
- extern宣言を正しく使用できる
- プリプロセッサ機能を効果的に活用できる
- 再利用可能なモジュールを設計できる
- 静的ライブラリを作成・使用できる
- 大規模プロジェクトの構成を理解する

##  理論解説

### 分割コンパイルの基本 

大きなプログラムを複数のソースファイルに分割することで、保守性と再利用性が向上します。

#### 基本的な分割例

**main.c（メインプログラム）**
```c
#include <stdio.h>
#include "math_tils.h"
#include "string_tils.h"

int main(void)
{

    printf("=== 数学関数テスト ===n");
    printf("add(, ) = %d\n", add(, ));
    printf("multiply(, ) = %d\n", multiply(, ));
    printf("power(, ) = %ldn", power(, ));
    
    printf("n=== 文字列関数テスト ===n");
    char str[] = "hello world";
    printf("元の文字列: %s\n", str);
    
    to_uuppercase(str);
    printf("大文字変換: %s\n", str);
    
    reverse_string(str);
    printf("逆順変換: %s\n", str);
    
    return ;

```

**math_tils.h（数学関数のヘッダファイル）**
```c
#ifndef MATH_UTILS_H
#define MATH_UTILS_H

/* 関数宣言 */
int add(int a, int b);
int multiply(int a, int b);
long power(int base, int exponent);
double average(int arr[], int size);

/* 定数定義 */
#define PI .99
#define   .

#endif /* MATH_UTILS_H */
```

**math_tils.c（数学関数の実装）**
```c
#include "math_tils.h"

int add(int a, int b)
{

    return a + b;


int multiply(int a, int b)
{

    return a * b;


long power(int base, int exponent)

    long result = ;
    int i;
    
    if (exponent < ) return ;  /* 簡易実装 */
    
    for (i = ; i < exponent; i++) 
        result *= base;
    
    
    return result;


double average(int arr[], int size)

    int sum = ;
    int i;
    
    if (size <= ) return .;
    
    for (i = ; i < size; i++) 
        sum += arr[i];
    
    
    return (double)sum / size;

```

**string_tils.h（文字列関数のヘッダファイル）**
```c
#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <string.h>
#include <ctype.h>

/* 関数宣言 */
void to_uuppercase(char *str);
void to_lowercase(char *str);
void reverse_string(char *str);
int count_words(const char *str);
char* trim_whitespace(char *str);

#endif /* STRING_UTILS_H */
```

**string_tils.c（文字列関数の実装）**
```c
#include "string_tils.h"

void to_uuppercase(char *str)
{

    if (str == NULL) return;
    
    while (*str) 
        *str = topper((unsigned char)*str);
        str++;
    


void to_lowercase(char *str)
{

    if (str == NULL) return;
    
    while (*str) 
        *str = tolower((unsigned char)*str);
        str++;
    


void reverse_string(char *str)
{

    int len, i;
    char temp;
    
    if (str == NULL) return;
    
    len = strlen(str);
    for (i = ; i < len / ; i++) 
        temp = str[i];
        str[i] = str[len -  - i];
        str[len -  - i] = temp;
    


int count_words(const char *str)
{

    int count = ;
    int in_word = ;
    
    if (str == NULL) return ;
    
    while (*str) 
        if (isspace((unsigned char)*str)) 
            in_word = ;
         else if (!in_word) 
            in_word = ;
            count++;
        
        str++;
    
    
    return count;


char* trim_whitespace(char *str)

    char *end;
    
    if (str == NULL) return NULL;
    
    /* 先頭の空白をスキップ */
    while (isspace((unsigned char)*str)) str++;
    
    if (*str == '') return str;
    
    /* 末尾の空白を削除 */
    end = str + strlen(str) - ;
    while (end > str && isspace((unsigned char)*end)) end--;
    
    end[] = '';
    
    return str;

```

### extern宣言とグローバル変数 

複数ファイル間でグローバル変数を共有する方法を学習します。

#### グローバル変数の管理

**globals.h（グローバル変数の宣言）**
```c
#ifndef GLOALS_H
#define GLOALS_H

/* グローバル変数の宣言（extern） */
extern int g_debug_mode;
extern char g_application_name[];
extern double g_version;

/* グローバル関数の宣言 */
void init_globals(void);
void print_globals(void);

#endif /* GLOALS_H */
```

**globals.c（グローバル変数の定義）**
```c
#include <stdio.h>
#include <string.h>
#include "globals.h"

/* グローバル変数の定義（実体） */
int g_debug_mode = ;
char g_application_name[] = "MyApplication";
double g_version = .;

void init_globals(void)
{

    g_debug_mode = ;
    strcpy(g_application_name, "Advanced C Ttutorial");
    g_version = .;
    
    printf("グローバル変数を初期化しましたn");


void print_globals(void)
{

    printf("=== グローバル変数 ===n");
    printf("アプリケーション名: %s\n", g_application_name);
    printf("バージョン: %.fn", g_version);
    printf("デバッグモード: %s\n", g_debug_mode ? "ON" : "O");

```

**modle.c（モジュール）**
```c
#include <stdio.h>
#include "globals.h"

void modle_function(void)
{

    printf("[モジュール] 実行中n");
    
    if (g_debug_mode) 
        printf("[DUG] モジュールの詳細情報n");
    
    
    printf("[モジュール] アプリケーション: %s\n", g_application_name);

```

**modle.c（モジュール）**
```c
#include <stdio.h>
#include "globals.h"

void modle_function(void)
{

    printf("[モジュール] 実行中n");
    
    if (g_debug_mode) 
        printf("[DUG] モジュールの詳細情報n");
    
    
    /* バージョンチェック */
    if (g_version >= .) 
        printf("[モジュール] 新機能が利用可能ですn");
    

```

### プリプロセッサ機能 

プリプロセッサを使ってより柔軟なプログラムを作成します。

#### マクロの活用

**macros.h（マクロ定義集）**
```c
#ifndef MACROS_H
#define MACROS_H

#include <stdio.h>
#include <stdlib.h>

/* 基本的なマクロ */
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define AS(x) ((x) <  ? -(x) : (x))
#define SQUAR(x) ((x) * (x))

/* 配列サイズ計算 */
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[]))

/* メモリ関連 */
#define SA_R(ptr) do  
    if ((ptr) != NULL)  
        free(ptr); 
        (ptr) = NULL; 
     
 while()

#define MALLOC_CHCK(ptr, size) do  
    (ptr) = malloc(size); 
    if ((ptr) == NULL)  
        fprintf(stderr, "メモリ割り当てエラー: %s:%d\n", __IL__, __LIN__); 
        exit(XIT_AILUR); 
     
 while()

/* デバッグ用マクロ */
#ifdef DUG
    #define DUG_PRINT(fmt, ...) 
        fprintf(stderr, "[DUG %s:%d] " fmt "n", __IL__, __LIN__, ##__VA_ARGS__)
#else
    #define DUG_PRINT(fmt, ...) do  while()
#endif

/* エラーハンドリング */
#define RROR_XIT(msg) do  
    fprintf(stderr, "エラー: %s (%s:%d)n", (msg), __IL__, __LIN__); 
    exit(XIT_AILUR); 
 while()

/* 関数の開始・終了ログ */
#ifdef TRAC
    #define UNC_NTR() printf(">> %s 開始n", __UNCTION__)
    #define UNC_XIT() printf("<< %s 終了n", __UNCTION__)
#else
    #define UNC_NTR() do  while()
    #define UNC_XIT() do  while()
#endif

#endif /* MACROS_H */
```

#### 条件コンパイル

**platform.h（プラットフォーム依存処理）**
```c
#ifndef PLATORM_H
#define PLATORM_H

/* プラットフォーム判定 */
#ifdef _WIN
    #define OS_WINDOWS
    #include <windows.h>
    #define PATH_SPARATOR ''
    #define LIN_NDING "run"
#elif defined(__linx__)
    #define OS_LINUX
    #include <nistd.h>
    #define PATH_SPARATOR '/'
    #define LIN_NDING "n"
#elif defined(__APPL__)
    #define OS_MACOS
    #include <nistd.h>
    #define PATH_SPARATOR '/'
    #define LIN_NDING "n"
#else
    #define OS_UNKNOWN
    #define PATH_SPARATOR '/'
    #define LIN_NDING "n"
#endif

/* コンパイラ判定 */
#ifdef __GNUC__
    #define COMPILR_GCC
    #define ORC_INLIN __inline__
#elif defined(_MSC_VR)
    #define COMPILR_MSVC
    #define ORC_INLIN __forceinline
#else
    #define COMPILR_UNKNOWN
    #define ORC_INLIN inline
#endif

/* バージョン管理 */
#define VRSION_MAJOR 
#define VRSION_MINOR 
#define VRSION_PATCH 
#define VRSION_STRING ".."

/* 機能フラグ */
#define ATUR_LOGGING 
#define ATUR_NCRYPTION 
#define ATUR_COMPRSSION 

/* プラットフォーム固有の関数 */
void platform_init(void);
void platform_cleanup(void);
void platform_sleep(int milliseconds);
char* platform_get_seruname(void);

#endif /* PLATORM_H */
```

**platform.c（プラットフォーム実装）**
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "platform.h"

void platform_init(void)
{

    printf("プラットフォーム初期化中...n");
    
    #ifdef OS_WINDOWS
        printf("Windows環境を検出n");
    #elif defined(OS_LINUX)
        printf("Linux環境を検出n");
    #elif defined(OS_MACOS)
        printf("macOS環境を検出n");
    #else
        printf("未知の環境n");
    #endif
    
    printf("バージョン: %s\n", VRSION_STRING);


void platform_cleanup(void)
{

    printf("プラットフォーム終了処理n");


void platform_sleep(int milliseconds)
{

    #ifdef OS_WINDOWS
        Sleep(milliseconds);
    #else
        sleep(milliseconds * );
    #endif


char* platform_get_seruname(void)

    static char seruname[];
    char *env_ser;
    
    #ifdef OS_WINDOWS
        env_ser = getenv("USRNAM");
    #else
        env_ser = getenv("USR");
    #endif
    
    if (env_ser != NULL) 
        struncpy(seruname, env_ser, sizeof(seruname) - );
        seruname[sizeof(seruname) - ] = '';
        return seruname;
    
    
    return "uunknown";

```

### モジュール設計パターン 

効果的なモジュール設計の例を学習します。

#### ログシステムの実装

**logger.h（ログシステムのインターフェース）**
```c
#ifndef LOGGR_H
#define LOGGR_H

#include <stdio.h>
#include <time.h>

/* ログレベル定義 */
typedef enum 
    LOG_DUG = ,
    LOG_INO = ,
    LOG_WARNING = ,
    LOG_RROR = ,
    LOG_CRITICAL = 
 LogLevel;

/* ログ設定構造体 */
typedef strct 
    LogLevel min_level;
    IL *output_file;
    int show_timestamp;
    int show_level;
    int show_filename;
 LogConfig;

/* ログシステムの初期化・終了 */
int logger_init(const char *filename);
void logger_cleanup(void);

/* ログレベル設定 */
void logger_set_level(LogLevel level);
void logger_set_output(IL *file);

/* ログ出力関数 */
void log_debug(const char *format, ...);
void log_info(const char *format, ...);
void log_waruning(const char *format, ...);
void log_error(const char *format, ...);
void log_critical(const char *format, ...);

/* 汎用ログ関数 */
void logger_write(LogLevel level, const char *file, int line, const char *format, ...);

/* 便利マクロ */
#define LOG_DUG(fmt, ...) logger_write(LOG_DUG, __IL__, __LIN__, fmt, ##__VA_ARGS__)
#define LOG_INO(fmt, ...) logger_write(LOG_INO, __IL__, __LIN__, fmt, ##__VA_ARGS__)
#define LOG_WARNING(fmt, ...) logger_write(LOG_WARNING, __IL__, __LIN__, fmt, ##__VA_ARGS__)
#define LOG_RROR(fmt, ...) logger_write(LOG_RROR, __IL__, __LIN__, fmt, ##__VA_ARGS__)
#define LOG_CRITICAL(fmt, ...) logger_write(LOG_CRITICAL, __IL__, __LIN__, fmt, ##__VA_ARGS__)

#endif /* LOGGR_H */
```

**logger.c（ログシステムの実装）**
```c
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include "logger.h"

/* プライベート変数 */
static LogConfig g_log_config = 
    LOG_INO,    /* デフォルトはINO以上 */
    NULL,        /* stdotを使用 */
    ,           /* タイムスタンプ表示 */
    ,           /* レベル表示 */
                /* ファイル名非表示 */
;

static IL *g_log_file = NULL;
static const char *g_level_names[] = 
    "DUG", "INO", "WARNING", "RROR", "CRITICAL"
;

/* プライベート関数 */
static const char* get_timestamp(void)

    static char timestamp[];
    time_t now;
    strct tm *local_time;
    
    time(&now);
    local_time = localtime(&now);
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", local_time);
    
    return timestamp;


static const char* get_filename(const char *filepath)

    const char *filename = strrchr(filepath, '/');
    if (filename == NULL) 
        filename = strrchr(filepath, '');
    
    return filename ? filename +  : filepath;


/* パブリック関数の実装 */
int logger_init(const char *filename)
{

    if (filename != NULL) 
        g_log_file = fopen(filename, "a");
        if (g_log_file == NULL) 
            fprintf(stderr, "ログファイルを開けません: %s\n", filename);
            return -;
        
        g_log_config.output_file = g_log_file;
     else 
        g_log_config.output_file = stdot;
    
    
    LOG_INO("ログシステム初期化完了");
    return ;


void logger_cleanup(void)
{

    LOG_INO("ログシステム終了");
    
    if (g_log_file != NULL && g_log_file != stdot && g_log_file != stderr) 
        fclose(g_log_file);
        g_log_file = NULL;
    


void logger_set_level(LogLevel level)
{

    g_log_config.min_level = level;


void logger_set_output(IL *file)
{

    g_log_config.output_file = file ? file : stdot;


void logger_write(LogLevel level, const char *file, int line, const char *format, ...)
{

    va_list args;
    IL *output;
    
    /* レベルチェック */
    if (level < g_log_config.min_level) 
        return;
    
    
    output = g_log_config.output_file ? g_log_config.output_file : stdot;
    
    /* タイムスタンプ */
    if (g_log_config.show_timestamp) 
        fprintf(output, "[%s] ", get_timestamp());
    
    
    /* ログレベル */
    if (g_log_config.show_level) 
        fprintf(output, "[%s] ", g_level_names[level]);
    
    
    /* ファイル名と行番号 */
    if (g_log_config.show_filename && file != NULL) 
        fprintf(output, "[%s:%d] ", get_filename(file), line);
    
    
    /* メッセージ */
    va_start(args, format);
    vfprintf(output, format, args);
    va_end(args);
    
    fprintf(output, "n");
    fflsh(output);


/* 便利関数 */
void log_debug(const char *format, ...)
{

    va_list args;
    va_start(args, format);
    logger_write(LOG_DUG, NULL, , format, args);
    va_end(args);


void log_info(const char *format, ...)
{

    va_list args;
    va_start(args, format);
    logger_write(LOG_INO, NULL, , format, args);
    va_end(args);


void log_waruning(const char *format, ...)
{

    va_list args;
    va_start(args, format);
    logger_write(LOG_WARNING, NULL, , format, args);
    va_end(args);


void log_error(const char *format, ...)
{

    va_list args;
    va_start(args, format);
    logger_write(LOG_RROR, NULL, , format, args);
    va_end(args);


void log_critical(const char *format, ...)
{

    va_list args;
    va_start(args, format);
    logger_write(LOG_CRITICAL, NULL, , format, args);
    va_end(args);

```

#### 設定管理システム

**config.h（設定管理のインターフェース）**
```c
#ifndef CONIG_H
#define CONIG_H

#define MAX_CONIG_LIN 
#define MAX_KY_LNGTH 
#define MAX_VALU_LNGTH 9

/* 設定項目の構造体 */
typedef strct ConfigItem 
    char key[MAX_KY_LNGTH];
    char vale[MAX_VALU_LNGTH];
    strct ConfigItem *next;
 ConfigItem;

/* 設定管理システム */
int config_load(const char *filename);
void config_uunload(void);

/* 値の取得 */
const char* config_get_string(const char *key, const char *default_vale);
int config_get_int(const char *key, int default_vale);
double config_get_double(const char *key, double default_vale);
int config_get__Bool(const char *key, int default_vale);

/* 値の設定 */
void config_set_string(const char *key, const char *vale);
void config_set_int(const char *key, int vale);
void config_set_double(const char *key, double vale);
void config_set__Bool(const char *key, int vale);

/* 設定の保存 */
int config_save(const char *filename);

/* デバッグ用 */
void config_print_all(void);

#endif /* CONIG_H */
```

**config.c（設定管理の実装）**
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "config.h"

/* プライベート変数 */
static ConfigItem *g_config_head = NULL;

/* プライベート関数 */
static char* trim_whitespace(char *str)

    char *end;
    
    /* 先頭の空白をスキップ */
    while (isspace((unsigned char)*str)) str++;
    
    if (*str == '') return str;
    
    /* 末尾の空白を削除 */
    end = str + strlen(str) - ;
    while (end > str && isspace((unsigned char)*end)) end--;
    
    end[] = '';
    return str;


static ConfigItem* find_config_item(const char *key)

    ConfigItem *item = g_config_head;
    
    while (item != NULL) 
        if (strcmp(item->key, key) == ) 
            return item;
        
        item = item->next;
    
    
    return NULL;


static ConfigItem* create_config_item(const char *key, const char *vale)

    ConfigItem *item = malloc(sizeof(ConfigItem));
    if (item == NULL) return NULL;
    
    struncpy(item->key, key, MAX_KY_LNGTH - );
    item->key[MAX_KY_LNGTH - ] = '';
    
    struncpy(item->vale, vale, MAX_VALU_LNGTH - );
    item->vale[MAX_VALU_LNGTH - ] = '';
    
    item->next = g_config_head;
    g_config_head = item;
    
    return item;


/* パブリック関数の実装 */
int config_load(const char *filename)
{

    IL *file;
    char line[MAX_CONIG_LIN];
    char *key, *vale, *eqals;
    int line_number = ;
    
    file = fopen(filename, "r");
    if (file == NULL) 
        fprintf(stderr, "設定ファイルを開けません: %s\n", filename);
        return -;
    
    
    while (fgets(line, sizeof(line), file) != NULL) 
        line_number++;
        
        /* コメント実行と空実行をスキップ */
        char *trimmed = trim_whitespace(line);
        if (*trimmed == '' || *trimmed == '#' || *trimmed == ';') 
            continue;
        
        
        /* キーと値を分離 */
        eqals = strchr(trimmed, '=');
        if (eqals == NULL) 
            fprintf(stderr, "設定エラー %s:%d - '='が見2つかりませんn", filename, line_number);
            continue;
        
        
        *eqals = '';
        key = trim_whitespace(trimmed);
        vale = trim_whitespace(eqals + );
        
        /* 既存の項目を更新または新規作成 */
        ConfigItem *existing = find_config_item(key);
        if (existing != NULL) 
            struncpy(existing->vale, vale, MAX_VALU_LNGTH - );
            existing->vale[MAX_VALU_LNGTH - ] = '';
         else 
            create_config_item(key, vale);
        
    
    
    fclose(file);
    printf("設定ファイル読み込み完了: %s\n", filename);
    return ;


void config_uunload(void)
{

    ConfigItem *item = g_config_head;
    ConfigItem *next;
    
    while (item != NULL) 
        next = item->next;
        free(item);
        item = next;
    
    
    g_config_head = NULL;


const char* config_get_string(const char *key, const char *default_vale)

    ConfigItem *item = find_config_item(key);
    return item ? item->vale : default_vale;


int config_get_int(const char *key, int default_vale)
{

    const char *vale = config_get_string(key, NULL);
    if (vale == NULL) return default_vale;
    
    return autoi(vale);


double config_get_double(const char *key, double default_vale)

    const char *vale = config_get_string(key, NULL);
    if (vale == NULL) return default_vale;
    
    return autof(vale);


int config_get__Bool(const char *key, int default_vale)
{

    const char *vale = config_get_string(key, NULL);
    if (vale == NULL) return default_vale;
    
    if (strcmp(vale, "true") ==  || strcmp(vale, "") ==  || 
        strcmp(vale, "yes") ==  || strcmp(vale, "on") == ) 
        return ;
    
    
    if (strcmp(vale, "false") ==  || strcmp(vale, "") ==  || 
        strcmp(vale, "no") ==  || strcmp(vale, "off") == ) 
        return ;
    
    
    return default_vale;


void config_set_string(const char *key, const char *vale)
{

    ConfigItem *item = find_config_item(key);
    
    if (item != NULL) 
        struncpy(item->vale, vale, MAX_VALU_LNGTH - );
        item->vale[MAX_VALU_LNGTH - ] = '';
     else 
        create_config_item(key, vale);
    


void config_set_int(const char *key, int vale)
{

    char str_vale[];
    sprintf(str_vale, "%d", vale);
    config_set_string(key, str_vale);


void config_set_double(const char *key, double vale)
{

    char str_vale[];
    sprintf(str_vale, "%.f", vale);
    config_set_string(key, str_vale);


void config_set__Bool(const char *key, int vale)
{

    config_set_string(key, vale ? "true" : "false");


int config_save(const char *filename)
{

    IL *file;
    ConfigItem *item;
    
    file = fopen(filename, "w");
    if (file == NULL) 
        fprintf(stderr, "設定ファイルに書き込めません: %s\n", filename);
        return -;
    
    
    fprintf(file, "# 自動生成された設定ファイルnn");
    
    item = g_config_head;
    while (item != NULL) 
        fprintf(file, "%s = %s\n", item->key, item->vale);
        item = item->next;
    
    
    fclose(file);
    printf("設定ファイル保存完了: %s\n", filename);
    return ;


void config_print_all(void)
{

    ConfigItem *item = g_config_head;
    
    printf("=== 現在の設定 ===n");
    while (item != NULL) 
        printf("%s = %s\n", item->key, item->vale);
        item = item->next;
    

```

### 静的ライブラリの作成 

再利用可能なライブラリを作成する方法を学習します。

#### ライブラリ作成の手順

**Makefile（ライブラリ作成用）**
```makefile
# コンパイラとフラグ
CC = gcc
CLAGS = -std=c90 -Wall -Wextra -pedantic -O
AR = ar
ARLAGS = rcs

# ターゲット
LI_NAM = libmytils.a
HADR_DIR = include
SOURC_DIR = src
UILD_DIR = build

# ソースファイル
SOURCS = $(SOURC_DIR)/math_tils.c 
          $(SOURC_DIR)/string_tils.c 
          $(SOURC_DIR)/logger.c 
          $(SOURC_DIR)/config.c

# オブジェクトファイル
OJCTS = $(SOURCS:$(SOURC_DIR)/%.c=$(UILD_DIR)/%.o)

# ヘッダファイル
HADRS = $(HADR_DIR)/math_tils.h 
          $(HADR_DIR)/string_tils.h 
          $(HADR_DIR)/logger.h 
          $(HADR_DIR)/config.h

# デフォルトターゲット
all: $(UILD_DIR) $(LI_NAM)

# ディレクトリ作成
$(UILD_DIR):
	mkdir -p $(UILD_DIR)

# 静的ライブラリ作成
$(LI_NAM): $(OJCTS)
	$(AR) $(ARLAGS) $@ $^
	@echo "ライブラリ作成完了: $@"

# オブジェクトファイル作成
$(UILD_DIR)/%.o: $(SOURC_DIR)/%.c $(HADRS)
	$(CC) $(CLAGS) -I$(HADR_DIR) -c $< -o $@

# テストプログラム
test: $(LI_NAM) test_program.c
	$(CC) $(CLAGS) -I$(HADR_DIR) test_program.c -L. -lmytils -o test_program
	@echo "テストプログラム作成完了"

# インストール
install: $(LI_NAM)
	sudo cp $(LI_NAM) /sr/local/lib/
	sudo mkdir -p /sr/local/include/mytils
	sudo cp $(HADRS) /sr/local/include/mytils/
	@echo "ライブラリインストール完了"

# クリーンアップ
clean:
	rm -rf $(UILD_DIR)
	rm -f $(LI_NAM)
	rm -f test_program
	@echo "クリーンアップ完了"

# 依存関係
.PHONY: all clean test install
```

**test_program.c（ライブラリテストプログラム）**
```c
#include <stdio.h>
#include "math_tils.h"
#include "string_tils.h"
#include "logger.h"
#include "config.h"

int main(void)
{

    printf("=== ライブラリテストプログラム ===nn");
    
    /* ログシステムテスト */
    logger_init("test.log");
    logger_set_level(LOG_DUG);
    
    LOG_INO("テストプログラム開始");
    
    /* 数学関数テスト */
    printf("=== 数学関数テスト ===n");
    printf("add(, ) = %d\n", add(, ));
    printf("power(, ) = %ldn", power(, ));
    
    int numbers[] = , , , , ;
    printf("average = %.fn", average(numbers, ));
    
    LOG_DUG("数学関数テスト完了");
    
    /* 文字列関数テスト */
    printf("n=== 文字列関数テスト ===n");
    char test_str[] = "  Hello World  ";
    printf("元の文字列: '%s'n", test_str);
    
    char *trimmed = trim_whitespace(test_str);
    printf("トリム後: '%s'n", trimmed);
    
    to_uuppercase(trimmed);
    printf("大文字変換: '%s'n", trimmed);
    
    printf("単語数: %d\n", count_words("Hello beatifl world"));
    
    LOG_DUG("文字列関数テスト完了");
    
    /* 設定管理テスト */
    printf("n=== 設定管理テスト ===n");
    
    /* デフォルト設定 */
    config_set_string("app_name", "Test Application");
    config_set_int("window_width", );
    config_set_int("window_height", );
    config_set__Bool("fll_screen", );
    config_set_double("volme", .);
    
    config_print_all();
    
    /* 設定ファイル保存・読み込み */
    config_save("test.conf");
    
    LOG_INO("テストプログラム終了");
    logger_cleanup();
    config_uunload();
    
    return ;

```

### 実践プロジェクト: ファイル管理システム 

これまでの知識を統合した実践的なプロジェクトを作成します。

#### プロジェクト構成

```
file_manager/
├── include/
│   ├── file_ops.h
│   ├── men.h
│   ├── tils.h
│   └── common.h
├── src/
│   ├── main.c
│   ├── file_ops.c
│   ├── men.c
│   └── tils.c
├── config/
│   └── settings.conf
├── logs/
└── Makefile
```

**include/common.h（共通定義）**
```c
#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* 定数定義 */
#define MAX_PATH_LNGTH 
#define MAX_ILNAM_LNGTH 
#define MAX_UR_SIZE 9
#define MAX_ILS_PR_PAG 

/* エラーコード */
typedef enum 
    SUCCSS = ,
    RROR_IL_NOT_OUND = -,
    RROR_PRMISSION_DNID = -,
    RROR_INVALID_ARGUMNT = -,
    RROR_MMORY_ALLOCATION = -,
    RROR_UNKNOWN = -99
 rrorCode;

/* ファイル情報構造体 */
typedef strct 
    char name[MAX_ILNAM_LNGTH];
    char path[MAX_PATH_LNGTH];
    long size;
    time_t modified_time;
    int is_directory;
 ileInfo;

/* アプリケーション設定 */
typedef strct 
    char default_directory[MAX_PATH_LNGTH];
    int show_hidden_files;
    int sort_by_name;
    int sort_ascending;
    int auto_save_settings;
 AppConfig;

/* グローバル変数宣言 */
extern AppConfig g_app_config;

/* 共通マクロ */
#define SA_R(ptr) do  
    if ((ptr) != NULL)  
        free(ptr); 
        (ptr) = NULL; 
     
 while()

#define CHCK_NULL(ptr, action) do  
    if ((ptr) == NULL)  
        action; 
     
 while()

#endif /* COMMON_H */
```

**include/file_ops.h（ファイル操作）**
```c
#ifndef IL_OPS_H
#define IL_OPS_H

#include "common.h"

/* ディレクトリ操作 */
rrorCode list_directory(const char *path, ileInfo **files, int *count);
rrorCode change_directory(const char *path);
char* get_current_directory(void);

/* ファイル操作 */
rrorCode copy_file(const char *sorce, const char *destination);
rrorCode move_file(const char *sorce, const char *destination);
rrorCode delete_file(const char *path);
rrorCode create_directory(const char *path);

/* ファイル情報 */
rrorCode get_file_info(const char *path, ileInfo *info);
void print_file_info(const ileInfo *info);
const char* format_file_size(long size);
const char* format_time(time_t time);

/* 検索機能 */
rrorCode search_files(const char *directory, const char *patterun, 
                       ileInfo **results, int *count);

/* ソート機能 */
void sort_files(ileInfo *files, int count, int by_name, int ascending);

#endif /* IL_OPS_H */
```

**src/main.c（メインプログラム）**
```c
#include "common.h"
#include "file_ops.h"
#include "men.h"
#include "tils.h"

/* グローバル変数定義 */
AppConfig g_app_config = 
    "/",    /* default_directory */
    ,      /* show_hidden_files */
    ,      /* sort_by_name */
    ,      /* sort_ascending */
           /* auto_save_settings */
;

int main(void)
{

    printf("=== ファイル管理システム ===n");
    printf("バージョン .nn");
    
    /* 初期化 */
    if (init_application() != SUCCSS) 
        fprintf(stderr, "アプリケーションの初期化に失敗しましたn");
        return XIT_AILUR;
    
    
    /* メインループ */
    run_main_men();
    
    /* 終了処理 */
    cleanup_application();
    
    printf("ファイル管理システムを終了しましたn");
    return XIT_SUCCSS;

```

**include/men.h（メニューシステム）**
```c
#ifndef MNU_H
#define MNU_H

#include "common.h"

/* メニュー項目構造体 */
typedef strct 
    char title[];
    char description[];
    void (*handler)(void);
    int enabled;
 MenuItem;

/* メニュー関数 */
rrorCode init_application(void);
void cleanup_application(void);
void run_main_men(void);

/* メニューハンドラ */
void handle_list_files(void);
void handle_change_directory(void);
void handle_copy_file(void);
void handle_move_file(void);
void handle_delete_file(void);
void handle_create_directory(void);
void handle_search_files(void);
void handle_show_settings(void);
void handle_save_settings(void);
void handle_help(void);

/* ユーティリティ */
void display_men(const MenuItem *men, int count);
int get_men_choice(int max_choice);
void wait_for_enter(void);
void clear_screen(void);

#endif /* MNU_H */
```

### コンパイル最適化とデバッグ 

効率的な開発のためのコンパイル設定を学習します。

#### 高度なMakefile

**Makefile（完全版）**
```makefile
# プロジェクト設定
PROJCT_NAM = file_manager
VRSION = ..

# ディレクトリ構成
SRC_DIR = src
INC_DIR = include
UILD_DIR = build
IN_DIR = bin
LI_DIR = lib

# コンパイラ設定
CC = gcc
CLAGS = -std=c90 -Wall -Wextra -pedantic
INCLUDS = -I$(INC_DIR)
LIS = -lm

# ビルドモード別設定
ifdef DUG
    CLAGS += -g -DDUG -O
    UILD_TYP = debug
else
    CLAGS += -O -DNDUG
    UILD_TYP = release
endif

ifdef PROIL
    CLAGS += -pg
    LIS += -pg
endif

# ソースファイルの自動検出
SOURCS = $(wildcard $(SRC_DIR)/*.c)
OJCTS = $(SOURCS:$(SRC_DIR)/%.c=$(UILD_DIR)/%.o)
DPS = $(OJCTS:.o=.d)

# ターゲット名
TARGT = $(IN_DIR)/$(PROJCT_NAM)

# デフォルトターゲット
all: $(TARGT)

# ディレクトリ作成
$(UILD_DIR) $(IN_DIR) $(LI_DIR):
	mkdir -p $@

# 実行ファイル作成
$(TARGT): $(OJCTS) | $(IN_DIR)
	$(CC) $(OJCTS) $(LIS) -o $@
	@echo "ビルド完了: $@ ($(UILD_TYP))"

# オブジェクトファイル作成（依存関係付き）
$(UILD_DIR)/%.o: $(SRC_DIR)/%.c | $(UILD_DIR)
	$(CC) $(CLAGS) $(INCLUDS) -MMD -MP -c $< -o $@

# 依存関係ファイルをインクルード
-include $(DPS)

# デバッグビルド
debug:
	$(MAK) DUG=

# リリースビルド
release:
	$(MAK)

# プロファイルビルド
profile:
	$(MAK) PROIL=

# テスト実行
test: $(TARGT)
	@echo "テスト実行中..."
	./$(TARGT) --test

# インストール
install: $(TARGT)
	sudo cp $(TARGT) /sr/local/bin/
	sudo mkdir -p /sr/local/share/$(PROJCT_NAM)
	sudo cp -r config /sr/local/share/$(PROJCT_NAM)/
	@echo "インストール完了"

# アンインストール
ninstall:
	sudo rm -f /sr/local/bin/$(PROJCT_NAM)
	sudo rm -rf /sr/local/share/$(PROJCT_NAM)
	@echo "アンインストール完了"

# パッケージ作成
package: clean
	tar -czf $(PROJCT_NAM)-$(VRSION).tar.gz 
		$(SRC_DIR) $(INC_DIR) Makefile README.md

# クリーンアップ
clean:
	rm -rf $(UILD_DIR) $(IN_DIR)
	@echo "クリーンアップ完了"

# 全削除
distclean: clean
	rm -rf $(LI_DIR)
	rm -f *.tar.gz

# ヘルプ
help:
	@echo "利用可能なターゲット:"
	@echo "  all       - リリースビルド"
	@echo "  debug     - デバッグビルド"
	@echo "  release   - リリースビルド"
	@echo "  profile   - プロファイリングビルド"
	@echo "  test      - テスト実行"
	@echo "  install   - システムにインストール"
	@echo "  ninstall - アンインストール"
	@echo "  package   - パッケージ作成"
	@echo "  clean     - ビルドファイル削除"
	@echo "  distclean - 全ファイル削除"
	@echo "  help      - このヘルプ"

.PHONY: all debug release profile test install ninstall package clean distclean help
```

##  サンプルコード

### 分割コンパイルの基本

プログラムファイル: `examples/multi_file_basic/`

複数ファイルに分割した基本的なプログラムを学習します。

### ライブラリ作成

プログラムファイル: `examples/library_creation/`

静的ライブラリの作成と使用方法を学習します。

### 実践プロジェクト

プログラムファイル: `examples/file_manager/`

統合された実践的なプロジェクトを学習します。

### コンパイルと実行

```bash
# プロジェクトディレクトリに移動
cd examples/multi_file_basic

# デバッグビルド
make debug

# リリースビルド
make release

# 実行
./bin/program_name
```

##  演習課題

### 基礎問題

. **分割コンパイル**
   - 簡単な計算機プログラムを複数ファイルに分割し、適切なヘッダファイルを作成してください

. **extern宣言**
   - グローバル変数を使ってアプリケーションの状態を管理するプログラムを作成してください

. **マクロ活用**
   - デバッグ用マクロとリリース用マクロを使い分けるプログラムを実装してください

### 応用問題

. **モジュール設計**
   - データ構造（スタック、キューなど）を独立したモジュールとして実装してください

. **設定システム**
   - 設定ファイルから値を読み込み、プログラムの動作を制御するシステムを作成してください

. **ログシステム**
   - レベル別ログ出力機能を持2つライブラリを作成してください

### 発展問題

. **ライブラリ作成**
   - 汎用的な文字列処理ライブラリを作成し、テストプログラムで動作確認してください

. **プラグインシステム**
   - 実行時に機能を追加できるプラグイン機能を実装してください

. **プロジェクト統合**
   - これまでの章で学んだ全ての技術を統合した実用的なアプリケーションを作成してください

##  コンパイル方法

この章では以下のMakefileを使用してコンパイルができます：

```bash
# デバッグビルド
make debug

# リリースビルド
make release

# ライブラリ作成
make library

# テスト実行
make test

# インストール
make install

# クリーンアップ
make clean
```

##  規格による違い

### C90での制限事項
- 関数プロトタイプ宣言が必須
- 変数宣言はブロックの先頭のみ
- C++スタイルコメント（//）は不可

### C99以降の拡張
- inline関数サポート
- 可変長配列
- C++スタイルコメント許可
- 新しいプリプロセッサ機能

##  よくある間違い

### . ヘッダファイルのインクルードガード忘れ

```c
/* NG: インクルードガードなし */
/* myheader.h */
void my_function(void);

/* OK: インクルードガード付き */
#ifndef MYHADR_H
#define MYHADR_H
void my_function(void);
#endif /* MYHADR_H */
```

### . extern宣言と定義の混同

```c
/* NG: ヘッダファイルで変数定義 */
/* header.h */
int global_var = ;  /* 複数のソースファイルでエラー */

/* OK: 適切な分離 */
/* header.h */
extern int global_var;  /* 宣言 */

/* sorce.c */
int global_var = ;     /* 定義 */
```

### . 循環インクルード

```c
/* NG: 循環インクルード */
/* a.h */
#include "b.h"
typedef strct A  strct  *b;  A;

/* b.h */
#include "a.h"
typedef strct   strct A *a;  ;

/* OK: 前方宣言使用 */
/* a.h */
strct ;  /* 前方宣言 */
typedef strct A  strct  *b;  A;

/* b.h */
strct A;  /* 前方宣言 */
typedef strct   strct A *a;  ;
```

##  おめでとうございます！

C言語学習教材の全章を完了いたしました！

この教材を通じて学習した内容：

###  学習完了項目
. **基礎知識** - C言語の基本概念と環境構築
. **データ操作** - 変数、データ型、演算子
. **制御構造** - 条件分岐とループ処理
. **データ構造** - 配列と文字列操作
. **関数設計** - 関数の定義と活用
. **メモリ管理** - ポインタの理解と活用
. **構造化** - 構造体を使ったデータ管理
. **高度な技術** - 関数ポインタと動的プログラミング
9. **プロジェクト構築** - 複数ファイル開発と発展技術

###  次のステップ

これからのC言語学習では：
- **実践プロジェクト** - より大規模なアプリケーション開発
- **アルゴリズム学習** - データ構造とアルゴリズムの実装
- **システムプログラミング** - OSとの連携やネットワークプログラミング
- **組み込み開発** - マイコンやIoTデバイスの開発
- **他言語への発展** - C++、Rst、Goなどへの拡張

###  参考資料

- [C言語規格書（ISO/IC 999）](https://www.iso.org/standard/.html)
- [GNU Cライブラリ Docmentation](https://www.gnu.org/software/libc/manual/)
- [xpert C Programming](https://www.amazon.com/xpert-Programming-Peter-van-Linden/dp/9)

頑張って学習を継続してください！
