#include "utils.h"
#include <stdio.h>
#include <stdbool.h>

_Bool CheckInput(const int countVertices, const int countEdges) {
    if (countVertices < 0 || countVertices > 2000) {
        printf("bad number of vertices");
        return false;
    }

    const int MAX_COUNT_EDGES = countVertices * (countVertices + 1) / 2;
    if (countEdges < 0 || countEdges > MAX_COUNT_EDGES) {
        printf("bad number of edges");
        return false;
    }
    return true;
}

_Bool CheckVertices(const int start, const int end, const int maxNumber) {
    if (start < 1 || start > maxNumber || end < 1 || end > maxNumber) {
        printf("bad vertex");
        return false;
    }
    return true;
} 
