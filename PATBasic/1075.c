#include <stdio.h>

int main()
{
    int data[100000] = {0}, next[100000] = {0},
        firstaddr, addr, lastaddr = -1, N, K;

    /* Read */
    scanf("%d %d %d", &firstaddr, &N, &K);
    for(int i = 0; i < N; i++)
    {
        scanf("%d", &addr);
        scanf("%d %d", data + addr, next + addr);
    }

    /* Scan three times */
    for(int i = 0; i < 3; i++)
    {
        /* Scan along the linked list */
        for(addr = firstaddr; addr != -1; addr = next[addr])
        {
            /* If the number fits the condition */
            if((i == 0 && data[addr] < 0)
            || (i == 1 && 0 <= data[addr] && data[addr] <= K)
            || (i == 2 && data[addr] > K))
            {
                /* Print */
                if(lastaddr != -1) printf(" %05d\n", addr);
                printf("%05d %d", addr, data[addr]);
                lastaddr = addr;
            }
        }
    }
    printf(" -1");

    return 0;
}
