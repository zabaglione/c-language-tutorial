# 複数ファイル・発展技術

## 対応C規格

- **主要対象：** C90/C99/C11/C17
- **学習内容：** 分割コンパイル、extern宣言、プリプロセッサ、モジュール設計、ライブラリ作成、高度な演算子テクニック

## 学習目標

この章を完了すると、以下のことができるようになります。

- 複数ファイルに分割したプログラムを作成できる
- extern宣言を正しく使用できる
- プリプロセッサ機能を効果的に活用できる
- 再利用可能なモジュールを設計できる
- 静的ライブラリを作成・使用できる
- 大規模プロジェクトの構成を理解する
- 短絡評価の評価順序を利用して、事前条件を検査できる
- 共用体（union）を理解し活用できる

## 概要と詳細

### 複数ファイルへ分割する目的

ソースファイルを機能ごとに分けると、公開する宣言と内部の実装を分離できます。
変更時に再コンパイルする範囲も翻訳単位ごとに限定できます。

#### 分割によって得られる性質

1. **大規模プログラムの開発**

    - 機能ごとに宣言と定義を配置できる
    - 担当範囲と変更範囲を分けられる

2. **コードの再利用**

    - 一度書いたコードを他のプロジェクトでも使える
    - ライブラリとして配布可能

3. **保守性の向上**

    - 機能ごとにファイルを分けて管理
    - バグの特定と修正が容易

### 分割コンパイルの基本

大きなプログラムを複数のソースファイルに分割することで、保守性と再利用性が向上します。

#### 基本的な分割例

#### `math_utils.h`（ヘッダーファイル）

```c
#ifndef MATH_UTILS_H
#define MATH_UTILS_H

int add(int a, int b);
int multiply(int a, int b);
double circle_area(double radius);

#endif
```

#### `math_utils.c`（実装ファイル）

```c
#include "math_utils.h"
#define PI 3.14159265359

int add(int a, int b)
{
    return a + b;
}

int multiply(int a, int b)
{
    return a * b;
}

double circle_area(double radius)
{
    return PI * radius * radius;
}
```

#### `main.c`（メインプログラム）

```c
#include <stdio.h>
#include "math_utils.h"

int main(void)
{
    int sum = add(10, 20);
    int product = multiply(5, 6);
    double area = circle_area(3.0);

    printf("Sum: %d\n", sum);
    printf("Product: %d\n", product);
    printf("Circle area: %.2f\n", area);

    return 0;
}
```

### extern宣言とグローバル変数

#### extern宣言の基本

```c
/* config.h */
#ifndef CONFIG_H
#define CONFIG_H

extern int debug_level;
extern char app_name[];

#endif

/* config.c */
#include "config.h"

int debug_level = 1;
char app_name[] = "MyApplication";
```

#### 外部リンケージを持つ変数の宣言

```c
/* logger.h */
#ifndef LOGGER_H
#define LOGGER_H

typedef enum {
    LOG_ERROR,
    LOG_WARNING,
    LOG_INFO,
    LOG_DEBUG
} LogLevel;

extern LogLevel current_log_level;

void log_message(LogLevel level, const char *message);

#endif
```

### プリプロセッサの活用

#### 基本的なマクロ定義

```c
#define MAX_SIZE 100
#define PI 3.14159265359
#define SQUARE(x) ((x) * (x))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
```

#### 条件付きコンパイル

可変個引数マクロはC99で追加されました。
次の形式は、`DEBUG_PRINT("value=%d\n", value)`のように書式文字列を含む引数を渡します。

```c
#ifdef DEBUG
    #define DEBUG_PRINT(...) fprintf(stderr, __VA_ARGS__)
#else
    #define DEBUG_PRINT(...) ((void)0)
#endif

#if defined(_WIN32)
    #include <windows.h>
#elif defined(__linux__)
    #include <unistd.h>
#endif
```

`_WIN32`や`__linux__`は処理系が定義するマクロであり、C規格が定めるマクロではありません。
利用するコンパイラの定義を確認します。

#### マクロと関数の選択

```c
/* 引数を一度ずつ評価し、状態を戻り値で返す */
int safe_divide(int a, int b, int *result)
{
    if (b == 0 || result == NULL) {
        return 0;
    }

    *result = a / b;
    return 1;
}

/* 配列サイズ取得マクロ */
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
```

関数形式なら、引数に副作用のある式を渡しても各引数を一度だけ評価します。
`ARRAY_SIZE`は配列オブジェクトにだけ使用でき、ポインターへ適用すると要素数を求められません。

### ヘッダーファイルの設計

#### インクルードガードの重要性

```c
#ifndef MODULE_NAME_H
#define MODULE_NAME_H

/* ヘッダーファイルの内容 */

#endif /* MODULE_NAME_H */
```

#### 共通ヘッダー

```c
/* common.h - よく使われるヘッダーをまとめる */
#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

/* 共通の型定義 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

/* 共通のマクロ */
#define TRUE 1
#define FALSE 0

#endif
```

`u8`、`u16`、`u32`が正確に8、16、32ビットを表す保証はありません。
C99以降で幅を固定する必要がある場合は、処理系が提供する`<stdint.h>`の`uint8_t`、`uint16_t`、`uint32_t`を使用します。

### モジュール設計の原則

#### 単一責任の原則

各モジュールは1つの明確な責任を持つべきです。

```c
/* string_utils.h - 文字列処理のみ */
#ifndef STRING_UTILS_H
#define STRING_UTILS_H

char *trim_whitespace(char *str);
int string_compare_ignore_case(const char *s1, const char *s2);
char *string_duplicate(const char *src);

#endif

/* file_utils.h - ファイル操作のみ */
#ifndef FILE_UTILS_H
#define FILE_UTILS_H

int file_exists(const char *filename);
long file_size(const char *filename);
char *read_entire_file(const char *filename);

#endif
```

#### 依存関係の最小化

```c
/* good_module.h - 最小限の依存関係 */
#ifndef GOOD_MODULE_H
#define GOOD_MODULE_H

/* 標準ライブラリのみに依存 */
#include <stddef.h>

typedef struct point {
    double x;
    double y;
} Point;

Point point_create(double x, double y);
double point_distance(const Point *p1, const Point *p2);

#endif
```

### 静的ライブラリの作成

#### ライブラリの構築手順

```bash

# オブジェクトファイルの作成

gcc -c math_utils.c -o math_utils.o
gcc -c string_utils.c -o string_utils.o

# 静的ライブラリの作成

ar rcs libmyutils.a math_utils.o string_utils.o

# ライブラリの使用

gcc main.c -L. -lmyutils -o main
```

#### Makefileでのライブラリ管理

```makefile
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c90
AR = ar
ARFLAGS = rcs

# ライブラリのソースファイル

LIB_SOURCES = math_utils.c string_utils.c file_utils.c
LIB_OBJECTS = $(LIB_SOURCES:.c=.o)
LIB_TARGET = libmyutils.a

# メインプログラム

MAIN_SOURCE = main.c
MAIN_TARGET = main

all: $(LIB_TARGET) $(MAIN_TARGET)

$(LIB_TARGET): $(LIB_OBJECTS)
    $(AR) $(ARFLAGS) $@ $^

$(MAIN_TARGET): $(MAIN_SOURCE) $(LIB_TARGET)
    $(CC) $(CFLAGS) $< -L. -lmyutils -o $@

clean:
    rm -f *.o $(LIB_TARGET) $(MAIN_TARGET)
```

### 大規模プロジェクトの構成

#### 推奨ディレクトリ構造

```text
project/
├── src/           # ソースファイル
│   ├── main.c
│   └── modules/
│       ├── math/
│       ├── string/
│       └── file/
├── include/       # ヘッダーファイル
│   └── myproject/
├── lib/          # ライブラリファイル
├── tests/        # テストファイル
├── docs/         # ドキュメント
├── Makefile
└── README.md
```

#### モジュール間のインターフェース設計

```c
/* 良いインターフェース設計の例 */

/* logger.h */
typedef enum {
    LOG_LEVEL_ERROR,
    LOG_LEVEL_WARNING,
    LOG_LEVEL_INFO,
    LOG_LEVEL_DEBUG
} LogLevel;

/* 初期化と終了 */
int logger_init(const char *filename);
void logger_cleanup(void);

/* ログ出力 */
void log_error(const char *format, ...);
void log_warning(const char *format, ...);
void log_info(const char *format, ...);
void log_debug(const char *format, ...);

/* 設定 */
void logger_set_level(LogLevel level);
LogLevel logger_get_level(void);
```

### C11で追加された機能

#### _Static_assert

```c
#include <assert.h>

/* コンパイル時アサーション */
_Static_assert(sizeof(int) >= 4, "int must be at least 4 bytes");

typedef struct {
    char data[64];
} Buffer;

_Static_assert(sizeof(Buffer) == 64, "Buffer size must be exactly 64 bytes");
```

#### _Generic（型汎用選択）

```c
#include <math.h>
#include <stdlib.h>

#define abs_generic(x) _Generic((x), \
    int: abs, \
    long: labs, \
    float: fabsf, \
    double: fabs, \
    long double: fabsl \
    )(x)

/* 使用例 */
int i = -5;
double d = -3.14;
printf("%d\n", abs_generic(i));    /* abs(i) */
printf("%.2f\n", abs_generic(d));  /* fabs(d) */
```

### 実践的なモジュール例

#### エラーハンドリングモジュール

```c
/* error.h */
#ifndef ERROR_H
#define ERROR_H

typedef enum {
    ERROR_SUCCESS = 0,
    ERROR_NULL_POINTER,
    ERROR_OUT_OF_MEMORY,
    ERROR_FILE_NOT_FOUND,
    ERROR_INVALID_ARGUMENT
} ErrorCode;

const char *error_get_message(ErrorCode code);
void error_set_last_error(ErrorCode code);
ErrorCode error_get_last_error(void);

#endif
```

#### 設定管理モジュール

```c
/* config.h */
#ifndef CONFIG_H
#define CONFIG_H

typedef struct {
    char *key;
    char *value;
} ConfigItem;

int config_load(const char *filename);
const char *config_get_string(const char *key, const char *default_value);
int config_get_int(const char *key, int default_value);
double config_get_double(const char *key, double default_value);
void config_cleanup(void);

#endif
```

### デバッグとテスト支援

#### デバッグマクロの活用

次の`__func__`と可変個引数マクロはC99以降で使用できます。

```c
/* debug.h */
#ifndef DEBUG_H
#define DEBUG_H

#ifdef DEBUG_MODE
    #define DBG_ENTER() printf("ENTER: %s\n", __func__)
    #define DBG_EXIT() printf("EXIT: %s\n", __func__)
    #define DBG_PRINT(...) fprintf(stderr, __VA_ARGS__)
#else
    #define DBG_ENTER() ((void)0)
    #define DBG_EXIT() ((void)0)
    #define DBG_PRINT(...) ((void)0)
#endif

#endif
```

#### 単体テストフレームワーク

```c
/* test_framework.h */
#ifndef TEST_FRAMEWORK_H
#define TEST_FRAMEWORK_H

#include <stdio.h>

extern int test_count;
extern int test_passed;

#define TEST_ASSERT(condition) \
    do { \
        test_count++; \
        if (condition) { \
            test_passed++; \
            printf("PASS: %s\n", #condition); \
        } else { \
            printf("FAIL: %s (line %d)\n", #condition, __LINE__); \
        } \
    } while (0)

#define TEST_SUMMARY() \
    printf("\nTest Results: %d/%d passed\n", test_passed, test_count)

#endif
```

### パフォーマンス最適化

#### インライン関数（C99以降）

```c
/* C99のinline関数 */
static inline int max_inline(int a, int b)
{
    return (a > b) ? a : b;
}

/* ヘッダーファイルでは内部リンケージにすると定義を完結させやすい */
static inline double square_inline(double x)
{
    return x * x;
}
```

#### コンパイラ最適化の活用

```c
/* 最適化ヒントの提供 */
#ifdef __GNUC__
    #define LIKELY(x)   __builtin_expect(!!(x), 1)
    #define UNLIKELY(x) __builtin_expect(!!(x), 0)
#else
    #define LIKELY(x)   (x)
    #define UNLIKELY(x) (x)
#endif

/* 使用例 */
if (LIKELY(ptr != NULL)) {
    /* 通常の処理 */
} else {
    /* エラー処理（稀） */
}
```

## 実例コード

完全な実装例は以下のファイルを参照してください。

### 基本的な分割コンパイル

- [multi_file_basic/](examples/multi_file_basic/) - 基本的な分割例
- [library_example/](examples/library_example/) - ライブラリ作成例

### 高度なプリプロセッサ活用

- [preprocessor_demo.c](examples/preprocessor_demo.c) - マクロとプリプロセッサ
- [conditional_compile.c](examples/conditional_compile.c) - 条件付きコンパイル

### 実用的なモジュール

- [utils_library/](examples/utils_library/) - 実用的なユーティリティライブラリ
- [project_template/](examples/project_template/) - プロジェクトテンプレート

## コンパイル方法

### 基本的な分割コンパイル

```bash

# 個別にコンパイル

gcc -c math_utils.c -o math_utils.o
gcc -c main.c -o main.o
gcc math_utils.o main.o -o main

# 一括コンパイル

gcc math_utils.c main.c -o main
```

### 静的ライブラリの作成と使用

```bash

# ライブラリ作成

gcc -c *.c
ar rcs libmyutils.a *.o

# ライブラリ使用

gcc main.c -L. -lmyutils -o main
```

### Makefileを使用した場合

```bash

# 全てのターゲットをビルド

make all

# 特定のターゲットをビルド

make library

# クリーンアップ

make clean

# インストール

make install
```

## 学習フローとコンパイル方法

### 推奨学習順序

1. **理論学習**: README.mdで基本概念を理解
2. **サンプルコード**: examples/の基本例を確認
3. **演習課題**: exercises/README.mdで課題を確認
4. **実装練習**: solutions/の解答例を参考に自分で実装

### 実践的な学習方法

1. **小さなプロジェクトから始める**: 2-3ファイルの分割から
2. **段階的に複雑化**: 機能追加ごとにモジュール分割
3. **実際のライブラリを参考**: オープンソースプロジェクトの構成を学習
4. **チーム開発の模擬**: 複数人での分担開発を体験

## C標準の違いと対応

### C90での制限と対策

- inline関数なし → マクロまたは最適化に頼る
- 可変長引数マクロなし → 固定引数マクロを使用
- _Bool型なし → int型でbooleanを表現

### C99以降の拡張機能活用

- inline関数の使用
- 可変長引数マクロ
- 指定初期化子
- 複合リテラル

### C11の機能とC17

- _Static_assert
- _Generic
- _Alignas/_Alignof
- _Thread_local

C17はC11に対する不具合修正が中心で、新しい言語機能は追加していません。

### 短絡評価と共用体

論理AND演算子`&&`は左オペランドが0なら右オペランドを評価しません。
論理OR演算子`||`は左オペランドが0以外なら右オペランドを評価しません。
この評価順序を使うと、ポインターや添字の事前条件を検査してから対象の式を評価できます。

#### 短絡評価による安全なプログラミング

短絡評価を使う場合は、左から右へ事前条件が成立する順に式を並べます。

##### 配列とポインターの安全な操作

C言語では配列の境界チェックが自動的に行われないため、プログラマーが明示的にチェックする必要があります。

```c
/* 配列の境界チェック */
int array[10];
int index = 15;
if (index >= 0 && index < 10 && array[index] > 0) {
    /* index が範囲外なので、array[index] へのアクセスは行われない */
    printf("Valid value: %d\n", array[index]);
}

/* 多次元配列の安全なアクセス */
int matrix[5][5];
int row = 3, col = 7;
if (row >= 0 && row < 5 && col >= 0 && col < 5 && matrix[row][col] != 0) {
    /* 行と列の両方が範囲内の場合のみアクセス */
    process_element(matrix[row][col]);
}

/* 動的配列（ポインター）の操作 */
int *data = NULL;
if (size > 0 && (size_t)size <= ((size_t)-1) / sizeof *data) {
    data = malloc((size_t)size * sizeof *data);
}
if (data != NULL && initialize_array(data, size)) {
    /* メモリ確保成功、かつ初期化成功の場合のみ使用 */
    use_array(data, size);
}
free(data);  /* free()はNULLに対して安全 */
```

##### 文字列処理の安全性確保

```c
/* 文字列の安全なチェック */
char *str = get_string();  /* NULL を返す可能性がある */
if (str && strlen(str) > 0 && str[0] == 'A') {
    /* str が NULL の場合、strlen や str[0] は評価されない */
    printf("String starts with 'A'\n");
}

/* 文字列の詳細な検証 */
char *input = get_user_input();
if (input && *input && strlen(input) < MAX_LENGTH && is_valid_format(input)) {
    /* NULL でない、空でない、長さ制限内、フォーマット正しい */
    process_input(input);
}
```

##### ファイル操作とリソース管理

```c
/* ファイル操作の連鎖的エラーチェック */
FILE *fp = fopen("data.txt", "r");
if (fp != NULL && read_header(fp) && validate_data(fp)) {
    /* 各段階でエラーがあれば、後続の処理はスキップされる */
    process_file(fp);
}
if (fp != NULL) {
    fclose(fp);
}

/* 複数リソースの管理 */
void process_data_file(const char *filename)
{
    FILE *fp = NULL;
    char *buffer = NULL;
    int *data = NULL;

    /* リソースの段階的確保 */
    if ((fp = fopen(filename, "rb")) != NULL &&
        (buffer = malloc(BUFFER_SIZE)) != NULL &&
        (data = malloc(sizeof *data * MAX_ITEMS)) != NULL &&
        read_file_to_buffer(fp, buffer, BUFFER_SIZE) &&
        parse_buffer_to_data(buffer, data, MAX_ITEMS)) {

        /* すべてのリソースが正常に確保され、処理が成功 */
        analyze_data(data, MAX_ITEMS);

    } else {
        /* どこかでエラーが発生した */
        fprintf(stderr, "Data processing failed\n");
    }

    /* クリーンアップ（NULL チェック不要） */
    free(data);
    free(buffer);
    if (fp != NULL) fclose(fp);
}
```

#### ビット操作とビットフィールド

ビット演算の詳細な解説、ビットマスクを使った高度なテクニック、ビットフィールドによるメモリ最適化については、専用の章を設けています。

[第12章：ビット操作とビットフィールド](../bit-operations/README.md)では、次の内容を説明しています。

- ビット演算子の詳細と活用法
- フラグ管理システムの実装
- ビットカウントなどの高度なアルゴリズム
- ビットフィールドによるデータ圧縮
- RGB色操作などの実践的な応用例

#### 共用体（union）

共用体は、複数のメンバが同じ記憶域を共有する型です。
同時には一つの表現だけを保持するデータを、タグと組み合わせて表す場合に使います。

##### 基本的な共用体の使い方

```c
/* 基本的な共用体の定義 */
union Data {
    int i;
    float f;
    char str[20];
};

int main(void) {
    union Data data;

    /* 整数として使用 */
    data.i = 42;
    printf("Integer: %d\n", data.i);

    /* 浮動小数点として使用（前の値は上書きされる） */
    data.f = 3.14f;
    printf("Floating: %f\n", data.f);

    /* 文字列として使用 */
    strcpy(data.str, "Hello");
    printf("String: %s\n", data.str);

    printf("Union size: %lu bytes\n", (unsigned long)sizeof(union Data));
    return 0;
}
```

##### オブジェクト表現の取得

```c
/* floatのオブジェクト表現を1バイトずつ表示する */
#include <stddef.h>
#include <stdio.h>
#include <string.h>

void print_float_representation(float value)
{
    unsigned char bytes[sizeof value];
    size_t i;

    memcpy(bytes, &value, sizeof value);
    for (i = 0; i < sizeof bytes; i++) {
        printf("%02X ", (unsigned int)bytes[i]);
    }
    putchar('\n');
}
```

`unsigned char`の配列へ`memcpy`すると、別の共用体メンバを読む方法に依存せずオブジェクト表現を取得できます。
ただし、`float`の形式やバイト順序は処理系に依存するため、表示結果をIEEE 754の各フィールドとみなせるとは限りません。

##### 32ビット値からオクテットを取り出す

```c
#include <stdint.h>

void print_ipv4_value(uint32_t ip)
{
    printf("%u.%u.%u.%u\n",
           (unsigned int)((ip >> 24) & UINT32_C(0xff)),
           (unsigned int)((ip >> 16) & UINT32_C(0xff)),
           (unsigned int)((ip >> 8) & UINT32_C(0xff)),
           (unsigned int)(ip & UINT32_C(0xff)));
}
```

整数と文字配列を共用体で重ねる方法は、処理系のバイト順序と`unsigned int`の幅に依存します。
外部形式の順序が決まっている場合は、幅が明確な整数型とシフト演算で各部分を取り出します。

##### タグ付き共用体（判別共用体）

```c
/* データ型を識別するタグ付き共用体 */
typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_STRING
} DataType;

typedef struct {
    DataType type;
    union {
        int i;
        float f;
        char *s;
    } value;
} Variant;

void print_variant(const Variant *var) {
    switch (var->type) {
        case TYPE_INT:
            printf("Integer: %d\n", var->value.i);
            break;
        case TYPE_FLOAT:
            printf("Floating: %f\n", var->value.f);
            break;
        case TYPE_STRING:
            printf("String: %s\n", var->value.s);
            break;
    }
}
```

##### 共用体の注意点

1. **現在の表現を管理する**

    - 最後に値を格納したメンバをタグで記録する
    - 別のメンバを読む処理は型や処理系に依存するため、移植可能な型変換には使わない

2. **メモリサイズ**

    - 最大のメンバを格納できる大きさ以上になる
    - パディングの影響を受ける

3. **初期化**

    - C90では最初のメンバーでのみ初期化可能
    - C99では指定初期化子が使用可能

##### 条件の評価順序を使った処理

```c
/* 条件付き処理の最適化 */
typedef struct {
    int is_cached;
    int cache_value;
} Cache;

int get_expensive_value(Cache *cache, int param)
{
    int result;

    /* キャッシュ済みなら、値が0でもその値を返す */
    if (cache != NULL && cache->is_cached) {
        return cache->cache_value;
    }

    /* 高コストな計算 */
    result = expensive_calculation(param);

    /* キャッシュに保存 */
    if (cache != NULL) {
        cache->is_cached = 1;
        cache->cache_value = result;
    }

    return result;
}

/* 権限チェックの最適化 */
int can_access_resource(User *user, Resource *resource)
{
    /* 管理者の場合は、右辺の詳細な権限検査を評価しない */
    return (user != NULL && user->is_admin) ||
           /* 一般ユーザーは詳細な権限チェック */
           (user != NULL &&
            resource != NULL &&
            user->level >= resource->required_level &&
            has_permission(user, resource->type) &&
            !is_blocked(user, resource));
}
```

## 次の章へ

規格ごとの機能差を続けて確認する場合は、[C23の新機能](../c23-features/README.md)を参照してください。

- [C23の新機能](../c23-features/README.md)（オプション）

## 参考資料

- examples/ - 実装例（複数C標準対応）
- exercises/ - 演習問題
- solutions/ - 解答例
- [C標準ライブラリリファレンス](https://en.cppreference.com/w/c)
- [GNU Make Manual](https://www.gnu.org/software/make/manual/)

## 演習問題

[演習問題](exercises/)では、分割コンパイル、リンケージ、マクロ、短絡評価、共用体を確認できます。

- 基礎問題：基本的な文法や概念の確認
- 応用問題：より実践的なプログラムの作成
- チャレンジ問題：高度な理解と実装力が必要な問題
