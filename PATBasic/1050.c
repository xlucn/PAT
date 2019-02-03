#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b)
{
    return *(int*)b - *(int*)a;
}

int main()
{
    int N, m, n;
    int array[10000] = {0}, matrix[10000] = {0};

    scanf("%d", &N);
    for(int i = 0; i < N; i++)
        scanf("%d", array + i);

    qsort(array, N, sizeof(int), cmp);

    /* determine m and n */
    for(m = 1; !(m * m >= N && N % m == 0); m++) ;
    n = N / m;

    int x = -1, y = 0, index = 0;
    int horizontal = n, virtical = m;

    while(horizontal > 0 && virtical > 0)
    {
        for(int i = 0; i < horizontal && virtical > 0; i++)  /* toward right */
            matrix[y * n + ++x] = array[index++];
        virtical--;

        for(int i = 0; i < virtical && horizontal > 0; i++)  /* toward bottom */
            matrix[++y * n + x] = array[index++];
        horizontal--;

        for(int i = 0; i < horizontal && virtical > 0; i++)  /* toward left */
            matrix[y * n + --x] = array[index++];
        virtical--;

        for(int i = 0; i < virtical && horizontal > 0; i++)  /* toward top */
            matrix[--y * n + x] = array[index++];
        horizontal--;
    }

    for(int i = 0; i < m; i++)
        for(int j = 0; j < n; j++)
            printf("%d%c", matrix[i * n + j], j == n - 1 ? '\n' : ' ');

    return 0;
}
