/**
 * 1014. Waiting in Line (30)
 * 
 * Suppose a bank has N windows open for service. There is a yellow line in 
 * front of the windows which devides the waiting area into two parts. The rules
 * for the customers to wait in line are:
 * 
 *     The space inside the yellow line in front of each window is enough to 
 * contain a line with M customers. Hence when all the N lines are full, all the
 * customers after (and including) the (NM+1)st one will have to wait in a line 
 * behind the yellow line.
 *     Each customer will choose the shortest line to wait in when crossing the 
 * yellow line. If there are two or more lines with the same length, the 
 * customer will always choose the window with the smallest number.
 *     Customer[i] will take T[i] minutes to have his/her transaction processed.
 *     The first N customers are assumed to be served at 8:00am. 
 *
 * Now given the processing time of each customer, you are supposed to tell the 
 * exact time at which a customer has his/her business done.
 *
 * For example, suppose that a bank has 2 windows and each window may have 2 
 * custmers waiting inside the yellow line. There are 5 customers waiting with 
 * transactions taking 1, 2, 6, 4 and 3 minutes, respectively. At 08:00 in the 
 * morning, customer1 is served at window1 while customer2 is served at window2.
 * Customer3 will wait in front of window1 and customer4 will wait in front of 
 * window2. Customer5 will wait behind the yellow line.
 * 
 * At 08:01, customer1 is done and customer5 enters the line in front of window1
 * since that line seems shorter now. Customer2 will leave at 08:02, customer4 
 * at 08:06, customer3 at 08:07, and finally customer5 at 08:10.
 * 
 * Input
 * 
 * Each input file contains one test case. Each case starts with a line 
 * containing 4 positive integers: N (<=20, number of windows), M (<=10, the 
 * maximum capacity of each line inside the yellow line), K (<=1000, number of 
 * customers), and Q (<=1000, number of customer queries).
 * 
 * The next line contains K positive integers, which are the processing time of 
 * the K customers.
 * 
 * The last line contains Q positive integers, which represent the customers who
 * are asking about the time they can have their transactions done. The 
 * customers are numbered from 1 to K.
 * 
 * Output
 * 
 * For each of the Q customers, print in one line the time at which his/her 
 * transaction is finished, in the format HH:MM where HH is in [08, 17] and MM 
 * is in [00, 59]. Note that since the bank is closed everyday after 17:00, for 
 * those customers who cannot be served before 17:00, you must output "Sorry" 
 * instead.
 * Sample Input
 * 
 * 2 2 7 5
 * 1 2 6 4 3 534 2
 * 3 4 5 6 7
 * 
 * Sample Output
 * 
 * 08:07
 * 08:06
 * 08:10
 * 17:00
 * Sorry
 **/

#include <stdio.h>

#define FORWARD(I, M) ((I) = ((I) == (M - 1)) ? 0 : ((I) + 1))
#define FRONT(I) queue[I][qi[I].front]
#define REAR(I) queue[I][qi[I].rear]

typedef struct {
    int front, rear, length;
} queue_info;

int main()
{
    int N, M, K, Q, query;
    int time[1000] = {0}, total_time = 0, queue[20][10] = {{0}};
    queue_info qi[20] = {0};
    
    scanf("%d %d %d %d", &N, &M, &K, &Q);
    for(int i = 0; i < K; i++)
        scanf("%d", time + i);
    
    /* Dequeue and enqueue */
    int count = (K < M * N) ? (2 * K) : (K + M * N);
    for(int i = 0; i < count; i++)
    {
        if(i >= count - K)      /* Dequeue */
        {
            int time_span=9999, fastest;
            for(int j = 0; j < N; j++)
                if(qi[j].length && time[FRONT(j)] < time_span)
                    fastest = j, time_span = time[FRONT(j)];
            for(int j = 0; j < N; j++)
                if(qi[j].length)
                    time[FRONT(j)] -= time_span;
            total_time += time_span;
            /* Update time */
            time[FRONT(fastest)] = total_time;
            /* Dequeue */
            FORWARD(qi[fastest].front, M);
            qi[fastest].length--;
        }
        if(i < K)               /* Enqueue */
        {
            int shortest = 0;
            for(int j = 0; j < N; j++)
                if(qi[shortest].length > qi[j].length)
                    shortest = j;
            REAR(shortest) = i;
            FORWARD(qi[shortest].rear, M);
            qi[shortest].length++;
        }
    }
    
    /* Read queries and print answers */
    for(int i = 0; i < Q; i++)
    {
        scanf("%d", &query);
        query--;
        if(time[query] <= 540)
            printf("%02d:%02d\n", 8 + time[query] / 60, time[query] % 60);
        else
            printf("Sorry\n");
    }
    
    return 0;
}
