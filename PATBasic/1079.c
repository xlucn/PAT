#include <stdio.h>
#include <string.h>

int isPalindromicNumber(char n[])
{
    int len = strlen(n);
    for(int i = 0; i < len / 2; i++)
        if(n[i] != n[len - i - 1])
            return 0;
    return 1;
}

void addBtoA(char a[], char b[])
{
    /* Assume length of a and b are the same */
    int len = strlen(a), sum, carry = 0;
    for(int i = len - 1; i >= 0; i --)
    {
        sum = a[i] - '0' + b[i] - '0' + carry;
        a[i] = sum % 10 + '0';
        carry = sum / 10;
    }
    if(carry) /* Length of a + b is larger than a or b */
    {
        memmove(a + 1, a, len + 1); /* Shift to right by 1 */
        a[0] = carry + '0';         /* Add the carry to beginning */
    }
}

void reverseAtoB(char a[], char b[])
{
    int len = strlen(a);
    for(int i = 0; i < len; i++)
        b[len - i - 1] = a[i];
}

int main()
{
    int i;
    char a[1011] = {0}, b[1011] = {0};

    scanf("%s", a);
    for (i = 0; i < 10 && !isPalindromicNumber(a); i++)
    {
        reverseAtoB(a, b);
        printf("%s + %s = ", a, b);
        addBtoA(a, b);
        printf("%s\n", a);
    }

    if(i == 10)
        printf("Not found in 10 iterations.");
    else
        printf("%s is a palindromic number.", a);

    return 0;
}
