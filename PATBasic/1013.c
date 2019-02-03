#include <stdio.h>

int main()
{

    int M, N;
    scanf("%d %d", &M, &N);
    int primes[10000];

    for(int n = 2, count = 0; count < N; n++)
    {
        /* Check if n is prime number */
        int iprime = 1;
        for(int j = 0; count > 0 && primes[j] * primes[j] <= n; j++)
            if(n % primes[j] == 0)
                iprime = 0;

        /* Record */
        if(iprime)
            primes[count++] = n;
    }

    /* Print */
    for(int i = M; i < N; i++)
    {
        printf("%d", primes[i - 1]);
        printf((i - M + 1) % 10 ? " " : "\n");
    }
    printf("%d", primes[N - 1]);

    return 0;
}
