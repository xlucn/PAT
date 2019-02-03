#include <stdio.h>

int main()
{
    int N, D, K;
    int empty = 0, pempty = 0, lower;
    float e, E;

    scanf("%d %f %d", &N, &e, &D);
    for(int i = 0; i < N; i++)
    {
        lower = 0;
        scanf("%d", &K);
        for(int j = 0; j < K; j++)
        {
            scanf("%f", &E);
            if(E < e)   lower++;
        }
        if(lower > K / 2 && K > D)  empty++;
        else if(lower > K / 2)      pempty++;
    }
    printf("%.1f%% %.1f%%", 100.0 * pempty / N, 100.0 * empty / N);

    return 0;
}
