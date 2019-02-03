#include <stdio.h>

int main()
{
    int A, B, C;
    scanf("%d %d", &A, &B);
    C = A * B;

    while(!(C % 10))
        C /= 10;

    while(C)
    {
        putchar('0' + C % 10);
        C /= 10;
    }

    return 0;
}
