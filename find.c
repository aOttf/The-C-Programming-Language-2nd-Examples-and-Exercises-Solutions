#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define MAXLINE 1000

int getline1(char *line, int max) {
	int i, c;

	for (i = 0; i < max - 1 && (c = getchar()) != '\n' && c != EOF; i++)
		line[i] = c;

	if (c == '\n')
		line[i++] = c;
	line[i] = '\0';

	return i;
}
/* find */
int main(int argc, char *argv[]) {
	char line[MAXLINE];
	long lineno = 0;
	int c, except = 0, no = 0, found = 0;

	/*Set Optional arguments */
	while (--argc > 0 && (*++argv)[0] == '-')
		while ((c = *++argv[0]))
			switch (c) {
			case 'x':
				except = 1;
				break;
			case 'n':
				no = 1;
				break;
			default:
				perror("Illegal Command.\n");
				argc = 0;
				found = -1;
				break;

			}

	if (argc != 1)
		puts("Find -x -n pattern.");
	else {
		while (getline1(line, MAXLINE) > 0) {
			lineno++;
			if ((strstr(line, argv[0]) != NULL) != except) {
				if (no)
					printf("%ld", lineno);
				printf("%s", line);
				found++;
			}
		}
	}
	return found;
}
