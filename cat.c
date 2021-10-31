#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <assert.h>

#define MAXLEN 1000
/* Cat */
int main(int argc, char *argv[]) {
	FILE *fp;
	void filecopy(FILE*, FILE*);

	if (argc == 1)
		filecopy(stdin, stdout);
	else {
		while (--argc > 0 && (fp = fopen(*++argv, "r"))) {
			filecopy(fp, stdout);
			fclose(fp);
		}

		if (argc) {
			fprintf(stderr, "Error occured in %s when open file %s at line %d",
			__FILE__, *argv, __LINE__ - 4);
			exit(EXIT_FAILURE);
		}
	}

	return EXIT_SUCCESS;
}

void filecopy(FILE *ifp, FILE *ofp) {
	char s[MAXLEN];

	while (fgets(s, MAXLEN, ifp))
		if (fputs(s, ofp) == EOF) {
			fprintf(stderr,
					"Error occured in %s when writing to output file, at line %d",
					__FILE__, __LINE__ - 2);
			exit(EXIT_FAILURE);
		}

	/*	Check Error	*/
	if (ferror(ifp)) {
		fprintf(stderr,
				"Error occured in %s when reading from input file at line %d",
				__FILE__, __LINE__ - 9);
		exit(EXIT_FAILURE);
	}

}
