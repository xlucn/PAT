#include <ctype.h>
#include <stdio.h>

int main()
{
    int printed[128] = {0};
    char c, line[82];

    fgets(line, 82, stdin);
    while((c = getchar()) != '\n')
        printed[toupper(c)]++;

    for(char *p = line; *p; p++)
    {
        c = toupper(*p);
        if(printed[(int)c] == 0)
        {
            putchar(c);
            printed[(int)c] = -1;
        }
    }
    return 0;
}
