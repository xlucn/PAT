#include <stdio.h>

#define LATE_FLAG -1
#define FORWARD(I) ((I) = ((I) == 10) ? 0 : ((I) + 1))
#define TIME_FRONT(I) time[queue[I][front[I]]]
#define TIME_REAR_PREVIOUS(I) time[queue[I][rear[I] == 0 ? 10 : (rear[I] - 1)]]

int main()
{
    int N, M, K, Q, query;
    int time[1000], queue[20][11] = {{0}};
    int front[20] = {0}, rear[20] = {0}, length[20] = {0};

    scanf("%d %d %d %d", &N, &M, &K, &Q);
    for(int i = 1; i <= K; i++)
        scanf("%d", time + i);

    /* Total number of operations */
    int count = (K < M * N) ? (2 * K) : (K + M * N);
    /* Doing dequeues and enqueues for every customer */
    for(int i = 1; i <= count; i++)
    {
        if(i > count - K)      /* Dequeue in the last K operations */
        {
            /* Find the next customer */
            int time_span = 9999, next = -1;
            for(int j = 0; j < N; j++) if(length[j])
            {
                if(TIME_FRONT(j) < time_span)
                    next = j, time_span = TIME_FRONT(j);
                else if(next == -1 && TIME_FRONT(j) == LATE_FLAG)
                    next = j;
            }
            /* Dequeue */
            FORWARD(front[next]);
            length[next]--;
        }
        if(i <= K)               /* Enqueue in the first K operations */
        {
            /* Find shortest queue */
            int shortest = 0;
            for(int j = 0; j < N; j++)
                if(length[shortest] > length[j])
                    shortest = j;
            /* Set flag or add time */
            int previous_time = TIME_REAR_PREVIOUS(shortest);
            if(previous_time >= 9 * 60 || previous_time == LATE_FLAG)
                time[i] = LATE_FLAG;
            else
                time[i] += previous_time;
            /* Enqueue */
            queue[shortest][rear[shortest]] = i;
            FORWARD(rear[shortest]);
            length[shortest]++;
        }
    }

    /* Read queries and print answers */
    for(int i = 0; i < Q; i++)
    {
        scanf("%d", &query);
        if(time[query] != LATE_FLAG)
            printf("%02d:%02d\n", 8 + time[query] / 60, time[query] % 60);
        else
            printf("Sorry\n");
    }

    return 0;
}
