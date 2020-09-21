#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _CRT_SECURE_NO_WARNINGS
#define MAX_STRING_SIZE 10000000
#define MAX_PATTERN_SIZE 3000

int pmatch(char*, char*);
void fail(char*);

int failure[MAX_PATTERN_SIZE];
char string[MAX_STRING_SIZE];
char pat[MAX_PATTERN_SIZE];
int p_arr[MAX_STRING_SIZE];

void main() {

    int i, count;
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

    fp1 = fopen("result_kmp.txt", "wt");
    fail(pat);
    count = pmatch(string, pat);
    int na = sizeof(p_arr) / sizeof(p_arr[0]);
    fprintf(fp1, "%d\n", count);
    for (i = 0; i < count; i++) {
        fprintf(fp1, "%d ", p_arr[i]);
    }
    fclose(fp1);
    printf("Program complete. Result saved to result_kmp.txt\n");
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

int pmatch(char* string, char* pat) {

    /* Knuth-Morris-Pratt string matching algorithm */
    int i = 0, j = 0, count;
    int lens = strlen(string);
    int lenp = strlen(pat);

    for (count = 0; i < lens; count++) {
        while (i < lens && j < lenp) {
            if (string[i] == pat[j]) { i++; j++; }
            else if (j == 0) i++;
            else j = failure[j - 1] + 1;
        }
        p_arr[count] = (j == lenp) ? (i - lenp) : -1;
        if (j != 0)
            j = failure[j - 1] + 1;
    }
    if (p_arr[0] == -1)
        count--;
    else if (p_arr[count-1] == -1)
        count--;

    return count;
}