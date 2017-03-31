/**
 * 1017. A除以B (20)
 * 
 * 本题要求计算A/B，其中A是不超过1000位的正整数，B是1位正整数。你需要输出商数Q和
 * 余数R，使得A = B * Q + R成立。
 * 
 * 输入格式：
 * 
 * 输入在1行中依次给出A和B，中间以1空格分隔。
 * 
 * 输出格式：
 * 
 * 在1行中依次输出Q和R，中间以1空格分隔。
 * 
 * 输入样例：
 * 123456789050987654321 7
 * 输出样例：
 * 17636684150141093474 3
 **/
#include <stdio.h>
int main()
{
    /* read 2 digits from highest digit of A, do manual division, get the quotient
     and remainder. Read one more digit, combine this with the last remainder to
    get a new 2-digits number. Do this until read to the end of A */
    int B;
    char A[1001];
    
    /* read A and B */
    int count = 0;
    char c;
    while((c = getchar()) != ' ')
    {
        A[count++] = c;
    }
    A[count] = '\0';
    B = getchar() - '0';
    
    /* calculate */
    /* In consideration of reusability, the results are stored in A and B
    instead of printed out on-the-fly */
    int tens, unit, twodigit;
    int remainder = 0;
    for(int i = 0; A[i]; i ++)
    {
        tens = remainder;
        unit = A[i] - '0';
        twodigit = tens * 10 + unit;
        A[i] = twodigit / B + '0';
        remainder = twodigit % B;
    }
    B = remainder;
    
    /* print */
    if(A[0] == '0' && A[1] != '\0')
        printf("%s", A + 1);
    else
        printf("%s", A);
    printf(" %d", B);
    
    return 0;
}
