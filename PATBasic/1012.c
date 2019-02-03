#include <stdio.h>

int main()
{
    int count;
    int A1 = 0, A2 = 0, A3 = 0, A4 = 0, A5 = 0;
    int A2flag = 0, A4count = 0;

    scanf("%d", &count);
    for(int i = 0, n; i < count; i++)
    {
        scanf("%d", &n);
        switch(n % 5)
        {
            case 0: A1 += n % 2 ? 0 : n;                                break;
            case 1: A2flag = A2flag == 1 ? -1 : 1; A2 += A2flag * n;    break;
            case 2: A3 ++;                                              break;
            case 3: A4 += n; A4count ++;                                break;
            case 4: A5 = n > A5? n : A5;                                break;
        }
    }

    if(A1 == 0)     printf("N ");   else printf("%d ", A1);
    if(A2flag == 0) printf("N ");   else printf("%d ", A2);
    if(A3 == 0)     printf("N ");   else printf("%d ", A3);
    if(A4 == 0)     printf("N ");   else printf("%.1f ", A4 * 1.0 / A4count);
    if(A5 == 0)     printf("N");    else printf("%d", A5);

    return 0;
}
