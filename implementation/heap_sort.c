#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ELEMENTS 1000001
#define HEAP_FULL(n) (n == MAX_ELEMENTS-1)
#define HEAP_EMPTY(n) (!n)

typedef struct {
    int key;
} element;
element max_heap[MAX_ELEMENTS];
int n = 0;
element min_heap[MAX_ELEMENTS];
int m = 0;
element copy_heap[MAX_ELEMENTS];
int c = 0;

void insert_max_heap(element item, int* n);
element delete_max_heap(int* n);
void insert_min_heap(element item, int* m);
element delete_min_heap(int* m);

void main(int argc, char* argv[]) {
    if (argc == 2) {
        FILE* fp, * outfile;

        fp = fopen(argv[1], "r");
        outfile = fopen("mp2_result.txt", "wt");
        if (fp == NULL) {
            printf("The input file does not exist.\n");
            return;
        }
        else {
            char func[10];
            int data;
            clock_t	start, end;
            double runtime;

            start = clock();
            while (fscanf(fp, "%s %d", func, &data) != EOF) {
                if (!strcmp(func, "INSERT")) {
                    element item;
                    item.key = data;
                    insert_max_heap(item, &n);
                    insert_min_heap(item, &m);
                }
                else if (!strcmp(func, "ASCEND")) {
                    int i;
                    c = m;
                    for (i = 1; i < m + 1; i++) {
                        copy_heap[i] = min_heap[i];
                    }
                    for (i = 1; i < m + 1; i++) {
                        element item = delete_min_heap(&c);
                        fprintf(outfile, "%d ", item.key);
                    }
                    fprintf(outfile, "\n");
                }
                else if (!strcmp(func, "DESCEND")) {
                    int i;
                    c = n;
                    for (i = 1; i < n + 1; i++) {
                        copy_heap[i] = max_heap[i];
                    }
                    for (i = 1; i < n + 1; i++) {
                        element item = delete_max_heap(&c);
                        fprintf(outfile, "%d ", item.key);
                    }
                    fprintf(outfile, "\n");
                }
                else {
                    fclose(fp);
                    fclose(outfile);
                    return;
                }
            }
            end = clock();
            runtime = (double)(end - start) / CLOCKS_PER_SEC;
            printf("output written to mp2_result.txt.\n");
            printf("running time: %.6f seconds\n", runtime);
        }
        fclose(fp);
        fclose(outfile);
    }
    else {
        printf("usage: ./mp2 input_filename\n");
        return;
    }
    return;
}

void insert_max_heap(element item, int* n) {
    /* insert item into a max heap of current size *n */
    int i;
    if (HEAP_FULL(*n)) {
        fprintf(stderr, "The heap is full.\n");
        exit(1);
    }
    i = ++(*n);
    while ((i != 1) && (item.key > max_heap[i / 2].key)) {
        max_heap[i] = max_heap[i / 2];
        i /= 2;
    }
    max_heap[i] = item;
}

element delete_max_heap(int* n) {
    /* delete element with the highest key from the heap */
    int parent, child;
    element item, temp;
    if (HEAP_EMPTY(*n)) {
        fprintf(stderr, "The heap is empty");
        exit(1);
    }
    /* save value of the element with the largest key */
    item = copy_heap[1];
    /* use the last element in the heap to adjust heap */
    temp = copy_heap[(*n)--];
    parent = 1;
    child = 2;
    while (child <= *n) {
        /* find the larger child of the current parent */
        if ((child < *n) && (copy_heap[child].key < copy_heap[child + 1].key)) child++;
        if (temp.key >= copy_heap[child].key) break;
        /* move to the next lower level */
        copy_heap[parent] = copy_heap[child];
        parent = child;
        child *= 2;
    }
    copy_heap[parent] = temp;
    return item;
}

void insert_min_heap(element item, int* m) {
    /* insert item into a max heap of current size *n */
    int i;
    if (HEAP_FULL(*m)) {
        fprintf(stderr, "The heap is full.\n");
        exit(1);
    }
    i = ++(*m);
    while ((i != 1) && (item.key < min_heap[i / 2].key)) {
        min_heap[i] = min_heap[i / 2];
        i /= 2;
    }
    min_heap[i] = item;
}

element delete_min_heap(int* m) {
    /* delete element with the highest key from the heap */
    int parent, child;
    element item, temp;
    if (HEAP_EMPTY(*m)) {
        fprintf(stderr, "The heap is empty");
        exit(1);
    }
    /* save value of the element with the largest key */
    item = copy_heap[1];
    /* use the last element in the heap to adjust heap */
    temp = copy_heap[(*m)--];
    parent = 1;
    child = 2;
    while (child <= *m) {
        /* find the larger child of the current parent */
        if ((child < *m) && (copy_heap[child].key > copy_heap[child + 1].key)) child++;
        if (temp.key <= copy_heap[child].key) break;
        /* move to the next lower level */
        copy_heap[parent] = copy_heap[child];
        parent = child;
        child *= 2;
    }
    copy_heap[parent] = temp;
    return item;
}