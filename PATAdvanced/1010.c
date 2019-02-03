#include <ctype.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>

#define OVERFLOW -1
#define NOTFOUNT -1
#define CBASE10(C) ((C) >= '0' && (C) <= '9' ? (C) - '0' : (C) - 'a' + 10)

/* Calculate decimal value of a text-form number s under a radix */
long long base10(char *s, long long radix)
{
    long long n, sum;
    for(sum = 0; *s; s++)
    {
        n = CBASE10(*s);
        if((LLONG_MAX - n) / radix < sum) /* overflow */
            return OVERFLOW;
        sum = sum * radix + n;
    }
    return sum;
}

/* Find the smallest possible radix of a numbers */
int minradix(char *s)
{   /* Simply the largest digit in the number plus 1 */
    char r;
    for(r = '0'; *s; s++)
        if(*s > r)
            r = *s;
    return CBASE10(r) + 1;
}

/* Use binary search to locate radix of s which makes it equals n */
long long binsearch(char *s, long long n, long long rmin, long long rmax)
{
    long long r, m;
    while(rmax >= rmin)
    {
        r = rmin + (rmax - rmin) / 2; /* avoid (rmin + rmax) overflow */
        if((m = base10(s, r)) > n || m == OVERFLOW)
            rmax = r - 1;
        else if(m < n)
            rmin = r + 1;
        else
            return r;
    }
    return NOTFOUNT;
}

int main()
{
    int tag, radix;
    long long N1, rmin, rmax, r;
    char buf1[11], buf2[11], *S1, *S2;

    /* Make S1 point to the number with known radix, S2 to the other */
    scanf("%s %s %d %d", buf1, buf2, &tag, &radix);
    if(tag == 1) S1 = buf1, S2 = buf2;
    if(tag == 2) S1 = buf2, S2 = buf1;

    N1 = base10(S1, radix);     /* Corresponding decimal of S1 */
    rmin = minradix(S2);        /* Smallest possible radix of S2 */
    rmax = LLONG_MAX;           /* Largest possible radix of S2 */
    if(strlen(S2) == 1) /* If so, N2 will be same value under any radix */
    {                           /* rmin - 1 (naturally equals N2) equals N1 */
        if(N1 == rmin - 1)      printf("%lld", rmin);
        else                    printf("Impossible");
    }
    else                /* Binary search to find the radix of N2 */
    {
        r = binsearch(S2, N1, rmin, rmax);
        if(r != NOTFOUNT)       printf("%lld", r);
        else                    printf("Impossible");
    }

    return 0;
}
