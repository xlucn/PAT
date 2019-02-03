#include <stdio.h>
#include <math.h>

typedef struct Poly{
    double coef;
    int exp;
} Poly[20];

int main()
{
    int KA, KB, Ksum = 0;
    Poly A, B, sum;

    scanf("%d", &KA);
    for(int i = 0; i < KA; i++)
        scanf("%d %lf", &A[i].exp, &A[i].coef);

    scanf("%d", &KB);
    for(int i = 0; i < KB; i++)
        scanf("%d %lf", &B[i].exp, &B[i].coef);

    int i = 0, j = 0;
    while(i < KA || j < KB)
    {
        if(i == KA || (j < KB && A[i].exp < B[j].exp))
        {
            sum[Ksum].exp = B[j].exp;
            sum[Ksum].coef = B[j++].coef;
        }
        else if(j == KB || (i < KA && A[i].exp > B[j].exp))
        {
            sum[Ksum].exp = A[i].exp;
            sum[Ksum].coef = A[i++].coef;
        }
        else
        {
            sum[Ksum].exp = A[i].exp;
            sum[Ksum].coef = A[i++].coef + B[j++].coef;
        }
        if(fabs(sum[Ksum].coef) >= 0.05) Ksum++;
    }

    printf("%d", Ksum);

    for(int i = 0; i < Ksum; i++)
        printf(" %d %.1lf", sum[i].exp, sum[i].coef);

    return 0;
}
