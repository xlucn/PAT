/** passed
 * 09-排序1 排序   (25分)
 * 给定N个（长整型范围内的）整数，要求输出从小到大排序后的结果。
 * 
 * 本题旨在测试各种不同的排序算法在各种数据情况下的表现。各组测试数据特点如下：
 * 
 * 数据1：只有1个元素；
 * 数据2：11个不相同的整数，测试基本正确性；
 * 数据3：10^3个随机整数；
 * 数据4：10^4个随机整数；
 * 数据5：10^5个随机整数；
 * 数据6：10^5个顺序整数；
 * 数据7：10^5个逆序整数；
 * 数据8：10^5个基本有序的整数；
 * 数据9：10^5个随机正整数，每个数字不超过1000。
 * 
 * 输入格式:
 * 输入第一行给出正整数N（≤10^​5），随后一行给出N个（长整型范围内的）整数，其间以空格分隔。
 * 
 * 输出格式:
 * 在一行中输出从小到大排序后的结果，数字间以1个空格分隔，行末不得有多余空格。
 * 
 * 输入样例:
11
4 981 10 -17 0 -20 29 50 8 43 -5
 * 
 * 输出样例:
 * -20 -17 -5 0 4 8 10 29 43 50 981
 */

#include <stdio.h>

#define cutoff 3

void InsertionSort(long int A[], int N)
{
    int j;
    long int tmp;
    for( int p = 1; p < N; p++ )
    {
        tmp = A[ p ];
        for( j = p; j > 0 && A[ j - 1 ] > tmp; j-- )
        {
            A[ j ] = A[ j - 1 ];
        }
        A[ j ] = tmp;
    }
}

void swap(long int *a, long int *b)
{
    long int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

long int median3(long int A[], int left, int right)
{
    int center = ( left + right ) / 2;
    
    if( A[ left ] > A[ center ] )
        swap( &A[ left ], &A[ center ] );
    if( A[ left ] > A[ right ] )
        swap( &A[ left ], &A[ right ] );
    if( A[ center ] > A[ right ] )
        swap( &A[ center ], &A[ right ] );
    
    swap( &A[ center ], &A[ right - 1 ] );
    return A[ right - 1 ];
}

void Qsort(long int A[], int left, int right)
{
    int i, j;
    long int pivot;
    
    if(left + cutoff <= right)
    {
        pivot = median3(A, left, right);
        i = left;
        j = right - 1;
        for( ; ; )
        {
            while(A[++i] < pivot){;}
            while(A[--j] > pivot){;}
            if(i < j)
            {
                swap(&A[i], &A[j]);
            }
            else
            {
                break;
            }
        }
        swap( &A[ i ], &A[ right - 1 ] );
        
        Qsort( A, left, i - 1 );
        Qsort( A, i + 1, right );
    }
    else
    {
        InsertionSort( A + left, right - left + 1 );
    }
}

void QuickSort( long int A[], int N )
{
    Qsort( A, 0, N - 1 );
}

int main()
{
    int num;
    scanf( "%d", &num );
    
    long int a[ 100000 ];
    for( int i = 0; i < num; i++ )
        scanf( "%ld", &a[ i ] );
    
    QuickSort( a, num );
    
    for( int i = 0; i < num; i++ )
    {
        printf( "%s", i == 0 ? "" : " " );
        printf( "%ld", a[ i ] );
    }
    return 0;
}
