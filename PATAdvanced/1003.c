/**
 * 1003. Emergency (25)
 * 
 * As an emergency rescue team leader of a city, you are given a special map of 
 * your country. The map shows several scattered cities connected by some roads.
 * Amount of rescue teams in each city and the length of each road between any 
 * pair of cities are marked on the map. When there is an emergency call to you 
 * from some other city, your job is to lead your men to the place as quickly as
 * possible, and at the mean time, call up as many hands on the way as possible.
 * 
 * Input
 * 
 * Each input file contains one test case. For each test case, the first line 
 * contains 4 positive integers: N (<= 500) - the number of cities (and the 
 * cities are numbered from 0 to N-1), M - the number of roads, C1 and C2 - the 
 * cities that you are currently in and that you must save, respectively. The 
 * next line contains N integers, where the i-th integer is the number of rescue
 * teams in the i-th city. Then M lines follow, each describes a road with three
 * integers c1, c2 and L, which are the pair of cities connected by a road and 
 * the length of that road, respectively. It is guaranteed that there exists at 
 * least one path from C1 to C2.
 * 
 * Output
 * 
 * For each test case, print in one line two numbers: the number of different 
 * shortest paths between C1 and C2, and the maximum amount of rescue teams you 
 * can possibly gather.
 * All the numbers in a line must be separated by exactly one space, and there 
 * is no extra space allowed at the end of a line.
 * 
 * Sample Input
 * 5 6 0 2
 * 1 2 1 5 3
 * 0 1 1
 * 0 2 2
 * 0 3 1
 * 1 2 1
 * 2 4 1
 * 3 4 1
 * Sample Output
 * 2 4
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define Inf INT_MAX

typedef struct Vertex *Vertex, *Vertexes;
typedef struct Adj *Adj, *Adjs;
typedef struct Graph *Graph;

struct Vertex{
    int id;         /* Unique id of a vertex */
    int known;      /* If the vertex has been traversed */
    int dist;       /* the distance along the path from start point */
    int nrescue;    /* Rescue teams in this city */
    int totrescue;  /* Total rescue teams along the path */
    int npath;      /* Length of the path */
    Adj adj;        /* Pointer to the next vertex */
};

struct Adj{
    int id;         /* The city's id it is connected to */
    int length;     /* The length of the edge */
    Adj iter;       /* Pointer to the next adjacent city */
};

struct Graph{
    Vertexes vs;
    Adjs es;
    int nvertex;
    int nadj;
};

/* Read the graph */
void Read(Graph G)
{
    int nrescue;
    for(int i = 0; i < G->nvertex; i++)
    {
        Vertex v = G->vs + i;
        scanf("%d", &nrescue);
        v->id        = i;
        v->known     = 0;
        v->dist      = Inf;
        v->nrescue   = nrescue;
        v->totrescue = nrescue;
        v->npath     = 0;
        v->adj       = NULL;
    }
    
    int id1, id2, length;
    for(int i = 0; i < G->nadj; i++)
    {
        scanf("%d %d %d", &id1, &id2, &length);
        /* From id1 to id2 */
        Adj e = G->es + i;
        e->id        = id2;
        e->length    = length;
        e->iter      = G->vs[id1].adj;
        G->vs[id1].adj = e;
        e->length    = length;
        e->iter      = G->vs[i].adj;
        G->vs[i].adj = e;
    }
}

/* Find the shortest path length using Dijkstra alg, 
 * in the same time record the number of shortest paths and max rescue teams */
void ModifiedDijkstra(Graph G)
{
    int minUnknownDist;
    Vertex v, w;
    while(1)
    {
        /* find the smallest unknown distance vertex */
        v = NULL;
        minUnknownDist = Inf;
        for(w = G->vs; w < &G->vs[G->nvertex]; w++)
            if(!w->known && w->dist < minUnknownDist)
            {
                minUnknownDist = w->dist;
                v = w;
            }
        if(v == NULL) break;
        
        v->known = 1;
        for(Adj e = v->adj; e; e = e->iter) if(!G->vs[e->id].known)
        {
            w = G->vs + e->id; /* w is every adjacent vertex to v */
            /* find shorter distance */
            if(v->dist + e->length < w->dist)
            {
                w->npath = v->npath;
                w->totrescue = w->nrescue + v->totrescue;
                w->dist = v->dist + e->length;
            }
            /* find same shortest distance */
            else if(v->dist + e->length == w->dist)
            {
                w->npath += v->npath;
                if(w->totrescue < w->nrescue + v->totrescue)
                    w->totrescue = w->nrescue + v->totrescue;
            }
        }
    }
}

int main()
{
    int N, M, C1, C2;
    scanf("%d %d %d %d", &N, &M, &C1, &C2);
    
    /* Create graph */
    Vertexes vs = (Vertexes)malloc(N * sizeof(struct Vertex));
    Adjs es = (Adjs)malloc(M * 2 * sizeof(struct Adj));
    struct Graph sG = {.vs = vs, .es = es, .nvertex = N, .nadj = M * 2};
    Graph G = &sG;
    
    /* Read all the data and build the graph */
    Read(G);
    G->vs[C1].dist = 0;
    G->vs[C1].npath = 1;
    
    /* Find the shortest path and maximum rescue teams */
    ModifiedDijkstra(G);
    
    printf("%d %d", G->vs[C2].npath, G->vs[C2].totrescue);
    
    return 0;
}
