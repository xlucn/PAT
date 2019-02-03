#include <stdio.h>

#define MAX 1000

void DFS(int v, int known[], int G[][MAX])
{
    known[v] = 1;
    for(int i = 0; i < MAX; i++)
        if((G[v][i] || G[i][v]) && !known[i])
            DFS(i, known, G);
}

int main()
{
    int N, M, K;
    scanf("%d %d %d", &N, &M, &K);

    int Graph[MAX][MAX] = {{0}};

    int city1, city2;
    for(int i = 0; i < M; i++)
    {
        scanf("%d %d", &city1, &city2);
        Graph[city1][city2] = 1;
    }

    for(int i = 0; i < K; i++)
    {
        int known[MAX] = {0}, lostcity, count = 0;
        scanf("%d", &lostcity);

        known[lostcity] = 1;
        for(int i = 1; i <= N; i++) if(!known[i])
        {
            DFS(i, known, Graph);
            count++;
        }
        printf("%d\n", count - 1);
    }
}
