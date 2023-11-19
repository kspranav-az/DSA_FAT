#include <stdio.h>
#include <stdlib.h>

// Define the structure for a singly linked list node
struct Node {
    int data;
    struct Node* next;
};

// Define the structure for a singly linked list
struct SinglyLinkedList {
    struct Node* head;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to initialize a singly linked list
void initLinkedList(struct SinglyLinkedList* list) {
    list->head = NULL;
}

// Function to insert a node at the end of the list
void insertAtEnd(struct SinglyLinkedList* list, int data) {
    struct Node* newNode = createNode(data);
    if (list->head == NULL) {
        list->head = newNode;
    } else {
        struct Node* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Function to insert a node at the front of the list (beginning)
void insertAtFront(struct SinglyLinkedList* list, int data) {
    struct Node* newNode = createNode(data);
    newNode->next = list->head;
    list->head = newNode;
}

// Function to insert a node at a specific position
void insertAtPosition(struct SinglyLinkedList* list, int data, int position) {
    if (position < 0) {
        printf("Invalid position\n");
        return;
    }

    struct Node* newNode = createNode(data);

    if (position == 0) {
        // Insert at the front
        newNode->next = list->head;
        list->head = newNode;
    } else {
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

        newNode->next = current->next;
        current->next = newNode;
    }
}

// Function to display the linked list
void display(const struct SinglyLinkedList* list) {
    struct Node* current = list->head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

// Function to delete a node with a specific value
void deleteNode(struct SinglyLinkedList* list, int target) {
    struct Node* current = list->head;
    struct Node* prev = NULL;

    while (current != NULL) {
        if (current->data == target) {
            if (prev == NULL) {
                list->head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            return; // Node deleted
        }
        prev = current;
        current = current->next;
    }
}

// Function to reverse the linked list
void reverseList(struct SinglyLinkedList* list) {
    struct Node* prev = NULL;
    struct Node* current = list->head;
    struct Node* next = NULL;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    list->head = prev; // Update the head to the new start of the reversed list
}

// Main function for testing singly linked list
int main() {
    struct SinglyLinkedList linkedList;
    initLinkedList(&linkedList);
    
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

    // Reverse the list
    reverseList(&linkedList);
    display(&linkedList);

    return 0;
}
