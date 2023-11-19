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

struct Queue {
    int front, rear, size;
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

struct Queue* createQueue(unsigned capacity) {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    queue->array = (int*)malloc(capacity * sizeof(int));
    return queue;
}

bool isFull(struct Queue* queue) {
    return queue->size == queue->capacity;
}

bool isEmpty(struct Queue* queue) {
    return queue->size == 0;
}

void enqueue(struct Queue* queue, int item) {
    if (!isFull(queue)) {
        queue->rear = (queue->rear + 1) % queue->capacity;
        queue->array[queue->rear] = item;
        queue->size = queue->size + 1;
    }
}

int dequeue(struct Queue* queue) {
    if (!isEmpty(queue)) {
        int item = queue->array[queue->front];
        queue->front = (queue->front + 1) % queue->capacity;
        queue->size = queue->size - 1;
        return item;
    }
    return -1;
}

void BFS(struct Graph* graph, int startVertex) {
    struct Queue* queue = createQueue(graph->V);
    bool* visited = (bool*)calloc(graph->V, sizeof(bool));

    enqueue(queue, startVertex);
    visited[startVertex] = true;

    printf("Breadth-First Traversal starting from vertex %d: ", startVertex);

    while (!isEmpty(queue)) {
        int currentVertex = dequeue(queue);
        printf("%d ", currentVertex);

        for (struct Node* currentNode = graph->adjList[currentVertex]; currentNode ; currentNode = currentNode->next) {
            int adjacentVertex = currentNode->data;
            if (!visited[adjacentVertex]) {
                enqueue(queue, adjacentVertex);
                visited[adjacentVertex] = true;
            }
        }
    }

    printf("\n");

    free(queue->array);
    free(queue);
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

    BFS(graph, 0);

    freeGraph(graph);

    return 0;
}
