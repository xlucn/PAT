#include <stdio.h>

typedef struct node{
    int visited, level, depth;
    struct adj *adj;
} node;

typedef struct adj{
    struct node *node;
    struct adj *next;
} adj;

void DFS(node *n, int level)
{
    n->visited = 1;
    n->level = level + 1;

    for(adj *a = n->adj; a; a = a->next)
        if(a->node->visited == 0)
            DFS(a->node, level + 1);
}

int main()
{
    int N, n1, n2, count, depth, maxdepth = 0;
    node nodes[10000] = {0}, *pnode;
    adj edges[20000] = {0}, *padj;

    /* Read and build the adjacent linked list */
    scanf("%d", &N);
    for(int i = 0; i < N - 1; i++)
    {
        scanf("%d %d", &n1, &n2);
        /* n1 to n2 */
        pnode = &nodes[n1 - 1];
        padj = &edges[i * 2];
        padj->node = &nodes[n2 - 1];
        padj->next = pnode->adj;
        pnode->adj = padj;
        /* n2 to n1 */
        pnode = &nodes[n2 - 1];
        padj = &edges[i * 2 + 1];
        padj->node = &nodes[n1 - 1];
        padj->next = pnode->adj;
        pnode->adj = padj;
    }

    for(int i = 0; i < N; i++)
    {
        /* Reset the whole graph */
        depth = 0;
        count = 1;
        for(int i = 0; i < N; i++)
            nodes[i].visited = nodes[i].level = 0;

        /* Start from the ith node */
        DFS(nodes + i, 0);

        /* Get the depth of the tree */
        for(int i = 0; i < N; i++)
            if(nodes[i].visited == 1)
                if(nodes[i].level > depth)
                    depth = nodes[i].level;

        /* Try to find other disjoint components */
        for(int i = 0; i < N; i++)
            if(nodes[i].visited == 0)
            {
                DFS(nodes + i, 0);
                count ++;
            }

        if(count != 1)  /* If not all the nodes are visited */
        {
            printf("Error: %d components", count);
            return 0;  /* Only have to do it once */
        }
        else            /* It is one tree */
        {
            nodes[i].depth = depth;
            if(maxdepth < depth)
                maxdepth = depth;
        }
    }

    /* Find the root with the same maximum depth */
    for(int i = 0; i < N; i++)
        if(nodes[i].depth == maxdepth)
            printf("%d\n", i + 1);

    return 0;
}
