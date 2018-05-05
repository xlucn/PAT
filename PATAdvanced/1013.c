/**
 * 1013. Battle Over Cities (25)
 * 
 * It is vitally important to have all the cities connected by highways in a 
 * war. If a city is occupied by the enemy, all the highways from/toward that 
 * city are closed. We must know immediately if we need to repair any other 
 * highways to keep the rest of the cities connected. Given the map of cities 
 * which have all the remaining highways marked, you are supposed to tell the 
 * number of highways need to be repaired, quickly.
 * 
 * For example, if we have 3 cities and 2 highways connecting city1-city2 and 
 * city1-city3. Then if city1 is occupied by the enemy, we must have 1 highway 
 * repaired, that is the highway city2-city3.
 * 
 * Input
 * 
 * Each input file contains one test case. Each case starts with a line 
 * containing 3 numbers N (<1000), M and K, which are the total number of 
 * cities, the number of remaining highways, and the number of cities to be 
 * checked, respectively. Then M lines follow, each describes a highway by 2 
 * integers, which are the numbers of the cities the highway connects. The 
 * cities are numbered from 1 to N. Finally there is a line containing K 
 * numbers, which represent the cities we concern.
 * 
 * Output
 * 
 * For each of the K cities, output in a line the number of highways need to be 
 * repaired if that city is lost.
 * 
 * Sample Input
 * 3 2 3
 * 1 2
 * 1 3
 * 1 2 3
 * Sample Output
 * 1
 * 0
 * 0
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Edge{
    int id;
    struct Edge *iter;
} *Edge;

typedef struct Vertex{
    int known;
    Edge adj;
} *Vertex;

typedef struct Graph{
    int nvertex;
    int nedge;
    Vertex vs;
    Edge es;
} *Graph;

Graph ReadGraph(int nvertex, int nedge)
{
    /* create new graph */
    Graph G = (Graph)malloc(sizeof(struct Graph));
    G->nvertex = nvertex;
    G->nedge = nedge;
    G->vs = (Vertex)malloc(nvertex * sizeof(struct Vertex));
    G->es = (Edge)malloc(nedge * sizeof(struct Edge));
    for(int i = 0; i < G->nvertex; i++)
        G->vs[i].adj = NULL;
    /* read */
    int start, end;
    for(int i = 0; i < G->nedge; i++)
    {
        scanf("%d %d", &start, &end);
        start--, end--;
        if(start > end) {int temp = start; start = end; end = temp;}
        G->es[i].id = end;
        G->es[i].iter = G->vs[start].adj;
        G->vs[start].adj = &G->es[i];
    }
    return G;
}

typedef struct Queue{
    int front;
    int rear;
    Vertex list[1000];
} *Queue;

void Traversal(Graph G, Vertex start)
{
    Queue Q = (Queue)malloc(sizeof(struct Queue));
    Q->rear = Q->front = 0;
    Q->list[++Q->front] = start;
    start->known = 1;
    
    while(Q->front != Q->rear)
    {
        Q->rear = Q->rear == 999 ? 0 : Q->rear + 1;
        Vertex v = Q->list[Q->rear];
        for(Edge e = v->adj; e; e = e->iter) if(!G->vs[e->id].known)
        {
            Q->front = Q->front == 999 ? 0 : Q->front + 1;
            Q->list[Q->front] = &G->vs[e->id];
            G->vs[e->id].known = 1;
        }
    }
    free(Q);
}

int main()
{
    int N, M, K, lostcity, count;
    scanf("%d %d %d", &N, &M, &K);
    Graph G = ReadGraph(N, M);
    for(int i = 0; i < K; i++)
    {
        scanf("%d", &lostcity);
        /* Reset the graph */
        lostcity--, count = 0;
        for(int i = 0; i < G->nvertex; i++)
            G->vs[i].known = 0;
        /* Traversal */
        G->vs[lostcity].known = 1;
        for(int i = 0; i < G->nvertex; i++) if(!G->vs[i].known)
        {
            Traversal(G, &G->vs[i]);
            count++;
        }
        printf("%d\n", count - 1);
    }
}
