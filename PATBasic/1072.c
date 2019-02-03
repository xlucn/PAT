#include <stdio.h>

int main()
{
    int N, M, K, SNlist[10], SNtarget;
    char name[5];

    scanf("%d %d", &N, &M);
    for(int i = 0; i < M; i ++)
        scanf("%d", SNlist + i);

    int flag, student_total = 0, item_total = 0;
    for(int i = 0; i < N; i ++)
    {
        flag = 0;
        scanf("%s %d", name, &K);
        for(int i = 0; i < K; i++)
        {
            scanf("%d", &SNtarget);
            for(int i = 0 ; i < M; i ++)
            {
                if(SNtarget == SNlist[i])
                {
                    if(flag == 0)
                    {
                        flag = 1;
                        student_total++;
                        printf("%s:", name);
                    }
                    item_total++;
                    printf(" %04d", SNtarget);
                }
            }
        }
        if(flag) printf("\n");
   }
    printf("%d %d", student_total, item_total);

    return 0;
}
