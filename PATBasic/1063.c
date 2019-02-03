#include <stdio.h>
#include <math.h>

int main()
{
    int N, R, I, norm = 0;

    scanf("%d", &N);
    for(int i = 0; i < N; i++)
    {
        scanf("%d %d", &R, &I);
        if(R * R + I * I > norm)
            norm = R * R + I * I;
    }
    printf("%.2lf", sqrt(norm));

    return 0;
}
