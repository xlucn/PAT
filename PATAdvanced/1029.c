#include <stdio.h>
#include <limits.h>

int main()
{
    int N1, N2, seq[200001], *p = seq, n, c = 0, median;

    /* Read one sequence into array */
    scanf("%d", &N1);
    for(int i = 0; i < N1; i++)
        scanf("%d", seq + i);
    /* Boundary setup */
    seq[N1] = INT_MAX;

    /* Read the other sequence on the fly while doing merge sort.
     * This is due to the memory limitation of the problem (1.5MB) */
    scanf("%d", &N2);
    /* read the first one */
    scanf("%d", &n);
    /* just enough to find the median: skip the first half */
    for(int i = 0; i < (N1 + N2 + 1) / 2; i++)
    {
        /* Record the smallest of the two */
        if(*p < n)
            median = *p;
        else
            median = n;

        /* Either point p at the next number or read a new number into n */
        if((*p < n && p < seq + N1) || (*p > n && c == N2))
            p++;
        else
        {
            if(c == N2 - 1)
                n = INT_MAX;
            else
                scanf("%d", &n);
            c++;
        }
    }

    printf("%d", median);

    return 0;
}
