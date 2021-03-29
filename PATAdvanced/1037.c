#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b) { return *(int*)b - *(int*)a; }

int main()
{
    int NC, NP;
    long sum = 0, coupon[100000] = {0}, product[100000] = {0};

    /* read and sort */
    scanf("%d", &NC);
    for(int i = 0; i < NC; i++)
        scanf("%ld", coupon + i);
    qsort(coupon, NC, sizeof(long), cmp);
    scanf("%d", &NP);
    for(int i = 0; i < NP; i++)
        scanf("%ld", product + i);
    qsort(product, NP, sizeof(long), cmp);

    for(int i = 0; coupon[i] > 0 && product[i] > 0; i++)
        sum += coupon[i] * product[i];
    for(int i = 0; coupon[NC - i - 1] < 0 && product[NP - i - 1] < 0; i++)
        sum += coupon[NC - i - 1] * product[NP - i - 1];

    printf("%ld\n", sum);

    return 0;
}
