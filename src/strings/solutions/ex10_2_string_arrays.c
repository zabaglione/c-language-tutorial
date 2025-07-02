/*
 * ファイル名: ex10_2_string_arrays.c
 * 演習10-2: 文字列配列の管理
 * 説明: 学生名を格納する文字列配列の追加・削除・表示機能
 * 規格: C90準拠
 */

#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 10
#define MAX_NAME_LENGTH 50

/* 学生名配列の表示 */
void display_students(char students[][MAX_NAME_LENGTH], int count)
{
    int i;
    
    if (count == 0) {
        printf("登録されている学生はいません。\n");
        return;
    }
    
    printf("=== 学生一覧 ===\n");
    for (i = 0; i < count; i++) {
        printf("%d. %s\n", i + 1, students[i]);
    }
    printf("合計: %d名\n", count);
}

/* 学生の追加 */
int add_student(char students[][MAX_NAME_LENGTH], int *count, const char *name)
{
    if (*count >= MAX_STUDENTS) {
        printf("エラー: これ以上学生を追加できません（最大%d名）\n", MAX_STUDENTS);
        return 0;  /* 失敗 */
    }
    
    if (strlen(name) >= MAX_NAME_LENGTH) {
        printf("エラー: 名前が長すぎます（最大%d文字）\n", MAX_NAME_LENGTH - 1);
        return 0;  /* 失敗 */
    }
    
    /* 重複チェック */
    {
        int i;
        for (i = 0; i < *count; i++) {
            if (strcmp(students[i], name) == 0) {
                printf("エラー: \"%s\" は既に登録されています\n", name);
                return 0;  /* 失敗 */
            }
        }
    }
    
    strcpy(students[*count], name);
    (*count)++;
    printf("\"%s\" を追加しました\n", name);
    return 1;  /* 成功 */
}

/* 学生の削除（名前で検索） */
int remove_student_by_name(char students[][MAX_NAME_LENGTH], int *count, const char *name)
{
    int i, found_index = -1;
    
    /* 削除対象を検索 */
    for (i = 0; i < *count; i++) {
        if (strcmp(students[i], name) == 0) {
            found_index = i;
            break;
        }
    }
    
    if (found_index == -1) {
        printf("エラー: \"%s\" は見つかりませんでした\n", name);
        return 0;  /* 失敗 */
    }
    
    /* 要素を前に詰める */
    for (i = found_index; i < *count - 1; i++) {
        strcpy(students[i], students[i + 1]);
    }
    
    (*count)--;
    printf("\"%s\" を削除しました\n", name);
    return 1;  /* 成功 */
}

/* 学生の削除（インデックス指定） */
int remove_student_by_index(char students[][MAX_NAME_LENGTH], int *count, int index)
{
    int i;
    char name[MAX_NAME_LENGTH];
    
    if (index < 0 || index >= *count) {
        printf("エラー: 無効なインデックスです（1-%d の範囲で指定してください）\n", *count);
        return 0;  /* 失敗 */
    }
    
    /* 削除前に名前を保存 */
    strcpy(name, students[index]);
    
    /* 要素を前に詰める */
    for (i = index; i < *count - 1; i++) {
        strcpy(students[i], students[i + 1]);
    }
    
    (*count)--;
    printf("%d番目の学生 \"%s\" を削除しました\n", index + 1, name);
    return 1;  /* 成功 */
}

/* 学生の検索 */
int search_student(char students[][MAX_NAME_LENGTH], int count, const char *name)
{
    int i;
    
    for (i = 0; i < count; i++) {
        if (strcmp(students[i], name) == 0) {
            return i;  /* 見つかった場合のインデックス */
        }
    }
    
    return -1;  /* 見つからない場合 */
}

/* 学生名のソート（アルファベット順） */
void sort_students(char students[][MAX_NAME_LENGTH], int count)
{
    int i, j;
    char temp[MAX_NAME_LENGTH];
    
    /* バブルソート */
    for (i = 0; i < count - 1; i++) {
        for (j = 0; j < count - 1 - i; j++) {
            if (strcmp(students[j], students[j + 1]) > 0) {
                strcpy(temp, students[j]);
                strcpy(students[j], students[j + 1]);
                strcpy(students[j + 1], temp);
            }
        }
    }
    
    printf("学生名をアルファベット順にソートしました\n");
}

/* 部分一致検索 */
void search_partial(char students[][MAX_NAME_LENGTH], int count, const char *partial)
{
    int i;
    int found_count = 0;
    
    printf("「%s」を含む学生名:\n", partial);
    
    for (i = 0; i < count; i++) {
        if (strstr(students[i], partial) != NULL) {
            printf("  %d. %s\n", i + 1, students[i]);
            found_count++;
        }
    }
    
    if (found_count == 0) {
        printf("  該当する学生はいません\n");
    } else {
        printf("  %d名が見つかりました\n", found_count);
    }
}

int main(void)
{
    char students[MAX_STUDENTS][MAX_NAME_LENGTH];
    int student_count = 0;
    int search_index;
    
    printf("===== 学生名管理システム =====\n\n");
    
    /* 初期データの追加 */
    printf("1. 学生の追加:\n");
    add_student(students, &student_count, "田中太郎");
    add_student(students, &student_count, "佐藤花子");
    add_student(students, &student_count, "鈴木一郎");
    add_student(students, &student_count, "高橋二郎");
    add_student(students, &student_count, "伊藤三子");
    
    printf("\n");
    display_students(students, student_count);
    
    /* 重複追加のテスト */
    printf("\n2. 重複追加のテスト:\n");
    add_student(students, &student_count, "田中太郎");  /* 既に存在 */
    
    /* 検索のテスト */
    printf("\n3. 学生の検索:\n");
    search_index = search_student(students, student_count, "佐藤花子");
    if (search_index != -1) {
        printf("\"佐藤花子\" は %d番目にいます\n", search_index + 1);
    }
    
    search_index = search_student(students, student_count, "山田太郎");
    if (search_index == -1) {
        printf("\"山田太郎\" は見つかりませんでした\n");
    }
    
    /* 部分一致検索 */
    printf("\n4. 部分一致検索:\n");
    search_partial(students, student_count, "太郎");
    search_partial(students, student_count, "田");
    
    /* ソート */
    printf("\n5. ソート:\n");
    sort_students(students, student_count);
    display_students(students, student_count);
    
    /* 削除のテスト */
    printf("\n6. 学生の削除:\n");
    remove_student_by_name(students, &student_count, "佐藤花子");
    display_students(students, student_count);
    
    printf("\n");
    remove_student_by_index(students, &student_count, 0);  /* 最初の学生を削除 */
    display_students(students, student_count);
    
    /* エラーケースのテスト */
    printf("\n7. エラーケースのテスト:\n");
    remove_student_by_name(students, &student_count, "存在しない学生");
    remove_student_by_index(students, &student_count, 100);  /* 無効なインデックス */
    
    /* 最終状態 */
    printf("\n=== 最終状態 ===\n");
    display_students(students, student_count);
    
    /* 統計情報 */
    printf("\n=== 統計情報 ===\n");
    printf("現在の学生数: %d名\n", student_count);
    printf("最大収容数: %d名\n", MAX_STUDENTS);
    printf("残り収容可能数: %d名\n", MAX_STUDENTS - student_count);
    
    return 0;
}

/*
学習ポイント:
1. 配列の動的管理:
   - 要素の追加・削除
   - 配列の圧縮（詰める処理）
   - 容量管理

2. 文字列配列の操作:
   - strcpy()による安全なコピー
   - strcmp()による比較
   - strstr()による部分一致検索

3. エラーハンドリング:
   - 境界チェック
   - 重複チェック
   - 戻り値による成功/失敗の通知

4. 実用的な機能:
   - 検索機能（完全一致・部分一致）
   - ソート機能
   - 統計情報の表示

5. データ構造の設計:
   - 配列サイズの管理
   - インデックスの有効性確認
   - 一貫性のあるAPI設計

注意点:
- バッファオーバーフローの防止
- 配列の境界チェック
- メモリ効率的な削除処理
- ユーザビリティの向上
*/
