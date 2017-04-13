/**
 * 1043. 输出PATest(20)
 * 
 * 给定一个长度不超过10000的、仅由英文字母构成的字符串。请将字符重新调整顺序，按
 * “PATestPATest....”这样的顺序输出，并忽略其它字符。当然，六种字符的个数不一定是
 * 一样多的，若某种字符已经输出完，则余下的字符仍按PATest的顺序打印，直到所有字符都
 * 被输出。
 * 
 * 输入格式：
 * 
 * 输入在一行中给出一个长度不超过10000的、仅由英文字母构成的非空字符串。
 * 
 * 输出格式：
 * 
 * 在一行中按题目要求输出排序后的字符串。题目保证输出非空。
 * 
 * 输入样例：
 * redlesPayBestPATTopTeePHPereatitAPPT
 * 输出样例：
 * PATestPATestPTetPTePePee
 */
#include <stdio.h>
int main()
{
    char c;
    int count[128] = {0};                       /* for each ASCII char */
    int str[] = {'P', 'A', 'T', 'e', 's', 't'}; /* use as index for count[] */
    
    /* read any char other than \n and count their numbers */
    while((c = getchar()) != '\n')
        count[(int)c]++;
    
    /* among "PATest" find the most frequent char and asign its count to max */
    int max = 0;
    for(int i = 0; i < 6; i++)
        if(max < count[str[i]])
            max = count[str[i]];
    
    /* before max prints, print any char in "PATest" if it is still left */
    while(max--)
        for(int j = 0; j < 6; j++) 
            if(count[str[j]]-- > 0)
                putchar(str[j]);
    
    return 0;
}
