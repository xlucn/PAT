#include <stdio.h>

int main()
{
	char c;
	int num;
	scanf("%d", &num);
	/* read the rest of the line, make sure to start from a new line later */
	while ((c = getchar()) != '\n');

	for (int i = 0; i < num; i++) {
		/* pos: indicate the position of current index for count[]     */
		/* count[3]: number of As; before P, between P & T and after T */
		int pos = 0, count[3] = {0, 0, 0};
		while ((c = getchar()) != EOF) {
			if (c == 'A')                   /* count 'A's     */
				count[pos]++;
			else if (c == 'P' && pos == 0)  /* one P before T */
				pos = 1;
			else if (c == 'T' && pos == 1)  /* one T after P  */
				pos = 2;
			else                            /* 'wrong' string */
				break;
		}

		if (c == '\n'                       /* 1. no other characters at end */
		&& pos == 2                         /* 2. appearance of 'P' and 'T'  */
		&& count[1]                         /* 3. existance of 'A'           */
		&& count[2] == count[1] * count[0]) /* 4. relation between numbers   */
			puts("YES");
		else
			puts("NO");

		/* read the rest of the line */
		if (c != '\n')
			while ((c = getchar()) != EOF && c != '\n');
	}

	return 0;
}
