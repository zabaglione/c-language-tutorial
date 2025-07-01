# 複数ファイル・発展技術
##  対応C規格
- **主要対象:** C90/C99/C11/C17
- **学習内容:** 分割コンパイル、extern宣言、プリプロセッサ、モジュール設計、ライブラリ作成

##  学習目標
この章を完了すると、以下のことができるようになります：
- 複数ファイルに分割したプログラムを作成できる
- extern宣言を正しく使用できる
- プリプロセッサ機能を効果的に活用できる
- 再利用可能なモジュールを設計できる
- 静的ライブラリを作成・使用できる
- 大規模プロジェクトの構成を理解する

##  概要と詳細

### 高度なトピックとは？
これまで学んできたC言語の基礎を活かして、より実践的なプログラミング技術を学びます。実際の開発現場で使われる技術です！

#### なぜ高度なトピックを学ぶのか？
1. **大規模プログラムの開発**
   - 1つのファイルに全てを書くのは非現実的
   - チーム開発では分割が必須

2. **コードの再利用**
   - 一度書いたコードを他のプロジェクトでも使える
   - ライブラリとして配布可能

3. **保守性の向上**
   - 機能ごとにファイルを分けて管理
   - バグの特定と修正が容易

### 分割コンパイルの基本 
大きなプログラムを複数のソースファイルに分割することで、保守性と再利用性が向上します。

#### 分割コンパイルの日常例
レストランの厨房を考えてみましょう：
- **前菜担当** → string_utils.c（文字列処理）
- **メイン担当** → math_utils.c（数値計算）
- **デザート担当** → file_utils.c（ファイル処理）
- **総料理長** → main.c（全体の統括）

各担当が独立して作業し、最後に組み合わせて完成！

#### 基本的な分割例

**math_utils.h（ヘッダーファイル）**
```c
#ifndef MATH_UTILS_H
#define MATH_UTILS_H

int add(int a, int b);
int multiply(int a, int b);
double circle_area(double radius);

#endif
```

**math_utils.c（実装ファイル）**
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

**main.c（メインプログラム）**
```c
#include <stdio.h>
#include "math_utils.h"

int main(void)
{
    int sum = add(10, 20);
    int product = multiply(5, 6);
    double area = circle_area(3.0);
    
    printf("合計: %d\n", sum);
    printf("積: %d\n", product);
    printf("円の面積: %.2f\n", area);
    
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

#### グローバル変数の適切な使用
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
```c
#ifdef DEBUG
    #define DEBUG_PRINT(fmt, ...) \
        printf("[DEBUG] " fmt "\n", ##__VA_ARGS__)
#else
    #define DEBUG_PRINT(fmt, ...)
#endif

#ifdef WINDOWS
    #include <windows.h>
#elif defined(LINUX)
    #include <unistd.h>
#endif
```

#### 複雑なマクロ
```c
/* 安全な除算マクロ */
#define SAFE_DIVIDE(a, b, result) \
    do { \
        if ((b) != 0) { \
            *(result) = (a) / (b); \
        } else { \
            printf("エラー: ゼロ除算\n"); \
            *(result) = 0; \
        } \
    } while (0)

/* 配列サイズ取得マクロ */
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
```

### ヘッダーファイルの設計

#### インクルードガードの重要性
```c
#ifndef MODULE_NAME_H
#define MODULE_NAME_H

/* ヘッダーファイルの内容 */

#endif /* MODULE_NAME_H */
```

#### プリコンパイルされたヘッダー
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

### モジュール設計の原則

#### 単一責任の原則
各モジュールは1つの明確な責任を持つべきです：

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
```
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

### C11/C17の新機能

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
```c
/* debug.h */
#ifndef DEBUG_H
#define DEBUG_H

#ifdef DEBUG_MODE
    #define DBG_ENTER() printf("ENTER: %s\n", __func__)
    #define DBG_EXIT() printf("EXIT: %s\n", __func__)
    #define DBG_PRINT(fmt, ...) \
        printf("[%s:%d] " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#else
    #define DBG_ENTER()
    #define DBG_EXIT()
    #define DBG_PRINT(fmt, ...)
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

/* ヘッダーファイルでのinline関数定義 */
inline double square_inline(double x)
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
完全な実装例は以下のファイルを参照してください：

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

### C11/C17の新機能
- _Static_assert
- _Generic
- _Alignas/_Alignof
- _Thread_local

## 次の章へ
これでC言語の主要トピックは完了です。さらに学習を続けたい場合は：
- [C23の新機能](../c23-features/README.md)（オプション）
- プロジェクト実践
- 他の言語への応用

## 参考資料
- examples/ - 実装例（複数C標準対応）
- exercises/ - 演習問題
- solutions/ - 解答例
- [C標準ライブラリリファレンス](https://en.cppreference.com/w/c)
- [GNU Make Manual](https://www.gnu.org/software/make/manual/)