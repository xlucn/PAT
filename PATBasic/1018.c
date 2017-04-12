/**
 * 1018. 锤子剪刀布 (20)
 * 
 * 
 * 大家应该都会玩“锤子剪刀布”的游戏：两人同时给出手势，胜负规则如图所示：
 * 
 * 图略
 * 
 * 现给出两人的交锋记录，请统计双方的胜、平、负次数，并且给出双方分别出什么手势的
 * 胜算最大。
 * 
 * 输入格式：
 * 
 * 输入第1行给出正整数N（<=105），即双方交锋的次数。随后N行，每行给出一次交锋的信息，
 * 即甲、乙双方同时给出的的手势。C代表“锤子”、J代表“剪刀”、B代表“布”，第1个字母代表
 * 甲方，第2个代表乙方，中间有1个空格。
 * 
 * 输出格式：
 * 
 * 输出第1、2行分别给出甲、乙的胜、平、负次数，数字间以1个空格分隔。第3行给出两个字
 * 母，分别代表甲、乙获胜次数最多的手势，中间有1个空格。如果解不唯一，则输出按字母序
 * 最小的解。
 * 
 * 输入样例：
 * 10
 * C J
 * J B
 * C B
 * B B
 * B C
 * C C
 * C B
 * J B
 * B C
 * J J
 * 输出样例：
 * 5 3 2
 * 2 3 5
 * B B
 */
#include <stdio.h>
char max(int B, int C, int J)
{
    if(B >= C && B >= J) return 'B';
    if(C >  B && C >= J) return 'C';
    /* J > B && J > C */ return 'J';
}
int main()
{
    int N;
    char line[5];
    int AwinB = 0, AwinC = 0, AwinJ = 0;
    int BwinB = 0, BwinC = 0, BwinJ = 0;
    
    scanf("%d", &N);
    while(getchar() != '\n');
    for(int i = 0; i < N; i++)
    {
        fgets(line, 5, stdin);
        if(line[0] == 'B' && line[2] == 'C') AwinB++;
        if(line[0] == 'C' && line[2] == 'J') AwinC++;
        if(line[0] == 'J' && line[2] == 'B') AwinJ++;
        if(line[0] == 'B' && line[2] == 'J') BwinJ++;
        if(line[0] == 'C' && line[2] == 'B') BwinB++;
        if(line[0] == 'J' && line[2] == 'C') BwinC++;
    }
    
    int Awin = AwinB + AwinC + AwinJ;
    int Bwin = BwinB + BwinC + BwinJ;
    int Tie = N - Awin - Bwin;
    printf("%d %d %d\n", Awin, Tie, Bwin);
    printf("%d %d %d\n", Bwin, Tie, Awin);
    printf("%c %c", max(AwinB, AwinC, AwinJ), max(BwinB, BwinC, BwinJ));
    return 0;
}
