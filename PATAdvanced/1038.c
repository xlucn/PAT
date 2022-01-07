#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp(const void *a, const void *b)
{
	char *A = (char*)a, *B = (char*)b;
	char s1[17], s2[17];
	int lenA = strlen(A), lenB = strlen(B);

	/* Repeat the numbers to form a long string
	 * e.g. 123 -> 123123123123123 */
	for (int i = 0; i < 16 / lenA; i++)
		strcpy(s1 + i * lenA, A);
	for (int i = 0; i < 16 / lenB; i++)
		strcpy(s2 + i * lenB, B);

	return strcmp(s1, s2);
}

int main()
{
	int N, k = 0, number = 0;
	char numbers[10000][9] = {{0}};

	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%s", numbers[i]);

	qsort(numbers, N, 9 * sizeof(char), cmp);

	/* Go to the first non-zero segment */
	while (k < N && number == 0)
		sscanf(numbers[k++], "%d", &number);

	/* Print the first non-zero segment */
	printf("%d", number);
	/* Print the rest */
	while (k < N)
		printf("%s", numbers[k++]);
	return 0;
}
