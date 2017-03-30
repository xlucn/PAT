/**
 * 1009. 说反话
 * 给定一句英语，要求你编写程序，将句中所有单词的顺序颠倒输出。
 * 
 * 输入格式：测试输入包含一个测试用例，在一行内给出总长度不超过80的字符串。字符串
 * 由若干单词和若干空格组成，其中单词是由英文字母（大小写有区分）组成的字符串，
 * 单词之间用1个空格分开，输入保证句子末尾没有多余的空格。
 * 
 * 输出格式：每个测试用例的输出占一行，输出倒序后的句子。
 * 
 * 输入样例：
 * Hello World Here I Come
 * 输出样例：
 * Come I Here World Hello
 **/
#include <stdio.h>
#include <string.h>
int main()
{
    char line[81], line1[81] = "", line2[81];
    char *newline, *word, *temp;
    fgets(line, 81, stdin);
    
    newline = line1;
    word = line2;
    strcpy(word, strtok(line, " \n"));
    while(word != NULL)
    {
        /* swap */
        temp = word;
        word = newline;
        newline = temp;
        
        strcat(newline, " ");
        strcat(newline, word);
        
        temp = strtok(NULL, " \n");
        if(temp != NULL)
        {
            strcpy(word, temp);
        }
        else
        {
            word = NULL;
        }
    }
    newline[strlen(newline) - 1] = '\0';
    puts(newline);
    
    return 0;
}
