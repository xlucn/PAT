#include <stdio.h>

int main()
{
    int N, M, A, B, C, D;

    scanf("%d %d %d %d %d", &M, &N, &A, &B, &C);

    for(int i = 0; i < M; i++)
        for(int j = 0; j < N; j++)
        {
            scanf("%d", &D);
            if(A <= D && D <= B)    D = C;
            printf("%03d%c", D, j == N - 1 ? '\n' : ' ');
        }

    return 0;
}
