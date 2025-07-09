/*
 * 演習1-5: 数字を使った挨拶
 */

#include <stdio.h>

int main(void) {
    char name[50];
    int age;
    
    printf("お名前は？: ");
    scanf("%s", name);
    
    printf("年齢は？: ");
    scanf("%d", &age);
    
    printf("こんにちは、%sさん（%d歳）！\n", name, age);
    
    return 0;
}