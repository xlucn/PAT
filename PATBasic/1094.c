#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int iPrime(int n)
{
    if(n < 2)
        return 0;
    for(int i = 2; i * i <= n; i++)
        if(n % i == 0)
            return 0;
    return 1;
}

int main()
{
    char N[1000], n[10] = {0};
    int L, K;

    scanf("%d %d %s", &L, &K, N);  /* L == strlen(N) */
    for(int i = 0; i <= L - K; i++)
    {
        strncpy(n, N + i, K);
        if(iPrime(atoi(n)))
        {
            printf("%s", n);
            return 0;
        }
    }

    printf("404");
    return 0;
}
