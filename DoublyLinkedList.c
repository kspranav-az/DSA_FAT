#include <stdio.h>
#include <stdlib.h>

// Define the structure for a doubly linked list node
struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

// Define the structure for a doubly linked list
struct DoublyLinkedList {
    struct Node* head;
    struct Node* tail;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Function to initialize a doubly linked list
void initDoublyLinkedList(struct DoublyLinkedList* list) {
    list->head = NULL;
    list->tail = NULL;
}

// Function to insert a node at the end of the list
void insertAtEnd(struct DoublyLinkedList* list, int data) {
    struct Node* newNode = createNode(data);
    if (list->tail == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        newNode->prev = list->tail;
        list->tail->next = newNode;
        list->tail = newNode;
    }
}

// Function to insert a node at the front of the list (beginning)
void insertAtFront(struct DoublyLinkedList* list, int data) {
    struct Node* newNode = createNode(data);
    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        newNode->next = list->head;
        list->head->prev = newNode;
        list->head = newNode;
    }
}

// Function to insert a node at a specific position
void insertAtPosition(struct DoublyLinkedList* list, int data, int position) {
    if (position < 0) {
        printf("Invalid position\n");
        return;
    }

    if (position == 0) {
        // Insert at the front
        insertAtFront(list, data);
        return;
    }

    struct Node* newNode = createNode(data);
    struct Node* current = list->head;
    int currentPosition = 0;

    while (current != NULL && currentPosition < position - 1) {
        current = current->next;
        currentPosition++;
    }

    if (current == NULL) {
        printf("Invalid position\n");
        free(newNode);
        return;
    }

    newNode->prev = current;
    newNode->next = current->next;
    if (current->next != NULL) {
        current->next->prev = newNode;
    }
    current->next = newNode;
}

// Function to delete a node with a specific value
void deleteNode(struct DoublyLinkedList* list, int target) {
    struct Node* current = list->head;

    while (current != NULL) {
        if (current->data == target) {
            if (current == list->head) {
                list->head = current->next;
                if (list->head != NULL) {
                    list->head->prev = NULL;
                }
            } else if (current == list->tail) {
                list->tail = current->prev;
                list->tail->next = NULL;
            } else {
                current->prev->next = current->next;
                current->next->prev = current->prev;
            }
            free(current);
            return; // Node deleted
        }
        current = current->next;
    }
}

// Function to display the doubly linked list
void display(const struct DoublyLinkedList* list) {
    struct Node* current = list->head;
    while (current != NULL) {
        printf("%d <-> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

// Main function for testing doubly linked list
int main() {
    struct DoublyLinkedList linkedList;
    initDoublyLinkedList(&linkedList);

    // Insert at the end
    insertAtEnd(&linkedList, 1);
    insertAtEnd(&linkedList, 3);
    display(&linkedList);

    // Insert at the front
    insertAtFront(&linkedList, 0);
    display(&linkedList);

    // Insert at a specific position
    insertAtPosition(&linkedList, 2, 2);
    display(&linkedList);

    // Delete a node
    deleteNode(&linkedList, 2);
    display(&linkedList);

    return 0;
}
