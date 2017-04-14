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
    char line[82];
    fgets(line, 82, stdin);
    
    for(int index = strlen(line) - 1; index >= 0; index--)
    {
        while(index >= 0 && line[index] != ' ') index--;
        int i = index + 1;
        while(line[i] != ' ' && line[i] != '\n' && line[i]) putchar(line[i++]);
        putchar(index == -1 ? '\0' : ' ');
    }
    
    return 0;
}
