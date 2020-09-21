#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 10000  
#define INF 50000001      
#define MAX_ELEMENT 50000001 

typedef struct {
    int key;  
    int u;    
    int v;    
} element;

typedef struct {
    element heap[MAX_ELEMENT];
    int heap_size;
} HeapType;

HeapType h;

int parent[MAX_VERTICES]; 
int num[MAX_VERTICES];    

void set_init(int n);
int set_find(int vertex);
void set_union(int s1, int s2);
void init(HeapType* h);
void insert_min_heap(HeapType* h, element item);
element delete_min_heap(HeapType* h);
void insert_heap_edge(HeapType* h, int u, int v, int weight);
void kruskal(FILE* fp, HeapType* h, int n);

void main(int argc, char* argv[])
{
    if (argc == 2) {
        FILE* fp, * outfile;

        fp = fopen(argv[1], "r");
        outfile = fopen("fp1_result.txt", "wt");
        if (fp == NULL) {
            printf("The input file does not exist.\n");
            return;
        }
        else {
            int numV, numE, sV, dV, W;
            clock_t	start, end;
            double runtime;

            start = clock();
            fscanf(fp, "%d", &numV);
            fscanf(fp, "%d", &numE);
            init(&h);       
            while (fscanf(fp, "%d %d %d", &sV, &dV, &W) != EOF) {
                insert_heap_edge(&h, sV, dV, W);
            }
            kruskal(outfile, &h, numV);
            end = clock();
            runtime = (double)(end - start) / CLOCKS_PER_SEC;
            printf("output written to fp1_result.txt.\n");
            printf("running time: %.6f seconds\n", runtime);
        }
        fclose(fp);
        fclose(outfile);
    }
    else {
        printf("usage: ./fp1 input_filename\n");
        return;
    }
    return;
}

void set_init(int n) {
    int i;
    for (i = 0; i < n; i++) {
        parent[i] = -1;
        num[i] = 1;
    }
}

int set_find(int v) {
    int p, s, i = -1; 

    for (i = v; (p = parent[i]) >= 0; i = p);

    s = i;  

    for (i = v; (p = parent[i]) >= 0; i = p)
        parent[i] = s;

    return s; 
}

void set_union(int s1, int s2) {
    if (num[s1] < num[s2]) {
        parent[s1] = s2;  
        num[s2] += num[s1];
    }
    else {
        parent[s2] = s1;
        num[s1] += num[s2];
    }
}

void init(HeapType* h) {
    h->heap_size = 0;
}

int is_empty(HeapType* h) {
    if (h->heap_size == 0)
        return TRUE;
    else
        return FALSE;
}

void insert_min_heap(HeapType* h, element item) {
    int i = ++(h->heap_size);

    while ((i != 1) && (item.key < h->heap[i / 2].key)) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = item;
}

element delete_min_heap(HeapType* h) {
    int parent, child;
    element item, temp;

    item = h->heap[1];
    temp = h->heap[(h->heap_size)--];

    parent = 1; 
    child = 2; 

    while (child <= h->heap_size) {
        if ((child < h->heap_size) && (h->heap[child].key) > h->heap[child + 1].key)
            child++;

        if (temp.key <= h->heap[child].key)
            break;

        h->heap[parent] = h->heap[child]; 
        parent = child; 
        child *= 2; 
    }
    h->heap[parent] = temp;
    return item;
}

void insert_heap_edge(HeapType* h, int u, int v, int weight) {
    element e;
    e.u = u;
    e.v = v;
    e.key = weight;
    insert_min_heap(h, e);
}

void kruskal(FILE* fp, HeapType* h, int n)
{
    int edge_accepted = 0;  
    int uset, vset;     
    int sum_cost = 0;
    element e;        

    set_init(n);      

    while (edge_accepted < (n - 1)) {
        e = delete_min_heap(h);  
        uset = set_find(e.u);   
        vset = set_find(e.v);   

        if (e.u == 0 && e.v == 0)
            break;

        if (uset != vset) {
            fprintf(fp, "%d %d %d\n", e.u, e.v, e.key);
            sum_cost += e.key;
            edge_accepted++;
            set_union(uset, vset); 
        }
    }
    fprintf(fp, "%d\n", sum_cost);
    if (edge_accepted < (n - 1))
        fprintf(fp, "DISCONNECTED\n");
    else
        fprintf(fp, "CONNECTED\n");
}