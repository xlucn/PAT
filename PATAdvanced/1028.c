#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int ID;
    char name[9];
    int grade;
} Student, *pStudent;

/* increasing by ID */
int cmp1(const void *a, const void *b)
{
    pStudent s1 = *(pStudent*)a, s2 = *(pStudent*)b;
    return s1->ID - s2->ID;
}

/* non decreasing by name, then increasing by ID */
int cmp2(const void *a, const void *b)
{
    pStudent s1 = *(pStudent*)a, s2 = *(pStudent*)b;
    if(strcmp(s1->name, s2->name))
        return strcmp(s1->name, s2->name);
    else
        return s1->ID - s2->ID;
}

/* non decreasing by grade, then increasing by ID */
int cmp3(const void *a, const void *b)
{
    pStudent s1 = *(pStudent*)a, s2 = *(pStudent*)b;
    if(s1->grade - s2->grade)
        return s1->grade - s2->grade;
    else
        return s1->ID - s2->ID;
}

int main()
{
    int N, C;
    Student buffer[100000] = {0};
    pStudent students[100000] = {0}, *s = students;

    scanf("%d %d", &N, &C);
    for(int i = 0; i < N; i++, s++)
    {
        /* use a new struct buffer */
        *s = buffer + i;
        scanf("%d %s %d", &(*s)->ID, (*s)->name, &(*s)->grade);
    }

    if(C == 1)  /* increasing ID */
        qsort(students, N, sizeof(pStudent), cmp1);
    else if(C == 2)  /* non-decreasing name */
        qsort(students, N, sizeof(pStudent), cmp2);
    else  /* C == 3, non-decreasing grade */
        qsort(students, N, sizeof(pStudent), cmp3);

    for(int i = 0; i < N; i++)
        printf("%06d %s %d\n", students[i]->ID,
                               students[i]->name,
                               students[i]->grade);

    return 0;
}
