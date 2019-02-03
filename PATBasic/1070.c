#include <stdio.h>

int main()
{
    int l[10001] = {0}, N, i;
    double length = 0;

    scanf("%d", &N);
    for(int j = 0; j < N; j++)
    {
        scanf("%d", &i);
        l[i]++;                 /* record counts */
    }

    for(i = 0; i < 10001; i++)  /* find the shortest, special case */
        if(l[i])
        {
            length = i;
            break;
        }

    for(; i < 10001; i++)       /* make new ropes */
        while(l[i]--)
            length = (length + i) / 2;

    printf("%d", (int)length);

    return 0;
}
