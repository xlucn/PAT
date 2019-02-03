#include <stdio.h>

int main()
{
    int A, B, D, Sum;
    scanf("%d %d %d", &A, &B, &D);
    Sum = A + B;

    /* calculate the bits of Sum */
    int power = 1;
    /* use Sum / D >= power to avoid using long int */
    while(Sum / D >= power) power *= D;

    /* calculate D-base number. print them on-the-fly */
    for(; power > 0; Sum %= power, power /= D)
        printf("%d", Sum / power);

    return 0;
}
