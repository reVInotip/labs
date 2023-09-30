#include "graph.h"
#include "../queue/queue.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>

// static functions

static int Compare(const void* i, const void* j) {
	return (int)(((const TEdge*)i)->Vertex - ((const TEdge*)j)->Vertex);
}

static void AddAvailibleVertecesToQueue(TQueue* queue, const TGraph* graph, const TEdge edge) {
	for (int i = 0; i < graph->CountVertices ; ++i) {
		if ((graph->Matrix)[edge.Vertex * (graph->CountVertices) + i] == 0) {
			continue;
		}
		TEdge currentEdge = {
			.MinPath = (long long)(graph->Matrix)[edge.Vertex * (graph->CountVertices) + i],
			.Parent = edge.Vertex,
			.Vertex = i
		};
		DecreaseKey(/*queue*/queue, /*pathToParent*/edge.MinPath, /*edge*/currentEdge);
	}
}

static bool FindPathsToVertices(TEdge* paths, const TGraph* graph, const short from) {
	TQueue queueOfAvailibleVerteces = CreateQueue(/*size*/graph->CountVertices);
	TEdge firstEdge = { .MinPath = 0, .Parent = SHRT_MAX, .Vertex = from };
	DecreaseKey(/*queue*/&queueOfAvailibleVerteces, /*pathToParent*/0ll, /*edge*/firstEdge);
	
	int indexInPaths = 0;
	while (queueOfAvailibleVerteces.HeapSize != 0) {
		TEdge edge = Get(/*queue*/&queueOfAvailibleVerteces);
		
		paths[indexInPaths] = edge;

		AddAvailibleVertecesToQueue(/*queue*/&queueOfAvailibleVerteces,
				/*graph*/graph,
				/*edge*/edge);
		++indexInPaths;
	}
	DestroyQueue(/*queue*/&queueOfAvailibleVerteces);

	return true;
}

static void PrintPathsToAllVertices(const TGraph* graph, const TEdge* paths) {
    for (int i = 0; i < graph->CountVertices; ++i) {
        if (paths[i].MinPath == LLONG_MAX) {
            printf("oo ");
        } else if (paths[i].MinPath > INT_MAX) {
            printf("INT_MAX+ ");
        } else {
            printf("%lld ", paths[i].MinPath);
        }
    }
    printf("\n");
}

static void PrintAllVerticesInPath(
        const TGraph* graph,
        const TEdge* paths,
        const short start,
        const short finish
) {
	int waysToFinish = 0;
	for (int i = 0; i < graph->CountVertices; ++i) {
		if ((graph->Matrix)[finish * (graph->CountVertices) + i] != 0) {
			++waysToFinish;
		}
	}

	if (paths[finish].MinPath == LLONG_MAX) {
		printf("no path");
	} else if (paths[finish].MinPath > INT_MAX && waysToFinish > 1) {
		printf("overflow");
	} else {
		int index = (int)finish;
		while(paths[index].Vertex != start) {
			printf("%d ", paths[index].Vertex + 1);
			index = paths[index].Parent;
		}
		printf("%d", paths[index].Vertex + 1);
	}
}

// end static


void Dijkstra(const TGraph* graph, const short from, const short to) {
    TEdge* paths = (TEdge*)calloc(graph->CountVertices, sizeof(TEdge));
    assert(paths);
	
    if (FindPathsToVertices(/*paths*/paths, /*graph*/graph, /*from*/from)) {
		qsort(paths, graph->CountVertices, sizeof(TEdge), Compare);
		PrintPathsToAllVertices(/*graph*/graph, /*paths*/paths);
		PrintAllVerticesInPath(/*graph*/graph, /*paths*/paths, /*start*/from, /*finish*/to);
    }
	
    free(paths);
}

TGraph CreateGraph(const int countVertices) {
	int* matrix = (int*)calloc(countVertices * countVertices, sizeof(int));
	assert(matrix);
	TGraph graph = {
		.Matrix = matrix,
		.CountVertices = countVertices,
	};
	return graph;
}

void DestroyGraph(TGraph* graph) {
	assert(graph);
	free(graph->Matrix);
	graph->CountVertices = 0;
}
