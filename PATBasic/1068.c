#include <stdio.h>

#define SQR(X) ((X)*(X))
#define R(COLOR) ((COLOR & 0XFF0000) >> 16)
#define G(COLOR) ((COLOR & 0X00FF00) >> 8)
#define B(COLOR) (COLOR & 0X0000FF)
#define D(C1, C2) (SQR(R(C1) - R(C2)) + SQR(G(C1) - G(C2)) +  SQR(B(C1) - B(C2)))

int iUnique(int array[][1000], int x, int y, int x0, int y0)
{
    for(int i = 0; i < x; i++)
        for(int j = 0; j < y; j++)
            if(array[i][j] == array[x0][y0] && !(i == x0 && j == y0))
                return 0;
    return 1;
}

int main()
{
    int M, N, TOL;
    scanf("%d %d %d", &M, &N, &TOL);

    int fig[1000][1000];
    for(int i = 0; i < N; i++)
        for(int j = 0; j < M; j++)
            scanf("%d", &fig[i][j]);

    int count = 0, M0, N0;
    for(int i = 0; i < N; i ++)
        for (int j = 0; j < M; j++)
            if((i > 0 && j > 0 ? D(fig[i][j], fig[i - 1][j - 1]) > SQR(TOL) : 1)
            && (i > 0          ? D(fig[i][j], fig[i - 1][j    ]) > SQR(TOL) : 1)
            && (i > 0 && j < M ? D(fig[i][j], fig[i - 1][j + 1]) > SQR(TOL) : 1)
            && (         j > 0 ? D(fig[i][j], fig[i    ][j - 1]) > SQR(TOL) : 1)
            && (         j < M ? D(fig[i][j], fig[i    ][j + 1]) > SQR(TOL) : 1)
            && (i < N && j > 0 ? D(fig[i][j], fig[i + 1][j - 1]) > SQR(TOL) : 1)
            && (i < N          ? D(fig[i][j], fig[i + 1][j    ]) > SQR(TOL) : 1)
            && (i < N && j < M ? D(fig[i][j], fig[i + 1][j + 1]) > SQR(TOL) : 1)
            && iUnique(fig, N, M, i, j))
            {
                count++;
                N0 = i;
                M0 = j;
            }

    if(count == 0)  printf("Not Exist");
    if(count == 1)  printf("(%d, %d): %d", M0 + 1, N0 + 1, fig[N0][M0]);
    if(count >= 2)  printf("Not Unique");

    return 0;
}
