#include <stdio.h>

int main()
{
    int N;
    char c;
    scanf("%d %c", &N, &c);

    for(int i = 0; i < (N + 1) / 2; i++)
    {
        for(int j = 0; j < N; j++)
        {
            if(i == 0 || i == (N - 1) / 2 || j == 0 || j == N - 1)
                putchar(c);
            else
                putchar(' ');
        }
        putchar('\n');
    }

    return 0;
}
