#include <stdio.h>

int main()
{
    int K, n, table[101] = {0};

    scanf("%d", &K);
    for(int i = 0; i < K; i++)
    {
        scanf("%d", &n);
        table[n] = 1;
    }

    /* find numbers needed to test */
    for(int i = 1; i <= 100; i++)
        if(table[i])
            for(int j = i; j > 1; )
            {
                /* calculate for one step */
                if(j % 2)      j = (3 * j + 1) / 2;
                else           j /= 2;

                /* see if the new number is in given numbers */
                if(j <= 100 && table[j])
                {
                    table[j] = 0;       /* 'covered' this number */
                    K--;                /* one less number not 'covered' */
                    if(j < i) break;    /* did this before, no need going on */
                }
            }

    for(int i = 100; i >= 1; i--)
        if(table[i] == 1)
            printf("%d%c", i, --K ? ' ' : '\0');

    return 0;
}
