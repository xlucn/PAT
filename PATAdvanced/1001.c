#include <stdio.h>
#include <string.h>

int main()
{
    int a, b, pos;
    char num[11];

    scanf("%d%d", &a, &b);
    sprintf(num, "%d", a + b);

    for(pos = strlen(num) - 3; pos > 0 && num[pos - 1] != '-'; pos -= 3)
    {
        memmove(num + pos + 1, num + pos, strlen(num) - pos + 1);
        num[pos] = ',';
    }

    puts(num);
    return 0;
}
