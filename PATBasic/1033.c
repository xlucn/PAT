#include <stdio.h>
#include <ctype.h>

int main()
{
    char c;
    int bad[128] = {0}; /* record keys are broken or not */

    while((c = getchar()) != '\n')      /* read broken keys */
        bad[toupper(c)] = 1;

    while((c = getchar()) != '\n')      /* read string and print */
        if(!bad[toupper(c)] && !(isupper(c) && bad['+']))
              putchar(c);

    return 0;
}
