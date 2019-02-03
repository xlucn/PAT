#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int count = 0, N;
    double f, sum = 0;
    /* Maxium scenario: -1000.00. So just need to read 8 chars(+ '\0' = 9) */
    char s[9], *pEnd, *pDot, c;

    scanf("%d", &N);
    for(int i = 0; i < N; i++)
    {
        scanf("%8s", s);                /* Just read up to 8 chars */

        c = ungetc(getchar(), stdin);   /* Read next char and push back */
        f = strtod(s, &pEnd);           /* pEnd -> converted floating number */
        pDot = strchr(s, '.');          /* pDot -> (first) decimal point */

        if(!isspace(c)                          /* string too long */
        || *pEnd                                /* not floating number */
        || (f > 1000 || f < -1000)              /* out of range */
        || (pDot && pDot - s < strlen(s) - 3))  /* precision too high */
        {
            printf("ERROR: %s", s);
            /* this can avoid overflow (we don't know how long input is) */
            while(!isspace(c = getchar())) putchar(c);
            printf(" is not a legal number\n");
        }
        else                                    /* legel number */
        {
            count++;
            sum += f;
        }
    }

    if(count == 0)  printf("The average of 0 numbers is Undefined\n");
    if(count == 1)  printf("The average of 1 number is %.2lf", sum);
    if(count >= 2)  printf("The average of %d numbers is %.2lf", count, sum / count);

    return 0;
}
