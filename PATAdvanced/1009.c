#include <stdio.h>
int main()
{
    int N, exp, count = 0;
    float coef, A[1001] = {0}, B[1001] = {0}, MUL[2001] = {0};

    scanf("%d", &N);
    while(N--){ scanf("%d %f", &exp, &coef); A[exp] = coef; }
    scanf("%d", &N);
    while(N--){ scanf("%d %f", &exp, &coef); B[exp] = coef; }

    for(int i = 0; i < 1001; i++)
        for(int j = 0; j < 1001; j++)
            MUL[i + j] += A[i] * B[j];

    for(int i = 0; i < 2001; i++)
        if(MUL[i]) count++;

    printf("%d", count);
    for(int i = 2000; i >= 0; i--) if(MUL[i])
        printf(" %d %.1f", i, MUL[i]);

    return 0;
}
