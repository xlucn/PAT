#include <stdio.h>
#include <stdlib.h>

typedef struct student{
    char ID[17];
    int test_seat;
    int exam_seat;
}Student, *pStudent;

int main()
{
    int N, M, test;
    Student students[1001] = {0};       /* N >= 1000 */
    pStudent sp[1001] = {0};

    scanf("%d", &N);
    for(int i = 0; i < N; i++)
    {
        pStudent s = students + i;      /* fill in the ith in the array */
        scanf("%s %d %d", s->ID, &s->test_seat, &s->exam_seat);
        sp[s->test_seat] = s;           /* set index same as test number */
    }

    scanf("%d", &M);
    for(int i = 0; i < M; i ++)
    {
        scanf("%d", &test);
        printf("%s %d\n", sp[test]->ID, sp[test]->exam_seat);
    }

    return 0;
}
