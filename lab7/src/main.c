#include "stack/stack.h"
#include "graph/graph.h"
#include "utils/utils.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    int countVertices, countEdges;
    if (scanf("%d %d", &countVertices, &countEdges) != 2) {
        printf("bad number of lines");
        return EXIT_SUCCESS;
    }
    if (!CheckInput(/*countVertices*/countVertices, /*countEdges*/countEdges)) {
        return EXIT_SUCCESS;
    }
    
    TGraph graph = CreateGraph(/*countVertices*/countVertices);
    
    for (int i = 0; i < countEdges; ++i) {
        short start, end;
        if (scanf("%hd %hd", &start, &end) != 2) {
            printf("bad number of lines");
            DestroyGraph(/*graph*/&graph);
            return EXIT_SUCCESS;
        }
        if (!CheckVertices(/*start*/(int)start, /*end*/(int)end, /*maxNumber*/countVertices)) {
            DestroyGraph(/*graph*/&graph);
            return EXIT_SUCCESS;
        }
        
        AddPathToGraph(/*graph*/&graph, /*start*/start, /*end*/end);
    }
    
    TStack sortedGraph = CreateStack(/*size*/countVertices);
    
    if (TopSort(/*sortedGraph*/&sortedGraph, /*graph*/&graph)) {
        PrintStack(/*sortedGraph*/sortedGraph);
    } else {
        printf("impossible to sort");
    }
    
    DestroyGraph(/*graph*/&graph);
    DestroyStack(/*stack*/&sortedGraph);

    return EXIT_SUCCESS;
}
