#include <stdio.h>

int main()
{
    int N, team, member, score, highest = 0, teams[1000] = {0};

    scanf("%d", &N);
    for(int i = 0; i < N; i++)
    {
        scanf("%d-%d %d", &team, &member, &score);
        teams[team - 1] += score;
    }
    for(int i = 0; i < 1000; i++)
        if(teams[i] > teams[highest])
            highest = i;
    printf("%d %d", highest + 1, teams[highest]);

    return 0;
}
