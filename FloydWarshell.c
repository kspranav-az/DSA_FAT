#include <stdio.h>
//#include <limits.h>
#include <stdlib.h>

#define INT_MAX 1024

typedef struct Graph{
    int V ;
    int** AdjMat ;
} Graph ;

Graph* createGraph(int v) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = v;
    graph->AdjMat = (int**)calloc(v , sizeof(int*));
    for (int i = 0; i < v; i++) {
        graph->AdjMat[i] = (int*)calloc(v ,sizeof(int));
        for (int j = 0; j < v; j++) {
            graph->AdjMat[i][j] = (i == j) ? 0 : INT_MAX;
        }
    }
    return graph;
}

void addEdge(Graph* graph, int src, int dst, int wt){
    graph->AdjMat[src][dst] = wt;
    graph->AdjMat[dst][src] = wt;
}

void floydWarshell(Graph* graph){
  for(int i = 0; i < graph->V ; i++){
    for(int j = 0 ; j < graph->V ; j++){
        for(int k = 0 ; k < graph->V ; k++){
            if(graph->AdjMat[i][k] + graph->AdjMat[k][j] < graph->AdjMat[i][j]){
                graph->AdjMat[i][j] = graph->AdjMat[i][k] + graph->AdjMat[j][k] ;
            }
        }
    }
  }
  for(int i = 0; i < graph->V ; i++){
    for(int j = 0 ; j < graph->V ; j++){
        if(graph->AdjMat[i][j] == INT_MAX){
            printf(" - ");
        }else{
            printf(" %d " , graph->AdjMat[i][j] ) ; 
        } 
    }
    printf("\n");
  }    
}

int main(){
    Graph* graph = createGraph(5);

    addEdge(graph, 0, 1, 2);
    addEdge(graph, 0, 2, 4);
    addEdge(graph, 1, 2, 1);
    addEdge(graph, 1, 3, 7);
    addEdge(graph, 2, 4, 3);
    addEdge(graph, 3, 4, 1);

    floydWarshell(graph);
}