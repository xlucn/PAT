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

#define BLANK -1
#define SIGNED -2
#define SINGLE -3

int main()
{
    int couple[100000], count = 0, N, M, ID1, ID2;
    for(int i = 0; i < 100000; i++) 
        couple[i] = BLANK;
    
    /* Read 'couple-list', every pair of 'index' and 'value' are a couple. */
    scanf("%d", &N);
    for(int i = 0; i < N; i++)
    {
        scanf("%d %d", &ID1, &ID2);
        couple[ID1] = ID2;
        couple[ID2] = ID1;
    }
    
    scanf("%d", &M);
    for(int i = 0; i < M; i++)          /* Read guest list. */
    {
        scanf("%d", &ID1);
        if(couple[ID1] >= 0)                /* If one has a mate */
            couple[ID1] = SIGNED;           /*   set SIGNED */
        else                                /* Else: not in the 'couple-list' */
            couple[ID1] = SINGLE, count++;  /*   set SINGLE */
    }
    
    /* If couple[ID] is >= 0 (but not signed) but couple[couple[ID]] == SIGNED
     * (signed in), this means 'ID' didn't come but his/her mate did.
     * So his/her mate is alone in the party, set to SINGLE. */
    for(int i = 0; i < 100000; i++) 
        if(couple[i] >= 0 && couple[couple[i]] == SIGNED) 
            couple[couple[i]] = SINGLE, count++;

    /* Those whose value is SINGLE is either a bachelor or came alone */
    printf("%d\n", count);
    for(int i = 0; i < 100000; i++) 
        if(couple[i] == SINGLE)
            printf("%05d%c", i, --count ? ' ' : '\0');
    
    return 0;
}
