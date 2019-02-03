#include <stdio.h>

int main()
{
    int N, m, sum, friendID[37] = {0}, count = 0;

    scanf("%d", &N);
    for(int i = 0; i < N; i++)
    {
        scanf("%d", &m);
        for(sum = 0; m; m /= 10)
            sum += m % 10;
        if(!friendID[sum])
            friendID[sum] = 1, count++;
    }

    printf("%d\n", count);
    for(int i = 1; i < 37; i++)
        if(friendID[i])
            printf("%d%c", i, --count ? ' ' : '\0');

    return 0;
}
