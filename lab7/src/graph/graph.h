#pragma once
#include "../stack/stack.h"
#include <stdbool.h>

typedef enum colors {
    WHITE,
    GREY,
    BLACK
} eVertexColors;

typedef struct TGraph {
    char* Matrix;
    eVertexColors* VerticesColors;
    int CountVertices;
} TGraph;

TGraph CreateGraph(const int countVertices);
void AddPathToGraph(TGraph* graph, const short start, const short end);
_Bool TopSort(TStack* sortedGraph, TGraph* graph);
void DestroyGraph(TGraph* graph);
