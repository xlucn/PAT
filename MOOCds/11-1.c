/**
 * 11-散列1 电话聊天狂人   (25分)
 * 给定大量手机用户通话记录，找出其中通话次数最多的聊天狂人。
 * 
 * 输入格式:
 * 输入首先给出正整数N（≤10^5），为通话记录条数。随后N行，每行给出一条通话记录。简单起见，
 * 这里只列出拨出方和接收方的11位数字构成的手机号码，其中以空格分隔。
 * 
 * 输出格式:
 * 在一行中给出聊天狂人的手机号码及其通话次数，其间以空格分隔。如果这样的人不唯一，则输出狂人
 * 中最小的号码及其通话次数，并且附加给出并列狂人的人数。
 * 
 * 输入样例:
4
13005711862 13588625832
13505711862 13088625832
13588625832 18087925832
15005713862 13588625832
 * 
 * 输出样例:
 * 13588625832 3
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int TABLESIZE;

int hash(long int a)
{
    a = a / 10000 % 10000 * 9 + a % 10000 * 3;
    return a % TABLESIZE;
}

typedef struct _info{
    long int number;
    int count;
}*info;

info newinfo()
{
    info item;
    item = malloc(sizeof(struct _info));
    item->number = 0;
    item->count = 0;
    return item;
}
void test(){}
int find(info list[], long int number)
{
    int current = hash(number);
    int collision = 0;
    
    while(list[current]->number != 0 && list[current]->number != number)
    {test();
        collision ++;
        current += 2 * collision - 1;
        if(current >= TABLESIZE)
        {
            current -= TABLESIZE;
        }
    }
    return current;
}

int insert(info list[], long int number)
{
    int pos = find(list, number);
    list[pos]->number = number;
    list[pos]->count++;
    return list[pos]->count;
}

int main()
{
    int N;
    scanf("%d", &N);
    /* find prime */
    TABLESIZE = N * 4;
    int isprime = 0;
    while(isprime == 0)
    {
        TABLESIZE++;
        isprime = 1;
        for(int j = 2; j <= sqrt(TABLESIZE); j++)
        {
            if(TABLESIZE % j == 0)
            {
                isprime = 0;
                break;
            }
        }
    }
    printf("%d\n", TABLESIZE);
    /* initialize */
    info *list = malloc(TABLESIZE * sizeof(info));
    for(int i = 0; i < TABLESIZE; i++)
    {
        list[i] = newinfo();
    }
    printf("D");
    for(long int i = 0; i < 200000; i++)insert(list, i + 13005711862);
    printf("D");
    
    ///* read */
    //int max = 0;
    //long int number1, number2;
    //for(int i = 0; i < N; i++)
    //{
        //int count;
        //scanf("%ld %ld", &number1, &number2);
        //if((count = insert(list, number1)) > max)
        //{
            //max = count;
        //}
        //if((count = insert(list, number2)) > max)
        //{
            //max = count;
        //}
    //}
    
    ///* find */
    //long int thenumber = 100000000000;
    //int numbercount = 0;
    //for(int i = 0; i < TABLESIZE; i++)
    //{
        //if(list[i]->count == max)
        //{
            //numbercount++;
            //if(list[i]->number < thenumber)
            //{
                //thenumber = list[i]->number;
                
            //}
        //}
    //}
    //printf("%ld %d", thenumber, max);
    //if(numbercount > 1)
    //{
        //printf(" %d", numbercount);
    //}
    
    return 0;
}
