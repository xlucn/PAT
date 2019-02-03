#include <stdio.h>

int main()
{
    int sum = 0;
    char c, *pinyins[] = {"ling", "yi", "er", "san", "si",
                          "wu", "liu", "qi", "ba", "jiu"};

    while((c = getchar()) != '\n')
        sum += c - '0';

    if(sum / 100)                           /* hundreds */
        printf("%s ", pinyins[sum / 100]);
    if(sum / 10)                            /* tens */
        printf("%s ", pinyins[sum / 10 % 10]);
    printf("%s", pinyins[sum % 10]);        /* units */

    return 0;
}
