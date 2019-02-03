#include <stdio.h>

int main()
{
    int N;
    int weight[] = {7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2};
    char ZtoM[] = {'1', '0', 'X', '9', '8', '7', '6', '5', '4', '3', '2'};
    char ID[19];

    scanf("%d", &N);
    int d, sum, count = 0;     /* index, weighted sum and count for legal IDs */
    for(int i = 0; i < N; i++)
    {
        scanf("%s", ID);

        for(d = 0, sum = 0; d < 17 && ID[d] >= '0' && ID[d] <= '9'; d++)
            sum += (ID[d] - '0') * weight[d];

        if(d == 17 && ID[17] == ZtoM[sum % 11])     /* legal ID */
            count++;
        else                                        /* illegal ID */
            puts(ID);
    }
    if(count == N)
        puts("All passed");

    return 0;
}
