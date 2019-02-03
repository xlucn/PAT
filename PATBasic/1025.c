#include <stdio.h>
#include <stdlib.h>

#define SWAPNODE(A, B) {Node temp = A; A = B; B = temp;}

typedef struct node{
    int addr;
    int data;
    int next;
}node, *Node;

int main()
{
    int A, N, K;
    node nodes[100000] = {0};
    Node np[100000] = {0}, *p;

    /* read */
    scanf("%d %d %d", &A, &N, &K);
    for(int i = 0; i < N; i++)
    {
        np[i] = nodes + i;
        scanf("%d %d %d", &np[i]->addr, &np[i]->data, &np[i]->next);
    }

    /* link the list */
    for(int i = 0; i < N; i++)
    {
        for(int j = i; j < N; j++)
            if(np[j]->addr == (i ? np[i - 1]->next : A))
            {
                SWAPNODE(np[i], np[j]);
                break;
            }
        if(np[i]->next == -1)   /* there could be useless nodes */
            N = i + 1;
    }

    /* reverse the list */
    for(int i = 0; i < N / K; i++)
    {
        p = np + i * K;
        for(int j = 0; j < K / 2; j++)
            SWAPNODE(p[j], p[K - j - 1]);
    }

    /* print the list */
    for(int i = 0; i < N - 1; i++)
        printf("%05d %d %05d\n", np[i]->addr, np[i]->data, np[i + 1]->addr);
    printf("%05d %d -1\n", np[N - 1]->addr, np[N - 1]->data);

    return 0;
}
