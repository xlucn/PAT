/**
 * 1028. 人口普查(20)
 * 
 * 某城镇进行人口普查，得到了全体居民的生日。现请你写个程序，找出镇上最年长和最年轻的人。
 * 
 * 这里确保每个输入的日期都是合法的，但不一定是合理的——假设已知镇上没有超过200岁的
 * 老人，而今天是2014年9月6日，所以超过200岁的生日和未出生的生日都是不合理的，应该
 * 被过滤掉。
 * 
 * 输入格式：
 * 
 * 输入在第一行给出正整数N，取值在(0, 10^5]；随后N行，每行给出1个人的姓名（由不超过
 * 5个英文字母组成的字符串）、以及按“yyyy/mm/dd”（即年/月/日）格式给出的生日。题目
 * 保证最年长和最年轻的人没有并列。
 * 
 * 输出格式：
 * 
 * 在一行中顺序输出有效生日的个数、最年长人和最年轻人的姓名，其间以空格分隔。
 * 
 * 输入样例：
 * 5
 * John 2001/05/12
 * Tom 1814/09/06
 * Ann 2121/01/30
 * James 1814/09/05
 * Steve 1967/11/20
 * 输出样例：
 * 3 Tom John
 *
 * (暂未全部通过)
 */
#include <stdio.h>
#include <string.h>
#define date(S) (S + S[18] + 1) /* point to S[18] + 1 chars after S */

int main()
{
    int N;
    /* "NAMES YYYY/MM/DD\n\0[s]" 18 chars is needed, the 19th record the position of ' ' */
    char current[19] = {0}, eldest[19] = {0}, youngest[19] = {0};
    fgets(current, 18, stdin);
    sscanf(current, "%d", &N);
    
    for(int i = 0; i < N; )
    {
        fgets(current, 18, stdin);                              /* read */
        for(current[18] = 0; *(current + current[18]) != ' '; current[18]++) ; /* record the position of ' ' */
        
        /* Luckily we just have to compare the string to know who is older or younger */
        if(strncmp(date(current), "1814/09/06", 10) >= 0 &&          
           strncmp(date(current), "2014/09/06", 10) <= 0)       /* legal */
        {           
            if(eldest[0] == '\0' || youngest[0] == '\0')                /* empty */ 
            {           
                memcpy(eldest, current, 19);
                memcpy(youngest, current, 19);
            } 
            else if(strncmp(date(current), date(eldest), 10) <= 0)      /* older than eldest */
            {     
                memcpy(eldest, current, 19);
            } 
            else if(strncmp(date(current), date(youngest), 10) >= 0)    /* younger than youngest */
            {   
                memcpy(youngest, current, 19);
            }
            i++;
        }
        else                                                    /* illegal */
        {
            N--;
        }
    }
    
    if(N)           /* use %.[precision]s to write first [precision] chars */
        printf("%d %.*s %.*s", N, eldest[18], eldest, youngest[18], youngest);
    else 
        printf("0");
    
    return 0;
}
