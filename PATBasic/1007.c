/**
 * 1007. 素数对猜想
 * 让我们定义 dn 为：dn = pn+1 - pn，其中 pi 是第i个素数。显然有 d1=1 且对于n>1有
 *  dn 是偶数。“素数对猜想”认为“存在无穷多对相邻且差为2的素数”。
 * 
 * 现给定任意正整数N (< 10^5)，请计算不超过N的满足猜想的素数对的个数。
 * 
 * 输入格式：每个测试输入包含1个测试用例，给出正整数N。
 * 
 * 输出格式：每个测试用例的输出占一行，不超过N的满足猜想的素数对的个数。
 * 
 * 输入样例：
 * 20
 * 输出样例：
 * 4
 **/
#include <stdio.h>
int main()
{
    int N;
    scanf("%d", &N);
    /* record primality of three successive numbers starting from 2, 3, 4 */
    int iPrimeMinus2 = 1, iPrimeMinus1 = 1, iPrime;
    int primes[100] = {2, 3};   /* record the prime numbers before sqrt(10^5) */
    int twincount = 0;          /* count of twin primes */
    int primecount = 2;         /* count of prime numbers */
    
    for(int i = 4; i <= N; i++)
    {
        iPrime = 1;
        /* test if i is a prime number */
        for(int j = 0; iPrime && primes[j] * primes[j] <= i; j++) 
            if(i % primes[j] == 0)
                iPrime = 0;
        /* i is a prime number, record */
        if(iPrime)
        {
            if(primecount < 100)    primes[primecount++] = i;
            if(iPrimeMinus2 == 1)   twincount++;    /* a prime pair found */
        }
        /* shift the flags */
        iPrimeMinus2 = iPrimeMinus1;
        iPrimeMinus1 = iPrime;
    }
    printf("%d", twincount);
    
    return 0;
}
