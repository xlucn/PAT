#include <stdio.h>

int main()
{
    int sum = 0;
    char c, *digits[] = {
        "zero", "one", "two", "three", "four", "five",
        "six", "seven", "eight", "nine"
    };

    while((c = getchar()) != '\n')
        sum += c - '0';

    if(sum >= 100)
        printf("%s ", digits[sum / 100]);
    if(sum >= 10)
        printf("%s ", digits[sum % 100 / 10]);
    printf("%s", digits[sum % 10]);

    return 0;
}
