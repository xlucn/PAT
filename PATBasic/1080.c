#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char name[21];
    int programming;
    int midterm;
    int finalexam;
    int total_mark;
} Score;

int cmp_sort_total(const void *a, const void *b)
{
    Score *s1 = *(Score**)a, *s2 = *(Score**)b;
    if(s2->total_mark - s1->total_mark)
        return s2->total_mark - s1->total_mark;
    return strcmp(s1->name, s2->name);
}

int cmp_sort_name(const void *a, const void *b)
{
    Score *s1 = *(Score**)a, *s2 = *(Score**)b;
    return strcmp(s1->name, s2->name);
}

int cmp_bsearch(const void *strptr, const void *scoreptr)
{
    Score *s = *(Score**)scoreptr;
    char *name = (char*)strptr;
    return strcmp(name, s->name);
}

int main()
{
    int P, M, N;
    scanf("%d %d %d", &P, &M, &N);

    int score, count = 0;
    char name[21];
    Score buf[10000], *scores[10000] = {0}, *s = buf;

    for(int i = 0; i < P; i++)  /* Read programming grade */
    {
        scanf("%s %d", name, &score);
        if(score >= 200)        /* Only record if score >= 200 */
        {
            strcpy(s->name, name);
            s->programming = score;
            s->midterm = -1;
            s->finalexam = -1;
            s->total_mark = 0;
            scores[count++] = s++;
        }
    }

    /* Sort by name for future searchings using bsearch */
    qsort(scores, count, sizeof(Score*), cmp_sort_name);

    void *result;
    for(int i = 0; i < M; i++)  /* Read midterm grade */
    {
        scanf("%s %d", name, &score);
        result = bsearch(name, scores, count, sizeof(Score*), cmp_bsearch);
        if(result != NULL)      /* If name is in the list, then record */
            (*(Score**)result)->midterm = score;
    }

    for(int i = 0; i < N; i++)  /* Read final exam grade */
    {
        scanf("%s %d", name, &score);
        result = bsearch(name, scores, count, sizeof(Score*), cmp_bsearch);
        if(result != NULL)
        {
            s = *(Score**)result;
            s->finalexam = score;

            /* Calculate total mark */
            if(s->finalexam >= s->midterm)      /* final exam grade higher */
                s->total_mark = s->finalexam;
            else                                /* midterm grade higher */
                s->total_mark = 0.6 * s->finalexam + 0.4 * s->midterm + 0.5;
        }
    }

    /* Sort by total mark */
    qsort(scores, count, sizeof(Score*), cmp_sort_total);

    for(Score **p = scores; *p && (*p)->total_mark >= 60; p++)
        printf("%s %d %d %d %d\n", (*p)->name, (*p)->programming,
               (*p)->midterm, (*p)->finalexam, (*p)->total_mark);

    return 0;
}
