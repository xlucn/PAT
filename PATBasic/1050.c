/**
 * 1050. 螺旋矩阵(25)
 * 
 * 本题要求将给定的N个正整数按非递增的顺序，填入“螺旋矩阵”。所谓“螺旋矩阵”，是指从左
 * 上角第1个格子开始，按顺时针螺旋方向填充。要求矩阵的规模为m行n列，满足条件：m*n等
 * 于N；m>=n；且m-n取所有可能值中的最小值。
 * 
 * 输入格式：
 * 
 * 输入在第1行中给出一个正整数N，第2行给出N个待填充的正整数。所有数字不超过104，相邻
 * 数字以空格分隔。
 * 
 * 输出格式：
 * 
 * 输出螺旋矩阵。每行n个数字，共m行。相邻数字以1个空格分隔，行末不得有多余空格。
 * 
 * 输入样例：
 * 12
 * 37 76 20 98 76 42 53 95 60 81 58 93
 * 输出样例：
 * 98 95 93
 * 42 37 81
 * 53 20 76
 * 58 60 76
 */

#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b) {return *(int*)b - *(int*)a;}

int main()
{
    int N, m, n;
    scanf("%d", &N);
    
    int *array = (int*)malloc(N * sizeof(int));
    int *matrix = (int*)malloc(N * sizeof(int));
    for(int i = 0; i < N; i++)
        scanf("%d", array + i);

    qsort(array, N, sizeof(int), cmp);
    
    /* determine m and n */
    for(m = 1; !(m * m >= N && N % m == 0); m++) ;
    n = N / m;
    
    int x = -1, y = 0, index = 0;
    int horizontal = n, virtical = m;
    
    while(horizontal > 0 && virtical > 0)
    {
        for(int i = 0; i < horizontal && virtical > 0; i++)  /* toward right */
            matrix[y * n + ++x] = array[index++];
        virtical--;

        for(int i = 0; i < virtical && horizontal > 0; i++)  /* toward bottom */
            matrix[++y * n + x] = array[index++];
        horizontal--;

        for(int i = 0; i < horizontal && virtical > 0; i++)  /* toward left */
            matrix[y * n + --x] = array[index++];
        virtical--;

        for(int i = 0; i < virtical && horizontal > 0; i++)  /* toward top */
            matrix[--y * n + x] = array[index++];
        horizontal--;
    }
    
    for(int i = 0; i < m; i++)
        for(int j = 0; j < n; j++)
            printf("%d%c", matrix[i * n + j], j == n - 1 ? '\n' : ' ');
    
    return 0;
}
