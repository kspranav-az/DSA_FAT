#include <stdio.h>
#include <stdlib.h>

// Node structure for a priority queue
struct Node {
    int data;
    int priority;
    struct Node* next;
};

// Priority Queue structure
struct PriorityQueue {
    struct Node* front;
};

// Function to create a new node
struct Node* createNode(int data, int priority) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->priority = priority;
    newNode->next = NULL;
    return newNode;
}

// Function to initialize an empty priority queue
struct PriorityQueue* createPriorityQueue() {
    struct PriorityQueue* pq = (struct PriorityQueue*)malloc(sizeof(struct PriorityQueue));
    if (pq == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    pq->front = NULL;
    return pq;
}

// Function to insert an element with a given priority into the priority queue
void enqueue(struct PriorityQueue* pq, int data, int priority) {
    struct Node* newNode = createNode(data, priority);
    if (pq->front == NULL || priority < pq->front->priority) {
        newNode->next = pq->front;
        pq->front = newNode;
    } else {
        struct Node* current = pq->front;
        while (current->next != NULL && current->next->priority <= priority) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

// Function to remove and return the highest-priority element from the priority queue
int dequeue(struct PriorityQueue* pq) {
    if (pq->front == NULL) {
        printf("Priority Queue is empty!\n");
        exit(1);
    }
    struct Node* frontNode = pq->front;
    int data = frontNode->data;
    pq->front = frontNode->next;
    free(frontNode);
    return data;
}

// Function to check if the priority queue is empty
int isEmpty(struct PriorityQueue* pq) {
    return pq->front == NULL;
}

int main() {
    struct PriorityQueue* pq = createPriorityQueue();

    enqueue(pq, 3, 1);
    enqueue(pq, 1, 2);
    enqueue(pq, 2, 1);
    enqueue(pq, 4, 3);

    printf("Priority Queue elements: ");
    while (!isEmpty(pq)) {
        printf("%d ", dequeue(pq));
    }

    return 0;
}
