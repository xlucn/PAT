#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

typedef struct {char id[7], school[7]; int score; } Student;
typedef struct {char name[7]; int score, num; } School;

int cmp_school(const void *a, const void *b)
{
    return strcmp((*(Student**)a)->school, (*(Student**)b)->school);
}

int cmp_sort_all(const void *a, const void *b)
{
    School *s1 = *(School**)a, *s2 = *(School**)b;
    if(s1->score - s2->score)
        return s2->score - s1->score;
    else if(s1->num - s2->num)
        return s1->num - s2->num;
    else
        return strcmp(s1->name, s2->name);
}

int main()
{
    int N, M = 0, num = 0;
    double total_score = 0;
    Student students[100001] = {0}, *stu[100001] = {0};
    School schools[100001] = {0}, *sch[100001] = {0};

    /* Read into an array */
    scanf("%d", &N);
    for(int i = 0; i < N; i++)
    {
        stu[i] = students + i;  /* Initialize pointer array */
        scanf("%s %d %s", stu[i]->id, &stu[i]->score, stu[i]->school);
        for(char *s = stu[i]->school; *s; s++)
            *s = tolower(*s);   /* Change to lower case */
    }

    /* Sort by school name */
    qsort(stu, N, sizeof(Student*), cmp_school);

    /* Calculate, count and record */
    for(Student **p = stu; p < stu + N; p++)
    {
        switch((*p)->id[0]) /* Calculate total score */
        {
            case 'B': total_score += (*p)->score / 1.5; break;
            case 'A': total_score += (*p)->score;       break;
            case 'T': total_score += (*p)->score * 1.5; break;
        }
        num++;              /* Count number of students */
        if(!*(p + 1) || strcmp((*p)->school, (*(p + 1))->school))
        {                   /* Record into an array */
            sch[M] = schools + M;
            strcpy(sch[M]->name, (*p)->school);
            sch[M]->score = (int)total_score;
            sch[M]->num = num;
            total_score = 0, num = 0, M++;  /* Reset and increament counter */
        }
    }

    /* Sort according to rules */
    qsort(sch, M, sizeof(School*), cmp_sort_all);

    /* Print result */
    printf("%d\n", M);
    for(int i = 0, ranking = 0; i < M; i++)
    {
        if(i > 0 && sch[i]->score < sch[i - 1]->score)
            ranking = i;
        printf("%d %s %d %d\n", ranking + 1, sch[i]->name,
               sch[i]->score, sch[i]->num);
    }

    return 0;
}
