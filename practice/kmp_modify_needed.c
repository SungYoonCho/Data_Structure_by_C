#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _CRT_SECURE_NO_WARNINGS
#define MAX_STRING_SIZE 10000000
#define MAX_PATTERN_SIZE 3000

int pmatch(char*, char*, int);
void fail(char*);

int failure[MAX_PATTERN_SIZE];
char string[MAX_STRING_SIZE];
char pat[MAX_PATTERN_SIZE];
int p_arr[MAX_STRING_SIZE];


void main() {

    int i;
    strcpy(string, "aaaaaaa");
    strcpy(pat, "aa");
    p_arr = (int*)malloc(strlen(string) * sizeof(int));
    if (p_arr != NULL) {
        fail(pat);
        for (i = 0; i < strlen(pat); i++) {
            printf("%d ", failure[i]);
        }
        printf("\n");
        pmatch(string, pat);
        int na = sizeof(p_arr) / sizeof(p_arr[0]);
        printf("%d %d\n", na, sizeof(p_arr));
        for (i = 0; i < na; i++) {
            printf("rv: %d ", p_arr[i]);
        }
        free(p_arr);
    }
}

void fail(char* pat) {

    /* compute pattern's failure function */
    int i, j, n = strlen(pat);
    failure[0] = -1;
    for (j = 1; j < n; j++) {
        i = failure[j - 1];
        while ((pat[j] != pat[i + 1]) && (i >= 0)) i = failure[i];
        if (pat[j] == pat[i + 1]) failure[j] = i + 1;
        else failure[j] = -1;
    }
}

void pmatch(char* string, char* pat) {

    /* Knuth-Morris-Pratt string matching algorithm */
    int i = 0, j = 0, l = 0;
    int lens = strlen(string);
    int lenp = strlen(pat);
    
    for (l = 0; i < lens; l++) {

        while (i < lens && j < lenp) {
            if (string[i] == pat[j]) { i++; j++; }
            else if (j == 0) i++;
            else j = failure[j - 1] + 1;
        }
        p_arr[l] = (j == lenp) ? (i - lenp) : -1;
        j = 0;
    }
}