#include <stdio.h>

int main()
{
    int M, N, K, L, mask;

    scanf("%d", &M);
    for(int i = 0; i < M; i++)
    {
        scanf("%d", &K);
        for(N = 1; N < 10; N++)
        {
            L = N * K * K;

            /* compare the lowest digits one by one */
            for(mask = 1; mask <= K; mask *= 10)
                if(L / mask % 10 != K / mask % 10)
                    break;

            if(mask > K)  /* all passed! */
            {
                printf("%d %d\n", N, L);
                break;
            }
        }
        if(N == 10)  /* No results */
            printf("No\n");
    }

    return 0;
}
