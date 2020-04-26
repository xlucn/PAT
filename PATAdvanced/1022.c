#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct book {
    int ID;
    char title[81];
    char author[81];
    char keywords[5][11];
    char publisher[81];
    int year;
} Book;

int cmpbyid(const void *a, const void *b)
{
    return (*(Book**)a)->ID - (*(Book**)b)->ID;
}

int main()
{
    int N, M, count, query_type, query_year;
    char space, query_str[81];
    Book books[10000] = {0}, *p, *booksbyid[10000];

    scanf("%d", &N);
    for(int i = 0; i < N; i++)
    {
        p = booksbyid[i] = books + i;
        scanf("%d%c", &p->ID, &space);
        scanf("%[^\n]%c", p->title, &space);
        scanf("%[^\n]%c", p->author, &space);
        space = '\0';
        for(int k = 0; space != '\n'; k++)
            scanf("%s%c", p->keywords[k], &space);
        scanf("%[^\n]%c", p->publisher, &space);
        scanf("%d", &p->year);
    }

    qsort(booksbyid, N, sizeof(Book*), cmpbyid);

    scanf("%d", &M);
    for(int i = 0; i < M; i ++)
    {
        count = 0;
        scanf("%d: %[^\n]%c", &query_type, query_str, &space);
        printf("%d: %s\n", query_type, query_str);
        for(int j = 0; j < N; j++)
        {
            p = booksbyid[j];
            switch(query_type)
            {
                case 1:
                    if(strcmp(query_str, p->title) == 0)
                    {
                        printf("%07d\n", p->ID);
                        count ++;
                    }
                    break;
                case 2:
                    if(strcmp(query_str, p->author) == 0)
                    {
                        printf("%07d\n", p->ID);
                        count ++;
                    }
                    break;
                case 3:
                    for(int k = 0; k < 5; k ++)
                        if(strcmp(query_str, p->keywords[k]) == 0)
                        {
                            printf("%07d\n", p->ID);
                            count ++;
                        }
                    break;
                case 4:
                    if(strcmp(query_str, p->publisher) == 0)
                    {
                        printf("%07d\n", p->ID);
                        count ++;
                    }
                    break;
                case 5:
                    sscanf(query_str, "%d", &query_year);
                    if(query_year == p->year)
                    {
                        printf("%07d\n", p->ID);
                        count ++;
                    }
                    break;
                default:
                    break;
            }
        }
        if(count == 0) puts("Not Found");
    }

    return 0;
}
