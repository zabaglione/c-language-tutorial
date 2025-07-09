/*
 * 演習1-6: 簡単な計算機
 */

#include <stdio.h>

int main(void) {
    int num1, num2, result;
    
    printf("簡単な計算機\n");
    
    printf("1つ目の数: ");
    scanf("%d", &num1);
    
    printf("2つ目の数: ");
    scanf("%d", &num2);
    
    result = num1 + num2;
    
    printf("%d + %d = %d\n", num1, num2, result);
    
    return 0;
}