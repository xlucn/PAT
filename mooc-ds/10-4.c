/**
 * 10-排序4 统计工龄   (20分)
 * 给定公司NN名员工的工龄，要求按工龄增序输出每个工龄段有多少员工。
 * 
 * 输入格式:
 * 输入首先给出正整数N（<=10^5），即员工总人数；随后给出N个整数，即每个员工的工龄，范围在[0, 50]。
 * 
 * 输出格式:
 * 按工龄的递增顺序输出每个工龄的员工个数，格式为：“工龄:人数”。每项占一行。如果人数为0则不输出该项。
 * 
 * 输入样例:
 * 
8
10 2 0 5 7 2 5 2
 *
 * 输出样例:
 * 0:1
 * 2:3
 * 5:2
 * 7:1
 * 10:1
 */

#include <stdio.h>

int main()
{
    int num;
    scanf( "%d", &num );
    int seniority;
    int count[ 51 ] = { 0 };
    for( int i = 0; i < num; i++ )
    {
        scanf( "%d", &seniority );
        count[ seniority ]++;
    }
    for( int i = 0; i < 51; i++ )
    {
        if( count[ i ] != 0 )
            printf( "%d:%d\n", i, count[ i ] );
    }
    return 0;
}
