#include <stdio.h>

#define QLEN 15
#define CNODE 31

typedef struct node{
    int *post, *in, length;
}node;

typedef struct queue{
    node *nodes[QLEN];
    int front, rear, count;
}queue;

void enqueue(queue *q, node *n)
{
    q->nodes[q->rear] = n;
    q->rear = (q->rear == QLEN - 1) ? 0 : q->rear + 1;
    q->count++;
}

node *dequeue(queue *q)
{
    node *n = q->nodes[q->front];
    q->front = (q->front == QLEN - 1) ? 0 : q->front + 1;
    q->count--;
    return n;
}

int main()
{
    int post[CNODE] = {0}, in[CNODE] = {0}, N;
    queue q = {0};  /* Initialize to zeros or NULL array */
    int root, index, count;

    scanf("%d", &N);
    for(int i = 0; i < N; i++)
        scanf("%d", post + i);
    for(int i = 0; i < N; i++)
        scanf("%d", in + i);

    node nodes[CNODE] = {{post, in, N}}, *p = nodes, *n;
    enqueue(&q, p++);
    for(count = 0; q.count; count++)
    {
        n = dequeue(&q);
        /* Find root node in post-order, which is the last one */
        root = n->post[n->length - 1];
        /* Find the root node in in-order */
        for(index = 0; index < n->length; index++)
            if(n->in[index] == root)
                break;
        /* The subsequence post/in-order of left child */
        p->post = n->post;
        p->in = n->in;
        p->length = index;
        if(p->length != 0)              /* left child not NULL */
            enqueue(&q, p++);
        /* The subsequence post/in-order of right child */
        p->post = n->post + index;
        p->in = n->in + index + 1;
        p->length = n->length - index - 1;
        if(p->length != 0)              /* right child not NULL */
            enqueue(&q, p++);
        /* print */
        printf("%d%c", root, (count == N - 1) ? '\0' : ' ');
    }

    return 0;
}
