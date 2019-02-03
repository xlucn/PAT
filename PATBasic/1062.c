#include <stdio.h>

int gcd(int a, int b)
{
    for(int r; (r = a % b); a = b, b = r) ;
    return b;
}

int main()
{
    int N1, N2, M1, M2, K, L, count = 0;
    scanf("%d/%d %d/%d %d", &N1, &M1, &N2, &M2, &K);

    if(N1 * M2 > N2 * M1)
    {
        L = N1, N1 = N2, N2 = L;
        L = M1, M1 = M2, M2 = L;
    }

    for(L = N1 * K / M1 + 1; N2 * K > M2 * L; L++)
        if(gcd(L, K) == 1)
            printf("%s%d/%d", count++ ? " " : "", L, K);

    return 0;
}
