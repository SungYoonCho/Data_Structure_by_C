#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

void strnins(char*, char*, int);

void main() {

	char s[MAX_SIZE] = "amobile";
	char t[MAX_SIZE] = "uto";
	strnins(s, t, 1);
	printf("%s\n", s);
}

void strnins(char* s, char* t, int i) {
	char string[MAX_SIZE] = {'\0'}, * temp = string;

	if (i<0 && i > strlen(s)) {
		fprintf(stderr, "position is out of bounds.\n"); exit(1);
	}

	if (!strlen(s)) strcpy(s, t);
	else if (strlen(t)) {
		strncpy(temp, s, i);
		strcat(temp, t);
		strcat(temp, (s + i));
		strcpy(s, temp);
	}
	
}