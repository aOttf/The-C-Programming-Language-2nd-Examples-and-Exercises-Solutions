#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* Echo */
int main(int argc, char *argv[]) {
	/*
	 * Version 1
	 * int i;
	 * for(i = 1; i < argc; i++)
	 * printf("%s%s", argv[i], (i == argc)?"":" ");
	 * printf("\n");
	 */

	/*Version 2*/
	while (--argc > 0)
		printf("%s%s", *argv++, (argc == 1) ? "" : " ");
	printf("\n");
}
