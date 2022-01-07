#include <stdio.h>

int main()
{
	int N, M, L, c, order_to_color[200] = {0}, color_to_order[200] = {0};
	int longest_for_color[200] = {0}, longest_before_current, max_length = 0;

	/* read number of different colors */
	scanf("%d", &N);
	/* read color-order pairs (colors start from 0, orders start from 1) */
	scanf("%d", &M);
	for (int i = M; i > 0; i--) {
		scanf("%d", &c);
		order_to_color[i] = --c;
		color_to_order[c] = i;
	}
	/* read color list */
	scanf("%d", &L);
	for (int i = 0; i < L; i++) {
		scanf("%d", &c);
		/* this color is not in the favourite list, do nothing */
		if (color_to_order[--c] == 0)
			continue;
		/* for colors of higher/equal order, find the longest sub-stripe */
		longest_before_current = 0;
		for (int j = M; j >= color_to_order[c]; j--)
			if (longest_before_current < longest_for_color[order_to_color[j]])
				longest_before_current = longest_for_color[order_to_color[j]];
		/* after this color, the length increases by 1 */
		longest_for_color[c] = longest_before_current + 1;
	}

	for (int i = 0; i < N; i++)
		if (max_length < longest_for_color[i])
			max_length = longest_for_color[i];
	printf("%d\n", max_length);

	return 0;
}
