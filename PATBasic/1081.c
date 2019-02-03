#include <stdio.h>
#include <ctype.h>

int main()
{
    char c;
    int N, count, num_digit, num_alpha, num_else;

    scanf("%d", &N);
    while(getchar() == '\n');
    for(int i = 0; i < N; i++)
    {
        num_digit = num_alpha = num_else = 0;
        for(count = 0; (c = getchar()) != '\n'; count++)
        {
            if(isdigit(c))      num_digit++;
            else if(isalpha(c)) num_alpha++;
            else if(c != '.')   num_else++;
        }
        if(count < 6)                    puts("Your password is tai duan le.");
        else if(num_else)                puts("Your password is tai luan le.");
        else if(num_alpha && !num_digit) puts("Your password needs shu zi.");
        else if(num_digit && !num_alpha) puts("Your password needs zi mu.");
        else                             puts("Your password is wan mei.");
    }

    return 0;
}
