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
