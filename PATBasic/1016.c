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

long Dpart(long A, int D_A)
{
    long P_A;
    for(P_A = 0; A; A /= 10)
        if(A % 10 == D_A)
            P_A = P_A * 10 + D_A;
    return P_A;
}

int main()
{
    long A, B;
    int D_A, D_B;
    scanf("%ld %d %ld %d", &A, &D_A, &B, &D_B);
    printf("%ld", Dpart(A, D_A) + Dpart(B, D_B));
    
    return 0;
}
