#include <stdio.h>

int main()
{
    int N, b, c, isPalindromicNumber = 1, b_base[30] = {0};

    scanf("%d %d", &N, &b);

    /* Calculate N in b-base */
    for(c = 0; N; N /= b, c++)
        b_base[c] = N % b;

    /* Check if it is palindromic number */
    for(int i = 0; i < c / 2; i++)
        if(b_base[i] != b_base[c - i - 1])
            isPalindromicNumber = 0;
    puts(isPalindromicNumber ? "Yes" : "No");

    if(c == 0)
        printf("0");
    /* Reversely printing is the correct order */
    while(c--)
        printf("%d%c", b_base[c], c ? ' ' : '\0');

    return 0;
}
