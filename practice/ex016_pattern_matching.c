#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int nfind(char*, char*);

void main() {

    char pat[] = "wor";
    char str[] = "hello world I am a student.";
    int rv;

    rv = nfind(str, pat);
    if (rv == -1) {
        printf("The pattern %s was not found in the string.\n", pat);
    }
    else {
        printf("The pattern %s was found at position %d in the string.\n", pat, rv);
    }
}

int nfind(char* string, char* pat) {

    /* try implementing this function yourself! */
    int i, j, start = 0;
    int lasts = strlen(string) - 1;
    int lastp = strlen(pat) - 1;
    int endmatch = lastp;
    for (i = 0, j = 0; endmatch <= lasts; endmatch++, start++) {
        if (string[endmatch] == pat[lastp])
            for (j = 0, i = start; j < lastp && string[i] == pat[j]; i++, j++);
        if (j == lastp) return start;
    }
    return -1;
}