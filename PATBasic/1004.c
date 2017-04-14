/**
 * 1004. 成绩排名
 * 
 * 读入n名学生的姓名、学号、成绩，分别输出成绩最高和成绩最低学生的姓名和学号。
 * 
 * 输入格式：每个测试输入包含1个测试用例，格式为
 * 
 *   第1行：正整数n
 *   第2行：第1个学生的姓名 学号 成绩
 *   第3行：第2个学生的姓名 学号 成绩
 *   ... ... ...
 *   第n+1行：第n个学生的姓名 学号 成绩
 * 
 * 其中姓名和学号均为不超过10个字符的字符串，成绩为0到100之间的一个整数，这里保证在
 * 一组测试用例中没有两个学生的成绩是相同的。
 * 
 * 输出格式：对每个测试用例输出2行，第1行是成绩最高学生的姓名和学号，第2行是成绩最
 * 低学生的姓名和学号，字符串间有1空格。
 * 
 * 输入样例：
 * 3
 * Joe Math990112 89
 * Mike CS991301 100
 * Mary EE990830 95
 * 输出样例：
 * Mike CS991301
 * Joe Math990112
 **/
#include <stdio.h>
#include <string.h>

int main()
{
    int N;
    scanf("%d", &N);
    
    char name[2][11], id[2][11], curname[11], curid[11];
    int grade[2] = {-1, 101}, curgrade;
    
    for(int i = 0; i < N; i++)
    {
        scanf("%s %s %d", curname, curid, &curgrade);
        
        if(curgrade > grade[0])
        {
            strcpy(name[0], curname);
            strcpy(id[0], curid);
            grade[0] = curgrade;
        }
        if(curgrade < grade[1])
        {
            strcpy(name[1], curname);
            strcpy(id[1], curid);
            grade[1] = curgrade;
        }
    }
    
    printf("%s %s\n%s %s", name[0], id[0], name[1], id[1]);
    
    return 0;
}
