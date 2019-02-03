#include <stdio.h>

int main()
{
    int N, a, sum = 0;

    scanf("%d", &N);
    for(int i = 0; i < N; i++)
    {
        scanf("%d", &a);
        sum += a;
    }
    printf("%d", sum * (N - 1) * 11);

    return 0;
}
