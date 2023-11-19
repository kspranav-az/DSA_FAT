#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define INT_MAX 10

//IMPLEMENTATION OF GRAPH USING ADJMAT

struct graph{
    int V;
    int** adjmat;
};

struct graph* createGraph(int v){
    struct graph* g = (struct graph*)malloc(sizeof(struct graph));
    g->V = v;
    g->adjmat = (int*)calloc(v,sizeof(int));
    for (int i = 0; i < v; i++) {
        g->adjmat[i] = (int*)calloc(v, sizeof(int));
        for(int j = 0; j < v; j++){
            g->adjmat[i][j] = INT_MAX;
        }
    }
    return g;
}

void addEdge(struct graph* g, int src, int dest, int weight) {
    if (src >= 0 && src < g->V && dest >= 0 && dest < g->V) {
        g->adjmat[src][dest] = weight;
        g->adjmat[dest][src] = weight;
    } else {
        printf("Invalid vertex indices\n");
    }
}

//Floyd warshall algorithm for shortest path
void FloydWarshall(struct graph* g,int src){
    int** dist = g->adjmat;
    for(int k = 0 ; k < g->V ; k++){
        for(int i = 0 ; i < g->V ; i++){
            for(int j = 0 ; j < g->V ; j++){
                if(dist[i][k] + dist[k][j] < dist[i][j]){
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }

    }
    for(int i = 0 ; i < g->V ;i++){
        for(int j = 0 ; j < g->V ; j++){
            if(dist[i][j]==INT_MAX){
                printf("INF ");
            }
            else{
                printf("%d ",dist[i][j]);
            }
        }
        printf("\n");
    }

}


int main() {
    // Example graph represented as an adjacency matrix
    struct graph* g = createGraph(5);
    addEdge(g, 0, 1, 2);
    addEdge(g, 0, 2, 4);
    addEdge(g, 1, 2, 1);
    addEdge(g, 1, 3, 7);
    addEdge(g, 2, 4, 3);
    addEdge(g, 3, 4, 1);

    int sourceVertex = 0;
    FloydWarshall(g, sourceVertex);

    // Free the memory
    for (int i = 0; i < g->V; i++) {
        free(g->adjmat[i]);
    }
    free(g->adjmat);
    free(g);

    return 0;
}