#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* next;
};

struct node* createNode(int data) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    if (newNode == NULL) {
        printf("Memory allocation error");
    }
    newNode->data = data;
    newNode->next = newNode; 
    return newNode;
}

struct node* insert(struct node* head, int data) {
    if (head == NULL) {
        return createNode(data);
    }

    struct node* newNode = createNode(data);
    newNode->next = head->next;
    head->next = newNode;
    return head;
}

void display(struct node* head) {
    if (head == NULL) {
        printf("Circular Linked List is empty.\n");
        return;
    }

    struct node* current = head;
    do {
        printf("%d ", current->data);
        current = current->next;
    } while (current != head);

    printf("\n");
}

int main() {
    struct node* head = NULL;

    head = insert(head, 3);
    head = insert(head, 2);
    head = insert(head, 1);

    display(head);

   
    struct node* current = head;
    struct node* nextNode;

    do {
        nextNode = current->next;
        free(current);
        current = nextNode;
    } while (current != head);

    return 0;
}