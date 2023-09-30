#include "dsu/dsu.h"
#include "edges/edges.h"
#include "graph/graph.h"
#include "input/input.h"
#include <stdlib.h>
#include <stdio.h>

int Compare(const void* i, const void* j) {
	return ((TEdges*)i)->EdgeLength - ((TEdges*)j)->EdgeLength;
}

void KrushalMinimumSpanningTree(TGraph* graph) {
	TDSU dsu = CreateDSU(/*count*/graph->CountVertices);
	for (int numVertice = 0; numVertice < graph->CountVertices; ++numVertice) {
		MakeSet(/*value*/numVertice, /*dsu*/dsu);
	}
	if (!GraphIsConnected(/*graph*/*graph, /*dsu*/dsu)) {
		DestroyDSU(/*dsu*/dsu);
		printf("no spanning tree");
		return;
	}
	for (int numVertice = 0; numVertice < graph->CountVertices; ++numVertice) {
		MakeSet(/*value*/numVertice, /*dsu*/dsu);
	}
	for (int i = 0; i < graph->CountEdges; ++i) {
		int u = (graph->Edges)[i].EdgeStart;
		int v = (graph->Edges)[i].EdgeEnd;
		unsigned int setForU = Find(/*value*/u, /*dsu*/dsu);
		unsigned int setForV = Find(/*value*/v, /*dsu*/dsu);
		if (setForU != setForV) {
			printf("%d %d\n", u + 1, v + 1);
			Unite(/*firstValue*/u, /*secondValue*/v, /*dsu*/dsu);
		}
	}
	DestroyDSU(/*dsu*/dsu);
}

int main(void) {
	TGraph graph = {
		.Edges = NULL,
		.CountVertices = 0,
		.CountEdges = 0
	};
	if (Input(/*graph*/&graph)) {
		qsort(graph.Edges, graph.CountEdges, sizeof(TEdges), Compare);
		KrushalMinimumSpanningTree(/*graph*/&graph);
	}
	DestroyEdges(/*edges*/graph.Edges);
    return EXIT_SUCCESS;
}
