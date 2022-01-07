#include <stdio.h>

typedef struct Node Node;
struct Node {
	int checked;
	struct Node *next;
};

int main()
{
	char data;
	int start1, start2, address, next, N;
	Node list[100000] = {0}, *p;

	scanf("%d %d %d", &start1, &start2, &N);
	/* record a linked list */
	for (int i = 0; i < N; i++) {
		scanf("%d %c %d", &address, &data, &next);
		list[address].next = next == -1 ? NULL : &list[next];
	}

	if (start1 == -1 || start2 == -1) {
		printf("-1");
		return 0;
	}
	/* First traverse the first string */
	for (p = list + start1; p; p = p->next)
		p->checked = 1;
	/* Then traverse the second looking for checked node */
	for (p = list + start2; p && !p->checked; p = p->next)
		;

	if (p)
		printf("%05ld", p - list);
	else
		printf("-1");

	return 0;
}
