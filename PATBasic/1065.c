#include <stdio.h>

#define BLANK -1
#define SIGNED -2
#define SINGLE -3

int main()
{
    int couple[100000], count = 0, N, M, ID1, ID2;
    for(int i = 0; i < 100000; i++)
        couple[i] = BLANK;

    /* Read 'couple-list', every pair of 'index' and 'value' are a couple. */
    scanf("%d", &N);
    for(int i = 0; i < N; i++)
    {
        scanf("%d %d", &ID1, &ID2);
        couple[ID1] = ID2;
        couple[ID2] = ID1;
    }

    scanf("%d", &M);
    for(int i = 0; i < M; i++)          /* Read guest list. */
    {
        scanf("%d", &ID1);
        if(couple[ID1] >= 0)                /* If one has a mate */
            couple[ID1] = SIGNED;           /*   set SIGNED */
        else                                /* Else: not in the 'couple-list' */
            couple[ID1] = SINGLE, count++;  /*   set SINGLE */
    }

    /* If couple[ID] is >= 0 (but not signed) but couple[couple[ID]] == SIGNED
     * (signed in), this means 'ID' didn't come but his/her mate did.
     * So his/her mate is alone in the party, set to SINGLE. */
    for(int i = 0; i < 100000; i++)
        if(couple[i] >= 0 && couple[couple[i]] == SIGNED)
            couple[couple[i]] = SINGLE, count++;

    /* Those whose value is SINGLE is either a bachelor or came alone */
    printf("%d\n", count);
    for(int i = 0; i < 100000; i++)
        if(couple[i] == SINGLE)
            printf("%05d%c", i, --count ? ' ' : '\0');

    return 0;
}
