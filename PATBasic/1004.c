#include <stdio.h>
#include <string.h>

int main()
{
    int N;
    scanf("%d", &N);

    char maxname[11], minname[11], curname[11],
        maxid[11], minid[11], curid[11];
    int maxgrade = -1, mingrade = 101, curgrade;

    for(int i = 0; i < N; i++)
    {
        scanf("%s %s %d", curname, curid, &curgrade);

        if(curgrade > maxgrade)
        {
            strcpy(maxname, curname);
            strcpy(maxid, curid);
            maxgrade = curgrade;
        }
        if(curgrade < mingrade)
        {
            strcpy(minname, curname);
            strcpy(minid, curid);
            mingrade = curgrade;
        }
    }

    printf("%s %s\n%s %s", maxname, maxid, minname, minid);

    return 0;
}
