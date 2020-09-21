#include <stdio.h>
#include <time.h>


int i = 0;

void hanoi_tower(int disk_num, char A, char B, char C) {
	
	if (disk_num == 1) {
		i++;
		printf("MOVE DISK #1 FROM %c TO %c (moves: %d)\n", A, C, i);
	}
	else {
		hanoi_tower(disk_num - 1, A, C, B);
		i++;
		printf("MOVE DISK #%d FROM %c TO %c (moves: %d)\n", disk_num, A, C, i);
		hanoi_tower(disk_num - 1, B, A, C);
	}
}

void main(int argc, char* argv[]) {
	clock_t	start, end;
	double runtime;

	if (argc == 2) {
		start = clock();
		hanoi_tower(atoi(argv[1]), 'A', 'B', 'C');
		end = clock();
		runtime = (double)(end - start) / CLOCKS_PER_SEC;
		printf("Total number of moves for %d disks: %d\n", atoi(argv[1]), i);
		printf("Running time: %f seconds", runtime);
	}
	else {
		printf("usage: ./hw2 number-of-disks");
		return;
	}
}