/**
 * 1016. Phone Bills (25)
 * 
 * A long-distance telephone company charges its customers by the following 
 * rules:
 * 
 * Making a long-distance call costs a certain amount per minute, depending on 
 * the time of day when the call is made. When a customer starts connecting a 
 * long-distance call, the time will be recorded, and so will be the time when 
 * the customer hangs up the phone. Every calendar month, a bill is sent to the 
 * customer for each minute called (at a rate determined by the time of day). 
 * Your job is to prepare the bills for each month, given a set of phone call 
 * records.
 * 
 * Input Specification:
 * 
 * Each input file contains one test case. Each case has two parts: the rate 
 * structure, and the phone call records.
 * 
 * The rate structure consists of a line with 24 non-negative integers denoting 
 * the toll (cents/minute) from 00:00 - 01:00, the toll from 01:00 - 02:00, and 
 * so on for each hour in the day.
 * 
 * The next line contains a positive number N (<= 1000), followed by N lines of 
 * records. Each phone call record consists of the name of the customer (string 
 * of up to 20 characters without space), the time and date (mm:dd:hh:mm), and 
 * the word "on-line" or "off-line".
 * 
 * For each test case, all dates will be within a single month. Each "on-line" 
 * record is paired with the chronologically next record for the same customer 
 * provided it is an "off-line" record. Any "on-line" records that are not 
 * paired with an "off-line" record are ignored, as are "off-line" records not 
 * paired with an "on-line" record. It is guaranteed that at least one call is 
 * well paired in the input. You may assume that no two records for the same 
 * customer have the same time. Times are recorded using a 24-hour clock.
 * 
 * Output Specification:
 * 
 * For each test case, you must print a phone bill for each customer.
 * 
 * Bills must be printed in alphabetical order of customers' names. For each 
 * customer, first print in a line the name of the customer and the month of 
 * the bill in the format shown by the sample. Then for each time period of a 
 * call, print in one line the beginning and ending time and date (dd:hh:mm), 
 * the lasting time (in minute) and the charge of the call. The calls must be 
 * listed in chronological order. Finally, print the total charge for the month 
 * in the format shown by the sample.
 * 
 * Sample Input:
 * 
 * 10 10 10 10 10 10 20 20 20 15 15 15 15 15 15 15 20 30 20 15 15 10 10 10
 * 10
 * CYLL 01:01:06:01 on-line
 * CYLL 01:28:16:05 off-line
 * CYJJ 01:01:07:00 off-line
 * CYLL 01:01:08:03 off-line
 * CYJJ 01:01:05:59 on-line
 * aaa 01:01:01:03 on-line
 * aaa 01:02:00:01 on-line
 * CYLL 01:28:15:41 on-line
 * aaa 01:05:02:24 on-line
 * aaa 01:04:23:59 off-line
 * 
 * Sample Output:
 * 
 * CYJJ 01
 * 01:05:59 01:07:00 61 $12.10
 * Total amount: $12.10
 * CYLL 01
 * 01:06:01 01:08:03 122 $24.40
 * 28:15:41 28:16:05 24 $3.85
 * Total amount: $28.25
 * aaa 01
 * 02:00:01 04:23:59 4318 $638.80
 * Total amount: $638.80
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ON 1
#define OFF 0
#define TIME(P) (((P)->day * 24 + (P)->hour) * 60 + (P)->min)

/* Struct to store phone records */
typedef struct {
    char name[21];
    int month, day, hour, min, state;
}Record, *pRecord;

/* Compare first by name, then by date and time */
int cmp(const void *record1, const void *record2)
{
    pRecord r1 = *(pRecord*)record1;
    pRecord r2 = *(pRecord*)record2;
    
    if(strcmp(r1->name, r2->name))
        return strcmp(r1->name, r2->name);
    else if(r1->month - r2->month)
        return r1->month - r2->month;
    else if(r1->day - r2->day)
        return r1->day - r2->day;
    else if(r1->hour - r2->hour)
        return r1->hour - r2->hour;
    else
        return r1->min - r2->min;
}

/* Calculate the charge of the call with start record p1 and end record p2 */
int calccharge(pRecord p1, pRecord p2, int toll[])
{
    /* Convert time to unit of minite */
    int charge = 0, start = TIME(p1), end = TIME(p2);
    int h, time1, time2;
    
    /* Add the charge of the call hour by hour */
    for(time1 = start; time1 < end; time1 = time2)
    {
        /* time will be the time of next hour */
        time2 = time1 / 60 * 60 + 60;
        /* h will be the index of the hour in a day */
        h = time1 / 60 % 24;
        /* Add the charge within this hour */
        charge += ((time2 > end ? end : time2) - time1) * toll[h];
    }
    
    return charge;
}

int main()
{
    char state[9];
    int N, toll[24], charge, charge_total = 0;
    Record records[1001] = {0};
    pRecord precords[1001] = {0}, *p = precords;
    
    /* Read data */
    for(int i = 0; i < 24; i++)
        scanf("%d", toll + i);
    scanf("%d", &N);
    for(int i = 0; i < N; i++, p++)
    {
        *p = records + i;
        scanf("%s %d:%d:%d:%d %s", (*p)->name, 
              &(*p)->month, &(*p)->day, &(*p)->hour, &(*p)->min, state);
        (*p)->state = strcmp(state, "on-line") ? OFF : ON;
    }
    
    /* Sort first by name, then by date and time */
    qsort(precords, N, sizeof(pRecord), cmp);
    
    /* Print phone bill one by one */
    printf("%s %02d\n", precords[0]->name, precords[0]->month);
    for(p = precords + 1; *p; p++)
    { 
        if(strcmp((*p)->name, (*(p - 1))->name))      /* A new customer */
        {
            printf("Total amount: $%.2f\n", charge_total * 1e-2);
            printf("%s %02d\n", (*p)->name, (*p)->month);
            charge_total = 0;
        }
        else if((*(p - 1))->state == ON && (*p)->state == OFF)
        {            /* Still the same customer, finding on/off record pair */
            charge = calccharge(*(p - 1), *p, toll);
            charge_total += charge;
            /* Print info of this call */
            printf("%02d:%02d:%02d %02d:%02d:%02d %d $%.2f\n", 
                   (*(p - 1))->day, (*(p - 1))->hour, (*(p - 1))->min,
                   (*p)->day, (*p)->hour, (*p)->min,
                   TIME(*p) - TIME(*(p - 1)), charge * 1e-2);  
        }
    }
    printf("Total amount: $%.2f\n", charge_total * 1e-2);
    
    return 0;
}
