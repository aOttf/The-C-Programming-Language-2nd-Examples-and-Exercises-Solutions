#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXTOKEN	100

enum {
	NAME, PARENS, BRACKETS
};

int gettoken();
void dcl();
void dirdcl();

int tokentype; /*	The last read token type	*/
char token[MAXTOKEN]; /*	The last token read	*/
char name[MAXTOKEN] = { 0 };
char datatype[MAXTOKEN];
char out[100]; /*	Output	String	*/

static int lastc = '\0';

void dcl() {
	int c, n = 0;
	while ((c = gettoken()) == '*') /*	Pointer	*/
		n++;

	dirdcl();

	while (n-- > 0)
		strcat(out, "Pointer to ");
}

void dirdcl() {
	int type;

	/*	Match pattern (dcl)	*/
	if (tokentype == '(') {
		dcl();
		if (tokentype != ')')
			perror("Missing )\n");
	}

	/*	Match Pattern name	*/
	else if (tokentype == NAME)
		strcpy(name, token);

	else
		perror("Direct-dcl expects name or (dcl) at the beginning.\n");

	/*	Match Pattern parens and brackets	*/
	while ((type = gettoken()) == PARENS || type == BRACKETS) {
		if (type == PARENS)
			strcat(out, "function returning ");
		else {
			strcat(out, "array ");
			strcat(out, token);
			strcat(out, " of ");
		}
	}
}

int getch() {
	int c;

	if (lastc) {
		c = lastc;
		lastc = '\0';
	} else
		c = getchar();

	return c;
}

int gettoken() {
	int getch();

	int i, c;

	/*	Consume Blanks	*/
	while ((c = getch()) == '\t' || c == ' ')
		;

	switch (c) {
	case '(':
		if ((c = getch()) == ')') {
			tokentype = PARENS;
			strcpy(token, "()");
		} else {
			lastc = c;
			tokentype = '(';
		}
		break;
	case '[':
		for (i = 0; (token[i++] = c) != ']'; c = getch())
			;
		token[i] = '\0';
		tokentype = BRACKETS;
		break;
	default:
		if (isalpha(c)) {
			for (i = 0; isalpha(c); c = getch())
				token[i++] = c;
			token[i] = '\0';
			lastc = c;
			tokentype = NAME;
		} else {
			/*	Pointer *, Right Paren ), newline \n */
			tokentype = c;
		}
		break;
	}

	return tokentype;
}

int main(int argc, char *argv[]) {
	setvbuf(stdout, NULL, _IONBF, 0);
	int type;
	while ((type = gettoken()) != EOF) {
		if (type != NAME)
			perror("Missing Data Type Declareation\n");

		strcpy(datatype, token);
		dcl();

		if (tokentype != '\n')
			perror("Syntax Error.\n");

		printf("%s:	%s %s\n", name, out, datatype);
	}

	return EXIT_SUCCESS;
}
