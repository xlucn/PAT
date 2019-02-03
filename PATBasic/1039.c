#include <stdio.h>

int main()
{
    char c;
    int record[128] = {0};  /* all ASCII characters */
    while((c = getchar()) != '\n')  record[(int)c]++;
    while((c = getchar()) != '\n')  record[(int)c]--;

    int more = 0, less = 0;
    for(int i = 0; i < 128; i++)
    {
        if(record[i] > 0)    more += record[i];
        if(record[i] < 0)    less -= record[i];
    }

    if(less)    printf("No %d", less);
    else        printf("Yes %d", more);

    return 0;
}
