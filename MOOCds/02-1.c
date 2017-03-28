/** passed
 * 02-线性结构1 一元多项式的乘法与加法运算   (20分)
 * 设计函数分别求两个一元多项式的乘积与和。
 * 
 * 输入格式:
 * 输入分2行，每行分别先给出多项式非零项的个数，再以指数递降方式输入一个多项式非零项系数和指
 * 数（绝对值均为不超过1000的整数）。数字间以空格分隔。
 * 
 * 输出格式:
 * 输出分2行，分别以指数递降方式输出乘积多项式以及和多项式非零项的系数和指数。数字间以空格分
 * 隔，但结尾不能有多余空格。零多项式应输出0 0。
 * 
 * 输入样例:
4 3 4 -5 2  6 1  -2 0
3 5 20 -7 4  3 1
 * 
 * 输出样例:
 * 15 24 -25 22 30 21 -10 20 -21 8 35 6 -33 5 14 4 -15 3 18 2 -6 1
 * 5 20 -4 4 -5 2 9 1 -2 0
 * 
 * 测试点
 * sample换个数字
 * 同类项合并时有抵消
 * 系数和指数取上限，结果有零多项式
 * 输入有零多项式和常数多项式
 */

#include <stdio.h>

#define POLYLEN 1001

void readpoly(int array[])
{
    int num;
    int base;
    int index;
    scanf("%d", &num);
    for(int i = 0; i < num; i++)
    {
        scanf("%d", &base);
        scanf("%d", &index);
        array[index] = base;
    }
}

void printpoly(int array[], int length)
{
    int count = 0; /* record the number of non-zero numbers */
    for(int i = length - 1; i >= 0; i--)
    {
        if(array[i] != 0)
        {
            if(count == 0)
            {
                printf("%d %d", array[i], i);
            }
            else
            {
                printf(" %d %d", array[i], i);
            }
            count++;
        }
    }
    if(count == 0) /* it is a zero polynominal */
    {
        printf("0 0");
    }
    printf("\n");
}

void addpoly(int a[], int b[], int c[])
{
    for(int i = 0; i < POLYLEN; i++)
    {
        c[i] = a[i] + b[i];
    }
}

void multipoly(int a[], int b[], int c[])
{
    for(int i = 0; i < POLYLEN; i++)
    {
        for(int j = 0; j < POLYLEN; j++)
        {
            c[i + j] += a[i] * b[j];
        }
    }
}

int main()
{
    int a[POLYLEN] = {0};
    int b[POLYLEN] = {0};
    int add[POLYLEN] = {0};
    int mul[POLYLEN * 2 - 1] = {0};
    
    readpoly(a);
    readpoly(b);
    
    addpoly(a, b, add);
    multipoly(a, b, mul);
    
    printpoly(mul, POLYLEN * 2 - 1);
    printpoly(add, POLYLEN);
    
    return 0;
}
