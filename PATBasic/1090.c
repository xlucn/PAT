#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b)
{
    return *(int*)a - *(int*)b;
}

int main()
{
    int N, M, K, status;
    int itemlist[1000], pairlist[10000][2] = {{0}};

    /* Record incompatible list */
    scanf("%d %d", &N, &M);
    for(int i = 0; i < N; i ++)
        scanf("%d %d", &pairlist[i][0], &pairlist[i][1]);

    for(int i = 0; i < M; i++)
    {
        status = 1;
        scanf("%d", &K);
        for(int j = 0; j < K && status; j++)
            scanf("%d", itemlist + j);

        qsort(itemlist, K, sizeof(int), cmp);

        for(int j = 0; j < N; j++)
        {
            if(bsearch(&pairlist[j][0], itemlist, K, sizeof(int), cmp)
            && bsearch(&pairlist[j][1], itemlist, K, sizeof(int), cmp))
            {
                puts("No");
                status = 0;
                break;
            }
        }

        if(status)
            puts("Yes");
    }

    return 0;
}
