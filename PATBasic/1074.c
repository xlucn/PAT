/**
 * 1074. 宇宙无敌加法器(20)
 * 
 * 地球人习惯使用十进制数，并且默认一个数字的每一位都是十进制的。而在PAT星人开挂的世界
 * 里，每个数字的每一位都是不同进制的，这种神奇的数字称为“PAT数”。每个PAT星人都必须熟
 * 记各位数字的进制表，例如“……0527”就表示最低位是7进制数、第2位是2进制数、第3位是5进
 * 制数、第4位是10进制数，等等。每一位的进制d或者是0（表示十进制）、或者是[2，9]区间
 * 内的整数。理论上这个进制表应该包含无穷多位数字，但从实际应用出发，PAT星人通常只需要
 * 记住前20位就够用了，以后各位默认为10进制。
 * 
 * 在这样的数字系统中，即使是简单的加法运算也变得不简单。例如对应进制表“0527”，该如何
 * 计算“6203+415”呢？我们得首先计算最低位：3+5=8；因为最低位是7进制的，所以我们得
 * 到1和1个进位。第2位是：0+1+1（进位）=2；因为此位是2进制的，所以我们得到0和1个进
 * 位。第3位是：2+4+1（进位）=7；因为此位是5进制的，所以我们得到2和1个进位。第4位
 * 是：6+1（进位）=7；因为此位是10进制的，所以我们就得到7。最后我们得到：6203+415=
 * 7201。
 * 
 * 输入格式：
 * 
 * 输入首先在第一行给出一个N位的进制表（0 < N <=20），以回车结束。 随后两行，每行给
 * 出一个不超过N位的正的PAT数。
 * 
 * 输出格式：
 * 
 * 在一行中输出两个PAT数之和。
 * 
 * 输入样例：
 * 30527
 * 06203
 * 415
 * 输出样例：
 * 7201
 */

#include <stdio.h>
#include <string.h>

int main()
{
    int nBase, nA, nB, nS = 21, base, a, b;
    char sBase[21] = {0}, sA[21] = {0}, sB[21] = {0}, sSum[22] = {0};
    
    /* Read base table, number A and B into strings */
    scanf("%s %s %s", sBase, sA, sB);
    
    nBase = strlen(sBase);
    nA = strlen(sA);
    nB = strlen(sB);
    
    for(int i = 0; i < nBase; i++)
    {
        /* Transform corresponding digit to integers */
        a = nA <= i ? 0 : sA[nA - i - 1] - '0';
        b = nB <= i ? 0 : sB[nB - i - 1] - '0';
        base = sBase[nBase - i - 1] - '0';
        base = base == 0 ? 10 : base;
        /* Calculate ith digit A + B, temperately store integers here */
        sSum[nS - i - 1] += a + b;
        sSum[nS - i - 2] += sSum[nS - i - 1] / base;
        sSum[nS - i - 1] = sSum[nS - i - 1] % base;
    }
    
    /* Change to char type */
    for(int i = 0; i < 21; i++)
        sSum[i] += '0';
    
    /* find the first non-zero bit */
    for(int first = 0; first < 21; first++) 
        if(sSum[first] != 0 && sSum[first] != '0')
        {
            puts(sSum + first);
            return 0;
        }
    /* If A + B = 0, then all bits are zero */
    printf("0");
    return 0;
}
