/**
 * 10-排序5 PAT Judge   (25分)
 * The ranklist of PAT is generated from the status list, which shows the 
 * scores of the submittions. This time you are supposed to generate the 
 * ranklist for PAT.
 * 
 * Input Specification:
 * Each input file contains one test case. For each case, the first line 
 * contains 3 positive integers, N (≤10^4), the total number of users, K (≤5), 
 * the total number of problems, and M (≤10^5), the total number of submittions.
 * It is then assumed that the user id's are 5-digit numbers from 00001 to N, 
 * and the problem id's are from 1 to K. The next line contains K positive 
 * integers p[i] (i=1, ..., K), where p[i] corresponds to the full mark of the 
 * i-th problem. Then M lines follow, each gives the information of a submittion
 * in the following format:
 * user_id problem_id partial_score_obtained
 * where partial_score_obtained is either -1 if the submittion cannot even pass 
 * the compiler, or is an integer in the range [0, p[problem_id]]. All the 
 * numbers in a line are separated by a space.
 * 
 * Output Specification:
 * For each test case, you are supposed to output the ranklist in the following 
 * format:
 * rank user_id total_score s[1] ... s[K]
 * where rank is calculated according to the total_score, and all the users 
 * with the same total_score obtain the same rank; and s[i] is the partial 
 * score obtained for the i-th problem. If a user has never submitted a 
 * solution for a problem, then "-" must be printed at the corresponding 
 * position. If a user has submitted several solutions to solve one problem, 
 * then the highest score will be counted.
 * The ranklist must be printed in non-decreasing order of the ranks. For those 
 * who have the same rank, users must be sorted in nonincreasing order according
 * to the number of perfectly solved problems. And if there is still a tie, then
 * they must be printed in increasing order of their id's. For those who has 
 * never submitted any solution that can pass the compiler, or has never 
 * submitted any solution, they must NOT be shown on the ranklist. It is 
 * guaranteed that at least one user can be shown on the ranklist.
 * 
 * Sample Input:
7 4 20
20 25 25 30
00002 2 12
00007 4 17
00005 1 19
00007 2 25
00005 1 20
00002 2 2
00005 1 15
00001 1 18
00004 3 25
00002 2 25
00005 3 22
00006 4 -1
00001 2 18
00002 1 20
00004 1 15
00002 4 18
00001 3 4
00001 4 2
00005 2 -1
00004 2 0
 * 
 * 
 * Sample Output:
 * 1 00002 63 20 25 - 18
 * 2 00005 42 20 0 22 -
 * 2 00007 42 - 25 - 17
 * 2 00001 42 18 18 4 2
 * 5 00004 40 15 0 25 -
 */

#include <stdio.h>
#include <stdlib.h>

#define max(A,B) ((A)>(B)?(A):(B))

typedef struct _info{
    int id;
    int tot;
    int full;
    int pass;
    int score[5];
}*info;

int cmp(const void* i1, const void* i2)
{
    info s1 = *(info*)i1;
    info s2 = *(info*)i2;
    
    if(s1->tot != s2->tot)
    {
        return s1->tot > s2->tot ? -1 : 1;
    }
    if(s1->full != s2->full)
    {
        return s1->full > s2->full ? -1 : 1;
    }
    return s1->id > s2->id ? 1 : -1;
}

int main()
{
    int N, K, M;
    int fullscore[5];
    info infos[10000];
    scanf("%d %d %d", &N, &K, &M);
    /* initialize */
    for(int i = 0; i < N; i++)
    {
        infos[i] = malloc(sizeof(struct _info));
        infos[i]->id = i;
        infos[i]->tot = 0;
        infos[i]->full = 0;
        infos[i]->pass = 0;
        for(int j = 0; j < 5; j++)
        {
            infos[i]->score[j] = -1;/* haven't submitted */
        }
    }
    /* read the full score of each problem */
    for(int i = 0; i < K; i ++)
    {
        scanf("%d", &fullscore[i]);
    }
    /* read submittion infomation */
    for(int i = 0, id, index, score; i < M; i++)
    {
        scanf("%d %d %d", &id, &index, &score);
        id--; index--;
        if(score >= 0)
        {
            infos[id]->pass = 1;
        }
        score = max(score, 0); /* submitted but not passed, still show 0 score */
        if(score > infos[id]->score[index])
        {
            if(score == fullscore[index])
            {
                infos[id]->full++;
            }
            infos[id]->tot += (score - max(infos[id]->score[index], 0));
            infos[id]->score[index] = score;
        }
        
    }
    
    /* qsort */
    qsort(infos, N, sizeof(info), cmp);
    
    for(int i = 0, rank = 0, tie = 1; i < N; i++)
    {
        if(infos[i]->pass == 1)
        {
            if(i > 0 && infos[i]->tot == infos[i - 1]->tot)
            {
                tie++;
            }
            else
            {
                rank += tie;
                tie = 1;
            }
            printf("%d", rank);
            printf(" %05d %d", infos[i]->id + 1, infos[i]->tot);
            for(int j = 0; j < K; j++)
            {
                if(infos[i]->score[j] < 0)
                {
                    printf(" -");
                }
                else
                {
                    printf(" %d", infos[i]->score[j]);
                }
            }
            printf("\n");
        }
    }
    
    return 0;
}
