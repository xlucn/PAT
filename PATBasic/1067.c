#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main()
{
    int N;
    char c, correct[21], user[21];

    scanf("%s %d", correct, &N);
    while(getchar() != '\n');
    while(N--)
    {
        scanf("%20[^\n]", user); /* avoid overflow */
        c = ungetc(getchar(), stdin);
        if(!strcmp(user, "#") && c == '\n')
        {
            break;
        }
        else if(!strcmp(correct, user) && c == '\n')
        {
            puts("Welcome in");
            break;
        }
        else
        {
            printf("Wrong password: %s", user);
            while(putchar(getchar()) != '\n') ;
            if(!N)  puts("Account locked");
        }
    }

    return 0;
}
