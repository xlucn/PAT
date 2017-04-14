/**
 * 1002. 写出这个数
 * 读入一个自然数n，计算其各位数字之和，用汉语拼音写出和的每一位数字。
 * 
 * 输入格式：每个测试输入包含1个测试用例，即给出自然数n的值。这里保证n小于10^100。
 * 
 * 输出格式：在一行内输出n的各位数字之和的每一位，拼音数字间有1 空格，但一行中最后
 * 一个拼音数字后没有空格。
 * 
 * 输入样例：
 * 1234567890987654321123456789
 * 输出样例：
 * yi san wu
 **/
#include <stdio.h>
#include <string.h>
int main()
{
    char c;
    int sum = 0;
    while((c = getchar()) != '\n')  sum += c - '0';
    
    char *pinyins[] = {"ling", "yi", "er", "san", "si", "wu", "liu", "qi", "ba", "jiu"};
    
    if(sum / 100)                           /* hundreds */
        printf("%s ", pinyins[sum/100]);
    if(sum / 10)                            /* tens */
        printf("%s ", pinyins[sum/10%10]);
    printf("%s", pinyins[sum%10]);          /* unit */
    
    return 0;
}
