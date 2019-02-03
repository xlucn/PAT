#include <stdio.h>

int main()
{
    int K, n, first;
    int start, end, sum = -1;   /* the current non-negative subsequence */
    int a = -1, b, s = 0;       /* the maximum-sum subsequence */

    scanf("%d", &K);
    for(int i = 0; i < K; i++)
    {
        scanf("%d", &n);
        if(i == 0) first = n;               /* record the first number */

        /* update start, end and sum for the current non-negative subsequence */
        if(sum < 0) start = n, sum = 0;     /* reset if sum < 0 */
        sum += n;                           /* update sum */
        if(sum >= 0) end = n;               /* update end if sum >= 0 */

        /* update a, b and s for the so-far maximum-sum subsequence */
        if(sum > s || (!sum && !s))         /* special case is max-sum is 0 */
            a = start, b = end, s = sum;
    }
    /* a won't be updated if all the numbers are negative */
    if(a == -1) printf("0 %d %d", first, n);
    else        printf("%d %d %d", s, a, b);

    return 0;
}
