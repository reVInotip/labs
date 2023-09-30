#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include "graph.h"
#include "../queue/queue.h"

// static functions

static void AddAvailibleVertecesToQueue(
		TQueue* queue, 
		const TGraph* graph, 
		const short vertex,
		const bool* used
) {
	for (int i = 0; i < graph->CountVertices ; ++i) {
		if ((graph->Matrix)[vertex * (graph->CountVertices) + i] == 0 || used[i]) {
			continue;
		}
		TEdge currentEdge = { .Parent = vertex, .Vertex = i };
		DecreaseKey(/*queue*/queue,
			/*newKey*/(unsigned int)(graph->Matrix)[vertex * (graph->CountVertices) + i],
			/*edge*/currentEdge);
	}
}

static _Bool FindFrame(TEdge* frame, const TGraph* graph) {
	bool* used = (bool*)calloc(graph->CountVertices, sizeof(bool));
	assert(used);
	TQueue queueOfAvailibleVerteces = CreateQueue(/*size*/graph->CountVertices);
	TEdge firstEdge = { .Parent = SHRT_MAX, .Vertex = 0 };
	DecreaseKey(/*queue*/&queueOfAvailibleVerteces, /*newKey*/0u, /*edge*/firstEdge);
	
	int countVerticesInFrame = 1;
	while (queueOfAvailibleVerteces.HeapSize != 0) {
		TEdge edge = Get(/*queue*/&queueOfAvailibleVerteces);
		
		if (!used[edge.Vertex]) {
			if (edge.Parent != SHRT_MAX) {
				frame[countVerticesInFrame - 1] = edge;
				++countVerticesInFrame;
			}
			used[edge.Vertex] = true;
			AddAvailibleVertecesToQueue(/*queue*/&queueOfAvailibleVerteces,
					/*graph*/graph,
					/*vertex*/edge.Vertex,
					/*used*/used);
		}
	}
	DestroyQueue(/*queue*/&queueOfAvailibleVerteces);
	free(used);

	if (countVerticesInFrame < graph->CountVertices) {
		return false;
	}
	return true;
}

// end static

void PrimMinimumSpanningTree(const TGraph* graph) {
	TEdge* minFrame = (TEdge*)calloc(graph->CountVertices, sizeof(TEdge));
	assert(minFrame);
	
    if (FindFrame(/*frame*/minFrame, /*graph*/graph)) {
        for (int i = 0; i < graph->CountVertices - 1; ++i) {
            printf("%d %d\n", minFrame[i].Parent + 1, minFrame[i].Vertex + 1);
        }
    } else {
	    printf("no spanning tree");
    }

    free(minFrame);
}

TGraph CreateGraph(const int countVertices) {
	int* matrix = (int*)calloc(countVertices * countVertices, sizeof(int));
	assert(matrix);
	TGraph graph = {
		.Matrix = matrix,
		.CountVertices = countVertices,
		.MatrixSize = countVertices * countVertices
	};
	return graph;
}

void DestroyGraph(TGraph* graph) {
	assert(graph);
	free(graph->Matrix);
	graph->MatrixSize = 0;
	graph->CountVertices = 0;
}
