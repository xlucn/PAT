/**
 * 1022. D进制的A+B (20)
 * 
 * 输入两个非负10进制整数A和B(<=2^30-1)，输出A+B的D (1 < D <= 10)进制数。
 * 
 * 输入格式：
 * 
 * 输入在一行中依次给出3个整数A、B和D。
 * 
 * 输出格式：
 * 
 * 输出A+B的D进制数。
 * 
 * 输入样例：
 * 123 456 8
 * 输出样例：
 * 1103
 */
/*
 * use Sum / D >= power to avoid using long int 
 */
#include <stdio.h>
int main()
{
    int A, B, D, Sum;
    scanf("%d %d %d", &A, &B, &D);
    Sum = A + B;
    
    /* calculate the bits of Sum */
    int power = 1;
    while(Sum / D >= power) power *= D;
    
    /* calculate D-base number. print them on-the-fly */
    for(; power > 0; Sum %= power, power /= D)
        printf("%d", Sum / power);
    
    return 0;
}
