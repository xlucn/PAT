#include <stdio.h>

int main()
{
    int N, num, diff[10000] = {0};

    scanf("%d", &N);
    for(int i = 0; i < N; i++)
    {   /* The front is i + 1, the back is num */
        scanf("%d", &num);
        diff[(num > i + 1) ? (num - i - 1) : (i + 1 - num)]++;
    }

    for(int i = N - 1; i >= 0; i--)
        if(diff[i] >= 2)
            printf("%d %d\n", i, diff[i]);

    return 0;
}
