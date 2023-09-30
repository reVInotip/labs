#pragma once

typedef struct TEdge {
    short Parent;
    short Vertex;
} TEdge;

typedef struct TGraph {
    int* Matrix;
    int CountVertices;
    int MatrixSize;
} TGraph;

TGraph CreateGraph(const int countVertices);
void DestroyGraph(TGraph* graph);
void PrimMinimumSpanningTree(const TGraph* graph);
