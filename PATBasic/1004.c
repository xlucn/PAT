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
#include <stdlib.h>

/* a struct type to store the name, ID and grade */
struct _Student{
    char name[11];
    char ID[11];
    int grade;
};
typedef struct _Student *Student;

int main()
{
    int N, max = 0, min = 0;
    scanf("%d", &N);
    
    Student *students = (Student*)malloc(N * sizeof(Student));
    for(int i = 0; i < N; i++)
    {
        students[i] = (Student)malloc(sizeof(struct _Student));
        scanf("%s %s %d", students[i]->name, students[i]->ID, &students[i]->grade);
        
        if(students[i]->grade > students[max]->grade)   max = i;
        if(students[i]->grade < students[min]->grade)   min = i;
    }
    
    printf("%s %s\n%s %s", students[max]->name, students[max]->ID, 
                           students[min]->name, students[min]->ID);
    
    for(int i = 0; i < N; i++) free(students[i]); free(students);
    
    return 0;
}
