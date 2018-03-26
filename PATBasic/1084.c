/**
 * 1084. 外观数列 (20)
 *
 * 外观数列是指具有以下特点的整数序列：
 *
 * d, d1, d111, d113, d11231, d112213111, ...
 *
 * 它从不等于 1 的数字 d 开始，序列的第 n+1 项是对第 n 项的描述。比如第 2 项表示
 * 第 1 项有 1 个 d，所以就是 d1；第 2 项是 1 个 d（对应 d1）和 1 个 1（对应
 * 11），所以第 3 项就是 d111。又比如第 4 项是 d113，其描述就是 1 个 d，2 个 1，
 * 1 个 3，所以下一项就是 d11231。当然这个定义对 d = 1 也成立。本题要求你推算任
 * 意给定数字 d 的外观数列的第 N 项。
 *
 * 输入格式：
 *
 * 输入第一行给出[0,9]范围内的一个整数 d、以及一个正整数 N（<=40），用空格分隔。
 *
 * 输出格式：
 *
 * 在一行中给出数字 d 的外观数列的第 N 项。
 * 输入样例：
 *
 * 1 8
 *
 * 输出样例：
 *
 * 1123123111
 **/

#include <stdio.h>

int main()
{
    int N, count;
    char string1[100000] = {0}, string2[100000] = {0};
    char *s1 = string1, *s2 = string2, *temp;
    char *p1, *p2;
    
    scanf("%s", s1);
    scanf("%d", &N);
    
    for(int i = 1; i < N; i++)  /* Loop through nth string */
    {
        for(p1 = s1 + 1, p2 = s2, count = 1; *(p1 - 1); p1++)
        {
            if(*p1 != *(p1 - 1))    /* New char or end */
            {
                *p2++ = *(p1 - 1);  /* Record into s2 */
                *p2++ = count + '0';
                count = 1;          /* Reset count */
            }
            else                    /* Same char, increase count */
            {
                count++;
            }
        }
        
        /* Swap */
        temp = s1, s1 = s2, s2 = temp;
    }
    
    puts(s1);
    
    return 0;
}
