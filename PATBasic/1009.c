#include <stdio.h>
#include <string.h>

int main()
{
    char s[82], *p;

    scanf("%[^\n]", s);

    for(p = s + strlen(s) - 1; p >= s; p--)
    {
        if(*(p - 1) == ' ')
            printf("%s ", p);
        if(p == s)
            printf("%s", p);
        if(*p == ' ')
            *p = '\0';
    }

    return 0;
}
