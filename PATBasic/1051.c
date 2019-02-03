#include <stdio.h>
#include <math.h>

int main()
{
    double R1, P1, R2, P2;          /* float type won't pass, not sure why */
    double A, B;

    scanf("%lf %lf %lf %lf", &R1, &P1, &R2, &P2);
    A = R1 * R2 * cos(P1 + P2);     /* doesn't matter how you calculate */
    B = R1 * R2 * sin(P1 + P2);

    if(A < 0 && A > -0.005) A = 0;  /* Rounding */
    if(B < 0 && B > -0.005) B = 0;

    printf("%.2lf%+.2lfi", A, B);

    return 0;
}
