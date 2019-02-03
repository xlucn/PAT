#include <stdio.h>

int main()
{
    int number, steps;
    scanf("%d", &number);

    for(steps = 0; number != 1; steps++)
        if(number % 2 == 0)
            number /= 2;
        else
            number = (3 * number + 1) / 2;

    printf("%d", steps);

    return 0;
}
