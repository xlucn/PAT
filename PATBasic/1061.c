#include <stdio.h>

int main()
{
    int N, M;
    int fullmark[100], answer[100];
    int score, choice;

    scanf("%d %d", &N, &M);
    for(int i = 0; i < M; i++)
        scanf("%d", fullmark + i);
    for(int i = 0; i < M; i++)
        scanf("%d", answer + i);

    for(int i = 0; i < N; i++)
    {
        score = 0;
        for(int j = 0; j < M; j++)
        {
            scanf("%d", &choice);
            if(choice == answer[j])
                score += fullmark[j];
        }
        printf("%d\n", score);
    }

    return 0;
}
