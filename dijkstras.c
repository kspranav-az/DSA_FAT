#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>

typedef struct Edge {
    int data;
    int weight;
    struct Edge* next;
} Edge;

typedef struct PriorityQueue {
    struct Edge* front;
} PriorityQueue;

struct Edge* createEdge(int data, int weight) {
    struct Edge* newEdge = (struct Edge*)malloc(sizeof(struct Edge));
    if (newEdge == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newEdge->data = data;
    newEdge->weight = weight;
    newEdge->next = NULL;
    return newEdge;
}

struct PriorityQueue* createPriorityQueue() {
    struct PriorityQueue* pq = (struct PriorityQueue*)malloc(sizeof(struct PriorityQueue));
    if (pq == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    pq->front = NULL;
    return pq;
}

void enqueue(struct PriorityQueue* pq, int data, int weight) {
    struct Edge* newEdge = createEdge(data, weight);
    if (pq->front == NULL || weight < pq->front->weight) {
        newEdge->next = pq->front;
        pq->front = newEdge;
    } else {
        struct Edge* current = pq->front;
        while (current->next != NULL && current->next->weight <= weight) {
            current = current->next;
        }
        newEdge->next = current->next;
        current->next = newEdge;
    }
}

int dequeue(struct PriorityQueue* pq) {
    if (pq->front == NULL) {
        printf("Priority Queue is empty!\n");
        exit(1);
    }
    struct Edge* frontEdge = pq->front;
    int des = frontEdge->data;
    pq->front = frontEdge->next;
    free(frontEdge);
    return des;
}

bool isEmpty(struct PriorityQueue* pq) {
    return pq->front == NULL;
}

typedef struct Graph {
    int V;
    Edge** AdjList;
} Graph;

Graph* createGraph(int v) {
    Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = v;
    graph->AdjList = (Edge**)calloc(v, sizeof(Edge*));
    for (int i = 0; i < v; i++) {
        graph->AdjList[i] = NULL;
    }
    return graph;
}

void addEdge(Graph* graph, int src, int dst, int weight) {
    if (graph->V <= src) {
        return;
    }
    Edge* newEdge = createEdge(dst, weight);
    newEdge->next = graph->AdjList[src];
    graph->AdjList[src] = newEdge;
}

int childCount(Graph* graph, int node) {
    if (graph->AdjList[node] == NULL) {
        return 0;
    }
    Edge* temp = graph->AdjList[node];
    int count = 0;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

void dijkstra(Graph* graph, int src) {
    bool* visited = (bool*)calloc(graph->V, sizeof(bool));
    int* shortestDistance = (int*)calloc(graph->V, sizeof(int));
    struct Edge* temp;
    for (int i = 0; i < graph->V; i++) {
        shortestDistance[i] = INT_MAX;
    }

    PriorityQueue* queue = createPriorityQueue();
    enqueue(queue, src, 0);
    visited[src] = true;
    shortestDistance[src] = 0;

    while (!isEmpty(queue)) {
        int u = dequeue(queue);
        temp = graph->AdjList[u];
        for (int i = 0; i < childCount(graph, u); i++) {
            int v = temp->data;
            int weight = temp->weight;
            if (!visited[v] && (shortestDistance[u] + weight < shortestDistance[v])) {
                shortestDistance[v] = shortestDistance[u] + weight;
                enqueue(queue, v, shortestDistance[v]);
            }
            temp = temp->next;
        }
    }


    printf("Shortest Distances from Source %d:\n", src);
    for (int i = 0; i < graph->V; i++) {
        printf("To node %d: %d\n", i, shortestDistance[i]);
    }

    free(visited);
    free(shortestDistance);
}

int main() {
    int V = 5;
    Graph* graph = createGraph(V);

    addEdge(graph, 0, 1, 2);
    addEdge(graph, 0, 2, 4);
    addEdge(graph, 1, 2, 1);
    addEdge(graph, 1, 3, 7);
    addEdge(graph, 2, 4, 3);
    addEdge(graph, 3, 4, 1);

    int source = 0;

    dijkstra(graph, source);

    return 0;
}
