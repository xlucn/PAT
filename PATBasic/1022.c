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
#include <stdio.h>
int main()
{
    long int A, B, D, Sum;
    scanf("%ld %ld %ld", &A, &B, &D);
    Sum = A + B;
    
    if(Sum == 0) {
        printf("0");
        return 0;
    }
    
    /* calculate the bits of Sum. E.g. If Sum is 4 bits in D-base, power will be 10000 in D-base */
    long int power = 1;
    while(Sum >= power) power *= D;
    
    /* calculate D-base number. print them on-the-fly */
    for(power /= D; power > 0; power /= D){
        printf("%ld", Sum / power);
        Sum %= power;
    }
    
    return 0;
}
