#include <stdio.h>

int main()
{
    int m, n, a, b, X, Y, M, diffab;
    double c;
    scanf("%d %d %d", &M, &X, &Y);

    for(m = 9; m > 0; m--)
    {
        for(n = 9; n >= 0; n--)
        {
            a = 10 * m + n;
            b = 10 * n + m;
            diffab = 9 * (m > n ? m - n : n - m);
            if(diffab * Y == b * X)
            {
                c = b * 1.0 / Y;
                printf("%d", a);
                printf(a > M ? " Cong" : (a == M ? " Ping" : " Gai"));
                printf(b > M ? " Cong" : (b == M ? " Ping" : " Gai"));
                printf(c > M ? " Cong" : (c == M ? " Ping" : " Gai"));
                return 0;
            }
        }
    }

    printf("No Solution");
    return 0;
}
