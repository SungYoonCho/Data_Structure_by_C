#include <stdio.h>

int** make2dArray(int rows, int cols) {
	int** x, i;

	x = malloc(rows * sizeof(*x));

	for (i = 0; i < rows; i++)
		x[i] = malloc(cols * sizeof(**x));

	return x;

}