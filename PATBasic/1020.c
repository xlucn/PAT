#include <stdio.h>

int main()
{
    int N, max;
    float D, Storage[1000], Total = 0, Price[1000];

    scanf("%d %f", &N, &D);
    for(int i = 0; i < N; i++) scanf("%f", Storage + i);
    for(int i = 0; i < N; i++) scanf("%f", Price + i);

    while(D > 0)
    {
        max = 0;
        for(int i = 0; i < N; i++)
            if(Price[i] / Storage[i] > Price[max] / Storage[max])
                max = i;

        if(Storage[max] < D)
        {
            Total += Price[max];
            D -= Storage[max];
            Price[max] = 0;
        }
        else
        {
            Total += Price[max] * D / Storage[max];
            D = 0;
        }
    }
    printf("%.2f", Total);

    return 0;
}
