#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct listNode {
    struct listNode* prev;
    int data;
    struct listNode* next;
};
typedef struct listNode* listPointer;

listPointer dlist = NULL;

void insert(int);
void delete(int);
void print_forward(listPointer);
void print_reverse(listPointer);

void main(int argc, char* argv[]) {
    if (argc == 2) {
        FILE* fp, * rp;

        rp = fopen("mp1_result.txt", "wt, ccs = UTF-8");
        fclose(rp);

        fp = fopen(argv[1], "r");
        if (fp == NULL) {
            printf("The input file does not exist.\n");
            return;
        }
        else {
            char func[10];
            int data;
            while (fscanf(fp, "%s %d", func, &data) != EOF) {
                if (!strcmp(func, "INSERT")) {
                    insert(data);
                }
                else if (!strcmp(func, "DELETE")) {
                    delete(data);
                }
                else if (!strcmp(func, "ASCEND")) {
                    print_forward(dlist);
                }
                else if (!strcmp(func, "DESCEND")) {
                    print_reverse(dlist);
                }
                else {
                    fclose(fp);
                    return;
                }
            }
        }
        fclose(fp);
    }
    else {
        printf("usage: ./mp1 input_filename\n");
        return;
    }
    return;
} 

void insert(int value) {
    listPointer newnode, curr;

    newnode = (listPointer)malloc(sizeof(struct listNode));
    newnode->data = value;
    newnode->prev = NULL;
    newnode->next = NULL;

    if (dlist == NULL) {
        dlist = newnode;
        newnode->prev = newnode;
        newnode->next = newnode;
        return;
    }

    curr = dlist;
    if (curr->data > value) {
        newnode->next = curr;
        newnode->prev = curr->prev;
        curr->prev->next = newnode;
        curr->prev = newnode;
        dlist = newnode;
    }
    else {
        while (curr->data <= value) {
            if (curr->data == value) return;
            curr = curr->next;
            if (curr == dlist) break;
        }
        curr = curr->prev;
        newnode->prev = curr;
        newnode->next = curr->next;
        curr->next->prev = newnode;
        curr->next = newnode;
    }
    return;
}

void delete(int value) {
    listPointer delnode, curr;
    
    if (dlist == NULL)
        return;
    
    curr = dlist;
    while (curr->data != value) {
        curr = curr->next;
        if (curr == dlist) return;
    }

    if (curr == dlist) {
        if (curr->next != curr) {  // 여러 개 노드 있을 때, 첫 번째 노드 삭제
            delnode = curr;

            delnode->prev->next = delnode->next;
            delnode->next->prev = delnode->prev;
            dlist = delnode->next;
            free(delnode);
        }
        else {  // 한 개 노드 뿐일 때, 첫 번째 노드 삭제
            delnode = curr;
            free(delnode);
            dlist = NULL;
        }
    }
    else {
        delnode = curr;

        delnode->prev->next = delnode->next;
        delnode->next->prev = delnode->prev;
        free(delnode);
    }
    return;
}


void print_forward(listPointer list) {
    listPointer curr;
    FILE* outfile;

    outfile = fopen("mp1_result.txt", "a");
    if (list) { 
        curr = list;
        while (1) { 
            fprintf(outfile, "%d ", curr->data);
            printf("%d ", curr->data);     
            curr = curr->next;     
            if (curr == list) break; 
        } 
    } 
    fprintf(outfile, "\n"); 
    printf("\n"); 
    fclose(outfile);
}

void print_reverse(listPointer list) {

    listPointer curr;   
    FILE* outfile;

    outfile = fopen("mp1_result.txt", "a");   
    if (list) {
        curr = list->prev;

        while (curr != list) { 
            fprintf(outfile, "%d ", curr->data);       
            printf("%d ", curr->data);       
            curr = curr->prev; 
        } 
        fprintf(outfile, "%d ", curr->data);   
        printf("%d ", curr->data);
    }   
    fprintf(outfile, "\n");   
    printf("\n");   
    fclose(outfile);
}