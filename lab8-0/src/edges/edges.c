#include "edges.h"
#include <stdlib.h>
#include <assert.h>

TEdges* CreateEdges(const int count) {
	TEdges* edges = (TEdges*)malloc(sizeof(TEdges) * count);
	assert(edges);
	return edges;
}

void DestroyEdges(TEdges* edges) {
	if (edges) {
		free(edges);
	}
}
