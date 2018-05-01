/**
 * 1069. 微博转发抽奖(20)
 * 
 * 小明PAT考了满分，高兴之余决定发起微博转发抽奖活动，从转发的网友中按顺序每隔N个人
 * 就发出一个红包。请你编写程序帮助他确定中奖名单。
 * 
 * 输入格式：
 * 
 * 输入第一行给出三个正整数M（<= 1000）、N和S，分别是转发的总量、小明决定的中奖间隔、
 * 以及第一位中奖者的序号（编号从1开始）。随后M行，顺序给出转发微博的网友的昵称（不
 * 超过20个字符、不包含空格回车的非空字符串）。
 * 
 * 注意：可能有人转发多次，但不能中奖多次。所以如果处于当前中奖位置的网友已经中过奖，
 * 则跳过他顺次取下一位。
 * 
 * 输出格式：
 * 
 * 按照输入的顺序输出中奖名单，每个昵称占一行。如果没有人中奖，则输出“Keep going...”。
 * 
 * 输入样例1：
 * 9 3 2
 * Imgonnawin!
 * PickMe
 * PickMeMeMeee
 * LookHere
 * Imgonnawin!
 * TryAgainAgain
 * TryAgainAgain
 * Imgonnawin!
 * TryAgainAgain
 * 输出样例1：
 * PickMe
 * Imgonnawin!
 * TryAgainAgain
 * 输入样例2：
 * 2 3 5
 * Imgonnawin!
 * PickMe
 * 输出样例2：
 * Keep going...
 */

#include <stdio.h>
#include <string.h>

int main()
{
    char s[1000][21] = {{0}}, line[21];
    int M, N, S, m, count = 0, r = 0;
    
    scanf("%d %d %d", &M, &N, &S);
    
    for(m = 0, S--; m < M; m++)
    {
        scanf("%s", line);
        if(m == S + count * N + r)
        {
            int flag = 1;
            for(int i = 0; i < count && flag; i++) 
                if(!strcmp(s[i], line)) 
                {
                    flag = 0; 
                    r++; 
                    break;
                }
            if(flag) 
                strcpy(s[count++], line);
        }
    }
    
    for(int i = 0; i < count; i++) 
        printf("%s\n", s[i]);
    if(!count) 
        printf("Keep going...");
    
    return 0;
}
