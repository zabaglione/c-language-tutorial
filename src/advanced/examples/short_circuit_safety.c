/*
 * short_circuit_safety.c
 * 短絡評価を使った安全なプログラミングパターン
 * C90準拠
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ダミー関数（実際のプログラムを想定） */
int initialize_array(int *arr, int size) {
    int i;
    if (!arr || size <= 0) return 0;
    for (i = 0; i < size; i++) {
        arr[i] = i + 1;
    }
    return 1;  /* 成功 */
}

void process_element(int value) {
    printf("要素を処理: %d\n", value);
}

char* get_user_input(void) {
    static char buffer[100] = "test input";
    return buffer;  /* 実際はNULLを返す可能性がある */
}

int is_valid_format(const char *str) {
    /* 簡単な検証（実際はもっと複雑） */
    return str && strlen(str) > 0 && str[0] != ' ';
}

/* 配列の安全な操作デモ */
void safe_array_demo(void) {
    int array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int *dynamic_array = NULL;
    int index, size;
    
    printf("\n=== 配列の安全な操作 ===\n");
    
    /* 境界チェックの例 */
    index = 15;  /* 範囲外 */
    if (index >= 0 && index < 10 && array[index] > 0) {
        printf("array[%d] = %d\n", index, array[index]);
    } else {
        printf("インデックス %d は範囲外です\n", index);
    }
    
    /* 動的配列の安全な操作 */
    size = 5;
    dynamic_array = (int*)malloc(size * sizeof(int));
    
    /* メモリ確保と初期化の連鎖チェック */
    if (dynamic_array && size > 0 && initialize_array(dynamic_array, size)) {
        int i;
        printf("動的配列の内容: ");
        for (i = 0; i < size; i++) {
            printf("%d ", dynamic_array[i]);
        }
        printf("\n");
    } else {
        printf("配列の初期化に失敗しました\n");
    }
    
    free(dynamic_array);  /* free()はNULLに対して安全 */
}

/* 文字列の安全な処理デモ */
void safe_string_demo(void) {
    char *str1 = NULL;
    char *str2 = "Hello";
    char *filename = "document.txt";
    char *input;
    int len;
    
    printf("\n=== 文字列の安全な処理 ===\n");
    
    /* NULLチェックの重要性 */
    if (str1 && strlen(str1) > 0 && str1[0] == 'H') {
        printf("str1は'H'で始まります\n");
    } else {
        printf("str1はNULLまたは無効です\n");
    }
    
    /* 有効な文字列の処理 */
    if (str2 && strlen(str2) > 0 && str2[0] == 'H') {
        printf("str2は'H'で始まります: %s\n", str2);
    }
    
    /* 拡張子チェック */
    len = strlen(filename);
    if (len > 4 && filename[len-4] == '.' && 
        strcmp(&filename[len-3], "txt") == 0) {
        printf("%s はテキストファイルです\n", filename);
    }
    
    /* ユーザー入力の検証 */
    input = get_user_input();
    if (input && *input && strlen(input) < 100 && is_valid_format(input)) {
        printf("有効な入力: %s\n", input);
    } else {
        printf("無効な入力です\n");
    }
}

/* ファイル操作の安全な処理 */
void safe_file_demo(void) {
    FILE *fp;
    char buffer[256];
    
    printf("\n=== ファイル操作の安全な処理 ===\n");
    
    /* ファイルオープンと読み取りの連鎖 */
    fp = fopen("test.txt", "r");
    if (fp && fgets(buffer, sizeof(buffer), fp) && strlen(buffer) > 0) {
        printf("ファイルの最初の行: %s", buffer);
    } else {
        if (!fp) {
            printf("ファイルを開けませんでした\n");
        } else {
            printf("ファイルが空または読み取りエラー\n");
        }
    }
    
    if (fp) fclose(fp);
}

/* リソース管理のデモ */
typedef struct {
    int *data;
    char *buffer;
    FILE *file;
} Resources;

int allocate_resources(Resources *res, const char *filename) {
    /* リソースの初期化 */
    res->data = NULL;
    res->buffer = NULL;
    res->file = NULL;
    
    /* 段階的なリソース確保 */
    if ((res->data = (int*)malloc(100 * sizeof(int))) &&
        (res->buffer = (char*)malloc(1024)) &&
        (res->file = fopen(filename, "r"))) {
        /* すべて成功 */
        return 1;
    }
    
    /* 失敗時のクリーンアップ */
    free(res->data);
    free(res->buffer);
    if (res->file) fclose(res->file);
    
    /* NULLに戻す */
    res->data = NULL;
    res->buffer = NULL;
    res->file = NULL;
    
    return 0;
}

void free_resources(Resources *res) {
    free(res->data);
    free(res->buffer);
    if (res->file) fclose(res->file);
}

void resource_management_demo(void) {
    Resources res;
    
    printf("\n=== リソース管理の安全な処理 ===\n");
    
    if (allocate_resources(&res, "data.txt")) {
        printf("すべてのリソースが正常に確保されました\n");
        /* リソースを使った処理 */
        free_resources(&res);
    } else {
        printf("リソースの確保に失敗しました\n");
    }
}

/* コマンドライン引数の検証 */
void validate_args(int argc, char *argv[]) {
    printf("\n=== コマンドライン引数の検証 ===\n");
    
    /* 引数の段階的チェック */
    if (argc > 1 && argv[1] && strlen(argv[1]) > 0) {
        printf("第1引数: %s\n", argv[1]);
        
        /* 追加の引数をチェック */
        if (argc > 2 && argv[2] && strlen(argv[2]) > 0) {
            printf("第2引数: %s\n", argv[2]);
        }
    } else {
        printf("引数が指定されていません\n");
    }
}

int main(int argc, char *argv[]) {
    printf("===== 短絡評価による安全なプログラミング =====\n");
    
    /* 各種デモの実行 */
    safe_array_demo();
    safe_string_demo();
    safe_file_demo();
    resource_management_demo();
    validate_args(argc, argv);
    
    return 0;
}