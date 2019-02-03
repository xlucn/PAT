#include <stdio.h>

typedef struct Student{ int ID, score[4]; } Student;

int main()
{
    /* scores array stores the number of students of any score */
    int N, M, ID, scores[4][102] = {{0}};

    /* Setting a score of 101 is to make it easy to calculate rank */
    scores[0][101] = scores[1][101] = scores[2][101] = scores[3][101] = 1;
    Student students[2000];

    scanf("%d %d", &N, &M);
    for(int i = 0; i < N; i++)
    {   /* record all the scores for every student: A, C, M, E */
        Student *s = students + i;
        scanf("%d %d %d %d", &s->ID, &s->score[1], &s->score[2], &s->score[3]);
        s->score[0] = (s->score[1] + s->score[2] + s->score[3] + 1) / 3;
        for(int j = 0; j < 4; j++)                         /* +1 for rounding */
            scores[j][s->score[j]]++;       /* record how many got this score */
    }

    for(int i = 0; i < M; i++)
    {
        int max = 3, ranks[4] = {0}, stu;

        scanf("%d", &ID);
        for(stu = 0; stu < N && students[stu].ID != ID; stu++) ;      /* find */
        if(stu == N) { puts("N/A"); continue;}

        for(int j = 3; j >= 0; j--)
        {   /* calculate the rank: sum the counts from score + 1 to 101 */
            /* e.g. score 100 will have rank 1, since scores[101] is 1 */
            for(int score = 100; score >= students[stu].score[j]; score--)
                ranks[j] += scores[j][score + 1];
            if(ranks[j] <= ranks[max]) /* The best rank with highest priority */
                max = j;
        }
        printf("%d %c\n", ranks[max], "ACME"[max]);
    }
}
