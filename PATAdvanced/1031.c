#include <stdio.h>
#include <string.h>

int main()
{
    int N, n1, n2, e;
    char string[81];

    scanf("%s", string);
    N = strlen(string);

    /* the math is: n1 = n3; n2 >= n1; n2 + 2n1 = N + 2 */
    e = ((N % 3) + 2) % 3;
    n1 = (N + 2 - e) / 3;
    n2 = n1 + e;

    for(int i = 0; i < n1; i++)
    {
        putchar(string[i]);
        for(int j = 0; j < n2 - 2; j++)
            if(i < n1 - 1)
                putchar(' ');
            else
                putchar(string[n1 + j]);
        putchar(string[N - 1 - i]);
        putchar('\n');
    }

    return 0;
}
