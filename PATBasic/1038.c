#include <stdio.h>

int main()
{
    int N, M, score, count[101] = {0};

    scanf("%d", &N);
    for(int i = 0; i < N; i++)
    {
        scanf("%d", &score);
        count[score]++;
    }

    scanf("%d", &M);
    for(int i = 0; i < M; i++)
    {
        scanf("%d", &score);
        printf("%d%c", count[score], i == M - 1 ? '\n' : ' ');
    }

    return 0;
}
