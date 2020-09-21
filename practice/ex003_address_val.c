#include <stdio.h>

void print1(int*, int);

void main() {
	int one[] = { 0, 1, 2, 3, 4 };
	print1(one, 5);
}

void print1(int* ptr, int rows) {
	int i;
	printf("address contents\n");
	for (i = 0; i < rows; i++)
		//printf("%8p%5d\n", &ptr[i], ptr[i]);
		printf("%8p%5d\n", ptr + i, *(ptr + i));
	printf("\n");
}