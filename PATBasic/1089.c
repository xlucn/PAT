#include <stdio.h>
#include <stdlib.h>

/**
 * According to the problem, we know that there will be:
 *  one 'good' player who lies,
 *  one 'bad' player who lies and
 *  one 'bad' pleyer who doesn't
 */
int main()
{
    int N, flag, badguys[2] = {100, 100}, assum[2];
    int records[101];

    /* Read and update */
    scanf("%d", &N);
    for(int i = 1; i <= N; i++)
        scanf("%d", &records[i]);

    /* Assume: m and n are the players who lied */
    for(int m = 1; m <= N; m++)
    {   /* Assume: n and l are the 'bad' players */
        for(int n = 1; n <= N; n++)
        {
            for(int l = 1; l <= N; l++)
            {
                /* only when m, n, l are not same */
                if(m == n || n == l || l == m)
                    continue;

                /* reverse */
                records[m] *= -1;
                records[n] *= -1;

                flag = 0;
                for(int i = 1; i <= N; i++)
                {
                    /* if n or l is good or anyone else is bad, wrong! */
                    if(((abs(records[i]) == n || abs(records[i]) == l)
                         && records[i] > 0)
                    || ((abs(records[i]) != n && abs(records[i]) != l)
                         && records[i] < 0))
                        flag = 1;
                }

                if(!flag)
                {
                    assum[0] = n > l ? l : n;
                    assum[1] = n > l ? n : l;
                    /* if they are smaller */
                    if((assum[0] < badguys[0])
                    || (assum[0] == badguys[0] && assum[1] < badguys[1]))
                    {
                        badguys[0] = assum[0];
                        badguys[1] = assum[1];
                    }
                }

                /* reverse back */
                records[m] *= -1;
                records[n] *= -1;
            }
        }
    }

    if(badguys[0] == 100 && badguys[1] == 100)
        printf("No Solution");
    else
        printf("%d %d", badguys[0], badguys[1]);

    return 0;
}
