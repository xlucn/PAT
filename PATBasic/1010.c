/**
 * 1010. 一元多项式求导
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
 * 输出样例：
 * 12 3 -10 1 6 0
 **/
#include <stdio.h>
int main()
{
    int coef;
    int index;
    int count = 0;
    
    char c;
    while((c = getchar()) != '\n')
    {
        /* not the end of input */
        ungetc(c, stdin);
        scanf("%d %d", &coef, &index);
        count++;
        /* zero polynomial or constant, the result is zero polynomial */
        if(count == 1 && (coef == 0 || index == 0))
        {
            puts("0 0");
            break;
        }
        
        /* constant terms results in zero term, so no output */
        if(index != 0)
        {
            if(count > 1)
            {
                putc(' ', stdout);
            }
            printf("%d %d", coef * index, index - 1);
        }
    }
    
    return 0;
}
