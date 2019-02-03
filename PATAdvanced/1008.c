#include <stdio.h>
int main()
{
    int N, time, cur, pre;

    scanf("%d", &N);
    for(pre = 0, time = 0; N--; pre = cur)
    {
        scanf("%d", &cur);
        if(cur > pre)   time += (cur - pre) * 6 + 5;
        else            time += (pre - cur) * 4 + 5;
    }

    printf("%d", time);

    return 0;
}
