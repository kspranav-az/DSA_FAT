#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
    int data;
    struct Node* next;
};

struct Graph {
    int V;
    struct Node** adjList;
};

struct Stack {
    int top;
    unsigned capacity;
    int* array;
};

struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->adjList = (struct Node**)malloc(V * sizeof(struct Node*));
    for (int i = 0; i < V; ++i) graph->adjList[i] = NULL;
    return graph;
}

void addEdge(struct Graph* graph, int src, int dest) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = dest;
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = src;
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
}

struct Stack* createStack(unsigned capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(capacity * sizeof(int));
    return stack;
}

bool isFull(struct Stack* stack) {
    return stack->top == stack->capacity - 1;
}

bool isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

void push(struct Stack* stack, int item) {
    if (!isFull(stack)) {
        stack->array[++stack->top] = item;
    }
}

int pop(struct Stack* stack) {
    if (!isEmpty(stack)) {
        return stack->array[stack->top--];
    }
    return -1; // Stack underflow
}

void DFS(struct Graph* graph, int startVertex) {
    struct Stack* stack = createStack(graph->V);
    bool* visited = (bool*)calloc(graph->V, sizeof(bool));

    push(stack, startVertex);
    visited[startVertex] = true;

    printf("Depth-First Traversal starting from vertex %d: ", startVertex);

    while (!isEmpty(stack)) {
        int currentVertex = pop(stack);
        printf("%d ", currentVertex);

        for (struct Node* currentNode = graph->adjList[currentVertex]; currentNode; currentNode = currentNode->next) {
            int adjacentVertex = currentNode->data;
            if (!visited[adjacentVertex]) {
                push(stack, adjacentVertex);
                visited[adjacentVertex] = true;
            }
        }
    }

    printf("\n");

    free(stack->array);
    free(stack);
    free(visited);
}

void freeGraph(struct Graph* graph) {
    for (int i = 0; i < graph->V; ++i) {
        struct Node* current = graph->adjList[i];
        while (current != NULL) {
            struct Node* temp = current;
            current = current->next;
            free(temp);
        }
    }

    free(graph->adjList);
    free(graph);
}


int main() {
    struct Graph* graph = createGraph(7);

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 5);
    addEdge(graph, 2, 6);

    DFS(graph, 0);

    freeGraph(graph);

    return 0;
}
