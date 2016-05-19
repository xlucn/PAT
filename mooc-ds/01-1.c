/**
 * 01-复杂度1 最大子列和问题   (20分)
 * 给定K个整数组成的序列{N_1, N_2, ..., N_K}，“连续子列”被定义为
 * { N_i, N_{i+1}, ..., N_j}，其中 1 < i < j < K。“最大子列和”则被定义为所有连续子列元
 * 素的和中最大者。例如给定序列{ -2, 11, -4, 13, -5, -2 }，其连续子列{ 11, -4, 13 }有
 * 最大的和20。现要求你编写程序，计算给定整数序列的最大子列和。
 * 
 * 本题旨在测试各种不同的算法在各种数据情况下的表现。各组测试数据特点如下：
 * 数据1：与样例等价，测试基本正确性；
 * 数据2：10^2个随机整数；
 * 数据3：10^3个随机整数；
 * 数据4：10^4个随机整数；
 * 数据5：10^5个随机整数；
 * 
 * 输入格式:
 * 输入第1行给出正整数K(≤100000)；第2行给出K个整数，其间以空格分隔。
 * 
 * 输出格式:
 * 在一行中输出最大子列和。如果序列中所有整数皆为负数，则输出0。
 * 
 * 输入样例:
 * 6
 * -2 11 -4 13 -5 -2
 * 
 * 输出样例:
 * 20
 * 
 * 测试点
 * sample 有正负，负数开头结尾，最大和有更新
 * 100个随机数
 * 1000个随机数
 * 10000个随机数
 * 100000个随机数
 **/

#include <stdio.h>      /* printf fgets puts */
#include <stdlib.h>     /* atoi */
#include <string.h>     /* strtok */

int main()
{
    /* TODO:change the read procession */
    /* Get the number of list items */
    int num;
    scanf("%d\n", &num);
    
    int current;
    int sum = 0;
    int maxsum = 0;
    char sarray[2000000];
    
    fgets(sarray, 2000000, stdin);
    
    for (int i = 0; i < num; i++)
    {
        if (i == 0)
        {
            current = atoi(strtok(sarray, " "));
        }
        else
        {
            current = atoi(strtok(NULL, " "));
        }
        sum += current;
        if (sum > maxsum)
        {
            maxsum = sum;
        }        
        else if (sum < 0)
        {
            sum = 0;
        }
        
    }
    printf("%d", maxsum);

    return 0;
}
