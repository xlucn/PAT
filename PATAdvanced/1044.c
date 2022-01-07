#include <stdio.h>

int main()
{
	int N, M, D[100000] = {0}, pair[100000][2] = {{0}};

	scanf("%d %d", &N, &M);
	for (int n = 0; n < N; n++)
		scanf("%d", D + n);

	int i = 0, j = 0, sum = D[0], min = 100000000, count = 0;
	while (1) {
		if (sum <= min && sum >= M) {
			/* reset if found lower solution */
			if (sum < min) {
				min = sum;
				count = 0;
			}
			/* record */
			pair[count][0] = i;
			pair[count][1] = j;
			count ++;
		}
		/* Find closest solution */
		if (sum <= M && j < N - 1)
			sum += D[++j];
		else if (i < N - 1)
			sum -= D[i++];
		else
			break;
	}

	for (int n = 0; n < count; n++)
		printf("%d-%d\n", pair[n][0] + 1, pair[n][1] + 1);

	return 0;
}
