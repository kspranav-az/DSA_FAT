#include <stdio.h>
#include <stdlib.h>

// Node structure for a deque
struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

// Deque structure
struct Deque {
    struct Node* front;
    struct Node* rear;
};

// Function to initialize an empty deque
void initializeDeque(struct Deque* deque) {
    deque->front = NULL;
    deque->rear = NULL;
}

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Function to insert a node at the front of the deque
void insertFront(struct Deque* deque, int data) {
    struct Node* newNode = createNode(data);
    if (deque->front == NULL) {
        deque->front = newNode;
        deque->rear = newNode;
        return;
    }
    newNode->next = deque->front;
    deque->front->prev = newNode;
    deque->front = newNode;
}

// Function to insert a node at the rear of the deque
void insertRear(struct Deque* deque, int data) {
    struct Node* newNode = createNode(data);
    if (deque->rear == NULL) {
        deque->front = newNode;
        deque->rear = newNode;
        return;
    }
    newNode->prev = deque->rear;
    deque->rear->next = newNode;
    deque->rear = newNode;
}

// Function to remove and return a node from the front of the deque
int removeFront(struct Deque* deque) {
    if (deque->front == NULL) {
        printf("Deque is empty!\n");
        exit(1);
    }

    struct Node* temp = deque->front;
    int data = temp->data;
    deque->front = temp->next;
    if (deque->front != NULL) {
        deque->front->prev = NULL;
    }
    free(temp);
    return data;
}

// Function to remove and return a node from the rear of the deque
int removeRear(struct Deque* deque) {
    if (deque->rear == NULL) {
        printf("Deque is empty!\n");
        exit(1);
    }

    struct Node* temp = deque->rear;
    int data = temp->data;
    deque->rear = temp->prev;
    if (deque->rear != NULL) {
        deque->rear->next = NULL;
    }
    free(temp);
    return data;
}

// Function to check if the deque is empty
int isEmpty(struct Deque* deque) {
    return deque->front == NULL;
}

// Function to display the deque from front to rear
void display(struct Deque* deque) {
    struct Node* current = deque->front;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

int main() {
    struct Deque deque;
    initializeDeque(&deque);

    insertFront(&deque, 1);
    insertRear(&deque, 2);
    insertFront(&deque, 3);
    insertRear(&deque, 4);

    printf("Deque: ");
    display(&deque);

    printf("Removed item from the front: %d\n", removeFront(&deque));
    printf("Removed item from the rear: %d\n", removeRear(&deque));

    printf("Deque after removals: ");
    display(&deque);

    return 0;
}
