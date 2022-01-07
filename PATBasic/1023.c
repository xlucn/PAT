#include <stdio.h>

int main()
{
	int zero, nonzero;

	scanf("%d", &zero);
	for (int i = 1; i < 10; i++) {
		scanf("%d", &nonzero);
		while (nonzero--) {
			putchar('0' + i);
			/* after the first non-zero, print all the zeros */
			for (; zero; zero--)
				putchar('0');
		}
	}

	return 0;
}
