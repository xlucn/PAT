#include <stdio.h>

int main()
{
    int exponent;    /* the exponent part */
    char line[10000], *p = line;
    scanf("%[^E]E%d", line, &exponent);

    if(*p++ == '-') putchar('-');       /* no print if it's '+' */
    if(exponent >= 0)           /* print '.' later or add zeros in the end */
    {
        putchar(*p);
        for(p += 2; exponent; exponent--)    /* print the integer part */
            putchar(*p ? *p++ : '0');
        if(*p)                               /* there is still fraction part */
        {
            putchar('.');
            while(*p) putchar(*p++);
        }
    }
    if(exponent < 0)            /* add exponent zeros in the beginning */
    {
        printf("0.");
        for(exponent++; exponent; exponent++)       /* add zeros */
            putchar('0');
        for(; *p; p++) if(*p != '.') putchar(*p);   /* the rest */
    }

    return 0;
}
