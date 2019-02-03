#include <stdio.h>

int main()
{
    int N, iSchool, score, imax = 0;
    scanf("%d", &N);

    int schools[100000] = {0};
    for(int i = 0; i < N; i++)
    {
        scanf("%d %d", &iSchool, &score);
        schools[iSchool - 1] += score;
    }

    for(int i = 0; i < N; i++)
        if(schools[i] > schools[imax])
            imax = i;

    printf("%d %d", imax + 1, schools[imax]);

    return 0;
}
