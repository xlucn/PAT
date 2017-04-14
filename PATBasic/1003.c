/**
 * 1003. 我要通过！
 * “答案正确”是自动判题系统给出的最令人欢喜的回复。本题属于PAT的“答案正确”大派送
 *  —— 只要读入的字符串满足下列条件，系统就输出“答案正确”，否则输出“答案错误”。
 * 
 * 得到“答案正确”的条件是：
 * 
 * 1. 字符串中必须仅有P, A, T这三种字符，不可以包含其它字符；
 * 2. 任意形如 xPATx 的字符串都可以获得“答案正确”，其中 x 或者是空字符串，或者
 * 是仅由字母 A 组成的字符串；
 * 3. 如果 aPbTc 是正确的，那么 aPbATca 也是正确的，其中 a, b, c 均或者是空字符
 * 串，或者是仅由字母 A 组成的字符串。
 * 
 * 现在就请你为PAT写一个自动裁判程序，判定哪些字符串是可以获得“答案正确”的。
 * 输入格式： 每个测试输入包含1个测试用例。第1行给出一个自然数n (<10)，是需要检测
 * 的字符串个数。接下来每个字符串占一行，字符串长度不超过100，且不包含空格。
 * 
 * 输出格式：每个字符串的检测结果占一行，如果该字符串可以获得“答案正确”，则输出
 * YES，否则输出NO。
 * 
 * 输入样例：
 * 8
 * PAT
 * PAAT
 * AAPATAA
 * AAPAATAAAA
 * xPATx
 * PT
 * Whatever
 * APAAATAA
 * 输出样例：
 * YES
 * YES
 * YES
 * YES
 * NO
 * NO
 * NO
 * NO
 **/

#include <stdio.h>
int main()
{
    char c;
    int num;
    scanf("%d", &num);
    while(getchar() != '\n') ; /* need to read the rest of the line, make sure starting from a new line later */
    
    for(int i = 0; i < num; i++)
    {
        /* three numbers to count number of As: before P, between P&T and after T */
        int pos = 0, count[3] = {0, 0, 0};
        while((c = getchar()) != '\n')
        {
            if(c == 'A')                    count[pos]++;
            else if(c == 'P' && pos == 0)   pos = 1;        /* should have only one P and only before T */
            else if(c == 'T' && pos == 1)   pos = 2;        /* should have only one T and only after P */
            else                            break;          /* 'wrong' string */
        }
        
        if(c == '\n' && pos == 2                            /* correct appearance of P and T, no other chars */
         && count[1] && count[2] == count[1] * count[0])    /* relation between three groups of As */
            puts("YES");
        else
            puts("NO");
        
        if(c != '\n') while((c = getchar()) != '\n'); /* still, read the whole line */
    }
    return 0;
}
