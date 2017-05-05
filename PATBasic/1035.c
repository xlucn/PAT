/**
 * 1035. 插入与归并(25)
 * 
 * 根据维基百科的定义：
 * 
 * 插入排序是迭代算法，逐一获得输入数据，逐步产生有序的输出序列。每步迭代中，算法从
 * 输入序列中取出一元素，将之插入有序序列中正确的位置。如此迭代直到全部元素有序。
 * 
 * 归并排序进行如下迭代操作：首先将原始序列看成N个只包含1个元素的有序子序列，然后每
 * 次迭代归并两个相邻的有序子序列，直到最后只剩下1个有序的序列。
 * 
 * 现给定原始序列和由某排序算法产生的中间序列，请你判断该算法究竟是哪种排序算法？
 * 
 * 输入格式：
 * 
 * 输入在第一行给出正整数N (<=100)；随后一行给出原始序列的N个整数；最后一行给出由某
 * 排序算法产生的中间序列。这里假设排序的目标序列是升序。数字间以空格分隔。
 * 
 * 输出格式：
 * 首先在第1行中输出“Insertion Sort”表示插入排序、或“Merge Sort”表示归并排序；然后
 * 在第2行中输出用该排序算法再迭代一轮的结果序列。题目保证每组测试的结果是唯一的。
 * 数字间以空格分隔，且行末不得有多余空格。
 * 输入样例1：
 * 10
 * 3 1 2 8 7 5 9 4 6 0
 * 1 2 3 7 8 5 9 4 6 0
 * 输出样例1：
 * Insertion Sort
 * 1 2 3 5 7 8 9 4 6 0
 * 输入样例2：
 * 10
 * 3 1 2 8 7 5 9 4 0 6
 * 1 3 2 8 5 7 4 9 0 6
 * 输出样例2：
 * Merge Sort
 * 1 2 3 8 4 5 7 9 0 6
 */

#include <stdio.h>
#include <stdlib.h>

int comp(const void *a, const void *b){ return *(int*)a - *(int*)b;}

int main()
{
    int N, origin[100], halfsort[100], i, j, length;
    scanf("%d", &N);
    for(int i = 0; i < N; i++) scanf("%d", origin + i);
    for(int i = 0; i < N; i++) scanf("%d", halfsort + i);
    
    /* if it is insertion sort, return sorted length if yes, zero otherwise */
    for(i = 0; i < N - 1 && halfsort[i] <= halfsort[i + 1]; i++) ;
    for(length = ++i; i < N && halfsort[i] == origin[i]; i++) ;
    length = i == N ? length + 1 : 0;
    
    if(length)                  /* insertion sort */
    {
        puts("Insertion Sort");
        qsort(origin, length, sizeof(int), comp);
    }
    else                        /* merge sort, operate on the original array */
    {
        puts("Merge Sort");
        for(length = 1, i = 0; i < N && length <= N; length *= 2)
        {
            /* i == N means identical, also breaks the outer 'for' loop */
            for(i = 0; i < N && origin[i] == halfsort[i]; i++) ; 
            for(j = 0; j < N / length; j++)
                qsort(origin + j * length, length, sizeof(int), comp);
            qsort(origin + j * length, N % length, sizeof(int), comp);
        }
    }
    
    for(int i = 0; i < N; i++) 
        printf("%d%c", origin[i], i == N - 1 ? '\n' : ' ');
    
    return 0;
}
