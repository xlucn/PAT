#include <stdio.h>

int main()
{
    int N, counts[10001] = {0}, bets[100000] = {0};

    scanf("%d", &N);
    for(int i = 0; i < N; i++)
    {
        scanf("%d", bets + i);
        counts[bets[i]]++;
    }

    for(int i = 0; i < N; i++)
        if(counts[bets[i]] == 1)
        {
            printf("%d", bets[i]);
            return 0;
        }

    printf("None");
    return 0;
}
