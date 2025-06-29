/**
 * 演習14-1: bool型の活用
 * システム状態管理プログラム
 * 
 * C23のbool型を使用して、システムの各種状態を管理し、
 * 状態の組み合わせによる判定ロジックを実装します。
 */

#include <stdio.h>

/* システム状態を管理する構造体 */
typedef struct {
    bool is_connected;      /* ネットワーク接続状態 */
    bool is_authenticated;  /* 認証状態 */
    bool has_permission;    /* アクセス権限 */
    bool is_busy;          /* ビジー状態 */
} SystemStatus;

/* 状態を初期化 */
void init_status(SystemStatus *status)
{
    status->is_connected = false;
    status->is_authenticated = false;
    status->has_permission = false;
    status->is_busy = false;
}

/* 状態を表示 */
void display_status(const SystemStatus *status)
{
    printf("=== システム状態 ===\n");
    printf("接続状態: %s\n", status->is_connected ? "接続中" : "未接続");
    printf("認証状態: %s\n", status->is_authenticated ? "認証済み" : "未認証");
    printf("権限状態: %s\n", status->has_permission ? "権限あり" : "権限なし");
    printf("動作状態: %s\n", status->is_busy ? "ビジー" : "アイドル");
    printf("==================\n");
}

/* システムが利用可能かチェック */
bool is_system_available(const SystemStatus *status)
{
    /* 接続済み、認証済み、権限あり、かつビジーでない場合に利用可能 */
    return status->is_connected && 
           status->is_authenticated && 
           status->has_permission && 
           !status->is_busy;
}

/* セキュリティチェック */
bool check_security(const SystemStatus *status)
{
    /* 接続済みかつ認証済みの場合のみセキュア */
    return status->is_connected && status->is_authenticated;
}

/* 接続を試行 */
bool connect_system(SystemStatus *status)
{
    if (status->is_connected) {
        printf("既に接続されています\n");
        return false;
    }
    
    printf("システムに接続中...\n");
    status->is_connected = true;
    printf("接続成功\n");
    return true;
}

/* 認証を試行 */
bool authenticate_system(SystemStatus *status, const char *username)
{
    if (!status->is_connected) {
        printf("エラー: 先に接続してください\n");
        return false;
    }
    
    if (status->is_authenticated) {
        printf("既に認証済みです\n");
        return false;
    }
    
    printf("ユーザー '%s' で認証中...\n", username);
    status->is_authenticated = true;
    
    /* 特定のユーザーには自動的に権限を付与 */
    if (username[0] == 'a' && username[1] == 'd' && 
        username[2] == 'm' && username[3] == 'i' && 
        username[4] == 'n' && username[5] == '\0') {
        status->has_permission = true;
        printf("管理者権限を付与しました\n");
    }
    
    printf("認証成功\n");
    return true;
}

/* タスクを実行 */
bool execute_task(SystemStatus *status, const char *task_name)
{
    if (!is_system_available(status)) {
        printf("エラー: システムが利用できません\n");
        display_status(status);
        return false;
    }
    
    status->is_busy = true;
    printf("タスク '%s' を実行中...\n", task_name);
    
    /* タスク実行のシミュレーション */
    for (int i = 0; i < 3; i++) {
        printf(".");
    }
    printf(" 完了\n");
    
    status->is_busy = false;
    return true;
}

/* 切断 */
void disconnect_system(SystemStatus *status)
{
    printf("システムから切断中...\n");
    init_status(status);  /* すべての状態をリセット */
    printf("切断完了\n");
}

int main(void)
{
    SystemStatus system;
    
    /* システム初期化 */
    init_status(&system);
    
    printf("=== bool型を使ったシステム状態管理 ===\n\n");
    
    /* 初期状態を表示 */
    display_status(&system);
    
    /* セキュリティチェック（失敗するはず） */
    printf("\nセキュリティチェック: %s\n", 
           check_security(&system) ? "OK" : "NG");
    
    /* 接続試行 */
    printf("\n");
    connect_system(&system);
    
    /* 再度セキュリティチェック（まだ失敗） */
    printf("\nセキュリティチェック: %s\n", 
           check_security(&system) ? "OK" : "NG");
    
    /* 一般ユーザーで認証 */
    printf("\n");
    authenticate_system(&system, "user");
    
    /* セキュリティチェック（成功） */
    printf("\nセキュリティチェック: %s\n", 
           check_security(&system) ? "OK" : "NG");
    
    /* タスク実行（権限なしで失敗） */
    printf("\n");
    execute_task(&system, "重要なタスク");
    
    /* 切断して再接続 */
    printf("\n");
    disconnect_system(&system);
    
    /* 管理者で再接続 */
    printf("\n");
    connect_system(&system);
    authenticate_system(&system, "admin");
    
    /* 現在の状態 */
    printf("\n");
    display_status(&system);
    
    /* タスク実行（成功） */
    printf("\n");
    execute_task(&system, "重要なタスク");
    
    /* 別のタスクも実行 */
    execute_task(&system, "データベース更新");
    execute_task(&system, "ログファイル圧縮");
    
    /* 最終的な切断 */
    printf("\n");
    disconnect_system(&system);
    
    return 0;
}
