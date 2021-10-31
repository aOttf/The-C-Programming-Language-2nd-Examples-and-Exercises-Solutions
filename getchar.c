#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <fcntl.h>
#include "unistd.h"

/*unbuffered version of getchar */
int getchar1() {
	char c;

	return (read(0, &c, 1) == 1) ? (unsigned char)c : EOF;
}

/*buffered version of getchar */
int getchar2() {
	static char buf[BUFSIZ], *bptr = buf;
	static int n = 0;

	if (n == 0) /*No characters buffered */
		n = read(0, buf, sizeof buf);

	return (n-- > 0) ? (unsigned char)*bptr++ : EOF;
}

