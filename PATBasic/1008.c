#include <stdio.h>

int main()
{
    int N, M, numbers[100];

    scanf("%d %d", &N, &M);
    M %= N; /* M could be larger than N */

    /* Read */
    for(int i = 0; i < N; i++)
        scanf("%d", &numbers[i]);

    /* Print */
    for(int i = N - M; i < N; i++)      /* Print N - M to N - 1 */
        printf("%d ", numbers[i]);
    for(int i = 0; i < N - M - 1; i++)  /* Print 0 to N - M - 2 */
        printf("%d ", numbers[i]);
    printf("%d", numbers[N - M - 1]);   /* Print N - M - 1, no blankspace */

    return 0;
}
