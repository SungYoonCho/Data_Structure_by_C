#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_STACK_SIZE 1000000
int stack[MAX_STACK_SIZE];        
int top;           


void stackFull(void) {
    fprintf(stderr, "Stack is full, cannot add element.\n");
    exit(EXIT_FAILURE);
//    printf("Stack is full, cannot add element.\n");
//    return -1;
}

int stackEmpty() {
    return (top > -1) ? 0 : 1;
}

void push(int t) {
    if (top >= MAX_STACK_SIZE - 1) {
        stackFull();
    }
    stack[++top] = t;
}

int pop(void) {
    if (top < 0) {
        printf("Stack is empty, cannot pop element.\n");
        return -1;
    }
    return stack[top--];
}


void hanoi_tower(int n, char from, char by, char to, FILE* fp) {
    int i = 1;
    int cnt = 0;
    top = -1;
    while (1) {
        while (i < n) {
            push(to);    
            push(by);    
            push(from);  
            push(i);     
            i++;        
            push(to);   
            to = by;    
            by = pop(); 
        }

        cnt++;
        fprintf(fp, "MOVE DISK #%d FROM %c to %c (moves: %d)\n", i, from, to, cnt);
        
        if (!stackEmpty()) {
            i = pop();
            from = pop();
            by = pop();
            to = pop();

            cnt++;
            fprintf(fp, "MOVE DISK #%d FROM %c to %c (moves: %d)\n", i, from, to, cnt);

            i++;        // 인자리스트 변경 2
            push(from);
            from = by;
            by = pop();
        }
        else {
            fprintf(fp, "Total number of moves for %d disks: %d\n", n, cnt);
            break;
        }
    }
}

void main(int argc, char* argv[]) {
    if (argc == 2) {
        if (atoi(argv[1]) > 0) {
            FILE* fp;
            fp = fopen("hw2_result.txt", "wt");
            clock_t	start, end;
            double runtime;

            start = clock();
            hanoi_tower(atoi(argv[1]), 'A', 'B', 'C', fp);
            end = clock();
            runtime = (double)(end - start) / CLOCKS_PER_SEC;
            fprintf(fp, "Running time: %f seconds\n", runtime);
            fclose(fp);
        }
        else {
            printf("Segmentation fault (core dumped)\n");
            return;
        }
    }
    else {
        printf("usage: ./hw2 number-of-disks\n");
        return;
    }
    printf("Program Complete. Output saved to hw2_result.txt.\n");
    return;
}