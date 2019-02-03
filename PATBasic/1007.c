#include <stdio.h>

int main()
{
    int N;
    scanf("%d", &N);

    /* Record primality of three successive numbers starting from 2, 3, 4 */
    int iPrimeMinus2 = 1, iPrimeMinus1 = 1, iPrime;
    int primes[100] = {2, 3};   /* Record the prime numbers before sqrt(10^5) */
    int twincount = 0;          /* Count of twin primes */
    int primecount = 2;         /* Count of prime numbers */

    /* Start from 4 */
    for(int i = 4; i <= N; i++)
    {
        /* Test if i is a prime number */
        iPrime = 1;
        for(int j = 0; iPrime && primes[j] * primes[j] <= i; j++)
            if(i % primes[j] == 0)
                iPrime = 0;

        /* If i is a prime number, record */
        if(iPrime)
        {
            if(primecount < 100)    primes[primecount++] = i;
            if(iPrimeMinus2 == 1)   twincount++;    /* a prime pair found */
        }

        /* Shift the primality flags to next numbers */
        iPrimeMinus2 = iPrimeMinus1;
        iPrimeMinus1 = iPrime;
    }
    printf("%d", twincount);

    return 0;
}
