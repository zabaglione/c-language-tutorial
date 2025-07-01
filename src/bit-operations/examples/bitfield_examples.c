/*
 * ビットフィールドの活用例（C90準拠版）
 * 
 * このプログラムは、ビットフィールドの宣言と使用方法、
 * および実践的な応用例を示します。
 */
#include <stdio.h>

/* 基本的なビットフィールド */
struct Flags {
    unsigned int flag_a : 1;   /* 1ビット */
    unsigned int flag_b : 1;   /* 1ビット */
    unsigned int flag_c : 1;   /* 1ビット */
    unsigned int reserved : 5; /* 5ビット（予約） */
};

/* 日付を圧縮して格納 */
struct PackedDate {
    unsigned int day   : 5;  /* 1-31 (5ビット) */
    unsigned int month : 4;  /* 1-12 (4ビット) */
    unsigned int year  : 7;  /* 0-127 (7ビット) 2000年からのオフセット */
};

/* RGB565形式の色 */
struct RGB565 {
    unsigned int blue  : 5;  /* 青成分 (0-31) */
    unsigned int green : 6;  /* 緑成分 (0-63) */
    unsigned int red   : 5;  /* 赤成分 (0-31) */
};

/* ファイルアクセス権限 */
struct FilePermissions {
    unsigned int owner_read    : 1;
    unsigned int owner_write   : 1;
    unsigned int owner_execute : 1;
    unsigned int group_read    : 1;
    unsigned int group_write   : 1;
    unsigned int group_execute : 1;
    unsigned int other_read    : 1;
    unsigned int other_write   : 1;
    unsigned int other_execute : 1;
    unsigned int reserved      : 7;  /* 将来の拡張用 */
};

/* ハードウェアレジスタのシミュレーション */
struct ControlRegister {
    unsigned int enable        : 1;   /* ビット0: 有効/無効 */
    unsigned int interrupt_en  : 1;   /* ビット1: 割り込み許可 */
    unsigned int mode         : 2;   /* ビット2-3: 動作モード */
    unsigned int clock_div    : 3;   /* ビット4-6: クロック分周 */
    unsigned int power_save   : 1;   /* ビット7: 省電力モード */
};

/* デバイスステータス */
struct DeviceStatus {
    unsigned int ready      : 1;
    unsigned int busy       : 1;
    unsigned int error      : 1;
    unsigned int data_ready : 1;
    unsigned int overflow   : 1;
    unsigned int underflow  : 1;
    unsigned int parity_err : 1;
    unsigned int timeout    : 1;
};

/* 権限を8進数形式で表示 */
void print_permissions(struct FilePermissions perm)
{
    int owner = (perm.owner_read << 2) | (perm.owner_write << 1) | perm.owner_execute;
    int group = (perm.group_read << 2) | (perm.group_write << 1) | perm.group_execute;
    int other = (perm.other_read << 2) | (perm.other_write << 1) | perm.other_execute;
    
    printf("権限: %d%d%d ", owner, group, other);
    
    /* rwx形式でも表示 */
    printf("(");
    printf("%c%c%c", 
           perm.owner_read ? 'r' : '-',
           perm.owner_write ? 'w' : '-',
           perm.owner_execute ? 'x' : '-');
    printf("%c%c%c", 
           perm.group_read ? 'r' : '-',
           perm.group_write ? 'w' : '-',
           perm.group_execute ? 'x' : '-');
    printf("%c%c%c", 
           perm.other_read ? 'r' : '-',
           perm.other_write ? 'w' : '-',
           perm.other_execute ? 'x' : '-');
    printf(")\n");
}

int main(void)
{
    struct Flags flags = {0};
    struct PackedDate today = {0};
    struct RGB565 color = {0};
    struct FilePermissions file_perm = {0};
    struct ControlRegister ctrl_reg = {0};
    struct DeviceStatus dev_status = {0};
    
    printf("=== ビットフィールドの活用例 ===\n\n");
    
    /* 基本的なフラグ操作 */
    printf("--- 基本的なフラグ ---\n");
    printf("初期状態: flag_a=%u, flag_b=%u, flag_c=%u\n", 
           flags.flag_a, flags.flag_b, flags.flag_c);
    
    flags.flag_a = 1;
    flags.flag_c = 1;
    printf("設定後:   flag_a=%u, flag_b=%u, flag_c=%u\n", 
           flags.flag_a, flags.flag_b, flags.flag_c);
    
    printf("構造体のサイズ: %lu バイト\n\n", sizeof(struct Flags));
    
    /* 日付の圧縮格納 */
    printf("--- 日付の圧縮格納 ---\n");
    today.day = 25;
    today.month = 12;
    today.year = 24;  /* 2024年 (2000 + 24) */
    
    printf("日付: %d年%d月%d日\n", 
           2000 + today.year, today.month, today.day);
    printf("構造体のサイズ: %lu バイト ", sizeof(struct PackedDate));
    printf("(通常なら12バイト必要)\n\n");
    
    /* RGB色の操作 */
    printf("--- RGB565形式の色 ---\n");
    /* 赤色を設定 */
    color.red = 31;    /* 最大値 */
    color.green = 0;
    color.blue = 0;
    printf("赤色: R=%u, G=%u, B=%u\n", color.red, color.green, color.blue);
    
    /* 白色を設定 */
    color.red = 31;
    color.green = 63;  /* 緑は6ビットなので最大値が違う */
    color.blue = 31;
    printf("白色: R=%u, G=%u, B=%u\n", color.red, color.green, color.blue);
    
    printf("構造体のサイズ: %lu バイト\n\n", sizeof(struct RGB565));
    
    /* ファイル権限 */
    printf("--- ファイルアクセス権限 ---\n");
    /* 755 (rwxr-xr-x) を設定 */
    file_perm.owner_read = 1;
    file_perm.owner_write = 1;
    file_perm.owner_execute = 1;
    file_perm.group_read = 1;
    file_perm.group_execute = 1;
    file_perm.other_read = 1;
    file_perm.other_execute = 1;
    
    print_permissions(file_perm);
    
    /* 644 (rw-r--r--) に変更 */
    file_perm.owner_execute = 0;
    file_perm.group_execute = 0;
    file_perm.other_execute = 0;
    
    print_permissions(file_perm);
    printf("\n");
    
    /* ハードウェアレジスタ */
    printf("--- ハードウェアレジスタ ---\n");
    ctrl_reg.enable = 1;
    ctrl_reg.interrupt_en = 0;
    ctrl_reg.mode = 2;        /* モード2 */
    ctrl_reg.clock_div = 3;   /* 1/8分周 */
    ctrl_reg.power_save = 0;
    
    printf("制御レジスタ設定:\n");
    printf("  有効: %s\n", ctrl_reg.enable ? "ON" : "OFF");
    printf("  割り込み: %s\n", ctrl_reg.interrupt_en ? "許可" : "禁止");
    printf("  動作モード: %u\n", ctrl_reg.mode);
    printf("  クロック分周: 1/%d\n", 1 << ctrl_reg.clock_div);
    printf("  省電力: %s\n", ctrl_reg.power_save ? "ON" : "OFF");
    printf("\n");
    
    /* デバイスステータス */
    printf("--- デバイスステータス ---\n");
    dev_status.ready = 1;
    dev_status.busy = 0;
    dev_status.data_ready = 1;
    
    printf("ステータス: ");
    if (dev_status.ready) printf("READY ");
    if (dev_status.busy) printf("BUSY ");
    if (dev_status.error) printf("ERROR ");
    if (dev_status.data_ready) printf("DATA_READY ");
    if (dev_status.overflow) printf("OVERFLOW ");
    if (dev_status.underflow) printf("UNDERFLOW ");
    if (dev_status.parity_err) printf("PARITY_ERR ");
    if (dev_status.timeout) printf("TIMEOUT ");
    printf("\n");
    
    /* エラー状態をシミュレート */
    dev_status.error = 1;
    dev_status.overflow = 1;
    
    printf("エラー発生後: ");
    if (dev_status.error) {
        printf("ERROR(");
        if (dev_status.overflow) printf("OVERFLOW ");
        if (dev_status.underflow) printf("UNDERFLOW ");
        if (dev_status.parity_err) printf("PARITY ");
        if (dev_status.timeout) printf("TIMEOUT ");
        printf(")");
    }
    printf("\n");
    
    return 0;
}