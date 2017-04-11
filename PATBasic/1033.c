/**
 * 1033. 旧键盘打字(20)
 * 
 * 旧键盘上坏了几个键，于是在敲一段文字的时候，对应的字符就不会出现。现在给出应该
 * 输入的一段文字、以及坏掉的那些键，打出的结果文字会是怎样？
 * 
 * 输入格式：
 * 
 * 输入在2行中分别给出坏掉的那些键、以及应该输入的文字。其中对应英文字母的坏键以大写
 * 给出；每段文字是不超过105个字符的串。可用的字符包括字母[a-z, A-Z]、数字0-9、以及
 * 下划线“_”（代表空格）、“,”、“.”、“-”、“+”（代表上档键）。题目保证第2行输入的文字
 * 串非空。
 * 
 * 注意：如果上档键坏掉了，那么大写的英文字母无法被打出。
 * 
 * 输出格式：
 * 
 * 在一行中输出能够被打出的结果文字。如果没有一个字符能被打出，则输出空行。
 * 
 * 输入样例：
 * 7+IE.
 * 7_This_is_a_test.
 * 输出样例：
 * _hs_s_a_tst
 */
#include <stdio.h>
#include <ctype.h>
int main()
{
    char c;
    int bad[41] = {0}; /* record keys: (A-Z 0-9 _ , . - +) are broken or not */
    
    /* read broken keys */
    while((c = getchar()) != '\n')
    {
        if(isalpha(c))          bad[toupper(c) - 'A'] = 1;  /* alphabets */
        else if(isdigit(c))     bad[c - '0' + 26] = 1;      /* digits */
        else if(c == '_')       bad[36] = 1;                /* blank space */
        else if(c == ',')       bad[37] = 1;                /* comma */
        else if(c == '.')       bad[38] = 1;                /* period */
        else if(c == '-')       bad[39] = 1;                /* hyphen */
        else if(c == '+')       bad[40] = 1;                /* shift */
    }
    
    /* read string and print */
    while((c = getchar()) != '\n')
    {
        if((isalpha(c) && !bad[toupper(c) - 'A'] && !(isupper(c) && bad[40]))
        || (isdigit(c) && !bad[c - '0' + 26])
        || (c == '_' && !bad[36])
        || (c == ',' && !bad[37])
        || (c == '.' && !bad[38])
        || (c == '-' && !bad[39]))      putchar(c);
    }
    
    return 0;
}
