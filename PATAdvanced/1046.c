#include <stdio.h>

int main()
{
	int N, M, start, end, d, D[100001] = {0};

	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", D + i + 1);
		/* record the distance between the current and the first exits */
		D[i + 1] += D[i];
	}

	scanf("%d", &M);
	for (int i = 0; i < M; i++) {
		scanf("%d %d", &start, &end);
		d = --start > --end ? D[start] - D[end] : D[end] - D[start];
		/* if the distance is more than half total length, the other direction will be shorter */
		printf("%d\n", d * 2 > D[N] ? D[N] - d : d);
	}

	return 0;
}
