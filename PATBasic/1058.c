/**
 * 1058. 选择题(20)
 * 
 * 批改多选题是比较麻烦的事情，本题就请你写个程序帮助老师批改多选题，并且指出哪道题错
 * 的人最多。
 * 
 * 输入格式：
 * 
 * 输入在第一行给出两个正整数N（<=1000）和M（<=100），分别是学生人数和多选题的个数。
 * 随后M行，每行顺次给出一道题的满分值（不超过5的正整数）、选项个数（不少于2且不超过
 * 5的正整数）、正确选项个数（不超过选项个数的正整数）、所有正确选项。注意每题的选项
 * 从小写英文字母a开始顺次排列。各项间以1个空格分隔。最后N行，每行给出一个学生的答题
 * 情况，其每题答案格式为“(选中的选项个数 选项1 ……)”，按题目顺序给出。注意：题目保证
 * 学生的答题情况是合法的，即不存在选中的选项数超过实际选项数的情况。
 * 
 * 输出格式：
 * 
 * 按照输入的顺序给出每个学生的得分，每个分数占一行。注意判题时只有选择全部正确才能
 * 得到该题的分数。最后一行输出错得最多的题目的错误次数和编号（题目按照输入的顺序从
 * 1开始编号）。如果有并列，则按编号递增顺序输出。数字间用空格分隔，行首尾不得有多余
 * 空格。如果所有题目都没有人错，则在最后一行输出“Too simple”。
 * 
 * 输入样例：
 * 3 4 
 * 3 4 2 a c
 * 2 5 1 b
 * 5 3 2 b c
 * 1 5 4 a b d e
 * (2 a c) (2 b d) (2 a c) (3 a b e)
 * (2 a c) (1 b) (2 a b) (4 a b d e)
 * (2 b d) (1 e) (2 b c) (4 a b c d)
 * 输出样例：
 * 3
 * 6
 * 5
 * 2 2 3 4
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct prob{
    int score;
    int answer; /* bitwise storage for at most 5 options */
    int wrong;
} Prob;

/* read 'count option1 ...' format */
int readanswer()
{
    char c;
    int count, answer = 0;
    scanf("%d", &count);
    for(int k = 0; k < count; k++)
    {
        while((c = getchar()) == ' ');
        answer |= 1 << (c - 'a');
    }
    return answer;
}

int main()
{
    int N, M, max = 0, useless;
    Prob probs[100];
    
    /* read the answers for each problem */
    scanf("%d %d", &N, &M);
    for(int i = 0; i < M; i++)
    {
        scanf("%d %d", &probs[i].score, &useless);
        probs[i].wrong = 0;
        probs[i].answer = readanswer();
    }
    
    /* read every student's answer */
    for(int i = 0; i < N; i++)
    {
        int score = 0;
        for(int j = 0; j < M; j++)
        {
            /* read answer for one problem */
            while(getchar() != '(');
            if(readanswer() == probs[j].answer) /* If it is right */
                score += probs[j].score;
            else if(max < ++probs[j].wrong)  /* If most students got it wrong */
                max = probs[j].wrong;
            while(getchar() != ')');
        }
        printf("%d\n", score);
    }
    
    if(max == 0)
        printf("Too simple");
    else
    {
        printf("%d", max);
        for(int i = 0; i < M; i++) if(probs[i].wrong == max)
            printf(" %d", i + 1);
    }
    
    return 0;
}
