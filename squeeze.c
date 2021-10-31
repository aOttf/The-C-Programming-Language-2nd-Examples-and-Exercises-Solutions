#include <stdlib.h>
#include <stdio.h>

void squeeze(char* s, int c){
	int i, j;
	i = j = 0;

	for(; s[i] != '\0'; i++){
		if(s[i] == c)
			s[j++] = s[i++];

	}

	s[j] = '\0';
}


