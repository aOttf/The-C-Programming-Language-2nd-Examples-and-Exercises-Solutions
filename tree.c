#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define MAXWORD	100

typedef struct tnode {
	char *word;
	int count;
	struct tnode *left;
	struct tnode *right;
} tnode;

tnode* talloc();
tnode* addtree(tnode*, char*);
void printtree(tnode *p);

int getword(char*, int);
int getch();
void ungetch(int);
void error(char*);

int main() {
	tnode *root = NULL;
	char word[MAXWORD];
	int c;
	while ((c = getword(word, MAXWORD)) != EOF)
		if (isalpha(c))
			root = addtree(root, word);
	printtree(root);
	return EXIT_SUCCESS;
}

int getword(char *word, int lim) {
	void incmt(int);

	int c, d, type;
	char *w = word; /*	Current Pointer	*/

	/*	Consume Blanks	*/
	while (isspace(c = getch()))
		;

	/*	Match Patterns	*/
	type = c;

	if (isalpha(c) || c == '#' || c == '_') {
		/*	a word	*/
		for (*w++ = c; --lim > 1 && (isalnum(c = getch()) || c == '_');)
			*w++ = c;

		if (lim != 1)
			ungetch(c);

	} else if (c == '/') {
		if ((c = getch()) == '*' || c == '/')
			/*	A Comment	*/
			incmt(c);
	} else if (c == '\'' || c == '"') {
		/*	A String	*/
		d = c;
		while (--lim > 0 && (c = getch()) != d && c != EOF)
			if (c != '\\' || (c = getch()) != EOF)
				*w++ = c;
	}

	*w = '\0';
	return type;
}

/*	Add a new node of the given word to the tree if the word doesn't exist in the tree
 * Otherwise increment the count of the node with the given word	*/
tnode* addtree(tnode *p, char *word) {
	if (!p) {
		/*	Create a new Node	*/
		tnode *np;
		if (!((np = talloc()) && (np->word = strdup(word))))
			error("Not Enough Memory.");

		np->count = 1;
		np->left = np->right = NULL;

		return np;
	}

	int cmp;
	if ((cmp = strcmp(word, p->word)) < 0)
		p->left = addtree(p->left, word);
	else if (cmp > 0)
		p->right = addtree(p->right, word);
	else
		p->count++;
	return p;
}

/*	Print tree in left-mid-right order	*/
void printtree(tnode *p) {
	if (p) {
		printtree(p->left);

		printf("%4d %s\n", p->count, p->word);

		printtree(p->right);
	}
}

/*	Allocate a new tree node	*/
tnode* talloc() {
	return (tnode*) malloc(sizeof(tnode));
}

/*	Jump Over a Comment Block	*/
void incmt(int type) {
	assert(type == '*' || type == '/');

	int c, lastc;
	switch (type) {
	case '*':
		// Comment Format  /* ... */
		for (c = getch();
				(lastc = c) != EOF && ((c = getch()) != '/' || lastc != '*');)
			;

		break;
	case '/':
		/*	Comment Format // ... \n */
		while ((c = getch()) != '\n' && c != EOF)
			;
		break;
	default:
		break;
	}
}

static int lastc;
int getch() {
	int c;
	if (lastc != '\0') {
		c = lastc;
		lastc = '\0';
	} else
		c = getchar();
	return c;
}

void ungetch(int c) {
	assert(!lastc);

	lastc = c;
}

void error(char *msg) {
	perror(msg);
	exit(1);
}
