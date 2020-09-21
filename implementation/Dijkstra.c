#include <stdio.h>
#include <time.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 10000 
#define INF 100000000 
#define MAX_INT 200000000 

int dist[MAX_VERTICES]; 
int found[MAX_VERTICES]; 
int path[MAX_VERTICES][MAX_VERTICES];
int path_num[MAX_VERTICES];
int weight[MAX_VERTICES][MAX_VERTICES];


void path_init(int path[][MAX_VERTICES], int numV); 
int choose(int distance[], int n, int found[]); 
void Dijkstra(int start, int n);

void main(int argc, char* argv[]) {
    if (argc == 2) {
        FILE* fp, * outfile;

        fp = fopen(argv[1], "r");
        outfile = fopen("fp2_result.txt", "wt");
        if (fp == NULL) {
            printf("The input file does not exist.\n");
            return;
        }
        else {
            int numV, numE, i, j, sV, dV, W, start;
            clock_t	tstart, end;
            double runtime;

            tstart = clock();
            
            fscanf(fp, "%d", &numV);
            fscanf(fp, "%d", &numE);
            for (i = 0; i < numV; i++) {
                for (j = 0; j < numV; j++) {
                    weight[i][j] = INF;
                }
            }
            for (i = 0; i < numE; i++) {
                fscanf(fp, "%d %d %d", &sV, &dV, &W);
                weight[sV][dV] = W;
            }
            fscanf(fp, "%d", &start);
                       
            path_init(path, numV);
            Dijkstra(start, numV);

            for (i = 0; i < numV; i++) {
                fprintf(outfile, "SRC: %d, DST: %d, LENGTH: ", start, i);
                if (dist[i] == INF) {
                    fprintf(outfile, "-, PATH: -");
                }
                else {
                    fprintf(outfile, "%d, PATH: ", dist[i]);
                    for (j = 0; j < numV; j++) {
                        if (path[i][j] != INF) {
                            fprintf(outfile, "%d ", path[i][j]);
                        }
                    }
                    if (start != i) {
                        fprintf(outfile, "%d", i);
                    }
                }
                fprintf(outfile, "\n");
            }

            end = clock();
            runtime = (double)(end - tstart) / CLOCKS_PER_SEC;
            printf("output written to fp2_result.txt.\n");
            printf("running time: %.6f seconds\n", runtime);
        }
        fclose(fp);
        fclose(outfile);
    }
    else {
        printf("usage: ./fp2 input_filename\n");
        return;
    }
    return;
}

void path_init(int path[][MAX_VERTICES], int numV) {
    int i, j;
    for (i = 0; i < numV; i++)
        for (j = 0; j < numV; j++)
            path[i][j] = INF;
}

int choose(int distance[], int n, int found[]) {
    int i, min, minidx;
    min = MAX_INT;
    minidx = -1;

    for (i = 0; i < n; i++)
        if (distance[i] < min && !found[i]) {
            min = distance[i];
            minidx = i;
        }
    return minidx;
}

void Dijkstra(int start, int n) {
    int i, j, u, w;
    for (i = 0; i < n; i++) {
        dist[i] = weight[start][i];
        found[i] = FALSE;
        path_num[i] = 1;
        path[i][0] = start;
    }

    found[start] = TRUE;
    dist[start] = 0;

    for (i = 0; i < n - 2; i++) {
        u = choose(dist, n, found);  // 방문하지 않은 vertex 중 최소 length를 가진 vertex를 찾음
        found[u] = TRUE;  // 방문 업데이트
        for (w = 0; w < n; w++) {
            if (!found[w]) {
                if (dist[u] + weight[u][w] < dist[w]) {
                    if (i == 0) {
                        path[w][path_num[w]] = u; 
                        path_num[w]++;
                    }
                    else {
                        path_num[w] = 1;
                        for (j = 0; j < path_num[u]; j++) {
                            path[w][j] = path[u][j]; 
                            path[w][j + 1] = u; 
                            path_num[w]++;
                        }
                    }
                    dist[w] = dist[u] + weight[u][w];
                }
            }
        }
    }
}