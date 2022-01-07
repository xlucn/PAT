#include <stdio.h>

int main()
{
	int N, count = 0, modified;
	char username[1000][11], password[1000][11];

	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		modified = 0;
		scanf("%s %s", username[i], password[i]);
		for (char *p = password[i]; *p; p++) {
			switch(*p) {
			case '1': *p = '@'; modified = 1; break;
			case '0': *p = '%'; modified = 1; break;
			case 'l': *p = 'L'; modified = 1; break;
			case 'O': *p = 'o'; modified = 1; break;
			default: break;
			}
		}
		if (modified)
			count++;
		else  /* mark unmodified password */
			password[i][0] = '\0';
	}

	if (count) {
		printf("%d\n", count);
		for (int i = 0; i < N; i++)
			if (password[i][0] != '\0')
				printf("%s %s\n", username[i], password[i]);
	} else {
		printf("There %s %d %s and no account is modified",
			N > 1 ? "are" : "is", N, N > 1 ? "accounts" : "account");
	}

	return 0;
}
