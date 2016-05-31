/** passed
 * 05-树7 堆中的路径   (25分)
 * 将一系列给定数字插入一个初始为空的小顶堆H[]。随后对任意给定的下标i，打印从H[i]到根结点的
 * 路径。
 * 
 * 输入格式:
 * 每组测试第1行包含2个正整数N和M(≤1000)，分别是插入元素的个数、以及需要打印的路径条数。
 * 下一行给出区间[-10000, 10000]内的N个要被插入一个初始为空的小顶堆的整数。最后一行给出M
 * 个下标。
 * 
 * 输出格式:
 * 对输入中给出的每个下标i，在一行中输出从H[i]到根结点的路径上的数据。数字间以1个空格分隔，
 * 行末不得有多余空格。
 * 
 * 输入样例:
5 3
46 23 26 24 10
5 4 3
 * 
 * 输出样例:
 * 24 23 10
 * 46 23 10
 * 26 10
 */

#include <stdio.h>
#define TOTAL 1001
int main()
{
    int heap[TOTAL];
    heap[0] = -10001;
    int N, M;
    int current, index;
    int size = 0;
    
    scanf("%d %d", &N, &M);
    for(int i = 0; i < N; i++)
    {
        int j;
        size++;
        scanf("%d", &current);
        for(j = size; heap[j / 2] > current; j /= 2)
        {
            heap[j] = heap[j / 2];
        }
        heap[j] = current;
    }
    
    for(int i = 0; i < M; i++)
    {
        scanf("%d", &index);
        for( ; index > 0; index /= 2)
        {
            printf("%d", heap[index]);
            printf("%s", index == 1 ? "\n" : " ");
        }
    }
    return 0;
}
