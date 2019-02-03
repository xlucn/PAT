#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student{
    char name[9];
    int height;
}student, *Student;

int cmp(const void *a, const void *b)
{
    Student s1 = *(Student*)a;
    Student s2 = *(Student*)b;
    if(s1->height != s2->height)
        return s2->height - s1->height;
    return strcmp(s1->name, s2->name);
}

/**
 * Print one row
 * Return the address of the beginning of next line
 **/
Student *printrow(Student *s, int num)
{
    for(int i = num / 2 * 2 - 1; i > 0; i -= 2)  /* the left half */
        printf("%s ", s[i]->name);
    for(int i = 0; i < num; i += 2)              /* the right half */
        printf("%s%c", s[i]->name, i + 2 < num ? ' ' : '\n');
    return s + num;
}

int main()
{
    /* read and sort data */
    int N, K;
    student students[10000] = {0};
    Student sp[10000] = {0}, *p = sp;

    scanf("%d %d", &N, &K);
    for(int i = 0; i < N; i++)
    {
        sp[i] = students + i;
        scanf("%s %d", sp[i]->name, &sp[i]->height);
    }

    qsort(sp, N, sizeof(Student), cmp);

    /* print */
    p = printrow(p, N - N / K * (K - 1));   /* the last row */
    while(p < sp + N)
        p = printrow(p, N / K);

    return 0;
}
