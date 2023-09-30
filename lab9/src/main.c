#include "utils/utils.h"
#include "graph/graph.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int countVertices = 0, countEdges = 0;
    short from = 0, to = 0;
    if (scanf("%d", &countVertices) != 1) {
        printf("bad number of lines");
        return EXIT_SUCCESS;
    }
    if (scanf("%hd %hd", &from, &to) != 2) {
        printf("bad number of lines");
        return EXIT_SUCCESS;
    }
    if (scanf("%d", &countEdges) != 1) {
        printf("bad number of lines");
        return EXIT_SUCCESS;
    }
    
    if (!CheckInput(/*countVertices*/countVertices, /*countEdges*/countEdges)) {
        return EXIT_SUCCESS;
    } else if (!CheckVertex(/*vertex*/from, /*maxVertexNumber*/countVertices)) {
        return EXIT_SUCCESS;
    } else if (!CheckVertex(/*vertex*/from, /*maxVertexNumber*/countVertices)) {
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
	
    Dijkstra(/*graph*/&graph, /*from*/from - 1, /*to*/to - 1);

    DestroyGraph(/*graph*/&graph);

    return EXIT_SUCCESS;
}
