#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char string[14];
    char level[2];  /* use 2-char array to avoid reading problems */
    int room;
    int date;
    int id;
    int score;
} Info;

int cmp(const void *a, const void *b)
{
    Info *ipa = (Info*)a;
    Info *ipb = (Info*)b;

    if(ipa->score != ipb->score)
        return ipb->score - ipa->score;
    return strcmp(ipa->string, ipb->string);
}

int main()
{
    int N, M, type, NAflag;
    Info info[10000];

    scanf("%d %d", &N, &M);
    for(int i = 0; i < N; i++)
    {
        scanf("%s %d", info[i].string,     &info[i].score);
        sscanf(info[i].string, "%1s%3d%6d%3d", info[i].level,
                &info[i].room,   &info[i].date,
                &info[i].id);
    }

    qsort(info, N, sizeof(Info), cmp);

    for(int i = 0; i < M; i++)
    {
        NAflag = 1;
        scanf("%d", &type);
        if(type == 1)
        {
            char level[2];
            scanf("%1s", level);
            printf("Case %d: %d %c\n", i + 1, type, level[0]);
            for(int j = 0; j < N; j++)
                if(info[j].level[0] == level[0])
                {
                    NAflag = 0;
                    printf("%c%03d%06d%03d %d\n", info[j].level[0],
                                  info[j].room,   info[j].date,
                                  info[j].id,     info[j].score);
                }
            if(NAflag)
                printf("NA\n");
        }
        else if(type == 2)
        {
            int room, sum = 0, count = 0;
            scanf("%d", &room);
            printf("Case %d: %d %d\n", i + 1, type, room);
            for(int j = 0; j < N; j++)
                if(info[j].room == room)
                {
                    NAflag = 0;
                    count++;
                    sum += info[j].score;
                }
            if(NAflag)
                printf("NA\n");
            else
                printf("%d %d\n", count, sum);
        }
        else if(type == 3)
        {
            int date, max = 0, rooms[1000] = {0};
            scanf("%d", &date);
            printf("Case %d: %d %06d\n", i + 1, type, date);
            for(int j = 0; j < N; j++)
                if(info[j].date == date)
                {
                    NAflag = 0;
                    rooms[info[j].room]++;
                    if(max < rooms[info[j].room])
                        max = rooms[info[j].room];
                }
            if(NAflag)
                printf("NA\n");
            else  /* print by count dec and room number inc */
                for(int c = max; c > 0; c--)
                    for(int r = 101; r < 1000; r++)
                        if(rooms[r] == c)
                            printf("%d %d\n", r, c);
        }
    }

    return 0;
}
