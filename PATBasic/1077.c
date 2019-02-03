#include <stdio.h>

int main()
{
    int N, M, count;
    double G1, G2, Gsum, Gmax, Gmin, G;
    scanf("%d %d", &N, &M);

    for(int i = 0; i < N; i++)
    {
        scanf("%lf", &G2);

        /* Calculate G1 */
        Gsum = 0;
        count = 0;
        Gmin = M;
        Gmax = 0;
        for(int j = 0; j < N - 1; j++)
        {
            scanf("%lf", &G);
            if(G >= 0 && G <= M)
            {
                count++;
                Gsum += G;
                if(G > Gmax)    /* Record highest score */
                    Gmax = G;
                if(G < Gmin)    /* Record lowest score */
                    Gmin = G;
            }
        }
        G1 = (Gsum - Gmax - Gmin) / (count - 2); /* Average */

        printf("%d\n", (int)((G1 + G2 + 1) / 2));
    }

    return 0;
}
