/**
 * 1054. 求平均值 (20)
 * 
 * 本题的基本要求非常简单：给定N个实数，计算它们的平均值。但复杂的是有些输入数据可能
 * 是非法的。一个“合法”的输入是[-1000，1000]区间内的实数，并且最多精确到小数点后2位。
 * 当你计算平均值的时候，不能把那些非法的数据算在内。
 * 
 * 输入格式：
 * 
 * 输入第一行给出正整数N（<=100）。随后一行给出N个实数，数字间以一个空格分隔。
 * 
 * 输出格式：
 * 
 * 对每个非法输入，在一行中输出“ERROR: X is not a legal number”，其中X是输入。最后
 * 在一行中输出结果：“The average of K numbers is Y”，其中K是合法输入的个数，Y是它
 * 们的平均值，精确到小数点后2位。如果平均值无法计算，则用“Undefined”替换Y。如果K为
 * 1，则输出“The average of 1 number is Y”。
 * 
 * 输入样例1：
 * 7
 * 5 -3.2 aaa 9999 2.3.4 7.123 2.35
 * 输出样例1：
 * ERROR: aaa is not a legal number
 * ERROR: 9999 is not a legal number
 * ERROR: 2.3.4 is not a legal number
 * ERROR: 7.123 is not a legal number
 * The average of 3 numbers is 1.38
 * 输入样例2：
 * 2
 * aaa -9999
 * 输出样例2：
 * ERROR: aaa is not a legal number
 * ERROR: -9999 is not a legal number
 * The average of 0 numbers is Undefined
 */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    int count = 0, N;
    double f, sum = 0;
    /* Maxium scenario: -1000.00. So just need to read 8 chars(+ '\0' = 9) */
    char s[9], *pEnd, *pDot, c;
    
    scanf("%d", &N);
    for(int i = 0; i < N; i++)
    {
        scanf("%8s", s);              /* Just read 8 chars */
        
        c = ungetc(getchar(), stdin); 
        f = strtod(s, &pEnd);
        pDot = strchr(s, '.');
        
        if(!isspace(c)                          /* string too long */
        || *pEnd                                /* not floating number */
        || (f > 1000 || f < -1000)              /* out of range */
        || (pDot && pDot - s < strlen(s) - 3))  /* precision too high */
        {
            printf("ERROR: %s", s);
            /* this can avoid overflow (we don't know how long input is) */
            while(!isspace(c = getchar())) putchar(c);
            printf(" is not a legal number\n");
        }
        else
        {   /* legel number */
            count++;
            sum += f;
        }
    }
    
    if(count == 0)  printf("The average of 0 numbers is Undefined\n");
    if(count == 1)  printf("The average of 1 number is %.2lf", sum);
    if(count >= 2)  printf("The average of %d numbers is %.2lf", count, sum / count);
    
    return 0;
}
