#include "./utils.h"
#include <limits.h>
#include <stdio.h>

_Bool CheckLength(const long long len) {
    if (len < 0 || len > INT_MAX) {
        printf("bad length\n");
        return false;
    }
    return true;
}

_Bool CheckInput(const int countVertices, const int countEdges) {
    if (countVertices < 0 || countVertices > 5000) {
        printf("bad number of vertices\n");
        return false;
    }
    if (countVertices == 0) {
        printf("no spanning tree\n");
        return false;
    }
    const int EDGES_MAX = countVertices * (countVertices - 1) / 2;
    if (countEdges < 0 || countEdges > EDGES_MAX) {
        printf("bad number of edges\n");
        return false;
    }
    return true;
}

_Bool CheckVertex(const int vertex, const int maxVertexNumber) {
    if (vertex < 1 || vertex > maxVertexNumber) {
        printf("bad vertex\n");
        return false;
    }
    return true;
}
