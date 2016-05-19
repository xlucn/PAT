/**
 * 02-线性结构3 Pop Sequence   (25分)
 * 
 * Given a stack which can keep M numbers at most. Push N numbers in the order 
 * of 1, 2, 3, ..., N and pop randomly. You are supposed to tell if a given 
 * sequence of numbers is a possible pop sequence of the stack. 
 * For example, if M is 5 and N is 7, we can obtain 1, 2, 3, 4, 5, 6, 7 
 * from the stack, but not 3, 2, 1, 7, 5, 6, 4.
 * 
 * Input Specification:
 * Each input file contains one test case. For each case, the first line 
 * contains 3 numbers (all no more than 1000): M (the maximum capacity of 
 * the stack), N (the length of push sequence), and K (the number of pop 
 * sequences to be checked). Then K lines follow, each contains a pop sequence 
 * of N numbers. All the numbers in a line are separated by a space.
 * 
 * Output Specification:
 * For each pop sequence, print in one line "YES" if it is indeed a possible 
 * pop sequence of the stack, or "NO" if not.
 * 
 * Sample Input:
5 7 5
1 2 3 4 5 6 7
3 2 1 7 5 6 4
7 6 5 4 3 2 1
5 6 4 3 7 2 1
1 7 6 5 4 3 2
 * 
 * Sample Output:
 * YES
 * NO
 * NO
 * YES
 * NO
 * 
 * 测试点
 * sample乱序，一般的Y&N
 * 达到最大size后又溢出
 * M==N
 * 最大数
 * 最小数
 * 卡特殊错误算法（通过比较大小判断）
 **/

/**
 * tip: （FIXME: 不能通过最后一个测试点）
 * 将数组“贪婪地”连续分割为降序排列（e.g.3 2 1 | 7 5 | 6 4）：
 * 1.所有的降序子数组长度不能超过堆栈长度M
 * 2.非隔一递减的子序列中跳过的数字（如上述7 5中跳过了6，6 4中跳过了5）必须在之前出现过
 */
#include <stdio.h>

int main()
{
    /* read N, M, K */
    int N, M, K;
    scanf("%d %d %d\n", &M, &N, &K);
    
    int num[1000];
    /* loop K times to examine the samples */
    for(int sample = 0; sample < K; sample++)
    {   
        /* read the line and parse the numbers */
        for(int i = 0 ; i < N; i++)
        {
            scanf("%d", &num[i]);
        }
        
        /* find a decreasing sublist, record its length */
        int length = 1;
        int passed = 1; /* 1 for passed and 0 for failed */
        for(int i = 1; i < N; i++)
        {
            /* whether it is a decreasing sequence */
            if (num[i] < num[i - 1])
            {
                length++;
                /* length is not more than M */
                if (length > M)
                {
                    passed = 0;
                    break;
                }
                /* if there is a skipped number, it should appeared before */
                if (num[i - 1] - num[i] > 1)
                {
                    int appeared = 0; /* 0 for not appeared, 1 for appeared */
                    /* for each skipped numbers */
                    for(int j = num[i] + 1; j < num[i - 1]; j++) 
                    {
                        /* FIXME: may not be necessary sufficient */
                        /* find its appearance */
                        for(int k = 0; k < i; k++)
                        {
                            if (num[k] == j)
                            {
                                appeared = 1;
                            }
                        }
                    }
                    if (appeared == 0)
                    {
                        passed = 0;
                        break;
                    }
                }
            }
            else /* not decreasing */
            {
                length = 1;
            }
        }
        
        /* print */
        printf("%s\n", passed == 1 ? "YES" : "NO");
    }
    
    return 0;
}
