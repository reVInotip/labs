#include <stdio.h>
#include <stdlib.h>
#include "graph/graph.h"
#include "utils/utils.h"

int main(void) {
    int countVertices, countEdges;
    if (!scanf("%d", &countVertices)) {
        return EXIT_SUCCESS;
    }
    if (!scanf("%d", &countEdges)) {
        return EXIT_SUCCESS;
    }
    if (!CheckInput(/*countVertices*/countVertices, /*countEdges*/countEdges)) {
        return EXIT_SUCCESS;
    }

    TGraph graph = CreateGraph(/*countVertices*/countVertices);
	
    for (int i = 0; i < countEdges; ++i) {
        short start, end;
        long long length;
        if (scanf("%hd %hd %lld", &start, &end, &length) < 3) {
            printf("bad number of lines");
            DestroyGraph(/*graph*/&graph);
            return EXIT_SUCCESS;
        }
        if (!CheckVertex(/*vertex*/start, /*maxVertexNumber*/countVertices)) {
            DestroyGraph(/*graph*/&graph);
            return EXIT_SUCCESS;
        } else if (!CheckVertex(/*vertex*/end, /*maxVertexNumber*/countVertices)) {
            DestroyGraph(/*graph*/&graph);
            return EXIT_SUCCESS;
        } else if (!CheckLength(/*len*/length)) {
            DestroyGraph(/*graph*/&graph);
            return EXIT_SUCCESS;
        }
		
        graph.Matrix[(start - 1) * countVertices + (end - 1)] = (int)length;
        graph.Matrix[(end - 1) * countVertices + (start - 1)] = (int)length;
    }
	
    PrimMinimumSpanningTree(/*graph*/&graph);

    DestroyGraph(/*graph*/&graph);

    return EXIT_SUCCESS;
}
