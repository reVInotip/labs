#include "graph.h"
#include "../stack/stack.h"
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

// static functions

static _Bool DFS(TStack* sortedGraph, TGraph* graph, const int vertex) {
    char* matrix = graph->Matrix;
    eVertexColors* color = graph->VerticesColors;
    color[vertex] = GREY;
    for (int i = 0; i < graph->CountVertices; ++i) {
        if (matrix[(vertex * graph->CountVertices + i)]) {
            if (color[i] == GREY) {
                return false;
            }
            if (color[i] == WHITE) {
                if (!DFS(sortedGraph, graph, i)) {
                    return false;
                }
            }
        }
    }
    Push(/*stack*/sortedGraph, /*value*/(short)vertex);
    color[vertex] = BLACK;
    return true;
}

// end static

TGraph CreateGraph(const int countVertices) {
    char* matrix = (char*)calloc(countVertices * countVertices, sizeof(char));
    assert(matrix);
    eVertexColors* colors = (eVertexColors*)calloc(countVertices, sizeof(eVertexColors));
    assert(colors);
    
    TGraph graph = {
        .Matrix = matrix,
        .VerticesColors = colors,
        .CountVertices = countVertices
    };

    return graph;
}

void AddPathToGraph(TGraph* graph, const short start, const short end) {
    (graph->Matrix)[(start - 1) * graph->CountVertices + (end - 1)] = 1;
}

_Bool TopSort(TStack* sortedGraph, TGraph* graph) {
    for (int i = 0; i < graph->CountVertices; ++i) {
        if ((graph->VerticesColors)[i] == WHITE) {
            if (!DFS(/*sortedGraph*/sortedGraph, /*graph*/graph, /*vertex*/i)) {
                return false;
            }
        }
    }
    return true;
}

void DestroyGraph(TGraph* graph) {
    free(graph->Matrix);
    free(graph->VerticesColors);
    graph->CountVertices = 0;
}
