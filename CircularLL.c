#include <stdio.h>
#include <stdlib.h>

// Define the structure for a circular linked list node
struct Node {
    int data;
    struct Node* next;
};

// Define the structure for a circular linked list
struct CircularLinkedList {
    struct Node* head;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to initialize a circular linked list
void initCircularLinkedList(struct CircularLinkedList* list) {
    list->head = NULL;
}

// Function to insert a node at the end of the circular list
void insertAtEnd(struct CircularLinkedList* list, int data) {
    struct Node* newNode = createNode(data);
    
    if (list->head == NULL) {
        list->head = newNode;
        newNode->next = list->head; // Point to itself to make it circular
    } else {
        struct Node* current = list->head;
        while (current->next != list->head) {
            current = current->next;
        }
        current->next = newNode;
        newNode->next = list->head; // Make it circular
    }
}

// Function to display the circular linked list
void display(const struct CircularLinkedList* list) {
    if (list->head == NULL) {
        printf("Circular Linked List is empty.\n");
        return;
    }

    struct Node* current = list->head;
    
    do {
        printf("%d -> ", current->data);
        current = current->next;
    } while (current != list->head);

    printf("(head)\n");
}

// Function to delete a node with a specific value from the circular list
void deleteNode(struct CircularLinkedList* list, int target) {
    if (list->head == NULL) {
        printf("Circular Linked List is empty.\n");
        return;
    }

    struct Node* current = list->head;
    struct Node* prev = NULL;

    do {
        if (current->data == target) {
            if (prev == NULL) {
                // Deleting the head node
                struct Node* last = list->head;
                while (last->next != list->head) {
                    last = last->next;
                }

                if (current == list->head) {
                    // Only one node in the circular list
                    free(current);
                    list->head = NULL;
                } else {
                    last->next = current->next;
                    list->head = current->next;
                    free(current);
                }

                return; // Node deleted
            } else {
                prev->next = current->next;
                free(current);
                return; // Node deleted
            }
        }
        prev = current;
        current = current->next;
    } while (current != list->head);

    printf("Node with value %d not found in the Circular Linked List.\n", target);
}

// Main function for testing circular linked list
int main() {
    struct CircularLinkedList circularList;
    initCircularLinkedList(&circularList);

    // Insert at the end
    insertAtEnd(&circularList, 1);
    insertAtEnd(&circularList, 3);
    display(&circularList);

    // Delete a node
    deleteNode(&circularList, 1);
    display(&circularList);

    // Insert at the end
    insertAtEnd(&circularList, 5);
    insertAtEnd(&circularList, 7);
    display(&circularList);

    return 0;
}
