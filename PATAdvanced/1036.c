#include <stdio.h>

typedef struct student {
    char name[11];
    char gender;
    char ID[11];
} Student;

int main()
{
    int N, grade, gradeF = -1, gradeM = 101;
    Student students[101] = {0}, s;

    scanf("%d", &N);
    for(int i = 0; i < N; i++)
    {
        scanf("%s %c %s %d", s.name, &s.gender, s.ID, &grade);
        students[grade] = s;
        if(s.gender == 'F')
            gradeF = grade > gradeF ? grade : gradeF;
        else
            gradeM = grade < gradeM ? grade : gradeM;
    }

    if(gradeF != -1)
        printf("%s %s\n", students[gradeF].name, students[gradeF].ID);
    else
        printf("Absent\n");

    if(gradeM != 101)
        printf("%s %s\n", students[gradeM].name, students[gradeM].ID);
    else
        printf("Absent\n");

    if(gradeM == 101 || gradeF == -1)
        printf("NA");
    else
        printf("%d", gradeF - gradeM);

    return 0;
}
