/**
 * 1040. 有几个PAT（25）
 * 
 * 字符串APPAPT中包含了两个单词“PAT”，其中第一个PAT是第2位(P),第4位(A),第6位(T)；
 * 第二个PAT是第3位(P),第4位(A),第6位(T)。
 * 
 * 现给定字符串，问一共可以形成多少个PAT？
 * 
 * 输入格式：
 * 
 * 输入只有一行，包含一个字符串，长度不超过10^5，只包含P、A、T三种字母。
 * 
 * 输出格式：
 * 
 * 在一行中输出给定字符串中包含多少个PAT。由于结果可能比较大，只输出对1000000007取
 * 余数的结果。
 * 
 * 输入样例：
 * APPAPT
 * 输出样例：
 * 2
 */
#include <stdio.h>
#define LIM 1000000007
int main()
{
    int P = 0, PA = 0, PAT = 0;
    char c;
    while((c = getchar()) != '\n')
    {
        switch(c)
        {
            case 'P':   P++;                        break;
            case 'A':   PA = (PA + P) % LIM;        break;
            case 'T':   PAT = (PAT + PA) % LIM;     break;
        }
    }
    printf("%d", PAT);
    return 0;
}
