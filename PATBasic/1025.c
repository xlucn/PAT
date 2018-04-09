/**
 * 1025. 反转链表 (25)
 * 
 * 给定一个常数K以及一个单链表L，请编写程序将L中每K个结点反转。例如：给定L为
 * 1→2→3→4→5→6，K为3，则输出应该为3→2→1→6→5→4；如果K为4，则输出应该为
 * 4→3→2→1→5→6，即最后不到K个元素不反转。
 * 
 * 输入格式：
 * 
 * 每个输入包含1个测试用例。每个测试用例第1行给出第1个结点的地址、结点总个数
 * 正整数N(<= 105)、以及正整数K(<=N)，即要求反转的子链结点的个数。结点的地址是
 * 5位非负整数，NULL地址用-1表示。
 * 
 * 接下来有N行，每行格式为：
 * Address Data Next
 * 
 * 其中Address是结点地址，Data是该结点保存的整数数据，Next是下一结点的地址。
 * 
 * 输出格式：
 * 
 * 对每个测试用例，顺序输出反转后的链表，其上每个结点占一行，格式与输入相同。
 * 
 * 输入样例：
 * 00100 6 4
 * 00000 4 99999
 * 00100 1 12309
 * 68237 6 -1
 * 33218 3 00000
 * 99999 5 68237
 * 12309 2 33218
 * 输出样例：
 * 00000 4 33218
 * 33218 3 12309
 * 12309 2 00100
 * 00100 1 99999
 * 99999 5 68237
 * 68237 6 -1
 */

#include <stdio.h>
#include <stdlib.h>

#define SWAPNODE(A, B) {Node temp = A; A = B; B = temp;}

typedef struct node *Node;

struct node{
    int addr;
    int data;
    int next;
};

int main()
{
    int A, N, K;
    Node *nodes, *p;
    
    /* read */
    scanf("%d %d %d", &A, &N, &K);
    nodes = (Node*)malloc(N * sizeof(Node));
    for(int i = 0; i < N; i++) 
    {
        nodes[i] = (Node)malloc(sizeof(struct node));
        scanf("%d %d %d", &nodes[i]->addr, &nodes[i]->data, &nodes[i]->next);
    }
    
    /* link the list */
    for(int i = 0; i < N; i++)
    {
        for(int j = i; j < N; j++)
            if(nodes[j]->addr == (i ? nodes[i - 1]->next : A))
            {
                SWAPNODE(nodes[i], nodes[j]);
                break;
            }
        if(nodes[i]->next == -1)   /* there could be useless nodes */
            N = i + 1;
    }

    /* reverse the list */
    for(int i = 0; i < N / K; i++)
    {
        p = nodes + i * K;
        for(int j = 0; j < K / 2; j++)
            SWAPNODE(p[j], p[K - j - 1]);
    }
    
    /* print the list */
    for(int i = 0; i < N - 1; i++)
        printf("%05d %d %05d\n", 
               nodes[i]->addr, nodes[i]->data, nodes[i + 1]->addr);
    printf("%05d %d -1\n", nodes[N - 1]->addr, nodes[N - 1]->data);

    return 0;
}
