#include <stdio.h>
#include <ctype.h>

int main()
{
    char line[81], *p = line, *i;
    fgets(line, 81, stdin);

    while(*++p);                               /* Go to the end of the string */
    while(p > line)              /* Will break at the beginning of the string */
    {
        while(isspace(*--p)) ;                      /* Find the end of a word */
        while(p > line && !isspace(*(p - 1))) p--;  /* Find start of the word */
        for(i = p; *i && !isspace(*i); putchar(*i++));      /* Print the word */
        putchar(p == line ? '\0' : ' ');    /* print blankspace if not at end */
    }

    return 0;
}
