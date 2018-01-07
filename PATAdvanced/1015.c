/**
 * 1015. Reversible Primes (20)
 * 
 * A reversible prime in any number system is a prime whose "reverse" in
 * that number system is also a prime. For example in the decimal system
 * 73 is a reversible prime because its reverse 37 is also a prime.
 * 
 * Now given any two positive integers N (< 105) and D (1 < D <= 10), 
 * you are supposed to tell if N is a reversible prime with radix D.
 * 
 * Input Specification:
 * 
 * The input file consists of several test cases. Each case occupies a 
 * line which contains two integers N and D. The input is finished by a 
 * negative N.
 * 
 * Output Specification:
 * 
 * For each test case, print in one line "Yes" if N is a reversible 
 * prime with radix D, or "No" if not.
 * 
 * Sample Input:
 * 73 10
 * 23 2
 * 23 10
 * -2
 * Sample Output:
 * Yes
 * Yes
 * No
 */

#include <stdio.h>

int iPrime(int N)
{
    if(N == 0 || N == 1)
        return 0;
    for(int i = 2; i * i <= N; i++)
        if(N % i == 0)
            return 0;
    return 1;
}

int Rev(int N, int D)
{
    int Nrev;
    for(Nrev = 0; N; N /= D)
    {    
        Nrev *= D; 
        Nrev += N % D;
    }
    return Nrev;
}

int main()
{
    int N, D;
    scanf("%d", &N);
    while(N >= 0)
    {
        scanf("%d", &D);
        puts(iPrime(N) && iPrime(Rev(N, D)) ? "Yes" : "No");
        scanf("%d", &N);
    }
    
    return 0;
}
