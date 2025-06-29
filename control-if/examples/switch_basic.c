/*
 * switch文の基本的な使い方（C90準拠）
 * 
 * このプログラムは、switch文による多分岐処理の
 * 基本的な使い方を示します。
 * 規格: C90準拠
 */
#include <stdio.h>

int main(void)
{
    /* 変数の宣言（C90では先頭で宣言） */
    int menu_choice;
    char grade;
    int month;
    
    /* メニュー選択の例 */
    printf("=== レストランメニュー ===\n");
    printf("1. ハンバーガー (500円)\n");
    printf("2. ピザ (800円)\n");
    printf("3. パスタ (700円)\n");
    printf("4. サラダ (400円)\n");
    printf("選択してください (1-4): ");
    scanf("%d", &menu_choice);
    
    switch (menu_choice) {
        case 1:
            printf("ハンバーガーを注文しました。500円です。\n");
            break;
        case 2:
            printf("ピザを注文しました。800円です。\n");
            break;
        case 3:
            printf("パスタを注文しました。700円です。\n");
            break;
        case 4:
            printf("サラダを注文しました。400円です。\n");
            break;
        default:
            printf("無効な選択です。\n");
            break;
    }
    
    /* 成績評価の例 */
    printf("\n成績を入力してください (A-F): ");
    scanf(" %c", &grade);  /* 空白文字を読み飛ばすため、%cの前に空白を入れる */
    
    switch (grade) {
        case 'A':
        case 'a':
            printf("優秀: 90点以上\n");
            break;
        case 'B':
        case 'b':
            printf("良好: 80-89点\n");
            break;
        case 'C':
        case 'c':
            printf("普通: 70-79点\n");
            break;
        case 'D':
        case 'd':
            printf("可: 60-69点\n");
            break;
        case 'F':
        case 'f':
            printf("不可: 60点未満\n");
            break;
        default:
            printf("無効な成績です。\n");
            break;
    }
    
    /* 月から季節を判定する例（フォールスルーの活用） */
    printf("\n月を入力してください (1-12): ");
    scanf("%d", &month);
    
    printf("季節: ");
    switch (month) {
        case 12:
        case 1:
        case 2:
            printf("冬\n");
            break;
        case 3:
        case 4:
        case 5:
            printf("春\n");
            break;
        case 6:
        case 7:
        case 8:
            printf("夏\n");
            break;
        case 9:
        case 10:
        case 11:
            printf("秋\n");
            break;
        default:
            printf("無効な月です\n");
            break;
    }
    
    return 0;
}