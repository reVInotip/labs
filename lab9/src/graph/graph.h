#pragma once

typedef struct TEdge {
    long long MinPath;
    short Parent;
    short Vertex;
} TEdge;

typedef struct TGraph {
    int* Matrix;
    int CountVertices;
} TGraph;

TGraph CreateGraph(const int countVertices);
void DestroyGraph(TGraph* graph);
void Dijkstra(const TGraph* graph, const short from, const short to);
