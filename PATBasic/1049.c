#include <stdio.h>

int main()
{
    int N;
    double ai, sum = 0;

    scanf("%d", &N);
    for(int i = 0; i < N; i++)
    {
        scanf("%lf", &ai);
        /* ai is put at the beginning to avoid overflow */
        sum += ai * (i + 1) * (N - i);
    }
    printf("%.2lf", sum);

    return 0;
}
