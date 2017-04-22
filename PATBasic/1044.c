/**
 * 1044. 火星数字(20)
 * 
 * 火星人是以13进制计数的：
 * 
 * 地球人的0被火星人称为tret。
 * 地球人数字1到12的火星文分别为：jan, feb, mar, apr, may, jun, jly, aug, sep, 
 * oct, nov, dec。
 * 火星人将进位以后的12个高位数字分别称为：tam, hel, maa, huh, tou, kes, hei, elo, 
 * syy, lok, mer, jou。
 * 
 * 例如地球人的数字“29”翻译成火星文就是“hel mar”；而火星文“elo nov”对应地球数字
 * “115”。为了方便交流，请你编写程序实现地球和火星数字之间的互译。
 * 
 * 输入格式：
 * 
 * 输入第一行给出一个正整数N（<100），随后N行，每行给出一个[0, 169)区间内的数字 —— 
 * 或者是地球文，或者是火星文。
 * 
 * 输出格式：
 * 
 * 对应输入的每一行，在一行中输出翻译后的另一种语言的数字。
 * 
 * 输入样例：
 * 4
 * 29
 * 5
 * elo nov
 * tam
 * 输出样例：
 * hel mar
 * may
 * 115
 * 13
 */
#include <ctype.h>
#include <stdio.h>
#include <string.h>

char *units[] = {"tret", "jan", "feb", "mar", "apr", "may", "jun", "jly", 
    "aug", "sep", "oct", "nov", "dec"};
char *tens[] = {"tam", "hel", "maa", "huh", "tou", "kes", "hei", "elo", 
    "syy", "lok", "mer", "jou"};

int Mars2Earth(char *s)
{
    if(s)
    {
        for(int i = 0; i < 13; i++)         /* units digits */
            if(strcmp(s, units[i]) == 0)
                return i;
        for(int i = 1; i < 13; i++)         /* tens digits */
            if(strcmp(s, tens[i - 1]) == 0)
                return i * 13;
    }
    return 0;
}

int main()
{
    int N, m;
    char line[11];
    
    fgets(line, 11, stdin);
    sscanf(line, "%d", &N);
    for(int i = 0; i < N; i++)
    {
        fgets(line, 11, stdin);
        if(isdigit(line[0]))                  /* Earth line */
        {
            sscanf(line, "%d", &m);
            if(m / 13 && m % 13)
                printf("%s %s\n", tens[m / 13 - 1], units[m % 13]);
            if(m / 13 && m % 13 == 0)
                printf("%s\n", tens[m / 13 - 1]);
            if(m / 13 == 0)
                printf("%s\n", units[m % 13]);
        }
        if(isalpha(line[0]))                  /* Mars line */
        {
            m = Mars2Earth(strtok(line, " \n"));      /* higher digit */
            m += Mars2Earth(strtok(NULL, " \n"));       /* lower digit */
            printf("%d\n", m);
        }
    }
    
    return 0;
}
