#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100
#define MAX_QUEUE_SIZE 100

struct node {
    char data;
    struct node* left_child, * right_child;
};
typedef struct node* tree_pointer;

tree_pointer create_tree_node(char data);
void recursive_inorder(tree_pointer ptr);
void iter_inorder(tree_pointer ptr);
void iter_postorder(tree_pointer ptr);
void iter_preorder(tree_pointer ptr);
void level_order(tree_pointer ptr);

/* TODO: add function prototype if necessary */

void main() {

    /* create a tree that represents an arithmetic expression */
    tree_pointer ptr, ptr1, ptr2;

    ptr1 = create_tree_node('A');
    ptr2 = create_tree_node('B');
    ptr = create_tree_node('/');
    ptr->left_child = ptr1;
    ptr->right_child = ptr2;

    ptr1 = ptr;
    ptr2 = create_tree_node('C');
    ptr = create_tree_node('*');
    ptr->left_child = ptr1;
    ptr->right_child = ptr2;

    ptr1 = ptr;
    ptr2 = create_tree_node('D');
    ptr = create_tree_node('*');
    ptr->left_child = ptr1;
    ptr->right_child = ptr2;

    ptr1 = ptr;
    ptr2 = create_tree_node('E');
    ptr = create_tree_node('+');
    ptr->left_child = ptr1;
    ptr->right_child = ptr2;

    /* call traversal functions */
    recursive_inorder(ptr);
    printf("\n");
    iter_inorder(ptr);
    printf("\n");
    iter_preorder(ptr);
    printf("\n");
    iter_postorder(ptr);
    printf("\n");
    level_order(ptr);
    printf("\n");
}

tree_pointer create_tree_node(char data) {
    tree_pointer ptr = (tree_pointer)malloc(sizeof(struct node));
    ptr->data = data;
    ptr->left_child = NULL;
    ptr->right_child = NULL;
    return ptr;
}

void recursive_inorder(tree_pointer ptr) {
    if (ptr) {
        recursive_inorder(ptr->left_child);
        printf("%c ", ptr->data);
        recursive_inorder(ptr->right_child);
    }
}

void iter_inorder(tree_pointer ptr) {
    /* TODO: you must complete this function */
}
void iter_preorder(tree_pointer ptr) {
    /* TODO: you must complete this function */
}
void iter_postorder(tree_pointer ptr) {
    /* TODO: you must complete this function */
}
void level_order(tree_pointer ptr) {
    /* TODO: you must complete this function */
    int front, rear;
    front = rear = 0;
    tree_pointer queue[MAX_QUEUE_SIZE];
    if (!ptr) return; /* empty tree */
    addq(front, &rear, ptr);
    for (; ; ) { 
        ptr = deleteq(&front, rear); 
        if (ptr) { 
            printf("%c ", ptr->data); 
            if (ptr->left_child) addq(front, &rear, ptr->left_child); 
            if (ptr->right_child) addq(front, &rear, ptr->right_child); 
        } 
        else break; 
    }
}

/* TODO: add function implementations here */
void addq(tree_pointer item) {
    if (rear == MAX_QUEUE_SIZE - 1)
        queueFull();
    queue[++rear] = item;
}

tree_pointer deleteq() {
    if (front == rear)
        return queueEmpty();
    return queue[++front];
}

void queueFull() {
    int i, offset;

    if (front == -1) {
        fprintf(stderr, "no more space in the queue\n");
        exit(1);
    }

    offset = front + 1;

    for (i = front + 1; i < MAX_QUEUE_SIZE; i++) {
        queue[i - offset] = queue[i];
    }

    front = front - offset;
    rear = rear - offset;

    printf(" ==== queue reorganized. (front: %2d rear: %2d) ====\n", front, rear);
}

tree_pointer queueEmpty() {
    tree_pointer e;
    e.key = INVALID_KEY;
    return e;
}


