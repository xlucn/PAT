#include <stdio.h>

#define MAX_M 100
#define MAX_OPTIONS 5

int readanswer()
{
    char c;
    int answer = 0, count;

    scanf("%d", &count);
    for(int i = 0; i < count; i++)
    {
        while((c = getchar()) == ' ');
        answer |= 1 << (c - 'a');
    }
    return answer;
}

int main()
{
    int N, M, full_score[MAX_M] = {0}, correct_ans[MAX_M] = {0},
        wrong_ans[MAX_M] = {0}, wrong_count[MAX_M][5] = {{0}},
        wrong_count_max = 0;

    scanf("%d %d", &N, &M);
    /* Read M lines */
    int count_options;
    for(int i = 0; i < M; i++)
    {
        scanf("%d %d", full_score + i, &count_options);
        correct_ans[i] = readanswer();
    }

    /* Read N lines */
    for(int i = 0; i < N; i++)
    {
        float score = 0;
        int answer;
        for(int j = 0; j < M; j++)
        {
            while(getchar() != '(');
            answer = readanswer();
            wrong_ans[j] = answer ^ correct_ans[j];

            if(wrong_ans[j] == 0)               /* all correct */
                score += full_score[j];
            else if((wrong_ans[j] | correct_ans[j]) == correct_ans[j])
                score += 0.5 * full_score[j];   /* partially corrent */

            /* For every option, record the number of students got wrong */
            for(int k = 0; k < MAX_OPTIONS; k++)
            {
                wrong_count[j][k] += wrong_ans[j] >> k & 1; /* k-th bit */
                if(wrong_count[j][k] > wrong_count_max)
                    wrong_count_max = wrong_count[j][k];
            }

            while(getchar() != ')');
        }
        printf("%.1f\n", score);
    }

    if(wrong_count_max == 0)
        printf("Too simple");
    else
        for(int i = 0; i < M; i ++)
            for(int j = 0; j < MAX_OPTIONS; j++)
                if(wrong_count[i][j] == wrong_count_max)
                    printf("%d %d-%c\n", wrong_count_max, i + 1, j + 'a');

    return 0;
}
