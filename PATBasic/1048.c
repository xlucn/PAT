/**
 * 1048. 数字加密(20)
 * 
 * 本题要求实现一种数字加密方法。首先固定一个加密用正整数A，对任一正整数B，将其每1位
 * 数字与A的对应位置上的数字进行以下运算：对奇数位，对应位的数字相加后对13取余——这里
 * 用J代表10、Q代表11、K代表12；对偶数位，用B的数字减去A的数字，若结果为负数，则再
 * 加10。这里令个位为第1位。
 * 
 * 输入格式：
 * 
 * 输入在一行中依次给出A和B，均为不超过100位的正整数，其间以空格分隔。
 * 
 * 输出格式：
 * 
 * 在一行中输出加密后的结果。
 * 
 * 输入样例：
 * 1234567 368782971
 * 输出样例：
 * 3695Q8118
 */

#include <stdio.h>
#include <string.h>

int main()
{
    char A[101], B[101];
    char encrypt[] = "0123456789JQK";

    scanf("%s %s", A, B);
    int lenA = strlen(A);
    int lenB = strlen(B);
    int maxlen = lenA > lenB ? lenA : lenB;
    int a, b;
    
    for(int i = 0; i < maxlen; i++)
    {
        a = lenA + i - maxlen < 0 ? 0 : A[lenA + i - maxlen] - '0';
        b = lenB + i - maxlen < 0 ? 0 : B[lenB + i - maxlen] - '0';
        
        if((maxlen - i) % 2)
            putchar(encrypt[(a + b) % 13]);
        else
            putchar('0' + (b - a < 0 ? b - a + 10 : b - a));
    }

    return 0;
}
