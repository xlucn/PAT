#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Structure to store phone records */
typedef struct {
    char name[21];
    int month, day, hour, min, time, state;
}Record, *pRecord;

/* Compare first by name, then by date and time */
int cmp(const void *record1, const void *record2)
{
    pRecord r1 = *(pRecord*)record1, r2 = *(pRecord*)record2;
    return strcmp(r1->name, r2->name) ?
        strcmp(r1->name, r2->name) : r1->time - r2->time;
}

/* Calculate the charge of the call with start record p1 and end record p2 */
int calccharge(pRecord p1, pRecord p2, int toll[])
{
    int charge = 0, start = p1->time, end = p2->time, h, time1, time2;

    for(time1 = start; time1 < end; time1 = time2)
    {   /* Add the charge hour by hour */
        time2 = (time1 / 60 + 1) * 60; /* time2 will be the time of next hour */
        h = time1 / 60 % 24;           /* h will be the index of the hour */
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
        (*p)->time = ((*p)->day * 24 + (*p)->hour) * 60 + (*p)->min;
        (*p)->state = strcmp(state, "on-line") ? 0 : 1;
    }

    /* Sort first by name, then by date and time */
    qsort(precords, N, sizeof(pRecord), cmp);

    /* Print phone bill one by one */
    for(p = precords + 1; *p; p++)
    {
        if(strcmp((*p)->name, (*(p - 1))->name))
        {            /* A new customer, print last total amount if any */
            if(charge_total)
                printf("Total amount: $%.2f\n", charge_total * 1e-2);
            charge_total = 0;
        }
        else if((*(p - 1))->state == 1 && (*p)->state == 0)
        {            /* Still the same customer, finding on/off record pair */
            if(charge_total == 0)
                printf("%s %02d\n", (*p)->name, (*p)->month);
            charge = calccharge(*(p - 1), *p, toll);
            charge_total += charge;
            /* Print info of this call */
            printf("%02d:%02d:%02d %02d:%02d:%02d %d $%.2f\n",
                   (*(p - 1))->day, (*(p - 1))->hour, (*(p - 1))->min,
                   (*p)->day, (*p)->hour, (*p)->min,
                   (*p)->time - (*(p - 1))->time, charge * 1e-2);
        }
    }
    if(charge_total)
        printf("Total amount: $%.2f\n", charge_total * 1e-2);

    return 0;
}
