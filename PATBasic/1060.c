/**
 * 1060. 爱丁顿数(25)
 * 
 * 英国天文学家爱丁顿很喜欢骑车。据说他为了炫耀自己的骑车功力，还定义了一个“爱丁顿数”
 * E，即满足有E天骑车超过E英里的最大整数E。据说爱丁顿自己的E等于87。
 * 
 * 现给定某人N天的骑车距离，请你算出对应的爱丁顿数E（<=N）。
 * 
 * 输入格式：
 * 
 * 输入第一行给出一个正整数N（<=105），即连续骑车的天数；第二行给出N个非负整数，代表
 * 每天的骑车距离。
 * 
 * 输出格式：
 * 
 * 在一行中给出N天的爱丁顿数。
 * 
 * 输入样例：
 * 10
 * 6 7 6 9 3 10 8 2 7 8
 * 输出样例：
 * 6
 */

#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b) 
{ 
    return *(int*)b - *(int*)a; 
}

int main()
{
    int N, E, miles[100000];
    
    scanf("%d", &N);
    for(int i = 0; i < N; i++) 
        scanf("%d", miles + i);
    
    qsort(miles, N, sizeof(int), cmp);
    
    for(E = 0; E < N && miles[E] > E + 1; E++) ;
    printf("%d", E);
    
    return 0;
}
