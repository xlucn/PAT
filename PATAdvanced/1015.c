#include <stdio.h>

int iPrime(int N)
{
    if(N == 0 || N == 1)
        return 0;
    for(int i = 2; i * i <= N; i++)
        if(N % i == 0)
            return 0;
    return 1;
}

int Rev(int N, int D)
{
    int Nrev;
    for(Nrev = 0; N; N /= D)
    {
        Nrev *= D;
        Nrev += N % D;
    }
    return Nrev;
}

int main()
{
    int N, D;

    while(scanf("%d %d", &N, &D) == 2)
        puts(iPrime(N) && iPrime(Rev(N, D)) ? "Yes" : "No");

    return 0;
}
