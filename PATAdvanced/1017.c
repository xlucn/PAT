#include <stdio.h>
#include <stdlib.h>

typedef struct Customer{
    int start, len;
}Customer;

/* Compare two Customer stucture by start time */
int cmp(const void *a, const void *b)
{
    Customer c1 = *(Customer*)a;
    Customer c2 = *(Customer*)b;
    return c1.start - c2.start;
}

int main()
{
    int N, K, earliest, i;
    int HH, MM, SS;
    int wait_time = 0, queue_time[100] = {0};
    Customer customers[10000], *p;

    scanf("%d %d", &N, &K);
    for(int i = 0; i < N; i++)
    {
        scanf("%d:%d:%d %d", &HH, &MM, &SS, &customers[i].len);
        /* Relative time to 08:00:00 */
        customers[i].start = SS + 60 * (MM + 60 * (HH - 8));
        customers[i].len *= 60;
    }

    qsort(customers, N, sizeof(Customer), cmp);

    for(i = 0; i < N; i++)
    {
        p = customers + i;

        /* Find the queue number which will finish next */
        earliest = 0;
        for(int i = 0; i < K; i++)
            if(queue_time[i] < queue_time[earliest])
                earliest = i;

        /* later than 17:00:00 */
        if(p->start > (17 - 8) * 3600)
            break;
        /* processing time longer than one hour */
        if(p->len > 3600)
            p->len = 3600;

        /* increase total waiting time and modify the time of each queue */
        if(p->start < queue_time[earliest])
        {
            wait_time += queue_time[earliest] - p->start;
            queue_time[earliest] += p->len;
        }
        else
        {
            queue_time[earliest] = p->start + p->len;
        }
    }

    if(i)
        printf("%.1f", wait_time / 60.0 / i);
    else
        printf("0.0");

    return 0;
}
