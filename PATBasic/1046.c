#include <stdio.h>

int main()
{
    int N, A1, A2, B1, B2;
    int A = 0, B = 0;

    scanf("%d", &N);
    for(int i = 0; i < N; i++)
    {
        scanf("%d %d %d %d", &A1, &A2, &B1, &B2);
        if(A2 == A1 + B1 && B2 != A1 + B1)   B++;
        if(A2 != A1 + B1 && B2 == A1 + B1)   A++;
    }
    printf("%d %d", A, B);

    return 0;
}
