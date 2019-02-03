#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b)
{
    return *(int*)b - *(int*)a;
}

int sort(int n)
{
    int digits[4] = {n/1000, n%1000/100, n%100/10, n%10};
    qsort(digits, 4, sizeof(int), cmp);
    return digits[0] * 1000 + digits[1] * 100 + digits[2] * 10 + digits[3];
}

int reverse(int n)
{
    return n/1000 + n%1000/100 * 10 + n%100/10 * 100 + n%10 * 1000;
}

int main()
{
    int N;

    scanf("%d", &N);
    do
    {
        N = sort(N);
        printf("%04d - %04d = %04d\n", N, reverse(N), N - reverse(N));
        N = N - reverse(N);
    }while(N != 0 && N != 6174) ;

    return 0;
}
