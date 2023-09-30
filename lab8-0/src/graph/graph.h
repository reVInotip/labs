#pragma once
#include "../dsu/dsu.h"
#include "../edges/edges.h"
#include <stdbool.h>

typedef struct TGraph {
	TEdges* Edges;
	int CountVertices;
	int CountEdges;
} TGraph;

_Bool GraphIsConnected(TGraph graph, TDSU dsu);
