#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "unistd.h"

#define PERMS 0666

/*	Implementation of cp	*/
int main(int argc, char *argv[]) {
	char buf[BUFSIZ];
	int f1, f2, n;

	if (argc != 3)
		error("Usage: cp from to");
	if ((f1 = open(argv[1], O_RDONLY, 0)) == -1)
		error("cp : Cannot Open %s", argv[1]);
	if ((f2 = creat(argv[2], PERMS)) == -1)
		error("cp : Cannot Create %s, mode %03o", argv[2], PERMS);

	while ((n = read(f1, buf, sizeof buf)) > 0)
		if (write(f2, buf, sizeof buf) != n)
			error("cp : Write Error on file %s", argv[2]);

	return EXIT_SUCCESS;
}
