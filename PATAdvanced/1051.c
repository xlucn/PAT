#include <stdio.h>

int main()
{
	char c;
	int M, N, K, stack[7] = {0}, top, pushed, popped, wanted;

	scanf("%d %d %d", &M, &N, &K);
	for (int i = 0; i < K; i++) {
		top = -1;
		pushed = 0;
		popped = 0;
		/* push */
		stack[++top] = ++pushed;
		scanf("%d", &wanted);
		for ( ; ; ) {
			if (top != -1 && stack[top] == wanted) {
				/* pop */
				stack[top--] = 0;
				popped++;
				/* read */
				if (popped < N) {
						scanf("%d", &wanted);
						continue;
				}
				else
						break;
			}
			/* push */
			if (pushed < N && top < M - 1)
				stack[++top] = ++pushed;
			else
				break;
		}
		printf("%s\n", popped < N ? "NO" : "YES");
		while ((c = getchar()) != EOF && c != '\n');
	}

	return 0;
}
