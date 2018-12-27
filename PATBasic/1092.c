#include <stdio.h>

int main()
{
    int N, M, cur, max = 0, sales[1000] = {0};

    scanf("%d %d", &N, &M);
    for(int i = 0; i < M; i++)
    {
        for(int j = 0; j < N; j++)
        {
            scanf("%d", &cur);
            sales[j] += cur;
        }
    }

    /* find the max */
    for(int i = 0; i < N; i++)
        if(max < sales[i])
            max = sales[i];

    /* print all the indexes of max sales */
    printf("%d", max);
    for(int i = 0, count = 0; i < N; i++)
        if(sales[i] == max)
            printf("%c%d", count++ ? ' ' : '\n', i + 1);

    return 0;
}
