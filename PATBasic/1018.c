#include <stdio.h>

char max(int B, int C, int J)
{
    if(B >= C && B >= J) return 'B';
    if(C >  B && C >= J) return 'C';
    /* J > B && J > C */ return 'J';
}

int main()
{
    int N;
    char a, b;
    int AwinB = 0, AwinC = 0, AwinJ = 0;
    int BwinB = 0, BwinC = 0, BwinJ = 0;

    scanf("%d", &N);
    for(int i = 0; i < N; i++)
    {
        scanf(" %c %c", &a, &b);  /* Notice the space before every %c */
        if(a == 'B' && b == 'C') AwinB++;
        if(a == 'C' && b == 'J') AwinC++;
        if(a == 'J' && b == 'B') AwinJ++;
        if(a == 'B' && b == 'J') BwinJ++;
        if(a == 'C' && b == 'B') BwinB++;
        if(a == 'J' && b == 'C') BwinC++;
    }

    int Awin = AwinB + AwinC + AwinJ;
    int Bwin = BwinB + BwinC + BwinJ;
    int Tie = N - Awin - Bwin;
    printf("%d %d %d\n", Awin, Tie, Bwin);
    printf("%d %d %d\n", Bwin, Tie, Awin);
    printf("%c %c", max(AwinB, AwinC, AwinJ), max(BwinB, BwinC, BwinJ));

    return 0;
}
