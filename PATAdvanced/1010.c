/**
 * 1010. Radix (25)
 * 
 * Given a pair of positive integers, for example, 6 and 110, can this equation 
 * 6 = 110 be true? The answer is "yes", if 6 is a decimal number and 110 is a 
 * binary number.
 * 
 * Now for any pair of positive integers N1 and N2, your task is to find the 
 * radix of one number while that of the other is given.
 * 
 * Input Specification:
 * 
 * Each input file contains one test case. Each case occupies a line which 
 * contains 4 positive integers:
 * N1 N2 tag radix
 * Here N1 and N2 each has no more than 10 digits. A digit is less than its 
 * radix and is chosen from the set {0-9, a-z} where 0-9 represent the decimal 
 * numbers 0-9, and a-z represent the decimal numbers 10-35. The last number 
 * "radix" is the radix of N1 if "tag" is 1, or of N2 if "tag" is 2.
 * 
 * Output Specification:
 * 
 * For each test case, print in one line the radix of the other number so that 
 * the equation N1 = N2 is true. If the equation is impossible, print 
 * "Impossible". If the solution is not unique, output the smallest possible 
 * radix.
 * 
 * Sample Input 1:
 * 6 110 1 10
 * Sample Output 1:
 * 2
 * Sample Input 2:
 * 1 ab 1 2
 * Sample Output 2:
 * Impossible
 */
#include <ctype.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>

#define OVERFLOW -1
#define NOTFOUNT -1
#define CBASE10(C) ((C) >= '0' && (C) <= '9' ? (C) - '0' : (C) - 'a' + 10)

long long base10(char *s, long long radix)
{
    long long n, sum = 0;
    for(; *s; s++)
    {
        n = CBASE10(*s);
        if((LLONG_MAX - n) / radix < sum) /* overflow */
            return OVERFLOW;
        sum = sum * radix + n;
    }
    return sum;
}

int minradix(char *s)
{
    char r = '0';
    for(; *s; s++) if(*s > r) 
        r = *s;
    return CBASE10(r) + 1;
}

long long binsearch(char *s, long long n, long long rmin, long long rmax)
{
    long long r, m;
    while(rmax >= rmin)
    {
        r = rmin + (rmax - rmin) / 2; /* avoid overflow when rmax + rmin      */
        if((m = base10(s, r)) > n || m == OVERFLOW)  /*           > LLONG_MAX */
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
    
    /* S1 points to the number with known radix, S2 to the other */
    scanf("%s %s %d %d", buf1, buf2, &tag, &radix);
    if(tag == 1) S1 = buf1, S2 = buf2;
    if(tag == 2) S1 = buf2, S2 = buf1;
    
    N1 = base10(S1, radix);
    rmin = minradix(S2);
    rmax = LLONG_MAX;
    if(strlen(S2) == 1)  /* N2 will be same value under any radix */
    {   /* rmin - 1 is the value of N2 */
        if(N1 == rmin - 1)  printf("%lld", rmin);
        else                printf("Impossible");
    }
    else                 /* Binary search to find the radix of N2 */
    {
        r = binsearch(S2, N1, rmin, rmax);
        if(r != NOTFOUNT)   printf("%lld", r);
        else                printf("Impossible");
    }
    
    return 0;
}
