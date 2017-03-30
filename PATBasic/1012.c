/**
 * 1012. 数字分类
 * 给定一系列正整数，请按要求对数字进行分类，并输出以下5个数字：
 * 
 * A1 = 能被5整除的数字中所有偶数的和；
 * A2 = 将被5除后余1的数字按给出顺序进行交错求和，即计算n1-n2+n3-n4...；
 * A3 = 被5除后余2的数字的个数；
 * A4 = 被5除后余3的数字的平均数，精确到小数点后1位；
 * A5 = 被5除后余4的数字中最大数字。
 * 输入格式：
 * 
 * 每个输入包含1个测试用例。每个测试用例先给出一个不超过1000的正整数N，随后给出N个
 * 不超过1000的待分类的正整数。数字间以空格分隔。
 * 
 * 输出格式：
 * 
 * 对给定的N个正整数，按题目要求计算A1~A5并在一行中顺序输出。数字间以空格分隔，但
 * 行末不得有多余空格。
 * 
 * 若其中某一类数字不存在，则在相应位置输出“N”。
 * 
 * 输入样例1：
 * 13 1 2 3 4 5 6 7 8 9 10 20 16 18
 * 输出样例1：
 * 30 11 2 9.7 9
 * 输入样例2：
 * 8 1 2 4 5 6 7 9 16
 * 输出样例2：
 * N 11 2 N 9
 **/

#include <stdio.h>

int main()
{
    int count;
    int A1 = 0, A2 = 0, A3 = 0, A4 = 0, A5 = 0;
    int A2flag = 0, A4count = 0;
    
    scanf("%d", &count);
    for(int i = 0, n; i < count; i++)
    {
        scanf("%d", &n);
        switch(n % 5)
        {
        case 0: A1 += n % 2 ? 0 : n;                                break;
        case 1: A2flag = A2flag == 1 ? -1 : 1; A2 += A2flag * n;    break;
        case 2: A3 ++;                                              break;
        case 3: A4 += n; A4count ++;                                break;
        case 4: A5 = n > A5? n : A5;                                break;
        }
    }

    if(A1 == 0)     printf("N ");   else printf("%d ", A1);
    if(A2flag == 0) printf("N ");   else printf("%d ", A2);
    if(A3 == 0)     printf("N ");   else printf("%d ", A3);
    if(A4 == 0)     printf("N ");   else printf("%.1f ", A4 * 1.0 / A4count);
    if(A5 == 0)     printf("N");    else printf("%d", A5);
    
    return 0;
}
