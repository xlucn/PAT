#include <stdio.h>
#include <ctype.h>

int main()
{
    char c;
    int count[26] = {0}, max = 25;

    while((c = getchar()) != '\n')
        if(isalpha(c))
            count[tolower(c) - 'a']++;

    /* find forward from end in case there are multiple maximums */
    for(int i = 25; i >= 0; i--)
        if(count[i] >= count[max])
            max = i;

    printf("%c %d", max + 'a', count[max]);

    return 0;
}
