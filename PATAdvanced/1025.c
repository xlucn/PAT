#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* registration number, location nubmer, total score, final rank, local rank */
typedef struct {
    char reg[14];
    int loc, score, rank, lrank;
} Testee, *pTestee;

int cmp(const void *a, const void *b)
{
    pTestee p1 = *(pTestee*)a, p2 = *(pTestee*)b;
    if(p1->score != p2->score)
        return p2->score - p1->score;
    else
        return strcmp(p1->reg, p2->reg);
}

int main()
{
    int N, K;
    Testee buffers[100 * 300] = {0}, *q = buffers;
    pTestee testees[100 * 300] = {0}, *p = testees;

    scanf("%d", &N);
    for(int n = 0; n < N; n++)
    {
        /* read one test location */
        scanf("%d", &K);
        for(int k = 0; k < K; k++, p++)
        {
            *p = q++;  /* use a new cell */
            (*p)->loc = n + 1;
            scanf("%s %d", (*p)->reg, &(*p)->score);
        }

        /* sort the kth location sublist */
        qsort(p - K, K, sizeof(pTestee), cmp);

        /* get the local rank, i is the offset (we need left K cells of p) */
        int lrank = 1;
        pTestee *lp;
        (*(p - K))->lrank = lrank;  /* boundary special case */
        for(int i = 1; i < K; i++)
        {
            lp = p - K + i;
            if((*lp)->score != (*(lp - 1))->score)
                lrank = i + 1;
            (*lp)->lrank = lrank;
        }
    }

    /* sort the whole list */
    qsort(testees, p - testees, sizeof(pTestee), cmp);
    /* get the final rank */
    int rank = 1;
    pTestee *fp;
    (*testees)->rank = rank;
    for(int i = 1; testees + i < p; i++)
    {
        fp = testees + i;
        if((*fp)->score != (*(fp - 1))->score)
            rank = i + 1;
        (*fp)->rank = rank;
    }

    /* output */
    printf("%ld\n", p - testees);
    for(pTestee* i = testees; i < p; i++)
        printf("%s %d %d %d\n", (*i)->reg, (*i)->rank, (*i)->loc, (*i)->lrank);

    return 0;
}
