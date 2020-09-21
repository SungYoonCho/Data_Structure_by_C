#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _CRT_SECURE_NO_WARNINGS
#define MAX_STRING_SIZE 10000000
#define MAX_PATTERN_SIZE 3000

int nfind(char*, char*);
char string[MAX_STRING_SIZE];
char pat[MAX_PATTERN_SIZE];
int p_arr[MAX_STRING_SIZE];

void main() {
    int idx, i;
    FILE* fp1;
    FILE* fp2;

    fp1 = fopen("string.txt", "r");
    fp2 = fopen("pattern.txt", "r");
    if (fp1 == NULL || fp2 == NULL) {
        if (fp1 == NULL) 
            printf("The string file does not exist.\n");
        if (fp2 == NULL)
            printf("The pattern file does not exist.\n");
        return;
    }
    fgets(string, sizeof(string), fp1);
    fgets(pat, sizeof(pat), fp2);
    fclose(fp1);
    fclose(fp2);

    fp1 = fopen("result_naive.txt", "wt");
    idx = nfind(string, pat);
    fprintf(fp1, "%d\n", idx);
    for (i = 0; i < idx; i++) {
        fprintf(fp1, "%d ", p_arr[i]);
    }
    fclose(fp1);
    printf("Program complete. Result saved to result_naive.txt\n");
}

int nfind(char* string, char* pat) {

    /* try implementing this function yourself! */
    int i, j, idx = 0, start = 0;
    int lasts = strlen(string) - 1;
    int lastp = strlen(pat) - 1;
    int endmatch = lastp;
    for (i = 0, j = 0; endmatch <= lasts; endmatch++, start++) {
        if (string[endmatch] == pat[lastp]) {
            i = start;
            j = 0;
            for (; j <= lastp && string[i] == pat[j]; i++, j++);
        }
        if (j == lastp + 1) {
            p_arr[idx] = start;
            idx++;
            j = 0;
        }
    }
    return idx;
}