#include <stdio.h>

/* About special characters, see:
 * https://en.wikipedia.org/wiki/Variable-width_encoding */

int main()
{
    int N, m[5];
    char c, symbols[3][10][5] = {0};

    for(int symbol = 0; symbol < 3; symbol++)
        for(int index = 0; (c = getchar()) != '\n'; )
            if(c == '[') scanf("%[^]]", symbols[symbol][index++]);

    scanf("%d", &N);
    for(int i = 0; i < N; i++)
    {
        for(int i = 0; i < 5; i++)  scanf("%d", m + i);
        if(m[0] > 0 && m[0] <= 10 && *symbols[0][--m[0]]
        && m[1] > 0 && m[1] <= 10 && *symbols[1][--m[1]]
        && m[2] > 0 && m[2] <= 10 && *symbols[2][--m[2]]
        && m[3] > 0 && m[3] <= 10 && *symbols[1][--m[3]]
        && m[4] > 0 && m[4] <= 10 && *symbols[0][--m[4]])
            printf("%s(%s%s%s)%s\n", symbols[0][m[0]], symbols[1][m[1]],
                   symbols[2][m[2]], symbols[1][m[3]], symbols[0][m[4]]);
        else
            puts("Are you kidding me? @\\/@");
    }

    return 0;
}
