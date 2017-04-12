/**
 * 1014. 福尔摩斯的约会 (20)
 * 
 * 大侦探福尔摩斯接到一张奇怪的字条：“我们约会吧！ 
 * 3485djDkxh4hhGE 
 * 2984akDfkkkkggEdsb 
 * s&hgsfdk 
 * d&Hyscvnm”。大侦探很快就明白了，字条上奇怪的乱码实际上就是约会的时间
 * “星期四 14:04”，因为前面两字符串中第1对相同的大写英文字母（大小写有区分）
 * 是第4个字母'D'，代表星期四；第2对相同的字符是'E'，那是第5个英文字母，代表
 * 一天里的第14个钟头（于是一天的0点到23点由数字0到9、以及大写字母A到N表示）；
 * 后面两字符串第1对相同的英文字母's'出现在第4个位置（从0开始计数）上，代表
 * 第4分钟。现给定两对字符串，请帮助福尔摩斯解码得到约会的时间。
 * 
 * 输入格式：
 * 
 * 输入在4行中分别给出4个非空、不包含空格、且长度不超过60的字符串。
 * 
 * 输出格式：
 * 
 * 在一行中输出约会的时间，格式为“DAY HH:MM”，其中“DAY”是某星期的3字符缩写，即
 * MON表示星期一，TUE表示星期二，WED表示星期三，THU表示星期四，FRI表示星期五，
 * SAT表示星期六，SUN表示星期日。题目输入保证每个测试存在唯一解。
 * 
 * 输入样例：
 * 3485djDkxh4hhGE 
 * 2984akDfkkkkggEdsb 
 * s&hgsfdk 
 * d&Hyscvnm
 * 输出样例：
 * THU 14:04
 **/
#include <stdio.h>
#include <ctype.h>
int main()
{
    /* the length of string is not more than 60, so the length of 
    character array should be at least 62: 60+\n\0 */
    char str1[61], str2[61], str3[61], str4[61];
    scanf("%s %s %s %s", str1, str2, str3, str4);
    
    /* Find day, same character from [A-G] and same position from frist two lines */
    int DAY;
    char *weekdays[] = {"MON", "TUE", "WED", "THU", "FRI", "SAT", "SUN"};
    for(DAY = 0; str1[DAY] && str2[DAY]; DAY++)
        if(str1[DAY] == str2[DAY] && str1[DAY] >= 'A' && str1[DAY] <= 'G')
        {
            printf("%s", weekdays[str1[DAY] - 'A']);
            break;
        }
    
    /* Find hour, picking up from DAY, same character and position, [A-N|0-9] */
    int HH;
    for(HH = DAY + 1; str1[HH] && str2[HH]; HH++)
        if(str1[HH] == str2[HH])
        {
            if(str1[HH] >= 'A' && str1[HH] <= 'N')
            {
                printf(" %02d", str1[HH] - 'A' + 10);
                break;
            }
            if(isdigit(str1[HH]))
            {
                printf(" %02d", str1[HH] - '0');
                break;
            }
        }
    
    /* Find minute, same alphabet character from last two lines */
    int MM;
    for(MM = 0; str3[MM] && str4[MM]; MM++)
        if(str3[MM] == str4[MM] && isalpha(str3[MM]))
        {
            printf(":%02d", MM);
            break;
        }
    
    return 0;
}
