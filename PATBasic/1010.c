/**
 * 1010. 一元多项式求导
 * 
 * 设计函数求一元多项式的导数。（注：x^n（n为整数）的一阶导数为n*x^n-1。）
 * 
 * 输入格式：以指数递降方式输入多项式非零项系数和指数（绝对值均为不超过1000的整数）。
 * 数字间以空格分隔。
 * 
 * 输出格式：以与输入相同的格式输出导数多项式非零项的系数和指数。数字间以空格分隔，但
 * 结尾不能有多余空格。注意“零多项式”的指数和系数都是0，但是表示为“0 0”。
 * 
 * 输入样例：
 * 3 4 -5 2 6 1 -2 0
 * 
 * 输出样例：
 * 12 3 -10 1 6 0
 **/

#include <stdio.h>

int main()
{
    int coef, index, count = 0;

    while(scanf("%d %d", &coef, &index) != EOF) 
        if(index) /* Constant terms result in zero */
        {
            if(count++) putchar(' ');
            printf("%d %d", coef * index, index - 1);
        }

    /* Zero polynomial or constant */
    if(count == 0) 
        puts("0 0");
    
    return 0;
}
