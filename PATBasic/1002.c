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
    int sum = 0;
    char c;
    while((c = getchar()) != EOF)
    {
        if(c >= '0' && c <= '9')
        {
            sum += c - '0';
        }
        if(c == '\n')
        {
            break;
        }
    }
    
    char pinyin[13] = {'\0'};
    char new[5], *pnew = new;
    char *pinyins[] = {"ling", "yi", "er", "san", "si", "wu", "liu", "qi", "ba", "jiu"};
    while(sum > 0)
    {
        strcpy(pnew, pinyins[sum % 10]);
        if(pinyin[0] != '\0')
        {
            pnew = strcat(pnew, " ");
        }
        strcpy(pinyin, strcat(pnew, pinyin));
        sum /= 10;
    } 
    puts(pinyin);
    
    return 0;
}
