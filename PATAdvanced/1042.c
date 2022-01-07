#include <stdio.h>

int main()
{
	int count, order[54], deck[54], pos;
	char types[] = "SHCDJ";

	scanf("%d", &count);
	for (int i = 0; i < 54; i++)
		scanf("%d", order + i);

	for (int i = 0; i < 54; i++) {
		pos = i;
		for (int j = 0; j < count; j++)
			pos = order[pos] - 1;  /* the input order[] was 1 based */
		deck[pos] = i;
	}

	for (int i = 0; i < 54; i++) {
		printf("%c", types[deck[i] / 13]);
		printf("%d", deck[i] % 13 + 1);
		printf("%c", i == 53 ? '\0' : ' ');
	}

	return 0;
}
