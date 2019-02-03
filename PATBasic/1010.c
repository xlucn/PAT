#include <stdio.h>

int main()
{
    int coef, index, count = 0;

    while(scanf("%d %d", &coef, &index) != EOF)
    {
        if(index) /* Constant terms result in zero */
        {
            if(count++) putchar(' ');
            printf("%d %d", coef * index, index - 1);
        }
    }

    /* Zero polynomial or constant */
    if(count == 0)
        puts("0 0");

    return 0;
}
