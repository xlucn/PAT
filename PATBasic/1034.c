#include <stdio.h>

/* Both parameters take positive value */
long calcgcd(long a, long b)
{
    long r;
    while((r = a % b))
    {
        a = b;
        b = r;
    }
    return b;
}

/* print a fraction number, giving the numerator and dominator */
void printfrac(long n, long d)
{
    if(d == 0) { printf("Inf"); return; }

    /* record the sign and make them positive */
    int inegative = 1;
    if(n < 0) { n = -n; inegative *= -1; }
    if(d < 0) { d = -d; inegative *= -1; }

    /* reduce the fraction */
    long gcd = calcgcd(n, d);
    n /= gcd;
    d /= gcd;

    /* print */
    if(inegative == -1)  printf("(-");
    if(n / d && n % d)   printf("%ld %ld/%ld", n / d, n % d, d); /* mixed fractions */
    else if(n % d)       printf("%ld/%ld", n % d, d);            /* proper fractions */
    else                 printf("%ld", n / d);                   /* integers */
    if(inegative == -1)  printf(")");
}

int main()
{
    long a1, b1, a2, b2;
    scanf("%ld/%ld %ld/%ld", &a1, &b1, &a2, &b2);

    char op[4] = {'+', '-', '*', '/'};
    for(int i = 0; i < 4; i++)
    {
        printfrac(a1, b1);        printf(" %c ", op[i]);
        printfrac(a2, b2);        printf(" = ");
        switch(op[i])
        {
            case '+': printfrac(a1 * b2 + a2 * b1, b1 * b2); break;
            case '-': printfrac(a1 * b2 - a2 * b1, b1 * b2); break;
            case '*': printfrac(a1 * a2,           b1 * b2); break;
            case '/': printfrac(a1 * b2,           b1 * a2); break;
        }
        printf("\n");
    }

    return 0;
}
