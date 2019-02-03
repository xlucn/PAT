#include <stdio.h>
#include <stdlib.h>

int comp(const void *a, const void *b)
{
    return *(int*)a - *(int*)b;
}

int main()
{
    int N, p, data[100000];
    int max = 0, first, last;

    scanf("%d %d", &N, &p);                                         /* read */
    for(int i = 0; i < N; i++)
        scanf("%d", data + i);

    qsort(data, N, sizeof(int), comp);                              /* sort */

    for(first = 0, last = 0; last < N && max < N - first; first++)  /* find */
    {
        while(last < N && data[last] <= 1L * data[first] * p)
            last++;
        if(max < last - first)
            max = last - first;
    }
    printf("%d", max);

    return 0;
}
