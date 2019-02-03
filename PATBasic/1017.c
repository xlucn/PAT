#include <stdio.h>

/* read 2 digits from highest digit of A, do manual division, get the quotient
 and remainder. Read one more digit, combine this with the last remainder to
get a new 2-digits number. Do this until read to the end of A */

int main()
{
    int B;
    char A[1001], *p = A;
    scanf("%s %d", A, &B);

    /* the results are stored in A and B instead of printed out on-the-fly */
    int twodigit, remainder = 0;
    for(int i = 0; A[i]; i ++)
    {
        twodigit = remainder * 10 + (A[i] - '0');
        A[i] = twodigit / B + '0';
        remainder = twodigit % B;
    }
    B = remainder;

    /* print */
    if(A[0] == '0' && A[1] != '\0') p++;
    printf("%s %d", p, B);

    return 0;
}
