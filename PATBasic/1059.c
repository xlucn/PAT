#include <stdio.h>

int isPrime(int n)
{
    if(n == 1) return 0;
    for(int i = 2; i * i <= n; i++)
        if(n % i == 0)
            return 0;
    return 1;
}

int main()
{
    int award[10000] = {0}, N, K, ID;

    scanf("%d", &N);
    for(int i = 0; i < N; i++)
    {
        scanf("%d", &ID);
        if(i == 0)              award[ID] = 1;
        else if(isPrime(i + 1)) award[ID] = 2;
        else                    award[ID] = 3;
    }
    scanf("%d", &K);
    for(int i = 0; i < K; i++)
    {
        scanf("%d", &ID);
        switch(award[ID])
        {
            case 0: printf("%04d: Are you kidding?\n", ID);               break;
            case 1: printf("%04d: Mystery Award\n", ID);  award[ID] = 4;  break;
            case 2: printf("%04d: Minion\n", ID);         award[ID] = 4;  break;
            case 3: printf("%04d: Chocolate\n", ID);      award[ID] = 4;  break;
            case 4: printf("%04d: Checked\n", ID);                        break;
        }
    }

    return 0;
}
