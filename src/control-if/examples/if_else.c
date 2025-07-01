/*
 * if-else文のデモ
 * 二者択一の条件分岐
 */
#include <stdio.h>

int main(void)
{
    int age = 19;
    int password = 1234;
    int input = 1234;
    
    printf("=== if-else文 ===\n");
    
    /* 成人判定 */
    printf("年齢: %d歳\n", age);
    if (age >= 20) {
        printf("成人です\n");
        printf("選挙権があります\n");
    } else {
        printf("未成年です\n");
        printf("あと%d年で成人です\n", 20 - age);
    }
    
    /* パスワード認証 */
    printf("\nパスワード認証:\n");
    if (password == input) {
        printf("ログイン成功！\n");
        printf("ようこそ！\n");
    } else {
        printf("パスワードが違います\n");
        printf("もう一度お試しください\n");
    }
    
    return 0;
}