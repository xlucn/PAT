#include <stdio.h>

int main()
{
    char c;
    float odd, maxodd, maxprofit = 1;

    for(int i = 0; i < 3; i++)
    {
        maxodd = 0;
        for(int j = 0; j < 3; j++)
        {
            scanf("%f", &odd);
            if(maxodd < odd)
            {
                maxodd = odd;
                c = "WTL"[j];
            }
        }
        printf("%c ", c);
        maxprofit *= maxodd;
    }
    printf("%.2f", (maxprofit * 0.65 - 1) * 2);

    return 0;
}
