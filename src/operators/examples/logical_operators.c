/*
 * 論理演算子のデモ
 * AND, OR, NOT演算子の使用方法
 */
#include <stdio.h>

int main(void)
{
    int age = 25;
    int income = 300000;
    int has_license = 1;
    
    printf("=== 論理演算子 ===\n");
    printf("年齢: %d, 収入: %d, 免許: %d\n\n", age, income, has_license);
    
    /* AND演算子 */
    printf("AND演算子 (&&):\n");
    printf("年齢20以上 AND 収入200000以上: %d\n", 
           (age >= 20) && (income >= 200000));
    
    /* OR演算子 */
    printf("\nOR演算子 (||):\n");
    printf("年齢18未満 OR 年齢65以上: %d\n", 
           (age < 18) || (age >= 65));
    
    /* NOT演算子 */
    printf("\nNOT演算子 (!):\n");
    printf("免許を持っていない: %d\n", !has_license);
    
    return 0;
}