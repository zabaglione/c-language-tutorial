/**
 * 演習16-2: ビット操作と2進数リテラル
 * 8ビットフラグ管理システム
 * 
 * C23の2進数リテラルを使用して、ビットフラグの管理システムを実装します。
 */

#include <stdio.h>

/* ビットフラグの定義（2進数リテラル使用） */
#define FLAG_READ       0b00000001  /* 読み取り権限 */
#define FLAG_WRITE      0b00000010  /* 書き込み権限 */
#define FLAG_EXECUTE    0b00000100  /* 実行権限 */
#define FLAG_DELETE     0b00001000  /* 削除権限 */
#define FLAG_SHARE      0b00010000  /* 共有権限 */
#define FLAG_ARCHIVE    0b00100000  /* アーカイブフラグ */
#define FLAG_HIDDEN     0b01000000  /* 隠しファイルフラグ */
#define FLAG_SYSTEM     0b10000000  /* システムファイルフラグ */

/* ビット操作マクロ */
#define SET_BIT(flags, bit)     ((flags) |= (bit))
#define CLEAR_BIT(flags, bit)   ((flags) &= ~(bit))
#define TOGGLE_BIT(flags, bit)  ((flags) ^= (bit))
#define CHECK_BIT(flags, bit)   ((flags) & (bit))

/* フラグの型定義 */
typedef unsigned char FileFlags;

/* フラグを2進数形式で表示 */
void display_binary(FileFlags flags)
{
    printf("0b");
    for (int i = 7; i >= 0; i--) {
        printf("%d", (flags >> i) & 1);
    }
}

/* フラグの状態を詳細表示 */
void display_flags(FileFlags flags)
{
    printf("現在のフラグ: ");
    display_binary(flags);
    printf(" (0x%02X)\n", flags);
    
    printf("権限設定:\n");
    printf("  読み取り: %s\n", CHECK_BIT(flags, FLAG_READ) ? "○" : "×");
    printf("  書き込み: %s\n", CHECK_BIT(flags, FLAG_WRITE) ? "○" : "×");
    printf("  実行:     %s\n", CHECK_BIT(flags, FLAG_EXECUTE) ? "○" : "×");
    printf("  削除:     %s\n", CHECK_BIT(flags, FLAG_DELETE) ? "○" : "×");
    printf("  共有:     %s\n", CHECK_BIT(flags, FLAG_SHARE) ? "○" : "×");
    
    printf("属性:\n");
    printf("  アーカイブ: %s\n", CHECK_BIT(flags, FLAG_ARCHIVE) ? "○" : "×");
    printf("  隠し:       %s\n", CHECK_BIT(flags, FLAG_HIDDEN) ? "○" : "×");
    printf("  システム:   %s\n", CHECK_BIT(flags, FLAG_SYSTEM) ? "○" : "×");
}

/* 基本権限の設定（読み取り、書き込み、実行） */
void set_basic_permissions(FileFlags *flags)
{
    *flags = FLAG_READ | FLAG_WRITE | FLAG_EXECUTE;
    printf("基本権限を設定しました: ");
    display_binary(*flags);
    printf("\n");
}

/* フルアクセス権限の設定 */
void set_full_access(FileFlags *flags)
{
    *flags = FLAG_READ | FLAG_WRITE | FLAG_EXECUTE | FLAG_DELETE | FLAG_SHARE;
    printf("フルアクセス権限を設定しました: ");
    display_binary(*flags);
    printf("\n");
}

/* 読み取り専用に設定 */
void set_readonly(FileFlags *flags)
{
    *flags = FLAG_READ;
    printf("読み取り専用に設定しました: ");
    display_binary(*flags);
    printf("\n");
}

/* アクセスレベルをチェック */
void check_access_level(FileFlags flags)
{
    printf("\nアクセスレベル解析:\n");
    
    /* 基本的なアクセスパターンをチェック */
    if ((flags & (FLAG_READ | FLAG_WRITE | FLAG_EXECUTE)) == 
        (FLAG_READ | FLAG_WRITE | FLAG_EXECUTE)) {
        printf("- フルコントロール可能\n");
    } else if ((flags & (FLAG_READ | FLAG_WRITE)) == (FLAG_READ | FLAG_WRITE)) {
        printf("- 読み書き可能\n");
    } else if (flags & FLAG_READ) {
        printf("- 読み取り専用\n");
    } else {
        printf("- アクセス権限なし\n");
    }
    
    /* 特殊な組み合わせをチェック */
    if ((flags & (FLAG_SYSTEM | FLAG_HIDDEN)) == (FLAG_SYSTEM | FLAG_HIDDEN)) {
        printf("- 保護されたシステムファイル\n");
    }
    
    if (!(flags & FLAG_SHARE) && (flags & FLAG_WRITE)) {
        printf("- 排他的書き込みモード\n");
    }
}

/* ビット演算のデモンストレーション */
void demonstrate_bit_operations(void)
{
    FileFlags flags = 0;
    
    printf("\n=== ビット演算デモ ===\n");
    
    /* 個別ビットの設定 */
    printf("\n1. ビットを1つずつ設定:\n");
    SET_BIT(flags, FLAG_READ);
    printf("   READ設定後:     ");
    display_binary(flags);
    printf("\n");
    
    SET_BIT(flags, FLAG_WRITE);
    printf("   WRITE設定後:    ");
    display_binary(flags);
    printf("\n");
    
    SET_BIT(flags, FLAG_HIDDEN);
    printf("   HIDDEN設定後:   ");
    display_binary(flags);
    printf("\n");
    
    /* ビットのクリア */
    printf("\n2. ビットをクリア:\n");
    CLEAR_BIT(flags, FLAG_WRITE);
    printf("   WRITEクリア後:  ");
    display_binary(flags);
    printf("\n");
    
    /* ビットのトグル */
    printf("\n3. ビットをトグル:\n");
    printf("   EXECUTE トグル前: ");
    display_binary(flags);
    printf("\n");
    TOGGLE_BIT(flags, FLAG_EXECUTE);
    printf("   EXECUTE トグル後: ");
    display_binary(flags);
    printf("\n");
    TOGGLE_BIT(flags, FLAG_EXECUTE);
    printf("   再度トグル後:     ");
    display_binary(flags);
    printf("\n");
    
    /* 複数ビットの一括操作 */
    printf("\n4. 複数ビットの一括設定:\n");
    flags |= (FLAG_ARCHIVE | FLAG_SYSTEM);
    printf("   ARCHIVE|SYSTEM:  ");
    display_binary(flags);
    printf("\n");
}

int main(void)
{
    FileFlags file_flags = 0;
    
    printf("=== 2進数リテラルを使ったビットフラグ管理 ===\n\n");
    
    /* 初期状態 */
    printf("初期状態:\n");
    display_flags(file_flags);
    
    /* 基本権限の設定 */
    printf("\n--- 基本権限の設定 ---\n");
    set_basic_permissions(&file_flags);
    display_flags(file_flags);
    check_access_level(file_flags);
    
    /* 属性の追加 */
    printf("\n--- 属性の追加 ---\n");
    SET_BIT(file_flags, FLAG_ARCHIVE);
    printf("アーカイブ属性を追加\n");
    display_flags(file_flags);
    
    /* フルアクセスに変更 */
    printf("\n--- フルアクセスに変更 ---\n");
    set_full_access(&file_flags);
    display_flags(file_flags);
    check_access_level(file_flags);
    
    /* システムファイルとして設定 */
    printf("\n--- システムファイル設定 ---\n");
    SET_BIT(file_flags, FLAG_SYSTEM);
    SET_BIT(file_flags, FLAG_HIDDEN);
    CLEAR_BIT(file_flags, FLAG_DELETE);  /* 削除不可に */
    display_flags(file_flags);
    check_access_level(file_flags);
    
    /* 読み取り専用に変更 */
    printf("\n--- 読み取り専用に変更 ---\n");
    set_readonly(&file_flags);
    display_flags(file_flags);
    check_access_level(file_flags);
    
    /* ビット演算のデモ */
    demonstrate_bit_operations();
    
    /* 実用例: 権限のマスク処理 */
    printf("\n\n=== 権限マスクの例 ===\n");
    FileFlags user_request = FLAG_READ | FLAG_WRITE | FLAG_DELETE;
    FileFlags allowed_mask = FLAG_READ | FLAG_WRITE;  /* 削除は許可しない */
    FileFlags granted = user_request & allowed_mask;
    
    printf("要求された権限: ");
    display_binary(user_request);
    printf("\n許可マスク:     ");
    display_binary(allowed_mask);
    printf("\n付与された権限: ");
    display_binary(granted);
    printf("\n");
    
    return 0;
}
