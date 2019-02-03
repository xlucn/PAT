#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b)
{
    return *(int*)b - *(int*)a;
}

int main()
{
    int N, E, miles[100000];

    scanf("%d", &N);
    for(int i = 0; i < N; i++)
        scanf("%d", miles + i);

    qsort(miles, N, sizeof(int), cmp);

    for(E = 0; E < N && miles[E] > E + 1; E++) ;
    printf("%d", E);

    return 0;
}
