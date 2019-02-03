#include <stdio.h>

int main()
{
    char c, *str = "PATest";                /* use as index for count[] */
    int i, flag = 1, count[128] = {0};      /* for each ASCII char */

    /* Read and count numbers for every character */
    while((c = getchar()) != '\n')
        count[(int)c]++;

    /* Print any character in "PATest" if it is still left */
    while(flag)
        for(i = 0, flag = 0; i < 6; i++)
            if(count[(int)str[i]]-- > 0)    /* Check the number left */
                putchar(str[i]), flag = 1;

    return 0;
}
