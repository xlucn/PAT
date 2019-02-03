#include <stdio.h>
#include <ctype.h>

int main()
{
    char str1[61], str2[61], str3[61], str4[61];
    scanf("%s %s %s %s", str1, str2, str3, str4);

    /* Find day, same char from [A-G] and same position in frist two lines */
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
