/**
 * 1016. 部分A+B (15)
 * 
 * 正整数A的“D_A（为1位整数）部分”定义为由A中所有D_A组成的新整数P_A。例如：给定
 * A = 3862767，D_A = 6，则A的“6部分”P_A是66，因为A中有2个6。
 * 
 * 现给定A、D_A、B、D_B，请编写程序计算P_A + P_B。
 * 
 * 输入格式：
 * 
 * 输入在一行中依次给出A、D_A、B、D_B，中间以空格分隔，其中0 < A, B < 10^10。
 * 
 * 输出格式：
 * 
 * 在一行中输出P_A + P_B的值。
 * 
 * 输入样例1：
 * 3862767 6 13530293 3
 * 输出样例1：
 * 399
 * 输入样例2：
 * 3862767 1 13530293 8
 * 输出样例2：
 * 0
 **/
#include <stdio.h>

/* To contain a number within 0-10^10, we need 64-bit integer */
typedef long int INT;

INT part(INT A, int D_A)
{
    INT P_A;
    for(P_A = 0; A; A /= 10)
        if(A % 10 == D_A)
            P_A = P_A * 10 + D_A;
    return P_A;
}

int main()
{
    INT A, B;
    int P_A, P_B;
    scanf("%ld %d %ld %d", &A, &P_A, &B, &P_B);
    printf("%ld", part(A, P_A) + part(B, P_B));
    
    return 0;
}
