#include <stdio.h>

int main()
{
    int N, base10, lo, curr, hi, count = 0;

    scanf("%d", &N);

    /* for every digits, from lower to higher */
    for(base10 = 1; base10 <= N; base10 *= 10)
    {
        lo = N % base10;        /* part of the number after current digit */
        hi = N / base10 / 10;   /* part of the number before current digit */
        curr = N / base10 - hi * 10;     /* current digit */
        /* count numbers that is smaller than N and has '1' in the current digit */
        if(curr == 0)           /* count: [0~(hi-1)]1[0~9...9] */
            count += hi * base10;
        else if(curr == 1)      /* count: [0~(hi-1)]1[0~9...9] or [hi]1[0~lo] */
            count += lo + 1 + hi * base10;
        else                    /* count: [0~hi]1[0~9...9] */
            count += (hi + 1) * base10;
    }

    printf("%d\n", count);

    return 0;
}
