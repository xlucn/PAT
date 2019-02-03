#include <stdio.h>

int main()
{
    char c;
    int count[10] = {0};
    while((c = getchar()) != '\n')
        count[c - '0']++;

    for(int i = 0; i < 10; i++) if(count[i])
        printf("%d:%d\n", i, count[i]);

    return 0;
}
