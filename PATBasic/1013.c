/**
 * 1013. 数素数 (20)
 * 
 * 令P_i表示第i个素数。现任给两个正整数M <= N <= 10^4，请输出P_M到P_N的所有素数。
 * 
 * 输入格式：
 * 
 * 输入在一行中给出M和N，其间以空格分隔。
 * 
 * 输出格式：
 * 
 * 输出从P_M到P_N的所有素数，每10个数字占1行，其间以空格分隔，但行末不得有多余空格。
 * 
 * 输入样例：
 * 5 27
 * 输出样例：
 * 11 13 17 19 23 29 31 37 41 43
 * 47 53 59 61 67 71 73 79 83 89
 * 97 101 103
 **/
#include <stdio.h>
int main()
{
    
    int M, N;
    scanf("%d %d", &M, &N);
    int primes[10000];
    
    for(int n = 2, count = 0; count < N; n++)
    {
        int iprime = 1;
        for(int j = 0; count > 0 && primes[j] * primes[j] <= n; j++)
            if(n % primes[j] == 0)
                iprime = 0;
        if(iprime) primes[count++] = n;
    }
    
    for(int i = M; i < N; i++)
    {
        printf("%d", primes[i - 1]);
        printf((i - M + 1) % 10 ? " " : "\n");
    }
    printf("%d", primes[N - 1]);
    
    return 0;
}
