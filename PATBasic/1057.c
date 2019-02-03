#include <stdio.h>
#include <ctype.h>

int main()
{
    char c;
    int sum = 0, count[2] = {0};

    while((c = getchar()) != '\n')
        if(isalpha(c))
            sum += tolower(c) - 'a' + 1;

    for(; sum; sum >>= 1)
        count[sum & 1]++;

    printf("%d %d", count[0], count[1]);

    return 0;
}
