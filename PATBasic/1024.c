/**
 * 1024. 科学计数法 (20)
 * 
 * 科学计数法是科学家用来表示很大或很小的数字的一种方便的方法，其满足正则表达式
 * [+-][1-9]"."[0-9]+E[+-][0-9]+，即数字的整数部分只有1位，小数部分至少有1位，
 * 该数字及其指数部分的正负号即使对正数也必定明确给出。
 * 
 * 现以科学计数法的格式给出实数A，请编写程序按普通数字表示法输出A，并保证所有有效位
 * 都被保留。
 * 
 * 输入格式：
 * 
 * 每个输入包含1个测试用例，即一个以科学计数法表示的实数A。该数字的存储长度不超过
 * 9999字节，且其指数的绝对值不超过9999。
 * 
 * 输出格式：
 * 
 * 对每个测试用例，在一行中按普通数字表示法输出A，并保证所有有效位都被保留，
 * 包括末尾的0。
 * 
 * 输入样例1：
 * +1.23400E-03
 * 输出样例1：
 * 0.00123400
 * 输入样例2：
 * -1.2E+10
 * 输出样例2：
 * -12000000000
 */

#include <stdio.h>

int main()
{
    int exponent;    /* the exponent part */
    char line[10000], *p = line;
    scanf("%[^E]E%d", line, &exponent);

    if(*p++ == '-') putchar('-');       /* no print if it's '+' */
    if(exponent >= 0)           /* print '.' later or add zeros in the end */
    {
        putchar(*p);
        for(p += 2; exponent; exponent--)    /* print the integer part */
            putchar(*p ? *p++ : '0');
        if(*p)                               /* there is still fraction part */
        {
            putchar('.');
            while(*p) putchar(*p++);
        }
    }
    if(exponent < 0)            /* add exponent zeros in the beginning */
    {
        printf("0.");
        for(exponent++; exponent; exponent++)       /* add zeros */
            putchar('0');
        for(; *p; p++) if(*p != '.') putchar(*p);   /* the rest */
    }
    
    return 0;
}
