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
    char line[81], buffer1[81] = {0}, buffer2[81] = {0};
    fgets(line, 81, stdin);
    
    char *newline = buffer1, *word = buffer2, *temp;
    strcpy(word, strtok(line, " \n"));
    while(1)
    {
        /* swap */
        temp = word;
        word = newline;
        newline = temp;
        
        strcat(newline, " ");
        strcat(newline, word);
        
        if((temp = strtok(NULL, " \n")) != NULL)
        {
            strcpy(word, temp);
        }
        else
        {
            break;
        }
    }
    newline[strlen(newline) - 1] = '\0';
    puts(newline);
    
    return 0;
}
