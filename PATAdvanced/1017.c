/**
 * 1017. Queueing at Bank (25)
 * 
 * Suppose a bank has K windows open for service. There is a yellow line in 
 * front of the windows which devides the waiting area into two parts. All the 
 * customers have to wait in line behind the yellow line, until it is his/her 
 * turn to be served and there is a window available. It is assumed that no 
 * window can be occupied by a single customer for more than 1 hour.
 * 
 * Now given the arriving time T and the processing time P of each customer, you
 * are supposed to tell the average waiting time of all the customers.
 * 
 * Input Specification:
 * 
 * Each input file contains one test case. For each case, the first line 
 * contains 2 numbers: N (<=10000) - the total number of customers, and K 
 * (<=100) - the number of windows. Then N lines follow, each contains 2 times: 
 * HH:MM:SS - the arriving time, and P - the processing time in minutes of a 
 * customer. Here HH is in the range [00, 23], MM and SS are both in [00, 59]. 
 * It is assumed that no two customers arrives at the same time.
 * 
 * Notice that the bank opens from 08:00 to 17:00. Anyone arrives early will 
 * have to wait in line till 08:00, and anyone comes too late (at or after 
 * 17:00:01) will not be served nor counted into the average.
 * 
 * Output Specification:
 * 
 * For each test case, print in one line the average waiting time of all the 
 * customers, in minutes and accurate up to 1 decimal place.
 * Sample Input:
 * 
 * 7 3
 * 07:55:00 16
 * 17:00:01 2
 * 07:59:59 15
 * 08:01:00 60
 * 08:00:00 30
 * 08:00:02 2
 * 08:03:00 10
 * 
 * Sample Output:
 * 
 * 8.2
 **/

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
