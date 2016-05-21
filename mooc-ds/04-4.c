/**
 * 04-树4 是否同一棵二叉搜索树   (25分)
 * 给定一个插入序列就可以唯一确定一棵二叉搜索树。然而，一棵给定的二叉搜索树却可以由多种不同
 * 的插入序列得到。例如分别按照序列{2, 1, 3}和{2, 3, 1}插入初始为空的二叉搜索树，都得到一
 * 样的结果。于是对于输入的各种插入序列，你需要判断它们是否能生成一样的二叉搜索树。
 * 
 * 输入格式:
 * 输入包含若干组测试数据。每组数据的第1行给出两个正整数N (≤10)和L，分别是每个序列插入元素
 * 的个数和需要检查的序列个数。第2行给出N个以空格分隔的正整数，作为初始插入序列。最后L行，
 * 每行给出N个插入的元素，属于L个需要检查的序列。
 * 
 * 简单起见，我们保证每个插入序列都是1到N的一个排列。当读到N为0时，标志输入结束，这组数据不
 * 要处理。
 * 
 * 输出格式:
 * 对每一组需要检查的序列，如果其生成的二叉搜索树跟对应的初始序列生成的一样，输出“Yes”，
 * 否则输出“No”。
 * 
 * 输入样例:
4 2
3 1 4 2
3 4 1 2
3 2 4 1
2 1
2 1
1 2
0
 * 
 *输出样例:
 * Yes
 * No
 * No
 */

#include <stdio.h>

void _insert(int a[], int index, int n)
{
    if( a[ index ] == 0 )
        a[ index ] = n;
    else if( n < a[ index ] )
        _insert( a, index * 2, n );
    else if( n > a[ index ] )
        _insert( a, index * 2 + 1, n );
}

void insert(int a[], int n)
{
    _insert(a, 1, n);
}

int main()
{
    int N, L;
    int current;
    for( ; ; )
    {
        scanf( "%d", &N );
        if( N == 0 ) break;
        scanf( "%d", &L );
        
        /* read and create the initial search tree */
        int a[ 1024 ] = { 0 };
        for( int i = 0; i < N; i++ )
        {
            scanf( "%d", &current );
            insert( a, current );
        }
        
        /* check each sample */
        for( int j = 0; j < L; j++ )
        {
            /* read and create a search tree */
            int b[ 1024 ] = { 0 };
            for( int i = 0; i < N; i++ )
            {
                scanf( "%d", &current );
                insert( b, current );
            }
            
            /* compare two search trees */
            int issame = 1;
            for( int i = 0; i < 1024; i++ )
            {
                if( a[ i ] != b[ i ] )
                {
                    issame = 0;
                    break;
                }
            }
            printf( "%s\n", issame == 1 ? "Yes": "No" );
        }
    }
    return 0;
}
