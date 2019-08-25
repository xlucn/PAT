#include <stdio.h>

int main()
{
    int n, DIGITS = 3;
    char convert[] = "0123456789ABC";
    printf("#");

    for(int i = 0; i < DIGITS; i++)
    {
        scanf("%d", &n);
        printf("%c%c", convert[n / 13], convert[n % 13]);
    }
    return 0;
}
