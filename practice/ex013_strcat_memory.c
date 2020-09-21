#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

void main() {
    char s[] = "dog";
    char t[] = "house";
    char u[] = "rainbow";
    printf("%s\n", s);
    printf("%s\n", t);
    printf("%s\n", u);
    strcat(s, u);
    printf("%s\n", s);  // dograinbow
    printf("%s\n", t);  // house
    printf("%s\n", u);  // 
}