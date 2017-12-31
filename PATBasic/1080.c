/**
 * 1080. MOOC期终成绩 (25)
 * 
 * 对于在中国大学MOOC（http://www.icourse163.org/）学习“数据结构”课程的学生，
 * 想要获得一张合格证书，必须首先获得不少于200分的在线编程作业分，然后总评获得不少于
 * 60分（满分100）。总评成绩的计算公式为 G = (G期中x 40% + G期末x 60%)，如果 
 * G期中 > G期末；否则总评 G 就是 G期末。这里 G期中 和 G期末 分别为学生的期中和
 * 期末成绩。
 * 
 * 现在的问题是，每次考试都产生一张独立的成绩单。本题就请你编写程序，把不同的成绩单合
 * 为一张。
 * 
 * 输入格式：
 * 
 * 输入在第一行给出3个整数，分别是 P（做了在线编程作业的学生数）、M（参加了期中考试的
 * 学生数）、N（参加了期末考试的学生数）。每个数都不超过10000。
 * 
 * 接下来有三块输入。第一块包含 P 个在线编程成绩 G编程；第二块包含 M 个期中考试成绩
 *  G期中；第三块包含 N 个期末考试成绩 G期末。每个成绩占一行，格式为：学生学号 分数。
 * 其中学生学号为不超过20个字符的英文字母和数字；分数是非负整数（编程总分最高为900分，
 * 期中和期末的最高分为100分）。
 * 
 * 输出格式：
 * 
 * 打印出获得合格证书的学生名单。每个学生占一行，格式为：
 * 
 * 学生学号 G编程 G期中 G期末 G
 * 
 * 如果有的成绩不存在（例如某人没参加期中考试），则在相应的位置输出“-1”。输出顺序为按
 * 照总评分数（四舍五入精确到整数）递减。若有并列，则按学号递增。题目保证学号没有重复，
 * 且至少存在1个合格的学生。
 * 
 * 输入样例：
 * 6 6 7
 * 01234 880
 * a1903 199
 * ydjh2 200
 * wehu8 300
 * dx86w 220
 * missing 400
 * ydhfu77 99
 * wehu8 55
 * ydjh2 98
 * dx86w 88
 * a1903 86
 * 01234 39
 * ydhfu77 88
 * a1903 66
 * 01234 58
 * wehu8 84
 * ydjh2 82
 * missing 99
 * dx86w 81
 * 
 * 输出样例：
 * missing 400 -1 99 99
 * ydjh2 200 98 82 88
 * dx86w 220 88 81 84 
 * wehu8 300 55 84 84
 **/

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

int cmp(const void *a, const void *b)
{
    Score *s1 = *(Score**)a, *s2 = *(Score**)b;
    if(s2->total_mark - s1->total_mark)
        return s2->total_mark - s1->total_mark;
    return strcmp(s1->name, s2->name);
}

int main()
{
    int P, M, N;
    scanf("%d %d %d", &P, &M, &N);
    
    int score, count = 0;
    char name[21];
    Score scores[10000];
    
    for(int i = 0; i < P; i++)  /* Read programming grade */
    {
        scanf("%s %d", name, &score);
        if(score >= 200)        /* Only record if score >= 200 */
        {
            strcpy(scores[count].name, name);
            scores[count].programming = score;
            scores[count].midterm = -1;
            scores[count].finalexam = -1;
            count++;
        }
    }
    
    for(int i = 0; i < M; i++)  /* Read midterm grade */
    {
        scanf("%s %d", name, &score);
        for(int j = 0; j < count; j++)
            if(strcmp(name, scores[j].name) == 0)
            {
                scores[j].midterm = score;
                break;
            }
    }
    
    for(int i = 0; i < N; i++)  /* Read final exam grade */
    {
        scanf("%s %d", name, &score);
        for(int j = 0; j < count; j++)
            if(strcmp(name, scores[j].name) == 0)
            {
                scores[j].finalexam = score;
                
                /* Calculate total mark */
                double total_mark;
                if(scores[j].finalexam >= scores[j].midterm)
                    total_mark = scores[j].finalexam;
                else if(scores[j].finalexam != -1)
                    total_mark = 0.6 * scores[j].finalexam +
                                 0.4 * scores[j].midterm;
                else
                    total_mark = 0.4 * scores[j].midterm;
                scores[j].total_mark = (int)(total_mark + 0.5);
                
                break;
            }
    }
    
    /* Sort scores */
    Score *ptrscores[10000];
    for(int i = 0; i < count; i++)
        ptrscores[i] = scores + i;
    qsort(ptrscores, count, sizeof(Score*), cmp);
    
    for(int i = 0; i < count && ptrscores[i]->total_mark >= 60; i++)
        printf("%s %d %d %d %d\n", ptrscores[i]->name, 
               ptrscores[i]->programming, ptrscores[i]->midterm, 
               ptrscores[i]->finalexam, ptrscores[i]->total_mark);
    
    return 0;
}
