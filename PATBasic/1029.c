/**
 * 1029. 旧键盘(20)
 * 
 * 旧键盘上坏了几个键，于是在敲一段文字的时候，对应的字符就不会出现。现在给出应该
 * 输入的一段文字、以及实际被输入的文字，请你列出肯定坏掉的那些键。
 * 
 * 输入格式：
 * 
 * 输入在2行中分别给出应该输入的文字、以及实际被输入的文字。每段文字是不超过80个字符
 * 的串，由字母A-Z（包括大、小写）、数字0-9、以及下划线“_”（代表空格）组成。题目保证
 * 2个字符串均非空。
 * 
 * 输出格式：
 * 
 * 按照发现顺序，在一行中输出坏掉的键。其中英文字母只输出大写，每个坏键只输出一次。
 * 题目保证至少有1个坏键。
 * 
 * 输入样例：
 * 7_This_is_a_test
 * _hs_s_a_es
 * 输出样例：
 * 7TI
 */
#include <ctype.h>
#include <stdio.h>
#include <string.h>
int main()
{
    int index, bad[37] = {0};
    char c, complete[82], partial[82];
    
    scanf("%s %s", complete, partial);
    for(char *p = complete; *p; p++) 
    {
        c = toupper(*p);
        index = isdigit(c) ? c - '0' : isalpha(c) ? c - 'A' + 10 : 36;
        if( !strchr(partial, c) && !strchr(partial, tolower(c)) && !bad[index])
        {
            putchar(c);
            bad[index] = 1;
        }
    }
    return 0;
}
