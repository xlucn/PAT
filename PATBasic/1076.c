#include <stdio.h>

int main()
{
    char string[4];

    while(scanf("%s", string) != EOF)
        if(string[2] == 'T')
            putchar("1234"[string[0] - 'A']);

    return 0;
}
