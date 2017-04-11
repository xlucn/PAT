/**
 * 1034. 有理数四则运算(20)
 * 
 * 本题要求编写程序，计算2个有理数的和、差、积、商。
 * 
 * 输入格式：
 * 
 * 输入在一行中按照“a1/b1 a2/b2”的格式给出两个分数形式的有理数，其中分子和分母全是
 * 整型范围内的整数，负号只可能出现在分子前，分母不为0。
 * 
 * 输出格式：
 * 
 * 分别在4行中按照“有理数1 运算符 有理数2 = 结果”的格式顺序输出2个有理数的和、差、
 * 积、商。注意输出的每个有理数必须是该有理数的最简形式“k a/b”，其中k是整数部分，
 * a/b是最简分数部分；若为负数，则须加括号；若除法分母为0，则输出“Inf”。题目保证正
 * 确的输出中没有超过整型范围的整数。
 * 
 * 输入样例1：
 * 2/3 -4/2
 * 输出样例1：
 * 2/3 + (-2) = (-1 1/3)
 * 2/3 - (-2) = 2 2/3
 * 2/3 * (-2) = (-1 1/3)
 * 2/3 / (-2) = (-1/3)
 * 输入样例2：
 * 5/3 0/6
 * 输出样例2：
 * 1 2/3 + 0 = 1 2/3
 * 1 2/3 - 0 = 1 2/3
 * 1 2/3 * 0 = 0
 * 1 2/3 / 0 = Inf
 */
#include <stdio.h>

/* take all positive values as params */
long calcgcd(long a, long b)
{
    long r;
    while((r = a % b))
    {
        a = b;
        b = r;
    }
    return b;
}

void printfrac(long n, long d)  /* numerator and dominator */
{
    if(d == 0) { printf("Inf"); return; }
    
    /* record the sign and make them positive */
    /* can not use d * n < 0 to determine the sign if using long type */
    long inegative = (d < 0 && n >= 0) || (d > 0 && n < 0) ? 1 : 0; 
    n = n < 0 ? -n : n;
    d = d < 0 ? -d : d;
    
    /* reduce the fraction */
    long gcd = calcgcd(n, d);           
    n /= gcd;
    d /= gcd;
    
    /* print */
    if(inegative)           printf("(-");
    if(n / d && n % d)      printf("%ld %ld/%ld", n / d, n % d, d); /* proper fractions */
    else if(n % d)          printf("%ld/%ld", n % d, d);            /* improper fractions */
    else                    printf("%ld", n / d);                   /* integers */
    if(inegative)           printf(")");
}

int main()
{
    long a1, b1, a2, b2;
    scanf("%ld/%ld %ld/%ld", &a1, &b1, &a2, &b2);
    
    char op[4] = {'+', '-', '*', '/'};
    for(int i = 0; i < 4; i++)
    {
        printfrac(a1, b1);        printf(" %c ", op[i]);
        printfrac(a2, b2);        printf(" = ");
        switch(op[i])
        {
            case '+': printfrac(a1 * b2 + a2 * b1, b1 * b2); break;
            case '-': printfrac(a1 * b2 - a2 * b1, b1 * b2); break;
            case '*': printfrac(a1 * a2,           b1 * b2); break;
            case '/': printfrac(a1 * b2,           b1 * a2); break;
        }
        printf("\n");
    }
    
    return 0;
}
