/**
 * 1065. 单身狗(25)
 * 
 * “单身狗”是中文对于单身人士的一种爱称。本题请你从上万人的大型派对中找出落单的客人，
 * 以便给予特殊关爱。
 * 
 * 输入格式：
 * 
 * 输入第一行给出一个正整数N（<=50000），是已知夫妻/伴侣的对数；随后N行，每行给出一
 * 对夫妻/伴侣——为方便起见，每人对应一个ID号，为5位数字（从00000到99999），ID间以空
 * 格分隔；之后给出一个正整数M（<=10000），为参加派对的总人数；随后一行给出这M位客人
 * 的ID，以空格分隔。题目保证无人重婚或脚踩两条船。
 * 
 * 输出格式：
 * 
 * 首先第一行输出落单客人的总人数；随后第二行按ID递增顺序列出落单的客人。ID间用1个
 * 空格分隔，行的首尾不得有多余空格。
 * 
 * 输入样例：
 * 3
 * 11111 22222
 * 33333 44444
 * 55555 66666
 * 7
 * 55555 44444 10000 88888 22222 11111 23333
 * 输出样例：
 * 5
 * 10000 23333 44444 55555 88888
 */
#include <stdio.h>
int main()
{
    int couple[100001] = {0}, N, ID1, ID2, M, count = 0;
    
    /* every pair of 'index' and 'value' are a couple.
     * record ID + 1 to avoid '00000' conflict with 0 */
    scanf("%d", &N);
    for(int i = 0; i < N; i++)
    {
        scanf("%d %d", &ID1, &ID2); ID1++; ID2++;
        couple[ID1] = ID2;
        couple[ID2] = ID1;
    }
    
    /* Record those who come. If one has a mate then set 0(which means signed in), 
     * else(means he is not even in the 'couple-list') set -1(which means bachelor) */
    scanf("%d", &M);
    for(int i = 0; i < M; i++)
    {
        scanf("%d", &ID1); ID1++;
        if(couple[ID1]) couple[ID1] = 0;
        else            {couple[ID1] = -1; count++;}
    }
    
    /* If couple[ID] is positive but couple[couple[ID]] is zero, 
     * it means 'ID' didn't come but his/her mate did(signed in). */
    for(int i = 0; i < 100001; i++) if(couple[i] > 0 && !couple[couple[i]]) 
    {
        couple[couple[i]] = -1;
        count++;
    }
    
    /* Those whose value is -1 is a bachelor or came alone */
    printf("%d\n", count);
    for(int i = 0; i < 100001; i++) if(couple[i] == -1)
        printf("%05d%c", i - 1, --count ? ' ' : '\0');
    
    return 0;
}
