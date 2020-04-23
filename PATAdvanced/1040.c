#include <stdio.h>
#include <string.h>

int main()
{
    int maxlen = 0, l, L;
    char string[1002];

    fgets(string, 1001, stdin);

    L = strlen(string);
    for(int i = 0; i < L; i++)
    {
        /* odd symmetric */
        l = 0;
        while(i - l >= 0
            && i + l < L
            && string[i - l] == string[i + l])
            l++;
        maxlen = (l * 2 - 1) > maxlen ? (l * 2 - 1) : maxlen;
        /* even symmetric */
        l = 0;
        while(i - l >= 0
            && i + l + 1 < L
            && string[i - l] == string[i + l + 1])
            l++;
        maxlen = (l * 2) > maxlen ? (l * 2) : maxlen;
    }

    printf("%d", maxlen);
    return 0;
}
