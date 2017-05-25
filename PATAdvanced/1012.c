/**
 * 1012. The Best Rank (25)
 * 
 * To evaluate the performance of our first year CS majored students, we 
 * consider their grades of three courses only: C - C Programming Language, M - 
 * Mathematics (Calculus or Linear Algebra), and E - English. At the mean time, 
 * we encourage students by emphasizing on their best ranks -- that is, among 
 * the four ranks with respect to the three courses and the average grade, we 
 * print the best rank for each student.
 * 
 * For example, The grades of C, M, E and A - Average of 4 students are given as
 * the following:
 * 
 * StudentID  C  M  E  A
 * 310101     98 85 88 90
 * 310102     70 95 88 84
 * 310103     82 87 94 88
 * 310104     91 91 91 91
 * Then the best ranks for all the students are No.1 since the 1st one has done 
 * the best in C Programming Language, while the 2nd one in Mathematics, the 3rd
 * one in English, and the last one in average.
 * 
 * Input
 * 
 * Each input file contains one test case. Each case starts with a line 
 * containing 2 numbers N and M (<=2000), which are the total number of 
 * students, and the number of students who would check their ranks, 
 * respectively. Then N lines follow, each contains a student ID which is a 
 * string of 6 digits, followed by the three integer grades (in the range of 
 * [0, 100]) of that student in the order of C, M and E. Then there are M lines,
 * each containing a student ID.
 * 
 * Output
 * 
 * For each of the M students, print in one line the best rank for him/her, and 
 * the symbol of the corresponding rank, separated by a space.
 * 
 * The priorities of the ranking methods are ordered as A > C > M > E. Hence if 
 * there are two or more ways for a student to obtain the same best rank, output
 * the one with the highest priority.
 * 
 * If a student is not on the grading list, simply output "N/A".
 * 
 * Sample Input
 * 5 6
 * 310101 98 85 88
 * 310102 70 95 88
 * 310103 82 87 94
 * 310104 91 91 91
 * 310105 85 90 90
 * 310101
 * 310102
 * 310103
 * 310104
 * 310105
 * 999999
 * Sample Output
 * 1 C
 * 1 M
 * 1 E
 * 1 A
 * 3 A
 * N/A
 */

#include <stdio.h>

typedef struct Student{ int ID, score[4]; } Student;

int main()
{
    int N, M, ID, scores[4][102] = {{0}};
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
        {   /* calculate the rank = sum the count from 101 to score + 1 */
            for(int score = 100; score >= students[stu].score[j]; score--)
                ranks[j] += scores[j][score + 1];
            if(ranks[j] <= ranks[max]) max = j;
        }
        printf("%d %c\n", ranks[max], "ACME"[max]);
    }
}
