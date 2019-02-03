#include <stdio.h>

#define MAX 999

typedef struct Member *Member;
typedef struct Child *Child;

struct Member{
    int level;
    Child child;
};

struct Child{
    int ID;
    Child iter;
};

int main()
{
    int N, M, ID, cID, K;
    struct Member nodes[100];
    struct Child children[100];

    /* Read data and initiate a adjacent list */
    scanf("%d %d", &N, &M);
    for(int i = 1; i <= N; i++)
    {
        nodes[i].level = MAX;
        nodes[i].child = NULL;
    }
    nodes[1].level = 0;         /* root node at level 0 */
    for(int i = 0, k = 0; i < M; i++)
    {
        scanf("%d %d", &ID, &K);
        for(; K--; k++)
        {
            scanf("%d", &cID);
            children[k].ID = cID;
            children[k].iter = nodes[ID].child;
            nodes[ID].child = &children[k];
        }
    }

    /* For every level, find leaf nodes */
    int n = N, count;
    for(int level = 0; n; level++)
    {
        count = 0;
        for(int i = 1; i <= N; i++) if(nodes[i].level == level)
        {
            n--;
            if(nodes[i].child == NULL)
                count++;
            /* set the children to next level */
            for(Child c = nodes[i].child; c; c = c->iter)
                nodes[c->ID].level = level + 1;
        }

        printf("%d%c", count, n ? ' ' : '\0');
    }

    return 0;
}
