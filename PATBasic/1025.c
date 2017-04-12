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

int main()
{
    int A, N, K;
    scanf("%d %d %d", &A, &N, &K);
    int **nodes = (int**)malloc(N * sizeof(int*));
    
    /* read */
    for(int i = 0; i < N; i++){   
        nodes[i] = (int*)malloc(3 * sizeof(int)); /* Address, Data, Next */
        scanf("%d %d %d", nodes[i], nodes[i] + 1, nodes[i] + 2);
    }
    
    /* link the list */
    int *temp;
    for(int i = 0; i < N - 1; i++){
        for(int j = i; j < N; j++){
            if(nodes[j][0] == (i ? nodes[i - 1][2] : A)){
                temp = nodes[i]; 
                nodes[i] = nodes[j]; 
                nodes[j] = temp;
                if(nodes[i][2] == -1){  /* there could be useless nodes ... */
                    N = i + 1;          /*    AND                           */
                }                       /*       NO             :-(         */
                break;                  /*         ONE                      */
            }                           /*            TOLD                  */
        }                               /*                ME                */
    }                                   /*                  BEFORE          */
                                        /*                        !!!!      */
    /* reverse the list */
    int **p = nodes;
    for(; N >= K; N -= K, p += K)   /* 1. every K nodes */
    {      
        for(int i = K - 1; i >= 0; i--)
        {
            /* Adreess and Data */
            printf("%05d %d ", p[i][0], p[i][1]);
            /* Next */
            if(i == 0)              /* 1.1. last node in every K nodes */
            {
                if(N - K >= K)      /* 1.1.1. point to the last in next K nodes */
                    printf("%05d\n", (*(p + 2 * K - 1))[0]);
                else if(N - K > 0)  /* 1.1.2. there is less then K nodes left, point to the first in next group */
                    printf("%05d\n", (*(p + K))[0]);
                else                /* 1.1.3. this is the last node, point to -1 */
                    printf("-1\n");                 
            }
            else                    /* 1.2. not last in every K nodes, point to the previous node */
            {
                printf("%05d\n", p[i - 1][0]); 
            }
        }
    }
    for(; N; p++, N--)              /* 2. last nodes if there is any */
    {
        printf("%05d %d ", (*p)[0], (*p)[1]);
        if(N > 1)                   /* 2.1. not last node */
            printf("%05d\n", (*p)[2]);
        else                        /* 2.2. last node */
            printf("-1\n");
    }
    
    return 0;
}
