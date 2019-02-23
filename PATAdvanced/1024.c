#include <stdio.h>
#include <string.h>

int isPalindromic(char n[])
{
    int len = strlen(n);
    for(int i = 0; i < len / 2; i++)
        if(n[i] != n[len - i - 1])
            return 0;
    return 1;
}

char* reverse(char n[])
{
    char temp;
    int len = strlen(n);
    for(int i = 0; i < len / 2; i++)
    {
        temp = n[i];
        n[i] = n[len - i - 1];
        n[len - i - 1] = temp;
    }
    return n;
}

/* only works when a and b are of the same length */
void addAtoB(char a[], char b[])
{
    int l, s = 0, len = strlen(a);

    for(int i = 0; i < len; i++)
    {
        s += (a[i] - '0') + (b[i] - '0');
        l = s / 10;
        s %= 10;
        b[i] = s + '0';

        s = l;
    }

    if(s)
        b[len] = s + '0';
}

int main()
{
    int K, steps;
    char s1[100] = {0}, s2[100] = {0}, *n = s1, *m = s2;

    scanf("%s %d", n, &K);
    reverse(n);

    for(steps = 0; steps < K && !isPalindromic(n); steps++)
    {
        /* change 'm' into reverse of 'n' */
        strncpy(m, n, 100);
        reverse(m);
        /* add n and reversed n, and keep the result in n */
        addAtoB(m, n);
    }

    printf("%s\n%d", reverse(n), steps);

    return 0;
}
