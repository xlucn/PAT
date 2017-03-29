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
#include <math.h>
int main()
{
    int N;
    scanf("%d", &N);
    int paircount = 0;
    /* record three successive numbers if they are prime numbers, start 
    from 2, 3, 4 */
    int iPrimeMinus2 = 1, iPrimeMinus1 = 1, iPrime;
    /* record the prime numbers before 350, which is lt sqrt(100000) */
    int primes[100] = {2, 3};
    int primecount = 2;
    
    for (int i = 4; i <= N; i++)
    {
        iPrime = 1;
        /* test if i is a prime number */
        int sqrt_i = (int)sqrt(i);
        for(int j = 0; primes[j] <= sqrt_i && j < primecount; j++)
        {
            /* only need to test on prime numbers before sqrt(i) */
            if(i % primes[j] == 0)
            {
                iPrime = 0;
            }
        }
        if(iPrime == 1)
        {
            if(primecount < 100)
            {
                primes[primecount] = i;
            }
            primecount++;
            if(iPrimeMinus2 == 1) /* a prime pair */
            {
                paircount++;
            }
        }
        /* shift the flags */
        iPrimeMinus2 = iPrimeMinus1;
        iPrimeMinus1 = iPrime;
    }
    printf("%d", paircount);
    
    return 0;
}
