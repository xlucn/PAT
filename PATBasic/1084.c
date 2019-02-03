#include <stdio.h>

int main()
{
    int N, count;
    char string1[100000] = {0}, string2[100000] = {0};
    char *s1 = string1, *s2 = string2, *temp;
    char *p1, *p2;

    scanf("%s %d", s1, &N);

    for(int i = 1; i < N; i++)  /* Loop through nth string */
    {
        for(p1 = s1, p2 = s2, count = 0; *p1; p1++)
        {
            count++;    /* Magic, don't touch! */
            if(*p1 != *(p1 + 1))        /* New char or end */
            {
                *p2++ = *p1;            /* Record character */
                *p2++ = count + '0';    /* Record count */
                count = 0;              /* Reset count */
            }
        }
        /* Swap */
        temp = s1, s1 = s2, s2 = temp;
    }

    puts(s1);

    return 0;
}
