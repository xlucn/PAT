#include <stdio.h>

int main()
{
    char c;
    int lines = 0, ascii[128] = {0};

    while(lines < 2)
    {
        c = getchar();
        if(c == '\n')
            lines++;
        else if(!ascii[(int)c])
        {
            putchar(c);
            ascii[(int)c]++;
        }
    }

    return 0;
}
