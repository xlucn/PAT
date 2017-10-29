/**
 * 1072. 开学寄语(20)
 * 
 * 下图是上海某校的新学期开学寄语：天将降大任于斯人也，必先删其微博，卸其QQ，封其电脑，
 * 夺其手机，收其ipad，断其wifi，使其百无聊赖，然后，净面、理发、整衣，然后思过、读
 * 书、锻炼、明智、开悟、精进。而后必成大器也！
 * 
 * 本题要求你写个程序帮助这所学校的老师检查所有学生的物品，以助其成大器。
 * 
 * 输入格式：
 * 
 * 输入第一行给出两个正整数N（<= 1000）和M（<= 6），分别是学生人数和需要被查缴的物品
 * 种类数。第二行给出M个需要被查缴的物品编号，其中编号为4位数字。随后N行，每行给出一位
 * 学生的姓名缩写（由1-4个大写英文字母组成）、个人物品数量K（0 <= K <= 10）、以及
 * K个物品的编号。
 * 
 * 输出格式：
 * 
 * 顺次检查每个学生携带的物品，如果有需要被查缴的物品存在，则按以下格式输出该生的信息
 * 和其需要被查缴的物品的信息（注意行末不得有多余空格）：
 * 
 * 姓名缩写: 物品编号1 物品编号2 ……
 * 最后一行输出存在问题的学生的总人数和被查缴物品的总数。
 * 
 * 输入样例：
 * 4 2
 * 2333 6666
 * CYLL 3 1234 2345 3456
 * U 4 9966 6666 8888 6666
 * GG 2 2333 7777
 * JJ 3 0012 6666 2333
 * 
 * 输出样例：
 * U: 6666 6666
 * GG: 2333
 * JJ: 6666 2333
 * 3 5
 */

#include <stdio.h>

int main()
{
    int N, M, K, SNlist[10], SNtarget;
    char name[5];
    
    scanf("%d %d", &N, &M);
    for(int i = 0; i < M; i ++)
        scanf("%d", SNlist + i);
    
    int flag, student_total = 0, item_total = 0;
    for(int i = 0; i < N; i ++)
    {
        flag = 0;
        scanf("%s %d", name, &K);
        for(int i = 0; i < K; i++)
        {
            scanf("%d", &SNtarget);
            for(int i = 0 ; i < M; i ++)
            {
                if(SNtarget == SNlist[i])
                {
                    if(flag == 0)
                    {
                        flag = 1;
                        student_total++;
                        printf("%s:", name);
                    }
                    item_total++;
                    printf(" %04d", SNtarget);
                }
            }
        }
        if(flag) printf("\n");
   }
    printf("%d %d", student_total, item_total);

    return 0;
}
