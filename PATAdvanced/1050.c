#include <stdio.h>

int main()
{
	char c, s1[10001];
	int s2[128] = {0};

	scanf("%[^\n]%c", s1, &c);
	while ((c = getchar()) != EOF && c != '\n')
		s2[(int)c] = 1;

	for (char *p = s1; *p; p++)
		if (!s2[(int)(*p)])
			putchar(*p);

	return 0;
}
