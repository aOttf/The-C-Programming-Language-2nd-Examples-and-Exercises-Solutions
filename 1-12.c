#include <stdio.h>
#include <stdlib.h>

#define OUT 0
#define IN 1

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	int c, state = OUT;

	while ((c = getchar()) != EOF) {
		if (c != '\n' && c != ' ' && c != '\t') {
			putchar(c);
			state = IN;
		} else if (state == IN) {
			putchar('\n');
			state = OUT;
		}
	}

}
