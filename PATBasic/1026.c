#include <stdio.h>

int main()
{
    int C1, C2, T;

    scanf("%d %d", &C1, &C2);
    T = (C2 - C1 + 50) / 100;   /* rounding */
    printf("%02d:%02d:%02d", T/3600, T%3600/60, T%60);

    return 0;
}
