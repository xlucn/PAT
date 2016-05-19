/**
 * 01-复杂度2 Maximum Subsequence Sum   (25分)
 * Given a sequence of K integers { N_1, N_2, ..., N_K}. A continuous subsequence 
 * is defined to be { N_i, N_{i+1}, ..., N_j} where 1≤i≤j≤K. The Maximum 
 * Subsequence is the continuous subsequence which has the largest sum of its 
 * elements. For example, given sequence { -2, 11, -4, 13, -5, -2 }, its maximum 
 * subsequence is { 11, -4, 13 } with the largest sum being 20.Now you are 
 * supposed to find the largest sum, together with the first and the last numbers
 * of the maximum subsequence.
 * 
 * Input Specification:
 * Each input file contains one test case. Each case occupies two lines. The 
 * first line contains a positive integer K (≤10000). The second line contains 
 * K numbers, separated by a space.
 * 
 * Output Specification:
 * For each test case, output in one line the largest sum, together with the 
 * first and the last numbers of the maximum subsequence. The numbers must be 
 * separated by one space, but there must be no extra space at the end of a 
 * line. In case that the maximum subsequence is not unique, output the one 
 * with the smallest indices i and j (as shown by the sample case). If all 
 * the K numbers are negative, then its maximum sum is defined to be 0, and you 
 * are supposed to output the first and the last numbers of the whole sequence.
 * 
 * Sample Input:
 * 10
 * -10 1 2 3 4 -5 -23 3 7 -21
 * 
 * Sample Output:
 * 10 1 4
 * 
 * 测试点
 * sample换1个数字。有正负，负数开头结尾，有并列最大和
 * 最大和序列中有负数
 * 并列和对应相同i但是不同j，即尾是0
 * 1个正数
 * 全是负数
 * 负数和0
 * 最大和前面有一段是0
 * 最大N
 **/

#include <stdio.h>

int main()
{
    int flag = 0; /* mark if all the numbers are negative */
    int current;
    int first;
    int maxfirst;
    int maxlast;
    int sum = 0;
    int maxsum = 0;

    /* Get the number of list items */
    int num;
    scanf("%d\n", &num);
    for (int i = 0; i < num; i++)
    {
        /* read */
        scanf("%d", &current);
        /* record the first number of current maximum subsequence */
        if (i == 0) first = current;

        if(flag == 1 && current >= 0) /* the numbers before are all negative */
        {
            first = current;
            flag = 0;
        }
        
        sum += current;
        if (sum > maxsum)
        {
            maxsum = sum;
            maxfirst = first;
            maxlast = current;
        }        
        else if (sum < 0)
        {
            sum = 0;
            flag = 1;
        }
    }
    if (first < 0)
    {
        maxfirst = first;
        maxlast = current;
    }
    
    printf("%d %d %d", maxsum, maxfirst, maxlast);

    return 0;
}

