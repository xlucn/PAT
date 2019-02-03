#include <stdio.h>

#define ABS(X) ((X) >= 0 ? (X) : -(X))

int main()
{
    char c;
    int N, M;
    scanf("%d %c", &N, &c);

    for(M = 1; 2 * M * M - 1 <= N; M++) ;
    M--;   /* determine the size */

    /* draw the sandglass */
    for(int i = 0; i < 2 * M - 1; i ++)
    {
        for(int j = 0; j < M - 1 - ABS(M - 1 - i); j++)
            putchar(' ');
        for(int j = 0; j < 2 * ABS(M - 1 - i) + 1; j++)
            putchar(c);
        putchar('\n');
    }
    printf("%d", N - 2 * M * M + 1);

    return 0;
}
