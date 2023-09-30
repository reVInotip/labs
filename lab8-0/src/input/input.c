#include "../graph/graph.h"
#include "../check/check.h"
#include "input.h"
#include <stdio.h>
#include <stdbool.h>

// static functions

static _Bool FillEdges(TGraph* graph) {
	for (int i = 0; i < graph->CountEdges; ++i) {
		int start = 0, end = 0;
		unsigned int length = 0;
		char countStrings = scanf("%d %d %u", &start, &end, &length);
		if (
			IsBadNumber(/*count*/countStrings) ||
			IsBadVertex(/*start*/start, /*end*/end, /*count*/graph->CountVertices) ||
			IsBadLength(/*len*/length)
		) {
			return false;
		}
		(graph->Edges)[i].EdgeLength = length;
		(graph->Edges)[i].EdgeStart = start - 1;
		(graph->Edges)[i].EdgeEnd = end - 1;
	}
	return true;
}

// end static

_Bool Input(TGraph* graph) {
	char count = scanf("%d\n%d", &(graph->CountVertices), &(graph->CountEdges));
	const int EDGES_MAX = (graph->CountVertices)*(graph->CountVertices + 1)/2;
	if (
		IsBadInput(/*count*/count) ||
		IsBadCountVertices(/*count*/graph->CountVertices) ||
		IsBadCountEdges(/*count*/graph->CountEdges, /*EDGES_MAX*/EDGES_MAX)
	) {
		return false;
	}
	graph->Edges = CreateEdges(/*count*/graph->CountEdges);
	if (!FillEdges(/*graph*/graph)) {
		return false;
	}
	return true;
}
