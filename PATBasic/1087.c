#include <stdio.h>

int main()
{
    int N, n, m, m0 = -1, count = 0;

    scanf("%d", &N);

    for(n = 1; n <= N; n++)
    {
        m = n / 2 + n / 3 + n / 5;
        if(m > m0)
            count++;
        m0 = m;
    }

    printf("%d", count);

    return 0;
}
