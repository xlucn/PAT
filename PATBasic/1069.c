#include <stdio.h>
#include <string.h>

int main()
{
    char s[1000][21] = {{0}}, line[21];
    int M, N, S, m, count = 0, r = 0;

    scanf("%d %d %d", &M, &N, &S);

    for(m = 0, S--; m < M; m++)
    {
        scanf("%s", line);
        if(m == S + count * N + r)
        {
            int flag = 1;
            for(int i = 0; i < count && flag; i++)
                if(!strcmp(s[i], line))
                {
                    flag = 0;
                    r++;
                    break;
                }
            if(flag)
                strcpy(s[count++], line);
        }
    }

    for(int i = 0; i < count; i++)
        printf("%s\n", s[i]);
    if(!count)
        printf("Keep going...");

    return 0;
}
