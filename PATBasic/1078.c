#include <stdio.h>

void compress()
{
    char previous = getchar(), current;
    int count = 1;

    while((current = getchar()))
    {
        if(current == previous)
        {
            count++;                /* Increament count */
        }
        else
        {
            if(count > 1)           /* Only print if count > 1 */
                printf("%d", count);
            putchar(previous);
            previous = current;
            count = 1;
        }

        if(current == '\n')         /* Don't put this in while() */
            break;
    }
}

void decompress()
{
    char c;
    int count = 0;

    while((c = getchar()) != '\n')
    {
        if(c >= '0' && c <= '9') /* If it is number */
        {
            count = count * 10 + c - '0';   /* Accumulate count */
        }
        else                     /* If it is not number */
        {
            if(count == 0)                  /* No number before char */
                count = 1;                      /* print once */
            for(int i = 0; i < count; i++)  /* Or print 'count' times */
                putchar(c);
            count = 0;                      /* Reset 'count' */
        }
    }
}

int main()
{
    switch(getchar())
    {
        case 'C':
            while(getchar() != '\n');
            compress();
            break;
        case 'D':
            while(getchar() != '\n');
            decompress();
            break;
        default:
            break;
    }

    return 0;
}
