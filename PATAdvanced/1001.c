/**
 * 1001. A+B Format (20)
 * 
 * Calculate a + b and output the sum in standard format -- that is, the digits 
 * must be separated into groups of three by commas (unless there are less than 
 * four digits).
 * 
 * Input
 * 
 * Each input file contains one test case. Each case contains a pair of integers
 * a and b where -1000000 <= a, b <= 1000000. The numbers are separated by a 
 * space.
 * 
 * Output
 * 
 * For each test case, you should output the sum of a and b in one line. The sum
 * must be written in the standard format.
 * 
 * Sample Input
 * -1000000 9
 * Sample Output
 * -999,991
 */

#include <stdio.h>
int main()
{
    int a, b, sum, count, dec;
    scanf("%d%d", &a, &b);
    sum = a + b;
    
    if(sum == 0) putchar('0');
    if(sum < 0) { putchar('-'); sum = -sum; }
    
    for(count = 0, dec = 1; sum >= dec; count++, dec *= 10) ;
    
    for(int c = count; c; c--, sum %= dec)
    {
        if(c < count && c % 3 == 0 && c) putchar(',');
        putchar('0' + sum / (dec /= 10));
    }
    
    return 0;
}
