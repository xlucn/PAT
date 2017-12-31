/**
 * 1078. 字符串压缩与解压 (20)
 * 
 * 文本压缩有很多种方法，这里我们只考虑最简单的一种：把由相同字符组成的一个连续的片段
 * 用这个字符和片段中含有这个字符的个数来表示。例如 ccccc 就用 5c 来表示。如果字符
 * 没有重复，就原样输出。例如 aba 压缩后仍然是 aba。
 * 
 * 解压方法就是反过来，把形如 5c 这样的表示恢复为 ccccc。
 * 
 * 本题需要你根据压缩或解压的要求，对给定字符串进行处理。这里我们简单地假设原始字符串
 * 是完全由英文字母和空格组成的非空字符串。
 * 
 * 输入格式：
 * 
 * 输入第一行给出一个字符，如果是 C 就表示下面的字符串需要被压缩；如果是 D 就表示下
 * 面的字符串需要被解压。第二行给出需要被压缩或解压的不超过1000个字符的字符串，以回
 * 车结尾。题目保证字符重复个数在整型范围内，且输出文件不超过1MB。
 * 
 * 输出格式：
 * 
 * 根据要求压缩或解压字符串，并在一行中输出结果。
 * 
 * 输入样例 1：
 * C
 * TTTTThhiiiis isssss a   tesssst CAaaa as
 * 输出样例 1：
 * 5T2h4is i5s a3 te4st CA3a as
 * 输入样例 2：
 * D
 * 5T2h4is i5s a3 te4st CA3a as10Z
 * 输出样例 2：
 * TTTTThhiiiis isssss a   tesssst CAaaa asZZZZZZZZZZ
 **/

#include <stdio.h>

void compress()
{
    char previous = getchar(), current;
    int count = 1;
    
    while((current = getchar()))
    {
        if(current == previous)
        {
            count++;                /* Increament count */
        }
        else
        {
            if(count > 1)           /* Only print if count > 1 */
                printf("%d", count);
            putchar(previous);
            previous = current;
            count = 1;
        }
        
        if(current == '\n')         /* Don't put this in while() */
            break;
    }
}

void decompress()
{
    char c;
    int count = 0;
    
    while((c = getchar()) != '\n')
    {
        if(c >= '0' && c <= '9') /* If it is number */
        {
            count = count * 10 + c - '0';   /* Accumulate count */
        }
        else                     /* If it is not number */
        {
            if(count == 0)                  /* No number before char */
                count = 1;                      /* print once */
            for(int i = 0; i < count; i++)  /* Or print 'count' times */
                putchar(c);
            count = 0;                      /* Reset 'count' */
        }
    }
}

int main()
{
    switch(getchar())
    {
        case 'C':
            while(getchar() != '\n');
            compress();
            break;
        case 'D':
            while(getchar() != '\n');
            decompress();
            break;
        default:
            break;
    }
    
    return 0;
}
