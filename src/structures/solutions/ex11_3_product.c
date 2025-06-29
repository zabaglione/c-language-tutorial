/*
 * ファイル名: ex11_3_product.c
 * 演習11-3: 商品管理
 * 説明: 商品情報の構造体配列で複数商品を管理
 * 規格: C90準拠
 */

#include <stdio.h>
#include <string.h>

#define MAX_PRODUCTS 10
#define MAX_NAME_LEN 50

/* 商品情報を表す構造体 */
struct Product {
    int code;
    char name[MAX_NAME_LEN];
    double price;
    int stock;
};

/* 商品を追加する関数 */
int add_product(struct Product products[], int *count, 
                int code, const char *name, double price, int stock)
{
    int i;
    
    if (*count >= MAX_PRODUCTS) {
        printf("エラー: これ以上商品を追加できません（最大%d個）\n", MAX_PRODUCTS);
        return 0;
    }
    
    if (name == NULL || strlen(name) == 0) {
        printf("エラー: 商品名が無効です\n");
        return 0;
    }
    
    if (price < 0) {
        printf("エラー: 価格は0以上である必要があります\n");
        return 0;
    }
    
    if (stock < 0) {
        printf("エラー: 在庫数は0以上である必要があります\n");
        return 0;
    }
    
    /* 商品コードの重複チェック */
    for (i = 0; i < *count; i++) {
        if (products[i].code == code) {
            printf("エラー: 商品コード %d は既に登録されています\n", code);
            return 0;
        }
    }
    
    /* 商品を追加 */
    products[*count].code = code;
    strncpy(products[*count].name, name, MAX_NAME_LEN - 1);
    products[*count].name[MAX_NAME_LEN - 1] = '\0';
    products[*count].price = price;
    products[*count].stock = stock;
    
    (*count)++;
    printf("商品を追加しました。\n");
    
    return 1;
}

/* 全商品を表示する関数 */
void display_all_products(const struct Product products[], int count)
{
    int i;
    double total_value = 0.0;
    
    if (count == 0) {
        printf("登録されている商品はありません。\n");
        return;
    }
    
    printf("\n=== 商品一覧 ===\n");
    printf("%-8s %-20s %10s %8s\n", "コード", "商品名", "価格", "在庫");
    printf("--------------------------------------------------------\n");
    
    for (i = 0; i < count; i++) {
        printf("%-8d %-20s %10.0f円 %8d個\n",
               products[i].code,
               products[i].name,
               products[i].price,
               products[i].stock);
        total_value += products[i].price * products[i].stock;
    }
    
    printf("--------------------------------------------------------\n");
    printf("登録商品数: %d個\n", count);
    printf("在庫総額: %.0f円\n", total_value);
}

/* 商品コードで検索する関数 */
struct Product* find_product_by_code(struct Product products[], int count, int code)
{
    int i;
    
    for (i = 0; i < count; i++) {
        if (products[i].code == code) {
            return &products[i];
        }
    }
    
    return NULL;
}

/* 在庫を更新する関数 */
int update_stock(struct Product products[], int count, int code, int new_stock)
{
    struct Product *product;
    int old_stock;
    
    if (new_stock < 0) {
        printf("エラー: 在庫数は0以上である必要があります\n");
        return 0;
    }
    
    product = find_product_by_code(products, count, code);
    
    if (product == NULL) {
        printf("エラー: 商品コード %d は見つかりませんでした\n", code);
        return 0;
    }
    
    old_stock = product->stock;
    product->stock = new_stock;
    
    printf("商品「%s」の在庫を更新しました: %d個 → %d個\n",
           product->name, old_stock, new_stock);
    
    return 1;
}

/* 在庫が少ない商品を表示する関数 */
void display_low_stock(const struct Product products[], int count, int threshold)
{
    int i;
    int found = 0;
    
    printf("\n=== 在庫が%d個以下の商品 ===\n", threshold);
    
    for (i = 0; i < count; i++) {
        if (products[i].stock <= threshold) {
            if (!found) {
                printf("%-8s %-20s %8s\n", "コード", "商品名", "在庫");
                printf("----------------------------------------\n");
                found = 1;
            }
            printf("%-8d %-20s %8d個\n",
                   products[i].code,
                   products[i].name,
                   products[i].stock);
        }
    }
    
    if (!found) {
        printf("該当する商品はありません。\n");
    }
}

/* 価格帯で商品を検索する関数 */
void search_by_price_range(const struct Product products[], int count,
                          double min_price, double max_price)
{
    int i;
    int found = 0;
    
    printf("\n=== 価格 %.0f円 〜 %.0f円 の商品 ===\n", min_price, max_price);
    
    for (i = 0; i < count; i++) {
        if (products[i].price >= min_price && products[i].price <= max_price) {
            if (!found) {
                printf("%-8s %-20s %10s\n", "コード", "商品名", "価格");
                printf("----------------------------------------\n");
                found = 1;
            }
            printf("%-8d %-20s %10.0f円\n",
                   products[i].code,
                   products[i].name,
                   products[i].price);
        }
    }
    
    if (!found) {
        printf("該当する商品はありません。\n");
    }
}

int main(void)
{
    struct Product products[MAX_PRODUCTS];
    int product_count = 0;
    int choice;
    
    printf("===== 商品管理システム =====\n\n");
    
    /* デモ用: 初期データを追加 */
    add_product(products, &product_count, 101, "ノートPC", 98000, 5);
    add_product(products, &product_count, 102, "USBメモリ", 2500, 20);
    add_product(products, &product_count, 103, "マウス", 1500, 15);
    add_product(products, &product_count, 104, "キーボード", 3500, 8);
    add_product(products, &product_count, 105, "モニター", 25000, 3);
    
    /* メニューのシミュレーション */
    printf("\n=== 商品管理システム ===\n");
    printf("1. 商品追加\n");
    printf("2. 商品一覧表示\n");
    printf("3. 在庫更新\n");
    printf("0. 終了\n");
    
    /* デモ: 商品一覧を表示 */
    printf("選択: 2\n");
    display_all_products(products, product_count);
    
    /* デモ: 新商品を追加 */
    printf("\n選択: 1\n");
    printf("\n商品コード: 106\n");
    printf("商品名: ヘッドセット\n");
    printf("価格: 4800\n");
    printf("在庫数: 12\n");
    add_product(products, &product_count, 106, "ヘッドセット", 4800, 12);
    
    /* デモ: 在庫更新 */
    printf("\n選択: 3\n");
    printf("\n更新する商品コード: 103\n");
    printf("新しい在庫数: 25\n");
    update_stock(products, product_count, 103, 25);
    
    /* 更新後の一覧表示 */
    printf("\n選択: 2\n");
    display_all_products(products, product_count);
    
    /* 追加機能のデモ */
    printf("\n\n=== 追加機能デモ ===\n");
    
    /* 在庫が少ない商品 */
    display_low_stock(products, product_count, 5);
    
    /* 価格帯検索 */
    search_by_price_range(products, product_count, 2000, 5000);
    
    /* 商品統計 */
    printf("\n\n=== 商品統計 ===\n");
    if (product_count > 0) {
        int i;
        double total_value = 0.0;
        double max_price = products[0].price;
        double min_price = products[0].price;
        int total_stock = 0;
        const char *expensive_product = products[0].name;
        const char *cheapest_product = products[0].name;
        
        for (i = 0; i < product_count; i++) {
            total_value += products[i].price * products[i].stock;
            total_stock += products[i].stock;
            
            if (products[i].price > max_price) {
                max_price = products[i].price;
                expensive_product = products[i].name;
            }
            if (products[i].price < min_price) {
                min_price = products[i].price;
                cheapest_product = products[i].name;
            }
        }
        
        printf("登録商品数: %d個\n", product_count);
        printf("在庫総数: %d個\n", total_stock);
        printf("在庫総額: %.0f円\n", total_value);
        printf("平均単価: %.0f円\n", total_value / total_stock);
        printf("最高価格商品: %s (%.0f円)\n", expensive_product, max_price);
        printf("最低価格商品: %s (%.0f円)\n", cheapest_product, min_price);
    }
    
    printf("\n選択: 0\n");
    printf("システムを終了します。\n");
    
    return 0;
}

/*
実行例:
===== 商品管理システム =====

商品を追加しました。
商品を追加しました。
商品を追加しました。
商品を追加しました。
商品を追加しました。

=== 商品管理システム ===
1. 商品追加
2. 商品一覧表示
3. 在庫更新
0. 終了
選択: 2

=== 商品一覧 ===
コード   商品名                     価格     在庫
--------------------------------------------------------
101      ノートPC                 98000円        5個
102      USBメモリ                 2500円       20個
103      マウス                    1500円       15個
104      キーボード                3500円        8個
105      モニター                 25000円        3個
--------------------------------------------------------
登録商品数: 5個
在庫総額: 693500円

選択: 1

商品コード: 106
商品名: ヘッドセット
価格: 4800
在庫数: 12
商品を追加しました。

選択: 3

更新する商品コード: 103
新しい在庫数: 25
商品「マウス」の在庫を更新しました: 15個 → 25個

選択: 2

=== 商品一覧 ===
コード   商品名                     価格     在庫
--------------------------------------------------------
101      ノートPC                 98000円        5個
102      USBメモリ                 2500円       20個
103      マウス                    1500円       25個
104      キーボード                3500円        8個
105      モニター                 25000円        3個
106      ヘッドセット              4800円       12個
--------------------------------------------------------
登録商品数: 6個
在庫総額: 766100円

=== 追加機能デモ ===

=== 在庫が5個以下の商品 ===
コード   商品名                   在庫
----------------------------------------
101      ノートPC                     5個
105      モニター                     3個

=== 価格 2000円 〜 5000円 の商品 ===
コード   商品名                     価格
----------------------------------------
102      USBメモリ                 2500円
104      キーボード                3500円
106      ヘッドセット              4800円

=== 商品統計 ===
登録商品数: 6個
在庫総数: 73個
在庫総額: 766100円
平均単価: 10495円
最高価格商品: ノートPC (98000円)
最低価格商品: マウス (1500円)

選択: 0
システムを終了します。
*/
