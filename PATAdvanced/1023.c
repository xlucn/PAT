#include <stdio.h>
#include <string.h>

void reverse(char n[])
{
    char temp;
    int len = strlen(n);
    for(int i = 0; i < len / 2; i++)
    {
        temp = n[i];
        n[i] = n[len - i - 1];
        n[len - i - 1] = temp;
    }
}

void doubleLargeNumber(char n[], char n2[])
{
    int l, s = 0, len = strlen(n);

    for(int i = 0; i < len; i++)
    {
        s += 2 * (n[i] - '0');
        l = s / 10;
        s %= 10;
        n2[i] = s + '0';

        s = l;
    }

    if(s)
        n2[len] = s + '0';
}

int main()
{
    char N[22] = {0}, N2[22] = {0};
    int diffcount[10] = {0};

    scanf("%s", N);
    /* store number in reverse order */
    reverse(N);
    doubleLargeNumber(N, N2);
    /* reverse back (just need N2) for printing */
    reverse(N2);

    /* Count the difference of counts of digits 0-9 */
    for(int i = 0; i < strlen(N); i++)
        diffcount[N[i] - '0']++;
    for(int i = 0; i < strlen(N2); i++)
        diffcount[N2[i] - '0']--;

    /* Check */
    for(int i = 0; i < 10; i++)
        if(diffcount[i])
        {
            printf("No\n%s", N2);
            return 0;
        }
    printf("Yes\n%s", N2);

    return 0;
}
