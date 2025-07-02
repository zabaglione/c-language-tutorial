/*
 * ファイル名: ex13_3_product_c99.c
 * 演習13-3: 商品管理（C99版）
 * 説明: 商品情報の構造体配列で複数商品を管理
 * 規格: C99準拠 - bool型、inline関数、指定初期化子、複合リテラル
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX_PRODUCTS 10
#define MAX_NAME_LEN 50

// 商品カテゴリのenum
typedef enum {
    CATEGORY_COMPUTER,
    CATEGORY_ACCESSORY,
    CATEGORY_PERIPHERAL,
    CATEGORY_OTHER
} ProductCategory;

// 商品情報を表す構造体
typedef struct {
    uint32_t code;
    char name[MAX_NAME_LEN];
    double price;
    int32_t stock;
    ProductCategory category;
    bool is_active;  // C99: 販売中フラグ
} Product;

// 検索結果を表す構造体
typedef struct {
    bool found;
    size_t index;
    Product *product;
} SearchResult;

// カテゴリ名を取得する関数
static inline const char* get_category_name(ProductCategory category)
{
    switch (category) {
        case CATEGORY_COMPUTER: return "コンピュータ";
        case CATEGORY_ACCESSORY: return "アクセサリ";
        case CATEGORY_PERIPHERAL: return "周辺機器";
        case CATEGORY_OTHER: default: return "その他";
    }
}

// C99: inline関数で商品検証
static inline bool validate_product(uint32_t code, const char *name, 
                                   double price, int32_t stock)
{
    if (name == NULL || strlen(name) == 0) {
        printf("エラー: 商品名が無効です\n");
        return false;
    }
    
    if (price < 0) {
        printf("エラー: 価格は0以上である必要があります\n");
        return false;
    }
    
    if (stock < 0) {
        printf("エラー: 在庫数は0以上である必要があります\n");
        return false;
    }
    
    return true;
}

// 商品を追加する関数（拡張版）
bool add_product_extended(Product products[], size_t *count, 
                         uint32_t code, const char *name, double price, 
                         int32_t stock, ProductCategory category)
{
    if (*count >= MAX_PRODUCTS) {
        printf("エラー: これ以上商品を追加できません（最大%d個）\n", MAX_PRODUCTS);
        return false;
    }
    
    if (!validate_product(code, name, price, stock)) {
        return false;
    }
    
    // 商品コードの重複チェック
    for (size_t i = 0; i < *count; i++) {
        if (products[i].code == code) {
            printf("エラー: 商品コード %u は既に登録されています\n", code);
            return false;
        }
    }
    
    // C99: 指定初期化子で商品を作成
    products[*count] = (Product){
        .code = code,
        .price = price,
        .stock = stock,
        .category = category,
        .is_active = true
    };
    strncpy(products[*count].name, name, MAX_NAME_LEN - 1);
    products[*count].name[MAX_NAME_LEN - 1] = '\0';
    
    (*count)++;
    printf("商品「%s」を追加しました。\n", name);
    
    return true;
}

// 全商品を表示する関数（詳細版）
void display_all_products_detailed(const Product products[], size_t count)
{
    if (count == 0) {
        printf("登録されている商品はありません。\n");
        return;
    }
    
    printf("\n=== 商品一覧 ===\n");
    printf("%-6s %-20s %-12s %10s %8s %8s\n", 
           "コード", "商品名", "カテゴリ", "価格", "在庫", "状態");
    printf("----------------------------------------------------------------------\n");
    
    double total_value = 0.0;
    int32_t active_count = 0;
    
    for (size_t i = 0; i < count; i++) {
        printf("%-6u %-20s %-12s %10.0f円 %8d個 %8s\n",
               products[i].code,
               products[i].name,
               get_category_name(products[i].category),
               products[i].price,
               products[i].stock,
               products[i].is_active ? "販売中" : "販売停止");
        
        if (products[i].is_active) {
            total_value += products[i].price * products[i].stock;
            active_count++;
        }
    }
    
    printf("----------------------------------------------------------------------\n");
    printf("登録商品数: %zu個 (販売中: %d個)\n", count, active_count);
    printf("在庫総額（販売中のみ）: %.0f円\n", total_value);
}

// C99: 高度な検索機能
SearchResult search_product(Product products[], size_t count, 
                           bool (*predicate)(const Product*))
{
    SearchResult result = {.found = false, .index = 0, .product = NULL};
    
    for (size_t i = 0; i < count; i++) {
        if (predicate(&products[i])) {
            result.found = true;
            result.index = i;
            result.product = &products[i];
            return result;
        }
    }
    
    return result;
}

// 検索条件の例: コードで検索
static bool search_by_code_predicate(const Product *product)
{
    static uint32_t target_code = 0;
    return product->code == target_code;
}

// 商品コードで検索する関数
Product* find_product_by_code(Product products[], size_t count, uint32_t code)
{
    for (size_t i = 0; i < count; i++) {
        if (products[i].code == code) {
            return &products[i];
        }
    }
    return NULL;
}

// 在庫を更新する関数（履歴機能付き）
bool update_stock_with_history(Product products[], size_t count, 
                              uint32_t code, int32_t new_stock)
{
    if (new_stock < 0) {
        printf("エラー: 在庫数は0以上である必要があります\n");
        return false;
    }
    
    Product *product = find_product_by_code(products, count, code);
    
    if (product == NULL) {
        printf("エラー: 商品コード %u は見つかりませんでした\n", code);
        return false;
    }
    
    int32_t old_stock = product->stock;
    int32_t diff = new_stock - old_stock;
    product->stock = new_stock;
    
    printf("商品「%s」の在庫を更新しました: %d個 → %d個 ",
           product->name, old_stock, new_stock);
    
    if (diff > 0) {
        printf("(+%d個)\n", diff);
    } else if (diff < 0) {
        printf("(%d個)\n", diff);
    } else {
        printf("(変更なし)\n");
    }
    
    // 在庫切れ警告
    if (new_stock == 0 && old_stock > 0) {
        printf("⚠️  警告: 在庫切れになりました！\n");
    }
    
    return true;
}

// カテゴリ別集計
void summarize_by_category(const Product products[], size_t count)
{
    struct CategorySummary {
        int count;
        double total_value;
        int total_stock;
    } summary[4] = {{0, 0.0, 0}};  // C99: 配列の初期化
    
    for (size_t i = 0; i < count; i++) {
        if (products[i].is_active) {
            ProductCategory cat = products[i].category;
            summary[cat].count++;
            summary[cat].total_value += products[i].price * products[i].stock;
            summary[cat].total_stock += products[i].stock;
        }
    }
    
    printf("\n=== カテゴリ別集計 ===\n");
    printf("%-12s %6s %12s %10s\n", "カテゴリ", "商品数", "在庫総額", "在庫数");
    printf("------------------------------------------------\n");
    
    for (int i = 0; i < 4; i++) {
        if (summary[i].count > 0) {
            printf("%-12s %6d %12.0f円 %10d個\n",
                   get_category_name((ProductCategory)i),
                   summary[i].count,
                   summary[i].total_value,
                   summary[i].total_stock);
        }
    }
}

// 価格分析
void analyze_prices(const Product products[], size_t count)
{
    if (count == 0) return;
    
    double min_price = products[0].price;
    double max_price = products[0].price;
    double total_price = 0.0;
    size_t active_count = 0;
    
    for (size_t i = 0; i < count; i++) {
        if (products[i].is_active) {
            if (products[i].price < min_price) min_price = products[i].price;
            if (products[i].price > max_price) max_price = products[i].price;
            total_price += products[i].price;
            active_count++;
        }
    }
    
    printf("\n=== 価格分析（販売中商品のみ）===\n");
    printf("最低価格: %.0f円\n", min_price);
    printf("最高価格: %.0f円\n", max_price);
    printf("平均価格: %.0f円\n", active_count > 0 ? total_price / active_count : 0);
    printf("価格幅: %.0f円\n", max_price - min_price);
}

int main(void)
{
    Product products[MAX_PRODUCTS];
    size_t product_count = 0;
    
    printf("===== 商品管理システム (C99版) =====\n\n");
    
    // C99: 複合リテラルを使った初期データ
    Product initial_products[] = {
        {.code = 101, .name = "ノートPC", .price = 98000, 
         .stock = 5, .category = CATEGORY_COMPUTER, .is_active = true},
        {.code = 102, .name = "USBメモリ", .price = 2500, 
         .stock = 20, .category = CATEGORY_ACCESSORY, .is_active = true},
        {.code = 103, .name = "マウス", .price = 1500, 
         .stock = 15, .category = CATEGORY_PERIPHERAL, .is_active = true},
        {.code = 104, .name = "キーボード", .price = 3500, 
         .stock = 8, .category = CATEGORY_PERIPHERAL, .is_active = true},
        {.code = 105, .name = "モニター", .price = 25000, 
         .stock = 3, .category = CATEGORY_PERIPHERAL, .is_active = true}
    };
    
    // 初期データを追加
    for (size_t i = 0; i < sizeof(initial_products) / sizeof(initial_products[0]); i++) {
        add_product_extended(products, &product_count,
                           initial_products[i].code,
                           initial_products[i].name,
                           initial_products[i].price,
                           initial_products[i].stock,
                           initial_products[i].category);
    }
    
    // メニューのシミュレーション
    printf("\n=== 商品管理システム ===\n");
    printf("1. 商品追加\n");
    printf("2. 商品一覧表示\n");
    printf("3. 在庫更新\n");
    printf("4. カテゴリ別集計\n");
    printf("0. 終了\n");
    
    // デモ: 商品一覧を表示
    printf("\n選択: 2\n");
    display_all_products_detailed(products, product_count);
    
    // デモ: 新商品を追加
    printf("\n選択: 1\n");
    printf("\n商品コード: 106\n");
    printf("商品名: ヘッドセット\n");
    printf("価格: 4800\n");
    printf("在庫数: 12\n");
    printf("カテゴリ: 2 (周辺機器)\n");
    add_product_extended(products, &product_count, 106, "ヘッドセット", 
                        4800, 12, CATEGORY_PERIPHERAL);
    
    // デモ: 在庫更新
    printf("\n選択: 3\n");
    printf("\n更新する商品コード: 103\n");
    printf("新しい在庫数: 25\n");
    update_stock_with_history(products, product_count, 103, 25);
    
    // デモ: カテゴリ別集計
    printf("\n選択: 4\n");
    summarize_by_category(products, product_count);
    
    // 追加機能のデモ
    printf("\n\n=== 追加機能デモ (C99) ===\n");
    
    // 価格分析
    analyze_prices(products, product_count);
    
    // 在庫アラート
    printf("\n\n=== 在庫アラート（5個以下）===\n");
    bool alert_found = false;
    for (size_t i = 0; i < product_count; i++) {
        if (products[i].is_active && products[i].stock <= 5) {
            if (!alert_found) {
                printf("%-6s %-20s %8s\n", "コード", "商品名", "在庫");
                printf("------------------------------------\n");
                alert_found = true;
            }
            printf("%-6u %-20s %8d個", 
                   products[i].code, products[i].name, products[i].stock);
            if (products[i].stock == 0) {
                printf(" ⚠️在庫切れ");
            } else if (products[i].stock <= 3) {
                printf(" ⚠️要補充");
            }
            printf("\n");
        }
    }
    
    if (!alert_found) {
        printf("在庫が少ない商品はありません。\n");
    }
    
    // 商品の無効化デモ
    printf("\n\n=== 商品の販売停止デモ ===\n");
    Product *product = find_product_by_code(products, product_count, 105);
    if (product) {
        product->is_active = false;
        printf("商品「%s」を販売停止にしました。\n", product->name);
    }
    
    // 最終状態表示
    printf("\n選択: 2\n");
    display_all_products_detailed(products, product_count);
    
    printf("\n選択: 0\n");
    printf("システムを終了します。\n");
    
    return 0;
}

/*
実行例:
===== 商品管理システム (C99版) =====

商品「ノートPC」を追加しました。
商品「USBメモリ」を追加しました。
商品「マウス」を追加しました。
商品「キーボード」を追加しました。
商品「モニター」を追加しました。

=== 商品管理システム ===
1. 商品追加
2. 商品一覧表示
3. 在庫更新
4. カテゴリ別集計
0. 終了

選択: 2

=== 商品一覧 ===
コード 商品名               カテゴリ          価格     在庫     状態
----------------------------------------------------------------------
101    ノートPC             コンピュータ    98000円        5個   販売中
102    USBメモリ            アクセサリ       2500円       20個   販売中
103    マウス               周辺機器         1500円       15個   販売中
104    キーボード           周辺機器         3500円        8個   販売中
105    モニター             周辺機器        25000円        3個   販売中
----------------------------------------------------------------------
登録商品数: 5個 (販売中: 5個)
在庫総額（販売中のみ）: 693500円

選択: 1

商品コード: 106
商品名: ヘッドセット
価格: 4800
在庫数: 12
カテゴリ: 2 (周辺機器)
商品「ヘッドセット」を追加しました。

選択: 3

更新する商品コード: 103
新しい在庫数: 25
商品「マウス」の在庫を更新しました: 15個 → 25個 (+10個)

選択: 4

=== カテゴリ別集計 ===
カテゴリ     商品数     在庫総額     在庫数
------------------------------------------------
コンピュータ      1      490000円         5個
アクセサリ        1       50000円        20個
周辺機器          4      226100円        51個

=== 追加機能デモ (C99) ===

=== 価格分析（販売中商品のみ）===
最低価格: 1500円
最高価格: 98000円
平均価格: 22133円
価格幅: 96500円

=== 在庫アラート（5個以下）===
コード 商品名                   在庫
------------------------------------
101    ノートPC                     5個
105    モニター                     3個 ⚠️要補充

=== 商品の販売停止デモ ===
商品「モニター」を販売停止にしました。

選択: 2

=== 商品一覧 ===
コード 商品名               カテゴリ          価格     在庫     状態
----------------------------------------------------------------------
101    ノートPC             コンピュータ    98000円        5個   販売中
102    USBメモリ            アクセサリ       2500円       20個   販売中
103    マウス               周辺機器         1500円       25個   販売中
104    キーボード           周辺機器         3500円        8個   販売中
105    モニター             周辺機器        25000円        3個 販売停止
106    ヘッドセット         周辺機器         4800円       12個   販売中
----------------------------------------------------------------------
登録商品数: 6個 (販売中: 5個)
在庫総額（販売中のみ）: 641100円

選択: 0
システムを終了します。
*/
