#include <stdio.h>
#include <string.h>

int main()
{
    int N, HH, MM, SS;
    int firsttime = 86400, lasttime = -1, time;
    char firstname[16], lastname[16], name[16];

    scanf("%d", &N);
    for(int i = 0; i < N; i++)
    {
        scanf("%s %d:%d:%d", name, &HH, &MM, &SS);
        time = (HH * 60 + MM) * 60 + SS;
        if(time < firsttime)
        {
            firsttime = time;
            strcpy(firstname, name);
        }

        scanf("%d:%d:%d", &HH, &MM, &SS);
        time = (HH * 60 + MM) * 60 + SS;
        if(time > lasttime)
        {
            lasttime = time;
            strcpy(lastname, name);
        }
    }

    printf("%s %s", firstname, lastname);

    return 0;
}
