#include <stdio.h>

int main()
{
	int N, M, counts[501] = {0}, coin;

	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		scanf("%d", &coin);
		counts[coin]++;
	}

	for (int i = 1; 2 * i - 1 < M; i++) {
		if ((i * 2 == M && counts[i] > 1)
		|| (i * 2 != M && M - i < 501 && counts[i] && counts[M - i])) {
			printf("%d %d", i, M - i);
			return 0;
		}
	}

	printf("No Solution");
	return 0;
}
